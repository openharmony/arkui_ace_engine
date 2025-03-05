# Arkoala and ArkCompiler coevolution, staged

## Stage 1

  * Compiler: @ohos/typeScript compiler + ETS compiler plugin + memo compiler plugin
    using MS TSC plugin API
  * Runtime: HZ VM in JS mode, executing .abc produced from .js
  * Arkoala:
     * frontend: new compiler, new hvigor plugin
     * interop: NAPI between JS code and ArkoalaNative.so, hidden behind Koala interop bridging API
     * OHOS APIs: JS interop in HZ VM
     * ArkUI components: libace.so with versioned Arkoala extensions (api.h) called by ArkoalaNative.so
   * OHOS APIs: JS APIs in HZ VM

## Stage 1.75

   * Compiler:
       * Compiler 1: @ohos/typescript with same compiler plugins as in stage 1 + small plugin emitting static mode ArkTS safe code
       * Compiler 2: static mode ArkTS compiler compiling Arkoala source code and user code transformed with the Compiler 1
   * Runtime: Panda VM in statically typed mode
   * Arkoala, same as in phase 1, but the whole source code is fully static mode ready:
     * frontend: new compiler, new hvigor plugin
     * interop: JNI between JS code and ArkoalaNative.so, hidden behind Koala interop bridging API
     * ArkUI components: libace.so with versioned Arkoala extensions (api.h) called by ArkoalaNative.so
   * OHOS APIs: JS interop in Panda VM

## Stage 2

   * Compiler: static mode ArkTS compiler + small UI compiler plugin + memo compiler plugin using managed ArkTS compiler plugin API (compiler_api.h + TS bindings) written in TS and executed on Node.js (i.e. it is executed on the host, during compilation)
   * Runtime: Panda VM in statically typed mode
   * Arkoala, same as in phase 1, but the whole source code is fully static mode ready:
     * frontend: new compiler, new hvigor plugin (static mode added)
     * interop: JNI between JS code and ArkoalaNative.so, hidden behind Koala interop bridging API
     * ArkUI components: libace.so with versioned Arkoala extensions (api.h) called by ArkoalaNative.so
   * OHOS APIs: JS interop in Panda VM

## Stage 3

   * Compiler: static mode ArkTS compiler + small UI compiler plugin + memo compiler plugin using managed ArkTS compiler plugin API (compiler_api.h + TS bindings) written in ?? and executed in ?? (i.e. it is executed on the host, during compilation)
   * Runtime: Panda VM in statically typed mode
   * Arkoala:
     * new Skoala-based statically typed low level rendering APIs
     * statically typed layout engine and new UI framework extension mechanisms (can reuse Koala UI solutions)
     * frontend: same as Stage 2
     * interop: JNI between JS code and ArkoalaNative.so, hidden behind Koala interop bridging API
     * backend:
        Option 1: libace.so with versioned Arkoala extensions (api.h) called by ArkoalaNative.so for system components
        Option 2: implementation based on ArkUI on top of Koala UI engine (if have sufficient performance)
   * OHOS APIs: hopefully implemented to run natively (static ArkTS + C++ via JNI bridges, maybe reused Koala interop style) on Panda VM
