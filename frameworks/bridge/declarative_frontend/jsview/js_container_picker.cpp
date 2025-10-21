/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_container_picker.h"

#include "frameworks/base/log/ace_scoring_log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/core/components_ng/pattern/container_picker/container_picker_model.h"
#include "frameworks/core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::Framework {

void JSContainerPicker::Create(const JSCallbackInfo& info)
{
    NG::ContainerPickerModel::Create();
    JSRef<JSVal> selectedIndex;
    if (info.Length() >= 1 && info[0]->IsObject()) {
        JSRef<JSObject> paramObj = JSRef<JSObject>::Cast(info[0]);
        if (!paramObj->IsUndefined()) {
            selectedIndex = paramObj->GetProperty("selectedIndex");
        }
    }
    
    if (!selectedIndex->IsNull() && selectedIndex->IsNumber()) {
        auto parseIndex = selectedIndex->ToNumber<int32_t>();
        NG::ContainerPickerModel::SetSelectedIndex(parseIndex);
    }
}

void JSContainerPicker::SetCanLoop(const JSCallbackInfo& info)
{
    bool value = true;
    if (info.Length() >= 1 && info[0]->IsBoolean()) {
        value = info[0]->ToBoolean();
    }
    NG::ContainerPickerModel::SetCanLoop(value);
}

void JSContainerPicker::SetEnableHapticFeedback(const JSCallbackInfo& info)
{
    bool isEnableHapticFeedback = true;
    if (info.Length() >= 1 && info[0]->IsBoolean()) {
        isEnableHapticFeedback = info[0]->ToBoolean();
    }
    NG::ContainerPickerModel::SetEnableHapticFeedback(isEnableHapticFeedback);
}

void JSContainerPicker::OnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = JSRef<JSFunc>::Cast(info[0]);
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const double& index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Picker.onChange");
        auto params = ConvertToJSValues(index);
        func->Call(JSRef<JSObject>(), 1, params.data());
    };
    NG::ContainerPickerModel::SetOnChange(std::move(onChange));
    info.ReturnSelf();
}

void JSContainerPicker::OnScrollStop(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = JSRef<JSFunc>::Cast(info[0]);
    auto onScrollStop = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const double& index) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Picker.onScrollStop");
        auto params = ConvertToJSValues(index);
        func->Call(JSRef<JSObject>(), 1, params.data());
    };
    NG::ContainerPickerModel::SetOnScrollStop(std::move(onScrollStop));
    info.ReturnSelf();
}

void JSContainerPicker::SetSelectionIndicator(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);

    NG::PickerIndicatorStyle indicatorStyle;
    int32_t type = jsObj->GetPropertyValue<int32_t>("type", static_cast<int32_t>(NG::IndicatorType::DIVIDER));
    indicatorStyle.type = type;
    SetDivider(jsObj, indicatorStyle);
    SetSelectedBackground(jsObj, indicatorStyle);
    NG::ContainerPickerModel::SetIndicatorStyle(indicatorStyle);
}

void JSContainerPicker::SetDivider(const JSRef<JSObject>& paramObj, NG::PickerIndicatorStyle& indicatorStyle)
{
    auto dividerWidth = paramObj->GetProperty("dividerWidth");
    auto dividerColor = paramObj->GetProperty("dividerColor");
    auto startMargin = paramObj->GetProperty("startMargin");
    auto endMargin = paramObj->GetProperty("endMargin");

    if (!dividerWidth->IsUndefined() && !dividerWidth->IsNull()) {
        CalcDimension dividerWidthVal;
        if (ParseLengthMetricsToDimension(dividerWidth, dividerWidthVal)) {
            if (GreatOrEqual(dividerWidthVal.Value(), 0.0f)) {
                indicatorStyle.dividerWidth = dividerWidthVal;
            }
        }
    }
    if (!dividerColor->IsUndefined() && !dividerColor->IsNull()) {
        Color color;
        if (ParseJsColor(dividerColor, color)) {
            indicatorStyle.dividerColor = color;
        }
    }
    if (!startMargin->IsUndefined() && !startMargin->IsNull()) {
        CalcDimension startMarginVal;
        if (ParseLengthMetricsToDimension(startMargin, startMarginVal)) {
            if (GreatOrEqual(startMarginVal.Value(), 0.0f)) {
                indicatorStyle.startMargin = startMarginVal;
            }
        }
    }
    if (!endMargin->IsUndefined() && !endMargin->IsNull()) {
        CalcDimension endMarginVal;
        if (ParseLengthMetricsToDimension(endMargin, endMarginVal)) {
            if (GreatOrEqual(endMarginVal.Value(), 0.0f)) {
                indicatorStyle.endMargin = endMarginVal;
            }
        }
    }
}

void JSContainerPicker::SetSelectedBackground(const JSRef<JSObject>& paramObj, NG::PickerIndicatorStyle& indicatorStyle)
{
    auto color = paramObj->GetProperty("backgroundColor");
    auto borderRadius = paramObj->GetProperty("borderRadius");

    if (!color->IsUndefined() && !color->IsNull()) {
        Color BgColor;
        if (ParseJsColor(color, BgColor)) {
            indicatorStyle.backgroundColor = BgColor;
        }
    }
    if (!borderRadius->IsUndefined() && !borderRadius->IsNull()) {
        CalcDimension calcDimension;
        NG::BorderRadiusProperty borderRadiusProperty;
        if (ParseLengthMetricsToDimension(borderRadius, calcDimension)) {
            if (GreatOrEqual(calcDimension.Value(), 0.0f)) {
                indicatorStyle.borderRadius = NG::BorderRadiusProperty(calcDimension);
            }
        } else if (ParseBindSheetBorderRadiusProps(borderRadius, borderRadiusProperty)) {
            SetBorderRadiusWithCheck(indicatorStyle.borderRadius, borderRadiusProperty);
        }
    }
}

void JSContainerPicker::JSBind(BindingTarget globalObj)
{
    JSClass<JSContainerPicker>::Declare("Picker");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSContainerPicker>::StaticMethod("create", &JSContainerPicker::Create, opt);
    JSClass<JSContainerPicker>::StaticMethod("canLoop", &JSContainerPicker::SetCanLoop);
    JSClass<JSContainerPicker>::StaticMethod("enableHapticFeedback", &JSContainerPicker::SetEnableHapticFeedback);
    JSClass<JSContainerPicker>::StaticMethod("selectionIndicator", &JSContainerPicker::SetSelectionIndicator);
    JSClass<JSContainerPicker>::StaticMethod("onChange", &JSContainerPicker::OnChange);
    JSClass<JSContainerPicker>::StaticMethod("onScrollStop", &JSContainerPicker::OnScrollStop);

    JSClass<JSContainerPicker>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSContainerPicker>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSContainerPicker>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSContainerPicker>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSContainerPicker>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSContainerPicker>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSContainerPicker>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSContainerPicker>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSContainerPicker>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
