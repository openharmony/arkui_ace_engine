/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_TYPE_DEFINE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_TYPE_DEFINE_H

#include <cstdint>
#include <string>

#include "base/geometry/dimension_offset.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {
enum class CalendarEdgeAlign {
    EDGE_ALIGN_START = 0,
    EDGE_ALIGN_CENTER,
    EDGE_ALIGN_END,
};

enum class CalendarPickerSelectedType {
    YEAR = 0,
    MONTH,
    DAY,
    ADDBTN,
    SUBBTN,
    OTHER,
};

struct CalendarSettingData {
    PickerDate selectedDate = PickerDate::Current();
    PickerDate startDate;
    PickerDate endDate;
    std::optional<Dimension> dayRadius;
    RefPtr<ResourceObject> dayRadiusResObj;
    WeakPtr<FrameNode> entryNode = nullptr;
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;
    bool markToday = false;
};

struct CalendarPickerOption {
    CalendarSettingData data;
    CalendarEdgeAlign alignType = CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset = DimensionOffset();
    PickerTextStyle textStyle;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_CALENDAR_TYPE_DEFINE_H
