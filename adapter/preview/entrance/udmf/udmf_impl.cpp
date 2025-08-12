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

#include "adapter/preview/entrance/udmf/udmf_impl.h"

#include <memory>
#include <unordered_map>

#include "js_native_api_types.h"

#include "base/utils/utils.h"
#include "core/common/udmf/unified_data.h"
namespace OHOS::Ace {
UdmfClient* UdmfClient::GetInstance()
{
    static UdmfClientImpl instance;
    return &instance;
}

RefPtr<UnifiedData> UdmfClientImpl::TransformUnifiedDataForNative(void* rawData)
{
    return nullptr;
}

RefPtr<DataLoadParams> UdmfClientImpl::TransformDataLoadParamsForNative(void* rawData)
{
    return nullptr;
}

void* UdmfClientImpl::TransformUnifiedDataPtr(RefPtr<UnifiedData>& unifiedData)
{
    return nullptr;
}

RefPtr<UnifiedData> UdmfClientImpl::TransformUnifiedData(napi_value napiValue)
{
    return nullptr;
}

RefPtr<DataLoadParams> UdmfClientImpl::TransformDataLoadParams(napi_env env, napi_value napiValue)
{
    return nullptr;
}

int32_t UdmfClientImpl::SetDelayInfo(RefPtr<DataLoadParams> dataLoadParams, std::string& key)
{
    return -1;
}

napi_value UdmfClientImpl::TransformUdmfUnifiedData(RefPtr<UnifiedData>& UnifiedData)
{
    return nullptr;
}

napi_value UdmfClientImpl::TransformSummary(std::map<std::string, int64_t>& summary)
{
    return nullptr;
}

RefPtr<UnifiedData> UdmfClientImpl::CreateUnifiedData()
{
    return nullptr;
}

int32_t UdmfClientImpl::SetData(const RefPtr<UnifiedData>& unifiedData, std::string& key)
{
    return -1;
}

int32_t UdmfClientImpl::GetData(const RefPtr<UnifiedData>& unifiedData, const std::string& key)
{
    return -1;
}

int32_t UdmfClientImpl::GetSummary(std::string& key, DragSummaryInfo& dragSummaryInfo)
{
    return -1;
}

bool UdmfClientImpl::GetRemoteStatus(std::string& key)
{
    return false;
}

void UdmfClientImpl::AddFormRecord(
    const RefPtr<UnifiedData>& unifiedData, int32_t formId, const RequestFormInfo& cardInfo)
{}

void UdmfClientImpl::AddLinkRecord(
    const RefPtr<UnifiedData>& unifiedData, const std::string& url, const std::string& description)
{}

void UdmfClientImpl::GetLinkRecord(const RefPtr<UnifiedData>& unifiedData, std::string& url, std::string& description)
{}

bool UdmfClientImpl::GetFileUriRecord(const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri)
{
    return false;
}

bool UdmfClientImpl::AddFileUriRecord(const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri)
{
    return false;
}

void UdmfClientImpl::AddHtmlRecord(
    const RefPtr<UnifiedData>& unifiedData, const std::string& htmlContent, const std::string& plainContent)
{}

void UdmfClientImpl::GetHtmlRecord(
    const RefPtr<UnifiedData>& unifiedData, std::string& htmlContent, std::string& plainContent)
{}

void UdmfClientImpl::AddPixelMapRecord(
    const RefPtr<UnifiedData>& unifiedData, std::vector<uint8_t>& data, PixelMapRecordDetails& details)
{}

void UdmfClientImpl::AddImageRecord(const RefPtr<UnifiedData>& unifiedData, const std::string& uri) {}

void UdmfClientImpl::AddPlainTextRecord(const RefPtr<UnifiedData>& unifiedData, const std::string& selectedStr) {}

std::string UdmfClientImpl::GetSinglePlainTextRecord(const RefPtr<UnifiedData>& unifiedData)
{
    return "";
}

std::vector<std::string> UdmfClientImpl::GetPlainTextRecords(const RefPtr<UnifiedData>& unifiedData)
{
    return {};
}

int32_t UdmfClientImpl::GetVideoRecordUri(const RefPtr<UnifiedData>& unifiedData, std::string& uri)
{
    return -1;
}

std::pair<int32_t, std::string> UdmfClientImpl::GetErrorInfo(int32_t errorCode)
{
    return {};
}

std::shared_ptr<UnifiedData> UnifiedDataImpl::GetUnifiedData()
{
    return nullptr;
}

void UnifiedDataImpl::SetUnifiedData(std::shared_ptr<UnifiedData> unifiedData)
{
    return;
}

void UdmfClientImpl::AddSpanStringRecord(
    const RefPtr<UnifiedData>& unifiedData, std::vector<uint8_t>& data)
{
    return;
}
std::vector<uint8_t> UdmfClientImpl::GetSpanStringRecord(const RefPtr<UnifiedData>& unifiedData)
{
    return {};
}

int32_t UdmfClientImpl::StartAsyncDataRetrieval(napi_env env, napi_value napiValue, const std::string& key)
{
    return -1;
}

int32_t UdmfClientImpl::Cancel(const std::string& key)
{
    return -1;
}

void UdmfClientImpl::SetTagProperty(const RefPtr<UnifiedData>& unifiedData, const std::string& tag) {}

std::string UdmfClientImpl::GetPlainTextEntry(const RefPtr<UnifiedData>& unifiedData)
{
    return "";
}

void UdmfClientImpl::GetHtmlEntry(
    const RefPtr<UnifiedData>& unifiedData, std::string& htmlContent, std::string& plainContent)
{}

void UdmfClientImpl::GetLinkEntry(const RefPtr<UnifiedData>& unifiedData, std::string& url, std::string& description) {}

bool UdmfClientImpl::GetFileUriEntry(const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri)
{
    return false;
}

std::vector<uint8_t> UdmfClientImpl::GetSpanStringEntry(const RefPtr<UnifiedData>& unifiedData)
{
    return {};
}

bool UdmfClientImpl::IsAppropriateType(DragSummaryInfo& dragSummaryInfo, const std::set<std::string>& allowTypes)
{
    return false;
}

#if defined(ACE_STATIC)
RefPtr<UnifiedData> UdmfClientImpl::TransformUnifiedDataFromANI(void* rawData)
{
    return nullptr;
}

void UdmfClientImpl::TransformSummaryANI(std::map<std::string, int64_t>& summary, void* summaryPtr)
{}
#endif
} // namespace OHOS::Ace