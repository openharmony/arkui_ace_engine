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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUT_UTILS_H

#include <string>
#include <unordered_map>
#include "core/components/common/properties/alignment.h"

namespace OHOS::Ace::NG {
Alignment ConvertStringToAlignment(std::string localizedAlignment)
{
    static const std::unordered_map<std::string, Alignment> alignmentMap = {
        {"top_start", Alignment::TOP_LEFT}, {"top", Alignment::TOP_CENTER}, {"top_end", Alignment::TOP_RIGHT},
        {"start", Alignment::CENTER_LEFT}, {"center", Alignment::CENTER}, {"end", Alignment::CENTER_RIGHT},
        {"bottom_start", Alignment::BOTTOM_LEFT}, {"bottom", Alignment::BOTTOM_CENTER},
        {"bottom_end", Alignment::BOTTOM_RIGHT}
    };
    auto it = alignmentMap.find(localizedAlignment);
    return it != alignmentMap.end() ? it->second : Alignment::CENTER;
}
} // namespace OHOS::Ace::NG
 
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUT_UTILS_H