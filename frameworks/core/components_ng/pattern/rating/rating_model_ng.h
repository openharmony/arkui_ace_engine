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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_NG_H

#include "core/components_ng/pattern/rating/rating_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RatingModelNG : public OHOS::Ace::RatingModel {
public:
    void Create() override;
    void SetRatingScore(double value) override;
    void SetIndicator(bool value) override;
    void SetStars(int32_t value) override;
    void SetStepSize(double value) override;
    void SetForegroundSrc(const std::string& value) override;
    void SetSecondarySrc(const std::string& value) override;
    void SetBackgroundSrc(const std::string& value) override;
    void SetOnChange(ChangeEvent&& onChange) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_NG_H
