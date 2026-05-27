/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_BASE_UTILS_APP_SPACE_COMP_CONFIG_READER_H
#define FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_BASE_UTILS_APP_SPACE_COMP_CONFIG_READER_H

#include <cstdint>
#include <string>
#include <utility>

namespace OHOS::CompConfigClient {
class AppSpaceCompConfigReader {
public:
    static int32_t Init(const std::string& bundleName);
    static std::pair<int32_t, std::string> GetConfig(const std::string& key);
};

namespace AppSpaceCompConfigReaderMock {
void Reset();
void SetInitResult(int32_t result);
void SetConfigResult(int32_t result, const std::string& value);
int32_t GetInitCallCount();
int32_t GetConfigCallCount();
const std::string& GetLastInitBundleName();
const std::string& GetLastConfigKey();
} // namespace AppSpaceCompConfigReaderMock
} // namespace OHOS::CompConfigClient

#endif // FOUNDATION_ACE_TEST_MOCK_FRAMEWORKS_BASE_UTILS_APP_SPACE_COMP_CONFIG_READER_H
