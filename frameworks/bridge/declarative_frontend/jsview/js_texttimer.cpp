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

#include "frameworks/bridge/declarative_frontend/jsview/js_texttimer.h"

#include <regex>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/text_timer_model_impl.h"
#include "core/components/common/layout/constants.h"
#include "core/components/declaration/texttimer/texttimer_declaration.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/texttimer/text_timer_model.h"
#include "core/components_ng/pattern/texttimer/text_timer_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TextTimerModel> TextTimerModel::instance_ = nullptr;
std::mutex TextTimerModel::mutex_;

TextTimerModel* TextTimerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TextTimerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TextTimerModelNG());
            } else {
                instance_.reset(new Framework::TextTimerModelImpl());
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
const std::string DEFAULT_FORMAT = "HH:mm:ss.SS";
constexpr double MAX_COUNT_DOWN = 86400000.0;
} // namespace

void JSTextTimer::Create(const JSCallbackInfo& info)
{
    auto controller = TextTimerModel::GetInstance()->Create();
    if (info.Length() < 1 || !info[0]->IsObject()) {
        SetFontDefault();
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto tempIsCountDown = paramObject->GetProperty("isCountDown");
    if (tempIsCountDown->IsBoolean()) {
        bool isCountDown = tempIsCountDown->ToBoolean();
        TextTimerModel::GetInstance()->SetIsCountDown(isCountDown);
        if (isCountDown) {
            auto count = paramObject->GetProperty("count");
            if (count->IsNumber()) {
                auto inputCount = count->ToNumber<double>();
                if (inputCount > 0 && inputCount < MAX_COUNT_DOWN) {
                    TextTimerModel::GetInstance()->SetInputCount(inputCount);
                } else {
                    TextTimerModel::GetInstance()->SetInputCount(TIME_DEFAULT_COUNT);
                }
            }
            if (count->IsUndefined() || count->IsNull()) {
                TextTimerModel::GetInstance()->SetInputCount(TIME_DEFAULT_COUNT);
            }
        }
    }

    auto controllerObj = paramObject->GetProperty("controller");
    if (controllerObj->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSTextTimerController>();
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            jsController->SetController(controller);
        }
    }
}

void JSTextTimer::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextTimer>::Declare("TextTimer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSTextTimer>::StaticMethod("create", &JSTextTimer::Create, opt);
    JSClass<JSTextTimer>::StaticMethod("format", &JSTextTimer::SetFormat);
    JSClass<JSTextTimer>::StaticMethod("fontColor", &JSTextTimer::SetTextColor);
    JSClass<JSTextTimer>::StaticMethod("fontSize", &JSTextTimer::SetFontSize);
    JSClass<JSTextTimer>::StaticMethod("fontWeight", &JSTextTimer::SetFontWeight, opt);
    JSClass<JSTextTimer>::StaticMethod("fontStyle", &JSTextTimer::SetFontStyle, opt);
    JSClass<JSTextTimer>::StaticMethod("fontFamily", &JSTextTimer::SetFontFamily, opt);
    JSClass<JSTextTimer>::StaticMethod("onTimer", &JSTextTimer::OnTimer);
    JSClass<JSTextTimer>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTextTimer>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTextTimer>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTextTimer>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTextTimer>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTextTimer>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTextTimer>::StaticMethod("textShadow", &JSTextTimer::SetTextShadow, opt);
    JSClass<JSTextTimer>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSTextTimer::SetFontDefault()
{
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    TextTimerModel::GetInstance()->SetFontSize(textTheme->GetTextStyle().GetFontSize());
    TextTimerModel::GetInstance()->SetTextColor(textTheme->GetTextStyle().GetTextColor());
    TextTimerModel::GetInstance()->SetFontFamily(textTheme->GetTextStyle().GetFontFamilies());
    TextTimerModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    TextTimerModel::GetInstance()->SetItalicFontStyle(textTheme->GetTextStyle().GetFontStyle());
}

void JSTextTimer::SetFormat(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsString()) {
        TextTimerModel::GetInstance()->SetFormat(DEFAULT_FORMAT);
        return;
    }

    auto format = info[0]->ToString();
    std::smatch result;
    std::regex pattern("(([YyMdD]+))");
    if (std::regex_search(format, result, pattern)) {
        if (!result.empty()) {
            format = DEFAULT_FORMAT;
        }
    }

    std::string target = "HmsS:.";
    for (auto ch : format) {
        if (target.find(ch) == std::string::npos) {
            format = DEFAULT_FORMAT;
        }
    }

    auto pos = format.find("hh");
    if (pos != std::string::npos) {
        format.replace(pos, sizeof("hh") - 1, "HH");
    }

    TextTimerModel::GetInstance()->SetFormat(format);
}

void JSTextTimer::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    if (fontSize.IsNegative() || fontSize.Unit() == DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    TextTimerModel::GetInstance()->SetFontSize(fontSize);
}

void JSTextTimer::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        textColor = theme->GetTextStyle().GetTextColor();
    }

    TextTimerModel::GetInstance()->SetTextColor(textColor);
}

void JSTextTimer::SetTextShadow(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<Shadow> shadows;
    ParseTextShadowFromShadowObject(info[0], shadows);
    if (!shadows.empty()) {
        TextTimerModel::GetInstance()->SetTextShadow(shadows);
    }
}

void JSTextTimer::SetFontWeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    RefPtr<TextTheme> textTheme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    auto fontWeight = info[0];
    if (fontWeight->IsUndefined()) {
        TextTimerModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
        return;
    }

    if (!fontWeight->IsNull()) {
        std::string weight;
        if (fontWeight->IsNumber()) {
            weight = std::to_string(fontWeight->ToNumber<int32_t>());
        } else {
            ParseJsString(fontWeight, weight);
        }
        TextTimerModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(weight));
    } else {
        TextTimerModel::GetInstance()->SetFontWeight(textTheme->GetTextStyle().GetFontWeight());
    }
}

void JSTextTimer::SetFontStyle(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
        return;
    }
    TextTimerModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[value]);
}

void JSTextTimer::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        return;
    }
    TextTimerModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSTextTimer::OnTimer(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        int64_t utc, int64_t elapsedTime) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("TextTimer.onTimer");
        PipelineContext::SetCallBackNode(node);
        JSRef<JSVal> newJSVal[2];
        newJSVal[0] = JSRef<JSVal>::Make(ToJSValue(utc));
        newJSVal[1] = JSRef<JSVal>::Make(ToJSValue(elapsedTime));
        func->ExecuteJS(2, newJSVal);
    };
    TextTimerModel::GetInstance()->SetOnTimer(std::move(onChange));
}

void JSTextTimerController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextTimerController>::Declare("TextTimerController");
    JSClass<JSTextTimerController>::CustomMethod("start", &JSTextTimerController::Start);
    JSClass<JSTextTimerController>::CustomMethod("pause", &JSTextTimerController::Pause);
    JSClass<JSTextTimerController>::CustomMethod("reset", &JSTextTimerController::Reset);
    JSClass<JSTextTimerController>::Bind(
        globalObj, JSTextTimerController::Constructor, JSTextTimerController::Destructor);
}

void JSTextTimerController::Constructor(const JSCallbackInfo& info)
{
    auto timerController = Referenced::MakeRefPtr<JSTextTimerController>();
    timerController->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(timerController));
}

void JSTextTimerController::Destructor(JSTextTimerController* timerController)
{
    if (timerController != nullptr) {
        timerController->DecRefCount();
    }
}

void JSTextTimerController::Start(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->Start();
    }
}

void JSTextTimerController::Pause(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->Pause();
    }
}

void JSTextTimerController::Reset(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->Reset();
    }
}
} // namespace OHOS::Ace::Framework
