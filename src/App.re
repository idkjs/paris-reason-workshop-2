include CssReset;

type state = {
  beerList: RequestStatus.t(Belt.Result.t(array(BeerList.t), Errors.t)),
  beers:
    Belt.Map.String.t(
      RequestStatus.t(Belt.Result.t((float, BeerDetail.t), Errors.t)),
    ),
};

type action =
  | LoadBeerList
  | ReceiveBeerList(Belt.Result.t(array(BeerList.t), Errors.t))
  | LoadBeerDetail(string)
  | ReceiveBeerDetail(string, Belt.Result.t(BeerDetail.t, Errors.t));

module Styles = {
  open Css;
  let contents =
    style([
      display(flexBox),
      flexDirection(column),
      alignItems(stretch),
      flexGrow(1.0),
    ]);
};

[@react.component]
let make = _ => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | LoadBeerList => {...state, beerList: Loading}
        | ReceiveBeerList(beerList) => {...state, beerList: Done(beerList)}
        | LoadBeerDetail(id) => {
            ...state,
            beers: state.beers->Belt.Map.String.set(id, Loading),
          }
        | ReceiveBeerDetail(id, payload) => {
            ...state,
            beers:
              state.beers
              ->Belt.Map.String.set(
                  id,
                  Done(payload->Belt.Result.map(ok => (Js.Date.now(), ok))),
                ),
          }
        },
      {beerList: NotAsked, beers: Belt.Map.String.empty},
    );
  let url = ReasonReactRouter.useUrl();
  let loadBeerDetail = id => {
    BeerDetail.query(~id)
    ->Future.get(payload => dispatch(ReceiveBeerDetail(id, payload)));
  };
  let loadBeerList = () => {
    BeerList.query()
    ->Future.get(payload => dispatch(ReceiveBeerList(payload)));
  };
  React.useEffect0(() => {
    loadBeerList();
    None;
  });
  <>
    <Header />
    <div className=Styles.contents>
      {switch (url.path) {
       | [] =>
         <BeerListPage
           onLoadRequest={() => loadBeerList()}
           beerList={state.beerList}
         />
       | ["beers", id] =>
         <BeerDetailPage
           onLoadRequest={() => {
             Js.log("load beer detail");
             loadBeerDetail(id);
           }}
           beer={
             state.beers
             ->Belt.Map.String.get(id)
             ->Belt.Option.getWithDefault(NotAsked)
           }
         />
       | _ => React.string("Error: Route not found")
       }}
    </div>
    <Footer />
  </>;
};
