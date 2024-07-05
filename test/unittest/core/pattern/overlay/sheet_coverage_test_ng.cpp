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

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_drag_bar_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SHEET_DETENTS_TWO = 2;
constexpr int32_t SHEET_DETENTS_THREE = 3;
} // namespace

class SheetCoverageTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
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
 * @tc.name: GetTitlePaddingPos001
 * @tc.desc: Increase the coverage of GetTitlePaddingPos function.
 * @tc.type: FUNC
 */
HWTEST_F(SheetCoverageTestNg, GetTitlePaddingPos001, TestSize.Level1)
{
    PaddingProperty padding;
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode("Sheet", 101,
        AceType::MakeRefPtr<SheetPresentationPattern>(201, "SheetPresentation", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    NG::SheetStyle sheetStyle;
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    AceApplicationInfo& applicationInfo = AceApplicationInfo::GetInstance();
    applicationInfo.apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TEN);
    EXPECT_FALSE(applicationInfo.GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    SheetView::GetTitlePaddingPos(padding, sheetNode);

    applicationInfo.apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    applicationInfo.isRightToLeft_ = false;
    EXPECT_TRUE(applicationInfo.GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE));
    EXPECT_FALSE(applicationInfo.IsRightToLeft());
    SheetView::GetTitlePaddingPos(padding, sheetNode);

    applicationInfo.isRightToLeft_ = true;
    EXPECT_TRUE(applicationInfo.IsRightToLeft());
    SheetView::GetTitlePaddingPos(padding, sheetNode);
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
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
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
    sheetPattern->OnScrollStartRecursive(0.0f, 0.0f);

    AnimationOption option;
    sheetPattern->animation_ = AnimationUtils::StartAnimation(option, []() {}, []() {});
    sheetPattern->isAnimationProcess_ = false;
    EXPECT_NE(sheetPattern->animation_, nullptr);
    EXPECT_FALSE(sheetPattern->isAnimationProcess_);
    sheetPattern->OnScrollStartRecursive(0.0f, 0.0f);

    sheetPattern->isAnimationProcess_ = true;
    EXPECT_TRUE(sheetPattern->isAnimationProcess_);
    sheetPattern->OnScrollStartRecursive(0.0f, 0.0f);
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
} // namespace OHOS::Ace::NG
