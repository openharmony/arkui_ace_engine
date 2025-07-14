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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RATING_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RATING_MODEL_IMPL_H

#include "core/common/resource/resource_object.h"
#include "core/components_ng/pattern/rating/rating_model.h"

namespace OHOS::Ace::Framework {

class RatingModelImpl : public RatingModel {
public:
    RatingModelImpl() = default;
    ~RatingModelImpl() override = default;

    void Create(double rating = .0, bool indicator = false) override;
    void SetRatingScore(double value) override;
    void SetIndicator(bool value) override;
    void SetStars(int32_t value) override;
    void SetStepSize(double value) override;
    void SetForegroundSrc(const std::string& value, bool flag = false) override;
    void SetSecondarySrc(const std::string& value, bool flag = false) override;
    void SetBackgroundSrc(const std::string& value, bool flag = false) override;
    void SetOnChange(RatingChangeEvent&& onChange) override;
    void SetOnChangeEvent(RatingChangeEvent&& onChangeEvent) override {};
    void CreateWithMediaResourceObj(const RefPtr<ResourceObject>& resObj,
        const RatingUriType ratingUriType) override {};
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RATING_MODEL_IMPL_H
