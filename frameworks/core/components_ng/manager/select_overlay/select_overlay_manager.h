/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_MANAGER_H

#include <cstdint>
#include <memory>
#include <unordered_map>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_overlay/select_overlay_proxy.h"
#include "core/components_ng/manager/select_overlay/selection_host.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

using ScrollableParentCallback = std::function<void(Axis, float, int32_t)>;

// SelectOverlayManager is the class to show and control select handle and select menu.
class ACE_EXPORT SelectOverlayManager : public virtual AceType {
    DECLARE_ACE_TYPE(SelectOverlayManager, AceType);

public:
    explicit SelectOverlayManager(const RefPtr<FrameNode>& rootNode) : rootNodeWeak_(rootNode) {}
    ~SelectOverlayManager() override = default;

    // Create and display selection pop-ups.
    RefPtr<SelectOverlayProxy> CreateAndShowSelectOverlay(
        const SelectOverlayInfo& info, const WeakPtr<SelectionHost>& host, bool animation = false);

    // Destroy the pop-up interface and delete the pop-up information.
    void DestroySelectOverlay(const RefPtr<SelectOverlayProxy>& proxy, bool animation = false);
    void DestroySelectOverlay(int32_t overlayId, bool animation = false);
    void DestroySelectOverlay(bool animation = false);

    bool HasSelectOverlay(int32_t overlayId);

    bool IsInSelectedOrSelectOverlayArea(const PointF& point);

    RefPtr<SelectOverlayNode> GetSelectOverlayNode(int32_t overlayId);

    bool IsSameSelectOverlayInfo(const SelectOverlayInfo& info);

    void SetOnTouchTestResults(const std::vector<std::string>& touchTestResults)
    {
        touchTestResults_ = touchTestResults;
    }

    void HandleGlobalEvent(const TouchEvent& touchPoint, const NG::OffsetF& rootOffset);

    void MarkDirty(PropertyChangeFlag flag);

    RefPtr<UINode> FindWindowScene(RefPtr<FrameNode> targetNode);

    const WeakPtr<FrameNode>& GetSelectOverlayItem() const
    {
        return selectOverlayItem_;
    }

    void NotifyOnScrollCallback(int32_t id, Axis axis, float offset, int32_t source);

    void RegisterScrollCallback(int32_t scrollableParentId, int32_t callbackId, ScrollableParentCallback&& callback);

    void RemoveScrollCallback(int32_t callbackId);

private:
    void DestroyHelper(const RefPtr<FrameNode>& overlay, bool animation = false);

    void Destroy(const RefPtr<FrameNode>& overlay);

    bool IsTouchInCallerArea() const;

    void NotifyOverlayClosed(bool closedByGlobalEvent = false);

    RefPtr<FrameNode> GetCallerHost() const;

    WeakPtr<FrameNode> rootNodeWeak_;

    WeakPtr<FrameNode> selectOverlayItem_;
    WeakPtr<SelectionHost> host_;

    SelectOverlayInfo selectOverlayInfo_;

    std::vector<TouchEvent> touchDownPoints_;
    std::vector<std::string> touchTestResults_;

    std::map<int32_t, std::map<int32_t, ScrollableParentCallback>> parentScrollCallbacks_;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_MANAGER_H
