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

#include "frameworks/bridge/declarative_frontend/jsview/js_save_button.h"
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"

using OHOS::Ace::NG::SaveButtonModelNG;
using OHOS::Ace::NG::SecurityComponentTheme;

namespace OHOS::Ace::Framework {
bool JSSaveButton::ParseComponentStyle(const JSCallbackInfo& info,
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
            (icon > SaveButtonIconStyle::ICON_PICTURE)) {
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

void JSSaveButton::Create(const JSCallbackInfo& info)
{
    SaveButtonSaveDescription textDesc;
    SaveButtonIconStyle iconType;
    int32_t backgroundType = 0;
    if (!ParseComponentStyle(info, textDesc, iconType, backgroundType)) {
        SaveButtonModelNG::GetInstance()->Create(
            static_cast<int32_t>(SaveButtonSaveDescription::DOWNLOAD),
            static_cast<int32_t>(SaveButtonIconStyle::ICON_FULL_FILLED),
            static_cast<int32_t>(ButtonType::CAPSULE), false);
    } else {
        SaveButtonModelNG::GetInstance()->Create(static_cast<int32_t>(textDesc),
            static_cast<int32_t>(iconType), backgroundType, false);
    }
}

void JsSaveButtonClickFunction::Execute(GestureEvent& info)
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
#ifdef SECURITY_COMPONENT_ENABLE
    auto secEventValue = info.GetSecCompHandleEvent();
    if (secEventValue != nullptr) {
        res = secEventValue->GetInt("handleRes", res);
        if (res == static_cast<int32_t>(SecurityComponentHandleResult::DROP_CLICK)) {
            return;
        }
    }
#endif
    JSRef<JSVal> errorParam = JSRef<JSVal>::Make(ToJSValue(res));
    JSRef<JSVal> params[] = { clickEventParam, errorParam };
    JsFunction::ExecuteJS(2, params);
}

void JSSaveButton::JsOnClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsSaveButtonClickFunction>(JSRef<JSFunc>::Cast(info[0]));
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

void JSSaveButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSSaveButton>::Declare("SaveButton");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSaveButton>::StaticMethod("create", &JSSaveButton::Create, opt);
    JSClass<JSSaveButton>::StaticMethod("iconSize", &JSSecButtonBase::SetIconSize);
    JSClass<JSSaveButton>::StaticMethod("layoutDirection", &JSSecButtonBase::SetLayoutDirection);
    JSClass<JSSaveButton>::StaticMethod("fontSize", &JSSecButtonBase::SetFontSize);
    JSClass<JSSaveButton>::StaticMethod("fontStyle", &JSSecButtonBase::SetFontStyle);
    JSClass<JSSaveButton>::StaticMethod("iconColor", &JSSecButtonBase::SetIconColor);
    JSClass<JSSaveButton>::StaticMethod("fontWeight", &JSSecButtonBase::SetFontWeight);
    JSClass<JSSaveButton>::StaticMethod("fontFamily", &JSSecButtonBase::SetFontFamily);
    JSClass<JSSaveButton>::StaticMethod("fontColor", &JSSecButtonBase::SetFontColor);
    JSClass<JSSaveButton>::StaticMethod("backgroundColor", &JSSecButtonBase::SetBackgroundColor);
    JSClass<JSSaveButton>::StaticMethod("borderStyle", &JSSecButtonBase::SetBackgroundBorderStyle);
    JSClass<JSSaveButton>::StaticMethod("borderWidth", &JSSecButtonBase::SetBackgroundBorderWidth);
    JSClass<JSSaveButton>::StaticMethod("borderColor", &JSSecButtonBase::SetBackgroundBorderColor);
    JSClass<JSSaveButton>::StaticMethod("borderRadius", &JSSecButtonBase::SetBackgroundBorderRadius);
    JSClass<JSSaveButton>::StaticMethod("padding", &JSSecButtonBase::SetBackgroundPadding);
    JSClass<JSSaveButton>::StaticMethod("textIconSpace", &JSSecButtonBase::SetTextIconSpace);
    JSClass<JSSaveButton>::StaticMethod("onClick", &JSSaveButton::JsOnClick);
    JSClass<JSSaveButton>::StaticMethod("key", &JSViewAbstract::JsKey);
    JSClass<JSSaveButton>::StaticMethod("position", &JSViewAbstract::JsPosition);
    JSClass<JSSaveButton>::StaticMethod("markAnchor", &JSViewAbstract::JsMarkAnchor);
    JSClass<JSSaveButton>::StaticMethod("offset", &JSViewAbstract::JsOffset);
    JSClass<JSSaveButton>::StaticMethod("pop", &JSViewAbstract::Pop, opt);
    JSClass<JSSaveButton>::StaticMethod("width", &JSViewAbstract::JsWidth);
    JSClass<JSSaveButton>::StaticMethod("height", &JSViewAbstract::JsHeight);
    JSClass<JSSaveButton>::StaticMethod("size", &JSViewAbstract::JsSize);
    JSClass<JSSaveButton>::StaticMethod("constraintSize", &JSViewAbstract::JsConstraintSize);
    JSClass<JSSaveButton>::StaticMethod("debugLine", &JSViewAbstract::JsDebugLine);
    JSClass<JSSaveButton>::Bind<>(globalObj);
}
} // namespace OHOS::Ace::Framework
