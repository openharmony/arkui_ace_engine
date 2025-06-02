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

#include "base/resource/data_provider_manager.h"

#include <sys/stat.h>
#include <unistd.h>
#include "base/utils/utils.h"

namespace OHOS::Ace {

std::unique_ptr<DataProviderRes> DataProviderManager::GetDataProviderResFromUri(
    const std::string& uriStr, ImageErrorInfo& errorInfo)
{
    if (platformImpl_) {
        return platformImpl_(uriStr);
    }
    return nullptr;
}

void* DataProviderManagerStandard::GetDataProviderThumbnailResFromUri(const std::string& uriStr)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    if (!helper_) {
        return nullptr;
    }
    return helper_->QueryThumbnailResFromDataAbility(uriStr);
}

std::unique_ptr<DataProviderRes> DataProviderManagerStandard::GetDataProviderResFromUri(
    const std::string& uriStr, ImageErrorInfo& errorInfo)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    if (!helper_) {
        return nullptr;
    }
    auto fd = helper_->OpenFile(uriStr, "r");
    if (fd == -1) {
        LOGW("open file %{public}s fail.", uriStr.c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_DATA_PROVIDER_OPEN_FAILED, "open file fail." };
        return nullptr;
    }

    // get size of file.
    struct stat statBuf;
    auto statRes = fstat(fd, &statBuf);
    if (statRes != 0) {
        LOGW("get file %{public}s stat fail.", uriStr.c_str());
        close(fd);
        errorInfo = { ImageErrorCode::GET_IMAGE_DATA_PROVIDER_GET_FAILED, "get file stat fail." };
        return nullptr;
    }
    auto size = statBuf.st_size;

    // read file content.
    auto buffer = std::unique_ptr<void, decltype(&std::free)>(std::malloc(size), std::free);
    auto readRes = read(fd, buffer.get(), size);
    close(fd);
    if (readRes == -1) {
        LOGW("read file %{public}s fail.", uriStr.c_str());
        errorInfo = { ImageErrorCode::GET_IMAGE_DATA_PROVIDER_READ_FAILED, "read file fail." };
        return nullptr;
    }

    auto result = std::make_unique<DataProviderRes>(std::move(buffer), size);
    return result;
}

void DataProviderManagerStandard::InitHelper()
{
    {
        std::shared_lock lock(helperMutex_);
        if (helper_) {
            return;
        }
    }
    // creating helper_, need exclusive access
    std::unique_lock lock(helperMutex_);
    if (!helper_ && dataAbilityHelperImpl_) {
        helper_ = dataAbilityHelperImpl_();
    }
}

int32_t DataProviderManagerStandard::GetDataProviderFile(const std::string& uriStr, const std::string& mode)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    CHECK_NULL_RETURN(helper_, -1);
    return helper_->OpenFile(uriStr, mode);
}

int32_t DataProviderManagerStandard::ReadMovingPhotoVideo(const std::string &uri)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    CHECK_NULL_RETURN(helper_, -1);
    return helper_->ReadMovingPhotoVideo(uri);
}

std::string DataProviderManagerStandard::GetMovingPhotoImageUri(const std::string& uri)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    CHECK_NULL_RETURN(helper_, "");
    return helper_->GetMovingPhotoImageUri(uri);
}

int64_t DataProviderManagerStandard::GetMovingPhotoDateModified(const std::string& uri)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    CHECK_NULL_RETURN(helper_, -1);
    return helper_->GetMovingPhotoDateModified(uri);
}

int64_t DataProviderManagerStandard::GetMovingPhotoCoverPosition(const std::string& columnName,
                                                                 const std::string& value,
                                                                 std::vector<std::string>& columns)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    CHECK_NULL_RETURN(helper_, -1);
    return helper_->GetMovingPhotoCoverPosition(columnName, value, columns);
}

std::string DataProviderManagerStandard::GetMovingPhotoImagePath(const std::string& uri)
{
    InitHelper();
    std::shared_lock lock(helperMutex_);
    CHECK_NULL_RETURN(helper_, "");
    return helper_->GetMovingPhotoImagePath(uri);
}
} // namespace OHOS::Ace
