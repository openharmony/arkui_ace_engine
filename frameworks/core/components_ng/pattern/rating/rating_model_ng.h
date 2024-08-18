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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/pattern/rating/rating_model.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class RatingConfiguration : public CommonConfiguration {
public:
    RatingConfiguration(int32_t starNum, bool isIndicator, double rating, double stepSize, bool enabled)
        : CommonConfiguration(enabled), starNum_(starNum), isIndicator_(isIndicator),
        rating_(rating), stepSize_(stepSize) {}
    int32_t starNum_;
    bool isIndicator_;
    double rating_;
    double stepSize_;
};
using RatingMakeCallback =
    std::function<RefPtr<FrameNode>(const RatingConfiguration& ratingConfiguration)>;
class ACE_EXPORT RatingModelNG : public OHOS::Ace::RatingModel {
public:
    void Create(double rating = .0, bool indicator = false) override;
    void SetRatingScore(double value) override;
    void SetIndicator(bool value) override;
    void SetStars(int32_t value) override;
    void SetStepSize(double value) override;
    void SetForegroundSrc(const std::string& value, bool flag = false) override;
    void SetSecondarySrc(const std::string& value, bool flag = false) override;
    void SetBackgroundSrc(const std::string& value, bool flag = false) override;
    void SetOnChange(RatingChangeEvent&& onChange) override;
    void SetOnChangeEvent(RatingChangeEvent&& onChangeEvent) override;
    
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetStars(FrameNode* frameNode, int32_t value);
    static void SetStepSize(FrameNode* frameNode, double value);
    static void SetForegroundSrc(FrameNode* frameNode, const std::string& value, bool flag = false);
    static void SetSecondarySrc(FrameNode* frameNode, const std::string& value, bool flag = false);
    static void SetBackgroundSrc(FrameNode* frameNode, const std::string& value, bool flag = false);
    static void SetBuilderFunc(FrameNode* frameNode, NG::RatingMakeCallback&& jsMake);
    static void SetChangeValue(FrameNode* frameNode, double value);
    static void SetRatingOptions(FrameNode* frameNode, double rating = .0, bool indicator = false);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RATING_RATING_MODEL_NG_H
