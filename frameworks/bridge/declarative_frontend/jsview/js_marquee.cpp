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

#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/marquee_model_impl.h"
#include "core/components_ng/pattern/marquee/marquee_model.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<MarqueeModel> MarqueeModel::instance_ = nullptr;

MarqueeModel* MarqueeModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::MarqueeModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::MarqueeModelNG());
        } else {
            instance_.reset(new Framework::MarqueeModelImpl());
        }
#endif
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSMarquee::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("marquee create error, info is non-valid");
        return;
    }

    MarqueeModel::GetInstance()->Create();
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto src = paramObject->GetProperty("src");
    if (!src->IsString()) {
        LOGE("marquee create error, src is non-valid");
        return;
    }
    MarqueeModel::GetInstance()->SetValue(src->ToString());

    auto getStart = paramObject->GetProperty("start");
    bool start = getStart->IsBoolean() ? getStart->ToBoolean() : false;
    MarqueeModel::GetInstance()->SetPlayerStatus(start);

    auto getStep = paramObject->GetProperty("step");
    if (getStep->IsNumber()) {
        MarqueeModel::GetInstance()->SetScrollAmount(getStep->ToNumber<double>());
    }

    auto getLoop = paramObject->GetProperty("loop");
    if (getLoop->IsNumber()) {
        MarqueeModel::GetInstance()->SetLoop(getLoop->ToNumber<int32_t>());
    }

    auto getFromStart = paramObject->GetProperty("fromStart");
    bool fromStart = getFromStart->IsBoolean() ? getFromStart->ToBoolean() : true;
    if (fromStart) {
        MarqueeModel::GetInstance()->SetDirection(MarqueeDirection::LEFT);
    } else {
        MarqueeModel::GetInstance()->SetDirection(MarqueeDirection::RIGHT);
    }
}

void JSMarquee::JSBind(BindingTarget globalObj)
{
    JSClass<JSMarquee>::Declare("Marquee");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMarquee>::StaticMethod("create", &JSMarquee::Create, opt);
    JSClass<JSMarquee>::StaticMethod("allowScale", &JSMarquee::SetAllowScale);
    JSClass<JSMarquee>::StaticMethod("fontColor", &JSMarquee::SetTextColor);
    JSClass<JSMarquee>::StaticMethod("fontSize", &JSMarquee::SetFontSize);
    JSClass<JSMarquee>::StaticMethod("fontWeight", &JSMarquee::SetFontWeight);
    JSClass<JSMarquee>::StaticMethod("fontFamily", &JSMarquee::SetFontFamily);
    JSClass<JSMarquee>::StaticMethod("onStart", &JSMarquee::OnStart);
    JSClass<JSMarquee>::StaticMethod("onBounce", &JSMarquee::OnBounce);
    JSClass<JSMarquee>::StaticMethod("onFinish", &JSMarquee::OnFinish);
    JSClass<JSMarquee>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSMarquee>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMarquee>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSMarquee>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSMarquee>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMarquee>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMarquee>::Inherit<JSViewAbstract>();
    JSClass<JSMarquee>::Bind(globalObj);
}

void JSMarquee::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("SetTextColor create error, info is non-valid");
        return;
    }

    Color color;
    if (!ParseJsColor(info[0], color)) {
        LOGE("the info[0] is null");
        return;
    }
    MarqueeModel::GetInstance()->SetTextColor(color);
}

void JSMarquee::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("SetFrontSize create error, info is non-valid");
        return;
    }

    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    MarqueeModel::GetInstance()->SetFontSize(fontSize);
}

void JSMarquee::SetAllowScale(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsBoolean()) {
        LOGE("SetAllowScale create error, info is non-valid");
        return;
    }
    MarqueeModel::GetInstance()->SetAllowScale(info[0]->ToBoolean());
}

void JSMarquee::SetFontWeight(const std::string& value)
{
    MarqueeModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSMarquee::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("SetFrontFamily create error, info is non-valid");
        return;
    }

    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }
    MarqueeModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSMarquee::OnStart(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Marquee.onStart");
        func->ExecuteJS();
    };
    MarqueeModel::GetInstance()->SetOnStart(std::move(onChange));
}

void JSMarquee::OnBounce(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Marquee.onBounce");
        func->ExecuteJS();
    };
    MarqueeModel::GetInstance()->SetOnBounce(std::move(onChange));
}

void JSMarquee::OnFinish(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Marquee.onFinish");
        func->ExecuteJS();
    };
    MarqueeModel::GetInstance()->SetOnFinish(std::move(onChange));
}

} // namespace OHOS::Ace::Framework
