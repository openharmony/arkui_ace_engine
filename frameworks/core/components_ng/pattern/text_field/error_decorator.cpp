/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text_field/error_decorator.h"

#include <string_view>

#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "frameworks/base/utils/utils.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t CONSTANT_TWO_FOR_CENTER = 2;
constexpr std::string_view INSPECTOR_PREFIX = "__SearchField__";
constexpr std::string_view ERRORNODE_PREFIX = "ErrorNodeField__";

} // namespace

void ErrorDecorator::UpdateTextFieldMargin()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldPaintProperty = textFieldPattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);

    UpdateErrorStyle();
    MarginProperty errorMargin;
    ScopedLayout scope(decoratedNode->GetContext());
    textNode->Measure(LayoutConstraintF());
    auto errorTextMargin = theme->GetErrorTextTopMargin().ConvertToPx() +
        theme->GetErrorTextBottomMargin().ConvertToPx() + GetDecoratorHeight();
    if (textFieldPattern->GetMarginBottom() < errorTextMargin) {
        errorMargin.bottom = CalcLength(errorTextMargin);
    }
    if (textFieldPaintProperty->HasMarginByUser()) {
        auto userMargin = textFieldPaintProperty->GetMarginByUserValue();
        userMargin.bottom = textFieldPattern->GetMarginBottom() < errorTextMargin ?
            errorMargin.bottom : userMargin.bottom;
        textFieldLayoutProperty->UpdateMargin(userMargin);
    } else {
        textFieldLayoutProperty->UpdateMargin(errorMargin);
    }
}

void ErrorDecorator::UpdateLayoutProperty()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);

    TextStyle errorTextStyle = theme->GetErrorTextStyle();
    auto errorText = textFieldLayoutProperty->GetErrorTextValue(u"");
    StringUtils::TransformStrCase(errorText, static_cast<int32_t>(errorTextStyle.GetTextCase()));
    textLayoutProperty->UpdateContent(errorText);
    textLayoutProperty->UpdateTextColor(errorTextStyle.GetTextColor());
    textLayoutProperty->UpdateFontWeight(errorTextStyle.GetFontWeight());
    textLayoutProperty->UpdateFontSize(errorTextStyle.GetFontSize());
    auto maxFontScale = theme->GetErrorTextMaxFontScale();
    if (textFieldLayoutProperty->HasMaxFontScale()) {
        maxFontScale = std::min(theme->GetErrorTextMaxFontScale(),
            textFieldLayoutProperty->GetMaxFontScale().value());
    }
    textLayoutProperty->UpdateMaxFontScale(maxFontScale);
    if (textFieldLayoutProperty->HasMinFontScale()) {
        auto minFontScale = textFieldLayoutProperty->GetMinFontScale().value();
        textLayoutProperty->UpdateMinFontScale(minFontScale);
    }
    textLayoutProperty->UpdateTextAlign(TextAlign::START);
    textLayoutProperty->UpdateMaxLines(theme->GetErrorTextMaxLine());
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateIsAnimationNeeded(false);
    auto isRTL = textFieldLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRTL) {
        textLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    } else {
        textLayoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    }
}

// The style of showError is basically fixed, just refresh it every time onModifyDone.
// Unlike showError, showCounter is not marked as dirty after insertValue and will not call onModifyDone,
// Only measure will be called, so counter's style need to be refreshed every time it is measured.
void ErrorDecorator::UpdateErrorStyle()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);
    TextStyle errorTextStyle = theme->GetErrorTextStyle();
    UpdateLayoutProperty();

    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel("yes");
    auto parentID = decoratedNode->GetInspectorIdValue("");
    textNode->UpdateInspectorId(std::string(INSPECTOR_PREFIX) + std::string(ERRORNODE_PREFIX) + parentID);
    textNode->SetIsCalculateInnerClip(true);

    textNode->MarkModifyDone();
    textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    auto context = textNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateForegroundColor(errorTextStyle.GetTextColor());
}

// Split the code from TextFieldContentModifier::ProcessErrorParagraph:
// Put the part that calculates width and layout into MeasureDecorator. Set the frame offset to LayoutDecorator.
// Should be called after the measure of counter and textInput, as it relies on them to calculate the width.
float ErrorDecorator::MeasureDecorator(float contentWidth, const std::u16string& textContent, bool showPlaceHolder)
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, 0.0);
    auto errorValue = textFieldPattern->GetErrorTextString();
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_RETURN(theme, 0.0);
    if (textFieldPattern->IsShowError() && !textFieldPattern->IsDisabled() && !errorValue.empty()) {
        float layoutWidth = CalculateErrorLayoutWidth();
        LayoutConstraintF invisibleConstraint;
        invisibleConstraint.UpdateMaxSizeWithCheck({0.0f, 0.0f});
        if (LessOrEqual(layoutWidth, 0.0f)) {
            textNode->Measure(invisibleConstraint);
            return 0.0f;
        }
        LayoutConstraintF textContentConstraint;
        textContentConstraint.UpdateMaxSizeWithCheck({layoutWidth, Infinity<float>()});
        auto textNodeLayoutWrapper = decoratedNode->GetOrCreateChildByIndex(decoratedNode->GetChildIndex(textNode));
        if (textNodeLayoutWrapper) {
            textNode->Measure(textContentConstraint);
            if (GreatNotEqual(GetContentWidth(), layoutWidth)) {
                textNode->Measure(invisibleConstraint);
                return 0.0f;
            }
        }
    }
    return textNode->GetGeometryNode()->GetFrameSize().Height();
}

float ErrorDecorator::CalculateErrorLayoutWidth()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0f);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, 0.0f);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    RectF textFieldFrameRect = decoratedNode->GetGeometryNode()->GetFrameRect();
    float padding = 0.0f;
    if (textFieldLayoutProperty->GetPaddingProperty()) {
        const auto& paddingProperty = textFieldLayoutProperty->GetPaddingProperty();
        padding = paddingProperty->left.value_or(CalcLength(0.0)).GetDimension().ConvertToPx() +
            paddingProperty->right.value_or(CalcLength(0.0)).GetDimension().ConvertToPx();
    }
    float layoutWidth = textFieldFrameRect.Width() - padding;
    auto border = textFieldPattern->GetBorderWidthProperty();
    float borderWidth = textFieldPattern->GetBorderLeft(border) + textFieldPattern->GetBorderRight(border);
    layoutWidth -= std::max(borderWidth, 0.0f);
    if (textFieldPattern->IsShowCount()) {
        auto counterDecorator = textFieldPattern->GetCounterDecorator();
        if (counterDecorator) {
            layoutWidth -= counterDecorator->GetContentWidth();
            if (theme->GetErrorTextAlign() == TextAlign::CENTER) {
                layoutWidth -= counterDecorator->GetContentWidth();
            }
        }
    }
    return layoutWidth;
}

void ErrorDecorator::BeforeLayout()
{
    MeasureDecorator(Infinity<float>(), u"", false);
}

void ErrorDecorator::LayoutDecorator()
{
    BeforeLayout();
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto textGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldGeometryNode = decoratedNode->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);

    float errorMargin = 0.0f;
    if (textFieldLayoutProperty->GetShowUnderlineValue(false) && textFieldPattern->IsShowError()) {
        errorMargin = theme->GetErrorTextUnderlineMargin().ConvertToPx();
    } else if (textFieldPattern->NeedShowPasswordIcon() && textFieldPattern->IsShowError()) {
        errorMargin = theme->GetErrorTextCapsuleMargin().ConvertToPx();
    } else if (textFieldPattern->IsShowError()) {
        errorMargin = theme->GetErrorTextCapsuleMargin().ConvertToPx();
    } else {
        errorMargin = 0;
    }

    RectF textFrameRect = decoratedNode->GetGeometryNode()->GetFrameRect();
    auto offset = textFieldGeometryNode->GetContentOffset();
    auto isRTL = textFieldLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto offSetX = offset.GetX();
    auto textFrameWidth = textGeometryNode->GetFrameRect().Width();
    if (isRTL) {
        auto textFieldContentRect = textFieldGeometryNode->GetContentRect();
        offSetX += textFieldContentRect.Width() - textFrameWidth;
    }
    if (theme->GetErrorTextAlign() == TextAlign::CENTER) {
        offSetX = (textFieldGeometryNode->GetFrameRect().Width() - textFrameWidth) / CONSTANT_TWO_FOR_CENTER;
    }
    textGeometryNode->SetFrameOffset(OffsetF(offSetX, textFrameRect.Bottom() - textFrameRect.Top() + errorMargin));
    textNode->Layout();
}

float ErrorDecorator::GetBoundHeight() const
{
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    auto geometryNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, 0.0);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_RETURN(theme, 0.0);
    return theme->GetErrorTextTopMargin().ConvertToPx() + theme->GetErrorTextBottomMargin().ConvertToPx() +
        geometryNode->GetFrameRect().Height();
}

}
