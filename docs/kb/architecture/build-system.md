# Build System Context

> 文档版本：v1.1
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `BuildSystem`

## 定位

编译构建是 ArkUI 引擎的 GN/Ninja 构建基础设施，涵盖平台发现、全局编译配置、主库聚合、前端生成物、接口包输出、组件独立库和部件入口声明。它不是对外公共 API，而是引擎内部构建架构，所有源码路径和构建目标均应回到当前 BUILD.gn/gni/bundle.json 核实。

本文档只提供稳定的构建入口、关键 target 和 Spec 路由。具体编译参数、平台宏、生成链细节应回到当前源码、构建配置和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 全局编译配置 | `ace_config.gni` | 构建参数声明（debug/PGO/coverage/split/wearable/Skia 等）、平台发现、路径常量、part/subsystem 定义 |
| 顶层 BUILD.gn | `BUILD.gn`（根） | ace_config/ace_test_config/ace_coverage_config 共享编译配置 |
| 主库聚合入口 | `build/BUILD.gn` | libace_static_* 遍历、分离引擎库、libace_compatible/libace 共享库 |
| 主库聚合模板 | `build/ace_lib.gni` | libace_static 模板（base+bridge+core 按平台选择）、ace_bridge_engine 模板 |
| OHOS 平台声明 | `adapter/ohos/build/platform.gni` | ohos/ohos_ng 平台声明、条件 libace_target 选择 |
| OHOS 平台配置 | `adapter/ohos/build/config.gni` | 旧框架配置、feature flags、libace_target 指向 |
| OHOS NG 配置 | `adapter/ohos/build/config_ng.gni` | NG 框架配置（并行于 config.gni） |
| OHOS 产物聚合 | `adapter/ohos/build/BUILD.gn` | ace_packages group + 57 个 libarkui_* 组件独立库 |
| OHOS 公共配置 | `adapter/ohos/build/common.gni` | JS engines、feature flags（accessibility/web/GPU/preload/smart gesture/drag 等） |
| 部件入口 | `bundle.json` | fwk_group/service_group/inner_kits 声明 |
| Base 框架源 | `frameworks/base/BUILD.gn` | ace_base_source_set 模板、按平台实例化 |
| Core 框架源 | `frameworks/core/BUILD.gn` | ace_core_source_set（旧）+ ace_core_ng_source_set（NG） |
| Bridge 框架源 | `frameworks/bridge/BUILD.gn` | framework_bridge（旧）+ framework_bridge_ng（NG） |
| NG 组件模板 | `frameworks/core/components_ng/components.gni` | build_component_ng 模板、默认依赖 idlize_gen |
| NDK 入口 | `interfaces/native/BUILD.gn` | ace_header NDK headers + ace_ndk 共享库 |
| NAPI 模块清单 | `interfaces/napi/kits/napi_lib.gni` | common_napi_libs 模块字符串数组 |
| NAPI 入口 | `interfaces/napi/kits/BUILD.gn` | 遍历 common_napi_libs 按平台实例化 ace_napi_lib |
| ANI 包入口 | `interfaces/ets/BUILD.gn` | ace_ani_package group 聚合 ANI 库和资源 |
| 静态 ArkTS 生成 | `frameworks/bridge/arkts_frontend/arkoala_generator/BUILD.gn` | idlize_gen source_set、SDK patch、IDL 生成 |
| 静态 ABC 生成 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/BUILD.gn` | components_compile_abc → components.abc |
| 单测入口 | `test/unittest/BUILD.gn` | unittest/linux_unittest/linux_unittest_capi |
| 单测模板 | `test/unittest/ace_unittest.gni` | ace_unittest 模板（组件/pipeline 等类型注入） |
| Benchmark 入口 | `test/benchmark/BUILD.gn` | ace_baseline/benchmark/benchmark_linux |
| 扩展组件入口 | `advanced_ui_component/BUILD.gn` | advanced_ui_component_libs 按 platform 生成 |
| 平台发现脚本 | `build/search.py` | 扫描 adapter 子目录 |

### API 入口

编译构建是引擎内部架构，没有独立 SDK API。构建产物通过 bundle.json inner_kits 暴露给外部模块。

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 相对外部仓的头文件/目标路径 | 说明 |
|----------|----------|------------|----------------------------|------|
| 图形渲染 | `build/ace_lib.gni` deps, `components.gni` | `foundation/graphic/graphic_2d` | `2d_graphics`, `librender_service_client`, `librender_service_base` | 主库和组件 source_set 编译依赖 |
| Skia | `ace_config.gni` Skia 路径 | `third_party/skia` | Skia 头文件和库 | 条件编译 USE_ROSEN_DRAWING |
| Ark 运行时 | `adapter/ohos/build/common.gni` js_engines | `arkcompiler/ets_runtime` | `ets_runtime:ark_js_runtime` | 分离引擎库依赖 |
| NAPI | `interfaces/napi/kits/BUILD.gn` | `arkcompiler/napi` | `napi:ace_napi` | NAPI 模块编译依赖 |
| ANI 运行时 | `interfaces/ets/BUILD.gn` | `arkcompiler/runtime_core` | `runtime_core:ani` | ANI 模块编译依赖 |
| HiLog | `BUILD.gn` ace_config USE_HILOG | `base/hiviewdfx/hilog` | `hilog:libhilog` | 日志编译依赖 |
| FFRT | `adapter/ohos/build/common.gni` | `foundation/resourceschedule/ffrt` | `ffrt:libffrt` | 异步任务调度编译依赖 |
| EventHandler | `components.gni` | `base/eventhandler` | `eventhandler:libeventhandler` | 事件分发编译依赖 |
| EGL/OpenGL | `components.gni` | `third_party/opengles` | `opengles:libGLES` | GPU 渲染编译依赖 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 构建 JSON 校验 | `python3 -m json.tool bundle.json` | 部件元数据语法验证 |
| 主库构建 | `./build.sh --product-name rk3568 --build-target ace_engine --ccache` | 完整 ace_engine 构建 |
| SDK 构建 | `./build.sh --product-name ohos-sdk --build-target ace_engine` | SDK 变体构建 |
| 单测构建 | `./build.sh --product-name rk3568 --build-target unittest` | 单测聚合构建 |
| Host 单测构建 | `./build.sh --product-name host_product --build-target unittest` | Linux x86_64 Host 单测 |
| C API 单测构建 | `./build.sh --product-name rk3568 --build-target linux_unittest_capi` | C API 单测 |
| Benchmark 构建 | `./build.sh --product-name rk3568 --build-target benchmark_linux` | Benchmark 构建 |
| GN 目标构建 | `./build.sh --product-name rk3568 --build-target <gn_target>` | 单个 GN 目标快速构建 |

### 相关 Spec

编译构建功能域：`specs/01-architecture/01-architecture-design/01-build-system/`（功能 ID `01-01-01`）。

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| BUILD.gn 结构规格 | `specs/01-architecture/01-architecture-design/01-build-system/Feat-01-build-gn-structure-spec.md` | 全局配置、主库聚合、框架 source_set、接口与包、测试入口 |
| 设计文档 | `specs/01-architecture/01-architecture-design/01-build-system/design.md` | 整体架构设计、ADR、根构建入口、平台发现、ArkUI-X 参考 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 新平台不进入构建图 | `adapter/<platform>/build/platform.gni` 是否声明 `platform.name`；`ace_config.gni` 平台发现过滤逻辑 |
| 主库链接失败 | `build/ace_lib.gni` base+bridge+core 依赖选择；`libace_target` 是否指向正确共享库 |
| libace vs libace_compatible 选择 | `adapter/ohos/build/config.gni` 中 `is_asan` 和 `ace_engine_feature_enable_libace` 条件 |
| 组件独立库不构建 | `adapter/ohos/build/BUILD.gn` component_modules 列表；pattern source_set 是否注册 |
| 前端生成物缺失 | declarative `action`/`gen_obj` 输入输出声明；arkoala_generator `idlize_gen` deps |
| bundle.json 构建入口报错 | `python3 -m json.tool bundle.json` 校验；fwk_group/service_group/inner_kits 路径 |
| ArkUI-X 构建图不复用 | `cross_platform_support = true` 是否在 adapter platform.gni 中声明 |
| 单测目标不构建 | `test/unittest/BUILD.gn` 聚合逻辑；`ace_unittest.gni` 模板实例化 |

## 调试入口

- 平台发现断点：`ace_config.gni` exec_script("build/search.py") → adapter 扫描 → platform.gni 导入
- 主库聚合断点：`build/BUILD.gn` → libace_static_* 遍历 → `ace_lib.gni` base/bridge/core 选择
- 分离引擎库断点：`build/BUILD.gn` engine_config → `ace_bridge_engine` 模板 → `libace_engine_*`
- 组件库断点：`adapter/ohos/build/BUILD.gn` component_modules → arkui_* shared_library per module
- 生成链断点：`arkoala_generator/BUILD.gn` idlize_gen → `koala_projects/BUILD.gn` components_compile_abc

## 相关主题

- 布局框架：`docs/kb/architecture/layout-framework.md`（同层级架构主题）
- 状态管理：`docs/kb/frontend/state_management/`（frontend 主题，总览页 `docs/kb/frontend/state_management.md`）
- 窗口机制：`docs/kb/architecture/window-mechanism.md`（同层级架构主题）
- IDLize 生成链路：`docs/common/idlize/idlize_Knowledge_Base.md`（idlize_gen 是构建图依赖节点；旧 KB 位置，尚未迁移）
