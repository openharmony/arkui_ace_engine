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

#include "frameworks/bridge/declarative_frontend/jsview/js_content_slot.h"

#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_bindings.h"
#include "core/components_ng/syntax/content_slot_model_ng.h"
#include "core/components_ng/syntax/node_content.h"

namespace OHOS::Ace::Framework {

void JSContentSlot::JSBind(BindingTarget globalObj)
{
    JSClass<JSContentSlot>::Declare("ContentSlot");
    JSClass<JSContentSlot>::StaticMethod("create", &JSContentSlot::Create);
    JSClass<JSContentSlot>::StaticMethod("pop", &JSContentSlot::Pop);

    JSClass<JSContentSlot>::Bind<>(globalObj);
}

void JSContentSlot::Create(const JSCallbackInfo& info)
{
    NG::NodeContent* content = nullptr;
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto hasNativePtr = JSRef<JSObject>::Cast(info[0])->HasProperty("nativePtr_");
        if (hasNativePtr) {
            auto nodeContent = JSRef<JSObject>::Cast(info[0])->GetProperty("nativePtr_");
            auto contentHandle = nodeContent.Get().GetLocalHandle();
            content = reinterpret_cast<NG::NodeContent*>(contentHandle->ToNativePointer(info.GetVm())->Value());
        }
    }
    NG::ContentSlotModel::Create(content);
}

void JSContentSlot::Pop() {}

void JSNodeContent::Constructor(const JSCallbackInfo& info)
{
    auto content = Referenced::MakeRefPtr<NG::NodeContent>();
    content->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(content));
}

void JSNodeContent::Destructor(NG::NodeContent* nodeContent)
{
    if (nodeContent != nullptr) {
        nodeContent->DecRefCount();
    }
}

void JSNodeContent::GetNativeContent(const JSCallbackInfo& info)
{
    if (info.Length() != 1 && !info[0]->IsObject()) {
        return;
    }
    auto* nodeContent = JSRef<JSObject>::Cast(info[0])->Unwrap<NG::NodeContent>();
    EcmaVM* vm = info.GetVm();
    info.SetReturnValue(JSRef<JSVal>::Make(panda::NativePointerRef::New(vm, nodeContent)));
}

void JSNodeContent::JSBind(BindingTarget globalObj)
{
    JSClass<NG::NodeContent>::Declare("ArkUINativeNodeContent");
    JSClass<NG::NodeContent>::StaticMethod("getNativeContent", &JSNodeContent::GetNativeContent);
    JSClass<NG::NodeContent>::Bind(globalObj, JSNodeContent::Constructor, JSNodeContent::Destructor);
}

} // namespace OHOS::Ace::Framework
