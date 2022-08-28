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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_H

#include "core/components/xcomponent/xcomponent_component.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace::Framework {
class XComponentClient {
public:
    using GetJSValCallback = std::function<bool(JSRef<JSVal>& param)>;
    using DeleteCallback = std::function<void()>;
    XComponentClient& operator=(const XComponentClient&) = delete;
    XComponentClient(const XComponentClient&) = delete;
    ~XComponentClient() = default;

    static XComponentClient& GetInstance()
    {
        static XComponentClient instance;
        return instance;
    }

    RefPtr<XComponentComponent> GetXComponentFromXcomponentsMap(const std::string& xcomponentId)
    {
        auto iter = xcomponentsMap_.find(xcomponentId);
        if (iter == xcomponentsMap_.end()) {
            LOGE("xcomponent: %s not exists", xcomponentId.c_str());
            return nullptr;
        }
        return AceType::DynamicCast<XComponentComponent>(iter->second.Upgrade());
    }

    RefPtr<JSXComponentController> GetControllerFromJSXComponentControllersMap(const std::string& xcomponentId)
    {
        auto iter = jsXComponentControllersMap_.find(xcomponentId);
        if (iter == jsXComponentControllersMap_.end()) {
            return nullptr;
        }
        return iter->second;
    }

    std::pair<RefPtr<OHOS::Ace::NativeXComponentImpl>, OH_NativeXComponent*> GetNativeXComponentFromXcomponentsMap(
        const std::string& xcomponentId)
    {
        auto it = nativeXcomponentsMap_.find(xcomponentId);
        if (it != nativeXcomponentsMap_.end()) {
            return it->second;
        } else {
            auto nativeXComponentImpl = AceType::MakeRefPtr<NativeXComponentImpl>();
            auto nativeXComponent = new OH_NativeXComponent(AceType::RawPtr(nativeXComponentImpl));
            nativeXcomponentsMap_[xcomponentId] = std::make_pair(nativeXComponentImpl, nativeXComponent);
            return nativeXcomponentsMap_[xcomponentId];
        }
    }

    void AddXComponentToXcomponentsMap(const std::string& xcomponentId, const RefPtr<XComponentComponent>& component)
    {
        auto result = xcomponentsMap_.try_emplace(xcomponentId, component);
        if (!result.second) {
            auto oldXcomponent = result.first->second.Upgrade();
            if (oldXcomponent) {
                oldXcomponent->SetDeleteCallbackToNull();
            }
            result.first->second = component;
        }
    }

    void AddControllerToJSXComponentControllersMap(const std::string& xcomponentId,
        JSXComponentController*& controller)
    {
        jsXComponentControllersMap_[xcomponentId] = controller;
    }

    void DeleteFromXcomponentsMapById(const std::string& xcomponentId)
    {
        auto it = xcomponentsMap_.find(xcomponentId);
        if (it == xcomponentsMap_.end()) {
            return;
        }
        auto xcomponent = it->second.Upgrade();
        if (xcomponent) {
            xcomponent->SetDeleteCallbackToNull();
        }
        xcomponentsMap_.erase(it);
    }

    void DeleteControllerFromJSXComponentControllersMap(const std::string& xcomponentId)
    {
        jsXComponentControllersMap_.erase(xcomponentId);
    }

    void DeleteFromNativeXcomponentsMapById(const std::string& xcomponentId)
    {
        auto it = nativeXcomponentsMap_.find(xcomponentId);
        if (it == nativeXcomponentsMap_.end()) {
            return;
        }
        if (it->second.second) {
            delete it->second.second;
            it->second.second = nullptr;
        }
        nativeXcomponentsMap_.erase(it);
    }

    void AddJsValToJsValMap(const std::string& xcomponentId, const JSRef<JSVal>& jsVal)
    {
        auto result = jsValMap_.try_emplace(xcomponentId, jsVal);
        if (!result.second) {
            result.first->second = jsVal;
        }
    }

    void DeleteFromJsValMapById(const std::string& xcomponentId)
    {
        auto it = jsValMap_.find(xcomponentId);
        if (it == jsValMap_.end()) {
            return;
        }
        jsValMap_.erase(it);
    }

    bool GetJSVal(const std::string& xcomponentId, JSRef<JSVal>& jsVal)
    {
        auto iter = jsValMap_.find(xcomponentId);
        if (iter != jsValMap_.end()) {
            jsVal = iter->second;
            jsValMap_.erase(iter);
            return true;
        }
        return false;
    }

private:
    XComponentClient() = default;
    std::unordered_map<std::string, WeakPtr<XComponentComponent>> xcomponentsMap_;
    std::unordered_map<std::string, RefPtr<JSXComponentController>> jsXComponentControllersMap_;
    std::unordered_map<std::string, std::pair<RefPtr<OHOS::Ace::NativeXComponentImpl>, OH_NativeXComponent*>>
        nativeXcomponentsMap_;
    std::unordered_map<std::string, JSRef<JSVal>> jsValMap_;
};

class ACE_EXPORT JSXComponent : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void JsOnLoad(const JSCallbackInfo& args);
    static void JsOnDestroy(const JSCallbackInfo& args);

private:
    static EventMarker GetEventMarker(const JSCallbackInfo& info, const std::vector<std::string>& keys);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_H