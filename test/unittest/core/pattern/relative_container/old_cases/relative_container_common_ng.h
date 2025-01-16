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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_COMMON_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_COMMON_NG_H

#include <map>

#include "core/components/common/layout/position_param.h"

namespace OHOS::Ace {

class RelativeContainerTestUtilsNG {
public:
    static void AddAlignRule(const std::string& id, const AlignDirection& direction,
        const HorizontalAlign& horizontalRule, std::map<AlignDirection, AlignRule>& alignRules);
    static void AddAlignRule(const std::string& id, const AlignDirection& direction, const VerticalAlign& verticalRule,
        std::map<AlignDirection, AlignRule>& alignRules);
    static AlignDirection AlignDirectionRtl(const AlignDirection& direction);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_COMMON_NG_H