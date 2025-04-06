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

#include "core/components_ng/pattern/text_field/text_component_decorator.h"

#include "core/components_ng/pattern/text/text_layout_property.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t DEFAULT_MODE = -1;
constexpr int32_t SHOW_COUNTER_PERCENT = 100;
const std::string INSPECTOR_PREFIX = "__SearchField__";
const std::string ERRORNODE_PREFIX = "ErrorNodeField__";

} // namespace

TextComponentDecorator::TextComponentDecorator(const RefPtr<FrameNode>& decoratedNode)
    : decoratedNode_(decoratedNode), textNode_(nullptr)
{
    BuildDecorator();
}

TextComponentDecorator::~TextComponentDecorator()
{
    CleanDecorator();
}

void TextComponentDecorator::BuildDecorator()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode_ = textNode;
    CHECK_NULL_VOID(textNode);
    textNode->MountToParent(decoratedNode);
}

void TextComponentDecorator::CleanDecorator()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    decoratedNode->RemoveChild(textNode);
    decoratedNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

// call after measure
float TextComponentDecorator::GetDecoratorHeight() const
{
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    auto geometryNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0);
    return geometryNode->GetFrameRect().Height();
}

float TextComponentDecorator::GetContentWidth() const
{
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    auto counterTextPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(counterTextPattern, 0.0f);
    
    auto counterWidth = 0.0f;
    auto counterParagraphs = counterTextPattern->GetParagraphs();
    for (auto &&info : counterParagraphs) {
        if (info.paragraph) {
            float width = info.paragraph->GetLongestLine();
            counterWidth = std::max(counterWidth, width);
        }
    }
    return counterWidth;
}

void CounterDecorator::UpdateTextFieldMargin()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto pipeline = decoratedNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);
    // Update TextInput's bottom margin, Counter is inside of TextArea, no need to update its bottom margin
    if (!textFieldPattern->IsTextArea() && textFieldPattern->IsShowCount()) {
        const auto& currentMargin = textFieldLayoutProperty->GetMarginProperty();

        auto counterHeight = MeasureTextNodeHeight();
        auto curFontScale = pipeline->GetFontScale();
        auto standardHeight = theme->GetStandardCounterTextMargin().ConvertToPx();
        auto otherHeight = theme->GetCounterTextTopMargin().ConvertToPx() +
            theme->GetCounterTextBottomMargin().ConvertToPx() + counterHeight;
        auto marginHeight = (NearEqual(curFontScale, 1.0f)) ? standardHeight : otherHeight;
        Dimension newBottomMargin(marginHeight, DimensionUnit::PX);

        if (!currentMargin) {
            MarginProperty margin;
            margin.bottom = CalcLength(newBottomMargin);
            textFieldLayoutProperty->UpdateMargin(margin);
        } else {
            auto currentBottomMargin = currentMargin->bottom->GetDimension();
            if (LessNotEqual(currentBottomMargin.ConvertToPx(), newBottomMargin.ConvertToPx())) {
                currentMargin->bottom = CalcLength(newBottomMargin);
            }
            textFieldLayoutProperty->UpdateMargin(*currentMargin);
        }
    }
}

float CounterDecorator::MeasureTextNodeHeight()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0);
    auto textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, 0.0);
    auto contentController = textFieldPattern->GetTextContentController();
    CHECK_NULL_RETURN(contentController, 0.0);
    auto counterGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(counterGeometryNode, 0.0);

    // For efficiency: keep content same, make full use of rs cache.
    auto textContent = contentController->GetTextValue();
    auto textLength = static_cast<uint32_t>(textContent.length());
    auto maxLength = static_cast<uint32_t>(textFieldLayoutProperty->GetMaxLengthValue(Infinity<uint32_t>()));
    UpdateCounterContentAndStyle(textLength, maxLength);
    // Both the non-backend rendering process and the backend rendering process will be called.
	// note using this statement have any impact on the back-end rendering process.
    ScopedLayout scope(decoratedNode->GetContext());
    textNode->Measure(LayoutConstraintF());
    return counterGeometryNode->GetFrameRect().Height();
}

void CounterDecorator::UpdateCounterContentAndStyle(uint32_t textLength, uint32_t maxLength, bool isVisible)
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);
    auto counterNodeLayoutProperty = DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    CHECK_NULL_VOID(counterNodeLayoutProperty);
    auto context = textNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    std::string counterText;
    if (isVisible) {
        counterText = std::to_string(textLength) + "/" + std::to_string(maxLength);
    }
    TextStyle countTextStyle = (textFieldPattern->GetShowCounterStyleValue() && textFieldPattern->HasFocus()) ?
                                theme->GetOverCountTextStyle() :
                                theme->GetCountTextStyle();
    counterNodeLayoutProperty->UpdateContent(counterText);
    
    if (textFieldLayoutProperty->HasMaxFontScale()) {
        auto maxFontScale = textFieldLayoutProperty->GetMaxFontScale().value();
        counterNodeLayoutProperty->UpdateMaxFontScale(maxFontScale);
    }
    if (textFieldLayoutProperty->HasMinFontScale()) {
        auto minFontScale = textFieldLayoutProperty->GetMinFontScale().value();
        counterNodeLayoutProperty->UpdateMinFontScale(minFontScale);
    }
    counterNodeLayoutProperty->UpdateFontSize(countTextStyle.GetFontSize());
    counterNodeLayoutProperty->UpdateTextColor(countTextStyle.GetTextColor());
    counterNodeLayoutProperty->UpdateFontWeight(countTextStyle.GetFontWeight());
    counterNodeLayoutProperty->UpdateTextAlign(GetCounterNodeAlignment());
    counterNodeLayoutProperty->UpdateMaxLines(theme->GetCounterTextMaxline());
    context->UpdateForegroundColor(countTextStyle.GetTextColor());
}

TextAlign CounterDecorator::GetCounterNodeAlignment()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, TextAlign::END);
    RefPtr<LayoutProperty> property = decoratedNode->GetLayoutProperty();
    CHECK_NULL_RETURN(property, TextAlign::END);

    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    TextDirection layoutDirection = property->GetLayoutDirection();
    if ((layoutDirection == TextDirection::RTL && !isRTL) ||
        (layoutDirection == TextDirection::LTR && isRTL)) {
        return TextAlign::START;
    }
    return TextAlign::END;
}

float CounterDecorator::MeasureDecorator(float contentWidth, const std::u16string& textContent, bool showPlaceHolder)
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    auto textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, 0.0f);
    auto textFieldLayoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);

    auto isInlineStyle = textFieldPattern->IsNormalInlineState();
    auto isShowPassword = textFieldPattern->IsShowPasswordIcon();
    if (textFieldLayoutProperty->GetShowCounterValue(false) && textFieldLayoutProperty->HasMaxLength() &&
        !isInlineStyle && !isShowPassword) {
        auto counterNodeLayoutWrapper = decoratedNode->GetOrCreateChildByIndex(decoratedNode->GetChildIndex(textNode));
        if (counterNodeLayoutWrapper) {
            auto textLength =
                static_cast<uint32_t>(showPlaceHolder ? 0 : textContent.length());
            auto maxLength = static_cast<uint32_t>(textFieldLayoutProperty->GetMaxLength().value());
            LayoutConstraintF textContentConstraint;
            textContentConstraint.UpdateIllegalSelfIdealSizeWithCheck(OptionalSizeF(contentWidth, std::nullopt));
            UpdateTextNodeAndMeasure(textLength, maxLength, textContentConstraint);
            return textNode->GetGeometryNode()->GetFrameSize().Height();
        }
    }
    return 0.0f;
}

void CounterDecorator::UpdateTextNodeAndMeasure(
    uint32_t textLength, uint32_t maxLength, const LayoutConstraintF& contentConstraint)
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto pipeline = decoratedNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto textFieldLayoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);

    auto counterType = textFieldLayoutProperty->GetSetCounterValue(DEFAULT_MODE);
    double thresholdPercent = static_cast<double>(counterType) / static_cast<double>(SHOW_COUNTER_PERCENT);
    auto limitSize = static_cast<uint32_t>(static_cast<double>(maxLength) * thresholdPercent);
    if (counterType == DEFAULT_MODE || (textLength >= limitSize && counterType != DEFAULT_MODE)) {
        UpdateCounterContentAndStyle(textLength, maxLength, true);
    } else {
        UpdateCounterContentAndStyle(textLength, maxLength, false);
    }
    // TextInput's counter is outside of it,
    // hence need to check whether counter's width is longer than TextInput's constraint
    if (!textFieldPattern->IsTextArea() && contentConstraint.selfIdealSize.Width().has_value()) {
        textNode->Measure(LayoutConstraintF());
        if (GetContentWidth() > contentConstraint.selfIdealSize.Width().value()) {
            return;
        }
    }
    textNode->Measure(contentConstraint);
}

void CounterDecorator::LayoutDecorator()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);

    bool isInlineStyle = textFieldPattern->IsNormalInlineState();
    bool isShowPassword = textFieldPattern->IsShowPasswordIcon();
    if (!isShowPassword && !isInlineStyle) {
        // ShowCounter is inside of TextArea, while outside of TextInput
        if (!textFieldPattern->IsTextArea()) {
            HandleNonTextArea();
        } else {
            HandleTextArea();
        }
    }
}

void CounterDecorator::HandleNonTextArea()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    RefPtr<LayoutProperty> decoratedNodeProperty = decoratedNode->GetLayoutProperty();
    CHECK_NULL_VOID(decoratedNodeProperty);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    RefPtr<GeometryNode> textGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);
    auto pipeline = decoratedNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_VOID(theme);
    
    bool isRTL = decoratedNodeProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    RectF frameRect = decoratedNode->GetGeometryNode()->GetFrameRect();
    RectF contentRect = decoratedNode->GetGeometryNode()->GetContentRect();
    float countX = contentRect.GetX();
    auto responseArea = textFieldPattern->GetResponseArea();
    auto cleanNodeResponseArea = textFieldPattern->GetCleanNodeResponseArea();
    auto updateCountXWithArea = [&countX, isRTL](const std::vector<RefPtr<TextInputResponseArea>>& areas) {
        for (auto area : areas) {
            if (!area) {
                continue;
            }
            if (isRTL) {
                countX -= area->GetAreaRect().Width();
            } else {
                countX += area->GetAreaRect().Width();
            }
        }
    };
    updateCountXWithArea({responseArea, cleanNodeResponseArea});
    auto curFontScale = pipeline->GetFontScale();
    auto countY = (NearEqual(curFontScale, 1.0f)) ? (frameRect.Height() + textGeometryNode->GetFrameRect().Height()) :
        (frameRect.Bottom() - frameRect.Top() + theme->GetCounterTextMarginOffset().ConvertToPx());
    textGeometryNode->SetFrameOffset(OffsetF(countX, countY));
    textNode->Layout();
}

void CounterDecorator::HandleTextArea()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto textFieldGeometryNode = decoratedNode->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    const std::unique_ptr<GeometryProperty> &content = textFieldGeometryNode->GetContent();
    CHECK_NULL_VOID(content);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto counterGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(counterGeometryNode);

    RectF frameRect = textFieldGeometryNode->GetFrameRect();
    float countX = content->GetRect().GetX();
    counterGeometryNode->SetFrameOffset(OffsetF(countX,
        frameRect.Height() - textFieldPattern->GetPaddingBottom() - counterGeometryNode->GetFrameRect().Height()));
    textNode->Layout();
}

float CounterDecorator::GetBoundHeight() const
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0);
    RefPtr<TextFieldPattern> textFieldPattern = decoratedNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, 0.0);
    auto theme = textFieldPattern->GetTheme();
    CHECK_NULL_RETURN(theme, 0.0);
    return theme->GetCounterTextTopMargin().ConvertToPx() + theme->GetCounterTextBottomMargin().ConvertToPx() +
        GetDecoratorHeight();
}

bool CounterDecorator::HasContent() const
{
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, false);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, false);
    return textLayoutProperty->GetContent().has_value() && !textLayoutProperty->GetContent().value().empty();
}

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
// Only measure will be called, so counter’s style need to be refreshed every time it is measured.
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
    textNode->UpdateInspectorId(INSPECTOR_PREFIX + ERRORNODE_PREFIX + parentID);
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
    auto textFieldLayoutProperty = decoratedNode->GetLayoutProperty();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, 0.0);
    RectF textFieldFrameRect = decoratedNode->GetGeometryNode()->GetFrameRect();
    auto errorValue = textFieldPattern->GetErrorTextString();
    if (textFieldPattern->IsShowError() && !textFieldPattern->IsDisabled() && !errorValue.empty()) {
        float padding = 0.0f;
        if (textFieldLayoutProperty && textFieldLayoutProperty->GetPaddingProperty()) {
            const auto& paddingProperty = textFieldLayoutProperty->GetPaddingProperty();
            padding = paddingProperty->left.value_or(CalcLength(0.0)).GetDimension().ConvertToPx() +
                paddingProperty->right.value_or(CalcLength(0.0)).GetDimension().ConvertToPx();
        }
        float layoutWidth = textFieldFrameRect.Width() - padding;
        auto border = textFieldPattern->GetBorderWidthProperty();
        float borderWidth = textFieldPattern->GetBorderLeft(border) + textFieldPattern->GetBorderRight(border);
        borderWidth = std::max(borderWidth, 0.0f);
        layoutWidth -= borderWidth; // subtract border width
        if (textFieldPattern->IsShowCount()) {
            auto counterDecorator = textFieldPattern->GetCounterDecorator();
            if (counterDecorator) {
                layoutWidth -= counterDecorator->GetContentWidth(); // subtract counter length
            }
        }
        LayoutConstraintF invisibleConstraint;
        invisibleConstraint.UpdateMaxSizeWithCheck({0.0f, 0.0f});
        if (LessOrEqual(layoutWidth, 0.0f)) {
            textNode->Measure(invisibleConstraint);
            return 0.0; // no enough space
        }
        LayoutConstraintF textContentConstraint;
        textContentConstraint.UpdateMaxSizeWithCheck({layoutWidth, Infinity<float>()});
        auto textNodeLayoutWrapper = decoratedNode->GetOrCreateChildByIndex(decoratedNode->GetChildIndex(textNode));
        if (textNodeLayoutWrapper) {
            textNode->Measure(textContentConstraint);
            if (GreatNotEqual(GetContentWidth(), layoutWidth)) {
                textNode->Measure(invisibleConstraint);
                return 0.0; // no enough space
            }
        }
    }
    return textNode->GetGeometryNode()->GetFrameSize().Height();
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
    if (theme->GetErrorTextCenter()) {
        offSetX = (textFieldGeometryNode->GetFrameRect().Width() - textFrameWidth) / 2;
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
