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

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"

namespace OHOS::Ace::NG {

class TextFieldContentModifier;
class ACE_EXPORT TextFieldLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TextFieldLayoutAlgorithm, LayoutAlgorithm);

public:
    TextFieldLayoutAlgorithm() = default;

    ~TextFieldLayoutAlgorithm() override = default;

    void OnReset() override
    {
        paragraph_->Reset();
    }

    const RefPtr<Paragraph>& GetParagraph() const;

    const RefPtr<Paragraph>& GetErrorParagraph() const;

    const RectF& GetTextRect() const
    {
        return textRect_;
    }

    const OffsetF& GetParentGlobalOffset() const
    {
        return parentGlobalOffset_;
    }

    float GetUnitWidth() const
    {
        return unitWidth_;
    }

    static TextDirection GetTextDirection(const std::string& content);

    static void UpdateTextStyle(const RefPtr<FrameNode>& frameNode,
        const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme,
        TextStyle& textStyle, bool isDisabled);
    static void UpdatePlaceholderTextStyle(const RefPtr<FrameNode>& frameNode,
        const RefPtr<TextFieldLayoutProperty>& layoutProperty, const RefPtr<TextFieldTheme>& theme,
        TextStyle& textStyle, bool isDisabled);

    virtual float CounterNodeMeasure(float contentWidth, LayoutWrapper* layoutWrapper)
    {
        return 0.0f;
    }

protected:
    static void FontRegisterCallback(const RefPtr<FrameNode>& frameNode, const std::vector<std::string>& fontFamilies);
    void CreateParagraph(const TextStyle& textStyle, std::string content, bool needObscureText,
        int32_t nakedCharPosition, bool disableTextAlign = false);
    void CreateParagraph(const TextStyle& textStyle, const std::vector<std::string>& contents,
        const std::string& content, bool needObscureText, bool disableTextAlign = false);
    void CreateErrorParagraph(const std::string& content, const RefPtr<TextFieldTheme>& theme);
    bool CreateParagraphAndLayout(
        const TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint);
    bool AdaptMinTextSize(TextStyle& textStyle, const std::string& content, const LayoutConstraintF& contentConstraint,
        const RefPtr<PipelineContext>& pipeline);
    bool DidExceedMaxLines(const LayoutConstraintF& contentConstraint);
    void SetPropertyToModifier(const TextStyle& textStyle, RefPtr<TextFieldContentModifier> modifier);

    float GetTextFieldDefaultHeight();

    void ConstructTextStyles(
        const RefPtr<FrameNode>& frameNode, TextStyle& textStyle, std::string& textContent, bool& showPlaceHolder);
    void ErrorTextMeasureContent(const std::string& content, const RefPtr<TextFieldTheme>& theme);

    int32_t ConvertTouchOffsetToCaretPosition(const Offset& localOffset);
    void UpdateUnitLayout(LayoutWrapper* layoutWrapper);
    ParagraphStyle GetParagraphStyle(const TextStyle& textStyle, const std::string& content) const;
    float ConstraintWithMinWidth(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, float removeValue = 0.0f);
    SizeF GetConstraintSize(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    std::optional<SizeF> InlineMeasureContent(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    SizeF PlaceHolderMeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, float imageWidth = 0.0f);
    SizeF TextInputMeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, float imageWidth);
    SizeF TextAreaMeasureContent(const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper);
    RefPtr<Paragraph> paragraph_;
    RefPtr<Paragraph> errorParagraph_;
    RectF textRect_;
    OffsetF parentGlobalOffset_;
    std::string textContent_;
    bool showPlaceHolder_ = false;
    float preferredHeight_ = 0.0f;

    float unitWidth_ = 0.0f;
    bool autoWidth_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_ALGORITHM_H
