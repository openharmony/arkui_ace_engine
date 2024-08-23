/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_rating_ffi.h"

#include "cj_lambda.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"

namespace {
    constexpr double RATING_SCORE_DEFAULT = 0;
    constexpr int32_t STARS_DEFAULT = 5;
    constexpr double STEPS_DEFAULT = 0.5;
}

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkRatingCreate(double rating, bool indicator)
{
    double ratnum = rating <= 0 ?  RATING_SCORE_DEFAULT : rating;
    RatingModel::GetInstance()->Create(ratnum, indicator);
}

void FfiOHOSAceFrameworkRatingSetStars(int32_t value)
{
    auto stars = value <= 0 ? STARS_DEFAULT : value;
    RatingModel::GetInstance()->SetStars(stars);
}

void FfiOHOSAceFrameworkRatingSetStepSize(double value)
{
    static const double stepSizeMin = 0.1;
    double stepSize = LessNotEqual(value, stepSizeMin) ? STEPS_DEFAULT : value;
    RatingModel::GetInstance()->SetStepSize(stepSize);
}

void FfiOHOSAceFrameworkRatingSetStarStyle(
    const char* backgroundUri, const char* foregroundUri, const char* secondaryUri)
{
    bool backgroundisempty = !(strlen(backgroundUri) != 0);
    bool secondaryisempty = !(strlen(secondaryUri) != 0);
    bool foregroundisempty = !(strlen(foregroundUri) != 0);
    RatingModel::GetInstance()->SetForegroundSrc(foregroundUri, foregroundisempty);
    RatingModel::GetInstance()->SetSecondarySrc(secondaryUri, secondaryisempty);
    RatingModel::GetInstance()->SetBackgroundSrc(backgroundUri, backgroundisempty);
}

void FfiOHOSAceFrameworkRatingSetOnChange(void (*callback)(double))
{
    auto onChange = [lambda = CJLambda::Create(callback)](const std::string& value) {
        lambda(std::stod(value));
    };
    RatingModel::GetInstance()->SetOnChange(onChange);
}
}
