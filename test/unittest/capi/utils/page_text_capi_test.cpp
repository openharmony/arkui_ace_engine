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
#include <cstdlib>
#include <cstring>
#include <thread>
#include "gtest/gtest.h"
#include "interfaces/native/ui_info_collection.h"
#include "interfaces/native/native_interface.h"
#include "interfaces/native/native_error_message_wrapper.h"
#include "interfaces/native/node/node_model.h"
#include "core/interfaces/native/node/page_text_api.h"
#include "core/interfaces/native/utility/error_message_manager.h"
#include "core/components_ng/base/page_text_json.h"

namespace {
thread_local bool support = true;
thread_local bool errorSupport = true;
thread_local int32_t collectCode = 0;
thread_local int32_t lastInstance = -1;
thread_local bool failMalloc = false;
thread_local bool failRealloc = false;

int32_t Collect(int32_t id, char** data, uint32_t* size, const char** reason)
{
    lastInstance = id;
    *data = nullptr;
    *reason = "Injected collection failure.";
    if (collectCode) {
        return collectCode;
    }
    *size = 12;
    *data = static_cast<char*>(std::malloc(13));
    if (!*data) {
        *reason = "Page text allocation failed.";
        return 100001;
    }
    std::memcpy(*data, "{\"texts\":[]}", 13);
    return 0;
}
void SetCode(int32_t code, const char* reason)
{
    OHOS::Ace::ErrorMessageManager::GetInstance().SetErrorCodeAndMessage(code, reason);
}
void SetName(const char* name)
{
    OHOS::Ace::ErrorMessageManager::GetInstance().SetFunctionName(name);
}
const char* GetMessage()
{
    return OHOS::Ace::ErrorMessageManager::GetInstance().GetErrorMessage();
}
const ArkUIBasicAPI* Basic()
{
    static ArkUIBasicAPI api {};
    api.setErrorCodeAndMessage = SetCode;
    api.setErrorFunctionName = SetName;
    api.getErrorMessage = GetMessage;
    return &api;
}
}
extern "C" void* __real_malloc(size_t size);
extern "C" void* __real_realloc(void* ptr, size_t size);
extern "C" void* __wrap_malloc(size_t size)
{
    if (failMalloc) {
        failMalloc = false;
        return nullptr;
    }
    return __real_malloc(size);
}
extern "C" void* __wrap_realloc(void* ptr, size_t size)
{
    if (failRealloc) {
        failRealloc = false;
        return nullptr;
    }
    return __real_realloc(ptr, size);
}
namespace OHOS::Ace::NodeModel {
const ArkUIPageTextAPI* GetPageTextAPI()
{
    static const ArkUIPageTextAPI api { Collect, [](char* data) { std::free(data); } };
    return support ? &api : nullptr;
}
ArkUIFullNodeAPI* GetFullImplForErrorMessage()
{
    static ArkUIFullNodeAPI api {};
    api.getBasicAPI = Basic;
    return errorSupport ? &api : nullptr;
}
}

class PageTextCapiTest : public testing::Test {
public:
    void SetUp() override { support = errorSupport = true; collectCode = 0; }
};

TEST_F(PageTextCapiTest, validationOrderAndSharedDiagnostics)
{
    ArkUI_Context context { 17 };
    OH_ArkUI_NativeModule_UIJsonWrapper* result = nullptr;
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(nullptr, nullptr), 401);
    EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("output slot"), std::string::npos);
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(nullptr, &result), 190001);
    support = false;
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 500);
    auto message = std::string(OH_ArkUI_NativeModule_GetErrorMessage());
    EXPECT_NE(message.find("500"), std::string::npos);
    EXPECT_NE(message.find("OH_ArkUI_NativeModule_GetPageText"), std::string::npos);
    EXPECT_NE(message.find("unavailable"), std::string::npos);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PageTextCapiTest, failureRecoveryAndIndependentSnapshots)
{
    ArkUI_Context context { 17 };
    OH_ArkUI_NativeModule_UIJsonWrapper* old = nullptr;
    ASSERT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &old), 0);
    EXPECT_EQ(lastInstance, 17);
    EXPECT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetSchemaVersion(old), 1u);
    OH_ArkUI_NativeModule_UIJsonWrapper* result = old;
    collectCode = 100001;
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 100001);
    EXPECT_EQ(result, nullptr);
    auto error = std::string(OH_ArkUI_NativeModule_GetErrorMessage());
    EXPECT_NE(error.find("Injected collection failure"), std::string::npos);
    collectCode = 0;
    ASSERT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 0);
    EXPECT_EQ(OH_ArkUI_NativeModule_GetErrorMessage(), error);
    EXPECT_STREQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetData(old), "{\"texts\":[]}");
    EXPECT_NE(old, result);
    OH_ArkUI_NativeModule_UIJsonWrapper_Destroy(result);
    OH_ArkUI_NativeModule_UIJsonWrapper_Destroy(old);
}

TEST_F(PageTextCapiTest, originalErrorChannelAvailabilityAndThreadIsolation)
{
    support = errorSupport = false;
    ArkUI_Context context { 1 };
    OH_ArkUI_NativeModule_UIJsonWrapper* result = nullptr;
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 500);
    EXPECT_EQ(result, nullptr);
    EXPECT_STREQ(OH_ArkUI_NativeModule_GetErrorMessage(), "");
    OH_ArkUI_NativeModule_GetPageText(nullptr, nullptr);
    EXPECT_STREQ(OH_ArkUI_NativeModule_GetErrorMessage(), "");

    errorSupport = true;
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 500);
    auto message = std::string(OH_ArkUI_NativeModule_GetErrorMessage());
    EXPECT_NE(message.find("500"), std::string::npos);
    std::thread worker([] {
        OH_ArkUI_NativeModule_GetPageText(nullptr, nullptr);
        EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("401"), std::string::npos);
    });
    worker.join();
    EXPECT_EQ(OH_ArkUI_NativeModule_GetErrorMessage(), message);
    OHOS::Ace::SetErrorMessageByModifier(401, "anotherAPI", "new error");
    EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("anotherAPI"), std::string::npos);
}

TEST_F(PageTextCapiTest, allocationFailuresAndRecovery)
{
    ArkUI_Context context { 1 };
    OH_ArkUI_NativeModule_UIJsonWrapper* result = nullptr;
    failMalloc = true;
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 100001);
    EXPECT_EQ(result, nullptr);
    EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("allocation"), std::string::npos);
    failMalloc = true;
    EXPECT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_Create("{}", 2, 1, &result), 100001);
    EXPECT_EQ(result, nullptr);
    ASSERT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 0);
    OH_ArkUI_NativeModule_UIJsonWrapper_Destroy(result);
}

TEST(UIJsonWrapperTest, immutableCopyMetadataNullAndConcurrentReaders)
{
    char source[] = "{\"texts\":[]}";
    OH_ArkUI_NativeModule_UIJsonWrapper* result = nullptr;
    ASSERT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_Create(source, 12, 1, &result), 0);
    source[0] = '!';
    auto read = [result] {
        EXPECT_STREQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetData(result), "{\"texts\":[]}");
        EXPECT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetSize(result), 12u);
    };
    std::thread worker(read);
    read();
    worker.join();
    OH_ArkUI_NativeModule_UIJsonWrapper_Destroy(result);
    EXPECT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetData(nullptr), nullptr);
    EXPECT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetSchemaVersion(nullptr), 0u);
    OH_ArkUI_NativeModule_UIJsonWrapper_Destroy(nullptr);
}

TEST(PageTextJsonTest, utf8GetterPayloadAndEmbeddedNul)
{
    OHOS::Ace::NG::PageTextJson json;
    std::string text = "中文e\u0301אב\"\\\n";
    text.push_back(0);
    text += "�";
    ASSERT_TRUE(json.String(text));
    uint32_t size = 0;
    char* data = json.Release(size);
    EXPECT_EQ(std::string(data, size), "\"中文e\u0301אב\\\"\\\\\\u000a\\u0000�\"");
    EXPECT_EQ(std::strlen(data), size);
    std::free(data);
}

TEST(PageTextJsonTest, failedGrowthKeepsBufferValid)
{
    OHOS::Ace::NG::PageTextJson json;
    ASSERT_TRUE(json.Append("["));
    failRealloc = true;
    EXPECT_FALSE(json.Append("123456"));
    EXPECT_TRUE(json.Append("7]"));
    uint32_t size = 0;
    char* data = json.Release(size);
    EXPECT_EQ(std::string(data, size), "[7]");
    std::free(data);
}

TEST_F(PageTextCapiTest, sharedErrorChannelPreservesLongLegacyMessages)
{
    std::string longReason(1024, 'r');
    std::string longName(256, 'n');
    OHOS::Ace::SetErrorMessageByModifier(401, longName.c_str(), longReason.c_str());
    auto message = std::string(OH_ArkUI_NativeModule_GetErrorMessage());
    EXPECT_NE(message.find(longName), std::string::npos);
    EXPECT_NE(message.find(longReason), std::string::npos);
    OHOS::Ace::SetErrorCodeAndMessageByModifier(500, "short reason");
    message = OH_ArkUI_NativeModule_GetErrorMessage();
    EXPECT_NE(message.find(longName), std::string::npos);
    EXPECT_NE(message.find("short reason"), std::string::npos);
    OHOS::Ace::SetErrorFunctionNameByModifier("short name");
    EXPECT_STREQ(OH_ArkUI_NativeModule_GetErrorMessage(),
        "errorCode: 500, functionName: short name, errorMessage: short reason");
}
