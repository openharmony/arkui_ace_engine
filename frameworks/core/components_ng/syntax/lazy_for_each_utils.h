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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_FOR_EACH_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_FOR_EACH_UTILS_H

#include "base/utils/macros.h"
#include <string>

namespace OHOS::Ace::NG {

enum class LazyForEachMemOptStrategy;
enum class RepeatMemOptStrategy;
enum class ReusableMemOptStrategy;

class ACE_EXPORT LazyForEachUtils {
public:
    
    static void SetEnableCustomComponentFreeze(bool enableCustomComponentFreeze);

    static bool GetEnableCustomComponentFreeze();

    static void SetIdsForRepeatAnimationAllowReuse(const std::string& ids);

    static bool IsIdInRepeatAnimationAllowReuseSet(const std::string& id);

    static void SetLazyForEachMemOptStrategy(std::string strategy);

    static LazyForEachMemOptStrategy GetLazyForEachMemOptStrategy();

    static void SetRepeatMemOptStrategy(std::string strategy);

    static RepeatMemOptStrategy GetRepeatMemOptStrategy();

    static void SetReusableMemOptStrategy(std::string strategy);

    static ReusableMemOptStrategy GetReusableMemOptStrategy();

    static void ParseMetaData(const std::string& name, const std::string & value);

private:
    static bool enableCustomComponentFreeze_;

    static std::vector<std::string> idsForRepeatAnimationAllowReuse_;

    static LazyForEachMemOptStrategy lazyForEachMemOptStrategy_;

    static RepeatMemOptStrategy repeatMemOptStrategy_;

    static ReusableMemOptStrategy reusableMemOptStrategy_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_LAZY_FOR_EACH_UTILS_H