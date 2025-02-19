/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_OVERLAY_MODIFIER_H

#include <cstdint>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class TextFieldOverlayModifier : public ScrollBarOverlayModifier {
    DECLARE_ACE_TYPE(TextFieldOverlayModifier, ScrollBarOverlayModifier);

public:
    TextFieldOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, WeakPtr<ScrollEdgeEffect>&& edgeEffect);
    ~TextFieldOverlayModifier() override = default;

    void ModifierAttachProperty();

    void onDraw(DrawingContext& context) override;

    void SetCursorColor(Color& value);
    void SetCursorWidth(float value);
    void SetSelectedBackGroundColor(Color& value);
    void SetCursorVisible(bool value);
    void SetContentSize(SizeF& value);
    void SetContentOffset(OffsetF& value);
    void SetCursorOffset(const OffsetF& value);
    void SetFloatingCursorOffset(const OffsetF& value);
    void SetFloatingCursorVisible(bool value);
    void SetShowOriginCursor(bool value);
    void SetInputStyle(InputStyle& value);
    void SetFrameSize(const SizeF& value);
    void SetCurrentOffset(float value);
    void PaintUnderline(RSCanvas& canvas) const;
    void SetUnderlineColor(const Color& value);
    void SetUnderlineWidth(float underlineWidth);
    void SetRedrawFlag(int32_t value);
    void SetScrollBar(const RefPtr<ScrollBar>& scrollBar);
    void SetChangeSelectedRects(bool value);
    void SetFirstHandleOffset(const OffsetF& offset);
    void SetSecondHandleOffset(const OffsetF& offset);
    void SetShowSelect(bool value);

    void SetTextRect(const RectF& textRect)
    {
        textRect_ = textRect;
    }

    void SetShowPreviewTextDecoration(bool value);
    void SetPreviewTextRects(bool value);
    void SetPreviewTextDecorationColor(const Color& value);
    void SetPreviewTextStyle(PreviewTextStyle style);
    void ContentChange();

    void StartFloatingCaretLand(const OffsetF& originCaretOffset);

    bool GetFloatCaretLanding() const
    {
        return caretLanding_;
    }

    void SetFloatCaretLanding(bool caretLanding)
    {
        caretLanding_ = caretLanding;
    }

private:
    void PaintSelection(DrawingContext& context) const;
    void PaintCursor(DrawingContext& context) const;
    void PaintFloatingCursor(DrawingContext& context) const;
    void PaintEdgeEffect(const SizeF& frameSize, RSCanvas& canvas);
    void PaintScrollBar(DrawingContext& context);
    void PaintMagnifier(DrawingContext& context);
    bool GetMagnifierRect(
        float& startX, float& startY, float& endX, float& endY, float& localOffsetX, float& cursorOffsetY);
    std::vector<TextPoint> GetTextPoints(float startX, float startY, float endX, float endY, bool haveOffset = false);
    std::shared_ptr<RSPath> GetPathByPoints(std::vector<TextPoint> points);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas);
    void GetFrameRectClip(RSRect& clipRect, std::vector<RSPoint>& clipRadius);
    void PaintPreviewTextDecoration(DrawingContext& context) const;

    bool caretLanding_ = false;
    bool needPaintSelect_ = false;
    bool needPaintPreviewText = false;
    PreviewTextStyle previewTextStyle_ = PreviewTextStyle::NORMAL;
    WeakPtr<Pattern> pattern_;
    WeakPtr<ScrollBar> scrollBar_;
    WeakPtr<ScrollEdgeEffect> edgeEffect_;
    RefPtr<AnimatablePropertyColor> cursorColor_;
    RefPtr<AnimatablePropertyFloat> cursorWidth_;
    RefPtr<AnimatablePropertyColor> selectedColor_;
    RefPtr<PropertyOffsetF> cursorOffset_;
    RefPtr<PropertyBool> cursorVisible_;
    RefPtr<PropertyBool> showSelect_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertyOffsetF> firstHandleOffset_;
    RefPtr<PropertyOffsetF> secondHandleOffset_;
    RefPtr<PropertyFloat> currentOffset_;
    RefPtr<PropertyFloat> underlineWidth_;
    RefPtr<PropertyColor> underlineColor_;
    InputStyle inputStyle_ = InputStyle::DEFAULT;
    RefPtr<PropertySizeF> frameSize_;
    RefPtr<PropertyBool> changeSelectedRects_;
    RefPtr<PropertyBool> showPreviewText_;
    RefPtr<PropertyBool> changePreviewTextRects_;
    RefPtr<PropertyBool> contentChange_;
    RefPtr<PropertyColor> previewTextDecorationColor_;
    RectF textRect_;
    RefPtr<AnimatablePropertyOffsetF> floatingCursorOffset_;
    RefPtr<PropertyBool> floatingCursorVisible_;
    RefPtr<PropertyBool> showOriginCursor_;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_OVERLAY_MODIFIER_H
