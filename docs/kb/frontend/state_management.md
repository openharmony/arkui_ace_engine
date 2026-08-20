# State Management Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmt`

## 定位

State Management（状态管理）是 ArkUI 声明式前端的引擎内部子系统，负责可观察状态、渲染期依赖收集、变更通知与局部重渲染、组件级存储与持久化、跨组件树传递，以及动态/静态前端的互操作桥接。它是 V1（`@State`/`@Prop`/`@Link`/`@Provide`/`@Consume`/`@Observed`/`@ObjectLink`/`@Watch`/`@Track`）和 V2（`@ObservedV2`/`@Trace`/`@Local`/`@Param`/`@Once`/`@Event`/`@Provider`/`@Consumer`/`@Monitor`/`@Computed`/`@Type`/`@Env`）两套装饰器体系的运行时基础。

本文档用于快速定位状态管理相关源码、SDK 声明和测试入口。具体装饰器语义、默认值、边界条件以对应 SDK 声明、源码实现和测试用例为准。状态管理的实现主体是编译为 `stateMgmt.abc` 的 TypeScript 库，C++ 侧只承载 JSI 绑定、宿主节点、管线集成与性能监控。

## 快速路由

### 子系统导航

状态管理按子系统拆分为 16 个子页面（9 个动态侧 + 7 个静态侧），本文档仅作总入口。子页面按关注点划分，可独立检索：

### 动态前端（ArkTS 1.1，`declarative_frontend/state_mgmt/`）

| 子系统 | KB 路径 | 覆盖范围 |
|--------|---------|----------|
| | V1 核心逻辑 | `docs/kb/frontend/state_management/v1_core.md` | `ViewPU`、`ObservedPropertyAbstractPU`、`PropertyDependencies`、依赖收集、变更通知、组件冻结、`@Observed` Proxy |
| | V2 核心逻辑 | `docs/kb/frontend/state_management/v2_core.md` | `ObserveV2` 单例、`trackInternal`、ID 分段、`autoProxyObject`、`ViewV2`、`PUV2ViewBase` |
| | 基础设施 | `docs/kb/frontend/state_management/infrastructure.md` | `ConfigureStateMgmt`、`stateMgmtConsole`、`stateMgmtDFX`、`UINodeRegisterProxy`、`UpdateFuncRecord`、`UIUtils`、`SubscribableAbstract` |
| | C++ 绑定与宿主节点 | `docs/kb/frontend/state_management/cpp_bindings.md` | `stateMgmt.abc` 载入、`JSViewPartialUpdate`、`ViewFunctions`、`CustomNode`、`ElementRegister`、`ViewStackProcessor` |
| | 存储体系 | `docs/kb/frontend/state_management/storage.md` | `AppStorage`、`LocalStorage`、`PersistentStorage`、`Environment`、`AppStorageV2`、`PersistenceV2` |
| | V1 装饰器 | `docs/kb/frontend/state_management/v1_decorators.md` | `@State`/`@Prop`/`@Link`/`@Watch`/`@Observed`/`@ObjectLink`/`@Provide`/`@Consume`/`@Track` |
| | V2 装饰器 | `docs/kb/frontend/state_management/v2_decorators.md` | `@ObservedV2`/`@Trace`/`@Local`/`@Param`/`@Once`/`@Event`/`@Provider`/`@Consumer`/`@Monitor`/`@SyncMonitor`/`@Computed`/`@Type`/`@Env`/`@CustomEnv` |
| | 自定义组件机制 | `docs/kb/frontend/state_management/custom_component.md` | `@Component`/`@ComponentV2` 创建管线、dirty 更新、复用、冻结、生命周期状态机、`@Builder` |
| | Interop 桥接 | `docs/kb/frontend/state_management/interop_bridge.md` | 动态前端（ArkTS1.1）与静态前端（ArkTS1.2/arkoala）之间的状态、存储、Builder 互操作 |

### 静态前端（ArkTS 1.2 / arkoala，`frameworks/bridge/arkts_frontend/`）

| 子系统 | KB 路径 | 覆盖范围 |
|--------|---------|----------|
| | 静态 V1 核心逻辑 | `docs/kb/frontend/state_management/static_v1_core.md` | `DecoratedV1VariableBase`、`IStateMgmtFactory`/`STATE_MGMT_FACTORY`、`ObserveSingleton`、`MutableStateMeta`、装饰变量工厂分发 |
| | 静态 V1 装饰器与数据对象 | `docs/kb/frontend/state_management/static_v1_decorators.md` | `@State`/`@Prop`/`@PropRef`/`@Link`/`@Provide`/`@Consume`/`@ObjectLink`/`@Watch` + `InterfaceProxyHandler`（`@Observed` 等价）+ `WrappedArray`/`Map`/`Set`/`Date` + `@Track` |
| | 静态 V2 核心逻辑 | `docs/kb/frontend/state_management/static_v2_core.md` | `DecoratedV2VariableBase`、`StateUpdateLoop`、`autoProxyObject`、`DecoratorBackingValue` |
| | 静态 V2 装饰器与数据对象 | `docs/kb/frontend/state_management/static_v2_decorators.md` | `@Local`/`@Param`/`@Provider`/`@Consumer`/`@Monitor`/`@SyncMonitor`/`@Computed` + `@ObservedV2`/`@Trace`（经 UIPlugin 转换 `MutableStateMeta`） |
| | 静态存储体系 | `docs/kb/frontend/state_management/static_storage.md` | `LocalStorage`/`AppStorage`/`PersistentStorage`/`Environment` + `AppStorageV2`/`PersistenceV2`/`V2CollectionCoder` + ANI 原生桥 |
| | 静态 Interop 桥接 | `docs/kb/frontend/state_management/static_interop_bridge.md` | `InteropState`/`openInterop`/14 个 register 回调、`CompatiblePeerNode`、`getCompatibleState`、`enableCompatibleObservedV2ForStatic`、Builder 互操作 |
| | 静态自定义组件状态相关 | `docs/kb/frontend/state_management/static_custom_component.md` | `BaseCustomComponent`/`CustomComponentV2`、`GlobalReusePool`/`GlobalReusePoolRegistry`、`@ReusableV2` 复用 |

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 状态管理 TS 库根 | `frameworks/bridge/declarative_frontend/state_mgmt/` | TS 源码、构建脚本、单元测试；README 说明 debug/release/profile 三种构建产物 |
| 模块入口 | `frameworks/bridge/declarative_frontend/state_mgmt/src/index.ts` | 初始化 `PersistenceV2`/`PersistentStorage`/`Environment` 后端 |
| 源码主目录 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/` | 按 `common/`、`partial_update/`、`full_update/`、`puv2_common/`、`v2/`、`sdk/`、`interop/`、`env_base/` 分层组织 |
| 公共抽象层 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/` | `ObservedPropertyAbstract`、`ObservedObject`、`ConfigureStateMgmt`、`stateMgmtConsole`、`stateMgmtDFX`、`stateMgmtProfiler`、`WeakRefPool` |
| PU 路径（V1 主路径） | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/` | `ViewPU`、`ObservedPropertyPU`、`Synched*PU`、`TrackedObject`、`RecycleManager`、`__RepeatImpl` |
| FU 路径（V1 遗留） | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/full_update/` | `View`、`ObservedPropertyObject`/`Simple` 等遗留全量更新实现 |
| PU/V2 共享基础 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/` | `PUV2ViewBase`、`CustomComponentLifecycle`、`__ReusePool__Internal`、`UpdateFuncsByElmtId`、`ViewBuildNodeBase` |
| V2 状态管理 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/` | `ObserveV2`、`trackInternal`、`ViewV2`、`ComputedV2`、`MonitorV2`、`ObjectProxyHandler`、`EnvV2`、`RecyclePoolV2` |
| SDK 公共类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/` | `AppStorage`、`LocalStorage`、`PersistentStorage`、`Environment`、`SubscriberManager`、`SubscribedAbstractProperty`、`AppStorageV2Impl`、`PersistenceV2Impl`、`UIUtils`、`ObservedUtil` |
| Interop 桥接 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/interop/` | `InteropConfigureStateMgmt`、`InteropExtractorModule`、`InteropStorage`、`ViewInterop`、`BuilderViewV2` |
| C++ JSI 绑定 | `frameworks/bridge/declarative_frontend/jsview/` | `js_state_mgmt_profiler.*`、`js_state_mgmt_histogram.*`、`js_local_storage.*`、`js_persistent.*`、`js_environment.*`、`js_view.*`、`js_view_functions.*`、`js_view_stack_processor.*` |
| 自定义节点宿主 | `frameworks/core/components_ng/pattern/custom/custom_node.*`、`custom_node_base.*`、`custom_node_pattern.*` | `@Component`/`@ComponentV2` 的 C++ 宿主节点与生命周期回调容器 |
| 元素注册表 | `frameworks/core/pipeline/base/element_register.*` | `ElementRegister` 全局 elmtId→UINode 映射、`MakeUniqueId`、移除集跟踪 |
| 视图栈处理器 | `frameworks/core/components_ng/base/view_stack_processor.*` | `ViewStackProcessor` 组件创建栈与 accessRecording |
| 管线集成 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `RecordStateMgmtNode`、`OnIdle`、`CallStateMgmtCleanUpIdleTaskFunc`、`GetStateMgmtInfo` |
| Frontend 反向调用接口 | `frameworks/core/common/frontend.h` | `CallStateMgmtCleanUpIdleTaskFunc`、`CallGetStateMgmtInfo`、`OpenStateMgmtInterop` 虚函数 |

### API 入口

状态管理没有 C API / Modifier / NAPI 范式，对外通过 ArkTS 装饰器语法和 `@ohos.arkui.StateManagement` 模块暴露。SDK 声明文件位于 `interface/sdk-js` 仓（不在本仓内），以下路径以 `<OH_ROOT>` 表示 OpenHarmony 根目录。

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `@State`/`@Prop`/`@Link`/`@Watch`/`@Provide`/`@Consume`/`@Observed`/`@ObjectLink`/`@Track`/`@StorageLink`/`@StorageProp`/`@LocalStorageLink`/`@LocalStorageProp` 声明；按装饰器名检索 |
| V2 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `@ObservedV2`/`@Trace`/`@Compute`/`@Monitor`/`@ComponentV2`/`@Local`/`@Param`/`@Once`/`@Event`/`@Provider`/`@Consumer`/`@Type` 声明 |
| V1/V2 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 静态 ArkTS 侧状态管理装饰器声明 |
| StateManagement 模块 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.StateManagement.d.ts` | `AppStorageV2`、`PersistenceV2`、`makeObserved`、`UIUtils`、`ObservedUtil` 等 API |
| 持久化后端接口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.StateManagement.d.ts` | `PersistenceV2.configureBackend(IStorage)`、`IStorage`、`DataType` 声明 |

API 检索建议：

- 装饰器语义：在 SDK 文件中搜索装饰器名（如 `@Param`、`@Trace`）。
- V1/V2 差异：以 SDK 注释中的 API 版本标注为准（V2 装饰器多为 API 12+）。
- `@ohos.arkui.StateManagement`：搜索 `AppStorageV2`、`PersistenceV2`、`makeObserved`、`UIUtils`。
- 具体行为、默认值与错误码以 SDK 声明和源码实现为准，本文档不重述完整行为矩阵。

### 外部依赖入口

状态管理 TS 库主要依赖本仓 C++ 侧通过 JSI 注入的原生对象，无跨仓源码依赖。构建依赖见 `frameworks/bridge/declarative_frontend/state_mgmt/build.py` 与 `generateGni.js`。

| 依赖方向 | 本仓入口 | 说明 |
|----------|----------|------|
| 原生运行时绑定 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/*.native.d.ts` | TS 侧通过 `.d.ts` 声明引用 C++ 注入的全局对象（`aceConsole`、`aceTrace`、`stateMgmtProfiler`、`stateMgmtHistogram`、`ViewStackProcessor`、`NativeView*` 等） |
| 环境后端 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/environment_setting.d.ts` | `EnvironmentSetting` 由 C++ `JSEnvironment` 注入，提供 `colorMode`/`fontScale`/`languageCode` 等 getter |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| TS 单元测试（hvigor 工程） | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/` | hvigor 测试工程根，测试源码在 `entry/src/main/` 下按测试套分组 |
| V1 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v1_tests/` | V1 装饰器、`ObservedPropertyPU`、`@Observed` Proxy、`@Track` 行为回归 |
| V2 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v2_tests/` | V2 装饰器、`ObserveV2`、`@Computed`、`@Monitor`、`@Provider`/`@Consumer` 行为回归 |
| 通用基础测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | `SubscriberManager`、`ObservedObject`、存储、`UIUtils`、Interop 等共享层 |
| Repeat 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/repeat_tests/` | `ForEach`/`Repeat`/`RepeatVirtualScroll` 与状态管理交互 |
| Env 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/env_tests/` | `@Env`/`@CustomEnv`、`EnvV2` 注册表 |
| 性能测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/performance_tests/` | 状态管理性能基准 |
| 构建配置 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/BUILD.gn`、`build-profile.json5`、`oh-package.json5` | hvigor 测试工程构建入口 |
| Context registry | `docs/context_registry.json` | 状态管理子系统的 KB、源码、API、测试统一路由 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 不确定问题属于 V1 还是 V2 | 先看子页面「V1 核心逻辑」「V2 核心逻辑」的定位；V1 用属性包装对象，V2 用 getter/setter + 全局 `ObserveV2` |
| 状态变量修改后 UI 不更新 | 对应子系统页的「变更通知」机制；V1 看 `notifyPropertyHasChangedPU`，V2 看 `ObserveV2.fireChange` |
| 对象/数组/Map/Set 修改不触发更新 | V1 看 `@Observed` Proxy 与 `ObservedObject`；V2 看 `autoProxyObject` 与 `ObjectProxyHandler`/`ArrayProxyHandler`/`SetMapProxyHandler` |
| 渲染期报 "State variable has changed during render!" | V1 核心逻辑页 — `ViewPU.viewPropertyHasChanged` 检测到 `isRenderInProgress` |
| 组件不可见时状态变更是否丢失 | 自定义组件机制页 + V1/V2 核心页 — V1 用 `delayedNotification_` 三态机，V2 用实时 `isViewActive()` 检查 |
| `@Consume`/`@Consumer` 找不到上游 | 对应装饰器页 — V1 `findProvidePU__` 递归搜索，V2 `connectConsumer2Provider` + `WeakRef` |
| 存储删除/清空返回 false | 存储体系页 — 属性仍有订阅者（`numberOfSubscrbers() > 0`） |
| 持久化恢复异常或类型丢失 | 存储体系页 — V1 `MapInfo`/`SetInfo`/`DateInfo` 序列化，V2 `DataCoder` + `@Type` |
| 跨动态/静态前端调用状态异常 | Interop 桥接页 — `needsInterop()`、`InteropStorage`、`deepCopyStaticProxy` |
| elmtId 分配/回收异常 | C++ 绑定页 — `ElementRegister.MakeUniqueId`/`RemoveItem`、`UINodeRegisterProxy` 两清理流程 |
| 性能/内存问题 | 基础设施页 + C++ 绑定页 — `stateMgmtProfiler`、`RecordStateMgmtNode`、`WeakRefPool`、`MAX_FRAME_COUNT_WITHOUT_JS_UNREGISTRATION` |

## 调试入口

- **构建产物定位**：状态管理 TS 编译为单一 `stateMgmt.js`（debug=`dist/`，release=`distRelease/`，profile=`distProfile/`），最终以 `stateMgmt.abc` 字节码在引擎初始化时载入（见 C++ 绑定页）。
- **日志开关**：`hdc shell param set persist.arkui.stateMgmt.debug true`；TS 侧统一走 `stateMgmtConsole`（`LogTag.STATE_MGMT = 0`），关键字见各子页面。
- **Profiler**：`stateMgmtDFX.enableProfiler = true` 输出每次变更的组件名/ID、装饰器类型、变量名、依赖 elmtId 列表、sync peer 信息；C++ 侧对应 `JSStateMgmtProfiler`（V1 遗留）和现代注入式 `stateMgmtProfiler`。
- **属性访问追踪**：V2 调 `stateMgmt.setPropertyAccessTrace(true)` 获取详细 `addRef`/`fireChange` 日志。
- **Inspector/Dump**：`hidumper -s WindowManagerService -a "-dumpAll -r"`、`-viewHierarchy`、`-stateVariables -viewId=N`、`-dirtyElementIds`、`-inactiveComponents`、`RecyclePool`；C++ 入口 `CustomNode::DumpInfo`，TS 入口 `onDumpInspector`。
- **调试信息查询**：`PipelineContext::GetStateMgmtInfo(nodeIds, propertyName, jsonPath)` 上报给 `UiSessionManager`（2000ms 超时）。
- **断点建议**：从对应装饰器实现类的 `set()`/`get()` 入手，V1 跟到 `notifyPropertyHasChangedPU` → `ViewPU.viewPropertyHasChanged`，V2 跟到 `ObserveV2.fireChange` → `updateDirty2Optimized`。

## 相关主题

- 子系统细分见上方「子系统导航」表。
- 自定义组件渲染管线与 `CustomNode`：见「C++ 绑定与宿主节点」与「自定义组件机制」子页面。
- `ForEach`/`LazyForEach`/`Repeat`/`RepeatVirtualScroll` 渲染控制语法专题：`docs/syntax/`。
- 动态/静态前端总体架构：`AGENTS.md` 的「Frontend Support」与 `frameworks/bridge/arkts_frontend/`。
- `@ohos.data.*` 持久化后端（外部仓）：由应用通过 `PersistenceV2.configureBackend(IStorage)` 注入，不在本仓。
