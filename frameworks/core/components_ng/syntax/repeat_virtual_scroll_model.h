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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SYNTAX_REPEAT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SYNTAX_REPEAT_MODEL_H

#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace {

class ACE_EXPORT RepeatVirtualScrollModel {
public:
    RepeatVirtualScrollModel() = default;
    virtual ~RepeatVirtualScrollModel() = default;

    static RepeatVirtualScrollModel* GetInstance();
    virtual void Create(
        uint32_t totalCount,
        const std::map<std::string, std::pair<bool, uint32_t>>& templateCachedCountMap,
        const std::function<void(uint32_t forIndex)>& onCreateNode,
        const std::function<void(const std::string& fromKey, uint32_t forIndex)>& onUpdateNode,
        const std::function<std::list<std::string>(uint32_t from, uint32_t to)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t from, uint32_t to)>& onGetTypes4Range,
        const std::function<void(int32_t from, int32_t to)>& onSetActiveRange) = 0;
    virtual void UpdateRenderState(uint32_t totalCount, bool visibleItemsChanged) = 0;
    virtual void OnMove(std::function<void(int32_t, int32_t)>&& onMove) = 0;
    virtual void SetCreateByTemplate(bool isCreatedByTemplate) = 0;

private:
    static std::unique_ptr<RepeatVirtualScrollModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_H
