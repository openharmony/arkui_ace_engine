/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

class TextPickerGradientHeightTestNg : public testing::Test {
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

void TextPickerGradientHeightTestNg::DestroyTextPickerTestNgObject()
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

void TextPickerGradientHeightTestNg::InitTextPickerTestNg()
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

void TextPickerGradientHeightTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerGradientHeightTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerGradientHeightTestNg::SetUp()
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

void TextPickerGradientHeightTestNg::TearDown()
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
 * @tc.name: TextPickerModelNGSetGradientHeight003
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight003, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(10.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight004
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight004, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(100.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight005
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight005, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.5f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight006
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight006, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(36.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight007
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight007, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1000000.0f, DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight008
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight008, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("10.0f", DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight009
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight009, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("-1.0f", DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight010
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight010, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("1000000.0f", DimensionUnit::PX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight011
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight011, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight012
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight012, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight013
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight013, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(10.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight014
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight014, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(100.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight015
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight015, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(-1.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight016
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight016, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(36.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight017
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight017, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1000000.0f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight018
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight018, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("10.0f", DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight019
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight019, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("-1.0f", DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight020
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight020, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("1000000.0f", DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight021
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight021, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight022
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight022, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight023
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight023, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(10.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight024
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight024, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(100.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight025
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight025, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(-1.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight026
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight026, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(36.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight027
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight027, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1000000.0f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight028
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight028, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("10.0f", DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight029
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight029, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("-1.0f", DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight030
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight030, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("1000000.0f", DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight031
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight031, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight032
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight032, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight033
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight033, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(10.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight034
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight034, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(100.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight035
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight035, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(-1.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight036
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight036, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(36.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight037
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight037, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1000000.0f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight038
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight038, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("10.0f", DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight039
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight039, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("-1.0f", DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight040
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight040, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("1000000.0f", DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight041
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight041, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.0f, DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight042
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight042, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(10.0f, DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight043
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight043, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(50.0f, DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight044
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight044, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(100.0f, DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight045
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight045, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(-1.0f, DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight046
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight046, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(1000000.0f, DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight047
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight047, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("10.0f", DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight048
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight048, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("-1.0f", DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight049
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight049, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = StringUtils::StringToDimensionWithUnit("1000000.0f", DimensionUnit::PERCENT);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight050
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight050, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.5f, DimensionUnit::VP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight051
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight051, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.5f, DimensionUnit::FP);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}

/**
 * @tc.name: TextPickerModelNGSetGradientHeight052
 * @tc.desc: Test TextPickerModelNG SetGradientHeight(set Dimension).
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerGradientHeightTestNg, TextPickerModelNGSetGradientHeight052, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPickerLayoutProperty = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(textPickerLayoutProperty, nullptr);

    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);

    auto height = Dimension(0.5f, DimensionUnit::LPX);
    /**
     * @tc.step: step2. Set paramaters to GradientHeight.
     */
    TextPickerModelNG::GetInstance()->SetGradientHeight(height);
    ASSERT_TRUE(textPickerLayoutProperty->HasGradientHeight());
    EXPECT_EQ(height, textPickerLayoutProperty->GetGradientHeightValue());
}
} // namespace OHOS::Ace::NG