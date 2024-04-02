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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H

#include "core/components/scroll/scroll_controller_base.h"

namespace OHOS::Ace::NG {

constexpr int32_t EMPTY_JUMP_INDEX = -2;

class WaterFlowLayoutInfoBase {
public:
    Axis axis_ = Axis::VERTICAL;

    bool itemStart_ = false;
    bool itemEnd_ = false;   // last item is partially in viewport
    bool offsetEnd_ = false; // last item's bottom is in viewport

    int32_t jumpIndex_ = EMPTY_JUMP_INDEX;
    ScrollAlign align_ = ScrollAlign::START;
    std::optional<int32_t> targetIndex_;

    int32_t startIndex_ = 0;
    int32_t endIndex_ = -1;
    int32_t footerIndex_ = -1;
    int32_t childrenCount_ = 0;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_INFO_BASE_H
