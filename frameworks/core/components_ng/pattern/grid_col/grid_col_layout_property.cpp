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

#include "core/components_ng/pattern/grid_col/grid_col_layout_property.h"

#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace OHOS::Ace::NG {

using OHOS::Ace::V2::GridContainerUtils;

void GridColLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto sizeType = GetSizeTypeValue(V2::GridSizeType::UNDEFINED);

    auto span = GetSpan(sizeType);
    auto offset = GetOffset(sizeType);
    auto order = GetOrder(sizeType);
    json->PutExtAttr("span", std::to_string(span).c_str(), filter);
    json->PutExtAttr("offset", std::to_string(offset).c_str(), filter);
    json->PutExtAttr("gridColOffset", std::to_string(offset).c_str(), filter);
    json->PutExtAttr("order", std::to_string(order).c_str(), filter);
}

int32_t GridColLayoutProperty::GetPropValue(const V2::GridContainerSize& prop, V2::GridSizeType sizeType)
{
    switch (sizeType) {
        case V2::GridSizeType::XS:
            return prop.xs;
            break;
        case V2::GridSizeType::SM:
            return prop.sm;
            break;
        case V2::GridSizeType::MD:
            return prop.md;
            break;
        case V2::GridSizeType::LG:
            return prop.lg;
            break;
        case V2::GridSizeType::XL:
            return prop.xl;
            break;
        case V2::GridSizeType::XXL:
            return prop.xxl;
            break;
        default:
            return prop.xs;
    }
}

} // namespace OHOS::Ace::NG
