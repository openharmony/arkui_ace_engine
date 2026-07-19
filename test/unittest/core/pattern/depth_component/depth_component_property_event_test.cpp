/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// TDD coverage for DepthComponentPaintMethod, the accessibility property (exercised
// through the AccessibilityProperty base interface), and DepthComponentEventHub.

#include "depth_component_test_base.h"

namespace OHOS::Ace::NG {

class DepthComponentPropertyEventTestNg : public DepthComponentTestBase {};

// ===================== Accessibility property (base interface) =====================

/**
 * @tc.name: AccessibilityGetText001
 * @tc.desc: GetText returns "" when no host is attached.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, AccessibilityGetText001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    auto prop = pattern->CreateAccessibilityProperty();
    EXPECT_EQ(prop->GetText(), std::string(""));
}

/**
 * @tc.name: AccessibilityGetText002
 * @tc.desc: GetText returns "Depth Component" when a host is attached.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, AccessibilityGetText002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto prop = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->host_ = AceType::WeakClaim(AceType::RawPtr(host));
    EXPECT_EQ(prop->GetText(), std::string("Depth Component"));
}

/**
 * @tc.name: AccessibilityGetValue001
 * @tc.desc: GetAccessibilityValue returns defaults when no host is attached.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, AccessibilityGetValue001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<DepthComponentPattern>();
    auto prop = pattern->CreateAccessibilityProperty();
    AccessibilityValue value = prop->GetAccessibilityValue();
    EXPECT_EQ(value.min, 0);
    EXPECT_EQ(value.max, 0);
    EXPECT_EQ(value.current, 0);
}

/**
 * @tc.name: AccessibilityGetValue002
 * @tc.desc: GetAccessibilityValue reports min=0, max=1, current=max when a host is attached.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, AccessibilityGetValue002, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto prop = host->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(prop, nullptr);
    prop->host_ = AceType::WeakClaim(AceType::RawPtr(host));
    AccessibilityValue value = prop->GetAccessibilityValue();
    EXPECT_EQ(value.min, 0);
    EXPECT_EQ(value.max, 1);
    EXPECT_EQ(value.current, 1);
}

// ===================== DepthComponentEventHub =====================

/**
 * @tc.name: EventHubOnComplete001
 * @tc.desc: SetOnComplete / GetOnComplete / FireCompleteEvent wiring.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, EventHubOnComplete001, TestSize.Level1)
{
    auto hub = AceType::MakeRefPtr<DepthComponentEventHub>();
    EXPECT_EQ(hub->GetOnComplete(), nullptr);
    hub->FireCompleteEvent(DepthComponentCompleteEvent()); // no callback -> no-op

    double width = 0.0;
    hub->SetOnComplete([&width](const DepthComponentCompleteEvent& event) { width = event.componentWidth; });
    EXPECT_NE(hub->GetOnComplete(), nullptr);
    DepthComponentCompleteEvent event;
    event.componentWidth = 480.0;
    hub->FireCompleteEvent(event);
    EXPECT_EQ(width, 480.0);
}

/**
 * @tc.name: EventHubOnError001
 * @tc.desc: SetOnError / GetOnError / FireErrorEvent wiring.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, EventHubOnError001, TestSize.Level1)
{
    auto hub = AceType::MakeRefPtr<DepthComponentEventHub>();
    EXPECT_EQ(hub->GetOnError(), nullptr);
    hub->FireErrorEvent(DepthComponentErrorEvent()); // no callback -> no-op

    int32_t code = 0;
    std::string message;
    hub->SetOnError([&](const DepthComponentErrorEvent& event) {
        code = event.errorCode;
        message = event.errorMessage;
    });
    EXPECT_NE(hub->GetOnError(), nullptr);
    DepthComponentErrorEvent event;
    event.errorCode = 500;
    event.errorMessage = "internal";
    hub->FireErrorEvent(event);
    EXPECT_EQ(code, 500);
    EXPECT_EQ(message, std::string("internal"));
}

/**
 * @tc.name: EventHubOnDepthMapError001
 * @tc.desc: SetOnDepthMapError / GetOnDepthMapError / FireDepthMapErrorEvent wiring.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, EventHubOnDepthMapError001, TestSize.Level1)
{
    auto hub = AceType::MakeRefPtr<DepthComponentEventHub>();
    EXPECT_EQ(hub->GetOnDepthMapError(), nullptr);
    hub->FireDepthMapErrorEvent(0, ""); // no callback -> no-op

    int32_t code = 0;
    std::string message;
    hub->SetOnDepthMapError([&](int32_t errorCode, const std::string& errorMessage) {
        code = errorCode;
        message = errorMessage;
    });
    EXPECT_NE(hub->GetOnDepthMapError(), nullptr);
    hub->FireDepthMapErrorEvent(42, "decode failed");
    EXPECT_EQ(code, 42);
    EXPECT_EQ(message, std::string("decode failed"));
}

// ===================== DepthComponentPaintMethod =====================

/**
 * @tc.name: PaintMethod001
 * @tc.desc: GetContentDrawFunction triggers OnPaint3D and returns a null draw function.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, PaintMethod001, TestSize.Level1)
{
    auto host = CreateNode(MakeImageSource());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    ASSERT_NE(pattern, nullptr);
    DepthComponentPaintMethod paintMethod(AceType::WeakClaim(AceType::RawPtr(pattern)));
    auto func = paintMethod.GetContentDrawFunction(nullptr);
    EXPECT_EQ(func, nullptr);
}

/**
 * @tc.name: PaintMethod002
 * @tc.desc: PerformPaint is a safe no-op when the pattern weak ref has expired.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentPropertyEventTestNg, PaintMethod002, TestSize.Level1)
{
    WeakPtr<DepthComponentPattern> expired; // default-constructed -> Upgrade() returns null
    DepthComponentPaintMethod paintMethod(expired);
    auto func = paintMethod.GetContentDrawFunction(nullptr); // CHECK_NULL_VOID in PerformPaint
    EXPECT_EQ(func, nullptr);
}
} // namespace OHOS::Ace::NG
