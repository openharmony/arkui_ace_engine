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
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
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
const std::string TITLE_BAR_TEXT = "title";
} // namespace
class TitleBarAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    bool InitTitleBarTestNg();
    RefPtr<TitleBarNode> frameNode_;
    RefPtr<TitleBarPattern> titleBarPattern_;
    RefPtr<TitleBarAccessibilityProperty> titleBarAccessibilityProperty_;
};

void TitleBarAccessibilityPropertyTestNg::SetUp()
{
    ASSERT_TRUE(InitTitleBarTestNg());
}

void TitleBarAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    titleBarPattern_ = nullptr;
    titleBarAccessibilityProperty_ = nullptr;
}

bool TitleBarAccessibilityPropertyTestNg::InitTitleBarTestNg()
{
    frameNode_ =
        AceType::MakeRefPtr<TitleBarNode>(V2::TITLE_BAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId());
    CHECK_NULL_RETURN(frameNode_, false);
    frameNode_->InitializePatternAndContext();

    titleBarPattern_ = frameNode_->GetPattern<TitleBarPattern>();
    CHECK_NULL_RETURN(titleBarPattern_, false);

    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(titleNode, false);
    frameNode_->SetTitle(titleNode);

    titleBarAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<TitleBarAccessibilityProperty>();
    CHECK_NULL_RETURN(titleBarAccessibilityProperty_, false);
    return true;
}

/**
 * @tc.name: TitleBarAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of titleBar.
 * @tc.type: FUNC
 */
HWTEST_F(TitleBarAccessibilityPropertyTestNg, TitleBarAccessibilityPropertyGetText001, TestSize.Level1)
{
    EXPECT_EQ(titleBarAccessibilityProperty_->GetText(), EMPTY_TEXT);

    auto titleNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(titleNode, nullptr);
    auto textLayoutProperty = titleNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(TITLE_BAR_TEXT);
    frameNode_->SetTitle(titleNode);

    EXPECT_EQ(titleBarAccessibilityProperty_->GetText(), TITLE_BAR_TEXT);
}
} // namespace OHOS::Ace::NG
