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

#include "core/drawable/drawable_descriptor_loader.h"

#include <memory>
#include <string>
#include <vector>

#include "securec.h"

#include "base/base64/base64_util.h"
#include "base/image/file_uri_helper.h"
#include "core/common/resource/resource_manager.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t RAW_TYPE = 30000;
constexpr int32_t MEDIA_TYPE = 20000;
} // namespace

DrawableDescriptorLoader* DrawableDescriptorLoader::GetInstance()
{
    static DrawableDescriptorLoader info;
    return &info;
}

MediaData DrawableDescriptorLoader::LoadData(const RefPtr<DrawableDescriptorInfo>& info)
{
    auto srcType = info->GetSrcType();
    switch (srcType) {
        case DrawableDescriptorInfo::SrcType::RESOURCE: {
            return LoadResourceData(info);
        }
        case DrawableDescriptorInfo::SrcType::BASE64: {
            return LoadBase64Data(info);
        }
        case DrawableDescriptorInfo::SrcType::FILE: {
            return LoadFileData(info);
        }
        default: {
            return {};
        }
    }
}

MediaData DrawableDescriptorLoader::LoadFileData(const RefPtr<DrawableDescriptorInfo>& info)
{
    auto src = info->GetSrc();
    auto iter = src.find_first_of(':');
    std::string result = src.substr(iter + 3);
    auto filePath = FileUriHelper::GetRealPath(result);
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        LOGW("open file failed: %{public}s", filePath.c_str());
        return {};
    }
    std::streamsize fileSize = file.tellg();
    if (fileSize <= 0) {
        LOGW("file is empty or invalid.");
        return {};
    }
    file.seekg(0, std::ios::beg);
    auto buffer = std::make_unique<uint8_t[]>(fileSize);
    if (!buffer) {
        LOGW("memory allocation failed.");
        return { nullptr, 0 };
    }
    if (!file.read(reinterpret_cast<char*>(buffer.get()), fileSize)) {
        LOGW("read file failed.");
        return {};
    }
    return { std::move(buffer), static_cast<size_t>(fileSize) };
}

MediaData DrawableDescriptorLoader::LoadBase64Data(const RefPtr<DrawableDescriptorInfo>& info)
{
    auto src = info->GetSrc();
    auto iter = src.find_first_of(',');
    if (iter == std::string::npos || ((src.size() > 0) && (iter == src.size() - 1))) {
        LOGW("wrong code format!");
        return { nullptr, 0 };
    }
    std::string code(src.c_str() + (iter + 1));
    std::string decodedData;
    auto result = Base64Util::Decode(code, decodedData);
    if (!result) {
        LOGW("base64 decode failed!");
        return { nullptr, 0 };
    }
    auto buffer = std::make_unique<uint8_t[]>(decodedData.size());
    if (memcpy_s(buffer.get(), decodedData.size(), decodedData.data(), decodedData.size()) != 0) {
        LOGW("memcpy failed from decoded data");
        return { nullptr, 0 };
    }
    return { std::move(buffer), decodedData.size() };
}

MediaData DrawableDescriptorLoader::LoadResourceData(const RefPtr<DrawableDescriptorInfo>& info)
{
    auto resourceObject = info->GetResource();
    auto resAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
    auto type = resourceObject->GetType();
    auto id = resourceObject->GetId();
    auto bundleName = resourceObject->GetBundleName();
    auto moduleName = resourceObject->GetModuleName();
    std::unique_ptr<uint8_t[]> data;
    size_t dataLen = 0;
    if (type == MEDIA_TYPE) {
        if (id != -1) {
            if (!resAdapter->GetMediaData(id, dataLen, data, bundleName, moduleName)) {
                LOGW("get media data failed, id = %{public}d", id);
                return { nullptr, 0 };
            }
            return { std::move(data), dataLen };
        } else {
            auto params = resourceObject->GetParams();
            if (params.empty()) {
                LOGW("get media data params empty");
                return { nullptr, 0 };
            }
            auto resName = params[0].value.value_or("");
            if (!resAdapter->GetMediaData(resName, dataLen, data, bundleName, moduleName)) {
                LOGW("get media data failed, id = -1, resName = %{public}s", resName.c_str());
                return { nullptr, 0 };
            }
            return { std::move(data), dataLen };
        }
    }
    if (type == RAW_TYPE) {
        auto params = resourceObject->GetParams();
        if (params.empty()) {
            LOGW("get rawfile data params empty");
            return { nullptr, 0 };
        }
        auto rawName = params[0].value.value_or("");
        if (!resAdapter->GetRawFileData(rawName, dataLen, data, bundleName, moduleName)) {
            LOGW("get rawfile data failed, rawName = %{public}s", rawName.c_str());
            return { nullptr, 0 };
        }
        return { std::move(data), dataLen };
    }
    return { nullptr, 0 };
}
} // namespace OHOS::Ace