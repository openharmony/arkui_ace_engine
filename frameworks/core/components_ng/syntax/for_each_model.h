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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SYNTAX_FOR_EACH_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SYNTAX_FOR_EACH_MODEL_H

#include <cstdint>
#include <functional>
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <mutex>

#include "base/utils/macros.h"

namespace OHOS::Ace {

struct ForEachFunc {
    std::function<std::vector<std::string>()> idGenFunc_;
    std::function<void(int32_t index)> itemGenFunc_;
};

class ACE_FORCE_EXPORT ForEachModel {
public:
    static ForEachModel* GetInstance();
    virtual ~ForEachModel() = default;

    virtual void Pop() = 0;

    // classic / full update code path
    virtual void Create(const std::string& compilerGenId, const ForEachFunc& ForEachFunc) = 0;

    // Only implemented by ForEachModelNG
    virtual void Create() = 0;

    virtual std::list<std::string> GetCurrentIdList(int32_t nodeId) = 0;
    virtual void SetNewIds(std::list<std::string>&& newIds) = 0;
    virtual void SetRemovedElmtIds(std::list<int32_t>& removedElmtId) = 0;

    virtual void CreateNewChildStart(const std::string& id) = 0;
    virtual void CreateNewChildFinish(const std::string& id) = 0;

    virtual void OnMove(std::function<void(int32_t, int32_t)>&& onMove) = 0;
    virtual void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop) = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_H
