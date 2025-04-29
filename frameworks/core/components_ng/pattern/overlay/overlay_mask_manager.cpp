/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/overlay/overlay_mask_manager.h"

#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
OverlayMaskManager::OverlayMaskManager() = default;

OverlayMaskManager::~OverlayMaskManager() = default;

void OverlayMaskManager::AddUECHostNodeMap(const std::string& uuid, const RefPtr<FrameNode>& node)
{
    std::lock_guard<std::mutex> lock(uecHostNodeMutex_);
    uecHostNodeMap_.try_emplace(uuid, AceType::WeakClaim(AceType::RawPtr(node)));
}

void OverlayMaskManager::RemoveUECHostNodeMap(const std::string& uuid)
{
    std::lock_guard<std::mutex> lock(uecHostNodeMutex_);
    uecHostNodeMap_.erase(uuid);
}

RefPtr<FrameNode> OverlayMaskManager::GetUECHostNode(const std::string& uuid)
{
    std::lock_guard<std::mutex> lock(uecHostNodeMutex_);
    auto result = uecHostNodeMap_.find(uuid);
    if (result != uecHostNodeMap_.end()) {
        return result->second.Upgrade();
    }

    return nullptr;
}

void OverlayMaskManager::AddUECHostMaskMap(const std::string& uuid, HostMaskTuple maskTuple)
{
    std::lock_guard<std::mutex> lock(uecHostMaskMutex_);
    uecHostMaskMap_.try_emplace(uuid, maskTuple);
}

void OverlayMaskManager::RemoveUECHostMaskMap(const std::string& uuid)
{
    std::lock_guard<std::mutex> lock(uecHostMaskMutex_);
    uecHostMaskMap_.erase(uuid);
}

HostMaskTuple OverlayMaskManager::GetUECHostMask(const std::string& uuid)
{
    std::lock_guard<std::mutex> lock(uecHostMaskMutex_);
    auto result = uecHostMaskMap_.find(uuid);
    if (result != uecHostMaskMap_.end()) {
        return result->second;
    }

    return {};
}

void OverlayMaskManager::RegisterOverlayHostMaskEventCallback()
{
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto container = Container::GetContainer(pipeline->GetInstanceId());
    CHECK_NULL_VOID(container);
    if (!container->IsUIExtensionWindow()) {
        return;
    }

#ifdef WINDOW_SCENE_SUPPORTED
    auto uiExtMgr = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtMgr);

    ModalUIExtension::RegisterBusinessConsumeCallbackOnUEA(
        uiExtMgr, UIContentBusinessCode::OVERLAY_MASK_EVENT, [](const AAFwk::Want& data) -> int32_t {
            UECHostMaskInfo maskInfo = ModalUIExtension::GetUECHostMaskInfoFromWant(data);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "UEA recv mask event from host, %{public}s", maskInfo.ToString().c_str());
            OverlayMaskManager::GetInstance().OnOverlayHostMaskEventCallback(maskInfo);
            return 0;
        });
#endif
}

void OverlayMaskManager::OnOverlayHostMaskEventCallback(const UECHostMaskInfo& maskInfo)
{
    auto uecNode = GetUECHostNode(maskInfo.uuid);
    if (uecNode) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "current window is UEC, send host mask event to next UEC");
        auto ret = ModalUIExtension::SendOverlayMaskInfoToUEA(
            uecNode, maskInfo, UIContentBusinessCode::OVERLAY_MASK_EVENT, BusinessDataSendType::ASYNC);
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_OVERLAY, "failed to send host mask event to UEA");
        }

        return;
    }

    if (maskInfo.maskType == UECHostMaskType::DIALOG) {
        HandleDialogHostMaskEvent(maskInfo);
    }
}

void OverlayMaskManager::HandleDialogHostMaskEvent(const UECHostMaskInfo& maskInfo)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "UEA handle dialog host mask event enter");

    auto dialog = FrameNode::GetFrameNodeOnly(maskInfo.overlayTag, maskInfo.overlayId);
    CHECK_NULL_VOID(dialog);
    auto dialogPattern = dialog->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);

    if (maskInfo.maskAction == UECHostMaskAction::CLICK) {
        auto dialogProperties = dialogPattern->GetDialogProperties();
        if (dialogProperties.autoCancel) {
            dialogPattern->CloseDialogByEvent(DialogDismissReason::DIALOG_TOUCH_OUTSIDE);
        }
    } else if (maskInfo.maskAction == UECHostMaskAction::PRESS_BACK) {
        dialogPattern->CloseDialogByEvent(DialogDismissReason::DIALOG_PRESS_BACK);
    }
}

void OverlayMaskManager::RegisterOverlayHostMaskMountCallback(int32_t uiExtensionId, const RefPtr<FrameNode>& uiextNode)
{
    CHECK_NULL_VOID(uiextNode);
    ModalUIExtension::RegisterBusinessConsumeCallbackOnHost(uiextNode, UIContentBusinessCode::OVERLAY_MASK_MOUNT,
        [uiExtensionId, uiextWeak = AceType::WeakClaim(AceType::RawPtr(uiextNode))](
            const AAFwk::Want& data) -> int32_t {
            UECHostMaskInfo maskInfo = ModalUIExtension::GetUECHostMaskInfoFromWant(data);
            TAG_LOGI(AceLogTag::ACE_OVERLAY, "host recv maskInfo from UEC, %{public}s", maskInfo.ToString().c_str());

            auto uiextNode = uiextWeak.Upgrade();
            CHECK_NULL_RETURN(uiextNode, -1);
            OverlayMaskManager::GetInstance().OnOverlayHostMaskMountCallback(uiExtensionId, uiextNode, maskInfo);
            return 0;
        });
}

void OverlayMaskManager::OnOverlayHostMaskMountCallback(
    int32_t uiExtensionId, const RefPtr<FrameNode>& uiextNode, const UECHostMaskInfo& maskInfo)
{
    CHECK_NULL_VOID(uiextNode);
    auto pipeline = uiextNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto container = Container::GetContainer(pipeline->GetInstanceId());
    CHECK_NULL_VOID(container);

    if (maskInfo.maskAction == UECHostMaskAction::UNMOUNT) {
        RemoveUECHostNodeMap(maskInfo.uuid);
    } else {
        AddUECHostNodeMap(maskInfo.uuid, uiextNode);
    }

    if (container->IsUIExtensionWindow()) {
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "current window is UEC, send to parnet host again");
#ifdef WINDOW_SCENE_SUPPORTED
        auto uiExtMgr = pipeline->GetUIExtensionManager();
        CHECK_NULL_VOID(uiExtMgr);
        auto ret = ModalUIExtension::SendOverlayMaskInfoToHost(
            uiExtMgr, maskInfo, UIContentBusinessCode::OVERLAY_MASK_MOUNT, BusinessDataSendType::ASYNC);
        if (!ret) {
            TAG_LOGW(AceLogTag::ACE_OVERLAY, "failed to send overlay mask info to host");
        }
#endif
        return;
    }

    if (maskInfo.maskType == UECHostMaskType::DIALOG) {
        HostMountDialogMask(uiExtensionId, maskInfo);
    }
}

void OverlayMaskManager::HostMountDialogMask(int32_t uiExtensionId, const UECHostMaskInfo& maskInfo)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "host process dialog mask info enter");

    if (maskInfo.maskAction == UECHostMaskAction::MOUNT) {
        auto pipeline = PipelineContext::GetMainPipelineContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);

        DialogProperties maskarg;
        maskarg.isUECHostMask = true;
        maskarg.maskColor = maskInfo.maskColor;
        auto mask = overlayManager->SetDialogMask(maskarg);
        CHECK_NULL_VOID(mask);
        auto dialogPattern = mask->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->SetUECHostMaskInfo(maskInfo);

        HostMaskTuple maskTuple = {
            .uiExtensionId = uiExtensionId, .maskInfo = maskInfo, .maskNode = AceType::WeakClaim(AceType::RawPtr(mask))
        };
        AddUECHostMaskMap(maskInfo.uuid, maskTuple);
    } else if (maskInfo.maskAction == UECHostMaskAction::UNMOUNT) {
        CloseHostMask(maskInfo.uuid);
    }
}

void OverlayMaskManager::SendMaskInfoToHost(const UECHostMaskInfo& maskInfo)
{
    if (maskInfo.uuid.empty()) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "uuid of maskInfo is invalid");
        return;
    }

#ifdef WINDOW_SCENE_SUPPORTED
    auto pipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto uiExtMgr = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtMgr);

    TAG_LOGI(AceLogTag::ACE_OVERLAY, "send mask info to host, %{public}s", maskInfo.ToString().c_str());

    auto ret = ModalUIExtension::SendOverlayMaskInfoToHost(
        uiExtMgr, maskInfo, UIContentBusinessCode::OVERLAY_MASK_MOUNT, BusinessDataSendType::ASYNC);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "failed to send overlay mask info to host");
    }
#endif
}

void OverlayMaskManager::SendMaskEventToUEA(const UECHostMaskInfo& maskInfo)
{
    auto hostUECNode = GetUECHostNode(maskInfo.uuid);
    CHECK_NULL_VOID(hostUECNode);

    TAG_LOGI(AceLogTag::ACE_OVERLAY, "host send mask event to UEA, %{public}s", maskInfo.ToString().c_str());

    auto ret = ModalUIExtension::SendOverlayMaskInfoToUEA(
        hostUECNode, maskInfo, UIContentBusinessCode::OVERLAY_MASK_EVENT, BusinessDataSendType::ASYNC);
    if (!ret) {
        TAG_LOGW(AceLogTag::ACE_OVERLAY, "failed to send host mask event to UEA");
    }
}

const std::vector<std::string> OverlayMaskManager::GetAllHostMaskUid(int32_t uiExtensionId)
{
    std::lock_guard<std::mutex> lock(uecHostMaskMutex_);

    std::vector<std::string> maskUids;
    for (auto it = uecHostMaskMap_.begin(); it != uecHostMaskMap_.end(); it++) {
        if (it->second.uiExtensionId == uiExtensionId) {
            maskUids.push_back(it->second.maskInfo.uuid);
        }
    }
    return maskUids;
}

void OverlayMaskManager::OnUIExtDestroy(int32_t uiExtensionId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "host is destroyed, close all mask by uiExtensionId: %{public}d", uiExtensionId);
    for (auto uuid : GetAllHostMaskUid(uiExtensionId)) {
        CloseHostMask(uuid);
    }
}

void OverlayMaskManager::CloseHostMask(const std::string& uuid)
{
    auto maskTuple = GetUECHostMask(uuid);
    auto maskNode = maskTuple.maskNode.Upgrade();
    CHECK_NULL_VOID(maskNode);

    if (maskTuple.maskInfo.maskType == UECHostMaskType::DIALOG) {
        auto dialogPattern = maskNode->GetPattern<DialogPattern>();
        CHECK_NULL_VOID(dialogPattern);
        dialogPattern->CloseDialog();
        RemoveUECHostMaskMap(uuid);
    } else {
        auto parent = maskNode->GetParent();
        CHECK_NULL_VOID(parent);
        parent->RemoveChild(maskNode);
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        RemoveUECHostMaskMap(uuid);
    }
}

void OverlayMaskManager::SendDialogMaskInfoToHost(
    const RefPtr<FrameNode>& dialogNode, UECHostMaskAction maskAction, int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "UEA send dialog mask info to host");

    CHECK_NULL_VOID(dialogNode);
    auto pipeline = dialogNode->GetContextRefPtr();
    auto currentId = pipeline ? pipeline->GetInstanceId() : instanceId;
    if (currentId < MIN_SUBCONTAINER_ID) {
        return;
    }

    CHECK_NULL_VOID(dialogNode);
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);
    auto dialogprop = dialogPattern->GetDialogProperties();

    UECHostMaskInfo maskInfo;
    if (maskAction == UECHostMaskAction::MOUNT) {
        auto nowTime = std::chrono::system_clock::now().time_since_epoch();
        uint64_t stamp = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(nowTime).count());
        maskInfo = {
            .uuid = std::to_string(stamp),
            .instanceId = currentId,
            .overlayTag = dialogNode->GetTag(),
            .overlayId = dialogNode->GetId(),
            .maskColor = dialogprop.maskColor,
            .maskAction = UECHostMaskAction::MOUNT,
            .maskType = UECHostMaskType::DIALOG,
        };
        dialogPattern->SetUECHostMaskInfo(maskInfo);
    } else if (maskAction == UECHostMaskAction::UNMOUNT) {
        maskInfo = dialogPattern->GetUECHostMaskInfo();
        maskInfo.maskAction = UECHostMaskAction::UNMOUNT;
    }

    SendMaskInfoToHost(maskInfo);
}

void OverlayMaskManager::SendDialogMaskEventToUEA(const RefPtr<FrameNode>& maskNode, UECHostMaskAction maskAction)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "host send dialog mask event to UEA enter");

    CHECK_NULL_VOID(maskNode);
    auto dialogPattern = maskNode->GetPattern<DialogPattern>();
    CHECK_NULL_VOID(dialogPattern);

    UECHostMaskInfo maskInfo = dialogPattern->GetUECHostMaskInfo();
    maskInfo.maskAction = maskAction;
    SendMaskEventToUEA(maskInfo);
}
} // namespace OHOS::Ace::NG