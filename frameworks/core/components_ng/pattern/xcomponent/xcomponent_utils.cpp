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

#include "core/components_ng/pattern/xcomponent/xcomponent_utils.h"

#include "core/components/xcomponent/native_interface_xcomponent_impl.h"

namespace OHOS::Ace::NG {
float XComponentUtils::RoundValueToPixelGrid(float value, bool isRound, bool forceCeil, bool forceFloor)
{
    float fractials = fmod(value, 1.0f);
    if (fractials < 0.0f) {
        ++fractials;
    }
    if (forceCeil) {
        return (value - fractials + 1.0f);
    } else if (forceFloor) {
        return (value - fractials);
    } else if (isRound) {
        if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.50f)) {
            return (value - fractials + 1.0f);
        } else {
            return (value - fractials);
        }
    }
    return value;
}

RectF XComponentUtils::AdjustPaintRect(float positionX, float positionY, float width, float height, bool isRound)
{
    RectF rect;
    float relativeLeft = positionX;
    float relativeTop = positionY;
    float nodeWidth = width;
    float nodeHeight = height;
    float absoluteRight = relativeLeft + nodeWidth;
    float absoluteBottom = relativeTop + nodeHeight;
    float roundToPixelErrorX = 0;
    float roundToPixelErrorY = 0;

    float nodeLeftI = RoundValueToPixelGrid(relativeLeft, isRound, false, false);
    float nodeTopI = RoundValueToPixelGrid(relativeTop, isRound, false, false);
    roundToPixelErrorX += nodeLeftI - relativeLeft;
    roundToPixelErrorY += nodeTopI - relativeTop;
    rect.SetLeft(nodeLeftI);
    rect.SetTop(nodeTopI);

    float nodeWidthI = RoundValueToPixelGrid(absoluteRight, isRound, false, false) - nodeLeftI;
    float nodeWidthTemp = RoundValueToPixelGrid(nodeWidth, isRound, false, false);
    roundToPixelErrorX += nodeWidthI - nodeWidth;
    if (roundToPixelErrorX > 0.5f) {
        nodeWidthI -= 1.0f;
        roundToPixelErrorX -= 1.0f;
    }
    if (roundToPixelErrorX < -0.5f) {
        nodeWidthI += 1.0f;
        roundToPixelErrorX += 1.0f;
    }
    if (nodeWidthI < nodeWidthTemp) {
        roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
        nodeWidthI = nodeWidthTemp;
    }

    float nodeHeightI = RoundValueToPixelGrid(absoluteBottom, isRound, false, false) - nodeTopI;
    float nodeHeightTemp = RoundValueToPixelGrid(nodeHeight, isRound, false, false);
    roundToPixelErrorY += nodeHeightI - nodeHeight;
    if (roundToPixelErrorY > 0.5f) {
        nodeHeightI -= 1.0f;
        roundToPixelErrorY -= 1.0f;
    }
    if (roundToPixelErrorY < -0.5f) {
        nodeHeightI += 1.0f;
        roundToPixelErrorY += 1.0f;
    }
    if (nodeHeightI < nodeHeightTemp) {
        roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
        nodeHeightI = nodeHeightTemp;
    }

    rect.SetWidth(nodeWidthI);
    rect.SetHeight(nodeHeightI);
    return rect;
}

std::string XComponentUtils::XComponentRenderFitToString(RenderFit renderFit)
{
    static const std::string renderFitStyles[] = { "RenderFit.CENTER", "RenderFit.TOP", "RenderFit.BOTTOM",
        "RenderFit.LEFT", "RenderFit.RIGHT", "RenderFit.TOP_LEFT", "RenderFit.TOP_RIGHT", "RenderFit.BOTTOM_LEFT",
        "RenderFit.BOTTOM_RIGHT", "RenderFit.RESIZE_FILL", "RenderFit.RESIZE_CONTAIN",
        "RenderFit.RESIZE_CONTAIN_TOP_LEFT", "RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT", "RenderFit.RESIZE_COVER",
        "RenderFit.RESIZE_COVER_TOP_LEFT", "RenderFit.RESIZE_COVER_BOTTOM_RIGHT" };
    return renderFitStyles[static_cast<int>(renderFit)];
}

OH_NativeXComponent_MouseEventAction XComponentUtils::ConvertNativeXComponentMouseEventAction(MouseAction mouseAction)
{
    switch (mouseAction) {
        case MouseAction::PRESS:
            return OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_PRESS;
        case MouseAction::RELEASE:
            return OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_RELEASE;
        case MouseAction::MOVE:
            return OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_MOVE;
        case MouseAction::CANCEL:
            return OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_CANCEL;
        default:
            return OH_NativeXComponent_MouseEventAction::OH_NATIVEXCOMPONENT_MOUSE_NONE;
    }
}

OH_NativeXComponent_MouseEventButton XComponentUtils::ConvertNativeXComponentMouseEventButton(MouseButton mouseButton)
{
    switch (mouseButton) {
        case MouseButton::LEFT_BUTTON:
            return OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_LEFT_BUTTON;
        case MouseButton::RIGHT_BUTTON:
            return OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_RIGHT_BUTTON;
        case MouseButton::MIDDLE_BUTTON:
            return OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_MIDDLE_BUTTON;
        case MouseButton::BACK_BUTTON:
            return OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_BACK_BUTTON;
        case MouseButton::FORWARD_BUTTON:
            return OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_FORWARD_BUTTON;
        default:
            return OH_NativeXComponent_MouseEventButton::OH_NATIVEXCOMPONENT_NONE_BUTTON;
    }
}

OH_NativeXComponent_TouchEventType XComponentUtils::ConvertNativeXComponentTouchEvent(const TouchType& touchType)
{
    switch (touchType) {
        case TouchType::DOWN:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_DOWN;
        case TouchType::UP:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UP;
        case TouchType::MOVE:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_MOVE;
        case TouchType::CANCEL:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_CANCEL;
        default:
            return OH_NativeXComponent_TouchEventType::OH_NATIVEXCOMPONENT_UNKNOWN;
    }
}

OH_NativeXComponent_TouchPointToolType XComponentUtils::ConvertNativeXComponentTouchToolType(const SourceTool& toolType)
{
    switch (toolType) {
        case SourceTool::FINGER:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER;
        case SourceTool::PEN:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN;
        case SourceTool::RUBBER:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER;
        case SourceTool::BRUSH:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH;
        case SourceTool::PENCIL:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL;
        case SourceTool::AIRBRUSH:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH;
        case SourceTool::MOUSE:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE;
        case SourceTool::LENS:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS;
        default:
            return OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    }
}

OH_NativeXComponent_KeyAction XComponentUtils::ConvertNativeXComponentKeyAction(const KeyAction& keyAction)
{
    switch (keyAction) {
        case KeyAction::DOWN:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN;
        case KeyAction::UP:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UP;
        default:
            return OH_NativeXComponent_KeyAction::OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    }
}

OH_NativeXComponent_EventSourceType XComponentUtils::ConvertNativeXComponentEventSourceType(
    const SourceType& sourceType)
{
    switch (sourceType) {
        case SourceType::MOUSE:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE;
        case SourceType::TOUCH:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN;
        case SourceType::TOUCH_PAD:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD;
        case SourceType::KEYBOARD:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD;
        default:
            return OH_NativeXComponent_EventSourceType::OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    }
}

OH_NativeXComponent_KeyEvent XComponentUtils::ConvertNativeXComponentKeyEvent(const KeyEvent& event)
{
    OH_NativeXComponent_KeyEvent nativeKeyEvent;
    nativeKeyEvent.action = ConvertNativeXComponentKeyAction(event.action);
    nativeKeyEvent.code = static_cast<OH_NativeXComponent_KeyCode>(event.code);
    nativeKeyEvent.sourceType = ConvertNativeXComponentEventSourceType(event.sourceType);
    nativeKeyEvent.deviceId = event.deviceId;
    nativeKeyEvent.timestamp = event.timeStamp.time_since_epoch().count();
    return nativeKeyEvent;
}

ArkUI_XComponent_ImageAnalyzerState XComponentUtils::ConvertNativeXComponentAnalyzerStatus(
    const ImageAnalyzerState state)
{
    switch (state) {
        case ImageAnalyzerState::UNSUPPORTED:
            return ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED;
        case ImageAnalyzerState::ONGOING:
            return ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING;
        case ImageAnalyzerState::STOPPED:
            return ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_STOPPED;
        case ImageAnalyzerState::FINISHED:
            return ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_FINISHED;
        default:
            return ArkUI_XComponent_ImageAnalyzerState::ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED;
    }
}
} // namespace OHOS::Ace::NG
