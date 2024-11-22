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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_MODEL_H

#include "base/geometry/axis.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"

namespace OHOS::Ace {

class ACE_EXPORT IndicatorModel {
public:
    static IndicatorModel* GetInstance();
    virtual ~IndicatorModel() = default;

    virtual RefPtr<NG::IndicatorController> Create();
    virtual void SetIndex(uint32_t index);
    virtual void SetCount(uint32_t count);
    virtual void SetLoop(bool loop);
    virtual void SetDirection(Axis axis);
    virtual void SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange);
    virtual void SetIndicatorStyle(const SwiperParameters& swiperParameters);
    virtual void SetIndicatorType(SwiperIndicatorType indicatorType) {}
    virtual void SetIsIndicatorCustomSize(bool isCustomSize) {}
    virtual void SetDotIndicatorStyle(const SwiperParameters& swiperParameters) {}
    virtual void SetDigitIndicatorStyle(const SwiperDigitalParameters& swiperDigitalParameters) {}
    virtual void SetShowIndicator(bool showIndicator);
private:
    static std::unique_ptr<IndicatorModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDICATOR_MODEL_NG_H
