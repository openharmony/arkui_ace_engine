/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"

#include "interfaces/native/event/ui_input_event_impl.h"
#include "interfaces/native/ui_input_event.h"

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
#include "feature/anco_manager/rs_ext_node_operation.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#endif

#include "core/components_ng/event/input_event.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_ext_surface_callback_client.h"
#include "core/event/event_info_convertor.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline_ng/pipeline_context.h"


namespace OHOS::Ace::NG {
namespace {
const std::string BUFFER_USAGE_XCOMPONENT = "xcomponent";
}

void XComponentPattern::InitSurfaceMultiThread(const RefPtr<FrameNode>& host)
{
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
    std::string xComponentType = GetType() == XComponentType::SURFACE ? "s" : "t";
    renderSurface_->SetBufferUsage(BUFFER_USAGE_XCOMPONENT + "-" + xComponentType + "-" + GetId());
    if (type_ == XComponentType::SURFACE) {
        InitializeRenderContext();
        if (!SystemProperties::GetExtSurfaceEnabled()) {
            renderSurface_->SetRenderContext(renderContextForSurface_);
        } else {
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
}

void XComponentPattern::InitControllerMultiThread()
{
    CHECK_NULL_VOID(xcomponentController_);
    if (!isTypedNode_) {
        xcomponentController_->SetSurfaceId(surfaceId_);
    }
    auto* controllerNG = static_cast<XComponentControllerNG*>(xcomponentController_.get());
    CHECK_NULL_VOID(controllerNG);
    controllerNG->SetPattern(AceType::Claim(this));
}

void XComponentPattern::RegisterContextEventMultiThread(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddOnAreaChangeNode(host->GetId());
    if (!HasTransformHintChangedCallbackId()) {
        RegisterTransformHintCallback(AceType::RawPtr(pipelineContext));
    }
    CHECK_NULL_VOID(xcomponentController_);
    auto uiTaskExecutor = SingleTaskExecutor::Make(pipelineContext->GetTaskExecutor(), TaskExecutor::TaskType::UI);
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
}

void XComponentPattern::OnAttachToMainTreeMultiThread(const RefPtr<FrameNode>& host)
{
    isOnTree_ = true;
    RegisterContextEventMultiThread(host);
    if (isTypedNode_ && surfaceCallbackMode_ == SurfaceCallbackMode::DEFAULT) {
        HandleSurfaceCreated();
    }
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

void XComponentPattern::OnDetachFromMainTreeMultiThread(const RefPtr<FrameNode>& host)
{
    isOnTree_ = false;
    if (isTypedNode_ && surfaceCallbackMode_ == SurfaceCallbackMode::DEFAULT) {
        HandleSurfaceDestroyed();
    }
    CHECK_NULL_VOID(host);
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        if (displaySync_ && displaySync_->IsOnPipeline()) {
            TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "OnDetachFromMainTree:remove displaySync: "
                "%{public}s(%{public}" PRIu64 ")", GetId().c_str(), displaySync_->GetId());
            displaySync_->DelFromPipelineOnContainer();
            needRecoverDisplaySync_ = true;
        }
    }
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    if (HasTransformHintChangedCallbackId()) {
        context->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
        transformHintChangedCallbackId_ = std::nullopt;
    }
}

void XComponentPattern::OnDetachFromFrameNodeMultiThread(FrameNode* frameNode)
{
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
            auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
            CHECK_NULL_VOID(eventHub);
            {
                eventHub->FireDestroyEvent(GetId());
            }
            if (id_.has_value()) {
                eventHub->FireDetachEvent(id_.value());
            }
            {
                eventHub->FireControllerDestroyedEvent(surfaceId_, GetId());
            }
#ifdef RENDER_EXTRACT_SUPPORTED
            if (renderContextForSurface_) {
                renderContextForSurface_->RemoveSurfaceChangedCallBack();
            }
#endif
        }
    }
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().DisableSelfRender();
    }
}

void XComponentPatternV2::InitSurfaceMultiThread(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderContext->SetClipToFrame(true);
    renderContext->SetClipToBounds(true);
    renderSurface_ = RenderSurface::Create();
    renderSurface_->SetInstanceId(GetHostInstanceId());
    if (type_ == XComponentType::SURFACE) {
        InitializeRenderContext();
        renderSurface_->SetRenderContext(renderContextForSurface_);
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
    surfaceId_ = renderSurface_->GetUniqueId();
}

void XComponentPatternV2::OnAttachToMainTreeMultiThread(const RefPtr<FrameNode>& host)
{
    RegisterContextEventMultiThread(host);
    isOnTree_ = true;
    if (autoInitialize_) {
        HandleSurfaceCreated();
    }
}

void XComponentPatternV2::RegisterContextEventMultiThread(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    if (!HasTransformHintChangedCallbackId()) {
        RegisterTransformHintCallback(AceType::RawPtr(pipelineContext));
    }
}

void XComponentPatternV2::OnDetachFromMainTreeMultiThread(const RefPtr<FrameNode>& host)
{
    isOnTree_ = false;
    if (autoInitialize_) {
        HandleSurfaceDestroyed();
    }
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(id);
    if (HasTransformHintChangedCallbackId()) {
        pipeline->UnregisterTransformHintChangedCallback(transformHintChangedCallbackId_.value_or(-1));
        transformHintChangedCallbackId_ = std::nullopt;
    }
}

void XComponentPatternV2::OnDetachFromFrameNodeMultiThread()
{
    if (FrameReport::GetInstance().GetEnable()) {
        FrameReport::GetInstance().DisableSelfRender();
    }
    HandleSurfaceDestroyed();
    
    CHECK_NULL_VOID(surfaceHolder_);
    surfaceHolder_->nativeWindow_ = nullptr;
    surfaceHolder_->node_ = nullptr;
}

}
