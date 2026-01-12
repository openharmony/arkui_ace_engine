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

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const int32_t HALF_NUMBER = 2;
constexpr int32_t COLUMN_INDEX_1 = 1;
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

class TextPickerColumnTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void InitTextPickerColumnTestThreeNg();
    void DestroyTextPickerColumnTestThreeNgObject();
    bool CompareTextPickerOptionProperties(std::vector<TextPickerOptionProperty> option1,
        std::vector<TextPickerOptionProperty> option2);

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

void TextPickerColumnTestThreeNg::DestroyTextPickerColumnTestThreeNgObject()
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

void TextPickerColumnTestThreeNg::InitTextPickerColumnTestThreeNg()
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

bool TextPickerColumnTestThreeNg::CompareTextPickerOptionProperties(std::vector<TextPickerOptionProperty> option1,
    std::vector<TextPickerOptionProperty> option2)
{
    int32_t size = option1.size();

    for (int32_t i = 0; i < size; i++) {
        if (option1[i].height != option2[i].height ||
            option1[i].fontheight != option2[i].fontheight ||
            option1[i].prevDistance != option2[i].prevDistance ||
            option1[i].nextDistance != option2[i].nextDistance) {
            return false;
        }
    }
    return true;
}

void TextPickerColumnTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void TextPickerColumnTestThreeNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextPickerColumnTestThreeNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TextPickerColumnTestThreeNg::TearDown()
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
 * @tc.name: TextPickerColumnProperties001
 * @tc.desc: Test TextPickerColumnPattern properties.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnProperties001, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::PORTRAIT));

    uint32_t columnKind = TEXT;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, columnKind);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    EXPECT_EQ(columnPattern->columnKind_, TEXT);

    auto textNode = AceType::DynamicCast<FrameNode>(child->GetLastChild());
    ASSERT_NE(textNode, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    std::vector<TextPickerOptionProperty> initOptionProperties = columnPattern->optionProperties_;

    std::vector<NG::RangeContent> range = { { "", "1" }, { "", "2" }, { "", "3" }, { "", "4" }, { "", "5" } };
    columnPattern->SetOptions(range);
    columnPattern->SetColumnKind(TEXT);

    TextPickerModelNG::GetInstance()->SetDisableTextStyleAnimation(true);
    columnPattern->FlushCurrentOptions(false, true);
    std::vector<TextPickerOptionProperty> enableOptionProperties = columnPattern->optionProperties_;
    auto textOverflow = textLayoutProperty->GetTextOverflow();
    EXPECT_TRUE(CompareTextPickerOptionProperties(enableOptionProperties, initOptionProperties));

    TextPickerModelNG::GetInstance()->SetDisableTextStyleAnimation(false);
    columnPattern->FlushCurrentOptions(false, true);

    TextPickerModelNG::GetInstance()->SetDisableTextStyleAnimation(true);
    columnPattern->FlushCurrentOptions(false, true);
    std::vector<TextPickerOptionProperty> reEnableOptionProperties = columnPattern->optionProperties_;
    EXPECT_TRUE(CompareTextPickerOptionProperties(reEnableOptionProperties, enableOptionProperties));
    EXPECT_EQ(textLayoutProperty->GetTextOverflow(), textOverflow);
}

/**
 * @tc.name: TextPickerColumnInitHeightAndFontHeight001
 * @tc.desc: Test when childIndex equals midIndex, the font height and height are calculated correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnInitHeightAndFontHeight001, TestSize.Level1)
{
    uint32_t columnKind = TEXT;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, columnKind);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    uint32_t childIndex = 3;
    uint32_t midIndex = 3;
    TextPickerOptionProperty prop;
    columnPattern->InitTextHeightAndFontHeight(childIndex, midIndex, prop);
    EXPECT_EQ(prop.height, columnPattern->dividerSpacing_);
    EXPECT_GT(prop.fontheight, 0);
}

/**
 * @tc.name: TextPickerColumnInitHeightAndFontHeight002
 * @tc.desc: Test when childIndex equals (midIndex + 1), the font height and height are calculated correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnInitHeightAndFontHeight002, TestSize.Level1)
{
    uint32_t columnKind = TEXT;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, columnKind);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    uint32_t midIndex = 3;
    uint32_t childIndex = midIndex + 1;
    TextPickerOptionProperty prop;
    columnPattern->InitTextHeightAndFontHeight(childIndex, midIndex, prop);
    EXPECT_EQ(prop.height, columnPattern->gradientHeight_);
    EXPECT_GT(prop.fontheight, 0);
}

/**
 * @tc.name: TextPickerColumnInitHeightAndFontHeight003
 * @tc.desc: Test when childIndex equals (midIndex - 1), the font height and height are calculated correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnInitHeightAndFontHeight003, TestSize.Level1)
{
    uint32_t columnKind = TEXT;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, columnKind);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    uint32_t midIndex = 3;
    uint32_t childIndex = midIndex - 1;
    TextPickerOptionProperty prop;
    columnPattern->InitTextHeightAndFontHeight(childIndex, midIndex, prop);
    EXPECT_EQ(prop.height, columnPattern->gradientHeight_);
    EXPECT_GT(prop.fontheight, 0);
}

/**
 * @tc.name: TextPickerColumnInitHeightAndFontHeight004
 * @tc.desc: Test when childIndex is not equals to midIndex, (midIndex + 1), (midIndex - 1),
 *           the font height and height are calculated correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnInitHeightAndFontHeight004, TestSize.Level1)
{
    uint32_t columnKind = TEXT;
    auto pipeline = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, columnKind);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    ASSERT_NE(textPickerPattern, nullptr);
    auto child = textPickerPattern->GetColumnNode();
    ASSERT_NE(child, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(child)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);

    uint32_t midIndex = 3;
    uint32_t childIndex = midIndex - 2;
    TextPickerOptionProperty prop;
    columnPattern->InitTextHeightAndFontHeight(childIndex, midIndex, prop);
    EXPECT_EQ(prop.height, columnPattern->gradientHeight_);
    EXPECT_GT(prop.fontheight, 0);
}

/**
 * @tc.name: GetShiftDistanceForLandscape003
 * @tc.desc: Test TextPickerColumnPattern GetShiftDistanceForLandscape when dir = UP and index = 1.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, GetShiftDistanceForLandscape003, TestSize.Level1)
{
    InitTextPickerColumnTestThreeNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);
    ScrollDirection dir = ScrollDirection::UP;
    TextPickerOptionProperty prop;
    prop.height = 2.0f;
    prop.fontheight = 1.0f;
    prop.prevDistance = 4.0f;
    prop.nextDistance = 5.0f;

    textPickerColumnPattern->optionProperties_.clear();
    uint32_t showCount = textPickerColumnPattern->GetShowOptionCount();
    for (uint32_t i = 0; i < showCount; i++) {
        textPickerColumnPattern->optionProperties_.emplace_back(prop);
    }

    int32_t currentIndex = COLUMN_INDEX_1;
    int32_t nextIndex = COLUMN_INDEX_1 - 1;
    double distance = 0.0f - std::round(textPickerColumnPattern->optionProperties_[currentIndex].height / HALF_NUMBER +
        textPickerColumnPattern->optionProperties_[nextIndex].height -
        textPickerColumnPattern->optionProperties_[nextIndex].fontheight / HALF_NUMBER);
    EXPECT_EQ(textPickerColumnPattern_->GetShiftDistanceForLandscape(currentIndex, dir), distance);
}

/**
 * @tc.name: SetOptionShiftDistance001
 * @tc.desc: Test SetOptionShiftDistance when optionProperties_ is empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, SetOptionShiftDistance001, TestSize.Level1)
{
    InitTextPickerColumnTestThreeNg();
    auto textPickerColumnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(textPickerColumnPattern, nullptr);

    textPickerColumnPattern->SetOptionShiftDistance();
    EXPECT_TRUE(textPickerColumnPattern->optionProperties_.empty());
}

/**
 * @tc.name: SetOptionShiftDistance002
 * @tc.desc: Test SetOptionShiftDistance when isLandscape is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, SetOptionShiftDistance002, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));

    InitTextPickerColumnTestThreeNg();
    auto columnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 5;

    TextPickerOptionProperty prop1;
    prop1.height = 117.0f;
    prop1.fontheight = 61.0f;
    TextPickerOptionProperty prop2;
    prop2.height = 117.0f;
    prop2.fontheight = 69.0f;
    TextPickerOptionProperty prop3;
    prop3.height = 182.0f;
    prop3.fontheight = 76.0f;

    const TextPickerOptionProperty tmpOptionProperties[] = {prop1, prop2, prop3, prop2, prop1};

    columnPattern->optionProperties_.clear();
    for (const auto& prop: tmpOptionProperties) {
        columnPattern->optionProperties_.emplace_back(prop);
    }

    columnPattern->SetOptionShiftDistance();

    std::vector<std::pair<float, float>> expectedValues = {
        {-117.0f, 117.0f},
        {-117.0f, 117.0f},
        {-117.0f, 206.0f},
        {-203.0f, 145.0f},
        {-141.0f, 117.0f}
    };

    for (size_t i = 0; i < columnPattern->optionProperties_.size(); i++) {
        EXPECT_EQ(columnPattern->optionProperties_[i].prevDistance, expectedValues[i].first);
        EXPECT_EQ(columnPattern->optionProperties_[i].nextDistance, expectedValues[i].second);
    }
}

/**
 * @tc.name: SetOptionShiftDistance003
 * @tc.desc: Test SetOptionShiftDistance when isLandscape and isDisableTextStyleAnimation_ are false.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, SetOptionShiftDistance003, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::PORTRAIT));

    InitTextPickerColumnTestThreeNg();
    auto columnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 7;
    columnPattern->isDisableTextStyleAnimation_ = false;

    TextPickerOptionProperty prop1;
    prop1.height = 117.0f;
    prop1.fontheight = 61.0f;
    TextPickerOptionProperty prop2;
    prop2.height = 117.0f;
    prop2.fontheight = 69.0f;
    TextPickerOptionProperty prop3;
    prop3.height = 182.0f;
    prop3.fontheight = 76.0f;
    const TextPickerOptionProperty tmpOptionProperties[] = {prop1, prop1, prop2, prop3, prop2, prop1, prop1};

    columnPattern->optionProperties_.clear();
    for (const auto& prop: tmpOptionProperties) {
        columnPattern->optionProperties_.emplace_back(prop);
    }

    columnPattern->SetOptionShiftDistance();

    std::vector<std::pair<float, float>> expectedValues = {
        {-117.0f, 117.0f},
        {-117.0f, 117.0f},
        {-117.0f, 170.0f},
        {-174.0f, 174.0f},
        {-170.0f, 117.0f},
        {-117.0f, 117.0f},
        {-117.0f, 117.0f}
    };

    for (size_t i = 0; i < columnPattern->optionProperties_.size(); i++) {
        EXPECT_EQ(columnPattern->optionProperties_[i].prevDistance, expectedValues[i].first);
        EXPECT_EQ(columnPattern->optionProperties_[i].nextDistance, expectedValues[i].second);
    }
}

/**
 * @tc.name: SetOptionShiftDistance004
 * @tc.desc: Test SetOptionShiftDistance when isLandscape is false and isDisableTextStyleAnimation_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, SetOptionShiftDistance004, TestSize.Level1)
{
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::PORTRAIT));

    InitTextPickerColumnTestThreeNg();
    auto columnPattern = columnNode_->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    theme->showOptionCount_ = 7;
    columnPattern->isDisableTextStyleAnimation_ = true;
    auto pickerNodeLayout = frameNode_->GetLayoutProperty<TextPickerLayoutProperty>();
    pickerNodeLayout->UpdateDisableTextStyleAnimation(true);

    TextPickerOptionProperty prop1;
    prop1.height = 117.0f;
    prop1.fontheight = 61.0f;
    TextPickerOptionProperty prop2;
    prop2.height = 117.0f;
    prop2.fontheight = 69.0f;
    TextPickerOptionProperty prop3;
    prop3.height = 182.0f;
    prop3.fontheight = 76.0f;
    const TextPickerOptionProperty tmpOptionProperties[] = {prop1, prop1, prop2, prop3, prop2, prop1, prop1};

    columnPattern->optionProperties_.clear();
    for (const auto& prop: tmpOptionProperties) {
        columnPattern->optionProperties_.emplace_back(prop);
    }

    columnPattern->SetOptionShiftDistance();

    std::vector<std::pair<float, float>> expectedValues = {
        {-117.0f, 117.0f},
        {-117.0f, 117.0f},
        {-117.0f, 150.0f},
        {-150.0f, 150.0f},
        {-150.0f, 117.0f},
        {-117.0f, 117.0f},
        {-117.0f, 117.0f}
    };

    for (size_t i = 0; i < columnPattern->optionProperties_.size(); i++) {
        EXPECT_EQ(columnPattern->optionProperties_[i].prevDistance, expectedValues[i].first);
        EXPECT_EQ(columnPattern->optionProperties_[i].nextDistance, expectedValues[i].second);
    }
}

/**
 * @tc.name: TextPickerColumnGetSelectedObject001
 * @tc.desc: Test GetSelectedObject when isDeclarative_ is true and isColumnChange is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnGetSelectedObject001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create TextPicker framenode and columnPattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    /**
     * @tc.step: step2. cover branch GetIsDeclarative() is true.
     */
    MockPipelineContext::GetCurrent()->isDeclarative_ = true;

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);

    /**
    * @tc.step: step3. call method GetSelectedObject.
    */
    std::string result = columnPattern->GetSelectedObject(false, 0);
    std::string expectValue = R"({"value":"text1","index":0,"status":0})";
    EXPECT_EQ(result, expectValue);
}

/**
 * @tc.name: GetPickerSpringMass001
 * @tc.desc: Test GetPickerSpringMass.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, GetPickerSpringMass001, TestSize.Level1)
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
    EXPECT_EQ(columnPattern->tossAnimationController_->GetPickerSpringMass(), 1.f);
}

/**
 * @tc.name: GetPickerMaxSlidingDistance001
 * @tc.desc: Test GetPickerMaxSlidingDistance.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, GetPickerMaxSlidingDistance001, TestSize.Level1)
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
    EXPECT_EQ(columnPattern->tossAnimationController_->GetPickerMaxSlidingDistance(), 30);
}

/**
 * @tc.name: TextPickerColumnGetSelectedObject002
 * @tc.desc: Test GetSelectedObject when isDeclarative_ and isColumnChange are false.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnGetSelectedObject002, TestSize.Level1)
{
    /**
    * @tc.step: step1. create TextPicker framenode and columnPattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    /**
    * @tc.step: step2. cover branch GetIsDeclarative() is true.
    */
    MockPipelineContext::GetCurrent()->isDeclarative_ = true;

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);

    /**
    * @tc.step: step3. call method GetSelectedObject.
    */
    std::string result = columnPattern->GetSelectedObject(true, 1);
    std::string expectValue = R"({"value":"text2","index":1,"status":1})";
    EXPECT_EQ(result, expectValue);
}

/**
 * @tc.name: TextPickerColumnGetSelectedObject003
 * @tc.desc: Test GetSelectedObject when isDeclarative_ and isColumnChange are false.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnGetSelectedObject003, TestSize.Level1)
{
    /**
    * @tc.step: step1. create TextPicker framenode and columnPattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    /**
    * @tc.step: step2. cover branch GetIsDeclarative() is false.
    */
    MockPipelineContext::GetCurrent()->isDeclarative_ = false;

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);

    /**
    * @tc.step: step3. call method GetSelectedObject.
    */
    std::string result = columnPattern->GetSelectedObject(false, 0);
    std::string expectValue = R"({"newValue":"text1","newSelected":0,"status":0})";
    EXPECT_EQ(result, expectValue);
}

/**
 * @tc.name: TextPickerColumnGetSelectedObject004
 * @tc.desc: Test GetSelectedObject when isDeclarative_ is false and isColumnChange are true.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnGetSelectedObject004, TestSize.Level1)
{
    /**
    * @tc.step: step1. create TextPicker framenode and columnPattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    /**
    * @tc.step: step2. cover branch GetIsDeclarative() is false.
    */
    MockPipelineContext::GetCurrent()->isDeclarative_ = false;

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);

    /**
    * @tc.step: step3. call method GetSelectedObject.
    */
    std::string result = columnPattern->GetSelectedObject(true, 1);
    std::string expectValue = R"({"newValue":"text2","newSelected":1,"status":1})";
    EXPECT_EQ(result, expectValue);
}

/**
 * @tc.name: TextPickerColumnGetSelectedObject005
 * @tc.desc: Test GetSelectedObject when status is default value.
 * @tc.type: FUNC
 */
HWTEST_F(TextPickerColumnTestThreeNg, TextPickerColumnGetSelectedObject005, TestSize.Level1)
{
    /**
    * @tc.step: step1. create TextPicker framenode and columnPattern.
    */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TextPickerModelNG::GetInstance()->Create(theme, TEXT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto columnNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild()->GetLastChild()->GetLastChild());
    ASSERT_NE(columnNode, nullptr);
    auto columnPattern = AceType::DynamicCast<FrameNode>(columnNode)->GetPattern<TextPickerColumnPattern>();
    ASSERT_NE(columnPattern, nullptr);
    auto pickerNodeLayout = frameNode->GetLayoutProperty<TextPickerLayoutProperty>();
    ASSERT_NE(pickerNodeLayout, nullptr);

    /**
    * @tc.step: step2. cover branch GetIsDeclarative() is true.
    */
    MockPipelineContext::GetCurrent()->isDeclarative_ = true;

    columnPattern->SetSelected(0);
    columnPattern->SetCurrentIndex(1);
    std::vector<RangeContent> options { { "icon1", "text1" }, { "icon2", "text2" } };
    columnPattern->SetOptions(options);

    /**
    * @tc.step: step3. call method GetSelectedObject without status.
    */
    std::string result = columnPattern->GetSelectedObject(true);
    std::string expectValue = R"({"value":"text2","index":1,"status":0})";
    EXPECT_EQ(result, expectValue);

    /**
    * @tc.step: step4. cover branch GetIsDeclarative() is false.
    */
    MockPipelineContext::GetCurrent()->isDeclarative_ = false;

    /**
    * @tc.step: step5. call method GetSelectedObject without status.
    */
    result = columnPattern->GetSelectedObject(true);
    expectValue = R"({"newValue":"text2","newSelected":1,"status":0})";
    EXPECT_EQ(result, expectValue);
}
} // namespace OHOS::Ace::NG
