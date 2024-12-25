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

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_scrollable_bridge.h"

#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue ScrollableBridge::SetContentClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto* node = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[1]->IsObject()) {
        auto* clipShape = Framework::JSRef<Framework::JSObject>::Cast(info[1])->Unwrap<Framework::JSShapeAbstract>();
        if (clipShape) {
            ScrollableModelNG::SetContentClip(reinterpret_cast<FrameNode*>(node), ContentClipMode::CUSTOM,
                AceType::DynamicCast<ShapeRect>(clipShape->GetBasicShape()));
            return panda::JSValueRef::Undefined(vm);
        }
    } else if (info[1]->IsNumber()) {
        GetArkUINodeModifiers()->getScrollableModifier()->setContentClip(node, info[1]->ToNumber<int32_t>());
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUINodeModifiers()->getScrollableModifier()->resetContentClip(node);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ScrollableBridge::ResetContentClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto* node = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getScrollableModifier()->resetContentClip(node);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
