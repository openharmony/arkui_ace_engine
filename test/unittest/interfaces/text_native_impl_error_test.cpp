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

#include "gtest/gtest.h"
#include "node_model.h"
#include "text_native_impl.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NodeModel;

class TextNativeImplErrorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        InitialFullImpl();
    }
    static void TearDownTestCase() {}
};

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetContent_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetContent with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetContent_NullItem_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetContent(nullptr, "test");
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetContent_NullContent_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetContent with null content.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetContent_NullContent_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetContent(item, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetContent_Success_003
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetContent with valid parameters.
 *           Verifies content is set and can be retrieved correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetContent_Success_003, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetContent(item, "hello");
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    char buffer[32] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode getResult = OH_ArkUI_TextMenuItem_GetContent(item, buffer, 32, &writeLen);
    EXPECT_EQ(getResult, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(buffer, "hello");
    EXPECT_EQ(writeLen, 5);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetContent_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetContent with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetContent_NullItem_001, TestSize.Level1)
{
    char buffer[32] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetContent(nullptr, buffer, 32, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetContent_NullContent_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetContent with item that has no content set.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetContent_NullContent_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    char buffer[32] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetContent(item, buffer, 32, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetContent_NullBuffer_003
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetContent with null buffer.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetContent_NullBuffer_003, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    OH_ArkUI_TextMenuItem_SetContent(item, "test");
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetContent(item, nullptr, 32, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetContent_NullWriteLength_004
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetContent with null writeLength.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetContent_NullWriteLength_004, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    OH_ArkUI_TextMenuItem_SetContent(item, "test");
    char buffer[32] = { 0 };
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetContent(item, buffer, 32, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetContent_BufferTooSmall_005
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetContent with buffer size too small.
 *           Verifies SET_ERROR_MESSAGE triggers and returns BUFFER_SIZE_ERROR.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetContent_BufferTooSmall_005, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    OH_ArkUI_TextMenuItem_SetContent(item, "hello world");
    char buffer[4] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetContent(item, buffer, 4, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetIcon_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetIcon with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetIcon_NullItem_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetIcon(nullptr, "icon.png");
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetIcon_NullIcon_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetIcon with null icon path.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetIcon_NullIcon_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetIcon(item, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetIcon_Success_003
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetIcon with valid parameters.
 *           Verifies icon is set and can be retrieved correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetIcon_Success_003, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetIcon(item, "icon.png");
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    char buffer[64] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode getResult = OH_ArkUI_TextMenuItem_GetIcon(item, buffer, 64, &writeLen);
    EXPECT_EQ(getResult, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(buffer, "icon.png");
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetIcon_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetIcon with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetIcon_NullItem_001, TestSize.Level1)
{
    char buffer[32] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetIcon(nullptr, buffer, 32, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetIcon_NullIcon_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetIcon with item that has no icon set.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetIcon_NullIcon_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    char buffer[32] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetIcon(item, buffer, 32, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetLabelInfo_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetLabelInfo with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetLabelInfo_NullItem_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetLabelInfo(nullptr, "label");
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetLabelInfo_NullLabelInfo_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetLabelInfo with null labelInfo.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetLabelInfo_NullLabelInfo_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetLabelInfo(item, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetLabelInfo_Success_003
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetLabelInfo with valid parameters.
 *           Verifies labelInfo is set and can be retrieved correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetLabelInfo_Success_003, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetLabelInfo(item, "menu_label");
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    char buffer[64] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode getResult = OH_ArkUI_TextMenuItem_GetLabelInfo(item, buffer, 64, &writeLen);
    EXPECT_EQ(getResult, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(buffer, "menu_label");
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetLabelInfo_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetLabelInfo with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetLabelInfo_NullItem_001, TestSize.Level1)
{
    char buffer[32] = { 0 };
    int32_t writeLen = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetLabelInfo(nullptr, buffer, 32, &writeLen);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetId_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetId with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetId_NullItem_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetId(nullptr, 1);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_SetId_Success_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_SetId with valid parameters.
 *           Verifies id is set and can be retrieved correctly.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_SetId_Success_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_SetId(item, 42);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    int32_t id = 0;
    ArkUI_ErrorCode getResult = OH_ArkUI_TextMenuItem_GetId(item, &id);
    EXPECT_EQ(getResult, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(id, 42);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetId_NullItem_001
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetId with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetId_NullItem_001, TestSize.Level1)
{
    int32_t id = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetId(nullptr, &id);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItem_GetId_NullId_002
 * @tc.desc: Test OH_ArkUI_TextMenuItem_GetId with null id pointer.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItem_GetId_NullId_002, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = OH_ArkUI_TextMenuItem_Create();
    ASSERT_NE(item, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItem_GetId(item, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItem_Dispose(item);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_GetSize_NullArray_001
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_GetSize with null itemArray.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_GetSize_NullArray_001, TestSize.Level1)
{
    int32_t size = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_GetSize(nullptr, &size);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_GetSize_Success_002
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_GetSize with valid empty array.
 *           Verifies the size is 0 for a newly created array.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_GetSize_Success_002, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    int32_t size = -1;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_GetSize(array, &size);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(size, 0);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_GetItem_NullArray_001
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_GetItem with null itemArray.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_GetItem_NullArray_001, TestSize.Level1)
{
    ArkUI_TextMenuItem* item = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_GetItem(nullptr, 0, &item);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_GetItem_NullItem_002
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_GetItem with null item output pointer.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_GetItem_NullItem_002, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_GetItem(array, 0, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_GetItem_IndexOutOfRange_003
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_GetItem with out-of-range index.
 *           Verifies SET_ERROR_MESSAGE triggers and returns PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_GetItem_IndexOutOfRange_003, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_TextMenuItem srcItem;
    srcItem.content = "test";
    srcItem.isDelContent = false;
    srcItem.icon = nullptr;
    srcItem.isDelIcon = false;
    srcItem.labelInfo = nullptr;
    srcItem.isDelLabel = false;
    srcItem.id = 0;
    OH_ArkUI_TextMenuItemArray_Insert(array, &srcItem, 0);
    ArkUI_TextMenuItem* outItem = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_GetItem(array, 5, &outItem);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextMenuItemArray_Clear(array);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Insert_NullArray_001
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Insert with null itemArray.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Insert_NullArray_001, TestSize.Level1)
{
    ArkUI_TextMenuItem item;
    item.content = "test";
    item.isDelContent = false;
    item.icon = nullptr;
    item.isDelIcon = false;
    item.labelInfo = nullptr;
    item.isDelLabel = false;
    item.id = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Insert(nullptr, &item, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Insert_NullItem_002
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Insert with null item.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Insert_NullItem_002, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Insert(array, nullptr, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Insert_NullContent_003
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Insert with item having null content.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Insert_NullContent_003, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_TextMenuItem item;
    item.content = nullptr;
    item.isDelContent = false;
    item.icon = nullptr;
    item.isDelIcon = false;
    item.labelInfo = nullptr;
    item.isDelLabel = false;
    item.id = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Insert(array, &item, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Insert_IndexOutOfRange_004
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Insert with out-of-range index.
 *           Verifies SET_ERROR_MESSAGE triggers and returns PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Insert_IndexOutOfRange_004, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_TextMenuItem item;
    item.content = "test";
    item.isDelContent = false;
    item.icon = nullptr;
    item.isDelIcon = false;
    item.labelInfo = nullptr;
    item.isDelLabel = false;
    item.id = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Insert(array, &item, 5);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Insert_Success_005
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Insert with valid parameters.
 *           Verifies the item is inserted and array size increases.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Insert_Success_005, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_TextMenuItem item;
    item.content = "test";
    item.isDelContent = false;
    item.icon = nullptr;
    item.isDelIcon = false;
    item.labelInfo = nullptr;
    item.isDelLabel = false;
    item.id = 10;
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Insert(array, &item, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    int32_t size = 0;
    OH_ArkUI_TextMenuItemArray_GetSize(array, &size);
    EXPECT_EQ(size, 1);
    ArkUI_TextMenuItem* outItem = nullptr;
    OH_ArkUI_TextMenuItemArray_GetItem(array, 0, &outItem);
    ASSERT_NE(outItem, nullptr);
    EXPECT_EQ(outItem->id, 10);
    OH_ArkUI_TextMenuItemArray_Clear(array);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Erase_NullArray_001
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Erase with null itemArray.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Erase_NullArray_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Erase(nullptr, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Erase_IndexOutOfRange_002
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Erase with out-of-range index.
 *           Verifies SET_ERROR_MESSAGE triggers and returns PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Erase_IndexOutOfRange_002, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Erase(array, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Erase_Success_003
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Erase with valid index.
 *           Verifies the item is removed and array size decreases.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Erase_Success_003, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_TextMenuItem item;
    item.content = "test";
    item.isDelContent = false;
    item.icon = nullptr;
    item.isDelIcon = false;
    item.labelInfo = nullptr;
    item.isDelLabel = false;
    item.id = 1;
    OH_ArkUI_TextMenuItemArray_Insert(array, &item, 0);
    int32_t size = 0;
    OH_ArkUI_TextMenuItemArray_GetSize(array, &size);
    EXPECT_EQ(size, 1);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Erase(array, 0);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_TextMenuItemArray_GetSize(array, &size);
    EXPECT_EQ(size, 0);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Clear_NullArray_001
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Clear with null itemArray.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Clear_NullArray_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Clear(nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextMenuItemArray_Clear_Success_002
 * @tc.desc: Test OH_ArkUI_TextMenuItemArray_Clear with valid array containing items.
 *           Verifies all items are cleared and array is empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextMenuItemArray_Clear_Success_002, TestSize.Level1)
{
    ArkUI_TextMenuItemArray* array = new ArkUI_TextMenuItemArray();
    ASSERT_NE(array, nullptr);
    ArkUI_TextMenuItem item;
    item.content = "test";
    item.isDelContent = false;
    item.icon = nullptr;
    item.isDelIcon = false;
    item.labelInfo = nullptr;
    item.isDelLabel = false;
    item.id = 0;
    OH_ArkUI_TextMenuItemArray_Insert(array, &item, 0);
    OH_ArkUI_TextMenuItemArray_Insert(array, &item, 1);
    int32_t size = 0;
    OH_ArkUI_TextMenuItemArray_GetSize(array, &size);
    EXPECT_EQ(size, 2);
    ArkUI_ErrorCode result = OH_ArkUI_TextMenuItemArray_Clear(array);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_TextMenuItemArray_GetSize(array, &size);
    EXPECT_EQ(size, 0);
    delete array;
}

/**
 * @tc.name: TextNativeImplErrorTest_TextEditMenuOptions_RegisterOnCreateMenu_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextEditMenuOptions_RegisterOnCreateMenuCallback with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextEditMenuOptions_RegisterOnCreateMenu_NullOptions_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextEditMenuOptions_RegisterOnCreateMenuCallback(
        nullptr, nullptr, [](ArkUI_TextMenuItemArray* menuArr, void* userData) -> void {});
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextEditMenuOptions_RegisterOnPrepareMenu_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextEditMenuOptions_RegisterOnPrepareMenuCallback with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextEditMenuOptions_RegisterOnPrepareMenu_NullOptions_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextEditMenuOptions_RegisterOnPrepareMenuCallback(
        nullptr, nullptr, [](ArkUI_TextMenuItemArray* menuArr, void* userData) -> void {});
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextEditMenuOptions_RegisterOnMenuItemClick_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextEditMenuOptions_RegisterOnMenuItemClickCallback with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextEditMenuOptions_RegisterOnMenuItemClick_NullOptions_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextEditMenuOptions_RegisterOnMenuItemClickCallback(nullptr, nullptr,
        [](const ArkUI_TextMenuItem* item, int32_t start, int32_t end, void* userData) -> bool { return false; });
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_SetSpanType_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_SetSpanType with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_SetSpanType_NullOptions_001, TestSize.Level1)
{
    ArkUI_ErrorCode result =
        OH_ArkUI_TextSelectionMenuOptions_SetSpanType(nullptr, ArkUI_TextSpanType::ARKUI_TEXT_SPAN_TYPE_IMAGE);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetSpanType_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetSpanType with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetSpanType_NullOptions_001, TestSize.Level1)
{
    ArkUI_TextSpanType spanType = ArkUI_TextSpanType::ARKUI_TEXT_SPAN_TYPE_TEXT;
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetSpanType(nullptr, &spanType);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetSpanType_NullOutParam_002
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetSpanType with null output parameter.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetSpanType_NullOutParam_002, TestSize.Level1)
{
    ArkUI_TextSelectionMenuOptions* options = OH_ArkUI_TextSelectionMenuOptions_Create();
    ASSERT_NE(options, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetSpanType(options, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextSelectionMenuOptions_Dispose(options);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_SetSpanType_Success_003
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_SetSpanType and GetSpanType roundtrip.
 *           Verifies the span type is correctly set and retrieved.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_SetSpanType_Success_003, TestSize.Level1)
{
    ArkUI_TextSelectionMenuOptions* options = OH_ArkUI_TextSelectionMenuOptions_Create();
    ASSERT_NE(options, nullptr);
    ArkUI_ErrorCode setResult =
        OH_ArkUI_TextSelectionMenuOptions_SetSpanType(options, ArkUI_TextSpanType::ARKUI_TEXT_SPAN_TYPE_IMAGE);
    EXPECT_EQ(setResult, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    ArkUI_TextSpanType spanType = ArkUI_TextSpanType::ARKUI_TEXT_SPAN_TYPE_TEXT;
    ArkUI_ErrorCode getResult = OH_ArkUI_TextSelectionMenuOptions_GetSpanType(options, &spanType);
    EXPECT_EQ(getResult, ArkUI_ErrorCode::ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(spanType, ArkUI_TextSpanType::ARKUI_TEXT_SPAN_TYPE_IMAGE);
    OH_ArkUI_TextSelectionMenuOptions_Dispose(options);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_SetContentNode_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_SetContentNode with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_SetContentNode_NullOptions_001, TestSize.Level1)
{
    ArkUI_Node node;
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_SetContentNode(nullptr, &node);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_SetContentNode_NullNode_002
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_SetContentNode with null node.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_SetContentNode_NullNode_002, TestSize.Level1)
{
    ArkUI_TextSelectionMenuOptions* options = OH_ArkUI_TextSelectionMenuOptions_Create();
    ASSERT_NE(options, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_SetContentNode(options, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextSelectionMenuOptions_Dispose(options);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetContentNode_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetContentNode with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetContentNode_NullOptions_001, TestSize.Level1)
{
    ArkUI_NodeHandle node = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetContentNode(nullptr, &node);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetContentNode_NullOutParam_002
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetContentNode with null output parameter.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetContentNode_NullOutParam_002, TestSize.Level1)
{
    ArkUI_TextSelectionMenuOptions* options = OH_ArkUI_TextSelectionMenuOptions_Create();
    ASSERT_NE(options, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetContentNode(options, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextSelectionMenuOptions_Dispose(options);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_SetResponseType_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_SetResponseType with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_SetResponseType_NullOptions_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_SetResponseType(
        nullptr, ArkUI_TextResponseType::ARKUI_TEXT_RESPONSE_TYPE_RIGHT_CLICK);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetResponseType_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetResponseType with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetResponseType_NullOptions_001, TestSize.Level1)
{
    ArkUI_TextResponseType responseType = ArkUI_TextResponseType::ARKUI_TEXT_RESPONSE_TYPE_LONG_PRESS;
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetResponseType(nullptr, &responseType);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetResponseType_NullOutParam_002
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetResponseType with null output parameter.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetResponseType_NullOutParam_002, TestSize.Level1)
{
    ArkUI_TextSelectionMenuOptions* options = OH_ArkUI_TextSelectionMenuOptions_Create();
    ASSERT_NE(options, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetResponseType(options, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextSelectionMenuOptions_Dispose(options);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_SetHapticFeedbackMode_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_SetHapticFeedbackMode with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_SetHapticFeedbackMode_NullOptions_001, TestSize.Level1)
{
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_SetHapticFeedbackMode(
        nullptr, OH_ArkUI_HapticFeedbackMode::OH_ARKUI_HAPTIC_FEEDBACK_MODE_ENABLED);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetHapticFeedbackMode_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetHapticFeedbackMode with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetHapticFeedbackMode_NullOptions_001, TestSize.Level1)
{
    OH_ArkUI_HapticFeedbackMode mode = OH_ArkUI_HapticFeedbackMode::OH_ARKUI_HAPTIC_FEEDBACK_MODE_DISABLED;
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetHapticFeedbackMode(nullptr, &mode);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_GetHapticFeedbackMode_NullOutParam_002
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_GetHapticFeedbackMode with null output parameter.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_GetHapticFeedbackMode_NullOutParam_002, TestSize.Level1)
{
    ArkUI_TextSelectionMenuOptions* options = OH_ArkUI_TextSelectionMenuOptions_Create();
    ASSERT_NE(options, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_GetHapticFeedbackMode(options, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextSelectionMenuOptions_Dispose(options);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_RegisterOnMenuShow_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuShowCallback with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_RegisterOnMenuShow_NullOptions_001, TestSize.Level1)
{
    auto callback = [](int32_t start, int32_t end, void* userData) {};
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuShowCallback(nullptr, nullptr, callback);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextSelectionMenuOptions_RegisterOnMenuHide_NullOptions_001
 * @tc.desc: Test OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuHideCallback with null options.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextSelectionMenuOptions_RegisterOnMenuHide_NullOptions_001, TestSize.Level1)
{
    auto callback = [](int32_t start, int32_t end, void* userData) {};
    ArkUI_ErrorCode result = OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuHideCallback(nullptr, nullptr, callback);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextController_SetStyledString_NullController_001
 * @tc.desc: Test OH_ArkUI_TextController_SetStyledString with null controller.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextController_SetStyledString_NullController_001, TestSize.Level1)
{
    ArkUI_StyledString_Descriptor descriptor;
    ArkUI_ErrorCode result = OH_ArkUI_TextController_SetStyledString(nullptr, &descriptor);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextController_SetStyledString_NullDescriptor_002
 * @tc.desc: Test OH_ArkUI_TextController_SetStyledString with null descriptor.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextController_SetStyledString_NullDescriptor_002, TestSize.Level1)
{
    OH_ArkUI_TextController* controller = OH_ArkUI_TextController_Create();
    ASSERT_NE(controller, nullptr);
    ArkUI_ErrorCode result = OH_ArkUI_TextController_SetStyledString(controller, nullptr);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextController_Destroy(controller);
}

/**
 * @tc.name: TextNativeImplErrorTest_TextController_SetStyledString_NullNode_003
 * @tc.desc: Test OH_ArkUI_TextController_SetStyledString with controller having null node.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(TextNativeImplErrorTest, TextController_SetStyledString_NullNode_003, TestSize.Level1)
{
    OH_ArkUI_TextController* controller = OH_ArkUI_TextController_Create();
    ASSERT_NE(controller, nullptr);
    ArkUI_StyledString_Descriptor descriptor;
    ArkUI_ErrorCode result = OH_ArkUI_TextController_SetStyledString(controller, &descriptor);
    EXPECT_EQ(result, ArkUI_ErrorCode::ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_TextController_Destroy(controller);
}
