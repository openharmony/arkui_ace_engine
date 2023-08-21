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

#include "core/components_ng/pattern/text/text_content_modifier.h"

namespace OHOS::Ace::NG {
TextContentModifier::TextContentModifier(const std::optional<TextStyle>& textStyle) {}

void TextContentModifier::SetDefaultAnimatablePropertyValue(const TextStyle& textStyle) {}

void TextContentModifier::SetDefaultFontSize(const TextStyle& textStyle) {}

void TextContentModifier::SetDefaultFontWeight(const TextStyle& textStyle) {}

void TextContentModifier::SetDefaultTextColor(const TextStyle& textStyle) {}

void TextContentModifier::SetDefaultTextShadow(const TextStyle& textStyle) {}
void TextContentModifier::SetDefaultTextDecoration(const TextStyle& textStyle) {}
void TextContentModifier::SetDefaultBaselineOffset(const TextStyle& textStyle) {}

void TextContentModifier::onDraw(DrawingContext& drawingContext) {}

void TextContentModifier::ModifyFontSizeInTextStyle(TextStyle& textStyle) {}

void TextContentModifier::ModifyFontWeightInTextStyle(TextStyle& textStyle) {}

void TextContentModifier::ModifyTextColorInTextStyle(TextStyle& textStyle) {}

void TextContentModifier::ModifyTextShadowsInTextStyle(TextStyle& textStyle) {}

void TextContentModifier::ModifyDecorationInTextStyle(TextStyle& textStyle) {}

void TextContentModifier::ModifyBaselineOffsetInTextStyle(TextStyle& textStyle) {}

void TextContentModifier::ModifyTextStyle(TextStyle& textStyle) {}

void TextContentModifier::UpdateFontSizeMeasureFlag(PropertyChangeFlag& flag) {}

void TextContentModifier::UpdateFontWeightMeasureFlag(PropertyChangeFlag& flag) {}

void TextContentModifier::UpdateTextColorMeasureFlag(PropertyChangeFlag& flag) {}

void TextContentModifier::UpdateTextShadowMeasureFlag(PropertyChangeFlag& flag) {}

void TextContentModifier::UpdateTextDecorationMeasureFlag(PropertyChangeFlag& flag) {}

void TextContentModifier::UpdateBaselineOffsetMeasureFlag(PropertyChangeFlag& flag) {}

bool TextContentModifier::NeedMeasureUpdate(PropertyChangeFlag& flag)
{
    return true;
}

void TextContentModifier::SetFontSize(const Dimension& value) {}

void TextContentModifier::SetFontWeight(const FontWeight& value) {}

void TextContentModifier::SetTextColor(const Color& value) {}

void TextContentModifier::SetTextShadow(const std::vector<Shadow>& value) {}

void TextContentModifier::SetTextDecoration(const TextDecoration& type) {}

void TextContentModifier::SetTextDecorationColor(const Color& color) {}

void TextContentModifier::SetBaselineOffset(const Dimension& value) {}

void TextContentModifier::StartTextRace() {}

void TextContentModifier::StopTextRace() {}

float TextContentModifier::GetTextRacePercent()
{
    return 0;
}

void TextContentModifier::ContentChange() {}
} // namespace OHOS::Ace::NG