# Static State Management — V2 核心逻辑 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticV2Core`

## 定位

静态前端（ArkTS 1.2 / arkoala）的 V2 状态管理核心。V2 装饰变量（`@Local`/`@Param`/`@Provider`/`@Consumer`/`@Monitor`/`@Computed` 等）的运行时实现基类与调度机制。与动态侧 V2 的「getter/setter + 全局 `ObserveV2` 单例 + `trackInternal`」不同，静态侧 V2 使用「`DecoratedV2VariableBase` 装饰变量 + `StateUpdateLoop` 延迟合并 + `autoProxyObject` 自动代理」范式。

本域对应 FuncID `07-02-11`（静态V2组件内状态管理）。注意：静态侧 **不实现** V2 类级装饰器（`@ObservedV2`/`@Trace`/`@Type`）的运行时——这些通过 UIPlugin 转换为 `MutableStateMeta`，归 `07-02-12`（静态V2数据对象）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| V2 装饰变量基类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorBase.ts` | `DecoratedV2VariableBase<T>` — 所有 V2 装饰变量实现的基类 |
| 延迟更新队列 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/stateUpdateLoop.ts` | `StateUpdateLoop` — 一次性延迟任务队列，`@Param.update`/`@ObjectLink.update` 合并到下次执行 |
| 自动代理工具 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/uiUtilsImpl.ts` | `UIUtilsImpl.autoProxyObject` — `@Local.set` 自动为非动态对象安装观测代理 |
| 观测单例 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/observeSingleton.ts` | `ObserveSingleton` — 渲染期切换 `RenderingComponentV2`/`RenderingComputed` |
| Backing Value | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/base/backingValue.ts` | `DecoratorBackingValue<T> implements IBackingValue<T>` — 持有值，`get(addRef)`/`set(newValue)` 同值短路 |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| V2 装饰变量延迟更新 | `base/stateUpdateLoop.ts` `StateUpdateLoop.add` — `@Param.update(newValue)` 入队，下次微任务执行 |
| `@Local` 自动代理 | `decoratorImpl/decoratorLocal.ts` `set()` — 调 `uiUtils.autoProxyObject` 为普通对象安装 Proxy |
| `@Computed` 惰性求值 | `decoratorImpl/decoratorComputed.ts` `runFunctionAndObserve()` — 切换 `ObserveSingleton.renderingComponent` 为 `RenderingComputed` 收集依赖 |
| `@Computed` 反向绑定清理 | `decoratorImpl/decoratorComputed.ts` `clearReverseBindings()` — 计算属性依赖变化时清理旧 binding |
| `@Monitor` 路径解析 | `decoratorImpl/decoratorMonitor.ts` `recordDependenciesForMonitorValue` — 路径通配符（`enableWildcard`）与依赖记录 |
| `@Monitor` 同步/异步分发 | `decoratorImpl/decoratorMonitor.ts` `MIN_SYNC_MONITOR_ID`/`isSynchronous` 构造参数 — `@SyncMonitor` 走同步路径 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V2 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@Local`/`@Param`/`@Once`/`@Event`/`@Provider`/`@Consumer`/`@Monitor`/`@SyncMonitor`/`@Computed` + 全部 `IDecoratedV2Variable` 接口族 |
| UIUtils 工具 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/utils.static.d.ets` | `UIUtils.makeObserved`/`makeBinding`/`addMonitor`/`clearMonitor`/`canBeObserved`/`getLifecycle` |
| Barrel 总入口 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.stateManagement.static.d.ets` | 重导出全部子模块 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 装饰变量测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/` | V2 装饰变量行为回归 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticV2Core` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-11` | `specs/07-frontend/02-state-management/11-static-v2-component-state/` | active（Feat-01~04 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@Param` 更新不触发重渲染 | `stateUpdateLoop.ts` — `update(newValue)` 入队后是否在下次微任务执行；检查 `__getCanUpdateStateVars__Internal()` 是否允许更新 |
| `@Local` 设置普通对象后不观测 | `decoratorLocal.ts` `set()` — 是否调用了 `autoProxyObject`；确认对象未被识别为已观测 |
| `@Computed` 缓存不失效 | `decoratorComputed.ts` `clearReverseBindings` — 依赖项变化时是否触发了反向 binding 清理 |
| `@Monitor` 通配符路径不匹配 | `decoratorMonitor.ts` `enableWildcard` — 仅路径末尾支持通配符 |
| `@SyncMonitor` 与 `@Monitor` 行为差异 | `decoratorMonitor.ts` `isSynchronous` 构造参数 — `@SyncMonitor` 走同步回调路径 |

## 调试入口

- **日志关键字**：`DecoratedV2VariableBase`、`StateUpdateLoop`、`autoProxyObject`、`ObserveSingleton`、`RenderingComputed`。
- **延迟更新排查**：`StateUpdateLoop` 队列状态，确认 `@Param.update` 是否正确入队/出队。
- **`@Computed` 依赖排查**：`ObserveSingleton.renderingComponent` 在 `RenderingComputed` 态时收集依赖，断点 `runFunctionAndObserve`。
- **断点建议**：`DecoratedV2VariableBase.set(newValue)` → `DecoratorBackingValue.set` → `fireChange` → `ObserveSingleton` 通知。

## 相关主题

- [总览](../state-management.md)
- [静态 V2 装饰器具体语义](static-v2-decorators.md)
- 静态 V2 数据对象（`@ObservedV2`/`@Trace` UIPlugin 转换）：[static-v2-decorators](static-v2-decorators.md)（数据对象段）
- [动态侧 V2 核心（对照参考）](v2-core.md)
- [静态 V1 核心](static-v1-core.md)