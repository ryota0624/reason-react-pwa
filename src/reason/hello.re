let component = ReasonReact.statelessComponent("hello");

let make = (_children, ~onSubmitMemo) => {
  ...component,
  render: _ => 
    <div>
      <Container.MemoContainer />
      <Container.TagContainer tagList=(GlobalState.getAllTags()) onSubmit=((tag) => { 
        GlobalState.addTag(tag);
        onSubmitMemo(tag.label)
      }) />
    </div>
};

[@bs.deriving abstract]
type jsProps = {
  onSubmitTag: string => unit
};

let jsComponent =
  ReasonReact.wrapReasonForJs(~component, jsProps =>
    make(
      ~onSubmitMemo=jsProps |> onSubmitTagGet,
      [||],
    )
  );