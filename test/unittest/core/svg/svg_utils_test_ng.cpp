/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <string>
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_rect.h"
#include "frameworks/core/components_ng/svg/svg_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SvgUtilsTestNg : public testing::Test {};

/**
 * @tc.name: SvgCalculate001
 * @tc.desc: test view box invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate001, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 100, 100 };
    Size svgSize = { -50, -50 };
    Rect viewBox = { -4.0, -10.0, -300.0, -300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgContainerSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgContainerSize.Height());
}

/**
 * @tc.name: SvgCalculate002
 * @tc.desc: test view box invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate002, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 100, 100 };
    Size svgSize = { 50, -50 };
    Rect viewBox = { -4.0, -10.0, -300.0, -300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgContainerSize.Height());
}

/**
 * @tc.name: SvgCalculate003
 * @tc.desc: test view box invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate003, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 100, 100 };
    Size svgSize = { -50, 50 };
    Rect viewBox = { -4.0, -10.0, -300.0, -300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgContainerSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgSize.Height());
}

/**
 * @tc.name: SvgCalculate004
 * @tc.desc: test view box invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate004, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 0, 0 };
    Size svgSize = { -50, -50 };
    Rect viewBox = { -4.0, -10.0, -300.0, -300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgContainerSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgContainerSize.Height());
}

/**
 * @tc.name: SvgCalculate005
 * @tc.desc: test view box valid and svg invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate005, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 0, 0};
    Size svgSize = { -50, -50 };
    Rect viewBox = { -4.0, -10.0, 300.0, 300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgContainerSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgContainerSize.Height());
}

/**
 * @tc.name: SvgCalculate006
 * @tc.desc: test view box valid and svg width valid, height invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate006, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 0, 0 };
    Size svgSize = { 50, -50 };
    Rect viewBox = { -4.0, -10.0, 300.0, 300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), viewBox.Height() / viewBox.Width() * svgSize.Width());
}

/**
 * @tc.name: SvgCalculate007
 * @tc.desc: test view box valid and svg width valid, height invalid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate007, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 0, 0 };
    Size svgSize = { -50, 50 };
    Rect viewBox = { -4.0, -10.0, 300.0, 300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), viewBox.Width() / viewBox.Height() * svgSize.Height());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgSize.Height());
}

/**
 * @tc.name: SvgCalculate008
 * @tc.desc: test view box valid and svg valid
 * @tc.type: FUNC
 */
HWTEST_F(SvgUtilsTestNg, SvgCalculate008, TestSize.Level1)
{
    Size svgContentSize;
    Size svgContainerSize = { 0, 0 };
    Size svgSize = { 50, 50 };
    Rect viewBox = { -4.0, -10.0, 300.0, 300.0 };
    SvgUtils::CalculateSvgConentSize(svgContentSize, svgContainerSize,
        svgSize, viewBox);
    EXPECT_FLOAT_EQ(svgContentSize.Width(), svgSize.Width());
    EXPECT_FLOAT_EQ(svgContentSize.Height(), svgSize.Height());
}
} // namespace OHOS::Ace::NG
