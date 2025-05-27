/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_data_panel.h"

#include <vector>

#include "bridge/declarative_frontend/ark_theme/theme_apply/js_data_panel_theme.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/data_panel_model_impl.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/data_panel/data_panel_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/data_panel/data_panel_model.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<DataPanelModel> DataPanelModel::instance_ = nullptr;
std::mutex DataPanelModel::mutex_;

DataPanelModel* DataPanelModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::DataPanelModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::DataPanelModelNG());
            } else {
                instance_.reset(new Framework::DataPanelModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
constexpr uint32_t TYPE_CYCLE = 0;
}

constexpr size_t MAX_COUNT = 9;
uint32_t JSDataPanel::dataPanelType_ = 0;

void JSDataPanel::JSBind(BindingTarget globalObj)
{
    JSClass<JSDataPanel>::Declare("DataPanel");
    JSClass<JSDataPanel>::StaticMethod("create", &JSDataPanel::Create);
    JSClass<JSDataPanel>::StaticMethod("closeEffect", &JSDataPanel::CloseEffect);

    JSClass<JSDataPanel>::StaticMethod("valueColors", &JSDataPanel::ValueColors);
    JSClass<JSDataPanel>::StaticMethod("trackBackgroundColor", &JSDataPanel::TrackBackground);
    JSClass<JSDataPanel>::StaticMethod("strokeWidth", &JSDataPanel::StrokeWidth);
    JSClass<JSDataPanel>::StaticMethod("trackShadow", &JSDataPanel::ShadowOption);
    JSClass<JSDataPanel>::StaticMethod("borderRadius", &JSDataPanel::BorderRadius);

    JSClass<JSDataPanel>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSDataPanel>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSDataPanel>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSDataPanel>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSDataPanel>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSDataPanel>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSDataPanel>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSDataPanel>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSDataPanel>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSDataPanel>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSDataPanel::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    // max
    double max = jsObj->GetPropertyValue<double>("max", 100.0);
    // values
    JSRef<JSVal> jsValue = jsObj->GetProperty("values");
    if (!jsValue->IsArray()) {
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(jsValue);
    size_t length = jsArray->Length();
    std::vector<double> dateValues;
    double dataSum = 0.0;
    size_t count = std::min(length, MAX_COUNT);
    for (size_t i = 0; i < count; ++i) {
        JSRef<JSVal> item = jsArray->GetValueAt(i);
        if (!item->IsNumber()) {
            continue;
        }
        double value = item->ToNumber<double>();
        if (LessOrEqual(value, 0.0)) {
            value = 0.0;
        }
        // if the sum of values exceeds the maximum value, only fill in to the maximum value
        if (GreatOrEqual(dataSum + value, max) && GreatNotEqual(max, 0)) {
            dateValues.emplace_back(max - dataSum);
            break;
        }
        dataSum += value;
        dateValues.emplace_back(value);
    }
    if (LessOrEqual(max, 0.0)) {
        max = dataSum;
    }

    size_t dataPanelType = 0;
    int32_t type = jsObj->GetPropertyValue<int32_t>("type", static_cast<int32_t>(ChartType::RAINBOW));
    if (type == static_cast<int32_t>(ChartType::LINE)) {
        dataPanelType = 1;
    }
    dataPanelType_ = dataPanelType;
    DataPanelModel::GetInstance()->Create(dateValues, max, dataPanelType);
    JSDataPanelTheme::ApplyTheme();
}

void JSDataPanel::CloseEffect(const JSCallbackInfo& info)
{
    bool isCloseEffect = true;
    if (info[0]->IsBoolean()) {
        isCloseEffect = info[0]->ToBoolean();
    }
    DataPanelModel::GetInstance()->SetEffect(isCloseEffect);
}

void JSDataPanel::ValueColors(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    std::vector<OHOS::Ace::NG::Gradient> valueColors;
    if (!info[0]->IsArray() || info[0]->IsEmpty()) {
        ConvertThemeColor(valueColors);
        DataPanelModel::GetInstance()->SetValueColors(valueColors);
        return;
    }

    auto paramArray = JSRef<JSArray>::Cast(info[0]);
    size_t length = paramArray->Length();
    size_t count = std::min(length, MAX_COUNT);
    for (size_t i = 0; i < count; ++i) {
        auto item = paramArray->GetValueAt(i);
        OHOS::Ace::NG::Gradient gradient;
        if (!ConvertGradientColor(item, gradient)) {
            valueColors.clear();
            ConvertThemeColor(valueColors);
            break;
        }
        valueColors.emplace_back(gradient);
    }
    DataPanelModel::GetInstance()->SetValueColors(valueColors);
}

void JSDataPanel::TrackBackground(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color color;
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        bool state = ParseJsColor(info[0], color, resObj);
        if (resObj) {
            DataPanelModel::GetInstance()->CreateWithResourceObj(
                OHOS::Ace::DataPanelResourceType::TRACK_BACKGROUND_COLOR, resObj);
        } else if (state) {
            DataPanelModel::GetInstance()->SetTrackBackground(color);
        } else {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            color = theme->GetBackgroundColor();
            DataPanelModel::GetInstance()->SetTrackBackground(color);
        }
    } else {
        RefPtr<ResourceObject> resObj;
        if (!ParseJsColor(info[0], color)) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            color = theme->GetBackgroundColor();
        }
        DataPanelModel::GetInstance()->SetTrackBackground(color);
    }
}

void JSDataPanel::StrokeWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
    CalcDimension strokeWidthDimension;
    RefPtr<ResourceObject> resObj;
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ParseJsDimensionVp(info[0], strokeWidthDimension, resObj);
        if (resObj) {
            DataPanelModel::GetInstance()->CreateWithResourceObj(
                OHOS::Ace::DataPanelResourceType::STROKE_WIDTH, resObj);
        } else if (state) {
            DataPanelModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
        } else {
            strokeWidthDimension = theme->GetThickness();
            DataPanelModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
        }
    } else {
        if (!ParseJsDimensionVp(info[0], strokeWidthDimension)) {
            strokeWidthDimension = theme->GetThickness();
        }
    }

    // If the parameter value is string(''), parse result 0.
    // The value of 0 is allowed, but the value of string('') is not allowed, so use theme value.
    if (info[0]->IsString() && (info[0]->ToString().empty() || !StringUtils::StringToDimensionWithUnitNG(
        info[0]->ToString(), strokeWidthDimension))) {
        strokeWidthDimension = theme->GetThickness();
    }

    if (strokeWidthDimension.IsNegative() || strokeWidthDimension.Unit() == DimensionUnit::PERCENT) {
        strokeWidthDimension = theme->GetThickness();
    }
    DataPanelModel::GetInstance()->SetStrokeWidth(strokeWidthDimension);
}

void JSDataPanel::ShadowOption(const JSCallbackInfo& info)
{
    OHOS::Ace::NG::DataPanelShadow shadow;
    if (info[0]->IsNull()) {
        shadow.isShadowVisible = false;
        DataPanelModel::GetInstance()->SetShadowOption(shadow);
        return;
    }
    RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
    double radius = theme->GetTrackShadowRadius().ConvertToVp();
    double offsetX = theme->GetTrackShadowOffsetX().ConvertToVp();
    double offsetY = theme->GetTrackShadowOffsetY().ConvertToVp();
    std::vector<OHOS::Ace::NG::Gradient> shadowColors;
    ConvertThemeColor(shadowColors);
    if (info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> jsRadius = paramObject->GetProperty("radius");
        JSRef<JSVal> jsOffsetX = paramObject->GetProperty("offsetX");
        JSRef<JSVal> jsOffsetY = paramObject->GetProperty("offsetY");
        RefPtr<ResourceObject> resR;
        RefPtr<ResourceObject> resX;
        RefPtr<ResourceObject> resY;
        HandleShadowRadius(jsRadius, radius, resR, shadow);
        HandleShadowOffsetX(jsOffsetX, offsetX, resX, shadow);
        HandleShadowOffsetY(jsOffsetY, offsetY, resY, shadow);
        auto colors = paramObject->GetProperty("colors");
        if (!colors->IsArray()) {
            shadow.radius = radius;
            shadow.offsetX = offsetX;
            shadow.offsetY = offsetY;
            shadow.colors = shadowColors;
            DataPanelModel::GetInstance()->SetShadowOption(shadow);
            return;
        }
        ParseShadowColors(colors, shadowColors);
    }

    shadow.radius = radius;
    shadow.offsetX = offsetX;
    shadow.offsetY = offsetY;
    shadow.colors = shadowColors;
    DataPanelModel::GetInstance()->SetShadowOption(shadow);
}

bool JSDataPanel::ConvertGradientColor(const JsiRef<JsiValue>& itemParam, OHOS::Ace::NG::Gradient& gradient)
{
    if (!itemParam->IsObject()) {
        return ConvertResourceColor(itemParam, gradient);
    }

    JSLinearGradient* jsLinearGradient = JSRef<JSObject>::Cast(itemParam)->Unwrap<JSLinearGradient>();
    if (!jsLinearGradient) {
        return ConvertResourceColor(itemParam, gradient);
    }

    size_t colorLength = jsLinearGradient->GetGradient().size();
    if (colorLength == 0) {
        return false;
    }
    for (size_t colorIndex = 0; colorIndex < colorLength; ++colorIndex) {
        OHOS::Ace::NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

bool JSDataPanel::ConvertResourceColor(const JsiRef<JsiValue>& itemParam, OHOS::Ace::NG::Gradient& gradient)
{
    Color color;
    RefPtr<ResourceObject> resObj;
    if (!ParseJsColor(itemParam, color, resObj)) {
        return false;
    }

    if (resObj && SystemProperties::ConfigChangePerform()) {
        std::string key = "gradient.Color";
        gradient.AddResource(key, resObj, [](const RefPtr<ResourceObject>& resObj, NG::Gradient& gradient) {
            Color color;
            ResourceParseUtils::ParseResColor(resObj, color);
            gradient.ClearColors();
            NG::GradientColor startColor;
            startColor.SetLinearColor(LinearColor(color));
            startColor.SetDimension(Dimension(0.0));
            NG::GradientColor endColor;
            endColor.SetLinearColor(LinearColor(color));
            endColor.SetDimension(Dimension(1.0));
            gradient.AddColor(startColor);
            gradient.AddColor(endColor);
        });
    }
    OHOS::Ace::NG::GradientColor gradientColorStart;
    gradientColorStart.SetLinearColor(LinearColor(color));
    gradientColorStart.SetDimension(Dimension(0.0));
    gradient.AddColor(gradientColorStart);
    OHOS::Ace::NG::GradientColor gradientColorEnd;
    gradientColorEnd.SetLinearColor(LinearColor(color));
    gradientColorEnd.SetDimension(Dimension(1.0));
    gradient.AddColor(gradientColorEnd);
    return true;
}

void JSDataPanel::ConvertThemeColor(std::vector<OHOS::Ace::NG::Gradient>& colors)
{
    RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
    auto themeColors = theme->GetColorsArray();
    for (const auto& item : themeColors) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(item.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(item.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        colors.emplace_back(gradient);
    }
}

void JSDataPanel::BorderRadius(const JSCallbackInfo& info)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        JSViewAbstract::JsBorderRadius(info);
    } else {
        std::vector<JSCallbackInfoType> checkList { JSCallbackInfoType::STRING, JSCallbackInfoType::NUMBER,
            JSCallbackInfoType::OBJECT };
        if (!CheckJSCallbackInfo("JsBorderRadius", info[0], checkList)) {
            if (dataPanelType_ != TYPE_CYCLE) {
                RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
                CHECK_NULL_VOID(theme);
                ViewAbstractModel::GetInstance()->SetBorderRadius(theme->GetDefaultBorderRadius());
            } else {
                ViewAbstractModel::GetInstance()->SetBorderRadius(Dimension {});
            }
            return;
        }
        JSViewAbstract::ParseBorderRadius(info[0]);
    }
}

void JSDataPanel::ParseShadowColors(const JSRef<JSVal>& colors, std::vector<OHOS::Ace::NG::Gradient>& shadowColors)
{
    shadowColors.clear();
    auto colorsArray = JSRef<JSArray>::Cast(colors);
    for (size_t i = 0; i < colorsArray->Length(); ++i) {
        auto item = colorsArray->GetValueAt(i);
        OHOS::Ace::NG::Gradient gradient;
        if (!ConvertGradientColor(item, gradient)) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        shadowColors.emplace_back(gradient);
    }
}

void JSDataPanel::HandleShadowRadius(
    const JSRef<JSVal>& jsRadius, double& radius, RefPtr<ResourceObject>& resR, OHOS::Ace::NG::DataPanelShadow& shadow)
{
    RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
    ParseJsDouble(jsRadius, radius, resR);
    if (resR && SystemProperties::ConfigChangePerform()) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resRadius, OHOS::Ace::NG::DataPanelShadow& shadow) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            double radius = theme->GetTrackShadowRadius().ConvertToVp();
            ResourceParseUtils::ParseResDouble(resRadius, radius);
            if (NonPositive(radius)) {
                radius = theme->GetTrackShadowRadius().ConvertToVp();
            }
            shadow.SetRadius(radius);
        };
        shadow.AddResource("shadow.radius", resR, std::move(updateFunc));
    } else {
        if (NonPositive(radius)) {
            radius = theme->GetTrackShadowRadius().ConvertToVp();
        }
    }
}

void JSDataPanel::HandleShadowOffsetX(const JSRef<JSVal>& jsOffsetX, double& offsetX, RefPtr<ResourceObject>& resX,
    OHOS::Ace::NG::DataPanelShadow& shadow)
{
    RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
    ParseJsDouble(jsOffsetX, offsetX, resX);
    if (resX && SystemProperties::ConfigChangePerform()) {
        auto&& updateFuncX = [](const RefPtr<ResourceObject>& resObj, OHOS::Ace::NG::DataPanelShadow& shadow) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            double val = theme->GetTrackShadowOffsetX().ConvertToVp();
            ResourceParseUtils::ParseResDouble(resObj, val);
            shadow.SetOffsetX(val);
        };
        shadow.AddResource("shadow.offsetX", resX, std::move(updateFuncX));
    }
}

void JSDataPanel::HandleShadowOffsetY(const JSRef<JSVal>& jsOffsetY, double& offsetY, RefPtr<ResourceObject>& resY,
    OHOS::Ace::NG::DataPanelShadow& shadow)
{
    RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
    ParseJsDouble(jsOffsetY, offsetY, resY);
    if (resY && SystemProperties::ConfigChangePerform()) {
        auto&& updateFuncY = [](const RefPtr<ResourceObject>& resObj, OHOS::Ace::NG::DataPanelShadow& shadow) {
            RefPtr<DataPanelTheme> theme = GetTheme<DataPanelTheme>();
            double val = theme->GetTrackShadowOffsetY().ConvertToVp();
            ResourceParseUtils::ParseResDouble(resObj, val);
            shadow.SetOffsetY(val);
        };
        shadow.AddResource("shadow.offsetY", resY, std::move(updateFuncY));
    }
}
} // namespace OHOS::Ace::Framework
