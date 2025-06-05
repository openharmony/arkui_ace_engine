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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_EXPANDED_MENU_PLUGIN_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_EXPANDED_MENU_PLUGIN_LOADER_H

#ifndef WINDOWS_PLATFORM
#include <dlfcn.h>
#endif

namespace OHOS::Ace::NG {

class ExpandedMenuPluginLoader {
#if (defined(__aarch64__) || defined(__x86_64__))
    const std::string EXPANDED_MENU_PLUGIN_SO_PATH = "/system/lib64/expanded_menu/libexpanded_menu.z.so";
#else
    const std::string EXPANDED_MENU_PLUGIN_SO_PATH = "/system/lib/expanded_menu/libexpanded_menu.z.so";
#endif
    typedef void (*CreateDeviceMenuFunc)(
        const RefPtr<FrameNode>& menuWrapper,
        const std::shared_ptr<SelectOverlayInfo>& info
    );

    typedef const char* (*GetStoreUrlFrontFunc)();
    typedef const char* (*GetAPPNameFunc)(TextDataDetectType type);

public:
    static ExpandedMenuPluginLoader& GetInstance()
    {
        static ExpandedMenuPluginLoader instance;
        return instance;
    }

    bool LoadPlugin()
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_RETURN(!createDeviceMenu, true);
        expandedMenuPluginHandle = dlopen(EXPANDED_MENU_PLUGIN_SO_PATH.c_str(), RTLD_LAZY);
        if (!expandedMenuPluginHandle) {
            TAG_LOGI(AceLogTag::ACE_MENU, "dlopen lib %{public}s Fail", EXPANDED_MENU_PLUGIN_SO_PATH.c_str());
            return false;
        }
        TAG_LOGI(AceLogTag::ACE_MENU, "dlopen lib %{public}s success", EXPANDED_MENU_PLUGIN_SO_PATH.c_str());
        createDeviceMenu = (CreateDeviceMenuFunc)(dlsym(expandedMenuPluginHandle, "CreateDeviceMenu"));
        if (!createDeviceMenu) {
            TAG_LOGI(AceLogTag::ACE_MENU, "CreateDeviceMenu func load failed");
            return false;
        }
        return true;
#endif
    }

    bool LoadStoreUrlFront()
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_RETURN(!getStoreUrlFront, true);
        expandedMenuPluginHandle = dlopen(EXPANDED_MENU_PLUGIN_SO_PATH.c_str(), RTLD_LAZY);
        if (!expandedMenuPluginHandle) {
            TAG_LOGI(AceLogTag::ACE_MENU, "dlopen lib %{public}s Fail", EXPANDED_MENU_PLUGIN_SO_PATH.c_str());
            return false;
        }
        TAG_LOGI(AceLogTag::ACE_MENU, "dlopen lib %{public}s success", EXPANDED_MENU_PLUGIN_SO_PATH.c_str());
        getStoreUrlFront = (GetStoreUrlFrontFunc)(dlsym(expandedMenuPluginHandle, "GetStoreUrlFront"));
        if (!getStoreUrlFront) {
            TAG_LOGI(AceLogTag::ACE_MENU, "GetStoreUrlFront func load failed");
            return false;
        }
        return true;
#else
        return false;
#endif
    }

    bool LoadAPPName()
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_RETURN(!getAPPName, true);
        expandedMenuPluginHandle = dlopen(EXPANDED_MENU_PLUGIN_SO_PATH.c_str(), RTLD_LAZY);
        if (!expandedMenuPluginHandle) {
            TAG_LOGI(AceLogTag::ACE_MENU, "dlopen lib %{public}s Fail", EXPANDED_MENU_PLUGIN_SO_PATH.c_str());
            return false;
        }
        getAPPName = (GetAPPNameFunc)(dlsym(expandedMenuPluginHandle, "GetAPPName"));
        if (!getAPPName) {
            TAG_LOGI(AceLogTag::ACE_MENU, "GetAPPName func load failed");
            return false;
        }
        return true;
#else
        return false;
#endif
    }

    std::string GetStoreUrlFront()
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_RETURN(LoadStoreUrlFront(), "");
        if (!getStoreUrlFront) {
            TAG_LOGI(AceLogTag::ACE_MENU, "dynamic get front failed");
            return "";
        }
        std::string result = getStoreUrlFront();
        return result;
#else
        return "";
#endif
    }

    std::string GetAPPName(TextDataDetectType type)
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_RETURN(LoadAPPName(), "");
        if (!getAPPName) {
            TAG_LOGI(AceLogTag::ACE_MENU, "dynamic load name failed");
            return "";
        }
        std::string result = getAPPName(type);
        return result;
#else
        return "";
#endif
    }

    void CreateServiceCollaborationMenu(const RefPtr<FrameNode>& menuWrapper,
        const std::shared_ptr<SelectOverlayInfo>& info)
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_VOID(menuWrapper);
        CHECK_NULL_VOID(info);
        CHECK_NULL_VOID(LoadPlugin());
        if (!createDeviceMenu) {
            TAG_LOGI(AceLogTag::ACE_MENU, "dynamic create expended menu failed");
            return;
        }
        TAG_LOGI(AceLogTag::ACE_MENU, "dynamic create expended menu");
        createDeviceMenu(menuWrapper, info);
        menuWrapper->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
#endif
    }

    bool HasCollaborationMenu()
    {
#ifndef WINDOWS_PLATFORM
        CHECK_NULL_RETURN(LoadPlugin(), false);
        CHECK_NULL_RETURN(createDeviceMenu, false);
        return true;
#else
        return false;
#endif
    }

    void *expandedMenuPluginHandle;
    CreateDeviceMenuFunc createDeviceMenu;
    GetStoreUrlFrontFunc getStoreUrlFront;
    GetAPPNameFunc getAPPName;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_EXPANDED_MENU_PLUGIN_LOADER_H