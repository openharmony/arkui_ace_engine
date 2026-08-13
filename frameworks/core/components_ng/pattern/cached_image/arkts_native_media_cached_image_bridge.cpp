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
#include "arkts_native_media_cached_image_bridge.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_image.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/cached_image/cached_image_model_ng.h"
 
namespace OHOS::Ace::NG {
const int NUM_0 = 0;
const int NUM_1 = 1;
const int NUM_2 = 2;
const int NUM_3 = 3;
const int NUM_4 = 4;

ArkUINativeModuleValue MediaCachedImageBridge::SetMediaCachedImageSrc(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool flag = secondArg->ToBoolean(vm)->Value();
    if (!flag) {
        // ResourceStr or PixelMap or Drawable type
        Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        std::string src;
        RefPtr<PixelMap> pixmap = nullptr;
        bool isSrcValid = ArkTSUtils::ParseJsMedia(vm, thirdArg, src);
        if (!isSrcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
            Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
            if (Framework::IsDrawable(info[NUM_2])) {
                pixmap = Framework::GetDrawablePixmap(info[NUM_2]);
            } else {
                pixmap = Framework::CreatePixelMapFromNapiValue(info[NUM_2]);
            }
#endif
        }
        CachedImageModelNG::SetCachedImageSrc(reinterpret_cast<FrameNode*>(nativeNode), src, pixmap);
    } else {
        // ASTCResource type
        Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
        Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
        int column = fifthArg->Int32Value(vm);
        Local<panda::ArrayRef> sourcesArray = static_cast<Local<panda::ArrayRef>>(thirdArg);
        int32_t length = fourthArg->Int32Value(vm);
        std::vector<std::string> resSources;
        for (int32_t i = 0; i < length; ++i) {
            Local<JSValueRef> objValue = sourcesArray->GetValueAt(vm, thirdArg, i);
            resSources.push_back(objValue->ToString(vm)->ToString(vm));
        }
        CachedImageModelNG::SetCachedImageASTC(reinterpret_cast<FrameNode*>(nativeNode), resSources, column);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MediaCachedImageBridge::SetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    RefPtr<PixelMap> pixmap = nullptr;
#if defined (PIXEL_MAP_SUPPORTED)
    pixmap = Framework::CreatePixelMapFromNapiValue(info[NUM_1]);
#endif
    if (pixmap) {
        CachedImageModelNG::SetCachedImageAlt(reinterpret_cast<FrameNode*>(nativeNode), pixmap);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MediaCachedImageBridge::ResetAlt(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG