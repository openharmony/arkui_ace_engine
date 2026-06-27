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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_CHILD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_CHILD_H

#include <cstdint>
#include <optional>
#include <vector>

#include "base/geometry/offset.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/manager/select_content_overlay/selection_entity.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text_field/text_selector.h"

namespace OHOS::Ace {
class GestureEvent;
class SpanString;
enum class WindowSizeChangeReason : uint32_t;
class TouchEventInfo;
}

namespace OHOS::Ace::NG {
class SelectionContainer;
class ScrollablePattern;
enum class SelectRectsType;
struct OverlayRequest;

enum class SelectionAreaResultType {
    // The child has no valid selection range.
    NONE,
    // The child has a visible selection area after clipping.
    VISIBLE_AREA,
    // The child has text boxes, but they are fully clipped by ancestor viewports.
    CLIPPED_OUT,
};

enum class HandleVisibleContentResult {
    INVISIBLE,
    VISIBLE,
    NEED_CHECK,
};

struct ScrollableParentResult {
    WeakPtr<ScrollablePattern> scrollable;
    bool isInsideContainer = false;
};

struct AncestorNodeViewPortInfo {
    WeakPtr<FrameNode> ancestorNode;
    RectF viewPort;
};

struct SelectionIndexRange {
    int32_t startIndex = -1;
    int32_t endIndex = -1;
};

struct SelectionCopyPayload {
    SelectionCopyPayload();
    SelectionCopyPayload(const SelectionCopyPayload& other);
    SelectionCopyPayload(SelectionCopyPayload&& other) noexcept;
    SelectionCopyPayload& operator=(const SelectionCopyPayload& other);
    SelectionCopyPayload& operator=(SelectionCopyPayload&& other) noexcept;
    ~SelectionCopyPayload();

    std::u16string plainText;
    RefPtr<SpanString> spanString;
};

struct ChildSelectionSummary {
    bool contributes = false;
    TextSpanType type = TextSpanType::NONE;

    bool operator==(const ChildSelectionSummary& other) const
    {
        return contributes == other.contributes && type == other.type;
    }

    bool operator!=(const ChildSelectionSummary& other) const
    {
        return !(*this == other);
    }
};

enum class SelectionContainerPropertyChange : uint32_t {
    COPY_OPTION = 1 << 0,
    ENABLE_HAPTIC_FEEDBACK = 1 << 1,
    SELECTED_BACKGROUND_COLOR = 1 << 2,
};

class ACE_EXPORT SelectionContainerChild : public SelectionEntity {
    DECLARE_ACE_TYPE(SelectionContainerChild, SelectionEntity);

public:
    SelectionContainerChild() = default;
    ~SelectionContainerChild() override = default;

    void RegisterChild();
    void UnregisterChild();
    bool HandleSelectionStart(const Offset& localPoint, int32_t startIndex, int32_t endIndex);
    bool HandleSelectionUpdate(const Offset& localPoint);
    bool ProcessGestureSelectionUpdate(const Offset& localPoint, const OffsetF& globalPoint);
    bool ProcessGestureSelectionEnd(const Offset& localPoint, const OffsetF& globalPoint);
    bool ProcessMouseLeftRelease(const Offset& localPoint);
    bool IsSelectionSessionOwner() const;
    void SetSelectionHoldCallback();
    bool IsSelectedBindSelectionMenu() const;
    void CloseSelectOverlay(bool animation = false, CloseReason reason = CloseReason::CLOSE_REASON_NORMAL);
    void ProcessOverlay(const OverlayRequest& request);
    void SwitchToOverlayMode();
    void ToggleMenu();
    void HideMenu(bool noAnimation = false, bool showSubMenu = false);
    bool IsUsingMouse();
    bool IsTriggerParentToScroll();
    bool HasScrollableParent();
    void TriggerScrollableParentToScroll(const OffsetF& globalPoint, bool isStopAutoScroll);
    bool ProcessMouseLeftSelectionUpdate(const Offset& localPoint, const OffsetF& globalPoint);
    void StopMouseSelectionTracking(const OffsetF& globalPoint);
    void UpdateHandleColor();
    virtual void UpdateChildHandleGlobalOffset() {}
    virtual OffsetF GetChildHandleGlobalOffset() const { return {}; }
    bool SelectOverlayIsOn();
    void MarkChildSortDirty();
    void ResetAllSelection();
    bool HandleOnCopy();
    void HandleOnCopyFromAI();
    bool HandleOnSelectAll();
    virtual void RecordSelectedChild();
    void NotifySelectionChanged(const std::u16string& selectedText);
    void NotifyResponseTypeChanged(TextResponseType responseType);
    void NotifySourceTypeChanged(SourceType sourceType);
    void NotifySelectedTypeSave();
    void NotifyContainerSelectionSpanTypeChanged(const ChildSelectionSummary& selectionSummary);
    void SetMouseMenuOffset(const OffsetF& offset);
    bool BetweenContainerSelectedPosition(const Offset& globalOffset) const;
    bool ExtendSelectionFromFixedAnchor(const Offset& localPoint);
    void DisableMenu();
    void UpdateAISelectMenu();
    bool IsCurrentMenuVisibile();
    bool GetIsHandleDragging();
    bool IsClickAtHandle(const GestureEvent& info);
    bool IsTouchAtHandle(const TouchEventInfo& info);
    void UpdateAllHandlesOffset();
    void UpdateViewPort();
    void MarkOverlayDirty();
    bool IsShowMouseMenu();
    void UpdateMenuOnWindowSizeChanged(WindowSizeChangeReason type);

    void SetSelectionContainer(const WeakPtr<SelectionContainer>& selectionContainer)
    {
        selectionContainer_ = selectionContainer;
    }

    void ClearSelectionContainer()
    {
        lastReportedSelectionSummary_.reset();
        selectionContainer_.Reset();
    }

    RefPtr<SelectionContainer> GetSelectionContainer() const
    {
        return selectionContainer_.Upgrade();
    }

    std::optional<CopyOptions> GetContainerCopyOption() const;
    std::optional<bool> GetContainerEnableHapticFeedback() const;
    std::optional<Color> GetContainerSelectedBackgroundColor() const;

    virtual std::optional<RectF> GetFirstHandleRect() = 0;
    virtual std::optional<RectF> GetSecondHandleRect() = 0;
    virtual HandleVisibleContentResult GetHandleVisibleContentRect(
        const RectF& paintRect, RectF& visibleContentRect, HandleLevelMode handleLevelMode) = 0;
    virtual std::optional<RectF> GetAncestorNodeViewPortForChild() = 0;
    virtual std::vector<AncestorNodeViewPortInfo> GetAncestorNodeViewPortInfos()
    {
        return {};
    }
    virtual RectF GetSelectionArea(SelectRectsType pos, SelectionAreaResultType& resultType)
    {
        resultType = SelectionAreaResultType::NONE;
        return {};
    }
    virtual SelectionIndexRange GetSelectionIndexes() const
    {
        return {};
    }
    virtual SelectionIndexRange GetSelectionIndexesByPoints(const OffsetF& firstPoint, const OffsetF& secondPoint) = 0;
    virtual int32_t GetSelectionIndexByPoint(const OffsetF& point)
    {
        return GetSelectionIndexesByPoints(point, point).startIndex;
    }
    virtual void SelectTextByIndex(int32_t startIndex, int32_t endIndex) = 0;
    virtual void SelectAll() {}
    virtual void UpdateSelectionHandleInfo() {}
    virtual bool BetweenSelectedPosition(const Offset& globalOffset)
    {
        return false;
    }
    virtual bool IsSelectAll() const
    {
        return false;
    }
    virtual bool HasSelectableText() const
    {
        return false;
    }
    virtual bool HandleOnAskCelia(const std::u16string& selectedContent) { return false; }
    virtual bool FireOnWillCopy(const std::u16string& selectedContent) { return true; }
    virtual void FireOnCopy(const std::u16string& selectedContent) {}
    virtual bool IsAskCeliaSupported() const { return false; }
    virtual SelectionCopyPayload GetSelectionCopyPayload();
    virtual RefPtr<SpanString> GetSelectedSpanString() { return nullptr; }
    virtual void ResetOriginCaretPosition() {}
    virtual void ReportSelectionText() {}
    virtual void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex) {}
    virtual void OnContainerPropertyUpdate(uint32_t flags) {}
    virtual bool CanSelect() const
    {
        return false;
    }
    virtual CopyOptions GetCopyOption() const
    {
        return CopyOptions::None;
    }

    virtual TextSpanType GetSelectionSpanType() const
    {
        return TextSpanType::NONE;
    }

    ScrollableParentResult FindNearestScrollable() const;

protected:
    WeakPtr<SelectionContainer> selectionContainer_;
    std::optional<ChildSelectionSummary> lastReportedSelectionSummary_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_CONTAINER_CHILD_H
