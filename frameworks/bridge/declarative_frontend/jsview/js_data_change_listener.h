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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DATA_CHANGE_LISTENER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DATA_CHANGE_LISTENER_H

#include <functional>
#include <set>
#include <string>

#include "base/memory/ace_type.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

class JSDataChangeListener : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);

    void AddListener(const WeakPtr<V2::DataChangeListener>& listener)
    {
        listeners_.emplace(listener);
    }

    void RemoveListener(const WeakPtr<V2::DataChangeListener>& listener)
    {
        listeners_.erase(listener);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto listener = Referenced::MakeRefPtr<JSDataChangeListener>();
        listener->instanceId_ = ContainerScope::CurrentId();
        listener->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(listener));
    }

    static void Destructor(JSDataChangeListener* listener)
    {
        if (listener != nullptr) {
            listener->DecRefCount();
        }
    }

    void OnDataReloaded(const JSCallbackInfo& args)
    {
        NotifyAll(&V2::DataChangeListener::OnDataReloaded);
    }

    void OnDataAdded(const JSCallbackInfo& args)
    {
        NotifyAll(&V2::DataChangeListener::OnDataAdded, args);
    }

    void OnDataDeleted(const JSCallbackInfo& args)
    {
        NotifyAll(&V2::DataChangeListener::OnDataDeleted, args);
    }

    void OnDataChanged(const JSCallbackInfo& args)
    {
        NotifyAll(&V2::DataChangeListener::OnDataChanged, args);
    }

    void OnDataMoved(const JSCallbackInfo& args)
    {
        ContainerScope scope(instanceId_);
        size_t from = 0;
        size_t to = 0;
        if (args.Length() < 2 || !ConvertFromJSValue(args[0], from) || !ConvertFromJSValue(args[1], to)) {
            return;
        }
        NotifyAll(&V2::DataChangeListener::OnDataMoved, from, to);
    }

    template<class... Args>
    void NotifyAll(void (V2::DataChangeListener::*method)(Args...), const JSCallbackInfo& args)
    {
        ContainerScope scope(instanceId_);
        size_t index = 0;
        if (args.Length() > 0 && ConvertFromJSValue(args[0], index)) {
            NotifyAll(method, index);
        }
    }

    template<class... Args>
    void NotifyAll(void (V2::DataChangeListener::*method)(Args...), Args... args)
    {
        ContainerScope scope(instanceId_);
        for (auto it = listeners_.begin(); it != listeners_.end();) {
            auto listener = it->Upgrade();
            if (!listener) {
                it = listeners_.erase(it);
                continue;
            }
            ++it;
            ((*listener).*method)(args...);
        }
    }

    std::set<WeakPtr<V2::DataChangeListener>> listeners_;
    int32_t instanceId_ = -1;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DATA_CHANGE_LISTENER_H
