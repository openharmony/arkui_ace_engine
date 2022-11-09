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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
inline const std::string MARQUEE_SRC = "marquee";
inline constexpr int32_t MARQUEE_LOOP = 3;
inline constexpr double MARQUEE_SCROLL_AMOUNT = 10.0;
} // namespace

struct TestProperty {
    std::optional<std::string> src = std::nullopt;
    std::optional<int32_t> loop = std::nullopt;
    std::optional<double> scrollAmount = std::nullopt;
    std::optional<MarqueeDirection> direction = std::nullopt;
    std::optional<bool> playerStatus = std::nullopt;
};

class MarqueePatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateMarqueeParagraph(const TestProperty& testProperty);
};

void MarqueePatternTestNg::SetUpTestCase() {}
void MarqueePatternTestNg::TearDownTestCase() {}
void MarqueePatternTestNg::SetUp() {}
void MarqueePatternTestNg::TearDown() {}

RefPtr<FrameNode> MarqueePatternTestNg::CreateMarqueeParagraph(const TestProperty& testProperty)
{
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    if (testProperty.src.has_value()) {
        marqueeModel.SetValue(testProperty.src.value());
    }
    if (testProperty.playerStatus.has_value()) {
        marqueeModel.SetPlayerStatus(testProperty.playerStatus.value());
    }
    if (testProperty.scrollAmount.has_value()) {
        marqueeModel.SetScrollAmount(testProperty.scrollAmount.value());
    }
    if (testProperty.loop.has_value()) {
        marqueeModel.SetLoop(testProperty.loop.value());
    }
    if (testProperty.direction.has_value()) {
        marqueeModel.SetDirection(testProperty.direction.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // MarqueeView pop
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: MarqueeFrameNodeCreator001
 * @tc.desc: Test all the properties of marquee.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueeFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.loop = std::make_optional(MARQUEE_LOOP);
    testProperty.playerStatus = std::make_optional(false);
    testProperty.direction = std::make_optional(MarqueeDirection::LEFT);
    testProperty.scrollAmount = std::make_optional(MARQUEE_SCROLL_AMOUNT);

    auto frameNode = CreateMarqueeParagraph(testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    auto marqueeLayoutProperty = AceType::DynamicCast<MarqueeLayoutProperty>(layoutProperty);
    EXPECT_EQ(marqueeLayoutProperty == nullptr, false);
    EXPECT_EQ(marqueeLayoutProperty->GetLoop(), MARQUEE_LOOP);
    EXPECT_EQ(marqueeLayoutProperty->GetDirection(), MarqueeDirection::LEFT);
    EXPECT_EQ(marqueeLayoutProperty->GetPlayerStatus(), false);
    EXPECT_EQ(marqueeLayoutProperty->GetScrollAmount(), MARQUEE_SCROLL_AMOUNT);

    auto textChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_EQ(textChild == nullptr, false);
    auto textLayoutProperty = textChild->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty == nullptr, false);
    EXPECT_EQ(textLayoutProperty->GetContent(), MARQUEE_SRC);
}

/**
 * @tc.name: MarqueeFrameNodeCreator002
 * @tc.desc: Test all the properties of marquee.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueeFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.src = std::make_optional(MARQUEE_SRC);
    testProperty.playerStatus = std::make_optional(false);

    auto frameNode = CreateMarqueeParagraph(testProperty);
    EXPECT_EQ(frameNode == nullptr, false);
    auto pattern = frameNode->GetPattern<MarqueePattern>();
    EXPECT_EQ(pattern == nullptr, false);
    auto layoutProperty = pattern->CreateLayoutProperty();
    EXPECT_EQ(layoutProperty == nullptr, false);
    auto event = pattern->CreateEventHub();
    EXPECT_EQ(event == nullptr, false);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_EQ(layoutAlgorithm == nullptr, false);
}

/**
 * @tc.name: MarqueeFrameNodeCreator003
 * @tc.desc: Test Marquee onChange event.
 * @tc.type: FUNC
 */
HWTEST_F(MarqueePatternTestNg, MarqueeFrameNodeCreator003, TestSize.Level1)
{
    MarqueeModelNG marqueeModel;
    marqueeModel.Create();
    bool isStart = false;
    auto onChangeStart = [&isStart]() { isStart = true; };
    marqueeModel.SetOnStart(onChangeStart);
    bool isBounce = false;
    auto onChangeBounce = [&isBounce]() { isBounce = true; };
    marqueeModel.SetOnBounce(onChangeBounce);
    bool isFinish = false;
    auto onChangeFinish = [&isFinish]() { isFinish = true; };
    marqueeModel.SetOnFinish(onChangeFinish);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(frameNode == nullptr, false);
    RefPtr<MarqueeEventHub> eventHub = frameNode->GetEventHub<NG::MarqueeEventHub>();
    EXPECT_EQ(eventHub == nullptr, false);
    eventHub->FireStartEvent();
    EXPECT_EQ(isStart, true);
    eventHub->FireBounceEvent();
    EXPECT_EQ(isBounce, true);
    eventHub->FireFinishEvent();
    EXPECT_EQ(isFinish, true);
}
} // namespace OHOS::Ace::NG
