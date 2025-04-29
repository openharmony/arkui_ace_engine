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
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "core/components_ng/pattern/ui_extension/accessibility_session_adapter_ui_extension.h"
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_pattern.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/accessibility/accessibility_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
    
class AccessibilitySessionAdapterUIExtensionTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void AccessibilitySessionAdapterUIExtensionTestNg::SetUp() {}

void AccessibilitySessionAdapterUIExtensionTestNg::TearDown() {}

/**
 * @tc.name: AccessibilitySessionAdapterUIExtensionTest001
 * @tc.desc: Test AccessibilitySessionAdapterUIExtension TransferHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilitySessionAdapterUIExtensionTestNg, AccessibilitySessionAdapterUIExtensionTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a SecurityUIExtensionPattern Node
     */
    auto securityUIExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto securityUIExtensionNode = FrameNode::GetOrCreateFrameNode(
        V2::UI_EXTENSION_COMPONENT_ETS_TAG, securityUIExtensionNodeId, []() {
            return AceType::MakeRefPtr<SecurityUIExtensionPattern>();
        });
    ASSERT_NE(securityUIExtensionNode, nullptr);
    EXPECT_EQ(securityUIExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    
    /**
     * @tc.steps: step2. get SecurityUIExtensionPattern
     */
    auto securityUIExtensionPattern = securityUIExtensionNode->GetPattern<SecurityUIExtensionPattern>();
    ASSERT_NE(securityUIExtensionPattern, nullptr);

    /**
     * @tc.steps: step3. initialize SecurityUIExtensionPattern
     */
    UIExtensionConfig uiExtensionConfig;
    securityUIExtensionPattern->Initialize(uiExtensionConfig);

    /**
     * @tc.steps: step4. get an AccessibilitySessionAdapter
     */
    auto accessibilitySessionAdapter = securityUIExtensionPattern->GetAccessibilitySessionAdapter();
    ASSERT_NE(accessibilitySessionAdapter, nullptr);

    /**
     * @tc.steps: step5. call TransferHoverEvent function
     */
    const NG::PointF point { 10, 10 };
    SourceType sourceType = SourceType::NONE;
    AccessibilityHoverEventType type = AccessibilityHoverEventType::MOVE;
    TimeStamp timeStamp;
    accessibilitySessionAdapter->TransferHoverEvent(point, sourceType, type, timeStamp);
#endif
}
} // namespace OHOS::Ace::NG
