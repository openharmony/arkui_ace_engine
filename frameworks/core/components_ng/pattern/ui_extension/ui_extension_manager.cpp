/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_manager.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
UIExtensionIdUtility::UIExtensionIdUtility() {}

UIExtensionIdUtility::~UIExtensionIdUtility() {}

int32_t UIExtensionIdUtility::ApplyExtensionId()
{
    std::lock_guard<std::mutex> poolMutex(poolMutex_);
    for (int32_t index = 0; index < UI_EXTENSION_ID_FIRST_MAX; index++) {
        if (!idPool_.test(index)) {
            idPool_.set(index, 1);
            return index + 1;
        }
    }
    return UI_EXTENSION_UNKNOW_ID;
}

void UIExtensionIdUtility::RecycleExtensionId(int32_t id)
{
    std::lock_guard<std::mutex> poolMutex(poolMutex_);
    if ((id > UI_EXTENSION_UNKNOW_ID) && (id <= UI_EXTENSION_ID_FIRST_MAX)) {
        idPool_.set(id - 1, 0);
    }
}

void UIExtensionManager::RegisterUIExtensionInFocus(
    const WeakPtr<UIExtensionPattern>& uiExtensionFocused, const WeakPtr<SessionWrapper>& sessionWrapper)
{
    securityUiExtensionFocused_ = nullptr;
    uiExtensionFocused_ = uiExtensionFocused;
    sessionWrapper_ = sessionWrapper;
}

void UIExtensionManager::RegisterSecurityUIExtensionInFocus(
    const WeakPtr<SecurityUIExtensionPattern>& uiExtensionFocused,
    const WeakPtr<SessionWrapper>& sessionWrapper)
{
    uiExtensionFocused_ = nullptr;
    securityUiExtensionFocused_ = uiExtensionFocused;
    sessionWrapper_ = sessionWrapper;
}

bool UIExtensionManager::OnBackPressed()
{
    auto sessionWrapper = sessionWrapper_.Upgrade();
    if (sessionWrapper) {
        return sessionWrapper->NotifyBackPressedSync();
    }

    return HandleUnfocusedModalUecBackPressed();
}

void UIExtensionManager::DumpUIExt()
{
    auto pattern = uiExtensionFocused_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->DumpOthers();
}

bool UIExtensionManager::HandleUnfocusedModalUecBackPressed()
{
    std::lock_guard<std::mutex> aliveUIExtensionMutex(aliveUIExtensionMutex_);
    for (auto item = aliveUIExtensions_.rbegin(); item != aliveUIExtensions_.rend(); ++item) {
        auto uiExtension = item->second.Upgrade();
        if (uiExtension == nullptr) {
            continue;
        }

        if (!uiExtension->IsModalUec()) {
            continue;
        }

        bool isForeground = uiExtension->IsForeground();
        bool isLastModal = IsLastModalUec(uiExtension->GetHost());
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "HandleUnfocusedModalUecBackPressed,"
            " sessionId: %{public}d, isForeground: %{public}d, isLastModal: %{public}d",
            uiExtension->GetSessionId(), isForeground, isLastModal);
        if (!isForeground || !isLastModal) {
            continue;
        }

        auto session = uiExtension->GetSessionWrapper();
        if (session) {
            return session->NotifyBackPressedSync();
        }
    }

    return false;
}

bool UIExtensionManager::IsLastModalUec(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto parentNode = frameNode->GetParent();
    CHECK_NULL_RETURN(parentNode, false);
    if (parentNode->GetTag() != V2::MODAL_PAGE_TAG) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "parentNode not modalPage, parentNode tag: %{public}s",
            parentNode->GetTag().c_str());
        return false;
    }

    auto grandpaNode = parentNode->GetParent();
    if (grandpaNode == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "ModalPage no parent.");
        return false;
    }

    auto lastChild = grandpaNode->GetLastChild();
    if (lastChild == nullptr) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "LastChild is null.");
        return false;
    }

    if (lastChild != parentNode) {
        TAG_LOGW(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "ModalPage is not the last "
            "child of rootNode, lastChild tag: %{public}s, parentNode tag: %{public}s",
            lastChild->GetTag().c_str(), parentNode->GetTag().c_str());
        return false;
    }

    return true;
}

bool UIExtensionManager::IsWrapExtensionAbilityId(int64_t elementId)
{
    return elementId > UI_EXTENSION_OFFSET_MIN;
}

bool UIExtensionManager::SendAccessibilityEventInfo(const Accessibility::AccessibilityEventInfo& eventInfo,
    int64_t uiExtensionOffset, const RefPtr<PipelineBase>& pipeline)
{
    CHECK_NULL_RETURN(pipeline, false);
    auto instanceId = pipeline->GetInstanceId();
    auto window = Platform::AceContainer::GetUIWindow(instanceId);
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->TransferAccessibilityEvent(eventInfo, uiExtensionOffset);
    return ret == OHOS::Rosen::WMError::WM_OK;
}

std::pair<int64_t, int64_t> UIExtensionManager::UnWrapExtensionAbilityId(int64_t extensionOffset, int64_t elementId)
{
    if (extensionOffset == 0) {
        return std::pair<int64_t, int64_t>(0, 0);
    }
    int64_t index = elementId / extensionOffset;
    int64_t abilityId = elementId % extensionOffset;
    return std::pair<int64_t, int64_t>(index, abilityId);
}

const RefPtr<FrameNode> UIExtensionManager::GetFocusUiExtensionNode()
{
    auto uiExtensionFocused = uiExtensionFocused_.Upgrade();
    CHECK_NULL_RETURN(uiExtensionFocused, nullptr);
    return uiExtensionFocused->GetHost();
}

int32_t UIExtensionManager::ApplyExtensionId()
{
    return UIExtensionIdUtility::GetInstance().ApplyExtensionId();
}

void UIExtensionManager::RecycleExtensionId(int32_t id)
{
    UIExtensionIdUtility::GetInstance().RecycleExtensionId(id);
}

void UIExtensionManager::AddAliveUIExtension(int32_t nodeId, const WeakPtr<UIExtensionPattern>& uiExtension)
{
    std::lock_guard<std::mutex> aliveUIExtensionMutex(aliveUIExtensionMutex_);
    RegisterListenerIfNeeded();
    aliveUIExtensions_.try_emplace(nodeId, uiExtension);
}

void UIExtensionManager::AddAliveUIExtension(
    int32_t nodeId, const WeakPtr<SecurityUIExtensionPattern>& uiExtension)
{
    aliveSecurityUIExtensions_.try_emplace(nodeId, uiExtension);
}

void UIExtensionManager::TransferOriginAvoidArea(const Rosen::AvoidArea& avoidArea, uint32_t type)
{
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->DispatchOriginAvoidArea(avoidArea, type);
        }
    }

    for (const auto& it : aliveSecurityUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->DispatchOriginAvoidArea(avoidArea, type);
        }
    }
}

void UIExtensionManager::RemoveDestroyedUIExtension(int32_t nodeId)
{
    {
        std::lock_guard<std::mutex> aliveUIExtensionMutex(aliveUIExtensionMutex_);
        auto it = aliveUIExtensions_.find(nodeId);
        if (it != aliveUIExtensions_.end()) {
            aliveUIExtensions_.erase(nodeId);
        }
        if (aliveUIExtensions_.empty()) {
            UnregisterListenerIfNeeded();
        }
    }

    auto iter = aliveSecurityUIExtensions_.find(nodeId);
    if (iter != aliveSecurityUIExtensions_.end()) {
        aliveSecurityUIExtensions_.erase(nodeId);
    }
}

bool UIExtensionManager::NotifyOccupiedAreaChangeInfo(const sptr<Rosen::OccupiedAreaChangeInfo>& info)
{
    int32_t keyboardHeight = static_cast<int32_t>(info->rect_.height_);
    if (keyboardHeight != 0) {
        auto sessionWrapper = sessionWrapper_.Upgrade();
        return sessionWrapper && sessionWrapper->NotifyOccupiedAreaChangeInfo(info, true);
    }
    // keyboardHeight is 0, broadcast it.
    bool ret = false;
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            auto session = uiExtension->GetSessionWrapper();
            if (session && session->IsSessionValid()) {
                ret |= session->NotifyOccupiedAreaChangeInfo(info);
            }
        }
    }
    return ret;
}

void UIExtensionManager::NotifySizeChangeReason(
    WindowSizeChangeReason type, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction)
{
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->NotifySizeChangeReason(type, rsTransaction);
        }
    }

    for (const auto& it : aliveSecurityUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->NotifySizeChangeReason(type, rsTransaction);
        }
    }
}

bool UIExtensionManager::IsShowPlaceholder(int32_t nodeId)
{
    auto it = aliveUIExtensions_.find(nodeId);
    if (it != aliveUIExtensions_.end()) {
        auto uiExtension = it->second.Upgrade();
        if (uiExtension) {
            return uiExtension->IsShowPlaceholder();
        }
    }

    auto itSec = aliveSecurityUIExtensions_.find(nodeId);
    if (itSec != aliveSecurityUIExtensions_.end()) {
        auto secExtension = itSec->second.Upgrade();
        if (secExtension) {
            return secExtension->IsShowPlaceholder();
        }
    }
    return true;
}

void UIExtensionManager::UpdateSessionViewportConfig(const ViewportConfig& config)
{
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension == nullptr) {
            continue;
        }

        uint64_t displayId = 0;
        auto instanceId = uiExtension->GetInstanceIdFromHost();
        auto container = Platform::AceContainer::GetContainer(instanceId);
        if (container) {
            displayId = container->GetCurrentDisplayId();
        }
        SessionViewportConfig newConfig = {
            .isDensityFollowHost_ = uiExtension->GetDensityDpi(),
            .density_ = config.Density(),
            .displayId_ = displayId,
            .orientation_ = config.Orientation(),
            .transform_ = config.TransformHint(),
        };
        auto oldConfig = uiExtension->GetSessionViewportConfig();
        if (oldConfig.density_ == newConfig.density_ &&
            oldConfig.transform_ == newConfig.transform_ &&
            oldConfig.orientation_ == newConfig.orientation_ &&
            oldConfig.displayId_ == newConfig.displayId_) {
            continue;
        }
        uiExtension->SetSessionViewportConfig(newConfig);
        if (uiExtension->IsForeground()) {
            auto sessionWrapper = uiExtension->GetSessionWrapper();
            if (sessionWrapper && sessionWrapper->IsSessionValid()) {
                sessionWrapper->UpdateSessionViewportConfig();
            }
        } else {
            uiExtension->SetViewportConfigChanged(true);
        }
    }
}

bool UIExtensionManager::UIExtBusinessDataSendValid()
{
    if (!businessSendToHostReplyFunc_ || !businessSendToHostFunc_) {
        return false;
    }
    return true;
}

// host send data to provider
void UIExtensionManager::RegisterBusinessDataSendCallback(
    UIContentBusinessCode code, BusinessDataSendType type, const UIExtBusinessDataSendCallback& callback,
    RSSubsystemId subsystemId)
{
    businessDataSendCallbacks_.try_emplace(code,
        std::tuple<BusinessDataSendType, UIExtBusinessDataSendCallback, RSSubsystemId>(type, callback, subsystemId));
}

void UIExtensionManager::UnRegisterBusinessDataSendCallback(UIContentBusinessCode code)
{
    auto it = businessDataSendCallbacks_.find(code);
    if (it == businessDataSendCallbacks_.end()) {
        return;
    }
    businessDataSendCallbacks_.erase(it);
}

bool UIExtensionManager::TriggerBusinessDataSend(UIContentBusinessCode code)
{
    CHECK_RUN_ON(UI);
    auto it = businessDataSendCallbacks_.find(code);
    if (it == businessDataSendCallbacks_.end()) {
        return false;
    }
    auto& [type, callback, subsystemId] = it->second;
    CHECK_NULL_RETURN(callback, false);
    bool ret = false;
    decltype(aliveUIExtensions_) tempAliveUIExtensions(aliveUIExtensions_);
    for (const auto& pattern : tempAliveUIExtensions) {
        auto uiExtension = pattern.second.Upgrade();
        CHECK_NULL_CONTINUE(uiExtension);
        auto frameNode = uiExtension->GetHost();
        CHECK_NULL_CONTINUE(frameNode);
        // data is std::optional<AAFwk::Want>, if data has value then send it.
        auto data = callback(frameNode);
        if (!data.has_value()) {
            continue;
        }
        ret |= uiExtension->SendBusinessData(code, data.value(), type, subsystemId);
    }
    decltype(aliveSecurityUIExtensions_) tempAliveSecurityUIExtensions(aliveSecurityUIExtensions_);
    for (const auto& pattern : aliveSecurityUIExtensions_) {
        auto uiExtension = pattern.second.Upgrade();
        CHECK_NULL_CONTINUE(uiExtension);
        auto frameNode = uiExtension->GetHost();
        CHECK_NULL_CONTINUE(frameNode);
        // data is std::optional<AAFwk::Want>, if data has value then send it.
        auto data = callback(frameNode);
        if (!data.has_value()) {
            continue;
        }
        ret |= uiExtension->SendBusinessData(code, data.value(), type, subsystemId);
    }
    return ret;
}

// provider consume data
void UIExtensionManager::RegisterBusinessDataConsumeCallback(
    UIContentBusinessCode code, const UIExtBusinessDataConsumeCallback& callback)
{
    businessDataConsumeCallbacks_.try_emplace(code, callback);
}

void UIExtensionManager::UnRegisterBusinessDataConsumeCallback(UIContentBusinessCode code)
{
    auto it = businessDataConsumeCallbacks_.find(code);
    if (it == businessDataConsumeCallbacks_.end()) {
        return;
    }
    businessDataConsumeCallbacks_.erase(it);
}

void UIExtensionManager::DispatchBusinessDataConsume(
    UIContentBusinessCode code, const AAFwk::Want& data)
{
    auto it = businessDataConsumeCallbacks_.find(code);
    if (it == businessDataConsumeCallbacks_.end()) {
        return;
    }
    auto callback = it->second;
    CHECK_NULL_VOID(callback);
    callback(data);
}

void UIExtensionManager::RegisterBusinessDataConsumeReplyCallback(
    UIContentBusinessCode code, const UIExtBusinessDataConsumeReplyCallback& callback)
{
    businessDataConsumeReplyCallbacks_.try_emplace(code, callback);
}

void UIExtensionManager::UnRegisterBusinessDataConsumeReplyCallback(UIContentBusinessCode code)
{
    auto it = businessDataConsumeReplyCallbacks_.find(code);
    if (it == businessDataConsumeReplyCallbacks_.end()) {
        return;
    }
    businessDataConsumeReplyCallbacks_.erase(it);
}

void UIExtensionManager::DispatchBusinessDataConsumeReply(
    UIContentBusinessCode code, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply)
{
    auto it = businessDataConsumeReplyCallbacks_.find(code);
    if (it == businessDataConsumeReplyCallbacks_.end()) {
        return;
    }
    auto callback = it->second;
    CHECK_NULL_VOID(callback);
    callback(data, reply);
}

// provider send data to host
void UIExtensionManager::RegisterBusinessSendToHostReply(const UIExtBusinessSendToHostReplyFunc& func)
{
    businessSendToHostReplyFunc_ = func;
}

void UIExtensionManager::RegisterBusinessSendToHost(const UIExtBusinessSendToHostFunc& func)
{
    businessSendToHostFunc_ = func;
}

bool UIExtensionManager::SendBusinessToHost(
    UIContentBusinessCode code, const AAFwk::Want& data, BusinessDataSendType type)
{
    if (!UIExtBusinessDataSendValid()) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "SendBusinessToHost callback not set.");
        return false;
    }
    auto callback = businessSendToHostFunc_;
    return callback(static_cast<uint32_t>(code), data, type);
}

bool UIExtensionManager::SendBusinessToHostSyncReply(
    UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply)
{
    if (!UIExtBusinessDataSendValid()) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "SendBusinessToHost callback not set.");
        return false;
    }
    auto callback = businessSendToHostReplyFunc_;
    return callback(static_cast<uint32_t>(code), data, reply);
}

void UIExtensionManager::NotifyWindowMode(Rosen::WindowMode mode)
{
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "NotifyWindowMode aliveUIExtensions = %{public}zu",
        aliveUIExtensions_.size());
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->NotifyHostWindowMode(mode);
        }
    }
}

void UIExtensionManager::SendPageModeToProvider(const int32_t nodeId, const std::string& pageMode)
{
    auto it = aliveUIExtensions_.find(nodeId);
    if(it == aliveUIExtensions_.end()) {
        return;
    }
    auto uiExtension = it->second.Upgrade();
    CHECK_NULL_VOID(uiExtension);
    AAFwk::Want data;
    data.SetParam("pageMode", pageMode);
    uiExtension->SendBusinessData(
        UIContentBusinessCode::SEND_PAGE_MODE_TO_UEA, std::move(data), BusinessDataSendType::ASYNC);
}

void UIExtensionManager::SendPageModeRequestToHost(const RefPtr<PipelineContext>& pipeline)
{
    AAFwk::Want data;
    data.SetParam("requestPageMode", std::string("yes"));
    AAFwk::Want reply;
    SendBusinessToHostSyncReply(UIContentBusinessCode::SEND_PAGE_MODE, data, reply);
    if (reply.HasParameter("pageMode")) {
        auto pageMode = reply.GetStringParam("pageMode");
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UEA received a reply, pageMode: %{public}s.", pageMode.c_str());
        auto accessibilityManager = pipeline->GetAccessibilityManager();
        CHECK_NULL_VOID(accessibilityManager);
        accessibilityManager->UpdatePageMode(pageMode);
    }
}

void UIExtensionManager::TransferAccessibilityRectInfo()
{
    {
        std::lock_guard<std::mutex> aliveUIExtensionMutex(aliveUIExtensionMutex_);
        for (const auto& it : aliveUIExtensions_) {
            auto uiExtension = it.second.Upgrade();
            if (uiExtension) {
                uiExtension->TransferAccessibilityRectInfo();
            }
        }
    }
    for (const auto& it : aliveSecurityUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->TransferAccessibilityRectInfo();
        }
    }
}

void UIExtensionManager::UpdateWMSUIExtProperty(UIContentBusinessCode code, const AAFwk::Want& data,
    RSSubsystemId subSystemId)
{
    CHECK_RUN_ON(UI);
    for (const auto& it : aliveUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->UpdateWMSUIExtProperty(code, data, subSystemId);
        }
    }
    for (const auto& it : aliveSecurityUIExtensions_) {
        auto uiExtension = it.second.Upgrade();
        if (uiExtension) {
            uiExtension->UpdateWMSUIExtProperty(code, data, subSystemId);
        }
    }
}

void UIExtensionManager::RegisterListenerIfNeeded()
{
    if (hasRegisterListener_) {
        return;
    }

    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    // Multi-layer nested UEC scenarios are not supported.
    if (container->IsUIExtensionWindow()) {
        hasRegisterListener_ = true;
        return;
    }

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto containerModalListener =
        [weakMgr = WeakClaim(this)](const RectF&, const RectF&) {
            auto mgr = weakMgr.Upgrade();
            CHECK_NULL_VOID(mgr);
            mgr->NotifyUECProviderIfNeedded();
        };
    TAG_LOGI(AceLogTag::ACE_LAYOUT, "UIExtensionManager register listener");
    containerModalListenerId_ = ContainerModalViewEnhance::AddButtonsRectChangeListener(
        AceType::RawPtr(pipeline), std::move(containerModalListener));
    hasRegisterListener_ = true;
}

void UIExtensionManager::UnregisterListenerIfNeeded()
{
    if (!hasRegisterListener_) {
        return;
    }

    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    // Multi-layer nested UEC scenarios are not supported.
    if (container->IsUIExtensionWindow()) {
        hasRegisterListener_ = false;
        return;
    }

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    TAG_LOGI(AceLogTag::ACE_LAYOUT, "UIExtensionManager unregister listener");
    ContainerModalViewEnhance::RemoveButtonsRectChangeListener(
        AceType::RawPtr(pipeline), containerModalListenerId_);
    hasRegisterListener_ = false;
}

void UIExtensionManager::NotifyUECProviderIfNeedded()
{
    if (aliveUIExtensions_.empty()) {
        return;
    }

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(avoidInfoMgr);
    for (const auto& it : aliveUIExtensions_) {
        auto uecPattern = it.second.Upgrade();
        CHECK_NULL_CONTINUE(uecPattern);
        const auto& preAvoidInfo = uecPattern->GetAvoidInfo();
        auto uecNode = AceType::DynamicCast<FrameNode>(uecPattern->GetHost());
        CHECK_NULL_CONTINUE(uecNode);
        ContainerModalAvoidInfo newAvoidInfo;
        AvoidInfoManager::GetContainerModalAvoidInfoForUEC(uecNode, newAvoidInfo);
        bool needNotify = AvoidInfoManager::CheckIfNeedNotifyAvoidInfoChange(preAvoidInfo, newAvoidInfo);
        uecPattern->SetAvoidInfo(newAvoidInfo);
        if (needNotify) {
            AAFwk::Want avoidInfoWant;
            avoidInfoMgr->BuildAvoidInfo(newAvoidInfo, avoidInfoWant);
            TAG_LOGI(AceLogTag::ACE_LAYOUT, "UECManager send AvoidInfo: %{public}s", newAvoidInfo.ToString().c_str());
            uecPattern->SendBusinessData(UIContentBusinessCode::NOTIFY_AVOID_INFO_CHANGE,
                std::move(avoidInfoWant), BusinessDataSendType::ASYNC);
        }
    }
}
} // namespace OHOS::Ace::NG
