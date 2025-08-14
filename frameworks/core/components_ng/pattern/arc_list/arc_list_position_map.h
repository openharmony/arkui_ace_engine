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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_POSITION_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_POSITION_MAP_H

#include "core/components_ng/pattern/arc_list/arc_list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_position_map.h"

namespace OHOS::Ace::NG {

class ArcListPositionMap : public ListPositionMap {
    DECLARE_ACE_TYPE(ArcListPositionMap, ListPositionMap);
public:
    explicit ArcListPositionMap(int32_t itemStartIndex) : itemStartIndex_(itemStartIndex) {}
    ~ArcListPositionMap() override = default;

    void UpdatePosMap(
        LayoutWrapper* layoutWrapper, int32_t lanes, float space, RefPtr<ListChildrenMainSize>& childrenSize) override
    {
        childrenSize_ = childrenSize;
        if (totalItemCount_ != layoutWrapper->GetTotalChildCount() - itemStartIndex_) {
            dirty_ |= LIST_UPDATE_ITEM_COUNT;
            totalItemCount_ = layoutWrapper->GetTotalChildCount() - itemStartIndex_;
        }
        if (!NearEqual(space, space_)) {
            dirty_ |= LIST_UPDATE_SPACE;
            space_ = space;
        }
        if (lanes != lanes_) {
            dirty_ |= LIST_UPDATE_SPACE;
            lanes_ = lanes;
        }
        switch (CheckPosMapUpdateRule()) {
            case ListPosMapUpdate::NO_CHANGE:
                break;
            case ListPosMapUpdate::UPDATE_ALL_SIZE:
                PosMapRecalculate(layoutWrapper);
                break;
            case ListPosMapUpdate::RE_CALCULATE:
            default:
                PosMapRecalculate(layoutWrapper);
        }
        ClearDirty();
    }

private:
    int32_t itemStartIndex_ = 0;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_POSITION_MAP_H