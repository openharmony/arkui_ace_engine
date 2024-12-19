/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/grid/irregular/grid_layout_utils.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {
GridItemSize GridLayoutUtils::GetItemSize(const GridLayoutInfo* info, const LayoutWrapper* wrapper, int32_t idx)
{
    GridItemSize size { 1, 1 };
    auto props = AceType::DynamicCast<GridLayoutProperty>(wrapper->GetLayoutProperty());
    const auto& opts = *props->GetLayoutOptions();
    if (opts.irregularIndexes.find(idx) != opts.irregularIndexes.end()) {
        if (!opts.getSizeByIndex) {
            // default irregular size = [1, full cross length]
            size.rows = 1;
            size.columns = info->crossCount_;
        } else {
            size = opts.getSizeByIndex(idx);
            // assume [row] represents mainLength and [column] represents crossLength in this class, so flip sides if
            // horizontal
            if (info->axis_ == Axis::HORIZONTAL) {
                std::swap(size.rows, size.columns);
            }
        }
    }

    // handle illegal size
    if (size.columns > info->crossCount_) {
        size.columns = info->crossCount_;
    }
    size.columns = std::max(1, size.columns);
    size.rows = std::max(1, size.rows);
    return size;
}

void GridLayoutUtils::PreloadGridItems(
    const RefPtr<GridPattern>& pattern, std::list<GridPreloadItem>&& items, const BuildGridItemCallback& buildCb)
{
    if (items.empty()) {
        return;
    }
    CHECK_NULL_VOID(pattern);
    const bool taskAdded = pattern->HasPreloadItemList();
    pattern->SetPreloadItemList(std::move(items));
    if (taskAdded) {
        // task already in queue, only need to update item list
        return;
    }
    PreloadGridItemsHelper(pattern, buildCb);
}

void GridLayoutUtils::PreloadGridItemsHelper(const RefPtr<GridPattern>& pattern, const BuildGridItemCallback& buildCb)
{
    auto* context = pattern->GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask([weak = AceType::WeakClaim(AceType::RawPtr(pattern)), buildCb](int64_t deadline, bool _) {
        ACE_SCOPED_TRACE("Grid preload items");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        const auto items = pattern->MovePreloadItemList();
        if (items.empty()) {
            return;
        }
        auto it = items.begin();
        if (pattern->IsPredictOutOfRange(it->idx)) {
            return;
        }
        bool needMarkDirty = false;
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        for (; it != items.end(); ++it) {
            if (GetSysTimestamp() > deadline) {
                break;
            }
            if (it->buildOnly) {
                host->GetOrCreateChildByIndex(it->idx, false, true);
                continue;
            }
            if (buildCb) {
                needMarkDirty = buildCb(host, it->idx) || needMarkDirty;
            }
        }
        if (needMarkDirty) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        if (it != items.end() && !needMarkDirty) {
            pattern->SetPreloadItemList(std::list<GridPreloadItem>(it, items.end()));
            PreloadGridItemsHelper(pattern, buildCb);
        } else {
            pattern->SetPreloadItemList({});
        }
    });
}
} // namespace OHOS::Ace::NG
