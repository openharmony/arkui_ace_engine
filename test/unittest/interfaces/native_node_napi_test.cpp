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
#include "native_node_napi.h"

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