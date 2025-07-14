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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double TEST_FONT_SIZE = 10.0;
}

class TimePickerResourceTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Theme> GetThemeByType(ThemeType type);

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;
};

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

void TimePickerResourceTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerResourceTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerResourceTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    pickerThem_ = MockThemeDefault::GetPickerTheme();
    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {return GetThemeByType(type);});

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {return GetThemeByType(type);});
}

void TimePickerResourceTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> TimePickerResourceTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == DialogTheme::TypeId()) {
        return dialogTheme_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerThem_;
    } else if (type == ButtonTheme::TypeId()) {
        return buttonTheme_;
    } else {
        return nullptr;
    }
}

/**
 * @tc.name: UpdateDisappearTextStyle001
 * @tc.desc: Test TimePickerRowPattern UpdateDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerResourceTest, UpdateDisappearTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateDisappearTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetDisappearColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetDisappearFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateNormalTextStyle001
 * @tc.desc: Test TimePickerRowPattern UpdateNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerResourceTest, UpdateNormalTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateNormalTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

/**
 * @tc.name: UpdateSelectedTextStyle001
 * @tc.desc: Test TimePickerRowPattern UpdateSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerResourceTest, UpdateSelectedTextStyle001, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetIsSystemColorChange(true);

    PickerTextStyle textStyle;
    textStyle.textColor = Color::RED;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::RED);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE));

    textStyle.textColor = Color::GREEN;
    textStyle.fontSize = Dimension(TEST_FONT_SIZE + 1);
    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(pickerPattern, nullptr);
    pickerPattern->UpdateSelectedTextStyle(textStyle);

    EXPECT_EQ(pickerProperty->GetSelectedColor().value(), Color::GREEN);
    EXPECT_EQ(pickerProperty->GetSelectedFontSize().value(), Dimension(TEST_FONT_SIZE + 1));
}

} // namespace OHOS::Ace::NG
