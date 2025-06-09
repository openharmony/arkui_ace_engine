/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include <cmath>
#include <cstdlib>

#include "interfaces/native/event/ui_input_event_impl.h"
#include "interfaces/native/ui_input_event.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/dump_log.h"
#include "base/log/frame_report.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/ressched/ressched_report.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/ace_view.h"
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
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "feature/anco_manager/rs_ext_node_operation.h"
#include "transaction/rs_interfaces.h"
#endif
#ifdef RENDER_EXTRACT_SUPPORTED
#include "core/components_ng/render/adapter/render_surface_impl.h"
#endif

#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_accessibility_session_adapter.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_utils.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_inner_surface_controller.h"
#include "core/event/event_info_convertor.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

const std::string BUFFER_USAGE_XCOMPONENT = "xcomponent";
} // namespace

XComponentPattern::XComponentPattern(const std::optional<std::string>& id, XComponentType type,
    const std::optional<std::string>& libraryname,
    const std::shared_ptr<InnerXComponentController>& xcomponentController, float initWidth, float initHeight,
    bool isTypedNode)
    : id_(id), type_(type), xcomponentController_(xcomponentController), initSize_(initWidth, initHeight),
      isTypedNode_(isTypedNode)
{
    SetLibraryName(libraryname);
    if (!isTypedNode_) {
        InitNativeXComponent();
    }
    RegisterSurfaceCallbackModeEvent();
}

std::string XComponentPattern::XComponentTypeToString(XComponentType type)
{
    switch (type) {
        case XComponentType::UNKNOWN:
            return "unknown";
        case XComponentType::SURFACE:
            return "surface";
        case XComponentType::COMPONENT:
            return "component";
        case XComponentType::TEXTURE:
            return "texture";
        case XComponentType::NODE:
            return "node";
        default:
            return "unknown";
    }
}

std::string XComponentPattern::XComponentNodeTypeToString(XComponentNodeType type)
{
    switch (type) {
        case XComponentNodeType::UNKNOWN:
            return "unknown";
        case XComponentNodeType::TYPE_NODE:
            return "type_node";
        case XComponentNodeType::DECLARATIVE_NODE:
            return "declarative_node";
        case XComponentNodeType::CNODE:
            return "cnode";
        default:
            return "unknown";
    }
}

void XComponentPattern::AdjustNativeWindowSize(float width, float height)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto viewScale = context->GetViewScale();
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->AdjustNativeWindowSize(
        static_cast<uint32_t>(width * viewScale), static_cast<uint32_t>(height * viewScale));
}

void XComponentPattern::InitNativeXComponent()
{
    if ((type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE) && libraryname_.has_value()) {
        isNativeXComponent_ = true;
        nativeXComponentImpl_ = AceType::MakeRefPtr<NativeXComponentImpl>();
        nativeXComponent_ = std::make_shared<OH_NativeXComponent>(AceType::RawPtr(nativeXComponentImpl_));
    }
}

void XComponentPattern::InitXComponent()
{
    // used for TypedNode, not for declareative
    if (isTypedNode_) {
        InitNativeXComponent();
        if (isNativeXComponent_) {
            InitializeAccessibility();
            LoadNative();
        }
    }
}

void XComponentPattern::InitSurface()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // only xcomponent created by capi will set successfully, others will be set in FireExternalEvent
    SetExpectedRateRangeInit();
    OnFrameEventInit();
    UnregisterOnFrameEventInit();

    renderContext->SetClipToFrame(true);
    renderContext->SetClipToBounds(true);
#ifdef RENDER_EXTRACT_SUPPORTED
    renderSurface_ = RenderSurface::Create(CovertToRenderSurfaceType(type_));
#else
    renderSurface_ = RenderSurface::Create();
#endif
    renderSurface_->SetInstanceId(GetHostInstanceId());
    renderSurface_->SetBufferUsage(BUFFER_USAGE_XCOMPONENT);
    if (type_ == XComponentType::SURFACE) {
        InitializeRenderContext();
        if (!SystemProperties::GetExtSurfaceEnabled()) {
            renderSurface_->SetRenderContext(renderContextForSurface_);
        } else {
            auto pipelineContext = host->GetContextRefPtr();
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
        renderContext->OnNodeNameUpdate(GetId());
    }
    renderSurface_->InitSurface();
    renderSurface_->UpdateSurfaceConfig();
    if (type_ == XComponentType::TEXTURE) {
        renderSurface_->RegisterBufferCallback();
    }
    if (isTypedNode_ || isCNode_) {
        InitNativeWindow(initSize_.Width(), initSize_.Height());
    }
    surfaceId_ = renderSurface_->GetUniqueId();
    initialSurfaceId_ = surfaceId_;
    UpdateTransformHint();
    RegisterSurfaceRenderContext();
}

void XComponentPattern::RegisterSurfaceRenderContext()
{
    if (type_ == XComponentType::SURFACE) {
        XComponentInnerSurfaceController::RegisterSurfaceRenderContext(
            initialSurfaceId_, WeakPtr(handlingSurfaceRenderContext_));
    }
}

void XComponentPattern::UnregisterSurfaceRenderContext()
{
    if (type_ == XComponentType::SURFACE) {
        XComponentInnerSurfaceController::UnregisterSurfaceRenderContext(initialSurfaceId_);
    }
}

void XComponentPattern::UpdateTransformHint()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    initialContext_ = pipelineContext;
    pipelineContext->AddWindowStateChangedCallback(host->GetId());
    RegisterTransformHintCallback(AceType::RawPtr(pipelineContext));
}

void XComponentPattern::RegisterTransformHintCallback(PipelineContext* context)
{
    CHECK_NULL_VOID(context);
    SetRotation(context->GetTransformHint());
    auto callbackId =
        context->RegisterTransformHintChangeCallback([weak = WeakClaim(this)](uint32_t transform) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->SetRotation(transform);
            }
        });
    UpdateTransformHintChangedCallbackId(callbackId);
}

void XComponentPattern::Initialize()
{
    if (type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE) {
        InitSurface();
        InitEvent();
        InitController();
    } else if (type_ == XComponentType::NODE && id_.has_value()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContextRefPtr();
        if (context) {
            FireExternalEvent(context, id_.value(), host->GetId(), false);
            InitNativeNodeCallbacks();
        }
    }
    if (!isTypedNode_) {
        InitializeAccessibility();
    }
}

void XComponentPattern::OnAttachToMainTree()
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] AttachToMainTree", GetId().c_str());
    ACE_SCOPED_TRACE("XComponent[%s] AttachToMainTree", GetId().c_str());
    isOnTree_ = true;
    if (isTypedNode_ && surfaceCallbackMode_ == SurfaceCallbackMode::DEFAULT) {
        HandleSurfaceCreated();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        if (needRecoverDisplaySync_ && displaySync_ && !displaySync_->IsOnPipeline()) {
            TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "OnAttachToMainTree:recover displaySync: "
                "%{public}s(%{public}" PRIu64 ")", GetId().c_str(), displaySync_->GetId());
            displaySync_->AddToPipelineOnContainer();
            needRecoverDisplaySync_ = false;
        }
    }
}

void XComponentPattern::OnDetachFromMainTree()
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] DetachFromMainTree", GetId().c_str());
    ACE_SCOPED_TRACE("XComponent[%s] DetachFromMainTree", GetId().c_str());
    isOnTree_ = false;
    if (isTypedNode_ && surfaceCallbackMode_ == SurfaceCallbackMode::DEFAULT) {
        HandleSurfaceDestroyed();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        if (displaySync_ && displaySync_->IsOnPipeline()) {
            TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "OnDetachFromMainTree:remove displaySync: "
                "%{public}s(%{public}" PRIu64 ")", GetId().c_str(), displaySync_->GetId());
            displaySync_->DelFromPipelineOnContainer();
            needRecoverDisplaySync_ = true;
        }
    }
}

void XComponentPattern::InitializeRenderContext()
{
    renderContextForSurface_ = RenderContext::Create();
#ifdef RENDER_EXTRACT_SUPPORTED
    auto contextType = type_ == XComponentType::TEXTURE ? RenderContext::ContextType::HARDWARE_TEXTURE
                                                        : RenderContext::ContextType::HARDWARE_SURFACE;
    RenderContext::ContextParam param = { contextType, GetId() + "Surface", RenderContext::PatternType::XCOM };
#else
    RenderContext::ContextParam param = { RenderContext::ContextType::HARDWARE_SURFACE,
                                          GetId() + "Surface", RenderContext::PatternType::XCOM };
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
    auto eventHub = host->GetOrCreateEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);

    focusHub->RequestFocusImmediately();
}
#endif

void XComponentPattern::OnAttachToFrameNode()
{
    Initialize();
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().EnableSelfRender();
    }
}

void XComponentPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    // if surface has been reset by pip, do not set backgourndColor
    if (handlingSurfaceRenderContext_ != renderContextForSurface_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    CHECK_NULL_VOID(handlingSurfaceRenderContext_);
    auto bkColor = renderContext->GetBackgroundColor().value_or(Color::BLACK);
    handlingSurfaceRenderContext_->UpdateBackgroundColor(
        (bkColor.GetAlpha() < UINT8_MAX) ? Color::TRANSPARENT : bkColor);
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
    if (type_ != XComponentType::SURFACE || !id_.has_value() ||
        !Rosen::RSExtNodeOperation::GetInstance().CheckNeedToProcess(id_.value())) {
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

    Rosen::RSExtNodeOperation::GetInstance().ProcessRSExtNode(
        GetId(), parentNode->GetId(), canvasRect.GetX(), canvasRect.GetY(), rsSurfaceNode);
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
    UnregisterSurfaceRenderContext();
    CHECK_NULL_VOID(frameNode);
    UninitializeAccessibility(frameNode);
    if (isTypedNode_) {
        if (surfaceCallbackMode_ == SurfaceCallbackMode::PIP) {
            HandleSurfaceDestroyed(frameNode);
        }
        if (isNativeXComponent_) {
            OnNativeUnload(frameNode);
        }
    } else {
        if (!hasXComponentInit_) {
            return;
        }
        if (type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE) {
            OnSurfaceDestroyed();
            auto eventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireDestroyEvent(GetId());
            if (id_.has_value()) {
                eventHub->FireDetachEvent(id_.value());
            }
            eventHub->FireControllerDestroyedEvent(surfaceId_, GetId());
#ifdef RENDER_EXTRACT_SUPPORTED
            if (renderContextForSurface_) {
                renderContextForSurface_->RemoveSurfaceChangedCallBack();
            }
#endif
        }
    }

    auto id = frameNode->GetId();
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    if (HasTransformHintChangedCallbackId()) {
        pipeline->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
    }
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().DisableSelfRender();
    }
}

void XComponentPattern::InitController()
{
    CHECK_NULL_VOID(xcomponentController_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto* controllerNG = static_cast<XComponentControllerNG*>(xcomponentController_.get());
    if (controllerNG) {
        controllerNG->SetPattern(AceType::Claim(this));
    }
    xcomponentController_->SetConfigSurfaceImpl(
        [weak = WeakClaim(this), uiTaskExecutor](uint32_t surfaceWidth, uint32_t surfaceHeight) {
            uiTaskExecutor.PostSyncTask(
                [weak, surfaceWidth, surfaceHeight]() {
                    auto pattern = weak.Upgrade();
                    CHECK_NULL_VOID(pattern);
                    pattern->ConfigSurface(surfaceWidth, surfaceHeight);
                },
                "ArkUIXComponentSurfaceConfigChange");
        });
    if (!isTypedNode_) {
        xcomponentController_->SetSurfaceId(surfaceId_);
    }
}

void XComponentPattern::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
{
    renderSurface_->ConfigSurface(surfaceWidth, surfaceHeight);
}

void XComponentPattern::OnAttachContext(PipelineContext* context)
{
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    context->AddWindowStateChangedCallback(host->GetId());
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->SetInstanceId(context->GetInstanceId());
    auto initialContext = initialContext_.Upgrade();
    if (initialContext && initialContext != context) {
        initialContext->RemoveWindowStateChangedCallback(host->GetId());
        if (HasTransformHintChangedCallbackId()) {
            initialContext->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value());
            RegisterTransformHintCallback(context);
        }
        initialContext_ = nullptr;
    }
}

void XComponentPattern::OnDetachContext(PipelineContext* context)
{
    CHECK_NULL_VOID(context);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    context->RemoveWindowStateChangedCallback(host->GetId());
}

void XComponentPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("enableAnalyzer", isEnableAnalyzer_ ? "true" : "false", filter);
    json->PutExtAttr("enableSecure", isEnableSecure_ ? "true" : "false", filter);
    json->PutExtAttr("hdrBrightness", std::to_string(hdrBrightness_).c_str(), filter);
    json->PutExtAttr("enableTransparentLayer", isTransparentLayer_ ? "true" : "false", filter);
    json->PutExtAttr("screenId", screenId_.has_value() ? std::to_string(screenId_.value()).c_str() : "", filter);
    if (type_ == XComponentType::SURFACE) {
        json->PutExtAttr(
            "renderFit", XComponentUtils::XComponentRenderFitToString(GetSurfaceRenderFit()).c_str(), filter);
    }
}

void XComponentPattern::SetRotation(uint32_t rotation)
{
    if (type_ != XComponentType::SURFACE || isSurfaceLock_ || rotation_ == rotation) {
        return;
    }
    rotation_ = rotation;
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->SetTransformHint(rotation);
}

void XComponentPattern::BeforeSyncGeometryProperties(const DirtySwapConfig& config)
{
    if (type_ == XComponentType::COMPONENT || type_ == XComponentType::NODE || config.skipMeasure) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    drawSize_ = geometryNode->GetContentSize();
    if (!drawSize_.IsPositive()) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s]'s size is not positive", GetId().c_str());
        return;
    }
    globalPosition_ = geometryNode->GetFrameOffset();
    localPosition_ = geometryNode->GetContentOffset();

    if (IsSupportImageAnalyzerFeature()) {
        UpdateAnalyzerUIConfig(geometryNode);
    }
    const auto& [offsetChanged, sizeChanged, needFireNativeEvent] = UpdateSurfaceRect();
    if (!hasXComponentInit_) {
        initSize_ = paintRect_.GetSize();
        if (!SystemProperties::GetExtSurfaceEnabled() && !isTypedNode_) {
            XComponentSizeInit();
        }
        auto offset = globalPosition_ + paintRect_.GetOffset();
        NativeXComponentOffset(offset.GetX(), offset.GetY());
        hasXComponentInit_ = true;
    }
#ifndef RENDER_EXTRACT_SUPPORTED
    if (SystemProperties::GetExtSurfaceEnabled()) {
        auto transformRelativeOffset = host->GetTransformRelativeOffset();
        renderSurface_->SetExtSurfaceBounds(
            static_cast<int32_t>(transformRelativeOffset.GetX() + localPosition_.GetX()),
            static_cast<int32_t>(transformRelativeOffset.GetY() + localPosition_.GetY()),
            static_cast<int32_t>(drawSize_.Width()), static_cast<int32_t>(drawSize_.Height()));
    }
    HandleSurfaceChangeEvent(false, offsetChanged, sizeChanged, needFireNativeEvent, config.frameOffsetChange);
#endif
    if (type_ == XComponentType::SURFACE && renderType_ == NodeRenderType::RENDER_TYPE_TEXTURE) {
        AddAfterLayoutTaskForExportTexture();
    }
    host->MarkNeedSyncRenderTree();
}

void XComponentPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("xcomponentId: ").append(id_.value_or("no id")));
    DumpLog::GetInstance().AddDesc(std::string("xcomponentType: ").append(XComponentTypeToString(type_)));
    DumpLog::GetInstance().AddDesc(std::string("libraryName: ").append(libraryname_.value_or("no library name")));
    DumpLog::GetInstance().AddDesc(std::string("surfaceId: ").append(surfaceId_));
    DumpLog::GetInstance().AddDesc(std::string("surfaceRect: ").append(paintRect_.ToString()));
}

void XComponentPattern::DumpAdvanceInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("enableSecure: ").append(isEnableSecure_ ? "true" : "false"));
    DumpLog::GetInstance().AddDesc(std::string("hdrBrightness: ").append(std::to_string(hdrBrightness_).c_str()));
    DumpLog::GetInstance().AddDesc(
        std::string("enableTransparentLayer: ").append(isTransparentLayer_ ? "true" : "false"));
    DumpLog::GetInstance().AddDesc(
        std::string("screenId: ").append(screenId_.has_value() ? std::to_string(screenId_.value()).c_str() : ""));
    if (renderSurface_) {
        renderSurface_->DumpInfo();
    }
}

void XComponentPattern::NativeXComponentOffset(double x, double y)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(renderSurface_);
    if (renderSurface_->GetNativeWindow()) {
        return;
    }
    if (renderSurface_->IsSurfaceValid() && (type_ == XComponentType::SURFACE || type_ == XComponentType::TEXTURE)) {
        float viewScale = context->GetViewScale();
        renderSurface_->CreateNativeWindow();
        renderSurface_->AdjustNativeWindowSize(
            static_cast<uint32_t>(textureWidth * viewScale), static_cast<uint32_t>(textureHeight * viewScale));
        nativeWindow_ = renderSurface_->GetNativeWindow();
    }
}

void XComponentPattern::XComponentSizeInit()
{
    CHECK_RUN_ON(UI);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!isCNode_) {
        InitNativeWindow(initSize_.Width(), initSize_.Height());
    } else {
        AdjustNativeWindowSize(initSize_.Width(), initSize_.Height());
    }
    
#ifdef RENDER_EXTRACT_SUPPORTED
    if (xcomponentController_ && renderSurface_) {
        surfaceId_ = renderSurface_->GetUniqueId();
        xcomponentController_->SetSurfaceId(surfaceId_);
    }
#endif
    auto eventHub = host->GetOrCreateEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] triggers onLoad and OnSurfaceCreated callback",
        GetId().c_str());
    if (id_.has_value()) {
        eventHub->FireSurfaceInitEvent(id_.value(), host->GetId());
    }
    eventHub->FireLoadEvent(GetId());
    eventHub->FireControllerCreatedEvent(surfaceId_, GetId());
}

void XComponentPattern::XComponentSizeChange(const RectF& surfaceRect, bool needFireNativeEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    renderSurface_->UpdateSurfaceSizeInUserData(
        static_cast<uint32_t>(surfaceRect.Width()), static_cast<uint32_t>(surfaceRect.Height()));

    // In declarative mode: Native onSurfaceCreated callback is triggred
    // when the component finish it's first layout, so do not trigger the native onSurfaceChanged callback
    if (!isTypedNode_ && isNativeXComponent_ && !needFireNativeEvent) {
        return;
    }
    // When creating the surface for the first time, needFireNativeEvent = false, other time needFireNativeEvent = true
    // the first time change size no need to resize nativeWindow
    OnSurfaceChanged(surfaceRect, needFireNativeEvent);
}

RefPtr<AccessibilitySessionAdapter> XComponentPattern::GetAccessibilitySessionAdapter()
{
    return accessibilitySessionAdapter_;
}

void XComponentPattern::InitializeAccessibility()
{
    if (accessibilityChildTreeCallback_) {
        return;
    }

    InitializeAccessibilityCallback();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int64_t accessibilityId = host->GetAccessibilityId();
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT,
        "InitializeAccessibility accessibilityId: %{public}" PRId64 "", accessibilityId);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityChildTreeCallback_ = std::make_shared<XComponentAccessibilityChildTreeCallback>(
        WeakClaim(this), host->GetAccessibilityId());
    accessibilityManager->RegisterAccessibilityChildTreeCallback(
        accessibilityId, accessibilityChildTreeCallback_);
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            pipeline->GetWindowId(), accessibilityManager->GetTreeId());
    }
}

void XComponentPattern::UninitializeAccessibility(FrameNode* frameNode)
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "UninitializeAccessibility");
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (accessibilityManager->IsRegister() && accessibilityChildTreeCallback_) {
        accessibilityChildTreeCallback_->OnDeregister();
    }
    accessibilityManager->DeregisterAccessibilityChildTreeCallback(accessibilityId);
    accessibilityChildTreeCallback_ = nullptr;
}

ArkUI_AccessibilityProvider* XComponentPattern::GetNativeProvider()
{
    if(useNodeHandleAccessibilityProvider_) {
        return arkuiAccessibilityProvider_;
    }
    auto pair = GetNativeXComponent();
    auto nativeXComponentImpl = pair.first;
    CHECK_NULL_RETURN(nativeXComponentImpl, nullptr);
    return nativeXComponentImpl->GetAccessbilityProvider().get();
}

bool XComponentPattern::OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    if (accessibilityProvider_ == nullptr) {
        accessibilityProvider_ =
            AceType::MakeRefPtr<XComponentAccessibilityProvider>(WeakClaim(this));
    }

    auto nativeProvider = GetNativeProvider();
    CHECK_NULL_RETURN(nativeProvider, false);
    if (!nativeProvider->IsRegister()) {
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "Not register native accessibility");
        return false;
    }

    nativeProvider->SetInnerAccessibilityProvider(accessibilityProvider_);
    if (accessibilitySessionAdapter_ == nullptr) {
        accessibilitySessionAdapter_ =
            AceType::MakeRefPtr<XcomponentAccessibilitySessionAdapter>(host);
    }
    Registration registration;
    registration.windowId = windowId;
    registration.parentWindowId = windowId;
    registration.parentTreeId = treeId;
    registration.elementId = host->GetAccessibilityId();
    registration.operatorType = OperatorType::JS_THIRD_PROVIDER;
    registration.hostNode = WeakClaim(RawPtr(host));
    registration.accessibilityProvider = WeakClaim(RawPtr(accessibilityProvider_));
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "OnAccessibilityChildTreeRegister, "
        "windowId: %{public}d, treeId: %{public}d.", windowId, treeId);
    return accessibilityManager->RegisterInteractionOperationAsChildTree(registration);
}

bool XComponentPattern::OnAccessibilityChildTreeDeregister()
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "OnAccessibilityChildTreeDeregister, "
        "windowId: %{public}u, treeId: %{public}d.", windowId_, treeId_);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_RETURN(accessibilityManager, false);
    auto nativeProvider = GetNativeProvider();
    CHECK_NULL_RETURN(nativeProvider, false);
    nativeProvider->SetInnerAccessibilityProvider(nullptr);
    accessibilitySessionAdapter_ = nullptr;
    accessibilityProvider_ = nullptr;
    return accessibilityManager->DeregisterInteractionOperationAsChildTree(windowId_, treeId_);
}

void XComponentPattern::OnSetAccessibilityChildTree(
    int32_t childWindowId, int32_t childTreeId)
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "OnSetAccessibilityChildTree, "
        "windowId: %{public}d, treeId: %{public}d.", childWindowId, childTreeId);
    windowId_ = static_cast<uint32_t>(childWindowId);
    treeId_ = childTreeId;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetChildWindowId(childWindowId);
    accessibilityProperty->SetChildTreeId(childTreeId);
}

void XComponentPattern::InitializeAccessibilityCallback()
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "InitializeAccessibilityCallback");
    CHECK_NULL_VOID(nativeXComponentImpl_);
    auto nativeProvider = nativeXComponentImpl_->GetAccessbilityProvider();
    CHECK_NULL_VOID(nativeProvider);
    nativeProvider->SetRegisterCallback(
        [weak = WeakClaim(this)] (bool isRegister) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleRegisterAccessibilityEvent(isRegister);
        });
}

void XComponentPattern::HandleRegisterAccessibilityEvent(bool isRegister)
{
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "HandleRegisterAccessibilityEvent, "
        "isRegister: %{public}d.", isRegister);
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    if (!isRegister) {
        accessibilityChildTreeCallback_->OnDeregister();
        return;
    }

    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            pipeline->GetWindowId(), accessibilityManager->GetTreeId());
    }
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

    nativeXComponentImpl_->registerNativeNodeCallbacks(
        std::move(OnAttachRootNativeNode), std::move(OnDetachRootNativeNode));
}

void XComponentPattern::InitEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (id_.has_value()) {
        eventHub->SetOnSurfaceInitEvent(CreateExternalEvent());
    }
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

    auto onFocusEvent = [weak = WeakClaim(this)](FocusReason reason) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        return pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(std::move(onFocusEvent));

    auto onKeyEvent = [weak = WeakClaim(this)](const KeyEvent& event) -> bool {
        TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "HandleKeyEvent[%{public}d,%{public}d,%{public}d,%{public}" PRId64 "]",
            event.action, event.code, event.sourceType, event.deviceId);
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

    OH_NativeXComponent_KeyEvent keyEvent = XComponentUtils::ConvertNativeXComponentKeyEvent(event);
    nativeXComponentImpl_->SetKeyEvent(keyEvent);

    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto keyEventCallbackWithResult = nativeXComponentImpl_->GetKeyEventCallbackWithResult();
    if (keyEventCallbackWithResult) {
        return keyEventCallbackWithResult(nativeXComponent_.get(), surface);
    }
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
        if (EventInfoConvertor::IsTouchEventNeedAbandoned(info)) {
            return;
        }
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
    gestureHub->SetOnTouchIntercept([weak = WeakClaim(this)](const TouchEventInfo& touchEvent) -> HitTestMode {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, NG::HitTestMode::HTMDEFAULT);
        auto hostNode = pattern->GetHost();
        CHECK_NULL_RETURN(hostNode, NG::HitTestMode::HTMDEFAULT);
        CHECK_NULL_RETURN(pattern->nativeXComponentImpl_, hostNode->GetHitTestMode());
        const auto onTouchInterceptCallback = pattern->nativeXComponentImpl_->GetOnTouchInterceptCallback();
        CHECK_NULL_RETURN(onTouchInterceptCallback, hostNode->GetHitTestMode());
        auto event = touchEvent.ConvertToTouchEvent();
        ArkUI_UIInputEvent uiEvent { ARKUI_UIINPUTEVENT_TYPE_TOUCH, TOUCH_EVENT_ID, &event, false,
            Container::GetCurrentApiTargetVersion() };
        return static_cast<NG::HitTestMode>(onTouchInterceptCallback(pattern->nativeXComponent_.get(), &uiEvent));
    });
}

void XComponentPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputHub)
{
    CHECK_NULL_VOID(!mouseEvent_);

    auto mouseTask = [weak = WeakClaim(this)](const MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        TouchEventInfo touchEventInfo("touchEvent");
        if (EventInfoConvertor::ConvertMouseToTouchIfNeeded(info, touchEventInfo)) {
            pattern->HandleTouchEvent(touchEventInfo);
            return;
        }
        TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "HandleMouseEvent[%{public}f,%{public}f,%{public}d,%{public}d]",
            info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY(), info.GetAction(), info.GetButton());
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
    touchEventPoint_.type = XComponentUtils::ConvertNativeXComponentTouchEvent(touchType);
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "HandleTouchEvent[%{public}f,%{public}f,%{public}d,%{public}zu,%{public}u]",
        localOffset.GetX(), localOffset.GetY(), touchInfo.GetFingerId(), touchInfoList.front().GetTouchType(),
        static_cast<uint32_t>(touchInfo.GetSize()));
    SetTouchPoint(info.GetTouches(), timeStamp, touchType);

    if (nativeXComponent_ && nativeXComponentImpl_) {
        nativeXComponentImpl_->SetHistoricalPoint(SetHistoryPoint(info.GetHistory()));
        nativeXComponentImpl_->SetCurrentSourceType({ touchInfo.GetFingerId(),
            XComponentUtils::ConvertNativeXComponentEventSourceType(info.GetSourceDevice()) });
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
    mouseEventPoint.action = XComponentUtils::ConvertNativeXComponentMouseEventAction(info.GetAction());
    mouseEventPoint.button = XComponentUtils::ConvertNativeXComponentMouseEventButton(info.GetButton());
    mouseEventPoint.timestamp = info.GetTimeStamp().time_since_epoch().count();
    OH_NativeXComponent_ExtraMouseEventInfo extraMouseEventInfo;
    extraMouseEventInfo.modifierKeyStates = CalculateModifierKeyState(info.GetPressedKeyCodes());
    NativeXComponentDispatchMouseEvent(mouseEventPoint, extraMouseEventInfo);
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

void XComponentPattern::NativeXComponentDispatchMouseEvent(const OH_NativeXComponent_MouseEvent& mouseEvent,
    const OH_NativeXComponent_ExtraMouseEventInfo& extraMouseEventInfo)
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    nativeXComponentImpl_->SetMouseEvent(mouseEvent);
    nativeXComponentImpl_->SetExtraMouseEventInfo(extraMouseEventInfo);
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
    ArkUI_UIInputEvent uiEvent { ARKUI_UIINPUTEVENT_TYPE_AXIS, AXIS_EVENT_ID, axisEvent, false,
        Container::GetCurrentApiTargetVersion() };
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
        const auto& pointWindowOffset = pointTouchInfo.GetGlobalLocation();
        const auto& pointLocalOffset = pointTouchInfo.GetLocalLocation();
        const auto& pointDisplayOffset = pointTouchInfo.GetScreenLocation();
        ohTouchPoint.id = pointTouchInfo.GetFingerId();
        // screenX and screenY implementation wrong but should not modify for maintaining compatibility
        ohTouchPoint.screenX = static_cast<float>(pointWindowOffset.GetX());
        ohTouchPoint.screenY = static_cast<float>(pointWindowOffset.GetY());
        ohTouchPoint.x = static_cast<float>(pointLocalOffset.GetX());
        ohTouchPoint.y = static_cast<float>(pointLocalOffset.GetY());
        ohTouchPoint.type = XComponentUtils::ConvertNativeXComponentTouchEvent(touchType);
        ohTouchPoint.size = pointTouchInfo.GetSize();
        ohTouchPoint.force = pointTouchInfo.GetForce();
        ohTouchPoint.timeStamp = timeStamp;
        ohTouchPoint.isPressed = (touchType == TouchType::DOWN);
        touchEventPoint_.touchPoints[index++] = ohTouchPoint;
        // set tiltX, tiltY, windowX, windowY, displayX, displayY and sourceToolType
        XComponentTouchPoint xcomponentTouchPoint;
        xcomponentTouchPoint.tiltX = pointTouchInfo.GetTiltX().value_or(0.0f);
        xcomponentTouchPoint.tiltY = pointTouchInfo.GetTiltY().value_or(0.0f);
        xcomponentTouchPoint.windowX = static_cast<float>(pointWindowOffset.GetX());
        xcomponentTouchPoint.windowY = static_cast<float>(pointWindowOffset.GetY());
        xcomponentTouchPoint.displayX = static_cast<float>(pointDisplayOffset.GetX());
        xcomponentTouchPoint.displayY = static_cast<float>(pointDisplayOffset.GetY());
        xcomponentTouchPoint.sourceToolType =
            XComponentUtils::ConvertNativeXComponentTouchToolType(pointTouchInfo.GetSourceTool());
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

void XComponentPattern::FireExternalEvent(
    RefPtr<NG::PipelineContext> context, const std::string& componentId, const uint32_t nodeId, const bool isDestroy)
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
    return
        [weak = AceType::WeakClaim(this)](const std::string& componentId, const uint32_t nodeId, const bool isDestroy) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto context = host->GetContextRefPtr();
            CHECK_NULL_VOID(context);
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
    handlingSurfaceRenderContext_->SetBounds(
        paintRect_.GetX(), paintRect_.GetY(), paintRect_.Width(), paintRect_.Height());
    host->MarkModifyDone();
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
    CHECK_NULL_RETURN(extPattern, XCOMPONENT_CONTROLLER_BAD_PARAMETER);
    if (extPattern_.Upgrade()) {
        return XCOMPONENT_CONTROLLER_REPEAT_SET;
    }
    if (handlingSurfaceRenderContext_) {
        // backgroundColor of pip's surface is black
        handlingSurfaceRenderContext_->UpdateBackgroundColor(Color::BLACK);
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
#ifdef ENABLE_ROSEN_BACKEND
    if (frameRateRange.preferred_ != lastFrameRateRange_.preferred_) {
        Rosen::RSInterfaces::GetInstance().NotifyXComponentExpectedFrameRate(GetId(), frameRateRange.preferred_);
    }
    lastFrameRateRange_.Set(range->min, range->max, range->expected);
#endif
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "Id: %{public}" PRIu64 " SetExpectedFrameRateRange"
        "{%{public}d, %{public}d, %{public}d}", displaySync_->GetId(), range->min, range->max, range->expected);
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
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "Id: %{public}" PRIu64 " RegisterOnFrame",
        displaySync_->GetId());
    displaySync_->AddToPipelineOnContainer();
}

void XComponentPattern::HandleUnregisterOnFrameEvent()
{
    CHECK_NULL_VOID(nativeXComponent_);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    CHECK_NULL_VOID(displaySync_);
    displaySync_->UnregisterOnFrame();
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "Id: %{public}" PRIu64 " UnregisterOnFrame",
        displaySync_->GetId());
    displaySync_->DelFromPipelineOnContainer();
    needRecoverDisplaySync_ = false;
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
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
    auto parent = parnetNodeContainer->GetAncestorNodeOfFrame(false);
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

void XComponentPattern::HandleSurfaceChangeEvent(
    bool needForceRender, bool offsetChanged, bool sizeChanged, bool needFireNativeEvent, bool frameOffsetChange)
{
    if (!drawSize_.IsPositive()) {
        return;
    }
    if (frameOffsetChange || offsetChanged) {
        auto offset = globalPosition_ + paintRect_.GetOffset();
        NativeXComponentOffset(offset.GetX(), offset.GetY());
    }
    if (sizeChanged) {
        XComponentSizeChange(paintRect_, needFireNativeEvent);
    }
    if (handlingSurfaceRenderContext_) {
        handlingSurfaceRenderContext_->SetBounds(
            paintRect_.GetX(), paintRect_.GetY(), paintRect_.Width(), paintRect_.Height());
    }
    if (renderSurface_) {
        renderSurface_->SetSurfaceDefaultSize(
            static_cast<int32_t>(paintRect_.Width()), static_cast<int32_t>(paintRect_.Height()));
#ifdef RENDER_EXTRACT_SUPPORTED
        if (!renderSurface_->IsTexture()) {
            auto impl = AceType::DynamicCast<RenderSurfaceImpl>(renderSurface_);
            if (impl != nullptr) {
                impl->SetSurfaceRect(paintRect_.GetX(), paintRect_.GetY(), paintRect_.Width(), paintRect_.Height());
            }
        }
#endif
    }
    if (needForceRender) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    }
}

std::tuple<bool, bool, bool> XComponentPattern::UpdateSurfaceRect()
{
    if (!drawSize_.IsPositive()) {
        return { false, false, false };
    }
    auto preSurfaceSize = surfaceSize_;
    auto preSurfaceOffset = surfaceOffset_;
    if (selfIdealSurfaceWidth_.has_value() && Positive(selfIdealSurfaceWidth_.value()) &&
        selfIdealSurfaceHeight_.has_value() && Positive(selfIdealSurfaceHeight_.value())) {
        surfaceOffset_.SetX(selfIdealSurfaceOffsetX_.has_value()
                                ? selfIdealSurfaceOffsetX_.value()
                                : (drawSize_.Width() - selfIdealSurfaceWidth_.value()) / 2.0f);

        surfaceOffset_.SetY(selfIdealSurfaceOffsetY_.has_value()
                                ? selfIdealSurfaceOffsetY_.value()
                                : (drawSize_.Height() - selfIdealSurfaceHeight_.value()) / 2.0f);
        surfaceSize_ = { selfIdealSurfaceWidth_.value(), selfIdealSurfaceHeight_.value() };
    } else {
        surfaceSize_ = drawSize_;
        surfaceOffset_ = localPosition_;
    }
    auto offsetChanged = preSurfaceOffset != surfaceOffset_;
    auto sizeChanged = preSurfaceSize != surfaceSize_;
    if (offsetChanged || sizeChanged) {
        paintRect_ = { surfaceOffset_, surfaceSize_ };
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            paintRect_ = AdjustPaintRect(
                surfaceOffset_.GetX(), surfaceOffset_.GetY(), surfaceSize_.Width(), surfaceSize_.Height(), true);
        }
    }
    return { offsetChanged, sizeChanged, preSurfaceSize.IsPositive() };
}

void XComponentPattern::LoadNative()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireSurfaceInitEvent(id_.value_or(""), host->GetId());
    OnNativeLoad(reinterpret_cast<FrameNode*>(AceType::RawPtr(host)));
}

void XComponentPattern::OnNativeLoad(FrameNode* frameNode)
{
    hasLoadNativeDone_ = true;
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireLoadEvent(GetId());
}

void XComponentPattern::OnNativeUnload(FrameNode* frameNode)
{
    hasLoadNativeDone_ = false;
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireDestroyEvent(GetId());
}

void XComponentPattern::OnSurfaceCreated()
{
    CHECK_RUN_ON(UI);
    auto width = initSize_.Width();
    auto height = initSize_.Height();
    if (isNativeXComponent_) {
        CHECK_NULL_VOID(nativeXComponentImpl_);
        CHECK_NULL_VOID(nativeXComponent_);
        nativeXComponentImpl_->SetXComponentWidth(static_cast<int32_t>(width));
        nativeXComponentImpl_->SetXComponentHeight(static_cast<int32_t>(height));
        nativeXComponentImpl_->SetSurface(nativeWindow_);
        const auto* callback = nativeXComponentImpl_->GetCallback();
        CHECK_NULL_VOID(callback);
        CHECK_NULL_VOID(callback->OnSurfaceCreated);
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] native OnSurfaceCreated", GetId().c_str());
        ACE_SCOPED_TRACE("XComponent[%s] NativeSurfaceCreated[w:%f,h:%f]", GetId().c_str(), width, height);
        callback->OnSurfaceCreated(nativeXComponent_.get(), nativeWindow_);
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetOrCreateEventHub<XComponentEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireControllerCreatedEvent(surfaceId_, GetId());
    }
}

void XComponentPattern::OnSurfaceChanged(const RectF& surfaceRect, bool needResizeNativeWindow)
{
    CHECK_RUN_ON(UI);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto width = surfaceRect.Width();
    auto height = surfaceRect.Height();
    if (needResizeNativeWindow) {
        AdjustNativeWindowSize(width, height);
    }
    if (isNativeXComponent_) {
        CHECK_NULL_VOID(nativeXComponent_);
        CHECK_NULL_VOID(nativeXComponentImpl_);
        nativeXComponentImpl_->SetXComponentWidth(static_cast<int32_t>(width));
        nativeXComponentImpl_->SetXComponentHeight(static_cast<int32_t>(height));
        auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
        const auto* callback = nativeXComponentImpl_->GetCallback();
        CHECK_NULL_VOID(callback);
        CHECK_NULL_VOID(callback->OnSurfaceChanged);
        {
            ACE_SCOPED_TRACE("XComponent[%s] native OnSurfaceChanged[w:%f,h:%f]", GetId().c_str(), width, height);
            callback->OnSurfaceChanged(nativeXComponent_.get(), surface);
        }
    } else {
        auto eventHub = host->GetOrCreateEventHub<XComponentEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireControllerChangedEvent(surfaceId_, surfaceRect, GetId());
    }
}

void XComponentPattern::OnSurfaceDestroyed(FrameNode* frameNode)
{
    if (isNativeXComponent_) {
        CHECK_RUN_ON(UI);
        CHECK_NULL_VOID(nativeXComponent_);
        CHECK_NULL_VOID(nativeXComponentImpl_);
        auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
        const auto* callback = nativeXComponentImpl_->GetCallback();
        CHECK_NULL_VOID(callback);
        CHECK_NULL_VOID(callback->OnSurfaceDestroyed);
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] native OnSurfaceDestroyed", GetId().c_str());
        ACE_SCOPED_TRACE("XComponent[%s] native OnSurfaceDestroyed", GetId().c_str());
        callback->OnSurfaceDestroyed(nativeXComponent_.get(), surface);
        nativeXComponentImpl_->SetSurface(nullptr);
    } else if (isTypedNode_) {
        RefPtr<FrameNode> host;
        if (!frameNode) {
            host = GetHost();
            CHECK_NULL_VOID(host);
            frameNode = Referenced::RawPtr(host);
        }
        auto eventHub = frameNode->GetOrCreateEventHub<XComponentEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireControllerDestroyedEvent(surfaceId_, GetId());
    }
}

void XComponentPattern::RegisterSurfaceCallbackModeEvent()
{
    if (isTypedNode_ && !surfaceCallbackModeChangeEvent_) {
        surfaceCallbackModeChangeEvent_ = [weak = WeakClaim(this)](SurfaceCallbackMode mode) {
            auto xcPattern = weak.Upgrade();
            CHECK_NULL_VOID(xcPattern);
            xcPattern->OnSurfaceCallbackModeChange(mode);
        };
    }
}

void XComponentPattern::OnSurfaceCallbackModeChange(SurfaceCallbackMode mode)
{
    CHECK_EQUAL_VOID(surfaceCallbackMode_, mode);
    surfaceCallbackMode_ = mode;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->IsOnMainTree()) {
        if (surfaceCallbackMode_ == SurfaceCallbackMode::PIP) {
            HandleSurfaceCreated();
        } else if (surfaceCallbackMode_ == SurfaceCallbackMode::DEFAULT) {
            HandleSurfaceDestroyed();
        }
    }
}

void XComponentPattern::HandleSurfaceCreated()
{
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->RegisterSurface();
    surfaceId_ = screenId_.has_value() ? "" : renderSurface_->GetUniqueId();
    CHECK_NULL_VOID(xcomponentController_);
    xcomponentController_->SetSurfaceId(surfaceId_);
    OnSurfaceCreated();
}

void XComponentPattern::HandleSurfaceDestroyed(FrameNode* frameNode)
{
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->ReleaseSurfaceBuffers();
    renderSurface_->UnregisterSurface();
    CHECK_NULL_VOID(xcomponentController_);
    OnSurfaceDestroyed(frameNode);
    xcomponentController_->SetSurfaceId("");
}

void XComponentPattern::NativeSurfaceShow()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(nativeXComponentImpl_);
    CHECK_NULL_VOID(nativeXComponent_);
    auto* surface = const_cast<void*>(nativeXComponentImpl_->GetSurface());
    const auto surfaceShowCallback = nativeXComponentImpl_->GetSurfaceShowCallback();
    CHECK_NULL_VOID(surfaceShowCallback);
    surfaceShowCallback(nativeXComponent_.get(), surface);
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
    CHECK_NULL_VOID(renderSurface_);
    renderSurface_->ReleaseSurfaceBuffers();
}

void XComponentPattern::OnWindowHide()
{
    if (!hasXComponentInit_ || hasReleasedSurface_ ||
        (type_ != XComponentType::SURFACE && type_ != XComponentType::TEXTURE)) {
        return;
    }
    if (renderSurface_) {
        renderSurface_->OnWindowStateChange(false);
    }
    NativeSurfaceHide();
    hasReleasedSurface_ = true;
}

void XComponentPattern::OnWindowShow()
{
    if (!hasXComponentInit_ || !hasReleasedSurface_ ||
        (type_ != XComponentType::SURFACE && type_ != XComponentType::TEXTURE)) {
        return;
    }
    if (renderSurface_) {
        renderSurface_->OnWindowStateChange(true);
    }
    NativeSurfaceShow();
    hasReleasedSurface_ = false;
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
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
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

void XComponentPattern::EnableAnalyzer(bool enable)
{
    isEnableAnalyzer_ = enable;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        return;
    }

    CHECK_NULL_VOID(!imageAnalyzerManager_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(host, ImageAnalyzerHolder::XCOMPONENT);
}

void XComponentPattern::SetImageAIOptions(void* options)
{
    if (!imageAnalyzerManager_) {
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(GetHost(), ImageAnalyzerHolder::XCOMPONENT);
    }
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAIOptions(options);
}

void XComponentPattern::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed)
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
    auto* context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CreateAnalyzerOverlay();
        },
        "ArkUIXComponentCreateAnalyzerOverlay");
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
    host->SetOverlayNode(nullptr);

    auto layoutProperty = GetLayoutProperty<XComponentLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto padding  = layoutProperty->CreatePaddingAndBorder();
    Rect contentRect = { padding.left.value_or(0), padding.top.value_or(0), drawSize_.Width(), drawSize_.Height() };
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto nailPixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(nailPixelMap);
    auto pixelMap = nailPixelMap->GetCropPixelMap(contentRect);
    CHECK_NULL_VOID(pixelMap);

    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->CreateAnalyzerOverlay(pixelMap);
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

void XComponentPattern::SetSurfaceRotation(bool isLock)
{
    if (type_ != XComponentType::SURFACE) {
        return;
    }
    isSurfaceLock_ = isLock;

    CHECK_NULL_VOID(handlingSurfaceRenderContext_);
    handlingSurfaceRenderContext_->SetSurfaceRotation(isLock);
#ifdef RENDER_EXTRACT_SUPPORTED
    CHECK_NULL_VOID(renderSurface_);
    if (!renderSurface_->IsTexture()) {
        auto impl = AceType::DynamicCast<RenderSurfaceImpl>(renderSurface_);
        CHECK_NULL_VOID(impl);
        impl->SetSurfaceRotation(isLock);
    }
#endif
}

void XComponentPattern::SetRenderFit(RenderFit renderFit)
{
    CHECK_NULL_VOID(handlingSurfaceRenderContext_);
    renderFit_ = renderFit;
    handlingSurfaceRenderContext_->SetRenderFit(renderFit);
}

void XComponentPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("xcomponentId", id_.value_or("no id").c_str());
    json->Put("xcomponentType", XComponentTypeToString(type_).c_str());
    json->Put("libraryName", libraryname_.value_or("no library name").c_str());
    json->Put("surfaceId", surfaceId_.c_str());
    json->Put("surfaceRect", paintRect_.ToString().c_str());
}

void XComponentPattern::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    if (renderSurface_) {
        renderSurface_->DumpInfo(json);
    }
}

void XComponentPattern::SetScreenId(uint64_t screenId)
{
    screenId_ = screenId;
    renderContextForSurface_->SetScreenId(screenId);
    surfaceId_ = "";
    xcomponentController_->SetSurfaceId(surfaceId_);
}

void XComponentPattern::EnableSecure(bool isSecure)
{
    if (type_ != XComponentType::SURFACE) {
        return;
    }
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContextForSurface_->SetSecurityLayer(isSecure);
    isEnableSecure_ = isSecure;
}

void XComponentPattern::HdrBrightness(float hdrBrightness)
{
    if (type_ != XComponentType::SURFACE) {
        return;
    }
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContextForSurface_->SetHDRBrightness(std::clamp(hdrBrightness, 0.0f, 1.0f));
    hdrBrightness_ = std::clamp(hdrBrightness, 0.0f, 1.0f);
}

void XComponentPattern::EnableTransparentLayer(bool isTransparentLayer)
{
    if (type_ != XComponentType::SURFACE) {
        return;
    }
    CHECK_NULL_VOID(renderContextForSurface_);
    renderContextForSurface_->SetTransparentLayer(isTransparentLayer);
    isTransparentLayer_ = isTransparentLayer;
}

RenderFit XComponentPattern::GetSurfaceRenderFit() const
{
    CHECK_NULL_RETURN(handlingSurfaceRenderContext_, RenderFit::RESIZE_FILL);
    return handlingSurfaceRenderContext_->GetRenderFit().value_or(RenderFit::RESIZE_FILL);
}

bool XComponentPattern::GetEnableAnalyzer()
{
    return isEnableAnalyzer_;
}

void XComponentPattern::NativeStartImageAnalyzer(std::function<void(int32_t)>& callback)
{
    CHECK_NULL_VOID(callback);
    if (!isOnTree_ || !isEnableAnalyzer_) {
        return callback(ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED);
    }
    if (!IsSupportImageAnalyzerFeature()) {
        return callback(ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED);
    }
    if (isNativeImageAnalyzing_) {
        return callback(ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING);
    }
    isNativeImageAnalyzing_ = true;

    OnAnalyzedCallback nativeOnAnalyzed = [weak = WeakClaim(this),
        callback](ImageAnalyzerState state) {
        CHECK_NULL_VOID(callback);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto statusCode = XComponentUtils::ConvertNativeXComponentAnalyzerStatus(state);
        callback(statusCode);
        pattern->isNativeImageAnalyzing_ = false;
    };

    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAnalyzerCallback(nativeOnAnalyzed);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->CreateAnalyzerOverlay();
        },
        "ArkUIXComponentCreateAnalyzerOverlay");
}

RSCanvas* XComponentPattern::LockCanvas()
{
    CHECK_NULL_RETURN(nativeWindow_, nullptr);
    auto canvas = RSCanvasUtils::CreateLockCanvas(reinterpret_cast<OHNativeWindow*>(nativeWindow_));
    if (canvas == nullptr) {
        TAG_LOGW(
            AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] LockCanvas's returnValue is nullptr", GetId().c_str());
    }
    return canvas;
}

void XComponentPattern::UnlockCanvasAndPost(RSCanvas* canvas)
{
    CHECK_NULL_VOID(canvas);
    CHECK_NULL_VOID(nativeWindow_);
    bool isUnlockOk = RSCanvasUtils::UnlockCanvas(canvas, reinterpret_cast<OHNativeWindow*>(nativeWindow_));
    if (!isUnlockOk) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] UnlockCanvasAndPost failed", GetId().c_str());
    }
}
} // namespace OHOS::Ace::NG
