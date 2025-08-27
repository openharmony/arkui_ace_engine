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

#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"

#include "bridge/common/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"

namespace OHOS::Ace::NG {
RefPtr<TextTimerController> TextTimerModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXTTIMER_ETS_TAG, nodeId);
    auto textTimerNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTTIMER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextTimerPattern>(); });

    auto textTimerPattern = textTimerNode->GetPattern<TextTimerPattern>();
    if (textTimerNode->GetChildren().empty()) {
        auto textId = textTimerPattern->GetTextId();
        auto textNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MarkModifyDone();
        textNode->MountToParent(textTimerNode);
    }
    stack->Push(textTimerNode);
    auto textTimerLayoutProperty = textTimerNode->GetLayoutProperty<TextTimerLayoutProperty>();
    if (textTimerLayoutProperty) {
        textTimerLayoutProperty->ResetTextColorSetByUser();
        textTimerLayoutProperty->ResetTextFontSizeSetByUser();
        textTimerLayoutProperty->ResetTextFontWeightSetByUser();
        textTimerLayoutProperty->ResetTextFontFamilySetByUser();
    }

    return textTimerPattern ? textTimerPattern->GetTextTimerController() : nullptr;
}

void TextTimerModelNG::SetFormat(const std::string& format)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, Format, format);
}

void TextTimerModelNG::SetIsCountDown(bool isCountDown)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, IsCountDown, isCountDown);
}

void TextTimerModelNG::SetInputCount(double count)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, InputCount, count);
}

void TextTimerModelNG::SetFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontSize, value);
}

void TextTimerModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColor, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColorSetByUser, true);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void TextTimerModelNG::SetTextColorByUser(bool isSetByUser)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColorSetByUser, isSetByUser);
}

void TextTimerModelNG::SetTextColorByUser(FrameNode* frameNode, bool isSetByUser)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColorSetByUser, isSetByUser, frameNode);
}

void TextTimerModelNG::SetTextShadow(const std::vector<Shadow>& value)
{
    std::string key = "textTimer.shadow";
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
    if (value.empty()) {
        return;
    }
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto&& updateFunc = [value, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        if (!frameNode) {
            return;
        }
        std::vector<Shadow> shadows = value;
        for (auto& shadow : shadows) {
            shadow.ReloadResources();
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextShadow, shadows, frameNode);
    };
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextShadow, value);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->AddResObj(key, resObj, std::move(updateFunc));
    }
}

void TextTimerModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, ItalicFontStyle, value);
}

void TextTimerModelNG::SetFontWeight(FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontWeight, value);
}

void TextTimerModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontFamily, value);
}

void TextTimerModelNG::SetOnTimer(std::function<void(int64_t, int64_t)> && onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextTimerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTimer(std::move(onChange));
}

void TextTimerModelNG::SetOnTimer(FrameNode* frameNode, std::function<void(int64_t, int64_t)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<TextTimerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTimer(std::move(onChange));
}

RefPtr<FrameNode> TextTimerModelNG::CreateFrameNode(int32_t nodeId)
{
    auto textTimerNode =
        FrameNode::CreateFrameNode(V2::TEXTTIMER_ETS_TAG, nodeId, AceType::MakeRefPtr<TextTimerPattern>());
    CHECK_NULL_RETURN(textTimerNode, nullptr);
    auto textTimerPattern = textTimerNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_RETURN(textTimerPattern, nullptr);
    if (textTimerNode->GetChildren().empty()) {
        auto textId = textTimerPattern->GetTextId();
        auto textNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textId, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_RETURN(textNode, nullptr);
        textNode->MarkModifyDone();
        textNode->MountToParent(textTimerNode);
    }
    return textTimerNode;
}

RefPtr<TextTimerController> TextTimerModelNG::InitTextController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPatternPtr<TextTimerPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTextTimerController();
}

void TextTimerModelNG::SetIsCountDown(FrameNode* frameNode, bool isCountDown)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, IsCountDown, isCountDown, frameNode);
}

void TextTimerModelNG::SetInputCount(FrameNode* frameNode, double count)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, InputCount, count, frameNode);
}

void TextTimerModelNG::SetFontColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColor, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextColorSetByUser, true, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void TextTimerModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontSize, value, frameNode);
}

void TextTimerModelNG::SetFontStyle(FrameNode* frameNode, Ace::FontStyle value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, ItalicFontStyle, value, frameNode);
}

void TextTimerModelNG::SetFontWeight(FrameNode* frameNode, FontWeight value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontWeight, value, frameNode);
}

void TextTimerModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, FontFamily, value, frameNode);
}

void TextTimerModelNG::SetFormat(FrameNode* frameNode, const std::string& format)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, Format, format, frameNode);
}

void TextTimerModelNG::SetTextShadow(FrameNode* frameNode, const std::vector<Shadow>& value)
{
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "textTimer.shadow";
    pattern->RemoveResObj(key);
    auto&& updateFunc = [value, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        if (!frameNode) {
            return;
        }
        std::vector<Shadow> shadows = value;
        for (auto& shadow : shadows) {
            shadow.ReloadResources();
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextShadow, shadows, frameNode);
    };
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextShadow, value, frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        pattern->AddResObj(key, resObj, std::move(updateFunc));
    }
}

void TextTimerModelNG::SetBuilderFunc(FrameNode* frameNode, TextTimerMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void TextTimerModelNG::SetJSTextTimerController(FrameNode* frameNode, const RefPtr<Referenced>& controller)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetJSTextTimerController(controller);
}

RefPtr<Referenced> TextTimerModelNG::GetJSTextTimerController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetJSTextTimerController();
}

void TextTimerModelNG::HandleTextColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "textTimer.textColor";
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            result = theme->GetTextStyle().GetTextColor();
        }
        pattern->UpdateTextColor(result, true);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void TextTimerModelNG::HandleFontWeight(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "textTimer.fontWeight";
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string fontWeightStr;
        ResourceParseUtils::ParseResString(resObj, fontWeightStr);
        pattern->UpdateFontWeight(ConvertStrToFontWeight(fontWeightStr), isFirstLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void TextTimerModelNG::HandleFontSize(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "textTimer.fontSize";
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CalcDimension fontSize;
        if (!ResourceParseUtils::ParseResDimensionFp(resObj, fontSize) || fontSize.IsNegative() ||
            fontSize.Unit() == DimensionUnit::PERCENT) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<TextTheme>();
            CHECK_NULL_VOID(theme);
            fontSize = theme->GetTextStyle().GetFontSize();
        }
        pattern->UpdateFontSize(fontSize, isFirstLoad);
    };

    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void TextTimerModelNG::HandleFontFamily(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    std::string key = "textTimer.fontFamily";
    auto pattern = frameNode->GetPattern<TextTimerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFirstLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::vector<std::string> fontFamilies;
        if (!ResourceParseUtils::ParseResFontFamilies(resObj, fontFamilies)) {
            return;
        }
        pattern->UpdateFontFamily(fontFamilies, isFirstLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void TextTimerModelNG::CreateWithResourceObj(
    JsTextTimerResourceType jsResourceType, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, jsResourceType, resObj);
}

void TextTimerModelNG::CreateWithResourceObj(
    FrameNode* frameNode, JsTextTimerResourceType jsResourceType, const RefPtr<ResourceObject>& resObj)
{
    switch (jsResourceType) {
        case JsTextTimerResourceType::TEXTCOLOR:
            HandleTextColor(frameNode, resObj);
            break;
        case JsTextTimerResourceType::FONTWEIGHT:
            HandleFontWeight(frameNode, resObj);
            break;
        case JsTextTimerResourceType::FONTSIZE:
            HandleFontSize(frameNode, resObj);
            break;
        case JsTextTimerResourceType::FONTFAMILY:
            HandleFontFamily(frameNode, resObj);
            break;
        default:
            return;
    }
}

void TextTimerModelNG::SetFontSizeByUser(bool isSetByUser)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextFontSizeSetByUser, isSetByUser);
    }
}

void TextTimerModelNG::SetFontWeightByUser(bool isSetByUser)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextFontWeightSetByUser, isSetByUser);
    }
}

void TextTimerModelNG::SetFontFamilyByUser(bool isSetByUser)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextFontFamilySetByUser, isSetByUser);
    }
}

void TextTimerModelNG::SetFontSizeByUser(FrameNode* frameNode, bool isSetByUser)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextFontSizeSetByUser, isSetByUser, frameNode);
    }
}

void TextTimerModelNG::SetFontWeightByUser(FrameNode* frameNode, bool isSetByUser)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextFontWeightSetByUser, isSetByUser, frameNode);
    }
}

void TextTimerModelNG::SetFontFamilyByUser(FrameNode* frameNode, bool isSetByUser)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextTimerLayoutProperty, TextFontFamilySetByUser, isSetByUser, frameNode);
    }
}
} // namespace OHOS::Ace::NG
