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

#include "base/error/error_code.h"
#include "interfaces/native/native_node.h"
#include "interfaces/native/node/node_model.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class CapiSwiperOptionTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: SwiperFinishAnimationTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_FinishAnimation with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperFinishAnimationTestNullNode, TestSize.Level1)
{
    auto ret = OH_ArkUI_Swiper_FinishAnimation(nullptr);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperFinishAnimationTestWrongNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_FinishAnimation with wrong node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperFinishAnimationTestWrongNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = ARKUI_NODE_TEXT;
    node.uiNodeHandle = nullptr;
    auto ret = OH_ArkUI_Swiper_FinishAnimation(&node);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperStartFakeDragTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_StartFakeDrag with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperStartFakeDragTestNullNode, TestSize.Level1)
{
    bool isSuccessful = false;
    auto ret = OH_ArkUI_Swiper_StartFakeDrag(nullptr, &isSuccessful);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperStartFakeDragTestWrongNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_StartFakeDrag with wrong node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperStartFakeDragTestWrongNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = ARKUI_NODE_TEXT;
    node.uiNodeHandle = nullptr;
    bool isSuccessful = false;
    auto ret = OH_ArkUI_Swiper_StartFakeDrag(&node, &isSuccessful);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperFakeDragByTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_FakeDragBy with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperFakeDragByTestNullNode, TestSize.Level1)
{
    bool isConsumedOffset = false;
    auto ret = OH_ArkUI_Swiper_FakeDragBy(nullptr, 10.0f, &isConsumedOffset);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperFakeDragByTestWrongNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_FakeDragBy with wrong node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperFakeDragByTestWrongNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = ARKUI_NODE_TEXT;
    node.uiNodeHandle = nullptr;
    bool isConsumedOffset = false;
    auto ret = OH_ArkUI_Swiper_FakeDragBy(&node, 10.0f, &isConsumedOffset);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperStopFakeDragTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_StopFakeDrag with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperStopFakeDragTestNullNode, TestSize.Level1)
{
    bool isSuccessful = false;
    auto ret = OH_ArkUI_Swiper_StopFakeDrag(nullptr, &isSuccessful);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperStopFakeDragTestWrongNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_StopFakeDrag with wrong node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperStopFakeDragTestWrongNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = ARKUI_NODE_TEXT;
    node.uiNodeHandle = nullptr;
    bool isSuccessful = false;
    auto ret = OH_ArkUI_Swiper_StopFakeDrag(&node, &isSuccessful);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperIsFakeDraggingTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_IsFakeDragging with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperIsFakeDraggingTestNullNode, TestSize.Level1)
{
    bool isFakeDragging = false;
    auto ret = OH_ArkUI_Swiper_IsFakeDragging(nullptr, &isFakeDragging);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperIsFakeDraggingTestZeroNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_IsFakeDragging with zero node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperIsFakeDraggingTestZeroNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = 0;
    node.uiNodeHandle = nullptr;
    bool isFakeDragging = false;
    auto ret = OH_ArkUI_Swiper_IsFakeDragging(&node, &isFakeDragging);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperShowPreviousTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_ShowPrevious with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperShowPreviousTestNullNode, TestSize.Level1)
{
    auto ret = OH_ArkUI_Swiper_ShowPrevious(nullptr);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperShowPreviousTestWrongNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_ShowPrevious with wrong node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperShowPreviousTestWrongNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = ARKUI_NODE_TEXT;
    node.uiNodeHandle = nullptr;
    auto ret = OH_ArkUI_Swiper_ShowPrevious(&node);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperShowNextTestNullNode
 * @tc.desc: Test OH_ArkUI_Swiper_ShowNext with null node
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperShowNextTestNullNode, TestSize.Level1)
{
    auto ret = OH_ArkUI_Swiper_ShowNext(nullptr);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SwiperShowNextTestWrongNodeType
 * @tc.desc: Test OH_ArkUI_Swiper_ShowNext with wrong node type
 * @tc.type: FUNC
 */
HWTEST_F(CapiSwiperOptionTestNg, SwiperShowNextTestWrongNodeType, TestSize.Level1)
{
    ArkUI_Node node;
    node.type = ARKUI_NODE_TEXT;
    node.uiNodeHandle = nullptr;
    auto ret = OH_ArkUI_Swiper_ShowNext(&node);
    EXPECT_EQ(ret, ERROR_CODE_PARAM_INVALID);
}
}