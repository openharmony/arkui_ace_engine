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

#ifndef INTERFACES_INNER_API_ACE_ARKUI_LOG_H
#define INTERFACES_INNER_API_ACE_ARKUI_LOG_H

#include "hilog/log.h"

#define PRINT_HILOG(level, fmt, ...) \
    HILOG_IMPL(LOG_CORE, LOG_##level, 0xD003900, "AceDrawableDescriptor", "[%{public}d]" fmt, \
        __LINE__, ##__VA_ARGS__)

#define HILOGE(fmt, ...) PRINT_HILOG(ERROR, fmt, ##__VA_ARGS__)
#define HILOGW(fmt, ...) PRINT_HILOG(WARN, fmt, ##__VA_ARGS__)
#define HILOGI(fmt, ...) PRINT_HILOG(INFO, fmt, ##__VA_ARGS__)
#define HILOGD(fmt, ...) PRINT_HILOG(DEBUG, fmt, ##__VA_ARGS__)

#endif // INTERFACES_INNER_API_ACE_ARKUI_LOG_H
