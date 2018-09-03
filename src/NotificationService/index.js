import {CREATED_TAG} from "../EventTypes";
import {renderNotificationBar} from "./view";

export function startNotification(target, renderTarget) {
  target.addEventListener(CREATED_TAG, (event) => {
    const id = renderNotificationBar("タグ: " + event.detail.label + "が作成されました", renderTarget);
    setTimeout(() => {
      const notificationDom = document.getElementById(id);
      renderTarget.removeChild(notificationDom);
    }, 2000)
  });
}