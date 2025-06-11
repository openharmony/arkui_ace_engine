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

#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_pattern.h"

#include <optional>

#include "core/event/key_event.h"
#include "core/event/pointer_event.h"
#include "session/host/include/extension_session.h"
#include "session/host/include/session.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_extra_input_data.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "base/error/error_code.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper.h"
#include "core/components_ng/pattern/ui_extension/session_wrapper_factory.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_adapter.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_session_wrapper_impl.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_proxy.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/event/ace_events.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
 
namespace OHOS::Ace::NG {
namespace {
constexpr char UI_EXTENSION_TYPE_KEY[] = "ability.want.params.uiExtensionType";
}
 
PreviewUIExtensionPattern::PreviewUIExtensionPattern(): SecurityUIExtensionPattern::SecurityUIExtensionPattern()
{
    PLATFORM_LOGI("The Preview UIExtension is created.");
}
 
PreviewUIExtensionPattern::~PreviewUIExtensionPattern()
{
    PLATFORM_LOGI("PreviewUIExtension The Security UIExtension is destroyed.");
}
 
void PreviewUIExtensionPattern::Initialize(const NG::UIExtensionConfig& config)
{
    if (sessionWrapper_ != nullptr) {
        return;
    }
    sessionType_ = SessionType::PREVIEW_UI_EXTENSION_ABILITY;
    SessionCreateParam sessionCreateParam;
    sessionCreateParam.hostPattern = WeakClaim(this);
    sessionCreateParam.instanceId = instanceId_;
    sessionCreateParam.isTransferringCaller = config.transferringCaller;
    sessionWrapper_ = SessionWrapperFactory::CreateSessionWrapper(
        sessionType_, sessionCreateParam);
    accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterUIExtension>(sessionWrapper_);
}
 
void PreviewUIExtensionPattern::UpdateWant(const RefPtr<OHOS::Ace::WantWrap>& wantWrap)
{
    if (!wantWrap) {
        PLATFORM_LOGW("wantWrap is nullptr");
        return;
    }
    auto wantWrapOhos = AceType::DynamicCast<WantWrapOhos>(wantWrap);
    if (!wantWrapOhos) {
        PLATFORM_LOGW("DynamicCast failed, wantWrapOhos is nullptr");
        return;
    }
    auto want = wantWrapOhos->GetWant();
    UpdateWant(want);
}
 
void PreviewUIExtensionPattern::UpdateWant(const AAFwk::Want& want)
{
    uiExtensionType_ = want.GetStringParam(UI_EXTENSION_TYPE_KEY);
    if (!CheckConstraint()) {
        PLATFORM_LOGE("PreviewUIExtension Check constraint failed.");
        return;
    }
 
    CHECK_NULL_VOID(sessionWrapper_);
    PLATFORM_LOGI("PreviewUIExtension The current state is '%{public}s' when UpdateWant.", ToString(state_));
    bool isBackground = state_ == AbilityState::BACKGROUND;
    // Prohibit rebuilding the session unless the Want is updated.
    if (sessionWrapper_->IsSessionValid()) {
        auto sessionWant = sessionWrapper_->GetWant();
        if (sessionWant == nullptr) {
            PLATFORM_LOGW("PreviewUIExtension The sessionWrapper want is nulllptr.");
            return;
        }
        if (sessionWant->IsEquals(want)) {
            return;
        }
        PLATFORM_LOGI("PreviewUIExtension The old want bundle = %{public}s, ability = %{public}s",
            sessionWant->GetElement().GetBundleName().c_str(), sessionWant->GetElement().GetAbilityName().c_str());
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->RemoveChild(contentNode_);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        NotifyDestroy();
        // reset callback, in order to register childtree call back again when onConnect to new ability
        ResetAccessibilityChildTreeCallback();
    }
 
    MountPlaceholderNode();
    SessionConfig config;
    config.uiExtensionUsage = UIExtensionUsage::PREVIEW_EMBEDDED;
    sessionWrapper_->CreateSession(want, config);
    if (isBackground) {
        PLATFORM_LOGW("PreviewUIExtension Unable to StartUiextensionAbility while in the background.");
        return;
    }
    NotifyForeground();
}

void PreviewUIExtensionPattern::OnAttachContext(PipelineContext *context)
{
    CHECK_NULL_VOID(context);
    auto newInstanceId = context->GetInstanceId();
    PLATFORM_LOGI("OnAttachContext newInstanceId: %{public}d, oldInstanceId: %{public}d",
        newInstanceId, instanceId_);
    if (newInstanceId != instanceId_) {
        instanceId_ = newInstanceId;
        UpdateSessionInstanceId(newInstanceId);
    }
}

void PreviewUIExtensionPattern::UpdateSessionInstanceId(int32_t instanceId)
{
    auto sessionWrapperImpl = AceType::DynamicCast<PreviewSessionWrapperImpl>(sessionWrapper_);
    if (!sessionWrapperImpl) {
        PLATFORM_LOGW("DynamicCast failed, PreviewSessionWrapperImpl is nullptr");
        return;
    }
    sessionWrapperImpl->UpdateInstanceId(instanceId);
}
 
void PreviewUIExtensionPattern::OnConnect()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(sessionWrapper_);
    PLATFORM_LOGI("PreviewUIExtension The session is connected and the current state is '%{public}s'.",
        ToString(state_));
    ContainerScope scope(instanceId_);
    contentNode_ = FrameNode::CreateFrameNode(V2::UI_EXTENSION_SURFACE_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    contentNode_->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    contentNode_->SetHitTestMode(HitTestMode::HTMNONE);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto&& opts = host->GetLayoutProperty()->GetSafeAreaExpandOpts();
    if (opts && opts->Expansive()) {
        contentNode_->GetLayoutProperty()->UpdateSafeAreaExpandOpts(*opts);
        contentNode_->MarkModifyDone();
    }
    auto context = AceType::DynamicCast<NG::RosenRenderContext>(contentNode_->GetRenderContext());
    CHECK_NULL_VOID(context);
    auto surfaceNode = sessionWrapper_->GetSurfaceNode();
    if (!surfaceNode) {
        PLATFORM_LOGE("PreviewUIExtension Get surfaceNode from session is null.");
        return;
    }
    context->SetRSNode(surfaceNode);
    RemovePlaceholderNode();
    host->AddChild(contentNode_, 0);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    surfaceNode->CreateNodeInRenderThread();
    FireOnRemoteReadyCallback();
    auto focusHub = host->GetFocusHub();
    bool isFocused = focusHub && focusHub->IsCurrentFocus();
    RegisterVisibleAreaChange();
    DispatchFocusState(isFocused);
    DispatchFollowHostDensity(GetDensityDpi());
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto uiExtensionManager = pipeline->GetUIExtensionManager();
    auto weakSecurityUIExtension = AceType::WeakClaim<SecurityUIExtensionPattern>(this);
    uiExtensionManager->AddAliveUIExtension(host->GetId(), weakSecurityUIExtension);
    if (isFocused) {
        uiExtensionManager->RegisterSecurityUIExtensionInFocus(
            WeakClaim(this), sessionWrapper_);
    }
    ReDispatchWantParams();
    InitializeAccessibility();
    InitBusinessDataHandleCallback();
}
 
class PreviewUECAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
    public:
    PreviewUECAccessibilitySAObserverCallback(
        const WeakPtr<PreviewUIExtensionPattern> &weakPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakUECPattern_(weakPattern)
    {}
 
    ~PreviewUECAccessibilitySAObserverCallback() override = default;
 
    bool OnState(bool state) override
    {
        auto pattern = weakUECPattern_.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        if (state) {
            pattern->TransferAccessibilityRectInfo(true);
        }
        return true;
    }
private:
    WeakPtr<PreviewUIExtensionPattern> weakUECPattern_;
};
 
void PreviewUIExtensionPattern::OnAttachToFrameNode()
{
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onAreaChangedFunc = [weak = WeakClaim(this)](
        const RectF& oldRect,
        const OffsetF& oldOrigin,
        const RectF& rect,
        const OffsetF& origin) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->DispatchDisplayArea();
    };
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));
    pipeline->AddOnAreaChangeNode(host->GetId());
    callbackId_ = pipeline->RegisterSurfacePositionChangedCallback(
        [weak = WeakClaim(this)](int32_t, int32_t) {
            auto pattern = weak.Upgrade();
            if (pattern) {
                pattern->TransferAccessibilityRectInfo();
                pattern->DispatchDisplayArea(true);
            }
        });
    host->RegisterNodeChangeListener();
    accessibilitySAObserverCallback_ = std::make_shared<PreviewUECAccessibilitySAObserverCallback>(
        WeakClaim(this), host->GetAccessibilityId());
    #ifndef ACE_UNITTEST
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->RegisterAccessibilitySAObserverCallback(host->GetAccessibilityId(),
        accessibilitySAObserverCallback_);
    #endif
    PLATFORM_LOGI("PreviewUIExtension OnAttachToFrameNode");
}

void PreviewUIExtensionPattern::FireOnRemoteReadyCallback()
{
    PLATFORM_LOGI("PreviewUIExtension The current state is '%{public}s'.", ToString(state_));
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<UIExtensionHub>();
    CHECK_NULL_VOID(eventHub);
    auto weakSecurityUIExtension = AceType::WeakClaim<SecurityUIExtensionPattern>(this);
    auto suec = weakSecurityUIExtension.Upgrade();
    eventHub->FireOnRemoteReadyCallback(
        MakeRefPtr<NG::SecurityUIExtensionProxy>(sessionWrapper_, suec));
}

void PreviewUIExtensionPattern::RegisterVisibleAreaChange()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto uiExtension = weak.Upgrade();
        CHECK_NULL_VOID(uiExtension);
        uiExtension->OnVisibleChange(visible);
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<double> ratioList = { 0.0 };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false);
}

void PreviewUIExtensionPattern::InitializeAccessibility()
{
    if (accessibilityChildTreeCallback_ != nullptr) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto ngPipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(ngPipeline);
    auto frontend = ngPipeline->GetFrontend();
    CHECK_NULL_VOID(frontend);
    auto accessibilityManager = frontend->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    auto frameNode = frameNode_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    int64_t accessibilityId = frameNode->GetAccessibilityId();
    accessibilityChildTreeCallback_ = std::make_shared<PlatformAccessibilityChildTreeCallback>(
        WeakClaim(this), accessibilityId);
    CHECK_NULL_VOID(accessibilityChildTreeCallback_);
    auto realHostWindowId = ngPipeline->GetRealHostWindowId();
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            realHostWindowId, accessibilityManager->GetTreeId());
    }
    PLATFORM_LOGI("PreviewUIExtension: %{public}" PRId64
        " register child tree, realHostWindowId: %{public}u",
        accessibilityId, realHostWindowId);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId, accessibilityChildTreeCallback_);
}
} // namespace OHOS::Ace::NG