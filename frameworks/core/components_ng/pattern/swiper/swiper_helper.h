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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_HELPER_H
#include "swiper_pattern.h"

#include "core/components/swiper/swiper_controller.h"
namespace OHOS::Ace::NG {
/* implements helper functions for SwiperPattern */
class SwiperHelper {
public:
    /* Init controller of swiper, controller support showNext, showPrevious and finishAnimation interface. */
    static void InitSwiperController(const RefPtr<SwiperController>& controller, const WeakPtr<SwiperPattern>& weak);

    static void SaveDigitIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperPattern& swiper);
    static void SaveDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode, SwiperPattern& swiper);

    static void DumpAdvanceInfo(SwiperPattern& swiper);

    static std::string GetDotIndicatorStyle(const std::shared_ptr<SwiperParameters>& params);
    static std::string GetDigitIndicatorStyle(const std::shared_ptr<SwiperDigitalParameters>& params);

    static float CalculateFriction(float gamma);

private:
    static void DumpInfoAddPositionDesc(SwiperPattern& swiper);
    static void DumpInfoAddGestureDesc(SwiperPattern& swiper);
    static void DumpInfoAddAnimationDesc(SwiperPattern& swiper);
    static void SetChangeIndexWithModeImpl(const RefPtr<SwiperController>& controller,
        const WeakPtr<SwiperPattern>& weak);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_HELPER_H
