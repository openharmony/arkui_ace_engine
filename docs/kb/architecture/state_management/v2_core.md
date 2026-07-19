# State Management — V2 核心逻辑 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtV2Core`

## 定位

V2 核心逻辑是 API 12+ 引入的下一代状态管理基础设施，与 V1 并存但设计不同。V2 不再使用「属性包装对象」（如 `ObservedPropertyPU`），而是直接在原生数据上安装 getter/setter，依赖与通知提取到全局 `ObserveV2` 单例。状态变量依赖记录在 `target[SYMBOL_REFS]` 和 `ObserveV2.id2targets_`；变更调度通过 `Promise.resolve().then()` 合并到 VSync，在一个 `updateDirty` 批次内统一处理。`PUV2ViewBase` 是 V1 `ViewPU` 与 V2 `ViewV2` 的共享抽象基类。V2 装饰器（`@ObservedV2`/`@Trace`/`@Computed`/`@Monitor` 等）都是纯 TS 实现，C++ 不参与 V2 观察逻辑（C++ 侧通过 `isV2_` 标志区分 V1/V2，但共用同一 `CustomNode` 宿主）。

本文档用于快速定位 V2 核心相关源码和测试入口。具体装饰器语义见「V2 装饰器」子页面。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 中心枢纽 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_change_observation.ts` | `ObserveV2` 单例 — 依赖跟踪、变更分发、`updateDirty2Optimized` 调度管线、`autoProxyObject` |
| 共享 track 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_change_observation.ts` | `trackInternal` — 被 `@Trace`/`@Local`/`@Provider` 共用，移动值到 `__ob_<prop>` 后装 getter/setter |
| 惰性 Proxy 体系 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_observed_proxy.ts` | `ObjectProxyHandler`、`ArrayProxyHandler`、`SetMapProxyHandler` — 首次读取时惰性包装 Array/Set/Map/Date |
| V2 视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_view.ts` | `ViewV2`（抽象，`@ComponentV2` 基类）— V2 dirty 更新、复用、冻结、Monitor 管理 |
| V2 装饰器定义 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts` | `ObservedV2`、`Trace`、`Local`、`Param`、`Once`、`Event`、`Provider`、`Consumer`、`Monitor`、`Computed`、`Env`、`CustomEnv` |
| `@Computed` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_computed.ts` | `ComputedV2`（`MIN_COMPUTED_ID = 0x1000000000`）— 惰性求值 + 缓存 |
| `@Monitor`/`@SyncMonitor` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_monitor.ts` | `MonitorV2`、`MonitorValueV2`、`MonitorPathHelper` — 路径遍历依赖注册 |
| `@Env` 注册表 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_env.ts` | `EnvV2` — 按 UIContext（instanceId）隔离的环境变量注册 |
| `makeObserved` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_make_observed.ts` | `RefInfo` — 将任意值包装为可观察 |
| 类装饰与 PC 工具 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorated_variables.ts` | `observedV2Internal`、`VariableUtilV2`（@Param）、`ProviderConsumerUtilV2` |
| V2 复用池 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_recycle_pool.ts` | `RecyclePoolV2` + `RecycledIdRegistry` — V2 按父节点的组件复用池 |
| 序列化编解码 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_data_coder/` | `DataCoder.stringify/parse/restoreTo`、`JSONCoder`、`Meta`（`@Type`）— 保持原型链的序列化 |
| V1/V2 共享视图基类 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/puv2_common/puv2_view_base.ts` | `PUV2ViewBase`（抽象）— `ViewPU`/`ViewV2` 共享，含 activeCount、freezeWhenInactive 继承、dump |
| GC 清理协调 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/common/weakref_pool.ts` | `WeakRefPool` — 规范化 WeakRef + `FinalizationRegistry` 驱动的依赖图 GC |
| V2 存储/持久化 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/v2_persistence.ts` | `AppStorageV2Impl`、`PersistenceV2Impl`、`StorageHelper` — 详见「存储体系」子页面 |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `trackInternal` 安装 getter/setter | `v2/v2_change_observation.ts` `trackInternal()` — 值移到 `__ob_<prop>`，getter 调 `addRef`+`autoProxyObject`，setter 调 `fireChange` |
| ID 分段路由 | `v2/v2_computed.ts`（`MIN_COMPUTED_ID`）、`v2/v2_monitor.ts`（Monitor ID 段）、`v2_persistence.ts`（`MIN_PERSISTENCE_ID`）— `fireChange` 按 ID 区间分发 |
| 惰性集合代理 | `v2/v2_change_observation.ts` `autoProxyObject()` — 首次读取包装 Array/Set/Map/Date，集合额外加 `OB_LENGTH` 依赖 |
| dirty 调度默认路径 | `v2/v2_change_observation.ts` `updateDirty2Optimized()` — 按 containerId 分组，经 `ViewStackProcessor.scheduleUpdateOnNextVSync` |
| `clearBinding` 延迟 | `v2/v2_change_observation.ts` — O(n) 操作放入 `idleTasks_`，避免阻塞渲染帧 |
| 同步更新路径 | `v2/v2_change_observation.ts` `updateDirty2()` — `applySync` 后用的同步 UI 更新 |
| ID_REFS 反向映射 | `v2/v2_decorated_variables.ts` `observedV2Internal` — `@Trace` 属性 >5 时启用反向映射加速 `clearBinding` |
| Monitor 微任务注册 | `v2/v2_computed.ts` `AsyncAddComputedV2`、`v2/v2_monitor.ts` `AsyncAddMonitorV2` — 经 `Promise.resolve().then()` 异步注册 |
| @Computed 惰性求值 | `v2/v2_computed.ts` `ComputedV2.InitRun`/`observeObjectAccess`/`fireChange`（结果 `===` 未变则不通知） |
| @Monitor 路径遍历 | `v2/v2_monitor.ts` `MonitorV2.analysisProp` — 点分路径逐层 `addRef`，路径不存在返回 `MONITOR_PATH_NOT_FOUND` |
| @Provider/@Consumer 弱引用 | `v2/v2_decorated_variables.ts` `connectConsumer2Provider` — 重定义 getter/setter 读写 Provider view，Provider GC 后 `weakView.deref()` 为 undefined 抛错 |
| @Env UIContext 隔离 | `v2/v2_env.ts` `EnvV2` — `envValues[instanceId][key]`，`registerEnv` 优先级：递归父 → UIContext 注册表 → 工厂创建 |

### API 入口

V2 装饰器的 SDK 声明位于 `interface/sdk-js` 仓（不在本仓）：

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V2 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common/stateMgmtV2.d.ts` | `@ObservedV2`/`@Trace`/`@Computed`/`@Monitor`/`@ComponentV2`/`@Local`/`@Param`/`@Once`/`@Event`/`@Provider`/`@Consumer`/`@Type` 声明 |
| V2 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/component/stateMgmt.static.d.ets` | 静态 ArkTS 侧 V2 装饰器声明 |
| StateManagement 模块 | `<OH_ROOT>/interface/sdk-js/api/arkui/@ohos.arkui.StateManagement.d.ts` | `makeObserved`、`UIUtils`、`ObservedUtil` 等 V2 相关 API |

具体装饰器语义、API 版本与错误码以 SDK 声明为准。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| V2 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v2_tests/` | `ObserveV2`、所有 V2 装饰器、`@Computed`、`@Monitor`、`@Provider`/`@Consumer`、Proxy handler 行为回归 |
| Env 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/env_tests/` | `@Env`/`@CustomEnv`、`EnvV2` 注册表、UIContext 隔离 |
| 通用测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/common_tests/` | `WeakRefPool`、`UIUtils`、共享基础 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtV2Core` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| V2 为何不需要包装对象 | 依赖/通知提取到全局 `ObserveV2`，状态变量仅需 getter/setter（`trackInternal`） |
| 深层嵌套对象如何观察 | 每层 `@Trace` getter 调 `addRef`；集合类型经 `autoProxyObject` 惰性代理 |
| `Promise.resolve().then()` 的作用 | 合并同一 microtask 内多次变更为一个 `updateDirty` 批次，`startDirty_` 防递归 |
| `clearBinding` 为何延迟 | O(n) 操作放入 `idleTasks_`，避免阻塞渲染帧 |
| V1/V2 能否混用 | `@ObservedV2` 对象不能用作 V1 `@State` 值（`checkIsSupportedValue` 拒绝）；建议同一组件树统一 |
| `updateDirty2Optimized` vs `updateDirty2` | 前者按 VSync 更新（默认），后者同步更新 UI（`applySync` 后用） |
| `@Trace` 赋相同值不触发 | setter 严格 `!==` 比较 |
| `@Computed` 在 getter 中有副作用 | 应为纯函数；`startDirty_` 防递归但不防状态不一致 |
| `@Monitor` 路径不存在 | `analysisProp` 返回 `MONITOR_PATH_NOT_FOUND` |
| `@Provider` 销毁后 `@Consumer` 访问 | `WeakRef.deref()` 为 undefined → 抛 `MISSING_PROVIDE_DEFAULT_VALUE_FOR_CONSUME_CONSUMER` |
| `@Param` 本地赋值被拒 | 无 `@Once` 时 setter 抛错，仅父组件可更新 |
| `@Env` 是否可写 | 只读，setter 抛错 |

## 调试入口

- **属性访问追踪**：`stateMgmt.setPropertyAccessTrace(true)` 输出详细 `addRef`/`fireChange` 日志。
- **ObserveV2 内部状态**：检查 `ObserveV2.getObserve()` 字段 `elmtIdsChanged_.size`、`computedPropIdsChanged_.size`、`monitorIdsChanged_.size`。
- **V2 元数据检查**：`ObserveV2.IsObservedObjectV2(obj)`、`IsProxiedObservedV2`、`IsMakeObserved`；查 `data[ObserveV2.V2_DECO_META]` 装饰器元信息，`data.__ob_<prop>` 后备存储，`data[ObserveV2.SYMBOL_REFS]` 已注册依赖。
- **日志关键字**：`ObserveV2.addRef 'X' for id N`、`ObserveV2.fireChange 'X' dependent ids: [...]`、`updateDirty2Optimized() start/end`、`updateDirtyComputedProps N`、`updateDirtyMonitors: N`、`updateUINodesSynchronously: N elmtId`、`ObjectProxyHandler get key 'X'`、`ArrayProxyHandler get key 'push'`。
- **断点建议**：`trackInternal()` → `fireChange()` → `updateDirty2Optimized()`；`@Computed` 看 `ComputedV2.InitRun`/`fireChange`；`@Monitor` 看 `MonitorV2.bindRun`。

## 相关主题

- 总览：`docs/kb/architecture/state_management.md`
- V1 对应核心：`docs/kb/architecture/state_management/v1_core.md`
- V2 装饰器具体语义：`docs/kb/architecture/state_management/v2_decorators.md`
- 基础设施（`WeakRefPool`、`UINodeRegisterProxy`）：`docs/kb/architecture/state_management/infrastructure.md`
- 存储体系（`AppStorageV2`/`PersistenceV2`）：`docs/kb/architecture/state_management/storage.md`
- 自定义组件机制（`ViewV2`）：`docs/kb/architecture/state_management/custom_component.md`
- Interop 桥接（V2 builder/storage 跨前端）：`docs/kb/architecture/state_management/interop_bridge.md`
