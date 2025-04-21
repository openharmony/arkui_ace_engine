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
#include "core/components_ng/syntax/for_each_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ForEachModelNG : public ForEachModel {
public:
    virtual ~ForEachModelNG() override = default;
    void Pop() override;
    
    void Create(const std::string& compilerGenId, const OHOS::Ace::ForEachFunc& ForEachFunc) override;
    std::list<std::string> GetCurrentIdList(int32_t nodeId) override;

    void SetNewIds(std::list<std::string>&& newIds) override;
    void SetRemovedElmtIds(std::list<int32_t>& removedElmtId) override;

    // Partial Update path.
    void Create() override;

    void CreateNewChildStart(const std::string& id) override;
    void CreateNewChildFinish(const std::string& id) override;

    void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop) override;
    void OnMove(std::function<void(int32_t, int32_t)>&& onMove) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_H
