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

#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "frameworks/core/components_ng/event/event_constants.h"
#include "interfaces/native/native_interface_xcomponent.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_XCOMPONENT_WIDTH = 800;
constexpr int32_t TEST_XCOMPONENT_HEIGHT = 600;
constexpr double TEST_XCOMPONENT_OFFSET_X = 10.5;
constexpr double TEST_XCOMPONENT_OFFSET_Y = 20.5;
constexpr uint32_t TEST_POINT_INDEX = 0;
constexpr float TEST_TILT_X = 0.3f;
constexpr float TEST_TILT_Y = 0.6f;
constexpr float TEST_WINDOW_X = 100.0f;
constexpr float TEST_WINDOW_Y = 200.0f;
constexpr float TEST_DISPLAY_X = 150.0f;
constexpr float TEST_DISPLAY_Y = 250.0f;
constexpr int32_t TEST_POINT_ID = 1;
constexpr int64_t TEST_DEVICE_ID = 100;
constexpr int64_t TEST_TIMESTAMP = 1234567890;
constexpr uint64_t TEST_MODIFIER_KEY_STATES = 0x01;
constexpr int32_t TEST_RATE_MIN = 30;
constexpr int32_t TEST_RATE_MAX = 120;
constexpr int32_t TEST_RATE_EXPECTED = 60;
constexpr int32_t BAD_PARAMETER_RESULT = OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;
constexpr int32_t SUCCESS_RESULT = OH_NATIVEXCOMPONENT_RESULT_SUCCESS;
} // namespace

class NativeInterfaceXComponentTestNg : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}

    void SetUp() override
    {
        impl_ = new NativeXComponentImpl();
        component_ = new OH_NativeXComponent(impl_);
    }

    void TearDown() override
    {
        delete component_;
        component_ = nullptr;
        delete impl_;
        impl_ = nullptr;
    }

    NativeXComponentImpl* impl_ = nullptr;
    OH_NativeXComponent* component_ = nullptr;
};

/**
 * @tc.name: NativeXComponent_GetXComponentId_NullParams
 * @tc.desc: Test GetXComponentId returns BAD_PARAMETER when any parameter is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentId_NullParams, TestSize.Level1)
{
    char buf[OH_XCOMPONENT_ID_LEN_MAX + 1] = { 0 };
    uint64_t size = OH_XCOMPONENT_ID_LEN_MAX;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(nullptr, buf, &size), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(component_, nullptr, &size), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(component_, buf, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetXComponentId_InvalidSize
 * @tc.desc: Test GetXComponentId returns BAD_PARAMETER when size is 0 or exceeds max
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentId_InvalidSize, TestSize.Level1)
{
    char buf[OH_XCOMPONENT_ID_LEN_MAX + 1] = { 0 };
    uint64_t zeroSize = 0;
    uint64_t overSize = OH_XCOMPONENT_ID_LEN_MAX + 2;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(component_, buf, &zeroSize), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(component_, buf, &overSize), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetXComponentId_Success
 * @tc.desc: Test GetXComponentId returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentId_Success, TestSize.Level1)
{
    const std::string testId = "test_xcomponent_id";
    impl_->SetXComponentId(testId);

    char buf[OH_XCOMPONENT_ID_LEN_MAX + 1] = { 0 };
    uint64_t size = OH_XCOMPONENT_ID_LEN_MAX;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(component_, buf, &size), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetXComponentSize_NullParams
 * @tc.desc: Test GetXComponentSize returns BAD_PARAMETER when any parameter is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentSize_NullParams, TestSize.Level1)
{
    void* window = &impl_;
    uint64_t width = 0;
    uint64_t height = 0;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(nullptr, window, &width, &height), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(component_, nullptr, &width, &height), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(component_, window, nullptr, &height), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(component_, window, &width, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetXComponentSize_Success
 * @tc.desc: Test GetXComponentSize returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentSize_Success, TestSize.Level1)
{
    impl_->SetXComponentWidth(TEST_XCOMPONENT_WIDTH);
    impl_->SetXComponentHeight(TEST_XCOMPONENT_HEIGHT);
    impl_->SetSurface(&impl_);

    void* window = &impl_;
    uint64_t width = 0;
    uint64_t height = 0;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(component_, window, &width, &height), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetXComponentOffset_NullParams
 * @tc.desc: Test GetXComponentOffset returns BAD_PARAMETER when any parameter is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentOffset_NullParams, TestSize.Level1)
{
    void* window = &impl_;
    double x = 0.0;
    double y = 0.0;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(nullptr, window, &x, &y), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(component_, nullptr, &x, &y), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(component_, window, nullptr, &y), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(component_, window, &x, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetXComponentOffset_Success
 * @tc.desc: Test GetXComponentOffset returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetXComponentOffset_Success, TestSize.Level1)
{
    impl_->SetXComponentOffsetX(TEST_XCOMPONENT_OFFSET_X);
    impl_->SetXComponentOffsetY(TEST_XCOMPONENT_OFFSET_Y);
    impl_->SetSurface(&impl_);

    void* window = &impl_;
    double x = 0.0;
    double y = 0.0;

    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(component_, window, &x, &y), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchEvent_NullParams
 * @tc.desc: Test GetTouchEvent returns BAD_PARAMETER when any parameter is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchEvent_NullParams, TestSize.Level1)
{
    void* window = &impl_;
    OH_NativeXComponent_TouchEvent touchEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetTouchEvent(nullptr, window, &touchEvent), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEvent(component_, nullptr, &touchEvent), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEvent(component_, window, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchEvent_Success
 * @tc.desc: Test GetTouchEvent returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchEvent_Success, TestSize.Level1)
{
    impl_->SetSurface(&impl_);
    OH_NativeXComponent_TouchEvent srcEvent = {};
    srcEvent.type = OH_NATIVEXCOMPONENT_DOWN;
    srcEvent.id = TEST_POINT_ID;
    srcEvent.numPoints = 1;
    impl_->SetTouchEvent(srcEvent);

    void* window = &impl_;
    OH_NativeXComponent_TouchEvent touchEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetTouchEvent(component_, window, &touchEvent), SUCCESS_RESULT);
    EXPECT_EQ(touchEvent.type, OH_NATIVEXCOMPONENT_DOWN);
    EXPECT_EQ(touchEvent.id, TEST_POINT_ID);
}

/**
 * @tc.name: NativeXComponent_GetMouseEvent_NullParams
 * @tc.desc: Test GetMouseEvent returns BAD_PARAMETER when any parameter is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetMouseEvent_NullParams, TestSize.Level1)
{
    void* window = &impl_;
    OH_NativeXComponent_MouseEvent mouseEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetMouseEvent(nullptr, window, &mouseEvent), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetMouseEvent(component_, nullptr, &mouseEvent), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetMouseEvent(component_, window, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetMouseEvent_Success
 * @tc.desc: Test GetMouseEvent returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetMouseEvent_Success, TestSize.Level1)
{
    impl_->SetSurface(&impl_);
    OH_NativeXComponent_MouseEvent srcEvent = {};
    srcEvent.action = OH_NATIVEXCOMPONENT_MOUSE_PRESS;
    srcEvent.button = OH_NATIVEXCOMPONENT_LEFT_BUTTON;
    srcEvent.x = 10.0f;
    srcEvent.y = 20.0f;
    impl_->SetMouseEvent(srcEvent);

    void* window = &impl_;
    OH_NativeXComponent_MouseEvent mouseEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetMouseEvent(component_, window, &mouseEvent), SUCCESS_RESULT);
    EXPECT_EQ(mouseEvent.action, OH_NATIVEXCOMPONENT_MOUSE_PRESS);
    EXPECT_EQ(mouseEvent.button, OH_NATIVEXCOMPONENT_LEFT_BUTTON);
}

/**
 * @tc.name: NativeXComponent_GetHistoricalPoints_NullParams
 * @tc.desc: Test GetHistoricalPoints returns BAD_PARAMETER when component or window is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetHistoricalPoints_NullParams, TestSize.Level1)
{
    void* window = &impl_;
    int32_t size = 0;
    OH_NativeXComponent_HistoricalPoint* points = nullptr;

    EXPECT_EQ(OH_NativeXComponent_GetHistoricalPoints(nullptr, window, &size, &points), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetHistoricalPoints(component_, nullptr, &size, &points), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetHistoricalPoints_Success
 * @tc.desc: Test GetHistoricalPoints returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetHistoricalPoints_Success, TestSize.Level1)
{
    impl_->SetSurface(&impl_);
    OH_NativeXComponent_HistoricalPoint point = {};
    point.id = TEST_POINT_ID;
    point.type = OH_NATIVEXCOMPONENT_MOVE;
    impl_->SetHistoricalPoint({ point });

    void* window = &impl_;
    int32_t size = 0;
    OH_NativeXComponent_HistoricalPoint* points = nullptr;

    EXPECT_EQ(OH_NativeXComponent_GetHistoricalPoints(component_, window, &size, &points), SUCCESS_RESULT);
    EXPECT_EQ(size, 1);
    EXPECT_NE(points, nullptr);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointToolType_NullParams
 * @tc.desc: Test GetTouchPointToolType returns BAD_PARAMETER when component or toolType is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointToolType_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_TouchPointToolType toolType = OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointToolType(nullptr, TEST_POINT_INDEX, &toolType),
        BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointToolType(component_, TEST_POINT_INDEX, nullptr),
        BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointToolType_Success
 * @tc.desc: Test GetTouchPointToolType returns SUCCESS and retrieves correct tool type
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointToolType_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].sourceToolType = OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER;
    impl_->SetTouchPoint(touchPoints);

    OH_NativeXComponent_TouchPointToolType toolType = OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointToolType(component_, TEST_POINT_INDEX, &toolType),
        SUCCESS_RESULT);
    EXPECT_EQ(toolType, OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointTiltX_NullParams
 * @tc.desc: Test GetTouchPointTiltX returns BAD_PARAMETER when component or tiltX is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointTiltX_NullParams, TestSize.Level1)
{
    float tiltX = 0.0f;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltX(nullptr, TEST_POINT_INDEX, &tiltX), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltX(component_, TEST_POINT_INDEX, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointTiltX_Success
 * @tc.desc: Test GetTouchPointTiltX returns SUCCESS and retrieves correct tiltX value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointTiltX_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].tiltX = TEST_TILT_X;
    impl_->SetTouchPoint(touchPoints);

    float tiltX = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltX(component_, TEST_POINT_INDEX, &tiltX), SUCCESS_RESULT);
    EXPECT_FLOAT_EQ(tiltX, TEST_TILT_X);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointTiltY_NullParams
 * @tc.desc: Test GetTouchPointTiltY returns BAD_PARAMETER when component or tiltY is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointTiltY_NullParams, TestSize.Level1)
{
    float tiltY = 0.0f;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltY(nullptr, TEST_POINT_INDEX, &tiltY), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltY(component_, TEST_POINT_INDEX, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointTiltY_Success
 * @tc.desc: Test GetTouchPointTiltY returns SUCCESS and retrieves correct tiltY value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointTiltY_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].tiltY = TEST_TILT_Y;
    impl_->SetTouchPoint(touchPoints);

    float tiltY = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltY(component_, TEST_POINT_INDEX, &tiltY), SUCCESS_RESULT);
    EXPECT_FLOAT_EQ(tiltY, TEST_TILT_Y);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointWindowX_NullParams
 * @tc.desc: Test GetTouchPointWindowX returns BAD_PARAMETER when component or windowX is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointWindowX_NullParams, TestSize.Level1)
{
    float windowX = 0.0f;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowX(nullptr, TEST_POINT_INDEX, &windowX), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowX(component_, TEST_POINT_INDEX, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointWindowX_Success
 * @tc.desc: Test GetTouchPointWindowX returns SUCCESS and retrieves correct value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointWindowX_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].windowX = TEST_WINDOW_X;
    impl_->SetTouchPoint(touchPoints);

    float windowX = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowX(component_, TEST_POINT_INDEX, &windowX), SUCCESS_RESULT);
    EXPECT_FLOAT_EQ(windowX, TEST_WINDOW_X);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointWindowY_NullParams
 * @tc.desc: Test GetTouchPointWindowY returns BAD_PARAMETER when component or windowY is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointWindowY_NullParams, TestSize.Level1)
{
    float windowY = 0.0f;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowY(nullptr, TEST_POINT_INDEX, &windowY), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowY(component_, TEST_POINT_INDEX, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointWindowY_Success
 * @tc.desc: Test GetTouchPointWindowY returns SUCCESS and retrieves correct value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointWindowY_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].windowY = TEST_WINDOW_Y;
    impl_->SetTouchPoint(touchPoints);

    float windowY = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowY(component_, TEST_POINT_INDEX, &windowY), SUCCESS_RESULT);
    EXPECT_FLOAT_EQ(windowY, TEST_WINDOW_Y);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointDisplayX_NullParams
 * @tc.desc: Test GetTouchPointDisplayX returns BAD_PARAMETER when component or displayX is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointDisplayX_NullParams, TestSize.Level1)
{
    float displayX = 0.0f;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayX(nullptr, TEST_POINT_INDEX, &displayX), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayX(component_, TEST_POINT_INDEX, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointDisplayX_Success
 * @tc.desc: Test GetTouchPointDisplayX returns SUCCESS and retrieves correct value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointDisplayX_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].displayX = TEST_DISPLAY_X;
    impl_->SetTouchPoint(touchPoints);

    float displayX = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayX(component_, TEST_POINT_INDEX, &displayX), SUCCESS_RESULT);
    EXPECT_FLOAT_EQ(displayX, TEST_DISPLAY_X);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointDisplayY_NullParams
 * @tc.desc: Test GetTouchPointDisplayY returns BAD_PARAMETER when component or displayY is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointDisplayY_NullParams, TestSize.Level1)
{
    float displayY = 0.0f;

    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayY(nullptr, TEST_POINT_INDEX, &displayY), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayY(component_, TEST_POINT_INDEX, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchPointDisplayY_Success
 * @tc.desc: Test GetTouchPointDisplayY returns SUCCESS and retrieves correct value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchPointDisplayY_Success, TestSize.Level1)
{
    std::vector<XComponentTouchPoint> touchPoints(1);
    touchPoints[0].displayY = TEST_DISPLAY_Y;
    impl_->SetTouchPoint(touchPoints);

    float displayY = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayY(component_, TEST_POINT_INDEX, &displayY), SUCCESS_RESULT);
    EXPECT_FLOAT_EQ(displayY, TEST_DISPLAY_Y);
}

/**
 * @tc.name: NativeXComponent_RegisterCallback_NullParams
 * @tc.desc: Test RegisterCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterCallback_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_Callback callback = {};

    EXPECT_EQ(OH_NativeXComponent_RegisterCallback(nullptr, &callback), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterCallback_Success
 * @tc.desc: Test RegisterCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterCallback_Success, TestSize.Level1)
{
    OH_NativeXComponent_Callback callback = {};
    callback.OnSurfaceCreated = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterCallback(component_, &callback), SUCCESS_RESULT);
    EXPECT_NE(impl_->GetCallback(), nullptr);
}

/**
 * @tc.name: NativeXComponent_RegisterMouseEventCallback_NullParams
 * @tc.desc: Test RegisterMouseEventCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterMouseEventCallback_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_MouseEvent_Callback callback = {};

    EXPECT_EQ(OH_NativeXComponent_RegisterMouseEventCallback(nullptr, &callback), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterMouseEventCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterMouseEventCallback_Success
 * @tc.desc: Test RegisterMouseEventCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterMouseEventCallback_Success, TestSize.Level1)
{
    OH_NativeXComponent_MouseEvent_Callback callback = {};
    callback.DispatchMouseEvent = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterMouseEventCallback(component_, &callback), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterFocusEventCallback_NullParams
 * @tc.desc: Test RegisterFocusEventCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterFocusEventCallback_NullParams, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterFocusEventCallback(nullptr, cb), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterFocusEventCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterFocusEventCallback_Success
 * @tc.desc: Test RegisterFocusEventCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterFocusEventCallback_Success, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterFocusEventCallback(component_, cb), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterKeyEventCallback_NullParams
 * @tc.desc: Test RegisterKeyEventCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterKeyEventCallback_NullParams, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallback(nullptr, cb), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterKeyEventCallback_Success
 * @tc.desc: Test RegisterKeyEventCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterKeyEventCallback_Success, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallback(component_, cb), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterBlurEventCallback_NullParams
 * @tc.desc: Test RegisterBlurEventCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterBlurEventCallback_NullParams, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterBlurEventCallback(nullptr, cb), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterBlurEventCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterBlurEventCallback_Success
 * @tc.desc: Test RegisterBlurEventCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterBlurEventCallback_Success, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterBlurEventCallback(component_, cb), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEvent_NullParams
 * @tc.desc: Test GetKeyEvent returns BAD_PARAMETER when component or keyEvent is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEvent_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent* keyEvent = nullptr;

    EXPECT_EQ(OH_NativeXComponent_GetKeyEvent(nullptr, &keyEvent), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEvent(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEvent_Success
 * @tc.desc: Test GetKeyEvent returns SUCCESS and retrieves key event
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEvent_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent srcEvent = {};
    srcEvent.action = OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN;
    srcEvent.code = KEY_A;
    srcEvent.deviceId = TEST_DEVICE_ID;
    impl_->SetKeyEvent(srcEvent);

    OH_NativeXComponent_KeyEvent* keyEvent = nullptr;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEvent(component_, &keyEvent), SUCCESS_RESULT);
    ASSERT_NE(keyEvent, nullptr);
    EXPECT_EQ(keyEvent->action, OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN);
    EXPECT_EQ(keyEvent->code, KEY_A);
    EXPECT_EQ(keyEvent->deviceId, TEST_DEVICE_ID);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventAction_NullParams
 * @tc.desc: Test GetKeyEventAction returns BAD_PARAMETER when keyEvent or action is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventAction_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_KeyAction action = OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventAction(nullptr, &action), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventAction(&keyEvent, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventAction_Success
 * @tc.desc: Test GetKeyEventAction returns SUCCESS and retrieves correct action value
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventAction_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.action = OH_NATIVEXCOMPONENT_KEY_ACTION_UP;

    OH_NativeXComponent_KeyAction action = OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventAction(&keyEvent, &action), SUCCESS_RESULT);
    EXPECT_EQ(action, OH_NATIVEXCOMPONENT_KEY_ACTION_UP);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventCode_NullParams
 * @tc.desc: Test GetKeyEventCode returns BAD_PARAMETER when keyEvent or code is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventCode_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_KeyCode code = KEY_UNKNOWN;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCode(nullptr, &code), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCode(&keyEvent, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventCode_Success
 * @tc.desc: Test GetKeyEventCode returns SUCCESS and retrieves correct key code
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventCode_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.code = KEY_ENTER;

    OH_NativeXComponent_KeyCode code = KEY_UNKNOWN;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCode(&keyEvent, &code), SUCCESS_RESULT);
    EXPECT_EQ(code, KEY_ENTER);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventSourceType_NullParams
 * @tc.desc: Test GetKeyEventSourceType returns BAD_PARAMETER when keyEvent or sourceType is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventSourceType_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventSourceType(nullptr, &sourceType), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventSourceType(&keyEvent, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventSourceType_Success
 * @tc.desc: Test GetKeyEventSourceType returns SUCCESS and retrieves correct source type
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventSourceType_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD;

    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventSourceType(&keyEvent, &sourceType), SUCCESS_RESULT);
    EXPECT_EQ(sourceType, OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventDeviceId_NullParams
 * @tc.desc: Test GetKeyEventDeviceId returns BAD_PARAMETER when keyEvent or deviceId is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventDeviceId_NullParams, TestSize.Level1)
{
    int64_t deviceId = 0;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventDeviceId(nullptr, &deviceId), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventDeviceId(&keyEvent, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventDeviceId_Success
 * @tc.desc: Test GetKeyEventDeviceId returns SUCCESS and retrieves correct device id
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventDeviceId_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.deviceId = TEST_DEVICE_ID;

    int64_t deviceId = 0;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventDeviceId(&keyEvent, &deviceId), SUCCESS_RESULT);
    EXPECT_EQ(deviceId, TEST_DEVICE_ID);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventTimestamp_NullParams
 * @tc.desc: Test GetKeyEventTimestamp returns BAD_PARAMETER when keyEvent or timestamp is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventTimestamp_NullParams, TestSize.Level1)
{
    int64_t timestamp = 0;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventTimestamp(nullptr, &timestamp), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventTimestamp(&keyEvent, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventTimestamp_Success
 * @tc.desc: Test GetKeyEventTimestamp returns SUCCESS and retrieves correct timestamp
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventTimestamp_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.timestamp = TEST_TIMESTAMP;

    int64_t timestamp = 0;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventTimestamp(&keyEvent, &timestamp), SUCCESS_RESULT);
    EXPECT_EQ(timestamp, TEST_TIMESTAMP);
}

/**
 * @tc.name: NativeXComponent_SetExpectedFrameRateRange_NullParams
 * @tc.desc: Test SetExpectedFrameRateRange returns BAD_PARAMETER when component or range is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_SetExpectedFrameRateRange_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_ExpectedRateRange range = {};

    EXPECT_EQ(OH_NativeXComponent_SetExpectedFrameRateRange(nullptr, &range), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_SetExpectedFrameRateRange(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterOnFrameCallback_NullComponent
 * @tc.desc: Test RegisterOnFrameCallback returns BAD_PARAMETER when component is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterOnFrameCallback_NullComponent, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, uint64_t, uint64_t) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterOnFrameCallback(nullptr, cb), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_UnregisterOnFrameCallback_NullComponent
 * @tc.desc: Test UnregisterOnFrameCallback returns BAD_PARAMETER when component is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_UnregisterOnFrameCallback_NullComponent, TestSize.Level1)
{
    EXPECT_EQ(OH_NativeXComponent_UnregisterOnFrameCallback(nullptr), BAD_PARAMETER_RESULT);

    SUCCEED();
}

/**
 * @tc.name: NativeXComponent_SetNeedSoftKeyboard_NullComponent
 * @tc.desc: Test SetNeedSoftKeyboard returns BAD_PARAMETER when component is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_SetNeedSoftKeyboard_NullComponent, TestSize.Level1)
{
    EXPECT_EQ(OH_NativeXComponent_SetNeedSoftKeyboard(nullptr, true), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_SetNeedSoftKeyboard(nullptr, false), BAD_PARAMETER_RESULT);
    SUCCEED();
}

/**
 * @tc.name: NativeXComponent_SetNeedSoftKeyboard_Success
 * @tc.desc: Test SetNeedSoftKeyboard returns SUCCESS with valid component
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_SetNeedSoftKeyboard_Success, TestSize.Level1)
{
    EXPECT_EQ(OH_NativeXComponent_SetNeedSoftKeyboard(component_, true), SUCCESS_RESULT);
    EXPECT_EQ(OH_NativeXComponent_SetNeedSoftKeyboard(component_, false), SUCCESS_RESULT);
    SUCCEED();
}

/**
 * @tc.name: NativeXComponent_RegisterSurfaceShowCallback_NullParams
 * @tc.desc: Test RegisterSurfaceShowCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterSurfaceShowCallback_NullParams, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterSurfaceShowCallback(nullptr, cb), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterSurfaceShowCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterSurfaceShowCallback_Success
 * @tc.desc: Test RegisterSurfaceShowCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterSurfaceShowCallback_Success, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterSurfaceShowCallback(component_, cb), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterSurfaceHideCallback_NullParams
 * @tc.desc: Test RegisterSurfaceHideCallback returns BAD_PARAMETER when component or callback is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterSurfaceHideCallback_NullParams, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterSurfaceHideCallback(nullptr, cb), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterSurfaceHideCallback(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterSurfaceHideCallback_Success
 * @tc.desc: Test RegisterSurfaceHideCallback returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterSurfaceHideCallback_Success, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterSurfaceHideCallback(component_, cb), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchEventSourceType_NullParams
 * @tc.desc: Test GetTouchEventSourceType returns BAD_PARAMETER when component or sourceType is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchEventSourceType_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;

    EXPECT_EQ(OH_NativeXComponent_GetTouchEventSourceType(nullptr, TEST_POINT_ID, &sourceType),
        BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEventSourceType(component_, TEST_POINT_ID, nullptr),
        BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetTouchEventSourceType_Success
 * @tc.desc: Test GetTouchEventSourceType returns SUCCESS when source type matches point id
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetTouchEventSourceType_Success, TestSize.Level1)
{
    impl_->SetCurrentSourceType({ TEST_POINT_ID, OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN });

    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    EXPECT_EQ(
        OH_NativeXComponent_GetTouchEventSourceType(component_, TEST_POINT_ID, &sourceType), SUCCESS_RESULT);
    EXPECT_EQ(sourceType, OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN);
}

/**
 * @tc.name: NativeXComponent_RegisterKeyEventCallbackWithResult_NullParams
 * @tc.desc: Test RegisterKeyEventCallbackWithResult returns BAD_PARAMETER when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterKeyEventCallbackWithResult_NullParams,
    TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) -> bool { return true; };

    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallbackWithResult(nullptr, cb), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallbackWithResult(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterKeyEventCallbackWithResult_Success
 * @tc.desc: Test RegisterKeyEventCallbackWithResult returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterKeyEventCallbackWithResult_Success, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, void*) -> bool { return true; };

    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallbackWithResult(component_, cb), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetExtraMouseEventInfo_NullParams
 * @tc.desc: Test GetExtraMouseEventInfo returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetExtraMouseEventInfo_NullParams, TestSize.Level1)
{
    OH_NativeXComponent_ExtraMouseEventInfo* info = nullptr;

    EXPECT_EQ(OH_NativeXComponent_GetExtraMouseEventInfo(nullptr, &info), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_GetExtraMouseEventInfo(component_, nullptr), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_GetExtraMouseEventInfo_Success
 * @tc.desc: Test GetExtraMouseEventInfo returns ERROR_CODE_NO_ERROR with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetExtraMouseEventInfo_Success, TestSize.Level1)
{
    OH_NativeXComponent_ExtraMouseEventInfo srcInfo = {};
    srcInfo.modifierKeyStates = TEST_MODIFIER_KEY_STATES;
    impl_->SetExtraMouseEventInfo(srcInfo);

    OH_NativeXComponent_ExtraMouseEventInfo* info = nullptr;
    EXPECT_EQ(OH_NativeXComponent_GetExtraMouseEventInfo(component_, &info), ERROR_CODE_NO_ERROR);
    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->modifierKeyStates, TEST_MODIFIER_KEY_STATES);
}

/**
 * @tc.name: NativeXComponent_GetMouseEventModifierKeyStates_NullParams
 * @tc.desc: Test GetMouseEventModifierKeyStates returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetMouseEventModifierKeyStates_NullParams, TestSize.Level1)
{
    uint64_t keys = 0;
    OH_NativeXComponent_ExtraMouseEventInfo info = {};

    EXPECT_EQ(OH_NativeXComponent_GetMouseEventModifierKeyStates(nullptr, &keys), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_GetMouseEventModifierKeyStates(&info, nullptr), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_GetMouseEventModifierKeyStates_Success
 * @tc.desc: Test GetMouseEventModifierKeyStates returns ERROR_CODE_NO_ERROR with correct key states
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetMouseEventModifierKeyStates_Success, TestSize.Level1)
{
    OH_NativeXComponent_ExtraMouseEventInfo info = {};
    info.modifierKeyStates = TEST_MODIFIER_KEY_STATES;

    uint64_t keys = 0;
    EXPECT_EQ(OH_NativeXComponent_GetMouseEventModifierKeyStates(&info, &keys), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEY_STATES);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventModifierKeyStates_NullParams
 * @tc.desc: Test GetKeyEventModifierKeyStates returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventModifierKeyStates_NullParams, TestSize.Level1)
{
    uint64_t keys = 0;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventModifierKeyStates(nullptr, &keys), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventModifierKeyStates(&keyEvent, nullptr), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventModifierKeyStates_Success
 * @tc.desc: Test GetKeyEventModifierKeyStates returns ERROR_CODE_NO_ERROR with correct key states
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventModifierKeyStates_Success, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.modifierKeyStates = TEST_MODIFIER_KEY_STATES;

    uint64_t keys = 0;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventModifierKeyStates(&keyEvent, &keys), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, TEST_MODIFIER_KEY_STATES);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventNumLockState_NullParams
 * @tc.desc: Test GetKeyEventNumLockState returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventNumLockState_NullParams, TestSize.Level1)
{
    bool isNumLockOn = false;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventNumLockState(nullptr, &isNumLockOn), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventNumLockState(&keyEvent, nullptr), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventNumLockState_True
 * @tc.desc: Test GetKeyEventNumLockState returns correct true state
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventNumLockState_True, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.isNumLockOn = true;

    bool isNumLockOn = false;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventNumLockState(&keyEvent, &isNumLockOn), ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(isNumLockOn);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventNumLockState_False
 * @tc.desc: Test GetKeyEventNumLockState returns correct false state
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventNumLockState_False, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.isNumLockOn = false;

    bool isNumLockOn = true;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventNumLockState(&keyEvent, &isNumLockOn), ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(isNumLockOn);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventCapsLockState_NullParams
 * @tc.desc: Test GetKeyEventCapsLockState returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventCapsLockState_NullParams, TestSize.Level1)
{
    bool isCapsLockOn = false;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCapsLockState(nullptr, &isCapsLockOn), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCapsLockState(&keyEvent, nullptr), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventCapsLockState_True
 * @tc.desc: Test GetKeyEventCapsLockState returns correct true state
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventCapsLockState_True, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.isCapsLockOn = true;

    bool isCapsLockOn = false;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCapsLockState(&keyEvent, &isCapsLockOn), ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(isCapsLockOn);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventCapsLockState_False
 * @tc.desc: Test GetKeyEventCapsLockState returns correct false state
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventCapsLockState_False, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.isCapsLockOn = false;

    bool isCapsLockOn = true;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCapsLockState(&keyEvent, &isCapsLockOn), ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(isCapsLockOn);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventScrollLockState_NullParams
 * @tc.desc: Test GetKeyEventScrollLockState returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventScrollLockState_NullParams, TestSize.Level1)
{
    bool isScrollLockOn = false;
    OH_NativeXComponent_KeyEvent keyEvent = {};

    EXPECT_EQ(OH_NativeXComponent_GetKeyEventScrollLockState(nullptr, &isScrollLockOn), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventScrollLockState(&keyEvent, nullptr), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventScrollLockState_True
 * @tc.desc: Test GetKeyEventScrollLockState returns correct true state
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventScrollLockState_True, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.isScrollLockOn = true;

    bool isScrollLockOn = false;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventScrollLockState(&keyEvent, &isScrollLockOn), ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(isScrollLockOn);
}

/**
 * @tc.name: NativeXComponent_GetKeyEventScrollLockState_False
 * @tc.desc: Test GetKeyEventScrollLockState returns correct false state
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetKeyEventScrollLockState_False, TestSize.Level1)
{
    OH_NativeXComponent_KeyEvent keyEvent = {};
    keyEvent.isScrollLockOn = false;

    bool isScrollLockOn = true;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventScrollLockState(&keyEvent, &isScrollLockOn), ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(isScrollLockOn);
}

/**
 * @tc.name: NativeXComponent_GetNativeXComponent_NullNode
 * @tc.desc: Test GetNativeXComponent returns nullptr when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetNativeXComponent_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_NativeXComponent_GetNativeXComponent(nullptr), nullptr);

    SUCCEED();
}

/**
 * @tc.name: NativeXComponent_GetNativeAccessibilityProvider_NullParams
 * @tc.desc: Test GetNativeAccessibilityProvider returns BAD_PARAMETER when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetNativeAccessibilityProvider_NullParams, TestSize.Level1)
{
    ArkUI_AccessibilityProvider* handle = nullptr;

    EXPECT_EQ(OH_NativeXComponent_GetNativeAccessibilityProvider(nullptr, &handle), BAD_PARAMETER_RESULT);
    EXPECT_EQ(OH_NativeXComponent_GetNativeAccessibilityProvider(component_, nullptr), BAD_PARAMETER_RESULT);
}

/**
 * @tc.name: NativeXComponent_GetNativeAccessibilityProvider_Success
 * @tc.desc: Test GetNativeAccessibilityProvider returns SUCCESS with valid parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_GetNativeAccessibilityProvider_Success, TestSize.Level1)
{
    ArkUI_AccessibilityProvider* handle = nullptr;

    EXPECT_EQ(OH_NativeXComponent_GetNativeAccessibilityProvider(component_, &handle), SUCCESS_RESULT);
}

/**
 * @tc.name: NativeXComponent_RegisterUIInputEventCallback_NullParams
 * @tc.desc: Test RegisterUIInputEventCallback returns ERROR_CODE_PARAM_INVALID when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterUIInputEventCallback_NullParams, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, ArkUI_UIInputEvent*, ArkUI_UIInputEvent_Type) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterUIInputEventCallback(nullptr, cb,
        ARKUI_UIINPUTEVENT_TYPE_AXIS), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_NativeXComponent_RegisterUIInputEventCallback(component_, nullptr,
        ARKUI_UIINPUTEVENT_TYPE_AXIS), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: ArkUI_SurfaceCallback_CreateAndDispose
 * @tc.desc: Test SurfaceCallback create and dispose lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_SurfaceCallback_CreateAndDispose, TestSize.Level1)
{
    OH_ArkUI_SurfaceCallback* callback = OH_ArkUI_SurfaceCallback_Create();
    ASSERT_NE(callback, nullptr);

    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(callback, /* created */
        [](OH_ArkUI_SurfaceHolder*) {});
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(callback, /* changed */
        [](OH_ArkUI_SurfaceHolder*, uint64_t, uint64_t) {});
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(callback, /* destroyed */
        [](OH_ArkUI_SurfaceHolder*) {});
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(callback, /* show */
        [](OH_ArkUI_SurfaceHolder*) {});
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(callback, /* hide */
        [](OH_ArkUI_SurfaceHolder*) {});

    OH_ArkUI_SurfaceCallback_Dispose(callback);
}

/**
 * @tc.name: ArkUI_SurfaceCallback_SetNullCallback
 * @tc.desc: Test SurfaceCallback set events with null callback does not crash
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_SurfaceCallback_SetNullCallback, TestSize.Level1)
{
    OH_ArkUI_SurfaceCallback* callback = OH_ArkUI_SurfaceCallback_Create();
    ASSERT_NE(callback, nullptr);

    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(callback, nullptr);
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(callback, nullptr);
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(callback, nullptr);
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(callback, nullptr);
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(callback, nullptr);

    OH_ArkUI_SurfaceCallback_Dispose(callback);
}

/**
 * @tc.name: ArkUI_SurfaceHolder_UserData_NullHolder
 * @tc.desc: Test SurfaceHolder set/get user data with null holder
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_SurfaceHolder_UserData_NullHolder, TestSize.Level1)
{
    int32_t data = 42;
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_SetUserData(nullptr, &data), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_GetUserData(nullptr), nullptr);
}

/**
 * @tc.name: ArkUI_SurfaceHolder_AddRemoveCallback_NullParams
 * @tc.desc: Test SurfaceHolder add/remove callback with null parameters
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_SurfaceHolder_AddRemoveCallback_NullParams, TestSize.Level1)
{
    OH_ArkUI_SurfaceCallback* callback = OH_ArkUI_SurfaceCallback_Create();
    ASSERT_NE(callback, nullptr);

    EXPECT_EQ(OH_ArkUI_SurfaceHolder_AddSurfaceCallback(nullptr, callback), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(nullptr, callback), ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_SurfaceCallback_Dispose(callback);
}

/**
 * @tc.name: ArkUI_XComponent_GetNativeWindow_NullHolder
 * @tc.desc: Test GetNativeWindow returns nullptr when holder is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_GetNativeWindow_NullHolder, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_GetNativeWindow(nullptr), nullptr);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponentSurfaceConfig_CreateAndDispose
 * @tc.desc: Test XComponentSurfaceConfig create and dispose lifecycle
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponentSurfaceConfig_CreateAndDispose, TestSize.Level1)
{
    ArkUI_XComponentSurfaceConfig* config = OH_ArkUI_XComponentSurfaceConfig_Create();
    ASSERT_NE(config, nullptr);

    OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(config, true);
    OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(config, false);

    OH_ArkUI_XComponentSurfaceConfig_Dispose(config);
}

/**
 * @tc.name: ArkUI_XComponent_StartImageAnalyzer_NullNode
 * @tc.desc: Test StartImageAnalyzer returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_StartImageAnalyzer_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_StartImageAnalyzer(nullptr, nullptr, nullptr), ERROR_CODE_PARAM_INVALID);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_StopImageAnalyzer_NullNode
 * @tc.desc: Test StopImageAnalyzer returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_StopImageAnalyzer_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_StopImageAnalyzer(nullptr), ERROR_CODE_PARAM_INVALID);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_SurfaceHolder_Create_NullNode
 * @tc.desc: Test SurfaceHolder_Create returns nullptr when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_SurfaceHolder_Create_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_Create(nullptr), nullptr);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_AccessibilityProvider_Create_NullNode
 * @tc.desc: Test AccessibilityProvider_Create returns nullptr when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_AccessibilityProvider_Create_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_AccessibilityProvider_Create(nullptr), nullptr);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_SetExpectedFrameRateRange_NullNode
 * @tc.desc: Test SetExpectedFrameRateRange returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_SetExpectedFrameRateRange_NullNode, TestSize.Level1)
{
    OH_NativeXComponent_ExpectedRateRange range = {};
    range.min = TEST_RATE_MIN;
    range.max = TEST_RATE_MAX;
    range.expected = TEST_RATE_EXPECTED;

    EXPECT_EQ(OH_ArkUI_XComponent_SetExpectedFrameRateRange(nullptr, range), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: ArkUI_XComponent_RegisterOnFrameCallback_NullNode
 * @tc.desc: Test RegisterOnFrameCallback returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_RegisterOnFrameCallback_NullNode, TestSize.Level1)
{
    auto cb = [](ArkUI_NodeHandle, uint64_t, uint64_t) {};
    EXPECT_EQ(OH_ArkUI_XComponent_RegisterOnFrameCallback(nullptr, cb), ERROR_CODE_PARAM_INVALID);
    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_UnregisterOnFrameCallback_NullNode
 * @tc.desc: Test UnregisterOnFrameCallback returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_UnregisterOnFrameCallback_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_UnregisterOnFrameCallback(nullptr), ERROR_CODE_PARAM_INVALID);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_SetNeedSoftKeyboard_NullNode
 * @tc.desc: Test SetNeedSoftKeyboard returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_SetNeedSoftKeyboard_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_SetNeedSoftKeyboard(nullptr, true), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_SetNeedSoftKeyboard(nullptr, false), ERROR_CODE_PARAM_INVALID);
    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_SetAutoInitialize_NullNode
 * @tc.desc: Test SetAutoInitialize returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_SetAutoInitialize_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_SetAutoInitialize(nullptr, true), ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_SetAutoInitialize(nullptr, false), ERROR_CODE_PARAM_INVALID);
    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_Initialize_NullNode
 * @tc.desc: Test Initialize returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_Initialize_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_Initialize(nullptr), ERROR_CODE_PARAM_INVALID);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_Finalize_NullNode
 * @tc.desc: Test Finalize returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_Finalize_NullNode, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_Finalize(nullptr), ERROR_CODE_PARAM_INVALID);

    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_IsInitialized_NullNode
 * @tc.desc: Test IsInitialized returns ERROR_CODE_PARAM_INVALID when node is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_IsInitialized_NullNode, TestSize.Level1)
{
    bool isInitialized = false;
    EXPECT_EQ(OH_ArkUI_XComponent_IsInitialized(nullptr, &isInitialized), ERROR_CODE_PARAM_INVALID);
    SUCCEED();
}

/**
 * @tc.name: ArkUI_XComponent_IsInitialized_NullIsInitialized
 * @tc.desc: Test IsInitialized returns ERROR_CODE_PARAM_INVALID when isInitialized is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, ArkUI_XComponent_IsInitialized_NullIsInitialized, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_XComponent_IsInitialized(nullptr, nullptr), ERROR_CODE_PARAM_INVALID);

    SUCCEED();
}

/**
 * @tc.name: NativeXComponent_RegisterUIInputEventCallback_NonAxisType
 * @tc.desc: Test RegisterUIInputEventCallback returns ERROR_CODE_PARAM_INVALID when type is not AXIS
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_RegisterUIInputEventCallback_NonAxisType, TestSize.Level1)
{
    auto cb = [](OH_NativeXComponent*, ArkUI_UIInputEvent*, ArkUI_UIInputEvent_Type) {};

    EXPECT_EQ(OH_NativeXComponent_RegisterUIInputEventCallback(component_, cb,
        ARKUI_UIINPUTEVENT_TYPE_TOUCH), ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeXComponent_AttachNativeRootNode_NullParams
 * @tc.desc: Test AttachNativeRootNode returns BAD_PARAMETER when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_AttachNativeRootNode_NullParams, TestSize.Level1)
{
    EXPECT_EQ(OH_NativeXComponent_AttachNativeRootNode(nullptr, nullptr), BAD_PARAMETER_RESULT);

    SUCCEED();
}

/**
 * @tc.name: NativeXComponent_DetachNativeRootNode_NullParams
 * @tc.desc: Test DetachNativeRootNode returns BAD_PARAMETER when params are nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeInterfaceXComponentTestNg, NativeXComponent_DetachNativeRootNode_NullParams, TestSize.Level1)
{
    EXPECT_EQ(OH_NativeXComponent_DetachNativeRootNode(nullptr, nullptr), BAD_PARAMETER_RESULT);

    SUCCEED();
}
} // namespace OHOS::Ace::NG
