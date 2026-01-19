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

#include <cstddef>
#include <cstdint>
#include "gtest/gtest.h"
#define private public
#define protected public
#include "native_interface.h"
#include "native_node.h"
#include "native_render.h"
#include "native_type.h"
#include "core/interfaces/arkoala/arkoala_api.h"
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

namespace {
constexpr int NUM_4 = 4;
constexpr int NUM_16 = 16;
}

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
class NodeVisualEffectTest : public testing::Test {
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
 * @tc.name: Matrix4ScaleOptions001
 * @tc.desc: Test getting and setting attribute of scaleX, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions001, TestSize.Level1)
{
    ArkUI_Matrix4ScaleOptions* options = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetX(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetX(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetX(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetX(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetX(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4ScaleOptions002
 * @tc.desc: Test getting and setting attribute of scaleY, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions002, TestSize.Level1)
{
    ArkUI_Matrix4ScaleOptions* options = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetY(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetY(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetY(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetY(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetY(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4ScaleOptions003
 * @tc.desc: Test getting and setting attribute of scaleZ, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions003, TestSize.Level1)
{
    ArkUI_Matrix4ScaleOptions* options = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetZ(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetZ(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetZ(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetZ(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetZ(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4ScaleOptions004
 * @tc.desc: Test getting and setting attribute of centerX, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions004, TestSize.Level1)
{
    ArkUI_Matrix4ScaleOptions* options = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetCenterX(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetCenterX(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetCenterX(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetCenterX(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetCenterX(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4ScaleOptions005
 * @tc.desc: Test getting and setting attribute of centerY, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions005, TestSize.Level1)
{
    ArkUI_Matrix4ScaleOptions* options = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetCenterY(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetCenterY(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetCenterY(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetCenterY(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetCenterY(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4RotationOptions001
 * @tc.desc: Test getting and setting attribute of X, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions001, TestSize.Level1)
{
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetX(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetX(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetX(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetX(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetX(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4RotationOptions002
 * @tc.desc: Test getting and setting attribute of Y, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions002, TestSize.Level1)
{
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetY(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetY(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetY(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetY(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetY(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4RotationOptions003
 * @tc.desc: Test getting and setting attribute of Z, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions003, TestSize.Level1)
{
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetZ(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetZ(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetZ(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetZ(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetZ(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4RotationOptions004
 * @tc.desc: Test getting and setting attribute of angle, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions004, TestSize.Level1)
{
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetAngle(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetAngle(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetAngle(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetAngle(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetAngle(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4RotationOptions005
 * @tc.desc: Test getting and setting attribute of centerX, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions005, TestSize.Level1)
{
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetCenterX(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetCenterX(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetCenterX(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetCenterX(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetCenterX(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4RotationOptions006
 * @tc.desc: Test getting and setting attribute of centerY, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions006, TestSize.Level1)
{
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetCenterY(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetCenterY(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetCenterY(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetCenterY(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_GetCenterY(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4TranslationOptions001
 * @tc.desc: Test getting and setting attribute of X, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions001, TestSize.Level1)
{
    ArkUI_Matrix4TranslationOptions* options = OH_ArkUI_Matrix4TranslationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_SetX(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_SetX(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetX(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetX(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetX(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4TranslationOptions002
 * @tc.desc: Test getting and setting attribute of Y, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions002, TestSize.Level1)
{
    ArkUI_Matrix4TranslationOptions* options = OH_ArkUI_Matrix4TranslationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_SetY(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_SetY(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetY(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetY(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetY(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4TranslationOptions003
 * @tc.desc: Test getting and setting attribute of Z, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions003, TestSize.Level1)
{
    ArkUI_Matrix4TranslationOptions* options = OH_ArkUI_Matrix4TranslationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_SetZ(nullptr, value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_SetZ(options, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetZ(nullptr, &value), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetZ(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4TranslationOptions_GetZ(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, value);
}

/**
 * @tc.name: Matrix4001
 * @tc.desc: Test OH_ArkUI_Matrix4, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4001, TestSize.Level1)
{
    ArkUI_Matrix4* options = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(options, nullptr);
    OH_ArkUI_Matrix4_Dispose(options);
    float result[] = { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 8.0f, 9.0f, 0.0f, 1.0f, 0.0f, 3.0f };
    ArkUI_Matrix4* matrix4 = OH_ArkUI_Matrix4_CreateByElements(result);
    ASSERT_NE(matrix4, nullptr);
    ArkUI_Matrix4* matrix4Copy = OH_ArkUI_Matrix4_Copy(matrix4);
    ASSERT_NE(matrix4Copy, nullptr);
    EXPECT_EQ(OH_ArkUI_Matrix4_Invert(nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Invert(matrix4Copy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4_Combine(nullptr, matrix4), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Combine(matrix4Copy, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Combine(matrix4Copy, matrix4), ARKUI_ERROR_CODE_NO_ERROR);
    ArkUI_Matrix4TranslationOptions* translationOptions = OH_ArkUI_Matrix4TranslationOptions_Create();
    ASSERT_NE(translationOptions, nullptr);
    EXPECT_EQ(OH_ArkUI_Matrix4_Translate(nullptr, translationOptions), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Translate(matrix4Copy, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Translate(matrix4Copy, translationOptions), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4_GetElements(nullptr, result), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_GetElements(matrix4Copy, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_GetElements(matrix4Copy, result), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: Matrix4002
 * @tc.desc: Test OH_ArkUI_Matrix4, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4002, TestSize.Level1)
{
    ArkUI_Matrix4* options = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(options, nullptr);
    ArkUI_Matrix4ScaleOptions* scaleOptions = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(scaleOptions, nullptr);
    EXPECT_EQ(OH_ArkUI_Matrix4_Scale(nullptr, scaleOptions), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Scale(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Scale(options, scaleOptions), ARKUI_ERROR_CODE_NO_ERROR);
    ArkUI_Matrix4RotationOptions* rotationOptions = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(rotationOptions, nullptr);
    EXPECT_EQ(OH_ArkUI_Matrix4_Rotate(nullptr, rotationOptions), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Rotate(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Rotate(options, rotationOptions), ARKUI_ERROR_CODE_NO_ERROR);
    float value = 1.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4RotationOptions_SetZ(rotationOptions, value), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4_Rotate(options, rotationOptions), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4_Skew(nullptr, 1.0f, 1.0f), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_Skew(options, 1.0f, 1.0f), ARKUI_ERROR_CODE_NO_ERROR);
    ArkUI_PointF oriPoint = {2.0f, 2.0f};
    ArkUI_PointF result7;
    EXPECT_EQ(OH_ArkUI_Matrix4_TransformPoint(nullptr, &oriPoint, &result7), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_TransformPoint(options, nullptr, &result7), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_TransformPoint(options, &oriPoint, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_TransformPoint(options, &oriPoint, &result7), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: Matrix4003
 * @tc.desc: Test OH_ArkUI_Matrix4, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4003, TestSize.Level1)
{
    ArkUI_Matrix4* options = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(options, nullptr);
    ArkUI_PointF src1[4] = {{0, 0}, {500, 0}, {0, 500}, {500, 500}};
    ArkUI_PointF dst[4] = {{0, 0}, {500, 0}, {0, 500}, {750, 1000}};
    EXPECT_EQ(OH_ArkUI_Matrix4_SetPolyToPoly(nullptr, src1, dst, NUM_4), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_SetPolyToPoly(options, nullptr, dst, NUM_4), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_SetPolyToPoly(options, src1, nullptr, NUM_4), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4_SetPolyToPoly(options, src1, dst, NUM_4), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: Matrix4001
 * @tc.desc: Test OH_ArkUI_Matrix4, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4004, TestSize.Level1)
{
    float result[] = { 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 8.0f, 9.0f, 0.0f, 1.0f, 0.0f, 3.0f };
    float result1[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f };
    ArkUI_Matrix4* matrix4 = OH_ArkUI_Matrix4_CreateByElements(result);
    ASSERT_NE(matrix4, nullptr);
    EXPECT_EQ(OH_ArkUI_Matrix4_GetElements(matrix4, result1), ARKUI_ERROR_CODE_NO_ERROR);
    const float epsilon = 1e-6f;
    for (int i = 0; i < NUM_16; i++) {
        float diff = std::abs(result[i] - result1[i]);
        EXPECT_LE(diff, epsilon);
    }
}
} // namespace OHOS::Ace