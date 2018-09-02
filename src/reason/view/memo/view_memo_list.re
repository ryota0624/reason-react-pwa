open Type.Memo;

let component = ReasonReact.statelessComponent("memo-list");

let make = (~memos, _children) => {
  ...component,
  render: _ => 
    <ul>
      (
        memos
          |> Belt.List.map(_, memo => <li> (memo.text |> ReasonReact.string) </li>)
          |> Array.of_list
          |> ReasonReact.array
      )
    </ul>
};
