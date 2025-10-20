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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropText(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropText(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropHintText(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropHintText(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropDesc(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropDesc(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropAccessibilityText(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropAccessibilityText(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropType(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropType(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropAccessibilityLevel(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropAccessibilityLevel(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropAccessibilityGroup(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropAccessibilityGroup(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
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
    Accessibility::PropValue newPropValue;
    Accessibility::PropValue PropValue1;
    Accessibility::PropValue PropValue2;
    EXPECT_FALSE(frameNodeRulesCheckNode1.GetPropIsEnable(PropValue1));
    EXPECT_EQ(PropValue1.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue1.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue1.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue1.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue1.valueBool, newPropValue.valueBool);
    EXPECT_FALSE(frameNodeRulesCheckNode2.GetPropIsEnable(PropValue2));
    EXPECT_EQ(PropValue2.valueType, newPropValue.valueType);
    EXPECT_EQ(PropValue2.valueArray, newPropValue.valueArray);
    EXPECT_EQ(PropValue2.valueStr, newPropValue.valueStr);
    EXPECT_EQ(PropValue2.valueNum, newPropValue.valueNum);
    EXPECT_EQ(PropValue2.valueBool, newPropValue.valueBool);
}

/**
 * @tc.name: JsAccessibilityFocusFrameNodeUtilsTest009
 * @tc.desc: test GetPropChildrenCount when no child
 * @tc.type: FUNC
 */
HWTEST_F(JsAccessibilityFocusFrameNodeUtilsTest, JsAccessibilityFocusFrameNodeUtilsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct FrameNodeRulesCheckNode
     */
    NG::FrameNodeHandleParam frameNodeHandleParam;
    auto frameNodeRulesCheckNode = FrameNodeRulesCheckNode(nullptr, 123);

    /**
     * @tc.steps: step2. test GetPropChildrenCount
     */
    Accessibility::PropValue propValue;
    EXPECT_TRUE(frameNodeRulesCheckNode.GetPropChildrenCount(propValue));
    EXPECT_EQ(propValue.valueType, Accessibility::ValueType::NUMBER);
    EXPECT_EQ(propValue.valueNum, 0);
}
} // namespace OHOS::Ace::Framework