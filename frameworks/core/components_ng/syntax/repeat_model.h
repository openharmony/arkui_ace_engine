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
#include <string>
#include <vector>
#include <memory>

#include "base/utils/macros.h"

namespace OHOS::Ace {

class ACE_EXPORT RepeatModel {
public:
    static RepeatModel* GetInstance();
    virtual ~RepeatModel() = default;

    // Only implemented by RepeatModelNG
    virtual void StartRender() = 0;
    virtual void FinishRender(std::list<int32_t>& removedElmtId) = 0;

    virtual void MoveChild(uint32_t fromIndex) = 0;

    virtual void CreateNewChildStart(const std::string& key) = 0;
    virtual void CreateNewChildFinish(const std::string& key) = 0;
    virtual void AfterAddChild() = 0;
    virtual void OnMove(std::function<void(int32_t, int32_t)>&& onMove) = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_H
