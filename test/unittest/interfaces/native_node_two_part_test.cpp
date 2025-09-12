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
#include "native_type.h"
#include "native_styled_string.h"
#include "event_converter.h"
#include "interfaces/native/node/node_extened.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/styled_string.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components_ng/base/ui_node.h"
#include "frameworks/core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
namespace {
    constexpr int32_t SIZE_2 = 2;
    constexpr int32_t SIZE_3 = 3;
}

class NativeNodeTwoPartTest : public testing::Test {
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
 * @tc.name: NativeNodeAlignitems
 * @tc.desc: Test alignitems function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeAlignitems, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

     //set get and reset
    ArkUI_NumberValue value[] = {{ .i32 = 1 }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_ALIGN_ITEMS, &item), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_GRID_ALIGN_ITEMS);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, 1);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_GRID_ALIGN_ITEMS), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_ALIGN_ITEMS);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, 0);
 
    // set invalid value
    value[0].i32 = -1;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_ALIGN_ITEMS, &item), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_ALIGN_ITEMS);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, 0);

    ArkUI_NumberValue zeroSizeValue[] = {};
    ArkUI_AttributeItem zeroSizeItem = {zeroSizeValue, sizeof(zeroSizeValue) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_ALIGN_ITEMS, &zeroSizeItem), ARKUI_ERROR_CODE_PARAM_INVALID);
    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeEnableScrollinteractionTest001
 * @tc.desc: Test enableScrollinteraction function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeEnableScrollinteractionTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    //set get and reset
    ArkUI_NumberValue value[] = {{ .i32 = true }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->value[0].i32);

    value[0].i32 = false;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->value[0].i32);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->value[0].i32);
 
    // set invalid value
    value[0].i32 = -1;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->value[0].i32);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->value[0].i32);

    ArkUI_NumberValue zeroSizeValue[] = {};
    ArkUI_AttributeItem zeroSizeItem = {zeroSizeValue, sizeof(zeroSizeValue) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &zeroSizeItem),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeEnableScrollinteractionTest002
 * @tc.desc: Test enableScrollinteraction of other node in order to cover other branch.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeEnableScrollinteractionTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);

    ArkUI_NumberValue value[] = {{ .i32 = true }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_ENABLE_SCROLL_INTERACTION);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeFriction001
 * @tc.desc: Test friction of grid.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeFriction001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    auto rootFrameNode = reinterpret_cast<ArkUI_Node*>(rootNode);
    ASSERT_NE(rootFrameNode, nullptr);
    auto frameNode = reinterpret_cast<NG::FrameNode*>(rootFrameNode->uiNodeHandle);
    ASSERT_NE(frameNode, nullptr);
    auto context = NG::MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    frameNode->context_ = AceType::RawPtr(context);
    RefPtr<NG::FrameNode> frameNodeRefPtr = AceType::Claim(frameNode);
    ASSERT_NE(context, frameNodeRefPtr);
    OHOS::Ace::NG::ViewStackProcessor::GetInstance()->Push(frameNodeRefPtr);

    //set get and reset
    ArkUI_NumberValue value[] = {{ .f32 = 0.5 }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    nodeAPI->setAttribute(rootNode, NODE_SCROLL_FRICTION, &item);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_FRICTION);
    EXPECT_EQ(result->value[0].f32, 0.5);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_FRICTION), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_FRICTION);
    ASSERT_NE(result, nullptr);

    // set invalid value
    value[0].f32 = -1.0f;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_FRICTION, &item), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_FRICTION);
    ASSERT_NE(result, nullptr);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_FRICTION, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_FRICTION);
    ASSERT_NE(result, nullptr);

    ArkUI_NumberValue zeroSizeValue[] = {};
    ArkUI_AttributeItem zeroSizeItem = {zeroSizeValue, sizeof(zeroSizeValue) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_FRICTION, &zeroSizeItem),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeFriction002
 * @tc.desc: Test friction of other node in order to cover other branch.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeFriction002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);

    ArkUI_NumberValue value[] = {{ .f32 = 0.5 }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_FRICTION, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_FRICTION), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_FRICTION);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}

void TestGridLayoutOptionsIrregularIndexes(ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes)
{
    int size = 1;
    uint32_t tmpIrregularIndexes[1];
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option, tmpIrregularIndexes, &size),
        ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR);
   
    size = SIZE_2;
    std::vector<uint32_t> retIrregularIndexes(size);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option, retIrregularIndexes.data(), &size),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retIrregularIndexes[0], irregularIndexes[0]);
    EXPECT_EQ(retIrregularIndexes[1], irregularIndexes[1]);

    int retSize = SIZE_3;
    std::vector<uint32_t> retIndexes(retSize);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option, retIndexes.data(), &retSize),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retSize, SIZE_2);
    EXPECT_EQ(retIndexes[0], irregularIndexes[0]);
    EXPECT_EQ(retIndexes[1], irregularIndexes[1]);

    // set invalid value
    std::vector<uint32_t> invalidIndexes(1);
    int invalidSize = 1;
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option, invalidIndexes.data(), &invalidSize),
        ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR);
    
    invalidSize = 0;
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option, nullptr, &invalidSize),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, irregularIndexes, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(nullptr, irregularIndexes, SIZE_2),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, nullptr, SIZE_2), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, irregularIndexes, -1), ARKUI_ERROR_CODE_PARAM_INVALID);

    uint32_t zeroSizeIrregularIndexes[0];
    EXPECT_EQ(
        OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, zeroSizeIrregularIndexes, 0), ARKUI_ERROR_CODE_NO_ERROR);
}

void TestRegisterGetIrregularSizeByIndexCallback(ArkUI_GridLayoutOptions* option)
{
    auto str = std::make_unique<std::string>("hello");
    void* userData = static_cast<void*>(str.get());

    OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
        option, userData, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemSize {
            if (userData == nullptr) {
                return { 1, 1 };
            }
            std::string* str = static_cast<std::string*>(userData);
            EXPECT_STREQ(str->c_str(), "hello");
            return { 2, 4 };
        });

    OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
        option, nullptr, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemSize {
            if (userData == nullptr) {
                return { 1, 1 };
            }

            return { 2, 4 };
        });
}

void TestRegisterGetRectByIndexCallback(ArkUI_GridLayoutOptions* option)
{
    auto str2 = std::make_unique<std::string>("world");
    void* userData2 = static_cast<void*>(str2.get());
    OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
        option, userData2, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemRect {
            if (userData == nullptr) {
                return { 1, 1 };
            }
            std::string* str = static_cast<std::string*>(userData);
            EXPECT_STREQ(str->c_str(), "world");
            return ArkUI_GridItemRect { 5, 5, 1, 1 };
        });

    OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
        option, nullptr, [](int32_t itemIndex, void* userData) -> ArkUI_GridItemRect {
            if (userData == nullptr) {
                return { 1, 1 };
            }
            return ArkUI_GridItemRect { 5, 5, 1, 1 };
        });
}
/**
 * @tc.name: NativeNodeGridLayoutOptions
 * @tc.desc: Test gridLayoutOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridLayoutOptions, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    // set and get
    auto option = OH_ArkUI_GridLayoutOptions_Create();
    uint32_t irregularIndexes[] = { 0, 7 };
    EXPECT_EQ(
        OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, irregularIndexes, SIZE_2), ARKUI_ERROR_CODE_NO_ERROR);

    TestRegisterGetIrregularSizeByIndexCallback(option);
    TestRegisterGetRectByIndexCallback(option);

    ArkUI_AttributeItem item = { .object = option };
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS, &item), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS);
    ASSERT_NE(result, nullptr);
    auto retOption = reinterpret_cast<ArkUI_GridLayoutOptions*>(result->object);
    ASSERT_NE(retOption, nullptr);
    EXPECT_EQ(retOption, option);

    TestGridLayoutOptionsIrregularIndexes(retOption, irregularIndexes);
    OH_ArkUI_GridLayoutOptions_Dispose(option);
    OH_ArkUI_GridLayoutOptions_Dispose(nullptr);
    nodeAPI->disposeNode(rootNode);
}

void TestGridLayoutOptionsReset(
    ArkUI_NativeNodeAPI_1* nodeAPI, ArkUI_NodeHandle rootNode, uint32_t* irregularIndexes1)
{
    //reset
    EXPECT_EQ(nodeAPI->resetAttribute(nullptr, NODE_GRID_LAYOUT_OPTIONS), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto result = nodeAPI->getAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS);
    ASSERT_NE(result, nullptr);
    auto retOption = reinterpret_cast<ArkUI_GridLayoutOptions*>(result->object);
    auto retSize = SIZE_2;
    std::vector<uint32_t> retIndexes(retSize);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(retOption, retIndexes.data(), &retSize),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retSize, SIZE_2);
    EXPECT_EQ(retIndexes[0], irregularIndexes1[0]);
    EXPECT_EQ(retIndexes[1], irregularIndexes1[1]);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS);
    ASSERT_NE(result, nullptr);
    retOption = reinterpret_cast<ArkUI_GridLayoutOptions*>(result->object);
    retSize = SIZE_3;
    retIndexes.resize(retSize);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(retOption, retIndexes.data(), &retSize),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retSize, SIZE_2);
}

/**
 * @tc.name: NativeNodeGridLayoutOptions001
 * @tc.desc: Test gridLayoutOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridLayoutOptions001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    // set and get
    auto option = OH_ArkUI_GridLayoutOptions_Create();
    uint32_t irregularIndexes[] = {};
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option, irregularIndexes, 0), ARKUI_ERROR_CODE_NO_ERROR);
    ArkUI_AttributeItem item = { .object = option };
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS, &item), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS);
    ASSERT_NE(result, nullptr);
    auto retOption = reinterpret_cast<ArkUI_GridLayoutOptions*>(result->object);
    ASSERT_NE(retOption, nullptr);
    EXPECT_EQ(retOption, option);
    auto retSize = SIZE_2;
    std::vector<uint32_t> retIndexes(retSize);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(retOption, retIndexes.data(), &retSize),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retSize, 0);

    auto option2 = OH_ArkUI_GridLayoutOptions_Create();
    retSize = SIZE_2;
    retIndexes.resize(retSize);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(option2, retIndexes.data(), &retSize),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retSize, 0);
    
    uint32_t irregularIndexes1[] = { 0, 7 };
    EXPECT_EQ(
        OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(option2, irregularIndexes1, SIZE_2), ARKUI_ERROR_CODE_NO_ERROR);
    ArkUI_AttributeItem item1 = { .object = option2 };
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS, &item1), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_LAYOUT_OPTIONS);
    ASSERT_NE(result, nullptr);
    retOption = reinterpret_cast<ArkUI_GridLayoutOptions*>(result->object);
    ASSERT_NE(retOption, nullptr);
    EXPECT_EQ(retOption, option2);
    retSize = SIZE_2;
    retIndexes.resize(retSize);
    EXPECT_EQ(OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(retOption, retIndexes.data(), &retSize),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(retSize, SIZE_2);
    EXPECT_EQ(retIndexes[0], irregularIndexes1[0]);
    EXPECT_EQ(retIndexes[1], irregularIndexes1[1]);

    // Continue with reset tests
    TestGridLayoutOptionsReset(nodeAPI, rootNode, irregularIndexes1);

    OH_ArkUI_GridLayoutOptions_Dispose(option);
    OH_ArkUI_GridLayoutOptions_Dispose(option2);
    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeNestedScrollTest001
 * @tc.desc: Test nestedScroll of grid.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeNestedScrollTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    // set get and reset
    ArkUI_NumberValue scrollnested[] = { { .i32 = ARKUI_SCROLL_NESTED_MODE_SELF_FIRST },
        { .i32 = ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST } };
    ArkUI_AttributeItem scrollnestedItem = { scrollnested, sizeof(scrollnested) / sizeof(ArkUI_NumberValue) };
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL, &scrollnestedItem), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_NESTED_MODE_SELF_FIRST);
    EXPECT_EQ(result->value[1].i32, ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);
    EXPECT_EQ(result->value[1].i32, ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);

    // set invalid value
    ArkUI_NumberValue invalidScrollnested[] = { { .i32 = -1 }, { .i32 = -1 } };
    ArkUI_AttributeItem invalidScrollnestedItem = { invalidScrollnested,
        sizeof(invalidScrollnested) / sizeof(ArkUI_NumberValue) };
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL, &invalidScrollnestedItem),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);
    EXPECT_EQ(result->value[1].i32, ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);
    EXPECT_EQ(result->value[1].i32, ARKUI_SCROLL_NESTED_MODE_SELF_ONLY);

    ArkUI_NumberValue zeroSizeValue[] = {};
    ArkUI_AttributeItem zeroSizeItem = {zeroSizeValue, sizeof(zeroSizeValue) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL, &zeroSizeItem),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeNestedScrollTest002
 * @tc.desc: Test nestedScroll of other node in order to cover other branch.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeNestedScrollTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);

    ArkUI_NumberValue value[] = { { .i32 = ARKUI_SCROLL_NESTED_MODE_SELF_FIRST },
        { .i32 = ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST } };
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_NESTED_SCROLL);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeScrollBarTest001
 * @tc.desc: Test scrollbar of grid.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeScrollBarTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    // set get and reset
    ArkUI_NumberValue value[] = {{ .i32 = ARKUI_SCROLL_BAR_DISPLAY_MODE_ON }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_BAR_DISPLAY_MODE_ON);

    value[0].i32 = ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE, &item), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO);
 
    // set invalid value
    value[0].i32 = -1;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE, &item), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO);

    ArkUI_NumberValue zeroSizeValue[] = {};
    ArkUI_AttributeItem zeroSizeItem = {zeroSizeValue, sizeof(zeroSizeValue) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE, &zeroSizeItem),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeScrollBarTest002
 * @tc.desc: Test scrollbar of other node in order to cover other branch.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeScrollBarTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);

    ArkUI_NumberValue value[] = {{ .i32 = ARKUI_SCROLL_BAR_DISPLAY_MODE_ON }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_DISPLAY_MODE);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeScrollBarColorTest001
 * @tc.desc: Test scrollBarColor of grid.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeScrollBarColorTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    //set and get
    ArkUI_NumberValue value[] = {{ .u32 = 0xFFFF0000 }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_COLOR, &item), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_COLOR);
    ASSERT_NE(result, nullptr);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_BAR_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_COLOR);
    ASSERT_NE(result, nullptr);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_COLOR, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_COLOR);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeScrollBarColorTest002
 * @tc.desc: Test scrollBarColor of other node in order to cover other branch.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeScrollBarColorTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);

    ArkUI_NumberValue value[] = {{ .u32 = 0xFFFF0000 }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_COLOR, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_BAR_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_COLOR);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}


/**
 * @tc.name: NativeNodeScrollBarWidthTest001
 * @tc.desc: Test scrollBarWidth of grid.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeScrollBarWidthTest001, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    //set get and reset
    ArkUI_NumberValue value[] = {{ .f32 = 1.0f }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_WIDTH, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_NE(nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_WIDTH), nullptr);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_BAR_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_WIDTH);
    ASSERT_NE(result, nullptr);

    // set invalid value
    value[0] = { .f32 = -1.0f };
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_WIDTH, &item), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_WIDTH);
    ASSERT_NE(result, nullptr);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_WIDTH, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_WIDTH);
    ASSERT_NE(result, nullptr);

    ArkUI_NumberValue zeroSizeValue[] = {};
    ArkUI_AttributeItem zeroSizeItem = {zeroSizeValue, sizeof(zeroSizeValue) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_WIDTH, &zeroSizeItem),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeScrollBarWidthTest002
 * @tc.desc: Test scrollBarColor of other node in order to cover other branch.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeScrollBarWidthTest002, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);

    ArkUI_NumberValue value[] = {{ .f32 = 1.0f }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_SCROLL_BAR_WIDTH, &item), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCROLL_BAR_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_SCROLL_BAR_WIDTH);
    ASSERT_NE(result, nullptr);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeGridItemOptions
 * @tc.desc: Test gridItemOptions function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridItemOptions, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_GRID);
    ASSERT_NE(rootNode, nullptr);

    //set get and reset
    ArkUI_NumberValue value[] = {{ .i32 = GRID_ITEM_STYLE_PLAIN }};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue), "test"};
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_ITEM_STYLE, &item), ARKUI_ERROR_CODE_NO_ERROR);
    auto result = nodeAPI->getAttribute(rootNode, NODE_GRID_ITEM_STYLE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, GRID_ITEM_STYLE_PLAIN);

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_GRID_ITEM_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_ITEM_STYLE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32, GRID_ITEM_STYLE_NONE);
 
    // set invalid value
    value[0].i32 = -1;
    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_ITEM_STYLE, &item), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_ITEM_STYLE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32,  GRID_ITEM_STYLE_NONE);

    EXPECT_EQ(nodeAPI->setAttribute(rootNode, NODE_GRID_ITEM_STYLE, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    result = nodeAPI->getAttribute(rootNode, NODE_GRID_ITEM_STYLE);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->value[0].i32,  GRID_ITEM_STYLE_NONE);

    nodeAPI->disposeNode(rootNode);
}

/**
 * @tc.name: NativeNodeGridOnScrollBarUpdate
 * @tc.desc: Test Grid onScrollBarUpdate event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnScrollBarUpdate, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_GRID_ON_SCROLL_BAR_UPDATE, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_GRID_ON_SCROLL_BAR_UPDATE);
    nodeAPI->disposeNode(scroll);
}

/**
 * @tc.name: NativeNodeGridOnScrollFrameBegin
 * @tc.desc: Test Grid onScrollFrameBegin event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnScrollFrameBegin, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN);
    nodeAPI->disposeNode(scroll);
}

/**
 * @tc.name: NativeNodeGridOnScrollindex
 * @tc.desc: Test Grid onScrollindex event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnScrollindex, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_GRID_ON_SCROLL_INDEX, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_GRID_ON_SCROLL_INDEX);
    nodeAPI->disposeNode(scroll);
}

/**
 * @tc.name: NativeNodeGridOnScrollStart
 * @tc.desc: Test Grid onScrollStart event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnScrollStart, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL_START, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL_START);
    nodeAPI->disposeNode(scroll);
}

/**
 * @tc.name: NativeNodeGridOnScrollStop
 * @tc.desc: Test Grid onScrollStop event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnScrollStop, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL_STOP, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL_STOP);
    nodeAPI->disposeNode(scroll);
}

/**
 * @tc.name: NativeNodeGridOnWillScroll
 * @tc.desc: Test Grid onWillScroll event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnWillScroll, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_GRID_ON_WILL_SCROLL, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_GRID_ON_WILL_SCROLL);
    nodeAPI->disposeNode(scroll);
}

/**
 * @tc.name: NativeNodeGridOnDidScroll
 * @tc.desc: Test Grid onDidScroll event.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTwoPartTest, NativeNodeGridOnDidScroll, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto scroll = nodeAPI->createNode(ARKUI_NODE_GRID);

    auto ret = nodeAPI->registerNodeEvent(scroll, NODE_GRID_ON_DID_SCROLL, 1, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    nodeAPI->unregisterNodeEvent(scroll, NODE_GRID_ON_DID_SCROLL);
    nodeAPI->disposeNode(scroll);
}
} // namespace OHOS::Ace
