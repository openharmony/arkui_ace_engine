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
#include "layered_drawable_descriptor_peer.h"

#include "frameworks/core/common/resource/resource_manager.h"

#ifdef PREVIEW
#ifdef WINDOWS_PLATFORM
#include <direct.h>
#include <windows.h>
#ifdef ERROR
#undef ERROR
#endif
#elif defined(MAC_PLATFORM)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#endif
#endif

// define for get resource path in preview scenes
const static char PREVIEW_LOAD_RESOURCE_ID[] = "ohos_drawable_descriptor_path";
#ifdef PREVIEW
#ifdef WINDOWS_PLATFORM
constexpr static char PREVIEW_LOAD_RESOURCE_PATH[] = "\\resources\\resources.index";
#else
constexpr static char PREVIEW_LOAD_RESOURCE_PATH[] = "/resources/resources.index";
#endif

#ifdef LINUX_PLATFORM
const static size_t MAX_PATH_LEN = 255;
#endif
#endif

using namespace OHOS::Ace::NG;

DrawableDescriptorPeer* LayeredDrawableDescriptorPeer::GetForeground() const
{
    return PeerUtils::CreatePeer<DrawableDescriptorPeer>(foreground);
}

DrawableDescriptorPeer* LayeredDrawableDescriptorPeer::GetBackground() const
{
    return PeerUtils::CreatePeer<DrawableDescriptorPeer>(background);
}

DrawableDescriptorPeer* LayeredDrawableDescriptorPeer::GetMask() const
{
    return PeerUtils::CreatePeer<DrawableDescriptorPeer>(mask);
}

std::string LayeredDrawableDescriptorPeer::GetStaticMaskClipPath()
{
    std::string data;
    auto resourceObject =
        AceType::MakeRefPtr<OHOS::Ace::ResourceObject>("", "", OHOS::Ace::Container::CurrentIdSafely());
    CHECK_NULL_RETURN(resourceObject, data);
    auto adapter = OHOS::Ace::ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    CHECK_NULL_RETURN(adapter, data);
#ifdef PREVIEW
    std::string pathTmp = "";
#ifdef WINDOWS_PLATFORM
    char pathBuf[MAX_PATH];
    _getcwd(pathBuf, MAX_PATH);
    pathTmp = pathBuf;
#elif defined(MAC_PLATFORM)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);

    char pathBuf[size + 1];
    if (_NSGetExecutablePath(pathBuf, &size) != 0) {
        pathBuf[0] = '\0';
        LOGE("Arkoala: Failed, buffer too small!");
    }
    pathBuf[size] = '\0';

    std::string previewFullPath = pathBuf;
    size_t lastPathIdx = previewFullPath.find_last_of("\\/");
    pathTmp = (lastPathIdx != std::string::npos) ? previewFullPath.substr(0, lastPathIdx) : "";
#else
    char pathBuf[MAX_PATH_LEN];
    readlink("/proc/self/exe", pathBuf, MAX_PATH_LEN);
    pathTmp = pathBuf;
#endif
    size_t lastPathSepLoc = pathTmp.find_last_of("\\/");
    std::string path = (lastPathSepLoc != std::string::npos) ? pathTmp.substr(0, lastPathSepLoc) : "";
    path += PREVIEW_LOAD_RESOURCE_PATH;
    OHOS::Ace::ResourceInfo info;
    info.SetPackagePath(path);
    adapter->Init(info);
#endif
    data = adapter->GetStringByName(PREVIEW_LOAD_RESOURCE_ID);
    return data;
}
