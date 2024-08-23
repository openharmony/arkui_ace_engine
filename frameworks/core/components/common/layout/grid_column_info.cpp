/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/common/layout/grid_column_info.h"

#include "core/components/common/layout/grid_system_manager.h"

namespace OHOS::Ace {

/* set offset by grid column number */
void GridColumnInfo::Builder::SetOffset(int32_t offset, GridSizeType type)
{
    columnInfo_->hasColumnOffset_ = true;
    if (IsValid(type)) {
        columnInfo_->offsets_[type] = offset;
    }
}

double GridColumnInfo::GetWidth() const
{
    if (!parent_) {
        LOGE("no parent info");
        return 0.0;
    }
    auto sizeType = parent_->GetSizeType();
    uint32_t columns = IsValid(sizeType) ? columns_[sizeType] : 0;
    columns = columns > 0 ? columns : columns_[GridSizeType::UNDEFINED];
    return (columns <= 0) ? 0.0 : GetWidth(columns);
}

double GridColumnInfo::GetWidth(uint32_t columns) const
{
    if (!parent_) {
        LOGE("no parent info");
        return 0.0;
    }
    double dipScale = GridSystemManager::GetInstance().GetDipScale();
    return columns == 0 ? 0.0
                        : (columns * parent_->GetColumnWidth()) +
                              ((columns - 1) * parent_->GetGutterWidth().ConvertToPx(dipScale));
}

double GridColumnInfo::GetMaxWidth() const
{
    if (!parent_) {
        LOGE("no parent info");
        return 0.0;
    }

    uint32_t columns = 0;
    auto sizeType = parent_->GetSizeType();
    if (IsValid(sizeType)) {
        columns = maxColumns_[sizeType];
        if (columns == 0) {
            columns = columns_[sizeType];
        }
    }
    columns = columns > 0 ? columns : columns_[GridSizeType::UNDEFINED];
    return GetWidth(columns);
}

Dimension GridColumnInfo::GetOffset() const
{
    if (!parent_) {
        LOGE("no parent info");
        return UNDEFINED_DIMENSION;
    }

    /* ace1.0 obsolete logic since 6 */
    auto sizeType = parent_->GetSizeType();
    if (!hasColumnOffset_) {
        return IsValid(sizeType) ? dimOffsets_[sizeType] : UNDEFINED_DIMENSION;
    }

    /* ace2.0 */
    int32_t offset = INVALID_OFFSET;
    if (IsValid(sizeType)) {
        offset = offsets_[sizeType];
    }

    if (offset == INVALID_OFFSET) {
        offset = offsets_[GridSizeType::UNDEFINED]; // use common offset
    }
    if (offset == INVALID_OFFSET) {
        return UNDEFINED_DIMENSION;
    }
    double dipScale = GridSystemManager::GetInstance().GetDipScale();
    double offsetVp = offset * (parent_->GetColumnWidth() + parent_->GetGutterWidth().ConvertToPx(dipScale));
    return Dimension(offsetVp, DimensionUnit::PX);
}

} // namespace OHOS::Ace
