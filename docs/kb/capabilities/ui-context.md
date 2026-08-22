# UIContext Context

> 文档版本：v1.3
> 更新时间：2026-07-25
> 来源：`docs/context_registry.json` 主题 `UIContext`

## 定位

UIContext 是 ArkUI 引擎的核心上下文入口能力，为 ArkTS 和 C API 提供统一的实例级 UI 操作接口。它涵盖 UIContext 报象基类与 UIContextImpl 实现、ArkUI_ContextHandle C API 透传桥、IUIContextAccessor 静态版 accessor 桥、AbilityContext 平台适配、FrameCallback 帧回调调度、以及 31 个 NAPI 子模块（Router、PromptAction、Animator、Measure、Observer 等）的挂载分发点。UIContext 不是独立组件，而是引擎级通用能力，是所有 UI 操作的实例级入口。

本文档只提供稳定的源码、API、测试和 Spec 路由。具体子工厂方法、回调调度语义和 C API handle 行为应回到当前源码、测试和 Spec 核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| UIContext 报象基类 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | Kit 层 UIContext 报象基类；RunScopeUITask/RunScopeUITaskSync、OnBackPressed、GetColorMode/GetFontScale、GetOverlayManager、RequestFrame 等 ~30 个纯虚方法 |
| UIContextImpl 实现 | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.h` | Kit 层 UIContextImpl；继承 UIContext，持有 PipelineContext*，所有方法委托到 PipelineContext |
| UIContextImpl 实现.cpp | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.cpp` | UIContextImpl 实现；UIContext::Current() 静态方法通过 PipelineContext::GetCurrentContextSafelyWithCheck() 获取实例 |
| PipelineContext 持有 UIContext | `frameworks/core/pipeline_ng/pipeline_context.h` | PipelineContext::GetUIContext() 惰性创建 UIContextImpl；FrameCallback 类型定义 |
| ArkUI_ContextHandle 定义 | `interfaces/native/native_type.h` | ArkUI_Context 结构体（只含 int32_t id）和 ArkUI_ContextHandle 类型定义 |
| IUIContextAccessor 实现 | `frameworks/core/interfaces/native/implementation/iui_context_accessor.cpp` | IUIContextAccessor 845 行；FreezeUINode、DispatchKeyEvent、OpenBindSheet/UpdateBindSheet/CloseBindSheet、BindTabsToScrollable、SetCustomKeyboardContinueFeature、SetCustomCursor、EnableEventPassthrough 等 |
| UIContextGetInfoAccessor | `frameworks/core/interfaces/native/implementation/ui_context_get_info_accessor.cpp` | GetNavigationInfoByUniqueId、EnableSwipeBack |
| UIContextAtomicServiceBarAccessor | `frameworks/core/interfaces/native/implementation/ui_context_atomic_service_bar_accessor.cpp` | AtomicService bar GetBarRect |
| GlobalScopeUicontextTextMenuAccessor | `frameworks/core/interfaces/native/implementation/global_scope_uicontext_text_menu_accessor.cpp` | SetMenuOptions、DisableSystemServiceMenuItems、DisableMenuItems |
| GlobalScopeUicontextFontScaleAccessor | `frameworks/core/interfaces/native/implementation/global_scope_uicontext_font_scale_accessor.cpp` | IsFollowingSystemFontScale、GetMaxFontScale |
| UIContextHelper（动态版前端） | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h` | UIContextHelper 静态方法；AddUIContext/RemoveUIContext/GetUIContext/HasUIContext，线程安全的 instanceId→JSValue 缓存 |
| IUIContext IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-iuicontext.idl` | 静态版 IUIContext IDL 定义 |
| OH_ArkUI_GetContextByNode 实现 | `interfaces/native/node/node_adapter_impl.cpp` | C API：从 ArkUI_NodeHandle 获取 ArkUI_ContextHandle |
| OH_ArkUI_GetContextFromNapiValue 实现 | `interfaces/native/node/native_node_napi.cpp` | NAPI 桥接：从 napi_value 获取 ArkUI_ContextHandle |
| OH_ArkUI_GetContextFromAniValue 实现 | `interfaces/native/node/native_node_ani.cpp` | ANI 桥接：从 ani_value 获取 ArkUI_ContextHandle |
| OH_ArkUI_PostUITask/RunTaskInScope | `interfaces/native/node/node_model_safely.cpp` | C API 作用域任务投递和同步执行 |
| OH_ArkUI_RunTaskInScope | `interfaces/native/node/node_utils.cpp` | C API 作用域任务执行 |
| 动态版前端 UIContext | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | 动态版 UIContext 全部 getXxx 工厂方法与直接方法；~20 个子对象 Impl 类（Router/PromptAction/OverlayManager/ComponentUtils/FocusController/DragController 等）+ animateTo/showDialog/vp2px 等；所有方法通过 withInstanceId(instanceId_) 守卫路由 |
| 动态版 UIContextHelper | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h` | AddUIContext/RemoveUIContext/GetUIContext/HasUIContext，线程安全的 instanceId→JSValue 缓存 |
| 动态版 UIContextHelper 实现 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.cpp` | UIContextHelper 实现；GetUIContext 先查缓存再通过 ArkTSUtils::GetContext 回填 |
| 静态版前端 UIContext | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | 静态版 UIContext 类定义；导入所有子对象 Impl 类；工厂方法返回 new XxxImpl(instanceId_)；所有 Impl 方法通过 Sync_InstanceId/Restore_InstanceId 守卫路由 |
| 静态版 UIContextImpl | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | 所有子对象 Impl 类实现（RouterImpl/PromptActionImpl/OverlayManagerImpl/ComponentUtilsImpl/FocusControllerImpl/DragControllerImpl 等）+ DetachedRootEntryManager |
| 静态版 UIContextUtil | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextUtil.ets` | availableInstanceIds_ 实例可用性集合；isAvailable() 校验；Sync_InstanceId/Restore_InstanceId 路由守卫原语 |
| 静态版 ANI common_module | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/common/common_module.cpp` | ANI 原生桥接实现；getWindowWidthBreakpoint/getWindowHeightBreakpoint/isEasySplit/getPageRootNode 等；通过 PipelineContext::GetContextByContainerId(instanceId) 获取上下文 |
| 静态版 UIContext IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-iuicontext.idl` | 静态版 IUIContext IDL 定义 |
| 静态版 UIContext 文本工具 IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-uicontext-text-utils.idl` | 静态版 MeasureUtils/Font 相关 IDL |
| 静态版 UIContext UIObserver IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-uicontext-uiobserver.idl` | 静态版 UIObserver 相关 IDL |
| 静态版 Generated 桥接 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/framework/ohos.arkui.UIContext.ets` | IDL 生成的静态桥接胶水代码（自动生成，勿手动修改） |
| 静态版 ComponentContent Transfer | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/handwritten/transfer/UIContextTransfer.ets` | ComponentContent/PeerNode 转移机制 |
| 静态版 Inner API 类型 | `frameworks/bridge/arkts_frontend/koala_projects/inner_api/arkui/base/UIContextUtil.d.ets` | UIContextUtil 的 .d.ets 类型声明 |
| 静态版 ANI Modifier（通用方法） | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | UIContext 通用方法的 ANI 原生实现（1409 行）；Sync_InstanceId/Restore_InstanceId/isAvailable/IsEasySplit/getWindowWidthBreakpoint/FreezeUINode 等 |
| 静态版 ANI common_node Modifier | `frameworks/core/interfaces/native/ani/common_node_ani_modifier.cpp` | FrameNode 相关 ANI 原生方法；getFrameNodeById/getAttachedFrameNodeById 等 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | UIContext 报象基类 |
| C API Handle | `interfaces/native/native_type.h` | ArkUI_ContextHandle 定义 |
| C API 方法 | `interfaces/native/native_node.h` | OH_ArkUI_GetContextByNode、OH_ArkUI_RunTaskInScope、OH_ArkUI_PostUITask/PostUITaskAndWait/PostAsyncUITask |
| NAPI 桥接 | `interfaces/native/native_node_napi.h` | OH_ArkUI_GetContextFromNapiValue、OH_ArkUI_PostFrameCallback、OH_ArkUI_PostIdleCallback |
| ANI 桥接 | `interfaces/native/native_node_ani.h` | OH_ArkUI_NativeModule_GetContextFromAniValue |
| 动态版 IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-iuicontext.idl` | 静态版 IUIContext IDL |
| NAPI 子模块挂载 | `interfaces/napi/kits/` | ~32 个子模块目录（Router、PromptAction、Animator、Measure、Observer 等） |
| 动态版 API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | 动态版 UIContext 类和 ~20 个子对象接口定义 |
| 静态版 API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | 静态版 UIContext 类和子对象接口定义 |
| C API 功能模块 | `interfaces/native/` | animate/drag/focus 等功能模块通过 ArkUI_ContextHandle 获取 PipelineContext，各模块头文件在 native_animate.h、drag_and_drop.h、native_interface_focus.h 等 |

### 接口实现路径总览

UIContext 动态接口覆盖 ~20 个 getXxx 工厂方法（返回绑定 instanceId 的子对象）和多个直接方法（animateTo/showDialog/vp2px 等），有三种实现范式。本节只给出架构级对比，动态版完整管道见下方 "动态接口实现路径" 章节，静态版完整管道见下方 "静态接口实现路径" 章节，不对具体功能模块（Router/PromptAction/Drag/Focus/Animate 等）展开。

| 范式 | 入口文件 | 实例路由守卫 | 子对象 Impl 模式 | 说明 |
|------|----------|--------------|------------------|------|
| 动态版（Declarative Frontend） | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `withInstanceId(instanceId_)` 包装 NAPI 调用 | 每个 Impl 类构造时接收 instanceId，方法体用 withInstanceId 包装 → globalThis.requireNapi('xxx') | JS 直接执行，NAPI 子模块按需加载 |
| 静态版（ArkTS Frontend） | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | `ArkUIAniModule._Common_Sync_InstanceId(instanceId_)` + `_Common_Restore_InstanceId()` | 每个 Impl 类构造时接收 instanceId，方法体开头 Sync_InstanceId、结尾 Restore_InstanceId → ArkUIAniModule.* | ArkTS 编译期绑定，ANI 桥接原生模块；完整管道见下方 "静态接口实现路径" |
| C API | `interfaces/native/native_node.h` 等 | `ArkUI_ContextHandle.id` → PipelineContext | 各功能模块（Animate/Drag/Focus 等）通过 ContextHandle 获取 PipelineContext | 不展开各模块细节 |

### 动态接口实现路径

动态版 UIContext（Declarative Frontend）采用 JS 主类 → Impl 内联 → withInstanceId 守卫 → NAPI 子模块 → PipelineContext 的管道。本节给出管道各层的稳定入口，不对各功能子模块展开。

| 管道层 | 稳定路径 | 说明 |
|--------|----------|------|
| API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | 动态版 UIContext 类和 ~20 个子对象接口定义 |
| JS 主类 + 所有 Impl | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | 2140 行；UIContext 类 + ~20 个子对象 Impl 类（Router/PromptAction/OverlayManager/ComponentUtils/FocusController/DragController 等）全部内联定义；工厂方法 + 直接方法 |
| getUINativeModule 工具 | `frameworks/bridge/declarative_frontend/engine/arkCommon.js` | getUINativeModule() 返回 arkUINativeModule 全局对象；UIContext 直接方法（getWindowWidthBreakpoint/getFrameNodeById 等）通过此模块调用 |
| withInstanceId 守卫 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js`（行 2036） | `function withInstanceId(instanceId, callback)` → `__JSScopeUtil__.syncInstanceId(instanceId)` + try/callback + `__JSScopeUtil__.restoreInstanceId()` |
| __availableInstanceIds__ | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js`（行 2081） | `const __availableInstanceIds__ = new Set()`；isAvailable() 校验实例可用性；`__addAvailableInstanceId__/__removeAvailableInstanceId__` 由 C++ 侧回调 |
| NAPI 子模块挂载 | `interfaces/napi/kits/`（~32 个子模块） | 各 Impl 构造时 `globalThis.requireNapi('moduleName')` 按需加载 NAPI 子模块（router/animator/promptAction/mediaquery/measure/arkui.inspector/arkui.dragController 等） |
| UIContextHelper 缓存 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h` | instanceId→JSValue 全局缓存（uiContextMap_）；线程安全读写锁 |
| UIContextHelper 实现 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.cpp` | AddUIContext（注册实例）/RemoveUIContext（容器销毁时移除）/GetUIContext（先查缓存再通过 ArkTSUtils::GetContext 回填）/HasUIContext |
| C++ 侧回调注册 | `frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.cpp` | CallAddAvailableInstanceIdFunc/CallRemoveAvailableInstanceIdFunc 调用 JS 层 `__addAvailableInstanceId__/__removeAvailableInstanceId__`；CallGetUIContextFunc 调用 `__getUIContext__`；RegisterRemoveUIContextFunc 注册容器销毁回调 |
| __JSScopeUtil__ | JS 引擎内置对象 | syncInstanceId/restoreInstanceId/getCallingScopeUIContext/getLastFocusedUIContext/getLastForegroundUIContext/getAllUIContexts/resolveUIContext |

**动态版管道调用链**（架构级，不展开各子模块）：

```
应用层 UIContext.getXxx / UIContext.animateTo / ...
  ↓
jsUIContext.js → new UIContext(instanceId_) → getXxx() → new XxxImpl(instanceId_)
  ↓
XxxImpl.method() → withInstanceId(instanceId_) → __JSScopeUtil__.syncInstanceId(instanceId_)
  → globalThis.requireNapi('moduleName').xxxMethod(args) 或 getUINativeModule().xxx(args)
  → __JSScopeUtil__.restoreInstanceId()
  ↓
NAPI 子模块 (router/animator/promptAction/...) 或 arkUINativeModule
  ↓
PipelineContext::GetCurrentContext() → C++ 引擎层
```

**直接方法路由**（不走子对象 Impl）：

```
UIContext.animateTo/animateToImmediately → Context.animateTo/animateToImmediately（JS 引擎内置）
UIContext.getWindowWidthBreakpoint/getWindowId → getUINativeModule().common.xxx（arkUINativeModule）
UIContext.getFrameNodeById/getFrameNodeByKey → getUINativeModule().xxx → C++ Native
UIContext.vp2px/px2vp → globalThis.vp2px/px2vp（JS 引擎内置）
```

**实例生命周期管理**：
- 创建：AceContainer 初始化 → JsiDeclarativeEngineInstance::CallAddAvailableInstanceIdFunc → `__addAvailableInstanceId__(instanceId)` → `__availableInstanceIds__.add(instanceId)`
- 缓存注册：UIContextHelper::AddUIContext(vm, instanceId, uiContext) → uiContextMap_.emplace(instanceId, globalRef)
- 销毁：容器销毁 → JsiDeclarativeEngineInstance::CallRemoveAvailableInstanceIdFunc → `__removeAvailableInstanceId__(instanceId)` → `__availableInstanceIds__.delete(instanceId)` + UIContextHelper::RemoveUIContext(instanceId) → uiContextMap_.erase(instanceId)
- 校验：isAvailable() → `__availableInstanceIds__.has(instanceId_)`；校验失败时抛 BusinessError(120007) 或返回 undefined/null

### 静态接口实现路径

静态版 UIContext（ArkTS Frontend）采用 IDL → generated → handwritten → Impl → ANI modifier → native 的多层管道。本节给出管道各层的稳定入口，不对各功能子模块展开。

| 管道层 | 稳定路径 | 说明 |
|--------|----------|------|
| IDL 定义 | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-iuicontext.idl` | IUIContext IDL；定义 UIContext 接口、getXxx 工厂方法签名、直接方法签名 |
| IDL 补充 | `arkui-uicontext-text-utils.idl` + `arkui-uicontext-uiobserver.idl`（同目录） | MeasureUtils/Font 和 UIObserver 的 IDL 补充 |
| Generated 桥接 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/generated/framework/ohos.arkui.UIContext.ets` | IDL 生成的静态桥接胶水代码；import UIContext + extractors |
| Handwritten 主类 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | 手写 UIContext 类；所有 getXxx 工厂方法 + 直接方法 + isAvailable/setResourceManagerCacheMaxCountForHSP 等 |
| Impl 子对象 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextImpl.ets` | 所有子对象 Impl 类；每个方法 Sync_InstanceId + ArkUIAniModule._Xxx_yyy + Restore_InstanceId |
| UIContextUtil 路由守卫 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/base/UIContextUtil.ets` | availableInstanceIds_ 集合管理；isAvailable()；Sync_InstanceId/Restore_InstanceId 原语 |
| Inner API 类型 | `frameworks/bridge/arkts_frontend/koala_projects/inner_api/arkui/base/UIContextUtil.d.ets` | UIContextUtil 的 .d.ets 类型声明 |
| ComponentContent Transfer | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/handwritten/transfer/UIContextTransfer.ets` | ComponentContent/PeerNode 转移机制；用于 openCustomDialog/executeDrag/createFromBuilder 等需要离屏渲染的 API |
| ANI Modifier（UIContext 通用方法） | `frameworks/core/interfaces/native/ani/common_ani_modifier.cpp` | 静态版 UIContext 通用方法的 ANI 原生实现（1409 行）；Sync_InstanceId/Restore_InstanceId/isAvailable/IsEasySplit/getWindowWidthBreakpoint/getWindowHeightBreakpoint/GetPageRootNode/setKeyboardAvoidMode/getKeyboardAvoidMode/FreezeUINode/EnableSwipeBack 等 |
| ANI common_node Modifier | `frameworks/core/interfaces/native/ani/common_node_ani_modifier.cpp` | 静态版 FrameNode 相关 ANI 原生方法；getFrameNodeById/getAttachedFrameNodeById 等 |
| ANI common_module | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/src/ani/native/common/common_module.cpp` | ANI 模块注册入口；通过 PipelineContext::GetContextByContainerId(instanceId) 获取上下文 |

**静态版管道调用链**（架构级，不展开各子模块）：

```
应用层 UIContext.getXxx / UIContext.animateTo / ...
  ↓
@ohos.arkui.UIContext.ts → new XxxImpl(instanceId_)
  ↓
XxxImpl.method() → Sync_InstanceId(instanceId_) → ArkUIAniModule._Xxx_yyy(instanceId, args) → Restore_InstanceId()
  ↓
ANI Modifier (common_ani_modifier / 各功能 ani_modifier)
  ↓
PipelineContext::GetContextByContainerId(instanceId) → PipelineContext → C++ 引擎层
```

**实例生命周期管理**：
- 创建：AceContainer 初始化 → AddUIContext → availableInstanceIds_.add(instanceId)
- 销毁：容器销毁 → RemoveUIContext → availableInstanceIds_.delete(instanceId)
- 校验：isAvailable() → availableInstanceIds_.has(instanceId)；校验失败时抛 BusinessError(120007) 或返回 undefined/null

**核心路由模式对比**：

- **动态版**：`withInstanceId(instanceId_)` → `globalThis.requireNapi('moduleName')` → NAPI 子模块 → PipelineContext
- **静态版**：`Sync_InstanceId(instanceId_)` → `ArkUIAniModule._Xxx_yyy(instanceId, ...)` → ANI 原生模块 → PipelineContext
- **C API 版**：`ArkUI_ContextHandle.id` → `PipelineContext::GetContextByContainerId(id)` → PipelineContext

**实例可用性校验**：
- 动态版：`__availableInstanceIds__.has(instanceId_)`（jsUIContext.js）
- 静态版：`UIContextUtil.availableInstanceIds_.has(instanceId_)`（UIContextUtil.ets）/ `ArkUIAniModule._Common_isAvailable(instanceId)`（ANI）
- C API 版：`ArkUI_Context.id` 提取 + PipelineContext 查找

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|------------|------|
| AbilityContext | `adapter/ohos/entrance/ace_container.h` | `ability_runtime` | AceContainer::GetAbilityContext() 获取 OHOS AbilityRuntime::Context |
| UIContent→AbilityContext | `adapter/ohos/entrance/ui_content_impl.cpp` | `ability_runtime` | UIContentImpl 持有 AbilityRuntime::Context，通过 Context::ConvertTo<AbilityContext> 转换 |
| Preview Context | `adapter/preview/external/ability/context.h` | preview stub | Preview 版本的 Context 空实现 |
| Rosen 渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.h` | `graphic_2d` | RS 渲染上下文绑定 |
| IPC Token | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h`（`IRemoteObject` 前向声明） | `ipc_core` | UIContext::GetToken() 返回 sptr<IRemoteObject>；AceContainer::GetToken() 提供实现；用于权限校验和 Ability 连接 |
| PixelMap | `adapter/ohos/osal/pixel_map_ohos.h` | `multimedia_image_framework` | 动态版 CursorController.setCustomCursor/静态版 common_ani_modifier setBackgroundImagePixelMap 通过 PixelMap::CreatePixelMap 使用图片资源 |
| 静态版 ANI PixelMap | `frameworks/bridge/arkts_frontend/...src/ani/native/common/common_module.cpp`（`OHOS::Media::PixelMapTaiheAni`） | `multimedia_image_framework` | 静态版 common_module 通过 PixelMapTaiheAni::GetNativePixelMap 获取原生 PixelMap |
| DisplayManager | `adapter/ohos/osal/display_manager_ohos.h` | `graphic_2d`（Rosen::DisplayManager） | UIContext::GetDisplayInfo() → DisplayManagerOhos → Rosen::DisplayManager::GetDefaultDisplay/GetDisplayById |
| Bundle Manager | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js`（`globalThis.requireNapi('bundle.bundleManager')`） | `bundle_framework` | 动态版 isEasySplit() 通过 bundle.bundleManager 查询分屏状态 |
| 资源管理 | `frameworks/core/common/resource/resource_manager.h` | 内部（AceType 派生） | UIContextImpl::GetOrCreateResourceAdapter → ResourceManager::GetInstance()；资源适配器内部通过 ResourceAdapterImpl 按平台桥接外部资源仓 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIContextImpl 单测 | `test/unittest/interfaces/ace_kit/ui_context_impl_test.cpp` | UIContextImpl 947 行测试；GetFontScale、GetColorMode、GetOverlayManager、RequestFrame、GetApiTargetVersion、RegisterSurfaceChangedCallback 等 |
| Mock UIContextImpl | `test/mock/interfaces/inner_api/ace_kit/view/mock_ui_context_impl.cpp` | Host 测试替身；UIContextImpl 所有方法的 stub 实现 |
| C API Handle 测试 | `test/unittest/interfaces/native_node_napi_test.cpp` | OH_ArkUI_GetContextFromNapiValue、OH_ArkUI_PostFrameCallback/PostIdleCallback |
| C API Node Handle 测试 | `test/unittest/interfaces/native_node_test.cpp` | OH_ArkUI_GetContextByNode、RunTaskInScope、PostUITask |
| AtomicServiceBar accessor | `test/unittest/capi/accessors/ui_context_atomic_service_bar_accessor_test.cpp` | UIContextAtomicServiceBarAccessor C API accessor |

### 相关 Spec

UIContext 功能域：`specs/04-common-capability/12-ui-context/`

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| UIContext 入口架构与实例路由 | `specs/04-common-capability/12-ui-context/01-ui-context-interface/Feat-01-uicontext-entry-architecture-instance-routing-spec.md` | UIContext 入口点、实例路由、getUIContext() 链路 |
| UIContext 实例解析与作用域调度 | `specs/04-common-capability/12-ui-context/01-ui-context-interface/Feat-02-uicontext-instance-resolution-scoped-task-spec.md` | 实例解析、RunScopeUITask、作用域调度 |
| 子对象工厂与直接方法 | `specs/04-common-capability/12-ui-context/01-ui-context-interface/Feat-03-uicontext-sub-factory-direct-methods-spec.md` | UIContext 子工厂（Router、PromptAction、Animator、Measure 等）、直接方法 |
| C-API UIContextHandle 接口 | `specs/04-common-capability/12-ui-context/01-ui-context-interface/Feat-04-capi-uicontext-handle-spec.md` | ArkUI_ContextHandle、OH_ArkUI_GetContextByNode/FromNapiValue/FromAniValue |
| Ability 上下文与窗口信息 | `specs/04-common-capability/12-ui-context/02-ability-context/Feat-01-ability-context-window-info-spec.md` | AbilityContext、窗口信息、GetAbilityContext |
| Frame 回调与帧调度 | `specs/04-common-capability/12-ui-context/03-frame-callback/Feat-01-frame-callback-scheduling-spec.md` | OH_ArkUI_PostFrameCallback、PostIdleCallback、帧调度 |
| UIContext 接口设计文档 | `specs/04-common-capability/12-ui-context/01-ui-context-interface/design.md` | 整体架构设计 |
| Ability 上下文设计文档 | `specs/04-common-capability/12-ui-context/02-ability-context/design.md` | AbilityContext 架构设计 |
| Frame 回调设计文档 | `specs/04-common-capability/12-ui-context/03-frame-callback/design.md` | FrameCallback 架构设计 |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| UIContext 实例获取失败 | UIContext::Current() 链路、PipelineContext::GetCurrentContextSafelyWithCheck()、容器 instanceId |
| ArkUI_ContextHandle 无效（190001 错误） | ArkUI_Context.id 字段、OH_ArkUI_GetContextFromNapiValue/FromAniValue/GetContextByNode 的 instanceId 提取 |
| 子工厂方法（Router/PromptAction）不返回正确实例 | UIContextHelper 缓存、NAPI 子模块挂载逻辑、instanceId 路由 |
| 动态版子对象方法不路由到正确实例 | jsUIContext.js 的 withInstanceId(instanceId_) 守卫、globalThis.requireNapi 模块加载、instanceId 是否已从 uiContextMap_ 缓存 |
| 静态版子对象方法不路由到正确实例 | @ohos.arkui.UIContext.ts 的 Sync_InstanceId/Restore_InstanceId 守卫、ArkUIAniModule 调用、availableInstanceIds_ 校验 |
| isAvailable() 返回 false | 动态版 __availableInstanceIds__ / 静态版 UIContextUtil.availableInstanceIds_ / 容器销毁时 RemoveUIContext |
| FrameCallback 不执行 | OH_ArkUI_PostFrameCallback 实现、PipelineContext::AddCAPIFrameCallback、帧调度循环 |
| RunScopeUITask 不在 UI 线程执行 | OH_ArkUI_RunTaskInScope 实现、node_model_safely.cpp 作用域任务投递 |
| IUIContextAccessor 方法不生效 | iui_context_accessor.cpp 实现、GeneratedModifier namespace、accessor vtable 注册 |
| AbilityContext 获取失败 | AceContainer::GetAbilityContext()、UIContentImpl context_ 初始化时机 |

## 调试入口

- UIContext 实例断点：UIContext::Current()、PipelineContext::GetUIContext()、UIContextImpl 惰性创建
- ArkUI_ContextHandle 断点：OH_ArkUI_GetContextFromNapiValue/FromAniValue/GetContextByNode 的 instanceId 提取
- FrameCallback 断点：OH_ArkUI_PostFrameCallback、PipelineContext::AddCAPIFrameCallback/FlushFrameCallbackFromCAPI
- 作用域任务断点：OH_ArkUI_RunTaskInScope、node_model_safely.cpp 的 instanceId→PipelineContext 映射
- 子工厂挂载断点：UIContextHelper::GetUIContext、NAPI 子模块注册链路
- 动态版子对象路由断点：jsUIContext.js 的 withInstanceId(instanceId_) 包装、globalThis.requireNapi 模块加载
- 静态版子对象路由断点：@ohos.arkui.UIContext.ts 的 Sync_InstanceId/Restore_InstanceId、ArkUIAniModule 调用
- 实例可用性断点：UIContextUtil.ets availableInstanceIds_、UIContextHelper::RemoveUIContext 容器销毁回调

## 相关主题

- [路由管理：[docs/kb/api/router.md](../api/router.md)](../api/router.md)
- [MediaQuery：[docs/kb/api/mediaquery.md](../api/mediaquery.md)](../api/mediaquery.md)
- Ability 上下文与窗口信息：[docs/kb/capabilities/ability-context.md](ability-context.md)
- Frame 帧回调：[docs/kb/capabilities/frame-callback.md](frame-callback.md)
- [窗口机制：[docs/kb/architecture/window-mechanism.md](../architecture/window-mechanism.md)](../architecture/window-mechanism.md)
- [布局框架：[docs/kb/architecture/layout-framework.md](../architecture/layout-framework.md)](../architecture/layout-framework.md)
- [UIContext 实例 ID 泄漏](../issues/lifecycle/uicontext-instance-id-leak.md) — JS 前端历史配对问题（已修复）与 ANI/C API 路径排查要点