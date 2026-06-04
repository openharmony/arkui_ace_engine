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
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
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
    float valueOrigin = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetX(nullptr, valueOrigin), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetX(options, valueOrigin), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetX(nullptr, &valueOrigin), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetX(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetX(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, valueOrigin);
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
    float valueOrigin = 1.0f;
    float valueCopy = 0.0f;
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetY(nullptr, valueOrigin), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_SetY(options, valueOrigin), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetY(nullptr, &valueOrigin), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetY(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Matrix4ScaleOptions_GetY(options, &valueCopy), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(valueCopy, valueOrigin);
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

/**
 * @tc.name: Matrix4ScaleOptions_SetX_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_SetX with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_SetX_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4ScaleOptions_SetX(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_SetX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_GetX_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_GetX with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_GetX_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4ScaleOptions_GetX(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_GetX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or scaleX is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_SetX_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_SetX with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_SetX_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4RotationOptions_SetX(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_SetX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4TranslationOptions_SetX_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4TranslationOptions_SetX with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions_SetX_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4TranslationOptions_SetX(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4TranslationOptions_SetX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_Invert_NullMatrix_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Invert with null matrix.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Invert_NullMatrix_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4_Invert(nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Invert"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_Combine_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Combine with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Combine_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4* matrix = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(matrix, nullptr);
    auto result = OH_ArkUI_Matrix4_Combine(nullptr, matrix);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Combine"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: oriMatrix or anotherMatrix is null"), std::string::npos);
    OH_ArkUI_Matrix4_Dispose(matrix);
}

/**
 * @tc.name: Matrix4_Scale_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Scale with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Scale_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4ScaleOptions* scaleOptions = OH_ArkUI_Matrix4ScaleOptions_Create();
    ASSERT_NE(scaleOptions, nullptr);
    auto result = OH_ArkUI_Matrix4_Scale(nullptr, scaleOptions);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Scale"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix or scale is null"), std::string::npos);
    OH_ArkUI_Matrix4ScaleOptions_Dispose(scaleOptions);
}

/**
 * @tc.name: Matrix4_Translate_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Translate with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Translate_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4TranslationOptions* translateOptions = OH_ArkUI_Matrix4TranslationOptions_Create();
    ASSERT_NE(translateOptions, nullptr);
    auto result = OH_ArkUI_Matrix4_Translate(nullptr, translateOptions);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Translate"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix or translate is null"), std::string::npos);
    OH_ArkUI_Matrix4TranslationOptions_Dispose(translateOptions);
}

/**
 * @tc.name: Matrix4_SetPolyToPoly_PointCountTooLarge_001
 * @tc.desc: Test OH_ArkUI_Matrix4_SetPolyToPoly with pointCount greater than 4.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_SetPolyToPoly_PointCountTooLarge_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4* matrix = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(matrix, nullptr);
    ArkUI_PointF src[5] = {{0, 0}, {100, 0}, {0, 100}, {100, 100}, {50, 50}};
    ArkUI_PointF dst[5] = {{0, 0}, {100, 0}, {0, 100}, {100, 100}, {50, 50}};
    auto result = OH_ArkUI_Matrix4_SetPolyToPoly(matrix, src, dst, 5);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_SetPolyToPoly"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: pointCount is greater than 4"), std::string::npos);
    OH_ArkUI_Matrix4_Dispose(matrix);
}

/**
 * @tc.name: Matrix4ScaleOptions_SetY_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_SetY with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_SetY_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4ScaleOptions_SetY(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_SetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_GetY_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_GetY with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_GetY_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4ScaleOptions_GetY(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_GetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or scaleY is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_SetZ_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_SetZ with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_SetZ_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4ScaleOptions_SetZ(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_SetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_GetZ_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_GetZ with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_GetZ_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4ScaleOptions_GetZ(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_GetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or scaleZ is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_SetCenterX_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_SetCenterX with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_SetCenterX_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4ScaleOptions_SetCenterX(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_SetCenterX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_GetCenterX_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_GetCenterX with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_GetCenterX_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4ScaleOptions_GetCenterX(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_GetCenterX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or centerX is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_SetCenterY_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_SetCenterY with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_SetCenterY_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4ScaleOptions_SetCenterY(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_SetCenterY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4ScaleOptions_GetCenterY_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4ScaleOptions_GetCenterY with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4ScaleOptions_GetCenterY_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4ScaleOptions_GetCenterY(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4ScaleOptions_GetCenterY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or centerY is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_GetX_NotSet_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetX when isSetX is false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetX_NotSet_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetX(options, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options, x is null or isSetX is false"), std::string::npos);
    OH_ArkUI_Matrix4RotationOptions_Dispose(options);
}

/**
 * @tc.name: Matrix4RotationOptions_GetX_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetX with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetX_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetX(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options, x is null or isSetX is false"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_SetY_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_SetY with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_SetY_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4RotationOptions_SetY(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_SetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_GetY_NotSet_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetY when isSetY is false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetY_NotSet_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetY(options, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options, y is null or isSetY is false"), std::string::npos);
    OH_ArkUI_Matrix4RotationOptions_Dispose(options);
}

/**
 * @tc.name: Matrix4RotationOptions_GetY_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetY with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetY_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetY(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options, y is null or isSetY is false"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_SetZ_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_SetZ with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_SetZ_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4RotationOptions_SetZ(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_SetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_GetZ_NotSet_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetZ when isSetZ is false.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetZ_NotSet_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4RotationOptions* options = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(options, nullptr);
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetZ(options, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options, z is null or isSetZ is false"), std::string::npos);
    OH_ArkUI_Matrix4RotationOptions_Dispose(options);
}

/**
 * @tc.name: Matrix4RotationOptions_GetZ_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetZ with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetZ_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetZ(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options, z is null or isSetZ is false"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_SetAngle_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_SetAngle with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_SetAngle_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4RotationOptions_SetAngle(nullptr, 45.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_SetAngle"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_GetAngle_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetAngle with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetAngle_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetAngle(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetAngle"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or angle is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_SetCenterX_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_SetCenterX with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_SetCenterX_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4RotationOptions_SetCenterX(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_SetCenterX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_GetCenterX_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetCenterX with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetCenterX_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetCenterX(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetCenterX"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or centerX is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_SetCenterY_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_SetCenterY with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_SetCenterY_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4RotationOptions_SetCenterY(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_SetCenterY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4RotationOptions_GetCenterY_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4RotationOptions_GetCenterY with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4RotationOptions_GetCenterY_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4RotationOptions_GetCenterY(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4RotationOptions_GetCenterY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or centerY is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4TranslationOptions_SetY_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4TranslationOptions_SetY with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions_SetY_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4TranslationOptions_SetY(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4TranslationOptions_SetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4TranslationOptions_GetY_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4TranslationOptions_GetY with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions_GetY_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4TranslationOptions_GetY(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4TranslationOptions_GetY"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or y is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4TranslationOptions_SetZ_NullOption_001
 * @tc.desc: Test OH_ArkUI_Matrix4TranslationOptions_SetZ with null option.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions_SetZ_NullOption_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4TranslationOptions_SetZ(nullptr, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4TranslationOptions_SetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4TranslationOptions_GetZ_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4TranslationOptions_GetZ with null parameters.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4TranslationOptions_GetZ_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float value = 0.0f;
    auto result = OH_ArkUI_Matrix4TranslationOptions_GetZ(nullptr, &value);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4TranslationOptions_GetZ"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: options or z is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_Rotate_NullMatrix_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Rotate with null matrix.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Rotate_NullMatrix_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4RotationOptions* rotationOptions = OH_ArkUI_Matrix4RotationOptions_Create();
    ASSERT_NE(rotationOptions, nullptr);
    auto result = OH_ArkUI_Matrix4_Rotate(nullptr, rotationOptions);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Rotate"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix or rotate is null"), std::string::npos);
    OH_ArkUI_Matrix4RotationOptions_Dispose(rotationOptions);
}

/**
 * @tc.name: Matrix4_Rotate_NullRotate_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Rotate with null rotate options.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Rotate_NullRotate_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4* matrix = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(matrix, nullptr);
    auto result = OH_ArkUI_Matrix4_Rotate(matrix, nullptr);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Rotate"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix or rotate is null"), std::string::npos);
    OH_ArkUI_Matrix4_Dispose(matrix);
}

/**
 * @tc.name: Matrix4_Skew_NullMatrix_001
 * @tc.desc: Test OH_ArkUI_Matrix4_Skew with null matrix.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_Skew_NullMatrix_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto result = OH_ArkUI_Matrix4_Skew(nullptr, 1.0f, 1.0f);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_Skew"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_TransformPoint_NullMatrix_001
 * @tc.desc: Test OH_ArkUI_Matrix4_TransformPoint with null matrix.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_TransformPoint_NullMatrix_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_PointF oriPoint = {2.0f, 2.0f};
    ArkUI_PointF resultPoint = {0.0f, 0.0f};
    auto result = OH_ArkUI_Matrix4_TransformPoint(nullptr, &oriPoint, &resultPoint);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_TransformPoint"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix, oriPoint or result is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_TransformPoint_NullParams_002
 * @tc.desc: Test OH_ArkUI_Matrix4_TransformPoint with null oriPoint or result.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_TransformPoint_NullParams_002, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4* matrix = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(matrix, nullptr);
    ArkUI_PointF resultPoint = {0.0f, 0.0f};
    auto result = OH_ArkUI_Matrix4_TransformPoint(matrix, nullptr, &resultPoint);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_TransformPoint"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix, oriPoint or result is null"), std::string::npos);
    OH_ArkUI_Matrix4_Dispose(matrix);
}

/**
 * @tc.name: Matrix4_SetPolyToPoly_NullParams_001
 * @tc.desc: Test OH_ArkUI_Matrix4_SetPolyToPoly with null matrix.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_SetPolyToPoly_NullParams_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_PointF src[4] = {{0, 0}, {100, 0}, {0, 100}, {100, 100}};
    ArkUI_PointF dst[4] = {{0, 0}, {100, 0}, {0, 100}, {100, 100}};
    auto result = OH_ArkUI_Matrix4_SetPolyToPoly(nullptr, src, dst, NUM_4);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_SetPolyToPoly"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix, src or dst is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_SetPolyToPoly_NullSrc_002
 * @tc.desc: Test OH_ArkUI_Matrix4_SetPolyToPoly with null src.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_SetPolyToPoly_NullSrc_002, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4* matrix = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(matrix, nullptr);
    ArkUI_PointF dst[4] = {{0, 0}, {100, 0}, {0, 100}, {100, 100}};
    auto result = OH_ArkUI_Matrix4_SetPolyToPoly(matrix, nullptr, dst, NUM_4);
    EXPECT_EQ(result, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(result)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_SetPolyToPoly"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix, src or dst is null"), std::string::npos);
    OH_ArkUI_Matrix4_Dispose(matrix);
}

/**
 * @tc.name: Matrix4_GetElements_NullMatrix_001
 * @tc.desc: Test OH_ArkUI_Matrix4_GetElements with null matrix.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_GetElements_NullMatrix_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    float result[NUM_16] = {0};
    auto errorCode = OH_ArkUI_Matrix4_GetElements(nullptr, result);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(errorCode)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_GetElements"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix or result is null"), std::string::npos);
}

/**
 * @tc.name: Matrix4_GetElements_NullResult_001
 * @tc.desc: Test OH_ArkUI_Matrix4_GetElements with null result.
 * @tc.type: FUNC
 */
HWTEST_F(NodeVisualEffectTest, Matrix4_GetElements_NullResult_001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_Matrix4* matrix = OH_ArkUI_Matrix4_CreateIdentity();
    ASSERT_NE(matrix, nullptr);
    auto errorCode = OH_ArkUI_Matrix4_GetElements(matrix, nullptr);
    EXPECT_EQ(errorCode, ARKUI_ERROR_CODE_PARAM_INVALID);

    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(errorCode)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_Matrix4_GetElements"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: matrix or result is null"), std::string::npos);
    OH_ArkUI_Matrix4_Dispose(matrix);
}
} // namespace OHOS::Ace
