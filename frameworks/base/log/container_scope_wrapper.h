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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_CONTAINER_SCOPE_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_CONTAINER_SCOPE_WRAPPER_H

#include "core/common/container_scope.h"

#define CONTAINER_SCOPE_CONCAT_IMPL(name, line) name##line
#define CONTAINER_SCOPE_CONCAT(name, line) CONTAINER_SCOPE_CONCAT_IMPL(name, line)

#ifdef ENABLE_CONTAINER_SCOPE_TRACKING
#define CURRENT_ID_PUSH(id, sourceType) \
    OHOS::Ace::ContainerScope::PushCurrent((id), __FILE__, __LINE__, static_cast<int32_t>(sourceType))

#define CURRENT_ID_POP(uid, restoreId, sourceType) \
    OHOS::Ace::ContainerScope::PopCurrent((uid), (restoreId), __FILE__, __LINE__, static_cast<int32_t>(sourceType))

#define CONTAINER_SCOPE(id) \
    OHOS::Ace::ContainerScope CONTAINER_SCOPE_CONCAT(containerScope_, __LINE__)((id), __FILE__, __LINE__)
#define CONTAINER_SCOPE_ENABLE(id, enable) \
    OHOS::Ace::ContainerScope CONTAINER_SCOPE_CONCAT(containerScope_, __LINE__)((id), (enable), __FILE__, __LINE__)
#else
#define CURRENT_ID_PUSH(id, sourceType) \
    (OHOS::Ace::ContainerScope::UpdateCurrent((id)), 0ULL)

#define CURRENT_ID_POP(uid, restoreId, sourceType) \
    OHOS::Ace::ContainerScope::UpdateCurrent((restoreId))

#define CONTAINER_SCOPE(id) \
    OHOS::Ace::ContainerScope CONTAINER_SCOPE_CONCAT(containerScope_, __LINE__)((id))
#define CONTAINER_SCOPE_ENABLE(id, enable) \
    OHOS::Ace::ContainerScope CONTAINER_SCOPE_CONCAT(containerScope_, __LINE__)((id), (enable))
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_CONTAINER_SCOPE_WRAPPER_H
