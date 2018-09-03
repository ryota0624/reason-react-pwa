import {CREATED_TAG} from "../EventTypes"
const observationEventTypes = [
    CREATED_TAG
  ];

export function startLogger(target) {
  observationEventTypes.forEach(eventType => {
    target.addEventListener(eventType, (ev) => {
      console.log(`
        --- start LoggerService log ---
        type: ${ev.type}
        detail: ${JSON.stringify(ev.detail)}
        --- end LoggerService log ---
      `)
    });
  });
}