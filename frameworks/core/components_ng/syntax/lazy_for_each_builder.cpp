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

#include "core/components_ng/syntax/lazy_for_each_builder.h"

namespace OHOS::Ace::NG {
    std::pair<std::string, RefPtr<UINode>> LazyForEachBuilder::GetChildByIndex(int32_t index, bool needBuild)
    {
        auto iter = cachedItems_.find(index);
        if (iter != cachedItems_.end()) {
            if (iter->second.second) {
                return iter->second;
            }
            auto keyIter = expiringItem_.find(iter->second.first);
            if (keyIter != expiringItem_.end() && keyIter->second.second) {
                iter->second.second = keyIter->second.second;
                expiringItem_.erase(keyIter);
                return iter->second;
            }
        }

        if (needBuild) {
            ACE_SCOPED_TRACE("Builder:BuildLazyItem [%d]", index);
            auto itemInfo = OnGetChildByIndex(index, expiringItem_);
            CHECK_NULL_RETURN(itemInfo.second, itemInfo);
            {
                cachedItems_[index] = itemInfo;
            }
            return itemInfo;
        }
        return {};
    }
}
