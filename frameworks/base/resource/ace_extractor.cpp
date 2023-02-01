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
#include "base/log/log.h"
#include "base/resource/ace_extractor.h"

namespace OHOS::Ace {
bool AceExtractor::ExtractToBufByName(const std::string& fileName,
                                      const std::string& hapPath,
                                      std::unique_ptr<uint8_t[]>& dataPtr, size_t& len) const
{
    if (hapPath.empty()) {
        LOGE("HapPath is not empty");
        return false;
    }
    std::string loadPath = AceGetLoadFilePath(hapPath);
    if (loadPath.empty()) {
        LOGE("Failed to load hapPath");
        return false;
    }

    return AceExtractToBufByName(fileName, loadPath, dataPtr, len);
}
} // namespace OHOS::Ace

