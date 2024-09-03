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

#include "core/components_ng/pattern/progress/progress_paint_property.h"

#include "core/components/progress/progress_theme.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
constexpr float PROGRSS_MAX_VALUE = 100.f;

void ProgressPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    PaintProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        ToJsonValueForCapsule(json, filter);
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);

    json->PutExtAttr("constructor", ProgressOptions().c_str(), filter);
    json->PutExtAttr("total", std::to_string(GetMaxValue().value_or(PROGRSS_MAX_VALUE)).c_str(), filter);
    json->PutExtAttr("value", std::to_string(GetValue().value_or(0.f)).c_str(), filter);
    json->PutExtAttr("isSensitive", std::to_string(GetIsSensitive().value_or(false)).c_str(), filter);
    json->PutExtAttr("scaleCount",
        std::to_string(GetScaleCount().value_or(progressTheme->GetScaleNumber())).c_str(), filter);
    json->PutExtAttr("scaleWidth",
        (GetScaleWidth().value_or(progressTheme->GetScaleWidth()).ToString()).c_str(), filter);
    Color defaultBackgroundColor = progressTheme->GetTrackBgColor();
    Color defaultColor = progressTheme->GetTrackSelectedColor();
    ProgressType progressType = GetProgressType().value_or(ProgressType::LINEAR);
    if (progressType == ProgressType::CAPSULE) {
        defaultColor = progressTheme->GetCapsuleSelectColor();
        defaultBackgroundColor = progressTheme->GetCapsuleBgColor();
    } else if (progressType == ProgressType::RING) {
        defaultBackgroundColor = progressTheme->GetRingProgressBgColor();
    }
    json->PutExtAttr("color", (GetColor().value_or(defaultColor)).ColorToString().c_str(), filter);
    json->PutExtAttr("backgroundColor",
        (GetBackgroundColor().value_or(defaultBackgroundColor)).ColorToString().c_str(), filter);
    json->PutExtAttr("capsuleBorderColor",
        (GetBorderColor().value_or(progressTheme->GetBorderColor())).ColorToString().c_str(), filter);
    ToJsonValueForCapsule(json, filter);
    json->PutExtAttr("progressGradientColor", ToJsonGradientColor().c_str(), filter);
}

std::string ProgressPaintProperty::ProgressOptions() const
{
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("value", std::to_string(GetValue().value_or(0.f)).c_str());
    jsonValue->Put("total", std::to_string(GetMaxValue().value_or(PROGRSS_MAX_VALUE)).c_str());
    jsonValue->Put("type",
        ProgressTypeUtils::ConvertProgressTypeToString(GetProgressType().value_or(ProgressType::LINEAR)).c_str());
    return jsonValue->ToString();
}

void ProgressPaintProperty::ToJsonValueForCapsule(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto progressTheme = pipeline->GetTheme<ProgressTheme>();
    CHECK_NULL_VOID(progressTheme);
    auto capsuleStyle = JsonUtil::Create(true);
    auto fontStyle = JsonUtil::Create(true);
    auto font = JsonUtil::Create(true);
    capsuleStyle->Put("borderWidth", (GetBorderWidth().value_or(progressTheme->GetBorderWidth())).ToString().c_str());
    capsuleStyle->Put(
        "borderColor", (GetBorderColor().value_or(progressTheme->GetBorderColor())).ColorToString().c_str());
    capsuleStyle->Put("fontColor", (GetTextColor().value_or(progressTheme->GetTextColor())).ColorToString().c_str());
    capsuleStyle->Put("content", (GetText().value_or("")).c_str());
    capsuleStyle->Put("enableScanEffect", (GetEnableScanEffect().value_or(false)) ? "true" : "false");
    capsuleStyle->Put("showDefaultPercentage", (GetEnableShowText().value_or(false)) ? "true" : "false");
    font->Put("size", (GetTextSize().value_or(progressTheme->GetTextSize())).ToString().c_str());
    font->Put("style", GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL
                           ? "FontStyle.Normal"
                           : "FontStyle.Italic");
    font->Put("weight", V2::ConvertWrapFontWeightToStirng(GetFontWeight().value_or(FontWeight::NORMAL)).c_str());
    std::vector<std::string> defaultFamily = { "Sans" };
    std::vector<std::string> fontFamilyVector = GetFontFamily().value_or(defaultFamily);
    if (fontFamilyVector.empty()) {
        fontFamilyVector = defaultFamily;
    }
    std::string fontFamily = fontFamilyVector.at(0);
    for (uint32_t i = 1; i < fontFamilyVector.size(); ++i) {
        fontFamily += ',' + fontFamilyVector.at(i);
    }
    font->Put("family", fontFamily.c_str());
    capsuleStyle->Put("font", font);
    json->PutExtAttr("capsuleStyle", capsuleStyle, filter);
}

std::string ProgressPaintProperty::ToJsonGradientColor() const
{
    Gradient colors;
    if (propGradientColor_.has_value()) {
        colors = propGradientColor_.value();
    } else {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, "");
        auto theme = pipelineContext->GetTheme<ProgressTheme>();
        auto endColor = theme->GetRingProgressEndSideColor();
        auto beginColor = theme->GetRingProgressBeginSideColor();
        GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(endColor));
        gradientColorEnd.SetDimension(Dimension(0.0f));
        colors.AddColor(gradientColorEnd);
        GradientColor gradientColorBegin;
        gradientColorBegin.SetLinearColor(LinearColor(beginColor));
        gradientColorBegin.SetDimension(Dimension(1.0f));
        colors.AddColor(gradientColorBegin);
    }

    auto jsonArray = JsonUtil::CreateArray(true);
    for (size_t index = 0; index < colors.GetColors().size(); ++index) {
        auto gradientColor = colors.GetColors()[index];
        auto gradientColorJson = JsonUtil::Create(true);
        gradientColorJson->Put("color", gradientColor.GetLinearColor().ToColor().ColorToString().c_str());
        gradientColorJson->Put("offset", std::to_string(gradientColor.GetDimension().Value()).c_str());
        jsonArray->Put(std::to_string(index).c_str(), gradientColorJson);
    }
    return jsonArray->ToString();
}
} // namespace OHOS::Ace::NG
