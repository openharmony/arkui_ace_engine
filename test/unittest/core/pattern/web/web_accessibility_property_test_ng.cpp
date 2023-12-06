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
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string EMPTY_TEXT = "";
const std::string WEB_CONTENT = "web";
} // namespace
class WebAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: WebAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of webAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityPropertyTestNg, WebAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto webAccessibilityProperty = frameNode->GetAccessibilityProperty<WebAccessibilityProperty>();
    ASSERT_NE(webAccessibilityProperty, nullptr);
    auto webPaintProperty = AceType::DynamicCast<WebPaintProperty>(webPattern->CreatePaintProperty());
    ASSERT_NE(webPaintProperty, nullptr);

    EXPECT_EQ(webAccessibilityProperty->GetText(), EMPTY_TEXT);

    webPaintProperty->SetWebPaintData(WEB_CONTENT);
    EXPECT_EQ(webAccessibilityProperty->GetText(), WEB_CONTENT);
}
} // namespace OHOS::Ace::NG
