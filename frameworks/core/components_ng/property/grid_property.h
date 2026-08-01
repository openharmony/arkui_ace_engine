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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_GRID_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_GRID_PROPERTIES_H

#include <utility>

#include "property.h"

#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_column_info.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace::NG {

constexpr uint32_t DEFAULT_GRID_SPAN = 1;
constexpr int32_t DEFAULT_GRID_OFFSET = 0;
struct GridTypedProperty {
    GridTypedProperty(GridSizeType type, uint32_t span, int32_t offset) : type_(type), span_(span), offset_(offset) {}

    bool operator==(const GridTypedProperty& other) const
    {
        if ((type_ != GridSizeType::UNDEFINED) && (other.type_ != GridSizeType::UNDEFINED) && (type_ != other.type_)) {
            return false;
        }
        return ((span_ == other.span_) && (offset_ == other.offset_));
    }

    GridSizeType type_ = GridSizeType::UNDEFINED;
    int32_t span_ = DEFAULT_GRID_SPAN;
    int32_t offset_ = DEFAULT_GRID_OFFSET;
};

class ACE_EXPORT GridProperty : public AceType {
    DECLARE_ACE_TYPE(GridProperty, AceType);

public:
    GridProperty() : typedPropertySet_ { { GridSizeType::UNDEFINED, DEFAULT_GRID_SPAN, DEFAULT_GRID_OFFSET } } {}

    GridProperty(const GridProperty& other)
    {
        *this = other;
    }

    ~GridProperty() override = default;

    GridProperty(const GridProperty&& other) = delete;

    GridProperty& operator=(const GridProperty&& other) = delete;

    GridProperty& operator=(const GridProperty& other)
    {
        if (&other != this) {
            typedPropertySet_ = other.typedPropertySet_;
        }
        container_ = other.container_;
        gridInfo_ = other.gridInfo_;
        return *this;
    }

    Dimension GetWidth();

    Dimension GetOffset();

    bool UpdateContainer(const RefPtr<Property>& container, const RefPtr<AceType>& host);

    bool UpdateSpan(int32_t span, GridSizeType type = GridSizeType::UNDEFINED);

    bool UpdateOffset(int32_t offset, GridSizeType type = GridSizeType::UNDEFINED);

    std::optional<GridTypedProperty> GetTypedProperty(GridSizeType type) const
    {
        for (const auto& item : typedPropertySet_) {
            if (item.type_ == type) {
                return item;
            }
        }
        return std::nullopt;
    }

    bool HasContainer()
    {
        return container_;
    }

    OffsetF GetContainerPosition();

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

private:
    bool SetSpan(GridSizeType type, int32_t span);

    bool SetOffset(GridSizeType type, int32_t offset);

    std::vector<GridTypedProperty> typedPropertySet_;
    RefPtr<Property> container_;
    RefPtr<GridColumnInfo> gridInfo_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_GRID_PROPERTIES_H
