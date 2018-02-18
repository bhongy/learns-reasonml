/**
 * Functions
 * http://reasonmlhub.com/exploring-reasonml/ch_functions.html
 */

let plus1 = (x) => x + 1;
Js.log(plus1(5));
/* List.map(plus1, [1, 2, 3, 4]); */

/* mutually recursive function */
let rec even = (x) => x <= 0 ? true : odd(x - 1)
and odd = (x) => even(x - 1);

let logBool = (x) => Js.log(string_of_bool(x));
logBool(even(2));
logBool(even(3));
logBool(odd(3));

let rec factorial = (x) =>
  if (x <= 1) 1 else x * factorial(x - 1);

Js.log2("factorial(0) =>", factorial(0)); /* 1 */
Js.log2("factorial(1) =>", factorial(1)); /* 1 */
Js.log2("factorial(3) =>", factorial(3)); /* 6 */
Js.log2("factorial(4) =>", factorial(4)); /* 24 */

/* calling a function without parameters is the same as calling it with a unit `()`
  ---
  these two are the same:
  func()
  func(())
*/

/* labeled parameter */
let subtract = (~x, ~y) => x - y;
{
  /* At call sites, you can abbreviate ~x=x as just ~x: */
  let x = 10;
  let y = 20;
  /* can invoke with any order of params - it's labeled */
  Js.log2("10 - 20 =>", subtract(~y, ~x)); /* -10 */
  /* however, function types are only compatible
    if labels are mentioned in the same order
  */
};

/* optional parameters: only support labeled params */
/* need at least one positional parameter */
let add = (~x=?, ~y=?, ()) =>
/* let add = (~x: option(int)=?, ~y: option(int)=?, ()) => */
  switch (x, y) {
  | (Some(x'), Some(y')) => x' + y'
  | (Some(x'), None) => x'
  | (None, Some(y')) => y'
  | (None, None) => 0
  };
Js.log2("1 + 2 =>", add(~x=1, ~y=2, ()));

/* default values */
let add2 = (~x=0, ~y=0, ()) => x + y;
Js.log2("0 + 4 =>", add2(~y=4, ()));

/* passing `option` values to optional parameter */
let multiply = (~x=1, ~y=1, ()) => x * y;
{
  /* syntax for passing option: `~label = ?expression`
    can shorten to `~label?` if variable is the same name as label
  */
  let x = Some(15);
  let z = Some(10);
  /* the unit `()` in type signature allows calling with no parameters
    the unit `()` is required to clarify the call (use default) from
    partially applied the labeled optional parameters
  */
  Js.log2("1 * 1 =>", multiply());
  Js.log2("15 * 1 =>", multiply(~x?, ()));
  Js.log2("10 * 2 =>", multiply(~x=?z, ~y = ?Some(2), ()));
};
/* so the caller doesn't have to define default value
  and rely on the callee's default
*/
let square = (~x=?, ()) => multiply(~x?, ~y=?x, ());
Js.log2("square(7) =>", square(~x=7, ()));
Js.log2("square() =>", square());

/* partially application and optional parameters
  # let add2 = (~x=0, ~y=0, ()) => x + y;

  /* partially applied */
  # add(~x=3);
  - : (~y: int=?, unit) => int = <fun>

  /* no partial application if provide positional parameter */
  # add(~x=3, ());
  - : int = 3
*/

/* all functions in ReasonML are automatically curried */
/* the following two types are equivalent:
  (int, int) => int
  int => int => int
*/

/* The reverse-application operator (|>) :: the _pipe_ operator */
Js.log(
  4
  |> x => x * 2
  |> string_of_int
  |> s => s ++ s
);

/* important tips from: http://reasonmlhub.com/exploring-reasonml/ch_functions.html */
/*
  • If a function has a single primary parameter, make it a positional parameter and put it at the end. **That supports the pipe operator for function composition.**
  • Some functions have multiple primary parameters that are all similar. Turn these into multiple positional parameters at the end. An example would be a function that concatenates two lists into a single list. In that case, both positional parameters are lists.
  • All other parameters should be labeled.
  • If there are two or more primary parameters that are different, all of them should be labeled.
  • If a function has only a single parameter, it tends to be unlabeled, even if it is not strictly primary.
*/
