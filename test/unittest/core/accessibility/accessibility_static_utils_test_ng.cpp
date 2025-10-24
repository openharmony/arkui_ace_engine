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

#include <climits>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/accessibility/static/accessibility_static_utils.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class AccessibilityStaticUtilsTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AccessibilityUtilsTest006
 * @tc.desc: GetPageModeType_NormalCases
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTestNg, AccessibilityUtilsTest006, TestSize.Level1)
{
    /**
     * @tc.step1: use nornal input to GetPageModeType.
     * @tc.expected: GetPageModeType return right result.
     */
    EXPECT_EQ(AccessibilityStaticUtils::GetPageModeType(0), "SEMI_SILENT");
    EXPECT_EQ(AccessibilityStaticUtils::GetPageModeType(1), "FULL_SILENT");
}

/**
 * @tc.name: AccessibilityUtilsTest007
 * @tc.desc: GetPageModeType_AbnormalCases
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTestNg, AccessibilityUtilsTest007, TestSize.Level1)
{
    /**
     * @tc.step1: use abnormal input to GetPageModeType.
     * @tc.expected: GetPageModeType return empty string.
     */
    EXPECT_EQ(AccessibilityStaticUtils::GetPageModeType(-1), "");
    EXPECT_EQ(AccessibilityStaticUtils::GetPageModeType(2), "");
    EXPECT_EQ(AccessibilityStaticUtils::GetPageModeType(INT_MAX), "");
    EXPECT_EQ(AccessibilityStaticUtils::GetPageModeType(INT_MIN), "");
}

/**
 * @tc.name: AccessibilityUtilsTest008
 * @tc.desc: GetFocusDrawLevel_NormalCases
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTestNg, AccessibilityUtilsTest008, TestSize.Level1)
{
    /**
     * @tc.step1: use nornal input to GetFocusDrawLevel.
     * @tc.expected: GetFocusDrawLevel return right result.
     */
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(0), 0);
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(1), 1);
}

/**
 * @tc.name: AccessibilityUtilsTest009
 * @tc.desc: GetFocusDrawLevel_AbnormalCases
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTestNg, AccessibilityUtilsTest009, TestSize.Level1)
{
    /**
     * @tc.step1: use abnormal input to GetFocusDrawLevel.
     * @tc.expected: GetFocusDrawLevel return -1.
     */
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(-1), -1);
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(2), -1);
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(INT_MAX), -1);
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(INT_MIN), -1);
}

/**
 * @tc.name: AccessibilityUtilsTest010
 * @tc.desc: GetFocusDrawLevel_AbnormalCases
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityStaticUtilsTestNg, AccessibilityUtilsTest010, TestSize.Level1)
{
    /**
     * @tc.step1: use abnormal input to GetFocusDrawLevel.
     * @tc.expected: GetFocusDrawLevel return 0 or 1.
     */
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(0), 0);
    EXPECT_EQ(AccessibilityStaticUtils::GetFocusDrawLevel(1), 1);
}
} // namespace OHOS::Ace::NG
