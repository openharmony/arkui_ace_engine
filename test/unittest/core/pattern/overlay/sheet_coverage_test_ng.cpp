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
#include <mutex>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SHEET_DETENTS_TWO = 2;
constexpr int32_t SHEET_DETENTS_THREE = 3;
constexpr Dimension WINDOW_EDGE_SPACE = 6.0_vp;
} // namespace

class SheetCoverageTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void TearDownTestCase();
    static void SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType);
};

void SheetCoverageTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
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

void SheetCoverageTestNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme.Upgrade();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetCoverageTestNg::SetSheetType(RefPtr<SheetPresentationPattern> sheetPattern, SheetType sheetType)
{
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    sheetStyle.sheetType = sheetType;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->sheetThemeType_ = "popup";
    Rect windowRect = { 0.0f, 0.0f, SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx(), 0.0f };
    MockPipelineContext::SetCurrentWindowRect(windowRect);
    sheetPattern->sheetKey_.hasValidTargetNode = true;
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetType_ = "popup";
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    SheetCoverageTestNg::SetSheetTheme(sheetTheme);
}

void SheetCoverageTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: InitTouchEvent001
 * @tc.desc: Increase the coverage of InitTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, InitTouchEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    auto host = dragBarPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    dragBarPattern->InitTouchEvent(gestureHub);

    auto touchTask = [](TouchEventInfo& info) {};
    dragBarPattern->touchEvent_ = AccessibilityManager::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    dragBarPattern->InitTouchEvent(gestureHub);
}

/**
 * @tc.name: InitClickEvent001
 * @tc.desc: Increase the coverage of InitClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, InitClickEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    EXPECT_EQ(dragBarPattern->clickListener_, nullptr);
    dragBarPattern->InitClickEvent();

    EXPECT_NE(dragBarPattern->clickListener_, nullptr);
    dragBarPattern->InitClickEvent();
}

/**
 * @tc.name: OnClick001
 * @tc.desc: Increase the coverage of OnClick function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, OnClick001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    EXPECT_EQ(dragBarPattern->clickArrowCallback_, nullptr);
    dragBarPattern->OnClick();

    dragBarPattern->clickArrowCallback_ = []() {};
    EXPECT_NE(dragBarPattern->clickArrowCallback_, nullptr);
    dragBarPattern->OnClick();
}

/**
 * @tc.name: ScaleAnimation001
 * @tc.desc: Increase the coverage of ScaleAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, ScaleAnimation001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    bool isDown = true;
    EXPECT_EQ(isDown, true);
    dragBarPattern->ScaleAnimation(isDown);

    isDown = false;
    EXPECT_EQ(isDown, false);
    dragBarPattern->ScaleAnimation(isDown);
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Increase the coverage of HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, HandleTouchEvent001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    TouchEventInfo eventInfo("touch");
    TouchLocationInfo locationInfo(1);
    locationInfo.touchType_ = TouchType::UNKNOWN;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::UNKNOWN);
    dragBarPattern->HandleTouchEvent(eventInfo);

    locationInfo.touchType_ = TouchType::DOWN;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::DOWN);
    dragBarPattern->HandleTouchEvent(eventInfo);

    locationInfo.touchType_ = TouchType::CANCEL;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::CANCEL);
    dragBarPattern->HandleTouchEvent(eventInfo);

    locationInfo.touchType_ = TouchType::UP;
    eventInfo.touches_.emplace_front(locationInfo);
    EXPECT_EQ(eventInfo.GetTouches().front().GetTouchType(), TouchType::UP);
    dragBarPattern->HandleTouchEvent(eventInfo);
}

/**
 * @tc.name: CreatePropertyCallback001
 * @tc.desc: Increase the coverage of CreatePropertyCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreatePropertyCallback001, TestSize.Level1)
{
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 101, AceType::MakeRefPtr<SheetDragBarPattern>());
    auto dragBarPattern = dragBarNode->GetPattern<SheetDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);
    EXPECT_EQ(dragBarPattern->property_, nullptr);
    dragBarPattern->CreatePropertyCallback();

    float scale = 1.0f;
    dragBarPattern->isDown_ = false;
    ASSERT_NE(dragBarPattern->property_, nullptr);
    auto property = AceType::DynamicCast<AnimatablePropertyFloat>(dragBarPattern->property_->property_);
    ASSERT_NE(property, nullptr);
    EXPECT_FALSE(NearZero(scale));
    EXPECT_NE(dragBarPattern->GetPaintProperty<SheetDragBarPaintProperty>(), nullptr);
    EXPECT_FALSE(dragBarPattern->isDown_);
    property->updateCallback_(scale);

    dragBarPattern->isDown_ = true;
    EXPECT_TRUE(dragBarPattern->isDown_);
    property->updateCallback_(scale);

    scale = 0.0f;
    EXPECT_TRUE(NearZero(scale));
    property->updateCallback_(scale);

    EXPECT_NE(dragBarPattern->property_, nullptr);
    dragBarPattern->CreatePropertyCallback();
}

/**
 * @tc.name: CreateOperationColumnNode001
 * @tc.desc: Increase the coverage of CreateOperationColumnNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreateOperationColumnNode001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_FALSE(sheetStyle.isTitleBuilder.has_value());
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    sheetStyle.isTitleBuilder = true;
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_FALSE(sheetStyle.sheetSubtitle.has_value());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateOperationColumnNode002
 * @tc.desc: Increase the coverage of CreateOperationColumnNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreateOperationColumnNode002, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 201,
        AceType::MakeRefPtr<SheetPresentationPattern>(301, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);

    sheetStyle.isTitleBuilder = true;
    sheetStyle.sheetTitle = "sheetTitle";
    sheetStyle.sheetSubtitle = "sheetSubtitle";
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    SheetView::CreateOperationColumnNode(titleBuilder, sheetStyle, sheetNode);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateDragBarNode001
 * @tc.desc: Increase the coverage of CreateDragBarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreateDragBarNode001, TestSize.Level1)
{
    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto operationColumn = FrameNode::CreateFrameNode("Column", 201, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_TWO);
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_THREE);
    EXPECT_FALSE(sheetStyle.isTitleBuilder.has_value());
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);

    SheetHeight detent;
    detent.sheetMode = SheetMode::AUTO;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::MEDIUM;
    sheetStyle.detents.emplace_back(detent);
    detent.sheetMode = SheetMode::LARGE;
    sheetStyle.detents.emplace_back(detent);
    sheetStyle.showDragBar = false;
    sheetStyle.isTitleBuilder = false;
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_TWO);
    EXPECT_EQ(sheetStyle.detents.size(), SHEET_DETENTS_THREE);
    EXPECT_FALSE(sheetStyle.showDragBar.value_or(true));
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_EQ(SheetView::BuildTitleColumn(sheetNode, sheetStyle), nullptr);
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);

    sheetStyle.detents.pop_back();
    sheetStyle.showDragBar = true;
    EXPECT_EQ(sheetStyle.detents.size(), SHEET_DETENTS_TWO);
    EXPECT_NE(sheetStyle.detents.size(), SHEET_DETENTS_THREE);
    EXPECT_TRUE(sheetStyle.showDragBar.value_or(true));
    SheetView::CreateDragBarNode(nullptr, operationColumn, sheetStyle, sheetNode);
}

/**
 * @tc.name: CreateDragBarNode002
 * @tc.desc: Increase the coverage of CreateDragBarNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreateDragBarNode002, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto operationColumn = FrameNode::CreateFrameNode("Column", 201, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetLayoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(sheetLayoutProperty, nullptr);
    NG::SheetStyle sheetStyle;
    sheetLayoutProperty->UpdateSheetStyle(sheetStyle);
    sheetStyle.isTitleBuilder = false;
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_NE(SheetView::BuildTitleColumn(sheetNode, sheetStyle), nullptr);
    SheetView::CreateDragBarNode(nullptr, operationColumn, sheetStyle, sheetNode);

    auto titleBuilder = FrameNode::CreateFrameNode("Title", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_FALSE(sheetStyle.isTitleBuilder.value());
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);

    sheetStyle.isTitleBuilder = true;
    EXPECT_TRUE(sheetStyle.isTitleBuilder.value());
    SheetView::CreateDragBarNode(titleBuilder, operationColumn, sheetStyle, sheetNode);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateCloseIconButtonNode001
 * @tc.desc: Increase the coverage of CreateCloseIconButtonNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreateCloseIconButtonNode001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->minPlatformVersion_;
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    EXPECT_TRUE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    SheetView::CreateCloseIconButtonNode(sheetNode, sheetStyle);

    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    EXPECT_FALSE(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN));
    SheetView::CreateCloseIconButtonNode(sheetNode, sheetStyle);
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = minPlatformVersion;
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildMainTitle001
 * @tc.desc: Increase the coverage of BuildMainTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, BuildMainTitle001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    SheetView::BuildMainTitle(sheetNode, sheetStyle);

    sheetStyle.sheetTitle = "sheetTitle";
    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    SheetView::BuildMainTitle(sheetNode, sheetStyle);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildSubTitle001
 * @tc.desc: Increase the coverage of BuildSubTitle function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, BuildSubTitle001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    EXPECT_FALSE(sheetStyle.sheetSubtitle.has_value());
    SheetView::BuildSubTitle(sheetNode, sheetStyle);

    sheetStyle.sheetSubtitle = "sheetSubtitle";
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    SheetView::BuildSubTitle(sheetNode, sheetStyle);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: BuildTitleColumn001
 * @tc.desc: Increase the coverage of BuildTitleColumn function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, BuildTitleColumn001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    NG::SheetStyle sheetStyle;
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale() + 1;
    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    EXPECT_FALSE(sheetStyle.sheetTitle.has_value());
    EXPECT_FALSE(sheetStyle.isTitleBuilder.has_value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);

    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    sheetStyle.isTitleBuilder = true;
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.has_value());
    EXPECT_TRUE(sheetStyle.isTitleBuilder.value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);

    sheetStyle.isTitleBuilder = false;
    EXPECT_FALSE(sheetStyle.isTitleBuilder.value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);

    sheetStyle.sheetTitle = "sheetTitle";
    EXPECT_TRUE(sheetStyle.sheetTitle.has_value());
    EXPECT_FALSE(sheetStyle.sheetSubtitle.has_value());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);

    sheetStyle.sheetSubtitle = "sheetSubtitle";
    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale() + 1;
    EXPECT_TRUE(sheetStyle.sheetSubtitle.has_value());
    EXPECT_NE(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);

    pipeline->fontScale_ = pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale();
    EXPECT_EQ(pipeline->GetFontScale(), pipeline->GetTheme<SheetTheme>()->GetSheetNormalScale());
    SheetView::BuildTitleColumn(sheetNode, sheetStyle);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnScrollStartRecursive001
 * @tc.desc: Increase the coverage of OnScrollStartRecursive function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, OnScrollStartRecursive001, TestSize.Level1)
{
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->animation_ = nullptr;
    EXPECT_EQ(sheetPattern->animation_, nullptr);
    sheetPattern->OnScrollStartRecursive(sheetPattern, 0.0f, 0.0f);

    AnimationOption option;
    sheetPattern->animation_ = AnimationUtils::StartAnimation(option, []() {}, []() {});
    sheetPattern->isAnimationProcess_ = false;
    EXPECT_NE(sheetPattern->animation_, nullptr);
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    sheetPattern->OnScrollStartRecursive(sheetPattern, 0.0f, 0.0f);

    sheetPattern->isAnimationProcess_ = true;
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
    sheetPattern->OnScrollStartRecursive(sheetPattern, 0.0f, 0.0f);
}

/**
 * @tc.name: HandleScroll001
 * @tc.desc: Increase the coverage of HandleScroll function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, HandleScroll001, TestSize.Level1)
{
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->currentOffset_ = -1.0f;
    sheetPattern->isSheetNeedScroll_ = true;
    int32_t source = SCROLL_FROM_ANIMATION;
    NestedState state = NestedState::CHILD_SCROLL;
    sheetPattern->isSheetPosChanged_ = false;
    EXPECT_FALSE(GreatOrEqual(sheetPattern->currentOffset_, 0.0f));
    EXPECT_TRUE(sheetPattern->isSheetNeedScroll_);
    EXPECT_EQ(state, NestedState::CHILD_SCROLL);
    sheetPattern->HandleScroll(0.0f, source, state, 0.0f);

    sheetPattern->currentOffset_ = 1.0f;
    sheetPattern->isSheetPosChanged_ = true;
    EXPECT_TRUE(GreatOrEqual(sheetPattern->currentOffset_, 0.0f));
    EXPECT_NE(source, SCROLL_FROM_UPDATE);
    sheetPattern->HandleScroll(0.0f, source, state, 0.0f);

    source = SCROLL_FROM_UPDATE;
    sheetPattern->isSheetNeedScroll_ = true;
    EXPECT_TRUE(sheetPattern->isSheetNeedScroll_);
    EXPECT_EQ(source, SCROLL_FROM_UPDATE);
    sheetPattern->HandleScroll(0.0f, source, state, 0.0f);

    state = NestedState::CHILD_OVER_SCROLL;
    sheetPattern->isSheetNeedScroll_ = false;
    EXPECT_FALSE(sheetPattern->isSheetNeedScroll_);
    EXPECT_EQ(state, NestedState::CHILD_OVER_SCROLL);
    sheetPattern->HandleScroll(0.0f, source, state, 0.0f);

    sheetPattern->currentOffset_ = -1.0f;
    sheetPattern->isSheetNeedScroll_ = true;
    state = NestedState::GESTURE;
    EXPECT_FALSE(GreatOrEqual(sheetPattern->currentOffset_, 0.0f));
    EXPECT_TRUE(sheetPattern->isSheetNeedScroll_);
    EXPECT_NE(state, NestedState::CHILD_SCROLL);
    EXPECT_NE(state, NestedState::CHILD_OVER_SCROLL);
    sheetPattern->HandleScroll(0.0f, source, state, 0.0f);

    sheetPattern->isSheetNeedScroll_ = false;
    EXPECT_FALSE(GreatOrEqual(sheetPattern->currentOffset_, 0.0f));
    EXPECT_FALSE(sheetPattern->isSheetNeedScroll_);
    sheetPattern->HandleScroll(0.0f, source, state, 0.0f);
}

/**
 * @tc.name: HandleScrollWithSheet001
 * @tc.desc: Increase the coverage of HandleScrollWithSheet function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, HandleScrollWithSheet001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    float scrollOffset = 0.0f;
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    sheetPattern->sheetDetentHeight_.emplace_back(1);
    sheetPattern->currentOffset_ = 1.0f;
    sheetPattern->height_ = 0.0f;
    sheetPattern->sheetHeightUp_ = 0.0f;
    sheetPattern->sheetMaxHeight_ = 0.0f;
    sheetPattern->scrollSizeMode_= ScrollSizeMode::FOLLOW_DETENT;
    EXPECT_FALSE(NearZero(sheetPattern->currentOffset_));
    sheetPattern->HandleScrollWithSheet(scrollOffset);

    scrollOffset = 0.0f;
    sheetPattern->currentOffset_ = 0.0f;
    EXPECT_TRUE(NearZero(sheetPattern->currentOffset_));
    EXPECT_FALSE(LessNotEqual(scrollOffset, 0.0f));
    sheetPattern->HandleScrollWithSheet(scrollOffset);

    scrollOffset = -1.0f;
    sheetPattern->scrollSizeMode_= ScrollSizeMode::CONTINUOUS;
    EXPECT_TRUE(LessNotEqual(scrollOffset, 0.0f));
    sheetPattern->HandleScrollWithSheet(scrollOffset);

    sheetPattern->sheetDetentHeight_.emplace_back(0);
    sheetPattern->HandleScrollWithSheet(scrollOffset);

    sheetPattern->sheetDetentHeight_.clear();
    EXPECT_EQ(sheetPattern->sheetDetentHeight_.size(), 0);
    sheetPattern->HandleScrollWithSheet(scrollOffset);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Increase the coverage of OnDirtyLayoutWrapperSwap function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->propSheetStyle_ = SheetStyle();
    auto dirty = sheetNode->CreateLayoutWrapper();
    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    ASSERT_NE(sheetLayoutAlgorithm, nullptr);
    sheetLayoutAlgorithm->sheetMaxHeight_ = 1.0f;
    sheetPattern->sheetOffsetX_ = sheetLayoutAlgorithm->sheetOffsetX_;
    sheetPattern->sheetOffsetY_ = sheetLayoutAlgorithm->sheetOffsetY_;
    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    EXPECT_FALSE(config.skipMeasure);
    EXPECT_TRUE(sheetLayoutAlgorithm->GetSheetMaxHeight() > 0);
    EXPECT_TRUE(NearEqual(sheetPattern->sheetOffsetX_, sheetLayoutAlgorithm->GetSheetOffsetX()));
    EXPECT_TRUE(NearEqual(sheetPattern->sheetOffsetY_, sheetLayoutAlgorithm->GetSheetOffsetY()));
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);

    config.skipMeasure = true;
    config.skipLayout = false;
    sheetPattern->sheetOffsetY_ = sheetLayoutAlgorithm->sheetOffsetY_ + 1.0f;
    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->windowRotate_ = false;
    AceApplicationInfo::GetInstance().packageName_ = "com.hua";
    AceApplicationInfo::GetInstance().packageName_.append("wei.hms.hua");
    AceApplicationInfo::GetInstance().packageName_.append("weiid");
    EXPECT_TRUE(config.skipMeasure && !config.skipLayout);
    EXPECT_TRUE(!NearEqual(sheetPattern->sheetOffsetY_, sheetLayoutAlgorithm->GetSheetOffsetY()));
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);

    sheetPattern->sheetOffsetY_ = sheetLayoutAlgorithm->sheetOffsetY_ + 1.0f;
    sheetPattern->sheetOffsetX_ = sheetLayoutAlgorithm->sheetOffsetX_ + 1.0f;
    EXPECT_TRUE(!NearEqual(sheetPattern->sheetOffsetX_, sheetLayoutAlgorithm->GetSheetOffsetX()));
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);

    config.skipLayout = true;
    EXPECT_TRUE(config.skipMeasure && config.skipLayout);
    sheetPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: CheckBuilderChange001
 * @tc.desc: Increase the coverage of CheckBuilderChange function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CheckBuilderChange001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto rootNode = FrameNode::CreateFrameNode("Root", 301, AceType::MakeRefPtr<RootPattern>());
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    sheetNode->MountToParent(rootNode);
    auto dragBarNode = FrameNode::CreateFrameNode("SheetDragBar", 401, AceType::MakeRefPtr<SheetDragBarPattern>());
    dragBarNode->MountToParent(sheetNode);
    auto scrollNode = FrameNode::CreateFrameNode("Scroll", 501, AceType::MakeRefPtr<ScrollPattern>());
    auto contentNode = FrameNode::GetOrCreateFrameNode("SheetContent", 601,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    contentNode->MountToParent(scrollNode);
    scrollNode->MountToParent(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto eventHub = contentNode->GetEventHub<EventHub>();
    RectF oldRect, rect;
    OffsetF oldOrigin, origin;
    sheetPattern->CheckBuilderChange();
    EXPECT_NE(sheetStyle.sheetMode, SheetMode::AUTO);
    auto innerCallbackInfo = eventHub->onAreaChangedInnerCallbacks_[contentNode->GetId()];
    ASSERT_NE(innerCallbackInfo, nullptr);
    innerCallbackInfo(oldRect, oldOrigin, rect, origin);

    sheetStyle.sheetMode = SheetMode::AUTO;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_EQ(sheetStyle.sheetMode, SheetMode::AUTO);
    innerCallbackInfo(oldRect, oldOrigin, rect, origin);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Increase the coverage of OnAttachToFrameNode function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->targetTag_ = "Sheet";
    sheetPattern->targetId_ = 101;
    auto targetNode = FrameNode::GetFrameNode(sheetPattern->targetTag_, sheetPattern->targetId_);
    ASSERT_NE(targetNode, nullptr);
    sheetPattern->OnAttachToFrameNode();
    auto eventHub = targetNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto innerOnAreaChangeCallback = eventHub->onAreaChangedInnerCallbacks_[sheetNode->GetId()];
    ASSERT_NE(innerOnAreaChangeCallback, nullptr);
    RectF oldRect, rect;
    OffsetF oldOrigin, origin;
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    innerOnAreaChangeCallback(oldRect, oldOrigin, rect, origin);

    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    sheetPattern->OnAttachToFrameNode();
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    innerOnAreaChangeCallback(oldRect, oldOrigin, rect, origin);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: InitPanEvent001
 * @tc.desc: Increase the coverage of InitPanEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, InitPanEvent001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->InitPanEvent();
    GestureEvent event;
    auto panEvent = sheetPattern->panEvent_;
    ASSERT_NE(panEvent, nullptr);
    panEvent->actionStart_(event);
    panEvent->actionUpdate_(event);
    panEvent->actionEnd_(event);
    panEvent->actionCancel_();
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: HandleDragStartAndOnCoordScrollStart001
 * @tc.desc: Increase the coverage of HandleDragStart and OnCoordScrollStart function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, HandleDragStartAndOnCoordScrollStart001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->animation_ = nullptr;
    EXPECT_EQ(sheetPattern->animation_, nullptr);
    sheetPattern->HandleDragStart();
    sheetPattern->OnCoordScrollStart();

    sheetPattern->animation_ = AnimationUtils::StartAnimation(AnimationOption(), []() {}, []() {});
    sheetPattern->isAnimationProcess_ = false;
    EXPECT_NE(sheetPattern->animation_, nullptr);
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    sheetPattern->HandleDragStart();
    sheetPattern->OnCoordScrollStart();

    sheetPattern->isAnimationProcess_ = true;
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
    sheetPattern->HandleDragStart();
    sheetPattern->OnCoordScrollStart();
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetType001
 * @tc.desc: Increase the coverage of GetSheetType function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetSheetType001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    int32_t minPlatformVersion = PipelineBase::GetCurrentContext()->minPlatformVersion_;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    sheetPattern->sheetThemeType_ = "center";
    EXPECT_TRUE(pipelineContext->GetDisplayWindowRectInfo().Width() >= SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx());
    EXPECT_FALSE(sheetStyle.sheetType.has_value());
    EXPECT_NE(sheetPattern->sheetThemeType_, "auto");
    EXPECT_NE(sheetPattern->sheetThemeType_, "popup");
    sheetPattern->GetSheetType();

    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->sheetThemeType_ = "popup";
    EXPECT_TRUE(sheetStyle.sheetType.has_value());
    EXPECT_NE(sheetStyle.sheetType.value(), SheetType::SHEET_BOTTOM);
    EXPECT_EQ(sheetPattern->sheetThemeType_, "popup");
    sheetPattern->GetSheetType();

    sheetPattern->sheetThemeType_ = "auto";
    EXPECT_EQ(sheetPattern->sheetThemeType_, "auto");
    sheetPattern->GetSheetType();

    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_EQ(sheetStyle.sheetType.value(), SheetType::SHEET_BOTTOM);
    sheetPattern->GetSheetType();

    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;
    pipelineContext->displayWindowRectInfo_.width_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx() - 5.0f;
    EXPECT_FALSE(pipelineContext->GetDisplayWindowRectInfo().Width() >= SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx());
    sheetPattern->GetSheetType();
    PipelineBase::GetCurrentContext()->minPlatformVersion_ = minPlatformVersion;
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTypeWithAuto001
 * @tc.desc: Increase the coverage of GetSheetTypeWithAuto function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetSheetTypeWithAuto001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return false; });
    MockPipelineContext::GetCurrent()->rootHeight_ = 6.0f;
    MockPipelineContext::GetCurrent()->rootWidth_ = 5.0f;
    EXPECT_FALSE(sheetPattern->IsFold());
    EXPECT_FALSE(LessNotEqual(PipelineContext::GetCurrentRootHeight(), PipelineContext::GetCurrentRootWidth()));
    SheetType sheetType;
    sheetPattern->GetSheetTypeWithAuto(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_BOTTOM);

    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBottom_ = "bottom";
    SheetCoverageTestNg::SetSheetTheme(sheetTheme);
    MockPipelineContext::GetCurrent()->rootHeight_ = 4.0f;
    EXPECT_TRUE(sheetPattern->IsFold());
    EXPECT_TRUE(sheetTheme->IsOnlyBottom());
    EXPECT_TRUE(LessNotEqual(PipelineContext::GetCurrentRootHeight(), PipelineContext::GetCurrentRootWidth()));
    sheetPattern->GetSheetTypeWithAuto(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_BOTTOMLANDSPACE);

    sheetTheme->sheetBottom_ = "undefined";
    EXPECT_FALSE(sheetTheme->IsOnlyBottom());
    sheetPattern->GetSheetTypeWithAuto(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_CENTER);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTypeWithAuto002
 * @tc.desc: Increase the coverage of GetSheetTypeWithAuto function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetSheetTypeWithAuto002, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBottom_ = "undefined";
    SheetCoverageTestNg::SetSheetTheme(sheetTheme);
    AceApplicationInfo::GetInstance().packageName_ = "com.ohos.useriam.authwidget";
    EXPECT_TRUE(sheetPattern->IsFold());
    EXPECT_FALSE(sheetTheme->IsOnlyBottom());
    EXPECT_FALSE(sheetStyle.sheetType.has_value());
    SheetType sheetType;
    sheetPattern->GetSheetTypeWithAuto(sheetType);

    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(sheetStyle.sheetType.has_value());
    EXPECT_NE(sheetStyle.sheetType.value(), SheetType::SHEET_CENTER);
    sheetPattern->GetSheetTypeWithAuto(sheetType);

    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(sheetStyle.sheetType.has_value());
    EXPECT_EQ(sheetStyle.sheetType.value(), SheetType::SHEET_CENTER);
    sheetPattern->GetSheetTypeWithAuto(sheetType);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTypeWithPopup001
 * @tc.desc: Increase the coverage of GetSheetTypeWithPopup function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetSheetTypeWithPopup001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrent()->rootWidth_ = 100.0f;
    EXPECT_FALSE(GreatOrEqual(PipelineContext::GetCurrentRootWidth(), SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()));
    EXPECT_FALSE(GreatOrEqual(PipelineContext::GetCurrentRootWidth(), SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()));
    SheetType sheetType;
    sheetPattern->GetSheetTypeWithPopup(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_BOTTOM_FREE_WINDOW);

    MockPipelineContext::GetCurrent()->rootWidth_ = SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    AceApplicationInfo::GetInstance().packageName_ = "";
    EXPECT_TRUE(GreatOrEqual(PipelineContext::GetCurrentRootWidth(), SHEET_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()));
    EXPECT_TRUE(LessNotEqual(PipelineContext::GetCurrentRootWidth(), SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()));
    EXPECT_FALSE(sheetStyle.sheetType.has_value());
    sheetPattern->GetSheetTypeWithPopup(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_CENTER);

    AceApplicationInfo::GetInstance().packageName_ = "com.ohos.useriam.authwidget";
    sheetPattern->GetSheetTypeWithPopup(sheetType);

    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(sheetStyle.sheetType.has_value());
    EXPECT_TRUE(sheetPattern->sheetKey_.hasValidTargetNode);
    sheetPattern->GetSheetTypeWithPopup(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_POPUP);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetSheetTypeWithPopup002
 * @tc.desc: Increase the coverage of GetSheetTypeWithPopup function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetSheetTypeWithPopup002, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MockPipelineContext::GetCurrent()->rootWidth_ = SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx();
    AceApplicationInfo::GetInstance().packageName_ = "";
    EXPECT_TRUE(GreatOrEqual(PipelineContext::GetCurrentRootWidth(), SHEET_PC_DEVICE_WIDTH_BREAKPOINT.ConvertToPx()));
    EXPECT_FALSE(sheetStyle.sheetType.has_value());
    SheetType sheetType;
    sheetPattern->GetSheetTypeWithPopup(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_POPUP);

    AceApplicationInfo::GetInstance().packageName_ = "com.ohos.useriam.authwidget";
    sheetPattern->GetSheetTypeWithPopup(sheetType);

    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    layoutProperty->propSheetStyle_ = sheetStyle;
    sheetPattern->sheetKey_.hasValidTargetNode = false;
    EXPECT_TRUE(sheetStyle.sheetType.has_value());
    EXPECT_FALSE(sheetPattern->sheetKey_.hasValidTargetNode);
    sheetPattern->GetSheetTypeWithPopup(sheetType);
    EXPECT_EQ(sheetType, SheetType::SHEET_CENTER);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: IsTypeNeedAvoidAiBar001
 * @tc.desc: Increase the coverage of IsTypeNeedAvoidAiBar function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, IsTypeNeedAvoidAiBar001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    SheetStyle sheetStyle;
    sheetStyle.showInPage = false;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto overlayManager = pipelineContext->overlayManager_;
    pipelineContext->overlayManager_ = nullptr;
    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_EQ(sheetPattern->GetOverlayManager(), nullptr);
    bool ret = sheetPattern->IsTypeNeedAvoidAiBar();
    EXPECT_TRUE(ret);

    layoutProperty->propSheetStyle_ = sheetStyle;
    pipelineContext->overlayManager_ = overlayManager;
    ASSERT_NE(sheetPattern->GetOverlayManager(), nullptr);
    EXPECT_FALSE(sheetPattern->GetOverlayManager()->IsRootExpansive());
    ret = sheetPattern->IsTypeNeedAvoidAiBar();
    EXPECT_TRUE(ret);

    auto rootLayoutProperty = AceType::DynamicCast<FrameNode>(pipelineContext->rootNode_)->GetLayoutProperty();
    rootLayoutProperty->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    rootLayoutProperty->safeAreaExpandOpts_->type = SAFE_AREA_TYPE_SYSTEM;
    rootLayoutProperty->safeAreaExpandOpts_->edges = SAFE_AREA_EDGE_TOP;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(sheetPattern->GetOverlayManager()->IsRootExpansive());
    EXPECT_FALSE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    ret = sheetPattern->IsTypeNeedAvoidAiBar();
    EXPECT_TRUE(ret);

    sheetPattern->overlayManager_ = AceType::WeakClaim(AceType::RawPtr(overlayManager));
    auto rootNode = FrameNode::CreateFrameNode("Root", 101, AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode("Stage", 201, AceType::MakeRefPtr<StagePattern>());
    stageNode->MountToParent(rootNode);
    sheetNode->MountToParent(stageNode);
    sheetStyle.showInPage = true;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    ret = sheetPattern->IsTypeNeedAvoidAiBar();
    EXPECT_FALSE(ret);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnScrollEndRecursiveAndHandleScrollVelocity001
 * @tc.desc: Increase the coverage of OnScrollEndRecursive and HandleScrollVelocity function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, OnScrollEndRecursiveAndHandleScrollVelocity001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->isSheetPosChanged_ = false;
    sheetPattern->OnScrollEndRecursive(std::nullopt);
    sheetPattern->isSheetNeedScroll_ = true;
    bool ret = sheetPattern->HandleScrollVelocity(1.0f, sheetPattern);
    EXPECT_TRUE(ret);

    sheetPattern->isSheetPosChanged_ = true;
    sheetPattern->OnScrollEndRecursive(std::nullopt);
    sheetPattern->isSheetPosChanged_ = true;
    sheetPattern->isSheetNeedScroll_ = false;
    ret = sheetPattern->HandleScrollVelocity(1.0f, sheetPattern);
    EXPECT_FALSE(ret);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: FireOnTypeDidChange001
 * @tc.desc: Increase the coverage of FireOnTypeDidChange function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, FireOnTypeDidChange001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->sheetType_ = SheetType::SHEET_CENTER;
    sheetPattern->preType_ = SheetType::SHEET_CENTER;
    EXPECT_EQ(sheetPattern->sheetType_, SheetType::SHEET_CENTER);
    EXPECT_EQ(sheetPattern->preType_, sheetPattern->sheetType_);
    sheetPattern->FireOnTypeDidChange();

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOM_FREE_WINDOW;
    EXPECT_EQ(sheetPattern->sheetType_, SheetType::SHEET_BOTTOM_FREE_WINDOW);
    EXPECT_NE(sheetPattern->preType_, sheetPattern->sheetType_);
    sheetPattern->FireOnTypeDidChange();

    sheetPattern->sheetType_ = SheetType::SHEET_BOTTOMLANDSPACE;
    EXPECT_EQ(sheetPattern->sheetType_, SheetType::SHEET_BOTTOMLANDSPACE);
    sheetPattern->FireOnTypeDidChange();
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayRoot001
 * @tc.desc: Increase the coverage of GetOverlayRoot function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetOverlayRoot001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    sheetPattern->GetOverlayRoot();

    sheetStyle.showInPage = false;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_FALSE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    sheetPattern->GetOverlayRoot();
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayManagerAndDeleteOverlay001
 * @tc.desc: Increase the coverage of GetOverlayManager and DeleteOverlay function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetOverlayManager001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    SheetStyle sheetStyle;
    sheetStyle.showInPage = true;
    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    layoutProperty->propSheetStyle_ = sheetStyle;
    auto rootNode = FrameNode::CreateFrameNode("Root", 101, AceType::MakeRefPtr<RootPattern>());
    auto stageNode = FrameNode::CreateFrameNode("Stage", 201, AceType::MakeRefPtr<StagePattern>());
    stageNode->MountToParent(rootNode);
    sheetNode->MountToParent(stageNode);
    EXPECT_TRUE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    EXPECT_NE(rootNode->GetTag(), V2::PAGE_ETS_TAG);
    EXPECT_NE(rootNode->GetTag(), V2::NAVDESTINATION_VIEW_ETS_TAG);
    sheetPattern->GetOverlayManager();

    rootNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    EXPECT_TRUE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    EXPECT_EQ(rootNode->GetTag(), V2::NAVDESTINATION_VIEW_ETS_TAG);
    sheetPattern->GetOverlayManager();

    rootNode->tag_ = V2::PAGE_ETS_TAG;
    rootNode->pattern_ = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    rootNode->GetPattern<PagePattern>()->overlayManager_ = PipelineContext::GetCurrentContext()->overlayManager_;
    EXPECT_EQ(rootNode->GetTag(), V2::PAGE_ETS_TAG);
    EXPECT_NE(rootNode->GetPattern<PagePattern>(), nullptr);
    EXPECT_NE(rootNode->GetPattern<PagePattern>()->GetOverlayManager(), nullptr);
    sheetPattern->GetOverlayManager();
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Increase the coverage of OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, OnWindowSizeChanged001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowManager = pipelineContext->windowManager_;
    pipelineContext->windowManager_ = nullptr;
    sheetPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::MOVE);

    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    pipelineContext->windowManager_ = windowManager;
    pipelineContext->windowManager_->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_UNDEFINED; };
    sheetPattern->OnWindowSizeChanged(0, 0,  WindowSizeChangeReason::ROTATION);

    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOMLANDSPACE);
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOMLANDSPACE);
    sheetPattern->isScrolling_ = false;
    pipelineContext->windowManager_->windowGetModeCallback_ = []() { return WindowMode::WINDOW_MODE_FLOATING; };
    sheetPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);

    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    sheetPattern->isScrolling_ = true;
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_BOTTOM);
    sheetPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::ROTATION);
    sheetPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::UNDEFINED);
    sheetPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG);
    sheetPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::RESIZE);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: HandleFitContontChange001
 * @tc.desc: Increase the coverage of HandleFitContontChange function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, HandleFitContontChange001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    sheetPattern->height_ = sheetPattern->sheetFitContentHeight_ + 1.0f;
    float height = sheetPattern->sheetFitContentHeight_;
    EXPECT_FALSE(NearEqual(sheetPattern->height_, sheetPattern->sheetFitContentHeight_));
    sheetPattern->HandleFitContontChange(height);

    sheetPattern->height_ = sheetPattern->sheetFitContentHeight_;
    EXPECT_TRUE(NearEqual(sheetPattern->height_, sheetPattern->sheetFitContentHeight_));
    EXPECT_TRUE(NearEqual(height, sheetPattern->sheetFitContentHeight_));
    sheetPattern->HandleFitContontChange(height);

    height = sheetPattern->sheetFitContentHeight_ + 1.0f;
    EXPECT_FALSE(NearEqual(height, sheetPattern->sheetFitContentHeight_));
    sheetPattern->HandleFitContontChange(height);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: DismissTransition001
 * @tc.desc: Increase the coverage of DismissTransition function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, DismissTransition001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto rootNode = FrameNode::CreateFrameNode("Root", 101,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    auto stageNode = FrameNode::CreateFrameNode("Stage", 201, AceType::MakeRefPtr<StagePattern>());
    stageNode->MountToParent(rootNode);
    sheetNode->MountToParent(stageNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    sheetPattern->overlayManager_ = AceType::WeakClaim(AceType::RawPtr(pipelineContext->overlayManager_));
    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_BOTTOM);
    EXPECT_NE(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    sheetPattern->DismissTransition(true, 1);

    auto layoutProperty = sheetPattern->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle sheetStyle;
    layoutProperty->propSheetStyle_ = sheetStyle;
    SheetCoverageTestNg::SetSheetType(sheetPattern, SheetType::SHEET_POPUP);
    EXPECT_FALSE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    EXPECT_EQ(sheetPattern->GetSheetType(), SheetType::SHEET_POPUP);
    sheetPattern->DismissTransition(false, 1);

    sheetStyle.showInPage = true;
    layoutProperty->propSheetStyle_ = sheetStyle;
    EXPECT_TRUE(layoutProperty->GetSheetStyleValue(SheetStyle()).showInPage.value_or(false));
    EXPECT_NE(rootNode->GetTag(), V2::PAGE_ETS_TAG);
    sheetPattern->DismissTransition(false, 1);

    rootNode->tag_ = V2::PAGE_ETS_TAG;
    EXPECT_EQ(rootNode->GetTag(), V2::PAGE_ETS_TAG);
    sheetPattern->DismissTransition(false, 1);
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetInAvoidanceRule001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::GetOffsetInAvoidanceRule function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetOffsetInAvoidanceRule001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    auto targetPlacement = algorithm->AvoidanceRuleOfPlacement(Placement::BOTTOM, SizeF(), OffsetF());
    EXPECT_NE(algorithm->getOffsetFunc_.find(targetPlacement), algorithm->getOffsetFunc_.end());
    algorithm->GetOffsetInAvoidanceRule(SizeF(), OffsetF());

    algorithm->getOffsetFunc_.clear();
    EXPECT_EQ(algorithm->getOffsetFunc_.find(targetPlacement), algorithm->getOffsetFunc_.end());
    algorithm->GetOffsetInAvoidanceRule(SizeF(), OffsetF());
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithBottomLeft001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::GetOffsetWithBottomLeft function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetOffsetWithBottomLeft001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    SizeF targetSize(50, 50);
    algorithm->sheetRadius_ = 10;
    Dimension arrowVertical = 8.0_vp;
    float arrowOffsetX = targetSize.Width() / 2;
    EXPECT_FALSE(LessNotEqual(arrowOffsetX - arrowVertical.ConvertToPx(), algorithm->sheetRadius_));
    algorithm->GetOffsetWithBottomLeft(targetSize, OffsetF());

    algorithm->sheetRadius_ = 100;
    EXPECT_TRUE(LessNotEqual(arrowOffsetX - arrowVertical.ConvertToPx(), algorithm->sheetRadius_));
    algorithm->GetOffsetWithBottomLeft(targetSize, OffsetF());
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithBottomRight001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::GetOffsetWithBottomRight function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetOffsetWithBottomRight001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    SizeF targetSize(50, 50);
    algorithm->sheetRadius_ = 10;
    algorithm->sheetWidth_ = 100;
    Dimension arrowVertical = 8.0_vp;
    float arrowOffsetX = algorithm->sheetWidth_ - targetSize.Width() / 2;
    EXPECT_FALSE(GreatNotEqual(arrowOffsetX + algorithm->sheetRadius_ + arrowVertical.ConvertToPx(),
        algorithm->sheetWidth_));
    algorithm->GetOffsetWithBottomRight(targetSize, OffsetF());

    algorithm->sheetRadius_ = 50;
    EXPECT_TRUE(GreatNotEqual(arrowOffsetX + algorithm->sheetRadius_ + arrowVertical.ConvertToPx(),
        algorithm->sheetWidth_));
    algorithm->GetOffsetWithBottomRight(targetSize, OffsetF());
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidanceRuleOfPlacement001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::AvoidanceRuleOfPlacement function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, AvoidanceRuleOfPlacement001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    algorithm->directionCheckFunc_[Placement::BOTTOM] = &SheetPresentationLayoutAlgorithm::CheckPlacementBottomLeft;
    algorithm->placementCheckFunc_[Placement::BOTTOM] = &SheetPresentationLayoutAlgorithm::CheckPlacementBottomLeft;
    OffsetF targetOffset(WINDOW_EDGE_SPACE.ConvertToPx() - 1.0f, 1.0f);
    EXPECT_FALSE(algorithm->CheckPlacementBottomLeft(SizeF(), targetOffset));
    algorithm->AvoidanceRuleOfPlacement(Placement::BOTTOM, SizeF(), targetOffset);

    targetOffset.x_ = WINDOW_EDGE_SPACE.ConvertToPx() + 1.0f;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    pipelineContext->displayWindowRectInfo_.width_ = 2*WINDOW_EDGE_SPACE.ConvertToPx() + algorithm->sheetWidth_ + 1.0f;
    EXPECT_TRUE(algorithm->CheckPlacementBottomLeft(SizeF(), targetOffset));
    algorithm->AvoidanceRuleOfPlacement(Placement::BOTTOM, SizeF(), targetOffset);

    algorithm->directionCheckFunc_[Placement::BOTTOM] = nullptr;
    algorithm->placementCheckFunc_[Placement::BOTTOM] = nullptr;
    algorithm->AvoidanceRuleOfPlacement(Placement::BOTTOM, SizeF(), OffsetF());
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetHeightBySheetStyle001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::GetHeightBySheetStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetHeightBySheetStyle001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    EXPECT_NE(algorithm->sheetStyle_.sheetMode, SheetMode::MEDIUM);
    EXPECT_NE(algorithm->sheetStyle_.sheetMode, SheetMode::LARGE);
    EXPECT_FALSE(algorithm->sheetStyle_.height.has_value());
    algorithm->GetHeightBySheetStyle();

    algorithm->sheetStyle_.sheetMode = SheetMode::MEDIUM;
    EXPECT_EQ(algorithm->sheetStyle_.sheetMode, SheetMode::MEDIUM);
    EXPECT_FALSE(algorithm->sheetStyle_.height.has_value());
    algorithm->GetHeightBySheetStyle();

    algorithm->sheetStyle_.sheetMode = SheetMode::LARGE;
    algorithm->sheetStyle_.height = 100.0_vp;
    EXPECT_EQ(algorithm->sheetStyle_.sheetMode, SheetMode::LARGE);
    EXPECT_TRUE(algorithm->sheetStyle_.height.has_value());
    EXPECT_FALSE(algorithm->SheetInSplitWindow());
    algorithm->GetHeightBySheetStyle();

    algorithm->sheetType_ = SheetType::SHEET_CENTER;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowManager = pipelineContext->windowManager_;
    windowManager->SetWindowGetModeCallBack([]() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_PRIMARY; });
    EXPECT_TRUE(algorithm->SheetInSplitWindow());
    algorithm->GetHeightBySheetStyle();
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: CreateSheetChildConstraint001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::CreateSheetChildConstraint function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, CreateSheetChildConstraint001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(algorithm->sheetStyle_.isTitleBuilder.has_value());
    algorithm->CreateSheetChildConstraint(sheetPattern->GetLayoutProperty<SheetPresentationProperty>());

    algorithm->sheetStyle_.isTitleBuilder = true;
    EXPECT_NE(algorithm->sheetType_, SheetType::SHEET_CENTER);
    EXPECT_NE(algorithm->sheetType_, SheetType::SHEET_POPUP);
    algorithm->CreateSheetChildConstraint(sheetPattern->GetLayoutProperty<SheetPresentationProperty>());

    algorithm->sheetType_ = SheetType::SHEET_CENTER;
    algorithm->CreateSheetChildConstraint(sheetPattern->GetLayoutProperty<SheetPresentationProperty>());
    algorithm->sheetType_ = SheetType::SHEET_POPUP;
    algorithm->CreateSheetChildConstraint(sheetPattern->GetLayoutProperty<SheetPresentationProperty>());
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: SheetInSplitWindow001
 * @tc.desc: Increase the coverage of SheetPresentationLayoutAlgorithm::SheetInSplitWindow function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, SheetInSplitWindow001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 301,
        AceType::MakeRefPtr<SheetPresentationPattern>(401, "SheetPresentation", std::move(callback)));
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    auto algorithm = AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    algorithm->sheetType_ = SheetType::SHEET_BOTTOM;
    EXPECT_FALSE(algorithm->SheetInSplitWindow());
    algorithm->sheetType_ = SheetType::SHEET_CENTER;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowManager = pipelineContext->windowManager_;
    pipelineContext->windowManager_ = nullptr;
    EXPECT_FALSE(algorithm->SheetInSplitWindow());
    pipelineContext->windowManager_ = windowManager;
    pipelineContext->displayWindowRectInfo_.height_ = SystemProperties::GetDeviceHeight();
    EXPECT_FALSE(algorithm->SheetInSplitWindow());
    pipelineContext->displayWindowRectInfo_.height_ = SystemProperties::GetDeviceHeight() - 10.0f;
    EXPECT_FALSE(algorithm->SheetInSplitWindow());

    windowManager->SetWindowGetModeCallBack([]() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_PRIMARY; });
    EXPECT_TRUE(algorithm->SheetInSplitWindow());
    windowManager->SetWindowGetModeCallBack([]() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_SECONDARY; });
    EXPECT_TRUE(algorithm->SheetInSplitWindow());
    SheetCoverageTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOverlayFromPageAndGetTagFromRootNodeType001
 * @tc.desc: Increase the coverage of SheetManager::GetOverlayFromPage and GetTagFromRootNodeType function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetOverlayFromPageAndGetTagFromRootNodeType001, TestSize.Level1)
{
    SheetCoverageTestNg::SetUpTestCase();
    int32_t rootNodeId = 101;
    auto sheetNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, rootNodeId,
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    RootNodeType rootNodeType = RootNodeType::PAGE_ETS_TAG;
    SheetManager::GetInstance().GetOverlayFromPage(-1, rootNodeType);
    EXPECT_NE(FrameNode::GetFrameNode(sheetNode->tag_, rootNodeId), nullptr);
    SheetManager::GetInstance().GetOverlayFromPage(rootNodeId, rootNodeType);

    rootNodeType = RootNodeType::NAVDESTINATION_VIEW_ETS_TAG;
    sheetNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;
    EXPECT_NE(FrameNode::GetFrameNode(sheetNode->tag_, rootNodeId), nullptr);
    SheetManager::GetInstance().GetOverlayFromPage(rootNodeId, rootNodeType);

    rootNodeType = RootNodeType::WINDOW_SCENE_ETS_TAG;
    sheetNode->tag_ = V2::WINDOW_SCENE_ETS_TAG;
    EXPECT_NE(FrameNode::GetFrameNode(sheetNode->tag_, rootNodeId), nullptr);
    SheetManager::GetInstance().GetOverlayFromPage(rootNodeId, rootNodeType);

    SheetManager::GetInstance().GetOverlayFromPage(rootNodeId, RootNodeType(100));
    SheetCoverageTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG
