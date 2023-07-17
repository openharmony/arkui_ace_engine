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

#include "frameworks/bridge/declarative_frontend/jsview/js_sec_paste_button.h"

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::PasteButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

namespace OHOS::Ace::Framework {
bool JSSecPasteButton::ParseComponentStyle(const JSCallbackInfo& info,
    PasteButtonPasteDescription& text, PasteButtonIconStyle& icon, int32_t& bg)
{
    if (!info[0]->IsObject()) {
        return false;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto value = paramObject->GetProperty("text");
    if (value->IsNumber()) {
        text = static_cast<PasteButtonPasteDescription>(value->ToNumber<int32_t>());
        if ((text < PasteButtonPasteDescription::PASTE) ||
            (text > PasteButtonPasteDescription::MAX_LABEL_TYPE)) {
            return false;
        }
    } else {
        text = PasteButtonPasteDescription::TEXT_NULL;
    }

    value = paramObject->GetProperty("icon");
    if (value->IsNumber()) {
        icon = static_cast<PasteButtonIconStyle>(value->ToNumber<int32_t>());
        if ((icon != PasteButtonIconStyle::ICON_LINE)) {
            return false;
        }
    } else {
        icon = PasteButtonIconStyle::ICON_NULL;
    }

    if ((text == PasteButtonPasteDescription::TEXT_NULL) &&
        (icon == PasteButtonIconStyle::ICON_NULL)) {
        return false;
    }

    value = paramObject->GetProperty("buttonType");
    if (value->IsNumber()) {
        bg = value->ToNumber<int32_t>();
        if ((bg < static_cast<int32_t>(ButtonType::NORMAL)) ||
            (bg > static_cast<int32_t>(ButtonType::CIRCLE))) {
            return false;
        }
    } else {
        bg = BUTTON_TYPE_NULL;
    }
    return true;
}

void JSSecPasteButton::Create(const JSCallbackInfo& info)
{
    PasteButtonPasteDescription textDesc;
    PasteButtonIconStyle iconType;
    int32_t backgroundType = 0;
    if (!ParseComponentStyle(info, textDesc, iconType, backgroundType)) {
        PasteButtonModelNG::GetInstance()->Create(
            static_cast<int32_t>(PasteButtonPasteDescription::PASTE),
            static_cast<int32_t>(PasteButtonIconStyle::ICON_LINE),
            static_cast<int32_t>(ButtonType::CAPSULE));
    } else {
        PasteButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
            static_cast<int32_t>(iconType), backgroundType);
    }
}

void JsSecPasteButtonClickFunction::Execute(GestureEvent& info)
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
    JSRef<JSVal> params[] = { clickEventParam, errorParam };
    JsFunction::ExecuteJS(2, params);
}

void JSSecPasteButton::JsOnClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsSecPasteButtonClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
    };

    NG::ViewAbstract::SetOnClick(std::move(onTap));
}

void JSSecPasteButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSSecPasteButton>::Declare("SecPasteButton");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSecPasteButton>::StaticMethod("create", &JSSecPasteButton::Create, opt);
    JSClass<JSSecPasteButton>::StaticMethod("iconSize", &JSSecButtonBase::SetIconSize);
    JSClass<JSSecPasteButton>::StaticMethod("layoutDirection", &JSSecButtonBase::SetLayoutDirection);
    JSClass<JSSecPasteButton>::StaticMethod("layoutOrder", &JSSecButtonBase::SetlayoutOrder);
    JSClass<JSSecPasteButton>::StaticMethod("fontSize", &JSSecButtonBase::SetFontSize);
    JSClass<JSSecPasteButton>::StaticMethod("fontStyle", &JSSecButtonBase::SetFontStyle);
    JSClass<JSSecPasteButton>::StaticMethod("iconColor", &JSSecButtonBase::SetIconColor);
    JSClass<JSSecPasteButton>::StaticMethod("fontWeight", &JSSecButtonBase::SetFontWeight);
    JSClass<JSSecPasteButton>::StaticMethod("fontFamily", &JSSecButtonBase::SetFontFamily);
    JSClass<JSSecPasteButton>::StaticMethod("fontColor", &JSSecButtonBase::SetFontColor);
    JSClass<JSSecPasteButton>::StaticMethod("backgroundColor", &JSSecButtonBase::SetBackgroundColor);
    JSClass<JSSecPasteButton>::StaticMethod("borderStyle", &JSSecButtonBase::SetBackgroundBorderStyle);
    JSClass<JSSecPasteButton>::StaticMethod("borderWidth", &JSSecButtonBase::SetBackgroundBorderWidth);
    JSClass<JSSecPasteButton>::StaticMethod("borderColor", &JSSecButtonBase::SetBackgroundBorderColor);
    JSClass<JSSecPasteButton>::StaticMethod("borderRadius", &JSSecButtonBase::SetBackgroundBorderRadius);
    JSClass<JSSecPasteButton>::StaticMethod("padding", &JSSecButtonBase::SetBackgroundPadding);
    JSClass<JSSecPasteButton>::StaticMethod("textIconSpace", &JSSecButtonBase::SetTextIconSpace);
    JSClass<JSSecPasteButton>::StaticMethod("onClick", &JSSecPasteButton::JsOnClick);
    JSClass<JSSecPasteButton>::StaticMethod("key", &JSViewAbstract::JsKey);
    JSClass<JSSecPasteButton>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSSecPasteButton>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSSecPasteButton>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSSecPasteButton>::StaticMethod("pop", &JSViewAbstract::Pop, opt);
#if defined(PREVIEW)
    JSClass<JSSecPasteButton>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
#endif
    JSClass<JSSecPasteButton>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
