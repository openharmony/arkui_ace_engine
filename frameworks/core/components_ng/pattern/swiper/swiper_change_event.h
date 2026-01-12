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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_CHANGE_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_CHANGE_EVENT_H
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/swiper_indicator.h"
#include "core/components/swiper/swiper_controller.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {
class ACE_EXPORT SwiperChangeEvent : public BaseEventInfo, public EventToJSONStringAdapter {
    DECLARE_RELATIONSHIP_OF_CLASSES(SwiperChangeEvent, BaseEventInfo, EventToJSONStringAdapter);

public:
    explicit SwiperChangeEvent(int32_t index) : BaseEventInfo("SwiperChangeEvent"), index_(index) {}
    ~SwiperChangeEvent() = default;

    int32_t GetIndex() const
    {
        return index_;
    }

    std::string ToJSONString() const override
    {
        return std::string(R"("change",{"index":)").append(std::to_string(index_).append("},null"));
    }

private:
    int32_t index_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_CHANGE_EVENT_H