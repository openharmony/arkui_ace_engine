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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Kit {
class DimensionTest : public testing::Test {
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();

        MockContainer::Current()->pipelineContext_->dipScale_ = 3.0f;
        MockContainer::Current()->pipelineContext_->followSystem_ = true;
        MockContainer::Current()->pipelineContext_->maxAppFontScale_ = 3.0f;
        MockContainer::Current()->pipelineContext_->fontScale_ = 3.0f;
        MockContainer::Current()->pipelineContext_->designWidthScale_ = 4.0f;
    }
    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }
};

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

/**
 * @tc.name: DimensionTest010
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest010, TestSize.Level1)
{
    auto dimension = Dimension::FromString("1vp");
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    auto value = dimension.ConvertToPx(3);
    EXPECT_TRUE(NearEqual(value, 3));

    dimension = Dimension::FromString("1fp");
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::FP);
    value = dimension.ConvertToPx(3);
    EXPECT_TRUE(NearEqual(value, 3));

    dimension = Dimension::FromString("1px");
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
    value = dimension.ConvertToPx(3);
    EXPECT_TRUE(NearEqual(value, 1));
}

/**
 * @tc.name: DimensionTest011
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest011, TestSize.Level1)
{
    auto dimension = Dimension::FromString("1vp");
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    auto value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension::FromString("3px");
    EXPECT_TRUE(NearEqual(dimension.Value(), 3.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension(3, DimensionUnit::NONE);
    EXPECT_TRUE(NearEqual(dimension.Value(), 3.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::NONE);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension::FromString("3fp");
    EXPECT_TRUE(NearEqual(dimension.Value(), 3.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::FP);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 9));

    dimension = Dimension::FromString("3lpx");
    EXPECT_TRUE(NearEqual(dimension.Value(), 3.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::LPX);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 4));

    dimension = Dimension(1.0f, DimensionUnit::CALC);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::CALC);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 0.0f));

    dimension = Dimension(1.0f, DimensionUnit::INVALID);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::INVALID);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 0.0f));

    dimension = Dimension(50, DimensionUnit::PERCENT);
    EXPECT_TRUE(NearEqual(dimension.Value(), 50));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PERCENT);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 0.0f));

    dimension = Dimension(1.0f, DimensionUnit::AUTO);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::AUTO);
    value = dimension.ConvertToVp();
    EXPECT_TRUE(NearEqual(value, 0.0f));
}

/**
 * @tc.name: DimensionTest012
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest012, TestSize.Level1)
{
    auto dimension = Dimension(1.0f, DimensionUnit::PX);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
    auto value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension(1.0f, DimensionUnit::NONE);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::NONE);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension(1.0f, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 3));

    dimension = Dimension(1.0f, DimensionUnit::FP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::FP);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 9));

    dimension = Dimension(1.0f, DimensionUnit::LPX);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::LPX);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 4));

    dimension = Dimension(1.0f, DimensionUnit::INVALID);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::INVALID);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 0));

    dimension = Dimension(50, DimensionUnit::PERCENT);
    EXPECT_TRUE(NearEqual(dimension.Value(), 50));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PERCENT);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 0));

    dimension = Dimension(50, DimensionUnit::AUTO);
    EXPECT_TRUE(NearEqual(dimension.Value(), 50));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::AUTO);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 0));

    dimension = Dimension(50, DimensionUnit::CALC);
    EXPECT_TRUE(NearEqual(dimension.Value(), 50));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::CALC);
    value = dimension.ConvertToPx();
    EXPECT_TRUE(NearEqual(value, 0));
}

/**
 * @tc.name: DimensionTest013
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DimensionTest, DimensionTest013, TestSize.Level1)
{
    auto dimension = Dimension(1.0f, DimensionUnit::FP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 1.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::FP);
    auto value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension(9.0f, DimensionUnit::NONE);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::NONE);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension(9.0f, DimensionUnit::PX);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PX);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 1));

    dimension = Dimension(9.0f, DimensionUnit::VP);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::VP);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 3));

    dimension = Dimension(9.0f, DimensionUnit::LPX);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::LPX);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 4));

    dimension = Dimension(9.0f, DimensionUnit::INVALID);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::INVALID);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 0));

    dimension = Dimension(9.0f, DimensionUnit::PERCENT);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::PERCENT);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 0));

    dimension = Dimension(9.0f, DimensionUnit::AUTO);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::AUTO);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 0));

    dimension = Dimension(9.0f, DimensionUnit::CALC);
    EXPECT_TRUE(NearEqual(dimension.Value(), 9.0));
    EXPECT_EQ(dimension.Unit(), DimensionUnit::CALC);
    value = dimension.ConvertToFp();
    EXPECT_TRUE(NearEqual(value, 0));
}
} // namespace OHOS::Ace::Kit
