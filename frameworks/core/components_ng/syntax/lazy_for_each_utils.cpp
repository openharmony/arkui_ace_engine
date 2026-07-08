/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/utils/string_utils.h"
#include "core/components_ng/syntax/lazy_for_each_utils.h"

namespace OHOS::Ace::NG {

bool LazyForEachUtils::enableCustomComponentFreeze_ = false;

std::vector<std::string> LazyForEachUtils::idsForRepeatAnimationAllowReuse_;

void LazyForEachUtils::SetEnableCustomComponentFreeze(bool enableCustomComponentFreeze)
{
    enableCustomComponentFreeze_ = enableCustomComponentFreeze;
}

bool LazyForEachUtils::GetEnableCustomComponentFreeze()
{
    return enableCustomComponentFreeze_;
}

void LazyForEachUtils::SetIdsForRepeatAnimationAllowReuse(const std::string& ids)
{
    StringUtils::SplitStr(ids, ",", idsForRepeatAnimationAllowReuse_);
}

bool LazyForEachUtils::IsIdInRepeatAnimationAllowReuseSet(const std::string& id)
{
    return std::find(idsForRepeatAnimationAllowReuse_.begin(), idsForRepeatAnimationAllowReuse_.end(), id) !=
        idsForRepeatAnimationAllowReuse_.end();
}

} // namespace OHOS::Ace::NG