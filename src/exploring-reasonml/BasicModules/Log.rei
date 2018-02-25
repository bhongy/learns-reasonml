type log; /* abstract type: we can change implementation */
let make: (unit) => log;
let logStr: (string, log) => log;
let print: (log) => unit;
