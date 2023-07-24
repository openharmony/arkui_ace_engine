/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/pipeline/pipeline_context.h"
#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "data_ability_helper.h"
#include "datashare_helper.h"

#include "adapter/ohos/entrance/data_ability_helper_standard.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {
const std::string MEDIA_PLUGIN = "multimedia/libmedialibrary.z.so";
const std::string FILE_PLUGIN = "filemanagement/libuserfilemanager.z.so";
const std::string PAH_PLUGIN = "file/libphotoaccesshelper.z.so";
const std::string MEDIA_SERVER_HEAD = "datashare:///media";

#if !defined(PREVIEW)
using ThumbnailNapiEntry = void* (*)(const char*, void*);
static void* GetThumbnailFromNapi(const std::string& uri, const std::weak_ptr<OHOS::AbilityRuntime::Context> &context)
{
    ACE_SCOPED_TRACE("GetThumbnailFromNapi");
#if defined(_ARM64_) || defined(SIMULATOR_64)
        static const std::string PREFIX = "/system/lib64/module/";
#else
        static const std::string PREFIX = "/system/lib/module/";
#endif
    static const std::vector<std::string> THUMB_PLUGINS = {
        PAH_PLUGIN,
        FILE_PLUGIN,
        MEDIA_PLUGIN,
    };
    void* outThumbnail = nullptr;
    auto runtimeContext = context.lock();
    CHECK_NULL_RETURN(runtimeContext, nullptr);
    static ThumbnailNapiEntry thumbnailNapiEntry = nullptr;
    if (!thumbnailNapiEntry) {
        for (const auto& plug : THUMB_PLUGINS) {
            auto napiPlug = PREFIX + plug;
            void* handle = dlopen(napiPlug.c_str(), RTLD_LAZY);
            CHECK_NULL_RETURN(handle, nullptr);
            thumbnailNapiEntry = reinterpret_cast<ThumbnailNapiEntry>(dlsym(handle, "OHOS_MEDIA_NativeGetThumbnail"));
            if (thumbnailNapiEntry == nullptr) {
                dlclose(handle);
                LOGE("Failed to get symbol OHOS_MEDIA_NativeGetThumbnail in %{public}s, try next plugin",
                    napiPlug.c_str());
                continue;
            }
            outThumbnail = thumbnailNapiEntry(uri.c_str(), &runtimeContext);
            if (outThumbnail == nullptr) {
                dlclose(handle);
                thumbnailNapiEntry = nullptr;
                LOGE("Failed to get thumbnail from %{private}s, try next plugin", napiPlug.c_str());
                continue;
            }
            return outThumbnail;
        }
    } else {
        outThumbnail = thumbnailNapiEntry(uri.c_str(), &runtimeContext);
        if (outThumbnail == nullptr) {
            thumbnailNapiEntry = nullptr;
            LOGE("Failed to get thumbnail!");
        }
    }
    return outThumbnail;
}
#endif
} // namespace

DataAbilityHelperStandard::DataAbilityHelperStandard(const std::shared_ptr<OHOS::AppExecFwk::Context>& context,
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext, bool useStageModel)
    : useStageModel_(useStageModel)
{
    if (useStageModel) {
        runtimeContext_ = runtimeContext;
    } else {
        context_ = context;
    }
}

void* DataAbilityHelperStandard::QueryThumbnailResFromDataAbility(const std::string& uri)
{
#ifdef PREVIEW
    return nullptr;
#else
    return GetThumbnailFromNapi(uri, runtimeContext_);
#endif
}

int32_t DataAbilityHelperStandard::OpenFile(const std::string& uriStr, const std::string& mode)
{
    LOGD("DataAbilityHelperStandard::OpenFile start uri: %{private}s, mode: %{private}s", uriStr.c_str(), mode.c_str());
    // FA model always uses DataAbility
    if (!useStageModel_ || StringUtils::StartWith(uriStr, "dataability://")) {
        return OpenFileWithDataAbility(uriStr, mode);
    }
    if (StringUtils::StartWith(uriStr, "datashare://") || StringUtils::StartWith(uriStr, "file://")) {
        return OpenFileWithDataShare(uriStr, mode);
    }
    LOGE("DataAbilityHelperStandard::OpenFile uri is not support.");
    return -1;
}

int32_t DataAbilityHelperStandard::OpenFileWithDataAbility(const std::string& uriStr, const std::string& mode)
{
    std::shared_ptr<OHOS::Uri> uri = std::make_shared<Uri>(uriStr);
    if (!dataAbilityHelper_) {
        if (useStageModel_) {
            dataAbilityHelper_ = AppExecFwk::DataAbilityHelper::Creator(runtimeContext_.lock(), uri, false);
        } else {
            dataAbilityHelper_ = AppExecFwk::DataAbilityHelper::Creator(context_.lock(), uri);
        }
    }

    CHECK_NULL_RETURN(dataAbilityHelper_, -1);
    return dataAbilityHelper_->OpenFile(*uri, mode);
}

int32_t DataAbilityHelperStandard::OpenFileWithDataShare(const std::string& uriStr, const std::string& mode)
{
    auto context = runtimeContext_.lock();
    if (useStageModel_ && !dataShareHelper_ && context) {
        dataShareHelper_ = DataShare::DataShareHelper::Creator(context->GetToken(), MEDIA_SERVER_HEAD);
    }

    CHECK_NULL_RETURN(dataShareHelper_, -1);
    Uri uri = Uri(uriStr);
    return dataShareHelper_->OpenFile(uri, mode);
}

} // namespace OHOS::Ace
