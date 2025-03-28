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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_PAINT_METHOD_H

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BubblePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(BubblePaintMethod, NodePaintMethod)
public:
    BubblePaintMethod() = default;
    ~BubblePaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
            auto bubble = weak.Upgrade();
            if (bubble) {
                bubble->PaintMask(canvas, paintWrapper);
                bubble->ClipBubble(paintWrapper);
                bubble->PaintBorder(canvas, paintWrapper);
            }
        };
    }

    CanvasDrawFunction GetOverlayDrawFunction(PaintWrapper* paintWrapper) override
    {
        return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
            auto bubble = weak.Upgrade();
            if (bubble) {
                bubble->PaintSingleBorder(canvas, paintWrapper);
                bubble->PaintInnerBorder(canvas, paintWrapper);
                bubble->PaintOuterBorder(canvas, paintWrapper);
            }
        };
    }

    void SetShowArrow(bool flag)
    {
        showArrow_ = flag;
    }

    void SetChildOffset(const OffsetF& offset)
    {
        childOffset_ = offset;
    }

    void SetChildSize(const SizeF& size)
    {
        childSize_ = size;
    }

    void SetArrowPosition(const OffsetF& offset)
    {
        arrowPosition_ = offset;
    }

    void SetClipPath(const std::string& clipPath)
    {
        clipPath_ = clipPath;
    }

    void SetBorder(const Border& border)
    {
        border_ = border;
    }

    void SetClipFrameNode(RefPtr<FrameNode>& clipFrameNode)
    {
        clipFrameNode_ = clipFrameNode;
    }

    void SetArrowOffsetsFromClip(const std::vector<std::vector<float>>& arrowOffsetsFromClip)
    {
        arrowOffsetsFromClip_ = arrowOffsetsFromClip;
    }

    void SetArrowWidth(const float arrowWidth)
    {
        arrowWidth_ = arrowWidth;
    }

    void SetArrowHeight(const float arrowHeight)
    {
        arrowHeight_ = arrowHeight;
    }

    void SetOuterBorderWidth(const Dimension outerBorderWidth)
    {
        outerBorderWidth_ = outerBorderWidth.ConvertToPx();
    }

    void SetInnerBorderWidth(const Dimension innerBorderWidth)
    {
        innerBorderWidth_ = innerBorderWidth.ConvertToPx();
    }

    void SetArrowBuildPlacement(const Placement arrowBuildPlacement)
    {
        arrowBuildPlacement_ = arrowBuildPlacement;
    }

    void SetOutlineLinearGradient(const PopupLinearGradientProperties& outlineLinearGradient)
    {
        outlineLinearGradient_ = outlineLinearGradient;
    }

    const PopupLinearGradientProperties& GetOutlineLinearGradient() const
    {
        return outlineLinearGradient_;
    }

    void SetInnerBorderLinearGradient(const PopupLinearGradientProperties& innerBorderLinearGradient)
    {
        innerBorderLinearGradient_ = innerBorderLinearGradient;
    }

    const PopupLinearGradientProperties& GetInnerBorderLinearGradient() const
    {
        return innerBorderLinearGradient_;
    }

    void SetOuterBorderWidthByUser(const Dimension outerBorderWidthByUser)
    {
        outerBorderWidthByUser_ = outerBorderWidthByUser.ConvertToPx();
    }

    void SetInnerBorderWidthByUser(const Dimension innerBorderWidthByUser)
    {
        innerBorderWidthByUser_ = innerBorderWidthByUser.ConvertToPx();
    }

    void PaintBubble(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintMask(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void ClipBubble(PaintWrapper* paintWrapper);
    void PaintSingleBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintDoubleBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintOuterBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintInnerBorder(RSCanvas& canvas, PaintWrapper* paintWrapper);
    bool IsPaintDoubleBorder(PaintWrapper* paintWrapper);
    void DrawDashedBorder(RSCanvas& canvas, RSPen& paint);
    std::vector<RSPoint> BorderLinearGradientPoint(int popupInnerBorderDirectionInt);
    std::pair<std::vector<uint32_t>, std::vector<float>> BorderLinearGradientColors(
        std::vector<PopupGradientColor> popupBorderGradientColor);
    void PaintOuterBorderGradient(RSPen& paint);
    void PaintInnerBorderGradient(RSPen& paint);

private:
    void PaintBubbleWithArrow(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintDoubleBorderWithArrow(RSCanvas& canvas, PaintWrapper* paintWrapper);
    void PaintNonCustomPopup(RSCanvas& canvas, PaintWrapper* wrapper);

    void PaintTopBubble(RSCanvas& canvas);
    void PaintBottomBubble(RSCanvas& canvas);
    void PaintDefaultBubble(RSCanvas& canvas);

    void UpdateArrowOffset(const std::optional<Dimension>& offset, const Placement& placement);

    RSRoundRect MakeRRect();
    float GetArrowOffset(const Placement& placement);
    void InitEdgeSize(Edge& edge);

    void BuildCompletePath(RSPath& path);
    void BuildCornerPath(RSPath& path, const Placement& placement, float radius);
    void BuildTopLinePath(RSPath& path, float arrowOffset, float radius);
    void BuildRightLinePath(RSPath& path, float arrowOffset, float radius);
    void BuildBottomLinePath(RSPath& path, float arrowOffset, float radius);
    void BuildLeftLinePath(RSPath& path, float arrowOffset, float radius);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas);
    void ClipBubbleWithPath(const RefPtr<FrameNode>& frameNode);

    void BuildDoubleBorderPath(RSPath& path);
    void BuildTopDoubleBorderPath(RSPath& path, float radius);
    void BuildRightDoubleBorderPath(RSPath& path, float radius);
    void BuildBottomDoubleBorderPath(RSPath& path, float radius);
    void BuildLeftDoubleBorderPath(RSPath& path, float radius);

    float GetInnerBorderOffset();
    float GetBorderOffset();
    float outerBorderWidth_ = Dimension(0.8_vp).ConvertToPx();
    float innerBorderWidth_ = Dimension(0.6_vp).ConvertToPx();
    bool needPaintOuterBorder_ = false;
    bool isPaintBubble_ = false;
    std::vector<std::vector<float>> arrowOffsetsFromClip_
        = { {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} };
    float arrowWidth_ = Dimension(16.0_vp).ConvertToPx();
    float arrowHeight_ = Dimension(8.0_vp).ConvertToPx();

    // Get from RenderProp
    bool isTips_ = false;
    bool useCustom_ = false;
    Placement arrowPlacement_ = Placement::BOTTOM;
    bool enableArrow_ = false;
    Dimension arrowOffset_;
    Color maskColor_;
    Color backgroundColor_;

    // Get from pattern
    OffsetF childOffset_;
    OffsetF arrowPosition_;
    SizeF childSize_;
    bool showArrow_ = false;
    std::string clipPath_;
    RefPtr<FrameNode> clipFrameNode_;
    Placement arrowBuildPlacement_ = Placement::BOTTOM;
    // Get from theme
    Border border_;
    Edge padding_;
    // top right bottom left
    std::vector<float> arrowOffsetByClips_ = { 0.0f, 0.0f, 0.0f, 0.0f };
    PopupLinearGradientProperties outlineLinearGradient_;
    PopupLinearGradientProperties innerBorderLinearGradient_;
    float outerBorderWidthByUser_;
    float innerBorderWidthByUser_;

#ifndef USE_ROSEN_DRAWING
    RSPath path_;
#else
    RSRecordingPath path_;
#endif

    ACE_DISALLOW_COPY_AND_MOVE(BubblePaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUBBLE_BUBBLE_PAINT_METHOD_H