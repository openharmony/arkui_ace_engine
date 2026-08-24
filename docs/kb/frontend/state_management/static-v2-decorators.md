# Static State Management — V2 装饰器与数据对象 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticV2Decorators`

## 定位

静态前端（ArkTS 1.2 / arkoala）V2 组件级装饰器与数据对象级观测。组件级装饰器（`@Local`/`@Param`/`@Provider`/`@Consumer`/`@Monitor`/`@Computed`）有完整的运行时类实现；数据对象级装饰器（`@ObservedV2`/`@Trace`）**不直接**在 arkoala 源码中实现运行时，而是通过 **UIPlugin 转换**为对应的 `IMutableStateMeta`/`MutableStateMeta`，由静态侧元数据系统驱动观测。

本域覆盖 FuncID `07-02-11`（静态V2组件内 — 装饰器部分）和 `07-02-12`（静态V2数据对象 — UIPlugin 转换）。

## 快速路由

### 源码入口

#### V2 组件级装饰器

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| `@Local` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorLocal.ts` | `LocalDecoratedVariable<T>` — `set` 自动 `autoProxyObject`，与动态侧 observed 对象经 `isDynamicObject`/`getV2ObservedObject` 互操作 |
| `@Param` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorParam.ts` | `ParamDecoratedVariable<T>` — `update(newValue)` 经 `StateUpdateLoop.add` 延迟，受 `__getCanUpdateStateVars__Internal()` 门控；不可变读 |
| `@Param @Once` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorParamOnce.ts` | `ParamOnceDecoratedVariable<T>` — 可变一次的 `@Param` 变体 |
| `@Provider` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorProvider.ts` | `ProviderDecoratedVariable<T>` — `__addProvider__Internal` 注册，`viewV2` 字段用于与动态 V2 互操作 |
| `@Consumer` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorConsumer.ts` | `ConsumerDecoratedVariable<T>` — `__findProvider__Internal` 查找，无 provider 时回退本地 backing，`rebindProviderOnReparent()` 复用重绑 |
| `@Monitor`/`@SyncMonitor` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorMonitor.ts` | `MonitorFunctionDecorator`/`MonitorValueInternal`/`MonitorValuePublic` — `IMonitor` API（`dirty[]`/`value<T>(path?)`）、通配符（`enableWildcard`）、`MIN_SYNC_MONITOR_ID` 同步/异步分发 |
| `@Computed` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorComputed.ts` | `ComputedDecoratedVariable<T>` — 惰性缓存值，`runFunctionAndObserve` 切换 `RenderingComputed`，`clearReverseBindings` 清理旧 binding |

#### V2 数据对象级（UIPlugin 转换）

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| UIPlugin 转换入口 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ets` | `enableCompatibleObservedV2ForStatic<T>`/`enableCompatibleObservedV2ForStaticMeta<T>` — 将静态侧 `@ObservedV2` 对象转换为 `MutableStateMeta` 通道 |
| Backing Value（V2 类） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/interopBackingValue.ts` | `InteropV2DecoratorBackingValue<T>` — 调 `enableCompatibleObservedV2ForStaticMeta(value)` 为 V2 对象绑定静态侧元数据 |
| 元数据安装 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ets` `staticStateBindObservedObject` | 为 V2 对象的每个 `@Trace` 属性创建 `IMutableStateMeta`，绑定 addRef/fireChange 通道 |
| Backing Value 基类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/interopBackingValue.ts` `DecoratorBackingValue<T>`/`IBackingValue<T>` | `InteropDecoratorBackingValue`（V1）/`InteropV2DecoratorBackingValue`（V2）的共享基类 |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `@Local` V1/V2 对象互操作 | `decoratorImpl/decoratorLocal.ts` `isDynamicObject`/`getV2ObservedObject` — 识别动态侧 observed 对象并通过 `FactoryInternal.mkInteropV2DecoratorValue` 桥接 |
| `@Param` 延迟更新 | `decoratorImpl/decoratorParam.ts` `StateUpdateLoop.add` — `update` 入队，受 `__getCanUpdateStateVars__Internal()` 门控 |
| `@Consumer` 复用重绑 | `decoratorImpl/decoratorConsumer.ts` `rebindProviderOnReparent()` — 跨父组件复用时重新查找 provider 并刷新 |
| `@Monitor` 通配符 | `decoratorImpl/decoratorMonitor.ts` `enableWildcard` — 仅路径末尾支持通配符匹配 |
| `@ObservedV2`/`@Trace` UIPlugin 路径 | `component/interop.ts` `enableCompatibleObservedV2ForStatic` — 不直接实现 V2 类观测运行时，通过 UIPlugin 转换为 `MutableStateMeta` |
| V2 对象属性元数据 | `component/interop.ts` `staticStateBindObservedObject(value, fireChange, onTrackPropertyRead, onTrackPropertyChange)` — 为 `@Trace` 属性安装 read/change 回调，转发到静态侧 `MutableStateMeta.addRef`/`fireChange` |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V2 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@Local`/`@Param`/`@Once`/`@Event`/`@Provider`/`@Consumer`/`@Monitor`/`@SyncMonitor`/`@Computed`/`@ObservedV2`/`@Trace` + `IMonitor`/`IMonitorValue` 接口 |
| `@ComponentV2` 生命周期 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@ComponentInit`/`@ComponentAppear`/`@ComponentBuilt`/`@ComponentReuse`/`@ComponentRecycle`/`@ComponentDisappear`/`@ComponentActive`/`@ComponentInactive`（`@since 24 static`/`26.0.0 static`） |
| Barrel 总入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 重导出全部子模块 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 装饰变量测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/` | V2 装饰变量行为回归 |
| 互操作测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/mock/` | `interopStorageV2.ts`/`interop.ts` 测试桩 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticV2Decorators` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-11` | `specs/07-frontend/02-state-management/11-static-v2-component-state/` | active（Feat-02~04 待补充） |
| `07-02-12` | `specs/07-frontend/02-state-management/12-static-v2-data-object-state/` | active（Feat-01 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@ObservedV2`/`@Trace` 对象修改不触发更新 | `component/interop.ts` `enableCompatibleObservedV2ForStatic` — 确认 UIPlugin 转换是否成功为 `@Trace` 属性创建 `MutableStateMeta` |
| `@Local` 收到 V2 对象后不观测 | `decoratorLocal.ts` `isDynamicObject`/`getV2ObservedObject` — V2 对象需经 `mkInteropV2DecoratorValue` 桥接 |
| `@Consumer` 复用后状态错误 | `decoratorConsumer.ts` `rebindProviderOnReparent` — 跨父组件复用时是否重新绑定了 provider |
| `@Monitor` 同步回调时序异常 | `decoratorMonitor.ts` `isSynchronous` — `@SyncMonitor` 走同步路径，`@Monitor` 走异步 |
| `@Computed` 依赖丢失 | `decoratorComputed.ts` `clearReverseBindings` — 依赖变化时是否清理旧 binding 后重新收集 |

## 调试入口

- **日志关键字**：`LocalDecoratedVariable`、`ParamDecoratedVariable`、`ProviderDecoratedVariable`、`ConsumerDecoratedVariable`、`MonitorFunctionDecorator`、`ComputedDecoratedVariable`、`enableCompatibleObservedV2ForStatic`。
- **UIPlugin 转换排查**：断点 `component/interop.ts` `staticStateBindObservedObject`，确认 `@Trace` 属性的 `IMutableStateMeta` 是否正确创建。
- **V2 对象互操作排查**：`isDynamicObject(value)`/`getV2ObservedObject(value)` 用于确认对象在静态/动态侧的归属。
- **`@Monitor` 依赖排查**：`MonitorValueInternal.recordDependenciesForMonitorValue` 记录路径依赖，可用于检查通配符匹配。

## 相关主题

- [总览](../state-management.md)
- 静态 V2 核心（`DecoratedV2VariableBase`/`StateUpdateLoop`）：[static-v2-core](static-v2-core.md)
- [动态侧 V2 装饰器（对照参考）](v2-decorators.md)
- 跨前端互操作（`enableCompatibleObservedV2ForStatic` 完整机制）：[static-interop-bridge](static-interop-bridge.md)