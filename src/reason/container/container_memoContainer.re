open Type.Memo;

type state = {
  memoList: list(Type_memo.memo), 
};

type action = 
  AppendMemo(string)
  | ForceUpdate;

let component = ReasonReact.reducerComponent("memo-container");

let make = (_children) => {
  ...component,
  initialState: () => { memoList: [] },
  didMount: (self) => {
    let token = GlobalState.subscribe(() => {
      self.send(ForceUpdate);
    });

    self.onUnmount(() => GlobalState.unSubscribe(token));
  },
  reducer: (action, state) => {
    switch (action) {
    | AppendMemo(text) => ReasonReact.Update({ memoList: state.memoList |> List.append(_, [{ 
        text: text,
        createdAt: Js.Date.fromFloat(Js.Date.now())
      }]) })
    | ForceUpdate => ReasonReact.Update(state);
    };
  },
  render: self => 
    <div>
      <View.Memo.Form tags=(GlobalState.getAllTags()) onSubmit=(text => AppendMemo(text) |> self.send) />
      <View.Memo.List memos=(self.state.memoList) />
    </div>
};