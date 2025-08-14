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

#include "gtest/gtest.h"
#include "native_interface.h"
#include "native_node.h"
#include "native_type.h"
#include "node_component_snapshot.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
class SnapshotTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp();
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: SnapshotTest001
 * @tc.desc: Test OH_ArkUI_CreateSnapshotOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue value[] = { { .f32 = 150 } };
    ArkUI_AttributeItem item = { value, 1 };
    nodeAPI->setAttribute(button, NODE_WIDTH, &item);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &item);
    nodeAPI->addChild(node, button);
    auto options = OH_ArkUI_CreateSnapshotOptions();
    EXPECT_NE(options, nullptr);
}

/**
 * @tc.name: SnapshotTest002
 * @tc.desc: Test OH_ArkUI_SnapshotOptions_SetScale function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue value[] = { { .f32 = 150 } };
    ArkUI_AttributeItem item = { value, 1 };
    nodeAPI->setAttribute(button, NODE_WIDTH, &item);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &item);
    nodeAPI->addChild(node, button);
    auto options = OH_ArkUI_CreateSnapshotOptions();
    ASSERT_NE(options, nullptr);
    EXPECT_EQ(OH_ArkUI_SnapshotOptions_SetScale(options, 0.0f), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SnapshotTest003
 * @tc.desc: Test OH_ArkUI_SnapshotOptions_SetScale function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest003, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue value[] = { { .f32 = 150 } };
    ArkUI_AttributeItem item = { value, 1 };
    nodeAPI->setAttribute(button, NODE_WIDTH, &item);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &item);
    nodeAPI->addChild(node, button);
    auto options = OH_ArkUI_CreateSnapshotOptions();
    ASSERT_NE(options, nullptr);
    auto opt = reinterpret_cast<ArkUISnapshotOptions*>(options);
    OH_ArkUI_SnapshotOptions_SetScale(options, 0.5f);
    EXPECT_EQ(opt->scale, 0.5f);
}

/**
 * @tc.name: SnapshotTest004
 * @tc.desc: Test OH_ArkUI_SnapshotOptions_SetScale function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest004, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue value[] = { { .f32 = 150 } };
    ArkUI_AttributeItem item = { value, 1 };
    nodeAPI->setAttribute(button, NODE_WIDTH, &item);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &item);
    nodeAPI->addChild(node, button);
    auto options = OH_ArkUI_CreateSnapshotOptions();
    ASSERT_NE(options, nullptr);
    auto opt = reinterpret_cast<ArkUISnapshotOptions*>(options);
    OH_ArkUI_SnapshotOptions_SetScale(options, 1.5f);
    EXPECT_EQ(opt->scale, 1.5f);
}

/**
 * @tc.name: SnapshotTest005
 * @tc.desc: Test OH_ArkUI_GetNodeSnapshot function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest005, TestSize.Level1)
{
    OH_PixelmapNative* pixelmap = nullptr;
    auto result = OH_ArkUI_GetNodeSnapshot(nullptr, nullptr, &pixelmap);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SnapshotTest006
 * @tc.desc: Test OH_ArkUI_SnapshotOptions_SetScale function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest006, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto node = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto button = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ArkUI_NumberValue value[] = { { .f32 = 150 } };
    ArkUI_AttributeItem item = { value, 1 };
    nodeAPI->setAttribute(button, NODE_WIDTH, &item);
    nodeAPI->setAttribute(button, NODE_HEIGHT, &item);
    nodeAPI->addChild(node, button);
    auto options = OH_ArkUI_CreateSnapshotOptions();
    ASSERT_NE(options, nullptr);
    EXPECT_EQ(OH_ArkUI_SnapshotOptions_SetScale(options, -1.0f), ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: SnapshotTest007
 * @tc.desc: Test OH_ArkUI_GetNodeSnapshot function.
 * @tc.type: FUNC
 */
HWTEST_F(SnapshotTest, SnapshotTest007, TestSize.Level1)
{
    OH_PixelmapNative* pixelmap = nullptr;
    auto options = OH_ArkUI_CreateSnapshotOptions();
    ASSERT_NE(options, nullptr);
    OH_ArkUI_SnapshotOptions_SetScale(options, 1.5f);
    auto result = OH_ArkUI_GetNodeSnapshot(nullptr, options, &pixelmap);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}
} // namespace OHOS::Ace