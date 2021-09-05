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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_H

#include <vector>

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::Framework {
class BackendDelegate : public AceType {
    DECLARE_ACE_TYPE(BackendDelegate, AceType);

public:
    BackendDelegate() = default;
    ~BackendDelegate() override = default;

    // posting js task from jsengine
    virtual void PostJsTask(std::function<void()>&& task) = 0;

    virtual void* GetAbility() = 0;
    virtual BackendType GetType() = 0;

    virtual SingleTaskExecutor GetAnimationJsTask() = 0;

    virtual bool GetAssetContent(const std::string &url, std::string &content) = 0;
    virtual bool GetAssetContent(const std::string &url, std::vector<uint8_t> &content) = 0;

    virtual void AddTaskObserver(std::function<void()> &&task) = 0;
    virtual void RemoveTaskObserver() = 0;

    ACE_DISALLOW_COPY_AND_MOVE(BackendDelegate);
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_BACKEND_DELEGATE_H
