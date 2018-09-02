let component = ReasonReact.statelessComponent("hello");

let make = (_children, ~message, ~onSubmitMemo) => {
  ...component,
  render: _ => 
    <div>
      (ReasonReact.string(message))
      <Container.MemoContainer />
      <Container.TagContainer tagList=(GlobalState.getAllTags()) onSubmit=(GlobalState.addTag) />
    </div>
};

[@bs.deriving abstract]
type jsProps = {
  message: string,
  onSubmitMemo: string => unit
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~message=jsProps |> messageGet,
      ~onSubmitMemo=jsProps |> onSubmitMemoGet,
      [||],
    )
  );