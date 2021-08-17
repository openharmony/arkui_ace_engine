/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_BACKEND_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_BACKEND_H

#include "base/memory/ace_type.h"
#include "base/thread/task_executor.h"
#include "core/common/js_message_dispatcher.h"

namespace OHOS::Ace {
enum class BackendType { SERVICE, DATA };

class ACE_EXPORT Backend : public AceType {
    DECLARE_ACE_TYPE(Backend, AceType);

public:
    Backend() = default;
    ~Backend() override = default;

    enum class State { ON_CREATE, ON_DESTROY };

    static RefPtr<Backend> Create();
    static RefPtr<Backend> CreateDefault();

    virtual bool Initialize(BackendType type, const RefPtr<TaskExecutor>& taskExecutor) = 0;

    virtual void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher> &transfer) const = 0;

    virtual BackendType GetType() = 0;

    // inform the frontend that onCreate or onDestroy
    virtual void UpdateState(State) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_BACKEND_H
