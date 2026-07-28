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
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace OHOS::Ace::NG {

bool LazyForEachUtils::enableCustomComponentFreeze_ = false;

std::vector<std::string> LazyForEachUtils::idsForRepeatAnimationAllowReuse_;

LazyForEachMemOptStrategy LazyForEachUtils::lazyForEachMemOptStrategy_ = LazyForEachMemOptStrategy::UNDEFINED;

RepeatMemOptStrategy LazyForEachUtils::repeatMemOptStrategy_ = RepeatMemOptStrategy::UNDEFINED;

ReusableMemOptStrategy LazyForEachUtils::reusableMemOptStrategy_ = ReusableMemOptStrategy::UNDEFINED;

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

void LazyForEachUtils::SetLazyForEachMemOptStrategy(std::string strategy)
{
    lazyForEachMemOptStrategy_ = strategy == "ENABLE_AUTO_CACHE_OPTIMIZATION" ?
        LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION : LazyForEachMemOptStrategy::DEFAULT;
}

LazyForEachMemOptStrategy LazyForEachUtils::GetLazyForEachMemOptStrategy()
{
    return lazyForEachMemOptStrategy_;
}

void LazyForEachUtils::SetRepeatMemOptStrategy(std::string strategy)
{
    repeatMemOptStrategy_ = strategy == "ENABLE_AUTO_CACHE_OPTIMIZATION" ?
        RepeatMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION : RepeatMemOptStrategy::DEFAULT;
}

RepeatMemOptStrategy LazyForEachUtils::GetRepeatMemOptStrategy()
{
    return repeatMemOptStrategy_;
}

void LazyForEachUtils::SetReusableMemOptStrategy(std::string strategy)
{
    reusableMemOptStrategy_ = strategy == "ENABLE_AUTO_CACHE_OPTIMIZATION" ?
        ReusableMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION : ReusableMemOptStrategy::DEFAULT;
}

ReusableMemOptStrategy LazyForEachUtils::GetReusableMemOptStrategy()
{
    return reusableMemOptStrategy_;
}

void LazyForEachUtils::ParseMetaData(const std::string& name, const std::string& value)
{
    if (name == "enableCustomComponentFreeze" && value == "true") {
        SetEnableCustomComponentFreeze(true);
    } else if (name == "idsForRepeatAnimationAllowReuse") {
        SetIdsForRepeatAnimationAllowReuse(value);
    } else if (name == "repeatMemoryOptimizationStrategy") {
        SetRepeatMemOptStrategy(value);
    } else if (name == "lazyForEachMemoryOptimizationStrategy") {
        SetLazyForEachMemOptStrategy(value);
    } else if (name == "reusableMemoryOptimizationStrategy") {
        SetReusableMemOptStrategy(value);
    }
}

} // namespace OHOS::Ace::NG