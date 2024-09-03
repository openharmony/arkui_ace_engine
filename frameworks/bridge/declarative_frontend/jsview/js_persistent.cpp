/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_persistent.h"

#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/storage/storage_proxy.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"

namespace OHOS::Ace::Framework {
constexpr int32_t DATA_REQUIRED_ARGS = 2;

void JSPersistent::JSBind(BindingTarget globalObj)
{
    JSClass<JSPersistent>::Declare("Storage");
    JSClass<JSPersistent>::CustomMethod("set", &JSPersistent::Set);
    JSClass<JSPersistent>::CustomMethod("get", &JSPersistent::Get);
    JSClass<JSPersistent>::CustomMethod("has", &JSPersistent::Has);
    JSClass<JSPersistent>::CustomMethod("clear", &JSPersistent::Clear);
    JSClass<JSPersistent>::CustomMethod("delete", &JSPersistent::Delete);
    JSClass<JSPersistent>::Bind(globalObj, JSPersistent::ConstructorCallback, JSPersistent::DestructorCallback);
}

void JSPersistent::ConstructorCallback(const JSCallbackInfo& args)
{
    bool needCrossThread = false;
    if (args.Length() > 0 && args[0]->IsBoolean()) {
        needCrossThread = args[0]->ToBoolean();
    }
    std::string fileName;
    auto persistent = Referenced::MakeRefPtr<JSPersistent>(needCrossThread, fileName);
    persistent->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(persistent));
}

void JSPersistent::DestructorCallback(JSPersistent* persistent)
{
    if (persistent != nullptr) {
        persistent->DecRefCount();
    }
}

void JSPersistent::Set(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < DATA_REQUIRED_ARGS || !args[0]->IsString()) {
        LOGW("JSPersistent: Fail to set persistent data, args too few or key type is not a string");
        return;
    }
    std::string key = args[0]->ToString();
    auto serializedValue = JSON::Stringify(args.GetVm(), args[1].Get().GetLocalHandle());
    std::string value = serializedValue->ToString(args.GetVm())->ToString(args.GetVm());
    if (!StorageProxy::GetInstance()->GetStorage()) {
        LOGW("no storage available");
        return;
    }
    StorageProxy::GetInstance()->GetStorage()->SetString(key, value);
}

void JSPersistent::Get(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < 1 || !args[0]->IsString()) {
        return;
    }
    auto storage = StorageProxy::GetInstance()->GetStorage();
    if (!storage) {
        LOGW("no storage available");
        return;
    }
    std::string key = args[0]->ToString();
    std::string value = storage->GetString(key);
    if (value.empty() || value == "undefined") {
        args.SetReturnValue(JSVal::Undefined());
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSVal> ret = obj->ToJsonObject(value.c_str());
    args.SetReturnValue(ret);
}

void JSPersistent::Has(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < 1 || !args[0]->IsString()) {
        LOGW("JSPersistent: Failed to Get persistent data, args too few");
        return;
    }
    std::string key = args[0]->ToString();
    if (!StorageProxy::GetInstance()->GetStorage()) {
        LOGW("no storage available");
        return;
    }
    std::string value = StorageProxy::GetInstance()->GetStorage()->GetString(key);
    args.SetReturnValue(value.empty()? JSVal::False() : JSVal::True());
}

void JSPersistent::Delete(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < 1 || !args[0]->IsString()) {
        return;
    }
    std::string key = args[0]->ToString();
    if (!StorageProxy::GetInstance()->GetStorage()) {
        LOGW("no storage available");
        return;
    }
    StorageProxy::GetInstance()->GetStorage()->Delete(key);
}

void JSPersistent::Clear(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    if (!StorageProxy::GetInstance()->GetStorage()) {
        LOGW("no storage available");
        return;
    }
    StorageProxy::GetInstance()->GetStorage()->Clear();
}

} // namespace OHOS::Ace::Framework