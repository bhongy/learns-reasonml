/**
 * Basic Modules
 * http://reasonmlhub.com/exploring-reasonml/ch_basic-modules.html
 *
 * The names of modules start with capital letters and are camel-cased.
 * File names define the names of their modules, so they follow the same rules.
 */

let main = () => {
  print_string("Hello world!");
  print_newline();

  print_int(MathTools.square(3));
  print_newline();
};

/* a pattern to ensure the execution doesn't return value */
/* alternative to just calling `main();` in global scope */
let () = {
  main();
};

/* modules can be nested */
/*
module S = {
  module Tools = {
    let times = (x, y) => x * y;
    let square = (x) => times(x, x);
  };
};

Math.Tools.square(3);
*/

let () = Log.make()
  |> Log.logStr("Hello")
  |> Log.logStr("everyone")
  |> Log.print;

let () = Log.(
  make()
  |> logStr("This opens the module locally")
  |> print
);

/*
module type LogWithDateInterface = {
  include (module type of Log); /* A */
  let logStrWithDate: (string, log) => log;
};

module LogWithDate: LogWithDateInterface = { ... };
*/

/* including a module: will include with the export of the module */
module LogWithDate = {
  include Log;
  let logStrWithDate = (str: string, log: log) => {
    let dateStr = Js.Date.toISOString(Js.Date.make());
    logStr("[" ++ dateStr ++ "] " ++ str, log);
  };
};

let () = LogWithDate.(
  /* notice `make` and `print` are exported as part of LogWithDate */
  make()
    |> logStrWithDate("Hello")
    |> logStrWithDate("everyone")
    |> print
);

/* alias module */
/* module L = List; */

/* alias a value from a module */
/* let m = List.map; */

/* Module `Pervasives` */
/*
  Zcore modules, automatically opened in all modules
  can also use `Pervasives.(op)` if the original is written
  1 + 2 == (+)(1, 2) == Pervasives.(+)(1, 2)
*/
