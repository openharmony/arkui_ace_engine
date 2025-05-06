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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_UTILS_H

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "core/event/mouse_event.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "interfaces/native/native_interface_xcomponent.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT XComponentUtils : public virtual AceType {
    DECLARE_ACE_TYPE(XComponentUtils, AceType);
public:
    static RectF AdjustPaintRect(float positionX, float positionY, float width, float height, bool isRound);
    static OH_NativeXComponent_MouseEventAction ConvertNativeXComponentMouseEventAction(MouseAction mouseAction);
    static OH_NativeXComponent_MouseEventButton ConvertNativeXComponentMouseEventButton(MouseButton mouseButton);
    static float RoundValueToPixelGrid(float value, bool isRound, bool forceCeil, bool forceFloor);
    static std::string XComponentRenderFitToString(RenderFit renderFit);
    static OH_NativeXComponent_TouchEventType ConvertNativeXComponentTouchEvent(const TouchType& touchType);
    static OH_NativeXComponent_TouchPointToolType ConvertNativeXComponentTouchToolType(const SourceTool& toolType);
    static OH_NativeXComponent_KeyAction ConvertNativeXComponentKeyAction(const KeyAction& keyAction);
    static OH_NativeXComponent_EventSourceType ConvertNativeXComponentEventSourceType(const SourceType& sourceType);
    static OH_NativeXComponent_KeyEvent ConvertNativeXComponentKeyEvent(const KeyEvent& event);
    static ArkUI_XComponent_ImageAnalyzerState ConvertNativeXComponentAnalyzerStatus(const ImageAnalyzerState state);

}; // XComponentUtils
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_UTILS_H
