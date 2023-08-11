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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_CONTENT_MODIFIER_H

#include <optional>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class TextContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(TextContentModifier, ContentModifier)

public:
    TextContentModifier(const std::optional<TextStyle> textStyle);

    void onDraw(DrawingContext& drawingContext) override;

    void SetFontFamilies(const std::vector<std::string>& value);
    void SetFontSize(const Dimension& value);
    void SetFontWeight(const FontWeight& value);
    void SetTextColor(const Color& value);
    void SetTextShadow(const Shadow& value);
    void SetTextDecoration(const TextDecoration& value);
    void SetTextDecorationStyle(const TextDecorationStyle& value);
    void SetTextDecorationColor(const Color& value);
    void SetBaselineOffset(const Dimension& value);
    void SetContentOffset(OffsetF& value);
    void SetContentSize(SizeF& value);

    void ContentChange();

    void ModifyTextStyle(TextStyle& textStyle);

    void StartTextRace();
    void StopTextRace();

    void SetParagraph(RefPtr<Paragraph> paragraph)
    {
        paragraph_ = paragraph;
    }

    void SetPrintOffset(const OffsetF& paintOffset)
    {
        paintOffset_ = paintOffset;
    }

    void SetObscured(const std::vector<ObscuredReasons>& reasons)
    {
        obscuredReasons_ = reasons;
    }

    void SetIfHaveSpanItemChildren(bool value)
    {
        ifHaveSpanItemChildren_ = value;
    }

    void SetDrawObscuredRects(const std::vector<Rect>& drawObscuredRects)
    {
        drawObscuredRects_ = drawObscuredRects;
    }

    bool NeedMeasureUpdate(PropertyChangeFlag& flag);

    void SetClip(bool clip);

    void SetFontReady(bool value);

private:
    double NormalizeToPx(const Dimension& dimension);
    void SetDefaultAnimatablePropertyValue(const TextStyle& textStyle);
    void SetDefaultFontSize(const TextStyle& textStyle);
    void SetDefaultFontWeight(const TextStyle& textStyle);
    void SetDefaultTextColor(const TextStyle& textStyle);
    void SetDefaultTextShadow(const TextStyle& textStyle);
    void SetDefaultTextDecoration(const TextStyle& textStyle);
    void SetDefaultBaselineOffset(const TextStyle& textStyle);

    float GetTextRacePercent();

    void ModifyFontSizeInTextStyle(TextStyle& textStyle);
    void ModifyFontWeightInTextStyle(TextStyle& textStyle);
    void ModifyTextColorInTextStyle(TextStyle& textStyle);
    void ModifyTextShadowsInTextStyle(TextStyle& textStyle);
    void ModifyDecorationInTextStyle(TextStyle& textStyle);
    void ModifyBaselineOffsetInTextStyle(TextStyle& textStyle);

    void UpdateFontSizeMeasureFlag(PropertyChangeFlag& flag);
    void UpdateFontWeightMeasureFlag(PropertyChangeFlag& flag);
    void UpdateTextColorMeasureFlag(PropertyChangeFlag& flag);
    void UpdateTextShadowMeasureFlag(PropertyChangeFlag& flag);
    void UpdateTextDecorationMeasureFlag(PropertyChangeFlag& flag);
    void UpdateBaselineOffsetMeasureFlag(PropertyChangeFlag& flag);

    void DrawObscuration(DrawingContext& drawingContext);

private:
    std::optional<Dimension> fontSize_;
    RefPtr<AnimatablePropertyFloat> fontSizeFloat_;

    std::optional<FontWeight> fontWeight_;
    RefPtr<AnimatablePropertyFloat> fontWeightFloat_;

    std::optional<Color> textColor_;
    RefPtr<AnimatablePropertyColor> animatableTextColor_;

    std::optional<Shadow> textShadow_;
    RefPtr<AnimatablePropertyFloat> shadowBlurRadiusFloat_;
    RefPtr<AnimatablePropertyFloat> shadowOffsetXFloat_;
    RefPtr<AnimatablePropertyFloat> shadowOffsetYFloat_;
    RefPtr<AnimatablePropertyColor> shadowColor_;

    float oldColorAlpha_ { 0.0f };
    std::optional<TextDecoration> textDecoration_;
    std::optional<TextDecorationStyle> textDecorationStyle_;
    std::optional<Color> textDecorationColor_;
    RefPtr<AnimatablePropertyFloat> textDecorationColorAlpha_;
    bool textDecorationAnimatable_ { false };

    std::optional<Dimension> baselineOffset_;
    RefPtr<AnimatablePropertyFloat> baselineOffsetFloat_;

    bool textRacing_ = false;
    RefPtr<AnimatablePropertyFloat> racePercentFloat_;
    std::shared_ptr<AnimationUtils::Animation> raceAnimation_;

    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<PropertyBool> contentChange_;
    RefPtr<PropertyBool> clip_;
    RefPtr<PropertyString> fontFamilyString_;
    RefPtr<PropertyBool> fontReady_;

    RefPtr<Paragraph> paragraph_;
    OffsetF paintOffset_;
    float textRaceSpaceWidth_ = 0;

    std::vector<ObscuredReasons> obscuredReasons_;
    bool ifHaveSpanItemChildren_ = false;
    std::vector<Rect> drawObscuredRects_;

    ACE_DISALLOW_COPY_AND_MOVE(TextContentModifier);
};
} // namespace OHOS::Ace::NG

#endif