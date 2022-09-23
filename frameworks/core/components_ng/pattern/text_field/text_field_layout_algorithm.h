/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_ALGORITHM_H

#include <string>
#include <utility>

#include "base/geometry/rect.h"
#include "base/memory/referenced.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextFieldLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TextFieldLayoutAlgorithm, LayoutAlgorithm);

public:
    TextFieldLayoutAlgorithm() = default;

    ~TextFieldLayoutAlgorithm() override = default;

    void OnReset() override
    {
        paragraph_.reset();
    }

    void Measure(LayoutWrapper* layoutWrapper) override;

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    const std::shared_ptr<RSParagraph>& GetParagraph();

    const RectF& GetTextRect() const
    {
        return textRect_;
    }

    const RectF& GetImageRect() const
    {
        return imageRect_;
    }

private:
    void UpdateTextStyle(const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme,
        TextStyle& textStyle);
    void UpdatePlaceholderTextStyle(const RefPtr<TextFieldLayoutProperty>& layoutProperty,
        const RefPtr<TextFieldTheme>& theme, TextStyle& textStyle);
    void CreateParagraph(const TextStyle& textStyle, std::string content);
    bool CreateParagraphAndLayout(
        const TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint);
    bool AdaptMinTextSize(TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint,
        const RefPtr<PipelineContext>& pipeline);
    bool DidExceedMaxLines(const LayoutConstraintF& contentConstraint);
    static TextDirection GetTextDirection(const std::string& content);

    float GetTextFieldDefaultHeight();

    float GetTextFieldDefaultImageHeight();

    std::shared_ptr<RSParagraph> paragraph_;

    RectF textRect_;
    RectF imageRect_;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_ALGORITHM_H
