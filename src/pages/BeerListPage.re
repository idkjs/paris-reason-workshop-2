module Styles = {
  open Css;
  let item =
    style([
      padding(10->px),
      borderBottomWidth(1->px),
      borderBottomStyle(solid),
      borderBottomColor(rgba(0, 0, 0, `num(0.1))),
      display(flexBox),
      flexDirection(row),
      alignItems(center),
    ]);
  let text = style([marginLeft(20->px)]);
};

[@react.component]
let make =
    (
      ~beerList: RequestStatus.t(Belt.Result.t(array(BeerList.t), Errors.t)),
      ~onLoadRequest,
      _,
    ) => {
  React.useEffect0(() => {
    {
      switch (beerList) {
      | NotAsked => onLoadRequest()
      | _ => ()
      };
    };
    None;
  });

  <div>
    {switch (beerList) {
     | NotAsked => React.null
     | Loading => React.string("Loading")
     | Done(Error(_)) => React.string("Request failed")
     | Done(Ok(beers)) =>
       beers
       ->Belt.Array.map(beer =>
           <a
             href={"/beers/" ++ string_of_int(beer.id)}
             onClick={event => {
               event->ReactEvent.Mouse.preventDefault;
               ReasonReact.Router.push("/beers/" ++ string_of_int(beer.id));
             }}
             className=Styles.item
             key={beer.id->string_of_int}>
             <img src={beer.image_url} width="32" alt="" />
             <div className=Styles.text> beer.name->React.string </div>
           </a>
         )
       ->React.array
     }}
  </div>;
};
