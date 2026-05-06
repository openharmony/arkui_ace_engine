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

#include "gtest/gtest.h"
#include "error_code.h"
#include "node_extened.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NodeModel;

class NodeUtilsErrorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        InitialFullImpl();
    }
    static void TearDownTestCase() {}
};

/**
 * @tc.name: NodeUtilsErrorTest_NodeUtils_GetLayoutSize_NullNode
 * @tc.desc: Test OH_ArkUI_NodeUtils_GetLayoutSize with null node parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NodeUtilsErrorTest, NodeUtils_GetLayoutSize_NullNode, TestSize.Level1)
{
    ArkUI_IntSize size;
    int32_t result = OH_ArkUI_NodeUtils_GetLayoutSize(nullptr, &size);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeUtilsErrorTest_NodeUtils_GetLayoutPosition_NullNode
 * @tc.desc: Test OH_ArkUI_NodeUtils_GetLayoutPosition with null node parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NodeUtilsErrorTest, NodeUtils_GetLayoutPosition_NullNode, TestSize.Level1)
{
    ArkUI_IntOffset localOffset;
    int32_t result = OH_ArkUI_NodeUtils_GetLayoutPosition(nullptr, &localOffset);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeUtilsErrorTest_NodeUtils_GetLayoutPositionInWindow_NullNode
 * @tc.desc: Test OH_ArkUI_NodeUtils_GetLayoutPositionInWindow with null node parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NodeUtilsErrorTest, NodeUtils_GetLayoutPositionInWindow_NullNode, TestSize.Level1)
{
    ArkUI_IntOffset globalOffset;
    int32_t result = OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(nullptr, &globalOffset);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeUtilsErrorTest_NodeUtils_GetLayoutPositionInScreen_NullNode
 * @tc.desc: Test OH_ArkUI_NodeUtils_GetLayoutPositionInScreen with null node parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NodeUtilsErrorTest, NodeUtils_GetLayoutPositionInScreen_NullNode, TestSize.Level1)
{
    ArkUI_IntOffset screenOffset;
    int32_t result = OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(nullptr, &screenOffset);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeUtilsErrorTest_NodeUtils_GetPositionWithTranslateInWindow_NullNode
 * @tc.desc: Test OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow with null node parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NodeUtilsErrorTest, NodeUtils_GetPositionWithTranslateInWindow_NullNode, TestSize.Level1)
{
    ArkUI_IntOffset translateOffset;
    int32_t result = OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow(nullptr, &translateOffset);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NodeUtilsErrorTest_NodeUtils_GetPositionWithTranslateInScreen_NullNode
 * @tc.desc: Test OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen with null node parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NodeUtilsErrorTest, NodeUtils_GetPositionWithTranslateInScreen_NullNode, TestSize.Level1)
{
    ArkUI_IntOffset translateOffset;
    int32_t result = OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen(nullptr, &translateOffset);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}
