type method = [ | `DELETE | `GET | `PATCH | `POST];

let make:
  (
    ~url: string,
    ~method: method=?,
    ~body: 'a=?,
    ~contentType: string=?,
    ~responseType: string=?,
    unit
  ) =>
  Future.t(Belt.Result.t('b, Errors.t));
