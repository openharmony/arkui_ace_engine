# Frame Callback Context

> 文档版本：v1.0
> 更新时间：2026-07-28
> 来源：`docs/context_registry.json` 主题 `FrameCallback`

## 定位

Frame Callback 是 UIContext 的子能力域，提供一次性帧回调（postFrameCallback / OH_ArkUI_PostFrameCallback）、延迟帧回调（postDelayedFrameCallback）和帧空闲回调（onIdle / OH_ArkUI_PostIdleCallback）机制。核心语义为 one-shot：回调在下一帧被执行后自动从列表移除，不会自动重注册。ArkTS 帧回调与 C-API 帧回调使用独立列表和独立 drain 函数，执行时序不同。

本文档只提供稳定的源码、API、测试和 Spec 路由。具体一次性语义、时序差异、MIN_IDLE_TIME 门槛等行为细节应回到当前源码、Spec 和测试核实。

## 快速路由

### 源码入口

| 关注点 | 稳定路径 | 说明 |
|--------|----------|------|
| PipelineContext 帧回调核心 | `frameworks/core/pipeline_ng/pipeline_context.h` | FrameCallbackFunc / FrameCallbackFuncFromCAPI / IdleCallbackFunc 类型定义；AddFrameCallback / FlushFrameCallback / AddCAPIFrameCallback / FlushFrameCallbackFromCAPI / TriggerIdleCallback 方法声明 |
| PipelineContext 帧回调实现 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | AddFrameCallback（立即/延迟注册）、FlushFrameCallback（std::swap drain）、FlushFrameCallbackFromCAPI（std::swap drain）、TriggerIdleCallback（MIN_IDLE_TIME 门槛 + std::move drain） |
| VSync 帧调度中回调时序 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | FlushVsync 中 FlushFrameCallback 在 FlushAnimation 后、FlushBuild 前执行（ArkTS）；FlushFrameCallbackFromCAPI 在 FlushTouchEvents 后、FlushBuild 前执行（C-API） |
| 动态版前端桥接 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | postFrameCallback / postDelayedFrameCallback → getUINativeModule().common.postFrameCallback |
| 静态版前端桥接 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | postFrameCallback → ArkUIAniModule._SetFrameCallback |
| JSI 桥接层 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | SetFrameCallback 原生操作：解析 FrameCallback 参数，提取 onFrame/onIdle → PipelineContext::AddFrameCallback |
| C-API 实现 | `interfaces/native/node/native_node_napi.cpp` | OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback：参数校验 + 线程安全检查 + AddCAPIFrameCallback / AddFrameCallback |
| C-API node_api | `frameworks/core/interfaces/native/node/node_api.cpp` | C-API 帧回调辅助实现：AddCAPIFrameCallback 调用 |
| C-API 声明 | `interfaces/native/native_node_napi.h` | OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback 函数声明 |
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | Kit::UIContext::PostFrameCallback 薄包装 PipelineContext::AddFrameCallback |
| Kit 实现 | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.cpp` | UIContextImpl::PostFrameCallback 实现 |
| OH_ArkUI_RunTaskInScope | `interfaces/native/node/node_utils.cpp` | C-API 作用域任务执行 |
| OH_ArkUI_PostUITask | `interfaces/native/node/node_model_safely.cpp`（如存在）或相关实现文件 | C-API 作用域任务投递 |

### API 入口

| 范式 | 稳定路径 | 说明 |
|------|----------|------|
| 动态版 API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.d.ts` | postFrameCallback / postDelayedFrameCallback / FrameCallback 类 |
| 静态版 API 声明 | `<OH_ROOT>/interface/sdk-js/api/@ohos.arkui.UIContext.static.d.ets` | 同上，FrameCallback 参数类型为 long（而非 number） |
| C-API 声明 | `interfaces/native/native_node_napi.h` | OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback |
| Kit 层 | `interfaces/inner_api/ace_kit/include/ui/view/ui_context.h` | Kit::UIContext::PostFrameCallback |

### 接口实现路径总览

| 范式 | 入口文件 | 实例路由守卫 | 说明 |
|------|----------|--------------|------|
| 动态版 | `frameworks/bridge/declarative_frontend/engine/jsUIContext.js` | `withInstanceId(instanceId_)` | postFrameCallback → getUINativeModule().common.postFrameCallback → SetFrameCallback |
| 静态版 | `frameworks/bridge/arkts_frontend/koala_projects/arkoala-arkts/arkui-ohos/@ohos.arkui.UIContext.ts` | `Sync_InstanceId(instanceId_)` + `Restore_InstanceId()` | postFrameCallback → ArkUIAniModule._SetFrameCallback |
| JSI 桥接 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | Container::Current() → PipelineContext | 解析 FrameCallback → AddFrameCallback |
| C-API | `interfaces/native/node/native_node_napi.cpp` | ArkUI_ContextHandle.id → PipelineContext | AddCAPIFrameCallback / AddFrameCallback；CheckThreadSafe() 线程检查 |
| Kit 层 | `interfaces/inner_api/ace_kit/src/view/ui_context_impl.cpp` | PipelineContext::Current() | PostFrameCallback → AddFrameCallback |

**关键架构约束**：

- ArkTS 帧回调与 C-API 帧回调使用独立列表（frameCallbackFuncs_ vs frameCallbackFuncsFromCAPI_），独立 drain（FlushFrameCallback vs FlushFrameCallbackFromCAPI），时序不同
- ArkTS 帧回调在 FlushAnimation 后执行，C-API 帧回调在 FlushTouchEvents 后、FlushBuild 前执行
- 所有回调均为一次性语义（std::swap / std::move drain），执行后从列表移除
- 空闲回调有 MIN_IDLE_TIME (1μs) 门槛，剩余空闲时间不足时推迟到下一帧（注：Spec 文档标注 1ms，实际源码值为 1000ns = 1μs）
- 延迟帧回调基于 PostDelayedTask，延迟到期后加入帧回调列表 + RequestFrame
- C-API 必须在 UI 线程调用，非 UI 线程返回错误码或触发 LOGF_ABORT

### 外部依赖入口

| 依赖方向 | 本仓入口 | 外部仓 | 说明 |
|----------|----------|--------|------|
| VSync 接收与帧调度 | `frameworks/core/pipeline_ng/pipeline_context.cpp` | `graphic_2d` | RSUIDirector 接收 VSync 信号 → FlushVsync → FlushFrameCallback / FlushFrameCallbackFromCAPI；RSTransaction 批量提交渲染指令 |
| Window VSync 请求 | `frameworks/core/pipeline_ng/pipeline_context.h`（通过 window_ 成员） | `window_manager` | Window::RequestVsync() 触发下一帧；Window::GetRSUIDirector() 获取 VSync 回调链；Window::GetVSyncPeriod() 提供帧周期 |
| JSI 回调桥接 | `frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.cpp` | `ets_runtime` | EcmaVM / ark_native_engine 用于将用户 onFrame/onIdle JS 回调包装为 FrameCallbackFunc / IdleCallbackFunc lambda |
| C-API 导出基础设施 | `interfaces/native/node/native_node_napi.cpp` | `napi` | NAPI 模块系统承载 OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback 导出 |

### 测试入口

| 类型 | 稳定路径 | 用途 |
|------|----------|------|
| C-API 帧回调单测 | `test/unittest/interfaces/native_node_napi_test.cpp` | OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback 参数校验、线程安全 |
| C-API Handle 单测 | `test/unittest/interfaces/native_node_test.cpp` | OH_ArkUI_GetContextByNode、RunTaskInScope |
| UIContextImpl 单测 | `test/unittest/interfaces/ace_kit/ui_context_impl_test.cpp` | Kit 层 PostFrameCallback 相关测试 |

### 相关 Spec

| 文档 | 稳定路径 | 覆盖范围 |
|------|----------|----------|
| Frame 回调与动画调度 Spec | `specs/04-common-capability/12-ui-context/03-frame-callback/Feat-01-frame-callback-scheduling-spec.md` | postFrameCallback / postDelayedFrameCallback / FrameCallback / OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback / 一次性语义 / 时序差异 / MIN_IDLE_TIME |
| Frame 回调设计文档 | `specs/04-common-capability/12-ui-context/03-frame-callback/design.md` | 架构设计、调用链层级分析、关键设计决策（ADR-1~6） |

## 常见问题定位

| 问题 | 优先查看 |
|------|----------|
| 帧回调不执行（只执行一次后不再触发） | 一次性语义（std::swap drain）；开发者需每帧重新调用 postFrameCallback |
| ArkTS 帧回调与 C-API 帧回调时序不同 | FlushVsync 中 FlushFrameCallback 在 FlushAnimation 后（ArkTS），FlushFrameCallbackFromCAPI 在 FlushTouchEvents 后（C-API） |
| onIdle 回调不执行 | MIN_IDLE_TIME (1μs) 门槛；剩余空闲时间 < 1μs 时推迟到下一帧 + RequestFrame |
| OH_ArkUI_PostFrameCallback 返回错误码 | nullptr uiContext → ARKUI_ERROR_CODE_UI_CONTEXT_INVALID；nullptr callback → ARKUI_ERROR_CODE_CALLBACK_INVALID；非 UI 线程 → ERROR_CODE_NATIVE_IMPL_NOT_MAIN_THREAD |
| postDelayedFrameCallback delayTime ≤ 0 | 等效于 postFrameCallback（立即注册到帧回调列表） |
| postDelayedFrameCallback 延迟精度不够 | 延迟基于 PostDelayedTask + RequestFrame，实际执行在延迟到期后的下一个 VSync 帧 |
| PipelineContext 销毁后延迟回调不执行 | WeakClaim(this) 弱引用保护；Upgrade() 返回 nullptr 时回调不执行 |
| frameCount == UINT64_MAX 时帧回调不执行 | recover vsync 场景：仅 RequestFrame，不执行回调 |

## 调试入口

- 帧回调注册断点：PipelineContext::AddFrameCallback（立即注册）、AddCAPIFrameCallback（C-API 注册）
- 帧回调执行断点：PipelineContext::FlushFrameCallback（ArkTS drain）、FlushFrameCallbackFromCAPI（C-API drain）
- 空闲回调断点：PipelineContext::TriggerIdleCallback（MIN_IDLE_TIME 检查 + std::move drain）
- 延迟回调断点：PipelineContext::AddFrameCallback delayMillis > 0 分支 → PostDelayedTask → WeakClaim
- JSI 桥接断点：arkts_native_common_bridge.cpp SetFrameCallback 原生操作
- C-API 断点：native_node_napi.cpp OH_ArkUI_PostFrameCallback / OH_ArkUI_PostIdleCallback
- VSync 时序断点：PipelineContext::FlushVsync 中各 Flush 阶段顺序

## 相关主题

- UIContext 入口架构：`docs/kb/capabilities/ui-context.md`
- Ability 上下文与窗口信息：`docs/kb/capabilities/ability-context.md`
- [动效框架：`docs/kb/capabilities/animation-framework.md`](animation-framework.md)
- 渲染管线：`docs/kb/architecture/basic-render-pipeline.md`
- [窗口机制：`docs/kb/architecture/window-mechanism.md`](../architecture/window-mechanism.md)
- [UIContext 实例 ID 泄漏](../issues/lifecycle/uicontext-instance-id-leak.md) — JS 前端历史配对问题（已修复）与帧回调实例路由排查