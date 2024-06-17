/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_POSITION_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_POSITION_CONTROLLER_H

#include "core/components/scroll/scroll_controller.h"
#include "core/components/scroll/scrollable.h"

namespace OHOS::Ace::V2 {
class ACE_EXPORT WaterFlowPositionController : public ScrollController {
    DECLARE_ACE_TYPE(WaterFlowPositionController, ScrollController);

public:
    WaterFlowPositionController() = default;
    ~WaterFlowPositionController() override = default;
    Axis GetScrollDirection() const override;

    void ScrollToIndex(int32_t index, bool smooth, ScrollAlign align, std::optional<float> extraOffset) override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowPositionController);
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_WATER_FLOW_POSITION_CONTROLLER_H
