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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_RS_DIR_ASSET_PROVIDER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_RS_DIR_ASSET_PROVIDER_H

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>

#ifdef WINDOWS_PLATFORM
#include <shlwapi.h>
#include <windows.h>
#else
#include <dirent.h>
#include <sys/types.h>
#endif

#include "base/resource/asset_manager.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/rosen/rosen_asset_manager.h"

namespace OHOS::Ace {
class ACE_EXPORT RSDirAssetProvider : public RSAssetProvider {
    DECLARE_ACE_TYPE(RSDirAssetProvider, RSAssetProvider);

public:
#ifdef WINDOWS_PLATFORM
    RSDirAssetProvider(const std::string& basePath) : basePath_(basePath + "\\") {}
#else
    RSDirAssetProvider(const std::string& basePath) : basePath_(basePath + "/") {}
#endif
    ~RSDirAssetProvider() override = default;

    bool IsValid() const override
    {
        return true;
    }

    RefPtr<Asset> GetAsset(const std::string& assetName) const override
    {
        errno = 0;
        LOGI("GetAsset: %{public}s, %{private}s", assetName.c_str(), basePath_.c_str());
        std::string fileName = basePath_ + assetName;
        char realPath[PATH_MAX] = { 0x00 };
        if (!RealPath(fileName, realPath)) {
            return nullptr;
        }
        auto fp = std::fopen(realPath, "rb");
        if (!fp) {
            return nullptr;
        }

        if (std::fseek(fp, 0, SEEK_END) != 0) {
            std::fclose(fp);
            return nullptr;
        }

        size_t size = std::ftell(fp);
        if (size < 0) {
            std::fclose(fp);
            return nullptr;
        }

        auto data = std::make_unique<char[]>(size);
        if (data == nullptr) {
            std::fclose(fp);
            return nullptr;
        }

        if (std::fseek(fp, 0, SEEK_SET) != 0) {
            std::fclose(fp);
            return nullptr;
        }

        auto rsize = std::fread(data.get(), 1, size, fp);
        if (rsize <= 0) {
            std::fclose(fp);
            return nullptr;
        }
        std::fclose(fp);
        LOGI("[%{public}s] length: %{public}zu/%{public}zu success", assetName.c_str(), rsize, size);
        return AceType::MakeRefPtr<RSAsset>(std::move(data), rsize);
    }

    std::string GetAssetPath(const std::string& assetName, bool isAddHapPath) override
    {
        std::string fileName = basePath_ + assetName;
        char realPath[PATH_MAX] = { 0x00 };
        if (!RealPath(fileName, realPath)) {
            return nullptr;
        }
        std::FILE* fp = std::fopen(realPath, "r");
        if (fp == nullptr) {
            return "";
        }
        std::fclose(fp);
        return basePath_;
    }

    void GetAssetList(const std::string& path, std::vector<std::string>& assetList) override
    {
#if defined(WINDOWS_PLATFORM)
        std::string dirPath = basePath_ + "\\" + path;
        WIN32_FIND_DATA fileInfo;
        HANDLE hFind;
        if ((hFind = FindFirstFile(dirPath.append("\\*").c_str(), &fileInfo)) != INVALID_HANDLE_VALUE) {
            do {
                if (strcmp(fileInfo.cFileName, ".") != 0 && strcmp(fileInfo.cFileName, "..") != 0) {
                    assetList.push_back(fileInfo.cFileName);
                }
            } while (FindNextFile(hFind, &fileInfo) != 0);
            FindClose(hFind);
        }
#elif defined(MAC_PLATFORM)
        std::string dirPath = basePath_ + "/" + path;
        DIR* dp = nullptr;
        if (nullptr == (dp = opendir(dirPath.c_str()))) {
            return;
        }
        struct dirent* dptr = nullptr;
        while ((dptr = readdir(dp)) != nullptr) {
            if (strcmp(dptr->d_name, ".") != 0 && strcmp(dptr->d_name, "..") != 0) {
                assetList.push_back(dptr->d_name);
            }
        }
        closedir(dp);
#endif
    }

private:
    std::string basePath_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_RS_DIR_ASSET_PROVIDER_H
