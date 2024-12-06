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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_CONTENT_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class TextFieldContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(TextFieldContentModifier, ContentModifier);

public:
    explicit TextFieldContentModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~TextFieldContentModifier() override = default;

    void onDraw(DrawingContext& context) override;
    void ModifyTextStyle(TextStyle& textStyle);
    void SetDefaultAnimatablePropertyValue();

    void SetFontFamilies(const std::vector<std::string>& value);
    void SetFontSize(const Dimension& value);
    void SetAdaptMinFontSize(const Dimension& value);
    void SetAdaptMaxFontSize(const Dimension& value);
    void SetFontWeight(const FontWeight& value);
    void SetTextColor(const Color& value);
    void SetFontStyle(const OHOS::Ace::FontStyle& value);
    void SetContentOffset(OffsetF& value);
    float GetContentOffsetY();
    void SetContentSize(SizeF& value);
    void SetTextValue(std::u16string& value);
    void SetErrorTextValue(const std::u16string& value);
    void SetPlaceholderValue(std::u16string&& value);
    void SetTextRectY(const float value);
    float GetTextRectX();
    void SetTextObscured(bool value);
    void ChangeDragStatus();
    void SetTextRectX(const float value);
    float GetTextRectY();
    void SetTextAlign(const TextAlign value);
    bool NeedMeasureUpdate(PropertyChangeFlag& flag);
    void SetShowErrorState(bool value);
    void SetShowUnderlineState(bool value);
    void SetFontReady(bool value);
    void SetTextOverflow(const TextOverflow value);
    void SetTextDecoration(const TextDecoration& value, const Color& color, const TextDecorationStyle& style);
    void ContentChange();

private:
    void SetDefaultFontSize(const TextStyle& textStyle);
    void SetDefaultAdaptMinFontSize(const TextStyle& textStyle);
    void SetDefaultAdaptMaxFontSize(const TextStyle& textStyle);
    void SetDefaultFontWeight(const TextStyle& textStyle);
    void SetDefaultTextColor(const TextStyle& textStyle);
    void SetDefaultFontStyle(const TextStyle& textStyle);
    void SetDefaultTextOverflow(const TextStyle& textStyle);
    void SetDefaultTextDecoration(const TextStyle& textStyle);
    void SetDefaultPropertyValue();
    void GetFrameRectClip(RSRect& clipRect, std::vector<RSPoint>& clipRadius);
    void ModifyDecorationInTextStyle(TextStyle& textStyle);
    void UpdateTextDecorationMeasureFlag(PropertyChangeFlag& flag);

    WeakPtr<Pattern> pattern_;
    RefPtr<PropertyString> fontFamilyString_;

    std::optional<Dimension> fontSize_;
    RefPtr<AnimatablePropertyFloat> fontSizeFloat_;

    std::optional<Dimension> adaptMinFontSize_;
    RefPtr<AnimatablePropertyFloat> adaptMinFontSizeFloat_;

    std::optional<Dimension> adaptMaxFontSize_;
    RefPtr<AnimatablePropertyFloat> adaptMaxFontSizeFloat_;

    std::optional<FontWeight> fontWeight_;
    RefPtr<AnimatablePropertyFloat> fontWeightFloat_;

    std::optional<Color> textColor_;
    RefPtr<AnimatablePropertyColor> animatableTextColor_;

    float oldColorAlpha_ { 0.0f };
    std::optional<TextDecoration> textDecoration_;
    std::optional<TextDecorationStyle> textDecorationStyle_;
    std::optional<Color> textDecorationColor_;
    RefPtr<AnimatablePropertyFloat> textDecorationColorAlpha_;
    bool textDecorationAnimatable_ { false };

    RefPtr<PropertyFloat> textRectX_;
    RefPtr<PropertyFloat> textRectY_;
    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<PropertyU16String> textValue_;
    RefPtr<PropertyU16String> errorTextValue_;
    RefPtr<PropertyU16String> placeholderValue_;
    RefPtr<PropertyBool> textObscured_;
    RefPtr<PropertyBool> dragStatus_;
    RefPtr<PropertyInt> textAlign_;
    RefPtr<PropertyBool> showErrorState_;
    RefPtr<PropertyBool> showUnderline_;
    RefPtr<PropertyBool> contentChange_;
    RefPtr<PropertyInt> fontStyle_;
    RefPtr<PropertyBool> fontReady_;
    RefPtr<PropertyInt> textOverflow_;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldContentModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_CONTENT_MODIFIER_H
