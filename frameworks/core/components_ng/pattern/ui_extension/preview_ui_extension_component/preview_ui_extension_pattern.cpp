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
#include "core/components_ng/pattern/ui_extension/preview_ui_extension_component/preview_ui_extension_adapter.h"
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
 
namespace {
    constexpr char PID_FLAG[] = "pidflag";
    constexpr char NO_EXTRA_UIE_DUMP[] = "-nouie";
}
namespace OHOS::Ace::NG {
 
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

void PreviewUIExtensionPattern::FireOnErrorCallback(
    int32_t code, const std::string& name, const std::string& message)
{
    state_ = AbilityState::NONE;
    PlatformPattern::FireOnErrorCallback(code, name, message);
    SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_NONE));
    if (sessionWrapper_ && sessionWrapper_->IsSessionValid()) {
        if (!IsShowPlaceholder()) {
            auto host = GetHost();
            if (host) {
                host->RemoveChildAtIndex(0);
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            }
        }
        sessionWrapper_->NotifyDestroy(false);
        sessionWrapper_->DestroySession();
    }
}

void PreviewUIExtensionPattern::RegisterVisibleAreaChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto uiExtension = weak.Upgrade();
        CHECK_NULL_VOID(uiExtension);
        uiExtension->OnVisibleChange(visible);
    };
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
    realHostWindowId_ = realHostWindowId;
    focusWindowId_ = ngPipeline->GetFocusWindowId();
    if (accessibilityManager->IsRegister()) {
        accessibilityChildTreeCallback_->OnRegister(
            realHostWindowId, accessibilityManager->GetTreeId());
    }
    PLATFORM_LOGI("PreviewUIExtension: %{public}" PRId64
        " register child tree, realHostWindowId: %{public}u",
        accessibilityId, realHostWindowId);
    accessibilityManager->RegisterAccessibilityChildTreeCallback(accessibilityId, accessibilityChildTreeCallback_);
}

void PreviewUIExtensionPattern::DumpInfo()
{
    CHECK_NULL_VOID(sessionWrapper_);
    PLATFORM_LOGI("Dump PreviewUIE Info In String Format");
    DumpLog::GetInstance().AddDesc(std::string("focusWindowId: ").append(std::to_string(focusWindowId_)));
    DumpLog::GetInstance().AddDesc(std::string("realHostWindowId: ").append(std::to_string(realHostWindowId_)));
    DumpLog::GetInstance().AddDesc(std::string("displayArea: ").append(displayArea_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("reason: ").append(std::to_string(sessionWrapper_->GetReasonDump())));
    DumpLog::GetInstance().AddDesc(std::string("abilityState: ").append(ToString(state_)));
    std::string eventProxyStr = "[]";
    if (platformEventProxy_) {
        eventProxyStr = platformEventProxy_->GetCurEventProxyToString();
    }
    DumpLog::GetInstance().AddDesc(std::string("eventProxy: ").append(eventProxyStr));

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra preview uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        PLATFORM_LOGI("Not Support Dump Extra Preview UIE Info");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dumpNodeIter = std::find(params.begin(), params.end(), std::to_string(host->GetId()));
    if (dumpNodeIter != params.end()) {
        params.erase(dumpNodeIter);
    }
    if (!container->IsUIExtensionWindow()) {
        params.push_back(PID_FLAG);
    }
    params.push_back(std::to_string(getpid()));
    std::vector<std::string> dumpInfo;
    sessionWrapper_->NotifyUieDump(params, dumpInfo);
    for (const std::string& info : dumpInfo) {
        DumpLog::GetInstance().AddDesc(std::string("Preview UI Extension info: ").append(info));
    }
}

void PreviewUIExtensionPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(sessionWrapper_);
    PLATFORM_LOGI("Dump Preview UIE Info In Json Format");
    json->Put("focusWindowId: ", std::to_string(focusWindowId_).c_str());
    json->Put("realHostWindowId: ", std::to_string(realHostWindowId_).c_str());
    json->Put("displayArea: ", displayArea_.ToString().c_str());
    json->Put("reason: ", std::to_string(sessionWrapper_->GetReasonDump()).c_str());
    json->Put("abilityState: ", ToString(state_));
    std::string eventProxyStr = "[]";
    if (platformEventProxy_) {
        eventProxyStr = platformEventProxy_->GetCurEventProxyToString();
    }
    json->Put("eventProxy: ", eventProxyStr.c_str());

    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    std::vector<std::string> params = container->GetUieParams();
    // Use -nouie to choose not dump extra preview uie info
    if (std::find(params.begin(), params.end(), NO_EXTRA_UIE_DUMP) != params.end()) {
        PLATFORM_LOGI("Not Support Dump Extra Preview UIE Info");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dumpNodeIter = std::find(params.begin(), params.end(), std::to_string(host->GetId()));
    if (dumpNodeIter != params.end()) {
        params.erase(dumpNodeIter);
    }
    if (!container->IsUIExtensionWindow()) {
        params.push_back(PID_FLAG);
    }
    params.push_back(std::to_string(getpid()));
    std::vector<std::string> dumpInfo;
    sessionWrapper_->NotifyUieDump(params, dumpInfo);
    for (const std::string& info : dumpInfo) {
        json->Put("Preview UI Extension info: ", info.c_str());
    }
}
} // namespace OHOS::Ace::NG