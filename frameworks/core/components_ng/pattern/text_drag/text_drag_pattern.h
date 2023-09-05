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

namespace OHOS::Ace::NG {
constexpr Dimension TEXT_DRAG_RADIUS = 12.0_vp;
constexpr Dimension TEXT_DRAG_OFFSET = 8.0_vp;
constexpr Dimension TEXT_DRAG_MIN_WIDTH = 64.0_vp;
constexpr uint32_t TEXT_DRAG_COLOR_BG = 0xf2ffffff;

struct SelectPositionInfo {
    SelectPositionInfo() {}
    SelectPositionInfo(float startX, float startY, float endX, float endY)
        : startX_(startX), startY_(startY), endX_(endX), endY_(endY)
    {}

    float startX_ = 0;
    float startY_ = 0;
    float endX_ = 0;
    float endY_ = 0;
};

struct TextDragData {
    TextDragData() {}
    TextDragData(RectF textRect, float frameWidth, float frameHeight, float lineHeight, SelectPositionInfo position,
        bool oneLineSelected)
        : textRect_(textRect), frameWidth_(frameWidth), frameHeight_(frameHeight), lineHeight_(lineHeight),
          selectPosition_(position), oneLineSelected_(oneLineSelected)
    {}

    RectF textRect_;
    float frameWidth_ = 0;
    float frameHeight_ = 0;
    float lineHeight_ = 0;
    SelectPositionInfo selectPosition_;
    bool oneLineSelected_ = false;
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

    void Initialize(const ParagraphT& paragraph, const TextDragData& data)
    {
        paragraph_ = paragraph;
        textDragData_ = data;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!overlayModifier_) {
            overlayModifier_ = AceType::MakeRefPtr<TextDragOverlayModifier>(WeakClaim(this));
        }
        return MakeRefPtr<TextDragPaintMethod>(WeakClaim(this), overlayModifier_);
    }

    const ParagraphT& GetParagraph() const
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

    std::shared_ptr<RSPath> GenerateBackgroundPath(float offset);

    void SetImageChildren(const std::list<RefPtr<FrameNode>>& imageChildren)
    {
        imageChildren_ = imageChildren;
    }

    const std::list<RefPtr<FrameNode>>& GetImageChildren()
    {
        return imageChildren_;
    }

    void InitSpanImageLayout(
        const std::list<RefPtr<FrameNode>>& imageChildren, const std::vector<Rect>& rectsForPlaceholders)
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

    const std::vector<Rect>& GetRectsForPlaceholders()
    {
        return rectsForPlaceholders_;
    }

protected:
    static TextDragData CalculateTextDragData(RefPtr<TextDragBase>& hostPattern, RefPtr<FrameNode>& dragContext);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    std::shared_ptr<RSPath> GenerateClipPath();
    void GenerateBackgroundPoints(std::vector<TextPoint>& points, float offset);
    void CalculateLineAndArc(std::vector<TextPoint>& points, std::shared_ptr<RSPath>& path);

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
    ParagraphT paragraph_;
    std::shared_ptr<RSPath> clipPath_;
    std::shared_ptr<RSPath> backGroundPath_;
    std::list<RefPtr<FrameNode>> imageChildren_;
    std::vector<Rect> rectsForPlaceholders_;

    ACE_DISALLOW_COPY_AND_MOVE(TextDragPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_DRAG_TEXT_DRAG_PATTERN_H
