/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"

namespace OHOS::Ace {

RatingModel* RatingModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::RatingModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::RatingModelNG instance;
        return &instance;
    } else {
        static Framework::RatingModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr double RATING_SCORE_DEFAULT = 0;
constexpr int32_t STARS_DEFAULT = 5;
constexpr double STEPS_DEFAULT = 0.5;
} // namespace

void ParseRatingObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChangeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                             const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Rating.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(stod(value)));
        func->ExecuteJS(1, &newJSVal);
    };
    RatingModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSRating::Create(const JSCallbackInfo& info)
{
    double rating = RATING_SCORE_DEFAULT;
    bool indicator = false;
    JSRef<JSVal> changeEventVal;
    if (info.Length() >= 1 && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto getRating = paramObject->GetProperty("rating");
        auto getIndicator = paramObject->GetProperty("indicator");
        if (getRating->IsObject()) {
            JSRef<JSObject> ratingObj = JSRef<JSObject>::Cast(getRating);
            changeEventVal = ratingObj->GetProperty("changeEvent");
            auto ratingValue = ratingObj->GetProperty("value");
            if (ratingValue->IsNumber()) {
                rating = ratingValue->ToNumber<double>();
            }
        } else if (paramObject->HasProperty("$rating")) {
            changeEventVal = paramObject->GetProperty("$rating");
            rating = getRating->ToNumber<double>();
        } else if (getRating->IsNumber()) {
            rating = getRating->ToNumber<double>();
        }
        if (rating < 0) {
            rating = RATING_SCORE_DEFAULT;
        }
        if (getIndicator->IsBoolean()) {
            indicator = getIndicator->ToBoolean();
        }
    }
    RatingModel::GetInstance()->Create(rating, indicator);
    if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction()) {
        ParseRatingObject(info, changeEventVal);
    }
}

void JSRating::SetStars(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        RatingModel::GetInstance()->SetStars(STARS_DEFAULT);
        return;
    }

    auto stars = info[0]->ToNumber<int32_t>();
    if (stars <= 0) {
        stars = STARS_DEFAULT;
    }
    RatingModel::GetInstance()->SetStars(stars);
}

void JSRating::SetStepSize(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        RatingModel::GetInstance()->SetStepSize(STEPS_DEFAULT);
        return;
    }
    static const double stepSizeMin = 0.1;
    auto steps = info[0]->ToNumber<double>();
    if (LessNotEqual(steps, stepSizeMin)) {
        steps = STEPS_DEFAULT;
    }
    RatingModel::GetInstance()->SetStepSize(steps);
}

void JSRating::SetStarStyle(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        RatingModel::GetInstance()->SetBackgroundSrc("", true);
        RatingModel::GetInstance()->SetForegroundSrc("", true);
        RatingModel::GetInstance()->SetSecondarySrc("", true);
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getBackgroundUri = paramObject->GetProperty("backgroundUri");
    auto getForegroundUri = paramObject->GetProperty("foregroundUri");
    auto getSecondaryUri = paramObject->GetProperty("secondaryUri");
    std::string backgroundUri;
    if (getBackgroundUri->IsString()) {
        backgroundUri = getBackgroundUri->ToString();
        if (backgroundUri.empty()) {
            RatingModel::GetInstance()->SetBackgroundSrc("", true);
        } else {
            RatingModel::GetInstance()->SetBackgroundSrc(backgroundUri, false);
        }
    } else {
        RatingModel::GetInstance()->SetBackgroundSrc("", true);
    }

    if (getForegroundUri->IsString()) {
        std::string foregroundUri = getForegroundUri->ToString();
        if (foregroundUri.empty()) {
            RatingModel::GetInstance()->SetForegroundSrc("", true);
        } else {
            RatingModel::GetInstance()->SetForegroundSrc(foregroundUri, false);
        }
    } else {
        RatingModel::GetInstance()->SetForegroundSrc("", true);
    }

    if (getSecondaryUri->IsString() && !getSecondaryUri->ToString().empty()) {
        RatingModel::GetInstance()->SetSecondarySrc(getSecondaryUri->ToString(), false);
    } else if (getBackgroundUri->IsString() && !backgroundUri.empty()) {
        RatingModel::GetInstance()->SetSecondarySrc(backgroundUri, false);
    } else {
        RatingModel::GetInstance()->SetSecondarySrc("", true);
    }
}

void JSRating::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Rating.onChange");
        PipelineContext::SetCallBackNode(node);
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
    JSClass<JSRating>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRating>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRating>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRating>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRating>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRating>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRating>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRating>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRating>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRating>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
