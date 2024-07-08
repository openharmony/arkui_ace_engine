/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "native_interface.h"
#include "native_node_napi.h"
#include "native_type.h"

using namespace testing;
using namespace testing::ext;

class NativeNodeNapiTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NativeNodeNapiTest001
 * @tc.desc: Test OH_ArkUI_GetContextFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest001, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_ContextHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetContextFromNapiValue(env, value, context);
    EXPECT_EQ(code, 401);
}

/**
 * @tc.name: NativeNodeNapiTest002
 * @tc.desc: Test OH_ArkUI_GetNodeContentFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest002, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_NodeContentHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetNodeContentFromNapiValue(env, value, context);
    EXPECT_EQ(code, 401);
}

/**
 * @tc.name: NativeNodeNapiTest003
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest003, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_NodeHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, context);
    EXPECT_EQ(code, 401);
}

/**
 * @tc.name: NativeNodeNapiTest004
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest004, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(static_cast<ArkUI_NativeAPIVariantKind>(-1), "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest005
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest005, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest006
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest006, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_DIALOG, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest007
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest007, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest008
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest008, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_ANIMATE, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest009
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest009, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(
        static_cast<ArkUI_NativeAPIVariantKind>(ARKUI_NATIVE_GESTURE + 1), "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NavigationAPITest001
 * @tc.desc: Test OH_ArkUI_GetNavigationId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest001, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavigationId(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest002
 * @tc.desc: Test OH_ArkUI_GetNavDestinationName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest002, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationName(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest003
 * @tc.desc: Test OH_ArkUI_GetNavStackLength function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest003, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavStackLength(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest004
 * @tc.desc: Test OH_ArkUI_GetNavDestinationNameByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest004, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationNameByIndex(nullptr, 0, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest005
 * @tc.desc: Test OH_ArkUI_GetNavDestinationId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest005, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationId(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest006
 * @tc.desc: Test OH_ArkUI_GetNavDestinationState function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest006, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationState(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest007
 * @tc.desc: Test OH_ArkUI_GetNavDestinationIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest007, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationIndex(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest008
 * @tc.desc: Test OH_ArkUI_GetNavDestinationParam function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest008, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationParam(nullptr);
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: NavigationAPITest009
 * @tc.desc: Test OH_ArkUI_GetRouterPageIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest009, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageIndex(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest010
 * @tc.desc: Test OH_ArkUI_GetRouterPageName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest010, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageName(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest011
 * @tc.desc: Test OH_ArkUI_GetRouterPagePath function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest011, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPagePath(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest012
 * @tc.desc: Test OH_ArkUI_GetRouterPageState function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest012, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageState(nullptr, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest013
 * @tc.desc: Test OH_ArkUI_GetRouterPageId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest013, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageId(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}
