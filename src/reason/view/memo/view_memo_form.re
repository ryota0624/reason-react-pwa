open Type.Tag;

module TagSelector = {
  type selectors = list(option(string));

  type state = {
    selectors: selectors
  };

  let initialState = { selectors : [] };

  type event = IncreaseSelector | Reset;

  let handleEvent = (e, state: state) => {
    switch (e) {
    | IncreaseSelector => { selectors : state.selectors |> List.append([None]) }
    | Reset => { selectors : [] }
    };
  }

  let component = ReasonReact.statelessComponent("memo-tag-selector");

  let make = (~onChange, ~state: state, ~tags, _children) => {
    ...component,
    render: _ => {
      let selectorElements = state.selectors
        |> List.mapi ((i, selectedTag) => {
          <select 
            key={j|memo-tag-selector-select-$i|j} 
            value=(selectedTag |> Js.Option.getWithDefault(""))
          >
          (
            tags
              |> List.map(tag => <option> (tag.label |> ReasonReact.string) </option>)
              |> Array.of_list
              |> ReasonReact.array
          )
        </select>
        });
      <div>
        <button type_="button" onClick=(_ => onChange(handleEvent(IncreaseSelector, state))) > ("+" |> ReasonReact.string) </button>
        (selectorElements |> Array.of_list |> ReasonReact.array)
      </div>
    }
  };

}

type state = {
  inputValue: option(string),
  tagSelector: TagSelector.state
};

type action = 
  InputText(string)
  | ClearInputText
  | Submit
  | ChangeTagSelector(TagSelector.state)

let component = ReasonReact.reducerComponent("memo-form");

let handleInput = (handler, e) => ReactEvent.Form.target(e)##value |> handler;

module EventBus = {
  let subscribers: ref(Belt.Map.String.t(unit => unit)) = ref(Belt.Map.String.fromArray([||]));

  let subscribe = (subscriber) => {
    let key = Js.Math.random() |> string_of_float;
    let updatedAllSubscriber = Belt.Map.String.set(subscribers^, key, subscriber);
    subscribers := updatedAllSubscriber;
    key
  };

  let publish = () => {
    let _ = subscribers^ |> Belt.Map.String.map (_, sub => sub());
  }
}

let make = (~tags, ~onSubmit, _children) => {
  ...component,
  initialState: () => { inputValue: None, tagSelector: TagSelector.initialState },
  reducer: (action, state) => {
    switch (action) {
    | InputText(text) => ReasonReact.Update({...state, inputValue: Some(text)})
    | ClearInputText => ReasonReact.Update({...state, inputValue: None})
    | Submit => {
        ReasonReact.SideEffects(self => {
          let _ = self.state.inputValue |> Belt.Option.map(_, onSubmit);
          self.send(ClearInputText);
          self.send(ChangeTagSelector(TagSelector.initialState))
        });
      }
    | ChangeTagSelector(selector) => {
        ReasonReact.Update({...state, tagSelector: selector })
      }
    };
  },
  render: self => 
    <div>
      <input 
        onInput=(handleInput(text => self.send(InputText(text)))) 
        type_="text"
        placeholder={j|メモを入力してね！|j}
        value=(self.state.inputValue |> Js.Option.getWithDefault("")) 
      />
      <TagSelector tags state={self.state.tagSelector} onChange=(state => ChangeTagSelector(state) |> self.send) />
      <button type_="button" onClick=(_ => Submit |> self.send)> ( ReasonReact.string({j|保存|j}) ) </button>
      <button type_="button" onClick=(_ => ClearInputText |> self.send)> ( ReasonReact.string({j|クリア|j}) ) </button>
    </div>
};
