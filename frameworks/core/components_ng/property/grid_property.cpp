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

#include "core/components_ng/pattern/grid_container/grid_container_layout_property.h"

namespace OHOS::Ace::NG {

Dimension GridProperty::GetWidth()
{
    CHECK_NULL_RETURN(gridInfo_, Dimension());
    // gridInfo_ must exist, because layout algorithm invoke UpdateContainer first
    return Dimension(gridInfo_->GetWidth());
}

Dimension GridProperty::GetOffset()
{
    CHECK_NULL_RETURN(gridInfo_, Dimension());
    // gridInfo_ must exist, because layout algorithm invoke UpdateContainer() first
    auto offset = gridInfo_->GetOffset();
    if (offset == UNDEFINED_DIMENSION) {
        return UNDEFINED_DIMENSION;
    }
    auto marginOffset = Dimension(gridInfo_->GetParent()->GetMarginLeft().ConvertToPx());
    return offset + marginOffset;
}

bool GridProperty::UpdateContainer(const RefPtr<Property>& container, const RefPtr<AceType>& host)
{
    auto currentContainer = DynamicCast<GridContainerLayoutProperty>(container);
    auto gridContainer = currentContainer->GetReserveObj();
    GridColumnInfo::Builder builder;
    auto containerInfo = AceType::MakeRefPtr<GridContainerInfo>(gridContainer->GetContainerInfoValue());
    builder.SetParent(containerInfo);
    for (const auto& item : typedPropertySet_) {
        builder.SetSizeColumn(item.type_, item.span_);
        builder.SetOffset(item.offset_, item.type_);
    }
    gridInfo_ = builder.Build();
    container_ = container;

    currentContainer->RegistGridChild(DynamicCast<FrameNode>(host));
    return true;
}

bool GridProperty::UpdateSpan(int32_t span, GridSizeType type)
{
    if (span < 0) {
        LOGE("Span value is illegal.");
        return false;
    }
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
    if (!container_) {
        SetOffset(type, offset);
        return true;
    }
    auto container = DynamicCast<GridContainerLayoutProperty>(container_);
    GridSizeType currentType = container->GetContainerInfo()->GetSizeType(); // working type, not UNDEFINED
    auto currentProp = GetTypedProperty(type);                               // working property

    return (currentProp->type_ == type || currentType == type) && SetOffset(type, offset);
}

bool GridProperty::SetSpan(GridSizeType type, int32_t span)
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

OffsetF GridProperty::GetContainerPosition()
{
    if (container_) {
        auto container = DynamicCast<GridContainerLayoutProperty>(container_);
        auto framenode = container->GetHost();
        CHECK_NULL_RETURN(framenode, OffsetF());
        return framenode->GetOffsetRelativeToWindow();
    }
    return OffsetF();
}

void GridProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    const char* GRID_SIZE_TYPE[] = { "default", "sx", "sm", "md", "lg" };
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (!gridInfo_) {
        auto item = std::find_if(typedPropertySet_.begin(), typedPropertySet_.end(),
            [](const GridTypedProperty& p) { return p.type_ == GridSizeType::UNDEFINED; });
        if (item == typedPropertySet_.end()) {
            json->PutExtAttr("gridSpan", 1, filter);
            json->PutExtAttr("gridOffset", 0, filter);
        } else {
            json->PutExtAttr("gridSpan", item->span_, filter);
            json->PutExtAttr("gridOffset", item->offset_, filter);
        }

        auto useSizeType = JsonUtil::Create(true);
        for (const auto& item : typedPropertySet_) {
            auto jsonValue = JsonUtil::Create(true);
            jsonValue->Put("span", item.span_);
            jsonValue->Put("offset", item.offset_);
            useSizeType->Put(GRID_SIZE_TYPE[static_cast<int32_t>(item.type_)], jsonValue);
        }
        json->PutExtAttr("useSizeType", useSizeType, filter);
        return;
    }

    auto gridOffset = gridInfo_->GetOffset(GridSizeType::UNDEFINED);
    json->PutExtAttr("gridSpan", static_cast<int32_t>(gridInfo_->GetColumns()), filter);
    json->PutExtAttr("gridOffset", gridOffset == -1 ? 0 : gridOffset, filter);

    auto useSizeType = JsonUtil::Create(true);
    auto index = static_cast<int32_t>(GridSizeType::XS);
    for (; index < static_cast<int32_t>(GridSizeType::XL); index++) {
        auto jsonValue = JsonUtil::Create(true);
        auto type = static_cast<GridSizeType>(index);
        jsonValue->Put("span", static_cast<int32_t>(gridInfo_->GetColumns(type)));
        jsonValue->Put("offset", gridInfo_->GetOffset(type));
        useSizeType->Put(GRID_SIZE_TYPE[index], jsonValue);
    }
    json->PutExtAttr("useSizeType", useSizeType, filter);
}

} // namespace OHOS::Ace::NG
