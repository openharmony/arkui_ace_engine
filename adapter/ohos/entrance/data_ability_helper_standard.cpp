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

namespace OHOS::Ace {
namespace {

#if !defined(PREVIEW)
using ThumbnaiNapiEntry = void* (*)(const char*, void*);
ThumbnaiNapiEntry GetThumbnailNapiEntry()
{
    static ThumbnaiNapiEntry thumbnailNapiEntry = nullptr;
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
        if (handle == nullptr) {
            LOGE("Failed to open shared library %{public}s, reason: %{public}s", napiPluginPath.c_str(), dlerror());
            return nullptr;
        }
        thumbnailNapiEntry = reinterpret_cast<ThumbnaiNapiEntry>(dlsym(handle, "OHOS_MEDIA_NativeGetThumbnail"));
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
            ThumbnaiNapiEntry thumbnailNapiEntry = GetThumbnailNapiEntry();
            if (!thumbnailNapiEntry) {
                LOGE("thumbnailNapiEntry is null");
                return nullptr;
            }
            auto runtimeContextSptr = runtimeContextWp.lock();
            if (runtimeContextSptr == nullptr) {
                LOGE("runtimeContext lock fail, uri: %{private}s", uri.c_str());
                return nullptr;
            }
            void* resPtr = thumbnailNapiEntry(uri.c_str(), &runtimeContextSptr);
            if (resPtr == nullptr) {
                LOGW("resPtr from native thumbnail is nullptr, uri: %{private}s", uri.c_str());
                return nullptr;
            }
            return std::unique_ptr<Media::PixelMap>(reinterpret_cast<Media::PixelMap*>(resPtr));
        };
#endif
    } else {
        context_ = context;
    }
}

void* DataAbilityHelperStandard::QueryThumbnailResFromDataAbility(const std::string& uri)
{
    if (!dataAbilityThumbnailQueryImpl_) {
        LOGW("no impl for thumbnail data query, please make sure you are using thumbnail resource on stage mode. "
             "uri: %{private}s",
            uri.c_str());
        return nullptr;
    }
    pixmap_ = dataAbilityThumbnailQueryImpl_(uri);
    if (!pixmap_) {
        LOGW("pixel map from thumb nail is nullptr, uri: %{public}s", uri.c_str());
        return nullptr;
    }
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

    if (dataAbilityHelper_) {
        return dataAbilityHelper_->OpenFile(uri, mode);
    }
    LOGE("DataAbilityHelperStandard::OpenFile fail, data ability helper is not exist.");
    return -1;
}

int32_t DataAbilityHelperStandard::OpenFileWithDataShare(const std::string& uriStr, const std::string& mode)
{
    if (useStageModel_ && !dataShareHelper_ && !runtimeContext_.expired()) {
        dataShareHelper_ = DataShare::DataShareHelper::Creator(runtimeContext_.lock()->GetToken(), uriStr);
    }

    if (dataShareHelper_) {
        Uri uri = Uri(uriStr);
        return dataShareHelper_->OpenFile(uri, mode);
    }
    LOGE("DataAbilityHelperStandard::OpenFile fail, data share helper is not exist.");
    return -1;
}

} // namespace OHOS::Ace
