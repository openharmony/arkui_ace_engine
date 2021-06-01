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

namespace OHOS::Ace {

constexpr uint32_t DEFAULT_GRID_COLUMN_SPAN = 1;

class GridColumnInfo : public GridLayoutInfo {
    DECLARE_ACE_TYPE(GridColumnInfo, GridLayoutInfo);

public:
    class Builder {
    public:
        Builder()
        {
            columnInfo_ = AceType::Claim(new GridColumnInfo());
        }
        void SetXsSizeColumn(uint32_t xsSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->xsSizeColumn_ = xsSizeColumn;
            columnInfo_->xsSizeOffset_ = offset;
        }

        void SetSmSizeColumn(uint32_t smSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->smSizeColumn_ = smSizeColumn;
            columnInfo_->smSizeOffset_ = offset;
        }

        void SetMdSizeColumn(uint32_t mdSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->mdSizeColumn_ = mdSizeColumn;
            columnInfo_->mdSizeOffset_ = offset;
        }

        void SetLgSizeColumn(uint32_t lgSizeColumn, const Dimension& offset = UNDEFINED_DIMENSION)
        {
            columnInfo_->lgSizeColumn_ = lgSizeColumn;
            columnInfo_->lgSizeOffset_ = offset;
        }
        void SetSmSizeMaxColumn(uint32_t smSizeMaxColumn)
        {
            columnInfo_->smSizeMaxColumn_ = smSizeMaxColumn;
        }
        void SetMdSizeMaxColumn(uint32_t mdSizeMaxColumn)
        {
            columnInfo_->mdSizeMaxColumn_ = mdSizeMaxColumn;
        }
        void SetLgSizeMaxColumn(uint32_t lgSizeMaxColumn)
        {
            columnInfo_->lgSizeMaxColumn_ = lgSizeMaxColumn;
        }

        void SetColumns(uint32_t columns)
        {
            columnInfo_->columns_ = columns;
        }

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

public:
    ~GridColumnInfo() override = default;
    double GetWidth() const;
    double GetWidth(uint32_t columns) const;
    double GetMaxWidth() const;
    const Dimension& GetOffset() const;
    const RefPtr<GridContainerInfo>& GetParent() const
    {
        return parent_;
    }

private:
    GridColumnInfo() = default;

    uint32_t xsSizeColumn_ = 0;
    uint32_t smSizeColumn_ = 0;
    uint32_t mdSizeColumn_ = 0;
    uint32_t lgSizeColumn_ = 0;

    Dimension xsSizeOffset_ = UNDEFINED_DIMENSION;
    Dimension smSizeOffset_ = UNDEFINED_DIMENSION;
    Dimension mdSizeOffset_ = UNDEFINED_DIMENSION;
    Dimension lgSizeOffset_ = UNDEFINED_DIMENSION;

    uint32_t smSizeMaxColumn_ = 0;
    uint32_t mdSizeMaxColumn_ = 0;
    uint32_t lgSizeMaxColumn_ = 0;

    // default column which no define column of the size
    uint32_t columns_ = DEFAULT_GRID_COLUMN_SPAN;
    // parent container grid infos
    RefPtr<GridContainerInfo> parent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_GRID_COLUMN_INFO_H
