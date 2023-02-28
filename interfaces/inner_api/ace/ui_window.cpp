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

#include <dlfcn.h>

namespace OHOS::Ace::NG {

using CreateRootSceneFunc = UIWindow* (*)();
using CreateWindowSceneFunc = UIWindow* (*)(const std::shared_ptr<AbilityRuntime::Context>&,
    const sptr<Rosen::ISession>&, const std::shared_ptr<Rosen::RSSurfaceNode>&);
using CreateWindowExtensionFunc = UIWindow* (*)(const std::shared_ptr<AbilityRuntime::Context>&,
    const sptr<Rosen::ISession>&, const std::shared_ptr<Rosen::RSSurfaceNode>&);
constexpr char CREATE_ROOT_SCENE_FUNC[] = "OHOS_ACE_CreateRootScene";
constexpr char CREATE_WINDOW_SCENE_FUNC[] = "OHOS_ACE_CreateWindowScene";
constexpr char CREATE_WINDOW_EXTENSION_FUNC[] = "OHOS_ACE_CreateWindowExtension";

UIWindow* CreateRootSceneFromLib()
{
    void* handle = dlopen("libace.z.so", RTLD_LAZY);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateRootSceneFunc>(dlsym(handle, CREATE_ROOT_SCENE_FUNC));
    dlclose(handle);
    if (entry == nullptr) {
        return nullptr;
    }

    return entry();
}

UIWindow* CreateWindowSceneFromLib(const std::shared_ptr<AbilityRuntime::Context>& context,
    const sptr<Rosen::ISession>& iSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    void* handle = dlopen("libace.z.so", RTLD_LAZY);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateWindowSceneFunc>(dlsym(handle, CREATE_WINDOW_SCENE_FUNC));
    dlclose(handle);
    if (entry == nullptr) {
        return nullptr;
    }

    return entry(context, iSession, surfaceNode);
}

UIWindow* CreateWindowExtensionFromLib(const std::shared_ptr<AbilityRuntime::Context>& context,
    const sptr<Rosen::ISession>& iSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    void* handle = dlopen("libace.z.so", RTLD_LAZY);
    if (handle == nullptr) {
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateWindowExtensionFunc>(dlsym(handle, CREATE_WINDOW_EXTENSION_FUNC));
    dlclose(handle);
    if (entry == nullptr) {
        return nullptr;
    }

    return entry(context, iSession, surfaceNode);
}

std::shared_ptr<UIWindow> UIWindow::CreateRootScene()
{
    std::shared_ptr<UIWindow> rootScene(CreateRootSceneFromLib());
    return rootScene;
}

std::shared_ptr<UIWindow> UIWindow::CreateWindowScene(const std::shared_ptr<AbilityRuntime::Context>& context,
    const sptr<Rosen::ISession>& iSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    std::shared_ptr<UIWindow> window(CreateWindowSceneFromLib(context, iSession, surfaceNode));
    return window;
}

std::shared_ptr<UIWindow> UIWindow::CreateWindowExtension(const std::shared_ptr<AbilityRuntime::Context>& context,
    const sptr<Rosen::ISession>& iSession, const std::shared_ptr<Rosen::RSSurfaceNode>& surfaceNode)
{
    std::shared_ptr<UIWindow> window(CreateWindowExtensionFromLib(context, iSession, surfaceNode));
    return window;
}

} // namespace OHOS::Ace::NG
