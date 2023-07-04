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

#include "frameworks/bridge/declarative_frontend/jsview/js_sec_save_button.h"

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::SaveButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

namespace OHOS::Ace::Framework {
bool JSSecSaveButton::ParseComponentStyle(const JSCallbackInfo& info,
    SaveButtonSaveDescription& text, SaveButtonIconStyle& icon, int32_t& bg)
{
    if (!info[0]->IsObject()) {
        return false;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto value = paramObject->GetProperty("text");
    if (value->IsNumber()) {
        text = static_cast<SaveButtonSaveDescription>(value->ToNumber<int32_t>());
        if ((text < SaveButtonSaveDescription::DOWNLOAD) ||
            (text > SaveButtonSaveDescription::MAX_LABEL_TYPE)) {
            return false;
        }
    } else {
        text = SaveButtonSaveDescription::TEXT_NULL;
    }

    value = paramObject->GetProperty("icon");
    if (value->IsNumber()) {
        icon = static_cast<SaveButtonIconStyle>(value->ToNumber<int32_t>());
        if ((icon < SaveButtonIconStyle::ICON_FULL_FILLED) ||
            (icon > SaveButtonIconStyle::ICON_LINE)) {
            return false;
        }
    } else {
        icon = SaveButtonIconStyle::ICON_NULL;
    }

    if ((text == SaveButtonSaveDescription::TEXT_NULL) &&
        (icon == SaveButtonIconStyle::ICON_NULL)) {
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

void JSSecSaveButton::Create(const JSCallbackInfo& info)
{
    SaveButtonSaveDescription textDesc;
    SaveButtonIconStyle iconType;
    int32_t backgroundType = 0;
    if (!ParseComponentStyle(info, textDesc, iconType, backgroundType)) {
        SaveButtonModelNG::GetInstance()->Create(
            static_cast<int32_t>(SaveButtonSaveDescription::DOWNLOAD),
            static_cast<int32_t>(SaveButtonIconStyle::ICON_FULL_FILLED),
            static_cast<int32_t>(ButtonType::CAPSULE));
    } else {
        SaveButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
            static_cast<int32_t>(iconType), backgroundType);
    }
}

void JsSecSaveButtonClickFunction::Execute(GestureEvent& info)
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

void JSSecSaveButton::JsOnClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsSecSaveButtonClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
    };

    NG::ViewAbstract::SetOnClick(std::move(onTap));
}

void JSSecSaveButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSSecSaveButton>::Declare("SecSaveButton");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSecSaveButton>::StaticMethod("create", &JSSecSaveButton::Create, opt);
    JSClass<JSSecSaveButton>::StaticMethod("iconSize", &JSSecButtonBase::SetIconSize);
    JSClass<JSSecSaveButton>::StaticMethod("layoutDirection", &JSSecButtonBase::SetLayoutDirection);
    JSClass<JSSecSaveButton>::StaticMethod("layoutOrder", &JSSecButtonBase::SetlayoutOrder);
    JSClass<JSSecSaveButton>::StaticMethod("fontSize", &JSSecButtonBase::SetFontSize);
    JSClass<JSSecSaveButton>::StaticMethod("fontStyle", &JSSecButtonBase::SetFontStyle);
    JSClass<JSSecSaveButton>::StaticMethod("iconColor", &JSSecButtonBase::SetIconColor);
    JSClass<JSSecSaveButton>::StaticMethod("fontWeight", &JSSecButtonBase::SetFontWeight);
    JSClass<JSSecSaveButton>::StaticMethod("fontFamily", &JSSecButtonBase::SetFontFamily);
    JSClass<JSSecSaveButton>::StaticMethod("fontColor", &JSSecButtonBase::SetFontColor);
    JSClass<JSSecSaveButton>::StaticMethod("backgroundColor", &JSSecButtonBase::SetBackgroundColor);
    JSClass<JSSecSaveButton>::StaticMethod("borderStyle", &JSSecButtonBase::SetBackgroundBorderStyle);
    JSClass<JSSecSaveButton>::StaticMethod("borderWidth", &JSSecButtonBase::SetBackgroundBorderWidth);
    JSClass<JSSecSaveButton>::StaticMethod("borderColor", &JSSecButtonBase::SetBackgroundBorderColor);
    JSClass<JSSecSaveButton>::StaticMethod("borderRadius", &JSSecButtonBase::SetBackgroundBorderRadius);
    JSClass<JSSecSaveButton>::StaticMethod("padding", &JSSecButtonBase::SetBackgroundPadding);
    JSClass<JSSecSaveButton>::StaticMethod("textIconSpace", &JSSecButtonBase::SetTextIconSpace);
    JSClass<JSSecSaveButton>::StaticMethod("onClick", &JSSecSaveButton::JsOnClick);
    JSClass<JSSecSaveButton>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSSecSaveButton>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSSecSaveButton>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSSecSaveButton>::StaticMethod("pop", &JSViewAbstract::Pop, opt);
#if defined(PREVIEW)
    JSClass<JSSecSaveButton>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
#endif
    JSClass<JSSecSaveButton>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
