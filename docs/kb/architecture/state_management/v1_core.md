# State Management — V1 核心逻辑 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtV1Core`

## 定位

V1 核心逻辑是所有 V1 装饰器（`@State`/`@Prop`/`@Link`/`@Provide`/`@Consume`/`@ObjectLink`/`@Watch`/`@Track`）共享的底层基础设施，职责包括：渲染期依赖收集（记录 elmtId ← 状态变量）、状态变更通知（精确触发依赖该变量的 UI 元素局部重渲染）、`@Observed` 对象的 ES6 Proxy 代理（嵌套对象变化感知）、组件冻结（非激活组件延迟通知）。V1 同时存在 PU（Partial Update，现代主路径，`partial_update/`）和 FU（Full Update，遗留路径，`full_update/`）两条渲染路径，由 `ConfigureStateMgmt` 决定；新组件默认走 PU，FU 仅用于历史兼容。PU 与 FU 共享 `ObservedPropertyAbstract` 基类，但 PU 覆盖了通知方法，使用 elmtId 级精确依赖追踪而非全量重渲染。

本文档用于快速定位 V1 核心相关源码和测试入口。具体装饰器语义见「V1 装饰器」子页面，C++ 后端集成见「C++ 绑定」子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| PU 视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts` | `ViewPU`（抽象）— 渲染调度、dirty 集合、`@Watch`/`@Provide`/`@Consume` 注册、组件冻结、`@StorageLink` 工厂 |
| PU 抽象属性基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_observed_property_abstract.ts` | `ObservedPropertyAbstractPU<T>` + `PropertyDependencies` — 依赖收集、`notifyPropertyHasChangedPU`、`DelayedNotifyChangesEnum` 三态机 |
| `@State`/`@Provide` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_observed_property.ts` | `ObservedPropertyPU<T>`、`ObservedPropertyObjectPU`、`ObservedPropertySimplePU` |
| `@Link`/`@Consume` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_synced_property_two_way.ts` | `SynchedPropertyTwoWayPU`、Object/Simple 变体 |
| `@Prop` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_synced_property_one_way.ts` | `SynchedPropertyOneWayPU`（含 API 10+ 深拷贝） |
| `@ObjectLink` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_synced_property_object_nested.ts` | `SynchedPropertyNestedObjectPU`（源码另有拼写 `SynchedPropertyNesedObjectPU`） |
| `@Track` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_tracked_object.ts` | `Track` 装饰器 + `TrackedObject`（含 `notifyObjectValueAssignment`） |
| `@Observed` + Proxy 体系 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/observed_object.ts` | `Observed`、`ObservedObject`、`SubscribableHandler`、`SubscribableArrayHandler`、`SubscribableMapSetHandler`、`SubscribableDateHandler`、`ExtendableProxy` |
| 公共抽象属性基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/observed_property_abstract.ts` | `ObservedPropertyAbstract<T>` — 订阅管理、FU `notifyHasChanged`、`createSync` 工厂 |
| SDK 抽象基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/subscribed_abstract_property.ts` | `SubscribedAbstractProperty<T>` — `AppStorage.link()`/`LocalStorage.link()` 的返回类型 |
| 订阅管理单例 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/subscriber_lookup.ts` | `SubscriberManager` — 全局 `IPropertySubscriber` 注册表，`MakeUniqueId`/`MakeStateVariableId` |
| FU 视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/full_update/fu_view.ts` | `View`（抽象，extends `NativeViewFullUpdate`） |
| FU 属性实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/full_update/fu_observed_property_object.ts`、`fu_observed_property_simple.ts` | `ObservedPropertyObject`/`ObservedPropertySimple`（遗留） |
| elmtId→View 映射 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_uinode_registry_proxy.ts` | `UINodeRegisterProxy` — elmtId 到 `IView` 的映射、已删除 elmtId 同步 |
| C++ 管线集成 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `RecordStateMgmtNode`（dirty node 计数）、`GetStateMgmtInfo`、`CallStateMgmtCleanUpIdleTaskFunc` |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| 渲染期 elmtId 缓存 | `partial_update/pu_observed_property_abstract.ts` `getRenderingElmtId()` |
| get() 触发依赖记录 | `partial_update/pu_observed_property_abstract.ts` `recordPropertyDependentUpdate()` |
| 依赖数据结构 | `partial_update/pu_observed_property_abstract.ts` `PropertyDependencies`（`propertyDependencies_` + `trackedObjectPropertyDependencies_`） |
| 变更通知主路径 | `partial_update/pu_observed_property_abstract.ts` `notifyPropertyHasChangedPU()` |
| PU 覆盖 FU 通知为空 | `partial_update/pu_observed_property_abstract.ts` `notifyHasChanged()`（被覆盖） |
| 冻结三态枚举 | `partial_update/pu_observed_property_abstract.ts` `DelayedNotifyChangesEnum`（`do_not_delay=0`/`delay_none_pending=1`/`delay_notification_pending=2`） |
| 启用/处理延迟通知 | `partial_update/pu_observed_property_abstract.ts` `enableDelayedNotification()`/`moveElmtIdsForDelayedUpdate()` |
| ViewPU 标记 dirty | `partial_update/pu_view.ts` `viewPropertyHasChanged()`、`markNeedUpdate()`、`performDelayedUpdate()` |
| 冻结态传播 | `partial_update/pu_view.ts` `setActiveInternal()`、`onActiveInternal()`、`onInactiveInternal()` |
| `@Observed` Proxy set trap | `common/observed_object.ts` `SubscribableHandler.set()`（兼容模式 vs `@Track` 模式分支） |
| `@Observed` Proxy get trap | `common/observed_object.ts` `SubscribableHandler.get()`（`@Track` 依赖收集 `readCbFunc_`） |
| V2 对象拒绝检查 | `partial_update/pu_observed_property_abstract.ts` `checkIsSupportedValue`（拒绝 `@ObservedV2` 对象） |

### API 入口

V1 装饰器的 SDK 声明位于 `interface/sdk-js` 仓（不在本仓），按装饰器名检索：

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common/stateMgmt.d.ts` | `@State`/`@Prop`/`@Link`/`@Watch`/`@Provide`/`@Consume`/`@Observed`/`@ObjectLink`/`@Track` 声明 |
| V1 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/component/stateMgmt.static.d.ets` | 静态 ArkTS 侧 V1 装饰器声明 |

具体装饰器语义、允许的变量类型、API 版本与错误码以 SDK 声明为准，本文档不重述。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| V1 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v1_tests/` | V1 装饰器、`ObservedPropertyPU`、`@Observed` Proxy、`@Track`、`@Provide`/`@Consume` 行为回归 |
| 通用测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | `SubscriberManager`、`ObservedObject`、Proxy handler、PU/FU 基础类 |
| Repeat 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/repeat_tests/` | `ForEach`/`Repeat` 与 V1 状态交互 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtV1Core` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 渲染期修改状态变量抛 "State variable has changed during render!" | `ViewPU.viewPropertyHasChanged` 检测到 `isRenderInProgress`；将修改移到事件回调/生命周期/`setTimeout` |
| 对象属性修改（`this.obj.name = x`）未触发 UI 更新 | 对象未 `@Observed` 或未通过 `ObservedObject.createNew` 包装；只有 Proxy 包装对象的 set trap 才通知 |
| FU vs PU 路径选择 | PU 是现代主路径，由 `ConfigureStateMgmt` 决定；FU 仅历史兼容，PU 覆盖了 `notifyHasChanged` 为空 |
| `@Track` 类中读取未标记属性 | 抛 `NON_TRACK_PROPERTY_ON_UI`；UI 只能访问被 `@Track` 标记的属性 |
| `@ObservedV2` 对象用作 V1 `@State` 被拒 | `checkIsSupportedValue` 显式拒绝 V2 对象，V1/V2 不应混用 |
| 组件冻结后状态变更是否丢失 | 不会；`delay_notification_pending` 保留待处理 elmtId，激活时 `performDelayedUpdate` 统一处理 |
| 依赖收集为何有时不生效 | 非渲染期 `getRenderingElmtId()` 返回 `notRecordingDependencies`（-1），不记录依赖 |
| `SynchedPropertyNesedObject` 拼写 | 源码拼写错误（应为 Nested），与 PU 侧命名不一致 |

## 调试入口

- **日志关键字**（统一走 `stateMgmtConsole`）：`ObservedPropertyPU`、`viewPropertyHasChanged`、`recordPropertyDependentUpdate`、`performDelayedUpdate`、`enableDelayedNotification`、`SubscribableHandler`。
- **Profiler dump**：`stateMgmtDFX.enableProfiler = true`，每次变更输出组件名/ID、装饰器类型、变量名、依赖 elmtId 列表、sync peer 信息。
- **调试信息查询**：`PipelineContext::GetStateMgmtInfo(nodeIds, propertyName, jsonPath)`（2000ms 超时）上报给 `UiSessionManager`。
- **断点建议**：`ObservedPropertyPU.set()` → `setValueInternal()` → `notifyPropertyHasChangedPU()` → `ViewPU.viewPropertyHasChanged()` → `markNeedUpdate()`。
- **`@Observed` Proxy 排查**：断点 `SubscribableHandler.set()`/`get()`，确认值是否变化（`Reflect.get === newValue` 跳过）及兼容模式 vs `@Track` 模式分支。

## 相关主题

- 总览：`docs/kb/architecture/state_management.md`
- V1 装饰器具体语义：`docs/kb/architecture/state_management/v1_decorators.md`
- C++ 后端集成（`stateMgmt.abc` 载入、`JSStateMgmtProfiler`、`PipelineContext`）：`docs/kb/architecture/state_management/cpp_bindings.md`
- 基础设施（`SubscriberManager`、`UINodeRegisterProxy`）：`docs/kb/architecture/state_management/infrastructure.md`
- V2 对应核心：`docs/kb/architecture/state_management/v2_core.md`
- 自定义组件机制（`ViewPU` 创建/复用/冻结/生命周期）：`docs/kb/architecture/state_management/custom_component.md`
