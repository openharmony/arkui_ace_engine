# State Management — 自定义组件机制 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtCustomComponent`

## 定位

自定义组件机制是 `ViewPU`（V1 `@Component` 基类）与 `ViewV2`（V2 `@ComponentV2` 基类）在装饰器之外的内部实现：组件创建管线（`observeComponentCreation`/`observeComponentCreation2`）、dirty 元素更新（`updateDirtyElements`）、`@Consume`/`@Consumer` 跨层重连、组件复用（`@Reusable`/`reuseOrCreateNewComponent`）、组件冻结（`freezeWhenInactive`）、生命周期状态机（新旧两套并存）、`@Builder`（`$$` 参数代理、动态切换）。`PUV2ViewBase` 是两者的共享抽象基类；V1/V2 在 C++ 侧共用同一 `CustomNode` 宿主，仅靠 `isV2_` 区分。生命周期有两套并存系统：遗留直接回调（`aboutToAppear`/`aboutToDisappear` 等）和新状态机装饰器（`@ComponentInit`/`@ComponentAppear` 等）。`@Styles`/`@Extend`/`@Require` 是纯编译期特性，运行时无对应代码。

本文档用于快速定位自定义组件机制相关源码和测试入口。装饰器本身见 V1/V2 装饰器子页面；C++ 宿主节点见「C++ 绑定」子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| V1 视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts` | `ViewPU`（抽象）— 组件创建、dirty 更新、`@Provide`/`@Consume`、存储装饰器工厂、复用、冻结 |
| V2 视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_view.ts` | `ViewV2`（抽象）— V2 dirty 更新、`ObserveV2` 依赖记录、复用、Monitor/Computed 管理 |
| 共享视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_base.ts` | `PUV2ViewBase`（抽象）— activeCount、`freezeWhenInactive` 继承、`onDumpInfo` 解析、新生命周期装饰器执行 |
| 生命周期状态机 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/pu_lifecycle.ts` | `CustomComponentLifecycle`（5 态 FSM）+ 新生命周期装饰器（`@ComponentInit` 等） |
| V1 复用池 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_recycle_manager.ts` | `RecycleManager` + `BidirectionalMap` — V1 按父节点的复用池 |
| V2 复用池 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_recycle_pool.ts` | `RecyclePoolV2` + `RecycledIdRegistry` |
| 全局跨父复用池 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_globalreuse.ts` | `__ReusePool__Internal` — shared/perInstance 两种模式 |
| update-function 记录 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_updatefunc.ts` | `UpdateFuncsByElmtId`、`UpdateFuncRecord`（含 If/Else `isPending`/`isChanged`） |
| `@Builder` 参数代理 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_builder_proxy.ts` | `makeBuilderParameterProxy` — `$$` Proxy |
| BuildNode 视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_buildnode_base.ts` | `ViewBuildNodeBase`（抽象） |
| C++ 宿主节点 | `frameworks/core/components_ng/pattern/custom/custom_node.cpp`、`custom_node_base.cpp` | `CustomNode`/`CustomNodeBase` — 生命周期回调容器（见「C++ 绑定」子页面） |
| `WrappedBuilder` 类型 | `frameworks/bridge/declarative_frontend/ark_node/types/index.d.ts` | `WrappedBuilder` 类型声明（`wrapBuilder` 返回） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `observeComponentCreation2` 流程 | `pu_view.ts` / `v2_view.ts` — elmtId 入 `currentlyRenderedElmtIdStack_`，注册 `UpdateFuncRecord` 到 `updateFuncByElmtId`，注册 elmtId→View 到 `UINodeRegisterProxy.ElementIdToOwningViewPU_`，执行 updateFunc |
| `updateDirtyElements` 循环（V1） | `pu_view.ts` `updateDirtyElements` — purge 已删除 → 升序排序 → `UpdateElement(elmtId)`（父先于子）→ 合并 `dirtRetakenElementIds_` |
| V2 dirty 更新 | `v2_view.ts` `uiNodeNeedToUpdateV2`/`updateDirtyElements` |
| `@Consume` 重连三件套 | `pu_view.ts` `reconnectToConsume`（挂载时找真实 `@Provide`）、`disconnectedConsume`（兜底默认值）、`reInitializeConsume`（全局复用时全量重初始化） |
| V2 Monitor 延迟集 | `v2_view.ts` `monitorIdsDelayedUpdate__`/`monitorIdsDelayedUpdateForAddMonitorBased__`/`computedIdsDelayedUpdate__`，在 `performDelayedUpdate` 处理 |
| V1 冻结 | 每个 `ObservedPropertyAbstractPU` 的 `delayedNotification_` 三态（见「V1 核心逻辑」） |
| V2 冻结 | 每个 `ObserveV2` 通知点实时检查 `isViewActive()`，无枚举 |
| V2 复用自动冻结 | `v2_view.ts` `freezeRecycledComponent`（`activeCount_--`）、`unfreezeReusedComponent`（重放 `elmtIdsDelayedUpdate_` 到 `elmtIdsChanged_`） |
| V2 复用 Monitor 重置 | `v2_view.ts` `resetMonitorsOnReuse`/`resetAllMonitorsOnReuse` |
| 新生命周期 FSM | `pu_lifecycle.ts` 5 态（INIT→APPEARED→BUILT→RECYCLED→DISAPPEARED）+ 事件（ON_APPEAR/ON_BUILD/ON_RECYCLE/ON_REUSE/ON_DISAPPEAR）；`executeInternalFunction`（装饰器方法）先于 `handleObserverFunction`（observer 回调） |
| `@Component*` 装饰器 | `pu_lifecycle.ts` `@ComponentInit`/`@ComponentAppear`/`@ComponentBuilt`/`@ComponentReuse`/`@ComponentRecycle`/`@ComponentDisappear`/`@ComponentActive`/`@ComponentInactive` — 置 `__newLifecycleNeedWork__Internal=true` 并 push 到 Symbol-keyed 数组 |
| Active/Inactive ref-counting | `puv2_view_base.ts` `activeCount_`（API 18+ 引用计数）、`executeActiveOrInactiveLifecycleByNonFreezeCount`（非冻结组件） |
| `freezeWhenInactive` 继承 | 子未设置则继承父（`puv2_view_base.ts`） |
| `@ComponentInit` 执行时机 | 非状态机，在 `__customComponentExecuteInit__Internal` 构造期执行 |
| `mutableBuilder` 动态切换 | `pu_view.ts`/`v2_view.ts` `mutableBuilderImpl` — 当作 If/Else，`builderId` 变化清理旧子 + 渲染新 builder；`builderIdMap_` WeakMap 从 1000000 起 ID |
| `makeBuilderParameterProxy` | `pu_builder_proxy.ts` — `$$` Proxy，set 抛 `INVALID_SET_IN_BUILDER`，get 执行函数参数或对 ObservedProperty 返回 `.get()` |
| `@Styles`/`@Extend`/`@Require` | 纯编译期，编译器内联，无运行时代码 |
| 新旧生命周期并存 | 不冲突，C++ 按顺序调用两套（旧 `FireOnAppear` 先，新 `FireTriggerLifecycleFunc` 后） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `@Component`、`@Reusable`、`@Builder`、`@BuilderParam`、`@Styles`、`@Extend`、`@Require` 声明 |
| V2 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts` | `@ComponentV2`、新生命周期装饰器（`@ComponentInit` 等）声明 |
| `WrappedBuilder` 类型 | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common.d.ts`（按 `WrappedBuilder`/`wrapBuilder` 检索） | `wrapBuilder` 返回类型 |
| V1/V2 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | 静态 ArkTS 侧组件相关装饰器 |

生命周期回调签名、`@Builder`/`@BuilderParam` 约束、`freezeWhenInactive` 选项、API 版本以 SDK 声明为准。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| V1 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v1_tests/` | `ViewPU` 创建/更新、`@Consume` 重连、复用、冻结 |
| V2 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v2_tests/` | `ViewV2` 创建/更新、复用自动冻结、Monitor 重置 |
| Repeat 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/repeat_tests/` | 复用场景（`reuseOrCreateNewComponent`/`recycleSelf`） |
| 通用测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | 生命周期状态机、冻结、`UpdateFuncRecord` |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtCustomComponent` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-03-01` | `specs/07-frontend/03-custom-components/01-componentization` | Baselined |
| `07-03-02` | `specs/07-frontend/03-custom-components/02-component-lifecycle` | Baselined |
| `07-03-03` | `specs/07-frontend/03-custom-components/03-component-reuse` | Baselined |
| `07-03-04` | `specs/07-frontend/03-custom-components/04-component-freeze` | Baselined |
## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `observeComponentCreation` vs `observeComponentCreation2` | 前者旧版无 classObject，后者现代版（`_componentName`/`_popFunc`） |
| `ViewV2` 不支持 `observeRecycleComponentCreation` | V2 用 `reuseOrCreateNewComponent` |
| V1/V2 `performDelayedUpdate` 区别 | V1 处理 `delayedWatchedProps_`；V2 处理 `monitorIdsDelayedUpdate__`/`computedIdsDelayedUpdate__` |
| 新旧生命周期冲突 | 不冲突，C++ 按顺序调用两套（旧先、新后） |
| `@ComponentInit` 何时执行 | 非状态机，构造期执行 |
| `freezeWhenInactive` 是否继承 | 子未设置则继承父 |
| 冻结期间状态变更是否丢失 | 不会；V1 `delay_notification_pending` 保留，V2 `scheduleDelayedUpdate`/`addDelayedMonitorIds` 存储 |
| `reuseId` 作用 | 池中区分组件类型的 key，相同可互换；默认类名 |
| V2 回收为何冻结 | 池中组件状态变量仍可能被引用，冻结避免无效更新 |
| `@Styles`/`@Extend`/`@Require` 运行时找不到 | 纯编译期，编译器内联，无运行时代码 |
| `mutableBuilder` 动态切换原理 | `builderId` 变化时清理旧子 + 渲染新 builder（`ifElseBranchUpdateFunction`） |
| `$$` 在 `@Builder` 中赋值报错 | `makeBuilderParameterProxy` 的 set 抛 `INVALID_SET_IN_BUILDER` |
| BuildNode 复用后 `@Consume` 未更新 | `reconnectToConsume` 未调用或祖先链未建立 |

## 调试入口

- **TS 调试方法**：`this.debugInfoViewHierarchy(true)`、`this.debugInfoUpdateFuncByElmtId(true)`、`this.dumpStateVars()`、`PUV2ViewBase.onDumpInfo`（解析 `-viewId=N`/`-r`）。
- **hidump**：`hidumper -s WindowManagerService -a "-dumpAll -r"`、`-viewHierarchy`、`-stateVariables -viewId=N`、`-dirtyElementIds`、`-inactiveComponents`、`-profiler`、`RecyclePool`。
- **日志关键字**：`calling @Watch function`、`calling delayed @Watch function`、`delays @Watch function while component is frozen`。
- **DFX trace**：`ViewPU.viewPropertyHasChanged / <Component> / <var> / <depCount>`。
- **同步更新检查**：`SyncedViewRegistry.dirtyNodesList`。
- **断点建议**：`observeComponentCreation2`、`updateDirtyElements`、`reconnectToConsume`、`recycleSelf`、`setActiveInternal`、`CustomNode::Render`。

## 相关主题

- 总览：`docs/kb/frontend/state-management.md`
- V1/V2 核心：`docs/kb/frontend/state_management/v1-core.md`、`v2-core.md`
- V1/V2 装饰器：`docs/kb/frontend/state_management/v1-decorators.md`、`v2-decorators.md`
- C++ 绑定（`CustomNode`/`ViewFunctions` 生命周期）：`docs/kb/frontend/state_management/cpp-bindings.md`
- 基础设施（`UpdateFuncRecord`/`UINodeRegisterProxy`/生命周期 FSM）：`docs/kb/frontend/state_management/infrastructure.md`
- [静态自定义组件状态相关（arkoala 侧）：`docs/kb/frontend/state_management/static-custom-component.md`](static-custom-component.md)