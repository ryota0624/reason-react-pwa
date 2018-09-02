open Type.Tag;


let getAllTags: unit => list(tag);

let addTag: tag => unit;

type subscriberToken;

let subscribe: (unit => unit) => subscriberToken;

let unSubscribe: subscriberToken => unit;