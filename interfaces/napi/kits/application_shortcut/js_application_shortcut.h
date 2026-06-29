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

#ifndef FOUNDATION_ACE_INTERFACES_NAPI_KITS_APPLICATION_SHORTCUT_JS_APPLICATION_SHORTCUT_H
#define FOUNDATION_ACE_INTERFACES_NAPI_KITS_APPLICATION_SHORTCUT_JS_APPLICATION_SHORTCUT_H

#include <string>

#include "interfaces/napi/kits/utils/napi_utils.h"

namespace OHOS::Ace::Napi {

class ApplicationShortcutCallback {
public:
    ApplicationShortcutCallback(napi_env env, napi_value callback);
    ~ApplicationShortcutCallback();

    void Execute(int32_t triggerInstanceId);
    bool NapiEqual(napi_env env, napi_value cb);

private:
    void ExecuteInner(int32_t triggerInstanceId);

    napi_env env_ = nullptr;
    napi_ref callback_ = nullptr;
};

} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_NAPI_KITS_APPLICATION_SHORTCUT_JS_APPLICATION_SHORTCUT_H
