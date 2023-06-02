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

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::LocationButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

namespace OHOS::Ace::Framework {
static ButtonType TransformSecCompBgType(SecurityComponentBackgroundType type)
{
    ButtonType buttonType = ButtonType::CAPSULE;
    switch (type) {
        case SecurityComponentBackgroundType::CAPSULE:
            buttonType = ButtonType::CAPSULE;
            break;
        case SecurityComponentBackgroundType::CIRCLE:
            buttonType = ButtonType::CIRCLE;
            break;
        case SecurityComponentBackgroundType::NORMAL:
            buttonType = ButtonType::NORMAL;
            break;
        default:
            break;
    }
    return buttonType;
}

bool JSSecLocationButton::ParseComponentStyle(const JSCallbackInfo& info,
    LocationButtonLocationDescription& text, LocationButtonIconStyle& icon, SecurityComponentBackgroundType& bg)
{
    if (!info[0]->IsObject()) {
        return false;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto value = paramObject->GetProperty("text");
    if (value->IsNumber()) {
        text = static_cast<LocationButtonLocationDescription>(value->ToNumber<int32_t>());
        if ((text < LocationButtonLocationDescription::CURRENT_LOCATION) ||
            (text > LocationButtonLocationDescription::CURRENT_POSITION)) {
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
            return false;
        }
    } else {
        icon = LocationButtonIconStyle::ICON_NULL;
    }

    if ((text == LocationButtonLocationDescription::TEXT_NULL) &&
        (icon == LocationButtonIconStyle::ICON_NULL)) {
        return false;
    }

    value = paramObject->GetProperty("background");
    if (value->IsNumber()) {
        bg = static_cast<SecurityComponentBackgroundType>(value->ToNumber<int32_t>());
        if ((bg < SecurityComponentBackgroundType::CAPSULE) ||
            (bg > SecurityComponentBackgroundType::NORMAL)) {
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
            static_cast<int32_t>(ButtonType::CAPSULE));
    } else {
        if (backgroundType == SecurityComponentBackgroundType::BACKGROUND_NULL) {
            LocationButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
                static_cast<int32_t>(iconType), static_cast<int32_t>(backgroundType));
        } else {
            LocationButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
                static_cast<int32_t>(iconType), static_cast<int32_t>(TransformSecCompBgType(backgroundType)));
        }
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
    JsFunction::ExecuteJS(2, params);
}

void JSSecLocationButton::JsOnClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
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
    JSClass<JSSecLocationButton>::StaticMethod("iconSize", &JSSecButtonBase::SetIconSize);
    JSClass<JSSecLocationButton>::StaticMethod("layoutDirection", &JSSecButtonBase::SetLayoutDirection);
    JSClass<JSSecLocationButton>::StaticMethod("layoutOrder", &JSSecButtonBase::SetlayoutOrder);
    JSClass<JSSecLocationButton>::StaticMethod("fontSize", &JSSecButtonBase::SetFontSize);
    JSClass<JSSecLocationButton>::StaticMethod("fontStyle", &JSSecButtonBase::SetFontStyle);
    JSClass<JSSecLocationButton>::StaticMethod("iconColor", &JSSecButtonBase::SetIconColor);
    JSClass<JSSecLocationButton>::StaticMethod("fontWeight", &JSSecButtonBase::SetFontWeight);
    JSClass<JSSecLocationButton>::StaticMethod("fontFamily", &JSSecButtonBase::SetFontFamily);
    JSClass<JSSecLocationButton>::StaticMethod("fontColor", &JSSecButtonBase::SetFontColor);
    JSClass<JSSecLocationButton>::StaticMethod("backgroundColor", &JSSecButtonBase::SetBackgroundColor);
    JSClass<JSSecLocationButton>::StaticMethod("borderStyle", &JSSecButtonBase::SetBackgroundBorderStyle);
    JSClass<JSSecLocationButton>::StaticMethod("borderWidth", &JSSecButtonBase::SetBackgroundBorderWidth);
    JSClass<JSSecLocationButton>::StaticMethod("borderColor", &JSSecButtonBase::SetBackgroundBorderColor);
    JSClass<JSSecLocationButton>::StaticMethod("borderRadius", &JSSecButtonBase::SetBackgroundBorderRadius);
    JSClass<JSSecLocationButton>::StaticMethod("backgroundPadding", &JSSecButtonBase::SetBackgroundPadding);
    JSClass<JSSecLocationButton>::StaticMethod("textIconPadding", &JSSecButtonBase::SetTextIconSpace);
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
