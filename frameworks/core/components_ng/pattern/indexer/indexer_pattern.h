/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_PATTERN_H

#include <optional>
#include <stdint.h>

#include "base/memory/referenced.h"
#include "core/animation/animator.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/indexer/indexer_accessibility_property.h"
#include "core/components_ng/pattern/indexer/indexer_event_hub.h"
#include "core/components_ng/pattern/indexer/indexer_layout_algorithm.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
enum class IndexerCollapsingMode {
    INVALID,
    NONE, // all array should be displayed
    FIVE, // 5 + 1 collapsing mode
    SEVEN // 7 + 1 collapsing mode
};

enum class PopupListGradientStatus {
    NONE,
    TOP,
    BOTTOM,
    BOTH
};

class IndexerPattern : public Pattern {
    DECLARE_ACE_TYPE(IndexerPattern, Pattern);

public:
    IndexerPattern() = default;
    ~IndexerPattern() override = default;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<IndexerEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<IndexerLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<IndexerPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto indexerLayoutAlgorithm = MakeRefPtr<IndexerLayoutAlgorithm>();
        return indexerLayoutAlgorithm;
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<IndexerAccessibilityProperty>();
    }

    void SetIsTouch(bool isTouch)
    {
        isTouch_ = isTouch;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

    int32_t GetSelected() const
    {
        return selected_;
    }

    bool IsMeasureBoundary() const override;
    void UpdateChildBoundary(RefPtr<FrameNode>& frameNode);

protected:
    void SetAccessibilityAction();
    bool MoveIndexByStep(int32_t step);
    void FireOnSelect(int32_t selectIndex, bool fromPress);
    void RemoveBubble();
    void StartCollapseDelayTask(RefPtr<FrameNode>& hostNode, uint32_t duration = INDEXER_COLLAPSE_WAIT_DURATION);
    void OnSelect();
    int32_t GetSkipChildIndex(int32_t step);
    void UpdatePopupOpacity(float ratio);
    void UpdatePopupVisibility(VisibleType visible);
    int32_t GenerateAnimationId();
    void UpdateBubbleBackgroundView();
    void ItemSelectedInAnimation(RefPtr<FrameNode>& itemNode);
    void ItemSelectedOutAnimation(RefPtr<FrameNode>& itemNode);
    void ShowBubble();

private:
    void OnModifyDone() override;
    void InitArrayValue(bool& autoCollapseModeChanged, bool& itemCountChanged);
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnColorConfigurationUpdate() override;
    void DumpInfo() override;
    void OnColorModeChange(uint32_t colorMode) override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override {}
    void BuildArrayValueItems();
    void BuildFullArrayValue();
    void CollapseArrayValue();
    void ApplySevenPlusOneMode(int32_t fullArraySize);
    void ApplyFivePlusOneMode(int32_t fullArraySize);
    int32_t GetAutoCollapseIndex(int32_t propSelect);
    int32_t GetActualIndex(int32_t index);

    void OnTouchDown(const TouchEventInfo& info);
    void OnTouchUp(const TouchEventInfo& info);
    void MoveIndexByOffset(const Offset& offset, bool isTouch = true);
    bool KeyIndexByStep(int32_t step);
    bool MoveIndexBySearch(const std::string& searchStr);
    void ApplyIndexChanged(
        bool isTextNodeInTree, bool selectChanged = true, bool fromTouchUp = false, bool indexerSizeChanged = false);
    void UpdateChildTextStyle(RefPtr<IndexerLayoutProperty>& layoutProperty,
        RefPtr<IndexerPaintProperty>& paintProperty, bool isTextNodeInTree, bool fromTouchUp);
    void UpdateFontStyle(RefPtr<IndexerLayoutProperty>& layoutProperty, RefPtr<IndexerTheme>& indexerTheme,
        TextStyle& unselectedFontStyle, TextStyle& selectedFontStyle);
    void UpdateHoverAndPressStyle(RefPtr<IndexerPaintProperty>& paintProperty, RefPtr<RenderContext>& textRenderContext,
        RefPtr<IndexerTheme>& indexerTheme, int32_t index) const;
    void UpdateFocusAndSelectedStyle(RefPtr<IndexerPaintProperty>& paintProperty,
        RefPtr<RenderContext>& textRenderContext, RefPtr<IndexerTheme>& indexerTheme, int32_t index,
        bool fromTouchUp) const;
    void UpdateNormalStyle(RefPtr<RenderContext>& textRenderContext, int32_t index, bool fromTouchUp) const;
    void UpdateTextLayoutProperty(RefPtr<FrameNode>& textNode, int32_t index, Dimension& borderWidth,
        TextStyle& fontStyle, Color& textColor) const;
    int32_t GetFocusChildIndex(const std::string& searchStr);

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitInputEvent();
    void InitCurrentInputEvent();
    void InitChildInputEvent(RefPtr<FrameNode>& itemNode, int32_t childIndex);
    void InitPopupInputEvent();
    void InitPopupPanEvent();
    void InitOnKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);
    void OnHover(bool isHover);
    void OnChildHover(int32_t index, bool isHover);
    void OnPopupHover(bool isHover);
    void ResetStatus();
    void OnKeyEventDisappear();
    void UpdateBubbleListItem(const RefPtr<FrameNode>& parentNode, RefPtr<IndexerTheme>& indexerTheme);
    void AddPopupTouchListener(RefPtr<FrameNode> popupNode);
    void OnPopupTouchDown(const TouchEventInfo& info);
    void AddListItemClickListener(RefPtr<FrameNode>& listItemNode, int32_t index);
    void OnListItemClick(int32_t index);
    void ClearClickStatus();
    void ChangeListItemsSelectedStyle(int32_t clickIndex);
    RefPtr<FrameNode> CreatePopupNode();
    void UpdateBubbleList();
    void UpdateBubbleView();
    Shadow GetPopupShadow();
    void UpdateBubbleSize();
    void CreateBubbleListView();
    void UpdateBubbleListView();
    bool NeedShowPopupView();
    bool NeedShowBubble();
    bool IfSelectIndexValid();
    int32_t GetSelectChildIndex(const Offset& offset, bool isTouch = true);
    void StartBubbleAppearAnimation();
    void StartDelayTask(uint32_t duration = INDEXER_BUBBLE_WAIT_DURATION);
    void StartBubbleDisappearAnimation();
    void IndexerHoverInAnimation();
    void IndexerHoverOutAnimation();
    void IndexerPressInAnimation();
    void ItemSelectedChangedAnimation();
    void IndexerPressOutAnimation();
    void SetActionSelect(RefPtr<FrameNode>& textNode, RefPtr<AccessibilityProperty>& accessibilityProperty);
    void SetActionClearSelection(RefPtr<FrameNode>& textNode, RefPtr<AccessibilityProperty>& accessibilityProperty);
    CalcSize CalcBubbleListSize(int32_t popupSize, int32_t maxItemsSize);
    GradientColor CreatePercentGradientColor(float percent, Color color);
    void UpdateBubbleLetterView(bool showDivider);
    void UpdateBubbleLetterStackAndLetterTextView();
    void DrawPopupListGradient(PopupListGradientStatus gradientStatus);
    void UpdatePopupListGradientView(int32_t popupSize, int32_t maxItemsSize);
    RefPtr<FrameNode> GetLetterNode();
    RefPtr<FrameNode> GetAutoCollapseLetterNode();
    void UpdateBubbleListSize();
    void UpdateBubbleListItemContext(
        const RefPtr<FrameNode>& listNode, RefPtr<IndexerTheme>& indexerTheme, uint32_t pos);
    void UpdateBubbleListItemMarkModify(RefPtr<FrameNode>& textNode, RefPtr<FrameNode>& listItemNode);
    void ReportSelectEvent();
    void ReportPoupSelectEvent();
    std::vector<int32_t> collapsedItemNums_;
    int32_t collapsedIndex_ = 0;
    int32_t lastCollapsedIndex_ = 0;
   
protected:
    RefPtr<FrameNode> popupNode_;
    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<PanEvent> panEvent_;
    RefPtr<Animator> bubbleAnimator_;
    bool isInputEventRegisted_ = false;
    bool isKeyEventRegisted_ = false;
    bool isTouch_ = false;
    bool isHover_ = false;
    bool isPopup_ = false;
    bool isPopupHover_ = false;

     // the array of displayed items, ths second param in the pair
     // indicates whether the item should be hidden and displayed as dot
    std::vector<std::pair<std::string, bool>> arrayValue_;
    // full array of items, used in auto-collapse mode
    std::vector<std::string> fullArrayValue_;
    // sharp item count is 0 or 1, indicates whether the first item is # in
    // original array, used in auto-collapse mode
    int32_t sharpItemCount_ = 0;
    int32_t itemCount_ = 0;
    int32_t selected_ = 0;
    int32_t animateSelected_ = -1;
    int32_t lastSelected_ = -1;
    bool initialized_ = false;
    int32_t childHoverIndex_ = -1;
    int32_t childFocusIndex_ = -1;
    int32_t childPressIndex_ = -1;
    int32_t animationId_ = 0;
    int32_t lastPopupIndex_ = -1;
    uint32_t lastPopupSize_ = 0;
    int32_t currentPopupIndex_ = -1;
    float itemHeight_ = 0.0f;
    int32_t popupClickedIndex_ = -1;
    int32_t lastFireSelectIndex_ = -1;
    float lastItemSize_ = -1.0f;
    bool lastIndexFromPress_ = false;
    bool selectChanged_ = false;
    bool autoCollapse_ = true;
    bool lastAutoCollapse_ = true;
    bool enableHapticFeedback_ = true;
    float maxContentHeight_ = 0.0f;
    bool isNewHeightCalculated_ = false;
    bool selectedChangedForHaptic_ = false;
    IndexerCollapsingMode lastCollapsingMode_ = IndexerCollapsingMode::INVALID;
    CancelableCallback<void()> delayTask_;
    CancelableCallback<void()> delayCollapseTask_;
    float actualIndexerHeight_ = 0.0f;
    float itemSizeRender_ = 0.0f;
    std::vector<std::string> currentListData_ = std::vector<std::string>();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H
