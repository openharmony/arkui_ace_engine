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
#include <utility>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/date_time_animation_controller.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_events.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class DatePickerTestTwoNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
    std::unique_ptr<DatePickerModelNG> datePickerNg_ = nullptr;
    std::unique_ptr<DatePickerDialogModelNG> datePickerDialogNg_ = nullptr;
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

void DatePickerTestTwoNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestTwoNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestTwoNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
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
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    if (datePickerNg_ == nullptr) {
        datePickerNg_.reset(new DatePickerModelNG());
    }
    if (datePickerDialogNg_ == nullptr) {
        datePickerDialogNg_.reset(new DatePickerDialogModelNG());
    }
}

void DatePickerTestTwoNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
    if (datePickerNg_) {
        auto item = datePickerNg_.release();
        datePickerNg_.reset();
        delete item;
    }
    if (datePickerDialogNg_) {
        auto item = datePickerDialogNg_.release();
        datePickerDialogNg_.reset();
        delete item;
    }
}

void DatePickerTestTwoNg::CreateDatePickerColumnNode()
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
 * @tc.name: SetDatePickerDialogShow001
 * @tc.desc: Test SetDatePickerDialogShow.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, SetDatePickerDialogShow001, TestSize.Level1)
{
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> dateChangeEvent;
    std::function<void(const std::string&)> dateAcceptEvent;
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelEvent = []{ std::cout << "cancelEvent successed."<< std::endl; };
    acceptEvent = [](const std::string& dateString) {
        std::cout << "acceptEvent dateString is " << dateString << std::endl; };
    changeEvent = [](const std::string& dateString) {
        std::cout << "changeEvent dateString is " << dateString << std::endl; };
    dateChangeEvent = [](const std::string& dateString) {
        std::cout << "dateChangeEvent dateString is " << dateString << std::endl; };
    dateAcceptEvent = [](const std::string& dateString) {
        std::cout << "dateAcceptEvent dateString is " << dateString << std::endl; };
    PickerDialogInfo pickerDialog;
    std::vector<ButtonInfo> buttonInfos;
    NG::DatePickerSettingData settingData;
    DatePickerType pickerType = DatePickerType::DATE;
    PickerDialogEvent pickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    datePickerDialogNg_->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
    EXPECT_FALSE(pickerDialog.alignment.has_value());
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto tmpVersion = pipeline->minPlatformVersion_;
    pipeline->minPlatformVersion_ = 0;
    datePickerDialogNg_->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
    EXPECT_FALSE(pickerDialog.alignment.has_value());
    pipeline->minPlatformVersion_ = tmpVersion;
}

/**
 * @tc.name: SetDatePickerDialogShow002
 * @tc.desc: Test SetDatePickerDialogShow.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestTwoNg, SetDatePickerDialogShow002, TestSize.Level1)
{
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> dateChangeEvent;
    std::function<void(const std::string&)> dateAcceptEvent;
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelEvent = []{ std::cout << "cancelEvent successed."<< std::endl; };
    acceptEvent = [](const std::string& dateString) {
        std::cout << "acceptEvent dateString is " << dateString << std::endl; };
    changeEvent = [](const std::string& dateString) {
        std::cout << "changeEvent dateString is " << dateString << std::endl; };
    dateChangeEvent = [](const std::string& dateString) {
        std::cout << "dateChangeEvent dateString is " << dateString << std::endl; };
    dateAcceptEvent = [](const std::string& dateString) {
        std::cout << "dateAcceptEvent dateString is " << dateString << std::endl; };
    DatePickerType pickerType = DatePickerType::DATE;
    PickerDialogInfo pickerDialog;
    std::vector<ButtonInfo> buttonInfos;
    NG::DatePickerSettingData settingData;
    PickerDialogEvent pickerDialogEvent { nullptr, nullptr, nullptr, nullptr };
    Shadow textShadow;
    textShadow.SetOffsetX(5.0);
    textShadow.SetOffsetY(5.0);
    textShadow.SetBlurRadius(0.0);
    textShadow.SetColor(Color::BLUE);
    pickerDialog.isEndDate = true;
    pickerDialog.isStartDate = true;
    pickerDialog.shadow = textShadow;
    pickerDialog.isSelectedDate = true;
    pickerDialog.backgroundBlurStyle = 2;
    pickerDialog.alignment = DialogAlignment::DEFAULT;
    pickerDialog.offset = DimensionOffset(Offset(0, -1.0f));
    pickerDialog.backgroundColor = Color::FromString("#FFFF0000");
    datePickerDialogNg_->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
    EXPECT_EQ(pickerDialog.isEndDate, true);
}
} // namespace OHOS::Ace::NG