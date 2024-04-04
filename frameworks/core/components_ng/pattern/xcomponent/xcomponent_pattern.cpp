/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

#include "interfaces/native/native_event.h"
#include "interfaces/native/event/ui_input_event_impl.h"

#include "base/geometry/ng/size_t.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/event/axis_event.h"
#ifdef NG_BUILD
#include "bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#else
#include "bridge/declarative_frontend/declarative_frontend.h"
#endif
#ifdef ENABLE_ROSEN_BACKEND
#include "transaction/rs_transaction_proxy.h"
#include "ui/rs_ext_node_operation.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif

#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
#ifdef OHOS_PLATFORM
constexpr int64_t INCREASE_CPU_TIME_ONCE = 4000000000; // 4s(unit: ns)
#endif
OH_NativeXComponent_TouchEventType ConvertNativeXComponentTouchEvent(const TouchType& touchType)
{
    switch (touchType) {
        case TouchType::DOWN:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_DOWN;
        case TouchType::UP:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP;
        case TouchType::MOVE:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_MOVE;
        case TouchType::CANCEL:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_CANCEL;
        default:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
    }
}

OH_NativeXComponent_TouchPointToolType ConvertNativeXComponentTouchToolType(const SourceTool& toolType)
{
    switch (toolType) {
        case SourceTool::FINGER:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER;
        case SourceTool::PEN:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN;
        case SourceTool::RUBBER:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER;
        case SourceTool::BRUSH:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH;
        case SourceTool::PENCIL:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL;
        case SourceTool::AIRBRUSH:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH;
        case SourceTool::MOUSE:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE;
        case SourceTool::LENS:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS;
        default:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    }
}

OH_NativeXComponent_KeyAction ConvertNativeXComponentKeyAction(const KeyAction& keyAction)
{
    switch (keyAction) {
        case KeyAction::DOWN:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN;
        case KeyAction::UP:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UP;
        default:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    }
}

OH_NativeXComponent_EventSourceType ConvertNativeXComponentEventSourceType(const SourceType& sourceType)
{
    switch (sourceType) {
        case SourceType::MOUSE:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE;
        case SourceType::TOUCH:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN;
        case SourceType::TOUCH_PAD:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD;
        case SourceType::KEYBOARD:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD;
        default:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    }
}

OH_NativeXComponent_KeyEvent ConvertNativeXComponentKeyEvent(const KeyEvent& event)
{
    OH_NativeXComponent_KeyEvent nativeKeyEvent;
    nativeKeyEvent.action = ConvertNativeXComponentKeyAction(event.action);
    nativeKeyEvent.code = static_cast<OH_NativeXComponent_KeyCode>(event.code);
    nativeKeyEvent.sourceType = ConvertNativeXComponentEventSourceType(event.sourceType);
    nativeKeyEvent.deviceId = event.deviceId;
    nativeKeyEvent.timestamp = event.timeStamp.time_since_epoch().count();
    return nativeKeyEvent;
}
} // namespace

XComponentPattern::XComponentPattern(const std::string& id, XComponentType type,
    const std::shared_ptr<InnerXComponentController>& xcomponentController, float initWidth, float initHeight)
    : id_(id), type_(type), xcomponentController_(xcomponentController), initSize_(initWidth, initHeight)
{}

XComponentPattern::XComponentPattern(const std::string& id, XComponentType type, const std::string& libraryname,
    const std::shared_ptr<InnerXComponentController>& xcomponentController, float initWidth, float initHeight)
    : XComponentPattern(id, type, xcomponentController, initWidth, initHeight)
{
    SetLibraryName(libraryname);
}

void XComponentPattern::Initialize(int32_t instanceId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    instanceId_ = (instanceId <= 0) ? Container::CurrentIdSafely() : instanceId;
    auto renderContext = host->GetRenderContext();
    if (type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE) {
        renderContext->SetClipToFrame(true);
        renderContext->SetClipToBounds(true);
#ifdef RENDER_EXTRACT_SUPPORTED
        renderSurface_ = RenderSurface::Create(CovertToRenderSurfaceType(type_));
#else
        renderSurface_ = RenderSurface::Create();
#endif
        renderSurface_->SetInstanceId(instanceId_);
        if (type_ == XComponentType::SURFACE) {
            InitializeRenderContext();
            if (!SystemProperties::GetExtSurfaceEnabled()) {
                renderSurface_->SetRenderContext(renderContextForSurface_);
            } else {
                auto pipelineContext = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->AddOnAreaChangeNode(host->GetId());
                extSurfaceClient_ = MakeRefPtr<XComponentExtSurfaceCallbackClient>(WeakClaim(this));
                renderSurface_->SetExtSurfaceCallback(extSurfaceClient_);
#ifdef RENDER_EXTRACT_SUPPORTED
                RegisterRenderContextCallBack();
#endif
            }
            handlingSurfaceRenderContext_ = renderContextForSurface_;
        } else if (type_ == XComponentType::TEXTURE) {
            renderSurface_->SetRenderContext(renderContext);
            renderSurface_->SetIsTexture(true);
        }
        auto* controllerNG = static_cast<XComponentControllerNG*>(xcomponentController_.get());
        if (controllerNG) {
            controllerNG->SetPattern(AceType::Claim(this));
        }
        renderSurface_->InitSurface();
        renderSurface_->UpdateSurfaceConfig();
        surfaceId_ = renderSurface_->GetUniqueId();
        InitEvent();
        SetMethodCall();
    } else if (type_ == XComponentType::NODE) {
        auto context = PipelineContext::GetCurrentContext();
        if (context) {
            FireExternalEvent(context, id_, host->GetId(), false);
            InitNativeNodeCallbacks();
        }
    }
}

void XComponentPattern::InitializeRenderContext()
{
    renderContextForSurface_ = RenderContext::Create();
#ifdef RENDER_EXTRACT_SUPPORTED
    auto contextType = type_ == XComponentType::TEXTURE ?
        RenderContext::ContextType::HARDWARE_TEXTURE : RenderContext::ContextType::HARDWARE_SURFACE;
    static RenderContext::ContextParam param = { contextType, id_ + "Surface" };
#else
    static RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE, id_ + "Surface" };
#endif

    renderContextForSurface_->InitContext(false, param);

    renderContextForSurface_->UpdateBackgroundColor(Color::BLACK);
}

#ifdef RENDER_EXTRACT_SUPPORTED
RenderSurface::RenderSurfaceType XComponentPattern::CovertToRenderSurfaceType(const XComponentType& hostType)
{
    switch (hostType) {
        case XComponentType::SURFACE:
            return RenderSurface::RenderSurfaceType::SURFACE;
        case XComponentType::TEXTURE:
            return RenderSurface::RenderSurfaceType::TEXTURE;
        default:
            return RenderSurface::RenderSurfaceType::UNKNOWN;
    }
}

void XComponentPattern::RegisterRenderContextCallBack()
{
    CHECK_NULL_VOID(renderContextForSurface_);
    auto OnAreaChangedCallBack = [weak = WeakClaim(this)](float x, float y, float w, float h) mutable {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto xcomponentNodeSize = geometryNode->GetContentSize();
        auto xcomponentNodeOffset = geometryNode->GetContentOffset();
        auto transformRelativeOffset = host->GetTransformRelativeOffset();
        Rect rect = Rect(transformRelativeOffset.GetX() + xcomponentNodeOffset.GetX(),
            transformRelativeOffset.GetY() + xcomponentNodeOffset.GetY(), xcomponentNodeSize.Width(),
            xcomponentNodeSize.Height());
        if (pattern->renderSurface_) {
            pattern->renderSurface_->SetExtSurfaceBoundsSync(rect.Left(), rect.Top(),
                rect.Width(), rect.Height());
        }
    };
    renderContextForSurface_->SetSurfaceChangedCallBack(OnAreaChangedCallBack);
}

void XComponentPattern::RequestFocus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->RequestFocusImmediately();
}
#endif

void XComponentPattern::OnAttachToFrameNode()
{
    instanceId_ = Container::CurrentIdSafely();
    Initialize(instanceId_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
}

void XComponentPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto bkColor = renderContext->GetBackgroundColor();
    if (bkColor.has_value() && handlingSurfaceRenderContext_) {
        handlingSurfaceRenderContext_->UpdateBackgroundColor(Color::TRANSPARENT);
    }
}

void XComponentPattern::OnAreaChangedInner()
{
#ifndef RENDER_EXTRACT_SUPPORTED
    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto xcomponentNodeSize = geometryNode->GetContentSize();
        auto xcomponentNodeOffset = geometryNode->GetContentOffset();
        auto transformRelativeOffset = host->GetTransformRelativeOffset();
        renderSurface_->SetExtSurfaceBounds(transformRelativeOffset.GetX() + xcomponentNodeOffset.GetX(),
            transformRelativeOffset.GetY() + xcomponentNodeOffset.GetY(), xcomponentNodeSize.Width(),
            xcomponentNodeSize.Height());
    }
#endif
}

void XComponentPattern::SetSurfaceNodeToGraphic()
{
#ifdef ENABLE_ROSEN_BACKEND
    if (type_ != XComponentType::SURFACE || !Rosen::RSExtNodeOperation::GetInstance().CheckNeedToProcess(GetId())) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    std::shared_ptr<Rosen::RSNode> parentNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_VOID(parentNode);
    RectF canvasRect = rosenRenderContext->GetPropertyOfPosition();

    CHECK_NULL_VOID(renderContextForSurface_);
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(renderContextForSurface_);
    CHECK_NULL_VOID(context);
    std::shared_ptr<Rosen::RSNode> rsNode = context->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    std::shared_ptr<Rosen::RSSurfaceNode> rsSurfaceNode = std::static_pointer_cast<Rosen::RSSurfaceNode>(rsNode);
    CHECK_NULL_VOID(rsSurfaceNode);

    Rosen::RSExtNodeOperation::GetInstance().ProcessRSExtNode(GetId(), parentNode->GetId(),
        canvasRect.GetX(), canvasRect.GetY(), rsSurfaceNode);
#endif
}

void XComponentPattern::OnRebuildFrame()
{
    if (type_ != XComponentType::SURFACE) {
        return;
    }
    if (!renderSurface_->IsSurfaceValid()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(handlingSurfaceRenderContext_);
    renderContext->AddChild(handlingSurfaceRenderContext_, 0);
    SetSurfaceNodeToGraphic();
}

void XComponentPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    if (!hasXComponentInit_) {
        return;
    }
    if (type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE) {
        NativeXComponentDestroy();
        auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireDestroyEvent();
        eventHub->FireDetachEvent(id_);
        eventHub->FireControllerDestroyedEvent(surfaceId_);
#ifdef RENDER_EXTRACT_SUPPORTED
        if (renderContextForSurface_) {
            renderContextForSurface_->RemoveSurfaceChangedCallBack();
        }
#endif
    }

    auto id = frameNode->GetId();
    auto pipeline = AceType::DynamicCast<PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
}

void XComponentPattern::SetMethodCall()
{
    CHECK_NULL_VOID(xcomponentController_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    xcomponentController_->SetConfigSurfaceImpl(
        [weak = WeakClaim(this), uiTaskExecutor](uint32_t surfaceWidth, uint32_t surfaceHeight) {
            uiTaskExecutor.PostSyncTask([weak, surfaceWidth, surfaceHeight]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->ConfigSurface(surfaceWidth, surfaceHeight);
            });
        });

    xcomponentController_->SetSurfaceId(surfaceId_);
}

void XComponentPattern::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
{
    renderSurface_->ConfigSurface(surfaceWidth, surfaceHeight);
}

bool XComponentPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (type_ == XComponentType::COMPONENT || type_ == XComponentType::NODE
        || config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    drawSize_ = geometryNode->GetContentSize();
    if (!drawSize_.IsPositive()) {
        return false;
    }
    globalPosition_ = geometryNode->GetFrameOffset();
    localPosition_ = geometryNode->GetContentOffset();

    if (IsSupportImageAnalyzerFeature()) {
        UpdateAnalyzerUIConfig(dirty->GetGeometryNode());
    }

    if (!hasXComponentInit_) {
        initSize_ = drawSize_;
        if (!SystemProperties::GetExtSurfaceEnabled()) {
            XComponentSizeInit();
        }
        auto offset = globalPosition_ + localPosition_;
        NativeXComponentOffset(offset.GetX(), offset.GetY());
        hasXComponentInit_ = true;
    }
#ifndef RENDER_EXTRACT_SUPPORTED
    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        auto transformRelativeOffset = host->GetTransformRelativeOffset();
        renderSurface_->SetExtSurfaceBounds(
            static_cast<int32_t>(transformRelativeOffset.GetX() + localPosition_.GetX()),
            static_cast<int32_t>(transformRelativeOffset.GetY() + localPosition_.GetY()),
            static_cast<int32_t>(drawSize_.Width()), static_cast<int32_t>(drawSize_.Height()));
    }
#endif
    UpdateSurfaceBounds(false, config.frameOffsetChange);
    // XComponentType::SURFACE has set surface default size in RSSurfaceNode->SetBounds()
    if (type_ == XComponentType::TEXTURE) {
        renderSurface_->SetSurfaceDefaultSize(
            static_cast<int32_t>(drawSize_.Width()), static_cast<int32_t>(drawSize_.Height()));
    }
    if (type_ == XComponentType::SURFACE && renderType_ == NodeRenderType::RENDER_TYPE_TEXTURE) {
        AddAfterLayoutTaskForExportTexture();
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkNeedSyncRenderTree();
    return false;
}

void XComponentPattern::OnPaint()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::BLACK);
}

void XComponentPattern::NativeXComponentChange(float width, float height)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    nativeXComponentImpl_->SetXComponentWidth(static_cast<int32_t>(width));
    nativeXComponentImpl_->SetXComponentHeight(static_cast<int32_t>(height));
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto* callback = nativeXComponentImpl_->GetCallback();
    CHECK_NULL_VOID(callback);
    CHECK_NULL_VOID(callback->OnSurfaceChanged);
    callback->OnSurfaceChanged(nativeXComponent_.get(), surface);
#ifdef RENDER_EXTRACT_SUPPORTED
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
#endif
}

void XComponentPattern::NativeXComponentDestroy()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto* callback = nativeXComponentImpl_->GetCallback();
    CHECK_NULL_VOID(callback);
    CHECK_NULL_VOID(callback->OnSurfaceDestroyed);
    callback->OnSurfaceDestroyed(nativeXComponent_.get(), surface);
}

void XComponentPattern::NativeXComponentOffset(double x, double y)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    float scale = pipelineContext->GetViewScale();
    nativeXComponentImpl_->SetXComponentOffsetX(x * scale);
    nativeXComponentImpl_->SetXComponentOffsetY(y * scale);
}

void XComponentPattern::NativeXComponentDispatchTouchEvent(
    const OH_NativeXComponent_TouchEvent& touchEvent, const std::vector<XComponentTouchPoint>& xComponentTouchPoints)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    nativeXComponentImpl_->SetTouchEvent(touchEvent);
    nativeXComponentImpl_->SetTouchPoint(xComponentTouchPoints);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto* callback = nativeXComponentImpl_->GetCallback();
    CHECK_NULL_VOID(callback);
    CHECK_NULL_VOID(callback->DispatchTouchEvent);
    callback->DispatchTouchEvent(nativeXComponent_.get(), surface);
}

void XComponentPattern::InitNativeWindow(float textureWidth, float textureHeight)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (renderSurface_->IsSurfaceValid() && (type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE)) {
        float viewScale = context->GetViewScale();
        renderSurface_->CreateNativeWindow();
        renderSurface_->AdjustNativeWindowSize(
            static_cast<uint32_t>(textureWidth * viewScale), static_cast<uint32_t>(textureHeight * viewScale));
    }
}

void XComponentPattern::XComponentSizeInit()
{
    CHECK_RUN_ON(UI);
    ContainerScope scope(instanceId_);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    InitNativeWindow(initSize_.Width(), initSize_.Height());
#ifdef RENDER_EXTRACT_SUPPORTED
    if (xcomponentController_ && renderSurface_) {
        xcomponentController_->SetSurfaceId(renderSurface_->GetUniqueId());
    }
#endif
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireSurfaceInitEvent(id_, host->GetId());
    eventHub->FireLoadEvent(id_);
    eventHub->FireControllerCreatedEvent(surfaceId_);
}

void XComponentPattern::XComponentSizeChange(const RectF& surfaceRect, bool needFireNativeEvent)
{
    // do not trigger when the size is first initialized
    if (needFireNativeEvent) {
        ContainerScope scope(instanceId_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto viewScale = context->GetViewScale();
        renderSurface_->AdjustNativeWindowSize(static_cast<uint32_t>(surfaceRect.Width() * viewScale),
            static_cast<uint32_t>(surfaceRect.Height() * viewScale));
        NativeXComponentChange(surfaceRect.Width(), surfaceRect.Height());
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireControllerChangedEvent(surfaceId_, surfaceRect);
}

void XComponentPattern::InitNativeNodeCallbacks()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    nativeXComponentImpl_->registerContaner(AceType::RawPtr(host));

    auto OnAttachRootNativeNode = [](void* container, void* root) {
        ContainerScope scope(Container::CurrentIdSafely());
        auto node = AceType::Claim(reinterpret_cast<NG::FrameNode*>(root));
        CHECK_NULL_VOID(node);
        auto host = AceType::Claim(reinterpret_cast<NG::FrameNode*>(container));
        CHECK_NULL_VOID(host);
        host->AddChild(node);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };

    auto OnDetachRootNativeNode = [](void* container, void* root) {
        ContainerScope scope(Container::CurrentIdSafely());
        auto node = AceType::Claim(reinterpret_cast<NG::FrameNode*>(root));
        CHECK_NULL_VOID(node);
        auto host = AceType::Claim(reinterpret_cast<NG::FrameNode*>(container));
        CHECK_NULL_VOID(host);
        host->RemoveChild(node);
    };

    nativeXComponentImpl_->registerNativeNodeCallbacks(std::move(OnAttachRootNativeNode),
        std::move(OnDetachRootNativeNode));
}

void XComponentPattern::InitEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSurfaceInitEvent(CreateExternalEvent());
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitTouchEvent(gestureHub);
    InitOnTouchIntercept(gestureHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    InitMouseEvent(inputHub);
    InitAxisEvent(inputHub);
    InitMouseHoverEvent(inputHub);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
}

void XComponentPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
#ifdef RENDER_EXTRACT_SUPPORTED
    focusHub->SetFocusable(true);
#endif

    auto onFocusEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        return pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(std::move(onFocusEvent));

    auto onKeyEvent = [weak = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->HandleKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto onBlurEvent = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        return pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(std::move(onBlurEvent));
}
void XComponentPattern::HandleFocusEvent()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto focusEventCallback = nativeXComponentImpl_->GetFocusEventCallback();
    CHECK_NULL_VOID(focusEventCallback);
    focusEventCallback(nativeXComponent_.get(), surface);
}

bool XComponentPattern::HandleKeyEvent(const KeyEvent& event)
{
    CHECK_NULL_RETURN(nativeXComponent_, false);
    CHECK_NULL_RETURN(nativeXComponentImpl_, false);

    OH_NativeXComponent_KeyEvent keyEvent = ConvertNativeXComponentKeyEvent(event);
    nativeXComponentImpl_->SetKeyEvent(keyEvent);

    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto keyEventCallback = nativeXComponentImpl_->GetKeyEventCallback();
    CHECK_NULL_RETURN(keyEventCallback, false);
    keyEventCallback(nativeXComponent_.get(), surface);
    return false;
}

void XComponentPattern::HandleBlurEvent()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto blurEventCallback = nativeXComponentImpl_->GetBlurEventCallback();
    CHECK_NULL_VOID(blurEventCallback);
    blurEventCallback(nativeXComponent_.get(), surface);
}

void XComponentPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!touchEvent_);

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };

    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void XComponentPattern::InitAxisEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(!axisEvent_);

    auto axisTask = [weak = WeakClaim(this)](const AxisInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleAxisEvent(info);
    };

    axisEvent_ = MakeRefPtr<InputEvent>(std::move(axisTask));
    inputHub->AddOnAxisEvent(axisEvent_);
}

void XComponentPattern::InitOnTouchIntercept(const RefPtr<GestureEventHub>& gestureHub)
{
    gestureHub->SetOnTouchIntercept(
        [pattern = Claim(this)](
            const TouchEventInfo& touchEvent) -> HitTestMode {
            auto event = touchEvent.ConvertToTouchEvent();
            ArkUI_UIInputEvent uiEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, &event };
            const auto onTouchInterceptCallback = pattern->nativeXComponentImpl_->GetOnTouchInterceptCallback();
            CHECK_NULL_RETURN(onTouchInterceptCallback, NG::HitTestMode::HTMDEFAULT);
            return static_cast<NG::HitTestMode>(onTouchInterceptCallback(pattern->nativeXComponent_.get(), &uiEvent));
        });
}

void XComponentPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(!mouseEvent_);

    auto mouseTask = [weak = WeakClaim(this)](const MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };

    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void XComponentPattern::InitMouseHoverEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(!mouseHoverEvent_);
    auto mouseHoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseHoverEvent(isHover);
    };
    mouseHoverEvent_ = MakeRefPtr<InputEvent>(std::move(mouseHoverTask));
    inputHub->AddOnHoverEvent(mouseHoverEvent_);
}

void XComponentPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchInfoList = info.GetChangedTouches();
    if (touchInfoList.empty()) {
        return;
    }
    const auto& touchInfo = touchInfoList.front();
    const auto& screenOffset = touchInfo.GetGlobalLocation();
    const auto& localOffset = touchInfo.GetLocalLocation();
    touchEventPoint_.id = touchInfo.GetFingerId();
    touchEventPoint_.screenX = static_cast<float>(screenOffset.GetX());
    touchEventPoint_.screenY = static_cast<float>(screenOffset.GetY());
    touchEventPoint_.x = static_cast<float>(localOffset.GetX());
    touchEventPoint_.y = static_cast<float>(localOffset.GetY());
    touchEventPoint_.size = touchInfo.GetSize();
    touchEventPoint_.force = touchInfo.GetForce();
    touchEventPoint_.deviceId = touchInfo.GetTouchDeviceId();
    const auto timeStamp = info.GetTimeStamp().time_since_epoch().count();
    touchEventPoint_.timeStamp = timeStamp;
    auto touchType = touchInfoList.front().GetTouchType();
    touchEventPoint_.type = ConvertNativeXComponentTouchEvent(touchType);
#ifdef OHOS_PLATFORM
    // increase cpu frequency
    if (touchType == TouchType::MOVE) {
        auto currentTime = GetSysTimestamp();
        auto increaseCpuTime = currentTime - startIncreaseTime_;
        if (increaseCpuTime >= INCREASE_CPU_TIME_ONCE) {
            startIncreaseTime_ = currentTime;
            ResSchedReport::GetInstance().ResSchedDataReport("slide_on");
        }
    } else if (touchType == TouchType::UP) {
        startIncreaseTime_ = 0;
        ResSchedReport::GetInstance().ResSchedDataReport("slide_off");
    }
#endif
    SetTouchPoint(info.GetTouches(), timeStamp, touchType);

    if (nativeXComponent_ && nativeXComponentImpl_) {
        nativeXComponentImpl_->SetHistoricalPoint(SetHistoryPoint(info.GetHistory()));
        nativeXComponentImpl_->SetCurrentSourceType(
            { touchInfo.GetFingerId(), ConvertNativeXComponentEventSourceType(info.GetSourceDevice()) });
    }
    NativeXComponentDispatchTouchEvent(touchEventPoint_, nativeXComponentTouchPoints_);

#ifdef RENDER_EXTRACT_SUPPORTED
    if (touchType == TouchType::DOWN) {
        RequestFocus();
    }
#endif
}

void XComponentPattern::HandleMouseEvent(const MouseInfo& info)
{
    OH_NativeXComponent_MouseEvent mouseEventPoint;
    mouseEventPoint.x = static_cast<float>(info.GetLocalLocation().GetX());
    mouseEventPoint.y = static_cast<float>(info.GetLocalLocation().GetY());
    mouseEventPoint.screenX = static_cast<float>(info.GetScreenLocation().GetX());
    mouseEventPoint.screenY = static_cast<float>(info.GetScreenLocation().GetY());
    switch (info.GetAction()) {
        case MouseAction::PRESS:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_PRESS;
            break;
        case MouseAction::RELEASE:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_RELEASE;
            break;
        case MouseAction::MOVE:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_MOVE;
            break;
        default:
            mouseEventPoint.action = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_NONE;
            break;
    }
    switch (info.GetButton()) {
        case MouseButton::LEFT_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_LEFT_BUTTON;
            break;
        case MouseButton::RIGHT_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_RIGHT_BUTTON;
            break;
        case MouseButton::MIDDLE_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_MIDDLE_BUTTON;
            break;
        case MouseButton::BACK_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_BACK_BUTTON;
            break;
        case MouseButton::FORWARD_BUTTON:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_FORWARD_BUTTON;
            break;
        default:
            mouseEventPoint.button = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON;
            break;
    }
    mouseEventPoint.timestamp = info.GetTimeStamp().time_since_epoch().count();
    NativeXComponentDispatchMouseEvent(mouseEventPoint);
}

void XComponentPattern::HandleAxisEvent(const AxisInfo& info)
{
    auto axisEvent = info.ConvertToAxisEvent();
    NativeXComponentDispatchAxisEvent(&axisEvent);
}

void XComponentPattern::HandleMouseHoverEvent(bool isHover)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    const auto* callback = nativeXComponentImpl_->GetMouseEventCallback();
    CHECK_NULL_VOID(callback);
    CHECK_NULL_VOID(callback->DispatchHoverEvent);
    callback->DispatchHoverEvent(nativeXComponent_.get(), isHover);
}

void XComponentPattern::NativeXComponentDispatchMouseEvent(const OH_NativeXComponent_MouseEvent& mouseEvent)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    nativeXComponentImpl_->SetMouseEvent(mouseEvent);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto* callback = nativeXComponentImpl_->GetMouseEventCallback();
    CHECK_NULL_VOID(callback);
    CHECK_NULL_VOID(callback->DispatchMouseEvent);
    callback->DispatchMouseEvent(nativeXComponent_.get(), surface);
}

void XComponentPattern::NativeXComponentDispatchAxisEvent(AxisEvent* axisEvent)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    const auto callback = nativeXComponentImpl_->GetUIAxisEventCallback();
    CHECK_NULL_VOID(callback);
    ArkUI_UIInputEvent uiEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID, axisEvent };
    callback(nativeXComponent_.get(), &uiEvent, ArkUI_UIInputEvent_Type::ARKUI_UIINPUTEVENT_TYPE_AXIS);
}

void XComponentPattern::SetTouchPoint(
    const std::list<TouchLocationInfo>& touchInfoList, const int64_t timeStamp, const TouchType& touchType)
{
    touchEventPoint_.numPoints =
        touchInfoList.size() <= OH_MAX_TOUCH_POINTS_NUMBER ? touchInfoList.size() : OH_MAX_TOUCH_POINTS_NUMBER;
    nativeXComponentTouchPoints_.clear();
    uint32_t index = 0;
    for (auto iterator = touchInfoList.begin(); iterator != touchInfoList.end() && index < OH_MAX_TOUCH_POINTS_NUMBER;
         iterator++) {
        OH_NativeXComponent_TouchPoint ohTouchPoint;
        const auto& pointTouchInfo = *iterator;
        const auto& pointScreenOffset = pointTouchInfo.GetGlobalLocation();
        const auto& pointLocalOffset = pointTouchInfo.GetLocalLocation();
        ohTouchPoint.id = pointTouchInfo.GetFingerId();
        ohTouchPoint.screenX = static_cast<float>(pointScreenOffset.GetX());
        ohTouchPoint.screenY = static_cast<float>(pointScreenOffset.GetY());
        ohTouchPoint.x = static_cast<float>(pointLocalOffset.GetX());
        ohTouchPoint.y = static_cast<float>(pointLocalOffset.GetY());
        ohTouchPoint.type = ConvertNativeXComponentTouchEvent(touchType);
        ohTouchPoint.size = pointTouchInfo.GetSize();
        ohTouchPoint.force = pointTouchInfo.GetForce();
        ohTouchPoint.timeStamp = timeStamp;
        ohTouchPoint.isPressed = (touchType == TouchType::DOWN);
        touchEventPoint_.touchPoints[index++] = ohTouchPoint;
        // set tiltX, tiltY and sourceToolType
        XComponentTouchPoint xcomponentTouchPoint;
        xcomponentTouchPoint.tiltX = pointTouchInfo.GetTiltX().value_or(0.0f);
        xcomponentTouchPoint.tiltY = pointTouchInfo.GetTiltY().value_or(0.0f);
        xcomponentTouchPoint.sourceToolType = ConvertNativeXComponentTouchToolType(pointTouchInfo.GetSourceTool());
        nativeXComponentTouchPoints_.emplace_back(xcomponentTouchPoint);
    }
    while (index < OH_MAX_TOUCH_POINTS_NUMBER) {
        OH_NativeXComponent_TouchPoint ohTouchPoint;
        ohTouchPoint.id = 0;
        ohTouchPoint.screenX = 0;
        ohTouchPoint.screenY = 0;
        ohTouchPoint.x = 0;
        ohTouchPoint.y = 0;
        ohTouchPoint.type = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
        ohTouchPoint.size = 0;
        ohTouchPoint.force = 0;
        ohTouchPoint.timeStamp = 0;
        ohTouchPoint.isPressed = false;
        touchEventPoint_.touchPoints[index++] = ohTouchPoint;
    }
}

std::vector<OH_NativeXComponent_HistoricalPoint> XComponentPattern::SetHistoryPoint(
    const std::list<TouchLocationInfo>& touchInfoList)
{
    std::vector<OH_NativeXComponent_HistoricalPoint> historicalPoints;
    for (auto&& item : touchInfoList) {
        OH_NativeXComponent_HistoricalPoint point;
        point.id = item.GetFingerId();
        point.x = item.GetLocalLocation().GetX();
        point.y = item.GetLocalLocation().GetY();
        point.screenX = item.GetScreenLocation().GetX();
        point.screenY = item.GetScreenLocation().GetY();
        point.type = static_cast<OH_NativeXComponent_TouchEventType>(item.GetTouchType());
        point.size = item.GetSize();
        point.force = item.GetForce();
        point.timeStamp = item.GetTimeStamp().time_since_epoch().count();
        point.titlX = item.GetTiltX().value_or(0.0f);
        point.titlY = item.GetTiltY().value_or(0.0f);
        point.sourceTool = static_cast<OH_NativeXComponent_TouchEvent_SourceTool>(item.GetSourceTool());

        historicalPoints.push_back(point);
    }
    return historicalPoints;
}

void XComponentPattern::FireExternalEvent(RefPtr<NG::PipelineContext> context,
    const std::string& componentId, const uint32_t nodeId, const bool isDestroy)
{
    CHECK_NULL_VOID(context);
#ifdef NG_BUILD
    auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(context->GetFrontend());
#else
    auto frontEnd = AceType::DynamicCast<DeclarativeFrontend>(context->GetFrontend());
#endif
    CHECK_NULL_VOID(frontEnd);
    auto jsEngine = frontEnd->GetJsEngine();
    jsEngine->FireExternalEvent(componentId, nodeId, isDestroy);
}

ExternalEvent XComponentPattern::CreateExternalEvent()
{
    return [weak = AceType::WeakClaim(this), instanceId = instanceId_](
               const std::string& componentId, const uint32_t nodeId, const bool isDestroy) {
        ContainerScope scope(instanceId);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireExternalEvent(context, componentId, nodeId, isDestroy);
    };
}

void XComponentPattern::SetHandlingRenderContextForSurface(const RefPtr<RenderContext>& otherRenderContext)
{
    CHECK_NULL_VOID(otherRenderContext);
    handlingSurfaceRenderContext_ = otherRenderContext;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    renderContext->ClearChildren();
    renderContext->AddChild(handlingSurfaceRenderContext_, 0);
    auto paintRect = AdjustPaintRect(
        localPosition_.GetX(), localPosition_.GetY(), drawSize_.Width(), drawSize_.Height(), true);
    handlingSurfaceRenderContext_->SetBounds(
        paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
}

OffsetF XComponentPattern::GetOffsetRelativeToWindow()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    return host->GetTransformRelativeOffset();
}

void XComponentPattern::RestoreHandlingRenderContextForSurface()
{
    SetHandlingRenderContextForSurface(renderContextForSurface_);
}

XComponentControllerErrorCode XComponentPattern::SetExtController(const RefPtr<XComponentPattern>& extPattern)
{
    if (!extPattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    if (extPattern_.Upgrade()) {
        return XCOMPONENT_CONTROLLER_REPEAT_SET;
    }
    extPattern->SetHandlingRenderContextForSurface(handlingSurfaceRenderContext_);
    extPattern_ = extPattern;
    handlingSurfaceRenderContext_.Reset();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

XComponentControllerErrorCode XComponentPattern::ResetExtController(const RefPtr<XComponentPattern>& extPattern)
{
    if (!extPattern) {
        return XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto curExtPattern = extPattern_.Upgrade();
    if (!curExtPattern || curExtPattern != extPattern) {
        return XCOMPONENT_CONTROLLER_RESET_ERROR;
    }
    RestoreHandlingRenderContextForSurface();
    extPattern->RestoreHandlingRenderContextForSurface();
    extPattern_.Reset();
    return XCOMPONENT_CONTROLLER_NO_ERROR;
}

void XComponentPattern::HandleSetExpectedRateRangeEvent()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    CHECK_NULL_VOID(displaySync_);
    OH_NativeXComponent_ExpectedRateRange* range = nativeXComponentImpl_->GetRateRange();
    CHECK_NULL_VOID(range);
    FrameRateRange frameRateRange;
    frameRateRange.Set(range->min, range->max, range->expected);
    displaySync_->SetExpectedFrameRateRange(frameRateRange);
}

void XComponentPattern::HandleOnFrameEvent()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    CHECK_NULL_VOID(displaySync_);
    displaySync_->RegisterOnFrameWithData([weak = AceType::WeakClaim(this)](RefPtr<DisplaySyncData> displaySyncData) {
        auto xComponentPattern = weak.Upgrade();
        CHECK_NULL_VOID(xComponentPattern);
        CHECK_NULL_VOID(xComponentPattern->nativeXComponentImpl_->GetOnFrameCallback());
        xComponentPattern->nativeXComponentImpl_->GetOnFrameCallback()(xComponentPattern->nativeXComponent_.get(),
            displaySyncData->GetTimestamp(), displaySyncData->GetTargetTimestamp());
    });
    displaySync_->AddToPipelineOnContainer();
}

void XComponentPattern::HandleUnregisterOnFrameEvent()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    CHECK_NULL_VOID(displaySync_);
    displaySync_->UnregisterOnFrame();
    displaySync_->DelFromPipelineOnContainer();
}

bool XComponentPattern::DoTextureExport()
{
    CHECK_NULL_RETURN(handlingSurfaceRenderContext_, false);
    if (!ExportTextureAvailable()) {
        return false;
    }
    if (!handlingSurfaceRenderContext_->DoTextureExport(exportTextureSurfaceId_)) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "DoTextureExport fail");
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    renderContext->SetIsNeedRebuildRSTree(false);
    return true;
}

bool XComponentPattern::StopTextureExport()
{
    CHECK_NULL_RETURN(handlingSurfaceRenderContext_, false);
    if (!handlingSurfaceRenderContext_->StopTextureExport()) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "StopTextureExport fail");
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    renderContext->ClearChildren();
    renderContext->AddChild(handlingSurfaceRenderContext_, 0);
    renderContext->SetIsNeedRebuildRSTree(true);
    return true;
}

void XComponentPattern::AddAfterLayoutTaskForExportTexture()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->DoTextureExport();
    });
}

bool XComponentPattern::ExportTextureAvailable()
{
    auto host = GetHost();
    auto parnetNodeContainer = host->GetNodeContainer();
    CHECK_NULL_RETURN(parnetNodeContainer, false);
    auto parent = parnetNodeContainer->GetAncestorNodeOfFrame();
    CHECK_NULL_RETURN(parent, false);
    auto ancestorNodeContainer = parent->GetNodeContainer();
    CHECK_NULL_RETURN(ancestorNodeContainer, true);
    auto ancestorViewNode = ancestorNodeContainer->GetChildAtIndex(0);
    CHECK_NULL_RETURN(ancestorViewNode, true);
    auto parnetExportTextureInfo = ancestorViewNode->GetExportTextureInfo();
    CHECK_NULL_RETURN(parnetExportTextureInfo, true);
    return parnetExportTextureInfo->GetCurrentRenderType() != NodeRenderType::RENDER_TYPE_TEXTURE;
}

bool XComponentPattern::ChangeRenderType(NodeRenderType renderType)
{
    if (type_ != XComponentType::SURFACE) {
        return renderType == NodeRenderType::RENDER_TYPE_DISPLAY;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!host->GetNodeContainer()) {
        renderType_ = renderType;
        return true;
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    if (renderType == NodeRenderType::RENDER_TYPE_TEXTURE) {
        if (DoTextureExport()) {
            renderType_ = renderType;
            return true;
        }
    } else {
        if (StopTextureExport()) {
            renderType_ = renderType;
            return true;
        }
    }
    return false;
}

void XComponentPattern::SetExportTextureSurfaceId(const std::string& surfaceId)
{
    exportTextureSurfaceId_ = StringUtils::StringToLongUint(surfaceId);
}

void XComponentPattern::SetIdealSurfaceWidth(float surfaceWidth)
{
    selfIdealSurfaceWidth_ = surfaceWidth;
}

void XComponentPattern::SetIdealSurfaceHeight(float surfaceHeight)
{
    selfIdealSurfaceHeight_ = surfaceHeight;
}

void XComponentPattern::SetIdealSurfaceOffsetX(float offsetX)
{
    selfIdealSurfaceOffsetX_ = offsetX;
}

void XComponentPattern::SetIdealSurfaceOffsetY(float offsetY)
{
    selfIdealSurfaceOffsetY_ = offsetY;
}

void XComponentPattern::ClearIdealSurfaceOffset(bool isXAxis)
{
    if (isXAxis) {
        selfIdealSurfaceOffsetX_.reset();
    } else {
        selfIdealSurfaceOffsetY_.reset();
    }
}

void XComponentPattern::UpdateSurfaceBounds(bool needForceRender, bool frameOffsetChange)
{
    if (!drawSize_.IsPositive()) {
        return;
    }
    auto preSurfaceSize = surfaceSize_;
    auto preLocalPosition = localPosition_;
    if (selfIdealSurfaceWidth_.has_value() && Positive(selfIdealSurfaceWidth_.value()) &&
        selfIdealSurfaceHeight_.has_value() && Positive(selfIdealSurfaceHeight_.value())) {
        localPosition_.SetX(selfIdealSurfaceOffsetX_.has_value()
                                ? selfIdealSurfaceOffsetX_.value()
                                : (drawSize_.Width() - selfIdealSurfaceWidth_.value()) / 2.0f);

        localPosition_.SetY(selfIdealSurfaceOffsetY_.has_value()
                                ? selfIdealSurfaceOffsetY_.value()
                                : (drawSize_.Height() - selfIdealSurfaceHeight_.value()) / 2.0f);
        surfaceSize_ = { selfIdealSurfaceWidth_.value(), selfIdealSurfaceHeight_.value() };
    } else {
        surfaceSize_ = drawSize_;
    }
    if (frameOffsetChange || preLocalPosition != localPosition_) {
        auto offset = globalPosition_ + localPosition_;
        NativeXComponentOffset(offset.GetX(), offset.GetY());
    }
    if (preSurfaceSize != surfaceSize_) {
        XComponentSizeChange({ localPosition_, surfaceSize_ }, preSurfaceSize.IsPositive());
    }
    if (handlingSurfaceRenderContext_) {
        auto paintRect = AdjustPaintRect(
            localPosition_.GetX(), localPosition_.GetY(), surfaceSize_.Width(), surfaceSize_.Height(), true);
        handlingSurfaceRenderContext_->SetBounds(
            paintRect.GetX(), paintRect.GetY(), paintRect.Width(), paintRect.Height());
#ifdef ENABLE_ROSEN_BACKEND
        auto* transactionProxy = Rosen::RSTransactionProxy::GetInstance();
        if (transactionProxy != nullptr) {
            transactionProxy->FlushImplicitTransaction();
        }
#endif
    }
    if (needForceRender) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    }
}

void XComponentPattern::NativeSurfaceHide()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto surfaceHideCallback = nativeXComponentImpl_->GetSurfaceHideCallback();
    CHECK_NULL_VOID(surfaceHideCallback);
    surfaceHideCallback(nativeXComponent_.get(), surface);
}

void XComponentPattern::NativeSurfaceShow()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    CHECK_NULL_VOID(nativeXComponent_);
    auto width = initSize_.Width();
    auto height = initSize_.Height();
    nativeXComponentImpl_->SetXComponentWidth(static_cast<uint32_t>(width));
    nativeXComponentImpl_->SetXComponentHeight(static_cast<uint32_t>(height));
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto surfaceShowCallback = nativeXComponentImpl_->GetSurfaceShowCallback();
    CHECK_NULL_VOID(surfaceShowCallback);
    surfaceShowCallback(nativeXComponent_.get(), surface);
}

void XComponentPattern::OnWindowHide()
{
    if (!hasXComponentInit_ || hasReleasedSurface_
        || (type_ != XComponentType::SURFACE && type_ != XComponentType::TEXTURE)) {
        return;
    }
    CHECK_NULL_VOID(renderSurface_);
    NativeSurfaceHide();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        renderSurface_->releaseSurfaceBuffers();
    }
    hasReleasedSurface_ = true;
}

void XComponentPattern::OnWindowShow()
{
    if (!hasXComponentInit_ || !hasReleasedSurface_
        || (type_ != XComponentType::SURFACE && type_ != XComponentType::TEXTURE)) {
        return;
    }
    NativeSurfaceShow();
    hasReleasedSurface_ = false;
}

void XComponentPattern::EnableAnalyzer(bool enable)
{
    isEnableAnalyzer_ = enable;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        return;
    }

    if (imageAnalyzerManager_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(host, ImageAnalyzerHolder::CANVAS);
    CHECK_NULL_VOID(imageAnalyzerManager_);
}

void XComponentPattern::StartImageAnalyzer(void* config, onAnalyzedCallback& onAnalyzed)
{
    if (!IsSupportImageAnalyzerFeature()) {
        CHECK_NULL_VOID(onAnalyzed);
        (onAnalyzed.value())(ImageAnalyzerState::UNSUPPORTED);
        return;
    }

    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAnalyzerConfig(config);
    imageAnalyzerManager_->SetImageAnalyzerCallback(onAnalyzed);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CreateAnalyzerOverlay();
    });
}

void XComponentPattern::StopImageAnalyzer()
{
    DestroyAnalyzerOverlay();
}

bool XComponentPattern::IsSupportImageAnalyzerFeature()
{
    return isEnableAnalyzer_ && imageAnalyzerManager_ && imageAnalyzerManager_->IsSupportImageAnalyzerFeature();
}

void XComponentPattern::CreateAnalyzerOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(pixelMap);
    if (IsSupportImageAnalyzerFeature()) {
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->CreateAnalyzerOverlay(pixelMap);
    }
}

void XComponentPattern::UpdateAnalyzerOverlay()
{
    auto context = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(pixelMap);
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->UpdateAnalyzerOverlay(pixelMap);
}

void XComponentPattern::UpdateAnalyzerUIConfig(const RefPtr<NG::GeometryNode>& geometryNode)
{
    if (IsSupportImageAnalyzerFeature()) {
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->UpdateAnalyzerUIConfig(geometryNode);
    }
}

void XComponentPattern::DestroyAnalyzerOverlay()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->DestroyAnalyzerOverlay();
}

void XComponentPattern::ReleaseImageAnalyzer()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->ReleaseImageAnalyzer();
}

RectF XComponentPattern::AdjustPaintRect(float positionX, float positionY, float width, float height, bool isRound)
{
    RectF rect;
    float relativeLeft = positionX;
    float relativeTop = positionY;
    float nodeWidth = width;
    float nodeHeight = height;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    float roundToPixelErrorX = 0;
    float roundToPixelErrorY = 0;

    float nodeLeftI = RoundValueToPixelGrid(relativeLeft, isRound, false, false);
    float nodeTopI = RoundValueToPixelGrid(relativeTop, isRound, false, false);
    roundToPixelErrorX += nodeLeftI -relativeLeft;
    roundToPixelErrorY += nodeTopI -relativeTop;
    rect.SetLeft(nodeLeftI);
    rect.SetTop(nodeTopI);

    float nodeWidthI = RoundValueToPixelGrid(absoluteRight, isRound, false, false) - nodeLeftI;
    float nodeWidthTemp = RoundValueToPixelGrid(nodeWidth, isRound, false, false);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = RoundValueToPixelGrid(absoluteBottom, isRound, false, false) - nodeTopI;
    float nodeHeightTemp = RoundValueToPixelGrid(nodeHeight, isRound, false, false);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }
    if (roundToPixelErrorX >= 1.0f || roundToPixelErrorX <= -1.0f) {
        LOGI("roundToPixelErrorX is %{public}f", roundToPixelErrorX);
    }
    if (roundToPixelErrorY >= 1.0f || roundToPixelErrorY <= -1.0f) {
        LOGI("roundToPixelErrorY is %{public}f", roundToPixelErrorY);
    }

    rect.SetWidth(nodeWidthI);
    rect.SetHeight(nodeHeightI);
    return rect;
}

float XComponentPattern::RoundValueToPixelGrid(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.50f)) {
            return (value - fractials + 1.0f);
        } else {
            return (value - fractials);
        }
    }
    return value;
}
} // namespace OHOS::Ace::NG
