/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_UI_EXTESNION_NATIVE_SECURITY_UI_EXTESNION
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_UI_EXTESNION_NATIVE_SECURITY_UI_EXTESNION

#include "ani.h"

#include <string>

namespace OHOS::Ace::Ani {
class NativeSecurityUiExtension {
public:
    static ani_status BindNativeSecurityUiExtension(ani_env *env);
    static ani_status BindNativeSecurityUiExtensionComponent(ani_env *env);

private:
    // SecurityUiExtensionModal
    static ani_status SetSecurityUiextensionOption(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object obj);
    static ani_status SetSecurityUiextensionWant(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object obj);
    static ani_status SetSecurityOnResult(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj);
    static ani_status SetSecurityOnError(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj);
    static ani_status SetSecurityOnRecive(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj);
    static ani_status SetSecurityOnTerminate(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj);
    static ani_status SetSecurityOnRelease(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj);
    static ani_status SetSecurityOnDrawReady(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
        [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object callbackObj);
};
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_UI_EXTESNION_NATIVE_SECURITY_UI_EXTESNION