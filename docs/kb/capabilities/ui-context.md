# UIContext Context

> 文档版本：v1.0
> 更新时间：2026-07-24
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

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | UIContext 报象基类 |
| C API Handle | `interfaces/native/native_type.h` | ArkUI_ContextHandle 定义 |
| C API 方法 | `interfaces/native/native_node.h` | OH_ArkUI_GetContextByNode、OH_ArkUI_RunTaskInScope、OH_ArkUI_PostUITask/PostUITaskAndWait/PostAsyncUITask |
| NAPI 桥接 | `interfaces/native/native_node_napi.h` | OH_ArkUI_GetContextFromNapiValue、OH_ArkUI_PostFrameCallback、OH_ArkUI_PostIdleCallback |
| ANI 桥接 | `interfaces/native/native_node_ani.h` | OH_ArkUI_NativeModule_GetContextFromAniValue |
| 动态版 IDL | `frameworks/bridge/arkts_frontend/arkoala_generator/arkui_extra_idl/arkui-iuicontext.idl` | 静态版 IUIContext IDL |
| NAPI 子模块挂载 | `interfaces/napi/kits/` | 31 个子模块目录（Router、PromptAction、Animator、Measure、Observer 等） |

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓路径 | 说明 |
|----------|----------|------------|------|
| AbilityContext | `adapter/ohos/entrance/ace_container.h` | `ability_runtime` | AceContainer::GetAbilityContext() 获取 OHOS AbilityRuntime::Context |
| UIContent→AbilityContext | `adapter/ohos/entrance/ui_content_impl.cpp` | `ability_runtime` | UIContentImpl 持有 AbilityRuntime::Context，通过 Context::ConvertTo<AbilityContext> 转换 |
| Preview Context | `adapter/preview/external/ability/context.h` | preview stub | Preview 版本的 Context 空实现 |
| Rosen 渲染 | `frameworks/core/components_ng/render/adapter/rosen_render_context.h` | `graphic_2d` | RS 渲染上下文绑定 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| UIContextImpl 单测 | `test/unittest/interfaces/ace_kit/ui_context_impl_test.cpp` | UIContextImpl 947 行测试；GetFontScale、GetColorMode、GetOverlayManager、RequestFrame、GetApiTargetVersion、RegisterSurfaceChangedCallback 等 |
| Mock UIContextImpl | `test/mock/interfaces/inner_api/ace_kit/view/mock_ui_context_impl.cpp` | Host 测试替身；UIContextImpl 所有方法的 stub 实现 |
| C API Handle 测试 | `test/unittest/interfaces/native_node_napi_test.cpp` | OH_ArkUI_GetContextFromNapiValue、OH_ArkUI_PostFrameCallback/PostIdleCallback |
| C API Node Handle 测试 | `test/unittest/interfaces/native_node_test.cpp` | OH_ArkUI_GetContextByNode、RunTaskInScope、PostUITask |
| AtomicServiceBar accessor | `test/unittest/capi/accessors/ui_context_atomic_service_bar_accessor_test.cpp` | UIContextAtomicServiceBarAccessor C API accessor |
| Animate C API 测试 | `test/unittest/interfaces/node_animate_test.cpp` | animateTo/keyframeAnimateTo/createAnimator 通过 ArkUI_ContextHandle |
| Drag C API 测试 | `test/unittest/interfaces/drag_and_drop_test.cpp` | Drag C API 通过 ArkUI_ContextHandle |

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

## 相关主题

- 路由管理：`docs/kb/api/router.md`
- 窗口机制：`docs/kb/architecture/window-mechanism.md`
- 布局框架：`docs/kb/architecture/layout-framework.md`
