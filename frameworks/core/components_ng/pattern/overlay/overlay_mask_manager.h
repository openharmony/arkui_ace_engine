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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MASK_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MASK_MANAGER_H

#include "base/utils/singleton.h"
#include "core/common/modal_ui_extension.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
namespace {
struct HostMaskTuple {
    int32_t uiExtensionId = -1;
    UECHostMaskInfo maskInfo = {};
    WeakPtr<FrameNode> maskNode;
};
} // namespace

class ACE_FORCE_EXPORT OverlayMaskManager : public Singleton<OverlayMaskManager> {
    DECLARE_SINGLETON(OverlayMaskManager);

public:
    void RegisterOverlayHostMaskEventCallback();
    void RegisterOverlayHostMaskMountCallback(int32_t uiExtensionId, const RefPtr<FrameNode>& uiextNode);

    void AddUECHostNodeMap(const std::string& uuid, const RefPtr<FrameNode>& node);
    void AddUECHostMaskMap(const std::string& uuid, HostMaskTuple maskTuple);
    void RemoveUECHostNodeMap(const std::string& uuid);
    void RemoveUECHostMaskMap(const std::string& uuid);
    RefPtr<FrameNode> GetUECHostNode(const std::string& uuid);
    HostMaskTuple GetUECHostMask(const std::string& uuid);

    void SendDialogMaskInfoToHost(
        const RefPtr<FrameNode>& dialogNode, UECHostMaskAction maskAction, int32_t instanceId = -1);
    void SendDialogMaskEventToUEA(const RefPtr<FrameNode>& maskNode, UECHostMaskAction maskAction);

    void OnUIExtDestroy(int32_t uiExtensionId);

private:
    void OnOverlayHostMaskMountCallback(
        int32_t uiExtensionId, const RefPtr<FrameNode>& uiextNode, const UECHostMaskInfo& maskInfo);
    void OnOverlayHostMaskEventCallback(const UECHostMaskInfo& maskInfo);

    void SendMaskInfoToHost(const UECHostMaskInfo& maskInfo);
    void SendMaskEventToUEA(const UECHostMaskInfo& maskInfo);

    void HostMountDialogMask(int32_t uiExtensionId, const UECHostMaskInfo& maskInfo);
    void HandleDialogHostMaskEvent(const UECHostMaskInfo& maskInfo);

    void CloseHostMask(const std::string& uuid);
    const std::vector<std::string> GetAllHostMaskUid(int32_t uiExtensionId);

    std::mutex uecHostNodeMutex_;
    std::unordered_map<std::string, WeakPtr<FrameNode>> uecHostNodeMap_;

    std::mutex uecHostMaskMutex_;
    std::unordered_map<std::string, HostMaskTuple> uecHostMaskMap_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_OVERLAY_MASK_MANAGER_H
