/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_text_clock.h"

#include <regex>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "base/utils/string_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/text_clock_model_impl.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TextClockModel> TextClockModel::instance_ = nullptr;
std::mutex TextClockModel::mutex_;

TextClockModel* TextClockModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TextClockModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TextClockModelNG());
            } else {
                instance_.reset(new Framework::TextClockModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const int32_t TWENTY_FOUR_HOUR_BASE = 24;
const std::string DEFAULT_FORMAT = "hms";
constexpr int32_t HOURS_WEST_LOWER_LIMIT = -14;
constexpr int32_t HOURS_WEST_UPPER_LIMIT = 12;
constexpr int32_t HOURS_WEST_GEOGRAPHICAL_LOWER_LIMIT = -12;

bool HoursWestIsValid(int32_t hoursWest)
{
    if (hoursWest < HOURS_WEST_LOWER_LIMIT || hoursWest > HOURS_WEST_UPPER_LIMIT) {
        return false;
    }
    if (hoursWest < HOURS_WEST_GEOGRAPHICAL_LOWER_LIMIT) {
        hoursWest += TWENTY_FOUR_HOUR_BASE;
    }
    return true;
}
} // namespace

void JSTextClock::Create(const JSCallbackInfo& info)
{
    auto controller = TextClockModel::GetInstance()->Create();
    if (info.Length() < 1 || !info[0]->IsObject()) {
        SetFontDefault();
        LOGD("TextClock Info is non-valid");
        return;
    }
    JSRef<JSObject> optionsObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> hourWestVal = optionsObject->GetProperty("timeZoneOffset");
    if (hourWestVal->IsNumber() && HoursWestIsValid(hourWestVal->ToNumber<int32_t>())) {
        TextClockModel::GetInstance()->SetHoursWest(hourWestVal->ToNumber<int32_t>());
    } else {
        TextClockModel::GetInstance()->SetHoursWest(INT_MAX);
        LOGE("hourWest args is invalid");
    }
    auto controllerObj = optionsObject->GetProperty("controller");
    if (!controllerObj->IsUndefined() && !controllerObj->IsNull() && controllerObj->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextClockController>();
        if (jsController != nullptr) {
            if (controller) {
                jsController->AddController(controller);
            } else {
                LOGE("TextClockController is nullptr");
            }
        }
        return;
    }
    LOGE("controllerObj is nullptr or undefined or invalid");
}

void JSTextClock::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextClock>::Declare("TextClock");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextClock>::StaticMethod("create", &JSTextClock::Create, opt);
    JSClass<JSTextClock>::StaticMethod("format", &JSTextClock::SetFormat, opt);
    JSClass<JSTextClock>::StaticMethod("onDateChange", &JSTextClock::JsOnDateChange, opt);
    JSClass<JSTextClock>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTextClock>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextClock>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTextClock>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTextClock>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextClock>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextClock>::StaticMethod("fontColor", &JSTextClock::SetTextColor, opt);
    JSClass<JSTextClock>::StaticMethod("fontSize", &JSTextClock::SetFontSize, opt);
    JSClass<JSTextClock>::StaticMethod("fontWeight", &JSTextClock::SetFontWeight, opt);
    JSClass<JSTextClock>::StaticMethod("fontStyle", &JSTextClock::SetFontStyle, opt);
    JSClass<JSTextClock>::StaticMethod("fontFamily", &JSTextClock::SetFontFamily, opt);
    JSClass<JSTextClock>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextClock::SetFontDefault()
{
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    TextClockModel::GetInstance()->SetFontSize(textTheme->GetTextStyle().GetFontSize());
    TextClockModel::GetInstance()->SetTextColor(textTheme->GetTextStyle().GetTextColor());
    TextClockModel::GetInstance()->SetFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    TextClockModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    TextClockModel::GetInstance()->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
}

void JSTextClock::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        textColor = theme->GetTextStyle().GetTextColor();
    }

    TextClockModel::GetInstance()->SetTextColor(textColor);
}

void JSTextClock::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("JSTextInput::SetFontSize The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID_NOLOG(theme);

    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    if (fontSize.IsNegative() || fontSize.Unit() == DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID_NOLOG(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID_NOLOG(theme);
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    TextClockModel::GetInstance()->SetFontSize(fontSize);
}

void JSTextClock::SetFontWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    const auto& fontWeight = info[0];
    if (fontWeight->IsUndefined()) {
        TextClockModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
        return;
    }

    if (!fontWeight->IsNull()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        TextClockModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
    } else {
        TextClockModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    }
}

void JSTextClock::SetFontStyle(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
        LOGE("TextTimer fontStyle(%{public}d) illegal value", value);
        return;
    }
    TextClockModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[value]);
}

void JSTextClock::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }
    TextClockModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSTextClock::SetFormat(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    if (!info[0]->IsString()) {
        LOGE("The arg is not string,it is supposed to be a string.");
        TextClockModel::GetInstance()->SetFormat(DEFAULT_FORMAT);
        return;
    }

    std::string value;
    auto format = info[0]->ToString();
    if (format.length() == 0) {
        format = DEFAULT_FORMAT;
        TextClockModel::GetInstance()->SetFormat(format);
        return;
    }

    if (!ParseJsString(info[0], value)) {
        return;
    }
    TextClockModel::GetInstance()->SetFormat(value);
}

void JSTextClock::JsOnDateChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextClock.onDateChange");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(1, &newJSVal);
    };
    TextClockModel::GetInstance()->SetOnDateChange(std::move(onChange));
}

void JSTextClockController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextClockController>::Declare("TextClockController");
    JSClass<JSTextClockController>::Method("start", &JSTextClockController::Start);
    JSClass<JSTextClockController>::Method("stop", &JSTextClockController::Stop);
    JSClass<JSTextClockController>::Bind(
        globalObj, JSTextClockController::Constructor, JSTextClockController::Destructor);
}

void JSTextClockController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSTextClockController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSTextClockController::Destructor(JSTextClockController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSTextClockController::Start()
{
    if (!controller_.empty()) {
        for (auto& i : controller_) {
            i->Start();
        }
    }
}

void JSTextClockController::Stop()
{
    if (!controller_.empty()) {
        for (auto& i : controller_) {
            i->Stop();
        }
    }
}
} // namespace OHOS::Ace::Framework
