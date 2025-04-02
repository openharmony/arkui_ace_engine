# Making ArkUI more functional styled

## Problem

In current ArkUI UI builder functions are defined in rather unexpected manner:

```typescript
declare type CustomBuilder = (() => any) | void
```

It makes the type system not aware about actual types used for UI building and unable
to perform type control upon user code.

Related issue is that struct-based APIs assumes implicit instance in member
builder functions, which could be captured (or not captured) in unexpected
manner.

It may make sense to specify builder functions with proper functional signatures,
which could be properly type-checked and appropriately combined using standard
functional-programming mechanisms.

And coordination of asynchronous operations with UI builders is also related.

## Prior art

Koala UI framework faced similar issues, and following set of design decisions were made:

   * Main UI framework primitive is frequently state-less parametrized builder function
   * States can be arbitrary encapsulated into class instances, as globals or positionally addressed function locals
   * UI composition is achieved via function invocation superposition, functional arguments and partial application mechanisms

Koala UI code may look like this
```typescript
/** @memo */
function Column(style: Partial<ColumnStyle>, content?: /** @memo */() => void) {
    content?.()
}

/** @memo */
function Button(text: string, style?: Partial<ButtonStyle>) {
}

/** @memo */
function MyButton1() {
    Button("button1")
}

/** @memo */
function MyButton2() {
    Column({}, memoBind(Button, "button2"))
}

/** @memo */
function User() {
    Column({align: Alignment.Center}, () => {
        Button("first")
        Button("second")
        MyButton1()
        MyButton2()
    })
}
```

So the primitives are functional, along with the means of UI superposition.
Builder functions can be stored in containers, passed as arguments and so on.
As TypeScript is a functional language, it provides quite broad assortment of
operations on functions. Koala UI augments this with several additional builder
function specific operations for cases like iterations and partial application.

`Promise` monad also combines with notions of states and functions quite naturally,
for example
```typescript
/** @memo */
function Loadable(url: string): ImageData|undefined {
    // Returns undefined until URL is loaded.
    return rememberAsyncState((url) => await loadUrl(url)).value
}

function User() {
    Image(Loadable("http://site.name/image.jpg") ?? PlaceholderData())
}
```

## ArkUI functional style extensions proposals

   * Properly typed UI builder functions
   * Functional core components instead of struct-based components
   * Higher level functional primitives

### Properly typed UI builder functions

Introduce `@Builder` as a type system notion and provide set of standardized predefined
builder function types.

```typescript
type CustomBuilder0 = @Builder () => void
type CustomBuilder1<A1> = @Builder (arg1: A1) => void
type CustomBuilder2<A1, A2> = @Builder (arg1: A1, arg2: A2) => void
```

### Functional core components

Provide functional interface to system components, i.e. along with

```typescript
struct Column implements ColumnAttribute {
    alignItems(value: HorizontalAlign) {}
}
```
also provide
```typescript
function Column(style?: Partial<ColumnAttributeValues>, content?: CustomBuilder0) {}
```

### Higher level functional primitives

To ensure we could properly pass
```typescript
   function builderBind1<T>(builder: CustomBuilder1<T>, arg: T): CustomBuilder0 {}
   function builderBind2_1<T1, T2>(
    builder: CustomBuilder2<T1, T2>, arg: T1): CustomBuilder1<T2> {}
   function builderBind2_2<T1, T2>(
    builder: CustomBuilder2<T1, T2>, arg: T2): CustomBuilder1<T1> {}
   ...
```