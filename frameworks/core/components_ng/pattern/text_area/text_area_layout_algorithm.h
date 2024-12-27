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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_AREA_TEXT_AREA_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_AREA_TEXT_AREA_PATTERN_H

#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
namespace OHOS::Ace::NG {
class TextAreaLayoutAlgorithm : public TextFieldLayoutAlgorithm {
    DECLARE_ACE_TYPE(TextAreaLayoutAlgorithm, TextFieldLayoutAlgorithm);

public:
    TextAreaLayoutAlgorithm() = default;
    ~TextAreaLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void ConstraintHeight(LayoutWrapper* layoutWrapper, OptionalSizeF& frameSize,
        float contentHeight);
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
protected:
    bool CreateParagraphEx(const TextStyle& textStyle, const std::u16string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_AREA_TEXT_AREA_PATTERN_H
