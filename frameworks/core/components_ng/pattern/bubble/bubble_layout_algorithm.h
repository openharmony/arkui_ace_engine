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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_ALGORITHM_H

#include <optional>
#include <string>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
namespace OHOS::Ace::NG {
enum class ArrowOfTargetOffset {
    START,
    CENTER,
    END,
    NONE,
};
// BubbleLayoutAlgorithm uses for Popup Node.
class ACE_EXPORT BubbleLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(BubbleLayoutAlgorithm, LayoutAlgorithm);

public:
    BubbleLayoutAlgorithm() = default;
    BubbleLayoutAlgorithm(int32_t id, const std::string& tag, const std::optional<OffsetF>& targetOffset = std::nullopt,
        const std::optional<SizeF>& targetSize = std::nullopt);
    ~BubbleLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    SizeF GetTargetSize() const
    {
        return targetSize_;
    }

    OffsetF GetTargetOffset() const
    {
        return targetOffsetForPaint_;
    }

    SizeF GetChildSize() const
    {
        return childSize_;
    }

    OffsetF GetChildOffset() const
    {
        return childOffsetForPaint_;
    }

    bool ShowArrow() const
    {
        return showArrow_;
    }

    OffsetF GetArrowPosition() const
    {
        return arrowPositionForPaint_;
    }

    RectF GetTouchRegion() const
    {
        return touchRegion_;
    }

    Placement GetArrowPlacement() const
    {
        return arrowPlacement_;
    }
    std::string GetClipPath() const
    {
        return clipPath_;
    }
    RefPtr<FrameNode> GetClipFrameNode()
    {
        return clipFrameNode_;
    }
    const std::vector<float>& GetArrowOffsetsFromClip() const
    {
        return arrowOffsetsFromClip_;
    }

protected:
    OffsetF positionOffset_;
    SizeF wrapperSize_;

private:
    enum class ErrorPositionType {
        NORMAL = 0,
        TOP_LEFT_ERROR,
        BOTTOM_RIGHT_ERROR,
    };
    bool CheckPosition(const OffsetF& position, const SizeF& childSize, size_t step, size_t& i);
    OffsetF GetPositionWithPlacementTop(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementTopLeft(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementTopRight(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementBottom(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementBottomLeft(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementBottomRight(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementLeft(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementLeftTop(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementLeftBottom(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementRight(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementRightTop(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF GetPositionWithPlacementRightBottom(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    OffsetF AddTargetSpace(const OffsetF& position);
    OffsetF AddOffset(const OffsetF& position);
    bool CheckPositionInPlacementRect(const Rect& rect, const OffsetF& position, const SizeF& childSize);
    OffsetF AdjustPosition(const OffsetF& position, float width, float height, float space);
    OffsetF GetAdjustPosition(std::vector<Placement>& currentPlacementStates, size_t step, const SizeF& childSize,
        const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition);
    void InitTargetSizeAndPosition(bool showInSubWindow);
    void InitCaretTargetSizeAndPosition();
    void InitProps(const RefPtr<BubbleLayoutProperty>& layoutProp, bool showInSubWindow);
    void InitArrowState(const RefPtr<BubbleLayoutProperty>& layoutProp);
    OffsetF GetPositionWithPlacement(
        const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition, OffsetF& arrowPosition);
    OffsetF GetChildPosition(const SizeF& childSize, bool didNeedArrow, bool useArrowOffset);
    OffsetF FitToScreen(
        const OffsetF& position, size_t step, size_t& i, const SizeF& childSize, bool didNeedArrow = false);
    bool GetIfNeedArrow(const RefPtr<BubbleLayoutProperty>& bubbleProp, const SizeF& childSize);
    void UpdateChildPosition(OffsetF& childOffset);
    void UpdateTouchRegion();

    std::string MoveTo(double x, double y);
    std::string LineTo(double x, double y);
    std::string ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y);
    void UpdateClipOffset(const RefPtr<FrameNode>& frameNode);

    std::string ClipBubbleWithPath();
    float GetArrowOffset(const Placement& placement);
    void InitEdgeSize(Edge& edge);
    float ModifyBorderRadius(float borderRadius, float halfChildHeight);
    void GetArrowBuildPlacement(Placement& arrowBuildplacement);
    std::string BuildTopLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement);
    std::string BuildRightLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement);
    std::string BuildBottomLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement);
    std::string BuildLeftLinePath(float arrowOffset, float radius, Placement& arrowBuildplacement);
    std::string ReplaceArrowTopLeft(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowTopRight(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowRightTop(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowRightBottom(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowBottomLeft(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowBottomRight(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowLeftTop(const float arrowOffset, const float childOffset);
    std::string ReplaceArrowLeftBottom(const float arrowOffset, const float childOffset);
    std::string BuildCornerPath(const Placement& placement, float radius);
    void UpdateArrowOffset(const std::optional<Dimension>& offset, const Placement& placement);
    void BubbleAvoidanceRule(RefPtr<LayoutWrapper> child, RefPtr<BubbleLayoutProperty> bubbleProp,
        RefPtr<FrameNode> bubbleNode, bool showInSubWindow);
    ArrowOfTargetOffset arrowOfTargetOffset_ = ArrowOfTargetOffset::NONE;
    Dimension arrowOffset_;

    int32_t targetNodeId_ = -1;
    std::string targetTag_;
    bool bCaretMode_ = false;

    SizeF targetSize_;
    OffsetF targetOffset_;
    OffsetF targetOffsetForPaint_;
    SizeF childSize_;
    OffsetF childOffset_;
    OffsetF childOffsetForPaint_;
    OffsetF arrowPosition_;
    OffsetF arrowPositionForPaint_;
    SizeF selfSize_;
    RectF touchRegion_;
    SizeF buttonRowSize_;
    OffsetF buttonRowOffset_;

    Edge padding_;
    Edge margin_;
    Border border_;
    Placement arrowPlacement_ = Placement::BOTTOM;
    Placement placement_ = Placement::BOTTOM;
    Dimension targetSpace_;
    Dimension borderRadius_;

    bool showArrow_ = false;
    bool enableArrow_ = false;
    float scaledBubbleSpacing_ = 0.0f;
    float arrowHeight_ = 0.0f;

    float paddingStart_ = 0.0f;
    float paddingEnd_ = 0.0f;
    float paddingTop_ = 0.0f;
    float paddingBottom_ = 0.0f;
    bool bHorizontal_ = false;
    bool bVertical_ = false;
    std::unordered_set<Placement> setHorizontal_;
    std::unordered_set<Placement> setVertical_;
    float targetSecurity_ = 0.0f;
    using PlacementFunc = OffsetF (BubbleLayoutAlgorithm::*)(const SizeF&, const OffsetF&, const OffsetF&, OffsetF&);
    std::map<Placement, PlacementFunc> placementFuncMap_;
    std::string clipPath_;
    RefPtr<FrameNode> clipFrameNode_;
    ACE_DISALLOW_COPY_AND_MOVE(BubbleLayoutAlgorithm);
    // top right bottom left
    std::vector<float> arrowOffsetsFromClip_ = { 0.0f, 0.0f, 0.0f, 0.0f };
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_LAYOUT_ALGORITHM_H
