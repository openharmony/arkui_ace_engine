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

#include "app_space_comp_config_reader.h"

#include <cstdlib>
#include <cstring>

struct AppSpaceCompConfigResult {
    int32_t code;
    char* value;
};

namespace OHOS::CompConfigClient {
namespace {
constexpr int32_t DEFAULT_SUCCESS = 0;

int32_t g_initResult = DEFAULT_SUCCESS;
int32_t g_configResult = DEFAULT_SUCCESS;
int32_t g_initCallCount = 0;
int32_t g_configCallCount = 0;
std::string g_configValue;
std::string g_lastInitBundleName;
std::string g_lastConfigKey;
} // namespace

int32_t AppSpaceCompConfigReader::Init(const std::string& bundleName)
{
    ++g_initCallCount;
    g_lastInitBundleName = bundleName;
    return g_initResult;
}

std::pair<int32_t, std::string> AppSpaceCompConfigReader::GetConfig(const std::string& key)
{
    ++g_configCallCount;
    g_lastConfigKey = key;
    return { g_configResult, g_configValue };
}

namespace AppSpaceCompConfigReaderMock {
void Reset()
{
    g_initResult = DEFAULT_SUCCESS;
    g_configResult = DEFAULT_SUCCESS;
    g_initCallCount = 0;
    g_configCallCount = 0;
    g_configValue.clear();
    g_lastInitBundleName.clear();
    g_lastConfigKey.clear();
}

void SetInitResult(int32_t result)
{
    g_initResult = result;
}

void SetConfigResult(int32_t result, const std::string& value)
{
    g_configResult = result;
    g_configValue = value;
}

int32_t GetInitCallCount()
{
    return g_initCallCount;
}

int32_t GetConfigCallCount()
{
    return g_configCallCount;
}

const std::string& GetLastInitBundleName()
{
    return g_lastInitBundleName;
}

const std::string& GetLastConfigKey()
{
    return g_lastConfigKey;
}
} // namespace AppSpaceCompConfigReaderMock
} // namespace OHOS::CompConfigClient

extern "C" int32_t OHOS_COMPCONFIGCLIENT_InitAppSpaceCompConfigReader(const char* bundleName)
{
    return OHOS::CompConfigClient::AppSpaceCompConfigReader::Init(bundleName ? bundleName : "");
}

extern "C" AppSpaceCompConfigResult* OHOS_COMPCONFIGCLIENT_GetAppSpaceCompConfig(const char* key)
{
    auto result = OHOS::CompConfigClient::AppSpaceCompConfigReader::GetConfig(key ? key : "");
    auto* config = static_cast<AppSpaceCompConfigResult*>(std::malloc(sizeof(AppSpaceCompConfigResult)));
    if (config == nullptr) {
        return nullptr;
    }

    auto valueSize = result.second.size() + 1;
    config->value = static_cast<char*>(std::malloc(valueSize));
    if (config->value == nullptr) {
        std::free(config);
        return nullptr;
    }

    config->code = result.first;
    std::memcpy(config->value, result.second.c_str(), valueSize);
    return config;
}

extern "C" void OHOS_COMPCONFIGCLIENT_DestroyAppSpaceCompConfig(AppSpaceCompConfigResult* result)
{
    if (result == nullptr) {
        return;
    }
    std::free(result->value);
    std::free(result);
}
