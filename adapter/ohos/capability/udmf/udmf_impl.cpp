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

#include "udmf_impl.h"

#include <unordered_map>
#include <variant>

#include "html.h"
#include "image.h"
#include "link.h"
#include "summary_napi.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "text.h"
#include "plain_text.h"
#include "udmf_client.h"
#include "application_defined_record.h"
#include "unified_data.h"
#include "unified_data_napi.h"
#include "unified_types.h"
#include "video.h"
#include "native_engine/native_engine.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#include "js_native_api_types.h"

#include "base/image/file_uri_helper.h"
#include "base/utils/utils.h"
#include "core/common/udmf/unified_data.h"
#include "ndk_data_conversion.h"
namespace OHOS::Ace {
UdmfClient* UdmfClient::GetInstance()
{
    static UdmfClientImpl instance;
    return &instance;
}

RefPtr<UnifiedData> UdmfClientImpl::CreateUnifiedData()
{
    return AceType::DynamicCast<UnifiedData>(AceType::MakeRefPtr<UnifiedDataImpl>());
}

RefPtr<UnifiedData> UdmfClientImpl::TransformUnifiedData(napi_value napiValue)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    void* native = nullptr;
    napi_unwrap(env, napiValue, &native);
    auto* unifiedData = reinterpret_cast<UDMF::UnifiedDataNapi*>(native);
    CHECK_NULL_RETURN(unifiedData, nullptr);
    CHECK_NULL_RETURN(unifiedData->value_, nullptr);
    auto udData = AceType::MakeRefPtr<UnifiedDataImpl>();
    udData->SetUnifiedData(unifiedData->value_);
    return udData;
}

napi_value UdmfClientImpl::TransformUdmfUnifiedData(RefPtr<UnifiedData>& UnifiedData)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    auto unifiedDataImpl = AceType::DynamicCast<UnifiedDataImpl>(UnifiedData);
    CHECK_NULL_RETURN(unifiedDataImpl, nullptr);
    auto unifiedData = unifiedDataImpl->GetUnifiedData();
    CHECK_NULL_RETURN(unifiedData, nullptr);
    napi_value dataVal = nullptr;
    UDMF::UnifiedDataNapi::NewInstance(env, unifiedData, dataVal);
    CHECK_NULL_RETURN(dataVal, nullptr);
    return dataVal;
}

void* UdmfClientImpl::TransformUnifiedDataPtr(RefPtr<UnifiedData>& unifiedDataImpl)
{
    CHECK_NULL_RETURN(unifiedDataImpl, nullptr);
    std::shared_ptr<UDMF::UnifiedData> unifiedData =
        AceType::DynamicCast<UnifiedDataImpl>(unifiedDataImpl)->GetUnifiedData();
    CHECK_NULL_RETURN(unifiedData, nullptr);
    return unifiedData.get();
}

RefPtr<UnifiedData> UdmfClientImpl::TransformUnifiedDataForNative(void* rawData)
{
    CHECK_NULL_RETURN(rawData, nullptr);
    auto udData = AceType::MakeRefPtr<UnifiedDataImpl>();
    auto udmfData = static_cast<OH_UdmfData*>(rawData);
    CHECK_NULL_RETURN(udmfData, nullptr);
    auto unifiedData = std::make_shared<UDMF::UnifiedData>();
    auto status = OHOS::UDMF::NdkDataConversion::GetNativeUnifiedData(udmfData, unifiedData);
    if (status) {
        return nullptr;
    }

    udData->SetUnifiedData(unifiedData);
    return udData;
}

napi_value UdmfClientImpl::TransformSummary(std::map<std::string, int64_t>& summary)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    std::shared_ptr<UDMF::Summary> udmfSummary = std::make_shared<UDMF::Summary>();
    CHECK_NULL_RETURN(udmfSummary, nullptr);
    udmfSummary->totalSize = 0;
    for (auto element : summary) {
        udmfSummary->totalSize += element.second;
    }
    udmfSummary->summary = std::move(summary);
    napi_value dataVal = nullptr;
    UDMF::SummaryNapi::NewInstance(env, udmfSummary, dataVal);
    CHECK_NULL_RETURN(dataVal, nullptr);
    return dataVal;
}

int32_t UdmfClientImpl::SetData(const RefPtr<UnifiedData>& unifiedData, std::string& key)
{
    auto& client = UDMF::UdmfClient::GetInstance();
    UDMF::CustomOption udCustomOption;
    udCustomOption.intention = UDMF::Intention::UD_INTENTION_DRAG;
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, UDMF::E_ERROR);
    int32_t ret = client.SetData(udCustomOption, *udData->GetUnifiedData(), key);
    return ret;
}

int32_t UdmfClientImpl::GetData(const RefPtr<UnifiedData>& unifiedData, const std::string& key)
{
    auto& client = UDMF::UdmfClient::GetInstance();
    UDMF::QueryOption queryOption;
    queryOption.key = key;
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, UDMF::E_ERROR);
    int ret = client.GetData(queryOption, *udData->GetUnifiedData());
    return ret;
}

int32_t UdmfClientImpl::GetSummary(std::string& key, std::map<std::string, int64_t>& summaryMap)
{
    auto& client = UDMF::UdmfClient::GetInstance();
    UDMF::Summary summary;
    UDMF::QueryOption queryOption;
    queryOption.key = key;
    int32_t ret = client.GetSummary(queryOption, summary);
    summaryMap = summary.summary;
    return ret;
}

bool UdmfClientImpl::GetRemoteStatus(std::string& key)
{
    auto& client = UDMF::UdmfClient::GetInstance();
    bool isRemoteData = false;
    UDMF::QueryOption queryOption;
    queryOption.key = key;
    int32_t ret = client.IsRemoteData(queryOption, isRemoteData);
    if (ret != 0) {
        // if ret is not 0, udmf client has not been sync, so return true to use remote getData.
        return true;
    }
    return isRemoteData;
}

int64_t UnifiedDataImpl::GetSize()
{
    CHECK_NULL_RETURN(unifiedData_, 0);
    return unifiedData_->GetRecords().size();
}

std::shared_ptr<UDMF::UnifiedData> UnifiedDataImpl::GetUnifiedData()
{
    if (unifiedData_ == nullptr) {
        unifiedData_ = std::make_shared<UDMF::UnifiedData>();
    }
    return unifiedData_;
}

void UnifiedDataImpl::SetUnifiedData(std::shared_ptr<UDMF::UnifiedData> unifiedData)
{
    unifiedData_ = unifiedData;
}

void UdmfClientImpl::AddFormRecord(
    const RefPtr<UnifiedData>& unifiedData, int32_t formId, const RequestFormInfo& cardInfo)
{
    auto formRecord = std::make_shared<UDMF::SystemDefinedForm>();
    formRecord->SetFormId(formId);
    formRecord->SetFormName(cardInfo.cardName);
    formRecord->SetBundleName(cardInfo.bundleName);
    formRecord->SetAbilityName(cardInfo.abilityName);
    formRecord->SetModule(cardInfo.moduleName);
    formRecord->SetType(UDMF::UDType::SYSTEM_DEFINED_FORM);

    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    udData->GetUnifiedData()->AddRecord(formRecord);
}

void UdmfClientImpl::AddLinkRecord(
    const RefPtr<UnifiedData>& unifiedData, const std::string& url, const std::string& description)
{
    auto record = std::make_shared<UDMF::Link>(url, description);

    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    udData->GetUnifiedData()->AddRecord(record);
}

void UdmfClientImpl::GetLinkRecord(
    const RefPtr<UnifiedData>& unifiedData, std::string& url, std::string& description)
{
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    auto records = udData->GetUnifiedData()->GetRecords();
    for (auto record : records) {
        UDMF::UDType type = record->GetType();
        if (type == UDMF::UDType::HYPERLINK) {
            UDMF::Link* link = reinterpret_cast<UDMF::Link*>(record.get());
            url = link->GetUrl();
            description = link->GetDescription();
            return;
        }
    }
}

void UdmfClientImpl::AddHtmlRecord(
    const RefPtr<UnifiedData>& unifiedData, const std::string& htmlContent, const std::string& plainContent)
{
    auto htmlRecord = std::make_shared<UDMF::Html>(htmlContent, plainContent);

    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    if (!plainContent.empty() || !htmlContent.empty()) {
        udData->GetUnifiedData()->AddRecord(htmlRecord);
    }
}

void UdmfClientImpl::GetHtmlRecord(
    const RefPtr<UnifiedData>& unifiedData, std::string& htmlContent, std::string& plainContent)
{
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    auto records = udData->GetUnifiedData()->GetRecords();
    for (auto record : records) {
        UDMF::UDType type = record->GetType();
        if (type == UDMF::UDType::HTML) {
            UDMF::Html* html = reinterpret_cast<UDMF::Html*>(record.get());
            plainContent = html->GetPlainContent();
            htmlContent = html->GetHtmlContent();
            return;
        }
    }
}

void UdmfClientImpl::AddPixelMapRecord(const RefPtr<UnifiedData>& unifiedData, std::vector<uint8_t>& data,
    PixelMapRecordDetails& details)
{
    auto record = std::make_shared<UDMF::SystemDefinedPixelMap>(data);
    UDMF::UDDetails uDetails = {
        { "width", details.width },
        { "height", details.height },
        { "pixel-format", static_cast<int32_t>(details.pixelFormat) },
        { "alpha-type", static_cast<int32_t>(details.alphaType) } };
    record->SetDetails(uDetails);
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    udData->GetUnifiedData()->AddRecord(record);
}

void UdmfClientImpl::AddImageRecord(const RefPtr<UnifiedData>& unifiedData, const std::string& uri)
{
    auto record = std::make_shared<UDMF::Image>(uri);

    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    udData->GetUnifiedData()->AddRecord(record);
}

void UdmfClientImpl::AddPlainTextRecord(const RefPtr<UnifiedData>& unifiedData, const std::string& selectedStr)
{
    auto record = std::make_shared<UDMF::PlainText>(selectedStr, "");

    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    udData->GetUnifiedData()->AddRecord(record);
}

std::string UdmfClientImpl::GetSinglePlainTextRecord(const RefPtr<UnifiedData>& unifiedData)
{
    std::string str = "";
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, str);
    CHECK_NULL_RETURN(udData->GetUnifiedData(), str);
    auto records = udData->GetUnifiedData()->GetRecords();
    if (records.size() >= 1 && records[0]->GetType() == UDMF::UDType::PLAIN_TEXT) {
        UDMF::PlainText* plainText = reinterpret_cast<UDMF::PlainText*>(records[0].get());
        str = plainText->GetContent();
    }
    return str;
}

bool UdmfClientImpl::AddFileUriRecord(const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri)
{
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, false);
    CHECK_NULL_RETURN(udData->GetUnifiedData(), false);

    for (std::string u : uri) {
        LOGI("DragDrop event AddFileUriRecord, uri:%{public}s", u.c_str());
        auto record = std::make_shared<UDMF::Image>(u);
        udData->GetUnifiedData()->AddRecord(record);
    }

    return true;
}

bool UdmfClientImpl::GetFileUriRecord(const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri)
{
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, false);
    CHECK_NULL_RETURN(udData->GetUnifiedData(), false);
    auto records = udData->GetUnifiedData()->GetRecords();

    for (auto record : records) {
        UDMF::UDType type = record->GetType();
        if (type == UDMF::UDType::IMAGE || type == UDMF::UDType::AUDIO ||
            type == UDMF::UDType::VIDEO || type == UDMF::UDType::FILE) {
            UDMF::File* file = reinterpret_cast<UDMF::File*>(record.get());
            if (file) {
                uri.emplace_back(file->GetUri());
                LOGI("DragDrop event GetFileUri, uri:%{public}s", file->GetUri().c_str());
            } else {
                LOGE("DragDrop event GetFileUri file is null");
            }
        }
    }
    return true;
}

std::vector<std::string> UdmfClientImpl::GetPlainTextRecords(const RefPtr<UnifiedData>& unifiedData)
{
    std::vector<std::string> textRecords;
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, textRecords);
    CHECK_NULL_RETURN(udData->GetUnifiedData(), textRecords);
    auto records = udData->GetUnifiedData()->GetRecords();
    for (const auto& record : records) {
        UDMF::UDType type = record->GetType();
        if (type == UDMF::UDType::PLAIN_TEXT) {
            UDMF::PlainText* plainText = reinterpret_cast<UDMF::PlainText*>(record.get());
            std::string str = plainText->GetContent();
            textRecords.emplace_back(str);
        }
    }
    return textRecords;
}

int32_t UdmfClientImpl::GetVideoRecordUri(const RefPtr<UnifiedData>& unifiedData, std::string& uri)
{
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, UDMF::E_ERROR);
    CHECK_NULL_RETURN(udData->GetUnifiedData(), UDMF::E_ERROR);
    auto records = udData->GetUnifiedData()->GetRecords();
    if (records.size() == 0) {
        return UDMF::E_ERROR;
    }
    auto video = static_cast<UDMF::Video*>(records[0].get());
    uri = video->GetUri();
    return 0;
}

std::pair<int32_t, std::string> UdmfClientImpl::GetErrorInfo(int32_t errorCode)
{
    switch (errorCode) {
        case UDMF::E_NOT_FOUND:
            return { ERROR_CODE_DRAG_DATA_NOT_FOUND, "GetData failed, data not found." };
        default:
            return { ERROR_CODE_DRAG_DATA_ERROR, "GetData failed, data error." };
    }
}

void UdmfClientImpl::AddSpanStringRecord(
    const RefPtr<UnifiedData>& unifiedData, std::vector<uint8_t>& data)
{
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_VOID(udData);
    CHECK_NULL_VOID(udData->GetUnifiedData());
    auto record = std::make_shared<UDMF::ApplicationDefinedRecord>("OPENHARMONY_STYLED_STRING_UDMF", data);
    udData->GetUnifiedData()->AddRecord(record);
}

std::vector<uint8_t> UdmfClientImpl::GetSpanStringRecord(const RefPtr<UnifiedData>& unifiedData)
{
    std::vector<uint8_t> arr;
    auto udData = AceType::DynamicCast<UnifiedDataImpl>(unifiedData);
    CHECK_NULL_RETURN(udData, arr);
    CHECK_NULL_RETURN(udData->GetUnifiedData(), arr);
    auto records = udData->GetUnifiedData()->GetRecords();
    for (auto record: records) {
        UDMF::UDType type = record->GetType();
        if (type == UDMF::UDType::APPLICATION_DEFINED_RECORD) {
            UDMF::ApplicationDefinedRecord* app = reinterpret_cast<UDMF::ApplicationDefinedRecord*>(record.get());
            if (app->GetApplicationDefinedType() == "OPENHARMONY_STYLED_STRING_UDMF") {
                arr = app->GetRawData();
                return arr;
            }
        }
    }
    return arr;
}
} // namespace OHOS::Ace
