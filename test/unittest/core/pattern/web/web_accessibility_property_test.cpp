/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/web/web_accessibility_property.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;

namespace OHOS::Ace::NG {

class WebAccessibilityPropertyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebAccessibilityPropertyTest::SetUpTestCase() {}
void WebAccessibilityPropertyTest::TearDownTestCase() {}
void WebAccessibilityPropertyTest::SetUp() {}
void WebAccessibilityPropertyTest::TearDown() {}

/**
 * @tc.name: GetText_001
 * @tc.desc: Test function GetText.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityPropertyTest, GetText_001, TestSize.Level1)
{
    WebAccessibilityProperty property;
    std::string result = property.GetText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetText_002
 * @tc.desc: Test function GetText.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityPropertyTest, GetText_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<ButtonPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    WebAccessibilityProperty property;
    property.SetHost(frameNode);
    std::string result = property.GetText();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetText_003
 * @tc.desc: Test function GetText.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityPropertyTest, GetText_003, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() {
        return AceType::MakeRefPtr<WebPattern>();
    });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    auto webPaintProperty = AceType::DynamicCast<WebPaintProperty>(webPattern->CreatePaintProperty());
    ASSERT_NE(webPaintProperty, nullptr);
    const std::string webData = "HelloWorld";
    webPaintProperty->SetWebPaintData(webData);

    WebAccessibilityProperty property;
    property.SetHost(frameNode);
    std::string result = property.GetText();
    EXPECT_EQ(result, webData);
}

} // namespace OHOS::Ace::NG
