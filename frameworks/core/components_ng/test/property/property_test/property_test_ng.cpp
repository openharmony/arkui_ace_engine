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
class PropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: PropertyTestNgTest001
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedRender and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step1. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    bool retResult = CheckNeedRender(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
    /**
     * @tc.steps: step2. call CheckNeedRender and set input is PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST.
     * @tc.expected: step2. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST = 1 << 7;

    retResult = CheckNeedRender(PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step3. call CheckNeedRender and set input is PROPERTY_UPDATE_RENDER.
     * @tc.expected: step3. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_RENDER = 1 << 6;

    retResult = CheckNeedRender(PROPERTY_UPDATE_RENDER);
    EXPECT_TRUE(retResult);
}

/**
 * @tc.name: PropertyTestNgTest002
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedRequestMeasureAndLayout and set input is PROPERTY_UPDATE_MEASURE.
     * @tc.expected: step1. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;

    bool retResult = CheckNeedRequestMeasureAndLayout(PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step2. call CheckNeedRequestMeasureAndLayout and set input is PROPERTY_UPDATE_BY_CHILD_REQUEST.
     * @tc.expected: step2. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 5;

    retResult = CheckNeedRequestMeasureAndLayout(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step3. call CheckNeedRequestMeasureAndLayout and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step3. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    retResult = CheckNeedRequestMeasureAndLayout(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
}

/**
 * @tc.name: PropertyTestNgTest003
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedRequestParentMeasure and set input is PROPERTY_UPDATE_MEASURE.
     * @tc.expected: step1. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;

    bool retResult = CheckNeedRequestParentMeasure(PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step2. call CheckNeedRequestParentMeasure and set input is PROPERTY_UPDATE_BY_CHILD_REQUEST.
     * @tc.expected: step2. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 5;

    retResult = CheckNeedRequestParentMeasure(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step3. call CheckNeedRequestParentMeasure and set input is PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT.
     * @tc.expected: step3. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT = 1 << 4;

    retResult = CheckNeedRequestParentMeasure(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step4. call CheckNeedRequestParentMeasure and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step4. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    retResult = CheckNeedRequestParentMeasure(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
}

/**
 * @tc.name: PropertyTestNgTest004
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedMeasure and set input is PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT.
     * @tc.expected: step1. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT = 1 << 4;

    bool retResult = CheckNeedMeasure(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step2. call CheckNeedMeasure and set input is PROPERTY_UPDATE_MEASURE_SELF.
     * @tc.expected: step2. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF = 1 << 3;

    retResult = CheckNeedMeasure(PROPERTY_UPDATE_MEASURE_SELF);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step3. call CheckNeedMeasure and set input is PROPERTY_UPDATE_MEASURE_SELF.
     * @tc.expected: step3. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    retResult = CheckNeedMeasure(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
}

/**
 * @tc.name: PropertyTestNgTest005
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckForceParentMeasureFlag and set input is PROPERTY_UPDATE_MEASURE.
     * @tc.expected: step1. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;

    bool retResult = CheckForceParentMeasureFlag(PROPERTY_UPDATE_MEASURE);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step2. call CheckForceParentMeasureFlag and set input is PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT.
     * @tc.expected: step2. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT = 1 << 4;

    retResult = CheckForceParentMeasureFlag(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step3. call CheckForceParentMeasureFlag and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step3. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    retResult = CheckForceParentMeasureFlag(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
}

/**
 * @tc.name: PropertyTestNgTest006
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckUpdateByChildRequest and set input is PROPERTY_UPDATE_BY_CHILD_REQUEST.
     * @tc.expected: step1. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_BY_CHILD_REQUEST = 1 << 5;

    bool retResult = CheckUpdateByChildRequest(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    EXPECT_TRUE(retResult);
    /**
     * @tc.steps: step2. call CheckUpdateByChildRequest and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step2. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    retResult = CheckUpdateByChildRequest(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
}

/**
 * @tc.name: PropertyTestNgTest007
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNoChanged and set input is PROPERTY_UPDATE_MEASURE.
     * @tc.expected: step1. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_MEASURE = 1;

    bool retResult = CheckNoChanged(PROPERTY_UPDATE_MEASURE);
    EXPECT_FALSE(retResult);
    /**
     * @tc.steps: step2. call CheckNoChanged and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step2. the return value is true.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    retResult = CheckNoChanged(PROPERTY_UPDATE_NORMAL);
    EXPECT_TRUE(retResult);
}
/**
 * @tc.name: PropertyTestNgTest008
 * @tc.desc: Set one index value into PropertyTestNg and get it.
 * @tc.type: FUNC
 */
HWTEST_F(PropertyTestNg, PropertyTestNgTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call CheckNeedLayout and set input is PROPERTY_UPDATE_NORMAL.
     * @tc.expected: step1. the return value is false.
     */
    PropertyChangeFlag PROPERTY_UPDATE_NORMAL = 0;

    bool retResult = CheckNeedLayout(PROPERTY_UPDATE_NORMAL);
    EXPECT_FALSE(retResult);
}
} // namespace OHOS::Ace::NG
