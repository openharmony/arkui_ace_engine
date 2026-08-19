# Static State Management — V1 装饰器与数据对象 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticV1Decorators`

## 定位

静态前端（ArkTS 1.2 / arkoala）V1 装饰器的运行时实现。每个 V1 装饰器在编译期由 `STATE_MGMT_FACTORY.makeXxx` 创建对应的 `IDecoratedV1Variable<T>` 实现类，与动态侧（`ObservedPropertyPU`/`SynchedPropertyXxxPU` 属性包装对象）不同，静态侧使用「装饰变量 + 元数据」范式。

本域覆盖 FuncID `07-02-08`（静态V1组件内 — 装饰器部分）和 `07-02-09`（静态V1数据对象 — `@Observed`/`@Track`）。核心机制（`DecoratedV1VariableBase`/工厂/`ObserveSingleton`）见「静态 V1 核心」子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 装饰变量实现目录 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/` | 所有 V1/V2 装饰变量运行时类 |
| `@State` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorState.ts` | `StateDecoratedVariable<T>` — `get`/`set`/`resetOnReuse`/`mkLink`/`mkProp`/`fireChange`/`setProxyValue` |
| `@Prop` 实现（深拷贝单向） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorProp.ts` | `PropDecoratedVariable<T>` — `propDeepCopy` 深拷贝，`__localValue`/`__sourceValue` 分离，`update(newValue)` 父同步 |
| `@PropRef` 实现（可变引用） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorPropRef.ts` | `PropRefDecoratedVariable<T>` — 可变引用，修改对父可见（建议深拷贝） |
| `@Link` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorLink.ts` | `LinkDecoratedVariable<T>` — 通过 `sourceGet_`/`sourceSet_` 读写穿透；工厂 `makeLinkOnState` 按 10 种源装饰器类型分发创建 |
| `@Provide` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorProvide.ts` | `ProvideDecoratedVariable<T>` — `__addProvide__Internal` 注册，`allowOverride_` 覆盖控制 |
| `@Consume` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorConsume.ts` | `ConsumeDecoratedVariable<T>` — `__findProvide__Internal` 查找，`ConsumeOptions.defaultValue` 回退，`resetOnReuse` 复用重绑 |
| `@ObjectLink` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorObjectLink.ts` | `ObjectLinkDecoratedVariable<T>` — 不可变从父接收，单层观测，`update()`/`resetOnReuse()` |
| `@Watch` 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorWatch.ts` | `SubscribedWatches`/`WatchFunc` — id 跟踪订阅者，`FinalizationRegistry` 自动清理，`WatchFunc.watchId2WatchFunc` 静态映射 |
| 存储联动装饰器 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorStorageLink.ts`、`decoratorStoragePropRef.ts`、`decoratorStorageProp.ts` | `@StorageLink`/`@LocalStorageLink`/`@StoragePropRef`/`@LocalStoragePropRef`/`@StorageProp` |
| `@Observed` Proxy 实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/tools/arkts/observeInterfaceProxy.ts` | `InterfaceProxyHandler implements reflect.InvocationHandler, IObservedObject, ISubscribedWatches, JsonReplacer` — ES Proxy 拦截器，arkoala 侧 `@Observed` 等价物 |
| 内置观测容器 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/observeWrappedArray.ts`、`observeWrappedMap.ts`、`observeWrappedSet.ts`、`observeWrappedDate.ts` | `WrappedArray`/`WrappedMap`/`WrappedSet`/`WrappedDate` — 完整方法拦截 |
| UIUtils observed 工具 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/uiUtilsImpl.ts` | `UIUtilsImpl` — `makeV1Observed`/`autoProxyObject`/`makeObservedArray`/`makeObservedDate`/`makeObservedMap`/`makeObservedSet` |
| 用户面 observed 容器类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/utils.ts` | `ObservedArray<T>`/`ObservedSet<K>`/`ObservedMap<K,V>`/`ObservedDate` — 用户侧类型（`Wrapped*` 为内部对端） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `@Link` 多源分发 | `base/stateMgmtFactory.ts` `makeLinkOnState` — 工厂按源类型（`@State`/`@Prop`/`@Link`/`@Provide`/`@Consume`/`@ObjectLink`/`@StorageLink`/`@LocalStorageLink`/`@StoragePropRef`/`@LocalStoragePropRef` 共 10 种）分发，为 `LinkDecoratedVariable` 构造对应的 `sourceGet_`/`sourceSet_` 回调 |
| `@Consume` 回退默认值 | `decoratorImpl/decoratorConsume.ts` — 找不到 `@Provide` 时用 `ConsumeOptions.defaultValue` 构造 fake Provide |
| `@Consume` 复用重绑 | `decoratorImpl/decoratorConsume.ts` `resetOnReuse(provideAliasName, watchFunc?, consumeOptions?)` — 跨父组件复用时重新查找 provider，旧 source `fireChange` 失效 |
| `@Watch` GC 清理 | `decoratorImpl/decoratorWatch.ts` — `FinalizationRegistry` 监控订阅者生命周期，自动清理 `watchId2WatchFunc` 映射 |
| `@Observed` 非类装饰器 | `tools/arkts/observeInterfaceProxy.ts` — arkoala 不实现 `@Observed` 类装饰器函数，而是通过 `InterfaceProxyHandler` 在对象构造时安装 Proxy |
| `@Track` 属性级元数据 | `tools/arkts/observeInterfaceProxy.ts` — `allowDeep_`/`isAPI_` 设置时为每个标记属性创建 `IMutableStateMeta` |
| `@StorageProp` 实现局限 | `decoratorImpl/decoratorStorageProp.ts` — Stub（36 行），只存 `propertyNameInAppStorage_`，无 `get`/`set` 覆写；工厂无 `makeStorageProp`（只读 `@StorageProp` 经 propRef 路径提供行为） |
| `autoProxyObject` | `base/uiUtilsImpl.ts` — `@Local` 的 `set` 自动为非动态对象安装 Proxy |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@State`/`@PropRef`/`@Link`/`@Observed`/`@Track`/`@ObjectLink`/`@Provide`/`@Consume`/`@Watch`/`@Require` + `@StorageLink`/`@StoragePropRef`/`@LocalStorageLink`/`@LocalStoragePropRef` + 全部 `IDecoratedV1Variable` 接口族 |
| 内置 observed 容器 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/utils.static.d.ets` | `ObservedArray`/`ObservedMap`/`ObservedSet`/`ObservedDate`（`@since 26.0.0 static`） |
| Barrel 总入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 重导出全部子模块 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 装饰变量测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/` 同目录 | 各装饰变量行为回归 |
| Proxy 测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/tools/arkts/` | `InterfaceProxyHandler`/`Wrapped*` 行为 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticV1Decorators` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-08` | `specs/07-frontend/02-state-management/08-static-v1-component-state/` | active（Feat-02~06 待补充） |
| `07-02-09` | `specs/07-frontend/02-state-management/09-static-v1-data-object-state/` | active（Feat-01~02 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@Link` 无法绑定到某源类型 | `base/stateMgmtFactory.ts` `makeLinkOnState` 分发表 — 仅支持 10 种源装饰器，不支持的类型在工厂分发时报错 |
| `@Consume` 找不到上游 `@Provide` | `decoratorConsume.ts` `__findProvide__Internal` — 检查祖先链是否注册了对应 alias 的 `@Provide` |
| `@Watch` 回调内存泄漏 | `decoratorWatch.ts` `FinalizationRegistry` — 确认订阅者 GC 后是否触发自动清理 |
| `@Observed` 对象修改不触发更新 | `observeInterfaceProxy.ts` — 确认对象是否经 `InterfaceProxyHandler` 包装；arkoala 侧 `@Observed` 是 Proxy 安装而非类装饰器 |
| `@Track` 属性级追踪不生效 | `observeInterfaceProxy.ts` `allowDeep_`/`isAPI_` — 仅在深度模式或 API 模式下为标记属性创建元数据 |
| `@StorageProp` 只读行为缺失 | `decoratorStorageProp.ts` — Stub 实现，行为经 `@StoragePropRef` 路径提供 |

## 调试入口

- **日志关键字**：`StateDecoratedVariable`、`LinkDecoratedVariable`、`ProvideDecoratedVariable`、`ConsumeDecoratedVariable`、`InterfaceProxyHandler`、`WrappedArray`。
- **Proxy 排查**：断点 `InterfaceProxyHandler` 的 `invoke` 方法，确认属性读写是否触发 `addRef`/`fireChange`。
- **类型检查**：`stateMgmtTool.ts` `isIObservedObject(obj)`/`isIStateDecoratedVariable(var)` 用于运行时确认装饰变量实际类型。
- **`@Watch` 排查**：`WatchFunc.watchId2WatchFunc` 静态映射保留所有 watchId → 回调的映射，可用于检查注册与清理。

## 相关主题

- 总览：`docs/kb/frontend/state-management.md`
- 静态 V1 核心机制（工厂/ObserveSingleton/MutableStateMeta）：`docs/kb/frontend/state_management/static-v1-core.md`
- 动态侧 V1 装饰器（对照参考）：`docs/kb/frontend/state_management/v1-decorators.md`
- [静态存储体系（存储联动装饰器行为）：`docs/kb/frontend/state_management/static-storage.md`](static-storage.md)
- 跨前端互操作：`docs/kb/frontend/state_management/static-interop-bridge.md`