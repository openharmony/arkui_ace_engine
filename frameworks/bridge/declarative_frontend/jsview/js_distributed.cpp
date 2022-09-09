/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_distributed.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

void JSDistributed::JSBind(BindingTarget globalObj)
{
    JSClass<JSDistributed>::Declare("DistributedObject");
    JSClass<JSDistributed>::CustomMethod("set", &JSDistributed::Set);
    JSClass<JSDistributed>::CustomMethod("get", &JSDistributed::Get);
    JSClass<JSDistributed>::CustomMethod("delete", &JSDistributed::Delete);
    JSClass<JSDistributed>::Bind(globalObj, JSDistributed::ConstructorCallback, JSDistributed::DestructorCallback);
}

void JSDistributed::ConstructorCallback(const JSCallbackInfo& args)
{
    std::string sessionId;
    if (args.Length() > 1 && args[0]->IsString() && args[1]->IsObject()) {
        sessionId = args[0]->ToString();
        LOGI("sessionId %{public}s", sessionId.c_str());
        auto distributed = Referenced::MakeRefPtr<JSDistributed>(sessionId);
        distributed->IncRefCount();
        distributed->Init(JSRef<JSObject>::Cast(args[1]), sessionId);
        args.SetReturnValue(Referenced::RawPtr(distributed));
    }
}

void JSDistributed::DestructorCallback(JSDistributed* distributed)
{
    if (distributed != nullptr) {
        distributed->DecRefCount();
    }
}

void JSDistributed::Set(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the DistributedStorage in the Previewer. Perform this operation on the "
         "emulator or a real device instead.");
    return;
#endif

    if (args.Length() < 2) {
        LOGW("fail to set distributed data");
        return;
    }
    if (!storage_) {
        LOGW("distributed storage is null, failed to set distributed data");
        return;
    }
    std::string key = args[0]->ToString();
    if (args[1]->IsBoolean()) {
        auto val = args[1]->ToBoolean();
        LOGW("JSDistributed::Set [%{public}s--%{public}d]", key.c_str(), val);
        storage_->SetBoolean(key, val);
        return;
    }

    if (args[1]->IsNumber()) {
        auto val = args[1]->ToNumber<double>();
        LOGW("JSDistributed::Set [%{public}s--%{public}lf]", key.c_str(), val);
        storage_->SetDouble(key, val);
        return;
    }

    if (args[1]->IsString()) {
        auto val = args[1]->ToString();
        LOGW("JSDistributed::Set [%{public}s--%{public}s]", key.c_str(), val.c_str());
        storage_->SetString(key, val);
        return;
    }
    LOGW("JSDistributed::Set type not support [%{public}s]", key.c_str());
}

void JSDistributed::Get(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the DistributedStorage in the Previewer. Perform this operation on the "
         "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < 1) {
        LOGW("fail to Get distributed data");
        return;
    }
    std::string key = args[0]->ToString();
    LOGW("JSDistributed::Get [%{public}s]", key.c_str());

    if (!storage_) {
        LOGW("distributed storage is null, failed to set distributed data");
        return;
    }

    auto dataType = storage_->GetDataType(key);
    JSVal returnValue = JSVal();

    switch (dataType) {
        case Storage::DataType::STRING: {
            auto value = storage_->GetString(key);
            if (!value.empty()) {
                returnValue = JSVal(ToJSValue(value));
                LOGE("Get distributed data success, key = [%{public}s] value = [%{public}s]", key.c_str(),
                    value.c_str());
            }
            break;
        }
        case Storage::DataType::DOUBLE: {
            double value = 0.0;
            if (storage_->GetDouble(key, value)) {
                returnValue = JSVal(ToJSValue(value));
                LOGE("Get distributed data success, key = [%{public}s] value = [%{public}lf]", key.c_str(), value);
            }
            break;
        }
        case Storage::DataType::BOOLEAN: {
            bool value = false;
            if (storage_->GetBoolean(key, value)) {
                returnValue = JSVal(ToJSValue(value));
                LOGE("Get distributed data success, key = [%{public}s] value = [%{public}d]", key.c_str(), value);
            }
            break;
        }
        default:
            break;
    }
    if (returnValue.IsEmpty()) {
        LOGE("fail to Get distributed data, key = [%{public}s]", key.c_str());
        return;
    }
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    args.SetReturnValue(returnPtr);
}

void JSDistributed::Delete(const JSCallbackInfo& args)
{
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the DistributedStorage in the Previewer. Perform this operation on the "
         "emulator or a real device instead.");
    return;
#endif
    if (args.Length() < 1) {
        LOGW("fail to Delete distributed data");
        return;
    }
    std::string key = args[0]->ToString();
    storage_->Delete(key);
}

void JSDistributed::Init(const JSRef<JSObject>& object, const std::string& sessionId)
{
    JSRef<JSVal> jsVal = object->GetProperty("onDataOnChange");
    if (!jsVal->IsFunction()) {
        LOGE("JSDistributed, get func onDataOnChange failed.");
        return;
    }
    onDataOnChange_ = JSRef<JSFunc>::Cast(jsVal);

    jsVal = object->GetProperty("onConnected");
    if (!jsVal->IsFunction()) {
        LOGE("JSDistributed, get func onConnected failed.");
        return;
    }
    onConnected_ = JSRef<JSFunc>::Cast(jsVal);

    object_ = object;
    auto instanceId = ContainerScope::CurrentId();
    auto notifier = [weak = WeakClaim(this), instanceId](const std::string& onlineStatus) {
        ContainerScope scope(instanceId);
        auto distributed = weak.Upgrade();
        distributed->OnStatusNotify(onlineStatus);
    };

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return;
    }
    auto executor = container->GetTaskExecutor();

    storage_ = StorageProxy::GetInstance()->GetStorage(sessionId, notifier, executor);
    
    auto onChangeCallback = [weak = WeakClaim(this), weakExecutor = WeakPtr<TaskExecutor>(executor), instanceId](
                                const std::string& key) {
        auto taskExecutor_ = weakExecutor.Upgrade();
        if (!taskExecutor_) {
            return;
        }
        taskExecutor_->PostTask(
            [weak, key, instanceId] {
                ContainerScope scope(instanceId);
                auto distributed = weak.Upgrade();
                if (distributed) {
                    distributed->OnDataOnChanged(key);
                }
            },
            TaskExecutor::TaskType::JS);
    };

    storage_->SetDataOnChangeCallback(std::move(onChangeCallback));
}

void JSDistributed::OnDataOnChanged(const std::string& key)
{
    LOGI("distributed date on change key = [%{public}s]", key.c_str());

    auto params = ConvertToJSValues(key);
    onDataOnChange_->Call(object_, params.size(), params.data());
}

void JSDistributed::OnStatusNotify(const std::string& onlineStatus)
{
    LOGI("distributed OnStatusNotify = [%{public}s]", onlineStatus.c_str());
    auto params = ConvertToJSValues(onlineStatus);
    onConnected_->Call(object_, params.size(), params.data());
}

} // namespace OHOS::Ace::Framework