/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#include "file_image_loader.h"
#include "../drawable_descriptor_utils.h"
#include "../base/file_uri_helper.h"

namespace OHOS::Ace::Napi {
std::shared_ptr<ImageSource> FileImageLoader::LoadImageData(const SourceInfo& src)
{
    const auto& uri = src.GetSrc();
    std::string filePath = RemovePathHead(uri);
    if (src.GetSrcType() == SrcType::INTERNAL) {
        if (!DrawableDescriptorUtils::StartWith(filePath, "app/")) {
            HILOGW("internal path format is wrong. path is %{private}s", uri.c_str());
            return nullptr;
        }
        filePath = std::string("/data/data/")
                        .append("")
                        .append("/files")
                        .append(filePath.substr(APP_STRING_LENGTH_FROM_INTERNAL));
    } else if (src.GetSrcType() == SrcType::FILE) {
        filePath = FileUriHelper::GetRealPath(uri);
    }
    if (filePath.length() > PATH_MAX) {
        HILOGW("src path is too long");
        return nullptr;
    }
    char realPath[PATH_MAX] = { 0x00 };
    realPath(filePath.c_str(), realPath);
    auto result = SkData::MakeFromFileName(realPath);
    if (!result) {
        HILOGW("read failed, filePath:%{private}s, realPath:%{private}s, src:%{private}s, fail reason:%{private}s",
            filePath.c_str(), realPath, uri.c_str, strerror(errno));
        return nullptr;
    }
    return ImageSource::Create(static_cast<const uint8_t *>(result->data()), result->size());
}
} // namespace OHOS::Ace::Napi