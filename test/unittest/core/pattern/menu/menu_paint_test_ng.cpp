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

#include <type_traits>
#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension ARROW_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_P1_OFFSET_Y = 8.0_vp;
}

class MenuPaintTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void MenuPaintTestNg::SetUpTestCase() {}

void MenuPaintTestNg::TearDownTestCase() {}

void MenuPaintTestNg::SetUp() {}

void MenuPaintTestNg::TearDown() {}

/**
 * @tc.name: MenuPaintClipMenuTestNg000
 * @tc.desc: Verify MoveTo.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg000, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    double x = 50.0f;
    double y = 60.0f;
    std::string pathStr = layoutAlgorithm->MoveTo(x, y);
    EXPECT_EQ(pathStr.substr(0, 1), "M");
}

/**
 * @tc.name: MenuPaintClipMenuTestNg001
 * @tc.desc: Verify LineTo.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg001, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    double x = 50.0f;
    double y = 60.0f;
    std::string pathStr = layoutAlgorithm->LineTo(x, y);
    EXPECT_EQ(pathStr.substr(0, 1), "L");
}

/**
 * @tc.name: MenuPaintClipMenuTestNg002
 * @tc.desc: Verify LineTo.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg002, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    double rx = 50.0f;
    double ry = 50.0f;
    double rotation = 0.0f;
    int32_t arc_flag = 0;
    double x = 50.0f;
    double y = 60.0f;
    std::string pathStr = layoutAlgorithm->ArcTo(rx, ry, rotation, arc_flag, x, y);
    EXPECT_EQ(pathStr.substr(0, 1), "A");
}

/**
 * @tc.name: MenuPaintClipMenuTestNg003
 * @tc.desc: Verify BuildBottomArrowPath.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg003, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    float arrowX = ARROW_P1_OFFSET_X.ConvertToPx();
    float arrowY = -ARROW_P1_OFFSET_Y.ConvertToPx();
    std::string pathStr;
    layoutAlgorithm->BuildBottomArrowPath(arrowX, arrowY, pathStr);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg004
 * @tc.desc: Verify BuildTopArrowPath.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg004, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    float arrowX = -ARROW_P1_OFFSET_X.ConvertToPx();
    float arrowY = ARROW_P1_OFFSET_Y.ConvertToPx();
    std::string pathStr;
    layoutAlgorithm->BuildTopArrowPath(arrowX, arrowY, pathStr);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg005
 * @tc.desc: Verify BuildRightArrowPath.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg005, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    float arrowX = -ARROW_P1_OFFSET_Y.ConvertToPx();
    float arrowY = ARROW_P1_OFFSET_X.ConvertToPx();
    std::string pathStr;
    layoutAlgorithm->BuildRightArrowPath(arrowX, arrowY, pathStr);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg006
 * @tc.desc: Verify BuildLeftArrowPath.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg006, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    float arrowX = ARROW_P1_OFFSET_Y.ConvertToPx();
    float arrowY = -ARROW_P1_OFFSET_X.ConvertToPx();
    std::string pathStr;
    layoutAlgorithm->BuildLeftArrowPath(arrowX, arrowY, pathStr);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg007
 * @tc.desc: Verify BuildTopLinePath when menu without arrow and placement is bottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg007, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = false;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_X.ConvertToPx(), -ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::BOTTOM;
    std::string pathStr = layoutAlgorithm->BuildTopLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg008
 * @tc.desc: Verify BuildTopLinePath when menu with arrow and placement is bottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg008, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_X.ConvertToPx(), -ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::BOTTOM;
    std::string pathStr = layoutAlgorithm->BuildTopLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg009
 * @tc.desc: Verify BuildTopLinePath when menu with arrow and placement is bottom_left.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg009, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_X.ConvertToPx(), -ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::BOTTOM_LEFT;
    std::string pathStr = layoutAlgorithm->BuildTopLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg010
 * @tc.desc: Verify BuildTopLinePath when menu with arrow and placement is bottom_right.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg010, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_X.ConvertToPx(), -ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::BOTTOM_RIGHT;
    std::string pathStr = layoutAlgorithm->BuildTopLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg011
 * @tc.desc: Verify BuildTopLinePath when menu with arrow and placement is top.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg011, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_X.ConvertToPx(), -ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::TOP;
    std::string pathStr = layoutAlgorithm->BuildTopLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg0012
 * @tc.desc: Verify BuildRightLinePath when menu without arrow and placement is left.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg0012, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = false;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_Y.ConvertToPx(), -ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::LEFT;
    std::string pathStr = layoutAlgorithm->BuildRightLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg013
 * @tc.desc: Verify BuildRightLinePath when menu with arrow and placement is left.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg013, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_Y.ConvertToPx(), -ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::LEFT;
    std::string pathStr = layoutAlgorithm->BuildRightLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg014
 * @tc.desc: Verify BuildRightLinePath when menu with arrow and placement is left_top.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg014, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_Y.ConvertToPx(), -ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::LEFT_TOP;
    std::string pathStr = layoutAlgorithm->BuildRightLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg015
 * @tc.desc: Verify BuildRightLinePath when menu with arrow and placement is left_bottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg015, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_Y.ConvertToPx(), -ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::LEFT_BOTTOM;
    std::string pathStr = layoutAlgorithm->BuildRightLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg016
 * @tc.desc: Verify BuildRightLinePath when menu with arrow and placement is right.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg016, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(ARROW_P1_OFFSET_Y.ConvertToPx(), -ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::RIGHT;
    std::string pathStr = layoutAlgorithm->BuildRightLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg017
 * @tc.desc: Verify BuildBottomLinePath when menu without arrow and placement is top.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg017, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = false;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_X.ConvertToPx(), ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::TOP;
    std::string pathStr = layoutAlgorithm->BuildBottomLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg018
 * @tc.desc: Verify BuildBottomLinePath when menu with arrow and placement is top.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg018, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_X.ConvertToPx(), ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::TOP;
    std::string pathStr = layoutAlgorithm->BuildBottomLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg019
 * @tc.desc: Verify BuildBottomLinePath when menu with arrow and placement is top_left.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg019, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_X.ConvertToPx(), ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::TOP_LEFT;
    std::string pathStr = layoutAlgorithm->BuildBottomLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg020
 * @tc.desc: Verify BuildBottomLinePath when menu with arrow and placement is top_right.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg020, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_X.ConvertToPx(), ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::TOP_RIGHT;
    std::string pathStr = layoutAlgorithm->BuildBottomLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg021
 * @tc.desc: Verify BuildBottomLinePath when menu with arrow and placement is bottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg021, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_X.ConvertToPx(), ARROW_P1_OFFSET_Y.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::BOTTOM;
    std::string pathStr = layoutAlgorithm->BuildBottomLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg022
 * @tc.desc: Verify BuildLeftLinePath when menu without arrow and placement is right.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg022, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = false;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_Y.ConvertToPx(), ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::RIGHT;
    std::string pathStr = layoutAlgorithm->BuildLeftLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg023
 * @tc.desc: Verify BuildLeftLinePath when menu with arrow and placement is right.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg023, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_Y.ConvertToPx(), ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::RIGHT;
    std::string pathStr = layoutAlgorithm->BuildLeftLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg024
 * @tc.desc: Verify BuildLeftLinePath when menu with arrow and placement is right_top.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg024, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_Y.ConvertToPx(), ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::RIGHT_TOP;
    std::string pathStr = layoutAlgorithm->BuildLeftLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg025
 * @tc.desc: Verify BuildLeftLinePath when menu with arrow and placement is right_bottom.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg025, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_Y.ConvertToPx(), ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::RIGHT_BOTTOM;
    std::string pathStr = layoutAlgorithm->BuildLeftLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L";
    EXPECT_EQ(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg026
 * @tc.desc: Verify BuildLeftLinePath when menu with arrow and placement is left.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg026, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();

    bool didNeedArrow = true;
    OffsetF arrowPosition = OffsetF(-ARROW_P1_OFFSET_Y.ConvertToPx(), ARROW_P1_OFFSET_X.ConvertToPx());
    float radiusPx = 50.0f;
    Placement placement = Placement::LEFT;
    std::string pathStr = layoutAlgorithm->BuildLeftLinePath(arrowPosition, radiusPx, placement, didNeedArrow);
    std::string expectedStr = "L0.000000 0.000000";
    EXPECT_NE(pathStr.substr(0, expectedStr.length()), expectedStr);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg027
 * @tc.desc: Verify CalculateMenuPath.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg027, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    std::string pathStr = layoutAlgorithm->CalculateMenuPath(nullptr, true);
    EXPECT_EQ(pathStr.length(), 0);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg029
 * @tc.desc: Verify CalculateChildOffset.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg029, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->CalculateChildOffset(false);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetX(), 0.0f);

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetX(), ARROW_HIGHT.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT_BOTTOM;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetX(), ARROW_HIGHT.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT_TOP;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetX(), ARROW_HIGHT.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetY(), ARROW_HIGHT.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM_LEFT;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetY(), ARROW_HIGHT.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM_RIGHT;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetY(), ARROW_HIGHT.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    layoutAlgorithm->CalculateChildOffset(true);
    EXPECT_EQ(layoutAlgorithm->childOffset_.GetX(), 0.0f);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg030
 * @tc.desc: Verify CalculateMenuPositionWithArrow.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg030, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    OffsetF menuPosition = OffsetF(0, 0);
    OffsetF menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, false);
    EXPECT_EQ(menuPositionWithArrow.GetX(), 0.0f);

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetX(), -ARROW_P1_OFFSET_X.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT_BOTTOM;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetX(), -ARROW_P1_OFFSET_X.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT_TOP;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetX(), -ARROW_P1_OFFSET_X.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetY(), -ARROW_P1_OFFSET_Y.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM_LEFT;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetY(), -ARROW_P1_OFFSET_Y.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM_RIGHT;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetY(), -ARROW_P1_OFFSET_Y.ConvertToPx());

    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    menuPositionWithArrow = layoutAlgorithm->CalculateMenuPositionWithArrow(menuPosition, true);
    EXPECT_EQ(menuPositionWithArrow.GetY(), 0.0f);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg031
 * @tc.desc: Verify UpdateMenuFrameSizeWithArrow part 1.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg031, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::NONE;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, false);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), 0.0f);

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::NONE;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), 0.0f);

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::LEFT;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::LEFT_TOP;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::LEFT_BOTTOM;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT_BOTTOM;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::RIGHT_TOP;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Width(), ARROW_HIGHT.ConvertToPx());
}

/**
 * @tc.name: MenuPaintClipMenuTestNg032
 * @tc.desc: Verify UpdateMenuFrameSizeWithArrow part 2.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg032, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::TOP;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::TOP_LEFT;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::TOP_RIGHT;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM_LEFT;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), ARROW_HIGHT.ConvertToPx());

    geometryNode->SetFrameSize(SizeF(0, 0));
    layoutAlgorithm->arrowPlacement_ = Placement::BOTTOM_RIGHT;
    layoutAlgorithm->UpdateMenuFrameSizeWithArrow(geometryNode, true);
    EXPECT_EQ(geometryNode->GetFrameSize().Height(), ARROW_HIGHT.ConvertToPx());
}

/**
 * @tc.name: MenuPaintClipMenuTestNg033
 * @tc.desc: Verify NormalizeBorderRadius with invalid width.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg033, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->childMarginFrameSize_ = SizeF(0, 100);
    float radiusTopLeftPx = 100.0f;
    float radiusTopRightPx = 100.0f;
    float radiusBottomLeftPx = 100.0f;
    float radiusBottomRightPx = 100.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 0.0f);
    EXPECT_EQ(radiusTopRightPx, 0.0f);
    EXPECT_EQ(radiusBottomLeftPx, 0.0f);
    EXPECT_EQ(radiusBottomRightPx, 0.0f);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg034
 * @tc.desc: Verify NormalizeBorderRadius with invalid height.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg034, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->childMarginFrameSize_ = SizeF(100, 0);
    float radiusTopLeftPx = 100.0f;
    float radiusTopRightPx = 100.0f;
    float radiusBottomLeftPx = 100.0f;
    float radiusBottomRightPx = 100.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 0.0f);
    EXPECT_EQ(radiusTopRightPx, 0.0f);
    EXPECT_EQ(radiusBottomLeftPx, 0.0f);
    EXPECT_EQ(radiusBottomRightPx, 0.0f);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg035
 * @tc.desc: Verify NormalizeBorderRadius.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg035, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->childMarginFrameSize_ = SizeF(100, 100);
    float radiusTopLeftPx = 20.0f;
    float radiusTopRightPx = 20.0f;
    float radiusBottomLeftPx = 20.0f;
    float radiusBottomRightPx = 20.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 20.0f);
    EXPECT_EQ(radiusTopRightPx, 20.0f);
    EXPECT_EQ(radiusBottomLeftPx, 20.0f);
    EXPECT_EQ(radiusBottomRightPx, 20.0f);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg036
 * @tc.desc: Verify NormalizeBorderRadius with invalid radius.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg036, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->childMarginFrameSize_ = SizeF(100, 120);
    float radiusTopLeftPx = 180.0f;
    float radiusTopRightPx = 20.0f;
    float radiusBottomLeftPx = 20.0f;
    float radiusBottomRightPx = 20.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 90.0f);
    EXPECT_EQ(radiusTopRightPx, 10.0f);
    EXPECT_EQ(radiusBottomLeftPx, 10.0f);
    EXPECT_EQ(radiusBottomRightPx, 10.0f);

    radiusTopLeftPx = 20.0f;
    radiusTopRightPx = 180.0f;
    radiusBottomLeftPx = 20.0f;
    radiusBottomRightPx = 20.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 10.0f);
    EXPECT_EQ(radiusTopRightPx, 90.0f);
    EXPECT_EQ(radiusBottomLeftPx, 10.0f);
    EXPECT_EQ(radiusBottomRightPx, 10.0f);

    radiusTopLeftPx = 20.0f;
    radiusTopRightPx = 20.0f;
    radiusBottomLeftPx = 180.0f;
    radiusBottomRightPx = 20.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 10.0f);
    EXPECT_EQ(radiusTopRightPx, 10.0f);
    EXPECT_EQ(radiusBottomLeftPx, 90.0f);
    EXPECT_EQ(radiusBottomRightPx, 10.0f);

    radiusTopLeftPx = 20.0f;
    radiusTopRightPx = 20.0f;
    radiusBottomLeftPx = 20.0f;
    radiusBottomRightPx = 180.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 10.0f);
    EXPECT_EQ(radiusTopRightPx, 10.0f);
    EXPECT_EQ(radiusBottomLeftPx, 10.0f);
    EXPECT_EQ(radiusBottomRightPx, 90.0f);
}

/**
 * @tc.name: MenuPaintClipMenuTestNg037
 * @tc.desc: Verify NormalizeBorderRadius with invalid radius.
 * @tc.type: FUNC
 */
HWTEST_F(MenuPaintTestNg, MenuPaintClipMenuTestNg037, TestSize.Level1)
{
    RefPtr<MenuLayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<MenuLayoutAlgorithm>();
    layoutAlgorithm->childMarginFrameSize_ = SizeF(100, 80);
    float radiusTopLeftPx = 180.0f;
    float radiusTopRightPx = 20.0f;
    float radiusBottomLeftPx = 220.0f;
    float radiusBottomRightPx = 20.0f;
    layoutAlgorithm->NormalizeBorderRadius(radiusTopLeftPx, radiusTopRightPx, radiusBottomLeftPx, radiusBottomRightPx);
    EXPECT_EQ(radiusTopLeftPx, 36.0f);
    EXPECT_EQ(radiusTopRightPx, 4.0f);
    EXPECT_EQ(radiusBottomLeftPx, 44.0f);
    EXPECT_EQ(radiusBottomRightPx, 4.0f);
}
}