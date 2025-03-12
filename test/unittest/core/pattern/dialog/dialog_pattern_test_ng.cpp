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

#include "base/utils/singleton.h"
#include "core/pipeline/base/constants.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/log/dump_log.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"
#include "core/components_ng/pattern/dialog/alert_dialog_model_ng.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const double DIMENSIONVALUE = 1.0;
const std::string TITLE = "title";
const std::string SUBTITLE = "subtitle";
const std::string MESSAGE = "hello world";
const CalcDimension WIDTHDIMENSION = CalcDimension(DIMENSIONVALUE);
const CalcDimension HEIGHTDIMENSION = CalcDimension(DIMENSIONVALUE);
const int32_t BACKGROUNDBLURSTYLEZERO = 0;
const int32_t BACKGROUNDBLURSTYLE = 1;
const NG::BorderWidthProperty BORDERWIDTH = { .leftDimen = Dimension(DIMENSIONVALUE) };
const BorderColorProperty BORDERCOLOR = { .bottomColor = Color::WHITE };
const Color COLOR = Color::WHITE;
const NG::BorderRadiusProperty BORDERRADIUS = BorderRadiusProperty(Dimension(DIMENSIONVALUE));
} // namespace

class DialogPatternAdditionalTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

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
    pattern->dialogProperties_.isScenceBoardDialog = false;
    pattern->dialogProperties_.isSysBlurStyle = false;
    pattern->dialogProperties_.isShowInSubWindow = false;
    pattern->DumpSimplifyBoolProperty(jsonPtr);
    EXPECT_FALSE(jsonPtr->Contains("AutoCancel"));
    EXPECT_FALSE(jsonPtr->Contains("CustomStyle"));
    EXPECT_FALSE(jsonPtr->Contains("IsMenu"));
    EXPECT_FALSE(jsonPtr->Contains("IsMask"));
    EXPECT_FALSE(jsonPtr->Contains("IsModal"));
    EXPECT_FALSE(jsonPtr->Contains("IsScenceBoardDialog"));
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
    pattern->dialogProperties_.isScenceBoardDialog = true;
    pattern->dialogProperties_.isSysBlurStyle = true;
    pattern->dialogProperties_.isShowInSubWindow = true;
    pattern->DumpSimplifyBoolProperty(jsonPtr);
    EXPECT_TRUE(jsonPtr->Contains("AutoCancel"));
    EXPECT_TRUE(jsonPtr->Contains("CustomStyle"));
    EXPECT_TRUE(jsonPtr->Contains("IsMenu"));
    EXPECT_TRUE(jsonPtr->Contains("IsMask"));
    EXPECT_TRUE(jsonPtr->Contains("IsModal"));
    EXPECT_TRUE(jsonPtr->Contains("IsScenceBoardDialog"));
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
} // namespace OHOS::Ace::NG