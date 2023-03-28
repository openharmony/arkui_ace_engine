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

#define private public
#define protected public
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string SELECT_TEXT = "select";
constexpr int32_t SELECT_ERROR = -1;
constexpr int32_t CURRENT_INDEX = 10;
} // namespace
class SelectAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    bool InitSelectTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;
    RefPtr<SelectAccessibilityProperty> selectAccessibilityProperty_;
};

void SelectAccessibilityPropertyTestNg::SetUp()
{
    ASSERT_TRUE(InitSelectTestNg());
}

void SelectAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    selectPattern_ = nullptr;
    selectAccessibilityProperty_ = nullptr;
}

bool SelectAccessibilityPropertyTestNg::InitSelectTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::SELECT_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<SelectPattern>(); });
    CHECK_NULL_RETURN(frameNode_, false);

    selectPattern_ = frameNode_->GetPattern<SelectPattern>();
    CHECK_NULL_RETURN(selectPattern_, false);

    selectAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<SelectAccessibilityProperty>();
    CHECK_NULL_RETURN(selectAccessibilityProperty_, false);
    return true;
}

/**
 * @tc.name: SelectAccessibilityPropertyGetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectAccessibilityPropertyTestNg, SelectAccessibilityPropertyGetCurrentIndex001, TestSize.Level1)
{
    EXPECT_EQ(selectAccessibilityProperty_->GetCurrentIndex(), SELECT_ERROR);

    selectPattern_->selected_ = CURRENT_INDEX;
    EXPECT_EQ(selectAccessibilityProperty_->GetCurrentIndex(), CURRENT_INDEX);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetBeginIndex001
 * @tc.desc: Test GetBeginIndex of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectAccessibilityPropertyTestNg, SelectAccessibilityPropertyGetBeginIndex001, TestSize.Level1)
{
    EXPECT_EQ(selectAccessibilityProperty_->GetBeginIndex(), SELECT_ERROR);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });

    selectPattern_->options_.push_back(option);
    EXPECT_EQ(selectAccessibilityProperty_->GetBeginIndex(), 0);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetEndIndex001
 * @tc.desc: Test GetEndIndex of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectAccessibilityPropertyTestNg, SelectAccessibilityPropertyGetEndIndex001, TestSize.Level1)
{
    EXPECT_EQ(selectAccessibilityProperty_->GetEndIndex(), SELECT_ERROR);

    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });

    selectPattern_->options_.push_back(option);
    selectPattern_->options_.push_back(option);
    EXPECT_EQ(selectAccessibilityProperty_->GetEndIndex(), 1);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectAccessibilityPropertyTestNg, SelectAccessibilityPropertyGetText001, TestSize.Level1)
{
    EXPECT_EQ(selectAccessibilityProperty_->GetText(), EMPTY_TEXT);

    selectPattern_->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(selectPattern_->text_, nullptr);

    selectPattern_->SetValue(SELECT_TEXT);
    EXPECT_EQ(selectAccessibilityProperty_->GetText(), SELECT_TEXT);
}

/**
 * @tc.name: SelectAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of select.
 * @tc.type: FUNC
 */
HWTEST_F(SelectAccessibilityPropertyTestNg, SelectAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    selectAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = selectAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
} // namespace OHOS::Ace::NG
