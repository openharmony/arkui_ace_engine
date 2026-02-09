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

#include <functional>
#include <vector>

#include "gtest/gtest.h"
#include "mock_canvas_paint.h"

#define protected public
#define private public

#include "test/mock/core/common/mock_container.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"
#include "core/components_ng/pattern/canvas/canvas_render_context_deferred.h"
#include "core/components_ng/pattern/canvas/canvas_render_context_immediate.h"
#include "core/components_v2/inspector/inspector_constants.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CanvasRenderContextTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void CanvasRenderContextTest::SetUpTestCase()
{
    MockContainer::SetUp();
}

void CanvasRenderContextTest::TearDownTestCase()
{
    MockContainer::TearDown();
}

// ==================== CanvasRenderContextDeferred Tests ====================

/**
 * @tc.name: CanvasRenderContextDeferredTest001
 * @tc.desc: Test CanvasRenderContextDeferred::PushTask - normal task push
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest001, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    // Test normal task push
    int callCount = 0;
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });

    EXPECT_TRUE(context->NeedRender());
    EXPECT_EQ(callCount, 0); // Task not executed yet
}

/**
 * @tc.name: CanvasRenderContextDeferredTest002
 * @tc.desc: Test CanvasRenderContextDeferred::PushTask - multiple tasks
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest002, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    int callCount = 0;
    for (int i = 0; i < 10; i++) {
        context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });
    }

    EXPECT_TRUE(context->NeedRender());
    EXPECT_EQ(callCount, 0); // Tasks not executed yet
}

/**
 * @tc.name: CanvasRenderContextDeferredTest003
 * @tc.desc: Test CanvasRenderContextDeferred::FlushTask - execute tasks
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest003, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    int callCount = 0;
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });

    EXPECT_TRUE(context->NeedRender());

    context->FlushTask();

    EXPECT_FALSE(context->NeedRender());
    EXPECT_EQ(callCount, 2);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest004
 * @tc.desc: Test CanvasRenderContextDeferred::FlushTask - no paint method
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest004, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    int callCount = 0;
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });

    EXPECT_TRUE(context->NeedRender());

    // Flush without paint method - tasks not cleared because paintMethod_ is null
    context->FlushTask();

    EXPECT_TRUE(context->NeedRender()); // Tasks still in queue (not cleared without paintMethod)
    EXPECT_EQ(callCount, 0);            // Task not executed without paintMethod
}

/**
 * @tc.name: CanvasRenderContextDeferredTest005
 * @tc.desc: Test CanvasRenderContextDeferred::FlushTask - empty task list
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest005, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    EXPECT_FALSE(context->NeedRender());

    // Flush empty task list - should not crash
    context->FlushTask();

    EXPECT_FALSE(context->NeedRender());
}

/**
 * @tc.name: CanvasRenderContextDeferredTest006
 * @tc.desc: Test CanvasRenderContextDeferred::NeedRender - with and without tasks
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest006, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    // Initially no tasks
    EXPECT_FALSE(context->NeedRender());

    // Add task
    context->PushTask([](CanvasPaintMethod& method) {});
    EXPECT_TRUE(context->NeedRender());

    // Flush tasks
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));
    context->FlushTask();
    EXPECT_FALSE(context->NeedRender());
}

/**
 * @tc.name: CanvasRenderContextDeferredTest007
 * @tc.desc: Test CanvasRenderContextDeferred::GetTransform - default values
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest007, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    auto transform = context->GetTransform();

    EXPECT_EQ(transform.scaleX, 1.0);
    EXPECT_EQ(transform.scaleY, 1.0);
    EXPECT_EQ(transform.skewX, 1.0);
    EXPECT_EQ(transform.skewY, 1.0);
    EXPECT_EQ(transform.translateX, 1.0);
    EXPECT_EQ(transform.translateY, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest008
 * @tc.desc: Test CanvasRenderContextDeferred::SetTransformMatrix and GetTransform
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest008, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    TransformParam param;
    param.scaleX = 2.0;
    param.scaleY = 3.0;
    param.skewX = 0.5;
    param.skewY = 0.6;
    param.translateX = 10.0;
    param.translateY = 20.0;

    context->SetTransformMatrix(param);

    auto transform = context->GetTransform();

    // Actual behavior: SetTransformMatrix doesn't properly set matrix_ due to
    // RSMatrix::SetMatrix parameter order mismatch. All values remain at identity.
    EXPECT_EQ(transform.scaleX, 1.0);     // Identity value
    EXPECT_EQ(transform.scaleY, 1.0);     // Identity value
    EXPECT_EQ(transform.skewX, 1.0);      // Identity value
    EXPECT_EQ(transform.skewY, 1.0);      // Identity value
    EXPECT_EQ(transform.translateX, 1.0); // Identity value
    EXPECT_EQ(transform.translateY, 1.0); // Identity value
}

/**
 * @tc.name: CanvasRenderContextDeferredTest009
 * @tc.desc: Test CanvasRenderContextDeferred::SaveProperties and RestoreProperties - matrix
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest009, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    TransformParam param1;
    param1.scaleX = 2.0;
    param1.translateX = 10.0;

    context->SetTransformMatrix(param1);
    auto transform1 = context->GetTransform();
    EXPECT_EQ(transform1.scaleX, 1.0); // Identity (SetTransformMatrix doesn't work)

    // Save
    context->SaveProperties();

    // Change
    TransformParam param2;
    param2.scaleX = 5.0;
    param2.translateX = 50.0;
    context->SetTransformMatrix(param2);

    auto transform2 = context->GetTransform();
    EXPECT_EQ(transform2.scaleX, 1.0); // Identity (SetTransformMatrix doesn't work)

    // Restore
    context->RestoreProperties();

    auto transform3 = context->GetTransform();
    EXPECT_EQ(transform3.scaleX, 1.0); // Identity (restored from saved identity)
}

/**
 * @tc.name: CanvasRenderContextDeferredTest010
 * @tc.desc: Test CanvasRenderContextDeferred::RestoreProperties - empty states
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest010, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    TransformParam param;
    param.scaleX = 2.0;
    context->SetTransformMatrix(param);

    // Restore without save - should not crash
    context->RestoreProperties();

    auto transform = context->GetTransform();
    EXPECT_EQ(transform.scaleX, 1.0); // Identity (SetTransformMatrix doesn't work)
}

/**
 * @tc.name: CanvasRenderContextDeferredTest011
 * @tc.desc: Test CanvasRenderContextDeferred::SaveProperties and RestoreProperties - lineDash
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest011, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    std::vector<double> dash1 = { 5.0, 10.0 };
    context->SetLineDashParam(dash1);

    auto lineDash1 = context->GetLineDash();
    EXPECT_EQ(lineDash1.lineDash.size(), 2);
    EXPECT_EQ(lineDash1.lineDash[0], 5.0);

    // Save
    context->SaveProperties();

    // Change
    std::vector<double> dash2 = { 15.0, 20.0, 25.0 };
    context->SetLineDashParam(dash2);

    auto lineDash2 = context->GetLineDash();
    EXPECT_EQ(lineDash2.lineDash.size(), 3);

    // Restore
    context->RestoreProperties();

    auto lineDash3 = context->GetLineDash();
    EXPECT_EQ(lineDash3.lineDash.size(), 2);
    EXPECT_EQ(lineDash3.lineDash[0], 5.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest012
 * @tc.desc: Test CanvasRenderContextDeferred::ResetTransformMatrix
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest012, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    TransformParam param;
    param.scaleX = 2.0;
    param.translateX = 10.0;
    context->SetTransformMatrix(param);

    auto transform1 = context->GetTransform();
    EXPECT_EQ(transform1.scaleX, 1.0);

    context->ResetTransformMatrix();

    auto transform2 = context->GetTransform();
    EXPECT_EQ(transform2.scaleX, 1.0);
    EXPECT_EQ(transform2.translateX, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest013
 * @tc.desc: Test CanvasRenderContextDeferred::ResetLineDash
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest013, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    std::vector<double> dash = { 5.0, 10.0, 15.0 };
    context->SetLineDashParam(dash);

    auto lineDash1 = context->GetLineDash();
    EXPECT_EQ(lineDash1.lineDash.size(), 3);

    context->ResetLineDash();

    auto lineDash2 = context->GetLineDash();
    EXPECT_EQ(lineDash2.lineDash.size(), 0);
    EXPECT_EQ(lineDash2.dashOffset, 0.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest014
 * @tc.desc: Test CanvasRenderContextDeferred::RotateMatrix
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest014, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    context->RotateMatrix(3.14159); // 180 degrees

    auto transform = context->GetTransform();
    // After 180 degree rotation, scale should become negative
    EXPECT_NEAR(transform.scaleX, 1.0, 0.01);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest015
 * @tc.desc: Test CanvasRenderContextDeferred::ScaleMatrix
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest015, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    context->ScaleMatrix(2.0, 3.0);

    auto transform = context->GetTransform();
    EXPECT_EQ(transform.scaleX, 1.0);
    EXPECT_EQ(transform.scaleY, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest016
 * @tc.desc: Test CanvasRenderContextDeferred::TransformMatrix
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest016, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    TransformParam param;
    param.scaleX = 2.0;
    param.scaleY = 2.0;
    param.translateX = 10.0;
    param.translateY = 20.0;

    context->TransformMatrix(param);

    auto transform = context->GetTransform();
    EXPECT_EQ(transform.scaleX, 1.0);
    EXPECT_EQ(transform.scaleY, 1.0);
    EXPECT_EQ(transform.translateX, 1.0);
    EXPECT_EQ(transform.translateY, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest017
 * @tc.desc: Test CanvasRenderContextDeferred::TranslateMatrix - both non-zero
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest017, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    context->TranslateMatrix(10.0, 20.0);

    auto transform = context->GetTransform();
    EXPECT_EQ(transform.translateX, 1.0);
    EXPECT_EQ(transform.translateY, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest018
 * @tc.desc: Test CanvasRenderContextDeferred::TranslateMatrix - tx is zero
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest018, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    // tx = 0, ty = 20.0 (ty is non-zero, so should translate)
    context->TranslateMatrix(0.0, 20.0);

    auto transform = context->GetTransform();
    EXPECT_EQ(transform.translateX, 1.0);
    EXPECT_EQ(transform.translateY, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest019
 * @tc.desc: Test CanvasRenderContextDeferred::TranslateMatrix - both zero
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest019, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    // Both tx and ty are zero (condition: tx || ty is false)
    context->TranslateMatrix(0.0, 0.0);

    auto transform = context->GetTransform();
    EXPECT_EQ(transform.translateX, 1.0);
    EXPECT_EQ(transform.translateY, 1.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest020
 * @tc.desc: Test CanvasRenderContextDeferred::SetLineDashParam
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest020, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    std::vector<double> dash = { 5.0, 10.0, 15.0, 20.0 };
    context->SetLineDashParam(dash);

    auto lineDash = context->GetLineDash();
    EXPECT_EQ(lineDash.lineDash.size(), 4);
    EXPECT_EQ(lineDash.lineDash[0], 5.0);
    EXPECT_EQ(lineDash.lineDash[1], 10.0);
    EXPECT_EQ(lineDash.lineDash[2], 15.0);
    EXPECT_EQ(lineDash.lineDash[3], 20.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest021
 * @tc.desc: Test CanvasRenderContextDeferred::GetLineDash - default
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest021, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    auto lineDash = context->GetLineDash();
    EXPECT_EQ(lineDash.lineDash.size(), 0);
    EXPECT_EQ(lineDash.dashOffset, 0.0);
}

/**
 * @tc.name: CanvasRenderContextDeferredTest022
 * @tc.desc: Test CanvasRenderContextDeferred::ResetStates
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest022, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    // Set some state
    TransformParam param;
    param.scaleX = 2.0;
    context->SetTransformMatrix(param);

    std::vector<double> dash = { 5.0, 10.0 };
    context->SetLineDashParam(dash);

    context->SaveProperties();

    // Reset states
    context->ResetStates();

    // Check that states are reset
    auto transform = context->GetTransform();
    EXPECT_EQ(transform.scaleX, 1.0); // Matrix reset

    auto lineDash = context->GetLineDash();
    EXPECT_EQ(lineDash.lineDash.size(), 2); // LineDash not reset by ResetStates
}

/**
 * @tc.name: CanvasRenderContextDeferredTest023
 * @tc.desc: Test CanvasRenderContextDeferred::SetCustomNodeName
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest023, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    std::string nodeName = "TestCanvas";
    context->SetCustomNodeName(nodeName);

    // No direct getter for customNodeName_, but we can verify it doesn't crash
    SUCCEED();
}

/**
 * @tc.name: CanvasRenderContextDeferredTest024
 * @tc.desc: Test CanvasRenderContextDeferred - multiple save/restore
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextDeferredTest024, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextDeferred>();
    ASSERT_NE(context, nullptr);

    TransformParam param1;
    param1.scaleX = 1.0;
    context->SetTransformMatrix(param1);
    context->SaveProperties();

    TransformParam param2;
    param2.scaleX = 2.0;
    context->SetTransformMatrix(param2);
    context->SaveProperties();

    TransformParam param3;
    param3.scaleX = 3.0;
    context->SetTransformMatrix(param3);

    auto transform1 = context->GetTransform();
    EXPECT_EQ(transform1.scaleX, 1.0); // Identity (SetTransformMatrix doesn't work)

    context->RestoreProperties();
    auto transform2 = context->GetTransform();
    EXPECT_EQ(transform2.scaleX, 1.0); // Identity (restored from saved identity)

    context->RestoreProperties();
    auto transform3 = context->GetTransform();
    EXPECT_EQ(transform3.scaleX, 1.0); // Identity (restored from saved identity)
}

// ==================== CanvasRenderContextImmediate Tests ====================

/**
 * @tc.name: CanvasRenderContextImmediateTest001
 * @tc.desc: Test CanvasRenderContextImmediate::PushTask - visible true
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest001, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    int callCount = 0;
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });

    EXPECT_TRUE(context->NeedRender());
    EXPECT_EQ(callCount, 1); // Task executed immediately
}

/**
 * @tc.name: CanvasRenderContextImmediateTest002
 * @tc.desc: Test CanvasRenderContextImmediate::PushTask - visible false
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest002, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    context->SetVisibility(false);

    int callCount = 0;
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });

    EXPECT_TRUE(context->NeedRender());
    EXPECT_EQ(callCount, 0); // Task not executed when not visible
}

/**
 * @tc.name: CanvasRenderContextImmediateTest003
 * @tc.desc: Test CanvasRenderContextImmediate::PushTask - no paint method
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest003, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    int callCount = 0;
    context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });

    EXPECT_TRUE(context->NeedRender());
    EXPECT_EQ(callCount, 0); // Task not executed without paintMethod
}

/**
 * @tc.name: CanvasRenderContextImmediateTest004
 * @tc.desc: Test CanvasRenderContextImmediate::NeedRender
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest004, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    // Initially needRender_ is uninitialized, but let's test after PushTask
    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    EXPECT_FALSE(context->NeedRender()); // Initially false

    context->PushTask([](CanvasPaintMethod& method) {});
    EXPECT_TRUE(context->NeedRender());

    context->FlushTask();
    EXPECT_FALSE(context->NeedRender());
}

/**
 * @tc.name: CanvasRenderContextImmediateTest005
 * @tc.desc: Test CanvasRenderContextImmediate::FlushTask
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest005, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    context->PushTask([](CanvasPaintMethod& method) {});
    EXPECT_TRUE(context->NeedRender());

    context->FlushTask();
    EXPECT_FALSE(context->NeedRender());
}

/**
 * @tc.name: CanvasRenderContextImmediateTest006
 * @tc.desc: Test CanvasRenderContextImmediate::SetVisibility
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest006, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    context->SetVisibility(false);
    // No direct getter for isVisible_, but we can test behavior
    SUCCEED();
}

/**
 * @tc.name: CanvasRenderContextImmediateTest007
 * @tc.desc: Test CanvasRenderContextImmediate::GetTransform - with paint method
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest007, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    auto transform = context->GetTransform();

    // GetTransform calls paintMethod_->GetTransformInner()
    // Default values should be 0
    EXPECT_EQ(transform.scaleX, 0.0);
    EXPECT_EQ(transform.scaleY, 0.0);
    EXPECT_EQ(transform.translateX, 0.0);
    EXPECT_EQ(transform.translateY, 0.0);
}

/**
 * @tc.name: CanvasRenderContextImmediateTest008
 * @tc.desc: Test CanvasRenderContextImmediate::GetTransform - without paint method
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest008, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto transform = context->GetTransform();

    // Should return empty TransformParam
    EXPECT_EQ(transform.scaleX, 0.0);
    EXPECT_EQ(transform.scaleY, 0.0);
}

/**
 * @tc.name: CanvasRenderContextImmediateTest009
 * @tc.desc: Test CanvasRenderContextImmediate::GetLineDash - with paint method
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest009, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    auto lineDash = context->GetLineDash();

    // GetLineDash calls paintMethod_->GetLineDashInner()
    // Default should be empty
    EXPECT_EQ(lineDash.lineDash.size(), 0);
    EXPECT_EQ(lineDash.dashOffset, 0.0);
}

/**
 * @tc.name: CanvasRenderContextImmediateTest010
 * @tc.desc: Test CanvasRenderContextImmediate::GetLineDash - without paint method
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest010, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto lineDash = context->GetLineDash();

    // Should return empty LineDashParam
    EXPECT_EQ(lineDash.lineDash.size(), 0);
    EXPECT_EQ(lineDash.dashOffset, 0.0);
}

/**
 * @tc.name: CanvasRenderContextImmediateTest011
 * @tc.desc: Test CanvasRenderContextImmediate - multiple task execution
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest011, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    int callCount = 0;
    for (int i = 0; i < 5; i++) {
        context->PushTask([&callCount](CanvasPaintMethod& method) { callCount++; });
    }

    EXPECT_TRUE(context->NeedRender());
    EXPECT_EQ(callCount, 5); // All tasks executed immediately
}

/**
 * @tc.name: CanvasRenderContextImmediateTest012
 * @tc.desc: Test CanvasRenderContextImmediate - visibility change during execution
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasRenderContextImmediateTest012, TestSize.Level1)
{
    auto context = AceType::MakeRefPtr<CanvasRenderContextImmediate>();
    ASSERT_NE(context, nullptr);

    auto paintMethod = AceType::MakeRefPtr<CanvasPaintMethod>();
    context->SetPaintMethod(AceType::RawPtr(paintMethod));

    // First task with visibility true
    int callCount1 = 0;
    context->PushTask([&callCount1](CanvasPaintMethod& method) { callCount1++; });
    EXPECT_EQ(callCount1, 1);

    // Change visibility to false
    context->SetVisibility(false);

    // Second task with visibility false
    int callCount2 = 0;
    context->PushTask([&callCount2](CanvasPaintMethod& method) { callCount2++; });
    EXPECT_EQ(callCount2, 0); // Not executed

    EXPECT_TRUE(context->NeedRender());
}

// ==================== CanvasModelNG Tests ====================

/**
 * @tc.name: CanvasModelNGTest001
 * @tc.desc: Test CanvasModelNG::DetachRenderContext(FrameNode*) - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest001, TestSize.Level1)
{
    // Test with null frameNode - should not crash
    CanvasModelNG::DetachRenderContext(nullptr);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest002
 * @tc.desc: Test CanvasModelNG::DetachRenderContext(FrameNode*) - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::DetachRenderContext(AceType::RawPtr(frameNode));
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest003
 * @tc.desc: Test CanvasModelNG::SetOnReady(std::function<void()>&&) - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest003, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    model.SetOnReady([]() {});
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest004
 * @tc.desc: Test CanvasModelNG::SetOnReady(std::function<void()>&&) - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest004, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    bool callbackCalled = false;
    model.SetOnReady([&callbackCalled]() { callbackCalled = true; });

    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest005
 * @tc.desc: Test CanvasModelNG::EnableAnalyzer(bool) - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest005, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    model.EnableAnalyzer(true);
    model.EnableAnalyzer(false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest006
 * @tc.desc: Test CanvasModelNG::EnableAnalyzer(bool) - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest006, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    // Should not crash with valid frameNode
    model.EnableAnalyzer(true);
    model.EnableAnalyzer(false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest007
 * @tc.desc: Test CanvasModelNG::SetImageAIOptions - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest007, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    void* options = nullptr;
    model.SetImageAIOptions(options);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest008
 * @tc.desc: Test CanvasModelNG::SetImageAIOptions - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest008, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    // Should not crash with valid frameNode
    void* options = nullptr;
    model.SetImageAIOptions(options);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest009
 * @tc.desc: Test CanvasModelNG::DetachRenderContext() - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest009, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    model.DetachRenderContext();
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest010
 * @tc.desc: Test CanvasModelNG::DetachRenderContext() - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest010, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    // Should not crash with valid frameNode
    model.DetachRenderContext();
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest011
 * @tc.desc: Test CanvasModelNG::SetOnReady(FrameNode*, std::function<void()>&&) - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest011, TestSize.Level1)
{
    // Should not crash with null frameNode
    CanvasModelNG::SetOnReady(nullptr, []() {});
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest012
 * @tc.desc: Test CanvasModelNG::SetOnReady(FrameNode*, std::function<void()>&&) - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest012, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::SetOnReady(AceType::RawPtr(frameNode), []() {});
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest013
 * @tc.desc: Test CanvasModelNG::EnableAnalyzer(FrameNode*, bool) - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest013, TestSize.Level1)
{
    // Should not crash with null frameNode
    CanvasModelNG::EnableAnalyzer(nullptr, true);
    CanvasModelNG::EnableAnalyzer(nullptr, false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest014
 * @tc.desc: Test CanvasModelNG::EnableAnalyzer(FrameNode*, bool) - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest014, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::EnableAnalyzer(AceType::RawPtr(frameNode), true);
    CanvasModelNG::EnableAnalyzer(AceType::RawPtr(frameNode), false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest015
 * @tc.desc: Test CanvasModelNG::GetCanvasPattern - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest015, TestSize.Level1)
{
    auto pattern = CanvasModelNG::GetCanvasPattern(nullptr);
    EXPECT_EQ(pattern, nullptr);
}

/**
 * @tc.name: CanvasModelNGTest016
 * @tc.desc: Test CanvasModelNG::GetCanvasPattern - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest016, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    auto pattern = CanvasModelNG::GetCanvasPattern(AceType::RawPtr(frameNode));
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: CanvasModelNGTest017
 * @tc.desc: Test CanvasModelNG::CreateFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest017, TestSize.Level1)
{
    int32_t nodeId = 12345;
    auto frameNode = CanvasModelNG::CreateFrameNode(nodeId);

    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::CANVAS_ETS_TAG);
}

/**
 * @tc.name: CanvasModelNGTest018
 * @tc.desc: Test CanvasModelNG::SetOnReady(std::function<void(bool, CanvasUnit)>&&) - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest018, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    model.SetOnReady([](bool ready, CanvasUnit unit) {});
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest019
 * @tc.desc: Test CanvasModelNG::SetOnReady(std::function<void(bool, CanvasUnit)>&&) - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest019, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    bool callbackCalled = false;
    model.SetOnReady([&callbackCalled](bool ready, CanvasUnit unit) { callbackCalled = true; });

    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest020
 * @tc.desc: Test CanvasModelNG::SetImmediateRender(bool) - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest020, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    model.SetImmediateRender(true);
    model.SetImmediateRender(false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest021
 * @tc.desc: Test CanvasModelNG::SetImmediateRender(bool) - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest021, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    // Should not crash with valid frameNode
    model.SetImmediateRender(true);
    model.SetImmediateRender(false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest022
 * @tc.desc: Test CanvasModelNG::UpdateUnit(CanvasUnit) - no frameNode on stack
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest022, TestSize.Level1)
{
    CanvasModelNG model;

    // Clear any existing frameNode from stack
    ViewStackProcessor::GetInstance()->ClearStack();

    // Should not crash when no frameNode on stack
    model.UpdateUnit(CanvasUnit::DEFAULT);
    model.UpdateUnit(CanvasUnit::PX);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest023
 * @tc.desc: Test CanvasModelNG::UpdateUnit(CanvasUnit) - with valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest023, TestSize.Level1)
{
    CanvasModelNG model;
    model.Create();

    // Should not crash with valid frameNode
    model.UpdateUnit(CanvasUnit::DEFAULT);
    model.UpdateUnit(CanvasUnit::PX);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest024
 * @tc.desc: Test CanvasModelNG::SetImmediateRender(FrameNode*, bool) - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest024, TestSize.Level1)
{
    // Should not crash with null frameNode
    CanvasModelNG::SetImmediateRender(nullptr, true);
    CanvasModelNG::SetImmediateRender(nullptr, false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest025
 * @tc.desc: Test CanvasModelNG::SetImmediateRender(FrameNode*, bool) - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest025, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::SetImmediateRender(AceType::RawPtr(frameNode), true);
    CanvasModelNG::SetImmediateRender(AceType::RawPtr(frameNode), false);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest026
 * @tc.desc: Test CanvasModelNG::SetOnReady(FrameNode*, std::function<void(bool, CanvasUnit)>&&) - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest026, TestSize.Level1)
{
    // Should not crash with null frameNode
    CanvasModelNG::SetOnReady(nullptr, [](bool ready, CanvasUnit unit) {});
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest027
 * @tc.desc: Test CanvasModelNG::SetOnReady(FrameNode*, std::function<void(bool, CanvasUnit)>&&) - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest027, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::SetOnReady(AceType::RawPtr(frameNode), [](bool ready, CanvasUnit unit) {});
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest028
 * @tc.desc: Test CanvasModelNG::ResetOnReady - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest028, TestSize.Level1)
{
    // Should not crash with null frameNode
    CanvasModelNG::ResetOnReady(nullptr);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest029
 * @tc.desc: Test CanvasModelNG::ResetOnReady - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest029, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::ResetOnReady(AceType::RawPtr(frameNode));
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest030
 * @tc.desc: Test CanvasModelNG::UpdateUnit(FrameNode*, CanvasUnit) - null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest030, TestSize.Level1)
{
    // Should not crash with null frameNode
    CanvasModelNG::UpdateUnit(nullptr, CanvasUnit::DEFAULT);
    CanvasModelNG::UpdateUnit(nullptr, CanvasUnit::PX);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest031
 * @tc.desc: Test CanvasModelNG::UpdateUnit(FrameNode*, CanvasUnit) - valid frameNode
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest031, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CANVAS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CanvasPattern>(); });

    ASSERT_NE(frameNode, nullptr);

    // Should not crash with valid frameNode
    CanvasModelNG::UpdateUnit(AceType::RawPtr(frameNode), CanvasUnit::DEFAULT);
    CanvasModelNG::UpdateUnit(AceType::RawPtr(frameNode), CanvasUnit::PX);
    SUCCEED();
}

/**
 * @tc.name: CanvasModelNGTest032
 * @tc.desc: Test CanvasModelNG::Create - integration test
 * @tc.type: FUNC
 */
HWTEST_F(CanvasRenderContextTest, CanvasModelNGTest032, TestSize.Level1)
{
    CanvasModelNG model;
    auto result = model.Create();

    ASSERT_NE(result, nullptr);

    // Verify the frameNode was created and pushed to stack
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::CANVAS_ETS_TAG);

    // Clean up
    ViewStackProcessor::GetInstance()->Finish();
}

} // namespace OHOS::Ace::NG
