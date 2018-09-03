import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';
import * as ReasonHello from "./reason/hello";
import {createdTagEvent} from "./EventTypes";
import {AppRequestCustomEvent} from "./SeriveProtocol";

class App extends Component {
  render() {
    return (
      <div className="App">
        <ReasonHello.jsComponent onSubmitTag={(label) => {
          createdTagEvent(label);
          
          const request = new AppRequestCustomEvent("tag/store", (payload) => {
            console.log(payload);
          });

          request.dispatch();
        }}></ReasonHello.jsComponent>
      </div>
    );
  }
}

export default App;
