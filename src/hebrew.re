module D = Webapi.Dom;
module Doc = Webapi.Dom.Document;
module Elem = Webapi.Dom.Element;

let getValue = (element:option(Elem.t)) : option(string) => {
  element
    -> Belt.Option.map(_, Elem.unsafeAsHtmlElement)
    -> Belt.Option.map(_, D.HtmlElement.value);
};

let reset_focus () : unit = { /* https://practicalmadscience.com/by-example-focus-a-text-box-with-reasonml.html */
  switch (Webapi.Dom.Document.getElementById("entree", Webapi.Dom.document)) {
    | None => ()
    | Some(element) =>
      switch (Webapi.Dom.Element.asHtmlElement(element)) {
      | None => ()
      | Some(h) => Webapi.Dom.HtmlElement.focus(h)
      }
    }
};

let translate = (_:Dom.event) : unit=> {
  let entree = getValue(Doc.getElementById("entree",D.document));
  let traduc = ToHebrew.translate(entree);
  let _ = Doc.getElementById("result",D.document)
  -> Belt.Option.map(_,Elem.setInnerText(_,traduc));
};

let translater = Doc.getElementById("entree", D.document);

switch(translater) {
  | Some(element) => D.EventTarget.addEventListener(
    "input", translate, Elem.asEventTarget(element))
  | None => ()
};

let resetButton = Doc.getElementById("breset", D.document);

let reset = (_:Dom.event) : unit => {
  let _rightNow = [%raw {| function () {
      document.getElementById("entree").value = ""; 
      document.getElementById("result").innerHTML = "";
    }()
  |}];
  reset_focus(); 
  Js.log("called reset");
};

let copyButton = Doc.getElementById("bcopy", D.document);

let copyToClipboard = (_:Dom.event) : unit => {
  let _rightNow = [%raw {| function () {
    var textArea = document.createElement("textarea");textArea.style.position = 'fixed'; textArea.style.top = 0; textArea.style.left = 0;textArea.style.width = '2em'; textArea.style.height = '2em'; textArea.style.padding = 0;textArea.style.border = 'none'; textArea.style.outline = 'none'; textArea.style.boxShadow = 'none';textArea.style.background = 'transparent';
    textArea.value = document.getElementById("result").innerHTML;document.body.appendChild(textArea);textArea.select();
    try {var successful = document.execCommand('copy');var msg = successful ? 'successful' : 'unsuccessful';console.log('Copying text command was ' + msg);
    }catch (err) {console.log('Oops, unable to copy');}document.body.removeChild(textArea);    
    }()
  |}];
  reset_focus(); 
  Js.log("called copyToClipboard");
};

switch(resetButton) { 
  |Some(element) => D.EventTarget.addEventListener(
    "click",reset,Elem.asEventTarget(element))
  |None => ()
};

switch(copyButton) { 
  |Some(element) => D.EventTarget.addEventListener(
    "click",copyToClipboard,Elem.asEventTarget(element))
  |None => ()
};
