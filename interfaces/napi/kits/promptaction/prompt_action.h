/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_NAPI_KITS_PROMPTACTION_PROMPT_ACTION_H_
#define INTERFACES_NAPI_KITS_PROMPTACTION_PROMPT_ACTION_H_

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::Ace::Napi {
napi_value JSPromptShowToast(napi_env env, napi_callback_info info);
napi_value JSPromptOpenToast(napi_env env, napi_callback_info info);
napi_value JSPromptCloseToast(napi_env env, napi_callback_info info);
napi_value JSPromptShowDialog(napi_env env, napi_callback_info info);
napi_value JSPromptShowActionMenu(napi_env env, napi_callback_info info);
napi_value JSPromptOpenCustomDialog(napi_env env, napi_callback_info info);
napi_value JSPromptOpenCustomDialogWithController(napi_env env, napi_callback_info info);
napi_value JSPromptPresentCustomDialog(napi_env env, napi_callback_info info);
napi_value JSPromptUpdateCustomDialog(napi_env env, napi_callback_info info);
napi_value JSPromptCloseCustomDialog(napi_env env, napi_callback_info info);
} // namespace OHOS::Ace::Napi
#endif // INTERFACES_NAPI_KITS_PROMPTACTION_PROMPT_ACTION_H_
