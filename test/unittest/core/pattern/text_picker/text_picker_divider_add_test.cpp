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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_dialog_view.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
Testing::MockCanvas testingCanvas;
const NG::RectF& CONTENTRECT { 1, 1, 1, 1 };
const Dimension TEST_STROKEWIDTH_DEFAULT = 30.0_vp;
const Dimension TEST_STARTMARGIN_DEFAULT = 20.0_vp;
const Dimension TEST_ENDMARGIN_DEFAULT = 30.0_vp;
const Dimension TEST_STROKEWIDTH_10 = 10.0_vp;
const Dimension TEST_STROKEWIDTH_20 = 20.0_vp;
const Dimension TEST_STROKEWIDTH_NEGATIVE_10 = -10.0_vp;
const Dimension TEST_STARTMARGIN_NEGATIVE_20 = -20.0_vp;
const Dimension TEST_ENDMARGIN_NEGATIVE_30 = -30.0_vp;
const Dimension TEST_NEEDLINE_STROKEWIDTH_MAX = 1000.0_vp;
const Dimension TEST_NEEDLINE_STARTMARGIN_MAX = 2000.0_vp;
const Dimension TEST_NEEDLINE_ENDMARGIN_MAX = 3000.0_vp;
const Dimension TEST_NEEDLINE_STROKEWIDTH_VALUE_20 = 20.0_vp;
const Dimension TEST_NEEDLINE_STROKEWIDTH_VALUE_10 = 10.0_vp;
const Dimension TEST_NEEDLINE_ITEM_VALUE_0 = 0.0_vp;
const float START_MARGIN_DEFAULT = 3.0f;
const float END_MARGIN_DEFAULT = 4.0f;
const float DIVIDER_WIDTH_DEFAULT = 5.0f;
const float DIVIDER_LENGTH_DEFAULT = 5.0f;
const float DIVIDER_MARGIN_DEFAULT = 2.0f;
const float DIVIDER_HEIGHT_DEFAULT = 2.0f;
const float START_MARGIN_NEGATIVE = -1.0f;
const float END_MARGIN_NEGATIVE = -3.0f;
const float DIVIDER_WIDTH_NEGATIVE = -2.0f;
const float DIVIDER_LENGTH_NEGATIVE = -4.0f;
const float DIVIDER_MARGIN_NEGATIVE = -6.0f;
const float DIVIDER_HEIGHT_NEGATIVE = -1.0f;
const float START_MARGIN_MAX = 3000;
const float END_MARGIN_MAX = 5000;
const float DIVIDER_WIDTH_MAX = 2000;
const float DIVIDER_LENGTH_MAX = 4000;
const float DIVIDER_MARGIN_MAX = 2000;
const float DIVIDER_HEIGHT_MAX = 5000;
const float TEST_NEEDLINE_INFO_VALUE_0 = 0.0;
const double TEST_DIVIDERHEIGHT_DEFAULT = 10.0;
const double DIVIDERWIDTH_VALUE = 1.0;
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}
} // namespace

class TextPickerDividerAddTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerTestNg();
    void DestroyTextPickerTestNgObject();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextPickerPattern> textPickerPattern_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityProperty_;
    RefPtr<TextPickerRowAccessibilityProperty> textPickerRowAccessibilityProperty_;
    RefPtr<FrameNode> stackNode_;
    RefPtr<FrameNode> blendNode_;
    RefPtr<FrameNode> columnNode_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPattern_;
    RefPtr<FrameNode> stackNodeNext_;
    RefPtr<FrameNode> blendNodeNext_;
    RefPtr<FrameNode> columnNodeNext_;
    RefPtr<TextPickerColumnPattern> textPickerColumnPatternNext_;
    RefPtr<TextPickerAccessibilityProperty> textPickerAccessibilityPropertyNext_;
};

void TextPickerDividerAddTestNg::DestroyTextPickerTestNgObject()
{
    frameNode_ = nullptr;
    textPickerPattern_ = nullptr;
    textPickerAccessibilityProperty_ = nullptr;
    textPickerRowAccessibilityProperty_ = nullptr;
    stackNode_ = nullptr;
    blendNode_ = nullptr;
    columnNode_ = nullptr;
    textPickerColumnPattern_ = nullptr;
    stackNodeNext_ = nullptr;
    blendNodeNext_ = nullptr;
    columnNodeNext_ = nullptr;
    textPickerColumnPatternNext_ = nullptr;
    textPickerAccessibilityPropertyNext_ = nullptr;
}

void TextPickerDividerAddTestNg::InitTextPickerTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode_, nullptr);
    textPickerRowAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextPickerRowAccessibilityProperty>();
    ASSERT_NE(textPickerRowAccessibilityProperty_, nullptr);
    textPickerPattern_ = frameNode_->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern_, nullptr);
    stackNode_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode_, nullptr);
    blendNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode_, nullptr);
    columnNode_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode_, nullptr);
    textPickerAccessibilityProperty_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityProperty_, nullptr);
    textPickerColumnPattern_ = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern_, nullptr);
    columnNode_->MountToParent(blendNode_);
    blendNode_->MountToParent(stackNode_);
    stackNode_->MountToParent(frameNode_);

    stackNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNodeNext_, nullptr);
    blendNodeNext_ = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNodeNext_, nullptr);
    columnNodeNext_ =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNodeNext_, nullptr);
    textPickerAccessibilityPropertyNext_ = columnNode_->GetAccessibilityProperty<TextPickerAccessibilityProperty>();
    ASSERT_NE(textPickerAccessibilityPropertyNext_, nullptr);
    textPickerColumnPatternNext_ = columnNodeNext_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPatternNext_, nullptr);
    columnNodeNext_->MountToParent(blendNodeNext_);
    blendNodeNext_->MountToParent(stackNodeNext_);
    stackNodeNext_->MountToParent(frameNode_);
}

void TextPickerDividerAddTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerDividerAddTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerDividerAddTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerDividerAddTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: NeedPaintDividerLines001
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines001, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick1 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick1, TEXT);
    themePick1->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider;
    itemDivider.strokeWidth = TEST_STROKEWIDTH_10;
    
    /**
     * @tc.steps: step2. set the dividerInfo
     * @tc.expected: strokeWidth is equal to value was set
     */
    DividerInfo dividerInfo;
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;
    dividerInfo.startMargin = START_MARGIN_DEFAULT;
    dividerInfo.endMargin = END_MARGIN_DEFAULT;
    dividerInfo.dividerWidth = DIVIDER_WIDTH_DEFAULT;
    dividerInfo.dividerLength = DIVIDER_LENGTH_DEFAULT;
    dividerInfo.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    dividerInfo.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    dividerInfo.dividerColor = Color::RED;
    RectF contentRect;
    contentRect.SetWidth(10.0);

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDivider, dividerHeight, dividerInfo);
    EXPECT_TRUE(result);
    
    /**
     * @tc.steps: step3. set dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto temp = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider, dividerHeight, dividerInfo);
    EXPECT_TRUE(temp);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines002
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines002, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick2 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick2, TEXT);
    themePick2->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider2;
    itemDivider2.strokeWidth = TEST_STROKEWIDTH_10;
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;
    DividerInfo dividerInfo2;

    /**
     * @tc.steps: step2. set the dividerInfo
     * @tc.expected: strokeWidth  the result is true
     */
    dividerInfo2.startMargin = START_MARGIN_NEGATIVE;
    dividerInfo2.endMargin = END_MARGIN_NEGATIVE;
    dividerInfo2.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    dividerInfo2.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    dividerInfo2.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    dividerInfo2.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    dividerInfo2.dividerColor = Color::GREEN;
    RectF contentRect;
    contentRect.SetWidth(2.0);

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider2, dividerHeight, dividerInfo2);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.steps: step3. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider2, dividerHeight, dividerInfo2);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines003
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines003, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick3 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick3, TEXT);
    themePick3->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider3;
    itemDivider3.strokeWidth = TEST_STROKEWIDTH_20;
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;

    /**
     * @tc.steps: step2. set the dividerInfo
     * @tc.expected: strokeWidth the result is true
     */
    DividerInfo dividerInfo3;
    dividerInfo3.startMargin = START_MARGIN_MAX;
    dividerInfo3.endMargin = END_MARGIN_MAX;
    dividerInfo3.dividerWidth = DIVIDER_WIDTH_MAX;
    dividerInfo3.dividerLength = DIVIDER_LENGTH_MAX;
    dividerInfo3.dividerMargin = DIVIDER_MARGIN_MAX;
    dividerInfo3.dividerHeight = DIVIDER_HEIGHT_MAX;
    dividerInfo3.dividerColor = Color::RED;
    RectF contentRect;
    contentRect.SetWidth(10.0);

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider3, dividerHeight, dividerInfo3);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step3. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider3, dividerHeight, dividerInfo3);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines004
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines004, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick4 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick4, TEXT);
    themePick4->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider4;

    /**
     * @tc.steps: step2. set the itemDivider
     * @tc.expected: strokeWidth the result is true
     */
    itemDivider4.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    itemDivider4.startMargin = TEST_STARTMARGIN_DEFAULT;
    itemDivider4.endMargin = TEST_ENDMARGIN_DEFAULT;
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;
    DividerInfo dividerInfo4;
    dividerInfo4.dividerColor = Color::RED;
    RectF contentRect;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider4, dividerHeight, dividerInfo4);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step3. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider4, dividerHeight, dividerInfo4);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines005
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines005, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick5 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick5, TEXT);
    themePick5->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider5;

    /**
     * @tc.steps: step2. set the itemDivider
     * @tc.expected: strokeWidth the result is false
     */
    itemDivider5.strokeWidth = TEST_STROKEWIDTH_NEGATIVE_10;
    itemDivider5.startMargin = TEST_STARTMARGIN_NEGATIVE_20;
    itemDivider5.endMargin = TEST_ENDMARGIN_NEGATIVE_30;
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;
    DividerInfo dividerInfo5;
    dividerInfo5.dividerWidth = DIVIDERWIDTH_VALUE;
    dividerInfo5.dividerColor = Color::RED;
    RectF contentRect;
    contentRect.SetWidth(20.0);

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider5, dividerHeight, dividerInfo5);
    EXPECT_EQ(temp, false);
    
    /**
     * @tc.step: step3. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is false
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider5, dividerHeight, dividerInfo5);
    EXPECT_EQ(result, false);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines006
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines006, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick6 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick6, TEXT);
    themePick6->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);

    /**
     * @tc.steps: step2. set the itemDivider
     * @tc.expected: strokeWidth the result is true
     */
    ItemDivider itemDivider6;
    itemDivider6.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_MAX;
    itemDivider6.startMargin = TEST_NEEDLINE_STARTMARGIN_MAX;
    itemDivider6.endMargin = TEST_NEEDLINE_ENDMARGIN_MAX;
    double dividerHeight = 10;
    DividerInfo dividerInfo6;
    dividerInfo6.dividerColor = Color::GREEN;
    RectF contentRect;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider6, dividerHeight, dividerInfo6);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step3. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider6, dividerHeight, dividerInfo6);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines007
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines007, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick7 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick7, TEXT);
    themePick7->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider7;
    itemDivider7.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 1.0;
    DividerInfo dividerInfo7;
    dividerInfo7.dividerColor = Color::TRANSPARENT;
    RectF contentRect;
    contentRect.SetWidth(20.0);
    itemDivider7.isRtl = true;

    /**
     * @tc.expected: SetStrokeWidth the result is true
     */
    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider7, dividerHeight, dividerInfo7);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider7, dividerHeight, dividerInfo7);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines008
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines008, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick8 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick8, TEXT);
    themePick8->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider8;
    itemDivider8.strokeWidth = 20.0_vp;
    double dividerHeight = 5;
    DividerInfo dividerInfo8;
    dividerInfo8.dividerColor = Color::BLUE;
    RectF contentRect;
    contentRect.SetWidth(20.0);
    itemDivider8.isRtl = false;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider8, dividerHeight, dividerInfo8);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider8, dividerHeight, dividerInfo8);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines009
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines009, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick9 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick9, TEXT);
    themePick9->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider9;
    itemDivider9.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_10;
    double dividerHeight = 0;
    DividerInfo dividerInfo9;
    dividerInfo9.dividerColor = Color::TRANSPARENT;
    RectF contentRect;
    contentRect.SetWidth(10.0);

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider9, dividerHeight, dividerInfo9);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result = textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider9, dividerHeight, dividerInfo9);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines010
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines0010, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick10 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick10, TEXT);
    themePick10->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider10;
    double dividerHeight = -30;
    DividerInfo dividerInfo10;
    dividerInfo10.dividerColor = Color::FOREGROUND;
    RectF contentRect;
    contentRect.SetWidth(10.0);

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider10, dividerHeight, dividerInfo10);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider10, dividerHeight, dividerInfo10);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines011
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines011, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick11 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick11, TEXT);
    themePick11->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider11;
    double dividerHeight = 5000;
    DividerInfo dividerInfo11;
    dividerInfo11.dividerColor = Color::TRANSPARENT;
    RectF contentRect;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider11, dividerHeight, dividerInfo11);
    EXPECT_EQ(temp, false);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is false
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider11, dividerHeight, dividerInfo11);
    EXPECT_EQ(result, false);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines012
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines012, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick12 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick12, TEXT);
    themePick12->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider12;
    itemDivider12.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo12;
    dividerInfo12.dividerColor = Color::BLUE;
    RectF contentRect;
    contentRect.SetWidth(0);
    contentRect.SetHeight(0);

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider12, dividerHeight, dividerInfo12);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is false
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider12, dividerHeight, dividerInfo12);
    EXPECT_EQ(result, false);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines013
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines013, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick13 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick13, TEXT);
    themePick13->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);

    ItemDivider itemDivider13;
    itemDivider13.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo13;
    dividerInfo13.dividerColor = Color::WHITE;
    RectF contentRect;
    contentRect.SetWidth(5000);
    contentRect.SetHeight(5000);
    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider13, dividerHeight, dividerInfo13);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider13, dividerHeight, dividerInfo13);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines014
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines014, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick14 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick14, TEXT);
    themePick14->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider14;
    itemDivider14.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo14;
    dividerInfo14.dividerColor = Color::GRAY;
    RectF contentRect;
    contentRect.SetWidth(-20);
    contentRect.SetHeight(-30);
    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider14, dividerHeight, dividerInfo14);
    EXPECT_TRUE(temp);

    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider14, dividerHeight, dividerInfo14);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines015
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines015, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick15 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick15, TEXT);
    themePick15->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider15;
    itemDivider15.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo15;
    dividerInfo15.dividerColor = Color::GRAY;
    RectF contentRect;
    contentRect.SetWidth(10);
    itemDivider15.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider15, dividerHeight, dividerInfo15);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider15, dividerHeight, dividerInfo15);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines016
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines016, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick16 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick16, TEXT);
    themePick16->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider16;
    itemDivider16.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo16;
    dividerInfo16.dividerColor = Color::RED;
    RectF contentRect;
    contentRect.SetWidth(20);
    itemDivider16.isRtl = false;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider16, dividerHeight, dividerInfo16);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider16, dividerHeight, dividerInfo16);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines017, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick17 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick17, TEXT);
    themePick17->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider17;
    itemDivider17.strokeWidth = TEST_NEEDLINE_ITEM_VALUE_0;
    itemDivider17.startMargin = TEST_NEEDLINE_ITEM_VALUE_0;
    itemDivider17.endMargin = TEST_NEEDLINE_ITEM_VALUE_0;
    double dividerHeight = 0;
    DividerInfo dividerInfo17;
    dividerInfo17.startMargin = TEST_NEEDLINE_INFO_VALUE_0;
    dividerInfo17.endMargin = TEST_NEEDLINE_INFO_VALUE_0;
    dividerInfo17.dividerWidth = TEST_NEEDLINE_INFO_VALUE_0;
    dividerInfo17.dividerLength = TEST_NEEDLINE_INFO_VALUE_0;
    dividerInfo17.dividerMargin = TEST_NEEDLINE_INFO_VALUE_0;
    dividerInfo17.dividerHeight = TEST_NEEDLINE_INFO_VALUE_0;
    dividerInfo17.dividerColor = Color::GRAY;
    RectF contentRect;
    contentRect.SetWidth(0);
    contentRect.SetHeight(0);
    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider17, dividerHeight, dividerInfo17);
    EXPECT_FALSE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and set dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is false
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider17, dividerHeight, dividerInfo17);
    EXPECT_FALSE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines018
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines018, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick18 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick18, TEXT);
    themePick18->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider18;
    itemDivider18.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = -300;
    DividerInfo dividerInfo18;
    dividerInfo18.dividerColor = Color::GRAY;
    RectF contentRect;
    contentRect.SetWidth(10);
    itemDivider18.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider18, dividerHeight, dividerInfo18);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider18, dividerHeight, dividerInfo18);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines019
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines019, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick19 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick19, TEXT);
    themePick19->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider19;
    itemDivider19.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo19;
    dividerInfo19.startMargin = START_MARGIN_NEGATIVE;
    dividerInfo19.endMargin = END_MARGIN_NEGATIVE;
    dividerInfo19.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    dividerInfo19.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    dividerInfo19.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    dividerInfo19.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    dividerInfo19.dividerColor = Color::GRAY;
    RectF contentRect;
    contentRect.SetWidth(10);
    itemDivider19.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider19, dividerHeight, dividerInfo19);
    EXPECT_TRUE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider19, dividerHeight, dividerInfo19);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines020
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines020, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick20 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick20, TEXT);
    themePick20->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider20;
    itemDivider20.strokeWidth = TEST_NEEDLINE_STROKEWIDTH_VALUE_20;
    double dividerHeight = 10;
    DividerInfo dividerInfo18;
    dividerInfo18.dividerColor = Color::GRAY;
    RectF contentRect;
    contentRect.SetWidth(10);
    itemDivider20.strokeWidth = TEST_STROKEWIDTH_NEGATIVE_10;
    itemDivider20.startMargin = TEST_STARTMARGIN_NEGATIVE_20;
    itemDivider20.endMargin = TEST_ENDMARGIN_NEGATIVE_30;
    itemDivider20.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider20, dividerHeight, dividerInfo18);
    EXPECT_FALSE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider20, dividerHeight, dividerInfo18);
    EXPECT_FALSE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines021
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines021, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick21 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick21, TEXT);
    themePick21->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider21;
    double dividerHeight = 10;
    DividerInfo dividerInfo21;
    dividerInfo21.dividerColor = Color::GRAY;
    dividerInfo21.startMargin = START_MARGIN_NEGATIVE;
    dividerInfo21.endMargin = END_MARGIN_NEGATIVE;
    dividerInfo21.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    dividerInfo21.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    dividerInfo21.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    dividerInfo21.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    RectF contentRect;
    contentRect.SetWidth(10);
    itemDivider21.strokeWidth = TEST_STROKEWIDTH_NEGATIVE_10;
    itemDivider21.startMargin = TEST_STARTMARGIN_NEGATIVE_20;
    itemDivider21.endMargin = TEST_ENDMARGIN_NEGATIVE_30;
    itemDivider21.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider21, dividerHeight, dividerInfo21);
    EXPECT_FALSE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider21, dividerHeight, dividerInfo21);
    EXPECT_FALSE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines022
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines022, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick22 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick22, TEXT);
    themePick22->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider22;
    double dividerHeight = -10;
    DividerInfo dividerInfo22;
    dividerInfo22.dividerColor = Color::GRAY;
    dividerInfo22.startMargin = START_MARGIN_NEGATIVE;
    dividerInfo22.endMargin = END_MARGIN_NEGATIVE;
    dividerInfo22.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    dividerInfo22.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    dividerInfo22.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    dividerInfo22.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    RectF contentRect;
    contentRect.SetWidth(10);
    itemDivider22.strokeWidth = TEST_STROKEWIDTH_NEGATIVE_10;
    itemDivider22.startMargin = TEST_STARTMARGIN_NEGATIVE_20;
    itemDivider22.endMargin = TEST_ENDMARGIN_NEGATIVE_30;
    itemDivider22.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider22, dividerHeight, dividerInfo22);
    EXPECT_FALSE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider22, dividerHeight, dividerInfo22);
    EXPECT_FALSE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines023
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerAddTestNg, NeedPaintDividerLines023, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto themePick23 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(themePick23, TEXT);
    themePick23->gradientHeight_ = Dimension(10.0);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);
    ItemDivider itemDivider23;
    double dividerHeight = -10;
    DividerInfo dividerInfo23;
    dividerInfo23.dividerColor = Color::GRAY;
    dividerInfo23.startMargin = START_MARGIN_NEGATIVE;
    dividerInfo23.endMargin = END_MARGIN_NEGATIVE;
    dividerInfo23.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    dividerInfo23.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    dividerInfo23.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    dividerInfo23.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    RectF contentRect;
    contentRect.SetWidth(-10);
    itemDivider23.strokeWidth = TEST_STROKEWIDTH_NEGATIVE_10;
    itemDivider23.startMargin = TEST_STARTMARGIN_NEGATIVE_20;
    itemDivider23.endMargin = TEST_ENDMARGIN_NEGATIVE_30;
    itemDivider23.isRtl = true;

    auto temp = textPickerPaintMethod->SetStrokeWidth(itemDivider23, dividerHeight, dividerInfo23);
    EXPECT_FALSE(temp);
    
    /**
     * @tc.step: step2. set stroke Width and get dividerInfo
     * @tc.expected: NeedPaintDividerLines the result is true
     */
    auto result =
        textPickerPaintMethod->NeedPaintDividerLines(contentRect, itemDivider23, dividerHeight, dividerInfo23);
    EXPECT_FALSE(result);
    DestroyTextPickerTestNgObject();
}
} // namespace OHOS::Ace::NG