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

#include "core/components_ng/layout/layout_wrapper_builder.h"

#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

RefPtr<LayoutWrapper> LayoutWrapperBuilder::GetOrCreateWrapperByIndex(int32_t index)
{
    auto iter = buildItems_.find(index);
    if (iter != buildItems_.end()) {
        return iter->second;
    }
    auto wrapper = OnGetOrCreateWrapperByIndex(index - startIndex_);
    if (wrapper) {
        buildItems_.emplace(index - startIndex_, wrapper);
    }
    return wrapper;
}

std::list<RefPtr<LayoutWrapper>> LayoutWrapperBuilder::ExpandAllChildWrappers()
{
    auto items = OnExpandChildLayoutWrapper();
    int32_t index = 0;
    for (const auto& item : items) {
        buildItems_.emplace(++index, item);
    }
    return items;
}

void LayoutWrapperBuilder::SwapDirtyChildrenOnMainThread()
{
    for (const auto& child : buildItems_) {
        child.second->SwapDirtyLayoutWrapperOnMainThread();
    }
}

} // namespace OHOS::Ace::NG
