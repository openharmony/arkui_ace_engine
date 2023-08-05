/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_node.h"
#include "frameworks/core/accessibility/accessibility_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class AccessibilityUtilsTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: accessibilityTest001
 * @tc.desc: CheckBetterRect-IsCandidateRect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest001, TestSize.Level1)
{
    /**
     * @tc.step1: create some Rect.
     * @tc.expected: CheckBetterRect return false.
     */
    Rect nodeRect(5.0, 0.0, 15.0, 15.0);
    Rect itemRect(0.0, 0.0, 10.0, 10.0);
    Rect tempBest(0.0, 0.0, 10.0, 10.0);

    /**
     * @tc.step2: rect not change and test direction left right up down.
     * @tc.expected: CheckBetterRect always return false.
     */
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest));
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest));
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_DOWN, itemRect, tempBest));

    /**
     * @tc.step3: test CheckBetterRect with unknown direction .
     * @tc.expected: CheckBetterRect return false.
     */
    EXPECT_FALSE(CheckBetterRect(nodeRect, 0, tempBest, itemRect));
}

/**
 * @tc.name: accessibilityTest002
 * @tc.desc: CheckBetterRect-OutrightBetter
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest002, TestSize.Level1)
{
    /**
     * @tc.step1: create some Rect.
     * @tc.expected: CheckBetterRect return false.
     */
    Rect nodeRect(5.0, 5.0, 15.0, 15.0);
    Rect itemRect(0.0, 0.0, 10.0, 10.0);
    Rect tempBest(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest));
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));

    /**
     * @tc.step2: change params, nodeRect now is [0.0, 0.0, 15.0, 15.0], itemRect now is [15.0, 20.0, 10.0, 10.0],
     * @tc.step2: tempBest now is [15.0, 0.0 ,10.0 ,10.0].
     * @tc.expected: when direction is FOCUS_DIRECTION_RIGHT return false and FOCUS_DIRECTION_DOWN return true.
     */
    nodeRect.SetLeft(0.0);
    nodeRect.SetTop(0.0);
    itemRect.SetLeft(15.0);
    itemRect.SetTop(20.0);
    tempBest.SetLeft(15.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest));
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_DOWN, itemRect, tempBest));
}

/**
 * @tc.name: accessibilityTest003
 * @tc.desc: CheckBetterRect-IsCandidateRect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest003, TestSize.Level1)
{
    /**
     * @tc.step1: create some Rect.
     * @tc.expected: CheckBetterRect return false.
     */
    Rect nodeRect(5.0, 0.0, 15.0, 15.0);
    Rect itemRect(0.0, 0.0, 10.0, 10.0);
    Rect tempBest(0.0, 0.0, 10.0, 10.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest));

    /**
     * @tc.step2: change tempBest params, tempBest now is [10.0, 0.0, 10.0, 10.0].
     * @tc.expected: CheckBetterRect return true.
     */
    tempBest.SetLeft(10.0);
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest));

    /**
     * @tc.step2: change nodeRect params, nodeRect now is [0.0, 0.0, 15.0, 15.0].
     * @tc.expected: CheckBetterRect return false.
     */
    nodeRect.SetLeft(0.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest));

    /**
     * @tc.step2: change params, itemRect now is [15.0, 20.0, 10.0, 10.0], tempBest now is [15.0, 0.0, 10.0, 10.0].
     * @tc.expected: CheckBetterRect with direction FOCUS_DIRECTION_RIGHT meeting expectations.
     */
    itemRect.SetLeft(15.0);
    itemRect.SetTop(20.0);
    tempBest.SetLeft(15.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest));
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, tempBest, itemRect));
}

/**
 * @tc.name: AccessibilityUtilsTest004
 * @tc.desc: Test the direction is FOCUS_DIRECTION_UP and FOCUS_DIRECTION_DOWN left remaining situation
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.step1: create some Rect, itemRect and tempBest out nodeRect.
     * @tc.expected: CheckBetterRect return false.
     */
    Rect nodeRect(10.0, 10.0, 10.0, 10.0);
    Rect itemRect(5.0, 5.0, 5.0, 5.0);
    Rect tempBest(5.0, 5.0, 5.0, 5.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));

    /**
     * @tc.step2: change itemRect params, itemRect now is [12.5, 0.0, 5.0, 5.0].
     * @tc.expected: CheckBetterRect return false.
     */
    itemRect.SetLeft(12.5);
    itemRect.SetTop(0.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));

    /**
     * @tc.step3: change params, itemRect now is [15.0, 5.0, 5.0, 5.0], tempBest now is [5.0, 5.0, 4.0, 6.0].
     * @tc.expected: CheckBetterRect return true.
     */
    itemRect.SetLeft(15.0);
    itemRect.SetTop(5.0);
    tempBest.SetWidth(4.0);
    tempBest.SetHeight(6.0);
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));

    /**
     * @tc.step4: change tempBest params, tempBest now is [5.0, 5.0, 5.0, 5.0].
     * @tc.expected: CheckBetterRect return true.
     */
    tempBest.SetHeight(5.0);
    tempBest.SetWidth(5.0);
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));

    /**
     * @tc.step5: change tempBest params, tempBest now is [5.0, 9.5, 5.0, 0.5].
     * @tc.expected: CheckBetterRect return true.
     */
    tempBest.SetHeight(0.5);
    tempBest.SetTop(9.5);
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest));

    /**
     * @tc.step5: change params, itemRect now is [15.0, 20.0, 5.0, 5.0],  tempBest now is [20.0, 20.0, 5.0, 0.5].
     * @tc.expected: CheckBetterRect return true.
     */
    itemRect.SetTop(20.0);
    tempBest.SetLeft(20.0);
    tempBest.SetTop(20.0);
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_DOWN, itemRect, tempBest));
}

/**
 * @tc.name: AccessibilityUtilsTest005
 * @tc.desc: Verify direction is FOCUS_DIRECTION_LEFT and FOCUS_DIRECTION_RIGHT left remaining situation.
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest005, TestSize.Level1)
{
    /**
     * @tc.step1: create some Rect, intersect itemRect and nodeRect, tempBest out nodeRect.
     * @tc.expected: CheckBetterRect return true.
     */
    Rect nodeRect(10.0, 10.0, 10.0, 10.0);
    Rect itemRect(5.0, 10.0, 5.0, 5.0);
    Rect tempBest(5.0, 5.0, 5.0, 5.0);
    EXPECT_TRUE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest));

    /**
     * @tc.step2: change params, itemRect now is [20.0, 20.0, 5.0, 5.0],  tempBest now is [20.0, 5.0, 5.0, 5.0].
     * @tc.expected: CheckBetterRect return false.
     */
    itemRect.SetLeft(20.0);
    itemRect.SetTop(20.0);
    tempBest.SetLeft(20.0);
    EXPECT_FALSE(CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest));
}
} // namespace OHOS::Ace::NG
