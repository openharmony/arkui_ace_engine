/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "core/components_ng/pattern/option/option_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string OPTION_TEST_TEXT = "option";
} // namespace
class OptionAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    bool InitOptionTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<OptionPattern> optionPattern_;
    RefPtr<OptionAccessibilityProperty> optionAccessibilityProperty_;
};

void OptionAccessibilityPropertyTestNg::SetUp()
{
    ASSERT_TRUE(InitOptionTestNg());
}

void OptionAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    optionPattern_ = nullptr;
    optionAccessibilityProperty_ = nullptr;
}

bool OptionAccessibilityPropertyTestNg::InitOptionTestNg()
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
HWTEST_F(OptionAccessibilityPropertyTestNg, OptionAccessibilityPropertyGetText001, TestSize.Level1)
{
    auto textLayoutProperty = optionPattern_->text_->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(OPTION_TEST_TEXT);
    EXPECT_EQ(optionAccessibilityProperty_->GetText(), OPTION_TEST_TEXT);
}
} // namespace OHOS::Ace::NG
