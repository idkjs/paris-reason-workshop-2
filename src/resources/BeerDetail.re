type t = {
  id: int,
  name: string,
  image_url: string,
  description: string,
};

let fromJs = jsBeer => {
  id: jsBeer##id,
  name: jsBeer##name,
  image_url: jsBeer##image_url,
  description: jsBeer##description,
};
// curl https://api.punkapi.com/v2/beers?brewed_before=11-2012&abv_gt=6
let query = (~id) => {
  Request.make(~url=Environment.apiUrl ++ "beers/" ++ id, ())
  ->Future.mapOk(item => fromJs(item[0]));
};
