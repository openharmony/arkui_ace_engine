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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GENERATOR_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GENERATOR_ELEMENT_H

#include "core/components_v2/list/render_list_item.h"

namespace OHOS::Ace::V2 {

class ListItemGenerator : virtual public Referenced {
public:
    static constexpr size_t INVALID_INDEX = std::numeric_limits<size_t>::max();

    virtual RefPtr<RenderListItem> RequestListItem(size_t index) = 0;
    virtual RefPtr<RenderNode> RequestListItemHeader()
    {
        return nullptr;
    }
    virtual RefPtr<RenderNode> RequestListItemFooter()
    {
        return nullptr;
    }
    virtual void RecycleListItem(size_t index) = 0;
    virtual size_t TotalCount() = 0;
    virtual size_t FindPreviousStickyListItem(size_t  /* index */)
    {
        return INVALID_INDEX;
    }
    virtual size_t FindItemStartIndex(size_t  /* index */)
    {
        return 0;
    }
};

} // namespace OHOS::Ace::V2

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_LIST_LIST_ITEM_GENERATOR_ELEMENT_H