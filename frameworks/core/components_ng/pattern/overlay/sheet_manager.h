/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_MANAGER_H

#include "base/utils/singleton.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT SheetManager : public Singleton<SheetManager> {
    DECLARE_SINGLETON(SheetManager);
public:
    static RefPtr<OverlayManager> FindPageNodeOverlay(
        const RefPtr<FrameNode>& targetNode, bool isShow, bool isStartByUIContext = false);
    static RefPtr<OverlayManager> GetOverlayFromPage(int32_t rootNodeId, RootNodeType rootNodeType);

    int32_t OpenBindSheetByUIContext(const RefPtr<NG::FrameNode>& sheetContentNode,
         std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange, std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack,
        int32_t currentInstanceId, int32_t targetId);
    int32_t UpdateBindSheetByUIContext(
        const RefPtr<NG::FrameNode>& sheetContentNode, NG::SheetStyle& sheetStyle, bool isPartialUpdate,
        int32_t currentInstanceId);
    int32_t CloseBindSheetByUIContext(const RefPtr<NG::FrameNode>& sheetContentNode, int32_t currentInstanceId);
    void CleanBindSheetMap(int32_t instanceId, int32_t sheetContentNodeId)
    {
        overlayManagerMap_.erase(SheetContentKey(instanceId, sheetContentNodeId));
        targetIdMap_.erase(SheetContentKey(instanceId, sheetContentNodeId));
    }

    void SetDismissSheet(int32_t dismissId)
    {
        sheetDismissId_ = dismissId;
    }

    int32_t GetDismissSheet()
    {
        return sheetDismissId_;
    }

    void SetFocusSheetId(const std::optional<int32_t>& id)
    {
        sheetFocusId_ = id;
    }

    std::optional<int32_t> GetFocusSheetId() const
    {
        return sheetFocusId_;
    }

    bool RemoveSheetByESC();

    void DeleteOverlayForWindowScene(int32_t rootNodeId, RootNodeType rootNodeType);

private:
    struct SheetContentKey {
        SheetContentKey() {}
        SheetContentKey(int32_t inputInstanceId, int32_t inputContentNodeId)
            : instanceId(inputInstanceId), contentNodeId(inputContentNodeId) {}
        int32_t instanceId;
        int32_t contentNodeId;
        bool operator<(const SheetContentKey& other) const {
            if (instanceId == other.instanceId) {
                return contentNodeId < other.contentNodeId;
            }
            return instanceId < other.instanceId;
        }
    };

    int32_t sheetDismissId_ = 0;
    std::optional<int32_t> sheetFocusId_;
    std::map<SheetContentKey, RefPtr<OverlayManager>> overlayManagerMap_;
    // Value:  The uniqueId of the FrameNode to which BindSheet is attached
    std::map<SheetContentKey, int32_t> targetIdMap_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_MANAGER_H
