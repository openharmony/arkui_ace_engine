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
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float TEST_MENU_WIDTH = 150.0f;
constexpr float TEST_MENU_HEIGHT = 60.0f;
constexpr float SAFE_AREA_TOP = 40.0f;
const RectF TEST_SHOW_AREA(0.0f, 0.0f, 1080.0f, 2400.0f);
const RectF TEST_FIRST_HANDLE(100.0f, 200.0f, 20.0f, 40.0f);
const RectF TEST_SECOND_HANDLE(300.0f, 200.0f, 20.0f, 40.0f);
const RectF TEST_SELECT_AREA(100.0f, 200.0f, 220.0f, 40.0f);
const OffsetF TEST_MENU_OFFSET(50.0f, 100.0f);
} // namespace

class SelectOverlayLayoutAlgorithmTddTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    RefPtr<SelectOverlayLayoutAlgorithm> CreateLayoutAlgorithm(
        const std::shared_ptr<SelectOverlayInfo>& info);
    std::shared_ptr<SelectOverlayInfo> CreateDefaultInfo();
    RefPtr<LayoutWrapperNode> CreateLayoutWrapper(
        const RefPtr<FrameNode>& frameNode);
};

void SelectOverlayLayoutAlgorithmTddTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(textOverlayTheme));
    auto rootNode = MockPipelineContext::GetCurrent()->rootNode_;
    if (rootNode) {
        auto rootRenderContext = rootNode->GetRenderContext();
        if (rootRenderContext) {
            rootRenderContext->UpdatePaintRect(RectF(0.0f, 0.0f, 1080.0f, 2400.0f));
        }
    }
}

void SelectOverlayLayoutAlgorithmTddTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<SelectOverlayLayoutAlgorithm> SelectOverlayLayoutAlgorithmTddTest::CreateLayoutAlgorithm(
    const std::shared_ptr<SelectOverlayInfo>& info)
{
    OffsetF defaultMenuEndOffset;
    std::optional<float> menuWidth = TEST_MENU_WIDTH;
    std::optional<float> menuHeight = TEST_MENU_HEIGHT;
    return AceType::MakeRefPtr<SelectOverlayLayoutAlgorithm>(
        info, defaultMenuEndOffset, menuWidth, menuHeight);
}

std::shared_ptr<SelectOverlayInfo> SelectOverlayLayoutAlgorithmTddTest::CreateDefaultInfo()
{
    auto info = std::make_shared<SelectOverlayInfo>();
    info->firstHandle.paintRect = TEST_FIRST_HANDLE;
    info->firstHandle.isShow = true;
    info->secondHandle.paintRect = TEST_SECOND_HANDLE;
    info->secondHandle.isShow = true;
    info->isSingleHandle = false;
    info->showArea = TEST_SHOW_AREA;
    info->selectArea = TEST_SELECT_AREA;
    info->menuInfo.menuIsShow = true;
    return info;
}

RefPtr<LayoutWrapperNode> SelectOverlayLayoutAlgorithmTddTest::CreateLayoutWrapper(
    const RefPtr<FrameNode>& frameNode)
{
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    return AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, geometryNode, layoutProperty);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_CheckInShowArea001
 * @tc.desc: Test CheckInShowArea with useFullScreen enabled
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, CheckInShowArea001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->useFullScreen = true;
    auto result = SelectOverlayLayoutAlgorithm::CheckInShowArea(*info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_CheckInShowArea002
 * @tc.desc: Test CheckInShowArea with single handle in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, CheckInShowArea002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->useFullScreen = false;
    info->isSingleHandle = true;
    info->firstHandle.paintRect = RectF(100.0f, 100.0f, 20.0f, 40.0f);
    auto result = SelectOverlayLayoutAlgorithm::CheckInShowArea(*info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_CheckInShowArea003
 * @tc.desc: Test CheckInShowArea with single handle outside show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, CheckInShowArea003, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->useFullScreen = false;
    info->isSingleHandle = true;
    info->firstHandle.paintRect = RectF(-10.0f, 100.0f, 20.0f, 40.0f);
    auto result = SelectOverlayLayoutAlgorithm::CheckInShowArea(*info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_CheckInShowArea004
 * @tc.desc: Test CheckInShowArea with both handles in show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, CheckInShowArea004, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->useFullScreen = false;
    info->isSingleHandle = false;
    info->firstHandle.paintRect = TEST_FIRST_HANDLE;
    info->secondHandle.paintRect = TEST_SECOND_HANDLE;
    auto result = SelectOverlayLayoutAlgorithm::CheckInShowArea(*info);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_CheckInShowArea005
 * @tc.desc: Test CheckInShowArea with first handle outside show area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, CheckInShowArea005, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->useFullScreen = false;
    info->isSingleHandle = false;
    info->firstHandle.paintRect = RectF(-10.0f, 100.0f, 20.0f, 40.0f);
    info->secondHandle.paintRect = TEST_SECOND_HANDLE;
    auto result = SelectOverlayLayoutAlgorithm::CheckInShowArea(*info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetDefaultMenuStartOffset001
 * @tc.desc: Test GetDefaultMenuStartOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetDefaultMenuStartOffset001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    algorithm->defaultMenuStartOffset_ = TEST_MENU_OFFSET;
    EXPECT_EQ(algorithm->GetDefaultMenuStartOffset(), TEST_MENU_OFFSET);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetDefaultMenuEndOffset001
 * @tc.desc: Test GetDefaultMenuEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetDefaultMenuEndOffset001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    OffsetF endOffset(200.0f, 100.0f);
    algorithm->defaultMenuEndOffset_ = endOffset;
    EXPECT_EQ(algorithm->GetDefaultMenuEndOffset(), endOffset);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetMenuWidth001
 * @tc.desc: Test GetMenuWidth with valid width
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetMenuWidth001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    auto width = algorithm->GetMenuWidth();
    EXPECT_TRUE(width.has_value());
    EXPECT_FLOAT_EQ(width.value(), TEST_MENU_WIDTH);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetMenuWidth002
 * @tc.desc: Test GetMenuWidth with no width set
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetMenuWidth002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    OffsetF offset;
    std::optional<float> menuWidth = std::nullopt;
    std::optional<float> menuHeight = TEST_MENU_HEIGHT;
    auto algorithm = AceType::MakeRefPtr<SelectOverlayLayoutAlgorithm>(
        info, offset, menuWidth, menuHeight);
    auto width = algorithm->GetMenuWidth();
    EXPECT_FALSE(width.has_value());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetMenuHeight001
 * @tc.desc: Test GetMenuHeight with valid height
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetMenuHeight001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    auto height = algorithm->GetMenuHeight();
    EXPECT_TRUE(height.has_value());
    EXPECT_FLOAT_EQ(height.value(), TEST_MENU_HEIGHT);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetMenuHeight002
 * @tc.desc: Test GetMenuHeight with no height set
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetMenuHeight002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    OffsetF offset;
    std::optional<float> menuWidth = TEST_MENU_WIDTH;
    std::optional<float> menuHeight = std::nullopt;
    auto algorithm = AceType::MakeRefPtr<SelectOverlayLayoutAlgorithm>(
        info, offset, menuWidth, menuHeight);
    auto height = algorithm->GetMenuHeight();
    EXPECT_FALSE(height.has_value());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetHasExtensionMenu001
 * @tc.desc: Test GetHasExtensionMenu when true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetHasExtensionMenu001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    algorithm->hasExtensionMenu_ = true;
    EXPECT_TRUE(algorithm->GetHasExtensionMenu());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetHasExtensionMenu002
 * @tc.desc: Test GetHasExtensionMenu when false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetHasExtensionMenu002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    algorithm->hasExtensionMenu_ = false;
    EXPECT_FALSE(algorithm->GetHasExtensionMenu());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetHideMoreOrBack001
 * @tc.desc: Test GetHideMoreOrBack when true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetHideMoreOrBack001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    algorithm->hideMoreOrBack_ = true;
    EXPECT_TRUE(algorithm->GetHideMoreOrBack());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetHideMoreOrBack002
 * @tc.desc: Test GetHideMoreOrBack when false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetHideMoreOrBack002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    algorithm->hideMoreOrBack_ = false;
    EXPECT_FALSE(algorithm->GetHideMoreOrBack());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_IsMenuAreaSmallerHandleArea001
 * @tc.desc: Test IsMenuAreaSmallerHandleArea when menu is smaller
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, IsMenuAreaSmallerHandleArea001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    RectF handleRect(0.0f, 0.0f, 20.0f, 60.0f);
    float menuHeight = 30.0f;
    float menuDistance = 5.0f;
    // 60 > 30 + 5 = true
    auto result = algorithm->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_IsMenuAreaSmallerHandleArea002
 * @tc.desc: Test IsMenuAreaSmallerHandleArea when menu is larger
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, IsMenuAreaSmallerHandleArea002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    RectF handleRect(0.0f, 0.0f, 20.0f, 30.0f);
    float menuHeight = 50.0f;
    float menuDistance = 5.0f;
    // 30 > 50 + 5 = false
    auto result = algorithm->IsMenuAreaSmallerHandleArea(handleRect, menuHeight, menuDistance);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_IsTextAreaSelectAll001
 * @tc.desc: Test IsTextAreaSelectAll with menu offset set
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, IsTextAreaSelectAll001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->menuInfo.menuOffset = OffsetF(100.0f, 200.0f);
    info->firstHandle.isShow = false;
    auto algorithm = CreateLayoutAlgorithm(info);
    EXPECT_TRUE(algorithm->IsTextAreaSelectAll());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_IsTextAreaSelectAll002
 * @tc.desc: Test IsTextAreaSelectAll without menu offset
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, IsTextAreaSelectAll002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->menuInfo.menuOffset = std::nullopt;
    auto algorithm = CreateLayoutAlgorithm(info);
    EXPECT_FALSE(algorithm->IsTextAreaSelectAll());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_IsTextAreaSelectAll003
 * @tc.desc: Test IsTextAreaSelectAll with both handles shown
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, IsTextAreaSelectAll003, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->menuInfo.menuOffset = OffsetF(100.0f, 200.0f);
    info->firstHandle.isShow = true;
    info->secondHandle.isShow = true;
    auto algorithm = CreateLayoutAlgorithm(info);
    EXPECT_FALSE(algorithm->IsTextAreaSelectAll());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustMenuInRootRect001
 * @tc.desc: Test AdjustMenuInRootRect with valid position
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustMenuInRootRect001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    OffsetF menuOffset(50.0f, 100.0f);
    SizeF menuSize(TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    SizeF rootSize(1080.0f, 2400.0f);
    algorithm->AdjustMenuInRootRect(menuOffset, menuSize, rootSize);
    // Position should remain valid
    EXPECT_GE(menuOffset.GetX(), 0.0f);
    EXPECT_GE(menuOffset.GetY(), 0.0f);
    EXPECT_LE(menuOffset.GetX() + menuSize.Width(), rootSize.Width());
    EXPECT_LE(menuOffset.GetY() + menuSize.Height(), rootSize.Height());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustMenuInRootRect002
 * @tc.desc: Test AdjustMenuInRootRect with position outside left boundary
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustMenuInRootRect002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    OffsetF menuOffset(-10.0f, 100.0f);
    SizeF menuSize(TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    SizeF rootSize(1080.0f, 2400.0f);
    algorithm->AdjustMenuInRootRect(menuOffset, menuSize, rootSize);
    // X position should be adjusted
    EXPECT_GE(menuOffset.GetX(), 0.0f);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustMenuInRootRect003
 * @tc.desc: Test AdjustMenuInRootRect with position outside right boundary
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustMenuInRootRect003, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    OffsetF menuOffset(1000.0f, 100.0f);
    SizeF menuSize(TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    SizeF rootSize(1080.0f, 2400.0f);
    algorithm->AdjustMenuInRootRect(menuOffset, menuSize, rootSize);
    // X position should be adjusted
    EXPECT_LE(menuOffset.GetX() + menuSize.Width(), rootSize.Width());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustMenuInRootRect004
 * @tc.desc: Test AdjustMenuInRootRect with position outside top boundary
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustMenuInRootRect004, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    OffsetF menuOffset(50.0f, -10.0f);
    SizeF menuSize(TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    SizeF rootSize(1080.0f, 2400.0f);
    algorithm->AdjustMenuInRootRect(menuOffset, menuSize, rootSize);
    // Y position should be adjusted
    EXPECT_GE(menuOffset.GetY(), 0.0f);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustMenuInRootRect005
 * @tc.desc: Test AdjustMenuInRootRect with position outside bottom boundary
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustMenuInRootRect005, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    OffsetF menuOffset(50.0f, 2350.0f);
    SizeF menuSize(TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    SizeF rootSize(1080.0f, 2400.0f);
    algorithm->AdjustMenuInRootRect(menuOffset, menuSize, rootSize);
    // Y position should be adjusted
    EXPECT_LE(menuOffset.GetY() + menuSize.Height(), rootSize.Height());
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_UpdateMainWindowOffset001
 * @tc.desc: Test UpdateMainWindowOffset when not in subwindow
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, UpdateMainWindowOffset001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto pattern = frameNode->GetPattern<SelectOverlayPattern>();
    pattern->isMenuShowInSubWindow_ = false;
    auto algorithm = CreateLayoutAlgorithm(info);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    algorithm->UpdateMainWindowOffset(AceType::RawPtr(layoutWrapper));
    // Offsets should be zero when not in subwindow
    EXPECT_FLOAT_EQ(algorithm->mainWindowOffset_.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(algorithm->mainWindowOffset_.GetY(), 0.0f);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetIsMenuShowInSubWindow001
 * @tc.desc: Test GetIsMenuShowInSubWindow when false
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetIsMenuShowInSubWindow001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto pattern = frameNode->GetPattern<SelectOverlayPattern>();
    pattern->isMenuShowInSubWindow_ = false;
    auto algorithm = CreateLayoutAlgorithm(info);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto result = algorithm->GetIsMenuShowInSubWindow(AceType::RawPtr(layoutWrapper));
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetIsMenuShowInSubWindow002
 * @tc.desc: Test GetIsMenuShowInSubWindow when true
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetIsMenuShowInSubWindow002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto pattern = frameNode->GetPattern<SelectOverlayPattern>();
    pattern->isMenuShowInSubWindow_ = true;
    auto algorithm = CreateLayoutAlgorithm(info);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto result = algorithm->GetIsMenuShowInSubWindow(AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_GetSafeAreaTop001
 * @tc.desc: Test GetSafeAreaTop with system safe area
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, GetSafeAreaTop001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto algorithm = CreateLayoutAlgorithm(info);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    SafeAreaInsets safeAreaInsets;
    safeAreaInsets.top_.start = SAFE_AREA_TOP;
    safeAreaManager->systemSafeArea_ = safeAreaInsets;
    auto top = algorithm->GetSafeAreaTop();
    EXPECT_GE(top, static_cast<uint32_t>(SAFE_AREA_TOP));
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustToInfo001
 * @tc.desc: Test AdjustToInfo with null info
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustToInfo001, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto algorithm = CreateLayoutAlgorithm(info);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    OffsetF menuOffset(50.0f, 100.0f);
    RectF menuRect(50.0f, 100.0f, TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    OffsetF windowOffset(0.0f, 0.0f);
    std::shared_ptr<SelectOverlayInfo> nullInfo = nullptr;
    auto result = algorithm->AdjustToInfo(
        AceType::RawPtr(layoutWrapper), menuOffset, menuRect, windowOffset, nullInfo);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustToInfo002
 * @tc.desc: Test AdjustToInfo without computeMenuOffset callback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustToInfo002, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->computeMenuOffset = nullptr;
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto algorithm = CreateLayoutAlgorithm(info);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    OffsetF menuOffset(50.0f, 100.0f);
    RectF menuRect(50.0f, 100.0f, TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    OffsetF windowOffset(0.0f, 0.0f);
    auto result = algorithm->AdjustToInfo(
        AceType::RawPtr(layoutWrapper), menuOffset, menuRect, windowOffset, info);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayLayoutAlgorithm_AdjustToInfo003
 * @tc.desc: Test AdjustToInfo with valid computeMenuOffset callback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayLayoutAlgorithmTddTest, AdjustToInfo003, TestSize.Level1)
{
    auto info = CreateDefaultInfo();
    info->computeMenuOffset = [](LayoutWrapper*, OffsetF& offset, const RectF&,
        OffsetF&, const std::shared_ptr<SelectOverlayInfo>&) -> bool {
        offset.SetX(200.0f);
        return true;
    };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(info);
    auto algorithm = CreateLayoutAlgorithm(info);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    OffsetF menuOffset(50.0f, 100.0f);
    RectF menuRect(50.0f, 100.0f, TEST_MENU_WIDTH, TEST_MENU_HEIGHT);
    OffsetF windowOffset(0.0f, 0.0f);
    auto result = algorithm->AdjustToInfo(
        AceType::RawPtr(layoutWrapper), menuOffset, menuRect, windowOffset, info);
    EXPECT_TRUE(result);
    EXPECT_FLOAT_EQ(menuOffset.GetX(), 200.0f);
}

} // namespace OHOS::Ace::NG
