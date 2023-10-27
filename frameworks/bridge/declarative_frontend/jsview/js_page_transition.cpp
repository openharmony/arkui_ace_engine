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

#include "frameworks/bridge/declarative_frontend/jsview/js_page_transition.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_page_transition_function.h"
#include "bridge/declarative_frontend/jsview/models/page_transition_model_impl.h"
#include "core/components_ng/pattern/stage/page_transition_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<PageTransitionModel> PageTransitionModel::instance_ = nullptr;
std::mutex PageTransitionModel::mutex_;

PageTransitionModel* PageTransitionModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::PageTransitionModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::PageTransitionModelNG());
            } else {
                instance_.reset(new Framework::PageTransitionModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSPageTransition::JSBind(BindingTarget globalObj)
{
    JSClass<JSPageTransition>::Declare("PageTransition");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPageTransition>::StaticMethod("create", &JSPageTransition::Create, opt);
    JSClass<JSPageTransition>::StaticMethod("pop", &JSPageTransition::Pop);
    JSClass<JSPageTransition>::Bind<>(globalObj);

    JSClass<JSPageTransitionEnter>::Declare("PageTransitionEnter");
    JSClass<JSPageTransitionEnter>::StaticMethod("create", &JSPageTransitionEnter::Create, opt);
    JSClass<JSPageTransitionEnter>::StaticMethod("slide", &JSPageTransition::Slide);
    JSClass<JSPageTransitionEnter>::StaticMethod("translate", &JSPageTransition::Translate);
    JSClass<JSPageTransitionEnter>::StaticMethod("scale", &JSPageTransition::Scale);
    JSClass<JSPageTransitionEnter>::StaticMethod("opacity", &JSPageTransition::Opacity);
    JSClass<JSPageTransitionEnter>::StaticMethod("onEnter", &JSPageTransition::JsHandlerOnEnter);
    JSClass<JSPageTransitionEnter>::StaticMethod("pop", &JSPageTransitionEnter::Pop);
    JSClass<JSPageTransitionEnter>::Bind<>(globalObj);

    JSClass<JSPageTransitionExit>::Declare("PageTransitionExit");
    JSClass<JSPageTransitionExit>::StaticMethod("create", &JSPageTransitionExit::Create, opt);
    JSClass<JSPageTransitionExit>::StaticMethod("slide", &JSPageTransition::Slide);
    JSClass<JSPageTransitionExit>::StaticMethod("translate", &JSPageTransition::Translate);
    JSClass<JSPageTransitionExit>::StaticMethod("scale", &JSPageTransition::Scale);
    JSClass<JSPageTransitionExit>::StaticMethod("opacity", &JSPageTransition::Opacity);
    JSClass<JSPageTransitionExit>::StaticMethod("onExit", &JSPageTransition::JsHandlerOnExit);
    JSClass<JSPageTransitionExit>::StaticMethod("pop", &JSPageTransitionExit::Pop);
    JSClass<JSPageTransitionExit>::Bind<>(globalObj);
}

void JSPageTransition::Slide(const JSCallbackInfo& info)
{
    LOGD("JSPageTransition::Slide");
    if (info.Length() > 0 && info[0]->IsNumber()) {
        auto effect = info[0]->ToNumber<int32_t>();

        if (effect >= static_cast<int32_t>(SlideEffect::LEFT) && effect <= static_cast<int32_t>(SlideEffect::BOTTOM)) {
            PageTransitionModel::GetInstance()->SetSlideEffect(static_cast<SlideEffect>(effect));
        }
    }
}

void JSPageTransition::Translate(const JSCallbackInfo& info)
{
    LOGD("JSPageTransitionTranslate");
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto args = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!args || args->IsNull()) {
            LOGE("JSTransition Translate failed json value is nullptr or json object is null");
            return;
        }

        NG::TranslateOptions option;

        CalcDimension length;
        if (JSViewAbstract::ParseJsonDimensionVp(args->GetValue("x"), length)) {
            option.x = length;
        }
        if (JSViewAbstract::ParseJsonDimensionVp(args->GetValue("y"), length)) {
            option.y = length;
        }
        if (JSViewAbstract::ParseJsonDimensionVp(args->GetValue("z"), length)) {
            option.z = length;
        }
        PageTransitionModel::GetInstance()->SetTranslateEffect(option);
    }
}

void JSPageTransition::Scale(const JSCallbackInfo& info)
{
    LOGD("JSPageTransition::Scale");
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto args = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!args || args->IsNull()) {
            LOGE("JSTransition Scale failed, json value is nullptr or json object is null");
            return;
        }

        // default: x, y, z (1.0, 1.0, 1.0)
        double scaleX = 1.0;
        double scaleY = 1.0;
        double scaleZ = 1.0;
        JSViewAbstract::ParseJsonDouble(args->GetValue("x"), scaleX);
        JSViewAbstract::ParseJsonDouble(args->GetValue("y"), scaleY);
        JSViewAbstract::ParseJsonDouble(args->GetValue("z"), scaleZ);
        // default centerX, centerY 50% 50%;
        CalcDimension centerX = 0.5_pct;
        CalcDimension centerY = 0.5_pct;

        // if specify centerX
        CalcDimension length;
        if (JSViewAbstract::ParseJsonDimensionVp(args->GetValue("centerX"), length)) {
            centerX = length;
        }
        // if specify centerY
        if (JSViewAbstract::ParseJsonDimensionVp(args->GetValue("centerY"), length)) {
            centerY = length;
        }
        NG::ScaleOptions option(
            static_cast<float>(scaleX), static_cast<float>(scaleY), static_cast<float>(scaleZ), centerX, centerY);
        PageTransitionModel::GetInstance()->SetScaleEffect(option);
    }
}

void JSPageTransition::Opacity(const JSCallbackInfo& info)
{
    LOGD("JSPageTransition::Opacity");
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    double opacity = 0.0;
    if (!JSViewAbstract::ParseJsDouble(info[0], opacity)) {
        return;
    }
    if (LessNotEqual(opacity, 0.0)) {
        opacity = 1.0;
    }
    PageTransitionModel::GetInstance()->SetOpacityEffect(static_cast<float>(opacity));
}

void JSPageTransition::JsHandlerOnEnter(const JSCallbackInfo& info)
{
    LOGD("JSPageTransition::JsHandlerOnEnter");
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("JsHandlerOnEnter info.Length < 0 or info[0] is not function");
        return;
    }

    RefPtr<JsPageTransitionFunction> function =
        AceType::MakeRefPtr<JsPageTransitionFunction>(JSRef<JSFunc>::Cast(info[0]));

    auto onEnterHandler = [execCtx = info.GetExecutionContext(), func = std::move(function)](
                              RouteType type, const float& progress) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("PageTransition.onEnter");
        func->Execute(type, progress);
    };

    PageTransitionModel::GetInstance()->SetOnEnter(std::move(onEnterHandler));
}

void JSPageTransition::JsHandlerOnExit(const JSCallbackInfo& info)
{
    LOGD("JSPageTransition::JsHandlerOnExit");
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("JsHandlerOnExit info.Length < 0 or info[0] is not function");
        return;
    }

    RefPtr<JsPageTransitionFunction> function =
        AceType::MakeRefPtr<JsPageTransitionFunction>(JSRef<JSFunc>::Cast(info[0]));

    auto onExitHandler = [execCtx = info.GetExecutionContext(), func = std::move(function)](
                             RouteType type, const float& progress) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("PageTransition.onExit");
        func->Execute(type, progress);
    };

    PageTransitionModel::GetInstance()->SetOnExit(std::move(onExitHandler));
}

void JSPageTransition::Create(const JSCallbackInfo& info)
{
    LOGD("JSPageTransition::JSTransition::Create");
    PageTransitionModel::GetInstance()->Create();
}

void JSPageTransition::Pop()
{
    LOGD("JSPageTransition::Pop");
    PageTransitionModel::GetInstance()->Pop();
}

PageTransitionOption JSPageTransition::ParseTransitionOption(const std::unique_ptr<JsonValue>& transitionArgs)
{
    PageTransitionOption option;
    const int32_t defaultDuration = 1000;
    option.duration = defaultDuration;
    option.curve = Curves::LINEAR;
    if (transitionArgs && !transitionArgs->IsNull()) {
        option.duration = transitionArgs->GetInt("duration", defaultDuration);
        if (option.duration < 0) {
            option.duration = defaultDuration;
        }
        option.delay = transitionArgs->GetInt("delay", 0);
        auto routeTypeTmp = transitionArgs->GetInt("type", static_cast<int32_t>(RouteType::NONE));
        if (routeTypeTmp >= static_cast<int32_t>(RouteType::NONE) &&
            routeTypeTmp <= static_cast<int32_t>(RouteType::POP)) {
            option.routeType = static_cast<RouteType>(routeTypeTmp);
        } else {
            LOGW("CreateTransition RouteType out of range");
        }

        auto curveArgs = transitionArgs->GetValue("curve");
        RefPtr<Curve> curve;
        if (curveArgs->IsString()) {
            curve = CreateCurve(curveArgs->GetString(), false);
        } else if (curveArgs->IsObject()) {
            auto curveString = curveArgs->GetValue("__curveString");
            if (curveString) {
                curve = CreateCurve(curveString->GetString(), false);
            }
        }
        if (curve) {
            option.curve = curve;
        }
    }
    return option;
}

void JSPageTransitionEnter::Create(const JSCallbackInfo& info)
{
    LOGD("JSPageTransitionEnter::Create");
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto transitionArgs = JsonUtil::ParseJsonString(info[0]->ToString());
        auto option = ParseTransitionOption(transitionArgs);
        PageTransitionModel::GetInstance()->CreateTransition(PageTransitionType::ENTER, option);
    }
}

void JSPageTransitionExit::Create(const JSCallbackInfo& info)
{
    LOGD("JSPageTransitionExit::Create");
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto transitionArgs = JsonUtil::ParseJsonString(info[0]->ToString());
        auto option = ParseTransitionOption(transitionArgs);
        PageTransitionModel::GetInstance()->CreateTransition(PageTransitionType::EXIT, option);
    }
}

} // namespace OHOS::Ace::Framework
