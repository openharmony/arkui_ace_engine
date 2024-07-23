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

#ifndef FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_UDMF_H
#define FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_UDMF_H

#include "gmock/gmock-function-mocker.h"
#include "gmock/gmock.h"

#include "base/memory/ace_type.h"
#include "core/common/udmf/udmf_client.h"

namespace OHOS::Ace {
class MockUdmfClient : public UdmfClient {
    DECLARE_ACE_TYPE(MockUdmfClient, UdmfClient);

public:
    MOCK_METHOD(RefPtr<UnifiedData>, TransformUnifiedData, (napi_value napiValue), (override));
    MOCK_METHOD(napi_value, TransformUdmfUnifiedData, (RefPtr<UnifiedData>& UnifiedData), (override));
    MOCK_METHOD(RefPtr<UnifiedData>, TransformUnifiedDataForNative, (void* rawData), (override));
    MOCK_METHOD(void*, TransformUnifiedDataPtr, (RefPtr<UnifiedData>& UnifiedData), (override));
    MOCK_METHOD(napi_value, TransformSummary, ((std::map<std::string, int64_t>& summary)), (override));
    MOCK_METHOD(RefPtr<UnifiedData>, CreateUnifiedData, (), (override));
    MOCK_METHOD(int32_t, SetData, (const RefPtr<UnifiedData>& unifiedData, std::string& key), (override));
    MOCK_METHOD(int32_t, GetData, (const RefPtr<UnifiedData>& unifiedData, const std::string& key), (override));
    MOCK_METHOD(int32_t, GetSummary, (std::string& key, (std::map<std::string, int64_t>& summaryMap)), (override));
    MOCK_METHOD(bool, GetRemoteStatus, (std::string& key), (override));
    MOCK_METHOD(void, AddFormRecord,
        (const RefPtr<UnifiedData>& unifiedData, int32_t formId, const RequestFormInfo& cardInfo), (override));
    MOCK_METHOD(void, AddLinkRecord,
        (const RefPtr<UnifiedData>& unifiedData, const std::string& url, const std::string& description), (override));
    MOCK_METHOD(void, GetLinkRecord,
        (const RefPtr<UnifiedData>& unifiedData, std::string& url, std::string& description), (override));
    MOCK_METHOD(bool, GetFileUriRecord,
        (const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri), (override));
    MOCK_METHOD(bool, AddFileUriRecord,
        (const RefPtr<UnifiedData>& unifiedData, std::vector<std::string>& uri), (override));
    MOCK_METHOD(void, AddHtmlRecord, (const RefPtr<UnifiedData>& unifiedData,
        const std::string& htmlContent, const std::string& plainContent), (override));
    MOCK_METHOD(void, GetHtmlRecord,
        (const RefPtr<UnifiedData>& unifiedData, std::string& htmlContent, std::string& plainContent), (override));
    MOCK_METHOD(void, AddPixelMapRecord, (const RefPtr<UnifiedData>& unifiedData, (std::vector<uint8_t> & data),
        PixelMapRecordDetails& details), (override));
    MOCK_METHOD(void, AddImageRecord, (const RefPtr<UnifiedData>& unifiedData, const std::string& uri), (override));
    MOCK_METHOD(
        void, AddPlainTextRecord, (const RefPtr<UnifiedData>& unifiedData, const std::string& selectedStr), (override));
    MOCK_METHOD(std::string, GetSinglePlainTextRecord, (const RefPtr<UnifiedData>& unifiedData), (override));
    MOCK_METHOD(std::vector<std::string>, GetPlainTextRecords, (const RefPtr<UnifiedData>& unifiedData), (override));
    MOCK_METHOD(int32_t, GetVideoRecordUri, (const RefPtr<UnifiedData>& unifiedData, std::string& uri), (override));
    MOCK_METHOD((std::pair<int32_t, std::string>), GetErrorInfo, (int32_t errorCode), (override));
    MOCK_METHOD(void, AddSpanStringRecord,
        (const RefPtr<UnifiedData>& unifiedData, std::vector<uint8_t>& data), (override));
    MOCK_METHOD(std::vector<uint8_t>, GetSpanStringRecord, (const RefPtr<UnifiedData>& unifiedData), (override));
};
class MockUnifiedData : public UnifiedData {
    DECLARE_ACE_TYPE(MockUnifiedData, UnifiedData);

public:
    MockUnifiedData() {};
    ~MockUnifiedData() = default;
    MOCK_METHOD(int64_t, GetSize, (), (override));
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_TEST_MOCK_CORE_COMMON_MOCK_UDMF_H
