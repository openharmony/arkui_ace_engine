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
#include "core/components_ng/pattern/text_clock/text_clock_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t HOURS_WEST = -8;
constexpr int32_t HOURS_WEST2 = INT_MAX;
constexpr int32_t TOTAL_MINUTE_OF_HOUR = 60;
inline const std::string CLOCK_FORMAT = "hms";
inline const std::string UTC_1 = "1000000000000";
inline const std::string UTC_2 = "2000000000000";
inline const std::string FORMAT_DATA = "08:00:00";
inline const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const std::string EMPTY_TEXT = "";
const std::string TEXTCLOCK_CONTENT = "08:00:00";

int32_t GetSystemTimeZone()
{
    struct timeval currentTime {};
    struct timezone timeZone {};
    gettimeofday(&currentTime, &timeZone);
    int32_t hoursWest = timeZone.tz_minuteswest / TOTAL_MINUTE_OF_HOUR;
    return hoursWest;
}
} // namespace

struct TestProperty {
    std::optional<std::string> format = std::nullopt;
    std::optional<int32_t> hoursWest = std::nullopt;
};

class TextClockTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateTextClockParagraph(const TestProperty& testProperty);
};

void TextClockTestNG::SetUpTestCase() {}
void TextClockTestNG::TearDownTestCase() {}
void TextClockTestNG::SetUp() {}
void TextClockTestNG::TearDown() {}

RefPtr<FrameNode> TextClockTestNG::CreateTextClockParagraph(const TestProperty& testProperty)
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
HWTEST_F(TextClockTestNG, TextClockTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of textclock.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT);
    testProperty.hoursWest = std::make_optional(HOURS_WEST);

    /**
     * @tc.steps: step2. create frameNode to get layout properties.
     * @tc.expected: related function is called.
     */
    RefPtr<FrameNode> frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextClockLayoutProperty> textClockLayoutProperty =
        AceType::DynamicCast<TextClockLayoutProperty>(layoutProperty);
    ASSERT_NE(textClockLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. get the properties of all settings.
     * @tc.expected: check whether the properties is correct.
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
HWTEST_F(TextClockTestNG, TextClockTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textclock and get frameNode.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(FORMAT_DATA);
    auto frameNode = CreateTextClockParagraph(testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto textNode = AceType::DynamicCast<FrameNode>(frameNode->GetLastChild());
    ASSERT_NE(textNode, nullptr);

    /**
     * @tc.steps: step2. get pattern and create layout property.
     * @tc.expected: related function is called.
     */
    auto pattern = frameNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextClockLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. call OnModifyDone and UpdateTimeTextCallBack function when default properties.
     * @tc.expected: check whether the content is correct.
     */
    pattern->InitTextClockController();
    pattern->OnModifyDone();
    pattern->UpdateTimeTextCallBack();
    EXPECT_EQ(textLayoutProperty->GetContent(), FORMAT_DATA);

    /**
     * @tc.steps: step4. get controller and create layout property and event.
     * @tc.expected: related function is called.
     */
    auto controller = pattern->GetTextClockController();
    ASSERT_NE(controller, nullptr);
    controller->Start();
    controller->Stop();
    EXPECT_EQ(textLayoutProperty->GetContent(), FORMAT_DATA);
    auto clockLayoutProperty = pattern->CreateLayoutProperty();
    ASSERT_NE(clockLayoutProperty, nullptr);
    auto event = pattern->CreateEventHub();
    ASSERT_NE(event, nullptr);

    /**
     * @tc.steps: step5. garbage branch coverage.
     * @tc.expected: related function is called.
     */
    pattern->isStart_ = false;
    pattern->UpdateTimeText();
    pattern->textClockController_ = nullptr;
    pattern->InitUpdateTimeTextCallBack();
    pattern->timeCallback_ = nullptr;
    pattern->UpdateTimeTextCallBack();
    EXPECT_EQ(pattern->textClockController_, nullptr);
    EXPECT_EQ(pattern->timeCallback_, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContent(), FORMAT_DATA);
}

/**
 * @tc.name: TextClockTest003
 * @tc.desc: Test event function of textclock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockTestNG, TextClockTest003, TestSize.Level1)
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
     * @tc.expected: function is called.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<TextClockEventHub> eventHub = frameNode->GetEventHub<NG::TextClockEventHub>();
    ASSERT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step3. call the event entry function.
     * @tc.expected: check whether the value is correct.
     */
    eventHub->FireChangeEvent(UTC_2);
    EXPECT_EQ(utc, UTC_2);
}
/**
 * @tc.name: TextClockTest004
 * @tc.desc: Test GetHourWest function of textclock.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockTestNG, TextClockTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize the format property of textclock.
     */
    TestProperty testProperty;
    testProperty.format = std::make_optional(CLOCK_FORMAT);

    /**
     * @tc.steps: step2. construct different params.
     */
    auto systemTimeZone = GetSystemTimeZone();
    std::vector<std::vector<int32_t>> params = { { HOURS_WEST2, systemTimeZone }, { HOURS_WEST, HOURS_WEST } };
    for (int turn = 0; turn < params.size(); turn++) {
        testProperty.hoursWest = std::make_optional(params[turn][0]);
        /**
         * @tc.steps: step3. create textclock and get frameNode.
         */
        auto frameNode = CreateTextClockParagraph(testProperty);
        ASSERT_NE(frameNode, nullptr);
        /**
         * @tc.steps: step4. get pattern.
         * @tc.expected: related function is called and return right value.
         */
        auto pattern = frameNode->GetPattern<TextClockPattern>();
        ASSERT_NE(pattern, nullptr);
        EXPECT_EQ(pattern->GetHoursWest(), params[turn][1]);
    }
}

/**
 * @tc.name: TextClockAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of textClockAccessibilityProperty.
 * @tc.type: FUNC
 */

HWTEST_F(TextClockTestNG, TextClockAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXTCLOCK_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextClockPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);
    auto textClockAccessibilityProperty = frameNode->GetAccessibilityProperty<TextClockAccessibilityProperty>();
    ASSERT_NE(textClockAccessibilityProperty, nullptr);
    textClockAccessibilityProperty->SetHost(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    EXPECT_EQ(textClockAccessibilityProperty->GetText(), EMPTY_TEXT);

    textLayoutProperty->UpdateContent(TEXTCLOCK_CONTENT);
    EXPECT_EQ(textClockAccessibilityProperty->GetText(), TEXTCLOCK_CONTENT);
}
} // namespace OHOS::Ace::NG
