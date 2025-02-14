/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/models/text_clock_model_impl.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TextClockModel> TextClockModel::instance_ = nullptr;
std::mutex TextClockModel::mutex_;
const char TEXTCLOCK_DATE_TIME_OPTIONS_HOUR[] = "hour";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_TWO_DIGIT_VAL = "2-digit";
const std::string TEXTCLOCK_DATE_TIME_OPTIONS_NUMERIC_VAL = "numeric";

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
const std::string DEFAULT_FORMAT_API_TEN = "hms";
constexpr int32_t HOURS_WEST_LOWER_LIMIT = -14;
constexpr int32_t HOURS_WEST_UPPER_LIMIT = 12;
constexpr float HOURS_WEST[] = { 9.5f, 3.5f, -3.5f, -4.5f, -5.5f, -5.75f, -6.5f, -9.5f, -10.5f, -12.75f };

bool HoursWestIsValid(int32_t hoursWest)
{
    return !(hoursWest < HOURS_WEST_LOWER_LIMIT || hoursWest > HOURS_WEST_UPPER_LIMIT);
}

float GetHoursWest(float hoursWest)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
        for (float i : HOURS_WEST) {
            if (NearEqual(hoursWest, i)) {
                return hoursWest;
            }
        }
    }

    return int32_t(hoursWest);
}
} // namespace

void JSTextClock::Create(const JSCallbackInfo& info)
{
    auto controller = TextClockModel::GetInstance()->Create();
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> optionsObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> hourWestVal = optionsObject->GetProperty("timeZoneOffset");
    if (hourWestVal->IsNumber() && HoursWestIsValid(hourWestVal->ToNumber<int32_t>())) {
        float hourWest = GetHoursWest(hourWestVal->ToNumber<float>());
        TextClockModel::GetInstance()->SetHoursWest(hourWest);
    } else {
        TextClockModel::GetInstance()->SetHoursWest(NAN);
    }
    auto controllerObj = optionsObject->GetProperty("controller");
    if (!controllerObj->IsUndefined() && !controllerObj->IsNull() && controllerObj->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextClockController>();
        if (jsController != nullptr) {
            jsController->SetInstanceId(Container::CurrentId());
            if (controller) {
                jsController->AddController(controller);
            }
        }
        return;
    }
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
    JSClass<JSTextClock>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTextClock>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextClock>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTextClock>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextClock>::StaticMethod("fontColor", &JSTextClock::SetTextColor, opt);
    JSClass<JSTextClock>::StaticMethod("fontSize", &JSTextClock::SetFontSize, opt);
    JSClass<JSTextClock>::StaticMethod("fontWeight", &JSTextClock::SetFontWeight, opt);
    JSClass<JSTextClock>::StaticMethod("fontStyle", &JSTextClock::SetFontStyle, opt);
    JSClass<JSTextClock>::StaticMethod("fontFamily", &JSTextClock::SetFontFamily, opt);
    JSClass<JSTextClock>::StaticMethod("textShadow", &JSTextClock::SetTextShadow, opt);
    JSClass<JSTextClock>::StaticMethod("fontFeature", &JSTextClock::SetFontFeature, opt);
    JSClass<JSTextClock>::StaticMethod("dateTimeOptions", &JSTextClock::SetDateTimeOptions, opt);
    JSClass<JSTextClock>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextClock::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        TextClockModel::GetInstance()->ResetTextColor();
        return;
    }
    TextClockModel::GetInstance()->SetTextColor(textColor);
}

void JSTextClock::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension fontSize;
    if (!ParseJsDimensionFpNG(info[0], fontSize, false)) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    if (fontSize.IsNegative() || fontSize.Unit() == DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    TextClockModel::GetInstance()->SetFontSize(fontSize);
}

void JSTextClock::SetFontWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
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
        return;
    }
    TextClockModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[value]);
}

void JSTextClock::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        return;
    }
    TextClockModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSTextClock::SetFormat(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsString()) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
            TextClockModel::GetInstance()->SetFormat("");
        } else {
            TextClockModel::GetInstance()->SetFormat(DEFAULT_FORMAT_API_TEN);
        }
        return;
    }

    auto format = info[0]->ToString();
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_ELEVEN)) {
        std::regex pattern(
            R"(^([Yy]*[_|\W\s]*[M]*[_|\W\s]*[d]*[_|\W\s]*[D]*[_|\W\s]*[Hh]*[_|\W\s]*[m]*[_|\W\s]*[s]*[_|\W\s]*[S]*)$)");
        if (format.empty() || !StringUtils::IsAscii(format) || !std::regex_match(format, pattern)) {
            TextClockModel::GetInstance()->SetFormat(DEFAULT_FORMAT_API_TEN);
            return;
        }
    }

    TextClockModel::GetInstance()->SetFormat(format);
}

void JSTextClock::SetTextShadow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<Shadow> shadows;
    ParseTextShadowFromShadowObject(info[0], shadows);
    if (!shadows.empty()) {
        TextClockModel::GetInstance()->SetTextShadow(shadows);
    }
}

void JSTextClock::SetFontFeature(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsString()) {
        return;
    }

    std::string fontFeatureSettings = info[0]->ToString();
    TextClockModel::GetInstance()->SetFontFeature(ParseFontFeatureSettings(fontFeatureSettings));
}

void JSTextClock::JsOnDateChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextClock.onDateChange");
        PipelineContext::SetCallBackNode(node);
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
    ContainerScope scope(instanceId_);
    if (!controller_.empty()) {
        for (auto& i : controller_) {
            i->Start();
        }
    }
}

void JSTextClockController::Stop()
{
    ContainerScope scope(instanceId_);
    if (!controller_.empty()) {
        for (auto& i : controller_) {
            i->Stop();
        }
    }
}

void JSTextClockController::removeController(const RefPtr<TextClockController>& controller)
{
    for (auto it = controller_.begin(); it != controller_.end(); it++) {
        if (controller == *it) {
            controller_.erase(it);
            break;
        }
    }
}

void JSTextClock::SetDateTimeOptions(const JSCallbackInfo& info)
{
    JSRef<JSObject> paramObject;
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    if (info.Length() >= 1 && info[0]->IsObject()) {
        paramObject = JSRef<JSObject>::Cast(info[0]);
        auto hourValue = paramObject->GetProperty(TEXTCLOCK_DATE_TIME_OPTIONS_HOUR);
        if (hourValue->IsString()) {
            std::string hour = hourValue->ToString();
            if (hour == TEXTCLOCK_DATE_TIME_OPTIONS_TWO_DIGIT_VAL) {
                hourType = ZeroPrefixType::SHOW;
            } else if (hour == TEXTCLOCK_DATE_TIME_OPTIONS_NUMERIC_VAL) {
                hourType = ZeroPrefixType::HIDE;
            }
        }
    }
    TextClockModel::GetInstance()->SetDateTimeOptions(hourType);
}
} // namespace OHOS::Ace::Framework
