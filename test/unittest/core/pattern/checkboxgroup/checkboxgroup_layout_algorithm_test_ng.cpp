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
#include <optional>
#include <string>
#include <utility>

#include "gtest/gtest.h"

// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float CHECKBOXGROUP_COMPONENT_WIDTH = 200.0;
constexpr Dimension DEFAULT_WIDTH = Dimension(CHECKBOXGROUP_COMPONENT_WIDTH);
constexpr Dimension DEFAULT_HEIGHT = Dimension(300.0);
constexpr Dimension HORIZONTAL_PADDING = Dimension(48.0);
constexpr Dimension VERTICAL_PADDING = Dimension(24.0);
constexpr Dimension DEFAULT_PADDING_SIZE = Dimension(96.0);
const std::string CHECKBOXGROUP_NAME = "checkboxGroup";
constexpr float MARGIN_VALUE = 10.0f;
constexpr int CHILD_NODE_ID = 100;

} // namespace

class CheckBoxGroupLayoutAlgorithmTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CheckBoxGroupLayoutAlgorithmTestNG::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void CheckBoxGroupLayoutAlgorithmTestNG::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void CheckBoxGroupLayoutAlgorithmTestNG::SetUp() {}

void CheckBoxGroupLayoutAlgorithmTestNG::TearDown() {}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest001
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create mock theme manager and some parameters.
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    theme->defaultPaddingSize_ = DEFAULT_PADDING_SIZE;
    theme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    theme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: The return values are DEFAULT_PADDING_SIZE and DEFAULT_PADDING_SIZE.
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, DEFAULT_PADDING_SIZE.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, DEFAULT_PADDING_SIZE.ConvertToPx());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest002
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create mock theme manager and some parameters.
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    theme->defaultPaddingSize_ = DEFAULT_PADDING_SIZE;
    theme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    theme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: The return values are HORIZONTAL_PADDING and VERTICAL_PADDING.
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest003
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest003, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create mock theme manager and some parameters.
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    theme->defaultWidth_ = DEFAULT_WIDTH;
    theme->defaultHeight_ = DEFAULT_HEIGHT;
    theme->defaultPaddingSize_ = DEFAULT_PADDING_SIZE;
    theme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    theme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: The return values are DEFAULT_WIDTH, DEFAULT_HEIGHT and DEFAULT_PADDING_SIZE.
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.defaultWidth_, DEFAULT_WIDTH.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.defaultHeight_, DEFAULT_HEIGHT.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, DEFAULT_PADDING_SIZE.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, DEFAULT_PADDING_SIZE.ConvertToPx());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest004
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create mock theme manager and some parameters.
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    theme->defaultWidth_ = DEFAULT_WIDTH;
    theme->defaultHeight_ = DEFAULT_HEIGHT;
    theme->defaultPaddingSize_ = DEFAULT_PADDING_SIZE;
    theme->hotZoneHorizontalPadding_ = HORIZONTAL_PADDING;
    theme->hotZoneVerticalPadding_ = VERTICAL_PADDING;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: The return values are DEFAULT_WIDTH, DEFAULT_HEIGHT, HORIZONTAL_PADDING and VERTICAL_PADDING.
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.defaultWidth_, DEFAULT_WIDTH.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.defaultHeight_, DEFAULT_HEIGHT.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, HORIZONTAL_PADDING.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, VERTICAL_PADDING.ConvertToPx());
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest005
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: Check the param value
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.defaultWidth_, theme->defaultWidth_.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.defaultHeight_, theme->defaultHeight_.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, theme->defaultPaddingSize_.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, theme->defaultPaddingSize_.ConvertToPx());
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest006
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest006, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: Check the param value
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.defaultWidth_, theme->defaultWidth_.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.defaultHeight_, theme->defaultHeight_.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, theme->defaultPaddingSize_.ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, theme->defaultPaddingSize_.ConvertToPx());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest007
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest007, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    /**
     * @tc.steps: step1. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: Check the param value
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.defaultWidth_, theme->GetWidth().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.defaultHeight_, theme->GetHeight().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, theme->GetDefaultPaddingSize().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, theme->GetDefaultPaddingSize().ConvertToPx());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest008
 * @tc.desc: Verify that CheckBoxGroupLayoutAlgorithm's InitializeParam.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));

    /**
     * @tc.steps: step2. Call InitializeParam
     * @tc.expected: Check the param value.
     */
    CheckBoxGroupLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.InitializeParam(0);
    EXPECT_EQ(layoutAlgorithm.defaultWidth_, theme->GetWidth().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.defaultHeight_, theme->GetHeight().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.horizontalPadding_, theme->GetHotZoneHorizontalPadding().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm.verticalPadding_, theme->GetHotZoneVerticalPadding().ConvertToPx());
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest009
 * @tc.desc: Test CheckBoxGroupLayoutAlgorithm MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest009, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create contentConstraint and layoutWrapper
     */
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    std::optional<float> nullLength;
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = OptionalSizeF(nullLength, nullLength);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, geometryNode, AccessibilityManager::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: step2. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    theme->defaultWidth_ = Dimension(CHECKBOXGROUP_COMPONENT_WIDTH);
    theme->defaultHeight_ = Dimension(CHECKBOXGROUP_COMPONENT_WIDTH / 2);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto layoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Call MeasureContent
     * @tc.expected: Return sizeF and check the param value.
     */
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), CHECKBOXGROUP_COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), CHECKBOXGROUP_COMPONENT_WIDTH / 2);
    EXPECT_EQ(layoutAlgorithm->horizontalPadding_, theme->GetDefaultPaddingSize().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm->verticalPadding_, theme->GetDefaultPaddingSize().ConvertToPx());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest0010
 * @tc.desc: Test CheckBoxGroupLayoutAlgorithm MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest0010, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step1. Create contentConstraint and layoutWrapper
     */
    std::optional<float> nullLength;
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = OptionalSizeF(nullLength, nullLength);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, geometryNode, AccessibilityManager::MakeRefPtr<LayoutProperty>());

    /**
     * @tc.steps: step2. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<CheckboxTheme>();
    theme->defaultWidth_ = Dimension(CHECKBOXGROUP_COMPONENT_WIDTH);
    theme->defaultHeight_ = Dimension(CHECKBOXGROUP_COMPONENT_WIDTH / 2);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    auto layoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);

    /**
     * @tc.steps: step3. Call MeasureContent
     * @tc.expected: Return sizeF and check the param value.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FLOAT_EQ(size->Width(), CHECKBOXGROUP_COMPONENT_WIDTH / 2);
    EXPECT_FLOAT_EQ(size->Height(), CHECKBOXGROUP_COMPONENT_WIDTH / 2);
    EXPECT_EQ(layoutAlgorithm->horizontalPadding_, theme->GetDefaultPaddingSize().ConvertToPx());
    EXPECT_EQ(layoutAlgorithm->verticalPadding_, theme->GetDefaultPaddingSize().ConvertToPx());
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckBoxGroupLayoutAlgorithmTest011
 * @tc.desc: Test CheckBoxGroupLayoutAlgorithm MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxGroupLayoutAlgorithmTestNG, CheckBoxGroupLayoutAlgorithmTest011, TestSize.Level1)
{
    CheckBoxGroupModelNG checkBoxGroupModelNG;
    checkBoxGroupModelNG.Create(CHECKBOXGROUP_NAME);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    ASSERT_NE(pattern, nullptr);
    geometryNode->SetContentSize(SizeF(CHECKBOXGROUP_COMPONENT_WIDTH, CHECKBOXGROUP_COMPONENT_WIDTH));
    /**
     * @tc.steps: step1. Create contentConstraint and layoutWrapper
     */
    LayoutConstraintF contentConstraint;
    contentConstraint.selfIdealSize = OptionalSizeF(CHECKBOXGROUP_COMPONENT_WIDTH, CHECKBOXGROUP_COMPONENT_WIDTH);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode, geometryNode, AccessibilityManager::MakeRefPtr<LayoutProperty>());
    /**
     * @tc.steps: step2. Create mock theme manager
     * @tc.expected: create successfully.
     */
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetGroupName(CHECKBOXGROUP_NAME);
    eventHub->SetEnabled(true);
    auto makeFunc = [](CheckBoxGroupConfiguration config) -> RefPtr<FrameNode> {
        EXPECT_EQ(CHECKBOXGROUP_NAME, config.name_);
        EXPECT_EQ(CheckBoxGroupPaintProperty::SelectStatus::NONE, config.status_);
        EXPECT_EQ(true, config.enabled_);
        RefPtr<FrameNode> child =
            AceType::MakeRefPtr<FrameNode>("child", CHILD_NODE_ID, AceType::MakeRefPtr<Pattern>());
        return child;
    };
    pattern->SetBuilderFunc(makeFunc);
    pattern->contentModifierNode_ = pattern->BuildContentModifierNode();
    auto layoutAlgorithm = AceType::MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    ASSERT_NE(layoutAlgorithm, nullptr);
    ASSERT_NE(geometryNode->content_, nullptr);
    auto host = layoutWrapper.GetHostNode();
    ASSERT_NE(host, nullptr);
    auto geometry = host->GetGeometryNode();
    ASSERT_NE(geometry, nullptr);
    geometry->SetContentSize(SizeF(CHECKBOXGROUP_COMPONENT_WIDTH, CHECKBOXGROUP_COMPONENT_WIDTH));
    MarginPropertyF margin { .left = MARGIN_VALUE, .right = MARGIN_VALUE, .top = MARGIN_VALUE, .bottom = MARGIN_VALUE };
    geometry->UpdateMargin(margin);
    auto size = layoutAlgorithm->MeasureContent(contentConstraint, &layoutWrapper);
    EXPECT_FALSE(size.has_value());
    EXPECT_EQ(geometry->GetContentSize(), SizeF(0, 0));
    EXPECT_EQ(geometry->GetMargin()->left.value(), MARGIN_VALUE);
}
} // namespace OHOS::Ace::NG