export function renderNotificationBar(message, target) {
  const id = `notification-service-view-${Math.random()}`;
  const msg = `<span id="${id}" style="color: red;">${message}</span>`
  const tmpSpane = document.createElement("span");

  tmpSpane.innerHTML = msg;
  target.appendChild(tmpSpane.children[0]);
  return id;
}