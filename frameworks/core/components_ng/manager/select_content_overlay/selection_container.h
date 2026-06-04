/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_H

#include <cstdint>
#include <list>
#include <vector>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/macros.h"
#include "core/components_ng/manager/select_content_overlay/selection_entity.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/manager/select_content_overlay/selection_container_child.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace {
class GestureEvent;
enum class WindowSizeChangeReason : uint32_t;
class TouchEventInfo;
}

namespace OHOS::Ace::NG {
struct OverlayRequest;

struct SelectionStartEventInfo {
    WeakPtr<SelectionContainerChild> child;
    OffsetF localPoint;
    int32_t startIndex = -1;
    int32_t endIndex = -1;
};

struct ChildSelectionInfo {
    int32_t childId = -1;
    int32_t startIndex = -1;
    int32_t endIndex = -1;
    bool operator==(const ChildSelectionInfo& other) const
    {
        return childId == other.childId && startIndex == other.startIndex && endIndex == other.endIndex;
    }
};

struct SelectionEndEventInfo {
    RefPtr<SelectionContainerChild> child;
    OffsetF localPoint;
};

class ACE_EXPORT SelectionContainer : public SelectionEntity {
    DECLARE_ACE_TYPE(SelectionContainer, SelectionEntity);

public:
    SelectionContainer() = default;
    ~SelectionContainer() override = default;

    void RegisterChild(const RefPtr<SelectionContainerChild>& child);
    void UnregisterChild(int32_t childId);
    virtual void CloseSelectOverlay(
        bool animation = false, CloseReason reason = CloseReason::CLOSE_REASON_NORMAL) = 0;
    virtual void ProcessOverlay(const OverlayRequest& request) = 0;
    virtual void SwitchToOverlayMode() = 0;
    virtual void ToggleMenu() = 0;
    virtual void HideMenu(bool noAnimation = false, bool showSubMenu = false) = 0;
    virtual void DisableMenu() = 0;
    virtual void UpdateAISelectMenu() = 0;
    virtual bool IsCurrentMenuVisibile() = 0;
    virtual bool GetIsHandleDragging() { return false; }
    virtual bool IsClickAtHandle(const GestureEvent& info) { return false; }
    virtual bool IsTouchAtHandle(const TouchEventInfo& info) { return false; }
    virtual void UpdateAllHandlesOffset() {}
    virtual void UpdateViewPort() {}
    virtual void MarkOverlayDirty() {}
    virtual bool IsShowMouseMenu() { return false; }
    virtual void UpdateMenuOnWindowSizeChanged(WindowSizeChangeReason type) {}
    virtual bool IsUsingMouse() = 0;
    virtual void SetSourceType(SourceType sourceType) {}
    virtual void SetMouseMenuOffset(const OffsetF& offset) {}
    virtual void UpdateHandleColor() = 0;
    virtual bool SelectOverlayIsOn() = 0;
    virtual void HandleOnCopy() = 0;
    virtual void HandleOnCopyFromAI(const RefPtr<SelectionContainerChild>& child) {}
    virtual void HandleOnSelectAll() = 0;
    virtual bool GetEnableHapticFeedback() const = 0;
    virtual CopyOptions GetCopyOption() const = 0;
    virtual std::optional<Color> GetSelectedBackgroundColor() const = 0;
    virtual void OnSelectionRangeChanged(const std::vector<std::u16string>& selectedTexts,
        const std::vector<ChildSelectionInfo>& selectionState = {}) {}
    virtual void OnChildResponseTypeChanged(TextResponseType responseType) {}
    virtual void OnChildSelectedTypeSave() {}
    virtual void OnChildSelectionSpanTypeChanged(
        int32_t childId, const ChildSelectionSummary& oldSummary, const ChildSelectionSummary& newSummary) {}
    virtual void RebuildSelectionSpanTypeByFullScan() {}
    virtual void SaveOldSelectedType() = 0;
    virtual void SetSelectionHoldCallback() {}
    virtual bool IsSelectedBindSelectionMenu() const { return false; }
    virtual bool BetweenSelectedPosition(const Offset& globalOffset);
    virtual bool IsTriggerParentToScroll()
    {
        return false;
    }
    virtual bool HasScrollableParent()
    {
        return false;
    }
    virtual void TriggerScrollableParentToScroll(const OffsetF& globalPoint, bool isStopAutoScroll) {}
    virtual void EnableMouseLeftSelectionTracking(const OffsetF& globalPoint) {}
    virtual void StopMouseLeftSelectionTracking() {}
    bool IsSelectionSessionOwner(const RefPtr<SelectionContainerChild>& child) const;
    bool HandleSelectionStart(const SelectionStartEventInfo& eventInfo);
    bool HandleSelectionStart(const OffsetF& fixedPointInContainer,
        const RefPtr<SelectionContainerChild>& startChild, int32_t startIndex, int32_t endIndex,
        bool fixedHandleIsTopOnStart = true);
    bool HandleSelectionUpdate(const SelectionEndEventInfo& eventInfo);
    bool HandleSelectionUpdate(const OffsetF& movingPointInContainer);
    bool ProcessGestureSelectionUpdate(const SelectionEndEventInfo& eventInfo, const OffsetF& globalPoint);
    bool ExtendSelectionFromFixedAnchor(const SelectionEndEventInfo& eventInfo);
    bool ProcessSelectionEndCommon(bool showOverlay);
    bool ProcessGestureSelectionEnd(const SelectionEndEventInfo& eventInfo);
    bool ProcessGestureSelectionEnd(const SelectionEndEventInfo& eventInfo, const OffsetF& globalPoint);
    bool ProcessMouseLeftRelease(const SelectionEndEventInfo& eventInfo);
    bool ProcessMouseLeftSelectionUpdate(const SelectionEndEventInfo& eventInfo, const OffsetF& globalPoint);
    void StopMouseSelectionTracking(const OffsetF& globalPoint);
    bool ProcessHandleMoveSelectionEnd(const OffsetF& movingPointInContainer);
    void ResetAllSelection();
    void ReportSelectionText();
    void RecordSelectedChild(const RefPtr<SelectionContainerChild>& child);
    bool IsSelectAll();
    bool HasSelectableText();
    void UpdateSelectionBoundaryChild(const RefPtr<SelectionContainerChild>& child);
    void MarkChildSortDirty();
    void RefreshChildSortResult();
    std::vector<WeakPtr<SelectionContainerChild>> GetChildList();
    RefPtr<SelectionContainerChild> GetSelectionStartChild() const
    {
        return selectionStartChild_.Upgrade();
    }
    RefPtr<SelectionContainerChild> GetSelectionEndChild() const
    {
        return selectionEndChild_.Upgrade();
    }
    RefPtr<SelectionContainerChild> GetSelectionMovingChild() const
    {
        return selectionMovingChild_.Upgrade();
    }

protected:
    struct SelectionChildSortInfo {
        WeakPtr<SelectionContainerChild> child;
        OffsetF positionInContainer;
    };

    void SortChildList();
    bool HandleSelectionStartCommon(const RefPtr<SelectionContainerChild>& startChild,
        int32_t startIndex, int32_t endIndex, bool fixedHandleIsTopOnStart = true);
    void CollectAndNotifySelectionChange();
    void SortSelectionBoundaryChildren(const RefPtr<FrameNode>& containerNode);
    void NotifyRegisteredChildrenPropertyUpdate(uint32_t flags);
    void ResetSelectionSessionState();
    void UpdateSelectionMovingChild(const RefPtr<SelectionContainerChild>& child);
    virtual void OnSelectionMovingChildChange(const RefPtr<SelectionContainerChild>& child) {}

    std::list<WeakPtr<SelectionContainerChild>> registeredChildList_;
    OffsetF fixedPointInContainer_;
    OffsetF fixedPointInChildLocal_;
    WeakPtr<SelectionContainerChild> selectionStartChild_;
    WeakPtr<SelectionContainerChild> selectionEndChild_;
    WeakPtr<SelectionContainerChild> selectionFixedChild_;
    WeakPtr<SelectionContainerChild> selectionMovingChild_;
    std::vector<WeakPtr<SelectionContainerChild>> selectedChildren_;
    int32_t selectionFixedIndex_ = -1;
    int32_t selectionStartIndex_ = -1;
    int32_t selectionEndIndex_ = -1;
    bool fixedHandleIsTopOnStart_ = true;
    bool hasSelectionStartEvent_ = false;
    bool sortDirty_ = true;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_H
