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
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_RESOURCE_ACE_EXTRACTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_RESOURCE_ACE_EXTRACTOR_H

#include <string>
#include <memory>
#include "base/utils/macros.h"

namespace OHOS::Ace {
std::string ACE_EXPORT AceGetLoadFilePath(const std::string& hapPath);
bool ACE_EXPORT AceExtractToBufByName(const std::string& fileName,
                                      const std::string& loadPath,
                                      std::unique_ptr<uint8_t[]>& dataPtr,
                                      size_t& len);

class ACE_EXPORT AceExtractor final {
public:
    AceExtractor() = default;
    ~AceExtractor() = default;
    bool ExtractToBufByName(const std::string& fileName,
                            const std::string& hapPath,
                            std::unique_ptr<uint8_t[]>& dataPtr,
                            size_t& len) const;
};
} // namespace OHOS::Ace

#endif

