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

#ifndef ARKCOMPILER_TOOLCHAIN_HILOG_WRAPPER_H
#define ARKCOMPILER_TOOLCHAIN_HILOG_WRAPPER_H

#include "hilog/log.h"

namespace OHOS::Ace::Framework {
#ifdef LOGF
#undef LOGF
#endif
#ifdef LOGE
#undef LOGE
#endif
#ifdef LOGW
#undef LOGW
#endif
#ifdef LOGI
#undef LOGI
#endif
#ifdef LOGD
#undef LOGD
#endif

static constexpr OHOS::HiviewDFX::HiLogLabel LABEL = {
    LOG_CORE,
    0xD003F00,
    "ArkCompiler"
};

#define LOGF(fmt, ...) OHOS::HiviewDFX::HiLog::Fatal(LABEL, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) OHOS::HiviewDFX::HiLog::Error(LABEL, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) OHOS::HiviewDFX::HiLog::Warn(LABEL, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) OHOS::HiviewDFX::HiLog::Info(LABEL, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) OHOS::HiviewDFX::HiLog::Debug(LABEL, fmt, ##__VA_ARGS__)
} // namespace OHOS::Ace::Framework
#endif // ARKCOMPILER_TOOLCHAIN_HILOG_WRAPPER_H
