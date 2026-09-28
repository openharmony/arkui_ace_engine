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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_ASYNC_LOAD_CONFIG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_ASYNC_LOAD_CONFIG_H

#include <cstdint>
#include <optional>
#include <string>

namespace OHOS::Ace {

/**
 * Configuration of asynchronous loading of a custom component, as declared by
 * CustomComponentAsyncLoadOptions on the public API side.
 *
 * Carried from the puv2 side into NG through NodeInfoPU. All members are value
 * copies: no JS object reference is retained, so the configuration stays valid
 * independently of the JS runtime's object lifetime.
 *
 * The placeholder size is intentionally absent. SizeOptions allows a Resource,
 * which cannot be serialized across the JS/C++ boundary here; a placeholder
 * without an explicit size keeps its template's own layout.
 */
struct AsyncLoadConfig {
    // Placeholder template id. Empty means no placeholder is configured, which
    // covers both an omitted placeholder and an explicitly empty id.
    std::string placeholderId;
    // Timeout threshold in ms. Absent means the framework default is used.
    // A negative value never times out; zero force-loads in subsequent frames.
    std::optional<int32_t> timeoutMs;

    bool HasPlaceholder() const
    {
        return !placeholderId.empty();
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_ASYNC_LOAD_CONFIG_H
