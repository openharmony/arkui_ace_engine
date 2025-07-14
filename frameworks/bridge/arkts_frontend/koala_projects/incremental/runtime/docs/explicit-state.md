# Primitives for Explicit State Objects and Positional Memoization

## Explicit State Interfaces

The explicit state management interface allows to manipulate states as regular ArkTS objects. 
This kind of primitive has proven to be useful in the industry and in our own experimental work.
It is a convenient implementation primitive. And it is a convenient user expression primitive.

### The benefits

#### Typing benefit

The state objects explicitly differentiate the type of the value and the type of the state.

#### Storage freedom

The state objects can be stored global variables, local variables, class properties. They can be passed as function arguments. They can be placed in arrays and other standard data structures.

#### Behaviour freedom

The state interfaces are quite generic. But the implementation can be different. The state value updates can be done explicitly by user code (this is MutableState, see below), state values can be updated by implementation library, state value can change according some internal time based law allowing animated behavior.

### The basic API structure

The API consists of several areas:

   * State objects: several interfaces describing state abstraction
   * Helper constructor functions that allow instantiate different kinds of states.
   * "Construct and attach" helper functions. They instantiate a state of some kind and attach them to the tree.

### The Interface

#### State

The most basic state interface is quite simple.

```
/**
 * Individual state, wrapping a value of type `Value`.
 */
export interface State<Value> {
    /**
     * If state was modified since last UI computations.
     */
    readonly modified: boolean
    /**
     * Current value of the state.
     * State value doesn't change during memo code execution.
     */
    readonly value: Value
}
```
#### MutableState

The most commonly used interface is 

```
/**
 * Individual mutable state, wrapping a value of type `Value`.
 */
export interface MutableState<Value> extends Disposable, State<Value> {
    /**
     * Current value of the state as a mutable value.
     * You should not change state value from a memo code.
     * State value doesn't change during memo code execution.
     * In the event handlers and other non-memo code
     * a changed value is immediately visible.
     */
    value: Value
}
```
#### ComputableState

```

/**
 * Individual computable state that provides recomputable value of type `Value`.
 */
export interface ComputableState<Value> extends Disposable, State<Value> {
    /**
     * If value will be recomputed on access.
     */
    readonly recomputeNeeded: boolean
}

```

### Constructor functions

#### mutableState

There is a constructor function to simplify instantiation of MutableState objects:

```
/**
 * Creates new mutable state in the global state manager.
 * This state is valid until it is manually detached from the manager.
 * It will be detached automatically if it is in the {@link remember}.
 * Note that thoughtless state disposing can lead to memory leaks.
 * @param value - initial value to initialize the created state
 * @param equivalent - optional value comparator for a state
 * @param tracker - optional tracker of values assigned to a state
 * @returns new mutable state trackable by memo-functions
 */
export function mutableState<T>(value: T, equivalent?: Equivalent<T>, tracker?: ValueTracker<T>): MutableState<T>
```

### Attachment Interfaces

#### remember()

The state objects can be cached in the UI tree. The basic attachment primitive is `remember`

```

/**
 * It calculates the value of the given lambda and caches its result.
 * In contrast to the `memo` function, the given lambda is calculated only once
 * even if it uses values of states (including parameters of @memo-functions).
 *
 * @param compute - a function to compute cacheable result
 * @returns the last calculated value
 * @see memo
 */
export function remember<Value>(compute: () => Value): Value

```

#### memo()

```

/**
 * It calculates the value of the given lambda and caches its result.
 * In contrast to the `remember` function, the given lambda can be recalculated
 * if it uses values of states (including parameters of @memo-functions).
 * If the given lambda does not use any state, it will be calculated only once.
 *
 * @param compute - a function to compute cacheable result
 * @returns the last calculated value
 * @see remember
 * @experimental
 */
export function memo<Value>(compute: () => Value): Value
```

### Construct and remember helper functions

#### rememberMutableState()

This is the most regular instantiate+remember helper function.

```

/**
 * Creates remembered state which can be updated from anywhere,
 * and if changed - all depending memo functions recache automatically.
 * Note that you can specify the value directly for primitive values,
 * which do not require computations or memory allocation.
 * It is highly recommended to provide a lambda for all others values.
 *
 * @param initial - initial value supplier used on the state creation
 * @returns a state remembered for the current code position
 * @memo:intrinsic
 */
export function rememberMutableState<Value>(initial: (() => Value) | Value): MutableState<Value>
```

#### rememberMutableAsyncState()

```
/**
 * Remember mutable state which is computed in async way and is undefined if promise
 * is not fulfilled.
 *
 * @param compute function returning promise to compute the state
 * @param initial value stored to the state
 * @param onError callback called if promise was rejected
 * @memo
 */
export function rememberMutableAsyncState<Value>(compute: () => Promise<Value | undefined>, initial?: Value, onError?: (error: Error) => void): MutableState<Value | undefined>
```
#### rememberComputableState()

```
/**
 * Remember mutable state which is
 * re-computed in async way if key has changed
 * and undefined while promise is not fulfilled.
 *
 * @param key a value to trigger state recomputation
 * @param compute function returning promise to compute the state
 * @param initial value stored to the state
 * @param onError callback called if promise was rejected
 * @memo
 */
export function rememberComputableState<Key, Value>(
    key: Key,
    /** @skip:memo */
    compute: (key: Key) => Promise<Value | undefined>,
    initial?: Value,
    onError?: (error: Error) => void
): MutableState<Value | undefined>
```

#### rememberDisposableValue()

```

/**
 * It calculates the value of the given lambda, caches its result,
 * and notifies, that this method is removed from the composition.
 *
 * @param compute - a function to compute cacheable result
 * @param cleanup - a function to cleanup computed result on dispose
 * @returns the last calculated value
 * @see remember
 * @memo:intrinsic
 */
export function rememberDisposable<Value>(compute: () => Value, cleanup: (value: Value | undefined) => void): Value

```

#### rememberComputableValue()

```
/**
 * Remember a value which is
 * re-computed in async way if key has changed
 * and undefined while promise is not fulfilled.
 *
 * @param key a value to trigger state recomputation
 * @param compute function returning promise to compute the state
 * @param initial value stored to the state
 * @param onError callback called if promise was rejected
 * @memo
 */
export function rememberComputableValue<Key, Value>(
    key: Key,
    /** @skip:memo */
    compute: (key: Key) => Promise<Value | undefined>,
    initial?: Value,
    onError?: (e: Error) => void
): Value | undefined

```

### Context local

Context local state is a kind of state that allows named state scopes on the tree.


#### contextLocalScope()

Creates a state, gives it a name and attaches it to the tree

```
/**
 * Creates a named state with the specified value in the context scope.
 * The specified value will be propagated immediately during recomposition.
 * Note that the state name must not be dynamically changed.
 *
 * @param name - a name of a context state
 * @param value - a value of a named state to share within the given content
 * @param content - a scope content in which a named state is available
 * @memo:intrinsic
 */
export function contextLocalScope<Value>(
    name: string,
    value: Value,
    @memo
    content: () => void
)
```

#### contextLocal()

Finds the closest attached state with the given name up in the tree

```
/**
 * @param name - a name of a context state
 * @returns the named context state or `undefined` if it does not exist
 * @memo:intrinsic
 */
export function contextLocal<Value>(name: string): State<Value> | undefined
```

#### contextLocalValue()

Finds the closest attached state with the given name up in the tree and reurns its value

```
/**
 * @param name - a name of a context state
 * @returns a value of a context state
 * @throws Error if a named context state does not exist
 * @memo:intrinsic
 */
export function contextLocalValue<Value>(name: string): Value
```

### Positional memoization primitive functions

#### Memo entry

Memo entry is a family of functions to allow entering memoizing call chain. 

```
/**
 * This is where regular code can enter the memo realm.
 * This function allows to run a memo function in a non-memo context.
 * @internal
 * @memo:entry
 */
export function memoEntry<R>(
    context: StateContext,
    id: CallsiteKey,
    @memo entry: () => R,
): R 
```

```
/**
 * This is where regular code can enter the memo realm.
 * This function allows to run a memo function in a non-memo context.
 * @internal
 * @memo:entry
 */
export function memoEntry1<T, R>(
    context: StateContext,
    id: CallsiteKey,
    @memo entry: (arg: T) => R,
    arg: T,
): R
```

```
/**
 * This is where regular code can enter the memo realm.
 * This function allows to run a memo function in a non-memo context.
 * @internal
 * @memo:entry
 */
export function memoEntry2<T1, T2, R>(
    memo_context: StateContext,
    memo_id: CallsiteKey,
    @memo entry: (arg1: T1, arg2: T2) => R,
    arg1: T1,
    arg2: T2,
): R 
```

#### Memo bind

These are functions transforming memo lambda arguments to memo lambda of lower arity by binding some arguments to given values.

```
export function memoBind<T>(
    @memo item: (arg: T) => void, 
    value: T
): @memo () => void

```

```
export function memoBind2<T1, T2>(
    @memo item: (arg1: T1, arg2: T2) => void, 
    value1: T1, 
    value2: T2
): @memo () => void
```

## Positional Memoization

### Semantics

Functions marked with @memo provide "positional memoization semantics".
A function call, instead of evaluating the function again, returns the
same (memoized) value as the previous call at the same call site (position).
Unless any of two things happens:
  1. A value of any argument is changed
  2. Any state object the function is subscribed (see below) to is changed.

### Subscription

A memo function or a memo lambda subscribes to a state variable by the fact of reading its value.

### Annotations

There are several annotations used by the incremental runtime plugin

   * @memo
   * @memo:entry


### Syntax

The annotations are accepted at the following syntactic positions:


#### Function declaration

```
@memo
function foo() {}
```

#### Method declaration

```
class X {
    @memo
    foo() {}
}
```

#### Parameters of functional type

```
function foo(
    @memo arg1: () => void
)
```

#### Lambda function literal
```
    @memo () => {...}
```


#### Property declaration
```
class X {
    @memo public p
}
```

#### Function type declaration
```
function foo():
    @memo () => void
```

### Memo code entry pointes @memo:entry
The places where regular code is allowed to enter memo realm are denoted @memo:entry.
The functions marked with @memo:entry are not memo themselves,
but they must provide enough implementation defined lexical context
for the memo call to succeed in their bodies.

For example

```
/** @memo:entry */
function entry(
    context: Context,
    id: MemoId,
    @memo ui: () => void
) {
    ui()
}
```
### Inference and defaults

For the first implementation we don't expect any type inference support.
There is the following simple inference allowing the user to omit memo markings.

#### Call sites don't need special marks

No special marking at the call site is needed.
Any call to an entity marked with @memo
(functions, methods, properties of functional types, variables of functional types, parameters of functional types etc)
including the entities declared in other modules
is automatically rewritten by the compiler.

#### Lambda literal arguments

Lambda literals passed as arguments to parameters marked as memo are treated by memo by default. For example:

```
function foo(
    @memo content: () => void
) {
    ...
}


foo(() => { // This lambda literal is assumed to be memo!
    ...
})
```

### Constraints

#### memo code and state variables

A memo function can only read state variable values.
A memo code can not write to a state variable.

An attempt to assign a state variable will cause a compiler diagnostics or a runtime error.

A memo function can create a non-memo lambda which contains an assignment to a state variable.
Such lambda can be called outside of memo context and is allowed to change the state variable value.


#### memo should only be called from memo code

Any memo function should be called from another memo function.
An attempt to call a memo function in non-memo code will result in compiler diagnostics or a runtime error.

See @memo:entry description for the details on how the implementation can initiate memo call sequence.

Calling a non-memo code is allowed.
Although it is a good practice to call only pure functions without side effects.
As the memo function body is typically omitted because of positional memoisation.


### Implementation

#### Annotations

The  annotations are to be implemented as compiler annotations.
For example:

```
@memo function foo() {
    // ...
}
```


## A vision for memo functions support in ArkTS

We have three levels of desires of memo support in the static ArkTS language

### Level 1

We'd like to have java-like code annotations (syntactically similar to TS decorators).
Like @Memo.
To be able to annotate callable declarations (functions; methods; lambdas; variables, parameters and properties of function types).
For example

```
@memo
function foo() {
    // ...
}
```

We need the same set of annotations: @memo, @memo:intrinsic, @memo:entry and @skip:memo.
May be spelled differently (like @MemoIntrinsic).

The implementation lowering should basically reproduce our current rewrite in the TS memo plugin.

This lowering only needs to rewrite AST and read type information provided by the typechecker.
It needs to be able to read @Memo annotations from the other modules.


### Level 2

At the moment the typescript compiler doesn't help the user with type check and type inference of @memo functional types.
The only inference piece in the current TS compiler we have is the following

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

Just several examples of what would be nice:

```
let x = @memo n => { ... }  // x is inferred to be of type @memo (int) => void

function foo() { // foo return type is deduced as memo
    return @memo (m, n) => {}
}

// The right hand side is automatically promoted to @memo.
let y: @memo (String) => String = (s: String) => s 

let z: (String) => String = y // A type violation a memo assigned to non-memo.

```


The general rule seems to be: when there is an explicit type specified require exact memo/or non memo. When the type is induced propagate memo/non-memo information.

After the inference is done we want the @Memo to stick to any functional type and only allow assigning memo types to memo types and non-memo to non-memo.

That would also allow to drop the need to annotate variables, parameters and class properties as @Memo. Instead we can just annotate their types.
That would in general leave only two syntactic position for the @Memo annotation: on a function/method declaration and on a functional type.


In addition to the previous level, supporting this approach requires annotation stick to types. 
And annotations need to participate in the inference and typecheking. 
The plugin needs to interact with the type checker (may be provide the rules to handle the annotation).


### Level 3

memo function by themselves don't deal with anything UI specific.
This is just another semantics of function calls.

It can be used whereever there is a need to incrementally update trees.
Like it can be used to implement a build system.

If at some point we feel that it is a general useful mechanism and it is stable enough
we could promote @Memo annotation to a memo keyword.

That would essentially turn the plugin supported AST transformation into regular lowerings.

The compiler will have to enforce the typing and scoping rules
at the source as well as at the linker level.

Also the compiler will need to answer the general questions such as for example, 
how memo affects intermediate compiled artifacts, i.e. libraries.

The question of stable ABI (for compatibility between releases and implementations) will need to be answered.
What is the stable runtime representation of memo functions?
What are the mechanism of compatibility under language and runtime evolution?

### VM support and optimizations

#### Optimizations

The current implementation of memo semantics heavily relies on lambdas.
An efficient mechanisms of lambda instantiation and calls should benefit the performance.

Aggressive inlining in the compiler or VM should also benefit the performance.

#### Support

The VM could provide intrinsics for efficient operations on positional id: compute, combine, compare
