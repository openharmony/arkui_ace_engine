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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
class ArcSwiperPattern : public SwiperPattern {
    DECLARE_ACE_TYPE(ArcSwiperPattern, SwiperPattern);
public:
    void SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode) override;
    void SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters) override;
    std::string GetArcDotIndicatorStyle() const override;
    std::shared_ptr<SwiperArcDotParameters> GetSwiperArcDotParameters() const override;

private:
    std::string GradientToJson(Gradient colors) const;
    mutable std::shared_ptr<SwiperArcDotParameters> swiperArcDotParameters_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H