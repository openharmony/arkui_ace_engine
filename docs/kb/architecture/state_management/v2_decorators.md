# State Management — V2 装饰器 Context

> 文档版本：v1.0
> 更新时间：2026-07-13
> 来源：`docs/context_registry.json` 主题 `StateMgmtV2Decorators`

## 定位

V2 装饰器是 API 12+ 的下一代状态管理 API，全部定义在 `v2/v2_decorators.ts`，核心机制委托给 `trackInternal`（`v2/v2_change_observation.ts`）和全局 `ObserveV2` 单例。与 V1 不同，V2 不创建属性包装对象，而是在原生数据上装 getter/setter。本页覆盖 14 个 V2 装饰器：类装饰器 `@ObservedV2`（可观察数据模型）、`@ComponentV2`（V2 自定义组件，见「自定义组件机制」子页面）；属性装饰器 `@Trace`（可观察属性）、`@Computed`（只读计算属性）、`@Monitor`/`@SyncMonitor`（路径感知变化监听）、`@Local`（组件私有，V2 的 `@State`）、`@Param`/`@Once`（父→子单向输入 + 仅首次同步修饰）、`@Event`（子→父回调通道）、`@Provider`/`@Consumer`（V2 跨层传递）、`@Type`（PersistenceV2 序列化类型标记）、`@Env`/`@CustomEnv`（系统/自定义环境注入）。V2 装饰器共享 V2 核心逻辑（`ObserveV2`、ID 分段、惰性 Proxy），核心机制见「V2 核心逻辑」子页面。

本文档用于快速定位各装饰器实现源码和测试入口。

## 快速路由

### 装饰器实现映射

| 装饰器 | 语义 | 实现 TS 类 / 文件 |
|--------|------|-------------------|
| `@ObservedV2` | 类装饰器，转为可观察数据模型 | `observedV2Internal`（`v2/v2_decorated_variables.ts`）+ `ObservedV2`（`v2/v2_decorators.ts`） |
| `@Trace` | `@ObservedV2` 类中的可观察属性 | `trackInternal`（`v2/v2_change_observation.ts`）+ `Trace`（`v2/v2_decorators.ts`） |
| `@Computed` | 只读计算属性（getter 求值 + 缓存） | `ComputedV2`（`v2/v2_computed.ts`，`MIN_COMPUTED_ID = 0x1000000000`）+ `Computed`（`v2/v2_decorators.ts`） |
| `@Monitor` | 异步路径感知变化监听（IMonitor before/now/path） | `MonitorV2` + `MonitorValueV2`（`v2/v2_monitor.ts`）+ `Monitor`（`v2/v2_decorators.ts`） |
| `@SyncMonitor` | 同步变化监听（在 fireChange 调用栈内执行） | `MonitorV2`（`MIN_SYNC_MONITOR_OR_SYNC_API_ID`）+ `SyncMonitor`（`v2/v2_decorators.ts`） |
| `@Local` | 组件私有状态（V2 的 `@State`） | `Local`（`v2/v2_decorators.ts`）→ `trackInternal` |
| `@Param` | 父→子单向输入 | `Param`（`v2/v2_decorators.ts`）+ `VariableUtilV2.updateParam`（`v2/v2_decorated_variables.ts`） |
| `@Once` | 修饰 `@Param` 仅首次同步 | `Once`（`v2/v2_decorators.ts`）— 设置 `deco2='@Once'` 元信息 |
| `@Event` | 子→父回调通道 | `Event`（`v2/v2_decorators.ts`）— 无 `trackInternal`，默认 `() => {}` |
| `@Provider` | 祖先提供（V2 的 `@Provide`） | `Provider`（`v2/v2_decorators.ts`）→ `trackInternal` + `ProviderConsumerUtilV2` |
| `@Consumer` | 后代消费（V2 的 `@Consume`） | `Consumer`（`v2/v2_decorators.ts`）+ `connectConsumer2Provider`（`v2/v2_decorated_variables.ts`） |
| `@Type` | PersistenceV2 序列化类型标记 | `Meta` 类（`v2/v2_data_coder/json_coder.ts`）+ `__Type__` |
| `@Env` | 系统环境注入（只读） | `Env`（`v2/v2_decorators.ts`）+ `EnvV2`（`v2/v2_env.ts`） |
| `@CustomEnv` | 自定义环境注入（首次允许赋值） | `CustomEnv`（`v2/v2_decorators.ts`） |

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 全部装饰器定义 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorators.ts` | `ObservedV2`/`Trace`/`Local`/`Param`/`Once`/`Event`/`Provider`/`Consumer`/`Monitor`/`SyncMonitor`/`Computed`/`Env`/`CustomEnv` |
| 共享 track 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_change_observation.ts` | `ObserveV2` 单例、`trackInternal`、`autoProxyObject`、`updateDirty2Optimized` |
| 类装饰与 PC 工具 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_decorated_variables.ts` | `observedV2Internal`、`VariableUtilV2`（@Param）、`ProviderConsumerUtilV2`、`connectConsumer2Provider` |
| `@Computed` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_computed.ts` | `ComputedV2`（`InitRun`/`observeObjectAccess`/`fireChange`） |
| `@Monitor` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_monitor.ts` | `MonitorV2`、`MonitorValueV2`、`MonitorPathHelper`（`analysisProp`/`bindRun`/`recordDependenciesForProp`） |
| `@Env` 注册表 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_env.ts` | `EnvV2`（按 instanceId 隔离）、`isDirectQuerySystemEnvKey`、`registerEnv`、`registerSimpleTypeMonitorFunc` |
| `@Type` 实现 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_data_coder/json_coder.ts` | `Meta`（WeakMap 基类元信息，原型链继承）、`disabled`/`alias`/`factory` |
| 序列化编解码 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_data_coder/data_coder.ts` | `DataCoder.stringify/parse/restoreTo` |
| `makeObserved` | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/v2/v2_make_observed.ts` | `RefInfo` |
| UI 工具 | `frameworks/bridge/declarative_frontend/state_mgmt/src/lib/sdk/ui_utils.ts` | `UIUtils.makeObserved`/`addMonitor`/`clearMonitor`/`applySync`/`flushUpdates` |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `observedV2Internal` 构造 5 步 | `v2_decorated_variables.ts` `observedV2Internal` — V1 `@Track` 冲突检查、`@Trace` 计数、ID_REFS（>5 属性）、`AsyncAddComputedV2`/`AsyncAddMonitorV2`（microtask）、`WeakRefPool.asyncRegisterToFinalizationRegistry` |
| `@Computed` 惰性求值 + 缓存 | `v2_computed.ts` `InitRun`（重定义属性）、`observeObjectAccess`（在 `startRecordDependencies` 下跑 getter）、缓存到 `___comp_cached_<prop>`；`fireChange` 仅结果 `===` 变化才通知 |
| `@Computed` 不支持 setter | `InitRun` setter 抛错 |
| `@Monitor` 路径遍历 | `v2_monitor.ts` `analysisProp` — 点分路径逐层 `addRef`，每层注册 MonitorV2 ID；路径不存在返回 `MONITOR_PATH_NOT_FOUND` |
| 通配符 `.*` | 创建两个 `MonitorValueV2`（Last Sure + Wildcard），父对象替换时重记录依赖 |
| `@Param` setter 阻止赋值 | 无 `@Once` 时 setter 抛错；`VariableUtilV2.updateParam` 跳过 `deco2 === '@Once'` |
| `@Once` 不能单独使用 | 需 `@Param` 先注册 `V2_DECO_META` |
| `@Provider`/`@Consumer` 弱引用 | `connectConsumer2Provider` 重定义 getter/setter 读写 Provider view；Provider GC → `weakView.deref()` undefined → 抛错 |
| `@Consumer` 找不到 Provider | 使用本地初始值 `defineConsumerWithoutProvider` |
| `@Env` UIContext 隔离 | `EnvV2` `envValues[instanceId][key]`；`registerEnv` 优先级：递归父 → UIContext 注册表 → 工厂创建 |
| `@Env` 直接查询 key | `system.arkui.layout.direction`、`system.arkui.fontScale` |
| `@Env` 只读 | setter 抛错 |
| `@CustomEnv` 首次赋值 | `isCustomEnvInit` false 时允许，存为本地默认 |
| `@Type` 元信息继承 | `Meta` WeakMap on prototype，原型链继承；嵌套对象缺 factory 抛 `PERSISTENCE_V2_LACK_TYPE` |
| `@Event` 无追踪 | 无 `trackInternal`，默认 `() => {}`（`??=`） |
| `@Trace` 赋相同值不触发 | setter 严格 `!==` 比较 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| V2 装饰器（Dynamic） | `<OH_ROOT>/interface/sdk-js/api/@internal/component/ets/common/stateMgmtV2.d.ts` | 全部 V2 装饰器声明，按装饰器名检索 |
| V2 装饰器（Static） | `<OH_ROOT>/interface/sdk-js/api/arkui/component/stateMgmt.static.d.ets` | 静态 ArkTS 侧 V2 装饰器声明 |
| StateManagement 模块 | `<OH_ROOT>/interface/sdk-js/api/arkui/@ohos.arkui.StateManagement.d.ts` | `makeObserved`、`UIUtils`、`SystemEnvKey`、`CustomEnvKey` |

各装饰器允许的变量类型、是否可写、API 版本、IMonitor 返回结构、错误码以 SDK 声明为准。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| V2 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/v2_tests/` | 全部 V2 装饰器、`@Computed`、`@Monitor`、`@Provider`/`@Consumer`、`@Param`/`@Once`、`@Type` 行为回归 |
| Env 测试套 | `frameworks/bridge/declarative_frontend/state_mgmt/test/unittest/entry/src/main/env_tests/` | `@Env`/`@CustomEnv`、`EnvV2` 注册表、UIContext 隔离 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtV2Decorators` |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@ObservedV2` 类中用 V1 `@Track` | 抛错（V1/V2 装饰器不能混用） |
| `@Trace` 不在 `@ObservedV2` 中 | 缺 GC 清理、`@Computed`/`@Monitor` 构造、ID_REFS 优化 |
| `@Trace` 赋相同值不触发 | setter 严格 `!==` 比较 |
| `@Computed` 不支持 setter | `InitRun` setter 抛错，计算属性只读 |
| `@Computed` 在 getter 中有副作用 | 应为纯函数；`startDirty_` 防递归但不防状态不一致 |
| `@Monitor` vs V1 `@Watch` | 前者深层路径 + IMonitor（before/now/path），后者仅变量名 |
| `@SyncMonitor` vs `@Monitor` | 前者同步立即执行（数据校验），后者异步 VSync |
| `@Monitor` 路径不存在 | `analysisProp` 返回 `MONITOR_PATH_NOT_FOUND` |
| `@Param` 本地赋值被拒 | 无 `@Once` 时 setter 抛错 |
| `@Once` 不能单独使用 | 需 `@Param` 先注册 |
| `@Consumer` 找不到 `@Provider` | 使用本地初始值 `defineConsumerWithoutProvider` |
| `@Provider` 销毁后 `@Consumer` 访问 | `WeakRef.deref()` undefined → 抛 `MISSING_PROVIDE_DEFAULT_VALUE_FOR_CONSUME_CONSUMER` |
| `@Type` 缺失反序列化失败 | 嵌套对象 null 时抛 `PERSISTENCE_V2_LACK_TYPE` |
| `@Env` 是否可写 | 只读，setter 抛错 |
| `@CustomEnv` 首次赋值规则 | `isCustomEnvInit` false 时允许首次赋值 |

## 调试入口

- **属性访问追踪**：`stateMgmt.setPropertyAccessTrace(true)` 输出详细 `addRef`/`fireChange` 日志。
- **元数据检查**：`data[ObserveV2.V2_DECO_META]`（装饰器元信息）、`data.__ob_<prop>`（后备存储）、`data[ObserveV2.SYMBOL_REFS]`（已注册依赖）。
- **对象检测**：`ObserveV2.IsObservedObjectV2(obj)`、`IsProxiedObservedV2`、`IsMakeObserved`、`UIUtils.canBeObserved(obj)`。
- **日志关键字**：`ObserveV2.addRef 'X' for id N`、`fireChange 'X' dependent ids`、`ObjectProxyHandler get key 'X'`、`ArrayProxyHandler get key 'push'`、`Miss @Type in object defined`、`Miss @Type in array defined`。
- **断点建议**：`trackInternal()` → `fireChange()` → `updateDirty2Optimized()`；`@Computed` 看 `ComputedV2.InitRun`/`fireChange`；`@Monitor` 看 `MonitorV2.analysisProp`/`bindRun`；`@Provider`/`@Consumer` 看 `connectConsumer2Provider`。

## 相关主题

- 总览：`docs/kb/architecture/state_management.md`
- V2 核心逻辑（`ObserveV2`、ID 分段、惰性 Proxy、调度）：`docs/kb/architecture/state_management/v2_core.md`
- V1 装饰器（V2 的上一代对应）：`docs/kb/architecture/state_management/v1_decorators.md`
- 存储体系（`@Type`/PersistenceV2/AppStorageV2）：`docs/kb/architecture/state_management/storage.md`
- 自定义组件机制（`@ComponentV2`/`ViewV2`）：`docs/kb/architecture/state_management/custom_component.md`
- 基础设施（`UIUtils`/`WeakRefPool`）：`docs/kb/architecture/state_management/infrastructure.md`
