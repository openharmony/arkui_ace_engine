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

#include <algorithm>
#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension WIDTH = 10.0_vp;
constexpr Dimension HEIGHT = 10.0_vp;
const std::string FRAME_ITEM_ETS_TAG = "FrameItem";
const Color COLOR = Color::BLUE;
constexpr double DEFAULT_BUTTON_OPACITY = 1.0;
} // namespace

class CounterTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CounterTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}
void CounterTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}
void CounterTestNg::SetUp() {}
void CounterTestNg::TearDown() {}

/**
 * @tc.name: CounterPatternTest001
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest001, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    EXPECT_NE(frameNode, nullptr);
    counterModelNG.Create();
    auto frameNode1 = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode1, nullptr);
}

/**
 * @tc.name: CounterPatternTest002
 * @tc.desc: Test counter SetOnInc and SetOnDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest002, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto counterEventFunc1 = []() {};
    counterModelNG.SetOnInc(std::move(counterEventFunc1));
    auto counterEventFunc2 = []() {};
    counterModelNG.SetOnDec(std::move(counterEventFunc2));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: CounterPatternTest003
 * @tc.desc: Test counter SetHeight and SetWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest003, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    counterModelNG.SetWidth(WIDTH);
    counterModelNG.SetHeight(HEIGHT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto selfIdealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    EXPECT_EQ(selfIdealSize->Width()->dimension_, WIDTH);
    EXPECT_EQ(selfIdealSize->Height()->dimension_, HEIGHT);
}

/**
 * @tc.name: CounterPatternTest004
 * @tc.desc: Test counter SetControlWidth, SetStateChange and SetBackgroundColor function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest004, TestSize.Level1)
{
    // create mock theme manager
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    counterModelNG.SetControlWidth(WIDTH);
    counterModelNG.SetStateChange(true);
    counterModelNG.SetBackgroundColor(COLOR);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor(), COLOR);
}

/**
 * @tc.name: CounterPatternTest005
 * @tc.desc: Test CounterNode AddChildToGroup function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest005, TestSize.Level1)
{
    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto counterNode = AceType::DynamicCast<CounterNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(counterNode, nullptr);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t contentId = counterNode->GetPattern<CounterPattern>()->GetContentId();
    auto contentChildNode = counterNode->GetChildAtIndex(counterNode->GetChildIndexById(contentId));
    counterNode->AddChildToGroup(frameNode);
    EXPECT_EQ(contentChildNode->children_.size(), 1);
}

/**
 * @tc.name: CounterPatternTest006
 * @tc.desc: Test CounterNode DeleteChildFromGroup function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest006, TestSize.Level1)
{
    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto counterNode = AceType::DynamicCast<CounterNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(counterNode, nullptr);

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t contentId = counterNode->GetPattern<CounterPattern>()->GetContentId();
    auto contentChildNode = counterNode->GetChildAtIndex(counterNode->GetChildIndexById(contentId));
    counterNode->AddChildToGroup(frameNode);
    EXPECT_EQ(contentChildNode->children_.size(), 1);
    counterNode->DeleteChildFromGroup();
    EXPECT_EQ(contentChildNode->children_.size(), 0);
}

/**
 * @tc.name: CounterPatternTest007
 * @tc.desc: Test counter SetEnableInc function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest007, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto addId = frameNode->GetPattern<CounterPattern>()->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(addId)));
    auto addNodeRenderContext = addNode->GetRenderContext();
    ASSERT_NE(addNodeRenderContext, nullptr);
    auto eventHub = addNode->GetEventHub<EventHub>();
    counterModelNG.SetEnableInc(true);
    EXPECT_EQ(eventHub->IsEnabled(), true);
    auto opacity = addNodeRenderContext->GetOpacityValue(-1);
    EXPECT_EQ(opacity, DEFAULT_BUTTON_OPACITY);

    counterModelNG.SetEnableInc(false);
    EXPECT_EQ(eventHub->IsEnabled(), false);
    opacity = addNodeRenderContext->GetOpacityValue(-1);
    EXPECT_EQ(opacity, BUTTON_ALPHA_DISABLED);
}

/**
 * @tc.name: CounterPatternTest008
 * @tc.desc: Test counter SetEnableDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest008, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto counterTheme = AceType::MakeRefPtr<CounterTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));

    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = stack->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto subId = frameNode->GetPattern<CounterPattern>()->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(subId)));
    auto subNodeRenderContext = subNode->GetRenderContext();
    ASSERT_NE(subNodeRenderContext, nullptr);
    auto eventHub = subNode->GetEventHub<EventHub>();
    counterModelNG.SetEnableDec(true);
    EXPECT_EQ(eventHub->IsEnabled(), true);
    auto opacity = subNodeRenderContext->GetOpacityValue(-1);
    EXPECT_EQ(opacity, DEFAULT_BUTTON_OPACITY);

    counterModelNG.SetEnableDec(false);
    EXPECT_EQ(eventHub->IsEnabled(), false);
    opacity = subNodeRenderContext->GetOpacityValue(-1);
    EXPECT_EQ(opacity, BUTTON_ALPHA_DISABLED);
}

/**
 * @tc.name: CounterPatternTest009
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest009, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    CounterModelNG counterModelNG;
    counterModelNG.Create();
    auto counterNode = AceType::DynamicCast<CounterNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(counterNode, nullptr);
    /**
     * Create again,cover all branches in function Create
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    counterModelNG.Create();
}

/**
 * @tc.name: CounterPatternTest010
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest010, TestSize.Level1)
{
    auto columnNode =
        CounterNode::GetOrCreateCounterNode("Column", 100, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    ASSERT_NE(columnNode, nullptr);
    auto subNode =
        CounterNode::GetOrCreateCounterNode("Column", 101, []() { return AceType::MakeRefPtr<CounterPattern>(); });
    ASSERT_NE(subNode, nullptr);
    subNode->MountToParent(columnNode);
    CounterNode::GetOrCreateCounterNode("Counter", 101, []() { return AceType::MakeRefPtr<CounterPattern>(); });
}
} // namespace OHOS::Ace::NG
