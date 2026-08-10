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

#include "core/components_ng/pattern/common_text/counter_decorator.h"

#include <string_view>

#include "core/components_ng/pattern/common_text/counter_host.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "frameworks/base/utils/multi_thread.h"
#include "frameworks/base/utils/utils.h"

#include "core/components_ng/pattern/text_field/text_input_response_area.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t DEFAULT_MODE = -1;
constexpr int32_t SHOW_COUNTER_PERCENT = 100;

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
    FREE_NODE_CHECK(decoratedNode, BuildDecorator);
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode_ = textNode;
    CHECK_NULL_VOID(textNode);
    textNode->MountToParent(decoratedNode);
}

void TextComponentDecorator::BuildDecoratorMultiThread()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    decoratedNode->PostAfterAttachMainTreeTask([weakThis = WeakClaim(this)]() {
        auto decorator = weakThis.Upgrade();
        CHECK_NULL_VOID(decorator);
        auto decoratedNode = decorator->decoratedNode_.Upgrade();
        CHECK_NULL_VOID(decoratedNode);
        auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        ACE_UINODE_TRACE(textNode);
        decorator->textNode_ = textNode;
        CHECK_NULL_VOID(textNode);
        textNode->MountToParent(decoratedNode);
    });
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
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);
    auto context = decoratedNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextFieldTheme>(decoratedNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    // Update TextInput's bottom margin, Counter is inside of TextArea, no need to update its bottom margin
    if (!host->IsTextAreaOnCounter() && host->IsShowCounterEnabled()) {
        auto currentMargin = host->GetMarginProperty();

        auto counterHeight = MeasureTextNodeHeight();
        auto curFontScale = host->GetFontScaleFromEnv();
        auto standardHeight = theme->GetStandardCounterTextMargin().ConvertToPx();
        auto otherHeight = theme->GetCounterTextTopMargin().ConvertToPx() +
            theme->GetCounterTextBottomMargin().ConvertToPx() + counterHeight;
        auto marginHeight = (NearEqual(curFontScale, 1.0f)) ? standardHeight : otherHeight;
        Dimension newBottomMargin(marginHeight, DimensionUnit::PX);

        if (!currentMargin) {
            MarginProperty margin;
            margin.bottom = CalcLength(newBottomMargin);
            host->UpdateMargin(margin);
        } else {
            auto currentBottomMargin = currentMargin->bottom->GetDimension();
            UpdateBottomMargin(currentMargin, currentBottomMargin);
            if (LessNotEqual(currentBottomMargin.ConvertToPx(), newBottomMargin.ConvertToPx())) {
                currentMargin->bottom = CalcLength(newBottomMargin);
            }
            host->UpdateMargin(*currentMargin);
        }
    }
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetAccessibilityLevel("yes");
}

void CounterDecorator::UpdateBottomMargin(std::optional<MarginProperty>& marginProp, Dimension& bottom)
{
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);
    if (!host->HasMarginByUser()) {
        return;
    }
    auto userMargin = host->GetMarginByUserValue();
    if (!userMargin.bottom.has_value() || userMargin.bottom->GetDimension().Unit() != DimensionUnit::LPX ||
        LessNotEqual(userMargin.bottom->GetDimension().ConvertToPx(), bottom.ConvertToPx())) {
        return;
    }
    marginProp->bottom = userMargin.bottom;
    bottom = userMargin.bottom->GetDimension();
}

float CounterDecorator::MeasureTextNodeHeight()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(decoratedNode, 0.0);
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, 0.0);
    auto host = GetCounterHost();
    CHECK_NULL_RETURN(host, 0.0);
    auto counterGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_RETURN(counterGeometryNode, 0.0);

    // For efficiency: keep content same, make full use of rs cache.
    auto textLength = host->GetTextLength();
    auto maxLength = host->GetRealMaxLength();
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
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);
    auto context = decoratedNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextFieldTheme>(decoratedNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    auto counterNodeLayoutProperty = DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    CHECK_NULL_VOID(counterNodeLayoutProperty);
    auto renderContext = textNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    std::string counterText;
    if (isVisible) {
        counterText = GetCounterFormatString(textLength, maxLength);
        accessibilityProperty->SetAccessibilityText(GetAccessibilityText(textLength, maxLength));
    } else {
        accessibilityProperty->SetAccessibilityText("");
    }
    TextStyle countTextStyle = (host->GetShowCounterStyleValue() && host->HasFocus())?
                                theme->GetOverCountTextStyle() :
                                theme->GetCountTextStyle();
    ProcessCounterColor(decoratedNode, countTextStyle);
    counterNodeLayoutProperty->UpdateContent(counterText);
    if (host->HasMaxFontScale()) {
        counterNodeLayoutProperty->UpdateMaxFontScale(host->GetMaxFontScale());
    }
    if (host->HasMinFontScale()) {
        counterNodeLayoutProperty->UpdateMinFontScale(host->GetMinFontScale());
    }
    counterNodeLayoutProperty->UpdateFontSize(countTextStyle.GetFontSize());
    counterNodeLayoutProperty->UpdateTextColor(countTextStyle.GetTextColor());
    counterNodeLayoutProperty->UpdateFontWeight(countTextStyle.GetFontWeight());
    counterNodeLayoutProperty->UpdateTextAlign(GetCounterNodeAlignment());
    counterNodeLayoutProperty->UpdateMaxLines(theme->GetCounterTextMaxline());
    renderContext->UpdateForegroundColor(countTextStyle.GetTextColor());
}

void CounterDecorator::ProcessCounterColor(RefPtr<FrameNode>& decoratedNode, TextStyle& countTextStyle)
{
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);
    if (host->GetShowCounterStyleValue() && host->HasFocus()) {
        if (host->HasCounterTextOverflowColor()) {
            countTextStyle.SetTextColor(host->GetCounterTextOverflowColor());
        }
    } else {
        if (host->HasCounterTextColor()) {
            countTextStyle.SetTextColor(host->GetCounterTextColor());
        }
    }
}

std::string CounterDecorator::GetAccessibilityText(uint32_t textLength, uint32_t maxLength)
{
    std::string result = "";
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, result);
    auto pipelineContext = textNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, result);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, result);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, result);

    std::string textLengthStr = std::to_string(textLength);
    std::string maxLengthStr = std::to_string(maxLength);
    std::string toFindStr = "%d";

    auto firstStr = themeConstants->GetPluralStringByName("sys.plurals.textfield_counter_content_part_one", textLength);
    if (firstStr.empty()) {
        return result;
    }
    size_t posFirst = firstStr.find(toFindStr);
    if (posFirst != std::string::npos) {
        firstStr.replace(posFirst, toFindStr.length(), textLengthStr);
    }

    auto secondStr = themeConstants->GetPluralStringByName("sys.plurals.textfield_counter_content_part_two", maxLength);
    if (secondStr.empty()) {
        return result;
    }
    size_t posSecond = secondStr.find(toFindStr);
    if (posSecond != std::string::npos) {
        secondStr.replace(posSecond, toFindStr.length(), maxLengthStr);
    }
    result = firstStr + " " + secondStr;
    return result;
}

TextAlign CounterDecorator::GetCounterNodeAlignment()
{
    auto host = GetCounterHost();
    CHECK_NULL_RETURN(host, TextAlign::END);

    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    TextDirection layoutDirection = host->GetNonAutoLayoutDirection();
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
    auto host = GetCounterHost();
    CHECK_NULL_RETURN(host, 0.0f);

    auto isInlineStyle = host->IsNormalInlineState();
    auto isShowPassword = host->IsShowPasswordIcon();
    if (host->GetShowCounterValue() && host->HasMaxLength() &&
        !isInlineStyle && !isShowPassword) {
        auto counterNodeLayoutWrapper = decoratedNode->GetOrCreateChildByIndex(decoratedNode->GetChildIndex(textNode));
        if (counterNodeLayoutWrapper) {
            auto textLength =
                static_cast<uint32_t>(showPlaceHolder ? 0 : textContent.length());
            auto maxLength = host->GetRealMaxLength();
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
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);

    auto counterType = host->GetCounterType();
    double thresholdPercent = static_cast<double>(counterType) / static_cast<double>(SHOW_COUNTER_PERCENT);
    auto limitSize = static_cast<uint32_t>(static_cast<double>(maxLength) * thresholdPercent);
    if (counterType == DEFAULT_MODE || (textLength >= limitSize && counterType != DEFAULT_MODE)) {
        UpdateCounterContentAndStyle(textLength, maxLength, true);
    } else {
        UpdateCounterContentAndStyle(textLength, maxLength, false);
    }
    // TextInput's counter is outside of it,
    // hence need to check whether counter's width is longer than TextInput's constraint
    if (!host->IsTextAreaOnCounter() && contentConstraint.selfIdealSize.Width().has_value()) {
        textNode->Measure(LayoutConstraintF());
        if (GetContentWidth() > contentConstraint.selfIdealSize.Width().value()) {
            return;
        }
    }
    textNode->Measure(contentConstraint);
}

void CounterDecorator::UpdateCounterContent()
{
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_VOID(textNode);
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);

    auto textLength = host->GetTextLength();
    auto maxLength = host->GetRealMaxLength();
    auto counterType = host->GetCounterType();
    double thresholdPercent = static_cast<double>(counterType) / static_cast<double>(SHOW_COUNTER_PERCENT);
    auto limitSize = static_cast<uint32_t>(static_cast<double>(maxLength) * thresholdPercent);
    if (counterType == DEFAULT_MODE || (textLength >= limitSize && counterType != DEFAULT_MODE)) {
        UpdateCounterContentAndStyle(textLength, maxLength, true);
    } else {
        UpdateCounterContentAndStyle(textLength, maxLength, false);
    }
    textNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CounterDecorator::LayoutDecorator()
{
    auto decoratedNode = decoratedNode_.Upgrade();
    CHECK_NULL_VOID(decoratedNode);
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);

    bool isInlineStyle = host->IsNormalInlineState();
    bool isShowPassword = host->IsShowPasswordIcon();
    if (!isShowPassword && !isInlineStyle) {
        // ShowCounter is inside of TextArea, while outside of TextInput
        if (!host->IsTextAreaOnCounter()) {
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
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);
    auto context = decoratedNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextFieldTheme>(decoratedNode->GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    RefPtr<GeometryNode> textGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(textGeometryNode);
    auto decoratedGeometryNode = decoratedNode->GetGeometryNode();
    CHECK_NULL_VOID(decoratedGeometryNode);

    bool isRTL = host->GetNonAutoLayoutDirection() == TextDirection::RTL;
    RectF frameRect = decoratedGeometryNode->GetFrameRect();
    RectF contentRect = decoratedGeometryNode->GetContentRect();
    float countX = contentRect.GetX();
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
    if (host->IsUnderlineAndButtonMode() &&
        decoratedNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        countX = isRTL ? countX - host->GetPaddingLeft() :
                         countX + host->GetPaddingRight();
    }
    updateCountXWithArea(host->GetAllResponseArea());
    auto curFontScale = host->GetFontScaleFromEnv();
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
    auto host = GetCounterHost();
    CHECK_NULL_VOID(host);
    auto textFieldGeometryNode = decoratedNode->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    const std::unique_ptr<GeometryProperty> &content = textFieldGeometryNode->GetContent();
    CHECK_NULL_VOID(content);
    auto counterGeometryNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(counterGeometryNode);

    RectF frameRect = textFieldGeometryNode->GetFrameRect();
    float countX = content->GetRect().GetX();
    counterGeometryNode->SetFrameOffset(OffsetF(countX,
        frameRect.Height() - host->GetPaddingBottom() - counterGeometryNode->GetFrameRect().Height()));
    textNode->Layout();
}

float CounterDecorator::GetBoundHeight() const
{
    auto hostNode = decoratedNode_.Upgrade();
    CHECK_NULL_RETURN(hostNode, 0.0);
    auto context = hostNode->GetContext();
    CHECK_NULL_RETURN(context, 0.0);
    auto theme = context->GetTheme<TextFieldTheme>(hostNode->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, 0.0);
    return theme->GetCounterTextTopMargin().ConvertToPx() +
        theme->GetCounterTextBottomMargin().ConvertToPx() + GetDecoratorHeight();
}

bool CounterDecorator::HasContent() const
{
    auto textNode = textNode_.Upgrade();
    CHECK_NULL_RETURN(textNode, false);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textNode->GetLayoutProperty());
    CHECK_NULL_RETURN(textLayoutProperty, false);
    return textLayoutProperty->GetContent().has_value() && !textLayoutProperty->GetContent().value().empty();
}

RefPtr<ICounterHost> CounterDecorator::GetCounterHost() const
{
    return counterHost_.Upgrade();
}

std::string CounterDecorator::GetCounterFormatString(uint32_t textLength, uint32_t maxLength) const
{
    return std::to_string(textLength) + "/" + std::to_string(maxLength);
}

}
