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
#include "core/components_ng/syntax/repeat_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RepeatModelNG : public RepeatModel {
public:
    virtual ~RepeatModelNG() override = default;

    // Partial Update path
    void StartRender() override;
    void FinishRender(std::list<int32_t>& removedElmtId) override;

    bool IsInAnimation() override;
    void MoveChild(uint32_t fromIndex) override;
    void CreateNewChildStart(const std::string& key) override;
    void CreateNewChildFinish(const std::string& key) override;
    void AfterAddChild() override;
    
    void OnMove(std::function<void(int32_t, int32_t)>&& onMove) override;
    void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_H
