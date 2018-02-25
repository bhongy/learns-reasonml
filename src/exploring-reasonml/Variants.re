/**
 * Variants
 * http://reasonmlhub.com/exploring-reasonml/ch_variants.html
 */

/*
  type name must starts with lowercase
  type values (constructors) must start with uppercase
  `type color = Red | Blue;`
*/

/* **In ReasonML, variants are often a better choice than booleans.**

type includeDetails = ShowEverything | HideDetails;
let stringOfContact(~levelOfDetail: includeDetails, c: contact) => ···;
let str = stringOfContact(~levelOfDetail=ShowEverything, myContact);
*/

/* constructors can take arguments - e.g. `Point(float, float)` */

/* notice `Empty` and `Node` constructors also available to use */
type intTree =
  | Empty
  | Node(int, intTree, intTree);

/* notice constructor `Node` is available */
let myIntTree =
  Node(1,
    Node(2, Empty, Empty),
    Node(3,
      Node(4, Empty, Empty),
      Empty
    )
  );

let rec computeSum = (t: intTree) =>
  switch t {
  | Empty => 0
  | Node(i, leftTree, rightTree) =>
    i + computeSum(leftTree) + computeSum(rightTree)
  };

Js.log2("computeSum(myIntTree) = ", computeSum(myIntTree)); /* 10 */

/* mutually recursive data structure with variants */
/*
  type intTree =
    | Empty
    | IntTreeNode(intNode)
  and intNode =
    | IntNode(int, intTree, intTree);
*/

/* parameterized variants (generics) */
type tree('a) =
  | Empty
  | Node('a, tree('a), tree('a));

/**
 * @param ~indent How much to indent the current (sub)tree.
 * @param ~valueToString Converts node values to strings.
 * @param t The tree to convert to a string.
 */
/* notice `'a` is inferred */
let rec treeToString = (
  ~indent = 0,
  ~valueToString: 'a => string,
  t: tree('a)
) => {
  let indentStr = String.make(indent * 2, ' ');
  switch t {
  | Empty => indentStr ++ "-" ++ "\n"
  | Node(x, leftTree, rightTree) =>
    indentStr ++ valueToString(x) ++ "\n" ++
    treeToString(~indent = indent + 1, ~valueToString, leftTree) ++
    treeToString(~indent = indent + 1, ~valueToString, rightTree)
  };
};

let () = {
  /* `'a` is inferred */
  let myStrTree =
    Node("a",
      Node("b", Empty, Empty),
      Node("c",
        Node("d", Empty, Empty),
        Empty
      )
    );

  Js.log("\nPrint string tree ...");
  Js.log("# # # # # # # # #");
  print_string(treeToString(~valueToString = x => x, myStrTree));
  Js.log("# # # # # # # # #");
};

/* example: evaluating integer expressions */
type expression =
  | Add(expression, expression)
  | Subtract(expression, expression)
  | Multiply(expression, expression)
  | Divide(expression, expression)
  | Literal(int);

let rec eval(e: expression) =
  switch e {
  | Add(e1, e2) => eval(e1) + eval(e2)
  | Subtract(e1, e2) => eval(e1) - eval(e2)
  | Multiply(e1, e2) => eval(e1) * eval(e2)
  | Divide(e1, e2) => eval(e1) / eval(e2)
  | Literal(e_) => e_
  };

let () = {
  /* (3 - (16 / (6 + 2)) */
  let expr =
    Subtract(
      Literal(3),
      Divide(
        Literal(16),
        Add(
          Literal(6),
          Literal(2)
        )
      )
    );

  Js.log2("\n(3 - (16 / (6 + 2)) = ", eval(expr)); /* 1 */
};
