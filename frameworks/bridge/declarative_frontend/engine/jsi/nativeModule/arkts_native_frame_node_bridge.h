/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_FRAME_NODE_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_FRAME_NODE_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class FrameNodeBridge {
public:
    static ArkUINodeHandle GetFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static Local<panda::ObjectRef> CreateEventTargetObject(EcmaVM* vm, const BaseEventInfo& info);
    static Local<panda::ObjectRef> CreateTouchInfo(
        EcmaVM* vm, const TouchLocationInfo& touchInfo, TouchEventInfo& info);
    static int GetInstanceId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static void SetDrawFunc(const RefPtr<FrameNode>& frameNode, ArkUIRuntimeCallInfo* runtimeCallInfo);
    static Local<panda::ObjectRef> CreateTouchEventInfo(EcmaVM* vm, TouchEventInfo& info);
    static Local<panda::ObjectRef> CreateGestureEventInfo(EcmaVM* vm, GestureEvent& info);
    static Local<panda::ObjectRef> CreateMouseInfo(EcmaVM* vm, MouseInfo& info);
    static ArkUINativeModuleValue MakeFrameNodeInfo(EcmaVM* vm, ArkUINodeHandle frameNode);
    static ArkUINativeModuleValue IsModifiable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue CreateFrameNode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue Invalidate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue AppendChild(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue InsertChildAfter(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RemoveChild(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ClearChildren(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetChildrenCount(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetChild(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetFirst(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetNextSibling(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetPreviousSibling(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetParent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetIdByNodePtr(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetPositionToParent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetPositionToWindow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetMeasuredSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetLayoutPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetConfigBorderWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetConfigPadding(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetConfigMargin(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetConfigSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetNodeType(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue IsVisible(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue IsClipToFrame(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue IsAttached(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetInspectorInfo(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnTouch(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnAppear(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnDisappear(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnKeyEvent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnBlur(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnHover(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnMouse(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnSizeChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue PropertyUpdate(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RegisterFrameCallback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue MarkDirty(ArkUIRuntimeCallInfo* runtimeCallInfo);
};

} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_FRAME_NODE_BRIDGE_H
