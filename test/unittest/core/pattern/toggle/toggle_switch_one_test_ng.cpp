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
#define protected public
#define private public
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "core/common/ace_application_info.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/toggle/switch_event_hub.h"
#include "core/components_ng/pattern/toggle/switch_modifier.h"
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
constexpr int32_t NODE_ID = 1;
constexpr int32_t THEME_SCOPEID = 0;
constexpr bool IS_ON = true;
constexpr float CONTAINER_WIDTH = 200.0f;
constexpr float CONTAINER_HEIGHT = 100.0f;
constexpr Dimension ZERO = 0.0_px;
constexpr Dimension TOGGLE_WIDTH = 60.0_px;
constexpr Dimension TOGGLE_HEIGHT = 20.0_px;
constexpr float SWITCH_WIDTH = 100.0f;
constexpr float SWITCH_HEIGHT = 50.0f;
constexpr float USER_DEFINE_WIDTH = 180.0f;
constexpr float USER_DEFINE_HEIGHT = 100.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
const SizeF TEST_CONTAINER_SIZE(200.0f, 200.0f);
const SizeF TEST_CONTAINER_SIZE0(0.0f, 0.0f);
constexpr float TEST_ZERO = 0.0f;
} // namespace

class ToggleSwitchOneTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static PaddingPropertyF CreatePadding(Dimension length);
};

void ToggleSwitchOneTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void ToggleSwitchOneTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

PaddingPropertyF ToggleSwitchOneTestNg::CreatePadding(Dimension length)
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
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest001, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), TOGGLE_WIDTH.ConvertToPx());
    EXPECT_EQ(switchSize->Height(), TOGGLE_HEIGHT.ConvertToPx());

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest002
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest002, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));
    // different branch: update frameWidth = frameHeight = 0
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = SizeF(30, 10); //30 is width of toggle, 10 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 30);  //30 is width of toggle
    EXPECT_EQ(switchSize->Height(), 10); //10 is height of toggle
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest003
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest003, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: update (frameWidth / frameHeight) > ratio = 1.8
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(SWITCH_WIDTH, SWITCH_HEIGHT));
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), SWITCH_WIDTH);
    EXPECT_EQ(switchSize->Height(), SWITCH_HEIGHT);

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest004
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest004, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: update (frameWidth / frameHeight) < ratio = 1.8
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(60, 40)); //60 is width of toggle, 40 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 60);  //60 is width of toggle
    EXPECT_EQ(switchSize->Height(), 40); //40 is height of toggle

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest005
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest005, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: update (frameWidth / frameHeight) = ratio = 1.8
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(USER_DEFINE_WIDTH, USER_DEFINE_HEIGHT));
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), USER_DEFINE_WIDTH);
    EXPECT_EQ(switchSize->Height(), USER_DEFINE_HEIGHT);

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest006
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest006, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: update width and height over constraint
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(280, 180)); //280 is width of toggle, 180 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 280);  //280 is width of toggle
    EXPECT_EQ(switchSize->Height(), 180); //180 is height of toggle

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest007
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest007, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: undefined selfIdealSize
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), TOGGLE_WIDTH.ConvertToPx());
    EXPECT_EQ(switchSize->Height(), TOGGLE_HEIGHT.ConvertToPx());

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest008
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest008, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: undefined selfIdealSize
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), CONTAINER_WIDTH);
    EXPECT_EQ(switchSize->Height(), CONTAINER_HEIGHT);

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest009
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest009, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: update width and height illegal value
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(
        SizeF(0, CONTAINER_HEIGHT)); //280 is width of toggle, 180 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), 0);
    EXPECT_EQ(switchSize->Height(), CONTAINER_HEIGHT);

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest010
 * @tc.desc: Test toggle switch layout.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest010, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
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
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(switchTheme));

    // different branch: update width and height illegal value
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.maxSize = CONTAINER_SIZE;
    layoutConstraintSize.selfIdealSize.SetSize(
        SizeF(-280, CONTAINER_HEIGHT)); //-280 is width of toggle, 180 is height of toggle
    auto switchSize = switchLayoutAlgorithm->MeasureContent(layoutConstraintSize, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), -280); //-280 is width of toggle
    EXPECT_EQ(switchSize->Height(), CONTAINER_HEIGHT);

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest014
 * @tc.desc: Test toggle switch matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest014, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);

    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2. get switchPattern and switchWrapper.
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
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to NO_MATCH.
     * @tc.expected: step3. switchSize is not equal to TEST_CONTAINER_SIZE.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutPolicyProperty layoutPolicyProperty;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_CONTAINER_SIZE);
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    auto switchSize = switchLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(switchSize->Width(), TEST_CONTAINER_SIZE.Width());
    EXPECT_NE(switchSize->Height(), TEST_CONTAINER_SIZE.Height());

    /**
     * @tc.steps: step4. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step4. switchSize is equal to TEST_CONTAINER_SIZE.
     */
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    switchSize = switchLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_EQ(switchSize->Width(), TEST_CONTAINER_SIZE.Width());
    EXPECT_EQ(switchSize->Height(), TEST_CONTAINER_SIZE.Height());

    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchPatternTest007
 * @tc.desc: Test HandleEnabled and OnClick.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest007, TestSize.Level1)
{
    SwitchPattern switchPattern;
    switchPattern.contentModifierNode_ =
        FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    switchPattern.HandleEnabled();
    switchPattern.OnClick();
    EXPECT_TRUE(switchPattern.UseContentModifier());
}

/**
 * @tc.name: ToggleSwitchPatternTest008
 * @tc.desc: Test MarkIsSelected.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest008, TestSize.Level1)
{
    SwitchPattern switchPattern;
    switchPattern.isOn_ = true;
    switchPattern.MarkIsSelected(true);
    EXPECT_TRUE(switchPattern.isOn_);
}

/**
 * @tc.name: ToggleSwitchPatternTest009
 * @tc.desc: Test OnTouchDown and OnTouchUp.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest009, TestSize.Level1)
{
    SwitchPattern switchPattern;
    switchPattern.contentModifierNode_ =
        FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    switchPattern.OnTouchDown();
    switchPattern.OnTouchUp();
    EXPECT_TRUE(switchPattern.UseContentModifier());
}

/**
 * @tc.name: ToggleSwitchPatternTest010
 * @tc.desc: Test BuildContentModifierNode.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest010, TestSize.Level1)
{
    SwitchPattern switchPattern;
    EXPECT_EQ(switchPattern.BuildContentModifierNode(), nullptr);
    SwitchMakeCallback callback = [](const ToggleConfiguration& toggleConfiguration) -> RefPtr<FrameNode> {
        return FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    };
    switchPattern.makeFunc_ = callback;
    auto framnode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    ASSERT_NE(framnode, nullptr);
    framnode->paintProperty_ = AceType::MakeRefPtr<SwitchPaintProperty>();
    framnode->eventHub_ = framnode->pattern_->CreateEventHub();
    switchPattern.frameNode_ = std::move(framnode);
    switchPattern.isOn_.reset();
    EXPECT_NE(switchPattern.BuildContentModifierNode(), nullptr);
}

/**
 * @tc.name: ToggleSwitchPatternTest011
 * @tc.desc: Test FireBuilder.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest011, TestSize.Level1)
{
    SwitchPattern switchPattern;
    auto framnode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    ASSERT_NE(framnode, nullptr);
    auto childrenOne = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, -1, AceType::MakeRefPtr<SwitchPattern>());
    ASSERT_NE(childrenOne, nullptr);
    auto childrenTwo = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    ASSERT_NE(childrenTwo, nullptr);
    framnode->children_.push_back(childrenOne);
    framnode->children_.push_back(childrenTwo);
    switchPattern.frameNode_ = std::move(framnode);
    switchPattern.FireBuilder();
    EXPECT_FALSE(switchPattern.makeFunc_.has_value());
    SwitchMakeCallback callback = [](const ToggleConfiguration& toggleConfiguration) -> RefPtr<FrameNode> {
        return FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    };
    switchPattern.makeFunc_ = callback;
    switchPattern.contentModifierNode_ = switchPattern.BuildContentModifierNode();
    switchPattern.FireBuilder();
    switchPattern.contentModifierNode_.Reset();
    switchPattern.FireBuilder();
    EXPECT_NE(switchPattern.contentModifierNode_, switchPattern.BuildContentModifierNode());
}

/**
 * @tc.name: ToggleSwitchPatternTest012
 * @tc.desc: Test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest012, TestSize.Level1)
{
    SwitchPattern switchPattern;
    auto framnode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    ASSERT_NE(framnode, nullptr);
    auto paintProperty = AceType::MakeRefPtr<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    framnode->paintProperty_ = paintProperty;
    switchPattern.frameNode_ = std::move(framnode);
    switchPattern.DumpInfo();
    EXPECT_NE(switchPattern.GetPaintProperty<SwitchPaintProperty>(), nullptr);
    paintProperty->UpdateIsOn(true);
    paintProperty->UpdateSelectedColor(Color::RED);
    paintProperty->UpdateUnselectedColor(Color::GREEN);
    paintProperty->UpdateSwitchPointColor(Color::BLUE);
    paintProperty->UpdatePointRadius(5.0_vp);
    paintProperty->UpdateTrackBorderRadius(2.0_vp);
    switchPattern.DumpInfo();
    EXPECT_TRUE(paintProperty->HasIsOn());
}

/**
 * @tc.name: ToggleSwitchPatternTest013
 * @tc.desc: Test OnThemeScopeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchPatternTest013, TestSize.Level1)
{
    SwitchPattern switchPattern;
    auto framnode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, NODE_ID, AceType::MakeRefPtr<SwitchPattern>());
    ASSERT_NE(framnode, nullptr);
    auto paintProperty = AceType::MakeRefPtr<SwitchPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
    framnode->paintProperty_ = paintProperty;
    switchPattern.frameNode_ = std::move(framnode);
    EXPECT_TRUE(switchPattern.OnThemeScopeUpdate(THEME_SCOPEID));
    paintProperty->UpdateSelectedColor(Color::RED);
    EXPECT_TRUE(switchPattern.OnThemeScopeUpdate(THEME_SCOPEID));
    paintProperty->UpdateSwitchPointColor(Color::BLUE);
    EXPECT_FALSE(switchPattern.OnThemeScopeUpdate(THEME_SCOPEID));
}

/**
 * @tc.name: ToggleFixIdealSizeTest003
 * @tc.desc: Test toggle switch fixIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleFixIdealSizeTest003, TestSize.Level1)
{
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    int32_t setApiVersion = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);

    /**
     * @tc.steps: step1. create switch and get frameNode.
     */
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(ToggleType::SWITCH, IS_ON);
    auto switchFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(switchFrameNode, nullptr);

    /**
     * @tc.steps: step2. get switchPattern and switchWrapper.
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
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to null.
     * @tc.expected: step3. switchSize is not equal to TEST_CONTAINER_SIZE.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF contentConstraint;
    contentConstraint.parentIdealSize.SetSize(TEST_CONTAINER_SIZE);
    auto switchSize = switchLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(switchSize, TEST_CONTAINER_SIZE);

    /**
     * @tc.steps: step3. set widthLayoutPolicy_ and heightLayoutPolicy_ to FIX_AT_IDEAL_SIZE,FIX_AT_IDEAL_SIZE.
     * @tc.expected: step3. switchSize is not equal to TEST_CONTAINER_SIZE.
     */
    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::FIX_AT_IDEAL_SIZE;
    layoutProperty->layoutPolicy_ = layoutPolicyProperty;
    switchSize = switchLayoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_NE(switchSize, TEST_CONTAINER_SIZE);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: ToggleSwitchLayoutTest015
 * @tc.desc: Test LayoutPolicyIsMatchParent.
 * @tc.type: FUNC
 */
HWTEST_F(ToggleSwitchOneTestNg, ToggleSwitchLayoutTest015, TestSize.Level1)
{
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
     * @tc.steps: step3. layoutPolicy is default.
     * @tc.expected: step3. frameWidth and frameHeight are equal to TEST_ZERO.
     */
    auto layoutProperty = layoutWrapper.GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    LayoutConstraintF contentConstraint;
    float frameWidth = 0.0f;
    float frameHeight = 0.0f;
    switchLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy,
        frameWidth, frameHeight);
    EXPECT_EQ(frameWidth, TEST_ZERO);
    EXPECT_EQ(frameHeight, TEST_ZERO);

    /**
     * @tc.steps: step4. set widthLayoutPolicy_ and heightLayoutPolicy_ to MATCH_PARENT.
     * @tc.expected: step4. frameWidth and frameHeight are equal to TEST_ZERO.
     */
    layoutPolicy->widthLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    layoutPolicy->heightLayoutPolicy_ = LayoutCalPolicy::MATCH_PARENT;
    switchLayoutAlgorithm->LayoutPolicyIsMatchParent(contentConstraint, layoutPolicy,
        frameWidth, frameHeight);
    EXPECT_EQ(frameWidth, TEST_ZERO);
    EXPECT_EQ(frameHeight, TEST_ZERO);
}
} // namespace OHOS::Ace::NG
