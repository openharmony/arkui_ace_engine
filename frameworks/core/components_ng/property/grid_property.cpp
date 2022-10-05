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

#include "grid_property.h"

#include <cstddef>

#include "core/components/common/layout/grid_container_info.h"
#include "core/components_ng/pattern/grid_container/grid_container_layout_property.h"

namespace OHOS::Ace::NG {

Dimension GridProperty::GetWidth()
{
    // gridInfo_ must exist, because layout algorithm invoke UpdateContainer first
    return Dimension(gridInfo_->GetWidth());
}

Dimension GridProperty::GetOffset()
{
    // gridInfo_ must exist, because layout algorithm invoke UpdateContainer() first
    auto marginOffset = Dimension(gridInfo_->GetParent()->GetMarginLeft().ConvertToPx());
    return gridInfo_->GetOffset() + marginOffset;
}

bool GridProperty::UpdateContainer(const RefPtr<Property>& container, const RefPtr<AceType>& host)
{
    auto gridContainer = DynamicCast<GridContainerLayoutProperty>(container);
    auto mGridContainer = DynamicCast<GridContainerLayoutProperty>(container_);

    if ((container_) && (*mGridContainer == *gridContainer)) {
        return false;
    }
    container_ = container;

    GridColumnInfo::Builder builder;
    auto containerInfo = MakeRefPtr<GridContainerInfo>(gridContainer->GetContainerInfoValue());
    builder.SetParent(containerInfo);

    for (const auto& item : typedPropertySet_) {
        builder.SetSizeColumn(item.type_, item.span_);
        builder.SetOffset(item.offset_, item.type_);
    }

    gridInfo_ = builder.Build();
    gridContainer->RegistGridChild(DynamicCast<FrameNode>(host));
    return true;
}

bool GridProperty::UpdateSpan(uint32_t span, GridSizeType type)
{
    LOGD("Update grid span. (span=%u, type=%i)", span, type);
    if (!container_) {
        SetSpan(type, span);
        return true;
    }

    auto container = DynamicCast<GridContainerLayoutProperty>(container_);
    GridSizeType currentType = container->GetContainerInfo()->GetSizeType(); // working type, not UNDEFINED
    auto currentProp = GetTypedProperty(type);                               // working property

    return (currentProp->type_ == type || currentType == type) && SetSpan(type, span);
}

bool GridProperty::UpdateOffset(int32_t offset, GridSizeType type)
{
    LOGD("Update grid span. (offset=%u, type=%i)", offset, type);
    if (!container_) {
        SetOffset(type, offset);
        return true;
    }
    auto container = DynamicCast<GridContainerLayoutProperty>(container_);
    GridSizeType currentType = container->GetContainerInfo()->GetSizeType(); // working type, not UNDEFINED
    auto currentProp = GetTypedProperty(type);                               // working property

    return (currentProp->type_ == type || currentType == type) && SetOffset(type, offset);
}

bool GridProperty::SetSpan(GridSizeType type, uint32_t span)
{
    auto item = std::find_if(typedPropertySet_.begin(), typedPropertySet_.end(),
        [type](const GridTypedProperty& p) { return p.type_ == type; });
    if (item == typedPropertySet_.end()) {
        typedPropertySet_.emplace_back(type, span, DEFAULT_GRID_OFFSET);
        return true;
    }
    if (item->span_ == span) {
        return false;
    }
    item->span_ = span;
    return true;
}

bool GridProperty::SetOffset(GridSizeType type, int32_t offset)
{
    auto item = std::find_if(typedPropertySet_.begin(), typedPropertySet_.end(),
        [type](const GridTypedProperty& p) { return p.type_ == type; });
    if (item == typedPropertySet_.end()) {
        typedPropertySet_.emplace_back(type, DEFAULT_GRID_SPAN, offset);
        return true;
    }
    if (item->offset_ == offset) {
        return false;
    }
    item->offset_ = offset;
    return true;
}

} // namespace OHOS::Ace::NG
