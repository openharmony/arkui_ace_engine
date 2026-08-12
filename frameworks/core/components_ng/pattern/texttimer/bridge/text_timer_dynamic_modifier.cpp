/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "frameworks/core/components_ng/pattern/texttimer/bridge/text_timer_dynamic_modifier.h"
#include "core/common/container.h"

#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"
#include "core/components_ng/pattern/texttimer/text_timer_event_hub.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
TextTimerModel* GetTextTimerModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("texttimer");
    static TextTimerModel* instance = loader ? reinterpret_cast<TextTimerModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_FONT_SIZE = Dimension(16.0, DimensionUnit::FP);
const std::vector<std::string> DEFAULT_FONT_FAMILY = { "HarmonyOS Sans" };
const std::string DEFAULT_FORMAT = "HH:mm:ss.SS";
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

namespace TextTimerModifier {
void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontColor(frameNode, Color(color));
}

void SetFontColorRes(ArkUINodeHandle node, ArkUI_Uint32 color, void* colorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        if (colorRawPtr) {
            auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
            auto colorResObj = AceType::Claim(color);
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::TEXTCOLOR, colorResObj);
        } else {
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::TEXTCOLOR, nullptr);
        }
    }
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    TextTimerModelNG::SetFontColor(frameNode, theme->GetTextStyle().GetTextColor());
    if (SystemProperties::ConfigChangePerform()) {
        TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::TEXTCOLOR, nullptr);
        TextTimerModelNG::SetTextColorByUser(frameNode, false);
    }
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontSize(frameNode, Dimension(value, static_cast<DimensionUnit>(unit)));
    TextTimerModelNG::SetFontSizeByUser(frameNode, true);
}

void SetFontSizeRes(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* fontSizeRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontSize(frameNode, Dimension(value, static_cast<DimensionUnit>(unit)));
    TextTimerModelNG::SetFontSizeByUser(frameNode, true);
    if (SystemProperties::ConfigChangePerform()) {
        if (fontSizeRawPtr) {
            auto* fontSize = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
            auto fontSizeResObj = AceType::Claim(fontSize);
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTSIZE, fontSizeResObj);
        } else {
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTSIZE, nullptr);
        }
    }
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontSize(frameNode, DEFAULT_FONT_SIZE);
    if (SystemProperties::ConfigChangePerform()) {
        TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTSIZE, nullptr);
        TextTimerModelNG::SetFontSizeByUser(frameNode, false);
    }
}

void SetFontStyle(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}

void ResetFontStyle(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontStyle(frameNode, OHOS::Ace::FontStyle::NORMAL);
}

void SetFontWeight(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    TextTimerModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
    TextTimerModelNG::SetFontWeightByUser(frameNode, true);
}

void SetFontWeightRes(ArkUINodeHandle node, ArkUI_CharPtr fontWeight, void* fontWeightRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    TextTimerModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
    TextTimerModelNG::SetFontWeightByUser(frameNode, true);
    if (SystemProperties::ConfigChangePerform()) {
        if (fontWeightRawPtr) {
            auto* fontWeight = reinterpret_cast<ResourceObject*>(fontWeightRawPtr);
            auto fontWeightResObj = AceType::Claim(fontWeight);
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTWEIGHT, fontWeightResObj);
        } else {
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTWEIGHT, nullptr);
        }
    }
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
    if (SystemProperties::ConfigChangePerform()) {
        TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTWEIGHT, nullptr);
        TextTimerModelNG::SetFontWeightByUser(frameNode, false);
    }
}

void SetFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextTimerModelNG::SetFontFamily(frameNode, fontFamilyResult);
    TextTimerModelNG::SetFontFamilyByUser(frameNode, true);
}

void SetFontFamilyRes(ArkUINodeHandle node, ArkUI_CharPtr fontFamily, void* fontFamilyRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    TextTimerModelNG::SetFontFamily(frameNode, fontFamilyResult);
    TextTimerModelNG::SetFontFamilyByUser(frameNode, true);
    if (SystemProperties::ConfigChangePerform()) {
        if (fontFamilyRawPtr) {
            auto* fontFamily = reinterpret_cast<ResourceObject*>(fontFamilyRawPtr);
            auto fontFamilyResObj = AceType::Claim(fontFamily);
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTFAMILY, fontFamilyResObj);
        } else {
            TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTFAMILY, nullptr);
        }
    }
}

void ResetFontFamily(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontFamily(frameNode, DEFAULT_FONT_FAMILY);
    if (SystemProperties::ConfigChangePerform()) {
        TextTimerModelNG::CreateWithResourceObj(frameNode, JsTextTimerResourceType::FONTFAMILY, nullptr);
        TextTimerModelNG::SetFontFamilyByUser(frameNode, false);
    }
}

void SetFormat(ArkUINodeHandle node, ArkUI_CharPtr format)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string formatStr = format;
    std::smatch result;
    std::regex pattern("(([YyMdD]+))");
    if (std::regex_search(formatStr, result, pattern)) {
        if (!result.empty()) {
            formatStr = DEFAULT_FORMAT;
        }
    }

    std::string target = "HmsS:.";
    for (auto ch : formatStr) {
        if (target.find(ch) == std::string::npos) {
            formatStr = DEFAULT_FORMAT;
        }
    }

    auto pos = formatStr.find("hh");
    if (pos != std::string::npos) {
        formatStr.replace(pos, sizeof("hh") - 1, "HH");
    }
    TextTimerModelNG::SetFormat(frameNode, formatStr);
}

void ResetFormat(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFormat(frameNode, DEFAULT_FORMAT);
}

void SetTextShadow(ArkUINodeHandle node, struct ArkUITextShadowStruct* shadows, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(shadows);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = shadows + i;
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        shadowList.at(i) = shadow;
    }
    TextTimerModelNG::SetTextShadow(frameNode, shadowList);
}

void ParseShadowRadiusUpdate(const RefPtr<ResourceObject>& radiusResObj, Shadow& shadow)
{
    if (!radiusResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        double radius = 0.0;
        ResourceParseUtils::ParseResDouble(resObj, radius);
        shadow.SetBlurRadius(radius);
    };
    shadow.AddResource("shadow.radius", radiusResObj, std::move(updateFunc));
}

void ParseShadowColorUpdate(const RefPtr<ResourceObject>& colorResObj, Shadow& shadow)
{
    if (!colorResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        Color color;
        ResourceParseUtils::ParseResColor(resObj, color);
        shadow.SetColor(color);
    };
    shadow.AddResource("shadow.colorValue", colorResObj, std::move(updateFunc));
}

void ParseShadowOffsetXUpdate(const RefPtr<ResourceObject>& offsetXResObj, Shadow& shadow)
{
    if (!offsetXResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        CalcDimension xValue;
        ResourceParseUtils::ParseResResource(resObj, xValue);
        shadow.SetOffsetX(xValue.Value());
    };
    shadow.AddResource("shadow.offsetX", offsetXResObj, std::move(updateFunc));
}

void ParseShadowOffsetYUpdate(const RefPtr<ResourceObject>& offsetYResObj, Shadow& shadow)
{
    if (!offsetYResObj) {
        return;
    }
    auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, Shadow& shadow) {
        CalcDimension yValue;
        ResourceParseUtils::ParseResResource(resObj, yValue);
        shadow.SetOffsetY(yValue.Value());
    };
    shadow.AddResource("shadow.offsetY", offsetYResObj, std::move(updateFunc));
}

void SetTextShadowRes(
    ArkUINodeHandle node, ArkUITextShadowStruct* shadows, ArkUITextShadowResStruct* shadowsRes, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(shadows);
    CHECK_NULL_VOID(shadowsRes);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = &shadows[i];
        ArkUITextShadowResStruct* shadowResStruct = &shadowsRes[i];
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        if (SystemProperties::ConfigChangePerform()) {
            auto* radius = shadowResStruct->radiusResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->radiusResObj) : nullptr;
            if (radius) {
                ParseShadowRadiusUpdate(AceType::Claim(radius), shadow);
            }
            auto* color = shadowResStruct->colorResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->colorResObj) : nullptr;
                if (color) {
                ParseShadowColorUpdate(AceType::Claim(color), shadow);
            }
            auto* offsetX = shadowResStruct->offsetXResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->offsetXResObj) : nullptr;
            if (offsetX) {
                ParseShadowOffsetXUpdate(AceType::Claim(offsetX), shadow);
            }
            auto* offsetY = shadowResStruct->offsetYResObj ?
                reinterpret_cast<ResourceObject*>(shadowResStruct->offsetYResObj) : nullptr;
            if (offsetY) {
                ParseShadowOffsetYUpdate(AceType::Claim(offsetY), shadow);
            }
        }
        shadowList.at(i) = shadow;
    }
    TextTimerModelNG::SetTextShadow(frameNode, shadowList);
}
void ResetTextShadow(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    shadow.SetBlurRadius(0);
    TextTimerModelNG::SetTextShadow(frameNode, std::vector<Shadow> { shadow });
}

void SetIsCountDown(ArkUINodeHandle node, ArkUI_Bool isCountDown)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetIsCountDown(frameNode, isCountDown);
}

void SetInputCount(ArkUINodeHandle node, ArkUI_Float64 count)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetInputCount(frameNode, count);
}

void SetStartTime(ArkUINodeHandle node, ArkUI_Int32 startTime)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetStartTime(frameNode, startTime);
}

void SetTextTimerOptions(ArkUINodeHandle node, ArkUI_Bool isCountDown, ArkUI_Float64 count, ArkUI_Int32 startTime)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetIsCountDown(frameNode, isCountDown);
    if (isCountDown) {
        TextTimerModelNG::SetInputCount(frameNode, count);
    }
    TextTimerModelNG::SetStartTime(frameNode, startTime);
}

void SetTextTimerOnTimer(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onTimer = reinterpret_cast<ChangeEvent*>(callback);
        TextTimerModelNG::SetOnTimer(frameNode, std::move(*onTimer));
    } else {
        TextTimerModelNG::SetOnTimer(frameNode, nullptr);
    }
}

void ResetTextTimerOnTimer(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetOnTimer(frameNode, nullptr);
}

void CreateTextTimerModel()
{
    TextTimerModelNG::CreateTextTimerModel();
}

ArkUINodeHandle CreateTextTimerFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = TextTimerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetTextColorByUser(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetTextColorByUser(frameNode, isByUser);
}

void SetFontSizeByUser(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontSizeByUser(frameNode, isByUser);
}

void SetFontWeightByUser(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontWeightByUser(frameNode, isByUser);
}

void SetFontFamilyByUser(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    TextTimerModelNG::SetFontFamilyByUser(frameNode, isByUser);
}

void SetFontDefault(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto textTheme = frameNode->GetTheme<TextTheme>(true);
    CHECK_NULL_VOID(textTheme);
    TextTimerModelNG::SetFontSize(frameNode, textTheme->GetTextStyle().GetFontSize());
    TextTimerModelNG::SetFontColor(frameNode, textTheme->GetTextStyle().GetTextColor());
    TextTimerModelNG::SetTextColorByUser(frameNode, false);
    TextTimerModelNG::SetFontFamily(frameNode, textTheme->GetTextStyle().GetFontFamilies());
    TextTimerModelNG::SetFontWeight(frameNode, textTheme->GetTextStyle().GetFontWeight());
    TextTimerModelNG::SetFontStyle(frameNode, textTheme->GetTextStyle().GetFontStyle());
}

#ifndef CROSS_PLATFORM
void SetFormatImpl(ArkUINodeHandle node, ArkUI_CharPtr format)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string formatStr = format;
    GetTextTimerModelImpl()->SetFormat(formatStr);
}

void ResetFormatImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFormat(DEFAULT_FORMAT);
}

void SetIsCountDownImpl(ArkUINodeHandle node, ArkUI_Bool isCountDown)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetIsCountDown(isCountDown);
}

void ResetIsCountDownImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetIsCountDown(false);
}

void SetInputCountImpl(ArkUINodeHandle node, ArkUI_Float64 count)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetInputCount(count);
}

void ResetInputCountImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetInputCount(0);
}

void SetStartTimeImpl(ArkUINodeHandle node, ArkUI_Int32 startTime)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetStartTime(startTime);
}
void ResetStartTimeImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetStartTime(0);
}

void SetTextTimerOnTimerImpl(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onTimer = reinterpret_cast<ChangeEvent*>(callback);
        GetTextTimerModelImpl()->SetOnTimer(std::move(*onTimer));
    } else {
        GetTextTimerModelImpl()->SetOnTimer(nullptr);
    }
}

void ResetTextTimerOnTimerImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetOnTimer(nullptr);
}

void SetFontSizeImpl(ArkUINodeHandle node, float value, int32_t unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontSize(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void ResetFontSizeImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontSize(DEFAULT_FONT_SIZE);
}

void SetTextColorImpl(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetTextColor(Color(color));
}

void ResetTextColorImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = frameNode->GetTheme<TextTheme>(true);
    CHECK_NULL_VOID(theme);
    GetTextTimerModelImpl()->SetTextColor(theme->GetTextStyle().GetTextColor());
}

void SetTextColorByUserImpl(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetTextColorByUser(isByUser);
}

void ResetTextColorByUserImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetTextColorByUser(false);
}

void SetTextShadowImpl(ArkUINodeHandle node, ArkUITextShadowStruct* shadows, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(shadows);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Shadow> shadowList(length);
    for (uint32_t i = 0; i < length; i++) {
        Shadow shadow;
        ArkUITextShadowStruct* shadowStruct = shadows + i;
        shadow.SetBlurRadius(shadowStruct->radius);
        shadow.SetShadowType(static_cast<ShadowType>(shadowStruct->type));
        shadow.SetColor(Color(shadowStruct->color));
        shadow.SetOffsetX(shadowStruct->offsetX);
        shadow.SetOffsetY(shadowStruct->offsetY);
        shadow.SetIsFilled(static_cast<bool>(shadowStruct->fill));
        shadowList.at(i) = shadow;
    }
    GetTextTimerModelImpl()->SetTextShadow(shadowList);
}

void ResetTextShadowImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    shadow.SetOffsetX(0.0);
    shadow.SetOffsetY(0.0);
    shadow.SetBlurRadius(0);
    GetTextTimerModelImpl()->SetTextShadow(std::vector<Shadow> { shadow });
}

void SetFontWeightImpl(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    GetTextTimerModelImpl()->SetFontWeight(Framework::ConvertStrToFontWeight(fontWeightStr));
    GetTextTimerModelImpl()->SetFontWeightByUser(true);
}

void ResetFontWeightImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontWeight(DEFAULT_FONT_WEIGHT);
}

void SetFontFamilyImpl(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontFamilyStr = fontFamily;
    GetTextTimerModelImpl()->SetFontFamily({fontFamilyStr});
}

void ResetFontFamilyImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontFamily(DEFAULT_FONT_FAMILY);
}

void SetFontSizeByUserImpl(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontSizeByUser(isByUser);
}

void ResetFontSizeByUserImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontSizeByUser(false);
}

void SetFontWeightByUserImpl(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontWeightByUser(isByUser);
}

void ResetFontWeightByUserImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontWeightByUser(false);
}

void SetFontFamilyByUserImpl(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontFamilyByUser(isByUser);
}

void ResetFontFamilyByUserImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetFontFamilyByUser(false);
}

void SetFontStyleImpl(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetItalicFontStyle(static_cast<Ace::FontStyle>(value));
}

void ResetFontStyleImpl(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetItalicFontStyle(Ace::FontStyle::NORMAL);
}

void SetTextTimerOptionsImpl(ArkUINodeHandle node, ArkUI_Bool isCountDown, ArkUI_Float64 count,
    ArkUI_Int32 startTime)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetTextTimerModelImpl()->SetIsCountDown(isCountDown);
    if (isCountDown) {
        GetTextTimerModelImpl()->SetInputCount(count);
    }
    GetTextTimerModelImpl()->SetStartTime(startTime);
}

void SetFontDefaultImpl(ArkUINodeHandle node)
{
    auto *frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto textTheme = frameNode->GetTheme<TextTheme>(true);
    CHECK_NULL_VOID(textTheme);
    GetTextTimerModelImpl()->SetFontSize(textTheme->GetTextStyle().GetFontSize());
    GetTextTimerModelImpl()->SetTextColor(textTheme->GetTextStyle().GetTextColor());
    GetTextTimerModelImpl()->SetTextColorByUser(false);
    GetTextTimerModelImpl()->SetFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    GetTextTimerModelImpl()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    GetTextTimerModelImpl()->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
}
#endif

} // namespace TextTimerModifier

const ArkUITextTimerModifier* GetTextTimerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUITextTimerModifier modifier = {
            .setFontColor = TextTimerModifier::SetTextColorImpl,
            .setFontColorRes = nullptr,
            .resetFontColor = TextTimerModifier::ResetTextColorImpl,
            .setFontSize = TextTimerModifier::SetFontSizeImpl,
            .setFontSizeRes = nullptr,
            .resetFontSize = TextTimerModifier::ResetFontSizeImpl,
            .setFontStyle = TextTimerModifier::SetFontStyleImpl,
            .resetFontStyle = TextTimerModifier::ResetFontStyleImpl,
            .setFontWeight = TextTimerModifier::SetFontWeightImpl,
            .setFontWeightRes = nullptr,
            .resetFontWeight = TextTimerModifier::ResetFontWeightImpl,
            .setFontFamily = TextTimerModifier::SetFontFamilyImpl,
            .setFontFamilyRes = nullptr,
            .resetFontFamily = TextTimerModifier::ResetFontFamilyImpl,
            .setFormat = TextTimerModifier::SetFormatImpl,
            .resetFormat = TextTimerModifier::ResetFormatImpl,
            .setTextShadow = TextTimerModifier::SetTextShadowImpl,
            .setTextShadowRes = nullptr,
            .resetTextShadow = TextTimerModifier::ResetTextShadowImpl,
            .setTextTimerOptions = TextTimerModifier::SetTextTimerOptionsImpl,
            .setTextTimerOnTimer = TextTimerModifier::SetTextTimerOnTimerImpl,
            .resetTextTimerOnTimer = TextTimerModifier::ResetTextTimerOnTimerImpl,
            .createTextTimerModel = nullptr,
            .createTextTimerFrameNode = nullptr,
            .setTextColorByUser = TextTimerModifier::SetTextColorByUserImpl,
            .setFontSizeByUser = TextTimerModifier::SetFontSizeByUserImpl,
            .setFontWeightByUser = TextTimerModifier::SetFontWeightByUserImpl,
            .setFontFamilyByUser = TextTimerModifier::SetFontFamilyByUserImpl,
            .setIsCountDown = TextTimerModifier::SetIsCountDownImpl,
            .setInputCount = TextTimerModifier::SetInputCountImpl,
            .setStartTime = TextTimerModifier::SetStartTimeImpl,
            .setFontDefault = TextTimerModifier::SetFontDefaultImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextTimerModifier modifier = {
        .setFontColor = TextTimerModifier::SetFontColor,
        .setFontColorRes = TextTimerModifier::SetFontColorRes,
        .resetFontColor = TextTimerModifier::ResetFontColor,
        .setFontSize = TextTimerModifier::SetFontSize,
        .setFontSizeRes = TextTimerModifier::SetFontSizeRes,
        .resetFontSize = TextTimerModifier::ResetFontSize,
        .setFontStyle = TextTimerModifier::SetFontStyle,
        .resetFontStyle = TextTimerModifier::ResetFontStyle,
        .setFontWeight = TextTimerModifier::SetFontWeight,
        .setFontWeightRes = TextTimerModifier::SetFontWeightRes,
        .resetFontWeight = TextTimerModifier::ResetFontWeight,
        .setFontFamily = TextTimerModifier::SetFontFamily,
        .setFontFamilyRes = TextTimerModifier::SetFontFamilyRes,
        .resetFontFamily = TextTimerModifier::ResetFontFamily,
        .setFormat = TextTimerModifier::SetFormat,
        .resetFormat = TextTimerModifier::ResetFormat,
        .setTextShadow = TextTimerModifier::SetTextShadow,
        .setTextShadowRes = TextTimerModifier::SetTextShadowRes,
        .resetTextShadow = TextTimerModifier::ResetTextShadow,
        .setTextTimerOptions = TextTimerModifier::SetTextTimerOptions,
        .setTextTimerOnTimer = TextTimerModifier::SetTextTimerOnTimer,
        .resetTextTimerOnTimer = TextTimerModifier::ResetTextTimerOnTimer,
        .createTextTimerModel = TextTimerModifier::CreateTextTimerModel,
        .createTextTimerFrameNode = TextTimerModifier::CreateTextTimerFrameNode,
        .setTextColorByUser = TextTimerModifier::SetTextColorByUser,
        .setFontSizeByUser = TextTimerModifier::SetFontSizeByUser,
        .setFontWeightByUser = TextTimerModifier::SetFontWeightByUser,
        .setFontFamilyByUser = TextTimerModifier::SetFontFamilyByUser,
        .setIsCountDown = TextTimerModifier::SetIsCountDown,
        .setInputCount = TextTimerModifier::SetInputCount,
        .setStartTime = TextTimerModifier::SetStartTime,
        .setFontDefault = TextTimerModifier::SetFontDefault,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextTimerModifier* GetCJUITextTimerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextTimerModifier modifier = {
        .setFontColor = TextTimerModifier::SetFontColor,
        .setFontColorRes = TextTimerModifier::SetFontColorRes,
        .resetFontColor = TextTimerModifier::ResetFontColor,
        .setFontSize = TextTimerModifier::SetFontSize,
        .setFontSizeRes = TextTimerModifier::SetFontSizeRes,
        .resetFontSize = TextTimerModifier::ResetFontSize,
        .setFontStyle = TextTimerModifier::SetFontStyle,
        .resetFontStyle = TextTimerModifier::ResetFontStyle,
        .setFontWeight = TextTimerModifier::SetFontWeight,
        .setFontWeightRes = TextTimerModifier::SetFontWeightRes,
        .resetFontWeight = TextTimerModifier::ResetFontWeight,
        .setFontFamily = TextTimerModifier::SetFontFamily,
        .setFontFamilyRes = TextTimerModifier::SetFontFamilyRes,
        .resetFontFamily = TextTimerModifier::ResetFontFamily,
        .setFormat = TextTimerModifier::SetFormat,
        .resetFormat = TextTimerModifier::ResetFormat,
        .setTextShadow = TextTimerModifier::SetTextShadow,
        .setTextShadowRes = TextTimerModifier::SetTextShadowRes,
        .resetTextShadow = TextTimerModifier::ResetTextShadow,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace OHOS::Ace::NG
