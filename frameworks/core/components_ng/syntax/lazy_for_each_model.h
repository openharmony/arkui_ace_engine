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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_FOR_EACH_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_FOR_EACH_MODEL_H

#include <mutex>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace {

class LazyForEachActuator : public AceType {
    DECLARE_ACE_TYPE(LazyForEachActuator, AceType)
public:
    LazyForEachActuator() = default;
    ~LazyForEachActuator() override = default;
};

class ACE_FORCE_EXPORT LazyForEachModel {
public:
    static LazyForEachModel* GetInstance();
    virtual ~LazyForEachModel() = default;

    virtual void Create(const RefPtr<LazyForEachActuator>& actuator) = 0;
    virtual void OnMove(std::function<void(int32_t, int32_t)>&& onMove) = 0;
    virtual void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress,
        std::function<void(int32_t)>&& onDragStart, std::function<void(int32_t, int32_t)>&& onMoveThrough,
        std::function<void(int32_t)>&& onDrop) = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_FOR_EACH_MODEL_H
