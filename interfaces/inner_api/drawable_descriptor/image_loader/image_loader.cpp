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

#include "image_laoder.h"
namespace OHOS::Ace::Napi {

std::shared_ptr<ImageSource> ImageLoader::GetImageData(const SourceInfo& src)
{
    return LoadImageData(src);
}

std::string ImageLoader::RemovePathHead(const std::string& uri)
{
    auto iter = uri.find_first_of(':');
    if (iter == std::string::npos) {
        HILOGW("no scheme, not a file or memory path");
        return std::string();
    }
    std::string head = uri.substr(0, iter);
    if ((head == "file" && uri.size() > FILE_HEAD_LENGTH) || (head == "memory" && uri.size() > MEMORY_HEAD_LENGTH) ||
        (head == "internal" && uri.size() > INTERNAL_FILE_HEAD_LENGTH)) {
        return uri.substr(iter + INTERNAL_FILE_HEAD_SKIP_LENGTH);
    }
    HILOGW("wrong scheme, not a file");
    return std::string();
}
} // namespace OHOS::Ace::Napi