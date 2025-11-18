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

#include <functional>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double FONT_SIZE_10 = 10.0;
const std::string EMPTY_TEXT = "";
const std::string TEXT_PICKER_CONTENT = "text";
const OffsetF CHILD_OFFSET(0.0f, 10.0f);
const SizeF TEST_TEXT_FRAME_SIZE { 100.0f, 10.0f };
const SizeF COLUMN_SIZE { 100.0f, 200.0f };
constexpr float DISABLE_ALPHA = 0.6f;
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

class TextPickerEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerEventTestNg();
    void DestroyTextPickerEventTestNgObject();

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

void TextPickerEventTestNg::DestroyTextPickerEventTestNgObject()
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

void TextPickerEventTestNg::InitTextPickerEventTestNg()
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

void TextPickerEventTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerEventTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerEventTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerEventTestNg::TearDown()
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
 * @tc.name: TextPickerColumnPatternOnClickEventTest001
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 0, click up
    textPickerColumnPattern_->SetCurrentIndex(0);
    param->instance = nullptr;
    param->itemIndex = 1;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest002
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest002, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 0, click up
    textPickerColumnPattern_->SetCurrentIndex(0);
    param->instance = nullptr;
    param->itemIndex = 0;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest003
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest003, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 0, click down
    textPickerColumnPattern_->SetCurrentIndex(0);
    param->instance = nullptr;
    param->itemIndex = 3;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest004
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest004, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 0, click down
    textPickerColumnPattern_->SetCurrentIndex(0);
    param->instance = nullptr;
    param->itemIndex = 4;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 0);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest005
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest005, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 2, click up
    textPickerColumnPattern_->SetCurrentIndex(2);
    param->instance = nullptr;
    param->itemIndex = 1;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 2);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest006
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest006, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 2, click up
    textPickerColumnPattern_->SetCurrentIndex(2);
    param->instance = nullptr;
    param->itemIndex = 0;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 2);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest007
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest007, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 2, click down
    textPickerColumnPattern_->SetCurrentIndex(2);
    param->instance = nullptr;
    param->itemIndex = 3;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 2);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest008
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest008, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 2, click down
    textPickerColumnPattern_->SetCurrentIndex(2);
    param->instance = nullptr;
    param->itemIndex = 4;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 2);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest009
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest009, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 4, click up
    textPickerColumnPattern_->SetCurrentIndex(4);
    param->instance = nullptr;
    param->itemIndex = 1;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest010
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest010, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 4, click up
    textPickerColumnPattern_->SetCurrentIndex(4);
    param->instance = nullptr;
    param->itemIndex = 0;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest011
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest011, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 4, click down
    textPickerColumnPattern_->SetCurrentIndex(4);
    param->instance = nullptr;
    param->itemIndex = 3;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextPickerColumnPatternOnClickEventTest012
 * @tc.desc: test OnTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerColumnPatternOnClickEventTest012, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    textPickerColumnPattern_->InitMouseAndPressEvent();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    theme->showOptionCount_ = 5;

    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    RefPtr<EventParam> param = AceType::MakeRefPtr<EventParam>();
    uint32_t index = 0;

    // current is 4, click down
    textPickerColumnPattern_->SetCurrentIndex(4);
    param->instance = nullptr;
    param->itemIndex = 4;
    param->itemTotalCounts = 5;
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->OnAroundButtonClick(param);
    index = textPickerColumnPattern_->GetCurrentIndex();
    EXPECT_EQ(index, 4);

    // color is set = Color::xxx
    param->instance = nullptr;
    param->itemIndex = 2;
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->OnMiddleButtonTouchDown();

    // color is set = Color::TRANSPARENT
    param->instance = nullptr;
    param->itemIndex = 2;
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->OnMiddleButtonTouchMove();

    // color is set = Color::TRANSPARENT
    param->instance = nullptr;
    param->itemIndex = 2;
    param->itemTotalCounts = 5;
    textPickerColumnPattern_->OnMiddleButtonTouchUp();

    textPickerColumnPattern_->HandleMouseEvent(false);
    textPickerColumnPattern_->HandleMouseEvent(true);
}

/**
 * @tc.name: TextPickerPatternHandleDirectionKey001
 * @tc.desc: Test HandleDirectionKey
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerPatternHandleDirectionKey001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern_->SetOptions(range);
    /**
     * @tc.cases: case. cover KeyCode == KEY_DPAD_UP.
     */
    EXPECT_TRUE(textPickerPattern_->HandleDirectionKey(KeyCode::KEY_DPAD_UP));
    /**
     * @tc.cases: case. cover KeyCode == KEY_DPAD_DOWN.
     */
    EXPECT_TRUE(textPickerPattern_->HandleDirectionKey(KeyCode::KEY_DPAD_DOWN));
    /**
     * @tc.cases: case. cover KeyCode == KEY_ENTER.
     */
    EXPECT_FALSE(textPickerPattern_->HandleDirectionKey(KeyCode::KEY_ENTER));
    /**
     * @tc.cases: case. cover KeyCode == KEY_DPAD_LEFT.
     */
    textPickerPattern_->focusKeyID_ = 0;
    EXPECT_TRUE(textPickerPattern_->HandleDirectionKey(KeyCode::KEY_DPAD_LEFT));
}

/**
 * @tc.name: TextPickerPatternHandleDirectionKey002
 * @tc.desc: Test HandleDirectionKey
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerPatternHandleDirectionKey002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create textpicker pattern.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_PICKER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextPickerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto stackNode1 = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode1, nullptr);
    auto stackNode2 = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode2, nullptr);
    auto blendNode1 = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode1, nullptr);
    auto blendNode2 = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(blendNode2, nullptr);
    auto columnNode1 = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode1, nullptr);
    auto columnNode2 = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });
    ASSERT_NE(columnNode2, nullptr);
    columnNode1->MountToParent(blendNode1);
    blendNode1->MountToParent(stackNode1);
    stackNode1->MountToParent(frameNode);
    columnNode2->MountToParent(blendNode2);
    blendNode2->MountToParent(stackNode2);
    stackNode2->MountToParent(frameNode);
    auto textPickerColumnPattern2 = columnNode2->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern2, nullptr);
    /**
     * @tc.step: step2. SetOptions and call HandleDirectionKey.
     */
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    textPickerColumnPattern2->SetOptions(range);
    textPickerPattern->focusKeyID_ = 1;
    bool result = textPickerPattern->HandleDirectionKey(KeyCode::KEY_DPAD_LEFT);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextPickerPatternPlayResetAnimation001
 * @tc.desc: Test PlayResetAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerPatternPlayResetAnimation001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);

    textPickerColumnPattern_->PlayResetAnimation();
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 0.0f);

    textPickerColumnPattern_->scrollDelta_ = -10.0f;
    textPickerColumnPattern_->PlayResetAnimation();
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, -5.0f);
}

/**
 * @tc.name: TextPickerPatternPlayResetAnimation002
 * @tc.desc: Test PlayResetAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerPatternPlayResetAnimation002, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);

    textPickerColumnPattern_->PlayResetAnimation();
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 0.0f);

    textPickerColumnPattern_->scrollDelta_ = 10.0f;
    textPickerColumnPattern_->PlayResetAnimation();
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 3.0f);
}

/**
 * @tc.name: TextPickerPatternUpdateColumnChildPosition001
 * @tc.desc: Test UpdateColumnChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerPatternUpdateColumnChildPosition001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    /**
     * @tc.cases: case. cover isReboundInProgress_ == true && canLoop_ == true
     */
    textPickerColumnPattern_->isReboundInProgress_ = true;
    textPickerColumnPattern_->SetYLast(1.0);
    textPickerColumnPattern_->UpdateColumnChildPosition(2.0);
    std::vector<NG::RangeContent> range = { { "", "" } };
    textPickerColumnPattern_->SetOptions(range);
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 1.0f);
    /**
     * @tc.cases: case. cover isReboundInProgress_ == true && canLoop_ == false
     */
    auto property = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateCanLoop(false);
    textPickerColumnPattern_->isReboundInProgress_ = true;
    textPickerColumnPattern_->SetYLast(1.0);
    textPickerColumnPattern_->UpdateColumnChildPosition(2.0);
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 2.0f);
    /**
     * @tc.cases: case. cover isReboundInProgress_ == false && canLoop_ == false
     */
    property->UpdateCanLoop(false);
    textPickerColumnPattern_->isReboundInProgress_ = false;
    textPickerColumnPattern_->SetYLast(1.0);
    textPickerColumnPattern_->UpdateColumnChildPosition(2.0);
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 0.0f);
}

/**
 * @tc.name: TextPickerPatternUpdateColumnChildPosition002
 * @tc.desc: Test UpdateColumnChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, TextPickerPatternUpdateColumnChildPosition002, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    TextPickerOptionProperty prop;
    prop.height = 4.0f;
    prop.fontheight = 3.0f;
    prop.prevDistance = 5.0f;
    prop.nextDistance = 7.0f;
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    textPickerColumnPattern_->optionProperties_.emplace_back(prop);
    std::vector<NG::RangeContent> range = { { "", "" } };
    textPickerColumnPattern_->SetOptions(range);
    /**
     * @tc.cases: case. covering the false branch
     */
    textPickerColumnPattern_->pressed_ = true;
    textPickerColumnPattern_->SetTossStatus(true);
    textPickerColumnPattern_->overscroller_.SetOverScroll(1.0);
    textPickerColumnPattern_->SetYLast(1.0);
    textPickerColumnPattern_->UpdateColumnChildPosition(2.0);
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 1.0f);
    /**
     * @tc.cases: case. covering the true branch
     */
    auto property = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(property, nullptr);
    property->UpdateCanLoop(false);
    textPickerColumnPattern_->pressed_ = false;
    textPickerColumnPattern_->SetTossStatus(true);
    textPickerColumnPattern_->overscroller_.SetOverScroll(10.0);
    textPickerColumnPattern_->SetYLast(1.0);
    textPickerColumnPattern_->UpdateColumnChildPosition(2.0);
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 0.0f);
    /**
     * @tc.cases: case. covering the return branch
     */
    textPickerColumnPattern_->SetYLast(1.0);
    textPickerColumnPattern_->UpdateColumnChildPosition(1.0);
    EXPECT_EQ(textPickerColumnPattern_->scrollDelta_, 0.0f);
}

/**
 * @tc.name: LinearFontSize001
 * @tc.desc: TextPickerColumnPattern LinearFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, LinearFontSize001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    Dimension dimension = Dimension(FONT_SIZE_10);
    Dimension dimension1;
    dimension1 = textPickerColumnPattern_->LinearFontSize(dimension, dimension, 1);
    EXPECT_FALSE(dimension < dimension1);
}

/**
 * @tc.name: LinearFontSize002
 * @tc.desc: TextPickerColumnPattern LinearFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, LinearFontSize002, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    Dimension dimension = Dimension(FONT_SIZE_10);
    Dimension dimension1;
    dimension1 = textPickerColumnPattern_->LinearFontSize(dimension, dimension, 2);
    EXPECT_FALSE(dimension < dimension1);
}

/**
 * @tc.name: UpdateButtonMargin001
 * @tc.desc: Test TextPickerPattern UpdateButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, UpdateButtonMargin001, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);

    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    auto layoutProperty = buttonConfirmNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    textPickerPattern_->UpdateButtonMargin(buttonConfirmNode, dialogTheme, true);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right, CalcLength(0.0_vp));

    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    textPickerPattern_->UpdateButtonMargin(buttonConfirmNode, dialogTheme, true);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left, CalcLength(0.0_vp));

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    textPickerPattern_->UpdateButtonMargin(buttonConfirmNode, dialogTheme, true);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right, CalcLength(0.0_vp));
}

/**
 * @tc.name: UpdateButtonMargin002
 * @tc.desc: Test TextPickerPattern UpdateButtonMargin
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, UpdateButtonMargin002, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    ASSERT_NE(dialogTheme, nullptr);

    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    auto layoutProperty = buttonCancelNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    textPickerPattern_->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left, CalcLength(0.0_vp));

    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    textPickerPattern_->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->right, CalcLength(0.0_vp));

    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(backupApiVersion));

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    textPickerPattern_->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left, CalcLength(0.0_vp));
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test TextPickerPattern OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, OnModifyDone001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    textPickerPattern_->isFiredSelectsChange_ = true;

    textPickerPattern_->OnModifyDone();
    EXPECT_FALSE(textPickerPattern_->isFiredSelectsChange_);

    ASSERT_NE(frameNode_, nullptr);
    auto layoutProperty = frameNode_->GetLayoutProperty<LinearLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    textPickerPattern_->OnModifyDone();

    ASSERT_NE(stackNode_, nullptr);
    auto stackLayoutProperty = stackNode_->GetLayoutProperty();
    ASSERT_NE(stackLayoutProperty, nullptr);
    EXPECT_EQ(stackLayoutProperty->GetLayoutDirection(), TextDirection::LTR);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test TextPickerPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode_, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());

    DirtySwapConfig config;
    textPickerPattern_->SetIsShowInDialog(true);
    EXPECT_FALSE(textPickerPattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: ParseDirectionKey001
 * @tc.desc: Test TextPickerPattern ParseDirectionKey
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, ParseDirectionKey001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    auto columnNode = FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPickerColumnPattern>(); });

    auto textPickerColumnPattern = columnNode->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    auto totalOptionCount = textPickerColumnPattern->GetOptionCount();

    KeyCode code = KeyCode::KEY_UNKNOWN;

    code = KeyCode::KEY_DPAD_UP;
    textPickerColumnPattern->stopHaptic_ = false;
    textPickerPattern_->ParseDirectionKey(textPickerColumnPattern, code, totalOptionCount, 0);
    EXPECT_FALSE(textPickerColumnPattern->InnerHandleScroll(0, false));
    EXPECT_TRUE(textPickerColumnPattern->stopHaptic_);

    code = KeyCode::KEY_DPAD_DOWN;
    textPickerColumnPattern->stopHaptic_ = false;
    textPickerPattern_->ParseDirectionKey(textPickerColumnPattern, code, totalOptionCount, 0);
    EXPECT_FALSE(textPickerColumnPattern->InnerHandleScroll(1, false));
    EXPECT_TRUE(textPickerColumnPattern->stopHaptic_);

    AceApplicationInfo::GetInstance().isRightToLeft_ = true;

    code = KeyCode::KEY_DPAD_LEFT;
    textPickerColumnPattern->stopHaptic_ = false;
    textPickerPattern_->ParseDirectionKey(textPickerColumnPattern, code, totalOptionCount, 0);
    EXPECT_EQ(textPickerPattern_->focusKeyID_, -1);
    EXPECT_FALSE(textPickerColumnPattern->stopHaptic_);

    code = KeyCode::KEY_DPAD_RIGHT;
    textPickerColumnPattern->stopHaptic_ = false;
    textPickerPattern_->ParseDirectionKey(textPickerColumnPattern, code, totalOptionCount, 0);
    EXPECT_EQ(textPickerPattern_->focusKeyID_, 0);
    EXPECT_FALSE(textPickerColumnPattern->stopHaptic_);
}

/**
 * @tc.name: NeedAdaptForAging001
 * @tc.desc: Test TextPickerPattern NeedAdaptForAging
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, NeedAdaptForAging001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);

    pipeline->SetFontScale(2.0f);
    EXPECT_TRUE(textPickerPattern_->NeedAdaptForAging());

    pipeline->SetFontScale(1.0f);
    EXPECT_FALSE(textPickerPattern_->NeedAdaptForAging());
}

/**
 * @tc.name: ChangeCurrentOptionValue001
 * @tc.desc: Test TextPickerPattern ChangeCurrentOptionValue
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, ChangeCurrentOptionValue001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    NG::TextCascadePickerOptions option1;
    NG::TextCascadePickerOptions options;
    options.children.emplace_back(option1);

    uint32_t value = 0;
    uint32_t curColumn = 0;
    uint32_t replaceColumn = 0;

    textPickerPattern_->selecteds_.emplace_back(0);
    textPickerPattern_->selecteds_.emplace_back(1);

    textPickerPattern_->values_.emplace_back("A");
    textPickerPattern_->values_.emplace_back("B");

    textPickerPattern_->ChangeCurrentOptionValue(options, value, curColumn, replaceColumn);
    EXPECT_EQ(textPickerPattern_->selecteds_[1], 0);
}

/**
 * @tc.name: ProcessCascadeOptionsValues001
 * @tc.desc: Test TextPickerPattern ProcessCascadeOptionsValues
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, ProcessCascadeOptionsValues001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);

    uint32_t index = 0;
    std::vector<std::string> rangeResultValue;
    rangeResultValue.emplace_back("A");
    rangeResultValue.emplace_back("B");

    textPickerPattern_->selecteds_.clear();
    textPickerPattern_->selecteds_.emplace_back(-1);

    textPickerPattern_->values_.clear();
    textPickerPattern_->values_.emplace_back("A");
    textPickerPattern_->values_.emplace_back("B");

    textPickerPattern_->ProcessCascadeOptionsValues(rangeResultValue, index);
    EXPECT_EQ(textPickerPattern_->selecteds_[0], 0);

    index = 1;
    textPickerPattern_->ProcessCascadeOptionsValues(rangeResultValue, index);
    EXPECT_GE(textPickerPattern_->selecteds_.size(), 2);
    EXPECT_EQ(textPickerPattern_->selecteds_[1], 1);
}

/**
 * @tc.name: InitDisabled001
 * @tc.desc: Test TextPickerPattern InitDisabled
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, InitDisabled001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);
    ASSERT_NE(frameNode_, nullptr);
    auto eventHub = frameNode_->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(false);
    textPickerPattern_->InitDisabled();
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetOpacity(), (textPickerPattern_->curOpacity_ * DISABLE_ALPHA));
}

/**
 * @tc.name: GetRangeStr001
 * @tc.desc: Test TextPickerPattern GetRangeStr
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, GetRangeStr001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    ASSERT_NE(textPickerPattern_, nullptr);
    textPickerPattern_->range_.clear();
    auto str = textPickerPattern_->GetRangeStr();
    EXPECT_EQ(str, "");
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test TextPickerPattern OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    int32_t minApiVersion = context->GetMinPlatformVersion();
    context->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    InitTextPickerEventTestNg();
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(textPickerPattern_, nullptr);

    auto contentRow = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    textPickerPattern_->SetContentRowNode(contentRow);
    textPickerPattern_->isPicker_ = false;
    auto contentRowNode = textPickerPattern_->contentRowNode_.Upgrade();
    ASSERT_NE(contentRowNode, nullptr);

    EXPECT_TRUE(frameNode_->needCallChildrenUpdate_);
    textPickerPattern_->OnColorConfigurationUpdate();
    EXPECT_TRUE(frameNode_->needCallChildrenUpdate_);
    context->SetMinPlatformVersion(minApiVersion);
    auto pickerProperty = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor(), Color::BLACK);
}

/**
 * @tc.name: GetOverScrollDeltaIndex001
 * @tc.desc: TextPickerColumnPattern GetOverScrollDeltaIndex
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, GetOverScrollDeltaIndex001, TestSize.Level1)
{
    InitTextPickerEventTestNg();
    int32_t index = textPickerColumnPattern_->GetOverScrollDeltaIndex();
    ASSERT_FALSE(index > 0);
}

/**
 * @tc.name: SetDisableTextStyleAnimation001
 * @tc.desc: Test SetDisableTextStyleAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerEventTestNg, SetDisableTextStyleAnimation001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    EXPECT_FALSE(textPickerPattern->GetDisableTextStyleAnimation());

    textPickerPattern->SetDisableTextStyleAnimation(true);
    EXPECT_TRUE(textPickerPattern->GetDisableTextStyleAnimation());
}
} // namespace OHOS::Ace::NG
