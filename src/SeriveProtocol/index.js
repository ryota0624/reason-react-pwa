export const ServiceProtocol = "ServiceProtocol"

export class AppRequestCustomEvent {
  constructor(method, callback) {
    this.event = new CustomEvent(ServiceProtocol, {detail: { method, callback }});
  }

  dispatch(target = document) {
    target.dispatchEvent(this.event);
  }
}