open Type.Tag;

let allTags: ref(list(tag)) = ref([]);

let allSubscribers: ref(Belt.Map.String.t(unit => unit)) = ref(Belt.Map.String.fromArray([||]));

let getAllTags = () => allTags^;

let publish = () => {
  let _ = allSubscribers^ |> Belt.Map.String.map(_, (subscribe) => {
    subscribe();
  })
}

let addTag = (tag) => {
  let _ = publish();
  allTags := ([allTags^, [tag]] |> List.concat) 
};

type subscriberToken = Token(string);

let subscribe: (unit => unit) => subscriberToken = (sub) => {
  let key = Js.Math.random() |> string_of_float;
  let updatedAllSubscriber = Belt.Map.String.set(allSubscribers^, key, sub);
  allSubscribers := updatedAllSubscriber;
  Token(key)
};

let unSubscribe = (token) => {
  let Token(t) = token;
  let updatedAllSubscriber = Belt.Map.String.remove(allSubscribers^, t);
  allSubscribers := updatedAllSubscriber;
};