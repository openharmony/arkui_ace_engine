/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h"
#include "core/components_ng/pattern/text_drag/text_drag_paint_method.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
constexpr Dimension TEXT_DRAG_RADIUS = 18.0_vp;
constexpr Dimension TEXT_DRAG_OFFSET = 8.0_vp;
constexpr Dimension TEXT_DRAG_MIN_WIDTH = 64.0_vp;
constexpr uint32_t TEXT_DRAG_COLOR_BG = 0xf2ffffff;

struct SelectPositionInfo {
    SelectPositionInfo() {}
    SelectPositionInfo(float startX, float startY, float endX, float endY)
        : startX_(startX), startY_(startY), endX_(endX), endY_(endY)
    {}

    void InitGlobalInfo(float globalX, float globalY)
    {
        globalX_ = globalX;
        globalY_ = globalY;
    }

    float startX_ = 0;
    float startY_ = 0;
    float endX_ = 0;
    float endY_ = 0;
    float globalX_ = 0;
    float globalY_ = 0;
};

struct TextDragData {
    TextDragData() {}
    TextDragData(RectF textRect, float frameWidth, float frameHeight, float lineHeight, float lastLineHeight)
        : textRect_(textRect), frameWidth_(frameWidth), frameHeight_(frameHeight), lineHeight_(lineHeight),
          lastLineHeight_(lastLineHeight)
    {}

    RectF textRect_;
    float frameWidth_ = 0;
    float frameHeight_ = 0;
    float lineHeight_ = 0;
    float lastLineHeight_ = 0;
    SelectPositionInfo selectPosition_;
    bool oneLineSelected_ = false;
    void initSelecitonInfo(SelectPositionInfo selectionInfo, bool oneLineSelected)
    {
        selectPosition_ = selectionInfo;
        oneLineSelected_ = oneLineSelected;
    }
};

struct TextPoint {
    TextPoint() {}
    TextPoint(float x, float y) : x(x), y(y) {}

    float x = 0;
    float y = 0;
};

class TextDragPattern : public Pattern {
    DECLARE_ACE_TYPE(TextDragPattern, Pattern);

public:
    TextDragPattern() = default;
    ~TextDragPattern() override = default;
    static RefPtr<FrameNode> CreateDragNode(const RefPtr<FrameNode>& hostNode);
    void Initialize(const RefPtr<Paragraph>& paragraph, const TextDragData& data)
    {
        paragraph_ = paragraph;
        textDragData_ = data;
    }

    void UpdateParagraph(const RefPtr<Paragraph>& paragraph)
    {
        paragraph_ = paragraph;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!overlayModifier_) {
            overlayModifier_ = AceType::MakeRefPtr<TextDragOverlayModifier>(WeakClaim(this));
        }
        return MakeRefPtr<TextDragPaintMethod>(WeakClaim(this), overlayModifier_);
    }

    const WeakPtr<Paragraph>& GetParagraph() const
    {
        return paragraph_;
    }

    virtual const RefPtr<TextDragOverlayModifier>& GetOverlayModifier() const
    {
        return overlayModifier_;
    }

    const RectF& GetTextRect() const
    {
        return textDragData_.textRect_;
    }

    float GetFrameWidth() const
    {
        return textDragData_.frameWidth_;
    }

    float GetFrameHeight() const
    {
        return textDragData_.frameHeight_;
    }

    float GetLineHeight() const
    {
        return textDragData_.lineHeight_;
    }

    const SelectPositionInfo& GetSelectPosition() const
    {
        return textDragData_.selectPosition_;
    }

    bool OneLineSelected() const
    {
        return textDragData_.oneLineSelected_;
    }

    const std::shared_ptr<RSPath>& GetClipPath()
    {
        if (!clipPath_) {
            clipPath_ = GenerateClipPath();
        }
        return clipPath_;
    }

    const std::shared_ptr<RSPath>& GetBackgroundPath()
    {
        if (!backGroundPath_) {
            backGroundPath_ = GenerateBackgroundPath(TEXT_DRAG_OFFSET.ConvertToPx());
        }
        return backGroundPath_;
    }

    const std::shared_ptr<RSPath>& GetSelBackgroundPath()
    {
        if (!selBackGroundPath_) {
            selBackGroundPath_ = GenerateSelBackgroundPath(0.0);
        }
        return selBackGroundPath_;
    }

    std::shared_ptr<RSPath> GenerateBackgroundPath(float offset, float radiusRatio = 1.0f);

    std::shared_ptr<RSPath> GenerateSelBackgroundPath(float offset);

    void SetImageChildren(const std::list<RefPtr<FrameNode>>& imageChildren)
    {
        imageChildren_ = imageChildren;
    }

    const std::list<RefPtr<FrameNode>>& GetImageChildren()
    {
        return imageChildren_;
    }

    void InitSpanImageLayout(
        const std::list<RefPtr<FrameNode>>& imageChildren, const std::vector<RectF>& rectsForPlaceholders)
    {
        imageChildren_ = imageChildren;
        rectsForPlaceholders_ = rectsForPlaceholders;
    }

    OffsetF GetContentOffset()
    {
        return contentOffset_;
    }

    void SetContentOffset(OffsetF contentOffset)
    {
        contentOffset_ = contentOffset;
    }

    const std::vector<RectF>& GetRectsForPlaceholders()
    {
        return rectsForPlaceholders_;
    }

    virtual Dimension GetDragCornerRadius()
    {
        return TEXT_DRAG_RADIUS;
    }

    Color GetDragBackgroundColor();
protected:
    static TextDragData CalculateTextDragData(RefPtr<TextDragBase>& pattern, RefPtr<FrameNode>& dragNode);
    static void AdjustMaxWidth(float& width, const RectF& contentRect, const std::vector<RectF>& boxes);
    static RectF GetHandler(const bool isLeftHandler, const std::vector<RectF> boxes, const RectF contentRect,
        const OffsetF globalOffset, const OffsetF textStartOffset);
    static void AdjustHandlers(const RectF contentRect, RectF& leftHandler, RectF& rightHandler);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    std::shared_ptr<RSPath> GenerateClipPath();
    void GenerateBackgroundPoints(std::vector<TextPoint>& points, float offset, bool needAdjust = true);
    void CalculateLineAndArc(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path, float radiusRatio);
    void CalculateLine(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path);
    static void CalculateFloatTitleOffset(RefPtr<FrameNode>& dragNode, OffsetF& offset);

    void SetLastLineHeight(float lineHeight)
    {
        lastLineHeight_ = lineHeight;
    }

protected:
    RefPtr<TextDragOverlayModifier> overlayModifier_;
    TextDragData textDragData_;

private:
    float lastLineHeight_ = 0.0f;
    OffsetF contentOffset_;
    WeakPtr<Paragraph> paragraph_;
    std::shared_ptr<RSPath> clipPath_;
    std::shared_ptr<RSPath> backGroundPath_;
    std::shared_ptr<RSPath> selBackGroundPath_;
    std::list<RefPtr<FrameNode>> imageChildren_;
    std::vector<RectF> rectsForPlaceholders_;

    ACE_DISALLOW_COPY_AND_MOVE(TextDragPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_PATTERN_H
