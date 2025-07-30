# ArkTS compiler plugin interface architecture technical proposal

To ease the migration from TS and ETS to Static ArkTS,
it is desirable to reuse the code of existing `memo` and `ets` plugins from `Arkoala phase 1` project
with ArkTS compiler for `Arkoala phase 2`.

The following architecture is proposed.


## Plugin AST manipulation API

Provide AST manipulation API compatible to the one used in @ohos/typescript
https://gitee.com/openharmony/third_party_typescript/blob/master/lib/typescript.d.ts#L3197

This is a very high level generic TS AST creation and update interface.
It is known to be sufficient to implement AST transformations needed for memo and ets lowering.

The following is a technical vision of how it could be achieved.


## An interface to the ArkTS compiler

We propose to structure the API plugin interface implementation as two layers: managed and unmanaged.
With a clearly declared interface between the layers.

### A single .h header file

The interop of managed API world and the compiler should be described by a single
"C-style" header file shared between the managed plugin interface part and the native world of the compiler.

The interface should provide an AST tree query, construction and update interface.
With a constraint of only passing primitive types or arrays of primitive types.

See a similar header for `libace` interface as an example [See api.h](../../framework/native/src/arkoala_api.h)

### Managed side of the interface

Make AST node implementations have peers on the native side.
So that the managed node holds the pointer to the C++ node and controls the lifetime of the native node interacting with the GC finalization queue.

See an example of the similar implementation in [See Finalizable.ts](../../../interop/src/interop/Finalizable.ts)

Similar to how it is done for `Skoala`, `Flying pandas` and `Arkoala` applications.

Reuse the koala-interop technology for the interop between managed and native world.

### Expose a C-style from ArkTS compiler

The ArkTS compiler needs a thin layer translating the "C-style" api.h calls
to the C++ manipulation of AST nodes.

See an example of similar layer in skoala library [See Paint.cc](../../skoala-bridges/src/cpp/Paint.cc)

### Organizational consideration

The managed and native sides of the interface can be developed by separate teams,
sharing just a single C-style header files.

