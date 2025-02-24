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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_STYLES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_STYLES_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct FlexLayoutAttribute {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexDirection, FlexDirection);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MainAxisAlign, FlexAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CrossAxisAlign, FlexAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Space, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(IsReverse, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WidthLayoutPolicy, uint8_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HeightLayoutPolicy, uint8_t);
};

struct WrapLayoutAttribute {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WrapDirection, WrapDirection);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Alignment, WrapAlignment);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MainAlignment, WrapAlignment);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CrossAlignment, WrapAlignment);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CrossSpace, Dimension);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_STYLES_H
