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

#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"

#include "core/components/marquee/marquee_component.h"
#include "core/components/marquee/marquee_theme.h"
#include "core/components/theme/theme_manager.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSMarquee::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("marquee create error, info is non-vaild");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto marqueeComponent = AceType::MakeRefPtr<OHOS::Ace::MarqueeComponent>();

    auto src = paramObject->GetProperty("src");
    if (!src->IsString()) {
        LOGI("src is not string");
        return;
    }
    marqueeComponent->SetValue(src->ToString());

    RefPtr<MarqueeTheme> theme = GetTheme<MarqueeTheme>();
    auto textStyle = marqueeComponent->GetTextStyle();
    textStyle.SetMaxLines(1);
    if (!theme) {
        LOGI("theme is nullptr");
        return;
    }
    textStyle.SetFontSize(theme->GetFontSize());
    textStyle.SetTextColor(theme->GetTextColor());
    marqueeComponent->SetTextStyle(std::move(textStyle));

    auto getStart = paramObject->GetProperty("start");
    bool Start = getStart->IsBoolean() ? getStart->ToBoolean() : false;
    marqueeComponent->SetPlayerStatus(Start);

    auto getStep = paramObject->GetProperty("step");
    if (!getStep->IsNumber()) {
        LOGE("marquee create error, step is non-vaild");
        return;
    }
    double Step = getStep->ToNumber<double>();
    marqueeComponent->SetScrollAmount(Step);

    auto getLoop = paramObject->GetProperty("loop");
    if (!getLoop->IsNumber()) {
        LOGE("textinput create error, type is non-vaild");
        return;
    }
    int32_t Loop = getLoop->ToNumber<int32_t>();
    marqueeComponent->SetLoop(Loop);

    auto getFromStart = paramObject->GetProperty("fromStart");
    bool FromStart = getFromStart->IsBoolean() ? getFromStart->ToBoolean() : false;
    if (FromStart) {
        marqueeComponent->SetDirection(MarqueeDirection::LEFT);
    } else {
        marqueeComponent->SetDirection(MarqueeDirection::RIGHT);
    }
    ViewStackProcessor::GetInstance()->Push(marqueeComponent);
}

void JSMarquee::JSBind(BindingTarget globalObj)
{
    JSClass<JSMarquee>::Declare("Marquee");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMarquee>::StaticMethod("create", &JSMarquee::Create, opt);
    JSClass<JSMarquee>::StaticMethod("onStart", &JSMarquee::OnStart);
    JSClass<JSMarquee>::StaticMethod("onBounce", &JSMarquee::OnBounce);
    JSClass<JSMarquee>::StaticMethod("onFinish", &JSMarquee::OnFinish);
    JSClass<JSMarquee>::Inherit<JSViewAbstract>();
    JSClass<JSMarquee>::Bind(globalObj);
}

void JSMarquee::OnStart(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&MarqueeComponent::SetOnStart, info)) {
        LOGW("Failed to bind event");
    }
    info.ReturnSelf();
}

void JSMarquee::OnBounce(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&MarqueeComponent::SetOnBounce, info)) {
        LOGW("Failed to bind event");
    }
    info.ReturnSelf();
}

void JSMarquee::OnFinish(const JSCallbackInfo& info)
{
    if (!JSViewBindEvent(&MarqueeComponent::SetOnFinish, info)) {
        LOGW("Failed to bind event");
    }
    info.ReturnSelf();
}

}
