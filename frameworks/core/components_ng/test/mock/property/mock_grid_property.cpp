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

#include "base/geometry/dimension.h"
#include "frameworks/core/components_ng/property/grid_property.h"

namespace OHOS::Ace::NG {
Dimension GridProperty::GetWidth()
{
    // gridInfo_ must exist, because layout algorithm invoke UpdateContainer first
    return Dimension(1.0f);
}

Dimension GridProperty::GetOffset()
{
    // gridInfo_ must exist, because layout algorithm invoke UpdateContainer() first
    return Dimension();
}

bool GridProperty::UpdateContainer(const RefPtr<Property>& container, const RefPtr<AceType>& host)
{
    return true;
}

bool GridProperty::UpdateSpan(int32_t span, GridSizeType type)
{
    return true;
}

bool GridProperty::UpdateOffset(int32_t offset, GridSizeType type)
{
    return true;
}

bool GridProperty::SetSpan(GridSizeType type, int32_t span)
{
    return true;
}

bool GridProperty::SetOffset(GridSizeType type, int32_t offset)
{
    return true;
}

void GridProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const {}
} // namespace OHOS::Ace::NG
