# On CJ UI framework DSL

## Overall approach

 UI DSL for incremental design assumes that certain functions are processed by compiler/plugin to add
optimization mechanisms of call avoidance if it is known, that particular UI sub-tree is not affected
by state change, and thus invocation of builder functions for that subtree can be avoided.
To deduce if particular function is suitable for this transformation, we need somehow color such functions,
and be able to detect on declaration side if rewrite is needed.

For example, current TypeScript DSL looks like this:

```typescript
/** @memo */
function Button(title: string, style?: Partial<ButtonStyle>, content?: /** @memo */ () => void) {
    // Build button...
    // Invoke child builder, if any.
    content?.()
}
/** @memo */
function Text(text: string, style?: Partial<TextStyle>) {}

/** @memo */
function MyUI(color?: Color) {
    Button("Hello" , { onClick: () => { console.log("Clicked")} }, () => {
        Text("text1", { font: Font.BOLD })
        Text("text2", { color: color ?? Color.RED })
    })
}
```

 In this approach `/** @memo */` JSDoc is used as a mechanism for function coloring on declaration side, and due to the
availability of usage => declaration mapping when rewriting we can both infer coloring of lambda parameters
and rewrite calls appropriately.

 `Partial<ComponentStyle>` is a flexible mechanism to provide extensible styling information to the components, due
to the facts that TypeScript compiler can infer literal type from function declaration and appropriately instantiate
styling interface.

## Open questions for CJ

   1. Mechanism for function coloring, possible variants are:
      * specially typed argument
      * function annotation
      * documentation comment
      * whole file/file range
      * all methods of certain class
   2. Mechanism to implement memoizing function rewrite
   3. Mechanism for function coloring type inference for anonymous lambdas (very important case for UI DSLs)
   4. How to provide styling parameter to builder functions
   5. Syntax sugar for null/undefined/optional checks, like `content?.()` and `color ?? Color.RED` in TypeScript
   6. Mechanism for callsite key (required for positional memoization of tree builders)


## Possible approach for CJ

   1. Memoizing functions are colored
   2. We detect colored functions by function signature analysis.
   3. Builder function combinations is achieved by trailing lambdas, like in Kotlin


Suggested DSL may look ideologically like the following Kotlin snippet:

```kotlin
interface UI {}
interface ButtonStyle {}
interface TextStyle {}

class UIImpl: UI {}

fun withUI(what: UI.() -> Unit) {
    val x = UIImpl()
    x.what()
}

fun UI.Button(title: String, style: ButtonStyle? = null, content: (UI.() -> Unit)? = null) {
    if (content != null) content()
}
fun UI.Text(text: String, style: TextStyle? = null) {}

fun ButtonPrime(ui: UI, title: String, style: ButtonStyle? = null, content: ((ui: UI) -> Unit)? = null) {
    if (content != null) content(ui)
}
fun TextPrime(ui: UI, text: String, style: TextStyle? = null) {}


fun ui1() {
    val ui = UIImpl()
    ButtonPrime(ui, "Hello") { ui: UI ->
		TextPrime(ui, "text1")
  		TextPrime(ui, "text2")
    }
}

fun ui2() {
    withUI {
        Button("Hello") {
            Text("text1")
            Text("text2")
        }
    }
}
```
Variant `ui1()` is simple for the language, requires no new language features but is quite ugly for users.

Variant `ui2()` is very straightforward for users, but requires the following language features to work:

   * extension functions
   * lambdas with receivers
   * implicit `this`

Coloring detection for the declaration side can be inferred from the signature (presence of first parameter of type `UI` for variant 1,
requires AST-only interface), or by traversing from usage to declaration (requires type-checker interface) for variant 2.

## Proposal as per discussion with CJ team

### Suggested DSL shape

```swift
@DeducedConstructor
open class Style {
    // @DeducedConstructor macro defines constructor for class from fields of class, i.e. it emits
    Style(width!: ?Int) {
        this.width = width
    }
    // from below property.
    // Is it possible?
    prop width: ?Int
}

@InheritedConstructor
class ButtonStyle <: Style {
    // @InheritedConstructor macro defines constructor for class from its and fields of super class, i.e. it emits
    ButtonStyle(width: ?Int, let border!: ?Int, let corners!: ?Int) {
        super(width = width)
    }
    prop border!: ?Int
    prop corners!: ?Int
}

@InheritedConstructor
class ColumnStyle <: Style {
    ColumnStyle(width: ?Int, gap: ?Int) {
        super(width = width)
        this.gap = gap
    }
    prop gap: ?Int
}

@Memo
func Button(title: String, style: ?ButtonStyle, content!: () -> Unit) {
    // Implementation here.
}

@Memo
func Column(style: ?ColumnStyle, content!: () -> Unit) {
    // Implementation here.
}

// Invocation.
Column(style = ColumnStyle(gap: 5)) {
    // Would be great to remove empty `{}`
    Button("One") {}
    Button("Two", style: ButtonStyle(corners: 3, border: 1)) {
        Button("Inner") {}
    }
}
```

### Suggested implementation

 Until late macros are available, we cannot do much, as early macro even have no way
to deduce its target FQ name, and as a result, external oracle defining if transformation
on function shall happen have no way to even obtain its input.

  When sufficiently functional late macro will be provided, we can switch to that mechanism
to detect if rewrite shall happen and avoid intermediate source code.

 We also need explicit `func callerId(): Int` intrinsic, with the property that

 ```swift
func a(): Unit {
    println(callerId())
}

func b() {
    // Different values are printed.
    a()
    a()
}

func c() {
    for (i in 0..2) {
        // Same value printed on each iteration.
        a()
    }
}
```
Semantically, call's runtime return address is good enough approximation for `callerId()` so implementation
can be straightforward.

If some improved syntax (à la JSON) for instantiation of style object instances is provided -
that would make DSL prettier, but even with current language features it's OKish.

### Required language mechanisms

If try to stay inside the language, and avoid external solutions, like compiler plugins, external source
transformers etc. - we need to provide additional language features to make above system feasible.

#### Late macros with usage => declaration mapping

 Macros executed after compiler's analysis phase, obtaining augmented AST with ability to jump
between usage and declaration in code of a macro, for example:

```swift
public macro Memo(input: Tokens): Tokens {
    var funcDecl = parseDecl(input, astKind: "FUNC") as FuncDecl
    var visitor = MemoFuncVisitor(ArrayList())
    funcDecl.traverse(visitor)
}
open class MemoVisitor <: Visitor {
    public override func visit(call: CallExpr) {
        // Hypothetic APIs
        var targetId = call.target.getId()
        var declaration = Reify(targetId)
        // Match possible declaration types with pattern matching.
        // If declaration is a function, check that its functional argument has @Memo macro itself.
        var argumentIndex = 0
        if (isLambda(call.params[argumentIndex]) && hasMemoOn(declaration, argumentIndex) {
            // Rewrite lambda body.
        }
    }
}
```

#### Function signature rewrite mechanism

 It's extremely desirable to make `@Memo` functions coloring make it type system incompatible with
functions with the same signature (think `async` functions is TypeScript or Kotlin), and pretty
much the only option for such coloring is adding special argument to signature and providing such an
argument in memo rewrite. It better be of non-instantiable and invisible by user type, so that no
unintentional signature mixup happens. This requires consistent signature rewrite mechanism.

#### Error reporting from macro

  To detect and report user errors we need to have compiler-friendly error reporting mechanism from macro,
combined with above usage => declaration mapping.

#### Ability to go from macro expanded to the original declaration in AST

  Not sure if we mandatory need it, but it may simplify detection if particular declaration is actually result of `@Memo`
expansion (it will be like `declaration.getOrigin().hasMacro("Memo")`).