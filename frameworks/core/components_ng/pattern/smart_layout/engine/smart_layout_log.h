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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_SMART_LAYOUT_LOG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_SMART_LAYOUT_LOG_H

#include "hilog/log.h"

namespace OHOS::Ace::NG {

// Use ACE Engine's domain for consistency
constexpr uint32_t ACE_DOMAIN = 0xD003900;
constexpr const char* SMART_LAYOUT_TAG = "SmartLayout";

#define SMT_LOGD(fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_DEBUG, ACE_DOMAIN, SMART_LAYOUT_TAG, "[%{public}s] " fmt, \
        SMART_LAYOUT_TAG, ##__VA_ARGS__)
#define SMT_LOGI(fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_INFO, ACE_DOMAIN, SMART_LAYOUT_TAG, "[%{public}s] " fmt, \
        SMART_LAYOUT_TAG, ##__VA_ARGS__)
#define SMT_LOGW(fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_WARN, ACE_DOMAIN, SMART_LAYOUT_TAG, "[%{public}s] " fmt, \
        SMART_LAYOUT_TAG, ##__VA_ARGS__)
#define SMT_LOGE(fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_ERROR, ACE_DOMAIN, SMART_LAYOUT_TAG, "[%{public}s] " fmt, \
        SMART_LAYOUT_TAG, ##__VA_ARGS__)

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SMART_LAYOUT_ENGINE_SMART_LAYOUT_LOG_H