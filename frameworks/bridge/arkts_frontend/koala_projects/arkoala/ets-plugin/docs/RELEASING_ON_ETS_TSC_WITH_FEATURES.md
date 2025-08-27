
# Can we release Arkoala with phase 1 compiler but with additional language features?

In this note we understand this
[list of features](../../koala-arkui/docs/ARKTS_COMPILER_REQ.md#generic-language-features-to-support-existing-and-new-syntax)
as "advanced features"

## Advanced features will help prototype the proper Static ArkTS solution

The ArkTS compiler is still under heavy development.
At the time of writing this note there are still issues with the basic primitive type support
and basic function signature elements support.

So the proper usage of "advanced compiler features" such as trailing lambdas or statc invoke etc
even when implemented is shadowed by more basic problems.

Having the some of the same features implemented in the @ohos/typescript compiler
will allow to experiment with the features and find limitations issues and solutions earlier

## Advanced language features are not hardly required

The current Arkoala rewrite is done completely in the compiler plugin.
No additional features are hardly *required*.

But having some of them should allow to drop large parts of the plugin
and large parts of the ["tsconfig configuration nightmare"](https://gitee.com/openharmony/developtools_ace_ets2bundle/blob/master/compiler/tsconfig.json#L4)
moving all required information to the library.


## What kind of problems can arise?

### The language will not match Static ArkTS

Currently the @ohos/typescript is kind of old limited and there are additional syntax limits placed on builder functions.
There can appear nuances of semantics or syntax so @ohos/typescript based solution similar but not exactly the same as the final Static ArkTS solution. That will bring complications during transition to Static ArkTS.

A demonstrative example: are extension functions allowed on primitive type receivers? `int.foo()`.

### The new features conflict with the current @ohos/typescript approach

For example, the trailing lambdas conflict with EtsComponentExpression.

So implementing them in @ohos/typescript compiler requires some way to disambiguate what the trailing block of, for example, `Text(){}`.

Good news is that we don't need them at the same time.

If we are lucky then just removing mentions of components tsconfig "ets" section
and introducing proper trailing lambda declarations for them will be enough.

### New declarations for system components need to be reflected in sdk components/*.d.ts files.

To be discussed.
May be we can keep compatibility with the current *.d.ts.
But we'd better try it out with existing compiler.

## How to mitigate the risks

   * If we only use the advanced features to prototype ArkTS and not enable them in the release, then the risk is zero.

   * If some feature is well done, well tested, plays nice with the user code, don't expose unmanaged incompatibilities and there is a sane way to turn it off, then we could take it to the release. We always can fallback to the current Arkoala rewrite in case problems are encountered.

   * We need to be able to enable and disable the features separately (preferably in the compiler configuration)

   * Make sure the test bases for the features are the same for @ohos/typescript and Static ArkTS



