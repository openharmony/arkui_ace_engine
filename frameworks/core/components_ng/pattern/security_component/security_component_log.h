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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LOG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LOG_H
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
#define SC_LOG_FATAL(fmt, ...)  \
    TAG_LOGF(AceLogTag::ACE_SECURITY_COMPONENT, fmt, ##__VA_ARGS__)
#define SC_LOG_ERROR(fmt, ...)  \
    TAG_LOGE(AceLogTag::ACE_SECURITY_COMPONENT, fmt, ##__VA_ARGS__)
#define SC_LOG_WARN(fmt, ...)  \
    TAG_LOGW(AceLogTag::ACE_SECURITY_COMPONENT, fmt, ##__VA_ARGS__)
#define SC_LOG_INFO(fmt, ...)  \
    TAG_LOGI(AceLogTag::ACE_SECURITY_COMPONENT, fmt, ##__VA_ARGS__)
#define SC_LOG_DEBUG(fmt, ...)  \
    TAG_LOGD(AceLogTag::ACE_SECURITY_COMPONENT, fmt, ##__VA_ARGS__)
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_LOG_H
