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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MAGIC_LAYOUT_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MAGIC_LAYOUT_PROPERTIES_H

#include <memory>

#include "base/json/json_util.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct MagicItemProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(LayoutWeight, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AspectRatio, float);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    inline void Reset()
    {
        propLayoutWeight.reset();
        propAspectRatio.reset();
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MAGIC_LAYOUT_PROPERTIES_H
