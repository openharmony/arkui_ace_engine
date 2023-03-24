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
namespace {
} // namespace

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
    Rect nodeRect(5.0, 0.0, 15.0, 15.0);
    Rect itemRect(0.0, 0.0, 10.0, 10.0);
    Rect tempBest(0.0, 0.0, 10.0, 10.0);
    auto result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest);
    EXPECT_FALSE(result);

    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest);
    EXPECT_FALSE(result);

    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest);
    EXPECT_FALSE(result);

    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_DOWN, itemRect, tempBest);
    EXPECT_FALSE(result);

    result = CheckBetterRect(nodeRect, 0, tempBest, itemRect);
    EXPECT_FALSE(result);
}


/**
 * @tc.name: accessibilityTest002
 * @tc.desc: CheckBetterRect-OutrightBetter
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest002, TestSize.Level1)
{
    Rect nodeRect(5.0, 5.0, 15.0, 15.0);
    Rect itemRect(0.0, 0.0, 10.0, 10.0);
    Rect tempBest(0.0, 0.0, 10.0, 10.0);

    auto result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest);
    EXPECT_FALSE(result);

    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_UP, itemRect, tempBest);
    EXPECT_FALSE(result);

    nodeRect.SetLeft(0.0);
    nodeRect.SetTop(0.0);
    itemRect.SetLeft(15.0);
    tempBest.SetLeft(15.0);
    itemRect.SetTop(20.0);
    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest);
    EXPECT_FALSE(result);

    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_DOWN, itemRect, tempBest);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: accessibilityTest003
 * @tc.desc: CheckBetterRect-IsCandidateRect
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityUtilsTestNg, AccessibilityUtilsTest003, TestSize.Level1)
{
    Rect nodeRect(5.0, 0.0, 15.0, 15.0);
    Rect itemRect(0.0, 0.0, 10.0, 10.0);
    Rect tempBest(0.0, 0.0, 10.0, 10.0);
    auto result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest);
    EXPECT_FALSE(result);

    tempBest.SetLeft(10.0);
    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest);
    EXPECT_TRUE(result);

    nodeRect.SetLeft(0.0);
    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_LEFT, itemRect, tempBest);
    EXPECT_FALSE(result);

    itemRect.SetLeft(15.0);
    tempBest.SetLeft(15.0);
    itemRect.SetTop(20.0);
    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, itemRect, tempBest);
    EXPECT_FALSE(result);
    result = CheckBetterRect(nodeRect, FOCUS_DIRECTION_RIGHT, tempBest, itemRect);
    EXPECT_TRUE(result);
}
} // namespace OHOS::Ace::NG