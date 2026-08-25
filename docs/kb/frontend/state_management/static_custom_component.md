# Static State Management — 自定义组件状态相关 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticCustomComponent`

## 定位

静态前端（ArkTS 1.2 / arkoala）下 `@Component`/`@ComponentV2` 自定义组件的状态相关行为：静态前端自定义组件的创建与状态变量初始化、`build` 渲染入口与 `_invokeImpl` 静态工厂入口、`aboutToAppear`/`aboutToDisappear`/`aboutToReuse` 等生命周期回调中状态管理的接入、`@ReusableV2`/`@Reusable` 静态侧复用机制的状态恢复、静态前端 Builder 与状态变量的绑定。

自定义组件通用机制（声明、生命周期、复用、冻结、测量布局）归 `07-03-01~05`；本域聚焦静态前端下自定义组件与状态管理相关的差异与适配。对应 FuncID `07-03-07`（静态自定义组件状态相关）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 自定义组件基类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/customComponent.ets` | `BaseCustomComponent`/`CustomComponentV2 extends BaseCustomComponent` — `@ComponentV2` 标记基类，`_invokeImpl` memo 入口；无原生 V2 观测（仅标记） |
| 生命周期回调 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/customComponent.ets` | `aboutToAppear`/`aboutToDisappear`/`aboutToReuse`/`aboutToRecycle`/`onAttach`/`onDetach` 等回调接入 |
| 复用池装饰变量 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorGlobalReusePool.ts` | `GlobalReusePoolDecoratedVariable implements IGlobalReusePoolVariable` — 框架生成的 `__backing_reusePool` 字段实现 |
| 复用池实现 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/tools/globalReusePool.ts` | `GlobalReusePool`/`GlobalReusePoolRegistry`/`ReusableInfo` — 实际回收池，含 `preRender` 预渲染 |
| Builder 参数代理 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ets` `registerMakeBuilderParameterStaticProxy` | Builder 参数在静态侧的状态变量绑定代理 |
| 组件生命周期 SDK 类型 | `<OH_ROOT>/interface/sdk-js/api/arkui/component/customComponent.static.d.ets` | `CustomComponentLifecycle` 接口（`UIUtils.getLifecycle()` 返回类型） |
| 复用池 SDK 类型 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/utils.static.d.ets` | `IReusePool`（`getReusableInfo`/`preRender`）/`IReusableInfo`（`count`/`maxCount`/`reuseId`）/`CustomComponentContext`（`getReusePool`/`registerActiveAndInactiveCallback`） |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| `@ComponentV2` 仅是标记 | `component/customComponent.ets` — `CustomComponentV2 extends BaseCustomComponent`，无 V2 观测追踪；状态观测由各 `@Local`/`@Param`/`@Computed` 装饰变量独立安装 |
| 复用池字段生成 | `decoratorImpl/decoratorGlobalReusePool.ts` — 框架在 `@Component`/`@ComponentV2` 上生成 `__backing_reusePool` 字段，由 `makeGlobalReusePool(reusePool, poolAccepts, owningView)` 工厂创建 |
| `preRender` 预渲染 | `tools/globalReusePool.ts` `GlobalReusePool.preRender(builder, times)` — 在组件实际需要前预创建多个实例 |
| `getReusePool()` 查询 | `utils.static.d.ets` `CustomComponentContext.getReusePool()` — 经 `UIUtils.getCustomComponentContext(component)` 获取 |
| `@Reusable`/`@ReusableV2` 复用回调 | `decoratorImpl/decoratorGlobalReusePool.ts` `resetOnReuse` — 复用时重置装饰变量 |
| 生命周期回调注册 | `utils.static.d.ets` `CustomComponentContext.registerActiveAndInactiveCallback` — `active`/`inactive` 回调注册（`@since 26.1.0 unpublished`） |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| `@Component`/`@ComponentV2` 装饰器 | `<OH_ROOT>/interface/sdk-js/api/arkui/incremental/annotation.static.d.ets` | `@Component`/`@ComponentV2`/`@Reusable`/`@ReusableV2`/`@Builder` 装饰器声明（经 barrel 重导出） |
| V2 生命周期装饰器 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/decorator.static.d.ets` | `@ComponentInit`/`@ComponentAppear`/`@ComponentBuilt`/`@ComponentReuse`/`@ComponentRecycle`/`@ComponentDisappear`/`@ComponentActive`/`@ComponentInactive`（`@since 24 static`/`26.0.0 static`） |
| 复用池查询 | `<OH_ROOT>/interface/sdk-js/api/arkui/stateManagement/utils.static.d.ets` | `UIUtils.getCustomComponentContext`/`getLifecycle`；`IReusePool`/`IReusableInfo`/`CustomComponentContext` |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 自定义组件测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/` 同目录 | `BaseCustomComponent`/`CustomComponentV2` 行为 |
| 复用池测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/tools/` | `GlobalReusePool`/`GlobalReusePoolRegistry` 行为 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticCustomComponent` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-03-07` | `specs/07-frontend/03-custom-components/07-static-custom-component-state/` | active（design.md 占位，Feat 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| `@ComponentV2` 状态变量修改不触发重渲染 | `CustomComponentV2` 仅是标记基类——确认每个状态变量是否独立使用了 `@Local`/`@Param`/`@Computed` 等装饰器 |
| 复用池未生效 | `decoratorGlobalReusePool.ts` — 确认 `__backing_reusePool` 字段是否由框架生成；`poolAccepts` 类列表是否包含目标组件类型 |
| `preRender` 预渲染失败 | `tools/globalReusePool.ts` `GlobalReusePool.preRender` — 检查 `builder` 参数与 `times` 是否合法 |
| 复用后状态未重置 | 各装饰变量的 `resetOnReuse(newValue)` 方法——确认复用回调是否触发了重置 |
| `active`/`inactive` 回调不触发 | `CustomComponentContext.registerActiveAndInactiveCallback` — `@since 26.1.0 unpublished`，确认 API 版本 |
| `UIUtils.getCustomComponentContext` 返回 undefined | 确认传入参数是否为 `IVariableOwner`（即 `@Component`/`@ComponentV2` 实例） |

## 调试入口

- **日志关键字**：`BaseCustomComponent`、`CustomComponentV2`、`GlobalReusePoolDecoratedVariable`、`GlobalReusePool`、`GlobalReusePoolRegistry`、`preRender`、`resetOnReuse`。
- **复用池状态**：`UIUtils.getCustomComponentContext(component).getReusePool().getReusableInfo(componentConstructor, reuseId?)` 查询当前池中实例数与上限。
- **生命周期排查**：`UIUtils.getLifecycle(component)` 返回 `CustomComponentLifecycle`，可用于检查当前阶段。
- **断点建议**：`GlobalReusePoolDecoratedVariable` 构造 → `GlobalReusePoolRegistry` 注册 → `preRender` 预创建 → 复用时 `resetOnReuse`。

## 相关主题

- 总览：`docs/kb/frontend/state_management.md`
- 静态 V2 核心（`DecoratedV2VariableBase` 基类）：`docs/kb/frontend/state_management/static_v2_core.md`
- 静态 V2 装饰器（`@Local`/`@Param` 等组件状态装饰器）：`docs/kb/frontend/state_management/static_v2_decorators.md`
- 跨前端组件互操作：`docs/kb/frontend/state_management/static_interop_bridge.md`
- 动态侧自定义组件机制（对照参考）：`docs/kb/frontend/state_management/custom_component.md`
