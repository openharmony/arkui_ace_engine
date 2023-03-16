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
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
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
const std::string BAR_ITEM_TEXT = "text";
} // namespace
class BarItemAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    bool InitBarItemTestNg();
    RefPtr<BarItemNode> frameNode_;
    RefPtr<BarItemPattern> barItemPattern_;
    RefPtr<BarItemAccessibilityProperty> barItemAccessibilityProperty_;
};

void BarItemAccessibilityPropertyTestNg::SetUp()
{
    ASSERT_TRUE(InitBarItemTestNg());
}

void BarItemAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    barItemPattern_ = nullptr;
    barItemAccessibilityProperty_ = nullptr;
}

bool BarItemAccessibilityPropertyTestNg::InitBarItemTestNg()
{
    frameNode_ = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId());
    CHECK_NULL_RETURN(frameNode_, false);
    frameNode_->InitializePatternAndContext();

    barItemPattern_ = frameNode_->GetPattern<BarItemPattern>();
    CHECK_NULL_RETURN(barItemPattern_, false);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(textNode, false);
    frameNode_->SetTextNode(textNode);

    barItemAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<BarItemAccessibilityProperty>();
    CHECK_NULL_RETURN(barItemAccessibilityProperty_, false);
    return true;
}

/**
 * @tc.name: BarItemAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of barItem.
 * @tc.type: FUNC
 */
HWTEST_F(BarItemAccessibilityPropertyTestNg, BarItemAccessibilityPropertyGetText001, TestSize.Level1)
{
    EXPECT_EQ(barItemAccessibilityProperty_->GetText(), EMPTY_TEXT);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(BAR_ITEM_TEXT);
    frameNode_->SetTextNode(textNode);

    EXPECT_EQ(barItemAccessibilityProperty_->GetText(), BAR_ITEM_TEXT);
}
} // namespace OHOS::Ace::NG
