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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_H

#include <cstdint>
#include <functional>
#include <list>
#include <string>
#include <vector>

#include "base/utils/macros.h"

namespace OHOS::Ace::NG {
struct ForEachFunc {
    std::function<std::vector<std::string>()> idGenFunc_;
    std::function<void(int32_t index)> itemGenFunc_;
};

class ACE_EXPORT ForEach {
public:
    static void Create(const ForEachFunc& ForEachFunc);

    static const std::list<std::string>& GetCurrentIdList(int32_t nodeId);

    static void SetNewIds(std::list<std::string>&& newIds);

    // Partial Update path.
    static void Create();

    static void CreateNewChildStart(const std::string& id);

    static void CreateNewChildFinish(const std::string& id);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_H
