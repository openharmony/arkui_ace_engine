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
    // The UTF-8 payload {"texts":[]} contains 12 bytes, excluding its terminating NUL.
    *size = 12;
    // Allocate 13 bytes for the 12-byte JSON payload plus its terminating NUL.
    *data = static_cast<char*>(std::malloc(13));
    if (!*data) {
        *reason = "Page text allocation failed.";
        // 100001 is ARKUI_ERROR_CODE_INTERNAL_ERROR for an allocation failure.
        return 100001;
    }
    // Copy all 13 bytes so the 12-byte JSON payload remains NUL-terminated.
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
    // 401 is ARKUI_ERROR_CODE_PARAM_INVALID for the null output slot.
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(nullptr, nullptr), 401);
    EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("output slot"), std::string::npos);
    // 190001 is ARKUI_ERROR_CODE_UI_CONTEXT_INVALID for the null UI context.
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
    // Instance ID 17 is a non-default mock instance used to verify forwarding through the public API.
    ArkUI_Context context { 17 };
    OH_ArkUI_NativeModule_UIJsonWrapper* old = nullptr;
    ASSERT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &old), 0);
    // The collector must receive the exact mock instance ID 17 supplied by the caller.
    EXPECT_EQ(lastInstance, 17);
    EXPECT_EQ(OH_ArkUI_NativeModule_UIJsonWrapper_GetSchemaVersion(old), 1u);
    OH_ArkUI_NativeModule_UIJsonWrapper* result = old;
    // Inject 100001 (ARKUI_ERROR_CODE_INTERNAL_ERROR) to test failure followed by recovery.
    collectCode = 100001;
    // 100001 is the injected ARKUI_ERROR_CODE_INTERNAL_ERROR and must reach the caller unchanged.
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
    // 500 is ARKUI_ERROR_CODE_CAPI_INIT_ERROR while the query implementation is unavailable.
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 500);
    auto message = std::string(OH_ArkUI_NativeModule_GetErrorMessage());
    // The diagnostic must contain code 500, matching the unavailable query implementation.
    EXPECT_NE(message.find("500"), std::string::npos);
    std::thread worker([] {
        OH_ArkUI_NativeModule_GetPageText(nullptr, nullptr);
        // Code 401 identifies the worker thread null-output error and must not replace the caller diagnostic.
        EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("401"), std::string::npos);
    });
    worker.join();
    EXPECT_EQ(OH_ArkUI_NativeModule_GetErrorMessage(), message);
    // Record 401 (ARKUI_ERROR_CODE_PARAM_INVALID) to verify replacement of the preceding diagnostic.
    OHOS::Ace::SetErrorMessageByModifier(401, "anotherAPI", "new error");
    EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("anotherAPI"), std::string::npos);
}

TEST_F(PageTextCapiTest, allocationFailuresAndRecovery)
{
    ArkUI_Context context { 1 };
    OH_ArkUI_NativeModule_UIJsonWrapper* result = nullptr;
    failMalloc = true;
    // 100001 is ARKUI_ERROR_CODE_INTERNAL_ERROR for the injected collection allocation failure.
    EXPECT_EQ(OH_ArkUI_NativeModule_GetPageText(&context, &result), 100001);
    EXPECT_EQ(result, nullptr);
    EXPECT_NE(std::string(OH_ArkUI_NativeModule_GetErrorMessage()).find("allocation"), std::string::npos);
    failMalloc = true;
    // The payload {} is 2 bytes; allocation failure must return 100001 (ARKUI_ERROR_CODE_INTERNAL_ERROR).
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
    // A 1024-byte reason verifies that long legacy diagnostics are preserved without truncation.
    std::string longReason(1024, 'r');
    // A 256-byte function name verifies preservation of long names in the shared diagnostic channel.
    std::string longName(256, 'n');
    // Use 401 (ARKUI_ERROR_CODE_PARAM_INVALID) as the error paired with the long diagnostic strings.
    OHOS::Ace::SetErrorMessageByModifier(401, longName.c_str(), longReason.c_str());
    auto message = std::string(OH_ArkUI_NativeModule_GetErrorMessage());
    EXPECT_NE(message.find(longName), std::string::npos);
    EXPECT_NE(message.find(longReason), std::string::npos);
    // 500 (ARKUI_ERROR_CODE_CAPI_INIT_ERROR) replaces the code while retaining the existing function name.
    OHOS::Ace::SetErrorCodeAndMessageByModifier(500, "short reason");
    message = OH_ArkUI_NativeModule_GetErrorMessage();
    EXPECT_NE(message.find(longName), std::string::npos);
    EXPECT_NE(message.find("short reason"), std::string::npos);
    OHOS::Ace::SetErrorFunctionNameByModifier("short name");
    EXPECT_STREQ(OH_ArkUI_NativeModule_GetErrorMessage(),
        "errorCode: 500, functionName: short name, errorMessage: short reason");
}
