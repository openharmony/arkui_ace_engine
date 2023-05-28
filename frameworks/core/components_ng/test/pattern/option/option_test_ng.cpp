/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "base/geometry/ng/rect_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/option/option_accessibility_property.h"
#include "core/components_ng/pattern/option/option_layout_algorithm.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/measure_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string OPTION_TEST_TEXT = "option";
} // namespace

class OptionTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    bool InitOptionTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<OptionPattern> optionPattern_;
    RefPtr<OptionAccessibilityProperty> optionAccessibilityProperty_;
};

void OptionTestNg::SetUp()
{
    ASSERT_TRUE(InitOptionTestNg());
}

void OptionTestNg::TearDown()
{
    frameNode_ = nullptr;
    optionPattern_ = nullptr;
    optionAccessibilityProperty_ = nullptr;
}

bool OptionTestNg::InitOptionTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    CHECK_NULL_RETURN(frameNode_, false);

    optionPattern_ = frameNode_->GetPattern<OptionPattern>();
    CHECK_NULL_RETURN(optionPattern_, false);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(textNode, false);

    optionPattern_->SetTextNode(textNode);

    optionAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<OptionAccessibilityProperty>();
    CHECK_NULL_RETURN(optionAccessibilityProperty_, false);
    return true;
}

/**
 * @tc.name: OptionAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of option.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionAccessibilityPropertyGetText001, TestSize.Level1)
{
    auto textLayoutProperty = optionPattern_->text_->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(OPTION_TEST_TEXT);
    EXPECT_EQ(optionAccessibilityProperty_->GetText(), OPTION_TEST_TEXT);
}

/**
 * @tc.name: OptionAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of option.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    optionAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = optionAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: OptionTestNg001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionTestNg001, TestSize.Level1)
{
    OHOS::Ace::NG::OptionLayoutAlgorithm rosenOptionLayoutAlgorithm;
    rosenOptionLayoutAlgorithm.horInterval_ = 2.0;
    EXPECT_FLOAT_EQ(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    auto rosenMakeRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::LayoutProperty>();
    auto rosenRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::GeometryNode>();
    rosenRefPtr->margin_ = nullptr;
    OHOS::Ace::NG::LayoutWrapper* rosenLayoutWrapper = new LayoutWrapper(nullptr, rosenRefPtr, rosenMakeRefPtr);
    rosenOptionLayoutAlgorithm.Layout(rosenLayoutWrapper);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Option Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create option frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(frameNode, nullptr);
    auto optionPattern = frameNode->GetPattern<OptionPattern>();
    ASSERT_NE(optionPattern, nullptr);
    optionPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get option accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto optionAccessibilityProperty = frameNode->GetAccessibilityProperty<OptionAccessibilityProperty>();
    ASSERT_NE(optionAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. Call the callback function in optionAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(optionAccessibilityProperty->ActActionSelect());
}
} // namespace OHOS::Ace::NG
