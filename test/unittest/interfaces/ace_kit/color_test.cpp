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
#include "ui/properties/color.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class ColorTest : public testing::Test {};

/**
 * @tc.name: ColorTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest001, TestSize.Level1)
{
    auto color = Color::FromARGB(255, 255, 255, 255);
    EXPECT_EQ(color.GetAlpha(), 255);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 255);
    EXPECT_EQ(color.GetGreen(), 255);
}

/**
 * @tc.name: ColorTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest002, TestSize.Level1)
{
    auto color = Color::FromRGBO(255, 255, 255, 1);
    EXPECT_EQ(color.GetAlpha(), 255);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 255);
    EXPECT_EQ(color.GetGreen(), 255);

    auto color2 = Color::FromRGBO(255, 255, 255, 0);
    EXPECT_EQ(color2.GetAlpha(), 0);
    EXPECT_EQ(color2.GetRed(), 255);
    EXPECT_EQ(color2.GetBlue(), 255);
    EXPECT_EQ(color2.GetGreen(), 255);
}

/**
 * @tc.name: ColorTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest003, TestSize.Level1)
{
    auto color = Color::FromRGB(255, 255, 255);
    EXPECT_EQ(color.GetAlpha(), 255);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 255);
    EXPECT_EQ(color.GetGreen(), 255);
}

/**
 * @tc.name: ColorTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest004, TestSize.Level1)
{
    auto color = Color::FromString("#ffff0000");
    EXPECT_EQ(color.GetAlpha(), 255);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 0);
    EXPECT_EQ(color.GetGreen(), 0);

    color = Color::FromString("", 255, Color::FromRGB(0, 255, 0));
    EXPECT_EQ(color.GetAlpha(), 0);
    EXPECT_EQ(color.GetRed(), 0);
    EXPECT_EQ(color.GetBlue(), 0);
    EXPECT_EQ(color.GetGreen(), 0);
}

/**
 * @tc.name: ColorTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest005, TestSize.Level1)
{
    Color color;
    auto result = Color::ParseColorString("#ffff0000", color);
    EXPECT_TRUE(result);
    EXPECT_EQ(color.GetAlpha(), 255);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 0);
    EXPECT_EQ(color.GetGreen(), 0);

    result = Color::ParseColorString("#00ff0000", color);
    EXPECT_TRUE(result);
    EXPECT_EQ(color.GetAlpha(), 0);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 0);
    EXPECT_EQ(color.GetGreen(), 0);

    result = Color::ParseColorString("", color);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ColorTest006
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest006, TestSize.Level1)
{
    Color defaultColor = Color::FromARGB(255, 255, 255, 255);

    Color color;
    auto result = Color::ParseColorString("#ffff0000", color, defaultColor);
    EXPECT_TRUE(result);
    EXPECT_EQ(color.GetAlpha(), 255);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 0);
    EXPECT_EQ(color.GetGreen(), 0);

    result = Color::ParseColorString("#00ff0000", color, defaultColor);
    EXPECT_TRUE(result);
    EXPECT_EQ(color.GetAlpha(), 0);
    EXPECT_EQ(color.GetRed(), 255);
    EXPECT_EQ(color.GetBlue(), 0);
    EXPECT_EQ(color.GetGreen(), 0);

    result = Color::ParseColorString("", color, defaultColor);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ColorTest007
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ColorTest, ColorTest007, TestSize.Level1)
{
    auto lineColor = Color::LineColorTransition(Color::FromRGB(0, 0, 0), Color::FromRGB(255, 255, 255), 1);
    EXPECT_EQ(lineColor.GetAlpha(), 255);
    EXPECT_EQ(lineColor.GetRed(), 255);
    EXPECT_EQ(lineColor.GetBlue(), 255);
    EXPECT_EQ(lineColor.GetGreen(), 255);

    lineColor = Color::LineColorTransition(Color::FromRGB(0, 0, 0), Color::FromRGB(255, 255, 255), 0.5);
    EXPECT_EQ(lineColor.GetAlpha(), 255);
    EXPECT_EQ(lineColor.GetRed(), 127);
    EXPECT_EQ(lineColor.GetBlue(), 127);
    EXPECT_EQ(lineColor.GetGreen(), 127);
}
} // namespace OHOS::Ace
