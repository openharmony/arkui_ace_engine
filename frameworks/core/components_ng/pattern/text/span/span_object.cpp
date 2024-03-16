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
#include "core/components_ng/pattern/text/span/span_objects.h"

#include <optional>
#include <utility>

#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace {
// SpanBase
int32_t SpanBase::GetStartIndex() const
{
    return start_;
}

int32_t SpanBase::GetEndIndex() const
{
    return end_;
}
void SpanBase::UpdateStartIndex(int32_t startIndex)
{
    start_ = startIndex;
}

void SpanBase::UpdateEndIndex(int32_t endIndex)
{
    end_ = endIndex;
}

// FontSpan
void FontSpan::ApplyToSpanItem(const RefPtr<NG::SpanItem>& spanItem) const
{
    if (font_.fontColor.has_value()) {
        spanItem->fontStyle->UpdateTextColor(font_.fontColor.value());
    }

    if (font_.fontFamiliesNG.has_value()) {
        spanItem->fontStyle->UpdateFontFamily(font_.fontFamiliesNG.value());
    }

    if (font_.fontSize.has_value()) {
        spanItem->fontStyle->UpdateFontSize(font_.fontSize.value());
    }

    if (font_.fontStyle.has_value()) {
        spanItem->fontStyle->UpdateItalicFontStyle(font_.fontStyle.value());
    }

    if (font_.fontWeight.has_value()) {
        spanItem->fontStyle->UpdateFontWeight(font_.fontWeight.value());
    }
}

bool FontSpan::IsAttributesEqual(const RefPtr<SpanBase>& other) const
{
    auto fontSpan = DynamicCast<FontSpan>(other);
    if (!fontSpan) {
        return false;
    }
    auto font = fontSpan->GetFont();
    return font_.IsEqual(font);
}
} // namespace OHOS::Ace