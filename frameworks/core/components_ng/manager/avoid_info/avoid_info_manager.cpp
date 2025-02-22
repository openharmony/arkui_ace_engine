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

#include "core/components_ng/manager/avoid_info/avoid_info_manager.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"

namespace OHOS::Ace::NG {

std::string ContainerModalAvoidInfo::ToString() const
{
    std::string str("needAvoid: ");
    str.append(needAvoid ? "true" : "false");
    str.append(", titleHeight: ");
    str.append(std::to_string(titleHeight));
    str.append(", rect: ");
    str.append(controlBottonsRect.ToString());
    return str;
}

void AvoidInfoManager::RegisterListenerIfNeeded()
{
    if (hasRegisterListener_) {
        return;
    }

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    if (!container->IsUIExtensionWindow()) {
        auto containerModalListener =
            [weakMgr = WeakClaim(this)](const RectF&, const RectF&) {
                auto mgr = weakMgr.Upgrade();
                CHECK_NULL_VOID(mgr);
                mgr->OnContainerModalInfoChange();
            };
        TAG_LOGI(AceLogTag::ACE_LAYOUT, "AvoidInfoManager register listener");
        containerModalListenerId_ = ContainerModalViewEnhance::AddButtonsRectChangeListener(
            AceType::RawPtr(pipeline), std::move(containerModalListener));
        // init avoid info
        ContainerModalAvoidInfo info;
        GetContainerModalAvoidInfo(info);
        SetAvoidInfo(info);
        hasRegisterListener_ = true;
        return;
    }

    if (!registerUECConsumerCallback_ || !requestAvoidInfoCallback_) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT, "AvoidInfoManager did not set register callback.");
        return;
    }

    auto consumer = [weakMgr = WeakClaim(this), instanceId = instanceId_](const AAFwk::Want& data) -> int32_t {
        ContainerScope scope(instanceId);
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_RETURN(mgr, 0);
        return mgr->OnUECAvoidInfoReceived(data);
    };
    TAG_LOGI(AceLogTag::ACE_LAYOUT, "AvoidInfoManager register listener for UEC");
    registerUECConsumerCallback_(std::move(consumer));
    // request avoid info for first time.
    requestAvoidInfoCallback_();
    hasRegisterListener_ = true;
}

void AvoidInfoManager::OnContainerModalInfoChange()
{
    ContainerModalAvoidInfo newInfo;
    GetContainerModalAvoidInfo(newInfo);
    bool needNotify = CheckIfNeedNotifyAvoidInfoChange(avoidInfo_, newInfo);
    SetAvoidInfo(newInfo);
    TAG_LOGI(AceLogTag::ACE_LAYOUT, "AvoidInfo change to: %{public}s", newInfo.ToString().c_str());
    if (needNotify) {
        OnAvoidInfoChange(newInfo);
    }
}

int32_t AvoidInfoManager::OnUECAvoidInfoReceived(const AAFwk::Want& data)
{
    ContainerModalAvoidInfo info;
    if (!ParseAvoidInfo(data, info)) {
        return -1;
    }
    SetAvoidInfoForUEC(info);
    TAG_LOGI(AceLogTag::ACE_LAYOUT, "[UEC]AvoidInfo change to: %{public}s", info.ToString().c_str());
    OnAvoidInfoChange(info);
    return 0;
}

void AvoidInfoManager::UnregisterListenerIfNeeded()
{
    if (!hasRegisterListener_) {
        return;
    }

    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    if (container->IsUIExtensionWindow()) {
        hasRegisterListener_ = false;
        return;
    }

    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    TAG_LOGI(AceLogTag::ACE_LAYOUT, "AvoidInfoManager unregister listener");
    ContainerModalViewEnhance::RemoveButtonsRectChangeListener(
        AceType::RawPtr(pipeline), containerModalListenerId_);
    hasRegisterListener_ = false;
}

int32_t AvoidInfoManager::GetContainerModalTitleHeight()
{
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, 0);
    if (container->IsUIExtensionWindow()) {
        return avoidInfoForUEC_.titleHeight;
    }
    return avoidInfo_.titleHeight;
}

bool AvoidInfoManager::GetContainerModalButtonsRect(RectF& containerModal, RectF& buttonsRect)
{
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    RectF* rect = nullptr;
    if (container->IsUIExtensionWindow()) {
        rect = &avoidInfoForUEC_.controlBottonsRect;
    } else {
        rect = &avoidInfo_.controlBottonsRect;
    }
    if (rect->IsValid()) {
        buttonsRect = *rect;
        return true;
    }
    return false;
}

bool AvoidInfoManager::NeedAvoidContainerModal()
{
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    if (container->IsUIExtensionWindow()) {
        return avoidInfoForUEC_.needAvoid;
    }
    return avoidInfo_.needAvoid;
}

void AvoidInfoManager::OnAvoidInfoChange(const ContainerModalAvoidInfo& info)
{
    for (auto& weak : listeners_) {
        auto listener = weak.Upgrade();
        if (listener) {
            listener->OnAvoidInfoChange(info);
        }
    }
}

void AvoidInfoManager::AddAvoidInfoListener(WeakPtr<IAvoidInfoListener> listener)
{
    RegisterListenerIfNeeded();
    listeners_.emplace(listener);
}

void AvoidInfoManager::RemoveAvoidInfoListener(WeakPtr<IAvoidInfoListener> listener)
{
    auto it = listeners_.find(listener);
    if (it != listeners_.end()) {
        listeners_.erase(it);
    }
    if (listeners_.empty()) {
        UnregisterListenerIfNeeded();
    }
}

void AvoidInfoManager::GetContainerModalAvoidInfoForUEC(const RefPtr<FrameNode>& uecNode, ContainerModalAvoidInfo& info)
{
    info.needAvoid = false;
    CHECK_NULL_VOID(uecNode);
    auto context = uecNode->GetContext();
    CHECK_NULL_VOID(context);
    if (context->GetContainerCustomTitleVisible() || !context->GetContainerControlButtonVisible()) {
        return;
    }
    auto offsetRelativeToWindow = uecNode->GetOffsetRelativeToWindow();
    auto uecGeometryNode = uecNode->GetGeometryNode();
    CHECK_NULL_VOID(uecGeometryNode);
    auto uecRect = uecGeometryNode->GetFrameRect();
    uecRect.SetOffset(offsetRelativeToWindow);
    RectF buttonsRect;
    RectF containerModal;
    if (!context->GetContainerModalButtonsRect(containerModal, buttonsRect)) {
        return;
    }
    auto height = context->GetContainerModalTitleHeight();
    if (height <= 0) {
        return;
    }
    if (!uecRect.IsIntersectWith(buttonsRect)) {
        return;
    }
    info.needAvoid = true;
    info.titleHeight = height;
    info.controlBottonsRect = uecRect.IntersectRectT(buttonsRect);
    info.controlBottonsRect -= offsetRelativeToWindow;
}

bool AvoidInfoManager::CheckIfNeedNotifyAvoidInfoChange(
    const ContainerModalAvoidInfo& preInfo, const ContainerModalAvoidInfo& curInfo)
{
    return (curInfo.needAvoid != preInfo.needAvoid) ||
        (curInfo.needAvoid && (curInfo.titleHeight != preInfo.titleHeight ||
            curInfo.controlBottonsRect != preInfo.controlBottonsRect));
}

void AvoidInfoManager::GetContainerModalAvoidInfo(ContainerModalAvoidInfo& info)
{
    info.needAvoid = false;
    auto context = PipelineContext::GetContextByContainerId(instanceId_);
    CHECK_NULL_VOID(context);
    if (context->GetContainerCustomTitleVisible() || !context->GetContainerControlButtonVisible()) {
        return;
    }
    RectF buttonsRect;
    RectF containerModal;
    if (!context->GetContainerModalButtonsRect(containerModal, buttonsRect)) {
        return;
    }
    auto height = context->GetContainerModalTitleHeight();
    if (height <= 0) {
        return;
    }
    info.needAvoid = true;
    info.titleHeight = height;
    info.controlBottonsRect = buttonsRect;
}
} // namespace OHOS::Ace::NG
