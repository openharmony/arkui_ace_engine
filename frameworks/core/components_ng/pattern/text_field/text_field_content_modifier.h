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
    TextFieldContentModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~TextFieldContentModifier() override = default;

    void onDraw(DrawingContext& context) override;
    void ModifyTextStyle(TextStyle& textStyle);
    void SetDefaultAnimatablePropertyValue();

    void SetFontSize(const Dimension& value);
    void SetFontWeight(const FontWeight& value);
    void SetTextColor(const Color& value);
    void SetContentOffset(OffsetF& value);
    void SetContentSize(SizeF& value);
    void SetTextValue(std::string& value);
    void SetTextRectY(const float value);
    bool NeedMeasureUpdate(PropertyChangeFlag& flag);

private:
    RefPtr<OHOS::Ace::NG::PipelineContext> GetPipelineContext();
    void SetDefaultFontSize(const TextStyle& textStyle);
    void SetDefaultFontWeight(const TextStyle& textStyle);
    void SetDefaultTextColor(const TextStyle& textStyle);
    void SetDefaultPropertyValue();

private:
    WeakPtr<Pattern> pattern_;
    std::optional<Dimension> fontSize_;
    RefPtr<AnimatablePropertyFloat> fontSizeFloat_;

    std::optional<FontWeight> fontWeight_;
    RefPtr<AnimatablePropertyFloat> fontWeightFloat_;

    std::optional<Color> textColor_;
    RefPtr<AnimatablePropertyColor> animatableTextColor_;

    RefPtr<PropertyFloat> textRectY_;
    RefPtr<PropertyOffsetF> contentOffset_;
    RefPtr<PropertySizeF> contentSize_;
    RefPtr<PropertyString> textValue_;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldContentModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_CONTENT_MODIFIER_H
