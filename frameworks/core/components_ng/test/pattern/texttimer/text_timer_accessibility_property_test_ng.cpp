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

#include "core/components_v2/inspector/inspector_constants.h"

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/texttimer/text_timer_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string TEXTTIMER_CONTENT = "08:00:00";
} // namespace
class TextTimerAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: TextTimerAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of textTimerAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextTimerAccessibilityPropertyTestNg, TextTimerAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::TEXTTIMER_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<TextTimerPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);
    auto textTimerAccessibilityProperty = frameNode->GetAccessibilityProperty<TextTimerAccessibilityProperty>();
    ASSERT_NE(textTimerAccessibilityProperty, nullptr);
    textTimerAccessibilityProperty->SetHost(AceType::WeakClaim(AceType::RawPtr(frameNode)));

    EXPECT_EQ(textTimerAccessibilityProperty->GetText(), EMPTY_TEXT);

    textLayoutProperty->UpdateContent(TEXTTIMER_CONTENT);
    EXPECT_EQ(textTimerAccessibilityProperty->GetText(), TEXTTIMER_CONTENT);
}
} // namespace OHOS::Ace::NG
