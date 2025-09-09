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

#include "adapter/ohos/entrance/data_ability_helper_standard.h"

#if !defined(PREVIEW)
#include <dlfcn.h>
#endif

#include "data_ability_helper.h"

#include "base/log/ace_trace.h"
#include "base/utils/string_utils.h"
#include "utils.h"

namespace OHOS::Ace {
const std::string MEDIA_SERVER_HEAD = "datashare:///media";
const std::string IMAGE_PATH_DATA = "data";
const std::string MOVINGPHOTO_IMAGE_COVERPOSITION = "cover_positon";
const std::string IMAGE_URI = "uri";

template<typename ResultSet>
static inline std::string GetStringVal(const std::string &field, const ResultSet &result)
{
    return std::get<std::string>(ResultSetUtils::GetValFromColumn(field, result, ResultSetDataType::TYPE_STRING));
}
template<typename ResultSet>
static inline int32_t GetInt32Val(const std::string &field, const ResultSet &result)
{
    return std::get<int32_t>(ResultSetUtils::GetValFromColumn(field, result, ResultSetDataType::TYPE_INT32));
}
template<typename ResultSet>
static inline int64_t GetInt64Val(const std::string &field, const ResultSet &result)
{
    return std::get<int64_t>(ResultSetUtils::GetValFromColumn(field, result, ResultSetDataType::TYPE_INT64));
}
template<typename ResultSet>
static inline double GetDoubleVal(const std::string &field, const ResultSet &result)
{
    return std::get<double>(ResultSetUtils::GetValFromColumn(field, result, ResultSetDataType::TYPE_DOUBLE));
}

DataAbilityHelperStandard::DataAbilityHelperStandard(const std::shared_ptr<OHOS::AppExecFwk::Context>& context,
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext, bool useStageModel)
    : useStageModel_(useStageModel)
{
    if (useStageModel) {
        runtimeContext_ = runtimeContext;
#ifdef MEDIA_LIBRARY_EXISTS
        mgr_.InitMediaLibraryManager(runtimeContext->GetToken());
#endif
    } else {
        context_ = context;
#ifdef MEDIA_LIBRARY_EXISTS
        mgr_.InitMediaLibraryManager(context->GetToken());
#endif
    }
}

void* DataAbilityHelperStandard::QueryThumbnailResFromDataAbility(const std::string& uri)
{
#ifdef PREVIEW
    return nullptr;
#else
#ifdef MEDIA_LIBRARY_EXISTS
    ACE_FUNCTION_TRACE();
    Uri fileUri(uri);
    return mgr_.GetThumbnail(fileUri).release();
#else
    return nullptr;
#endif
#endif
}

std::string DataAbilityHelperStandard::GetMovingPhotoImageUri(const std::string& uri)
{
#ifdef MEDIA_LIBRARY_EXISTS
    return mgr_.GetMovingPhotoImageUri(uri);
#else
    return "";
#endif
}

int64_t DataAbilityHelperStandard::GetMovingPhotoDateModified(const std::string& uri)
{
#ifdef MEDIA_LIBRARY_EXISTS
    return mgr_.GetMovingPhotoDateModified(uri);
#else
    return -1;
#endif
}

int64_t DataAbilityHelperStandard::GetMovingPhotoCoverPosition(const std::string& columnName,
                                                               const std::string& value,
                                                               std::vector<std::string>& columns)
{
#ifdef MEDIA_LIBRARY_EXISTS
    auto resultSet = mgr_.GetResultSetFromDb(columnName, value, columns);
    if (resultSet == nullptr || resultSet->GoToFirstRow() != 0) {
        LOGE("Result is nullptr or GoToFirstRow failed.");
        return -1;
    }
    int64_t coverPosition = GetInt64Val(MOVINGPHOTO_IMAGE_COVERPOSITION, resultSet);
    return coverPosition;
#else
    return -1;
#endif
}

std::string DataAbilityHelperStandard::GetMovingPhotoImagePath(const std::string& uri)
{
#ifdef MEDIA_LIBRARY_EXISTS
    std::vector<std::string> columns = {IMAGE_PATH_DATA};
    auto resultSet = mgr_.GetResultSetFromDb(IMAGE_URI, uri, columns);
    if (resultSet == nullptr || resultSet->GoToFirstRow() != 0) {
        LOGE("Result is nullptr or GoToFirstRow failed.");
        return "";
    }
    std::string path = GetStringVal(IMAGE_PATH_DATA, resultSet);
    LOGI("resultSet path : %{public}s.", path.c_str());
    return path;
#else
    return "";
#endif
}

int32_t DataAbilityHelperStandard::OpenFile(const std::string& uriStr, const std::string& mode)
{
    // FA model always uses DataAbility
    if (!useStageModel_ || StringUtils::StartWith(uriStr, "dataability://")) {
        return OpenFileWithDataAbility(uriStr, mode);
    }
    if (StringUtils::StartWith(uriStr, "datashare://") || StringUtils::StartWith(uriStr, "file://")) {
        return OpenFileWithDataShare(uriStr, mode);
    }
    LOGE("DataAbilityHelperStandard OpenFile uri is not support.");
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
    {
        std::shared_lock<std::shared_mutex> readLock(dataShareHelperLock_);
        if (dataShareHelper_) {
            Uri uri(uriStr);
            return dataShareHelper_->OpenFile(uri, mode);
        }
    }
    auto context = runtimeContext_.lock();
    {
        std::unique_lock<std::shared_mutex> writeLock(dataShareHelperLock_);
        if (useStageModel_ && !dataShareHelper_ && context) {
            dataShareHelper_ = DataShare::DataShareHelper::Creator(context->GetToken(), MEDIA_SERVER_HEAD);
        }
        CHECK_NULL_RETURN(dataShareHelper_, -1);
    }
    Uri uri = Uri(uriStr);
    {
        std::shared_lock<std::shared_mutex> readLock(dataShareHelperLock_);
        return dataShareHelper_->OpenFile(uri, mode);
    }
}

int32_t DataAbilityHelperStandard::ReadMovingPhotoVideo(const std::string &uri)
{
#ifdef MEDIA_LIBRARY_EXISTS
    return mgr_.ReadMovingPhotoVideo(uri);
#else
    return -1;
#endif
}

} // namespace OHOS::Ace
