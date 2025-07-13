/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <string>

#include "core/common/resource/resource_object.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {
using RatingChangeEvent = std::function<void(const std::string&)>;
enum class RatingUriType {
    BACKGROUND_URI,
    FOREGROUND_URI,
    SECONDARY_URI
};
class ACE_FORCE_EXPORT RatingModel {
public:
    static RatingModel* GetInstance();
    virtual ~RatingModel() = default;

    virtual void Create(double rating, bool indicator) = 0;
    virtual void SetRatingScore(double value) = 0;
    virtual void SetIndicator(bool value) = 0;
    virtual void SetStars(int32_t value) = 0;
    virtual void SetStepSize(double value) = 0;
    virtual void SetForegroundSrc(const std::string& value, bool flag) = 0;
    virtual void SetSecondarySrc(const std::string& value, bool flag) = 0;
    virtual void SetBackgroundSrc(const std::string& value, bool flag) = 0;
    virtual void SetOnChange(RatingChangeEvent&& onChange) = 0;
    virtual void SetOnChangeEvent(RatingChangeEvent&& onChangeEvent) = 0;
    virtual void CreateWithMediaResourceObj(const RefPtr<ResourceObject>& resObj,
        const RatingUriType ratingUriType) = 0;

private:
    static std::unique_ptr<RatingModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_H
