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

#include <cstddef>
#include <cstdint>
#include "gtest/gtest.h"
#define private public
#define protected public
#include "native_interface.h"
#include "native_node.h"
#include "native_render.h"
#include "native_type.h"
#include "interfaces/native/node/node_extened.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/render_node.h"
#include "interfaces/native/node/styled_string.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components_ng/base/ui_node.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
class NativeRenderNodeTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: NativeRenderNodeTest001
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ASSERT_NE(rootCustomNode, nullptr);
    result = OH_ArkUI_RenderNodeUtils_AddRenderNode(button, rootRenderNode);
    ASSERT_EQ(result, ERROR_CODE_PARAM_INVALID);
    result = OH_ArkUI_RenderNodeUtils_RemoveRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeRenderNodeTest002
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_ClearRenderNodeChildren(rootCustomNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeRenderNodeTest003
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest003, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_Invalidate(rootCustomNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    auto rsNodeFirstChild = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rsNodeFirstChild, nullptr);
    auto rsNodeSecondChild = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rsNodeSecondChild, nullptr);
    auto rsNodeThirdChild = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rsNodeThirdChild, nullptr);
    result = OH_ArkUI_RenderNodeUtils_AddChild(rootRenderNode, rsNodeFirstChild);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_AddChild(rootRenderNode, rsNodeSecondChild);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    int count = 0;
    result = OH_ArkUI_RenderNodeUtils_GetChildrenCount(rootRenderNode, &count);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(count, 2); //2 represents the number of sub-nodes that have been added by the sub-nodes.
    auto nodeForDispose = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(nodeForDispose, nullptr);
    result = OH_ArkUI_RenderNodeUtils_DisposeNode(nodeForDispose);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_InsertChildAfter(rootRenderNode, rsNodeThirdChild, rsNodeSecondChild);
    result = OH_ArkUI_RenderNodeUtils_GetChildrenCount(rootRenderNode, &count);
    ASSERT_EQ(count, 3); //3 represents the number of sub-nodes that have been added by the sub-nodes.
    OH_ArkUI_RenderNodeUtils_RemoveChild(rootRenderNode, rsNodeThirdChild);
    OH_ArkUI_RenderNodeUtils_GetChildrenCount(rootRenderNode, &count);
    ASSERT_EQ(count, 2); //2 represents the number of sub-nodes that have been added by the sub-nodes.
    OH_ArkUI_RenderNodeUtils_ClearChildren(rootRenderNode);
    OH_ArkUI_RenderNodeUtils_GetChildrenCount(rootRenderNode, &count);
    ASSERT_EQ(count, 0); //0 represents the number of sub-nodes that have been added by the sub-nodes.
}

/**
 * @tc.name: NativeRenderNodeTest004
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest004, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    auto rsNodeFirstChild = OH_ArkUI_RenderNodeUtils_CreateNode();
    auto rsNodeSecondChild = OH_ArkUI_RenderNodeUtils_CreateNode();
    auto rsNodeThirdChild = OH_ArkUI_RenderNodeUtils_CreateNode();
    OH_ArkUI_RenderNodeUtils_AddChild(rootRenderNode, rsNodeFirstChild);
    OH_ArkUI_RenderNodeUtils_AddChild(rootRenderNode, rsNodeSecondChild);
    OH_ArkUI_RenderNodeUtils_AddChild(rootRenderNode, rsNodeThirdChild);
    
    OH_ArkUI_RenderNodeUtils_SetSize(rootRenderNode, 300, 300); // size 300 marker node.
    OH_ArkUI_RenderNodeUtils_SetSize(rsNodeFirstChild, 100, 100); // size 100 marker node.
    OH_ArkUI_RenderNodeUtils_SetSize(rsNodeSecondChild, 200, 200); // size 200 marker node.
    OH_ArkUI_RenderNodeUtils_SetSize(rsNodeThirdChild, 250, 250); // size 250 marker node.

    int w = 0;
    ArkUI_RenderNodeHandle nodeTemp;
    result = OH_ArkUI_RenderNodeUtils_GetFirstChild(rootRenderNode, &nodeTemp);
    OH_ArkUI_RenderNodeUtils_GetSize(nodeTemp, &w, &w);
    ASSERT_EQ(w, 100); //100 represents rsNodeFirstChild.
    result = OH_ArkUI_RenderNodeUtils_GetChild(rootRenderNode, 1, &nodeTemp);
    OH_ArkUI_RenderNodeUtils_GetSize(nodeTemp, &w, &w);
    ASSERT_EQ(w, 200); //200 represents rsNodeSecondChild.
    result = OH_ArkUI_RenderNodeUtils_GetNextSibling(rsNodeSecondChild, &nodeTemp);
    OH_ArkUI_RenderNodeUtils_GetSize(nodeTemp, &w, &w);
    ASSERT_EQ(w, 250); //250 represents rsNodeThirdChild.
    result = OH_ArkUI_RenderNodeUtils_GetPreviousSibling(rsNodeSecondChild, &nodeTemp);
    OH_ArkUI_RenderNodeUtils_GetSize(nodeTemp, &w, &w);
    ASSERT_EQ(w, 100); //100 represents rsNodeFirstChild.

    ArkUI_RenderNodeHandle* nodeList;
    int count = 0;
    OH_ArkUI_RenderNodeUtils_GetChildren(rootRenderNode, &nodeList, &count);
    ASSERT_EQ(count, 3); //3 represents the number of sub-nodes that have been added by the sub-nodes.
    OH_ArkUI_RenderNodeUtils_GetSize(nodeList[0], &w, &w);
    ASSERT_EQ(w, 100); //100 represents rsNodeFirstChild.
}

} // namespace OHOS::Ace