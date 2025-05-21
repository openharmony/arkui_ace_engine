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

#include <chrono>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class XComponentUtilsTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();

protected:
    static RefPtr<FrameNode> CreateXComponentNode(TestProperty& testProperty);
};

void XComponentUtilsTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void XComponentUtilsTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}
/**
 * @tc.name: RoundValueToPixelGridTest
 * @tc.desc: Test RoundValueToPixelGrid Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, RoundValueToPixelGridTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test forceCeil
     * @tc.expected: ret = 2.0f
     */
    float value = 1.0f;
    float ret = XComponentUtils::RoundValueToPixelGrid(value, true, true, true);
    EXPECT_EQ(ret, 2.0f);

    /**
     * @tc.step2: Test isRound when value is positive
     * @tc.expected: ret = 2.0f
     */
    value = 1.5f;
    ret = XComponentUtils::RoundValueToPixelGrid(value, true, false, false);
    EXPECT_EQ(ret, 2.0f);

    /**
     * @tc.step3: Test isRound when value is negative
     * @tc.expected: ret = -2.0f
     */
    value = -1.6f;
    ret = XComponentUtils::RoundValueToPixelGrid(value, true, false, false);
    EXPECT_EQ(ret, -2.0f);

    /**
     * @tc.step4: Do Nothing
     * @tc.expected: ret = value
     */
    value = 1.0f;
    ret = XComponentUtils::RoundValueToPixelGrid(value, false, false, false);
    EXPECT_EQ(ret, 1.0f);
}

/**
 * @tc.name: AdjustPaintRectTest
 * @tc.desc: Test AdjustPaintRect Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, AdjustPaintRectTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test AdjustPaintRect when No Round
     * @tc.expected: result.Left() = 10.5f, result.Top() = 20.5f, result.Width() = 50.5f, result.Height() = 60.5f
     */
    RectF result = XComponentUtils::AdjustPaintRect(10.5f, 20.5f, 50.5f, 60.5f, false);
    EXPECT_FLOAT_EQ(result.Left(), 10.5f);
    EXPECT_FLOAT_EQ(result.Top(), 20.5f);
    EXPECT_FLOAT_EQ(result.Width(), 50.5f);
    EXPECT_FLOAT_EQ(result.Height(), 60.5f);

    /**
     * @tc.step2: Test AdjustPaintRect when Round
     * @tc.expected: result.Left() = 11.0f, result.Top() = 21.0f, result.Width() = 51.0f, result.Height() = 61.0f
     */
    result = XComponentUtils::AdjustPaintRect(10.5f, 20.5f, 50.5f, 60.5f, true);
    EXPECT_FLOAT_EQ(result.Left(), 11.0f);
    EXPECT_FLOAT_EQ(result.Top(), 21.0f);
    EXPECT_FLOAT_EQ(result.Width(), 51.0f);
    EXPECT_FLOAT_EQ(result.Height(), 61.0f);

    /**
     * @tc.step3: Test AdjustPaintRect when RoundError Exceeds Threshold
     * @tc.expected: result.Left() = 11.0f, result.Top() = 21.0f, result.Width() = 51.0f, result.Height() = 61.0f
     */
    result = XComponentUtils::AdjustPaintRect(10.6f, 20.6f, 50.6f, 60.6f, true);
    EXPECT_FLOAT_EQ(result.Left(), 11.0f);
    EXPECT_FLOAT_EQ(result.Top(), 21.0f);
    EXPECT_FLOAT_EQ(result.Width(), 51.0f);
    EXPECT_FLOAT_EQ(result.Height(), 61.0f);

    /**
     * @tc.step4: Test AdjustPaintRect when RoundError is Negative
     * @tc.expected: result.Left() = 10.0f, result.Top() = 20.0f, result.Width() = 51.0f, result.Height() = 61.0f
     */
    result = XComponentUtils::AdjustPaintRect(10.4f, 20.4f, 50.4f, 60.4f, true);
    EXPECT_FLOAT_EQ(result.Left(), 10.0f);
    EXPECT_FLOAT_EQ(result.Top(), 20.0f);
    EXPECT_FLOAT_EQ(result.Width(), 51.0f);
    EXPECT_FLOAT_EQ(result.Height(), 61.0f);

    /**
     * @tc.step5: Test AdjustPaintRect when adjusted size is smaller than expected
     * @tc.expected: result.Left() = 10.0f, result.Top() = 20.0f, result.Width() = 49.0f, result.Height() = 59.0f
     */
    result = XComponentUtils::AdjustPaintRect(10.0f, 20.0f, 49.0f, 59.0f, true);
    EXPECT_FLOAT_EQ(result.Left(), 10.0f);
    EXPECT_FLOAT_EQ(result.Top(), 20.0f);
    EXPECT_FLOAT_EQ(result.Width(), 49.0f);
    EXPECT_FLOAT_EQ(result.Height(), 59.0f);
}

/**
 * @tc.name: XComponentRenderFitToStringTest001
 * @tc.desc: Test XComponentRenderFitToString Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, XComponentRenderFitToStringTest001, TestSize.Level1)
{
    /**
     * @tc.step1: Test XComponentRenderFitToString when RenderFit is CENTER
     * @tc.expected: result = RenderFit.CENTER
     */
    std::string result = XComponentUtils::XComponentRenderFitToString(RenderFit::CENTER);
    EXPECT_EQ(result, "RenderFit.CENTER");

    /**
     * @tc.step2: Test XComponentRenderFitToString when RenderFit is TOP
     * @tc.expected: result = RenderFit.TOP
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::TOP);
    EXPECT_EQ(result, "RenderFit.TOP");

    /**
     * @tc.step3: Test XComponentRenderFitToString when RenderFit is BOTTOM
     * @tc.expected: result = RenderFit.BOTTOM
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::BOTTOM);
    EXPECT_EQ(result, "RenderFit.BOTTOM");

    /**
     * @tc.step4: Test XComponentRenderFitToString when RenderFit is LEFT
     * @tc.expected: result = RenderFit.LEFT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::LEFT);
    EXPECT_EQ(result, "RenderFit.LEFT");

    /**
     * @tc.step5: Test XComponentRenderFitToString when RenderFit is RIGHT
     * @tc.expected: result = RenderFit.RIGHT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RIGHT);
    EXPECT_EQ(result, "RenderFit.RIGHT");

    /**
     * @tc.step6: Test XComponentRenderFitToString when RenderFit is TOP_LEFT
     * @tc.expected: result = RenderFit.TOP_LEFT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::TOP_LEFT);
    EXPECT_EQ(result, "RenderFit.TOP_LEFT");
}

/**
 * @tc.name: XComponentRenderFitToStringTest002
 * @tc.desc: Test XComponentRenderFitToString Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, XComponentRenderFitToStringTest002, TestSize.Level1)
{
    /**
     * @tc.step1: Test XComponentRenderFitToString when RenderFit is TOP_RIGHT
     * @tc.expected: result = RenderFit.TOP_RIGHT
     */
    std::string result = XComponentUtils::XComponentRenderFitToString(RenderFit::TOP_RIGHT);
    EXPECT_EQ(result, "RenderFit.TOP_RIGHT");

    /**
     * @tc.step2: Test XComponentRenderFitToString when RenderFit is BOTTOM_LEFT
     * @tc.expected: result = RenderFit.BOTTOM_LEFT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::BOTTOM_LEFT);
    EXPECT_EQ(result, "RenderFit.BOTTOM_LEFT");

    /**
     * @tc.step3: Test XComponentRenderFitToString when RenderFit is BOTTOM_RIGHT
     * @tc.expected: result = RenderFit.BOTTOM_RIGHT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::BOTTOM_RIGHT);
    EXPECT_EQ(result, "RenderFit.BOTTOM_RIGHT");

    /**
     * @tc.step4: Test XComponentRenderFitToString when RenderFit is RESIZE_FILL
     * @tc.expected: result = RenderFit.RESIZE_FILL
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_FILL);
    EXPECT_EQ(result, "RenderFit.RESIZE_FILL");

    /**
     * @tc.step5: Test XComponentRenderFitToString when RenderFit is RESIZE_CONTAIN
     * @tc.expected: result = RenderFit.RESIZE_CONTAIN
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_CONTAIN);
    EXPECT_EQ(result, "RenderFit.RESIZE_CONTAIN");

    /**
     * @tc.step6: Test XComponentRenderFitToString when RenderFit is RESIZE_CONTAIN_TOP_LEFT
     * @tc.expected: result = RenderFit.RESIZE_CONTAIN_TOP_LEFT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_CONTAIN_TOP_LEFT);
    EXPECT_EQ(result, "RenderFit.RESIZE_CONTAIN_TOP_LEFT");
}

/**
 * @tc.name: XComponentRenderFitToStringTest003
 * @tc.desc: Test XComponentRenderFitToString Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, XComponentRenderFitToStringTest003, TestSize.Level1)
{
    /**
     * @tc.step1: Test XComponentRenderFitToString when RenderFit is RESIZE_CONTAIN_BOTTOM_RIGHT
     * @tc.expected: result = RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT
     */
    std::string result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_CONTAIN_BOTTOM_RIGHT);
    EXPECT_EQ(result, "RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT");

    /**
     * @tc.step2: Test XComponentRenderFitToString when RenderFit is RESIZE_COVER
     * @tc.expected: result = RenderFit.RESIZE_COVER
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_COVER);
    EXPECT_EQ(result, "RenderFit.RESIZE_COVER");

    /**
     * @tc.step3: Test XComponentRenderFitToString when RenderFit is RESIZE_COVER_TOP_LEFT
     * @tc.expected: result = RenderFit.RESIZE_COVER_TOP_LEFT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_COVER_TOP_LEFT);
    EXPECT_EQ(result, "RenderFit.RESIZE_COVER_TOP_LEFT");

    /**
     * @tc.step4: Test XComponentRenderFitToString when RenderFit is RESIZE_COVER_BOTTOM_RIGHT
     * @tc.expected: result = RenderFit.RESIZE_COVER_BOTTOM_RIGHT
     */
    result = XComponentUtils::XComponentRenderFitToString(RenderFit::RESIZE_COVER_BOTTOM_RIGHT);
    EXPECT_EQ(result, "RenderFit.RESIZE_COVER_BOTTOM_RIGHT");
}

/**
 * @tc.name: ConvertNativeXComponentMouseEventActionTest
 * @tc.desc: Test ConvertNativeXComponentMouseEventAction Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentMouseEventActionTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentMouseEventAction when mouseAction is PRESS
     * @tc.expected: result = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_PRESS
     */
    OH_NativeXComponent_MouseEventAction result =
        XComponentUtils::ConvertNativeXComponentMouseEventAction(MouseAction::PRESS);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_PRESS);

    /**
     * @tc.step2: Test ConvertNativeXComponentMouseEventAction when mouseAction is RELEASE
     * @tc.expected: result = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_RELEASE
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventAction(MouseAction::RELEASE);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_RELEASE);

    /**
     * @tc.step3: Test ConvertNativeXComponentMouseEventAction when mouseAction is MOVE
     * @tc.expected: result = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_MOVE
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventAction(MouseAction::MOVE);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_MOVE);

    /**
     * @tc.step4: Test ConvertNativeXComponentMouseEventAction when mouseAction is CANCEL
     * @tc.expected: result = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_CANCEL
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventAction(MouseAction::CANCEL);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_CANCEL);

    /**
     * @tc.step5: Test ConvertNativeXComponentMouseEventAction when unknown MouseAction enum value
     * @tc.expected: result = OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_NONE
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventAction(static_cast<MouseAction>(20));
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_NONE);
}

/**
 * @tc.name: ConvertNativeXComponentMouseEventButtonTest
 * @tc.desc: Test ConvertNativeXComponentMouseEventButton Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentMouseEventButtonTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentMouseEventButton when mouseButton is LEFT_BUTTON
     * @tc.expected: result = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_LEFT_BUTTON
     */
    OH_NativeXComponent_MouseEventButton result =
        XComponentUtils::ConvertNativeXComponentMouseEventButton(MouseButton::LEFT_BUTTON);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_LEFT_BUTTON);

    /**
     * @tc.step2: Test ConvertNativeXComponentMouseEventButton when mouseButton is RIGHT_BUTTON
     * @tc.expected: result = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_RIGHT_BUTTON
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventButton(MouseButton::RIGHT_BUTTON);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_RIGHT_BUTTON);

    /**
     * @tc.step3: Test ConvertNativeXComponentMouseEventButton when mouseButton is MIDDLE_BUTTON
     * @tc.expected: result = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_MIDDLE_BUTTON
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventButton(MouseButton::MIDDLE_BUTTON);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_MIDDLE_BUTTON);

    /**
     * @tc.step4: Test ConvertNativeXComponentMouseEventButton when mouseButton is BACK_BUTTON
     * @tc.expected: result = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_BACK_BUTTON
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventButton(MouseButton::BACK_BUTTON);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_BACK_BUTTON);

    /**
     * @tc.step5: Test ConvertNativeXComponentMouseEventButton when mouseButton is FORWARD_BUTTON
     * @tc.expected: result = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_FORWARD_BUTTON
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventButton(MouseButton::FORWARD_BUTTON);
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_FORWARD_BUTTON);

    /**
     * @tc.step6: Test ConvertNativeXComponentMouseEventButton when unknown MouseButton enum value
     * @tc.expected: result = OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON
     */
    result = XComponentUtils::ConvertNativeXComponentMouseEventButton(static_cast<MouseButton>(6));
    EXPECT_EQ(result, OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON);
}

/**
 * @tc.name: ConvertNativeXComponentTouchEventTest
 * @tc.desc: Test ConvertNativeXComponentTouchEvent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentTouchEventTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentTouchEvent when touchType is DOWN
     * @tc.expected: result = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_DOWN
     */
    OH_NativeXComponent_TouchEventType result = XComponentUtils::ConvertNativeXComponentTouchEvent(TouchType::DOWN);
    EXPECT_EQ(result, OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_DOWN);

    /**
     * @tc.step2: Test ConvertNativeXComponentTouchEvent when touchType is UP
     * @tc.expected: result = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP
     */
    result = XComponentUtils::ConvertNativeXComponentTouchEvent(TouchType::UP);
    EXPECT_EQ(result, OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP);

    /**
     * @tc.step3: Test ConvertNativeXComponentTouchEvent when touchType is MOVE
     * @tc.expected: result = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_MOVE
     */
    result = XComponentUtils::ConvertNativeXComponentTouchEvent(TouchType::MOVE);
    EXPECT_EQ(result, OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_MOVE);

    /**
     * @tc.step4: Test ConvertNativeXComponentTouchEvent when touchType is CANCEL
     * @tc.expected: result = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_CANCEL
     */
    result = XComponentUtils::ConvertNativeXComponentTouchEvent(TouchType::CANCEL);
    EXPECT_EQ(result, OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_CANCEL);

    /**
     * @tc.step5: Test ConvertNativeXComponentTouchEvent when unknown touchType enum value
     * @tc.expected: result = OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN
     */
    result = XComponentUtils::ConvertNativeXComponentTouchEvent(static_cast<TouchType>(5));
    EXPECT_EQ(result, OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN);
}
/**
 * @tc.name: ConvertNativeXComponentTouchToolTypeTest001
 * @tc.desc: Test ConvertNativeXComponentTouchToolType Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentTouchToolTypeTest001, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentTouchToolType when SourceTool is FINGER
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER
     */
    auto result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::FINGER);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER);

    /**
     * @tc.step2: Test ConvertNativeXComponentTouchToolType when SourceTool is PEN
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::PEN);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN);

    /**
     * @tc.step3: Test ConvertNativeXComponentTouchToolType when SourceTool is RUBBER
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::RUBBER);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER);

    /**
     * @tc.step4: Test ConvertNativeXComponentTouchToolType when SourceTool is BRUSH
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::BRUSH);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH);

    /**
     * @tc.step5: Test ConvertNativeXComponentTouchToolType when SourceTool is PENCIL
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::PENCIL);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL);
}

/**
 * @tc.name: ConvertNativeXComponentTouchToolTypeTest002
 * @tc.desc: Test ConvertNativeXComponentTouchToolType Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentTouchToolTypeTest002, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentTouchToolType when SourceTool is AIRBRUSH
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH
     */
    auto result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::AIRBRUSH);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH);

    /**
     * @tc.step2: Test ConvertNativeXComponentTouchToolType when SourceTool is MOUSE
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::MOUSE);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE);

    /**
     * @tc.step3: Test ConvertNativeXComponentTouchToolType when SourceTool is LENS
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(SourceTool::LENS);
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS);

    /**
     * @tc.step4: Test ConvertNativeXComponentTouchToolType when unknown SourceTool enum value
     * @tc.expected: result = OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN
     */
    result = XComponentUtils::ConvertNativeXComponentTouchToolType(static_cast<SourceTool>(20));
    EXPECT_EQ(result, OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN);
}

/**
 * @tc.name: ConvertNativeXComponentKeyActionTest
 * @tc.desc: Test ConvertNativeXComponentKeyAction Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentKeyActionTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentKeyAction when KeyAction is DOWN
     * @tc.expected: result = OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN
     */
    auto result = XComponentUtils::ConvertNativeXComponentKeyAction(KeyAction::DOWN);
    EXPECT_EQ(result, OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN);

    /**
     * @tc.step2: Test ConvertNativeXComponentKeyAction when KeyAction is UP
     * @tc.expected: result = OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UP
     */
    result = XComponentUtils::ConvertNativeXComponentKeyAction(KeyAction::UP);
    EXPECT_EQ(result, OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UP);

    /**
     * @tc.step3: Test ConvertNativeXComponentKeyAction when unknown KeyAction enum value
     * @tc.expected: result = OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN
     */
    result = XComponentUtils::ConvertNativeXComponentKeyAction(static_cast<KeyAction>(10));
    EXPECT_EQ(result, OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN);
}

/**
 * @tc.name: ConvertNativeXComponentEventSourceTypeTest
 * @tc.desc: Test ConvertNativeXComponentEventSourceType Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentEventSourceTypeTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentEventSourceType when SourceType is MOUSE
     * @tc.expected: result = OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE
     */
    auto result = XComponentUtils::ConvertNativeXComponentEventSourceType(SourceType::MOUSE);
    EXPECT_EQ(result, OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE);

    /**
     * @tc.step2: Test ConvertNativeXComponentEventSourceType when SourceType is TOUCH
     * @tc.expected: result = OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN
     */
    result = XComponentUtils::ConvertNativeXComponentEventSourceType(SourceType::TOUCH);
    EXPECT_EQ(result, OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN);

    /**
     * @tc.step3: Test ConvertNativeXComponentEventSourceType when SourceType is TOUCH_PAD
     * @tc.expected: result = OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD
     */
    result = XComponentUtils::ConvertNativeXComponentEventSourceType(SourceType::TOUCH_PAD);
    EXPECT_EQ(result, OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD);

    /**
     * @tc.step4: Test ConvertNativeXComponentEventSourceType when SourceType is KEYBOARD
     * @tc.expected: result = OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD
     */
    result = XComponentUtils::ConvertNativeXComponentEventSourceType(SourceType::KEYBOARD);
    EXPECT_EQ(result, OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD);

    /**
     * @tc.step5: Test ConvertNativeXComponentEventSourceType when unknown SourceType enum value
     * @tc.expected: result = OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN
     */
    result = XComponentUtils::ConvertNativeXComponentEventSourceType(static_cast<SourceType>(10));
    EXPECT_EQ(result, OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN);
}

/**
 * @tc.name: ConvertNativeXComponentKeyEventTest
 * @tc.desc: Test ConvertNativeXComponentKeyEvent Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentKeyEventTest, TestSize.Level1)
{
    /**
     * @tc.step1: Create KeyEvent
     * @tc.expected: Create KeyEvent Successfully
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_CALL;
    event.sourceType = SourceType::KEYBOARD;
    event.deviceId = 123;
    event.timeStamp = std::chrono::high_resolution_clock::now();
    event.pressedCodes = {};
    event.numLock = true;
    event.enableCapsLock = true;
    event.scrollLock = true;

    /**
     * @tc.step2: Call ConvertNativeXComponentKeyEvent Func
     * @tc.expected: Convert NativeXComponentKeyEvent Successfully
     */
    auto nativeKeyEvent = XComponentUtils::ConvertNativeXComponentKeyEvent(event);
    EXPECT_EQ(nativeKeyEvent.action, XComponentUtils::ConvertNativeXComponentKeyAction(event.action));
    EXPECT_EQ(nativeKeyEvent.code, static_cast<OH_NativeXComponent_KeyCode>(event.code));
    EXPECT_EQ(nativeKeyEvent.sourceType, XComponentUtils::ConvertNativeXComponentEventSourceType(event.sourceType));
    EXPECT_EQ(nativeKeyEvent.deviceId, event.deviceId);
    EXPECT_EQ(nativeKeyEvent.timestamp, event.timeStamp.time_since_epoch().count());
    EXPECT_EQ(nativeKeyEvent.modifierKeyStates, 0);
    EXPECT_EQ(nativeKeyEvent.isNumLockOn, true);
    EXPECT_EQ(nativeKeyEvent.isCapsLockOn, true);
    EXPECT_EQ(nativeKeyEvent.isScrollLockOn, true);
}

/**
 * @tc.name: ConvertNativeXComponentAnalyzerStatusTest
 * @tc.desc: Test ConvertNativeXComponentAnalyzerStatus Func
 * @tc.type: FUNC
 */
HWTEST_F(XComponentUtilsTestNg, ConvertNativeXComponentAnalyzerStatusTest, TestSize.Level1)
{
    /**
     * @tc.step1: Test ConvertNativeXComponentAnalyzerStatus when ImageAnalyzerState is UNSUPPORTED
     * @tc.expected: result = ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED
     */
    auto result = XComponentUtils::ConvertNativeXComponentAnalyzerStatus(ImageAnalyzerState::UNSUPPORTED);
    EXPECT_EQ(result, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED);

    /**
     * @tc.step2: Test ConvertNativeXComponentAnalyzerStatus when ImageAnalyzerState is ONGOING
     * @tc.expected: result = ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING
     */
    result = XComponentUtils::ConvertNativeXComponentAnalyzerStatus(ImageAnalyzerState::ONGOING);
    EXPECT_EQ(result, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING);

    /**
     * @tc.step3: Test ConvertNativeXComponentAnalyzerStatus when ImageAnalyzerState is STOPPED
     * @tc.expected: result = ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_STOPPED
     */
    result = XComponentUtils::ConvertNativeXComponentAnalyzerStatus(ImageAnalyzerState::STOPPED);
    EXPECT_EQ(result, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_STOPPED);

    /**
     * @tc.step4: Test ConvertNativeXComponentAnalyzerStatus when ImageAnalyzerState is FINISHED
     * @tc.expected: result = ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_FINISHED
     */
    result = XComponentUtils::ConvertNativeXComponentAnalyzerStatus(ImageAnalyzerState::FINISHED);
    EXPECT_EQ(result, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_FINISHED);

    /**
     * @tc.step5: Test ConvertNativeXComponentAnalyzerStatus when unknown ImageAnalyzerState enum value
     * @tc.expected: result = ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED
     */
    result = XComponentUtils::ConvertNativeXComponentAnalyzerStatus(static_cast<ImageAnalyzerState>(4));
    EXPECT_EQ(result, ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED);
}
} // namespace OHOS::Ace::NG
