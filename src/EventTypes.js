export const ApplicationEventPrefix = "APP_"
export const CREATED_TAG = ApplicationEventPrefix + "CREATED_TAG";

class AppCustomEvent {
  constructor(type, detail) {
    this.event = new CustomEvent(type, {detail});
  }

  dispatch(target = document) {
    target.dispatchEvent(this.event);
  }
}

export function createdTagEvent(label) {
  const event = new AppCustomEvent(CREATED_TAG, {label});
  event.dispatch();
}
