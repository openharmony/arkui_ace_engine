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

#include "js_mistouch_prevention.h"

#include <algorithm>
#include <cmath>
#include <sstream>

namespace OHOS::Ace::Napi {
using namespace OHOS::Ace;

napi_value MistouchPrevention::GetItemsInShapePath(napi_env env, napi_callback_info info)
{
    LOGI("GetItemsInShapePath start");
    size_t argc = 1;
    napi_value args[1] = { nullptr };

    napi_env napiEnv = env;
    napi_get_cb_info(napiEnv, info, &argc, args, nullptr, nullptr);
    napi_value imagesValue;
    napi_get_named_property(env, args[0], "images", &imagesValue);
    return imagesValue;
}

} // namespace OHOS::Ace::Napi