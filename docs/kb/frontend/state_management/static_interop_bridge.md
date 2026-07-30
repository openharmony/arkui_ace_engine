# Static State Management — Interop 桥接 Context

> 文档版本：v1.0
> 更新时间：2026-07-27
> 来源：`docs/context_registry.json` 主题 `StateMgmtStaticInterop`

## 定位

静态前端（ArkTS 1.2 / arkoala）与动态前端（ArkTS 1.1，`declarative_frontend`）之间的状态、存储、组件、Builder 互操作桥。arkoala 源码不实现 V2 类级观测运行时（`class ObserveV2`/`trackInternal`/`BindingProxyHandler`），而是通过 `ESValue.getGlobal().getProperty(...)` 跨前端调用动态侧运行时；同时通过互操作桥实现存储双向可见、组件代理、Builder 桥接、状态代理等。

本域对应 FuncID `07-02-14`（状态管理互操作）。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| 互操作源码根（存储/Backing） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/` | `interopStorage.ts`/`interopStorageV2.ts`/`interopBackingValue.ts`/`interopBinding.ts` |
| 组件互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` | 核心互操作文件（约 1400 行）：`CompatiblePeerNode`/`compatibleComponent`/`getCompatibleState`/`enableCompatibleObservedV2ForStatic*`/`staticStateBindObservedObject`/`createCompatibleStaticState`/14 个 `register*` 回调 |
| 扩展组件互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interopExtendableComponent.ets` | `InteropExtendableComponent extends ExtendableComponent` — 静态侧适配器，代理 `findProvide`/`findProvider`/`addProvide`/`setActive`/`localStorage` 到动态侧 |
| 互操作全局开关 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` `class InteropState` | 进程级互操作启用/禁用标志 |
| Builder 互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` | `compatibleWrappedBuilder`/`compatibleWrappedBuilderInternal`/`transferCompatibleBuilder`/`transferCompatibleUpdatableBuilder`/`unwrapTransferCompatibleUpdatableBuilder` |
| 状态代理（V1→动态） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` `getCompatibleState<T>` | 为静态 `StateDecoratedVariable`/`ProvideDecoratedVariable`/`PropDecoratedVariable`/`PropRefDecoratedVariable` 创建动态 `ObservedPropertyPU` 代理 |
| 状态代理（动态→静态） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` `createCompatibleStaticState<T>` | 为动态 `ObservedProperty` 包装为静态 `ProvideDecoratedVariable` 代理 |
| V2 类观测桥 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` | `enableCompatibleObservedV2ForStatic`/`enableCompatibleObservedV2ForStaticMeta`/`enableCompatibleObservedV2ForDynamic` — V2 类级观测跨前端桥接（调用方经 `ESValue.getGlobal().getProperty(...)`） |
| 对象判别工具 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/component/interop.ts` | `isDynamicObject(value)`/`getRawObject(value)`/`getObservedObject(value)`（V1）/`getV2ObservedObject(value)`（V2） |
| Binding 互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/interopBinding.ts` | `InteropTransferMutableBinding<T>`/`InteropTransferBinding<T>` — 经 `dynamicBinding: ESValue` 代理 `value` get/set |
| Backing Value 互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/interop/interopBackingValue.ts` | `InteropDecoratorBackingValue`（V1）/`InteropV2DecoratorBackingValue`（V2）— 绑定 observed 对象到静态侧元数据 |
| `@Watch` 互操作 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/decoratorImpl/decoratorInteropWatch.ts` | `InteropWatchFunc extends WatchFunc` — 包装 `@Watch` 回调，加 `UIContext.checkThread(instanceId)` 线程亲和性检查 |
| ANI 原生桥（ViewStackProcessor） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/interop/interop_module.cpp` | `CreateViewStackProcessor`/`PopViewStackProcessor`/`DeleteViewStackProcessor` — 仅 3 个函数，经 `getInteropAniModifier()` 分发 |

### 关键机制锚点

| 机制 | 源码位置 |
|------|----------|
| 互操作启动入口 | `component/interop.ts` `openInterop()` — 调用 14 个 `register*` 回调注册静态侧访问器到动态侧 |
| 14 个 register 回调 | `component/interop.ts` — `registerCreateWatchFuncCallback`/`registerCreateStaticObservedCallback`/`registerCompatibleStaticComponentCallback`/`registerMakeBuilderParameterStaticProxy`/`registerUpdateInteropExtendableComponent`/`registerResetInteropExtendableComponent`/`registerTransferCompatibleBuilderCallback`/`registertransferCompatibleDynamicBuilderCallback`/`registerCreateCompatibleStaticState`/`registerTransferCompatibleUpdatableBuilderCallback`/`registerNavPathStackCallback`/`registerLocalStorageSetProxy`/`registerIsCloneableObjectFunc`/`registerCloneCloneableObjectFunc` |
| 动态组件→静态 peer | `component/interop.ts` `compatibleComponent(init, update, component?)` — `@memo` 工厂，经 `ArkUIAniModule._CreateViewStackProcessor`/`_PopViewStackProcessor`/`_DeleteViewStackProcessor` 创建静态 peer 包装动态组件 |
| 静态组件→动态可见 | `component/interop.ts` `compatibleStaticComponent<T>(factory, options?, content?)` — 包装静态 `BaseCustomComponent` 供动态侧渲染 |
| 动态组件创建入口 | `component/interopExtendableComponent.ets` `createInteropView(staticComponent)` — 经 `ESValue.getGlobal().getProperty('createViewInterop')` 创建动态侧 `ViewInterop` |
| V2 类观测反向桥 | `component/interop.ts` `enableCompatibleObservedV2ForDynamic<T>(value)` — 反向：为静态 observed 对象添加动态 watch funcs |
| `@Track` 双路径 | `component/interop.ts` `staticStateBindObservedObject` — `onTrackPropertyRead`/`onTrackPropertyChange` 回调转发到静态侧 `MutableStateMeta` |
| `isStaticProxy` 检测 | （动态侧实现）— 互操作中检测对象是否为静态代理，决定是否需要 `deepCopyStaticProxy` |
| Binding 线程检查 | `decoratorImpl/decoratorInteropWatch.ts` `InteropWatchFunc` — `UIContext.checkThread(instanceId)` 确保回调在正确实例线程执行 |

### API 入口

互操作是引擎内部机制，不暴露公开 API。无独立 SDK 声明文件。

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| 互操作测试桩 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/stateManagement/mock/` | `interopStorageV2.ts`/`interop.ts`/`interop_component_mock.ts` 测试桩 |
| ANI 桥测试 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/interop/` 同目录 | 原生桥行为 |
| Context registry | `docs/context_registry.json` | 主题 `StateMgmtStaticInterop` |

### 相关 Spec

| FuncID | Spec 域 | 状态 |
|--------|---------|------|
| `07-02-14` | `specs/07-frontend/02-state-management/14-state-management-interop/` | active（Feat-01~05 待补充） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 跨前端状态传递丢失 | `component/interop.ts` `getCompatibleState`/`createCompatibleStaticState` — 确认代理是否成功创建并 `setProxy`/`setProxyValue` 绑定 |
| `@ObservedV2`/`@Trace` 跨前端不工作 | `component/interop.ts` `enableCompatibleObservedV2ForStatic` — UIPlugin 转换是否调用了动态侧 `ESValue.getGlobal().getProperty('enableCompatibleObservedV2ForStatic')` |
| 互操作未启用 | `component/interop.ts` `class InteropState` — 进程级开关；`openInterop()` 是否在启动时调用并注册了 14 个回调 |
| 动态组件在静态侧渲染异常 | `component/interop.ts` `compatibleComponent` — `ViewStackProcessor` 是否正确 push/pop；`CompatiblePeerNode` 是否正确代理了属性/事件 |
| 静态组件在动态侧渲染异常 | `component/interop.ts` `compatibleStaticComponent` — `BaseCustomComponent` 包装是否正确；`createInteropView` 是否调用了动态侧 `createViewInterop` |
| `@Watch` 跨前端线程异常 | `decoratorInteropWatch.ts` `InteropWatchFunc` — `UIContext.checkThread(instanceId)` 是否抛出线程亲和性错误 |
| Builder 跨前端传递失败 | `component/interop.ts` `transferCompatibleBuilder`/`transferCompatibleUpdatableBuilder` — 确认 Builder 包装/解包是否配对 |

## 调试入口

- **日志关键字**：`InteropState`、`openInterop`、`CompatiblePeerNode`、`compatibleComponent`、`getCompatibleState`、`createCompatibleStaticState`、`enableCompatibleObservedV2ForStatic`、`createViewInterop`、`bindStaticLocalStorage`/`bindStaticAppStorage`、`bindStaticAppStorageV2`。
- **互操作启用排查**：`InteropState` 进程级标志；`openInterop()` 是否在启动时执行；14 个 `register*` 回调是否全部注册成功。
- **跨前端对象判别**：`isDynamicObject(value)`/`getRawObject(value)`/`getObservedObject(value)`（V1）/`getV2ObservedObject(value)`（V2）用于确认对象在静态/动态侧的归属与原始对象。
- **断点建议**：`getCompatibleState` → `setProxy`/`setProxyValue` → 动态侧 `ObservedPropertyPU` 通知 → 静态侧 `MutableStateMeta.fireChange`。
- **V2 类观测排查**：`enableCompatibleObservedV2ForStatic` → `staticStateBindObservedObject` → 每个属性的 `IMutableStateMeta` 创建。

## 相关主题

- 总览：`docs/kb/frontend/state_management.md`
- 动态侧 Interop 桥接（对照参考）：`docs/kb/frontend/state_management/interop_bridge.md`
- 静态 V1 核心：`docs/kb/frontend/state_management/static_v1_core.md`
- 静态 V2 装饰器与数据对象（UIPlugin 转换的入口）：`docs/kb/frontend/state_management/static_v2_decorators.md`
- 静态存储体系（跨前端存储桥）：`docs/kb/frontend/state_management/static_storage.md`
- 静态自定义组件机制：`docs/kb/frontend/state_management/static_custom_component.md`
