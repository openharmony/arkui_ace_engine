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

#include "interfaces/native/node/event_converter.h"
#include "test/unittest/interfaces/ui_input_event_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
/**
 * @tc.name: OH_ArkUI_NodeEvent_GetTouchTestInfo001
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetTouchTestInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_NodeEvent_GetTouchTestInfo001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create nodeEvent.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent originEvent;
    ArkUITouchTestInfo touchTestInfo;
    originEvent.touchTestInfo = touchTestInfo;
    nodeEvent.origin = &originEvent;
    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is not nullptr.
     */
    auto result = OH_ArkUI_NodeEvent_GetTouchTestInfo(&nodeEvent);
    EXPECT_NE(result, nullptr);

    /**
     * @tc.steps: step3. call functions when nodeEvent is nullptr.
     * @tc.expected: result is nullptr.
     */
    result = OH_ArkUI_NodeEvent_GetTouchTestInfo(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: OH_ArkUI_NodeEvent_GetTouchTestInfo002
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetTouchTestInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_NodeEvent_GetTouchTestInfo002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create nodeEvent.
     */
    ArkUI_NodeEvent nodeEvent;
    ArkUINodeEvent originEvent;
    nodeEvent.origin = &originEvent;
    nodeEvent.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_MIXED_EVENT);

    /**
     * @tc.steps: step2. call functions when category is error.
     * @tc.expected: result is nullptr.
     */
    auto result = OH_ArkUI_NodeEvent_GetTouchTestInfo(&nodeEvent);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: OH_ArkUI_NodeEvent_GetTouchTestInfo003
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetTouchTestInfo
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_NodeEvent_GetTouchTestInfo003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create nodeEvent.
     */
    ArkUI_NodeEvent nodeEvent;
    nodeEvent.category = static_cast<int32_t>(NODE_EVENT_CATEGORY_INPUT_EVENT);
    nodeEvent.origin = nullptr;

    /**
     * @tc.steps: step2. call functions when origin is nullptr.
     * @tc.expected: result is nullptr.
     */
    auto result = OH_ArkUI_NodeEvent_GetTouchTestInfo(&nodeEvent);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_GetTouchTestInfoList001
 * @tc.desc: OH_ArkUI_TouchTestInfo_GetTouchTestInfoList
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_GetTouchTestInfoList001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    const int32_t ITEM_COUNT = 2;
    ArkUITouchTestInfoItemHandle itemHandles[ITEM_COUNT];
    ArkUITouchTestInfoItem item1 = { 10.0f, 20.0f, 100.0f, 200.0f, 5.0f, 5.0f, { 0, 0, 100, 200 }, "item1" };
    ArkUITouchTestInfoItem item2 = { 30.0f, 40.0f, 300.0f, 400.0f, 5.0f, 5.0f, { 0, 0, 100, 200 }, "item2" };
    itemHandles[0] = &item1;
    itemHandles[1] = &item2;
    originInfo.array = itemHandles;
    originInfo.size = ITEM_COUNT;
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is not nullptr.
     */
    ArkUI_TouchTestInfoItemArray outArray = nullptr;
    int32_t outSize = 0;
    auto ret = OH_ArkUI_TouchTestInfo_GetTouchTestInfoList(info, &outArray, &outSize);

    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(outSize, ITEM_COUNT);
    EXPECT_NE(outArray, nullptr);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_GetTouchTestInfoList002
 * @tc.desc: OH_ArkUI_TouchTestInfo_GetTouchTestInfoList
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_GetTouchTestInfoList002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);
    ArkUI_TouchTestInfoItemArray array = nullptr;
    int32_t size = 0;

    /**
     * @tc.steps: step2. call functions when info is nullptr.
     * @tc.expected: result is nullptr.
     */
    auto ret1 = OH_ArkUI_TouchTestInfo_GetTouchTestInfoList(nullptr, &array, &size);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3. call functions when array is nullptr.
     * @tc.expected: result is nullptr.
     */
    auto ret2 = OH_ArkUI_TouchTestInfo_GetTouchTestInfoList(info, nullptr, &size);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step4. call functions when size is nullptr.
     * @tc.expected: result is nullptr.
     */
    auto ret3 = OH_ArkUI_TouchTestInfo_GetTouchTestInfoList(info, &array, nullptr);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetX001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetX001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.nodeX = 100.5f;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    float x = OH_ArkUI_TouchTestInfoItem_GetX(info);
    EXPECT_EQ(x, 100.5f);

    /**
     * @tc.steps: step3. call functions when info is nullptr.
     * @tc.expected: result is 0.0f.
     */
    EXPECT_EQ(OH_ArkUI_TouchTestInfoItem_GetX(nullptr), 0.0f);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetY001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetY001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.nodeY = 200.8f;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    float y = OH_ArkUI_TouchTestInfoItem_GetY(info);
    EXPECT_EQ(y, 200.8f);

    /**
     * @tc.steps: step3. call functions when info is nullptr.
     * @tc.expected: result is 0.0f.
     */
    EXPECT_EQ(OH_ArkUI_TouchTestInfoItem_GetY(nullptr), 0.0f);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetWindowX001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetWindowX
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetWindowX001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.windowX = 300.2f;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    float windowX = OH_ArkUI_TouchTestInfoItem_GetWindowX(info);
    EXPECT_EQ(windowX, 300.2f);

    /**
     * @tc.steps: step3. call functions when info is nullptr.
     * @tc.expected: result is 0.0f.
     */
    EXPECT_EQ(OH_ArkUI_TouchTestInfoItem_GetWindowX(nullptr), 0.0f);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetWindowY001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetWindowY
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetWindowY001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.windowY = 400.6f;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    float windowY = OH_ArkUI_TouchTestInfoItem_GetWindowY(info);
    EXPECT_EQ(windowY, 400.6f);

    /**
     * @tc.steps: step3. call functions when info is nullptr.
     * @tc.expected: result is 0.0f.
     */
    EXPECT_EQ(OH_ArkUI_TouchTestInfoItem_GetWindowY(nullptr), 0.0f);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.parentNodeX = 50.3f;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    float parentX = OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent(info);
    EXPECT_EQ(parentX, 50.3f);

    /**
     * @tc.steps: step3. call functions when info is nullptr.
     * @tc.expected: result is 0.0f.
     */
    EXPECT_EQ(OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent(nullptr), 0.0f);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.parentNodeY = 60.9f;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    float parentY = OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent(info);
    EXPECT_EQ(parentY, 60.9f);

    /**
     * @tc.steps: step3. call functions when info is nullptr.
     * @tc.expected: result is 0.0f.
     */
    EXPECT_EQ(OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent(nullptr), 0.0f);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetChildRect001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetChildRect
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetChildRect001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.rect = { 10, 20, 300, 400 };
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    ArkUI_Rect rect;
    auto ret = OH_ArkUI_TouchTestInfoItem_GetChildRect(info, &rect);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(rect.x, 10);
    EXPECT_EQ(rect.y, 20);
    EXPECT_EQ(rect.width, 300);
    EXPECT_EQ(rect.height, 400);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetChildRect002
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetChildRect
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetChildRect002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);
    ArkUI_Rect rect;

    /**
     * @tc.steps: step2. call functions when info is nullptr.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret1 = OH_ArkUI_TouchTestInfoItem_GetChildRect(nullptr, &rect);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3. call functions when childRect is nullptr.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret2 = OH_ArkUI_TouchTestInfoItem_GetChildRect(info, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetChildId001
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetChildId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetChildId001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.id = "test_node_123";
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);
    char buffer[20] = { 0 };

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    auto ret = OH_ArkUI_TouchTestInfoItem_GetChildId(info, buffer, 20);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(buffer, "test_node_123");
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetChildId002
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetChildId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetChildId002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.id = "test";
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);
    char buffer[20] = { 0 };

    /**
     * @tc.steps: step2. call functions when info is nullptr.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret1 = OH_ArkUI_TouchTestInfoItem_GetChildId(nullptr, buffer, 20);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3. call functions when buffer is nullptr.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret2 = OH_ArkUI_TouchTestInfoItem_GetChildId(info, nullptr, 20);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step4. call functions when bufferSize <= 0.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret3 = OH_ArkUI_TouchTestInfoItem_GetChildId(info, buffer, 0);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfoItem_GetChildId003
 * @tc.desc: test OH_ArkUI_TouchTestInfoItem_GetChildId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfoItem_GetChildId003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfoItem originItem;
    originItem.id = "long_node_id_123456";
    const ArkUI_TouchTestInfoItem* info = reinterpret_cast<const ArkUI_TouchTestInfoItem*>(&originItem);
    char buffer[10] = { 0 };

    /**
     * @tc.steps: step2. call functions when bufferSize < id.lenght.
     * @tc.expected: result is ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH.
     */
    auto ret = OH_ArkUI_TouchTestInfoItem_GetChildId(info, buffer, 10);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_SetTouchResultStrategy001
 * @tc.desc: test OH_ArkUI_TouchTestInfo_SetTouchResultStrategy
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_SetTouchResultStrategy001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);

    /**
     * @tc.steps: step2. call functions set TOUCH_TEST_STRATEGY_DEFAULT.
     * @tc.expected: result is rigth.
     */
    auto ret1 = OH_ArkUI_TouchTestInfo_SetTouchResultStrategy(info, static_cast<ArkUI_TouchTestStrategy>(0));
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(originInfo.strategy, ArkUITouchTestStrategy::TOUCH_TEST_STRATEGY_DEFAULT);

    /**
     * @tc.steps: step3. call functions set TOUCH_TEST_STRATEGY_FORWARD_COMPETITION.
     * @tc.expected: result is rigth.
     */
    auto ret2 = OH_ArkUI_TouchTestInfo_SetTouchResultStrategy(info, static_cast<ArkUI_TouchTestStrategy>(1));
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(originInfo.strategy, ArkUITouchTestStrategy::TOUCH_TEST_STRATEGY_FORWARD_COMPETITION);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_SetTouchResultStrategy002
 * @tc.desc: test OH_ArkUI_TouchTestInfo_SetTouchResultStrategy
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_SetTouchResultStrategy002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);

    /**
     * @tc.steps: step2. call functions when info is nullptr.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret1 = OH_ArkUI_TouchTestInfo_SetTouchResultStrategy(nullptr, static_cast<ArkUI_TouchTestStrategy>(0));
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3. call functions when Strategy is invalid.
     * @tc.expected: result is ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret2 = OH_ArkUI_TouchTestInfo_SetTouchResultStrategy(info, static_cast<ArkUI_TouchTestStrategy>(100));
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(originInfo.strategy, TOUCH_TEST_STRATEGY_DEFAULT);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_SetTouchResultId001
 * @tc.desc: test OH_ArkUI_TouchTestInfo_SetTouchResultId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_SetTouchResultId001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    originInfo.resultId = nullptr;
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);

    /**
     * @tc.steps: step2. call functions.
     * @tc.expected: result is right.
     */
    const char* testId = "result_node_456";
    auto ret = OH_ArkUI_TouchTestInfo_SetTouchResultId(info, testId);

    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(originInfo.resultId, testId);

    /**
     * @tc.steps: step3. clean enviroment.
     */
    if (originInfo.resultId) {
        delete[] originInfo.resultId;
        originInfo.resultId = nullptr;
    }
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_SetTouchResultId002
 * @tc.desc: test OH_ArkUI_TouchTestInfo_SetTouchResultId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_SetTouchResultId002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);

    /**
     * @tc.steps: step2. call functions when info is nullptr.
     * @tc.expected: Return ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret1 = OH_ArkUI_TouchTestInfo_SetTouchResultId(nullptr, "id1");
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step3. call functions when id is nullptr.
     * @tc.expected: Return ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret2 = OH_ArkUI_TouchTestInfo_SetTouchResultId(info, nullptr);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: OH_ArkUI_TouchTestInfo_SetTouchResultId003
 * @tc.desc: test OH_ArkUI_TouchTestInfo_SetTouchResultId
 * @tc.type: FUNC
 */
HWTEST_F(UIInputEventTest, OH_ArkUI_TouchTestInfo_SetTouchResultId003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create info.
     */
    ArkUITouchTestInfo originInfo;
    originInfo.resultId = new char[6];
    strcpy(originInfo.resultId, "old_id");
    ArkUI_TouchTestInfo* info = reinterpret_cast<ArkUI_TouchTestInfo*>(&originInfo);

    /**
     * @tc.steps: step2. call functions when new_id.lenght > old_id.lenght.
     * @tc.expected: Return ARKUI_ERROR_CODE_NO_ERROR.
     */
    const char* newId = "new_id_789";
    auto ret = OH_ArkUI_TouchTestInfo_SetTouchResultId(info, newId);

    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(originInfo.resultId, newId);

    /**
     * @tc.steps: step3. clean enviroment.
     */
    if (originInfo.resultId) {
        delete[] originInfo.resultId;
        originInfo.resultId = nullptr;
    }
}
} // namespace OHOS::Ace