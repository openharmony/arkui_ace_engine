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

/**
 * @tc.name: NativeRenderNodeTest005
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest005, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto rootRenderNode1 = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode1, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode1);
    ASSERT_EQ(result, ERROR_CODE_CHILD_EXISTED);
}

/**
 * @tc.name: NativeRenderNodeTest006
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest006, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto rootRenderNode1 = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode1, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddChild(rootRenderNode, rootRenderNode1);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode1);
    ASSERT_EQ(result, ERROR_CODE_RENDER_PARENT_EXISTED);
}

/**
 * @tc.name: NativeRenderNodeTest090
 * @tc.desc: Test CreateFloatProperty and SetFloatPropertyValue functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest090, TestSize.Level1)
{
    auto floatProperty = OH_ArkUI_RenderNodeUtils_CreateFloatProperty(2.0f);
    ASSERT_NE(floatProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_SetFloatPropertyValue(floatProperty, 3.0f);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(floatProperty);
}

/**
 * @tc.name: NativeRenderNodeTest091
 * @tc.desc: Test GetFloatPropertyValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest091, TestSize.Level1)
{
    auto floatProperty = OH_ArkUI_RenderNodeUtils_CreateFloatProperty(4.0f);
    ASSERT_NE(floatProperty, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(floatProperty, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(value, 4.0f);
    OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(floatProperty);
}

/**
 * @tc.name: NativeRenderNodeTest092
 * @tc.desc: Test AttachFloatProperty and AttachVector2Property functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest092, TestSize.Level1)
{
    auto contentModifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(contentModifier, nullptr);

    auto floatProperty = OH_ArkUI_RenderNodeUtils_CreateFloatProperty(1.0f);
    ASSERT_NE(floatProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AttachFloatProperty(contentModifier, floatProperty);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    auto vector2Property = OH_ArkUI_RenderNodeUtils_CreateVector2Property(10.0f, 20.0f);
    ASSERT_NE(vector2Property, nullptr);
    result = OH_ArkUI_RenderNodeUtils_AttachVector2Property(contentModifier, vector2Property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_RenderNodeUtils_DisposeVector2Property(vector2Property);
    OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(floatProperty);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(contentModifier);
}

/**
 * @tc.name: NativeRenderNodeTest093
 * @tc.desc: Test AttachColorProperty and AttachFloatAnimatableProperty functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest093, TestSize.Level1)
{
    auto contentModifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(contentModifier, nullptr);

    auto colorProperty = OH_ArkUI_RenderNodeUtils_CreateColorProperty(0xFF0000FF);
    ASSERT_NE(colorProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AttachColorProperty(contentModifier, colorProperty);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    auto floatAnimProperty = OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(2.5f);
    ASSERT_NE(floatAnimProperty, nullptr);
    result = OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty(contentModifier, floatAnimProperty);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(floatAnimProperty);
    OH_ArkUI_RenderNodeUtils_DisposeColorProperty(colorProperty);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(contentModifier);
}

/**
 * @tc.name: NativeRenderNodeTest094
 * @tc.desc: Test AttachVector2AnimatableProperty and AttachColorAnimatableProperty functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest094, TestSize.Level1)
{
    auto contentModifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(contentModifier, nullptr);

    auto vector2AnimProperty = OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(100.0f, 200.0f);
    ASSERT_NE(vector2AnimProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty(contentModifier, vector2AnimProperty);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    auto colorAnimProperty = OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(0xFF00FFFF);
    ASSERT_NE(colorAnimProperty, nullptr);
    result = OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty(contentModifier, colorAnimProperty);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(colorAnimProperty);
    OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(vector2AnimProperty);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(contentModifier);
}

/**
 * @tc.name: NativeRenderNodeTest100
 * @tc.desc: Test DisposeFloatProperty function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest100, TestSize.Level1)
{
    auto floatProperty = OH_ArkUI_RenderNodeUtils_CreateFloatProperty(1.5f);
    ASSERT_NE(floatProperty, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(floatProperty);
}

/**
 * @tc.name: NativeRenderNodeTest101
 * @tc.desc: Test CreateVector2Property and SetVector2PropertyValue functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest101, TestSize.Level1)
{
    auto vector2Property = OH_ArkUI_RenderNodeUtils_CreateVector2Property(10.0f, 20.0f);
    ASSERT_NE(vector2Property, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_SetVector2PropertyValue(vector2Property, 30.0f, 40.0f);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeVector2Property(vector2Property);
}

/**
 * @tc.name: NativeRenderNodeTest102
 * @tc.desc: Test GetVector2PropertyValue and DisposeVector2Property functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest102, TestSize.Level1)
{
    auto vector2Property = OH_ArkUI_RenderNodeUtils_CreateVector2Property(50.0f, 60.0f);
    ASSERT_NE(vector2Property, nullptr);
    float x = 0.0f, y = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(vector2Property, &x, &y);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 50.0f);
    ASSERT_EQ(y, 60.0f);
    OH_ArkUI_RenderNodeUtils_DisposeVector2Property(vector2Property);
}

/**
 * @tc.name: NativeRenderNodeTest103
 * @tc.desc: Test CreateColorProperty and SetColorPropertyValue functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest103, TestSize.Level1)
{
    auto colorProperty = OH_ArkUI_RenderNodeUtils_CreateColorProperty(0xFF0000FF);
    ASSERT_NE(colorProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_SetColorPropertyValue(colorProperty, 0xFF00FF00);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeColorProperty(colorProperty);
}

/**
 * @tc.name: NativeRenderNodeTest104
 * @tc.desc: Test GetColorPropertyValue and DisposeColorProperty functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest104, TestSize.Level1)
{
    auto colorProperty = OH_ArkUI_RenderNodeUtils_CreateColorProperty(0xFFFF0000);
    ASSERT_NE(colorProperty, nullptr);
    uint32_t color = 0;
    auto result = OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(colorProperty, &color);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeColorProperty(colorProperty);
}

/**
 * @tc.name: NativeRenderNodeTest105
 * @tc.desc: Test CreateFloatAnimatableProperty and SetFloatAnimatablePropertyValue functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest105, TestSize.Level1)
{
    auto floatAnimProperty = OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(2.5f);
    ASSERT_NE(floatAnimProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_SetFloatAnimatablePropertyValue(floatAnimProperty, 3.5f);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(floatAnimProperty);
}

/**
 * @tc.name: NativeRenderNodeTest106
 * @tc.desc: Test GetFloatAnimatablePropertyValue and DisposeFloatAnimatableProperty functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest106, TestSize.Level1)
{
    auto floatAnimProperty = OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(4.5f);
    ASSERT_NE(floatAnimProperty, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(floatAnimProperty, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(value, 4.5f);
    OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(floatAnimProperty);
}

/**
 * @tc.name: NativeRenderNodeTest107
 * @tc.desc: Test CreateVector2AnimatableProperty and SetVector2AnimatablePropertyValue functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest107, TestSize.Level1)
{
    auto vector2AnimProperty = OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(100.0f, 200.0f);
    ASSERT_NE(vector2AnimProperty, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_SetVector2AnimatablePropertyValue(vector2AnimProperty, 300.0f, 400.0f);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(vector2AnimProperty);
}

/**
 * @tc.name: NativeRenderNodeTest108
 * @tc.desc: Test GetVector2AnimatablePropertyValue and DisposeVector2AnimatableProperty functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest108, TestSize.Level1)
{
    auto vector2AnimProperty = OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(500.0f, 600.0f);
    ASSERT_NE(vector2AnimProperty, nullptr);
    float x = 0.0f, y = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(vector2AnimProperty, &x, &y);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 500.0f);
    ASSERT_EQ(y, 600.0f);
    OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(vector2AnimProperty);
}

/**
 * @tc.name: NativeRenderNodeTest109
 * @tc.desc: Test CreateColorAnimatableProperty and SetColorAnimatablePropertyValue functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest109, TestSize.Level1)
{
    auto colorAnimProperty = OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(0xFF00FFFF);
    ASSERT_NE(colorAnimProperty, nullptr);
    OH_ArkUI_RenderNodeUtils_SetColorAnimatablePropertyValue(colorAnimProperty, 0xFFFFFF00);
    OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(colorAnimProperty);
}

/**
 * @tc.name: NativeRenderNodeTest110
 * @tc.desc: Test GetColorAnimatablePropertyValue and DisposeColorAnimatableProperty functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest110, TestSize.Level1)
{
    auto colorAnimProperty = OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(0xFFFF00FF);
    ASSERT_NE(colorAnimProperty, nullptr);
    uint32_t color = 0;
    auto result = OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(colorAnimProperty, &color);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(colorAnimProperty);
}

/**
 * @tc.name: NativeRenderNodeTest111
 * @tc.desc: Test SetContentModifierOnDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest111, TestSize.Level1)
{
    auto contentModifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(contentModifier, nullptr);

    static bool drawCallbackCalled = false;
    auto drawCallback = [](ArkUI_DrawContext* context, void* userData) {
        drawCallbackCalled = true;
    };

    int userData = 123;
    auto result = OH_ArkUI_RenderNodeUtils_SetContentModifierOnDraw(contentModifier, &userData, drawCallback);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(contentModifier);
}

/**
 * @tc.name: NativeRenderNodeTest112
 * @tc.desc: Test CreateRectShapeOption and DisposeRectShapeOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest112, TestSize.Level1)
{
    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
}

/**
 * @tc.name: NativeRenderNodeTest113
 * @tc.desc: Test SetRectShapeOptionEdgeValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest113, TestSize.Level1)
{
    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(rectShape, 10.0f, 0.0f, 0.0f, 20.0f);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
}

/**
 * @tc.name: NativeRenderNodeTest114
 * @tc.desc: Test CreateNodeBorderStyleOption and DisposeNodeBorderStyleOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest114, TestSize.Level1)
{
    auto borderStyle = OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption();
    ASSERT_NE(borderStyle, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(borderStyle);
}

/**
 * @tc.name: NativeRenderNodeTest115
 * @tc.desc: Test SetNodeBorderStyleOptionEdgeStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest115, TestSize.Level1)
{
    auto borderStyle = OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption();
    ASSERT_NE(borderStyle, nullptr);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
        borderStyle, ARKUI_BORDER_STYLE_SOLID, ARKUI_EDGE_DIRECTION_TOP);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
        borderStyle, ARKUI_BORDER_STYLE_DASHED, ARKUI_EDGE_DIRECTION_LEFT);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(borderStyle);
}

/**
 * @tc.name: NativeRenderNodeTest116
 * @tc.desc: Test CreateNodeBorderWidthOption and DisposeNodeBorderWidthOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest116, TestSize.Level1)
{
    auto borderWidth = OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption();
    ASSERT_NE(borderWidth, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(borderWidth);
}

/**
 * @tc.name: NativeRenderNodeTest117
 * @tc.desc: Test SetNodeBorderWidthOptionEdgeWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest117, TestSize.Level1)
{
    auto borderWidth = OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption();
    ASSERT_NE(borderWidth, nullptr);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(borderWidth, 5.0f, ARKUI_EDGE_DIRECTION_TOP);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(borderWidth, 8.0f, ARKUI_EDGE_DIRECTION_RIGHT);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(borderWidth, -1.0f, ARKUI_EDGE_DIRECTION_RIGHT);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(borderWidth);
}

/**
 * @tc.name: NativeRenderNodeTest118
 * @tc.desc: Test CreateNodeBorderColorOption and DisposeNodeBorderColorOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest118, TestSize.Level1)
{
    auto borderColor = OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption();
    ASSERT_NE(borderColor, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(borderColor);
}

/**
 * @tc.name: NativeRenderNodeTest119
 * @tc.desc: Test SetNodeBorderColorOptionEdgeColor function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest119, TestSize.Level1)
{
    auto borderColor = OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption();
    ASSERT_NE(borderColor, nullptr);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(borderColor, 0xFF0000FF, ARKUI_EDGE_DIRECTION_TOP);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(borderColor, 0xFF00FF00, ARKUI_EDGE_DIRECTION_BOTTOM);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(borderColor);
}

/**
 * @tc.name: NativeRenderNodeTest120
 * @tc.desc: Test CreateNodeBorderRadiusOption and DisposeNodeBorderRadiusOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest120, TestSize.Level1)
{
    auto borderRadius = OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption();
    ASSERT_NE(borderRadius, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(borderRadius);
}

/**
 * @tc.name: NativeRenderNodeTest121
 * @tc.desc: Test SetNodeBorderRadiusOptionEdgeRadius function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest121, TestSize.Level1)
{
    auto borderRadius = OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption();
    ASSERT_NE(borderRadius, nullptr);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(borderRadius, 10, ARKUI_CORNER_DIRECTION_TOP_LEFT);
    OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(borderRadius, 15, ARKUI_CORNER_DIRECTION_TOP_RIGHT);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(borderRadius);
}

/**
 * @tc.name: NativeRenderNodeTest122
 * @tc.desc: Test CreateCircleShapeOption and DisposeCircleShapeOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest122, TestSize.Level1)
{
    auto circleShape = OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();
    ASSERT_NE(circleShape, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(circleShape);
}

/**
 * @tc.name: NativeRenderNodeTest123
 * @tc.desc: Test SetCircleShapeOptionCenterX and SetCircleShapeOptionCenterY functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest123, TestSize.Level1)
{
    auto circleShape = OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();
    ASSERT_NE(circleShape, nullptr);
    OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(circleShape, 100.0f);
    OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterY(circleShape, 200.0f);
    OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(circleShape);
}

/**
 * @tc.name: NativeRenderNodeTest124
 * @tc.desc: Test SetCircleShapeOptionRadius function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest124, TestSize.Level1)
{
    auto circleShape = OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();
    ASSERT_NE(circleShape, nullptr);
    OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionRadius(circleShape, 50.0f);
    OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(circleShape);
}

/**
 * @tc.name: NativeRenderNodeTest125
 * @tc.desc: Test CreateRoundRectShapeOption and DisposeRoundRectShapeOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest125, TestSize.Level1)
{
    auto roundRectShape = OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption();
    ASSERT_NE(roundRectShape, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(roundRectShape);
}

/**
 * @tc.name: NativeRenderNodeTest126
 * @tc.desc: Test SetRoundRectShapeOptionEdgeValue and SetRoundRectShapeOptionCornerXY functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest126, TestSize.Level1)
{
    auto roundRectShape = OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption();
    ASSERT_NE(roundRectShape, nullptr);
    OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionEdgeValue(roundRectShape, 100.0f, 0.0f, 0.0f, 0.0f);
    OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionCornerXY(
        roundRectShape, 10.0f, 10.0f, ARKUI_CORNER_DIRECTION_TOP_LEFT);
    OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(roundRectShape);
}

/**
 * @tc.name: NativeRenderNodeTest127
 * @tc.desc: Test CreateCommandPathOption and DisposeCommandPathOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest127, TestSize.Level1)
{
    auto commandPath = OH_ArkUI_RenderNodeUtils_CreateCommandPathOption();
    ASSERT_NE(commandPath, nullptr);
    OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(commandPath);
}

/**
 * @tc.name: NativeRenderNodeTest128
 * @tc.desc: Test SetCommandPathOptionCommands function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest128, TestSize.Level1)
{
    auto commandPath = OH_ArkUI_RenderNodeUtils_CreateCommandPathOption();
    ASSERT_NE(commandPath, nullptr);
    char* commands = const_cast<char*>("M 100 100 L 200 100 L 200 200 Z");
    OH_ArkUI_RenderNodeUtils_SetCommandPathOptionCommands(commandPath, commands);
    OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(commandPath);
}

/**
 * @tc.name: NativeRenderNodeTest129
 * @tc.desc: Test CreateRenderNodeMaskOptionFromRectShape and CreateRenderNodeMaskOptionFromRoundRectShape functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest129, TestSize.Level1)
{
    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    auto maskFromRect = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(rectShape);
    ASSERT_NE(maskFromRect, nullptr);

    auto roundRectShape = OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption();
    ASSERT_NE(roundRectShape, nullptr);
    auto maskFromRoundRect = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRoundRectShape(roundRectShape);
    ASSERT_NE(maskFromRoundRect, nullptr);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(maskFromRect);
    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(maskFromRoundRect);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
    OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(roundRectShape);
}

/**
 * @tc.name: NativeRenderNodeTest130
 * @tc.desc: Test CreateRenderNodeMaskOptionFromCircleShape and CreateRenderNodeMaskOptionFromOvalShape functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest130, TestSize.Level1)
{
    auto circleShape = OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();
    ASSERT_NE(circleShape, nullptr);
    auto maskFromCircle = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCircleShape(circleShape);
    ASSERT_NE(maskFromCircle, nullptr);

    auto ovalShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(ovalShape, nullptr);
    auto maskFromOval = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromOvalShape(ovalShape);
    ASSERT_NE(maskFromOval, nullptr);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(maskFromCircle);
    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(maskFromOval);
    OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(circleShape);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(ovalShape);
}

/**
 * @tc.name: NativeRenderNodeTest131
 * @tc.desc: Test CreateRenderNodeMaskOptionFromCommandPath and DisposeRenderNodeMaskOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest131, TestSize.Level1)
{
    auto commandPath = OH_ArkUI_RenderNodeUtils_CreateCommandPathOption();
    ASSERT_NE(commandPath, nullptr);
    auto maskFromPath = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCommandPath(commandPath);
    ASSERT_NE(maskFromPath, nullptr);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(maskFromPath);
    OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(commandPath);
}

/**
 * @tc.name: NativeRenderNodeTest132
 * @tc.desc: Test SetRenderNodeMaskOptionFillColor and SetRenderNodeMaskOptionStrokeColor functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest132, TestSize.Level1)
{
    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    auto mask = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(rectShape);
    ASSERT_NE(mask, nullptr);

    OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(mask, 0xFF0000FF);
    OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(mask, 0xFF00FF00);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(mask);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
}

/**
 * @tc.name: NativeRenderNodeTest133
 * @tc.desc: Test SetRenderNodeMaskOptionStrokeWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest133, TestSize.Level1)
{
    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    auto mask = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(rectShape);
    ASSERT_NE(mask, nullptr);

    OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(mask, 5.0f);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(mask);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
}

/**
 * @tc.name: NativeRenderNodeTest134
 * @tc.desc: Test CreateRenderNodeClipOptionFromRectShape and CreateRenderNodeClipOptionFromRoundRectShape functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest134, TestSize.Level1)
{
    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    auto clipFromRect = OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRectShape(rectShape);
    ASSERT_NE(clipFromRect, nullptr);

    auto roundRectShape = OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption();
    ASSERT_NE(roundRectShape, nullptr);
    auto clipFromRoundRect = OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRoundRectShape(roundRectShape);
    ASSERT_NE(clipFromRoundRect, nullptr);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(clipFromRect);
    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(clipFromRoundRect);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
    OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(roundRectShape);
}

/**
 * @tc.name: NativeRenderNodeTest135
 * @tc.desc: Test CreateRenderNodeClipOptionFromCircleShape and CreateRenderNodeClipOptionFromOvalShape functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest135, TestSize.Level1)
{
    auto circleShape = OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();
    ASSERT_NE(circleShape, nullptr);
    auto clipFromCircle = OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCircleShape(circleShape);
    ASSERT_NE(clipFromCircle, nullptr);

    auto ovalShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(ovalShape, nullptr);
    auto clipFromOval = OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromOvalShape(ovalShape);
    ASSERT_NE(clipFromOval, nullptr);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(clipFromCircle);
    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(clipFromOval);
    OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(circleShape);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(ovalShape);
}

/**
 * @tc.name: NativeRenderNodeTest136
 * @tc.desc: Test CreateRenderNodeClipOptionFromCommandPath and DisposeRenderNodeClipOption functions.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest136, TestSize.Level1)
{
    auto commandPath = OH_ArkUI_RenderNodeUtils_CreateCommandPathOption();
    ASSERT_NE(commandPath, nullptr);
    auto clipFromPath = OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCommandPath(commandPath);
    ASSERT_NE(clipFromPath, nullptr);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(clipFromPath);
    OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(commandPath);
}

/**
 * @tc.name: NativeRenderNodeTest137
 * @tc.desc: Test SetMask function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest137, TestSize.Level1)
{
    auto renderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(renderNode, nullptr);

    auto rectShape = OH_ArkUI_RenderNodeUtils_CreateRectShapeOption();
    ASSERT_NE(rectShape, nullptr);
    OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(rectShape, 100.0f, 200.0f, 200.0f, 100.0f);

    auto maskOption = OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(rectShape);
    ASSERT_NE(maskOption, nullptr);
    OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(maskOption, 0xFF0000FF);
    OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(maskOption, 0xFF00FF00);
    OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(maskOption, 2.0f);

    auto result = OH_ArkUI_RenderNodeUtils_SetMask(renderNode, maskOption);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(maskOption);
    OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(rectShape);
    OH_ArkUI_RenderNodeUtils_DisposeNode(renderNode);
}

/**
 * @tc.name: NativeRenderNodeTest138
 * @tc.desc: Test SetClip function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest138, TestSize.Level1)
{
    auto renderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(renderNode, nullptr);

    auto circleShape = OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption();
    ASSERT_NE(circleShape, nullptr);
    OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(circleShape, 50.0f);
    OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterY(circleShape, 50.0f);
    OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionRadius(circleShape, 30.0f);
    auto result = OH_ArkUI_RenderNodeUtils_SetClip(renderNode, nullptr);
    ASSERT_EQ(result, ERROR_CODE_PARAM_INVALID);

    auto clipOption = OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCircleShape(circleShape);
    ASSERT_NE(clipOption, nullptr);

    result = OH_ArkUI_RenderNodeUtils_SetClip(renderNode, clipOption);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);

    OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(clipOption);
    OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(circleShape);
    OH_ArkUI_RenderNodeUtils_DisposeNode(renderNode);
}

/**
 * @tc.name: NativeRenderNodeTest201
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest201, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    ArkUI_NodeBorderStyleOption* borderStyle = OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption();
    ASSERT_NE(borderStyle, nullptr);
    result = OH_ArkUI_RenderNodeUtils_SetBorderStyle(rootRenderNode, borderStyle);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(borderStyle);
 
    ArkUI_NodeBorderStyleOption* borderStyle1 = OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption();
    ASSERT_NE(borderStyle1, nullptr);
    result = OH_ArkUI_RenderNodeUtils_GetBorderStyle(rootRenderNode, &borderStyle1);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(borderStyle1->leftStyle, ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID);
    ASSERT_EQ(borderStyle1->rightStyle, ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID);
    ASSERT_EQ(borderStyle1->topStyle, ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID);
    ASSERT_EQ(borderStyle1->bottomStyle, ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(borderStyle1);
}
 
/**
 * @tc.name: NativeRenderNodeTest202
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest202, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    ArkUI_NodeBorderWidthOption* borderWidth = OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption();
    ASSERT_NE(borderWidth, nullptr);
    result = OH_ArkUI_RenderNodeUtils_SetBorderWidth(rootRenderNode, borderWidth);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(borderWidth);
 
    ArkUI_NodeBorderWidthOption* borderWidth1 = OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption();
    ASSERT_NE(borderWidth1, nullptr);
    result = OH_ArkUI_RenderNodeUtils_GetBorderWidth(rootRenderNode, &borderWidth1);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(borderWidth1->leftWidth, 0.0f);
    ASSERT_EQ(borderWidth1->rightWidth, 0.0f);
    ASSERT_EQ(borderWidth1->topWidth, 0.0f);
    ASSERT_EQ(borderWidth1->bottomWidth, 0.0f);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(borderWidth1);
}
 
/**
 * @tc.name: NativeRenderNodeTest203
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest203, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    ArkUI_NodeBorderColorOption* borderColor = OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption();
    ASSERT_NE(borderColor, nullptr);
    result = OH_ArkUI_RenderNodeUtils_SetBorderColor(rootRenderNode, borderColor);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(borderColor);
 
    ArkUI_NodeBorderColorOption* borderColor1 = OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption();
    ASSERT_NE(borderColor1, nullptr);
    result = OH_ArkUI_RenderNodeUtils_GetBorderColor(rootRenderNode, &borderColor1);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(borderColor1->leftColor, 0);
    ASSERT_EQ(borderColor1->rightColor, 0);
    ASSERT_EQ(borderColor1->topColor, 0);
    ASSERT_EQ(borderColor1->bottomColor, 0);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(borderColor1);
}
 
/**
 * @tc.name: NativeRenderNodeTest204
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest204, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    ArkUI_NodeBorderRadiusOption* borderRadius = OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption();
    ASSERT_NE(borderRadius, nullptr);
    result = OH_ArkUI_RenderNodeUtils_SetBorderRadius(rootRenderNode, borderRadius);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(borderRadius);
 
    ArkUI_NodeBorderRadiusOption* borderRadius1 = OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption();
    ASSERT_NE(borderRadius1, nullptr);
    result = OH_ArkUI_RenderNodeUtils_GetBorderRadius(rootRenderNode, &borderRadius1);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(borderRadius1->topLeftRadius, 0.0f);
    ASSERT_EQ(borderRadius1->topRightRadius, 0.0f);
    ASSERT_EQ(borderRadius1->bottomLeftRadius, 0.0f);
    ASSERT_EQ(borderRadius1->bottomRightRadius, 0.0f);
    OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(borderRadius1);
}
 
/**
 * @tc.name: NativeRenderNodeTest205
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest205, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    result = OH_ArkUI_RenderNodeUtils_SetMarkNodeGroup(rootRenderNode, true);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}
 
/**
 * @tc.name: NativeRenderNodeTest206
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest206, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    result = OH_ArkUI_RenderNodeUtils_SetBounds(rootRenderNode, 50, 50, 100, 100);  // set x, y=50, width, height=100
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    int32_t x = 0;
    int32_t y = 0;
    int32_t width = 0;
    int32_t height = 0;
    result = OH_ArkUI_RenderNodeUtils_GetBounds(rootRenderNode, &x, &y, &width, &height);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 50);  // expect x equals to 50
    ASSERT_EQ(y, 50);  // expect y equals to 50
    ASSERT_EQ(width, 100);  // expect width equals to 100
    ASSERT_EQ(height, 100);  // expect height equals to 100
}
 
/**
 * @tc.name: NativeRenderNodeTest207
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest207, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    result = OH_ArkUI_RenderNodeUtils_SetDrawRegion(rootRenderNode, 50, 50, 100, 100);  // set x, y=50, w, h=100
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
}
 
/**
 * @tc.name: NativeRenderNodeTest208
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest208, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    auto result = OH_ArkUI_RenderNodeUtils_AddRenderNode(rootCustomNode, rootRenderNode);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
    result = OH_ArkUI_RenderNodeUtils_AttachContentModifier(rootRenderNode, modifier);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}
 
/**
 * @tc.name: NativeRenderNodeTest209
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest209, TestSize.Level1)
{
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
 
    ArkUI_FloatPropertyHandle property = OH_ArkUI_RenderNodeUtils_CreateFloatProperty(0.5f);  // set value=0.5f
    ASSERT_NE(property, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(value, 0.5f);  // expect value equals to 0.5f
    result = OH_ArkUI_RenderNodeUtils_SetFloatPropertyValue(property, 1.5f);  // set value=1.5f
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(value, 1.5f);  // expect value equals to 1.5f
 
    result = OH_ArkUI_RenderNodeUtils_AttachFloatProperty(modifier, property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(property);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}
 
/**
 * @tc.name: NativeRenderNodeTest210
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest210, TestSize.Level1)
{
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
 
    ArkUI_Vector2PropertyHandle property = OH_ArkUI_RenderNodeUtils_CreateVector2Property(0.5f, 0.5f);  // set x, y=0.5f
    ASSERT_NE(property, nullptr);
    float x = 0.0f;
    float y = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(property, &x, &y);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 0.5f);  // expect x equals to 0.5f
    ASSERT_EQ(y, 0.5f);  // expect y equals to 0.5f
    result = OH_ArkUI_RenderNodeUtils_SetVector2PropertyValue(property, 1.5f, 1.5f);  // set x, y=1.5f
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(property, &x, &y);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 1.5f);  // expect x equals to 1.5f
    ASSERT_EQ(y, 1.5f);  // expect y equals to 1.5f
 
    result = OH_ArkUI_RenderNodeUtils_AttachVector2Property(modifier, property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeVector2Property(property);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}
 
/**
 * @tc.name: NativeRenderNodeTest211
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest211, TestSize.Level1)
{
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
 
    ArkUI_ColorPropertyHandle property =
        OH_ArkUI_RenderNodeUtils_CreateColorProperty(0xFF0000FF);  // set value=0xFF0000FF
    ASSERT_NE(property, nullptr);
    uint32_t value = 0;
    auto result = OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_SetColorPropertyValue(property, 0xFF00FF00);  // set value=0xFF00FF00
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    result = OH_ArkUI_RenderNodeUtils_AttachColorProperty(modifier, property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeColorProperty(property);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}
 
/**
 * @tc.name: NativeRenderNodeTest212
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest212, TestSize.Level1)
{
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
 
    ArkUI_FloatAnimatablePropertyHandle property =
        OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(0.5f);  // set value=0.5f
    ASSERT_NE(property, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(value, 0.5f);  // expect value equals to 0.5f
    result = OH_ArkUI_RenderNodeUtils_SetFloatAnimatablePropertyValue(property, 1.5f);  // set value=1.5f
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(value, 1.5f);  // expect value equals to 1.5f
 
    result = OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty(modifier, property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(property);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}
 
/**
 * @tc.name: NativeRenderNodeTest213
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest213, TestSize.Level1)
{
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
 
    ArkUI_Vector2AnimatablePropertyHandle property =
        OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(0.5f, 0.5f);  // set x, y=0.5f
    ASSERT_NE(property, nullptr);
    float x = 0.0f;
    float y = 0.0f;
    auto result = OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(property, &x, &y);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 0.5f);  // expect x equals to 0.5f
    ASSERT_EQ(y, 0.5f);  // expect y equals to 0.5f
    result = OH_ArkUI_RenderNodeUtils_SetVector2AnimatablePropertyValue(property, 1.5f, 1.5f);  // set x, y=1.5f
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(property, &x, &y);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    ASSERT_EQ(x, 1.5f);  // expect x equals to 1.5f
    ASSERT_EQ(y, 1.5f);  // expect y equals to 1.5f
 
    result = OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty(modifier, property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(property);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}
 
/**
 * @tc.name: NativeRenderNodeTest214
 * @tc.desc: Test renderNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodeTest, NativeRenderNodeTest214, TestSize.Level1)
{
    ArkUI_RenderContentModifierHandle modifier = OH_ArkUI_RenderNodeUtils_CreateContentModifier();
    ASSERT_NE(modifier, nullptr);
 
    ArkUI_ColorAnimatablePropertyHandle property =
        OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(0xFF0000FF);  // set value=0xFF0000FF
    ASSERT_NE(property, nullptr);
    uint32_t value = 0;
    auto result = OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_SetColorAnimatablePropertyValue(property, 0xFF00FF00);  // set value=0xFF00FF00
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    result = OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(property, &value);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
 
    result = OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty(modifier, property);
    ASSERT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(property);
    OH_ArkUI_RenderNodeUtils_DisposeContentModifier(modifier);
}

} // namespace OHOS::Ace