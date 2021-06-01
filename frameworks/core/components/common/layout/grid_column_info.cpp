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

#include "base/log/log.h"
#include "core/components/common/layout/grid_system_manager.h"

namespace OHOS::Ace {

double GridColumnInfo::GetWidth() const
{
    if (!parent_) {
        LOGE("no parent info");
        return 0.0;
    }

    uint32_t columns = 0;
    auto sizeType = parent_->GetSizeType();
    switch (sizeType) {
        case GridSizeType::XS:
            columns = xsSizeColumn_ > 0 ? xsSizeColumn_ : columns_;
            break;
        case GridSizeType::SM:
            columns = smSizeColumn_ > 0 ? smSizeColumn_ : columns_;
            break;
        case GridSizeType::MD:
            columns = mdSizeColumn_ > 0 ? mdSizeColumn_ : columns_;
            break;
        case GridSizeType::LG:
            columns = lgSizeColumn_ > 0 ? lgSizeColumn_ : columns_;
            break;
        case GridSizeType::XL:
            columns = lgSizeColumn_ > 0 ? lgSizeColumn_ : columns_;
            break;
        default:
            break;
    }

    return GetWidth(columns);
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
    switch (sizeType) {
        case GridSizeType::XS:
            columns = xsSizeColumn_ > 0 ? xsSizeColumn_ : columns_;
            break;
        case GridSizeType::SM:
            columns = smSizeMaxColumn_ > 0 ? smSizeMaxColumn_ : smSizeColumn_ > 0 ? smSizeColumn_ : columns_;
            break;
        case GridSizeType::MD:
            columns = mdSizeMaxColumn_ > 0 ? mdSizeMaxColumn_ : mdSizeColumn_ > 0 ? mdSizeColumn_ : columns_;
            break;
        case GridSizeType::LG:
            columns = lgSizeMaxColumn_ > 0 ? lgSizeMaxColumn_ : lgSizeColumn_ > 0 ? lgSizeColumn_ : columns_;
            break;
        default:
            break;
    }

    return GetWidth(columns);
}

const Dimension& GridColumnInfo::GetOffset() const
{
    if (!parent_) {
        LOGE("no parent info");
        return UNDEFINED_DIMENSION;
    }
    auto sizeType = parent_->GetSizeType();
    switch (sizeType) {
        case GridSizeType::XS:
            return xsSizeOffset_;
            break;
        case GridSizeType::SM:
            return smSizeOffset_;
            break;
        case GridSizeType::MD:
            return mdSizeOffset_;
            break;
        case GridSizeType::LG:
            return lgSizeOffset_;
            break;
        default:
            break;
    }

    return UNDEFINED_DIMENSION;
}

} // namespace OHOS::Ace
