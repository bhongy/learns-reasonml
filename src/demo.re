Js.log("Hello, BuckleScript and Reason!");

/* From: http://reasonmlhub.com/exploring-reasonml/ch_syntax-overview.html */

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
