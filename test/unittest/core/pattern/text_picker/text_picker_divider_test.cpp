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
#include <securec.h>

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
const Dimension TEST_STROKEWIDTH_NEGATIVE = -30.0_vp;
const Dimension TEST_STARTMARGIN_NEGATIVE = -30.0_vp;
const Dimension TEST_ENDMARGIN_NEGATIVE = -30.0_vp;
const Dimension TEST_STROKEWIDTH_MAX = 1000.0_vp;
const Dimension TEST_STARTMARGIN_MAX = 1000.0_vp;
const Dimension TEST_ENDMARGIN_MAX = 2000.0_vp;
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
const float DIVIDER_HEIGHT_NEGATIVE_1 = 1.0f;
const float START_MARGIN_MAX = 3000;
const float END_MARGIN_MAX = 5000;
const float DIVIDER_WIDTH_MAX = 2000;
const float DIVIDER_LENGTH_MAX = 4000;
const float DIVIDER_MARGIN_MAX = 2000;
const float DIVIDER_HEIGHT_MAX = 5000;
const float EXCEPT_VALUE = 1.0f;
const float TEST_NEEDLINE_INFO_VALUE_0 = 0.0;
const double TEST_DIVIDERHEIGHT_DEFAULT = 10.0;
const double TEST_DIVIDERHEIGHT_NEGATIVE = -20.0;
const double TEST_DIVIDERHEIGHT_MAX = 1000.0;
const double DIVIDERWIDTH_VALUE = 1.0;
} // namespace

class TextPickerDividerTestNg : public testing::Test {
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

void TextPickerDividerTestNg::DestroyTextPickerTestNgObject()
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

void TextPickerDividerTestNg::InitTextPickerTestNg()
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

void TextPickerDividerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerDividerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerDividerTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else if (type == PickerTheme::TypeId()) {
            return MockThemeDefault::GetPickerTheme();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerDividerTestNg::TearDown()
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
 * @tc.name: TextPickerSetDivider001
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme1 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme1, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    
    /**
     * @tc.steps: step2. test method setDivider
     * @tc.expected: divider is set as expected
     */
    ItemDivider divider1;
    divider1.color = Color::RED;
    divider1.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    divider1.startMargin = TEST_STARTMARGIN_DEFAULT;
    divider1.endMargin = TEST_ENDMARGIN_DEFAULT;
    TextPickerModelNG::GetInstance()->SetDivider(divider1);

    auto itemDivider1 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider1->color, divider1.color);
    EXPECT_EQ(itemDivider1->strokeWidth, divider1.strokeWidth);
    EXPECT_EQ(itemDivider1->startMargin, divider1.startMargin);
    EXPECT_EQ(itemDivider1->endMargin, divider1.endMargin);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider002
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme2 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme2, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    
    /**
     * @tc.steps: step2. test method setDivider
     * @tc.expected: divider is set as expected
     */
    ItemDivider divider2;
    divider2.color = Color::GREEN;
    divider2.strokeWidth = TEST_STROKEWIDTH_NEGATIVE;
    divider2.startMargin = TEST_STARTMARGIN_NEGATIVE;
    divider2.endMargin = TEST_ENDMARGIN_NEGATIVE;
    TextPickerModelNG::GetInstance()->SetDivider(divider2);
    auto itemDivider2 = textPickerLayoutProperty->GetDivider();

    EXPECT_EQ(itemDivider2->color, divider2.color);
    EXPECT_EQ(itemDivider2->strokeWidth, divider2.strokeWidth);
    EXPECT_EQ(itemDivider2->startMargin, divider2.startMargin);
    EXPECT_EQ(itemDivider2->endMargin, divider2.endMargin);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider003
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme3 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme3, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    
    /**
     * @tc.steps: step2. test method setDivider
     * @tc.expected: divider is set as expected
     */
    ItemDivider divider3;
    divider3.color = Color::BLACK;
    divider3.strokeWidth = TEST_STROKEWIDTH_MAX;
    divider3.startMargin = TEST_STARTMARGIN_MAX;
    divider3.endMargin = TEST_ENDMARGIN_MAX;
    TextPickerModelNG::GetInstance()->SetDivider(divider3);

    auto itemDivider3 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider3->color, divider3.color);
    EXPECT_EQ(itemDivider3->strokeWidth, divider3.strokeWidth);
    EXPECT_EQ(itemDivider3->startMargin, divider3.startMargin);
    EXPECT_EQ(itemDivider3->endMargin, divider3.endMargin);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider004
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme4 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme4, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    
    /**
     * @tc.steps: step2. test method setDivider
     * @tc.expected: divider is set as expected
     */
    ItemDivider divider4;
    divider4.color = Color::BLACK;
    divider4.isRtl = true;
    TextPickerModelNG::GetInstance()->SetDivider(divider4);

    auto itemDivider4 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider4->color, divider4.color);
    EXPECT_EQ(itemDivider4->strokeWidth, divider4.strokeWidth);
    EXPECT_EQ(itemDivider4->startMargin, divider4.startMargin);
    EXPECT_EQ(itemDivider4->endMargin, divider4.endMargin);
    EXPECT_EQ(itemDivider4->isRtl, divider4.isRtl);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider005
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider005, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme5 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme5, TEXT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    /**
     * @tc.steps: step2. test method setDivider
     * @tc.expected: divider is set as expected
     */
    ItemDivider divider5;
    divider5.color = Color::BLACK;
    divider5.isRtl = false;
    TextPickerModelNG::GetInstance()->SetDivider(divider5);

    auto itemDivider5 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider5->color, divider5.color);
    EXPECT_EQ(itemDivider5->strokeWidth, divider5.strokeWidth);
    EXPECT_EQ(itemDivider5->startMargin, divider5.startMargin);
    EXPECT_EQ(itemDivider5->endMargin, divider5.endMargin);
    EXPECT_EQ(itemDivider5->isRtl, divider5.isRtl);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth001
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth001, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrentContext()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
     * @tc.steps: step2. set dividerHeight value,
     */
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;

    /**
     * @tc.steps: step3. set divier stroke width, the width is over dividerHeight/2
     */
    ItemDivider itemDiv1;
    itemDiv1.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    itemDiv1.startMargin = TEST_STARTMARGIN_DEFAULT;
    itemDiv1.endMargin = TEST_ENDMARGIN_DEFAULT;
    itemDiv1.color = Color::TRANSPARENT;

    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo1;
    divInfo1.startMargin = START_MARGIN_DEFAULT;
    divInfo1.endMargin = END_MARGIN_DEFAULT;
    divInfo1.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo1.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo1.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    divInfo1.dividerColor = Color::RED;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv1, dividerHeight, divInfo1);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step5. check the dividerInfo
     * @tc.expected: strokeWidth is equal to the dividerThickness of theme
     */
    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(divInfo1.dividerWidth, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth002
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth002, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrentContext()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
     * @tc.steps: step2. set dividerHeight value,
     */
    double dividerHeight = TEST_DIVIDERHEIGHT_MAX;

    /**
     * @tc.steps: step3. set divier stroke width, the width is less than dividerHeight/2
     */
    ItemDivider itemDiv2;
    itemDiv2.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    itemDiv2.startMargin = TEST_STARTMARGIN_DEFAULT;
    itemDiv2.endMargin = TEST_ENDMARGIN_DEFAULT;
    itemDiv2.color = Color::RED;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     */
    DividerInfo divInfo2;
    divInfo2.startMargin = START_MARGIN_DEFAULT;
    divInfo2.endMargin = END_MARGIN_DEFAULT;
    divInfo2.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo2.dividerWidth = DIVIDER_HEIGHT_NEGATIVE_1;
    divInfo2.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo2.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    divInfo2.dividerColor = Color::RED;
    /**
     * @tc.steps: step5. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv2, dividerHeight, divInfo2);
    EXPECT_TRUE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth003
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth003, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrentContext()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
     * @tc.steps: step2. set dividerHeight value,
     */
    double dividerHeight = TEST_DIVIDERHEIGHT_NEGATIVE;

    /**
     * @tc.steps: step3. set divier stroke width
     */
    ItemDivider itemDiv3;
    itemDiv3.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    itemDiv3.startMargin = TEST_STARTMARGIN_DEFAULT;
    itemDiv3.endMargin = TEST_ENDMARGIN_DEFAULT;
    itemDiv3.color = Color::RED;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo3;
    divInfo3.startMargin = START_MARGIN_DEFAULT;
    divInfo3.endMargin = END_MARGIN_DEFAULT;
    divInfo3.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo3.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo3.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    divInfo3.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv3, dividerHeight, divInfo3);
    EXPECT_TRUE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth004
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth004, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrentContext()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerPaintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(pickerPaintProperty, nullptr);
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto textPickerPaintMethod =
        AceType::MakeRefPtr<TextPickerPaintMethod>(AceType::WeakClaim(AceType::RawPtr(textPickerPattern)));
    ASSERT_NE(textPickerPaintMethod, nullptr);

    /**
     * @tc.steps: step2. set dividerHeight value,
     */
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;

    /**
     * @tc.steps: step3. set divier stroke width
     */
    ItemDivider itemDiv4;
    itemDiv4.color = Color::RED;
    itemDiv4.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    itemDiv4.isRtl = true;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo4;
    divInfo4.startMargin = START_MARGIN_DEFAULT;
    divInfo4.endMargin = END_MARGIN_DEFAULT;
    divInfo4.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo4.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo4.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    divInfo4.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv4, dividerHeight, divInfo4);
    EXPECT_TRUE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth005
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth005, TestSize.Level1)
{
    /**
     * @tc.step: step1. get TextPickerPaintMethod RefPtr.
     */
    auto theme = MockPipelineContext::GetCurrentContext()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
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
     * @tc.steps: step2. set dividerHeight value,
     */
    double dividerHeight = TEST_DIVIDERHEIGHT_DEFAULT;

    /**
     * @tc.steps: step3. set divier stroke width, the width is less than dividerHeight/2
     */
    ItemDivider itemDiv5;
    itemDiv5.color = Color::WHITE;
    itemDiv5.strokeWidth = TEST_STROKEWIDTH_10;
    itemDiv5.isRtl = false;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo5;
    divInfo5.dividerColor = Color::WHITE;
    divInfo5.startMargin = START_MARGIN_DEFAULT;
    divInfo5.endMargin = END_MARGIN_DEFAULT;
    divInfo5.dividerWidth = DIVIDER_WIDTH_DEFAULT;
    divInfo5.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo5.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo5.dividerHeight = DIVIDER_HEIGHT_DEFAULT;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv5, dividerHeight, divInfo5);
    EXPECT_TRUE(result);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: NeedPaintDividerLines001
 * @tc.desc: Test NeedPaintDividerLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines001, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines002, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines003, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines004, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines005, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines006, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines007, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines008, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines009, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines0010, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines011, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines012, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines013, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines014, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines015, TestSize.Level1)
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
HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines016, TestSize.Level1)
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

HWTEST_F(TextPickerDividerTestNg, NeedPaintDividerLines017, TestSize.Level1)
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

} // namespace OHOS::Ace::NG