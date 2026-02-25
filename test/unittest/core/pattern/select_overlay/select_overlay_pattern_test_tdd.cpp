/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "gtest/internal/gtest-internal.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/pipeline/base/constants.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEFAULT_MENU_WIDTH = 100.0f;
constexpr float DEFAULT_MENU_HEIGHT = 50.0f;
const RectF TEST_HANDLE_RECT(10.0f, 20.0f, 20.0f, 40.0f);
const RectF TEST_SECOND_HANDLE_RECT(50.0f, 70.0f, 20.0f, 40.0f);
const OffsetF TEST_OFFSET(100.0f, 200.0f);
const std::string TEST_SELECT_TEXT = "Test selected text";
} // namespace

class SelectOverlayPatternTddTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<SelectOverlayPattern> CreatePattern(SelectOverlayMode mode = SelectOverlayMode::ALL);
    SelectOverlayInfo CreateDefaultInfo();
};

void SelectOverlayPatternTddTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    auto rootNode = MockPipelineContext::GetCurrent()->rootNode_;
    if (rootNode) {
        auto rootRenderContext = rootNode->GetRenderContext();
        if (rootRenderContext) {
            rootRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 1280.0f, 2480.0f));
        }
    }
}

void SelectOverlayPatternTddTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<SelectOverlayPattern> SelectOverlayPatternTddTest::CreatePattern(SelectOverlayMode mode)
{
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    return AceType::MakeRefPtr<SelectOverlayPattern>(info, mode);
}

SelectOverlayInfo SelectOverlayPatternTddTest::CreateDefaultInfo()
{
    SelectOverlayInfo info;
    info.firstHandle.paintRect = TEST_HANDLE_RECT;
    info.firstHandle.isShow = true;
    info.firstHandle.isTouchable = true;
    info.secondHandle.paintRect = TEST_SECOND_HANDLE_RECT;
    info.secondHandle.isShow = true;
    info.secondHandle.isTouchable = true;
    info.isSingleHandle = false;
    info.menuInfo.menuIsShow = true;
    info.selectText = TEST_SELECT_TEXT;
    return info;
}

/**
 * @tc.name: SelectOverlayPattern_CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm returns valid algorithm
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::ALL);
    auto algorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(algorithm, nullptr);
    auto selectOverlayAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(algorithm);
    EXPECT_NE(selectOverlayAlgorithm, nullptr);
}

/**
 * @tc.name: SelectOverlayPattern_CreateLayoutAlgorithm002
 * @tc.desc: Test CreateLayoutAlgorithm with menu width and height
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CreateLayoutAlgorithm002, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::ALL);
    pattern->menuWidth_ = DEFAULT_MENU_WIDTH;
    pattern->menuHeight_ = DEFAULT_MENU_HEIGHT;
    auto algorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(algorithm, nullptr);
    auto selectOverlayAlgorithm = AceType::DynamicCast<SelectOverlayLayoutAlgorithm>(algorithm);
    ASSERT_NE(selectOverlayAlgorithm, nullptr);
    EXPECT_EQ(selectOverlayAlgorithm->GetMenuWidth().value_or(0.0f), DEFAULT_MENU_WIDTH);
    EXPECT_EQ(selectOverlayAlgorithm->GetMenuHeight().value_or(0.0f), DEFAULT_MENU_HEIGHT);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateFirstSelectHandleInfo001
 * @tc.desc: Test UpdateFirstSelectHandleInfo with same info
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateFirstSelectHandleInfo001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    auto originalInfo = pattern->info_->firstHandle;
    pattern->UpdateFirstSelectHandleInfo(originalInfo);
    // Should not trigger layout update when info is the same
    EXPECT_EQ(pattern->info_->firstHandle.paintRect, originalInfo.paintRect);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateFirstSelectHandleInfo002
 * @tc.desc: Test UpdateFirstSelectHandleInfo with different info and needLayout
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateFirstSelectHandleInfo002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    SelectHandleInfo newInfo;
    newInfo.paintRect = RectF(30.0f, 40.0f, 25.0f, 50.0f);
    newInfo.needLayout = true;
    pattern->UpdateFirstSelectHandleInfo(newInfo);
    EXPECT_EQ(pattern->info_->firstHandle.paintRect, newInfo.paintRect);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateSecondSelectHandleInfo001
 * @tc.desc: Test UpdateSecondSelectHandleInfo with same info
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateSecondSelectHandleInfo001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    auto originalInfo = pattern->info_->secondHandle;
    pattern->UpdateSecondSelectHandleInfo(originalInfo);
    EXPECT_EQ(pattern->info_->secondHandle.paintRect, originalInfo.paintRect);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateSecondSelectHandleInfo002
 * @tc.desc: Test UpdateSecondSelectHandleInfo with different info
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateSecondSelectHandleInfo002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    SelectHandleInfo newInfo;
    newInfo.paintRect = RectF(60.0f, 80.0f, 25.0f, 50.0f);
    newInfo.needLayout = false;
    pattern->UpdateSecondSelectHandleInfo(newInfo);
    EXPECT_EQ(pattern->info_->secondHandle.paintRect, newInfo.paintRect);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateFirstAndSecondHandleInfo001
 * @tc.desc: Test UpdateFirstAndSecondHandleInfo with same info
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateFirstAndSecondHandleInfo001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    auto originalFirst = pattern->info_->firstHandle;
    auto originalSecond = pattern->info_->secondHandle;
    pattern->UpdateFirstAndSecondHandleInfo(originalFirst, originalSecond);
    EXPECT_EQ(pattern->info_->firstHandle.paintRect, originalFirst.paintRect);
    EXPECT_EQ(pattern->info_->secondHandle.paintRect, originalSecond.paintRect);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateFirstAndSecondHandleInfo002
 * @tc.desc: Test UpdateFirstAndSecondHandleInfo with different info while dragging
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateFirstAndSecondHandleInfo002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->firstHandleDrag_ = true;
    SelectHandleInfo newFirst;
    newFirst.paintRect = RectF(35.0f, 45.0f, 25.0f, 50.0f);
    SelectHandleInfo newSecond;
    newSecond.paintRect = RectF(65.0f, 85.0f, 25.0f, 50.0f);
    pattern->UpdateFirstAndSecondHandleInfo(newFirst, newSecond);
    // Should not update while dragging
    EXPECT_NE(pattern->info_->firstHandle.paintRect, newFirst.paintRect);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateShowArea001
 * @tc.desc: Test UpdateShowArea with same area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateShowArea001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    RectF originalArea(0, 0, 100, 100);
    pattern->info_->showArea = originalArea;
    pattern->UpdateShowArea(originalArea);
    EXPECT_EQ(pattern->info_->showArea, originalArea);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateShowArea002
 * @tc.desc: Test UpdateShowArea with different area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateShowArea002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    RectF newArea(10, 20, 200, 300);
    pattern->UpdateShowArea(newArea);
    EXPECT_EQ(pattern->info_->showArea, newArea);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateAncestorViewPort001
 * @tc.desc: Test UpdateAncestorViewPort with valid viewport
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateAncestorViewPort001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    RectF viewPort(5, 10, 150, 250);
    pattern->UpdateAncestorViewPort(viewPort);
    EXPECT_TRUE(pattern->info_->ancestorViewPort.has_value());
    EXPECT_EQ(pattern->info_->ancestorViewPort.value(), viewPort);
}

/**
 * @tc.name: SelectOverlayPattern_UpdateAncestorViewPort002
 * @tc.desc: Test UpdateAncestorViewPort with nullopt
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateAncestorViewPort002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->ancestorViewPort = RectF(0, 0, 100, 100);
    pattern->UpdateAncestorViewPort(std::nullopt);
    EXPECT_FALSE(pattern->info_->ancestorViewPort.has_value());
}

/**
 * @tc.name: SelectOverlayPattern_SetSelectRegionVisible001
 * @tc.desc: Test SetSelectRegionVisible to true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetSelectRegionVisible001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->isSelectRegionVisible = false;
    pattern->SetSelectRegionVisible(true);
    EXPECT_TRUE(pattern->info_->isSelectRegionVisible);
}

/**
 * @tc.name: SelectOverlayPattern_SetSelectRegionVisible002
 * @tc.desc: Test SetSelectRegionVisible to false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetSelectRegionVisible002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->isSelectRegionVisible = true;
    pattern->SetSelectRegionVisible(false);
    EXPECT_FALSE(pattern->info_->isSelectRegionVisible);
}

/**
 * @tc.name: SelectOverlayPattern_SetHandleReverse001
 * @tc.desc: Test SetHandleReverse to true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetHandleReverse001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->handleReverse = false;
    pattern->SetHandleReverse(true);
    EXPECT_TRUE(pattern->info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPattern_SetSelectInfo001
 * @tc.desc: Test SetSelectInfo with valid text
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetSelectInfo001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    const std::string newText = "New selected text";
    pattern->SetSelectInfo(newText);
    EXPECT_EQ(pattern->GetSelectInfo(), newText);
}

/**
 * @tc.name: SelectOverlayPattern_GetSelectInfo001
 * @tc.desc: Test GetSelectInfo returns correct text
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetSelectInfo001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    EXPECT_EQ(pattern->GetSelectInfo(), TEST_SELECT_TEXT);
}

/**
 * @tc.name: SelectOverlayPattern_GetMenuWidth001
 * @tc.desc: Test GetMenuWidth with valid width
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetMenuWidth001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->menuWidth_ = DEFAULT_MENU_WIDTH;
    auto width = pattern->GetMenuWidth();
    EXPECT_TRUE(width.has_value());
    EXPECT_EQ(width.value(), DEFAULT_MENU_WIDTH);
}

/**
 * @tc.name: SelectOverlayPattern_GetMenuWidth002
 * @tc.desc: Test GetMenuWidth with no width set
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetMenuWidth002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->menuWidth_ = std::nullopt;
    auto width = pattern->GetMenuWidth();
    EXPECT_FALSE(width.has_value());
}

/**
 * @tc.name: SelectOverlayPattern_GetMenuHeight001
 * @tc.desc: Test GetMenuHeight with valid height
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetMenuHeight001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->menuHeight_ = DEFAULT_MENU_HEIGHT;
    auto height = pattern->GetMenuHeight();
    EXPECT_TRUE(height.has_value());
    EXPECT_EQ(height.value(), DEFAULT_MENU_HEIGHT);
}

/**
 * @tc.name: SelectOverlayPattern_GetMenuHeight002
 * @tc.desc: Test GetMenuHeight with no height set
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetMenuHeight002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->menuHeight_ = std::nullopt;
    auto height = pattern->GetMenuHeight();
    EXPECT_FALSE(height.has_value());
}

/**
 * @tc.name: SelectOverlayPattern_GetHandleRegion001
 * @tc.desc: Test GetHandleRegion for first handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetHandleRegion001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->firstHandleRegion_ = TEST_HANDLE_RECT;
    auto region = pattern->GetHandleRegion(true);
    EXPECT_EQ(region, TEST_HANDLE_RECT);
}

/**
 * @tc.name: SelectOverlayPattern_GetHandleRegion002
 * @tc.desc: Test GetHandleRegion for second handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetHandleRegion002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->secondHandleRegion_ = TEST_SECOND_HANDLE_RECT;
    auto region = pattern->GetHandleRegion(false);
    EXPECT_EQ(region, TEST_SECOND_HANDLE_RECT);
}

/**
 * @tc.name: SelectOverlayPattern_IsMenuShow001
 * @tc.desc: Test IsMenuShow when menu is showing
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsMenuShow001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->menuInfo.menuIsShow = true;
    EXPECT_TRUE(pattern->IsMenuShow());
}

/**
 * @tc.name: SelectOverlayPattern_IsMenuShow002
 * @tc.desc: Test IsMenuShow when menu is not showing
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsMenuShow002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->menuInfo.menuIsShow = false;
    EXPECT_FALSE(pattern->IsMenuShow());
}

/**
 * @tc.name: SelectOverlayPattern_IsSingleHandleMenuShow001
 * @tc.desc: Test IsSingleHandleMenuShow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsSingleHandleMenuShow001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->menuInfo.singleHandleMenuIsShow = true;
    EXPECT_TRUE(pattern->IsSingleHandleMenuShow());
}

/**
 * @tc.name: SelectOverlayPattern_IsHandleShow001
 * @tc.desc: Test IsHandleShow when first handle is visible
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsHandleShow001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->firstHandle.isShow = true;
    pattern->info_->secondHandle.isShow = false;
    EXPECT_TRUE(pattern->IsHandleShow());
}

/**
 * @tc.name: SelectOverlayPattern_IsHandleShow002
 * @tc.desc: Test IsHandleShow when second handle is visible
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsHandleShow002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->firstHandle.isShow = false;
    pattern->info_->secondHandle.isShow = true;
    EXPECT_TRUE(pattern->IsHandleShow());
}

/**
 * @tc.name: SelectOverlayPattern_IsHandleShow003
 * @tc.desc: Test IsHandleShow when neither handle is visible
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsHandleShow003, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->firstHandle.isShow = false;
    pattern->info_->secondHandle.isShow = false;
    EXPECT_FALSE(pattern->IsHandleShow());
}

/**
 * @tc.name: SelectOverlayPattern_IsSingleHandle001
 * @tc.desc: Test IsSingleHandle when is single handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsSingleHandle001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->isSingleHandle = true;
    EXPECT_TRUE(pattern->IsSingleHandle());
}

/**
 * @tc.name: SelectOverlayPattern_IsSingleHandle002
 * @tc.desc: Test IsSingleHandle when is not single handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsSingleHandle002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->isSingleHandle = false;
    EXPECT_FALSE(pattern->IsSingleHandle());
}

/**
 * @tc.name: SelectOverlayPattern_IsCustomMenu001
 * @tc.desc: Test IsCustomMenu when menuBuilder exists
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsCustomMenu001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->menuInfo.menuBuilder = []() -> RefPtr<UINode> { return nullptr; };
    EXPECT_TRUE(pattern->IsCustomMenu());
}

/**
 * @tc.name: SelectOverlayPattern_IsCustomMenu002
 * @tc.desc: Test IsCustomMenu when menuBuilder is null
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsCustomMenu002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->info_->menuInfo.menuBuilder = nullptr;
    EXPECT_FALSE(pattern->IsCustomMenu());
}

/**
 * @tc.name: SelectOverlayPattern_IsHiddenHandle001
 * @tc.desc: Test IsHiddenHandle when handle is hidden
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsHiddenHandle001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->isHiddenHandle_ = true;
    EXPECT_TRUE(pattern->IsHiddenHandle());
}

/**
 * @tc.name: SelectOverlayPattern_IsHiddenHandle002
 * @tc.desc: Test IsHiddenHandle when handle is not hidden
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsHiddenHandle002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->isHiddenHandle_ = false;
    EXPECT_FALSE(pattern->IsHiddenHandle());
}

/**
 * @tc.name: SelectOverlayPattern_IsDraggingHandle001
 * @tc.desc: Test IsDraggingHandle for first handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsDraggingHandle001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->firstHandleDrag_ = true;
    pattern->secondHandleDrag_ = false;
    EXPECT_TRUE(pattern->IsDraggingHandle(true));
    EXPECT_FALSE(pattern->IsDraggingHandle(false));
}

/**
 * @tc.name: SelectOverlayPattern_IsDraggingHandle002
 * @tc.desc: Test IsDraggingHandle for second handle
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsDraggingHandle002, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->firstHandleDrag_ = false;
    pattern->secondHandleDrag_ = true;
    EXPECT_FALSE(pattern->IsDraggingHandle(true));
    EXPECT_TRUE(pattern->IsDraggingHandle(false));
}

/**
 * @tc.name: SelectOverlayPattern_GetMode001
 * @tc.desc: Test GetMode returns correct mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetMode001, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::MENU_ONLY);
    EXPECT_EQ(pattern->GetMode(), SelectOverlayMode::MENU_ONLY);
}

/**
 * @tc.name: SelectOverlayPattern_SetHasShowAnimation001
 * @tc.desc: Test SetHasShowAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetHasShowAnimation001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->SetHasShowAnimation(true);
    EXPECT_TRUE(pattern->hasShowAnimation_);
    pattern->SetHasShowAnimation(false);
    EXPECT_FALSE(pattern->hasShowAnimation_);
}

/**
 * @tc.name: SelectOverlayPattern_CheckIfNeedMenu001
 * @tc.desc: Test CheckIfNeedMenu with ALL mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CheckIfNeedMenu001, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::ALL);
    EXPECT_TRUE(pattern->CheckIfNeedMenu());
}

/**
 * @tc.name: SelectOverlayPattern_CheckIfNeedMenu002
 * @tc.desc: Test CheckIfNeedMenu with MENU_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CheckIfNeedMenu002, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::MENU_ONLY);
    EXPECT_TRUE(pattern->CheckIfNeedMenu());
}

/**
 * @tc.name: SelectOverlayPattern_CheckIfNeedMenu003
 * @tc.desc: Test CheckIfNeedMenu with HANDLE_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CheckIfNeedMenu003, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::HANDLE_ONLY);
    EXPECT_FALSE(pattern->CheckIfNeedMenu());
}

/**
 * @tc.name: SelectOverlayPattern_CheckIfNeedHandle001
 * @tc.desc: Test CheckIfNeedHandle with ALL mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CheckIfNeedHandle001, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::ALL);
    EXPECT_TRUE(pattern->CheckIfNeedHandle());
}

/**
 * @tc.name: SelectOverlayPattern_CheckIfNeedHandle002
 * @tc.desc: Test CheckIfNeedHandle with HANDLE_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CheckIfNeedHandle002, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::HANDLE_ONLY);
    EXPECT_TRUE(pattern->CheckIfNeedHandle());
}

/**
 * @tc.name: SelectOverlayPattern_CheckIfNeedHandle003
 * @tc.desc: Test CheckIfNeedHandle with MENU_ONLY mode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, CheckIfNeedHandle003, TestSize.Level1)
{
    auto pattern = CreatePattern(SelectOverlayMode::MENU_ONLY);
    EXPECT_FALSE(pattern->CheckIfNeedHandle());
}

/**
 * @tc.name: SelectOverlayPattern_UpdateSelectArea001
 * @tc.desc: Test UpdateSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, UpdateSelectArea001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    RectF selectArea(10.0f, 20.0f, 100.0f, 200.0f);
    pattern->UpdateSelectArea(selectArea);
    EXPECT_EQ(pattern->info_->selectArea, selectArea);
}

/**
 * @tc.name: SelectOverlayPattern_SetIsNewAvoid001
 * @tc.desc: Test SetIsNewAvoid
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetIsNewAvoid001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->SetIsNewAvoid(true);
    EXPECT_TRUE(pattern->info_->isNewAvoid);
    pattern->SetIsNewAvoid(false);
    EXPECT_FALSE(pattern->info_->isNewAvoid);
}

/**
 * @tc.name: SelectOverlayPattern_IsMeasureBoundary001
 * @tc.desc: Test IsMeasureBoundary returns true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsMeasureBoundary001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    EXPECT_TRUE(pattern->IsMeasureBoundary());
}

/**
 * @tc.name: SelectOverlayPattern_IsAtomicNode001
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, IsAtomicNode001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    EXPECT_FALSE(pattern->IsAtomicNode());
}

/**
 * @tc.name: SelectOverlayPattern_GetDefaultMenuEndOffset001
 * @tc.desc: Test GetDefaultMenuEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetDefaultMenuEndOffset001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->defaultMenuEndOffset_ = TEST_OFFSET;
    EXPECT_EQ(pattern->GetDefaultMenuEndOffset(), TEST_OFFSET);
}

/**
 * @tc.name: SelectOverlayPattern_SetClosedByGlobalTouchEvent001
 * @tc.desc: Test SetClosedByGlobalTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetClosedByGlobalTouchEvent001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->SetClosedByGlobalTouchEvent(true);
    EXPECT_TRUE(pattern->closedByGlobalTouchEvent_);
    pattern->SetClosedByGlobalTouchEvent(false);
    EXPECT_FALSE(pattern->closedByGlobalTouchEvent_);
}

/**
 * @tc.name: SelectOverlayPattern_GetIsMenuShowInSubWindow001
 * @tc.desc: Test GetIsMenuShowInSubWindow when true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, GetIsMenuShowInSubWindow001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->isMenuShowInSubWindow_ = true;
    EXPECT_TRUE(pattern->GetIsMenuShowInSubWindow());
}

/**
 * @tc.name: SelectOverlayPattern_SetIsMenuShowInSubWindow001
 * @tc.desc: Test SetIsMenuShowInSubWindow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, SetIsMenuShowInSubWindow001, TestSize.Level1)
{
    auto pattern = CreatePattern();
    pattern->SetIsMenuShowInSubWindow(true);
    EXPECT_TRUE(pattern->isMenuShowInSubWindow_);
    pattern->SetIsMenuShowInSubWindow(false);
    EXPECT_FALSE(pattern->isMenuShowInSubWindow_);
}

/**
 * @tc.name: SelectOverlayPattern_DisableMenu001
 * @tc.desc: Test DisableMenu with true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, DisableMenu001, TestSize.Level1)
{
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto pattern = frameNode->GetPattern<SelectOverlayPattern>();
    pattern->DisableMenu(true);
    EXPECT_TRUE(pattern->info_->menuInfo.menuDisable);
}

/**
 * @tc.name: SelectOverlayPattern_DisableMenu002
 * @tc.desc: Test DisableMenu with false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTddTest, DisableMenu002, TestSize.Level1)
{
    auto info = std::make_shared<SelectOverlayInfo>(CreateDefaultInfo());
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto pattern = frameNode->GetPattern<SelectOverlayPattern>();
    pattern->info_->menuInfo.menuDisable = true;
    pattern->DisableMenu(false);
    EXPECT_FALSE(pattern->info_->menuInfo.menuDisable);
}

} // namespace OHOS::Ace::NG
