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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_JS_MISTOUCH_PREVENTION_H_
#define FOUNDATION_ACE_INTERFACE_INNERKITS_JS_MISTOUCH_PREVENTION_H_

#include <iostream>
#include <js_native_api.h>
#include <napi/native_api.h>
#include <vector>

#include "base/log/log.h"

#undef LOG_TAG
#define LOG_TAG "MISTOUCH_PREVENTION"
namespace OHOS::Ace::Napi {

class MistouchPrevention final {
public:
    static napi_value GetItemsInShapePath(napi_env env, napi_callback_info thisVar);
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_JS_MISTOUCH_PREVENTION_H_