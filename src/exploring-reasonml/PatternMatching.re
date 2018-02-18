/**
 * Pattern matching
 * http://reasonmlhub.com/exploring-reasonml/ch_pattern-matching.html
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
