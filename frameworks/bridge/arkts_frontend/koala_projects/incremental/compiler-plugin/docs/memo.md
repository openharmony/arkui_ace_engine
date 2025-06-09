# Memo functions for Koala runtime

## Annotations

There are five annotations used by the incremental runtime plugin

   * @memo
   * @memo:intrinsic
   * @memo:entry
   * @skip:memo


## Syntax

The annotations are accepted at the following syntactic positions:


### Function declaration

```
/** @memo */
function foo() {}
```

Function declarations can also be marked as `@memo:intrinsic`.

### Method declaration

```
class X {
    /** @memo */
    foo() {}
}
```

Method declarations can also be marked as `@memo:intrinsic`.


### Parameters of functional type

```
function foo(
    /** @memo */
    arg1: () => void
)
```

### A variable

Note that (currently) the declaration needs to be applied after let or const.
```
let
    /** @memo */
    x
```

### Arrow function literal
```
    /** @memo */
    () => {...}
```

### Function function literal
```
    /** @memo */
    function foo() {...}
```

### Property declaration
```
class X {
    /** @memo */
    public p
}
```

### Function type declaration
```
function foo():
    /** @memo */
    () => void
```

### Memo code entry pointes @memo:entry
The places where regular code is allowed to enter memo realm are denoted @memo:entry.
The functions marked with @memo:entry are not memo themselves,
but they must provide enough implementation defined lexical context
for the memo call to succeeed in their bodies.

For example

```
/** @memo:entry */
function entry(
    __memo_context: Context,
    __memo_id: MemoId,
    /** @memo */
    ui: () => void
) {
    ui()
}
```

### @skip:memo

For obscure implementation machinery we sometimes need to exclude arguments
from positional memoization tracking.
This is done using @skip:memo annotation.
For example:

```
/** @memo */
function foo(
    /** skip:memo */
    compute:() => void,
    int: arg
){}
```

## Inference and defaults

At the moment we do the following inference allowing the user to omit memo markings.

### Call sites don't need special marks

No special marking at the call site is needed.
Any call to an entity marked with @memo
(functions, methods, properties of functional types, variables of functional types, parameters of functional types etc)
including the entities declared in other modules
is automatically rewritten by the compiler.

### Lambda literal arguments

Lambda literals passed as arguments to parameters marked as memo are treated by memo by default. For example:

```
function foo(
    /** @memo */
    content: () => void
) {
    ...
}


foo(() => { // This lambda literal is assumed to be memo!
    ...
})
```

## Semantics

Functions marked with @memo provide "positional memoisation semantics".
A function call, instead of evaluating the function again, returns the
same (memoized) value as the previous call at the same call site (position).
Unless any of thow things happens:
  1. A value of any argument is changed
  2. Any state object the function is subscribed (see below) to is changed.


### State variable

State variables are objects implementing an interface (we omit some details for clarity):

```
interface State<T> {
    value: T
}
```

State variables are managed by the incremental runtime.
Reading and writing the state variables happens by calling the getter or the setter of the .value field.


### Subscription

A memo function or a memo lambda subscribes to a state variable by the fact of reading its value.


## Constraints

### memo code and state variables

A memo function can only read state variable values.
A memo code can not write to a state variable.

An attempt to assign a state variable will cause a compiler diagnostics or a runtime error.

A memo function can create a non-memo lambda which contains an assignment to a state variable.
Such lambda can be called outside of memo context and is allowed to change the state variable value.


### memo should only be called from memo code

Any memo function should be called from another memo function.
An attempt to call a memo function in non-memo code will result in compiler diagnostics or a runtime error.

See @memo:entry description for the details on how the implementation can initiate memo call sequence.

Calling a non-memo code is allowed.
Although it is a good practice to call only pure functions without side effects.
As the memo function body is typically omitted because of positional memoisation.


## Implementation

### Jsdoc annotations

The current annotations are implemented as jsdoc annotations, rather than TS decorators.
That is the annotations should be placed into "double star" comments. For example:

```
/** @memo */
```

That allows to apply the annotations at all the places we need and where
TS decorators can not be applied.
In particular at the global function declarations.

On the other hand it brings some complications. Such as jsdoc annotations
need to be placed at the previous line. For example

```
/** @memo */ function foo() {} // This one doesn't work :-(

/** @memo */
function foo() {}  // This one works
```

### The rewrite

### Rewrite for @memo

Any @memo declaration basicly wraps the body of the function into a lambda.
And adds a code to cache the previous results and side effects.
And to check if arguments or state variable in the body have changed so there is a need to recompute the body.
And inserts two additional arguments: an instance of the state manager and the positional id to have separate caches for each call site.

The rewrite is performed at the declaration as well as at the call site.

### Rewrite for @memo:intrinsic

For the @memo:intrinsic functions only the signature is rewritten with additional arguments.
No wrapping in lambda or caching is performed.
It is typically used for implementation of incremental runtime primitives.

### @skip:memo effect on rewrite

When an argument is marked as @skip:memo it is excluded from machinery to compare this parameter and trigger body recompute.

### @memo:entry effect on rewrite

The enclosing context should provide implementation defined lexical means for the entry function call to resove its incremental runtime context argument and initial value of positional ids.


