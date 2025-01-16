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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_H

#include <cstdint>
#include <functional>
#include <list>
#include <string>
#include <vector>

#include "base/utils/macros.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RepeatVirtualScrollModelNG : public RepeatVirtualScrollModel {
public:
    void Create(
        uint32_t totalCount,
        const std::map<std::string, std::pair<bool, uint32_t>>& templateCachedCountMap,
        const std::function<void(uint32_t forIndex)>& onCreateNode,
        const std::function<void(const std::string& fromKey, uint32_t forIndex)>& onUpdateNode,
        const std::function<std::list<std::string>(uint32_t from, uint32_t to)>& onGetKeys4Range,
        const std::function<std::list<std::string>(uint32_t from, uint32_t to)>& onGetTypes4Range,
        const std::function<void(int32_t from, int32_t to)>& onSetActiveRange) override;

    void UpdateRenderState(uint32_t totalCount, bool visibleItemsChanged) override;

    void OnMove(std::function<void(int32_t, int32_t)>&& onMove) override;
    void SetCreateByTemplate(bool isCreatedByTemplate) override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_H
