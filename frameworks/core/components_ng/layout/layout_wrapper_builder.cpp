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
    auto realIndex = index - startIndex_;
    auto iter = wrapperMap_.find(realIndex);
    if (iter != wrapperMap_.end()) {
        return iter->second;
    }
    auto wrapper = OnGetOrCreateWrapperByIndex(realIndex);
    CHECK_NULL_RETURN(wrapper, nullptr);
    wrapperMap_.try_emplace(realIndex, wrapper);
    return wrapper;
}

const std::list<RefPtr<LayoutWrapper>>& LayoutWrapperBuilder::ExpandAllChildWrappers()
{
    return OnExpandChildLayoutWrapper();
}

void LayoutWrapperBuilder::RemoveAllChildInRenderTree()
{
    for (auto& child : wrapperMap_) {
        child.second->SetActive(false);
    }
}

} // namespace OHOS::Ace::NG
