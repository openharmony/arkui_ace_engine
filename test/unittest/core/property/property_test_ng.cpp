/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "core/components_ng/property/property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_NORMAL = 0;
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST = 1 << 7;
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_RENDER = 1 << 6;
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_MEASURE = 1;
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 5;
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT = 1 << 4;
constexpr PropertyChangeFlag TEST_PROPERTY_UPDATE_MEASURE_SELF = 1 << 3;
}

class PropertyTestNg : public testing::Test {};

/**
 * @tc.name: PropertyTestNgTest001
 * @tc.desc: Test CheckNeedRender funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckNeedRender and set input is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected: the return value is false.
     */
    bool retFlag = CheckNeedRender(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step2. call CheckNeedRender and set input is TEST_PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNeedRender(TEST_PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step3. call CheckNeedRender and set input is TEST_PROPERTY_UPDATE_RENDER.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNeedRender(TEST_PROPERTY_UPDATE_RENDER);
    EXPECT_TRUE(retFlag);
}

/**
 * @tc.name: PropertyTestNgTest002
 * @tc.desc: Test CheckNeedRequestMeasureAndLayout funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckNeedRequestMeasureAndLayout and set input is PROPERTY_UPDATE_MEASURE.
     * @tc.expected: the return value is true.
     */
    bool retFlag = CheckNeedRequestMeasureAndLayout(TEST_PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. call CheckNeedRequestMeasureAndLayout and set input is TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNeedRequestMeasureAndLayout(TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step3. call CheckNeedRequestMeasureAndLayout and set input flag is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected: the return value is false.
     */
    retFlag = CheckNeedRequestMeasureAndLayout(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: PropertyTestNgTest003
 * @tc.desc: Test CheckNeedRequestParentMeasure funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckNeedRequestParentMeasure and set input is TEST_PROPERTY_UPDATE_MEASURE.
     * @tc.expected: the return value is true.
     */
    bool retFlag = CheckNeedRequestParentMeasure(TEST_PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. call CheckNeedRequestParentMeasure set input is TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNeedRequestParentMeasure(TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step3. call CheckNeedRequestParentMeasure set input is TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNeedRequestParentMeasure(TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step4. call CheckNeedRequestParentMeasure set input is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected: the return value is false.
     */
    retFlag = CheckNeedRequestParentMeasure(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: PropertyTestNgTest004
 * @tc.desc: Test CheckNeedMeasure funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckNeedMeasure and set input is TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT.
     * @tc.expected: the return value is true.
     */
    bool retFlag = CheckNeedMeasure(TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. call CheckNeedMeasure and set input is TEST_PROPERTY_UPDATE_MEASURE_SELF.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNeedMeasure(TEST_PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step3. call CheckNeedMeasure and set input is TEST_PROPERTY_UPDATE_MEASURE_SELF.
     * @tc.expected: the return value is false.
     */
    retFlag = CheckNeedMeasure(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: PropertyTestNgTest005
 * @tc.desc: Test CheckForceParentMeasureFlag funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckForceParentMeasureFlag and set input is TEST_PROPERTY_UPDATE_MEASURE.
     * @tc.expected: the return value is true.
     */
    bool retFlag = CheckForceParentMeasureFlag(TEST_PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. call CheckForceParentMeasureFlag set input is TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckForceParentMeasureFlag(TEST_PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step3. call CheckForceParentMeasureFlag and set input is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected: the return value is false.
     */
    retFlag = CheckForceParentMeasureFlag(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: PropertyTestNgTest006
 * @tc.desc: Test CheckUpdateByChildRequest funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckUpdateByChildRequest and set input is TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST.
     * @tc.expected: step1. the return value is true.
     */
    bool retFlag = CheckUpdateByChildRequest(TEST_PROPERTY_UPDATE_BY_CHILD_REQUEST);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step2. call CheckUpdateByChildRequest and set input is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step2. the return value is false.
     */
    retFlag = CheckUpdateByChildRequest(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: PropertyTestNgTest007
 * @tc.desc: Test CheckNoChanged funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest007, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckNoChanged and set input is TEST_PROPERTY_UPDATE_MEASURE.
     * @tc.expected: the return value is false.
     */
    bool retFlag = CheckNoChanged(TEST_PROPERTY_UPDATE_MEASURE);
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step2. call CheckNoChanged and set input is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected: the return value is true.
     */
    retFlag = CheckNoChanged(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_TRUE(retFlag);
}
/**
 * @tc.name: PropertyTestNgTest008
 * @tc.desc: Test CheckNeedLayout funcation.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest008, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CheckNeedLayout and set input is TEST_PROPERTY_UPDATE_NORMAL.
     * @tc.expected:the return value is false.
     */
    bool retFlag = CheckNeedLayout(TEST_PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retFlag);
}
} // namespace OHOS::Ace::NG
