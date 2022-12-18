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
#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "data_ability_helper.h"
#include "datashare_helper.h"
#include "pixel_map.h"

#include "adapter/ohos/entrance/data_ability_helper_standard.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {

#if !defined(PREVIEW)
using ThumbnailNapiEntry = void* (*)(const char*, void*);
ThumbnailNapiEntry GetThumbnailNapiEntry()
{
    static ThumbnailNapiEntry thumbnailNapiEntry = nullptr;
    if (!thumbnailNapiEntry) {
#ifdef _ARM64_
        std::string prefix = "/system/lib64/module/";
#else
        std::string prefix = "/system/lib/module/";
#endif
#ifdef OHOS_STANDARD_SYSTEM
        std::string napiPluginName = "multimedia/libmedialibrary.z.so";
#endif
        auto napiPluginPath = prefix.append(napiPluginName);
        void* handle = dlopen(napiPluginPath.c_str(), RTLD_LAZY);
        CHECK_NULL_RETURN(handle, nullptr);
        thumbnailNapiEntry = reinterpret_cast<ThumbnailNapiEntry>(dlsym(handle, "OHOS_MEDIA_NativeGetThumbnail"));
        if (thumbnailNapiEntry == nullptr) {
            dlclose(handle);
            LOGE("Failed to get symbol OHOS_MEDIA_NativeGetThumbnail in %{public}s", napiPluginPath.c_str());
            return nullptr;
        }
    }
    return thumbnailNapiEntry;
}
#endif

} // namespace

DataAbilityHelperStandard::DataAbilityHelperStandard(const std::shared_ptr<OHOS::AppExecFwk::Context>& context,
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext, bool useStageModel)
    : useStageModel_(useStageModel)
{
    if (useStageModel) {
        runtimeContext_ = runtimeContext;
#if !defined(PREVIEW)
        dataAbilityThumbnailQueryImpl_ = [runtimeContextWp = runtimeContext_](
                                             const std::string& uri) -> std::unique_ptr<Media::PixelMap> {
            ThumbnailNapiEntry thumbnailNapiEntry = GetThumbnailNapiEntry();
            CHECK_NULL_RETURN(thumbnailNapiEntry, nullptr);
            auto runtimeContextSptr = runtimeContextWp.lock();
            CHECK_NULL_RETURN(runtimeContextSptr, nullptr);
            void* resPtr = thumbnailNapiEntry(uri.c_str(), &runtimeContextSptr);
            CHECK_NULL_RETURN(resPtr, nullptr);
            return std::unique_ptr<Media::PixelMap>(reinterpret_cast<Media::PixelMap*>(resPtr));
        };
#endif
    } else {
        context_ = context;
    }
}

void* DataAbilityHelperStandard::QueryThumbnailResFromDataAbility(const std::string& uri)
{
    CHECK_NULL_RETURN(dataAbilityThumbnailQueryImpl_, nullptr);
    pixmap_ = dataAbilityThumbnailQueryImpl_(uri);
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return reinterpret_cast<void*>(&pixmap_);
}

int32_t DataAbilityHelperStandard::OpenFile(const std::string& uriStr, const std::string& mode)
{
    LOGD("DataAbilityHelperStandard::OpenFile start uri: %{private}s, mode: %{private}s", uriStr.c_str(), mode.c_str());
    // FA model always uses DataAbility
    if (!useStageModel_ || StringUtils::StartWith(uriStr, "dataability://")) {
        return OpenFileWithDataAbility(uriStr, mode);
    }
    if (StringUtils::StartWith(uriStr, "datashare://")) {
        return OpenFileWithDataShare(uriStr, mode);
    }
    LOGE("DataAbilityHelperStandard::OpenFile uri is not support.");
    return -1;
}

int32_t DataAbilityHelperStandard::OpenFileWithDataAbility(const std::string& uriStr, const std::string& mode)
{
    Uri uri = Uri(uriStr);
    uri_ = std::make_shared<Uri>(uriStr);
    if (!dataAbilityHelper_) {
        if (useStageModel_) {
            dataAbilityHelper_ = AppExecFwk::DataAbilityHelper::Creator(runtimeContext_.lock(), uri_, false);
        } else {
            dataAbilityHelper_ = AppExecFwk::DataAbilityHelper::Creator(context_.lock(), uri_);
        }
    }

    CHECK_NULL_RETURN(dataAbilityHelper_, -1);
    return dataAbilityHelper_->OpenFile(uri, mode);
}

int32_t DataAbilityHelperStandard::OpenFileWithDataShare(const std::string& uriStr, const std::string& mode)
{
    auto context = runtimeContext_.lock();
    if (useStageModel_ && !dataShareHelper_ && context) {
        dataShareHelper_ = DataShare::DataShareHelper::Creator(context->GetToken(), uriStr);
    }

    CHECK_NULL_RETURN(dataShareHelper_, -1);
    Uri uri = Uri(uriStr);
    return dataShareHelper_->OpenFile(uri, mode);
}

} // namespace OHOS::Ace
