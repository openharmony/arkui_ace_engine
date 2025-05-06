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
#include "frameworks/core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/base/log/log_wrapper.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_accessibility_child_tree_callback.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_layout_algorithm.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "adapter/ohos/entrance/ace_extra_input_data.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string UI_EXTENSION_COMPONENT_ETS_TAG = "UIExtensionComponent";
    const int32_t CODE = 10001;
    const std::string NAME = "Test name";
    const std::string MSG = "Test msg";
    const std::string TAG = "Test node tag";
    int32_t platformId = 1;
} // namespace

class UecAccessibilityChildTreeCallbackTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    }

    static void TearDownTestSuite()
    {
        MockContainer::Current()->pipelineContext_ = nullptr;
        NG::MockPipelineContext::TearDown();
    }

    void SetUp() override;
    void TearDown() override;
};

void UecAccessibilityChildTreeCallbackTest::SetUp() {}

void UecAccessibilityChildTreeCallbackTest::TearDown() {}

/**
 * @tc.name: UecAccessibilityChildTreeCallbackTest001
 * @tc.desc: Test PlatformPattern CreateLayoutAlgorithm/GetFocusPattern/OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(UecAccessibilityChildTreeCallbackTest, UecAccessibilityTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionPattern Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. construct a UIExtensionAccessibilityChildTreeCallback
     */
    int64_t accessibilityId = 10001;
    auto accessibilityChildTreeCallback = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(
        pattern, accessibilityId);
    ASSERT_NE(accessibilityChildTreeCallback, nullptr);
    bool ret = false;

    /**
     * @tc.steps: step3. OnRegister twice
     */
    ret = accessibilityChildTreeCallback->OnDeregister();
    EXPECT_EQ(ret, true);
    ret = accessibilityChildTreeCallback->OnRegister(0, 0);
    EXPECT_EQ(ret, true);
    ret = accessibilityChildTreeCallback->OnRegister(1, 1);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step4. OnDeregister test
     */
    ret = accessibilityChildTreeCallback->OnDeregister();
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: UecAccessibilityChildTreeCallbackTest002
 * @tc.desc: Test PlatformPattern CreateLayoutAlgorithm/GetFocusPattern/OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(UecAccessibilityChildTreeCallbackTest, UecAccessibilityTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionAccessibilityChildTreeCallback
     */
    int64_t accessibilityId = 10001;
    auto accessibilityChildTreeCallback = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(
        nullptr, accessibilityId);
    ASSERT_NE(accessibilityChildTreeCallback, nullptr);

    /**
     * @tc.steps: step2. OnRegister twice
     */
    bool ret = accessibilityChildTreeCallback->OnRegister(0, 0);
    EXPECT_EQ(ret, false);
    ret = accessibilityChildTreeCallback->OnRegister(1, 1);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step3. OnDeregister
     */
    ret = accessibilityChildTreeCallback->OnDeregister();
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: UecAccessibilityChildTreeCallbackTest003
 * @tc.desc: Test PlatformPattern CreateLayoutAlgorithm/GetFocusPattern/OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(UecAccessibilityChildTreeCallbackTest, UecAccessibilityTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct a UIExtensionPattern Node
     */
    auto uiExtensionNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto uiExtensionNode = FrameNode::GetOrCreateFrameNode(
        UI_EXTENSION_COMPONENT_ETS_TAG, uiExtensionNodeId, []() {
            return AceType::MakeRefPtr<UIExtensionPattern>();
        });
    ASSERT_NE(uiExtensionNode, nullptr);
    EXPECT_EQ(uiExtensionNode->GetTag(), V2::UI_EXTENSION_COMPONENT_ETS_TAG);
    auto pattern = uiExtensionNode->GetPattern<UIExtensionPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. construct a UIExtensionAccessibilityChildTreeCallback
     */
    int64_t accessibilityId = 10001;
    auto accessibilityChildTreeCallback = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(
        pattern, accessibilityId);
    ASSERT_NE(accessibilityChildTreeCallback, nullptr);
    bool ret = false;

    /**
     * @tc.steps: step3. OnRegister twice
     */
    ret = accessibilityChildTreeCallback->OnDeregister();
    EXPECT_EQ(ret, true);
    ret = accessibilityChildTreeCallback->OnRegister(0, 0);
    EXPECT_EQ(ret, true);
    ret = accessibilityChildTreeCallback->OnRegister(1, 1);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step4. OnDeregister test
     */
    ret = accessibilityChildTreeCallback->OnSetChildTree(1000, 1);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step5. construct a UIExtensionAccessibilityChildTreeCallback2 with no pattern
     */
    auto accessibilityChildTreeCallback2 = std::make_shared<UIExtensionAccessibilityChildTreeCallback>(
        nullptr, accessibilityId);
    ret = accessibilityChildTreeCallback2->OnSetChildTree(1000, 1);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step6. OnClearRegisterFlag
     */
    accessibilityChildTreeCallback2->OnClearRegisterFlag();
}
} // namespace OHOS::Ace::NG
 