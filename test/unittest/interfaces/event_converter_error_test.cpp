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
#include "error_code.h"
#include "node/event_converter.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NodeModel;

class EventConverterErrorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        InitialFullImpl();
    }
    static void TearDownTestCase() {}
};

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetNumberValue_NullEvent_001
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNumberValue with null event parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetNumberValue_NullEvent_001, TestSize.Level1)
{
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_GetNumberValue(nullptr, 0, &value);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetNumberValue_InvalidCategory_002
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNumberValue with invalid event category.
 *           Verifies SET_ERROR_MESSAGE triggers for category mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetNumberValue_InvalidCategory_002, TestSize.Level1)
{
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_COMPONENT_EVENT);
    event.origin = nullptr;
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_GetNumberValue(&event, 0, &value);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetNumberValue_NullOriginEvent_003
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNumberValue with null originNodeEvent.
 *           Verifies SET_ERROR_MESSAGE triggers when event->origin is null.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetNumberValue_NullOriginEvent_003, TestSize.Level1)
{
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = nullptr;
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_GetNumberValue(&event, 0, &value);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetNumberValue_IndexOutOfRange_004
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNumberValue with index out of range.
 *           Verifies SET_ERROR_MESSAGE triggers for invalid index.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetNumberValue_IndexOutOfRange_004, TestSize.Level1)
{
    ArkUINodeEvent originEvent;
    originEvent.mixedEvent.numberDataLength = 2;
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = &originEvent;
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_GetNumberValue(&event, 5, &value);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetNumberValue_NegativeIndex_005
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNumberValue with negative index.
 *           Verifies SET_ERROR_MESSAGE triggers for negative index.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetNumberValue_NegativeIndex_005, TestSize.Level1)
{
    ArkUINodeEvent originEvent;
    originEvent.mixedEvent.numberDataLength = 2;
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = &originEvent;
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_GetNumberValue(&event, -1, &value);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetStringValue_NullEvent_001
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetStringValue with null event parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetStringValue_NullEvent_001, TestSize.Level1)
{
    char* string = nullptr;
    int32_t stringSize = 0;
    int32_t result = OH_ArkUI_NodeEvent_GetStringValue(nullptr, 0, &string, &stringSize);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetStringValue_InvalidCategory_002
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetStringValue with invalid event category.
 *           Verifies SET_ERROR_MESSAGE triggers for category mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetStringValue_InvalidCategory_002, TestSize.Level1)
{
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_COMPONENT_EVENT);
    event.origin = nullptr;
    char* string = nullptr;
    int32_t stringSize = 0;
    int32_t result = OH_ArkUI_NodeEvent_GetStringValue(&event, 0, &string, &stringSize);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetStringValue_NullOriginEvent_003
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetStringValue with null originNodeEvent.
 *           Verifies SET_ERROR_MESSAGE triggers when event->origin is null.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetStringValue_NullOriginEvent_003, TestSize.Level1)
{
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = nullptr;
    char* string = nullptr;
    int32_t stringSize = 0;
    int32_t result = OH_ArkUI_NodeEvent_GetStringValue(&event, 0, &string, &stringSize);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetStringValue_IndexOutOfRange_004
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetStringValue with index out of range.
 *           Verifies SET_ERROR_MESSAGE triggers for invalid index.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetStringValue_IndexOutOfRange_004, TestSize.Level1)
{
    ArkUINodeEvent originEvent;
    originEvent.mixedEvent.stringPtrDataLength = 2;
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = &originEvent;
    char* string = nullptr;
    int32_t stringSize = 0;
    int32_t result = OH_ArkUI_NodeEvent_GetStringValue(&event, 5, &string, &stringSize);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetStringValue_NullStringData_005
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetStringValue with null string data at index.
 *           Verifies SET_ERROR_MESSAGE triggers when string data is null.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetStringValue_NullStringData_005, TestSize.Level1)
{
    ArkUINodeEvent originEvent;
    originEvent.mixedEvent.stringPtrDataLength = 2;
    originEvent.mixedEvent.stringPtrData[0] = 0;
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = &originEvent;
    char* string = nullptr;
    int32_t stringSize = 10;
    int32_t result = OH_ArkUI_NodeEvent_GetStringValue(&event, 0, &string, &stringSize);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_GetStringValue_InvalidStringSize_006
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetStringValue with invalid string size (<= 0).
 *           Verifies SET_ERROR_MESSAGE triggers for invalid buffer size.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_GetStringValue_InvalidStringSize_006, TestSize.Level1)
{
    const char* testString = "test";
    ArkUINodeEvent originEvent;
    originEvent.mixedEvent.stringPtrDataLength = 2;
    originEvent.mixedEvent.stringPtrData[0] = reinterpret_cast<ArkUI_Int64>(const_cast<char*>(testString));
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.origin = &originEvent;
    char* string = nullptr;
    int32_t stringSize = 0;
    int32_t result = OH_ArkUI_NodeEvent_GetStringValue(&event, 0, &string, &stringSize);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_SetReturnNumberValue_NullEvent_001
 * @tc.desc: Test OH_ArkUI_NodeEvent_SetReturnNumberValue with null event parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_SetReturnNumberValue_NullEvent_001, TestSize.Level1)
{
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_SetReturnNumberValue(nullptr, &value, 1);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_SetReturnNumberValue_InvalidCategory_002
 * @tc.desc: Test OH_ArkUI_NodeEvent_SetReturnNumberValue with invalid event category.
 *           Verifies SET_ERROR_MESSAGE triggers for category mismatch.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_SetReturnNumberValue_InvalidCategory_002, TestSize.Level1)
{
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_INPUT_EVENT);
    event.origin = nullptr;
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_SetReturnNumberValue(&event, &value, 1);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}

/**
 * @tc.name: EventConverterErrorTest_NodeEvent_SetReturnNumberValue_NullOriginEvent_003
 * @tc.desc: Test OH_ArkUI_NodeEvent_SetReturnNumberValue with null originNodeEvent.
 *           Verifies SET_ERROR_MESSAGE triggers when event->origin is null.
 * @tc.type: FUNC
 */
HWTEST_F(EventConverterErrorTest, NodeEvent_SetReturnNumberValue_NullOriginEvent_003, TestSize.Level1)
{
    ArkUI_NodeEvent event;
    event.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);
    event.kind = 0;
    event.origin = nullptr;
    ArkUI_NumberValue value;
    int32_t result = OH_ArkUI_NodeEvent_SetReturnNumberValue(&event, &value, 1);
    EXPECT_EQ(result, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_EVENT_PARAM_INVALID);
}
