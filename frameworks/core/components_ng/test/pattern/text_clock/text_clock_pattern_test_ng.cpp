/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define private public
#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/utils/time_util.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HOURS_WEST = -8;
inline const std::string CLOCK_FORMAT = "hms";
inline const std::string UTC_1 = "1000000000000";
inline const std::string UTC_2 = "2000000000000";
inline const std::string FORMAT_DATA = "08:00:00";
inline const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
} // namespace

struct TestProperty {
    std::optional<std::string> format = std::nullopt;
    std::optional<int32_t> hoursWest = std::nullopt;
};

class TextClockPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateTextClockParagraph(const TestProperty& testProperty);
};

void TextClockPatternTestNg::SetUpTestCase() {}
void TextClockPatternTestNg::TearDownTestCase() {}
void TextClockPatternTestNg::SetUp() {}
void TextClockPatternTestNg::TearDown() {}

RefPtr<FrameNode> TextClockPatternTestNg::CreateTextClockParagraph(const TestProperty& testProperty)
{
    TextClockModelNG textClockModel;
    textClockModel.Create();
    if (testProperty.format.has_value()) {
        textClockModel.SetFormat(testProperty.format.value());
    }
    if (testProperty.hoursWest.has_value()) {
        textClockModel.SetHoursWest(testProperty.hoursWest.value());
    }
    return ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

/**
 * @tc.name: TextClockTest001
 * @tc.desc: Test all the properties of textClock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNg, TextClockTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of textclock.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    EXPECT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    RefPtr<TextClockLayoutProperty> textClockLayoutProperty =
        AceType::DynamicCast<TextClockLayoutProperty>(layoutProperty);
    EXPECT_NE(textClockLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: step3. check whether the properties is correct.
     */
    EXPECT_EQ(textClockLayoutProperty->GetFormat(), CLOCK_FORMAT);
    EXPECT_EQ(textClockLayoutProperty->GetHoursWest(), HOURS_WEST);

    textClockLayoutProperty->UpdateFontFamily(FONT_FAMILY_VALUE);
    auto json = JsonUtil::Create(true);
    textClockLayoutProperty->ToJsonValue(json);
    EXPECT_EQ(textClockLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
}

/**
 * @tc.name: TextClockTest002
 * @tc.desc: Verify whether the layout property, event and controller functions are created.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNg, TextClockTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textclock and get frameNode.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTCLOCK_COMPONENT_TAG, 1, []() { return AceType::MakeRefPtr<TextClockPattern>(); });
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and create layout property.
     * @tc.expected: step2. related function is called.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    EXPECT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step3. call OnModifyDone and UpdateTimeTextCallBack function when default properties.
     * @tc.expected: step3. check whether the content is correct.
     */
    pattern->InitTextClockController();
    pattern->OnModifyDone();
    pattern->UpdateTimeTextCallBack();
    EXPECT_EQ(layoutProperty->GetContent(), FORMAT_DATA);

    /**
     * @tc.steps: step4. get controller and create layout property and event.
     * @tc.expected: step4. related function is called.
     */
    auto controller = pattern->GetTextClockController();
    EXPECT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();
    EXPECT_EQ(layoutProperty->GetContent(), FORMAT_DATA);
    auto clockLayoutProperty = pattern->CreateLayoutProperty();
    EXPECT_NE(clockLayoutProperty, nullptr);
    auto event = pattern->CreateEventHub();
    EXPECT_NE(event, nullptr);

    /**
     * @tc.steps: step5. garbage branch coverage.
     * @tc.expected: step5. related function is called.
     */
    pattern->isStart_ = false;
    pattern->UpdateTimeText();
    pattern->textClockController_ = nullptr;
    pattern->InitUpdateTimeTextCallBack();
    pattern->timeCallback_ = nullptr;
    pattern->UpdateTimeTextCallBack();
    EXPECT_EQ(pattern->textClockController_, nullptr);
    EXPECT_EQ(pattern->timeCallback_, nullptr);
    EXPECT_EQ(layoutProperty->GetContent(), FORMAT_DATA);
}

/**
 * @tc.name: TextClockTest003
 * @tc.desc: Test event function of textclock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockPatternTestNg, TextClockTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textclock and set event.
     */
    TextClockModelNG textClockModel;
    textClockModel.Create();
    std::string utc = UTC_1;
    auto onChange = [&utc](const std::string& isUtc) { utc = isUtc; };
    textClockModel.SetOnDateChange(onChange);

    /**
     * @tc.steps: step2. get textclock frameNode and event.
     * @tc.expected: step2. function is called.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    RefPtr<TextClockEventHub> eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: step3. check whether the value is correct.
     */
    eventHub->FireChangeEvent(UTC_2);
    EXPECT_EQ(utc, UTC_2);
}
} // namespace OHOS::Ace::NG
