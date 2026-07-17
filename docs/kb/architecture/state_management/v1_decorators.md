# State Management — V1 装饰器 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtV1Decorators`

## 定位

V1 装饰器是 ArkUI 声明式前端的初代状态管理 API，全部编译为 `ObservedPropertyAbstractPU` 的子类（位于 `partial_update/`）。本页覆盖 9 个 V1 组件级装饰器：`@State`（组件私有）、`@Prop`（父→子单向，深拷贝）、`@Link`（父↔子双向，读写穿透）、`@Watch`（变量变化回调）、`@Observed`+`@ObjectLink`（嵌套对象 ES6 Proxy 代理 + 共享引用）、`@Provide`+`@Consume`（祖先-后代双向同步）、`@Track`（`@Observed` 类的属性级精确追踪）。`@StorageLink`/`@StorageProp`/`@LocalStorageLink`/`@LocalStorageProp` 是存储装饰器，本质经 `AppStorage`/`LocalStorage` 的 `__createSync`，详见「存储体系」子页面。V1 装饰器共享 V1 核心逻辑（依赖收集、变更通知、组件冻结），核心机制见「V1 核心逻辑」子页面。

本文档用于快速定位各装饰器实现源码和测试入口。

## 快速路由

### 装饰器实现映射

| 装饰器 | 语义 | 实现 TS 类 / 文件 |
|--------|------|-------------------|
| `@State` | 组件私有状态，赋值触发依赖该变量的 UI 重渲染 | `ObservedPropertyPU<T>`（`partial_update/pu_observed_property.ts`） |
| `@Prop` | 父→子单向同步，每次父重渲染对子做深拷贝 | `SynchedPropertyOneWayPU<C>`（`partial_update/pu_synced_property_one_way.ts`） |
| `@Link` | 父↔子双向同步，读写穿透到源变量 | `SynchedPropertyTwoWayPU<C>`（`partial_update/pu_synced_property_two_way.ts`） |
| `@Watch` | 变量变化时回调（变量名级） | `ViewPU.declareWatch`、`watchedProps` Map、`delayedWatchedProps_`（`partial_update/pu_view.ts`） |
| `@Observed` | 类装饰器，每个实例包装为 ES6 Proxy | `ObservedObject.createNewInternal`（`common/observed_object.ts`） |
| `@ObjectLink` | 共享 ObservedObject 引用（不拷贝），接收方需 `@Observed` | `SynchedPropertyNestedObjectPU<C>`（`partial_update/pu_synced_property_object_nested.ts`） |
| `@Provide` | 祖先注册状态（= `@State` + `addProvidedVar`） | `ObservedPropertyPU` + `ViewPU.addProvidedVar`（`partial_update/pu_view.ts`） |
| `@Consume` | 后代双向同步到 `@Provide` | `SynchedPropertyTwoWayPU` 经 `ViewPU.initializeConsume` |
| `@Track` | `@Observed` 类的属性级精确追踪（仅标记的属性变化才通知） | `TrackedObject`（`partial_update/pu_tracked_object.ts`） + `PropertyDependencies.trackedObjectPropertyDependencies_` |

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| `@State` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_observed_property.ts` | `ObservedPropertyPU`、`ObservedPropertyObjectPU`、`ObservedPropertySimplePU`；`setValueInternal` 5 分支包装（Interop/简单/`SubscribableAbstract`/已 ObservedObject/普通对象） |
| `@Prop` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_synced_property_one_way.ts` | `SynchedPropertyOneWayPU`；API 10+ `deepCopyObjectInternal`（`Map<Object,Object>` 环检测，`__MATERIAL_REFERENCE__` 跳过） |
| `@Link` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_synced_property_two_way.ts` | `SynchedPropertyTwoWayPU`；`changeNotificationIsOngoing_` 防循环通知；`resetSource`/`resetFakeSource`/`fakeSourceBackup_` 用于 BuildNode 脱离/重连 |
| `@ObjectLink` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_synced_property_object_nested.ts` | `SynchedPropertyNestedObjectPU`；无 `source_` 字段，直接经 `addOwningProperty` 订阅 ObservedObject |
| `@Track` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_tracked_object.ts` | `Track` 装饰器 + `TrackedObject`；`notifyObjectValueAssignment` 整对象赋值时按属性比较 |
| `@Observed` + Proxy | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/observed_object.ts` | `Observed`、`ObservedObject`、`SubscribableHandler`/`SubscribableArrayHandler`/`SubscribableMapSetHandler`/`SubscribableDateHandler` |
| `@Provide`/`@Consume` 注册 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts` | `addProvidedVar`、`findProvidePU__`（递归搜索 self→`parent_`→`__parentViewBuildNode__`）、`initializeConsume`、BuildNode 重连三件套 `reconnectToConsume`/`disconnectedConsume`/`reInitializeConsume` |
| `@Watch` 注册 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts` | `declareWatch`、`viewPropertyHasChanged`（标记 dirty 后触发）、`__notifyDecoratedWatch__Internal`（`@Provide` 路径，含冻结延迟） |
| 存储装饰器工厂 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_view.ts` | `createStorageLink`/`createStorageProp`/`createLocalStorageLink`/`createLocalStorageProp`（编译产物入口） |
| 核心基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_observed_property_abstract.ts` | `ObservedPropertyAbstractPU`、`PropertyDependencies`（详见「V1 核心逻辑」子页面） |
| `@Builder` 参数代理 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/partial_update/pu_builder_proxy.ts` | `makeBuilderParameterProxy` — `$$` 参数 Proxy（详见「自定义组件机制」子页面） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `@State` setValueInternal 5 分支 | `pu_observed_property.ts` `setValueInternal` — 按值类型选择 Interop/简单/`SubscribableAbstract`/已 ObservedObject/普通对象自动包装 |
| `@Prop` 深拷贝 | `pu_synced_property_one_way.ts` `deepCopyObjectInternal`（API 10+，环检测） |
| `@Prop` 循环引用降级 | `NativePointer`/`@Sendable` 降级浅拷贝 |
| `@Prop` 子组件修改不回写 | 设计行为，`set()` 仅写 `localCopyObservedObject_` |
| `@Link` 写穿透 + 防循环 | `changeNotificationIsOngoing_` 防源 `set()` 回声 |
| `@Link`/`@Consume` 复用重连 | `resetSource`/`resetFakeSource`/`isSameType` 类型检查 |
| `@Watch` 双触发路径 | `viewPropertyHasChanged`（dirty 后）+ `__notifyDecoratedWatch__Internal`（`@Provide`，含冻结延迟） |
| `@ObjectLink` 无 source | 直接订阅 ObservedObject；`createSourceDependency` 读 fake tracked prop 建立父重渲染依赖 |
| `@Provide` = `@State` + `addProvidedVar` | 别名递归检查祖先链防冲突 |
| `@Consume` 递归搜索 | `findProvidePU__` — self → `parent_` → `__parentViewBuildNode__` |
| BuildNode 复用 @Consume 重连 | `reconnectToConsume`/`disconnectedConsume`/`reInitializeConsume` |
| `@Track` 整对象赋值 | `notifyObjectValueAssignment` 按属性比较，fake props 触发 @Prop/@ObjectLink 源同步 |
| `@Track` 未标记属性读取 | 抛 `NON_TRACK_PROPERTY_ON_UI` |
| `@Observed` Proxy set 路由 | 兼容模式（`notifyObjectPropertyHasChanged`）vs `@Track` 模式（`notifyTrackedObjectPropertyHasChanged`） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common/stateMgmt.d.ts` | 全部 V1 装饰器声明，按装饰器名检索 |
| V1 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/component/stateMgmt.static.d.ets` | 静态 ArkTS 侧 V1 装饰器声明 |

各装饰器允许的变量类型、是否支持 `$$`、API 版本、错误码以 SDK 声明为准。本文档不重述完整语义矩阵。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| V1 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v1_tests/` | 全部 V1 装饰器、`@Provide`/`@Consume`、`@Track`、`@Observed` Proxy 行为回归 |
| Repeat 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/repeat_tests/` | `ForEach`/`Repeat` 与 V1 状态交互 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtV1Decorators` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@State` 赋值未触发更新 | 直接改 `__var` 绕过 setter；值 `===` 未变；UI 未在渲染期读取；组件冻结 |
| `@State` 对象属性修改未更新 | 未 `@Observed` 或未 ObservedObject 包装 |
| `@Track` 读取未标记属性抛错 | `NON_TRACK_PROPERTY_ON_UI`，UI 只能访问被 `@Track` 标记的属性 |
| `@Prop` 子组件修改不回写 | 设计行为（单向），`set()` 仅写 `localCopyObservedObject_` |
| `@Prop` 深拷贝性能问题 | API 10+ 递归深拷贝，每次父重渲染重拷 |
| `@Prop` 循环引用拷贝失败 | `NativePointer`/`@Sendable` 降级浅拷贝 |
| `@Link` 报 "source variable must be defined" | 父组件未用 `$var` 语法传引用 |
| `@Consume` 找不到 `@Provide` | 别名不匹配；非祖先关系；BuildNode 未挂载；祖先链断裂 |
| `@Provide` 别名冲突 | `addProvidedVar` 递归检查祖先链 |
| `@ObjectLink` 传入非 `@Observed` 对象 | `frequentApplicationError` 警告但不阻止 |
| BuildNode 复用后 `@Consume` 未更新 | `reconnectToConsume` 未调用或祖先链未建立 |
| `@Watch` 回调不触发 | 变量未在渲染期被读取（无依赖）；组件冻结期间延迟到激活 |

## 调试入口

- **断点建议**：`ObservedPropertyPU.set()` → `setValueInternal()` → `notifyPropertyHasChangedPU()` → `ViewPU.viewPropertyHasChanged()`。
  - `@Prop`：`constructor`、`reset`、`syncPeerHasChanged`、`resetLocalValue`、`deepCopyObjectInternal`。
  - `@Link`：`constructor`、`set`、`setObject`、`syncPeerHasChanged`、`resetSource`、`isSameType`。
  - `@ObjectLink`：`setValueInternal`、`createSourceDependency`。
  - `@Provide`/`@Consume`：`addProvidedVar`、`findProvidePU__`、`initializeConsume`、`reconnectToConsume`。
- **日志开关**：`hdc shell param set persist.arkui.stateMgmt.debug true`。
- **日志关键字**：`calling @Watch function`、`calling delayed @Watch function`、`delays @Watch function while component is frozen`。
- **`@Track` 标记验证**：`Reflect.has(obj, '___IS_TRACKED_OPTIMISED')`、`___TRACKED_<prop>`。
- **`@Observed` Proxy 排查**：`SubscribableHandler.set/get` 断点，确认兼容模式 vs `@Track` 模式分支。

## 相关主题

- 总览：`docs/kb/architecture/state_management.md`
- V1 核心逻辑（依赖收集、变更通知、冻结、`@Observed` Proxy 体系）：`docs/kb/architecture/state_management/v1_core.md`
- V2 装饰器（V1 的下一代对应）：`docs/kb/architecture/state_management/v2_decorators.md`
- 存储体系（`@StorageLink`/`@StorageProp`/`@LocalStorageLink`/`@LocalStorageProp`）：`docs/kb/architecture/state_management/storage.md`
- 自定义组件机制（`ViewPU`、`@Provide`/`@Consume` 注册、BuildNode 复用）：`docs/kb/architecture/state_management/custom_component.md`
