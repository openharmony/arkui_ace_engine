/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "native_node_ani.h"

#include "gtest/gtest.h"
#include "native_interface.h"
#include "native_type.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;

class NativeNodeAniTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NativeNodeAniTest001
 * @tc.desc: Test OH_ArkUI_NativeModule_GetContextFromAniValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeAniTest, NativeNodeAniTest001, TestSize.Level1)
{
    ani_env* env = nullptr;
    ani_object value = nullptr;
    ArkUI_ContextHandle* contextHandle = nullptr;
    int32_t code = OH_ArkUI_NativeModule_GetContextFromAniValue(env, value, contextHandle);
    EXPECT_EQ(code, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeAniTest002
 * @tc.desc: Test OH_ArkUI_NativeModule_GetNodeHandleFromAniValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeAniTest, NativeNodeAniTest002, TestSize.Level1)
{
    ani_env* env = nullptr;
    ani_object value = nullptr;
    ArkUI_NodeHandle* nodeHandle = nullptr;
    int32_t code = OH_ArkUI_NativeModule_GetNodeHandleFromAniValue(env, value, nodeHandle);
    EXPECT_EQ(code, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeAniTest003
 * @tc.desc: Test OH_ArkUI_NativeModule_GetNodeContentFromAniValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeAniTest, NativeNodeAniTest003, TestSize.Level1)
{
    ani_env* env = nullptr;
    ani_object value = nullptr;
    ArkUI_NodeContentHandle* content = nullptr;
    int32_t code = OH_ArkUI_NativeModule_GetNodeContentFromAniValue(env, value, content);
    EXPECT_EQ(code, ARKUI_ERROR_CODE_PARAM_INVALID);
}
