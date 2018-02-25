type log = string;
let make = (): log => "";
let logStr = (str: string, log: log): log => log ++ str ++ "\n";
let print = (log: log) => print_string(log);
