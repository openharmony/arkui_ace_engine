/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_PARAM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_PARAM_H

#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

struct ACE_FORCE_EXPORT DynamicParam {
    int32_t workerId = 0;
    std::string entryPoint;
    bool backgroundTransparent = false;

    std::string ToString() const
    {
        std::string str;
        str.append("entryPoint: ").append(entryPoint)
            .append(", workerId: ").append(std::to_string(workerId))
            .append(", backgroundTransparent: ").append(std::to_string(backgroundTransparent));
        return str;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UI_EXTENSION_DYNAMIC_PARAM_H
