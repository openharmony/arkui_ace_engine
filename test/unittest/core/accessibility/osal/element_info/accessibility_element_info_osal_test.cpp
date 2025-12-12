/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "accessibility_system_ability_client.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "ui/properties/ui_material.h"

#include "base/log/dump_log.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/accessibility/utils/accessibility_property_utils.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"

using namespace OHOS::Accessibility;
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
constexpr float TEST_FRAME_NODE_WIDTH = 10.0f;
constexpr float TEST_FRAME_NODE_HEIGHT = 10.0f;
class MockRenderContextTest : public NG::RenderContext {
public:
    NG::RectF GetPaintRectWithoutTransform() override
    {
        return *retf;
    }
    std::shared_ptr<NG::RectF> retf;
};

RefPtr<NG::FrameNode> CreatFrameNode()
{
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->SetActive(true, false);
    auto renderContext = AceType::MakeRefPtr<MockRenderContextTest>();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto rect = std::make_shared<NG::RectF>(0.0, 0.0, TEST_FRAME_NODE_WIDTH, TEST_FRAME_NODE_HEIGHT);
    renderContext->retf = rect;
    frameNode->renderContext_ = renderContext;
    return frameNode;
}
} // namespace

class AccessibilityElementInfoOsalTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AccessibilityElementInfoOsalTest::SetUpTestCase()
{
    NG::MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
}

void AccessibilityElementInfoOsalTest::TearDownTestCase()
{
    NG::MockPipelineContext::TearDown();
    MockContainer::TearDown();
}


/**
 * @tc.name: FindLastNodeWithoutCheck001
 * @tc.desc: UpdateAccessibilityElementInfo
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityElementInfoOsalTest, UpdateHasChildText001, TestSize.Level1)
{
    auto frameNode = NG::FrameNode::CreateFrameNode("framenode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<NG::Pattern>(), false);
    ASSERT_NE(frameNode, nullptr);
    frameNode->SetActive(true, false);
    auto jsAccessibilityManager = AceType::MakeRefPtr<Framework::JsAccessibilityManager>();
    ASSERT_NE(jsAccessibilityManager, nullptr);
    Accessibility::AccessibilityElementInfo nodeInfo;
    nodeInfo.SetBelongTreeId(1);
    auto readEnableBackup = AceApplicationInfo::GetInstance().IsAccessibilityScreenReadEnabled();
    AceApplicationInfo::GetInstance().SetAccessibilityScreenReadEnabled(true);

    jsAccessibilityManager->UpdateHasChildText(frameNode, nodeInfo);
    ExtraElementInfo extraElementInfo = nodeInfo.GetExtraElement();
    auto extraElementInfoValue = extraElementInfo.GetExtraElementInfoValueStr();
    auto hasChildTextStr = extraElementInfoValue.find("childText");
    ASSERT_EQ(hasChildTextStr, extraElementInfoValue.end());
}


} // namespace OHOS::Ace::NG