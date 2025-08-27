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
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
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

class DatePickerTestToJson : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
    PickerDate limitStartDate_ = PickerDate(1900, 1, 31); // 1900, 1, 31 is the limit start date
    PickerDate limitEndDate_ = PickerDate(2100, 12, 31);  // 2100, 12, 31 is the limit end date
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

void DatePickerTestToJson::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestToJson::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestToJson::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestToJson::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestToJson::CreateDatePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    columnNode_ = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode_, nullptr);
    columnNode_->MarkModifyDone();
    columnPattern_ = columnNode_->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->OnAttachToFrameNode();
}

/**
 * @tc.name: DatePickerTestToJsonEnableHapticFeedback
 * @tc.desc: Test DatePickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestToJson, DatePickerTestToJsonEnableHapticFeedback, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetShowLunar(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.step: step1. Set SetEnableHapticFeedback value.
     */
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    ASSERT_NE(datePickerPattern, nullptr);
    bool enableHapticFeedback = true;
    datePickerPattern->SetEnableHapticFeedback(enableHapticFeedback);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    datePickerPattern->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be true.
     */
    EXPECT_TRUE(json->GetBool("enableHapticFeedback"));
}

/**
 * @tc.name: DatePickerTestToJsondataOption001
 * @tc.desc: Test DatePickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestToJson, DatePickerTestToJsondataOption001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetShowLunar(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto jsonValue = JsonUtil::Create(true);
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto rowLayoutProperty = pickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(rowLayoutProperty, nullptr);
    DatePickerModel::GetInstance()->SetSelectedDate(PickerDate(1990, 1, 1));
    DatePickerModel::GetInstance()->SetMode(DatePickerMode::YEAR_AND_MONTH);
    /**
     * @tc.step: step2. call pattern's ToJsonValue method.
     * @tc.expected: jsonValue2->GetValue("constructor") result content.
     */
    InspectorFilter filter;
    pickerPattern->ToJsonValue(jsonValue, filter);

    /**
     *  @tc.step: step3 check property of dateoption when lunar = true
     */
    auto constructor = jsonValue->GetObject("constructor");
    ASSERT_NE(constructor, nullptr);
    EXPECT_EQ(constructor->GetString("start"), "1970-1-1");
    EXPECT_EQ(constructor->GetString("end"), "2100-12-31");
    EXPECT_EQ(constructor->GetString("selected"), "1990-1-1");
    EXPECT_EQ(constructor->GetString("mode"), "DatePickerMode.YEAR_AND_MONTH");
}

/**
 * @tc.name: DatePickerTestToJsondataOption002
 * @tc.desc: Test DatePickerPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestToJson, DatePickerTestToJsondataOption002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create picker framenode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetShowLunar(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto jsonValue = JsonUtil::Create(true);
    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    auto rowLayoutProperty = pickerPattern->GetLayoutProperty<DataPickerRowLayoutProperty>();
    ASSERT_NE(rowLayoutProperty, nullptr);
    /**
     * @tc.step: step2. call pattern's ToJsonValue method.
     * @tc.expected: jsonValue2->GetValue("constructor") result content.
     */
    DatePickerModel::GetInstance()->SetSelectedDate(PickerDate(1990, 1, 1));
    InspectorFilter filter;
    pickerPattern->ToJsonValue(jsonValue, filter);

    /**
     *  @tc.step: step3 check property of dateoption when lunar = false
     */
    auto constructor = jsonValue->GetObject("constructor");
    ASSERT_NE(constructor, nullptr);
    EXPECT_EQ(constructor->GetString("start"), "1970-2-6");
    EXPECT_EQ(constructor->GetString("end"), "2101-1-30");
    EXPECT_EQ(constructor->GetString("selected"), "1990-1-1");
    EXPECT_EQ(constructor->GetString("mode"), "DatePickerMode.DATE");
}
} // namespace OHOS::Ace::NG
