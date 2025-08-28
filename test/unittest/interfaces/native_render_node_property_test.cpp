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
class NativeRenderNodePropertyTest : public testing::Test {
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
 * @tc.name: NativeRenderNodePropertyTest001
 * @tc.desc: Test renderNode backgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);

    uint32_t backgroundColor = 0;
    OH_ArkUI_RenderNodeUtils_SetBackgroundColor(rootRenderNode, 80000000);
    OH_ArkUI_RenderNodeUtils_GetBackgroundColor(rootRenderNode, &backgroundColor);
    ASSERT_EQ(backgroundColor, 79803706);
}

/**
 * @tc.name: NativeRenderNodePropertyTest002
 * @tc.desc: Test renderNode ClipToFrame.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    int32_t clipToFrameResult = true;
    OH_ArkUI_RenderNodeUtils_SetClipToFrame(rootRenderNode, true);
    OH_ArkUI_RenderNodeUtils_GetClipToFrame(rootRenderNode, &clipToFrameResult);
    ASSERT_TRUE(clipToFrameResult);
}

/**
 * @tc.name: NativeRenderNodePropertyTest003
 * @tc.desc: Test renderNode ClipToBounds.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest003, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    int32_t clipToBounds = true;
    OH_ArkUI_RenderNodeUtils_SetClipToBounds(rootRenderNode, 1);
    OH_ArkUI_RenderNodeUtils_GetClipToBounds(rootRenderNode, &clipToBounds);
    ASSERT_TRUE(clipToBounds);
}

/**
 * @tc.name: NativeRenderNodePropertyTest004
 * @tc.desc: Test renderNode opacity.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest004, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float opacity = 0;
    OH_ArkUI_RenderNodeUtils_SetOpacity(rootRenderNode, 0.5f);
    OH_ArkUI_RenderNodeUtils_GetOpacity(rootRenderNode, &opacity);
    ASSERT_EQ(opacity, 0.5f);
}

/**
 * @tc.name: NativeRenderNodePropertyTest005
 * @tc.desc: Test renderNode size.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest005, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    int32_t getSizeWidth = 0;
    int32_t getSizeHeight = 0;
    OH_ArkUI_RenderNodeUtils_SetSize(rootRenderNode, 300, 400);
    OH_ArkUI_RenderNodeUtils_GetSize(rootRenderNode, &getSizeWidth, &getSizeHeight);
    ASSERT_EQ(getSizeWidth, 300);
    ASSERT_EQ(getSizeHeight, 400);
}

/**
 * @tc.name: NativeRenderNodePropertyTest006
 * @tc.desc: Test renderNode position.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest006, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    int32_t setPositionX = 0;
    int32_t setPositionY = 0;
    OH_ArkUI_RenderNodeUtils_SetPosition(rootRenderNode, 200, 1500);
    OH_ArkUI_RenderNodeUtils_GetPosition(rootRenderNode, &setPositionX, &setPositionY);
    ASSERT_EQ(setPositionX, 200);
    ASSERT_EQ(setPositionY, 1500);
}

/**
 * @tc.name: NativeRenderNodePropertyTest007
 * @tc.desc: Test renderNode pivot.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest007, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float setPivotX = 0;
    float setPivotY = 0;
    OH_ArkUI_RenderNodeUtils_SetPivot(rootRenderNode, 5655, 232);
    OH_ArkUI_RenderNodeUtils_GetPivot(rootRenderNode, &setPivotX, &setPivotY);
    ASSERT_EQ(setPivotX, 5655);
    ASSERT_EQ(setPivotY, 232);
}

/**
 * @tc.name: NativeRenderNodePropertyTest008
 * @tc.desc: Test renderNode scale.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest008, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float setScaleX = 0;
    float setScaleY = 0;
    OH_ArkUI_RenderNodeUtils_SetScale(rootRenderNode, 36, 39);
    OH_ArkUI_RenderNodeUtils_GetScale(rootRenderNode, &setScaleX, &setScaleY);
    ASSERT_EQ(setScaleX, 36);
    ASSERT_EQ(setScaleY, 39);
}

/**
 * @tc.name: NativeRenderNodePropertyTest009
 * @tc.desc: Test renderNode translation.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest009, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float setTranslationX = 0;
    float setTranslationY = 0;
    OH_ArkUI_RenderNodeUtils_SetTranslation(rootRenderNode, 33, 44);
    OH_ArkUI_RenderNodeUtils_GetTranslation(rootRenderNode, &setTranslationX, &setTranslationY);
    ASSERT_EQ(setTranslationX, 33);
    ASSERT_EQ(setTranslationY, 44);
}

/**
 * @tc.name: NativeRenderNodePropertyTest010
 * @tc.desc: Test renderNode rotation.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest010, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float setRotationX = 0;
    float setRotationY = 0;
    float setRotationZ = 0;
    OH_ArkUI_RenderNodeUtils_SetRotation(rootRenderNode, 414, 55, 12);
    OH_ArkUI_RenderNodeUtils_GetRotation(rootRenderNode, &setRotationX, &setRotationY, &setRotationZ);
    ASSERT_EQ(setRotationX, 414);
    ASSERT_EQ(setRotationY, 55);
    ASSERT_EQ(setRotationZ, 12);
}

/**
 * @tc.name: NativeRenderNodePropertyTest011
 * @tc.desc: Test renderNode shadowColor.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest011, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    uint32_t shadowColor = 0;
    OH_ArkUI_RenderNodeUtils_SetShadowColor(rootRenderNode, 80000000);
    OH_ArkUI_RenderNodeUtils_GetShadowColor(rootRenderNode, &shadowColor);
    ASSERT_EQ(shadowColor, 80000000);
}

/**
 * @tc.name: NativeRenderNodePropertyTest012
 * @tc.desc: Test renderNode shadowOffset.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest012, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    int32_t shadowOffsetX = 0;
    int32_t shadowOffsetY = 0;
    OH_ArkUI_RenderNodeUtils_SetShadowOffset(rootRenderNode, 27, 56);
    OH_ArkUI_RenderNodeUtils_GetShadowOffset(rootRenderNode, &shadowOffsetX, &shadowOffsetY);
    ASSERT_EQ(shadowOffsetX, 27);
    ASSERT_EQ(shadowOffsetY, 56);
}

/**
 * @tc.name: NativeRenderNodePropertyTest013
 * @tc.desc: Test renderNode shadowAlpha.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest013, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float alpha = 0;
    OH_ArkUI_RenderNodeUtils_SetShadowAlpha(rootRenderNode, 0.5f);
    OH_ArkUI_RenderNodeUtils_GetShadowAlpha(rootRenderNode, &alpha);
    ASSERT_LE(alpha, 0.5f);
}

/**
 * @tc.name: NativeRenderNodePropertyTest014
 * @tc.desc: Test renderNode shadowElevation.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest014, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float elevation = 0;
    OH_ArkUI_RenderNodeUtils_SetShadowElevation(rootRenderNode, 67556);
    OH_ArkUI_RenderNodeUtils_GetShadowElevation(rootRenderNode, &elevation);
    ASSERT_EQ(elevation, 67556);
}

/**
 * @tc.name: NativeRenderNodePropertyTest015
 * @tc.desc: Test renderNode shadowRadius.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest015, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float radius = 0;
    OH_ArkUI_RenderNodeUtils_SetShadowRadius(rootRenderNode, 235553);
    OH_ArkUI_RenderNodeUtils_GetShadowRadius(rootRenderNode, &radius);
    ASSERT_EQ(radius, 235553);
}

/**
 * @tc.name: NativeRenderNodePropertyTest016
 * @tc.desc: Test renderNode transform.
 * @tc.type: FUNC
 */
HWTEST_F(NativeRenderNodePropertyTest, NativeRenderNodePropertyTest016, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootCustomNode = nodeAPI->createNode(ARKUI_NODE_CUSTOM);
    ASSERT_NE(rootCustomNode, nullptr);
    auto rootRenderNode = OH_ArkUI_RenderNodeUtils_CreateNode();
    ASSERT_NE(rootRenderNode, nullptr);
    
    float matrix[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    auto result = OH_ArkUI_RenderNodeUtils_SetTransform(rootRenderNode, matrix);
    ASSERT_EQ(result, ERROR_CODE_NO_ERROR);
}
} // namespace OHOS::Ace