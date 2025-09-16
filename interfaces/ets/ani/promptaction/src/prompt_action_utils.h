/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_ETS_ANI_PROMPT_ACTION_UTILS_H
#define INTERFACES_ETS_ANI_PROMPT_ACTION_UTILS_H

#include <ani.h>
#include <cstddef>
#include <string>

#include "core/common/ace_engine.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace::Ani {
std::string ErrorToMessage(int32_t code);
std::string GetErrorMsg(int32_t errorCode);
ani_error GetErrorObject(ani_env* env, const std::string& errMsg, int32_t code);
void AniThrow(ani_env* env, const std::string& errMsg, int32_t code);
} // namespace OHOS::Ace::Ani
#endif // #define INTERFACES_ETS_ANI_PROMPT_ACTION_UTILS_H