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
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/pattern/ui_extension/accessibility_session_adapter_isolated_component.h"
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "core/accessibility/accessibility_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

const std::string BUNDLE_NAME = "Test bundle name";
const std::string ABILITY_NAME = "Test ability name";
    
class AccessibilitySessionAdapterIsolatedComponentTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void AccessibilitySessionAdapterIsolatedComponentTestNg::SetUp() {}

void AccessibilitySessionAdapterIsolatedComponentTestNg::TearDown() {}

/**
* @tc.name: AccessibilitySessionAdapterIsolatedComponentTestNg001
* @tc.desc: Test AccessibilitySessionAdapterIsolatedComponentTestNg TransferHoverEvent
* @tc.type: FUNC
*/
HWTEST_F(AccessibilitySessionAdapterIsolatedComponentTestNg,
    AccessibilitySessionAdapterIsolatedComponentTestNg001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
    * @tc.steps: step1. construct a IsolatedComponent Node
    */
    auto isolatedComponentId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedComponentNode = FrameNode::GetOrCreateFrameNode(
        V2::ISOLATED_COMPONENT_ETS_TAG, isolatedComponentId, []() {
            return AceType::MakeRefPtr<IsolatedPattern>();
        });
    ASSERT_NE(isolatedComponentNode, nullptr);
    EXPECT_EQ(isolatedComponentNode->GetTag(), V2::ISOLATED_COMPONENT_ETS_TAG);
    
    /**
    * @tc.steps: step2. get isolatedComponentPattern
    */
    auto isolatedComponentPattern = isolatedComponentNode->GetPattern<IsolatedPattern>();
    ASSERT_NE(isolatedComponentPattern, nullptr);

    /**
    * @tc.steps: step3. initialize isolatedComponentPattern
    */
    IsolatedInfo curIsolatedInfo;
    void* runtime = nullptr;
    isolatedComponentPattern->dynamicComponentRenderer_ = DynamicComponentRenderer::Create(
        isolatedComponentNode, runtime, curIsolatedInfo);
    isolatedComponentPattern->dynamicComponentRenderer_->CreateContent();
    isolatedComponentPattern->dynamicComponentRenderer_->SetUIContentType(UIContentType::ISOLATED_COMPONENT);
    isolatedComponentPattern->dynamicComponentRenderer_->SetAdaptiveSize(true, true);
    isolatedComponentPattern->dynamicComponentRenderer_->SetBackgroundTransparent(true);
    isolatedComponentPattern->accessibilitySessionAdapter_ =
        AceType::MakeRefPtr<AccessibilitySessionAdapterIsolatedComponent>(
            isolatedComponentPattern->dynamicComponentRenderer_);
    /**
    * @tc.steps: step4. get an AccessibilitySessionAdapter
    */
    
    auto accessibilitySessionAdapter = isolatedComponentPattern->GetAccessibilitySessionAdapter();
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