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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_FLEX_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_FLEX_PROPERTIES_H

#include <memory>

#include "core/components/common/layout/constants.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct FlexItemProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexGrow, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexShrink, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AlignSelf, FlexAlign);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FlexBasis, CalcLength);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DisplayIndex, int32_t);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const
    {
        static const char* ITEM_ALIGN[] = { "ItemAlign.Auto", "ItemAlign.Start", "ItemAlign.Center", "ItemAlign.End",
            "ItemAlign.Stretch", "ItemAlign.Baseline" };
        json->Put("flexBasis", propFlexBasis.has_value() ? propFlexBasis.value().ToString().c_str() : "auto");
        json->Put("flexGrow", propFlexGrow.value_or(0.0));
        json->Put("flexShrink", propFlexShrink.value_or(1));
        json->Put("alignSelf", ITEM_ALIGN[static_cast<int32_t>(propAlignSelf.value_or(FlexAlign::AUTO))]);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_FLEX_PROPERTIES_H