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
const Dimension TEST_STROKEWIDTH_NEGATIVE = -30.0_vp;
const Dimension TEST_STARTMARGIN_NEGATIVE = -30.0_vp;
const Dimension TEST_ENDMARGIN_NEGATIVE = -30.0_vp;
const Dimension TEST_STROKEWIDTH_MAX = 1000.0_vp;
const Dimension TEST_STARTMARGIN_MAX = 1000.0_vp;
const Dimension TEST_ENDMARGIN_MAX = 2000.0_vp;
const Dimension TEST_STROKEWIDTH_10 = 10.0_vp;
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
const float EXCEPT_VALUE = 1.0f;
const double TEST_DIVIDERHEIGHT_DEFAULT = 10.0;
const double TEST_DIVIDERHEIGHT_NEGATIVE = -20.0;
const double TEST_DIVIDERHEIGHT_MAX = 1000.0;
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
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
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
 * @tc.name: TextPickerSetDivider006
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider006, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme6 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme6, TEXT);
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
    ItemDivider divider6;
    divider6.color = Color::BLACK;
    divider6.strokeWidth = TEST_NEEDLINE_ITEM_VALUE_0;
    divider6.startMargin = TEST_NEEDLINE_ITEM_VALUE_0;
    divider6.endMargin = TEST_NEEDLINE_ITEM_VALUE_0;
    TextPickerModelNG::GetInstance()->SetDivider(divider6);

    auto itemDivider6 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider6->color, divider6.color);
    EXPECT_EQ(itemDivider6->strokeWidth, divider6.strokeWidth);
    EXPECT_EQ(itemDivider6->startMargin, divider6.startMargin);
    EXPECT_EQ(itemDivider6->endMargin, divider6.endMargin);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider007
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider007, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme7 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme7, TEXT);
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
    ItemDivider divider7;
    divider7.color = Color::BLACK;
    divider7.strokeWidth = TEST_STROKEWIDTH_MAX;
    divider7.startMargin = TEST_STARTMARGIN_MAX;
    divider7.endMargin = TEST_ENDMARGIN_MAX;
    divider7.isRtl = true;
    TextPickerModelNG::GetInstance()->SetDivider(divider7);

    auto itemDivider7 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider7->color, divider7.color);
    EXPECT_EQ(itemDivider7->strokeWidth, divider7.strokeWidth);
    EXPECT_EQ(itemDivider7->startMargin, divider7.startMargin);
    EXPECT_EQ(itemDivider7->endMargin, divider7.endMargin);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider008
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider008, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme8 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme8, TEXT);
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
    ItemDivider divider8;
    divider8.color = Color::GREEN;
    divider8.strokeWidth = TEST_STROKEWIDTH_NEGATIVE;
    divider8.startMargin = TEST_STARTMARGIN_NEGATIVE;
    divider8.endMargin = TEST_ENDMARGIN_NEGATIVE;
    divider8.isRtl = true;
    TextPickerModelNG::GetInstance()->SetDivider(divider8);
    auto itemDivider8 = textPickerLayoutProperty->GetDivider();

    EXPECT_EQ(itemDivider8->color, divider8.color);
    EXPECT_EQ(itemDivider8->strokeWidth, divider8.strokeWidth);
    EXPECT_EQ(itemDivider8->startMargin, divider8.startMargin);
    EXPECT_EQ(itemDivider8->endMargin, divider8.endMargin);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: TextPickerSetDivider009
 * @tc.desc: Test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, TextPickerSetDivider009, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker framenode and textPickerLayoutProperty.
     */
    auto theme9 = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme9, TEXT);
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
    ItemDivider divider9;
    divider9.color = Color::RED;
    divider9.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    divider9.startMargin = TEST_STARTMARGIN_DEFAULT;
    divider9.endMargin = TEST_ENDMARGIN_DEFAULT;
    divider9.isRtl = true;
    TextPickerModelNG::GetInstance()->SetDivider(divider9);

    auto itemDivider9 = textPickerLayoutProperty->GetDivider();
    EXPECT_EQ(itemDivider9->color, divider9.color);
    EXPECT_EQ(itemDivider9->strokeWidth, divider9.strokeWidth);
    EXPECT_EQ(itemDivider9->startMargin, divider9.startMargin);
    EXPECT_EQ(itemDivider9->endMargin, divider9.endMargin);
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
 * @tc.name: SetStrokeWidth006
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth006, TestSize.Level1)
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
    ItemDivider itemDiv6;
    itemDiv6.color = Color::RED;
    itemDiv6.strokeWidth = TEST_STROKEWIDTH_NEGATIVE;
    itemDiv6.startMargin = TEST_STARTMARGIN_NEGATIVE;
    itemDiv6.endMargin = TEST_ENDMARGIN_NEGATIVE;
    itemDiv6.isRtl = false;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo6;
    divInfo6.startMargin = START_MARGIN_DEFAULT;
    divInfo6.endMargin = END_MARGIN_DEFAULT;
    divInfo6.dividerWidth = DIVIDER_WIDTH_DEFAULT;
    divInfo6.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo6.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo6.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    divInfo6.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv6, dividerHeight, divInfo6);
    EXPECT_FALSE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth007
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth007, TestSize.Level1)
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
    ItemDivider itemDiv7;
    itemDiv7.color = Color::RED;
    itemDiv7.strokeWidth = TEST_STROKEWIDTH_DEFAULT;
    itemDiv7.startMargin = TEST_STARTMARGIN_DEFAULT;
    itemDiv7.endMargin = TEST_ENDMARGIN_DEFAULT;
    itemDiv7.isRtl = false;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo7;
    divInfo7.startMargin = START_MARGIN_NEGATIVE;
    divInfo7.endMargin = END_MARGIN_NEGATIVE;
    divInfo7.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    divInfo7.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    divInfo7.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    divInfo7.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    divInfo7.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv7, dividerHeight, divInfo7);
    EXPECT_TRUE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth008
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth008, TestSize.Level1)
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
    ItemDivider itemDiv8;
    itemDiv8.color = Color::RED;
    itemDiv8.strokeWidth = TEST_STROKEWIDTH_NEGATIVE;
    itemDiv8.startMargin = TEST_STARTMARGIN_NEGATIVE;
    itemDiv8.endMargin = TEST_ENDMARGIN_NEGATIVE;
    itemDiv8.isRtl = false;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo8;
    divInfo8.startMargin = START_MARGIN_NEGATIVE;
    divInfo8.endMargin = END_MARGIN_NEGATIVE;
    divInfo8.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    divInfo8.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    divInfo8.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    divInfo8.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    divInfo8.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv8, dividerHeight, divInfo8);
    EXPECT_FALSE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth009
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth009, TestSize.Level1)
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
    ItemDivider itemDiv9;
    itemDiv9.color = Color::RED;
    itemDiv9.strokeWidth = TEST_STROKEWIDTH_NEGATIVE;
    itemDiv9.startMargin = TEST_STARTMARGIN_NEGATIVE;
    itemDiv9.endMargin = TEST_ENDMARGIN_NEGATIVE;
    itemDiv9.isRtl = true;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo9;
    divInfo9.startMargin = START_MARGIN_DEFAULT;
    divInfo9.endMargin = END_MARGIN_DEFAULT;
    divInfo9.dividerWidth = DIVIDER_WIDTH_DEFAULT;
    divInfo9.dividerLength = DIVIDER_LENGTH_DEFAULT;
    divInfo9.dividerMargin = DIVIDER_MARGIN_DEFAULT;
    divInfo9.dividerHeight = DIVIDER_HEIGHT_DEFAULT;
    divInfo9.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv9, dividerHeight, divInfo9);
    EXPECT_FALSE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}

/**
 * @tc.name: SetStrokeWidth010
 * @tc.desc: Test SetStrokeWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerDividerTestNg, SetStrokeWidth010, TestSize.Level1)
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
    ItemDivider itemDiv10;
    itemDiv10.color = Color::RED;
    itemDiv10.strokeWidth = TEST_STROKEWIDTH_NEGATIVE;
    itemDiv10.startMargin = TEST_STARTMARGIN_NEGATIVE;
    itemDiv10.endMargin = TEST_ENDMARGIN_NEGATIVE;
    itemDiv10.isRtl = true;
    
    /**
     * @tc.steps: step4. set stroke Width and get dividerInfo
     * @tc.expected: setStrokeWidth the result is true
     */
    DividerInfo divInfo10;
    divInfo10.startMargin = START_MARGIN_NEGATIVE;
    divInfo10.endMargin = END_MARGIN_NEGATIVE;
    divInfo10.dividerWidth = DIVIDER_WIDTH_NEGATIVE;
    divInfo10.dividerLength = DIVIDER_LENGTH_NEGATIVE;
    divInfo10.dividerMargin = DIVIDER_MARGIN_NEGATIVE;
    divInfo10.dividerHeight = DIVIDER_HEIGHT_NEGATIVE;
    divInfo10.dividerColor = Color::GRAY;

    auto result = textPickerPaintMethod->SetStrokeWidth(itemDiv10, dividerHeight, divInfo10);
    EXPECT_FALSE(result);

    auto dviderThickness = theme->GetDividerThickness().ConvertToPx();
    EXPECT_EQ(EXCEPT_VALUE, dviderThickness);
    DestroyTextPickerTestNgObject();
}
} // namespace OHOS::Ace::NG