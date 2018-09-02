open Type.Tag;

let component = ReasonReact.statelessComponent("tag-list");

let make = (~tags, _children) => {
  ...component,
  render: _ => 
    <ul>
      (
        tags
          |> Belt.List.map(_, tag => <li> (tag.label |> ReasonReact.string) </li>)
          |> Array.of_list
          |> ReasonReact.array
      )
    </ul>
};
