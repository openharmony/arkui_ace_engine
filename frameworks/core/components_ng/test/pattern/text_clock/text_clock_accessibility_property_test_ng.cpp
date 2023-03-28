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
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string TEXTCLOCK_CONTENT = "08:00:00";
} // namespace
class TextClockAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: TextClockAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of textClockAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TextClockAccessibilityPropertyTestNg, TextClockAccessibilityPropertyIsScrollable001, TestSize.Level1)
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
