/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ace/ui_window.h"

#include "utils.h"

namespace OHOS::Ace::NG {

#if defined(WINDOWS_PLATFORM)
constexpr char ACE_LIB_NAME[] = "libace.dll";
#elif defined(MAC_PLATFORM)
constexpr char ACE_LIB_NAME[] = "libace.dylib";
#elif defined(LINUX_PLATFORM)
constexpr char ACE_LIB_NAME[] = "libace.so";
#else
constexpr char ACE_LIB_NAME[] = "libace.z.so";
#endif

using CreateWindowExtensionFunc = std::shared_ptr<UIWindow>* (*)(const std::shared_ptr<AbilityRuntime::Context>&,
    const sptr<Rosen::ISession>&);
constexpr char CREATE_WINDOW_EXTENSION_FUNC[] = "OHOS_ACE_CreateWindowExtension";

std::shared_ptr<UIWindow> UIWindow::CreateWindowExtension(
    const std::shared_ptr<AbilityRuntime::Context>& context, const sptr<Rosen::ISession>& iSession)
{
    LIBHANDLE handle = LOADLIB(ACE_LIB_NAME);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateWindowExtensionFunc>(LOADSYM(handle, CREATE_WINDOW_EXTENSION_FUNC));
    if (entry == nullptr) {
        FREELIB(handle);
        return nullptr;
    }

    auto uiWindowPtr = entry(context, iSession);
    FREELIB(handle);
    if (uiWindowPtr == nullptr) {
        return nullptr;
    }
    std::shared_ptr<UIWindow> uiWindow = *uiWindowPtr;
    delete uiWindowPtr;

    return uiWindow;
}
} // namespace OHOS::Ace::NG
