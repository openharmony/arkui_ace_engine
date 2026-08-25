# Static State Management — V1 核心逻辑 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticV1Core`

## 定位

静态前端（ArkTS 1.2 / arkoala / Panda VM，`libarkts_frontend.z.so`）的 V1 状态管理核心。与动态侧（`declarative_frontend/state_mgmt`）的「属性包装对象 + elmtId 依赖追踪」范式不同，静态侧采用「装饰变量（Decorated Variable）+ `IMutableStateMeta` per-property 元数据」范式：每个 V1 装饰器（`@State`/`@Prop`/`@Link` 等）在编译期通过 `STATE_MGMT_FACTORY.makeXxx` 工厂方法创建对应的 `IDecoratedV1Variable<T>` 实现类，运行时通过 `ObserveSingleton` 全局单例协调渲染期依赖收集与变更通知。

本域对应 FuncID `07-02-08`（静态V1组件内状态管理）。具体装饰器语义见「静态 V1 装饰器」子页面，跨前端互操作见「静态 Interop 桥接」子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| L0 源码根（规范实现） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/` | ES/ARKTS 预处理源码，所有装饰变量类、工厂、存储、观测元系统的规范实现 |
| L1 OHOS 适配 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/` | TS 镜像，与 L0 文件名 1:1 对应，供 TS 侧 host 工具使用 |
| 装饰变量基类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorBase.ts` | `DecoratedV1VariableBase<T>` — 所有 V1 装饰变量实现的基类 |
| 工厂实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/stateMgmtFactory.ts` | `__StateMgmtFactoryImpl implements IStateMgmtFactory` — `STATE_MGMT_FACTORY` 单例，`makeLink` 按 11 种源类型分发 |
| 工厂内部辅助 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/factoryInternal.ts` | `FactoryInternalImpl` — `mkDecoratorValue`/`mkInteropDecoratorValue`/`mkMutableStateMeta` |
| 观测单例 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/observeSingleton.ts` | `ObserveSingleton implements IObserve` — `OBSERVE` 单例，`renderingComponent`/`renderingId` 协调渲染期依赖 |
| 属性元数据 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/mutableStateMeta.ts` | `MutableStateMeta`/`MutableKeyedStateMeta` — `addRef`/`fireChange` per-property 通道 |
| 公共入口注册 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/index.ts` | 重导出 `stateUpdateLoop`、所有装饰变量、存储类、DFX 工具 |
| DFX 工具 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/tools/stateMgmtDFX.ts` | `StateMgmtConsole`/`StateMgmtDFX`/`ObservedObjectRegistry`/`ObservedType` 枚举 |
| 类型判断工具 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/tools/arkts/stateMgmtTool.ts` | `StateMgmtTool` 运行时类型收窄（`isIObservedObject`/`isIStateDecoratedVariable` 等） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| 工厂分发入口 | `base/stateMgmtFactory.ts` `makeLink` — 按源类型（State/Prop/PropRef/Link/Provide/Consume/ObjectLink/StorageLink/LocalStorageLink/StoragePropRef/LocalStoragePropRef）分发到 11 个 typed helper |
| 渲染期依赖记录 | `base/observeSingleton.ts` `renderingComponent`/`renderingId` — 渲染期 `get()` 调用 `addRef` 记录依赖 |
| 变更通知 | `base/mutableStateMeta.ts` `fireChange()` — 触发所有 `bindingRefs_` 中注册的 binding 刷新 |
| Keyed 批量变更 | `base/mutableStateMeta.ts` `MutableKeyedStateMeta.fireChangeBatch` — Array/Map/Set 单次多 key 变更扇出一次 |
| 延迟更新队列 | `base/stateUpdateLoop.ts` `StateUpdateLoop` — `@Param.update`/`@ObjectLink.update` 的延迟合并执行 |
| 渲染态切换 | `base/observeSingleton.ts` `RenderingComponentV1`/`RenderingComponentV2`/`RenderingComputed` 常量 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V1 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@State`/`@PropRef`/`@Link`/`@Observed`/`@Track`/`@ObjectLink`/`@Provide`/`@Consume`/`@Watch`/`@Require` 装饰器声明 + `IStateMgmtFactory` 接口 + `STATE_MGMT_FACTORY`/`OBSERVE` 常量 |
| Barrel 总入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 重导出 `decorator`/`remember`/`storage/*`/`utils` 全部子模块 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 单元测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/` 下同目录测试文件 | 装饰变量行为回归 |
| Mock 互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/mock/` | `interop_component_mock.ts`/`interopStorageV2.ts` 测试桩 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticV1Core` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-08` | `specs/07-frontend/02-state-management/08-static-v1-component-state/` | active（Feat-01 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 工厂创建的装饰变量类型不对 | `stateMgmtFactory.ts` `makeLink` 分发表 — 按源装饰器类型（State/Prop/Provide 等）分发到不同 typed helper |
| `fireChange` 未触发 UI 刷新 | `mutableStateMeta.ts` `bindingRefs_` 是否在渲染期通过 `addRef` 注册了依赖 |
| Array/Map/Set 多次变更扇出过多 | `MutableKeyedStateMeta.fireChangeBatch` — 单批多 key 变更只扇出一次 |
| 渲染期外读取状态不收集依赖 | `observeSingleton.ts` `renderingComponent` 在非渲染期为 `-1`，`shouldAddRef` 返回 false |
| 装饰变量复用后状态残留 | 各装饰变量类的 `resetOnReuse(newValue)` 方法（`@since 26.1.0`） |

## 调试入口

- **日志关键字**（统一走 `StateMgmtConsole`）：`ObserveSingleton`、`fireChange`、`addRef`、`STATE_MGMT_FACTORY`、`makeLink`。
- **DFX 工具**：`stateMgmtDFX.ts` 中 `ObservedObjectRegistry` 跟踪所有被观测对象，`ObservedType` 枚举区分 `NON`/`OBSERVED`/`TRACK`/`TRACE`/`BUILTIN_V1`/`BUILTIN_V2`/`BUILTIN_MAKEOBSERVED`/`INTERFACE_V1`/`INTERFACE_MAKEOBSERVED`。
- **类型检查**：`stateMgmtTool.ts` 提供 `isIObservedObject`/`isIStateDecoratedVariable` 等运行时类型守卫，用于调试装饰变量实际类型。
- **断点建议**：`ObserveSingleton.shouldAddRef` → `MutableStateMeta.addRef` → 渲染期 `get()` → 变更时 `MutableStateMeta.fireChange` → binding 刷新。

## 相关主题

- [总览](../state-management.md)
- [静态 V1 装饰器具体语义](static-v1-decorators.md)
- [动态侧 V1 核心（对照参考）](v1-core.md)
- [静态 V2 核心](static-v2-core.md)
- [跨前端互操作](static-interop-bridge.md)
- [静态存储体系](static-storage.md)