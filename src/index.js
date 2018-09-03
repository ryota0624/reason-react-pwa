import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import registerServiceWorker from './registerServiceWorker';
import {CREATED_TAG} from "./EventTypes";
import {startLogger} from "./LoggerService";
import {startNotification} from "./NotificationService";
import {ServiceProtocol} from "./SeriveProtocol";

document.addEventListener(ServiceProtocol, (ev) => {
  ev.detail.callback("STORE DONE!")
});

startLogger(document);
startNotification(document, document.body);


ReactDOM.render(<App />, document.getElementById('root'));
registerServiceWorker();