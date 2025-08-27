# ArkUI/ArkTS NEXT Compatibility Guide

## Language Compatibility Aspects

### General Language Compatibility

The ArkTS NEXT language in similarly looking, but not quite the same as TS. Also its execution model is quite
different, as it is executed on statically typed VM. It implies serious consequences in the user code compatibility.

Most of the issues, where languages diverge, should have been covered by the TypeScript linter integrated
into SDK, informing our users their code is not subset.

In general, for non-obvious cases, the compiler team provides and maintains [the Cookbook PDF](https://gitee.com/igelhaus/arkcompiler_runtime_core/releases/download/arkts-spec-release-2024-06-13/ArkTSCookbook.pdf).


### UI DSL ArkTS syntax.

The current Arkoala rewrite is tested using [existing test suite](https://gitee.com/openharmony/developtools_ace_ets2bundle/tree/master/compiler/test/utForPartialUpdate/).

These are current known issues/incompatibilities worked around by [these patches](https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-ui/-/tree/master/ets-plugin/test/specification/patches).


### UI DSL: ArkTS semantics.

The current way of testing the TS semantics is "Battle test" using existing application (Fang Taobao, Healthy Diet).

The exhaustive semantics check is to be tested using [XTS suite](https://gitee.com/openharmony/xts_acts/) in comparison with legacy mode.

### UI DSL: ArkTS NEXT semantics.

The ArkTS mechanism for testing semantics of the state management to be created.
ArkUI APIs need to be reworked to make them ArkTS NEXT compatible. Automated [linter tool](https://gitee.com/nikolay-igotti/idlize/blob/master/src/linter.ts) shall be used to sanitize interfaces.


### UI DSL: ArkTS NEXT based solution

Initially we plan to directly re-use the same rewrite using ohos-typescript with Arkoala ets-plugin to
TSC-based compiler. Plugin need to be adjusted to emit more ArkTS NEXT compatible code.

We have investigated the issues with the compiler team.
Most of the issues will be fixed in the es2panda frontend.

The issues in the ets-plugin are tracked [here](https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-ui/-/issues/60).

Later we will switch from ets-plugin to es2panda native plugin, but that is still WIP.
The Umbrella issues for the plugin are [here](https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/14039).

The Umbrella issue for the Annotations is here:
https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/16785

### State management DSL version 3

We have investigated the feasibility of implementation [here](https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-ui/-/blob/master/arkoala/docs/StateManagement3.md).

Currently we discuss with the es2panda library team the needed reflection interfaces, see [this bug](https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/18038).

## Compatibility with older releases

### Calling legacy components from new components

  * We must be able to provide compile-time decidability that HAR was compiled in legacy or ArkUI NEXT mode. To do that we will check module's module.json5 for `ArkoalaPlugin` property in `metadata` section.
  * Then we must provide runtime mechanism to call legacy ViewPU-based code from incremental runtime maintained UI tree, this work is prototyped [here](https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-ui/-/merge_requests/3076).
  * Entry point support to call ArkUI NEXT event loop. NEEDS HQ ATTENTION!

### Calling new components from legacy components

   * Due to the nature of an incremental engine and event loop organization calling new components from
legacy components will be supported only with the page granularity. Assumed scenario is essentially
giving ArkUI NEXT page control over event processing and rendering loop when navigation to the page compiled
in NEXT mode happens. This requires some research and prototyping.

### C API compatibility

 * We assume that next version number surely breaks binary compatibility, and likely break source compatibility for some operations
 * Every API group is versioned independently and we assume that some APIs  (i.e. basic and extended) will stabilize soon
 * See [here](https://gitee.com/openharmony/arkui_ace_engine/blob/master/frameworks/core/interfaces/arkoala/arkoala_api.h) for API groups available (extended API supporting event loop coordination and custom measure/layout on client side is probably most sensitive here)

## Execution environment compatibility

### VM co-existence

Exact model of execution on hybrid JS/ArkTS NEXT VM to be defined in coordination with ArkTS NEXT team.
Current hypothesis is that entry point is executed in JS mode, and ArkTS NEXT code is executed in callbacks
from JS VM event loop via native interop mechanisms. [This umbrella issue](https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/18032) discusses this problem.

### Event loop ownership

Low level VM event loop must be per isolate and its control to be defined by ArkTS NEXT runtime (Panda) team.
We assume availability of operations to control high level event loop coordinated with vsync events via
general purpose await/Promise mechanisms. [This umbrella issue](https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/18033) discusses this problem.

### Calling existing (non-ArkUI) OHOS interface

 Calling of legacy JS interfaces from ArkTS NEXT code shall rely on general purpose ArkTS NEXT VM/JS VM interop mechanisms, and we assume that VM provides required machinery for that.
 [See this umbrella issue](https://rnd-gitlab-msc.huawei.com/rus-os-team/virtual-machines-and-tools/panda/-/issues/18035) for the details.
