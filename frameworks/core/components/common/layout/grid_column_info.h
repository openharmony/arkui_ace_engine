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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_GRID_COLUMN_INFO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_GRID_COLUMN_INFO_H

#include "core/components/common/layout/grid_container_info.h"
#include "core/components/common/layout/screen_system_manager.h"

namespace OHOS::Ace {

constexpr uint32_t DEFAULT_GRID_COLUMN_SPAN = 0;

class GridColumnInfo : public GridLayoutInfo {
    DECLARE_ACE_TYPE(GridColumnInfo, GridLayoutInfo);

public:
    class Builder : public AceType {
        DECLARE_ACE_TYPE(Builder, AceType);
    public:
        Builder()
        {
            columnInfo_ = AceType::MakeRefPtr<GridColumnInfo>();
        }
        void SetXsSizeColumn(uint32_t xsSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->columns_[ScreenSizeType::XS] = static_cast<int32_t>(xsSizeColumn);
            columnInfo_->dimOffsets_[ScreenSizeType::XS] = offset;
        }

        void SetSmSizeColumn(uint32_t smSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->columns_[ScreenSizeType::SM] = static_cast<int32_t>(smSizeColumn);
            columnInfo_->dimOffsets_[ScreenSizeType::SM] = offset;
        }

        void SetMdSizeColumn(uint32_t mdSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->columns_[ScreenSizeType::MD] = static_cast<int32_t>(mdSizeColumn);
            columnInfo_->dimOffsets_[ScreenSizeType::MD] = offset;
        }

        void SetLgSizeColumn(uint32_t lgSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->columns_[ScreenSizeType::LG] = static_cast<int32_t>(lgSizeColumn);
            columnInfo_->dimOffsets_[ScreenSizeType::LG] = offset;
        }

        void SetSizeColumn(GridSizeType type, uint32_t column, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->columns_[type] = static_cast<int32_t>(column);
            columnInfo_->dimOffsets_[type] = offset;
        }

        void SetSmSizeMaxColumn(uint32_t smSizeMaxColumn)
        {
            columnInfo_->maxColumns_[ScreenSizeType::SM]  = static_cast<int32_t>(smSizeMaxColumn);
        }
        void SetMdSizeMaxColumn(uint32_t mdSizeMaxColumn)
        {
            columnInfo_->maxColumns_[ScreenSizeType::MD]  = static_cast<int32_t>(mdSizeMaxColumn);
        }
        void SetLgSizeMaxColumn(uint32_t lgSizeMaxColumn)
        {
            columnInfo_->maxColumns_[ScreenSizeType::LG] = static_cast<int32_t>(lgSizeMaxColumn);
        }

        void SetColumns(uint32_t columns)
        {
            columnInfo_->columns_[ScreenSizeType::UNDEFINED] = static_cast<int32_t>(columns);
        }

        void ACE_EXPORT SetOffset(int32_t offset, GridSizeType type = GridSizeType::UNDEFINED);

        void SetParent(const RefPtr<GridContainerInfo>& parent)
        {
            columnInfo_->parent_ = parent;
        }

        const RefPtr<GridColumnInfo>& Build() const
        {
            return columnInfo_;
        }

    private:
        RefPtr<GridColumnInfo> columnInfo_;
    };

    ~GridColumnInfo() override = default;
    double GetWidth() const;
    double GetWidth(uint32_t columns) const;
    double GetMaxWidth() const;
    Dimension GetOffset() const;
    const RefPtr<GridContainerInfo>& GetParent() const
    {
        return parent_;
    }
    uint32_t GetColumns() const
    {
        return columns_[ScreenSizeType::UNDEFINED];
    }
    int32_t GetOffset(GridSizeType type) const
    {
        return offsets_[type];
    }
    uint32_t GetColumns(GridSizeType type) const
    {
        return IsValid(type) ? columns_[type] : DEFAULT_GRID_COLUMN_SPAN;
    }

private:
    static constexpr int32_t INVALID_OFFSET = -1;

    GridColumnInfo()
    {
        // default column and offset which no define column of the size
        columns_[ScreenSizeType::UNDEFINED] = DEFAULT_GRID_COLUMN_SPAN;
    }

    bool hasColumnOffset_ = false;
    ArrayByScreenType<int32_t> columns_ {0};
    ArrayByScreenType<int32_t> maxColumns_ {0};
    ArrayByScreenType<Dimension> dimOffsets_ {UNDEFINED_DIMENSION};
    ArrayByScreenType<int32_t> offsets_ {INVALID_OFFSET};
    // parent container grid infos
    RefPtr<GridContainerInfo> parent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_GRID_COLUMN_INFO_H
