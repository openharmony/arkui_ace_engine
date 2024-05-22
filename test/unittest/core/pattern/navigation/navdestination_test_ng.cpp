/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#define protected public
#define private public
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "mock_navigation_stack.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string NAVIGATION_TITLE = "NavdestinationTestNg";
const std::string NAVIGATION_SUBTITLE = "NavdestinationSubtitle";
constexpr float TITLEBAR_WIDTH = 480.0f;
constexpr float TITLEBAR_HEIGHT = 100.0f;
constexpr Dimension MAX_PADDING_START = 28.0_vp;
constexpr float BACK_BUTTON_FRAME_SIZE = 32.0f;
constexpr float TITLE_FRAME_WIDTH = 60.0f;
constexpr float TITLE_FRAME_HEIGHT = 30.0f;
constexpr float SUBTITLE_FRAME_WIDTH = 60.0f;
constexpr float SUBTITLE_FRAME_HEIGHT = 20.0f;

struct TestLayoutParams {
    RefPtr<LayoutWrapperNode> titleBarLayoutWrapper = nullptr;
    RefPtr<TitleBarNode> titleBarNode = nullptr;
    RefPtr<TitleBarLayoutProperty> titleBarLayoutProperty = nullptr;
    RefPtr<TitleBarLayoutAlgorithm> titleBarLayoutAlgorithm = nullptr;
};

struct TestGeometryOffsets {
    RefPtr<GeometryNode> backButtonGeometryNode = nullptr;
    RefPtr<GeometryNode> titleGeometryNode = nullptr;
    RefPtr<GeometryNode> subtitleGeometryNode = nullptr;
};
} // namespace

class NavdestinationTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    RefPtr<LayoutWrapperNode> CreateBackButtonWrapper(
        const RefPtr<TitleBarNode>& titleBarNode, const RefPtr<LayoutWrapperNode>& titleBarLayoutWrapper);
    RefPtr<LayoutWrapperNode> CreateTitleWrapper(
        const RefPtr<TitleBarNode>& titleBarNode, const RefPtr<LayoutWrapperNode>& titleBarLayoutWrapper);
    RefPtr<LayoutWrapperNode> CreateSubtitleWrapper(
        const RefPtr<TitleBarNode>& titleBarNode, const RefPtr<LayoutWrapperNode>& titleBarLayoutWrapper);
    RefPtr<LayoutWrapperNode> CreateTitleBarWrapper(
        const RefPtr<FrameNode>& frameNode, const RefPtr<LayoutWrapperNode>& layoutWrapper);
    RefPtr<LayoutWrapperNode> CreateNavDestinationWrapper();
    void InitChildrenComponent(TestLayoutParams& params, TestGeometryOffsets& offsets);
};

void NavdestinationTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void NavdestinationTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void NavdestinationTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

RefPtr<LayoutWrapperNode> NavdestinationTestNg::CreateNavDestinationWrapper()
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModelNG;
    navDestinationModelNG.Create();
    navDestinationModelNG.SetTitle(NAVIGATION_TITLE, true);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutWrapper, nullptr);
    return layoutWrapper;
}

RefPtr<LayoutWrapperNode> NavdestinationTestNg::CreateTitleBarWrapper(
    const RefPtr<FrameNode>& frameNode, const RefPtr<LayoutWrapperNode>& layoutWrapper)
{
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    CHECK_NULL_RETURN(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    CHECK_NULL_RETURN(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_RETURN(titleBarLayoutProperty, nullptr);
    auto titleBarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    CHECK_NULL_RETURN(titleBarGeometryNode, nullptr);
    auto titleBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(titleBarNode, titleBarGeometryNode, titleBarLayoutProperty);
    CHECK_NULL_RETURN(titleBarLayoutWrapper, nullptr);
    layoutWrapper->AppendChild(titleBarLayoutWrapper);
    titleBarGeometryNode->SetFrameSize(SizeF(TITLEBAR_WIDTH, TITLEBAR_HEIGHT));
    return titleBarLayoutWrapper;
}

RefPtr<LayoutWrapperNode> NavdestinationTestNg::CreateBackButtonWrapper(
    const RefPtr<TitleBarNode>& titleBarNode, const RefPtr<LayoutWrapperNode>& titleBarLayoutWrapper)
{
    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton());
    CHECK_NULL_RETURN(backButtonNode, nullptr);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty();
    CHECK_NULL_RETURN(backButtonLayoutProperty, nullptr);
    auto backButtonGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    CHECK_NULL_RETURN(backButtonGeometryNode, nullptr);
    auto backButtonLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(backButtonNode, backButtonGeometryNode, backButtonLayoutProperty);
    CHECK_NULL_RETURN(backButtonLayoutWrapper, nullptr);
    backButtonGeometryNode->SetFrameSize(SizeF(BACK_BUTTON_FRAME_SIZE, BACK_BUTTON_FRAME_SIZE));
    titleBarLayoutWrapper->AppendChild(backButtonLayoutWrapper);
    return backButtonLayoutWrapper;
}

RefPtr<LayoutWrapperNode> NavdestinationTestNg::CreateTitleWrapper(
    const RefPtr<TitleBarNode>& titleBarNode, const RefPtr<LayoutWrapperNode>& titleBarLayoutWrapper)
{
    auto titleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle());
    CHECK_NULL_RETURN(titleNode, nullptr);
    auto titleLayoutProperty = titleNode->GetLayoutProperty();
    CHECK_NULL_RETURN(titleLayoutProperty, nullptr);
    auto titleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    CHECK_NULL_RETURN(titleGeometryNode, nullptr);
    auto titleLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(titleNode, titleGeometryNode, titleLayoutProperty);
    CHECK_NULL_RETURN(titleLayoutWrapper, nullptr);
    titleGeometryNode->SetFrameSize(SizeF(TITLE_FRAME_WIDTH, TITLE_FRAME_HEIGHT));
    titleBarLayoutWrapper->AppendChild(titleLayoutWrapper);
    return titleLayoutWrapper;
}

RefPtr<LayoutWrapperNode> NavdestinationTestNg::CreateSubtitleWrapper(
    const RefPtr<TitleBarNode>& titleBarNode, const RefPtr<LayoutWrapperNode>& titleBarLayoutWrapper)
{
    auto subtitleNode = AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle());
    auto subtitleLayoutProperty = subtitleNode->GetLayoutProperty();
    CHECK_NULL_RETURN(subtitleLayoutProperty, nullptr);
    auto subtitleGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    CHECK_NULL_RETURN(subtitleGeometryNode, nullptr);
    auto subtitleLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(subtitleNode, subtitleGeometryNode, subtitleLayoutProperty);
    CHECK_NULL_RETURN(subtitleLayoutWrapper, nullptr);
    subtitleGeometryNode->SetFrameSize(SizeF(SUBTITLE_FRAME_WIDTH, SUBTITLE_FRAME_HEIGHT));
    titleBarLayoutWrapper->AppendChild(subtitleLayoutWrapper);
    return subtitleLayoutWrapper;
}

void NavdestinationTestNg::InitChildrenComponent(TestLayoutParams& params, TestGeometryOffsets& offsets)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto layoutWrapper = CreateNavDestinationWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    params.titleBarLayoutWrapper = CreateTitleBarWrapper(frameNode, layoutWrapper);
    ASSERT_NE(params.titleBarLayoutWrapper, nullptr);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    params.titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(params.titleBarNode, nullptr);
    auto backButtonLayoutWrapper = CreateBackButtonWrapper(params.titleBarNode, params.titleBarLayoutWrapper);
    ASSERT_NE(backButtonLayoutWrapper, nullptr);
    auto titleLayoutWrapper = CreateTitleWrapper(params.titleBarNode, params.titleBarLayoutWrapper);
    ASSERT_NE(titleLayoutWrapper, nullptr);
    auto subtitleLayoutWrapper = CreateSubtitleWrapper(params.titleBarNode, params.titleBarLayoutWrapper);
    ASSERT_NE(subtitleLayoutWrapper, nullptr);
    params.titleBarLayoutProperty = params.titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(params.titleBarLayoutProperty, nullptr);
    auto titleBarPattern = AceType::DynamicCast<TitleBarPattern>(params.titleBarNode->GetPattern());
    ASSERT_NE(titleBarPattern, nullptr);
    params.titleBarLayoutAlgorithm =
        AccessibilityManager::DynamicCast<TitleBarLayoutAlgorithm>(titleBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(params.titleBarLayoutAlgorithm, nullptr);
    offsets.backButtonGeometryNode = backButtonLayoutWrapper->GetGeometryNode();
    ASSERT_NE(offsets.backButtonGeometryNode, nullptr);
    offsets.titleGeometryNode = titleLayoutWrapper->GetGeometryNode();
    ASSERT_NE(offsets.titleGeometryNode, nullptr);
    offsets.subtitleGeometryNode = subtitleLayoutWrapper->GetGeometryNode();
    ASSERT_NE(offsets.subtitleGeometryNode, nullptr);
    params.titleBarLayoutAlgorithm->showBackButton_ = true;
    params.titleBarLayoutAlgorithm->maxPaddingStart_ = MAX_PADDING_START;
    params.titleBarLayoutAlgorithm->LayoutBackButton(
        AccessibilityManager::RawPtr(params.titleBarLayoutWrapper), params.titleBarNode, params.titleBarLayoutProperty);
    params.titleBarLayoutAlgorithm->LayoutTitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, SUBTITLE_FRAME_HEIGHT);
    params.titleBarLayoutAlgorithm->LayoutSubtitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, TITLE_FRAME_HEIGHT);
}

/**
 * @tc.name: NavDestinationTest001
 * @tc.desc: Test Create.
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG NavDestinationModelNG;
    NavDestinationModelNG.Create();
    NavDestinationModelNG.SetHideTitleBar(true);
    NavDestinationModelNG.SetTitle(NAVIGATION_TITLE, true);
    NavDestinationModelNG.SetSubtitle(NAVIGATION_SUBTITLE);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navDestinationPattern = navigationGroupNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    auto navDestinationLayoutProperty = navDestinationPattern->GetLayoutProperty<NavDestinationLayoutProperty>();
    ASSERT_NE(navDestinationLayoutProperty, nullptr);
}

/**
 * @tc.name: NavDestinationTest003
 * @tc.desc: Test Create.
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationTest003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG NavDestinationModelNG;
    auto builderFunc = []() {};
    NavDestinationModelNG.Create(std::move(builderFunc));
    NavDestinationModelNG.SetHideTitleBar(false);
    NavDestinationModelNG.SetTitle(NAVIGATION_TITLE, false);
    NavDestinationModelNG.SetSubtitle(NAVIGATION_SUBTITLE);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
}

/**
 * @tc.name: NavDestinationTest004
 * @tc.desc: Test CustomTitle.
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationTest004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG NavDestinationModelNG;
    auto builderFunc = []() {};
    auto onBackPressed = []() -> bool { return true; };
    NavDestinationModelNG.Create(std::move(builderFunc));
    NavDestinationModelNG.SetHideTitleBar(false);
    NavDestinationModelNG.SetTitle(NAVIGATION_TITLE, false);
    NavDestinationModelNG.SetSubtitle(NAVIGATION_SUBTITLE);
    NavDestinationModelNG.SetOnShown(std::move(builderFunc));
    NavDestinationModelNG.SetOnHidden(std::move(builderFunc));
    NavDestinationModelNG.SetOnBackPressed(std::move(onBackPressed));

    RefPtr<NG::UINode> customNode;
    NavDestinationModelNG.SetCustomTitle(customNode);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
}

/**
 * @tc.name: NavDestinationTest005
 * @tc.desc: Test SetBackButtonIcon.
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationTest005, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavDestinationModelNG navDestinationModelNG;
    auto builderFunc = []() {};
    std::string imageSource = "src";
    bool noPixMap = true;
    RefPtr<PixelMap> pixMap = nullptr;
    std::vector<std::string> nameList;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = true;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        CHECK_NULL_VOID(node);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    navDestinationModelNG.Create(std::move(builderFunc));
    navDestinationModelNG.SetBackButtonIcon(iconSymbol, imageSource, imageOption, pixMap, nameList);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    ASSERT_EQ(titleBarLayoutProperty->GetPixelMap(), nullptr);
    ASSERT_TRUE(titleBarLayoutProperty->GetNoPixMap());
    ASSERT_NE(titleBarLayoutProperty->GetBackIconSymbol(), nullptr);
    ImageSourceInfo imageSourceInfo = titleBarLayoutProperty->GetImageSourceValue();
    ASSERT_EQ(imageSourceInfo.GetSrc(), imageSource);
}

/**
 * @tc.name: NavDestinationOnReadyTest001
 * @tc.desc: Test onReady of NavDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationOnReadyTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(ElementRegister::GetInstance()->MakeUniqueId());

    /**
     * @tc.steps: step1. create navdestination and set onReady callback
     */
    NavDestinationModelNG navDestinationModel;
    navDestinationModel.Create([]() {}, AceType::MakeRefPtr<NavDestinationContext>());
    bool onReadyFired = false;
    navDestinationModel.SetOnReady([&onReadyFired](RefPtr<NG::NavDestinationContext>) { onReadyFired = true; });

    /**
     * @tc.steps: step2. process shallowBuilder
     * @tc.expected: check if onReady was called
     */
    auto groupNode = AceType::DynamicCast<NavDestinationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(groupNode, nullptr);
    groupNode->ProcessShallowBuilder();
    EXPECT_TRUE(onReadyFired);
}

/**
 * @tc.name: NavdestinationOnLanguageConfigurationUpdateTest001
 * @tc.desc: Test OnLanguageConfigurationUpdate of NavDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationOnLanguageConfigurationUpdateTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. create NavDestination
     */
    MockPipelineContextGetTheme();
    NavDestinationModelNG NavDestinationModelNG;
    NavDestinationModelNG.Create();
    NavDestinationModelNG.SetHideTitleBar(true);
    NavDestinationModelNG.SetTitle(NAVIGATION_TITLE, true);
    NavDestinationModelNG.SetSubtitle(NAVIGATION_SUBTITLE);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavDestinationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navDestinationPattern = navigationGroupNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestinationPattern, nullptr);
    /**
     * @tc.steps: step2. set the system language to right to left and call OnLanguageConfigurationUpdate
     * @tc.expected: NavDestination's isRightToLeft_ status is true
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    navDestinationPattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(navDestinationPattern->isRightToLeft_);
    /**
     * @tc.steps: step3. set the system language to left to right and call OnLanguageConfigurationUpdate
     * @tc.expected: NavDestination's isRightToLeft_ status is false
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    navDestinationPattern->OnLanguageConfigurationUpdate();
    EXPECT_FALSE(navDestinationPattern->isRightToLeft_);
}

/**
 * @tc.name: NavdestinationMirrorLayoutTest001
 * @tc.desc: test VERSION_NINE mirror layout of NavDestination title bar
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationMirrorLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set platform version to VERSION_NINE and create NavDestination.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_NINE));
    /**
     * @tc.steps: step2. set the system language to left to right and initialize children component.
     */
    TestLayoutParams params;
    TestGeometryOffsets offsets;
    InitChildrenComponent(params, offsets);
    auto ltrBackButton = offsets.backButtonGeometryNode->GetMarginFrameOffset().GetX();
    auto ltrTitle = offsets.titleGeometryNode->GetMarginFrameOffset().GetX();
    auto ltrSubtitle = offsets.subtitleGeometryNode->GetMarginFrameOffset().GetX();
    /**
     * @tc.steps: step3. set the system language to right to left, start layout and compare coordinates.
     * @tc.expected: NewOffsetX = titleBarWidth - componentWidth - offsetX.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    params.titleBarLayoutAlgorithm->LayoutBackButton(
        AccessibilityManager::RawPtr(params.titleBarLayoutWrapper), params.titleBarNode, params.titleBarLayoutProperty);
    params.titleBarLayoutAlgorithm->LayoutTitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, SUBTITLE_FRAME_HEIGHT);
    params.titleBarLayoutAlgorithm->LayoutSubtitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, TITLE_FRAME_HEIGHT);
    EXPECT_EQ(offsets.backButtonGeometryNode->GetMarginFrameOffset().GetX(),
        TITLEBAR_WIDTH - BACK_BUTTON_FRAME_SIZE - ltrBackButton);
    EXPECT_EQ(offsets.titleGeometryNode->GetMarginFrameOffset().GetX(), TITLEBAR_WIDTH - TITLE_FRAME_WIDTH - ltrTitle);
    EXPECT_EQ(offsets.subtitleGeometryNode->GetMarginFrameOffset().GetX(),
        TITLEBAR_WIDTH - SUBTITLE_FRAME_WIDTH - ltrSubtitle);
}

/**
 * @tc.name: NavdestinationMirrorLayoutTest002
 * @tc.desc: test VERSION_TEN mirror layout of NavDestination title bar
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationMirrorLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set platform version to VERSION_TEN and create NavDestination.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    /**
     * @tc.steps: step2. initialize children component and get default offset.
     */
    TestLayoutParams params;
    TestGeometryOffsets offsets;
    InitChildrenComponent(params, offsets);
    auto ltrBackButton = offsets.backButtonGeometryNode->GetMarginFrameOffset().GetX();
    auto ltrTitle = offsets.titleGeometryNode->GetMarginFrameOffset().GetX();
    auto ltrSubtitle = offsets.subtitleGeometryNode->GetMarginFrameOffset().GetX();
    /**
     * @tc.steps: step3. set the system language to right to left, start layout and compare coordinates.
     * @tc.expected: NewOffsetX = titleBarWidth - componentWidth - offsetX.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    params.titleBarLayoutAlgorithm->LayoutBackButton(
        AccessibilityManager::RawPtr(params.titleBarLayoutWrapper), params.titleBarNode, params.titleBarLayoutProperty);
    params.titleBarLayoutAlgorithm->LayoutTitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, SUBTITLE_FRAME_HEIGHT);
    params.titleBarLayoutAlgorithm->LayoutSubtitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, TITLE_FRAME_HEIGHT);
    EXPECT_EQ(offsets.backButtonGeometryNode->GetMarginFrameOffset().GetX(),
        TITLEBAR_WIDTH - BACK_BUTTON_FRAME_SIZE - ltrBackButton);
    EXPECT_EQ(offsets.titleGeometryNode->GetMarginFrameOffset().GetX(), TITLEBAR_WIDTH - TITLE_FRAME_WIDTH - ltrTitle);
    EXPECT_EQ(offsets.subtitleGeometryNode->GetMarginFrameOffset().GetX(),
        TITLEBAR_WIDTH - SUBTITLE_FRAME_WIDTH - ltrSubtitle);
}

/**
 * @tc.name: NavdestinationMirrorLayoutTest003
 * @tc.desc: test VERSION_TWELVE mirror layout of NavDestination title bar
 * @tc.type: FUNC
 */
HWTEST_F(NavdestinationTestNg, NavdestinationMirrorLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set platform version to VERSION_TWELVE and create NavDestination.
     */
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step2. set the system language to left to right and initialize children component.
     */
    TestLayoutParams params;
    TestGeometryOffsets offsets;
    InitChildrenComponent(params, offsets);
    auto ltrBackButton = offsets.backButtonGeometryNode->GetMarginFrameOffset().GetX();
    auto ltrTitle = offsets.titleGeometryNode->GetMarginFrameOffset().GetX();
    auto ltrSubtitle = offsets.subtitleGeometryNode->GetMarginFrameOffset().GetX();
    /**
     * @tc.steps: step3. set the system language to right to left, start layout and compare coordinates.
     * @tc.expected: NewOffsetX = titleBarWidth - componentWidth - offsetX.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    params.titleBarLayoutAlgorithm->LayoutBackButton(
        AccessibilityManager::RawPtr(params.titleBarLayoutWrapper), params.titleBarNode, params.titleBarLayoutProperty);
    params.titleBarLayoutAlgorithm->LayoutTitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, SUBTITLE_FRAME_HEIGHT);
    params.titleBarLayoutAlgorithm->LayoutSubtitle(AccessibilityManager::RawPtr(params.titleBarLayoutWrapper),
        params.titleBarNode, params.titleBarLayoutProperty, TITLE_FRAME_HEIGHT);
    EXPECT_EQ(offsets.backButtonGeometryNode->GetMarginFrameOffset().GetX(),
        TITLEBAR_WIDTH - BACK_BUTTON_FRAME_SIZE - ltrBackButton);
    EXPECT_EQ(offsets.titleGeometryNode->GetMarginFrameOffset().GetX(), TITLEBAR_WIDTH - TITLE_FRAME_WIDTH - ltrTitle);
    EXPECT_EQ(offsets.subtitleGeometryNode->GetMarginFrameOffset().GetX(),
        TITLEBAR_WIDTH - SUBTITLE_FRAME_WIDTH - ltrSubtitle);
}
} // namespace OHOS::Ace::NG
