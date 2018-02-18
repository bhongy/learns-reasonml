Js.log("Hello, BuckleScript and Reason!");

/* From: http://reasonmlhub.com/exploring-reasonml/toc.html */

/**
 * Basic types and operators
 */

/* comment /* nested comment */ this is nice! */
/* no single-line comment support - I think it's fine */

/* all bindings use `let` */
let x = 123;

/* function, first-class, just another let binding */
let add = (x, y) => x + y;

/* variant type */
type color = Red | Green | Blue;

/* pattern matching on the variant type */
let colorToString = (c: color) =>
  switch (c) {
  | Red => "red"
  | Green => "green"
  | Blue => "blue"
  };

/* calling a function */
Js.log(colorToString(Red));

/* most things are expressions */
let date = {
  let inFuture = true;
  let year = if (inFuture) "2024" else "2014";
  let month = "Jan";
  let day = "12";
  month ++ " " ++ day ++ ", " ++ year;
};
Js.log(date);

/* unused parameters cause warning */
/* let identity = (x, y) => x; */

/* prefix with _ to suppress unused param warning */
let identity2 = (x, _y) => x;

/* suffix with ' denotes a mutated version of a variable  */
let count = 20;
let count' = count + 10;

/* integer division resulted in integer */
Js.log("5 / 3 => " ++ string_of_int(5 / 3));

/* math operations on floats - notice trailing `.` */
Js.log("2. *. 3. => " ++ string_of_float(2. *. 3.));
Js.log("5. /. 3. => " ++ string_of_float(5. /. 3.));

/* ReasonML strings are encoded as UTF-8 */
Js.log("äöü");
/* short-term work-around use BuckleScript's Javascript strings */
Js.log({js|äöü|js});

/* char and string are not the same
  ---
  'x'; - : char = 'x'
  String.get("abc", 1); - : char = 'b'
  "abc".[1];
*/

/* unit type `();` */

/* `==` compares values even for reference types
  ---
  [1,2,3] == [1,2,3]; - : bool = true
*/

/* `===` compares references
  ---
  [1,2,3] === [1,2,3]; - : bool = false
*/

/**
 * `let` bindings and scopes
 */

/* `let` bindings are immutable
  - cannot re-assign values
  - must immediately initialize the variable
  - but you can redefine it (calling `let <var> = ...` again)
*/

/* type annotation: `let y: string = "abc";` */

/* use blocks `{ ... };` to create new scope
  ---
  remember - blocks are also expression
  its value is the value of the last expression inside it
  - i.e. implicitly return the value of its last expression
*/

/**
 * Pattern matching
 */

/* The same variable name cannot be used multiple times in a tuple */
/* (x, x) is illegal. */

/* using variable names in pattern matching will bind the values
  to the variables - e.g. (x, y) (1, 4) will match and bind x = 1, y = 4
  use `_` as "ignore" (will match anything) - can use multiple times
 */

/* destructuring */
/* let (x, y) = (7, 4); -> x = 7, y = 4 */
/* let (a, _) = (7, 4); -> a = 7 */
/* non-matching will throw. */
/* let (1, x) = (5, 5); */

/* switch: Reason checks for exhaustive pattern matching */
{
  let result = switch 3 {
    | 1 => "one"
    | 2 => "two"
    /* default */
    | x => "unknown: " ++ string_of_int(x)
    /* or */
    /* | _ => "unknown" */
    };
  Js.log(result);

  let tuple = (8, (5, 9));
  let result2 = switch tuple {
  | (0, _) => (0, (0, 0))
  /* inner as `t` and pick `x` out - return `x` with inner */
  | (_, (x, _) as t) => (x, t)
  };
  /* result == (5, (5, 9)) */
  Js.log(result2);

  switch (0, 2) /* tuple */ {
  | (0, 1 | 2 | 3) => "first branch"
  | _ => "second branch"
  }
  |> ignore;

  /* can also be used at the top level */
  switch "Monday" {
  | "Monday"
  | "Tuesday"
  | "Wednesday"
  | "Thursday"
  | "Friday" => "weekday"
  | "Saturday"
  | "Sunday" => "weekend"
  | day => "Illegal value: " ++ day
  };
  /* Result: "weekday" */
};

/* `if` expressions
  ---
  - returns value (it's an expression)
  - can omit "else" but "then" must return `unit`
    /* okay: if (true) print_string("hello\n"); */
    /* error: if (true) "abc"; */
 */
