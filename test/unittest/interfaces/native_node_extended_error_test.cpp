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

#include "drawing_text_typography.h"
#include "gtest/gtest.h"
#include "native_styled_string.h"
#include "node_extened.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NodeModel;

class NativeNodeExtendedErrorTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        InitialFullImpl();
    }
    static void TearDownTestCase() {}
};

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanMeasureInfo_GetFontSize_NullInfo_001
 * @tc.desc: Test OH_ArkUI_CustomSpanMeasureInfo_GetFontSize with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns 0.0f.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanMeasureInfo_GetFontSize_NullInfo_001, TestSize.Level1)
{
    float result = OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanMeasureInfo_GetFontSize_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanMeasureInfo_GetFontSize with valid info.
 *           Verifies the getter returns the correct fontSize value.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanMeasureInfo_GetFontSize_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanMeasureInfo* info = OH_ArkUI_CustomSpanMeasureInfo_Create();
    ASSERT_NE(info, nullptr);
    info->fontSize = 16.0f;
    float result = OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(info);
    EXPECT_FLOAT_EQ(result, 16.0f);
    OH_ArkUI_CustomSpanMeasureInfo_Dispose(info);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanMetrics_SetWidth_NullMetrics_001
 * @tc.desc: Test OH_ArkUI_CustomSpanMetrics_SetWidth with null metrics parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanMetrics_SetWidth_NullMetrics_001, TestSize.Level1)
{
    int32_t result = OH_ArkUI_CustomSpanMetrics_SetWidth(nullptr, 100.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanMetrics_SetWidth_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanMetrics_SetWidth with valid metrics.
 *           Verifies the setter stores the width value correctly.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanMetrics_SetWidth_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanMetrics* metrics = OH_ArkUI_CustomSpanMetrics_Create();
    ASSERT_NE(metrics, nullptr);
    int32_t result = OH_ArkUI_CustomSpanMetrics_SetWidth(metrics, 200.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(metrics->width, 200.0f);
    OH_ArkUI_CustomSpanMetrics_Dispose(metrics);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanMetrics_SetHeight_NullMetrics_001
 * @tc.desc: Test OH_ArkUI_CustomSpanMetrics_SetHeight with null metrics parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanMetrics_SetHeight_NullMetrics_001, TestSize.Level1)
{
    int32_t result = OH_ArkUI_CustomSpanMetrics_SetHeight(nullptr, 50.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanMetrics_SetHeight_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanMetrics_SetHeight with valid metrics.
 *           Verifies the setter stores the height value correctly.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanMetrics_SetHeight_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanMetrics* metrics = OH_ArkUI_CustomSpanMetrics_Create();
    ASSERT_NE(metrics, nullptr);
    int32_t result = OH_ArkUI_CustomSpanMetrics_SetHeight(metrics, 80.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(metrics->height, 80.0f);
    OH_ArkUI_CustomSpanMetrics_Dispose(metrics);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetXOffset_NullInfo_001
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetXOffset with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns 0.0f.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetXOffset_NullInfo_001, TestSize.Level1)
{
    float result = OH_ArkUI_CustomSpanDrawInfo_GetXOffset(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetXOffset_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetXOffset with valid info.
 *           Verifies the getter returns the correct x offset value.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetXOffset_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanDrawInfo* info = OH_ArkUI_CustomSpanDrawInfo_Create();
    ASSERT_NE(info, nullptr);
    info->optionsX = 15.5f;
    float result = OH_ArkUI_CustomSpanDrawInfo_GetXOffset(info);
    EXPECT_FLOAT_EQ(result, 15.5f);
    OH_ArkUI_CustomSpanDrawInfo_Dispose(info);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetLineTop_NullInfo_001
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetLineTop with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns 0.0f.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetLineTop_NullInfo_001, TestSize.Level1)
{
    float result = OH_ArkUI_CustomSpanDrawInfo_GetLineTop(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetLineTop_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetLineTop with valid info.
 *           Verifies the getter returns the correct line top value.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetLineTop_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanDrawInfo* info = OH_ArkUI_CustomSpanDrawInfo_Create();
    ASSERT_NE(info, nullptr);
    info->optionsLineTop = 5.0f;
    float result = OH_ArkUI_CustomSpanDrawInfo_GetLineTop(info);
    EXPECT_FLOAT_EQ(result, 5.0f);
    OH_ArkUI_CustomSpanDrawInfo_Dispose(info);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetLineBottom_NullInfo_001
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetLineBottom with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns 0.0f.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetLineBottom_NullInfo_001, TestSize.Level1)
{
    float result = OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetLineBottom_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetLineBottom with valid info.
 *           Verifies the getter returns the correct line bottom value.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetLineBottom_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanDrawInfo* info = OH_ArkUI_CustomSpanDrawInfo_Create();
    ASSERT_NE(info, nullptr);
    info->optionsLineBottom = 25.0f;
    float result = OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(info);
    EXPECT_FLOAT_EQ(result, 25.0f);
    OH_ArkUI_CustomSpanDrawInfo_Dispose(info);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetBaseline_NullInfo_001
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetBaseline with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns 0.0f.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetBaseline_NullInfo_001, TestSize.Level1)
{
    float result = OH_ArkUI_CustomSpanDrawInfo_GetBaseline(nullptr);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_CustomSpanDrawInfo_GetBaseline_Success_002
 * @tc.desc: Test OH_ArkUI_CustomSpanDrawInfo_GetBaseline with valid info.
 *           Verifies the getter returns the correct baseline value.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, CustomSpanDrawInfo_GetBaseline_Success_002, TestSize.Level1)
{
    ArkUI_CustomSpanDrawInfo* info = OH_ArkUI_CustomSpanDrawInfo_Create();
    ASSERT_NE(info, nullptr);
    info->optionsBaseLine = 18.5f;
    float result = OH_ArkUI_CustomSpanDrawInfo_GetBaseline(info);
    EXPECT_FLOAT_EQ(result, 18.5f);
    OH_ArkUI_CustomSpanDrawInfo_Dispose(info);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetLineCount_NullManager_001
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetLineCount with null layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetLineCount_NullManager_001, TestSize.Level1)
{
    int32_t lineCount = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetLineCount(nullptr, &lineCount);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetLineCount_NullNode_002
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetLineCount with null node in layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetLineCount_NullNode_002, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    int32_t lineCount = 0;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetLineCount(layoutManager, &lineCount);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetGlyphPositionAtCoordinate_NullManager_001
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate with null layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetGlyphPositionAtCoordinate_NullManager_001, TestSize.Level1)
{
    OH_Drawing_PositionAndAffinity* outPos = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate(nullptr, 0.0, 0.0, &outPos);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetGlyphPositionAtCoordinate_NullNode_002
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate with null node.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetGlyphPositionAtCoordinate_NullNode_002, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    OH_Drawing_PositionAndAffinity* outPos = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate(layoutManager, 0.0, 0.0, &outPos);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetLineMetrics_NullManager_001
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetLineMetrics with null layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetLineMetrics_NullManager_001, TestSize.Level1)
{
    OH_Drawing_LineMetrics outMetrics;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetLineMetrics(nullptr, 0, &outMetrics);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetLineMetrics_NullOutMetrics_002
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetLineMetrics with null outMetrics.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetLineMetrics_NullOutMetrics_002, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetLineMetrics(layoutManager, 0, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetLineMetrics_NullNode_003
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetLineMetrics with null node in layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetLineMetrics_NullNode_003, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    OH_Drawing_LineMetrics outMetrics;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetLineMetrics(layoutManager, 0, &outMetrics);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetCharacterPositionAtCoordinate_NullManager_001
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate with null layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(
    NativeNodeExtendedErrorTest, TextLayoutManager_GetCharacterPositionAtCoordinate_NullManager_001, TestSize.Level1)
{
    OH_Drawing_PositionAndAffinity* outPos = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate(nullptr, 0.0, 0.0, &outPos);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetCharacterPositionAtCoordinate_NullNode_002
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate with null node.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetCharacterPositionAtCoordinate_NullNode_002, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    OH_Drawing_PositionAndAffinity* outPos = nullptr;
    ArkUI_ErrorCode result =
        OH_ArkUI_TextLayoutManager_GetCharacterPositionAtCoordinate(layoutManager, 0.0, 0.0, &outPos);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetGlyphRangeForCharacterRange_NullManager_001
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRange with null layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetGlyphRangeForCharacterRange_NullManager_001, TestSize.Level1)
{
    OH_Drawing_Range* outGlyphRange = nullptr;
    OH_Drawing_Range* outActualCharRange = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRange(
        nullptr, nullptr, &outGlyphRange, &outActualCharRange);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetGlyphRangeForCharacterRange_NullNode_002
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRange with null node.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetGlyphRangeForCharacterRange_NullNode_002, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    OH_Drawing_Range* outGlyphRange = nullptr;
    OH_Drawing_Range* outActualCharRange = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetGlyphRangeForCharacterRange(
        layoutManager, nullptr, &outGlyphRange, &outActualCharRange);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetCharacterRangeForGlyphRange_NullManager_001
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRange with null layoutManager.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetCharacterRangeForGlyphRange_NullManager_001, TestSize.Level1)
{
    OH_Drawing_Range* outCharRange = nullptr;
    OH_Drawing_Range* outActualGlyphRange = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRange(
        nullptr, nullptr, &outCharRange, &outActualGlyphRange);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_TextLayoutManager_GetCharacterRangeForGlyphRange_NullNode_002
 * @tc.desc: Test OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRange with null node.
 *           Verifies CHECK_NULL_RETURN_WITH_MESSAGE triggers error return.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, TextLayoutManager_GetCharacterRangeForGlyphRange_NullNode_002, TestSize.Level1)
{
    ArkUI_TextLayoutManager* layoutManager = new ArkUI_TextLayoutManager();
    ASSERT_NE(layoutManager, nullptr);
    layoutManager->node = nullptr;
    OH_Drawing_Range* outCharRange = nullptr;
    OH_Drawing_Range* outActualGlyphRange = nullptr;
    ArkUI_ErrorCode result = OH_ArkUI_TextLayoutManager_GetCharacterRangeForGlyphRange(
        layoutManager, nullptr, &outCharRange, &outActualGlyphRange);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
    delete layoutManager;
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_GetCustomSpanMeasureInfo_NullEvent_001
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo with null event parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_GetCustomSpanMeasureInfo_NullEvent_001, TestSize.Level1)
{
    ArkUI_CustomSpanMeasureInfo info;
    int32_t result = OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(nullptr, &info);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_GetCustomSpanMeasureInfo_NullInfo_002
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_GetCustomSpanMeasureInfo_NullInfo_002, TestSize.Level1)
{
    ArkUI_NodeCustomEvent event;
    int32_t result = OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(&event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_GetCustomSpanMeasureInfo_NullInnerEvent_003
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo with null event->event.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_GetCustomSpanMeasureInfo_NullInnerEvent_003, TestSize.Level1)
{
    ArkUI_NodeCustomEvent event;
    event.event = nullptr;
    ArkUI_CustomSpanMeasureInfo info;
    int32_t result = OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(&event, &info);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_SetCustomSpanMetrics_NullEvent_001
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics with null event parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_SetCustomSpanMetrics_NullEvent_001, TestSize.Level1)
{
    ArkUI_CustomSpanMetrics metrics;
    int32_t result = OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(nullptr, &metrics);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_SetCustomSpanMetrics_NullMetrics_002
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics with null metrics parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_SetCustomSpanMetrics_NullMetrics_002, TestSize.Level1)
{
    ArkUI_NodeCustomEvent event;
    int32_t result = OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(&event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_SetCustomSpanMetrics_NullInnerEvent_003
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics with null event->event.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_SetCustomSpanMetrics_NullInnerEvent_003, TestSize.Level1)
{
    ArkUI_NodeCustomEvent event;
    event.event = nullptr;
    ArkUI_CustomSpanMetrics metrics;
    int32_t result = OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(&event, &metrics);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_GetCustomSpanDrawInfo_NullEvent_001
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo with null event parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_GetCustomSpanDrawInfo_NullEvent_001, TestSize.Level1)
{
    ArkUI_CustomSpanDrawInfo info;
    int32_t result = OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo(nullptr, &info);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_GetCustomSpanDrawInfo_NullInfo_002
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo with null info parameter.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_GetCustomSpanDrawInfo_NullInfo_002, TestSize.Level1)
{
    ArkUI_NodeCustomEvent event;
    int32_t result = OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo(&event, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeExtendedErrorTest_NodeCustomEvent_GetCustomSpanDrawInfo_NullInnerEvent_003
 * @tc.desc: Test OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo with null event->event.
 *           Verifies SET_ERROR_MESSAGE triggers and returns ARKUI_ERROR_CODE_PARAM_INVALID.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeExtendedErrorTest, NodeCustomEvent_GetCustomSpanDrawInfo_NullInnerEvent_003, TestSize.Level1)
{
    ArkUI_NodeCustomEvent event;
    event.event = nullptr;
    ArkUI_CustomSpanDrawInfo info;
    int32_t result = OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo(&event, &info);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);
}

