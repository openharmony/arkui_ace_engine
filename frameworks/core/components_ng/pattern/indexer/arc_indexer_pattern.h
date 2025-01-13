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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_INDEXER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_INDEXER_PATTERN_H

#include "core/components_ng/pattern/indexer/indexer_pattern.h"
#include "core/components_ng/pattern/indexer/arc_indexer_content_modifier.h"
#include "core/components_ng/pattern/indexer/arc_indexer_layout_algorithm.h"
#include "core/components_ng/pattern/indexer/arc_indexer_paint_method.h"
#include "core/components_ng/pattern/indexer/arc_indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/arc_indexer_paint_property.h"

namespace OHOS::Ace::NG {
class ArcIndexerPattern : public IndexerPattern {
    DECLARE_ACE_TYPE(ArcIndexerPattern, IndexerPattern)
public:
    ArcIndexerPattern() = default;
    ~ArcIndexerPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!contentModifier_) {
            contentModifier_ = AceType::MakeRefPtr<ArcIndexerContentModifier>();
        }
        return MakeRefPtr<ArcIndexerPaintMethod>(
            strokeWidth_, arcCenter_, startAngle_, sweepAngle_, arcRadius_, stepAngle_, contentModifier_);
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<IndexerEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ArcIndexerLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ArcIndexerPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto arcindexerLayoutAlgorithm = MakeRefPtr<ArcIndexerLayoutAlgorithm>(itemCount_, fullCount_);
        return arcindexerLayoutAlgorithm;
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

    void SetIsScreenReaderOn(bool isScreenReaderOn)
    {
        isScreenReaderOn_ = isScreenReaderOn;
    }

    bool IsMeasureBoundary() const override;
    void UpdateChildBoundary(RefPtr<FrameNode>& frameNode);
    void RemoveAccessibilityClickEvent();
    void InitAccessibilityClickEvent();

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void DumpInfo() override;

    void InitArrayValue(bool& autoCollapseModeChanged);
    void BuildArrayValueItems();
    void BuildFullArrayValue();
    void CollapseArrayValue();
    void ApplyFourPlusOneMode();

    void OnTouchDown(const TouchEventInfo& info);
    void OnTouchUp(const TouchEventInfo& info);
    void MoveIndexByOffset(const Offset& offset);
    int32_t GetFocusIndex(int32_t selected);
    void ApplyIndexChanged(bool isTextNodeInTree, bool refreshBubble = true, bool fromTouchUp = false,
        bool indexerSizeChanged = false);
    void OnSelect();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitTouchEvent ();
    void ResetArrayValue (bool isModeChanged);
    void UpdateChildNodeStyle(int32_t index);
    void SetChildNodeStyle(int32_t index, const std::string &nodeStr, bool fromTouchUp);
    void SetFocusIndexStyle(int32_t index, const std::string &nodeStr, bool isTextNodeInTree);
    std::string GetChildNodeContent(int32_t index);
    void UpdateIndexerRender();
    void ResetStatus();
    RefPtr<FrameNode> CreatePopupNode();
    void UpdateBubbleView();
    void UpdateBubbleLetterView(bool showDivider, std::vector<std::string>& currentListData);
    bool NeedShowBubble();
    void ShowBubble(bool isShow);
    bool IfSelectIndexValid();
    int32_t GetSelectChildIndex(const Offset& offset);
    void StartBubbleAppearAnimation();
    void StartDelayTask(uint32_t duration = ARC_INDEXER_BUBBLE_WAIT_DURATION);
    void StartBubbleDisappearAnimation();
    void ArcExpandedAnimation(int32_t nextIndex);
    void ArcCollapedAnimation(int32_t nextIndex);
    void ArcIndexerPressInAnimation();
    void ArcIndexerPressOutAnimation();
    void UpdateStartAndEndIndexbySelected();
    void UpdateStartAndEndIndexByTouch();

    void SetIndexerNodeOpacity(const RefPtr<FrameNode>& itemNode, float ratio);
    void UpdateIndexerNodeOpacityByIdx(RefPtr<RenderContext>& context, int32_t index);
    void StartIndexerNodeAppearAnimation(int32_t nodeIndex);
    void StartIndexerNodeDisappearAnimation(int32_t nodeIndex);
    void IndexNodeCollapsedAnimation();
    void IndexNodeExpandedAnimation();
    int32_t GetActualIndex(int32_t selectIndex);
    void FireOnSelect(int32_t selectIndex, bool fromPress);
    void UpdateBubbleBackgroundView();
    void UpdateBubbleLetterStackAndLetterTextView();
    RefPtr<FrameNode> GetLetterNode();
    float CalcArcItemAngle(int32_t index);
    float GetPositionAngle(const Offset& position);
    bool AtArcHotArea(const Offset& position);
    void FireAccessbilityExpanded();
    void FireAccessbilityCollapsed();
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void InitializeAccessibility();
    void FireAccessibilityIndexChanged(bool selectChanged, bool fromTouchUp);
    void InitExpandedProperty();
    void InitCollapsedProperty();

    std::vector<std::pair<std::string, ArcIndexerBarState>> arcArrayValue_;
    int32_t fullCount_ = 0;
    float arcIndexerSize_ = 0.0f;
    ArcIndexerCollapsingMode lastCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    ArcIndexerCollapsingMode currectCollapsingMode_ = ArcIndexerCollapsingMode::NONE;
    float strokeWidth_ = 24.0f;
    OffsetF arcCenter_;
    float startAngle_ = 0.0F;
    float sweepAngle_ = 0.0f;
    RefPtr<NodeAnimatablePropertyFloat> expandedProperty_;
    int32_t expandedAnimateIndex_ = 0;
    RefPtr<NodeAnimatablePropertyFloat> collapsedProperty_;
    int32_t collapsedAnimateIndex_ = 0;
    bool atomicAnimateOp_ = true;
    float arcRadius_ = 0.0f;
    float stepAngle_ = 0.0f;
    float itemRadius_ = 0.0f;
    RefPtr<ArcIndexerContentModifier> contentModifier_;
    int32_t startIndex_ = 0;
    int32_t endIndex_ = ARC_INDEXER_COLLAPSE_ITEM_COUNT;
    RefPtr<ClickEvent> expandedClickListener_;
    RefPtr<ClickEvent> collapsedClickListener_;
    std::shared_ptr<AccessibilitySAObserverCallback> accessibilitySAObserverCallback_;
    WeakPtr<FrameNode> expandedNode_ = nullptr;
    WeakPtr<FrameNode> collapsedNode_ = nullptr;
    bool isScreenReaderOn_ = false;
    bool isClickActionFire_ = false;
    int32_t focusIndex_ = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_INDEXER_PATTERN_H
