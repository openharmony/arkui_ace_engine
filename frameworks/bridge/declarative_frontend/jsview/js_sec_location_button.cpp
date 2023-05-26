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

#include "frameworks/bridge/declarative_frontend/jsview/js_sec_location_button.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::LocationButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;
namespace {
static constexpr int TWO_PARAMS = 2;
}

namespace OHOS::Ace::Framework {
void JSSecLocationButton::SetIconSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value) || (value.ConvertToVp() < theme->GetMinIconSize().ConvertToVp())) {
        LocationButtonModelNG::GetInstance()->SetIconSize(theme->GetIconSize());
    } else {
        LocationButtonModelNG::GetInstance()->SetIconSize(value);
    }
}

void JSSecLocationButton::SetIconColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color color;
    if (!ParseJsColor(info[0], color)) {
        color = theme->GetIconColor();
    }
    LocationButtonModelNG::GetInstance()->SetIconColor(color);
}

void JSSecLocationButton::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value) || (value.ConvertToVp() < theme->GetMinFontSize().ConvertToVp())) {
        LocationButtonModelNG::GetInstance()->SetFontSize(theme->GetFontSize());
    } else {
        LocationButtonModelNG::GetInstance()->SetFontSize(value);
    }
}

void JSSecLocationButton::SetFontStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber()) {
        LocationButtonModelNG::GetInstance()->SetFontStyle(Ace::FontStyle::NORMAL);
        return;
    }
    uint32_t value = info[0]->ToNumber<uint32_t>();
    if (value < static_cast<uint32_t>(Ace::FontStyle::NORMAL) ||
        value > static_cast<uint32_t>(Ace::FontStyle::ITALIC)) {
        LocationButtonModelNG::GetInstance()->SetFontStyle(Ace::FontStyle::NORMAL);
        return;
    }
    LocationButtonModelNG::GetInstance()->SetFontStyle(static_cast<Ace::FontStyle>(value));
}

void JSSecLocationButton::SetFontWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsString()) {
        LocationButtonModelNG::GetInstance()->SetFontWeight(FontWeight::NORMAL);
        return;
    }
    std::string value = info[0]->ToString();
    LocationButtonModelNG::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSSecLocationButton::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        fontFamilies.emplace_back("HarmonyOS Sans");
        LocationButtonModelNG::GetInstance()->SetFontFamily(fontFamilies);
        return;
    }
    LocationButtonModelNG::GetInstance()->SetFontFamily(fontFamilies);
}

void JSSecLocationButton::SetFontColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color color;
    if (!ParseJsColor(info[0], color)) {
        color = theme->GetFontColor();
    }
    LocationButtonModelNG::GetInstance()->SetFontColor(color);
}

void JSSecLocationButton::SetLayoutDirection(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsNumber()) {
        LocationButtonModelNG::GetInstance()->SetTextIconLayoutDirection(
            SecurityComponentLayoutDirection::HORIZONTAL);
        return;
    }
    int32_t value = info[0]->ToNumber<int32_t>();
    if ((value < static_cast<int32_t>(SecurityComponentLayoutDirection::HORIZONTAL)) ||
        (value > static_cast<int32_t>(SecurityComponentLayoutDirection::VERTICAL))) {
        LocationButtonModelNG::GetInstance()->SetTextIconLayoutDirection(
            SecurityComponentLayoutDirection::HORIZONTAL);
        return;
    }
    LocationButtonModelNG::GetInstance()->SetTextIconLayoutDirection(
        static_cast<SecurityComponentLayoutDirection>(value));
}

void JSSecLocationButton::SetlayoutOrder(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsNumber()) {
        LocationButtonModelNG::GetInstance()->SetlayoutOrder(
            SecSecurityComponentLayoutOrder::ICON_FIRST);
        return;
    }
    int32_t value = info[0]->ToNumber<int32_t>();
    if ((value < static_cast<int32_t>(SecSecurityComponentLayoutOrder::ICON_FIRST)) ||
        (value > static_cast<int32_t>(SecSecurityComponentLayoutOrder::TEXT_FIRST))) {
        LocationButtonModelNG::GetInstance()->SetlayoutOrder(
            SecSecurityComponentLayoutOrder::ICON_FIRST);
        return;
    }
    LocationButtonModelNG::GetInstance()->SetlayoutOrder(static_cast<SecSecurityComponentLayoutOrder>(value));
}

void JSSecLocationButton::SetBackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color color;
    if (!ParseJsColor(info[0], color)) {
        color = theme->GetBackgroundColor();
    }
    LocationButtonModelNG::GetInstance()->SetBackgroundColor(color);
}

void JSSecLocationButton::SetBackgroundBorderStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    if (!info[0]->IsNumber()) {
        LocationButtonModelNG::GetInstance()->SetBackgroundBorderStyle(BorderStyle::NONE);
        return;
    }
    int32_t value = info[0]->ToNumber<int32_t>();
    if ((value < static_cast<int32_t>(BorderStyle::SOLID)) ||
        (value > static_cast<int32_t>(BorderStyle::NONE))) {
        LocationButtonModelNG::GetInstance()->SetBackgroundBorderStyle(BorderStyle::NONE);
        return;
    }
    LocationButtonModelNG::GetInstance()->SetBackgroundBorderStyle(static_cast<BorderStyle>(value));
}

void JSSecLocationButton::SetBackgroundBorderWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LocationButtonModelNG::GetInstance()->SetBackgroundBorderWidth(theme->GetBorderWidth());
    } else {
        LocationButtonModelNG::GetInstance()->SetBackgroundBorderWidth(value);
    }
}

void JSSecLocationButton::SetBackgroundBorderColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    Color borderColor;
    if (!ParseJsColor(info[0], borderColor)) {
        borderColor = theme->GetBorderColor();
    }
    LocationButtonModelNG::GetInstance()->SetBackgroundBorderColor(borderColor);
}

void JSSecLocationButton::SetBackgroundBorderRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LocationButtonModelNG::GetInstance()->SetBackgroundBorderRadius(theme->GetBorderRadius());
    } else {
        LocationButtonModelNG::GetInstance()->SetBackgroundBorderRadius(value);
    }
}

void JSSecLocationButton::SetBackgroundPadding(const JSCallbackInfo& info)
{
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            left = leftDimen;
        }
        CalcDimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            right = rightDimen;
        }
        CalcDimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            top = topDimen;
        }
        CalcDimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            bottom = bottomDimen;
        }
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            LocationButtonModelNG::GetInstance()->SetBackgroundPadding(left, right, top, bottom);
            return;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        LocationButtonModelNG::GetInstance()->SetBackgroundPadding(std::nullopt);
    } else {
        LocationButtonModelNG::GetInstance()->SetBackgroundPadding(length);
    }
}

void JSSecLocationButton::SetTextIconPadding(const JSCallbackInfo& info)
{
    if ((info.Length() < 1)) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto theme = GetTheme<SecurityComponentTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        LocationButtonModelNG::GetInstance()->SetTextIconPadding(theme->GetTextIconPadding());
    } else {
        LocationButtonModelNG::GetInstance()->SetTextIconPadding(length);
    }
}

bool JSSecLocationButton::ParseComponentStyle(const JSCallbackInfo& info,
    LocationButtonLocationDescription& text, LocationButtonIconStyle& icon, SecurityComponentBackgroundType& bg)
{
    if ((info.Length() < 1) || !info[0]->IsObject()) {
        return false;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto value = paramObject->GetProperty("text");
    if (value->IsNumber()) {
        text = static_cast<LocationButtonLocationDescription>(value->ToNumber<int32_t>());
        if ((text < LocationButtonLocationDescription::CURRENT_LOCATION) ||
            (text > LocationButtonLocationDescription::CURRENT_POSITION)) {
            LOGE("The arg is wrong, text type invalid");
            return false;
        }
    } else {
        text = LocationButtonLocationDescription::TEXT_NULL;
    }

    value = paramObject->GetProperty("icon");
    if (value->IsNumber()) {
        icon = static_cast<LocationButtonIconStyle>(value->ToNumber<int32_t>());
        if ((icon < LocationButtonIconStyle::ICON_FULL_FILLED) ||
            (icon > LocationButtonIconStyle::ICON_LINE)) {
            LOGE("The arg is wrong, icon type invalid");
            return false;
        }
    } else {
        icon = LocationButtonIconStyle::ICON_NULL;
    }

    if ((text == LocationButtonLocationDescription::TEXT_NULL) &&
        (icon == LocationButtonIconStyle::ICON_NULL)) {
        LOGE("The arg is wrong, at least one of icon and text must exist");
        return false;
    }

    value = paramObject->GetProperty("background");
    if (value->IsNumber()) {
        bg = static_cast<SecurityComponentBackgroundType>(value->ToNumber<int32_t>());
        if ((bg < SecurityComponentBackgroundType::CAPSULE) ||
            (bg > SecurityComponentBackgroundType::NORMAL)) {
            LOGE("The arg is wrong, background type invalid");
            return false;
        }
    } else {
        bg = SecurityComponentBackgroundType::BACKGROUND_NULL;
    }
    return true;
}

void JSSecLocationButton::Create(const JSCallbackInfo& info)
{
    LocationButtonLocationDescription textDesc;
    LocationButtonIconStyle iconType;
    SecurityComponentBackgroundType backgroundType;
    if (!ParseComponentStyle(info, textDesc, iconType, backgroundType)) {
        LocationButtonModelNG::GetInstance()->Create(
            static_cast<int32_t>(LocationButtonLocationDescription::CURRENT_LOCATION),
            static_cast<int32_t>(LocationButtonIconStyle::ICON_FULL_FILLED),
            SecurityComponentBackgroundType::CAPSULE);
    } else {
        LocationButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
            static_cast<int32_t>(iconType), backgroundType);
    }
}

void JsSecLocationButtonClickFunction::Execute(GestureEvent& info)
{
    JSRef<JSObject> clickEventParam = JSRef<JSObject>::New();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    clickEventParam->SetProperty<double>("screenX", SystemProperties::Px2Vp(globalOffset.GetX()));
    clickEventParam->SetProperty<double>("screenY", SystemProperties::Px2Vp(globalOffset.GetY()));
    clickEventParam->SetProperty<double>("x", SystemProperties::Px2Vp(localOffset.GetX()));
    clickEventParam->SetProperty<double>("y", SystemProperties::Px2Vp(localOffset.GetY()));
    clickEventParam->SetProperty<double>("timestamp",
        static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    clickEventParam->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    clickEventParam->SetProperty<double>("pressure", info.GetForce());
    if (info.GetTiltX().has_value()) {
        clickEventParam->SetProperty<double>("tiltX", info.GetTiltX().value());
    }
    if (info.GetTiltY().has_value()) {
        clickEventParam->SetProperty<double>("tiltY", info.GetTiltY().value());
    }
    clickEventParam->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    auto target = CreateEventTargetObject(info);
    clickEventParam->SetPropertyObject("target", target);

    int32_t res = static_cast<int32_t>(SecurityComponentHandleResult::CLICK_GRANT_FAILED);
#ifdef SECURITY_COMPONENT_ENABLE
    auto secEventValue = info.GetSecCompHandleEvent();
    if (secEventValue != nullptr) {
        res = secEventValue->GetInt("handleRes", res);
    }
#endif
    JSRef<JSVal> errorParam = JSRef<JSVal>::Make(ToJSValue(res));
    JSRef<JSVal> params[] = { errorParam, clickEventParam };
    JsFunction::ExecuteJS(TWO_PARAMS, params);
}

void JSSecLocationButton::JsOnClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGW("the info is not click function");
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsSecLocationButtonClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
    };

    NG::ViewAbstract::SetOnClick(std::move(onTap));
}

void JSSecLocationButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSSecLocationButton>::Declare("SecLocationButton");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSecLocationButton>::StaticMethod("create", &JSSecLocationButton::Create, opt);
    JSClass<JSSecLocationButton>::StaticMethod("iconSize", &JSSecLocationButton::SetIconSize);
    JSClass<JSSecLocationButton>::StaticMethod("layoutDirection", &JSSecLocationButton::SetLayoutDirection);
    JSClass<JSSecLocationButton>::StaticMethod("layoutOrder", &JSSecLocationButton::SetlayoutOrder);
    JSClass<JSSecLocationButton>::StaticMethod("fontSize", &JSSecLocationButton::SetFontSize);
    JSClass<JSSecLocationButton>::StaticMethod("fontStyle", &JSSecLocationButton::SetFontStyle);
    JSClass<JSSecLocationButton>::StaticMethod("iconColor", &JSSecLocationButton::SetIconColor);
    JSClass<JSSecLocationButton>::StaticMethod("fontWeight", &JSSecLocationButton::SetFontWeight);
    JSClass<JSSecLocationButton>::StaticMethod("fontFamily", &JSSecLocationButton::SetFontFamily);
    JSClass<JSSecLocationButton>::StaticMethod("fontColor", &JSSecLocationButton::SetFontColor);
    JSClass<JSSecLocationButton>::StaticMethod("backgroundColor", &JSSecLocationButton::SetBackgroundColor);
    JSClass<JSSecLocationButton>::StaticMethod("borderStyle", &JSSecLocationButton::SetBackgroundBorderStyle);
    JSClass<JSSecLocationButton>::StaticMethod("borderWidth", &JSSecLocationButton::SetBackgroundBorderWidth);
    JSClass<JSSecLocationButton>::StaticMethod("borderColor", &JSSecLocationButton::SetBackgroundBorderColor);
    JSClass<JSSecLocationButton>::StaticMethod("borderRadius", &JSSecLocationButton::SetBackgroundBorderRadius);
    JSClass<JSSecLocationButton>::StaticMethod("backgroundPadding", &JSSecLocationButton::SetBackgroundPadding);
    JSClass<JSSecLocationButton>::StaticMethod("textIconPadding", &JSSecLocationButton::SetTextIconPadding);
    JSClass<JSSecLocationButton>::StaticMethod("onClick", &JSSecLocationButton::JsOnClick);
    JSClass<JSSecLocationButton>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSSecLocationButton>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSSecLocationButton>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSSecLocationButton>::StaticMethod("pop", &JSViewAbstract::Pop, opt);
#if defined(PREVIEW)
    JSClass<JSSecLocationButton>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
#endif
    JSClass<JSSecLocationButton>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
