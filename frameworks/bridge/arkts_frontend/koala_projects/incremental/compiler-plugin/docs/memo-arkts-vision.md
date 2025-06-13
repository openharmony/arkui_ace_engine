
# A vision for memo functions support in ArkTS

We have three levels of desires of memo support in the static ArkTS language

## Level 1: reproduce what we have in TS for Koala

We'd like to have java-like code annotations (syntactically similar to TS decorators).
Like @Memo.
To be able to annotate callable declarations (functions; methods; lambdas; variables, parameters and properties of function types).
For example

```
@Memo
function foo() {
    // ...
}
```

We need the same set of annotations: @memo, @memo:intrinsic, @memo:entry and @skip:memo.
May be spelled differently (like @MemoIntrinsic).

The implementation lowering should basicly reproduce our current rewrite in the TS memo plugin.

This lowering only needs to rewrite AST and read type information provided by the typechecker.
It needs to be able to read @Memo annotations from the other modules.


## Level 2: type inference and type check with @Memo

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
let x = @Memo n => { ... }  // x is inferred to be of type @Memo (int) => void

function foo() { // foo return type is deduced as memo
    return @Memo (m, n) => {}
}

// The right hand side is automatically promoted to @Memo.
let y: @Memo (String) => String = (s: String) => s 

let z: (String) => String = y // A type violation a memo assigned to non-memo.

```


The general rule seems to be: when there is an explicit type specified require exact memo/or non memo. When the type is induced propagate memo/non-memo information.

After the inference is done we want the @Memo to stick to any functional type and only allow assigning memo types to memo types and non-memo to non-memo.

That would also allow to drop the need to annotate variables, parameters and class properties as @Memo. Instead we can just annotate their types.
That would in general leave only two syntactic position for the @Memo annotation: on a function/method declaration and on a functional type.


In addition to the previous level, supporting this approach requires annotation stick to types. 
And annotations need to participate in the inference and typecheking. 
The plugin needs to interact with the type checker (may be provide the rules to handle the annotation).


## Level 3: promote @Memo annotation to a memo keyword.

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

## VM support and optimizations

### Optimizations

The current implementation of memo semantics heavily relies on lambdas.
An efficient mechanisms of lambda instantiation and calls should benefit the performance.

Aggressive inlining in the compiler or VM should also benefit the performance.

### Support

The VM could provide intrinsics for efficient operations on positional id: compute, combine, compare


