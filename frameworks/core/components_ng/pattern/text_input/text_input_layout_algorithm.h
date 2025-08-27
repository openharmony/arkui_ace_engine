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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_PATTERN_H

#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_input_response_area.h"

namespace OHOS::Ace::NG {
class TextFieldPattern;
class TextInputLayoutAlgorithm : public TextFieldLayoutAlgorithm {
    DECLARE_ACE_TYPE(TextInputLayoutAlgorithm, TextFieldLayoutAlgorithm);

public:
    TextInputLayoutAlgorithm() = default;
    ~TextInputLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    float GetDefaultHeightByType(LayoutWrapper* layoutWrapper);
protected:
    bool CreateParagraphEx(const TextStyle& textStyle, const std::u16string& content,
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;
    LayoutConstraintF BuildLayoutConstraintWithoutResponseArea(const LayoutConstraintF& contentConstraint,
        LayoutWrapper* layoutWrapper);

private:
    struct UpdateContentPositionParams {
        bool isRTL = false;
        OffsetF offsetBase = OffsetF(0.0f, 0.0f);
        SizeT<float> size = SizeT<float>(0.0f, 0.0f);
        SizeT<float> contentSize = SizeT<float>(0.0f, 0.0f);
        Alignment align = Alignment::CENTER;
        RefPtr<TextInputResponseArea> responseArea = nullptr;
        RefPtr<TextInputResponseArea> cleanResponseArea = nullptr;
    };

    struct UpdateTextRectParams {
        RefPtr<TextFieldLayoutProperty> layoutProperty = nullptr;
        RefPtr<TextFieldPattern> pattern = nullptr;
        SizeT<float> contentSize = SizeT<float>(0.0f, 0.0f);
        bool isRTL = false;
        RefPtr<TextInputResponseArea> responseArea = nullptr;
        RefPtr<TextInputResponseArea> cleanResponseArea = nullptr;
        OffsetF contentOffset = OffsetF(0.0f, 0.0f);
    };
    void UpdateContentPosition(const UpdateContentPositionParams& params,
        const std::unique_ptr<GeometryProperty>& content);
    void UpdateTextRect(const UpdateTextRectParams& params);
    bool IsFontSizeNonPositive(const TextStyle& textStyle) const;
    void MeasureAutoFillIcon(LayoutWrapper* layoutWrapper);
    void LayoutAutoFillIcon(LayoutWrapper* layoutWrapper);
    void MeasureCounterWithPolicy(LayoutWrapper* layoutWrapper, float nonContentWidth);

    SizeF autoFillIconSizeMeasure_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_TEXT_INPUT_PATTERN_H