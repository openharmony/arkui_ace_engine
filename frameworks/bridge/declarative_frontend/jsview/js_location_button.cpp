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

#include "frameworks/bridge/declarative_frontend/jsview/js_location_button.h"
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::LocationButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

namespace OHOS::Ace::Framework {
bool JSLocationButton::ParseComponentStyle(const JSCallbackInfo& info,
    LocationButtonLocationDescription& text, LocationButtonIconStyle& icon, int32_t& bg)
{
    if ((info.Length() < 1) || (!info[0]->IsObject())) {
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

    value = paramObject->GetProperty("buttonType");
    if (value->IsNumber()) {
        bg = value->ToNumber<int32_t>();
        if ((bg != static_cast<int32_t>(ButtonType::NORMAL)) &&
            (bg != static_cast<int32_t>(ButtonType::CIRCLE)) &&
            (bg != static_cast<int32_t>(ButtonType::CAPSULE)) &&
            (bg != static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE))) {
            return false;
        }
    } else {
        bg = static_cast<int32_t>(ButtonType::CAPSULE);
    }
    return true;
}

void JSLocationButton::Create(const JSCallbackInfo& info)
{
    LocationButtonLocationDescription textDesc;
    LocationButtonIconStyle iconType;
    int32_t backgroundType = 0;
    if (!ParseComponentStyle(info, textDesc, iconType, backgroundType)) {
        LocationButtonModelNG::GetInstance()->Create(
            static_cast<int32_t>(LocationButtonLocationDescription::CURRENT_LOCATION),
            static_cast<int32_t>(LocationButtonIconStyle::ICON_LINE),
            static_cast<int32_t>(ButtonType::CAPSULE), false);
    } else {
        LocationButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
            static_cast<int32_t>(iconType), backgroundType, false);
    }
}

void JsLocationButtonClickFunction::Execute(GestureEvent& info)
{
    JSRef<JSObject> clickEventParam = JSRef<JSObject>::New();
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    clickEventParam->SetProperty<double>("screenX", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
    clickEventParam->SetProperty<double>("screenY", PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));
    clickEventParam->SetProperty<double>("x", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
    clickEventParam->SetProperty<double>("y", PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));
    clickEventParam->SetProperty<double>("timestamp",
        static_cast<double>(info.GetTimeStamp().time_since_epoch().count()));
    clickEventParam->SetProperty<double>("source", static_cast<int32_t>(info.GetSourceDevice()));
    clickEventParam->SetProperty<double>("pressure", info.GetForce());
    clickEventParam->SetProperty<double>("tiltX", info.GetTiltX().value_or(0.0f));
    clickEventParam->SetProperty<double>("tiltY", info.GetTiltY().value_or(0.0f));
    clickEventParam->SetProperty<double>("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    auto target = CreateEventTargetObject(info);
    clickEventParam->SetPropertyObject("target", target);

    int32_t res = static_cast<int32_t>(SecurityComponentHandleResult::CLICK_GRANT_FAILED);
    JSRef<JSObject> errorMessage = JSRef<JSObject>::New();
#ifdef SECURITY_COMPONENT_ENABLE
    auto secEventValue = info.GetSecCompHandleEvent();
    if (secEventValue != nullptr) {
        res = secEventValue->GetInt("handleRes", res);
        int32_t code = static_cast<int32_t>(SecurityComponentErrorCode::SUCCESS);
        std::string message;
        if (res == static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK)) {
            return;
        }
        code = secEventValue->GetInt("code", code);
        errorMessage->SetProperty<int32_t>("code", code);
        message = secEventValue->GetString("message", message);
        errorMessage->SetProperty<std::string>("message", message);
    }
#endif
    JSRef<JSVal> errorParam = JSRef<JSVal>::Make(ToJSValue(res));
    JSRef<JSVal> params[] = { clickEventParam, errorParam, errorMessage };
    JsFunction::ExecuteJS(3, params); // 3 means three params.
}

void JSLocationButton::JsOnClick(const JSCallbackInfo& info)
{
    if ((info.Length() < 1) || (!info[0]->IsFunction())) {
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsLocationButtonClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = frameNode](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        JSInteractableView::ReportClickEvent(node);
#endif
    };

    double distanceThreshold = std::numeric_limits<double>::infinity();
    if (info.Length() > 1 && info[1]->IsNumber()) {
        distanceThreshold = info[1]->ToNumber<double>();
        distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
    }
    NG::ViewAbstract::SetOnClick(std::move(onTap), distanceThreshold);
}

void JSLocationButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSLocationButton>::Declare("LocationButton");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSLocationButton>::StaticMethod("create", &JSLocationButton::Create, opt);
    JSClass<JSLocationButton>::StaticMethod("iconSize", &JSSecButtonBase::SetIconSize);
    JSClass<JSLocationButton>::StaticMethod("layoutDirection", &JSSecButtonBase::SetLayoutDirection);
    JSClass<JSLocationButton>::StaticMethod("fontSize", &JSSecButtonBase::SetFontSize);
    JSClass<JSLocationButton>::StaticMethod("fontStyle", &JSSecButtonBase::SetFontStyle);
    JSClass<JSLocationButton>::StaticMethod("iconColor", &JSSecButtonBase::SetIconColor);
    JSClass<JSLocationButton>::StaticMethod("fontWeight", &JSSecButtonBase::SetFontWeight);
    JSClass<JSLocationButton>::StaticMethod("fontFamily", &JSSecButtonBase::SetFontFamily);
    JSClass<JSLocationButton>::StaticMethod("fontColor", &JSSecButtonBase::SetFontColor);
    JSClass<JSLocationButton>::StaticMethod("backgroundColor", &JSSecButtonBase::SetBackgroundColor);
    JSClass<JSLocationButton>::StaticMethod("borderStyle", &JSSecButtonBase::SetBackgroundBorderStyle);
    JSClass<JSLocationButton>::StaticMethod("borderWidth", &JSSecButtonBase::SetBackgroundBorderWidth);
    JSClass<JSLocationButton>::StaticMethod("borderColor", &JSSecButtonBase::SetBackgroundBorderColor);
    JSClass<JSLocationButton>::StaticMethod("borderRadius", &JSSecButtonBase::SetBackgroundBorderRadius);
    JSClass<JSLocationButton>::StaticMethod("padding", &JSSecButtonBase::SetBackgroundPadding);
    JSClass<JSLocationButton>::StaticMethod("textIconSpace", &JSSecButtonBase::SetTextIconSpace);
    JSClass<JSLocationButton>::StaticMethod("align", &JSSecButtonBase::SetAlign);
    JSClass<JSLocationButton>::StaticMethod("onClick", &JSLocationButton::JsOnClick);
    JSClass<JSLocationButton>::StaticMethod("key", &JSViewAbstract::JsKey);
    JSClass<JSLocationButton>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSLocationButton>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSLocationButton>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSLocationButton>::StaticMethod("pop", &JSViewAbstract::Pop, opt);
    JSClass<JSLocationButton>::StaticMethod("width", &JSViewAbstract::JsWidth);
    JSClass<JSLocationButton>::StaticMethod("height", &JSViewAbstract::JsHeight);
    JSClass<JSLocationButton>::StaticMethod("size", &JSViewAbstract::JsSize);
    JSClass<JSLocationButton>::StaticMethod("constraintSize", &JSViewAbstract::JsConstraintSize);
    JSClass<JSLocationButton>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
    JSClass<JSLocationButton>::StaticMethod("alignRules", &JSViewAbstract::JsAlignRules);
    JSClass<JSLocationButton>::StaticMethod("id", &JSViewAbstract::JsId);
    JSClass<JSLocationButton>::StaticMethod("chainMode", &JSViewAbstract::JsChainMode);
    JSClass<JSLocationButton>::StaticMethod("maxFontScale", &JSSecButtonBase::SetMaxFontScale);
    JSClass<JSLocationButton>::StaticMethod("minFontScale", &JSSecButtonBase::SetMinFontScale);
    JSClass<JSLocationButton>::StaticMethod("maxLines", &JSSecButtonBase::SetMaxLines);
    JSClass<JSLocationButton>::StaticMethod("maxFontSize", &JSSecButtonBase::SetMaxFontSize);
    JSClass<JSLocationButton>::StaticMethod("minFontSize", &JSSecButtonBase::SetMinFontSize);
    JSClass<JSLocationButton>::StaticMethod("heightAdaptivePolicy", &JSSecButtonBase::SetHeightAdaptivePolicy);
    JSClass<JSLocationButton>::StaticMethod("enabled", &JSViewAbstract::JsEnabled);
    JSClass<JSLocationButton>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
