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

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "core/common/ace_application_info.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_paint_method.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_ON = true;
constexpr float CONTAINER_WIDTH = 200.0f;
constexpr float CONTAINER_HEIGHT = 100.0f;
constexpr Dimension ZERO = 0.0_px;
constexpr Dimension TOGGLE_WIDTH = 60.0_px;
constexpr Dimension TOGGLE_HEIGHT = 20.0_px;
constexpr float SWITCH_WIDTH = 100.0f;
constexpr float SWITCH_HEIGHT = 50.0f;
constexpr float POINT_RADIUS_ILLEGAL = -20.0f;
constexpr float POINT_RADIUS_LARGE = 30.0f;
constexpr float TRACK_BORDER_RADIUS = 10.0f;
constexpr Color SELECTED_COLOR = Color(0XFFFF0000);
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr Dimension TOGGLE_TARGET_WIDTH = 36.0_px;
} // namespace

class ToggleSwitchTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleSwitchTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ToggleSwitchTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaddingPropertyF ToggleSwitchTestNg::CreatePadding(Dimension length)
{
    PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return padding;
}

/**
 * @tc.name: ToggleSwitchLayoutTest001
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest001, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), TOGGLE_TARGET_WIDTH.ConvertToPx());
    EXPECT_EQ(switchSize->Height(), TOGGLE_HEIGHT.ConvertToPx());

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest002
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest002, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));
    // different branch: update frameWidth = frameHeight = 0
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(30, 10); //30 is width of toggle, 10 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 18);  //18 is width of toggle
    EXPECT_EQ(switchSize->Height(), 10); //10 is height of toggle
    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest003
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest003, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: update (frameWidth / frameHeight) > ratio = 1.8
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 90);
    EXPECT_EQ(switchSize->Height(), SWITCH_HEIGHT);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest004
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest004, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: update (frameWidth / frameHeight) < ratio = 1.8
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(60, 40)); //60 is width of toggle, 40 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 60);  //60 is width of toggle

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest005
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest005, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: update (frameWidth / frameHeight) = ratio = 1.8
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(180, 100)); //180 is width of toggle, 100 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 180);  //180 is width of toggle
    EXPECT_EQ(switchSize->Height(), 100); //100 is height of toggle

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest006
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest006, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: update width and height over constraint
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(280, 180)); //280 is width of toggle, 180 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 280);  //280 is width of toggle

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest007
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest007, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: undefined selfIdealSize
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), TOGGLE_TARGET_WIDTH.ConvertToPx());
    EXPECT_EQ(switchSize->Height(), TOGGLE_HEIGHT.ConvertToPx());

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest008
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest008, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = 280.0_px;  //280.0_px is width of switchTheme
    switchTheme->height_ = 180.0_px; //180.0_px is height of switchTheme
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: undefined selfIdealSize
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 180);
    EXPECT_EQ(switchSize->Height(), CONTAINER_HEIGHT);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest009
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest009, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: update width and height illegal value
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(
        SizeF(0, CONTAINER_HEIGHT)); //280 is width of toggle, 180 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 0);
    EXPECT_EQ(switchSize->Height(), 0);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest010
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchLayoutTest010, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2.  get switchPattern and switchWrapper.
     * @tc.expected: step2. get switchPattern success.
     */
    auto switchPattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(switchPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(switchFrameNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(switchFrameNode, geometryNode, switchFrameNode->GetLayoutProperty());
    auto switchLayoutAlgorithm = AceType::DynamicCast<SwitchLayoutAlgorithm>(switchPattern->CreateLayoutAlgorithm());
    EXPECT_NE(switchLayoutAlgorithm, nullptr);
    layoutWrapper.SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(switchLayoutAlgorithm));

    /**
     * @tc.steps: step3. update layoutWrapper.
     */
    // set switchTheme to themeManager before using themeManager to get switchTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    // update switchTheme values
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    // different branch: update width and height illegal value
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(
        SizeF(-280, CONTAINER_HEIGHT)); //-280 is width of toggle, 180 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), -280); //-280 is width of toggle

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPaintTest001
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetPointRadius(), POINT_RADIUS_LARGE);
}

/**
 * @tc.name: ToggleSwitchPaintTest002
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetUnselectedColor(Color::RED);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->inactiveColor_, Color::RED);
}

/**
 * @tc.name: ToggleSwitchPaintTest003
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetSwitchPointColor(Color::BLACK);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->animatePointColor_->Get(), LinearColor(Color::BLACK));
}

/**
 * @tc.name: ToggleSwitchPaintTest004
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetTrackBorderRadius(Dimension(TRACK_BORDER_RADIUS));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetTrackRadius(), TRACK_BORDER_RADIUS);
}

/**
 * @tc.name: ToggleSwitchPaintTest005
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.ResetPointRadius();
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetPointRadius(), SWITCH_ERROR_RADIUS);
}

/**
 * @tc.name: ToggleSwitchPaintTest006
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.ResetTrackBorderRadius();
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetTrackRadius(), SWITCH_ERROR_RADIUS);
}

/**
 * @tc.name: ToggleSwitchPaintTest007
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetUnselectedColor(Color(0xFFFF00FF));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->inactiveColor_, Color(0xFFFF00FF));
}

/**
 * @tc.name: ToggleSwitchPaintTest008
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_ILLEGAL));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetPointRadius(), POINT_RADIUS_ILLEGAL);
}

/**
 * @tc.name: ToggleSwitchPaintTest009
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetTrackBorderRadius(Dimension(POINT_RADIUS_ILLEGAL));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetTrackRadius(), POINT_RADIUS_ILLEGAL);
}

/**
 * @tc.name: ToggleSwitchPaintTest010
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetPointRadius(Dimension(0));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetPointRadius(), 0);
}

/**
 * @tc.name: ToggleSwitchPaintTest011
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetWidth(Dimension(SWITCH_WIDTH));
    toggleModelNG.SetHeight(Dimension(SWITCH_HEIGHT));
    toggleModelNG.SetTrackBorderRadius(Dimension(0));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->GetTrackRadius(), 0);
}

/**
 * @tc.name: ToggleSwitchPaintTest012
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPaintTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetSwitchPointColor(Color(0xFF00FF00));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto switchTheme = AceType::MakeRefPtr<SwitchTheme>();
    switchTheme->width_ = TOGGLE_WIDTH;
    switchTheme->height_ = TOGGLE_HEIGHT;
    switchTheme->hotZoneHorizontalPadding_ = ZERO;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(switchTheme));

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    EXPECT_EQ(pattern->switchModifier_->animatePointColor_->Get(), LinearColor(Color(0xFF00FF00)));
}

/**
 * @tc.name: ToggleSwitchPatternTest001
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPatternTest001, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    pattern->width_ = SWITCH_WIDTH;
    pattern->height_ = SWITCH_HEIGHT;
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-5.00, -5.00) - [110.00 x 60.00]");

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPatternTest002
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPatternTest002, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    pattern->width_ = CONTAINER_WIDTH;
    pattern->height_ = CONTAINER_HEIGHT;
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (0.00, 0.00) - [200.00 x 100.00]");

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPatternTest003
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPatternTest003, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    pattern->width_ = TOGGLE_WIDTH.ConvertToPx();
    pattern->height_ = TOGGLE_HEIGHT.ConvertToPx();
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-20.00, -20.00) - [100.00 x 60.00]");

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPatternTest004
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPatternTest004, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    pattern->width_ = 0;
    pattern->height_ = TOGGLE_HEIGHT.ConvertToPx();
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-20.00, -20.00) - [40.00 x 60.00]");

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPatternTest005
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPatternTest005, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    pattern->width_ = 0;
    pattern->height_ = CONTAINER_HEIGHT;
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (0.00, 0.00) - [0.00 x 100.00]");

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPatternTest006
 * @tc.desc: Test update switchModifier.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchTestNg, ToggleSwitchPatternTest006, TestSize.Level1)
{
    int32_t rollbackApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    toggleModelNG.SetPointRadius(Dimension(POINT_RADIUS_LARGE));
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(switchFrameNode, nullptr);
    switchFrameNode->MarkModifyDone();
    auto pattern = AceType::DynamicCast<SwitchPattern>(switchFrameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->switchModifier_ = AceType::MakeRefPtr<SwitchModifier>(false, SELECTED_COLOR, 0.0f);
    SwitchPaintMethod switchPaintMethod = SwitchPaintMethod(pattern->switchModifier_);

    /**
     * @tc.steps: step2. get paintWrapper
     * @tc.expected: paintWrapper is not null
     */
    auto renderContext = switchFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto geometryNode = switchFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->GetPaintProperty<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    auto* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);

    EXPECT_EQ(pattern->switchModifier_, switchPaintMethod.GetContentModifier(paintWrapper));
    pattern->width_ = SWITCH_WIDTH;
    pattern->height_ = 0;
    switchPaintMethod.UpdateContentModifier(paintWrapper);
    auto eventHub = switchFrameNode->GetFocusHub();
    ASSERT_NE(eventHub, nullptr);
    RoundRect paintRect;
    eventHub->getInnerFocusRectFunc_(paintRect);
    EXPECT_EQ(paintRect.GetRect().ToString(), "RectT (-30.00, -30.00) - [160.00 x 60.00]");

    AceApplicationInfo::GetInstance().SetApiTargetVersion(rollbackApiVersion);
}
} // namespace OHOS::Ace::NG
