type state = {
  inputValue: option(string)
};

type action = 
  InputText(string)
  | ClearInputText
  | Submit

let component = ReasonReact.reducerComponent("tag-form");

let handleInput = (handler, e) => ReactEvent.Form.target(e)##value |> handler;

let make = (~onSubmit, _children) => {
  ...component,
  initialState: () => { inputValue: None },
  reducer: (action, _) => {
    switch (action) {
    | InputText(text) => ReasonReact.Update({inputValue: Some(text)})
    | ClearInputText => ReasonReact.Update({inputValue: None})
    | Submit => {
        ReasonReact.SideEffects(self => {
          let _ = self.state.inputValue |> Belt.Option.map(_, onSubmit);
          self.send(ClearInputText);
        });
      }
    };
  },
  render: self => 
    <div>
      <input 
        onInput=(handleInput(text => self.send(InputText(text)))) 
        type_="text"
        placeholder={j|タグを入力してね！|j}
        value=(self.state.inputValue |> Js.Option.getWithDefault("")) 
      />
      <button type_="button" onClick=(_ => Submit |> self.send)> ( ReasonReact.string({j|保存|j}) ) </button>
      <button type_="button" onClick=(_ => ClearInputText |> self.send)> ( ReasonReact.string({j|クリア|j}) ) </button>
    </div>
};
