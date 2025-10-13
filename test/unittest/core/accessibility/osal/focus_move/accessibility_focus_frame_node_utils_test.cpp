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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_frame_node_utils.h"
#include "base/log/dump_log.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"

using namespace OHOS::Ace::NG;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
class JsAccessibilityFocusFrameNodeUtilsTest : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest001
 * @tc.desc: test GetPropText when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropText
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropText(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropText(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest002
 * @tc.desc: test GetPropHintText when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropHintText
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropHintText(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropHintText(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest003
 * @tc.desc: test GetPropDesc when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropDesc
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropDesc(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropDesc(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest004
 * @tc.desc: test GetPropAccessibilityText when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropAccessibilityText
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropAccessibilityText(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropAccessibilityText(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest005
 * @tc.desc: test GetPropType when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropType
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropType(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropType(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest006
 * @tc.desc: test GetPropAccessibilityLevel when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropAccessibilityLevel
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropAccessibilityLevel(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropAccessibilityLevel(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest007
 * @tc.desc: test GetPropAccessibilityGroup when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropAccessibilityGroup
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropAccessibilityGroup(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropAccessibilityGroup(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest008
 * @tc.desc: test GetPropIsEnable when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode1 = FrameNodeRulesCheckNode(nullptr, 123);
    auto frameNodeRulesCheckNode2 = FrameNodeRulesCheckNode(nullptr, 234, frameNodeHandleParam);

    /**
     * @tc.steps: step2. test GetPropIsEnable
     */
    Accessibility::PropValueStub newPropValueStub;
    Accessibility::PropValueStub propValueStub1;
    Accessibility::PropValueStub propValueStub2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropIsEnable(propValueStub1));
    EXPECT_EQ(propValueStub1.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub1.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub1.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub1.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub1.valueBool, newPropValueStub.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropIsEnable(propValueStub2));
    EXPECT_EQ(propValueStub2.valueType, newPropValueStub.valueType);
    EXPECT_EQ(propValueStub2.valueArray, newPropValueStub.valueArray);
    EXPECT_EQ(propValueStub2.valueStr, newPropValueStub.valueStr);
    EXPECT_EQ(propValueStub2.valueNum, newPropValueStub.valueNum);
    EXPECT_EQ(propValueStub2.valueBool, newPropValueStub.valueBool);
}
} // namespace OHOS::Ace::Framework