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
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/measure_util.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TextPickerColumnTestOneNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerColumnTestOneNg();
    void DestroyTextPickerColumnTestOneNgObject();

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

void TextPickerColumnTestOneNg::DestroyTextPickerColumnTestOneNgObject()
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

void TextPickerColumnTestOneNg::InitTextPickerColumnTestOneNg()
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

void TextPickerColumnTestOneNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerColumnTestOneNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerColumnTestOneNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
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

void TextPickerColumnTestOneNg::TearDown()
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
 * @tc.name: CreateItemTouchEventListener001
 * @tc.desc: Test TextPickerColumnPattern CreateItemTouchEventListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, CreateItemTouchEventListener001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto testImpl = columnPattern->CreateItemTouchEventListener();
    ASSERT_NE(testImpl, nullptr);
    TouchEventInfo info("touch");
    info.touches_.front().SetTouchType(TouchType::UNKNOWN);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->touchBreak_ == false);
}

/**
 * @tc.name: CreateItemTouchEventListener002
 * @tc.desc: Test TextPickerColumnPattern CreateItemTouchEventListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, CreateItemTouchEventListener002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto testImpl = columnPattern->CreateItemTouchEventListener();
    ASSERT_NE(testImpl, nullptr);
    columnPattern->tossAnimationController_->SetColumn(columnPattern);
    TouchEventInfo info("touch");
    info.touches_.front().SetTouchType(TouchType::DOWN);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->touchBreak_ == false);
}

/**
 * @tc.name: CreateItemTouchEventListener003
 * @tc.desc: Test TextPickerColumnPattern CreateItemTouchEventListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, CreateItemTouchEventListener003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto testImpl = columnPattern->CreateItemTouchEventListener();
    ASSERT_NE(testImpl, nullptr);
    TouchEventInfo info("touch");
    info.touches_.front().SetTouchType(TouchType::UP);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->touchBreak_ == false);
    columnPattern->animationBreak_ = true;
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->isDownScroll_ == false);
}

/**
 * @tc.name: CreateMouseHoverEventListener001
 * @tc.desc: Test TextPickerColumnPattern CreateMouseHoverEventListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, CreateMouseHoverEventListener001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto testImpl = columnPattern->CreateMouseHoverEventListener(nullptr);
    ASSERT_NE(testImpl, nullptr);
    testImpl->GetOnHoverEventFunc()(false);
    EXPECT_TRUE(columnPattern->isHover_ == false);
}

/**
 * @tc.name: ParseTouchListener001
 * @tc.desc: Test TextPickerColumnPattern ParseTouchListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, ParseTouchListener001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->ParseTouchListener();
    auto testImpl = columnPattern->touchListener_;
    ASSERT_NE(testImpl, nullptr);
    TouchEventInfo info("touch");
    info.touches_.front().SetTouchType(TouchType::DOWN);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->localDownDistance_ != 0.0f);
    info.touches_.front().SetTouchType(TouchType::UP);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->localDownDistance_ == 0.0f);
    info.touches_.front().SetTouchType(TouchType::CANCEL);
    EXPECT_TRUE(columnPattern->localDownDistance_ == 0.0f);
    testImpl->GetTouchEventCallback()(info);
    info.touches_.front().SetTouchType(TouchType::MOVE);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->localDownDistance_ == 0.0f);
}

/**
 * @tc.name: ParseTouchListener002
 * @tc.desc: Test TextPickerColumnPattern ParseTouchListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, ParseTouchListener002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->ParseTouchListener();
    auto testImpl = columnPattern->touchListener_;
    ASSERT_NE(testImpl, nullptr);
    TouchEventInfo info("touch");
    info.touches_.front().SetTouchType(TouchType::MOVE);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->localDownDistance_ == 0.0f);
    AnimationOption tstOption;
    info.touches_.front().localLocation_.deltaX_ = 300.0f;
    info.touches_.front().localLocation_.deltaY_ = 400.0f;
    columnPattern->localDownDistance_ = 100.0f;
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->localDownDistance_ != 0.0f);
}

/**
 * @tc.name: ParseTouchListener003
 * @tc.desc: Test TextPickerColumnPattern ParseTouchListener.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, ParseTouchListener003, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->ParseTouchListener();
    auto testImpl = columnPattern->touchListener_;
    ASSERT_NE(testImpl, nullptr);
    TouchEventInfo info("touch");
    info.touches_.front().SetTouchType(TouchType::HOVER_ENTER);
    testImpl->GetTouchEventCallback()(info);
    EXPECT_TRUE(columnPattern->localDownDistance_ == 0.0f);
}

/**
 * @tc.name: FlushCurrentOptions001
 * @tc.desc: Test TextPickerColumnPattern FlushCurrentOptions001.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, FlushCurrentOptions001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->FlushCurrentOptions(false, true, false, true);
    EXPECT_TRUE(columnPattern->animationProperties_.size() != 0);
}

/**
 * @tc.name: SetCanLoop001
 * @tc.desc: Test TextPickerColumnPattern SetCanLoop.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, SetCanLoop001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->isLoop_ = true;
    columnPattern->isTossStatus_ = true;
    columnPattern->SetCanLoop(false);
    EXPECT_EQ(columnPattern->isLoop_, false);
}

/**
 * @tc.name: SpringCurveTailMoveProcess001
 * @tc.desc: Test TextPickerColumnPattern SpringCurveTailMoveProcess.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, SpringCurveTailMoveProcess001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto testToss = columnPattern->GetToss();
    testToss->isTossPlaying_ = true;
    double tstDragDelta = 0.0f;
    bool tstResult = columnPattern->SpringCurveTailMoveProcess(false, tstDragDelta);
    EXPECT_TRUE(tstResult == true);
    tstDragDelta = 100.0f;
    tstResult = columnPattern->SpringCurveTailMoveProcess(false, tstDragDelta);
    EXPECT_TRUE(tstResult == true);
    columnPattern->tossAnimationController_ = nullptr;
    tstResult = columnPattern->SpringCurveTailMoveProcess(false, tstDragDelta);
    EXPECT_TRUE(tstResult == false);
}

/**
 * @tc.name: SpringCurveTailEndProcess001
 * @tc.desc: Test TextPickerColumnPattern SpringCurveTailEndProcess.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, SpringCurveTailEndProcess001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->SpringCurveTailEndProcess(false, false);
    EXPECT_TRUE(columnPattern->GetToss()->isTossPlaying_ == false);
    columnPattern->tossAnimationController_ = nullptr;
    columnPattern->SpringCurveTailEndProcess(false, false);
    EXPECT_TRUE(columnPattern->GetToss() == nullptr);
}

/**
 * @tc.name: OnAroundButtonClick001
 * @tc.desc: Test TextPickerColumnPattern OnAroundButtonClick.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, OnAroundButtonClick001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->clickBreak_ = true;
    columnPattern->OnAroundButtonClick(nullptr);
    EXPECT_TRUE(columnPattern->clickBreak_ == true);
}

/**
 * @tc.name: OnAroundButtonClick002
 * @tc.desc: Test TextPickerColumnPattern OnAroundButtonClick.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, OnAroundButtonClick002, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" } };
    TextPickerModelNG::GetInstance()->SetRange(range);
    TextPickerModelNG::GetInstance()->SetSelected(1);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(false);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto childNode = AccessibilityManager::DynamicCast<FrameNode>(child->GetChildAtIndex(0));
    auto childSize = static_cast<int32_t>(child->GetChildren().size());
    RefPtr<EventParam> param = AccessibilityManager::MakeRefPtr<EventParam>();
    AnimationOption option;
    param->itemIndex = 0;
    param->instance = childNode;
    param->itemTotalCounts = childSize;
    auto layout = columnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    layout->UpdateCanLoop(false);
    columnPattern->overscroller_.overScroll_ = 100.0f;
    columnPattern->animation_ =
        AnimationUtils::StartAnimation(option, []() { std::cout << "start animation now ." << std::endl; });
    columnPattern->OnAroundButtonClick(param);
    EXPECT_TRUE(columnPattern->clickBreak_ == false);
    param->itemIndex = 100;
    layout->UpdateCanLoop(true);
    columnPattern->overscroller_.overScroll_ = 0.0f;
    columnPattern->OnAroundButtonClick(param);
    EXPECT_EQ(columnPattern->yLast_, 0.0f);
}

/**
 * @tc.name: InnerHandleScroll001
 * @tc.desc: Test TextPickerColumnPattern InnerHandleScroll001
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, InnerHandleScroll001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    RangeContent tstContent = { "test", "test" };
    columnPattern->options_.push_back(tstContent);
    columnPattern->GetParentLayout()->UpdateCanLoop(false);
    columnPattern->InnerHandleScroll(true);
    EXPECT_TRUE(columnPattern->currentChildIndex_ == 0);
    columnPattern->InnerHandleScroll(false);
    EXPECT_TRUE(columnPattern->currentChildIndex_ == 0);
    RangeContent tstContentOne = { "test1", "test1" };
    columnPattern->options_.push_back(tstContentOne);
    columnPattern->InnerHandleScroll(true);
    EXPECT_TRUE(columnPattern->currentChildIndex_ == 0);
    columnPattern->currentIndex_ = 1;
    columnPattern->InnerHandleScroll(false);
    EXPECT_TRUE(columnPattern->currentChildIndex_ == 0);
}

/**
 * @tc.name: CanMove001
 * @tc.desc: Test TextPickerColumnPattern CanMove001
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, CanMove001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    columnPattern->GetParentLayout()->UpdateCanLoop(true);
    columnPattern->CanMove(true);
    EXPECT_TRUE(columnPattern->NotLoopOptions() == false);
}

/**
 * @tc.name: UpdateColumnChildPosition001
 * @tc.desc: Test TextPickerColumnPattern UpdateColumnChildPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, UpdateColumnChildPosition001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto layout = columnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    layout->UpdateCanLoop(false);
    columnPattern->pressed_ = true;
    columnPattern->UpdateColumnChildPosition(0.0f);
    EXPECT_TRUE(columnPattern->pressed_ == true);
    columnPattern->pressed_ = false;
    columnPattern->isTossStatus_ = true;
    columnPattern->isTossStatus_ = true;
    columnPattern->isReboundInProgress_ = true;
    columnPattern->UpdateColumnChildPosition(0.0f);
    EXPECT_TRUE(columnPattern->isReboundInProgress_ == true);
    columnPattern->isReboundInProgress_ = false;
    columnPattern->overscroller_.overScroll_ = 100.0f;
    columnPattern->UpdateColumnChildPosition(0.0f);
    EXPECT_TRUE(columnPattern->isReboundInProgress_ == false);
}

/**
 * @tc.name: GetShiftDistanceForLandscape001
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistanceForLandscape
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, GetShiftDistanceForLandscape001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto layout = columnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    /**
     * @tc.steps: step1. index != enum OptionIndex and Call GetShiftDistanceForLandscape
     * @tc.expected:return 0
     */
    layout->UpdateCanLoop(false);
    columnPattern->pressed_ = true;
    int32_t index = 100;
    auto distance = columnPattern->GetShiftDistanceForLandscape(index, ScrollDirection::DOWN);
    EXPECT_TRUE(distance == 0);
}

/**
 * @tc.name: GetUpCandidateDistance001
 * @tc.desc: Test TextPickerColumnPattern GetUpCandidateDistance
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, GetUpCandidateDistance001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    int32_t tstIndex = 100;
    int32_t tstNextIndex = 0;
    ScrollDirection dir = ScrollDirection::UP;
    double distance = columnPattern->GetUpCandidateDistance(tstIndex, tstNextIndex, dir);
    EXPECT_TRUE(distance == 0);
    tstIndex = -1;
    distance = columnPattern->GetUpCandidateDistance(tstIndex, tstNextIndex, dir);
    EXPECT_TRUE(distance == 0);
    tstIndex = 5;
    tstNextIndex = 100;
    distance = columnPattern->GetUpCandidateDistance(tstIndex, tstNextIndex, dir);
    EXPECT_TRUE(distance == 0);
    tstNextIndex = -1;
    distance = columnPattern->GetUpCandidateDistance(tstIndex, tstNextIndex, dir);
    EXPECT_TRUE(distance == 0);
}

/**
 * @tc.name: GetSelectedDistance001
 * @tc.desc: Test TextPickerColumnPattern GetSelectedDistance
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, GetSelectedDistance001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    int32_t tstIndex = 0;
    int32_t tstNextIndex = 0;
    ScrollDirection dir = ScrollDirection::UP;
    columnPattern->columnkind_ = TEXT;
    columnPattern->optionProperties_[0].fontheight = 100.0f;
    columnPattern->optionProperties_[0].height = 800.0f;
    double distance = columnPattern->GetSelectedDistance(tstIndex, tstNextIndex, dir);
    EXPECT_TRUE(distance != 0);
}

/**
 * @tc.name: GetShiftDistance001
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistance
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, GetShiftDistance001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    /**
     * @tc.steps: step1. optionProperties_ is empty and Call GetShiftDistance
     * @tc.expected:immediately return 0
     */
    int32_t tstIndex = 100;
    ScrollDirection dir = ScrollDirection::UP;
    columnPattern->optionProperties_.clear();
    auto distance = columnPattern->GetShiftDistance(tstIndex, dir);
    EXPECT_TRUE(distance == 0);
}

/**
 * @tc.name: HandleDragEnd001
 * @tc.desc: Test TextPickerColumnPattern HandleDragEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, HandleDragEnd001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto layout = columnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    layout->UpdateCanLoop(false);
    columnPattern->overscroller_.overScroll_ = 100.0f;
    auto tstToss = columnPattern->GetToss();
    tstToss->timeEnd_ = 100.0f;
    auto tstWeak = AceType::WeakClaim(tstToss.GetRawPtr());
    auto tstRef = tstWeak.Upgrade();
    auto tstColumn = AceType::DynamicCast<TextPickerColumnPattern>(tstRef->column_.Upgrade());
    EXPECT_TRUE(tstColumn != nullptr);
    tstColumn->mainVelocity_ = 10000.0f;
    columnPattern->HandleDragEnd();
    EXPECT_TRUE(tstToss->Play() == true);
}

/**
 * @tc.name: HandleDragMove001
 * @tc.desc: Test TextPickerColumnPattern HandleDragMove
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, HandleDragMove001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    GestureEvent event;
    FingerInfo tstFinger;
    FingerInfo tstFingerSec;
    event.fingerList_.push_back(tstFinger);
    event.fingerList_.push_back(tstFingerSec);
    columnPattern->HandleDragMove(event);
    EXPECT_TRUE(event.GetFingerList().size() > 1);
    event.fingerList_.clear();
    event.inputEventType_ = InputEventType::AXIS;
    event.sourceTool_ = SourceTool::MOUSE;
    event.fingerList_.push_back(tstFinger);
    columnPattern->HandleDragMove(event);
    EXPECT_FALSE(event.GetFingerList().size() > 1);
    /**
     * @tc.steps: step1. Call HandleDragMove
     * @tc.expected: inner code of function: NearEqual(offsetY, yLast_, MOVE_THRESHOLD)==TRUE
     */
    event.sourceTool_ = SourceTool::FINGER;
    columnPattern->pressed_ = true;
    columnPattern->HandleDragMove(event);
    EXPECT_FALSE(columnPattern->animationBreak_);
    auto offsetY =
        event.GetGlobalPoint().GetY() + (event.GetInputEventType() == InputEventType::AXIS ? event.GetOffsetY() : 0.0);
    double epsilon = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? 2.0 : 1.0;
    EXPECT_TRUE(NearEqual(offsetY, columnPattern->yLast_, epsilon));
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: Test TextPickerColumnPattern HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, HandleDragStart001, TestSize.Level1)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    auto theme = pipeline->GetTheme<PickerTheme>();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(0);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateCanLoop(true);
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    textPickerPattern->OnModifyDone();
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto layout = columnPattern->GetParentLayout();
    ASSERT_NE(layout, nullptr);
    layout->UpdateCanLoop(false);
    GestureEvent event;
    AnimationOption option;
    columnPattern->animation_ =
        AnimationUtils::StartAnimation(option, []() { std::cout << "start animation now ." << std::endl; });
    columnPattern->reboundAnimation_ = nullptr;
    columnPattern->HandleDragStart(event);
    EXPECT_TRUE(columnPattern->reboundAnimation_ == nullptr);
    columnPattern->reboundAnimation_ = columnPattern->animation_;
    columnPattern->HandleDragStart(event);
    EXPECT_TRUE(columnPattern->NotLoopOptions());
    EXPECT_TRUE(columnPattern->reboundAnimation_ != nullptr);
}

/**
 * @tc.name: InitPanEvent001
 * @tc.desc: Test TextPickerColumnPattern InitPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestOneNg, InitPanEvent001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);
    pickerNodeLayout->UpdateCanLoop(true);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto gestureHub = eventHub->GetOrCreateGestureEventHub();
    columnPattern->InitPanEvent(gestureHub);
    auto panEvent = columnPattern->panEvent_;
    GestureEvent event;
    FingerInfo tstFinger;
    event.fingerList_.push_back(tstFinger);
    event.sourceTool_ = SourceTool::MOUSE;
    event.inputEventType_ = InputEventType::AXIS;
    panEvent->actionStart_(event);
    EXPECT_TRUE(event.GetSourceTool() == SourceTool::MOUSE);
    event.sourceTool_ = SourceTool::FINGER;
    panEvent->actionStart_(event);
    EXPECT_TRUE(event.GetSourceTool() != SourceTool::MOUSE);
    event.sourceTool_ = SourceTool::MOUSE;
    panEvent->actionEnd_(event);
    EXPECT_TRUE(event.GetSourceTool() == SourceTool::MOUSE);
}
} // namespace OHOS::Ace::NG