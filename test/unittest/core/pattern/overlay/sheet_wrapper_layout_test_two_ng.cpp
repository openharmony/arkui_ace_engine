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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class SheetWrapperLayoutTestTwoNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static void SetApiVersion(int32_t apiTargetVersion);
};

void SheetWrapperLayoutTestTwoNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return AceType::MakeRefPtr<SheetTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetWrapperLayoutTestTwoNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SheetWrapperLayoutTestTwoNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: GetOffsetWithLeft001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeft001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeft(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeft002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeft002, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeft(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeft003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeft003, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeft(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeftTop001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeftTop001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeftTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeftTop002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeftTop002, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeftTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeftTop003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeftTop003, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeftTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeftBottom001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeftBottom001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeftBottom(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeftBottom002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeftBottom002, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeftBottom(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithLeftBottom003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithLeftBottom003, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomRight = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithLeftBottom(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), 0.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRight001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRight001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRight(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRight002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRight002, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRight(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRight003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRight003, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRight(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRightTop001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRightTop001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRightTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRightTop002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRightTop002, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRightTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRightTop003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRightTop003, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRightTop(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRightBottom001
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRightBottom001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = false;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRightBottom(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRightBottom002
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRightBottom002, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 500.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 500.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRightBottom(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithRightBottom003
 * @tc.desc: Branch: if (!sheetPopupInfo_.showArrow) = false
 *           Branch: if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
 *               sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) = false
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, GetOffsetWithRightBottom003, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement = Placement::BOTTOM_LEFT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 800.0f;
    sheetWrapperLayoutAlgorithm->sheetHeight_ = 600.0f;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft = 0.0_vp;
    sheetWrapperLayoutAlgorithm->sheetRadius_.radiusBottomLeft = 0.0_vp;

    SizeF targetSize = SizeF(700.0f, 500.0f);
    OffsetF targetOffset = OffsetF();
    auto offset = sheetWrapperLayoutAlgorithm->GetOffsetWithRightBottom(targetSize, targetOffset);
    EXPECT_EQ(offset.GetX(), -800.0f);
    EXPECT_EQ(offset.GetY(), 6.0f);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.arrowPosition, SheetArrowPosition::BOTTOM_LEFT);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: RestrictOffsetInSpaceBottom001
 * @tc.desc: Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = false
 *           Condition: sheetPopupInfo_.placementRechecked = false
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = false
 *           Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = true
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, RestrictOffsetInSpaceBottom001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;

    float offsetX;
    float offsetY;
    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceBottom(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceBottom(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceBottom(offsetX, offsetY);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: RestrictOffsetInSpaceTop001
 * @tc.desc: Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = false
 *           Condition: sheetPopupInfo_.placementRechecked = false
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = false
 *           Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = true
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, RestrictOffsetInSpaceTop001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;

    float offsetX;
    float offsetY;
    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceTop(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceTop(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceTop(offsetX, offsetY);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: RestrictOffsetInSpaceLeft001
 * @tc.desc: Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = false
 *           Condition: sheetPopupInfo_.placementRechecked = false
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = false
 *           Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = true
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, RestrictOffsetInSpaceLeft001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;

    float offsetX;
    float offsetY;
    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceLeft(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceLeft(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceLeft(offsetX, offsetY);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}

/**
 * @tc.name: RestrictOffsetInSpaceRight001
 * @tc.desc: Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = false
 *           Condition: sheetPopupInfo_.placementRechecked = false
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = false
 *           Branch: if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) = true
 *           Condition: sheetPopupInfo_.placementRechecked = true, sheetPopupInfo_.placementOnTarget = true
 * @tc.type: FUNC
 */
HWTEST_F(SheetWrapperLayoutTestTwoNg, RestrictOffsetInSpaceRight001, TestSize.Level1)
{
    SheetWrapperLayoutTestTwoNg::SetUpTestCase();
    auto sheetWrapperLayoutAlgorithm = AceType::MakeRefPtr<SheetWrapperLayoutAlgorithm>();
    sheetWrapperLayoutAlgorithm->sheetRadius_ = { 0.0_vp, 0.0_vp, 0.0_vp, 0.0_vp };
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = false;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow = true;

    float offsetX;
    float offsetY;
    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceRight(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = false;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceRight(offsetX, offsetY);
    EXPECT_TRUE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);

    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementRechecked = true;
    sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget = true;

    sheetWrapperLayoutAlgorithm->RestrictOffsetInSpaceRight(offsetX, offsetY);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow);
    SheetWrapperLayoutTestTwoNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG