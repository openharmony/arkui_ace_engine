/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_DATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_DATE_H

#include "core/components/common/properties/progress_data.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

enum class ProgressType {
    LINEAR = 1,
    RING = 2,
    SCALE = 3,
    CIRCLE = 4,
    GAUGE = 5,
    ARC = 6,
    MOON = 7,
    BUBBLE = 8,
    CAPSULE = 9,
};

struct ProgressDate {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaxValue, double);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Value, double);
    //ACE_DEFINE_PROPERTY_GROUP_ITEM(CachedValue, double);
};

struct ProgressStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Color, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Type, ProgressType);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(StrokeWidth, double);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScaleCount, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScaleWidth, double);
};

// ProgressDate CreateProgressDateUsingTheme(const std::unique_ptr<ProgressDate>& progressDate,
//  const RefPtr<ProgressTheme>& progressTheme);

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_PROGRESS_DATE_H
