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

#include "base/resource/ace_extractor.h"

#include <string>

#include "base/log/log.h"
#include "extractor.h"

namespace OHOS::Ace {
using ExtractorUtil = AbilityBase::ExtractorUtil;
using Extractor = AbilityBase::Extractor;

std::string AceGetLoadFilePath(const std::string& hapPath)
{
    return ExtractorUtil::GetLoadFilePath(hapPath);
}

bool AceExtractToBufByName(const std::string& fileName,
                           const std::string& loadPath, std::unique_ptr<uint8_t[]>& dataPtr, size_t& len)
{
    bool newCreate = false;
    auto extractor = ExtractorUtil::GetExtractor(loadPath, newCreate);
    if (extractor == nullptr) {
        LOGE("AceExtractToBufByName:: GetExtractor failed to execute.");
        return false;
    }
    return extractor->ExtractToBufByName(fileName, dataPtr, len);
}
} // namespace OHOS::Ace
