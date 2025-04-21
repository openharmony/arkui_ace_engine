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

#include <memory>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/image/image_base.h"
#include "ui/base/ace_type.h"

#include "base/utils/singleton.h"
#include "core/common/display_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/constants.h"

#define private public
#define protected public
#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const double DIMENSIONVALUE = 1.0;
const double DIMENSIONVALUETWO = 2.0;
const double DIMENSIONVALUENE = -1.0;
const double DOUBLEZERO = 0.0;
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const CalcDimension WIDTHDIMENSION = CalcDimension(DIMENSIONVALUE);
const CalcDimension HEIGHTDIMENSION = CalcDimension(DIMENSIONVALUE);
const int32_t BACKGROUNDBLURSTYLEZERO = 0;
const int32_t BACKGROUNDBLURSTYLE = 1;
const int32_t INTONE = 1;
const NG::BorderWidthProperty BORDERWIDTH = { .leftDimen = Dimension(DIMENSIONVALUE) };
const BorderColorProperty BORDERCOLOR = { .bottomColor = Color::WHITE };
const Color COLOR = Color::WHITE;
const NG::BorderRadiusProperty BORDERRADIUS = BorderRadiusProperty(Dimension(DIMENSIONVALUE));
} // namespace

class DialogPatternAdditionalTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void DialogPatternAdditionalTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DialogPatternAdditionalTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump001
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogProperties_.title = TITLE;
    pattern->dialogProperties_.subtitle = SUBTITLE;
    pattern->dialogProperties_.content = MESSAGE;
    pattern->dialogProperties_.width = WIDTHDIMENSION;
    pattern->dialogProperties_.height = HEIGHTDIMENSION;
    pattern->dialogProperties_.backgroundBlurStyle = BACKGROUNDBLURSTYLE;
    pattern->dialogProperties_.borderWidth = BORDERWIDTH;
    pattern->dialogProperties_.borderColor = BORDERCOLOR;
    pattern->dialogProperties_.backgroundColor = COLOR;
    pattern->dialogProperties_.borderRadius = BORDERRADIUS;
    ButtonInfo buttonInfo = { .text = TITLE };
    pattern->dialogProperties_.buttons.emplace_back(buttonInfo);
    pattern->dialogProperties_.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    pattern->dialogProperties_.maskColor = COLOR;
    pattern->dialogProperties_.maskRect = DimensionRect();
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 26);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump002
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpInfo(jsonPtr);
    EXPECT_EQ(jsonPtr->GetArraySize(), 12);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump003
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.title = TITLE;
    pattern->dialogProperties_.subtitle = SUBTITLE;
    pattern->dialogProperties_.content = MESSAGE;
    pattern->dialogProperties_.width = WIDTHDIMENSION;
    pattern->dialogProperties_.height = HEIGHTDIMENSION;
    pattern->dialogProperties_.backgroundBlurStyle = BACKGROUNDBLURSTYLE;
    pattern->dialogProperties_.borderWidth = BORDERWIDTH;
    pattern->dialogProperties_.borderColor = BORDERCOLOR;
    pattern->dialogProperties_.backgroundColor = COLOR;
    pattern->dialogProperties_.borderRadius = BORDERRADIUS;
    ButtonInfo buttonInfo = { .text = TITLE };
    pattern->dialogProperties_.buttons.emplace_back(buttonInfo);
    pattern->dialogProperties_.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    pattern->dialogProperties_.maskColor = COLOR;
    pattern->dialogProperties_.maskRect = DimensionRect();
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpInfo(jsonPtr);
    EXPECT_EQ(jsonPtr->GetArraySize(), 26);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump004
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpSimplifyInfo(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("Type"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.title = TITLE;
    pattern->dialogProperties_.subtitle = SUBTITLE;
    pattern->dialogProperties_.content = MESSAGE;
    pattern->dialogProperties_.buttonDirection = DialogButtonDirection::HORIZONTAL;
    pattern->dialogProperties_.backgroundColor = COLOR;
    pattern->dialogProperties_.backgroundBlurStyle = BACKGROUNDBLURSTYLE;
    pattern->DumpSimplifyInfo(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("Title"));
    EXPECT_TRUE(jsonPtr->Contains("Subtitle"));
    EXPECT_TRUE(jsonPtr->Contains("Content"));
    EXPECT_TRUE(jsonPtr->Contains("ButtonDirection"));
    EXPECT_TRUE(jsonPtr->Contains("BackgroundBlurStyle"));
    EXPECT_TRUE(jsonPtr->Contains("BackgroundColor"));
    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.backgroundBlurStyle = BACKGROUNDBLURSTYLEZERO;
    pattern->DumpSimplifyInfo(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("BackgroundBlurStyle"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump005
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("Width"));
    EXPECT_FALSE(jsonPtr->Contains("Height"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.width = WIDTHDIMENSION;
    pattern->dialogProperties_.height = HEIGHTDIMENSION;
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("Width"));
    EXPECT_TRUE(jsonPtr->Contains("Height"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.width = CalcDimension();
    pattern->dialogProperties_.height = CalcDimension();
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("Width"));
    EXPECT_FALSE(jsonPtr->Contains("Height"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.width = CalcDimension();
    pattern->dialogProperties_.height = HEIGHTDIMENSION;
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("Width"));
    EXPECT_FALSE(jsonPtr->Contains("Height"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.width = WIDTHDIMENSION;
    pattern->dialogProperties_.height = CalcDimension();
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("Width"));
    EXPECT_FALSE(jsonPtr->Contains("Height"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump006
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->dialogProperties_.width = WIDTHDIMENSION;
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("Width"));
    EXPECT_FALSE(jsonPtr->Contains("Height"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.height = HEIGHTDIMENSION;
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("Width"));
    EXPECT_TRUE(jsonPtr->Contains("Height"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump007
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpSimplifyBorderProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("BorderWidth"));
    EXPECT_FALSE(jsonPtr->Contains("BorderColor"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.borderWidth = BORDERWIDTH;
    pattern->dialogProperties_.borderColor = BORDERCOLOR;
    pattern->DumpSimplifyBorderProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("BorderWidth"));
    EXPECT_TRUE(jsonPtr->Contains("BorderColor"));

    Dimension defaultValue(0, Dimension().Unit());
    BorderRadiusProperty defaultRadius(defaultValue);
    BorderColorProperty defaultColor = { Color::BLACK, Color::BLACK, Color::BLACK, Color::BLACK, std::nullopt,
        std::nullopt };
    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.borderWidth->SetBorderWidth(defaultValue);
    pattern->dialogProperties_.borderColor = defaultColor;
    pattern->DumpSimplifyBorderProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("BorderWidth"));
    EXPECT_FALSE(jsonPtr->Contains("BorderColor"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump008
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->dialogProperties_.autoCancel = false;
    pattern->dialogProperties_.customStyle = false;
    pattern->dialogProperties_.isMenu = false;
    pattern->dialogProperties_.isMask = false;
    pattern->dialogProperties_.isModal = false;
    pattern->dialogProperties_.isSceneBoardDialog = false;
    pattern->dialogProperties_.isSysBlurStyle = false;
    pattern->dialogProperties_.isShowInSubWindow = false;
    pattern->DumpSimplifyBoolProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("AutoCancel"));
    EXPECT_FALSE(jsonPtr->Contains("CustomStyle"));
    EXPECT_FALSE(jsonPtr->Contains("IsMenu"));
    EXPECT_FALSE(jsonPtr->Contains("IsMask"));
    EXPECT_FALSE(jsonPtr->Contains("IsModal"));
    EXPECT_FALSE(jsonPtr->Contains("IsSceneBoardDialog"));
    EXPECT_FALSE(jsonPtr->Contains("IsSysBlurStyle"));
    EXPECT_FALSE(jsonPtr->Contains("IsShowInSubWindow"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.autoCancel = true;
    pattern->dialogProperties_.customStyle = true;
    pattern->dialogProperties_.isMenu = true;
    pattern->dialogProperties_.isMask = true;
    pattern->dialogProperties_.isModal = true;
    pattern->dialogProperties_.isSceneBoardDialog = true;
    pattern->dialogProperties_.isSysBlurStyle = true;
    pattern->dialogProperties_.isShowInSubWindow = true;
    pattern->DumpSimplifyBoolProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("AutoCancel"));
    EXPECT_TRUE(jsonPtr->Contains("CustomStyle"));
    EXPECT_TRUE(jsonPtr->Contains("IsMenu"));
    EXPECT_TRUE(jsonPtr->Contains("IsMask"));
    EXPECT_TRUE(jsonPtr->Contains("IsModal"));
    EXPECT_TRUE(jsonPtr->Contains("IsSceneBoardDialog"));
    EXPECT_TRUE(jsonPtr->Contains("IsSysBlurStyle"));
    EXPECT_TRUE(jsonPtr->Contains("IsShowInSubWindow"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump009
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->DumpSimplifyObjectProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("Alignment"));
    EXPECT_TRUE(jsonPtr->Contains("Offset"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    ButtonInfo buttonInfo = { .text = TITLE };
    pattern->dialogProperties_.buttons.emplace_back(buttonInfo);
    pattern->dialogProperties_.shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultXS);
    pattern->dialogProperties_.maskColor = COLOR;
    pattern->dialogProperties_.maskRect = DimensionRect();
    pattern->DumpSimplifyObjectProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("Buttons"));
    EXPECT_TRUE(jsonPtr->Contains("Shadow"));
    EXPECT_TRUE(jsonPtr->Contains("MaskColor"));
    EXPECT_TRUE(jsonPtr->Contains("MaskRect"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump010
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->dialogProperties_.height = HEIGHTDIMENSION;
    EXPECT_FALSE(pattern->dialogProperties_.width.has_value());
    EXPECT_TRUE(pattern->dialogProperties_.height.has_value());
    pattern->DumpSimplifySizeProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("Width"));
    EXPECT_FALSE(jsonPtr->Contains("Height"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgDump011
 * @tc.desc: Test DialogPattern Dump
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgDump011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    /**
     * @tc.steps: step2. Invoke Dump functions.
     * @tc.expected: These Dump properties are matched.
     */
    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.borderRadius = BorderRadiusProperty(Dimension(1, Dimension().Unit()));
    pattern->DumpSimplifyBorderProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("BorderRadius"));

    Dimension defaultValue(0, Dimension().Unit());
    BorderRadiusProperty defaultRadius(defaultValue);
    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    pattern->dialogProperties_.borderRadius = defaultRadius;
    pattern->DumpSimplifyBorderProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("BorderRadius"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgHandle001
 * @tc.desc: Test DialogPattern Handle
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgHandle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    DialogProperties props;
    props.isSysBlurStyle = true;
    if (!props.backgroundBlurStyle.has_value()) {
        props.backgroundBlurStyle.emplace();
    }
    auto backgroundBlurStyle = static_cast<int>(BlurStyle::THIN);
    props.backgroundBlurStyle.value() = backgroundBlurStyle;
    pattern->UpdateContentRenderContext(frameNode, props);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->HandleBlurEvent();
    pattern->HandleFocusEvent();
    ASSERT_NE(pattern->contentRenderContext_, nullptr);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgToJsonValue001
 * @tc.desc: Test DialogPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::unique_ptr<JsonValue> jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    auto filterJson = InspectorFilter();
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->ToJsonValue(jsonPtr, filterJson);
    EXPECT_TRUE(jsonPtr->Contains("title"));
    EXPECT_TRUE(jsonPtr->Contains("subtitle"));
    EXPECT_TRUE(jsonPtr->Contains("message"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    const std::string attr = "color";
    filterJson.AddFilterAttr(attr);
    pattern->ToJsonValue(jsonPtr, filterJson);
    EXPECT_FALSE(jsonPtr->Contains("title"));
    EXPECT_FALSE(jsonPtr->Contains("subtitle"));
    EXPECT_FALSE(jsonPtr->Contains("message"));

    jsonPtr.reset();
    jsonPtr = JsonUtil::Create(false);
    ASSERT_NE(jsonPtr, nullptr);
    frameNode->tag_ = "UINode";
    pattern->ToJsonValue(jsonPtr, filterJson);
    EXPECT_FALSE(jsonPtr->Contains("title"));
    EXPECT_FALSE(jsonPtr->Contains("subtitle"));
    EXPECT_FALSE(jsonPtr->Contains("message"));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgOnDetachFromFrameNode001
 * @tc.desc: Test DialogPattern OnDetachFromFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgOnDetachFromFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(stageNode, nullptr);
    FrameNode& ref = *stageNode;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->foldDisplayModeChangedCallbackId_.reset();
    pattern->hoverModeChangedCallbackId_.reset();
    pattern->OnDetachFromFrameNode(&ref);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgOnAttachToMainTree001
 * @tc.desc: Test DialogPattern OnAttachToMainTree
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgOnAttachToMainTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    RefPtr<FrameNode> parent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);
    frameNode->SetParent(parent);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    auto parentNode = AceType::DynamicCast<FrameNode>(frameNode->GetParent());
    ASSERT_NE(parentNode, nullptr);
    parentNode->tag_ = V2::NAVDESTINATION_VIEW_ETS_TAG;

    auto containerId = Container::CurrentId();
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    mockSubwindow->isRosenWindowCreate_ = true;
    SubwindowManager::GetInstance()->AddSubwindow(containerId, SubwindowType::TYPE_DIALOG, mockSubwindow);

    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->OnAttachToMainTree();
}

/**
 * @tc.name: DialogPatternAdditionalTestNgUpdateHostWindowRect001
 * @tc.desc: Test DialogPattern UpdateHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgUpdateHostWindowRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->isUIExtensionSubWindow_ = true;
    pattern->UpdateHostWindowRect();
    EXPECT_TRUE(pipeline->GetInstanceId() < MIN_SUBCONTAINER_ID);
    pipeline->instanceId_ = MIN_SUBCONTAINER_ID + 1;
    pattern->UpdateHostWindowRect();
    EXPECT_FALSE(pipeline->GetInstanceId() < MIN_SUBCONTAINER_ID);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgUpdateHostWindowRect002
 * @tc.desc: Test DialogPattern UpdateHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgUpdateHostWindowRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->isUIExtensionSubWindow_ = true;
    pipeline->instanceId_ = MIN_SUBCONTAINER_ID + 1;
    EXPECT_FALSE(pipeline->GetInstanceId() < MIN_SUBCONTAINER_ID);
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    EXPECT_TRUE(SystemProperties::IsSuperFoldDisplayDevice());
    pattern->UpdateHostWindowRect();
}

/**
 * @tc.name: DialogPatternAdditionalTestNgParseBorderRadius001
 * @tc.desc: Test DialogPattern ParseBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgParseBorderRadius001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogTheme_->radius_ = Radius(DIMENSIONVALUETWO, DIMENSIONVALUETWO);
    BorderRadiusProperty raidus = {};
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->ParseBorderRadius(raidus);
    EXPECT_EQ(raidus.radiusTopLeft.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_EQ(raidus.radiusTopRight.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_EQ(raidus.radiusBottomLeft.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_EQ(raidus.radiusBottomRight.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());

    raidus.radiusTopLeft->SetValue(DIMENSIONVALUENE);
    raidus.radiusTopRight->SetValue(DIMENSIONVALUENE);
    raidus.radiusBottomLeft->SetValue(DIMENSIONVALUENE);
    raidus.radiusBottomRight->SetValue(DIMENSIONVALUENE);
    pattern->ParseBorderRadius(raidus);
    EXPECT_EQ(raidus.radiusTopLeft.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_EQ(raidus.radiusTopRight.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_EQ(raidus.radiusBottomLeft.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_EQ(raidus.radiusBottomRight.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());

    raidus.radiusTopLeft->SetValue(DIMENSIONVALUE);
    raidus.radiusTopRight->SetValue(DIMENSIONVALUE);
    raidus.radiusBottomLeft->SetValue(DIMENSIONVALUE);
    raidus.radiusBottomRight->SetValue(DIMENSIONVALUE);
    pattern->ParseBorderRadius(raidus);
    EXPECT_NE(raidus.radiusTopLeft.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_NE(raidus.radiusTopRight.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_NE(raidus.radiusBottomLeft.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
    EXPECT_NE(raidus.radiusBottomRight.value().Value(), pattern->dialogTheme_->GetRadius().GetX().Value());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgAddExtraMaskNode001
 * @tc.desc: Test DialogPattern AddExtraMaskNode
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgAddExtraMaskNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    DialogProperties props = {};
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    auto totalChildCount = frameNode->GetTotalChildCount();
    pattern->isUIExtensionSubWindow_ = true;
    props.isModal = false;
    pattern->AddExtraMaskNode(props);
    EXPECT_EQ(totalChildCount, frameNode->GetTotalChildCount());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgParseButtonFontColorAndBgColor001
 * @tc.desc: Test DialogPattern ParseButtonFontColorAndBgColor
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgParseButtonFontColorAndBgColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogTheme_->buttonHighlightBgColor_ = Color::BLACK;
    pattern->dialogTheme_->buttonDefaultBgColor_ = Color::GREEN;
    pattern->dialogTheme_->buttonDefaultFontColor_ = Color::BLUE;
    ButtonInfo params;
    params.dlgButtonStyle = DialogButtonStyle::DEFAULT;
    params.textColor = MESSAGE;
    params.defaultFocus = false;
    std::string textColor;
    std::optional<Color> bgColor;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->ParseButtonFontColorAndBgColor(params, textColor, bgColor);
    EXPECT_EQ(textColor, MESSAGE);

    params.dlgButtonStyle.reset();
    params.textColor = "";
    textColor = "";
    params.defaultFocus = true;
    pattern->isFirstDefaultFocus_ = false;
    pattern->ParseButtonFontColorAndBgColor(params, textColor, bgColor);
    EXPECT_EQ(textColor, pattern->dialogTheme_->GetButtonDefaultFontColor().ColorToString());
    EXPECT_EQ(bgColor, pattern->dialogTheme_->GetButtonDefaultBgColor());

    params.dlgButtonStyle.reset();
    params.textColor = "";
    textColor = "";
    params.defaultFocus = true;
    bgColor.reset();
    pattern->isFirstDefaultFocus_ = true;
    pattern->dialogTheme_->button_type_ = 1;
    pattern->ParseButtonFontColorAndBgColor(params, textColor, bgColor);
    EXPECT_EQ(textColor, pattern->dialogTheme_->GetButtonDefaultFontColor().ColorToString());
    EXPECT_EQ(bgColor, pattern->dialogTheme_->GetButtonDefaultBgColor());

    params.dlgButtonStyle.reset();
    params.defaultFocus = true;
    pattern->isFirstDefaultFocus_ = true;
    pattern->dialogTheme_->button_type_ = 0;
    bgColor.reset();
    pattern->ParseButtonFontColorAndBgColor(params, textColor, bgColor);
    EXPECT_EQ(bgColor, pattern->dialogTheme_->GetButtonHighlightBgColor());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgCreateButtonText001
 * @tc.desc: Test DialogPattern CreateButtonText
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgCreateButtonText001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    string text = TITLE;
    string colorStr = "";
    auto buttonNode = pattern->CreateButtonText(text, colorStr);
    ASSERT_NE(buttonNode, nullptr);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgBuildMenu001
 * @tc.desc: Test DialogPattern BuildMenu
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgBuildMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    std::vector<ButtonInfo> buttons;
    pattern->isSuitableForElderly_ = true;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    auto menuNode = pattern->BuildMenu(buttons, false);
    ASSERT_NE(menuNode, nullptr);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgUpdatePropertyForElderly001
 * @tc.desc: Test DialogPattern UpdatePropertyForElderly
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgUpdatePropertyForElderly001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogTheme_->minFontScaleForElderly_ = DOUBLEZERO;
    std::vector<ButtonInfo> buttons;
    ButtonInfo buttonInfo = {};
    buttons.emplace_back(buttonInfo);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    pattern->dialogTheme_->dialogLandscapeHeightBoundary_.value_ = pipeline->GetRootHeight() + DIMENSIONVALUE;
    windowManager->windowGetModeCallback_ = []() -> WindowMode { return WindowMode::WINDOW_MODE_SPLIT_PRIMARY; };
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->UpdatePropertyForElderly(buttons);
    EXPECT_TRUE(pattern->notAdapationAging_);

    windowManager->windowGetModeCallback_ = []() -> WindowMode { return WindowMode::WINDOW_MODE_UNDEFINED; };
    pattern->UpdatePropertyForElderly(buttons);
    EXPECT_FALSE(pattern->notAdapationAging_);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgOnWindowSizeChanged001
 * @tc.desc: Test DialogPattern OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgOnWindowSizeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFoldStatusChanged_ = true;
    WindowSizeChangeReason type = WindowSizeChangeReason::RESIZE;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->OnWindowSizeChanged(INTONE, INTONE, type);
    EXPECT_FALSE(pattern->isFoldStatusChanged_);

    pattern->isFoldStatusChanged_ = true;
    type = WindowSizeChangeReason::DRAG;
    pattern->OnWindowSizeChanged(INTONE, INTONE, type);
    EXPECT_FALSE(pattern->isFoldStatusChanged_);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgOnWindowSizeChanged002
 * @tc.desc: Test DialogPattern OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgOnWindowSizeChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isFoldStatusChanged_ = false;
    WindowSizeChangeReason type = WindowSizeChangeReason::RESIZE;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->OnWindowSizeChanged(INTONE, INTONE, type);
    EXPECT_FALSE(pattern->isFoldStatusChanged_);

    pattern->isFoldStatusChanged_ = false;
    type = WindowSizeChangeReason::DRAG;
    pattern->OnWindowSizeChanged(INTONE, INTONE, type);
    EXPECT_FALSE(pattern->isFoldStatusChanged_);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgNeedsButtonDirectionChange001
 * @tc.desc: Test DialogPattern NeedsButtonDirectionChange
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgNeedsButtonDirectionChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->buttonContainer_ =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, INTONE, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(pattern->buttonContainer_, nullptr);
    auto childNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, INTONE, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(childNode, nullptr);
    std::vector<ButtonInfo> buttons;
    ButtonInfo buttonInfoOne = { .text = TITLE };
    ButtonInfo buttonInfoTwo = { .text = TITLE };
    buttons.emplace_back(buttonInfoOne);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_FALSE(pattern->NeedsButtonDirectionChange(buttons));

    buttons.emplace_back(buttonInfoTwo);
    EXPECT_FALSE(pattern->NeedsButtonDirectionChange(buttons));

    childNode->MountToParent(pattern->buttonContainer_);
    EXPECT_FALSE(pattern->NeedsButtonDirectionChange(buttons));
}

/**
 * @tc.name: DialogPatternAdditionalTestNgCreateButton
 * @tc.desc: Test DialogPattern CreateButton
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgCreateButton, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogTheme_->buttonHighlightBgColor_ = Color::BLACK;
    pattern->dialogTheme_->buttonDefaultBgColor_ = Color::GREEN;
    pattern->dialogTheme_->buttonDefaultFontColor_ = Color::BLUE;
    pattern->dialogTheme_->button_type_ = 1;
    ButtonInfo params;
    params.textColor = MESSAGE;
    params.defaultFocus = false;
    params.text = TITLE;
    params.dlgButtonStyle = DialogButtonStyle::DEFAULT;
    params.isPrimary = true;
    std::string msg;
    auto clickCallback = [&msg](GestureEvent& /* info */) { msg = TITLE; };
    params.action = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_EQ(pattern->CreateButton(params, 0), nullptr);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgCheckScrollHeightIsNegative
 * @tc.desc: Test DialogPattern CheckScrollHeightIsNegative
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgCheckScrollHeightIsNegative, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->buttonContainer_ =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, INTONE, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(pattern->buttonContainer_, nullptr);
    DialogProperties Dialogprops;
    ButtonInfo buttonInfo1 = { .text = TITLE };
    ButtonInfo buttonInfo2 = { .text = TITLE };
    Dialogprops.buttons.emplace_back(buttonInfo1);
    RefPtr<UINode> contentColumn = AceType::MakeRefPtr<FrameNode>("node", -1, AceType::MakeRefPtr<Pattern>());
    pattern->buttonContainer_->MountToParent(contentColumn);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_TRUE(Dialogprops.buttons.size() == 1);
    pattern->CheckScrollHeightIsNegative(contentColumn, Dialogprops);

    Dialogprops.buttons.emplace_back(buttonInfo2);
    pattern->buttonContainer_->tag_ = V2::ROW_ETS_TAG;
    EXPECT_TRUE(pattern->buttonContainer_->GetTag() == V2::ROW_ETS_TAG);
    pattern->CheckScrollHeightIsNegative(contentColumn, Dialogprops);

    pattern->buttonContainer_->tag_ = V2::COLUMN_ETS_TAG;
    pattern->isScrollHeightNegative_ = true;
    pattern->CheckScrollHeightIsNegative(contentColumn, Dialogprops);
    EXPECT_TRUE(pattern->notAdapationAging_);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgNeedUpdateHostWindowRect001
 * @tc.desc: Test DialogPattern NeedUpdateHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgNeedUpdateHostWindowRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isUIExtensionSubWindow_ = true;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_FALSE(pattern->NeedUpdateHostWindowRect());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgNeedUpdateHostWindowRect002
 * @tc.desc: Test DialogPattern NeedUpdateHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgNeedUpdateHostWindowRect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isUIExtensionSubWindow_ = true;
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    EXPECT_TRUE(SystemProperties::IsSuperFoldDisplayDevice());
    auto host = frameNode->GetPattern<Pattern>()->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipeline = host->GetContextRefPtr();
    ASSERT_NE(pipeline, nullptr);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pipeline->instanceId_ = 0;
    EXPECT_TRUE(pipeline->GetInstanceId() < MIN_SUBCONTAINER_ID);
    EXPECT_FALSE(pattern->NeedUpdateHostWindowRect());
    pipeline->instanceId_ = MIN_SUBCONTAINER_ID + 1;
    EXPECT_FALSE(pipeline->GetInstanceId() < MIN_SUBCONTAINER_ID);
    AceEngine::Get().AddContainer(pipeline->GetInstanceId(), AceType::MakeRefPtr<MockContainer>());
    auto container = AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(pipeline->instanceId_));
    ASSERT_NE(container, nullptr);
    container->SetDisplayInfo(AceType::MakeRefPtr<DisplayInfo>());
    EXPECT_FALSE(container->GetCurrentFoldStatus() == FoldStatus::HALF_FOLD);
    EXPECT_FALSE(pattern->NeedUpdateHostWindowRect());
    MockContainer::Current()->GetMockDisplayInfo()->foldStatus_ = FoldStatus::HALF_FOLD;
    EXPECT_TRUE(container->GetCurrentFoldStatus() == FoldStatus::HALF_FOLD);
    EXPECT_FALSE(pattern->NeedUpdateHostWindowRect());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgNeedUpdateHostWindowRect003
 * @tc.desc: Test DialogPattern NeedUpdateHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgNeedUpdateHostWindowRect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isUIExtensionSubWindow_ = true;
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_FALSE(pattern->NeedUpdateHostWindowRect());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgGetContentRect
 * @tc.desc: Test DialogPattern GetContentRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgGetContentRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogProperties_.customStyle = true;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    frameNode->SetGeometryNode(geometryNode);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_EQ(pattern->GetContentRect(frameNode), frameNode->GetGeometryNode()->GetFrameRect());

    RefPtr<FrameNode> dialogNode = FrameNode::CreateFrameNode(
        V2::ACTION_SHEET_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(dialogNode, nullptr);
    pattern->customNode_ = dialogNode;
    auto customNode = pattern->customNode_.Upgrade();
    EXPECT_NE(pattern->customNode_.Upgrade(), nullptr);
    auto customContent = AccessibilityManagerNG::DynamicCast<FrameNode>(customNode);
    EXPECT_NE(customContent, nullptr);
    EXPECT_EQ(pattern->GetContentRect(frameNode), frameNode->GetGeometryNode()->GetFrameRect());
}

/**
 * @tc.name: DialogPatternAdditionalTestNgInitHostWindowRect
 * @tc.desc: Test DialogPattern InitHostWindowRect
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgInitHostWindowRect, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->dialogProperties_.isShowInSubWindow = true;
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    EXPECT_FALSE(!pattern->dialogProperties_.isShowInSubWindow);
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    EXPECT_FALSE(container->IsSubContainer());
    container->isUIExtensionWindow_ = true;
    EXPECT_TRUE(container->IsUIExtensionWindow());
    pattern->InitHostWindowRect();
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());
    pattern->InitHostWindowRect();
}

/**
 * @tc.name: DialogPatternAdditionalTestNgIsShowInFreeMultiWindow
 * @tc.desc: Test DialogPattern IsShowInFreeMultiWindow
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgIsShowInFreeMultiWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    MockContainer::container_ = nullptr;
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_EQ(container, nullptr);
    EXPECT_FALSE(pattern->IsShowInFreeMultiWindow());

    MockContainer::SetUp();
    container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());

    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    auto subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_EQ(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFreeMultiWindow());

    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    AceEngine::Get().AddContainer(currentId, container);
    subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_NE(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFreeMultiWindow());
}

/**
 * @tc.name: DialogModelTestNgShowActionSheet001
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogModelTestNgShowActionSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
        .isShowInSubWindow = true,
    };
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    pipeline->SetThemeManager(themeManager);
    ASSERT_NE(pipeline->GetTheme<SelectTheme>(), nullptr);
    theme->expandDisplay_ = true;
    container->isSubContainer_ = false;
    actionSheetModelNg.ShowActionSheet(props);
    container->isSubContainer_ = true;
    actionSheetModelNg.ShowActionSheet(props);
    theme->expandDisplay_ = false;
    actionSheetModelNg.ShowActionSheet(props);
    props.isShowInSubWindow = false;
    actionSheetModelNg.ShowActionSheet(props);
    container->isSubContainer_ = false;
    actionSheetModelNg.ShowActionSheet(props);
    EXPECT_FALSE(SubwindowManager::GetInstance()->GetIsExpandDisplay());
    container->ResetContainer();
}

/**
 * @tc.name: DialogModelTestNgShowActionSheet002
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogModelTestNgShowActionSheet002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
        .isShowInSubWindow = true,
        .dialogLevelMode = LevelMode::EMBEDDED,
        .dialogLevelUniqueId = 0,
    };
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    pipeline->SetThemeManager(themeManager);
    ASSERT_NE(pipeline->GetTheme<SelectTheme>(), nullptr);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    auto containerId = Container::CurrentId();
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    mockSubwindow->isRosenWindowCreate_ = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> dialog = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    EXPECT_CALL(*mockSubwindow, ShowDialogNG(_, _)).WillRepeatedly(Return(dialog));
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).WillRepeatedly(Return(containerId));
    SubwindowManager::GetInstance()->AddSubwindow(containerId, SubwindowType::TYPE_DIALOG, mockSubwindow);
    actionSheetModelNg.ShowActionSheet(props);
    container->isUIExtensionWindow_ = true;
    actionSheetModelNg.ShowActionSheet(props);
    props.isModal = false;
    actionSheetModelNg.ShowActionSheet(props);
    EXPECT_FALSE(SubwindowManager::GetInstance()->GetIsExpandDisplay());
    container->ResetContainer();
    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: DialogModelTestNgShowActionSheet003
 * @tc.desc: Test ActionSheetModelNG's ShowActionSheet.
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogModelTestNgShowActionSheet003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.Mock data.
     */
    bool onWillAppearFlag = false;
    auto onWillAppearEvent = [&onWillAppearFlag]() { onWillAppearFlag = true; };
    bool onDidAppearFlag = false;
    auto onDidAppearEvent = [&onDidAppearFlag]() { onDidAppearFlag = true; };
    bool onWillDisappearFlag = false;
    auto onWillDisappearEvent = [&onWillDisappearFlag]() { onWillDisappearFlag = true; };
    bool onDidDisappearFlag = false;
    auto onDidDisappearEvent = [&onDidDisappearFlag]() { onDidDisappearFlag = true; };
    ActionSheetModelNG actionSheetModelNg;
    DialogProperties props {
        .onWillAppear = std::move(onWillAppearEvent),
        .onDidAppear = std::move(onDidAppearEvent),
        .onWillDisappear = std::move(onWillDisappearEvent),
        .onDidDisappear = std::move(onDidDisappearEvent),
        .isShowInSubWindow = true,
        .dialogLevelMode = LevelMode::EMBEDDED,
        .dialogLevelUniqueId = 0,
    };
    /**
     * @tc.steps: step2. Call ShowActionSheet.
     * @tc.expected: Check ShowActionSheet.
     */
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto theme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    pipeline->SetThemeManager(themeManager);
    ASSERT_NE(pipeline->GetTheme<SelectTheme>(), nullptr);
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();

    auto pipelineContext = container->GetPipelineContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    ASSERT_NE(context, nullptr);

    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(contentNode, nullptr);
    contentNode->onMainTree_ = true;
    ElementRegister::GetInstance()->AddReferenced(props.dialogLevelUniqueId, contentNode);
    auto currentNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::FrameNode>(props.dialogLevelUniqueId);
    ASSERT_NE(currentNode, nullptr);
    auto getOverlayManager = DialogManager::FindPageNodeOverlay(currentNode);
    ASSERT_NE(getOverlayManager, nullptr);

    actionSheetModelNg.ShowActionSheet(props);
    EXPECT_FALSE(SubwindowManager::GetInstance()->GetIsExpandDisplay());
    container->ResetContainer();
    ElementRegister::GetInstance()->Clear();
}

/**
 * @tc.name: DialogPatternAdditionalTestNgUpdateButtonsProperty
 * @tc.desc: Test DialogPattern UpdateButtonsProperty
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgUpdateButtonsProperty, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->buttonContainer_ = nullptr;
    RefPtr<FrameNode> menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 2, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(menuNode, nullptr);
    pattern->menuNode_ = menuNode;
    RefPtr<FrameNode> childNodeOne =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeOne, nullptr);
    RefPtr<FrameNode> childNodeTwo =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeTwo, nullptr);
    RefPtr<FrameNode> childNodeThree =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 5, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeThree, nullptr);
    childNodeOne->MountToParent(menuNode);
    childNodeTwo->MountToParent(menuNode);
    childNodeThree->MountToParent(menuNode);
    RefPtr<FrameNode> childNodeFour =
        FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 6, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(childNodeFour, nullptr);
    childNodeFour->MountToParent(childNodeThree);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    pattern->UpdateButtonsProperty();
    EXPECT_EQ(pattern->buttonContainer_, nullptr);
}

/**
 * @tc.name: DialogPatternAdditionalTestNgIsShowInFloatingWindow
 * @tc.desc: Test DialogPattern IsShowInFloatingWindow
 * @tc.type: FUNC
 */
HWTEST_F(DialogPatternAdditionalTestNg, DialogPatternAdditionalTestNgIsShowInFloatingWindow, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create dialogNode and dialogTheme instance.
     * @tc.expected: The dialogNode and dialogNode created successfully.
     */
    MockSystemProperties::g_isSuperFoldDisplayDevice = true;
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode(
        V2::ALERT_DIALOG_ETS_TAG, 1, AceType::MakeRefPtr<DialogPattern>(dialogTheme, nullptr));
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. Invoke Handle functions.
     * @tc.expected: These Dump properties are matched.
     */
    MockContainer::container_ = nullptr;
    auto container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_EQ(container, nullptr);
    EXPECT_FALSE(pattern->IsShowInFloatingWindow());

    MockContainer::SetUp();
    container = AceType::DynamicCast<MockContainer>(Container::Current());
    ASSERT_NE(container, nullptr);
    container->isSubContainer_ = true;
    EXPECT_TRUE(container->IsSubContainer());
    container->UpdateCurrent(11);

    auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    auto subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_EQ(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFloatingWindow());

    SubwindowManager::GetInstance()->AddParentContainerId(Container::CurrentId(), Container::CurrentId());
    currentId = SubwindowManager::GetInstance()->GetParentContainerId(Container::CurrentId());
    AceEngine::Get().AddContainer(currentId, container);
    subcontainer = AceEngine::Get().GetContainer(currentId);
    ASSERT_NE(subcontainer, nullptr);
    EXPECT_FALSE(pattern->IsShowInFloatingWindow());

    container->ResetContainer();
    MockSystemProperties::g_isSuperFoldDisplayDevice = false;
}
} // namespace OHOS::Ace::NG
