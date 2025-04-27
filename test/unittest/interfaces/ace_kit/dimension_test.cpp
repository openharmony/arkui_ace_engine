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
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Kit {
class DimensionTest : public testing::Test {};

/**
 * @tc.name: DimensionTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest001, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    dimension.Reset();
    EXPECT_TRUE(NearEqual(dimension.Value(), 0.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: DimensionTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest002, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    dimension.SetValue(100.0);
    EXPECT_TRUE(NearEqual(dimension.Value(), 100.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
}

/**
 * @tc.name: DimensionTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest003, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    dimension.SetUnit(DimensionUnit::PX);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
}

/**
 * @tc.name: DimensionTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest004, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    EXPECT_TRUE(dimension.IsValid());

    dimension.SetValue(0);
    EXPECT_FALSE(dimension.IsValid());
}

/**
 * @tc.name: DimensionTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest005, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    EXPECT_TRUE(dimension.IsNonNegative());

    dimension.SetValue(-1);
    EXPECT_FALSE(dimension.IsNonNegative());
}

/**
 * @tc.name: DimensionTest006
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest006, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    EXPECT_FALSE(dimension.IsNonPositive());

    dimension.SetValue(-1);
    EXPECT_TRUE(dimension.IsNonPositive());
}

/**
 * @tc.name: DimensionTest007
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest007, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    EXPECT_FALSE(dimension.IsNegative());

    dimension.SetValue(-1);
    EXPECT_TRUE(dimension.IsNegative());
}

/**
 * @tc.name: DimensionTest008
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest008, TestSize.Level1)
{
    Dimension dimension(1.0, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    EXPECT_FALSE(dimension.IsNegative());
    EXPECT_EQ(dimension.ToString(), "1.00vp");
}

/**
 * @tc.name: DimensionTest009
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest009, TestSize.Level1)
{
    auto dimension = Dimension::FromString("1px");
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
}
} // namespace OHOS::Ace::Kit
