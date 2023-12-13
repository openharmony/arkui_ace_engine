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
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

void JSPersistent::JSBind(BindingTarget globalObj)
{
    JSClass<JSPersistent>::Declare("Storage");
    JSClass<JSPersistent>::CustomMethod("set", &JSPersistent::Set);
    JSClass<JSPersistent>::CustomMethod("get", &JSPersistent::Get);
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
    if (args.Length() < 2 || !args[0]->IsString() || args[1]->IsUndefined() || args[1]->IsNull()) {
        LOGW("JSPersistent: Fail to set persistent data, args too few");
        return;
    }
    std::string key = args[0]->ToString();
    auto serializedValue = JSON::Stringify(args.GetVm(), args[1].Get().GetLocalHandle());
    std::string value = serializedValue->ToString(args.GetVm())->ToString();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return;
    }
    auto executor = container->GetTaskExecutor();
    if(!StorageProxy::GetInstance()->GetStorage(executor)) {
        LOGW("no storage available");
        return;
    }
    StorageProxy::GetInstance()->GetStorage(executor)->SetString(key, value);
    LOGD("cross window notify, containerId=%{private}d", container->GetInstanceId());
    AceEngine::Get().NotifyContainers(
        [currInstanceId = container->GetInstanceId(), key, value](const RefPtr<Container>& container) {
        if (container && container->GetInstanceId() != currInstanceId) {
            container->NotifyAppStorage(key, value);
        }
    });
}

void JSPersistent::Get(const JSCallbackInfo& args)
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
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return;
    }
    auto executor = container->GetTaskExecutor();
    std::string value = StorageProxy::GetInstance()->GetStorage(executor)->GetString(key);
    if (value.empty()) {
        args.SetReturnValue(JSVal::Undefined());
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSVal> ret = obj->ToJsonObject(value.c_str());
    args.SetReturnValue(ret);
}

void JSPersistent::Delete(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < 1 || !args[0]->IsString()) {
        LOGW("JSPersistent: Fail to Delete persistent data, args too few");
        return;
    }
    std::string key = args[0]->ToString();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return;
    }
    auto executor = container->GetTaskExecutor();
    StorageProxy::GetInstance()->GetStorage(executor)->Delete(key);
}

void JSPersistent::Clear(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the PersistentStorage in the Previewer. Perform this operation on the "
        "emulator or a real device instead.");
    return;
#endif
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return;
    }
    auto executor = container->GetTaskExecutor();
    StorageProxy::GetInstance()->GetStorage(executor)->Clear();
}

} // namespace OHOS::Ace::Framework