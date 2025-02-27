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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/counter/counter_theme_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"

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

class CounterTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(CounterModelNG)>& callback = nullptr);

    RefPtr<CounterNode> frameNode_;
    RefPtr<CounterPattern> pattern_;
    RefPtr<LayoutProperty> layoutProperty_;
};

void CounterTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto themeConstants = CreateThemeConstants(THEME_PATTERN_COUNTER);
    auto counterTheme = CounterTheme::Builder().Build(themeConstants);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(counterTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly(Return(CounterThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants)));
}

void CounterTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void CounterTestNg::SetUp() {}

void CounterTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
}

void CounterTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<CounterNode>(element);
    pattern_ = frameNode_->GetPattern<CounterPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty();
}

void CounterTestNg::Create(const std::function<void(CounterModelNG)>& callback)
{
    CounterModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: CounterPatternTest002
 * @tc.desc: Test counter SetOnInc and SetOnDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest002, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        auto counterEventFunc1 = []() {};
        model.SetOnInc(std::move(counterEventFunc1));
        auto counterEventFunc2 = []() {};
        model.SetOnDec(std::move(counterEventFunc2));
    });

    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subGestureHub = subNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(subGestureHub->parallelCombineClick, false);
    EXPECT_NE(subGestureHub->clickEventActuator_->userCallback_, nullptr);

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addGestureHub = addNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(addGestureHub->parallelCombineClick, false);
    EXPECT_NE(addGestureHub->clickEventActuator_->userCallback_, nullptr);
}

/**
 * @tc.name: CounterPatternTest003
 * @tc.desc: Test counter SetHeight and SetWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest003, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetWidth(WIDTH);
        model.SetHeight(HEIGHT);
    });

    auto selfIdealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
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
    Create([](CounterModelNG model) {
        model.SetControlWidth(WIDTH);
        model.SetStateChange(true);
        model.SetBackgroundColor(COLOR);
    });

    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor(), COLOR);
}

/**
 * @tc.name: CounterPatternTest005
 * @tc.desc: Test CounterNode AddChildToGroup function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest005, TestSize.Level1)
{
    Create();

    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto childNode = AceType::MakeRefPtr<FrameNode>(FRAME_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>());
    int32_t contentId = pattern_->GetContentId();
    auto contentChildNode = frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(contentId));
    frameNode_->AddChildToGroup(childNode);
    EXPECT_EQ(contentChildNode->children_.size(), 1);

    frameNode_->DeleteChildFromGroup();
    EXPECT_EQ(contentChildNode->children_.size(), 0);
}

/**
 * @tc.name: CounterPatternTest007
 * @tc.desc: Test counter SetEnableInc function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest007, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetEnableInc(true);
        model.SetEnableDec(true);
    });

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetEventHub<EventHub>();
    EXPECT_EQ(addEventHub->IsEnabled(), true);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);
    EXPECT_EQ(subEventHub->IsEnabled(), true);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);
}

/**
 * @tc.name: CounterPatternTest008
 * @tc.desc: Test counter SetEnableDec function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest008, TestSize.Level1)
{
    Create([](CounterModelNG model) {
        model.SetEnableInc(false);
        model.SetEnableDec(false);
    });

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetEventHub<EventHub>();
    EXPECT_EQ(addEventHub->IsEnabled(), false);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
    EXPECT_EQ(subEventHub->IsEnabled(), false);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
}

/**
 * @tc.name: CounterPatternTest009
 * @tc.desc: Test counter Create function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest009, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    CounterModelNG model;
    model.Create();
    GetInstance();
    EXPECT_TRUE(pattern_->HasSubNode());
    EXPECT_TRUE(pattern_->HasContentNode());
    EXPECT_TRUE(pattern_->HasAddNode());

    /**
     * Create again,cover all branches in function Create
     */
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    model.Create();
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

/**
 * @tc.name: CounterPatternTest011
 * @tc.desc: Test counter SetEnableInc function.
 * @tc.type: FUNC
 */
HWTEST_F(CounterTestNg, CounterPatternTest011, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();

    auto addId = pattern_->GetAddId();
    auto addNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(addId)));
    auto addRenderContext = addNode->GetRenderContext();
    auto addEventHub = addNode->GetEventHub<EventHub>();
    auto subId = pattern_->GetSubId();
    auto subNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(frameNode_->GetChildIndexById(subId)));
    auto subRenderContext = subNode->GetRenderContext();
    auto subEventHub = subNode->GetEventHub<EventHub>();
    model.SetEnableInc(AceType::RawPtr(frameNode_), true);
    model.SetEnableDec(AceType::RawPtr(frameNode_), true);
    EXPECT_EQ(addEventHub->IsEnabled(), true);
    EXPECT_EQ(subEventHub->IsEnabled(), true);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), DEFAULT_BUTTON_OPACITY);

    model.SetEnableInc(AceType::RawPtr(frameNode_), false);
    model.SetEnableDec(AceType::RawPtr(frameNode_), false);
    EXPECT_EQ(addEventHub->IsEnabled(), false);
    EXPECT_EQ(subEventHub->IsEnabled(), false);
    EXPECT_EQ(addRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
    EXPECT_EQ(subRenderContext->GetOpacityValue(-1), BUTTON_ALPHA_DISABLED);
}

/**
 * @tc.name: CounterLayoutAlgorithmTestNg001
 * @tc.desc: test counter Layout.
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(CounterTestNg, CounterLayoutAlgorithmTestNg001, TestSize.Level1)
{
    CounterModelNG model;
    model.Create();
    GetInstance();
    
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto counterPattern = AceType::DynamicCast<CounterPattern>(frameNode->GetPattern());
    ASSERT_NE(counterPattern, nullptr);
    auto counterLayoutAlgorithm = counterPattern->CreateLayoutAlgorithm();
    ASSERT_NE(counterLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    counterLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(layoutDirection, TextDirection::RTL);
}
} // namespace OHOS::Ace::NG
