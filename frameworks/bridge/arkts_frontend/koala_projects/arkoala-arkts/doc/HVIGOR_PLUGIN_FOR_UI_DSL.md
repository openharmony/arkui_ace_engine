# Hvigor plugin for incremental, parallel and pluggable compilation

## The landscape

The OHOS SDK uses Hvigor as its build system.

Support for different toolchains is done by hvigor plugins.

Hvigor is executed in Node.js on the host, within DevEco or standalone.

The compiler is available as a shared library libes2panda.so with a C API.

## Interacting areas

We expect the implementations of:

   * compiler invocation from the hvigor plugin
   * parallel compilation
   * incremental compilation
   * compiler plugin injection
   * compiler plugins written in managed code
   * the CLI drivers

all to be tightly connected.

## Existing experimental research prototypes

### Parallel compiler invocation infrastructure (fast-arktsc)

The parallel compilation tool for es2panda

    https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/tree/master/incremental/tools/fast-arktsc

### Parallel libes2panda.so invocation prototype

The node workers based compiler invocation prototype for parallel libes2panda.so invocation can be found here

    https://gitee.com/nikolay-igotti/idlize/pulls/644

    https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/pulls/1152/files

### The plugin aware driver

The driver able to inject plugins written in TS can be found here

    https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/blob/master/arkoala-arkts/libarkts/src/es2panda.ts

### The usability wrappers

Currently we are using some usability wrappers around @panda/sdk binaries.

    https://gitee.com/openharmony-sig/arkcompiler_ets_frontend/tree/master/incremental/tools/panda/arkts

## The hvigor plugin

The current hvigor plugins can be found here (for reference)

    https://codehub-g.huawei.com/groups/IDE-DS/CompileBuild/detail

## Joint team

The architecture and design of the area need to be thought through
by a small team of closely communicating engineers.
Ideally knowlegable in
   * hvigor and its plugins,
   * the compiler initialization and staging infrastructure
   * the compiler plugin needs (represented by UI team, in our case).

