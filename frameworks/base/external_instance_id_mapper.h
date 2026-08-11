/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_EXTERNAL_INSTANCE_ID_MAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_EXTERNAL_INSTANCE_ID_MAPPER_H

#include <cstdint>
#include <mutex>
#include <unordered_map>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/singleton.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ExternalInstanceIdMapper final : public Singleton<ExternalInstanceIdMapper> {
    DECLARE_SINGLETON(ExternalInstanceIdMapper);

public:

    void Add(uint32_t windowId, int32_t instanceId);

    void Remove(uint32_t windowId);

    int32_t GetInstanceId(uint32_t windowId) const;

    int32_t GetWindowId(int32_t instanceId) const;

private:
    mutable std::mutex mutex_;
    std::unordered_map<uint32_t, int32_t> windowToInstance_; // windowId -> instanceId
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_EXTERNAL_INSTANCE_ID_MAPPER_H
