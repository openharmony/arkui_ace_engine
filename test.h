#ifndef FOUNDATION_ACE_TEST_H
#define FOUNDATION_ACE_TEST_H

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>
#include <utility>

#include "base/utils/macros.h"
#include "comp_config_read_util.h"

namespace OHOS::CompConfigClient {
class AppSpaceCompConfigReader {
public:
    AppSpaceCompConfigReader() =delete;
    AppSpaceCompConfigReader(const AppSpaceCompConfigReader&) = delete;
    AppSpaceCompConfigReader(AppSpaceCompConfigReader&&) = delete;
    static int32_t Init(const std::string& bundleName);
    static std::pair<int32_t, std::string> GetConfig(const std::string& key);
};
} // namespace OHOS::CompConfigClient

typedef struct AppSpaceCompConfigResult {
    int32_t code;
    char* value;
} AppSpaceCompConfigResult;

extern "C" ACE_FORCE_EXPORT int32_t OHOS_ACE_InitAppSpaceCompConfigReader(const char* bundleName)
{
    return OHOS::CompConfigClient::AppSpaceCompConfigReader::Init(bundleName ? bundleName : "");
}

extern "C" ACE_FORCE_EXPORT AppSpaceCompConfigResult* OHOS_ACE_GetAppSpaceCompConfig(const char* key)
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

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_DestroyAppSpaceCompConfig(AppSpaceCompConfigResult* result)
{
    if (result == nullptr) {
        return;
    }
    std::free(result->value);
    std::free(result);
}

#endif // FOUNDATION_ACE_TEST_H
