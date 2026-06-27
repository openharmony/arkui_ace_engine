/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#define private public
#define protected public
#include "core/components_ng/pattern/smart_layout/engine/smart_layout_types.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SmartLayoutTypesTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutSizeTest001
 * @tc.desc: Test SmartLayoutSize default constructor
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutSizeTest001, TestSize.Level1)
{
    SmartLayoutSize size;
    EXPECT_EQ(size.width, 0.0);
    EXPECT_EQ(size.height, 0.0);
    EXPECT_EQ(size.Width(), 0.0);
    EXPECT_EQ(size.Height(), 0.0);
}

/**
 * @tc.name: SmartLayoutSizeTest002
 * @tc.desc: Test SmartLayoutSize constructor with parameters
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutSizeTest002, TestSize.Level1)
{
    SmartLayoutSize size(100.0, 200.0);
    EXPECT_EQ(size.width, 100.0);
    EXPECT_EQ(size.height, 200.0);
    EXPECT_EQ(size.Width(), 100.0);
    EXPECT_EQ(size.Height(), 200.0);
}

/**
 * @tc.name: SmartLayoutSizeTest003
 * @tc.desc: Test SmartLayoutSize setter methods
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutSizeTest003, TestSize.Level1)
{
    SmartLayoutSize size;
    size.SetWidth(50.0);
    size.SetHeight(75.0);
    EXPECT_EQ(size.Width(), 50.0);
    EXPECT_EQ(size.Height(), 75.0);
}

/**
 * @tc.name: ChildLayoutInfoTest001
 * @tc.desc: Test ChildLayoutInfo default values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, ChildLayoutInfoTest001, TestSize.Level1)
{
    ChildLayoutInfo info;
    EXPECT_EQ(info.id, 0);
    EXPECT_EQ(info.width, 0.0);
    EXPECT_EQ(info.height, 0.0);
    EXPECT_EQ(info.offsetX, 0.0);
    EXPECT_EQ(info.offsetY, 0.0);
    EXPECT_FALSE(info.isBlank);
}

/**
 * @tc.name: ChildLayoutInfoTest002
 * @tc.desc: Test ChildLayoutInfo initialization with values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, ChildLayoutInfoTest002, TestSize.Level1)
{
    ChildLayoutInfo info;
    info.id = 12345;
    info.width = 100.0;
    info.height = 50.0;
    info.offsetX = 10.0;
    info.offsetY = 20.0;
    info.isBlank = true;

    EXPECT_EQ(info.id, 12345);
    EXPECT_EQ(info.width, 100.0);
    EXPECT_EQ(info.height, 50.0);
    EXPECT_EQ(info.offsetX, 10.0);
    EXPECT_EQ(info.offsetY, 20.0);
    EXPECT_TRUE(info.isBlank);
}

/**
 * @tc.name: SmartLayoutRectTest001
 * @tc.desc: Test SmartLayoutRect default constructor
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutRectTest001, TestSize.Level1)
{
    SmartLayoutRect rect;
    EXPECT_EQ(rect.offsetX, 0.0);
    EXPECT_EQ(rect.offsetY, 0.0);
    EXPECT_EQ(rect.width, 0.0);
    EXPECT_EQ(rect.height, 0.0);
    EXPECT_EQ(rect.Left(), 0.0);
    EXPECT_EQ(rect.Top(), 0.0);
    EXPECT_EQ(rect.Right(), 0.0);
    EXPECT_EQ(rect.Bottom(), 0.0);
    EXPECT_FALSE(rect.IsValid());
}

/**
 * @tc.name: SmartLayoutRectTest002
 * @tc.desc: Test SmartLayoutRect constructor with parameters
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutRectTest002, TestSize.Level1)
{
    SmartLayoutRect rect(10.0, 20.0, 100.0, 50.0);
    EXPECT_EQ(rect.offsetX, 10.0);
    EXPECT_EQ(rect.offsetY, 20.0);
    EXPECT_EQ(rect.width, 100.0);
    EXPECT_EQ(rect.height, 50.0);
    EXPECT_EQ(rect.Left(), 10.0);
    EXPECT_EQ(rect.Top(), 20.0);
    EXPECT_EQ(rect.Right(), 110.0);
    EXPECT_EQ(rect.Bottom(), 70.0);
    EXPECT_TRUE(rect.IsValid());
}

/**
 * @tc.name: SmartLayoutRectTest003
 * @tc.desc: Test SmartLayoutRect IsValid with edge cases
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutRectTest003, TestSize.Level1)
{
    SmartLayoutRect rect1(0.0, 0.0, -10.0, 50.0);
    EXPECT_FALSE(rect1.IsValid());

    SmartLayoutRect rect2(0.0, 0.0, 100.0, -5.0);
    EXPECT_FALSE(rect2.IsValid());

    SmartLayoutRect rect3(0.0, 0.0, 0.0, 50.0);
    EXPECT_FALSE(rect3.IsValid());

    SmartLayoutRect rect4(0.0, 0.0, 100.0, 0.0);
    EXPECT_FALSE(rect4.IsValid());

    SmartLayoutRect rect5(0.0, 0.0, 0.001, 0.001);
    EXPECT_TRUE(rect5.IsValid());
}

/**
 * @tc.name: EdgesSpacesTest001
 * @tc.desc: Test EdgesSpaces default values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, EdgesSpacesTest001, TestSize.Level1)
{
    EdgesSpaces spaces;
    EXPECT_EQ(spaces.left, 0.0);
    EXPECT_EQ(spaces.right, 0.0);
    EXPECT_EQ(spaces.top, 0.0);
    EXPECT_EQ(spaces.bottom, 0.0);
}

/**
 * @tc.name: EdgesSpacesTest002
 * @tc.desc: Test EdgesSpaces initialization with values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, EdgesSpacesTest002, TestSize.Level1)
{
    EdgesSpaces spaces;
    spaces.left = 5.0;
    spaces.right = 10.0;
    spaces.top = 15.0;
    spaces.bottom = 20.0;

    EXPECT_EQ(spaces.left, 5.0);
    EXPECT_EQ(spaces.right, 10.0);
    EXPECT_EQ(spaces.top, 15.0);
    EXPECT_EQ(spaces.bottom, 20.0);
}

/**
 * @tc.name: SmartLayoutTypeEnumTest001
 * @tc.desc: Test SmartLayoutType enum values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutTypeEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int>(SmartLayoutType::UNKNOWN), 0);
    EXPECT_EQ(static_cast<int>(SmartLayoutType::GENERAL), 1);
    EXPECT_EQ(static_cast<int>(SmartLayoutType::COLUMN), 2);
    EXPECT_EQ(static_cast<int>(SmartLayoutType::ROW), 3);
    EXPECT_EQ(static_cast<int>(SmartLayoutType::FLEX), 4);
}

/**
 * @tc.name: SmartLayoutAlignEnumTest001
 * @tc.desc: Test SmartLayoutAlign enum values
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutTypesTest, SmartLayoutAlignEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int>(SmartLayoutAlign::FLEX_START), 0);
    EXPECT_EQ(static_cast<int>(SmartLayoutAlign::CENTER), 1);
    EXPECT_EQ(static_cast<int>(SmartLayoutAlign::FLEX_END), 2);
}

} // namespace OHOS::Ace::NG