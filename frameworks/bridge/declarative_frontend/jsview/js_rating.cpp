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

#include "frameworks/bridge/declarative_frontend/jsview/js_rating.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/models/rating_model_impl.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<RatingModel> RatingModel::instance_ = nullptr;

RatingModel* RatingModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::RatingModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::RatingModelNG());
        } else {
            instance_.reset(new Framework::RatingModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSRating::Create(const JSCallbackInfo& info)
{
    double rating = 0;
    bool indicator = false;
    if (info.Length() >= 1 && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto getRating = paramObject->GetProperty("rating");
        auto getIndicator = paramObject->GetProperty("indicator");
        if (getRating->IsNumber()) {
            rating = getRating->ToNumber<double>();
        } else {
            LOGE("create rating fail because the rating is not value");
        }
        if (getIndicator->IsBoolean()) {
            indicator = getIndicator->ToBoolean();
        } else {
            LOGE("create rating fail because the indicator is not value");
        }
    }
    RatingModel::GetInstance()->Create();
    RatingModel::GetInstance()->SetRatingScore(rating);
    RatingModel::GetInstance()->SetIndicator(indicator);
}

void JSRating::SetStars(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("the arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not number.");
        return;
    }

    RatingModel::GetInstance()->SetStars(info[0]->ToNumber<int32_t>());
}

void JSRating::SetStepSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("the arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!info[0]->IsNumber()) {
        LOGE("arg is not number.");
        return;
    }

    RatingModel::GetInstance()->SetStepSize(info[0]->ToNumber<double>());
}

void JSRating::SetStarStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("the arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getBackgroundUri = paramObject->GetProperty("backgroundUri");
    auto getForegroundUri = paramObject->GetProperty("foregroundUri");
    auto getSecondaryUri = paramObject->GetProperty("secondaryUri");
    std::string backgroundUri;
    std::string foregroundUri;
    std::string secondaryUri;
    if (getBackgroundUri->IsString()) {
        backgroundUri = getBackgroundUri->ToString();
    } else {
        LOGE("backgroundUri error , because the backgroundUri is not string");
    }

    if (getForegroundUri->IsString()) {
        foregroundUri = getForegroundUri->ToString();
    } else {
        LOGE("foregroundUri error , because the foregroundUri is not string");
    }

    if (getSecondaryUri->IsString()) {
        secondaryUri = getSecondaryUri->ToString();
    } else {
        secondaryUri = backgroundUri;
    }

    RatingModel::GetInstance()->SetForegroundSrc(foregroundUri);
    RatingModel::GetInstance()->SetSecondarySrc(secondaryUri);
    RatingModel::GetInstance()->SetBackgroundSrc(backgroundUri);
}

void JSRating::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("failed to bind onChange Event to Rating due to it is not a function");
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Rating.onChange");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(stod(value)));
        func->ExecuteJS(1, &newJSVal);
    };

    RatingModel::GetInstance()->SetOnChange(onChange);
}

void JSRating::JSBind(BindingTarget globalObj)
{
    JSClass<JSRating>::Declare("Rating");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRating>::StaticMethod("create", &JSRating::Create, opt);
    JSClass<JSRating>::StaticMethod("stars", &JSRating::SetStars, opt);
    JSClass<JSRating>::StaticMethod("stepSize", &JSRating::SetStepSize, opt);
    JSClass<JSRating>::StaticMethod("starStyle", &JSRating::SetStarStyle, opt);
    JSClass<JSRating>::StaticMethod("onChange", &JSRating::SetOnChange);
    JSClass<JSRating>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRating>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRating>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRating>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRating>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRating>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRating>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRating>::Inherit<JSViewAbstract>();
    JSClass<JSRating>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework