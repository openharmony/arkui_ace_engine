# State Management — 基础设施 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtInfrastructure`

## 定位

基础设施层是 V1、V2、PU、Interop 共享的横切关注点：特性开关（`ConfigureStateMgmt`）、日志（`stateMgmtConsole`）、DFX/Profiler、API 版本工具、Sendable 检测、GC 回调、elmtId→View 映射同步、update-function 记录、SDK 公共工具类（`UIUtils`/`ObservedUtil`/`SubscribableAbstract`）。它把 TS 状态管理运行时与本仓 C++ 侧（`aceConsole`、`aceTrace`、`PipelineContext::OnIdle`）桥接起来，既不属于某个装饰器，也不属于存储或视图，而是被所有上层复用。

本文档用于快速定位基础设施相关源码和测试入口。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 特性开关 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/state_mgmt_configure.ts` | `ConfigureStateMgmt` 单例 — 跟踪 V2/PU 特性使用，`needsV2Observe()` |
| 日志门面 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/state_mgmt_console_trace.ts` | `stateMgmtConsole`、`stateMgmtTrace`、`errorReport`、`LogTag`；`limitLog` 20s 去重窗口（`MAX_LOG_TYPES = 3000`） |
| DFX 信息收集 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/state_mgmt_dfx.ts` | `stateMgmtDFX`、`DumpInfo`、`aceDebugTrace`、`getStateMgmtInfo`、`findViewById` |
| Profiler 门面 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/state_mgmt_profiler.ts` | `stateMgmtProfiler` — 由 C++ 注入实例 |
| API 版本工具 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/utils.ts` | `Utils`（`getApiVersion`、`isApiVersionEQAbove`） |
| Sendable 检测 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/sendable_type.ts` | `SendableType` — Sendable 容器检测 |
| GC 回调代理 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/arkui_object_finalization_register_proxy.ts` | `ArkUIObjectFinalizationRegisterProxy` — jsMemoryWatch 的 GC 回调 |
| WeakRef 池 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/weakref_pool.ts` | `WeakRefPool` — 规范化 WeakRef + `FinalizationRegistry`，V2 依赖图 GC |
| elmtId→View 映射 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_uinode_registry_proxy.ts` | `UINodeRegisterProxy` — elmtId→`IView` 映射、C++ 已删除 elmtId 同步、`uiNodeCleanUpIdleTask` |
| update-function 记录 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_updatefunc.ts` | `UpdateFuncRecord`、`UpdateFuncsByElmtId` — 每 elmtId 的更新函数 + If/Else 的 `isPending`/`isChanged` |
| 自定义可观察类型 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/subscribable_abstract.ts` | `SubscribableAbstract` — V1 SDK 抽象基类，供应用实现自定义可观察类型 |
| UI 工具类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/ui_utils.ts` | `UIUtilsImpl` — `getTarget`、`makeObserved`、`canBeObserved`、`addMonitor`、`clearMonitor`、`applySync`、`flushUpdates`、`flushUIUpdates` |
| 可观察检测 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/observed_util.ts` | `ObservedUtil` — `canBeObserved` 检测顺序（V2 → makeObserved → V2Proxy → V1），`ObservedReason` |
| 生命周期状态机 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/pu_lifecycle.ts` | `CustomComponentLifecycle`（5 态 FSM）+ 新生命周期装饰器（详见「自定义组件机制」子页面） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| V2 特性检测 | `common/state_mgmt_configure.ts` `needsV2Observe()` — 任何 `usingV2ObservedTrack` 调用后变 true |
| 日志去重 | `common/state_mgmt_console_trace.ts` `limitLog`（20s 窗口）、`frequentApplicationError` vs `applicationError` |
| DFX elmtId 命名映射 | `common/state_mgmt_dfx.ts` `getElementName` — 按 ID 区间映射到 @Computed/@Monitor/PersistenceV2 名 |
| Inspector 查询 | `common/state_mgmt_dfx.ts` `getStateMgmtInfo(nodeIds, propertyName, jsonPath)`（2000ms 超时） |
| 已删除 elmtId 同步（双流程） | `partial_update/pu_uinode_registry_proxy.ts` — A 延迟（下次重渲染 `purgeDeletedElmtIds`），B 即时（`aboutToBeDeleted` + `PipelineContext::OnIdle` 经 `uiNodeCleanUpIdleTask`） |
| If/Else 分支暂存 | `puv2_common/puv2_updatefunc.ts` `UpdateFuncRecord.isPending`/`isChanged` |
| `SubscribableAbstract` 三通知路径 | `sdk/subscribable_abstract.ts` `notifyPropertyHasChanged` — PU TrackedObject / FU 单一 / PU 多个 |
| `UIUtils` 刷新 API 区分 | `sdk/ui_utils.ts` — `applySync`（task + 全部 pending）、`flushUpdates`（全部 pending）、`flushUIUpdates`（仅 UI 节点，不处理 Computed/Monitor/Persistence）；在 `@Computed` 内调用抛 `140001` |
| `addMonitor` 不能用匿名函数 | 使用 `monitorFunc.name` 作 key（`v2/v2_change_observation.ts`） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| StateManagement 模块 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.StateManagement.d.ts` | `UIUtils`（`makeObserved`/`addMonitor`/`clearMonitor`/`applySync`/`flushUpdates`/`flushUIUpdates`）、`ObservedUtil`、`SubscribableAbstract` |
| V1 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `SubscribableAbstract`、`SubscribedAbstractProperty` 相关类型 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 通用测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | 日志、`Utils`、`UINodeRegisterProxy`、`SubscribableAbstract`、`UIUtils`、Profiler |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtInfrastructure` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-07` | `specs/07-frontend/02-state-management/07-state-management-utilities` | Baselined（UIUtils 2 Feat） |
## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `frequentApplicationError` vs `applicationError` 区别 | 前者 20s 窗口去重，后者每次输出（`state_mgmt_console_trace.ts`） |
| `needsV2Observe()` 何时变 true | 任何 `usingV2ObservedTrack` 调用（`@ObservedV2`/`@Trace`/`@Monitor` 应用） |
| 已删除 elmtId 同步为何有两条流程 | A 延迟（下次重渲染），B 即时（CustomNode 析构）+ `OnIdle` 补充 |
| `UpdateFuncRecord.isPending`/`isChanged` 用途 | If/Else 分支切换时暂存变更状态 |
| `stateMgmtProfiler` 实例何时注入 | C++ 初始化时 `stateMgmtProfiler.init(instance)` |
| `addMonitor` 报错 | 不能用匿名函数，使用 `monitorFunc.name` 作 key |
| `flushUIUpdates` 与 `flushUpdates` 区别 | 前者仅处理 `elmtIdsChanged_`，不处理 Computed/Monitor/Persistence |
| `applySync`/`flushUpdates` 在 `@Computed` 内调用 | 抛错误 `140001` |
| Profiler dump 缺少变量名 | `stateMgmtDFX.getElementName` 按 elmtId 区间映射，跨区间 ID 可能无名 |

## 调试入口

- **日志 TAG**：`stateMgmtConsole` 走 `LogTag.STATE_MGMT = 0`。
- **DFX 开关**：`setProfilerStatus()` / `setAceDebugMode()` 切换 DFX；`aceDebugTrace.begin/end` 仅在 `enableDebug = true` 时触发。
- **Inspector 查询**：`getStateMgmtInfo(nodeIds, propertyName, jsonPath)`（2000ms 超时）。
- **View 查找**：`findViewById(id)`（`state_mgmt_dfx.ts`，经 `SubscriberManager`）。
- **Profiler 实例**：检查 `stateMgmtProfiler` 是否被 C++ 注入（未注入时为桩）。

## 相关主题

- 总览：`docs/kb/frontend/state_management.md`
- V1/V2 核心（消费这些基础设施）：`docs/kb/frontend/state_management/v1_core.md`、`v2_core.md`
- C++ 绑定（`aceConsole`/`aceTrace`/`OnIdle` 反向调用）：`docs/kb/frontend/state_management/cpp_bindings.md`
- 自定义组件机制（消费 `UpdateFuncRecord`/生命周期 FSM）：`docs/kb/frontend/state_management/custom_component.md`
