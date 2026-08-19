# Ability Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `AbilityContext`

## 定位

Ability Context 是 UIContext 的子能力域，为 ArkTS 和 C API 提宿主 Ability 上下文获取（getHostContext / getSharedLocalStorage / getAtomicServiceBar）、窗口断点计算（WidthBreakpoint / HeightBreakpoint）、窗口交互控制（enableSwipeBack）和窗口信息查询（getWindowName / getWindowId / isEasySplit）等 API。这些 API 使 UI 层在不依赖全局入口的条件下获取 Ability 级信息和窗口级元数据。

本文档只提供稳定的源码、API、测试和 Spec 路由。具体 API 行为（如 HeightBreakpoint 宽高比语义、AtomicServiceBar bundleType 门控逻辑）应回到当前源码、Spec 和测试核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| AbilityContext 获取 | `adapter/ohos/entrance/ace_container.h` | AceContainer::GetAbilityContext() 获取 OHOS AbilityRuntime::Context |
| UIContent→AbilityContext | `adapter/ohos/entrance/ui_content_impl.cpp` | UIContentImpl 持有 AbilityRuntime::Context，通过 Context::ConvertTo<AbilityContext> 转换 |
| 动态版前端 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | getHostContext(getContext)、getSharedLocalStorage(NativeLocalStorage.GetShared)、getAtomicServiceBar(bundleMgr 门控)、enableSwipeBack、getWindowName/getWindowId/isEasySplit |
| getContext 动态版原生实现 | `frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_context_module.cpp` | JsiContextModule::GetContext 是全局 getContext() 的原生入口；getHostContext() 通过 withInstanceId → getContext() → JsiContextModule::GetContext(instanceId) 查找 contexts_ 缓存 |
| 静态版前端 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | getHostContext(_Common_GetHostContext)、getSharedLocalStorage(_Common_GetSharedLocalStorage)、getAtomicServiceBar(Nullable)、enableSwipeBack(UIContextGetInfo)、getWindowName/getWindowId/isEasySplit |
| ANI 桥接层 | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | GetHostContext / GetSharedLocalStorage / GetWindowName / GetWindowId / IsEasySplit / GetWindowWidthBreakpoint / GetWindowHeightBreakpoint 及 InstanceId 切换 |
| Breakpoint 计算 | `frameworks/core/components_ng/base/view_abstract.cpp` | WidthBreakpoint 枚举 + VP 阈值(320/600/840/1440)、HeightBreakpoint 枚举 + 宽高比阈值(0.8/1.2)、GetWindowWidthBreakpoint / GetWindowHeightBreakpoint 实现 |
| enableSwipeBack 管道层 | `frameworks/core/pipeline_ng/pipeline_context.h` | SetEnableSwipeBack / GetWindowName / GetWindowId / IsDisplayInForceSplitMode 声明 |
| enableSwipeBack 管道实现 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | SetEnableSwipeBack(写入 RootPattern)、GetWindowName(从 Window 获取)、IsDisplayInForceSplitMode(forceSplitMgr_ + stageManager_ 综合判断) |
| UIContextGetInfoAccessor | `frameworks/core/interfaces/native/implementation/ui_context_get_info_accessor.cpp` | EnableSwipeBack(undefined 默认 true)、EnableSwipeBack(bool)、GetNavigationInfoByUniqueId |
| AtomicServiceBarAccessor | `frameworks/core/interfaces/native/implementation/ui_context_atomic_service_bar_accessor.cpp` | AtomicServiceBar GetBarRect |
| NAPI 注册 | `frameworks/bridge/declarative_frontend/jsview/js_view_context.cpp` | enableSwipeBack / isEasySplit 动态版注册 |
| AbilityContextInfo 结构 | `frameworks/core/components_ng/base/observer_handler.h` | AbilityContextInfo 含 instanceId / abilityId / moduleName / processName / bundleName，用于 UIObserver 路由 |
| UIObserver 关联 | `interfaces/napi/kits/observer/ui_observer.h` | UIObserver 使用 uiAbilityContext(napi_value) 关联注册回调；GetAbilityInfos 提取 AbilityContextInfo |
| Kit 层 UIContext | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h` | UIContextImpl 薄包装 PipelineContext，提供 GetToken / GetDisplayInfo |
| Preview 适配 | `adapter/preview/entrance/ace_container.h` | Preview 版 SetAbilityContext / GetAbilityContextByModule 空实现 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态版 API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | getHostContext / getSharedLocalStorage / getAtomicServiceBar / getWindowWidthBreakpoint / getWindowHeightBreakpoint / enableSwipeBack / getWindowName / getWindowId / isEasySplit |
| 静态版 API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | 同上，部分返回值类型有差异（getWindowId 返回 undefined 而非 -1） |
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | UIContext::GetToken / GetDisplayInfo 等 Kit 层等价 API |
| C API Handle | `interfaces/native/native_type.h` | ArkUI_ContextHandle（通过 OH_ArkUI_GetContextByNode 等获取） |

### 接口实现路径总览

本能力域 API 通过 UIContext 实例调用，有三种实现范式：

| 范式 | 入口文件 | 实例路由守卫 | 说明 |
|------|----------|--------------|------|
| 动态版 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `withInstanceId(instanceId_)` | getHostContext→getContext()、getSharedLocalStorage→NativeLocalStorage.GetShared()、getAtomicServiceBar→bundleMgr 门控 |
| 静态版 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | `Sync_InstanceId(instanceId_)` + `Restore_InstanceId()` | getHostContext→_Common_GetHostContext(instanceId)、getAtomicServiceBar→Nullable 预创建 |
| C API / ANI | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | `ContainerScope scope(instanceId)` | 所有方法通过 ANI Modifier 注册表分发 |

**关键前端差异**：

- getHostContext：动态版通过全局 `getContext()`，静态版通过 `ArkUIAniModule._Common_GetHostContext(instanceId)`
- getAtomicServiceBar：动态版延迟门控（每次调用查 bundleType），静态版构造时预创建 AtomicServiceBarInternal
- enableSwipeBack：动态版非布尔参数静默忽略，静态版 undefined 默认 true
- getWindowId：动态版容器不存在返回 -1，静态版将 -1 映射为 undefined

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|------------|------|
| AbilityRuntime Context | `adapter/ohos/entrance/ace_container.h` | `ability_runtime` | AceContainer::GetAbilityContext() 获取 OHOS AbilityRuntime::Context |
| UIContent→AbilityContext | `adapter/ohos/entrance/ui_content_impl.cpp` | `ability_runtime` | Context::ConvertTo<AbilityContext> 转换 |
| Preview Context Stub | `adapter/preview/entrance/ace_container.h` | preview stub | Preview 版 SetAbilityContext / GetAbilityContextByModule 空实现 |
| Bundle Manager | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `bundle_framework` | getAtomicServiceBar 通过 globalThis.requireNapi('bundle.bundleManager') 查 bundleType |
| IPC Token | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | `ipc_core` | UIContext::GetToken() 返回 sptr<IRemoteObject> |
| Rosen DisplayManager | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h` | `graphic_2d` | GetDisplayInfo() → DisplayManagerOhos → Rosen::DisplayManager |
| Window Manager | `frameworks/core/pipeline_ng/pipeline_context.cpp`（通过 window_ 成员） | `window_manager` | enableSwipeBack 通过 Window::SetEnableSwipeBack() 下发；isEasySplit 通过 ForceSplitMgr 判断；getWindowName / getWindowId 从 Window 获取；WidthBreakpoint / HeightBreakpoint 使用窗口尺寸 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIContextImpl 单测 | `test/unittest/interfaces/ace_kit/ui_context_impl_test.cpp` | UIContextImpl 方法测试含 GetToken、GetDisplayInfo 等 |
| AtomicServiceBar accessor 测试 | `test/unittest/capi/accessors/ui_context_atomic_service_bar_accessor_test.cpp` | AtomicServiceBar GetBarRect C API accessor |
| UIContextGetInfo accessor 测试 | `test/unittest/capi/accessors/` 目录 | EnableSwipeBack / GetNavigationInfoByUniqueId |
| Mock UIContextImpl | `test/mock/interfaces/inner_api/ace_kit/view/mock_ui_context_impl.cpp` | Host 测试替身 |

### 相关 Spec

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Ability 上下文与窗口信息 Spec | `specs/04-common-capability/12-ui-context/02-ability-context/Feat-01-ability-context-window-info-spec.md` | getHostContext / getSharedLocalStorage / getAtomicServiceBar / WidthBreakpoint / HeightBreakpoint / enableSwipeBack / getWindowName / getWindowId / isEasySplit |
| Ability 上下文设计文档 | `specs/04-common-capability/12-ui-context/02-ability-context/design.md` | 架构设计、调用链层级分析、关键设计决策 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| getHostContext 返回 undefined | Frontend::GetHostContext() 是否返回空、AceContainer::GetAbilityContext() 初始化时机 |
| getSharedLocalStorage 返回 undefined/null | 静态版返回 undefined、C++ 层返回 null |
| getAtomicServiceBar 返回 undefined | jsUIContext.js bundleMgr 门控检查（动态版）、@ohos.arkui.UIContext.ts 构造时 AtomicServiceBarInternal（静态版） |
| HeightBreakpoint 计算结果不符合预期 | view_abstract.cpp 宽高比计算（aspectRatio = H/W，阈值 0.8/1.2）；不做 density 转换，使用窗口原始像素值 |
| HeightBreakpoint width=0 边界 | aspectRatio=0 → HEIGHT_SM |
| WidthBreakpoint 在容器/窗口为 null 时返回异常 | C++ 层返回 -2（container null）/ -3（window null）；静态前端 handleBreakpointError 防御性处理 -1（ANI 初始化失败场景）并映射为 WIDTH_XS / HEIGHT_SM |
| enableSwipeBack(undefined) 行为差异 | 动态版静默忽略 vs 静态版默认 true（ui_context_get_info_accessor.cpp） |
| getWindowId 返回 -1 vs undefined | 动态版返回 -1、静态版将 -1 映射为 undefined |
| getWindowName 窗口不存在时 | C++ 返回空字符串、静态版返回 undefined |
| isEasySplit 在 PipelineContext 不可获取时 | 安全降级返回 false（pipeline_context.cpp） |
| AbilityContext 获取失败 | AceContainer::GetAbilityContext()、UIContentImpl context_ 初始化时机 |
| AtomicServiceBarController 方法可见性 | setVisible/setBackgroundColor/setTitleContent/setTitleFontStyle/setIconColor/getBarRect/onBarRectChange — 通过 UIContext.getAtomicServiceBar() 获取 |
| UIObserver 回调不触发 | AbilityContextInfo 结构、uiAbilityContext napi_value 关联 |

## 调试入口

- getHostContext 断点：动态版 jsUIContext.js getContext()、静态版 common_ani_modifier.cpp GetHostContext → Frontend::GetHostContext()
- getAtomicServiceBar 门控断点：动态版 jsUIContext.js bundleMgr.getBundleInfoForSelfSync、静态版 AtomicServiceBarInternal 构造
- Breakpoint 计算断点：view_abstract.cpp GetWindowWidthBreakpoint / GetWindowHeightBreakpoint
- enableSwipeBack 断点：ui_context_get_info_accessor.cpp EnableSwipeBack → pipeline_context.cpp SetEnableSwipeBack → RootPattern
- isEasySplit 断点：common_ani_modifier.cpp IsEasySplit → pipeline_context.cpp IsDisplayInForceSplitMode
- 窗口信息断点：common_ani_modifier.cpp GetWindowName / GetWindowId → PipelineContext
- AbilityContext 获取断点：ace_container.cpp GetAbilityContext() → ability_runtime Context

## 相关主题

- UIContext 入口架构：`docs/kb/capabilities/ui-context.md`
- Frame 帧回调：`docs/kb/capabilities/frame-callback.md`
- [路由管理：`docs/kb/api/router.md`](../api/router.md)
- [窗口机制：`docs/kb/architecture/window-mechanism.md`](../architecture/window-mechanism.md)
- [UIObserver：`docs/kb/capabilities/ui-observer.md`](ui-observer.md)
- [UIContext 实例 ID 泄漏](../issues/lifecycle/uicontext-instance-id-leak.md) — JS 前端历史配对问题（已修复）与 AbilityContext 实例路由排查