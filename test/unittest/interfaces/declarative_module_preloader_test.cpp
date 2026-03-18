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

#include <cstdint>

#include "gtest/gtest.h"
#include "interfaces/inner_api/ace/ace_forward_compatibility.h"
#include "interfaces/inner_api/ace/declarative_module_preloader.h"
#include "interfaces/inner_api/ace/utils.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t CALL_COUNT_NONE = 0;
constexpr int32_t CALL_COUNT_ONCE = 1;
constexpr uintptr_t MOCK_HANDLE_VALUE = 0x1234;
constexpr uintptr_t TEST_RUNTIME_VALUE = 0x5678;
constexpr uintptr_t TEST_HAP_PATH_MAP_VALUE = 0x9abc;
constexpr int32_t TEST_FORM_CONFIG_VALUE = static_cast<int32_t>(FormJsXNodeLoadMode::FULL);
constexpr char TEST_BUNDLE_NAME[] = "com.test.bundle";
constexpr char MOCK_LIB_NAME[] = "libace_test_mock.z.so";
} // namespace

void* g_mockLoadLibResult = nullptr;
void* g_mockLoadSymResult = nullptr;
int32_t g_loadLibCallCount = 0;
int32_t g_loadSymCallCount = 0;
int32_t g_freeLibCallCount = 0;
void* g_lastHandle = nullptr;
const char* LAST_LIB_PATH = nullptr;
const char* LAST_SYMBOL = nullptr;
bool g_createEntryCalled = false;
void* g_createEntryRuntime = nullptr;
bool g_cardEntryCalled = false;
void* g_cardEntryRuntime = nullptr;
const char* CARD_ENTRY_BUNDLE_NAME = nullptr;
const void* g_cardEntryHapPathMap = nullptr;
bool g_formEntryCalled = false;
void* g_formEntryRuntime = nullptr;
int32_t g_formEntryConfig = CALL_COUNT_NONE;

void MockFreeLib(void* libHandle)
{
    g_freeLibCallCount++;
    g_lastHandle = libHandle;
}

void* MockLoadLib(const char* libPath)
{
    g_loadLibCallCount++;
    LAST_LIB_PATH = libPath;
    return g_mockLoadLibResult;
}

void* MockLoadSym(void* libHandle, const char* symbol)
{
    g_loadSymCallCount++;
    g_lastHandle = libHandle;
    LAST_SYMBOL = symbol;
    return g_mockLoadSymResult;
}

const char* AceForwardCompatibility::GetAceLibName()
{
    return MOCK_LIB_NAME;
}
} // namespace OHOS::Ace

#undef LOADLIB
#undef LOADSYM
#undef FREELIB
#define LOADLIB OHOS::Ace::MockLoadLib
#define LOADSYM OHOS::Ace::MockLoadSym
#define FREELIB OHOS::Ace::MockFreeLib

#include "interfaces/inner_api/ace/declarative_module_preloader.cpp"

namespace OHOS::Ace {
using namespace testing;
using namespace testing::ext;

class DeclarativeModulePreloaderTest : public testing::Test {
public:
    void SetUp() override
    {
        g_mockLoadLibResult = nullptr;
        g_mockLoadSymResult = nullptr;
        g_loadLibCallCount = CALL_COUNT_NONE;
        g_loadSymCallCount = CALL_COUNT_NONE;
        g_freeLibCallCount = CALL_COUNT_NONE;
        g_lastHandle = nullptr;
        LAST_LIB_PATH = nullptr;
        LAST_SYMBOL = nullptr;
        g_createEntryCalled = false;
        g_createEntryRuntime = nullptr;
        g_cardEntryCalled = false;
        g_cardEntryRuntime = nullptr;
        CARD_ENTRY_BUNDLE_NAME = nullptr;
        g_cardEntryHapPathMap = nullptr;
        g_formEntryCalled = false;
        g_formEntryRuntime = nullptr;
        g_formEntryConfig = CALL_COUNT_NONE;
    }
};

/**
 * @tc.name: DeclarativeModulePreloaderTest001
 * @tc.desc: Test InitAceModule when library loading fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest001, TestSize.Level1)
{
    InitAceModule(reinterpret_cast<void*>(TEST_RUNTIME_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_NONE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_FALSE(g_createEntryCalled);
    EXPECT_STREQ(LAST_LIB_PATH, MOCK_LIB_NAME);
    EXPECT_EQ(LAST_SYMBOL, nullptr);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest002
 * @tc.desc: Test InitAceModule when symbol lookup fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest002, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);

    InitAceModule(reinterpret_cast<void*>(TEST_RUNTIME_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_ONCE);
    EXPECT_FALSE(g_createEntryCalled);
    EXPECT_EQ(g_lastHandle, g_mockLoadLibResult);
    EXPECT_STREQ(LAST_SYMBOL, PRE_INIT_ACE_MODULE_FUNC);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest003
 * @tc.desc: Test InitAceModule when symbol lookup succeeds.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest003, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);
    g_mockLoadSymResult = reinterpret_cast<void*>(+[](void* runtime) {
        g_createEntryCalled = true;
        g_createEntryRuntime = runtime;
    });

    InitAceModule(reinterpret_cast<void*>(TEST_RUNTIME_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_TRUE(g_createEntryCalled);
    EXPECT_EQ(g_createEntryRuntime, reinterpret_cast<void*>(TEST_RUNTIME_VALUE));
    EXPECT_STREQ(LAST_SYMBOL, PRE_INIT_ACE_MODULE_FUNC);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest004
 * @tc.desc: Test InitAceModuleCard when library loading fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest004, TestSize.Level1)
{
    InitAceModuleCard(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_BUNDLE_NAME,
        reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_NONE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_FALSE(g_cardEntryCalled);
    EXPECT_STREQ(LAST_LIB_PATH, MOCK_LIB_NAME);
    EXPECT_EQ(LAST_SYMBOL, nullptr);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest005
 * @tc.desc: Test InitAceModuleCard when symbol lookup fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest005, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);

    InitAceModuleCard(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_BUNDLE_NAME,
        reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_ONCE);
    EXPECT_FALSE(g_cardEntryCalled);
    EXPECT_EQ(g_lastHandle, g_mockLoadLibResult);
    EXPECT_STREQ(LAST_SYMBOL, PRE_INIT_ACE_MODULE_FUNC_CARD);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest006
 * @tc.desc: Test InitAceModuleCard when symbol lookup succeeds.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest006, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);
    g_mockLoadSymResult = reinterpret_cast<void*>(+[](void* runtime, const char* bundleName, const void* hapPathMap) {
        g_cardEntryCalled = true;
        g_cardEntryRuntime = runtime;
        CARD_ENTRY_BUNDLE_NAME = bundleName;
        g_cardEntryHapPathMap = hapPathMap;
    });

    InitAceModuleCard(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_BUNDLE_NAME,
        reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_TRUE(g_cardEntryCalled);
    EXPECT_EQ(g_cardEntryRuntime, reinterpret_cast<void*>(TEST_RUNTIME_VALUE));
    EXPECT_STREQ(CARD_ENTRY_BUNDLE_NAME, TEST_BUNDLE_NAME);
    EXPECT_EQ(g_cardEntryHapPathMap, reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));
    EXPECT_STREQ(LAST_SYMBOL, PRE_INIT_ACE_MODULE_FUNC_CARD);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest007
 * @tc.desc: Test ReloadAceModuleCard when library loading fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest007, TestSize.Level1)
{
    ReloadAceModuleCard(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_BUNDLE_NAME,
        reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_NONE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_FALSE(g_cardEntryCalled);
    EXPECT_STREQ(LAST_LIB_PATH, MOCK_LIB_NAME);
    EXPECT_EQ(LAST_SYMBOL, nullptr);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest008
 * @tc.desc: Test ReloadAceModuleCard when symbol lookup fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest008, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);

    ReloadAceModuleCard(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_BUNDLE_NAME,
        reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_ONCE);
    EXPECT_FALSE(g_cardEntryCalled);
    EXPECT_EQ(g_lastHandle, g_mockLoadLibResult);
    EXPECT_STREQ(LAST_SYMBOL, RELOAD_ACE_MODULE_FUNC_CARD);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest009
 * @tc.desc: Test ReloadAceModuleCard when symbol lookup succeeds.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest009, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);
    g_mockLoadSymResult = reinterpret_cast<void*>(+[](void* runtime, const char* bundleName, const void* hapPathMap) {
        g_cardEntryCalled = true;
        g_cardEntryRuntime = runtime;
        CARD_ENTRY_BUNDLE_NAME = bundleName;
        g_cardEntryHapPathMap = hapPathMap;
    });

    ReloadAceModuleCard(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_BUNDLE_NAME,
        reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_TRUE(g_cardEntryCalled);
    EXPECT_EQ(g_cardEntryRuntime, reinterpret_cast<void*>(TEST_RUNTIME_VALUE));
    EXPECT_STREQ(CARD_ENTRY_BUNDLE_NAME, TEST_BUNDLE_NAME);
    EXPECT_EQ(g_cardEntryHapPathMap, reinterpret_cast<const void*>(TEST_HAP_PATH_MAP_VALUE));
    EXPECT_STREQ(LAST_SYMBOL, RELOAD_ACE_MODULE_FUNC_CARD);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest010
 * @tc.desc: Test LoadJsXNodeForm when library loading fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest010, TestSize.Level1)
{
    LoadJsXNodeForm(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_FORM_CONFIG_VALUE);

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_NONE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_FALSE(g_formEntryCalled);
    EXPECT_STREQ(LAST_LIB_PATH, MOCK_LIB_NAME);
    EXPECT_EQ(LAST_SYMBOL, nullptr);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest011
 * @tc.desc: Test LoadJsXNodeForm when symbol lookup fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest011, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);

    LoadJsXNodeForm(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_FORM_CONFIG_VALUE);

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_ONCE);
    EXPECT_FALSE(g_formEntryCalled);
    EXPECT_EQ(g_lastHandle, g_mockLoadLibResult);
    EXPECT_STREQ(LAST_SYMBOL, LOAD_JS_XNODE_FUNC_FORM);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest012
 * @tc.desc: Test LoadJsXNodeForm when symbol lookup succeeds.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest012, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);
    g_mockLoadSymResult = reinterpret_cast<void*>(+[](void* runtime, int32_t config) {
        g_formEntryCalled = true;
        g_formEntryRuntime = runtime;
        g_formEntryConfig = config;
    });

    LoadJsXNodeForm(reinterpret_cast<void*>(TEST_RUNTIME_VALUE), TEST_FORM_CONFIG_VALUE);

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_TRUE(g_formEntryCalled);
    EXPECT_EQ(g_formEntryRuntime, reinterpret_cast<void*>(TEST_RUNTIME_VALUE));
    EXPECT_EQ(g_formEntryConfig, TEST_FORM_CONFIG_VALUE);
    EXPECT_STREQ(LAST_SYMBOL, LOAD_JS_XNODE_FUNC_FORM);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest013
 * @tc.desc: Test InitAceModuleWorker when library loading fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest013, TestSize.Level1)
{
    InitAceModuleWorker(reinterpret_cast<void*>(TEST_RUNTIME_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_NONE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_FALSE(g_createEntryCalled);
    EXPECT_STREQ(LAST_LIB_PATH, MOCK_LIB_NAME);
    EXPECT_EQ(LAST_SYMBOL, nullptr);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest014
 * @tc.desc: Test InitAceModuleWorker when symbol lookup fails.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest014, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);

    InitAceModuleWorker(reinterpret_cast<void*>(TEST_RUNTIME_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_ONCE);
    EXPECT_FALSE(g_createEntryCalled);
    EXPECT_EQ(g_lastHandle, g_mockLoadLibResult);
    EXPECT_STREQ(LAST_SYMBOL, PRE_INIT_ACE_MODULE_FUNC_WORKER);
}

/**
 * @tc.name: DeclarativeModulePreloaderTest015
 * @tc.desc: Test InitAceModuleWorker when symbol lookup succeeds.
 * @tc.type: FUNC
 */
HWTEST_F(DeclarativeModulePreloaderTest, DeclarativeModulePreloaderTest015, TestSize.Level1)
{
    g_mockLoadLibResult = reinterpret_cast<void*>(MOCK_HANDLE_VALUE);
    g_mockLoadSymResult = reinterpret_cast<void*>(+[](void* runtime) {
        g_createEntryCalled = true;
        g_createEntryRuntime = runtime;
    });

    InitAceModuleWorker(reinterpret_cast<void*>(TEST_RUNTIME_VALUE));

    EXPECT_EQ(g_loadLibCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_loadSymCallCount, CALL_COUNT_ONCE);
    EXPECT_EQ(g_freeLibCallCount, CALL_COUNT_NONE);
    EXPECT_TRUE(g_createEntryCalled);
    EXPECT_EQ(g_createEntryRuntime, reinterpret_cast<void*>(TEST_RUNTIME_VALUE));
    EXPECT_STREQ(LAST_SYMBOL, PRE_INIT_ACE_MODULE_FUNC_WORKER);
}
} // namespace OHOS::Ace
