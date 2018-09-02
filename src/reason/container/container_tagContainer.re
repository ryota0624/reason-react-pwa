open Type.Tag;

let component = ReasonReact.statelessComponent("tag-container");

let make = (~onSubmit, ~tagList, _children) => {
  ...component,
  render: self => 
    <div>
      <View.Tag.Form onSubmit=(text => onSubmit({ label: text }) |> self.send) />
      <View.Tag.List tags=(tagList) />
    </div>
};