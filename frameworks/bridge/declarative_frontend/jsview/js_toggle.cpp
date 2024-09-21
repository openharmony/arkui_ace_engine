/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_toggle.h"

#include <cstddef>
#include <string>
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_button.h"
#include "bridge/declarative_frontend/jsview/models/toggle_model_impl.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_toggle_theme.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ToggleModel> ToggleModel::instance_ = nullptr;
std::mutex ToggleModel::mutex_;

ToggleModel* ToggleModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ToggleModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ToggleModelNG());
            } else {
                instance_.reset(new Framework::ToggleModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
int32_t JSToggle::toggleType_ = 1;
void JSToggle::JSBind(BindingTarget globalObj)
{
    JSClass<JSToggle>::Declare("Toggle");
    JSClass<JSToggle>::StaticMethod("create", &JSToggle::Create);
    JSClass<JSToggle>::StaticMethod("onChange", &JSToggle::OnChange);
    JSClass<JSToggle>::StaticMethod("selectedColor", &JSToggle::SelectedColor);
    JSClass<JSToggle>::StaticMethod("width", &JSToggle::JsWidth);
    JSClass<JSToggle>::StaticMethod("height", &JSToggle::JsHeight);
    JSClass<JSToggle>::StaticMethod("responseRegion", &JSToggle::JsResponseRegion);
    JSClass<JSToggle>::StaticMethod("size", &JSToggle::JsSize);
    JSClass<JSToggle>::StaticMethod("padding", &JSToggle::JsPadding);
    JSClass<JSToggle>::StaticMethod("pop", &JSToggle::Pop);
    JSClass<JSToggle>::StaticMethod("switchPointColor", &JSToggle::SwitchPointColor);
    JSClass<JSToggle>::StaticMethod("backgroundColor", &JSToggle::SetBackgroundColor);
    JSClass<JSToggle>::StaticMethod("hoverEffect", &JSToggle::JsHoverEffect);
    JSClass<JSToggle>::StaticMethod("switchStyle", &JSToggle::SwitchStyle);
    JSClass<JSToggle>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSToggle>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSToggle>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSToggle>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSToggle>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSToggle>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSToggle>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSToggle>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSToggle>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSToggle>::StaticMethod("borderRadius", &JSToggle::JsRadius);
    JSClass<JSToggle>::InheritAndBind<JSViewAbstract>(globalObj);
}

void ParseToggleIsOnObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChangeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                             bool isOn) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Toggle.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isOn));
        func->ExecuteJS(1, &newJSVal);
    };
    ToggleModel::GetInstance()->OnChangeEvent(std::move(onChangeEvent));
}

void JSToggle::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto type = paramObject->GetProperty("type");
    int32_t toggleTypeInt = 1;
    if (type->IsNumber()) {
        toggleTypeInt = type->ToNumber<int32_t>();
    }
    if (toggleTypeInt < 0 || toggleTypeInt > 2) {
        toggleTypeInt = 1;
    }
    toggleType_ = toggleTypeInt;
    auto tempIsOn = paramObject->GetProperty("isOn");
    bool isOn = false;
    JSRef<JSVal> changeEventVal;
    if (tempIsOn->IsObject()) {
        JSRef<JSObject> isOnObj = JSRef<JSObject>::Cast(tempIsOn);
        changeEventVal = isOnObj->GetProperty("changeEvent");
        auto isOnProperty = isOnObj->GetProperty("value");
        isOn = isOnProperty->IsBoolean() ? isOnProperty->ToBoolean() : false;
    } else {
        isOn = tempIsOn->IsBoolean() ? tempIsOn->ToBoolean() : false;
    }
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "toggle create type %{public}d isOn %{public}d", toggleTypeInt, isOn);
    ToggleModel::GetInstance()->Create(NG::ToggleType(toggleTypeInt), isOn);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseToggleIsOnObject(info, changeEventVal);
    }
    JSToggleTheme::ApplyTheme(NG::ToggleType(toggleType_));
}

void JSToggle::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        JSViewAbstract::JsWidth(info[0]);
        return;
    }
    JsWidth(info[0]);
}

void JSToggle::JsWidth(const JSRef<JSVal>& jsValue)
{
    auto switchTheme = GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    auto defaultWidth = switchTheme->GetWidth();
    auto horizontalPadding = switchTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    if (toggleType_ == 0) {
        auto checkboxTheme = GetTheme<CheckboxTheme>();
        CHECK_NULL_VOID(checkboxTheme);
        defaultWidth = checkboxTheme->GetDefaultWidth();
        horizontalPadding = checkboxTheme->GetHotZoneHorizontalPadding();
        width = defaultWidth - horizontalPadding * 2;
    }
    CalcDimension value(width);
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        value = width;
    }
    ToggleModel::GetInstance()->SetWidth(value);
}

void JSToggle::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        JSViewAbstract::JsHeight(info[0]);
        return;
    }
    JsHeight(info[0]);
}

void JSToggle::JsHeight(const JSRef<JSVal>& jsValue)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    auto defaultHeight = switchTheme->GetHeight();
    auto verticalPadding = switchTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;
    CalcDimension value(height);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(jsValue, value) || value.IsNegative()) {
            value = height;
        }
    } else {
        ParseJsDimensionVp(jsValue, value);
        if (value.IsNegative()) {
            value = height;
        }
    }
    ToggleModel::GetInstance()->SetHeight(value);
}

void JSToggle::JsResponseRegion(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsResponseRegion(info);
        return;
    }
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        return;
    }
    ToggleModel::GetInstance()->SetResponseRegion(result);
}

void JSToggle::JsSize(const JSCallbackInfo& info)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        JSViewAbstract::JsSize(info);
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSToggle::OnChange(const JSCallbackInfo& args)
{
    auto jsVal = args[0];
    if (!jsVal->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(jsVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](bool isOn) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Toggle.onChange");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(isOn));
        func->ExecuteJS(1, &newJSVal);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "Toggle.onChange");
#endif
    };
    ToggleModel::GetInstance()->OnChange(std::move(onChange));
    args.ReturnSelf();
}

void JSToggle::SelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color color;
    std::optional<Color> selectedColor;
    if (ParseJsColor(info[0], color)) {
        selectedColor = color;
    }

    ToggleModel::GetInstance()->SetSelectedColor(selectedColor);
}

void JSToggle::SwitchPointColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color color;
    if (!ParseJsColor(info[0], color)) {
        auto theme = GetTheme<SwitchTheme>();
        if (theme) {
            color = theme->GetPointColor();
        }
    }

    ToggleModel::GetInstance()->SetSwitchPointColor(color);
}

void JSToggle::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    NG::PaddingPropertyF oldPadding = GetOldPadding(info);
    NG::PaddingProperty newPadding = GetNewPadding(info);
    ToggleModel::GetInstance()->SetPadding(oldPadding, newPadding);
}

NG::PaddingPropertyF JSToggle::GetOldPadding(const JSCallbackInfo& info)
{
    NG::PaddingPropertyF padding({ 0.0f, 0.0f, 0.0f, 0.0f });
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->HasProperty("top") || jsObj->HasProperty("bottom")
            || jsObj->HasProperty("left") || jsObj->HasProperty("right")) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ParseJsDimensionVp(jsObj->GetProperty("top"), topDimen);
            ParseJsDimensionVp(jsObj->GetProperty("left"), leftDimen);
            ParseJsDimensionVp(jsObj->GetProperty("right"), rightDimen);
            ParseJsDimensionVp(jsObj->GetProperty("bottom"), bottomDimen);
            if (leftDimen == 0.0_vp) {
                leftDimen = rightDimen;
            }
            if (topDimen == 0.0_vp) {
                topDimen = bottomDimen;
            }
            if (leftDimen == 0.0_vp) {
                leftDimen = topDimen;
            }

            padding.left = leftDimen.ConvertToPx();
            padding.right = rightDimen.ConvertToPx();
            padding.top = topDimen.ConvertToPx();
            padding.bottom = bottomDimen.ConvertToPx();
            return padding;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        return padding;
    }

    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

NG::PaddingProperty JSToggle::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding({
        NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp)
    });
    if (info[0]->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        CommonCalcDimension commonCalcDimension;
        ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = GetPadding(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
            return padding;
        }
    }
    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        length.Reset();
    }

    padding.SetEdges(NG::CalcLength(length.IsNonNegative() ? length : CalcDimension()));
    return padding;
}

NG::PaddingProperty JSToggle::GetPadding(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty padding({
        NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp)
    });
    if (left.has_value() && left.value().IsNonNegative()) {
        padding.left = NG::CalcLength(left.value());
    }
    if (right.has_value() && right.value().IsNonNegative()) {
        padding.right = NG::CalcLength(right.value());
    }
    if (top.has_value() && top.value().IsNonNegative()) {
        padding.top = NG::CalcLength(top.value());
    }
    if (bottom.has_value() && bottom.value().IsNonNegative()) {
        padding.bottom = NG::CalcLength(bottom.value());
    }
    return padding;
}

void JSToggle::SetBackgroundColor(const JSCallbackInfo& info)
{
    Color backgroundColor = Color::TRANSPARENT;
    bool flag = ParseJsColor(info[0], backgroundColor);
    if (!Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsBackgroundColor(info);
        return;
    }
    ToggleModel::GetInstance()->SetBackgroundColor(backgroundColor, flag);
}

void JSToggle::JsHoverEffect(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsNumber()) {
        ToggleModel::GetInstance()->SetHoverEffect(static_cast<HoverEffectType>(info[0]->ToNumber<int32_t>()));
    }
}

void JSToggle::Pop()
{
    ToggleModel::GetInstance()->Pop();
}

void JSToggle::SwitchStyle(const JSCallbackInfo& info)
{
    if ((info.Length() < 1) || !info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);

    CalcDimension pointRadius;
    if (jsObj->HasProperty("pointRadius") &&
        ParseJsDimensionVpNG(jsObj->GetProperty("pointRadius"), pointRadius, false) && !pointRadius.IsNegative()) {
        ToggleModel::GetInstance()->SetPointRadius(pointRadius);
    } else {
        ToggleModel::GetInstance()->ResetPointRadius();
    }

    Color unselectedColor;
    if (jsObj->HasProperty("unselectedColor") &&
        ParseJsColor(jsObj->GetProperty("unselectedColor"), unselectedColor)) {
        ToggleModel::GetInstance()->SetUnselectedColor(unselectedColor);
    } else {
        auto theme = GetTheme<SwitchTheme>();
        if (theme) {
            unselectedColor = theme->GetInactiveColor();
        }
        ToggleModel::GetInstance()->SetUnselectedColor(unselectedColor);
    }

    Color pointColor;
    if (jsObj->HasProperty("pointColor") && ParseJsColor(jsObj->GetProperty("pointColor"), pointColor)) {
        ToggleModel::GetInstance()->SetSwitchPointColor(pointColor);
    } else {
        auto theme = GetTheme<SwitchTheme>();
        if (theme) {
            pointColor = theme->GetPointColor();
        }
        ToggleModel::GetInstance()->SetSwitchPointColor(pointColor);
    }

    CalcDimension trackRadius;
    if (jsObj->HasProperty("trackBorderRadius") &&
        ParseJsDimensionVpNG(jsObj->GetProperty("trackBorderRadius"), trackRadius, false) &&
        !trackRadius.IsNegative()) {
        ToggleModel::GetInstance()->SetTrackBorderRadius(trackRadius);
    } else {
        ToggleModel::GetInstance()->ResetTrackBorderRadius();
    }
}

void JSToggle::JsRadius(const JSCallbackInfo& info)
{
    CalcDimension radius;
    // when toggle equels button should follow button model.
    if (static_cast<NG::ToggleType>(toggleType_) == NG::ToggleType::BUTTON) {
        JSButton::JsRadius(info);
    } else {
        JSViewAbstract::JsBorderRadius(info);
    }
}
} // namespace OHOS::Ace::Framework
