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

#include "core/common/container.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace::Framework {

struct XComponentParams {
    int32_t elmtId = -1;
    int32_t xcomponentType = 0;
    int32_t renderType = 0;
    int32_t width = 0;
    int32_t height = 0;
    std::string xcomponentId;
    std::string surfaceId;
    std::string libraryName;
    JSXComponentController* controller = nullptr;
};

struct XComponentOptions {
    std::optional<std::string> id = std::nullopt;
    XComponentType xcomponentType = XComponentType::SURFACE;
    std::optional<std::string> libraryName = std::nullopt;
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    std::optional<std::uint64_t> screenId = std::nullopt;
};

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

    RefPtr<JSXComponentController> GetControllerFromJSXComponentControllersMap(const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto iter = jsXComponentControllersMap_.find(idWithContainerId);
        if (iter == jsXComponentControllersMap_.end()) {
            return nullptr;
        }
        return iter->second;
    }

    std::pair<RefPtr<OHOS::Ace::NativeXComponentImpl>, OH_NativeXComponent*> GetNativeXComponentFromXcomponentsMap(
        const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto it = nativeXcomponentsMap_.find(idWithContainerId);
        if (it != nativeXcomponentsMap_.end()) {
            return it->second;
        } else {
            auto nativeXComponentImpl = AceType::MakeRefPtr<NativeXComponentImpl>();
            auto nativeXComponent = new OH_NativeXComponent(AceType::RawPtr(nativeXComponentImpl));
            nativeXcomponentsMap_[idWithContainerId] = std::make_pair(nativeXComponentImpl, nativeXComponent);
            return nativeXcomponentsMap_[idWithContainerId];
        }
    }

    void AddControllerToJSXComponentControllersMap(const std::string& xcomponentId, JSXComponentController*& controller)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        jsXComponentControllersMap_[idWithContainerId] = controller;
    }

    void DeleteControllerFromJSXComponentControllersMap(const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        jsXComponentControllersMap_.erase(idWithContainerId);
    }

    void DeleteFromNativeXcomponentsMapById(const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto it = nativeXcomponentsMap_.find(idWithContainerId);
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
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto result = jsValMap_.try_emplace(idWithContainerId, jsVal);
        if (!result.second) {
            result.first->second = jsVal;
        }
    }

    void DeleteFromJsValMapById(const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto it = jsValMap_.find(idWithContainerId);
        if (it == jsValMap_.end()) {
            return;
        }
        jsValMap_.erase(it);
    }

    bool GetJSVal(const std::string& xcomponentId, JSRef<JSVal>& jsVal)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto iter = jsValMap_.find(idWithContainerId);
        if (iter != jsValMap_.end()) {
            jsVal = iter->second;
            jsValMap_.erase(iter);
            return true;
        }
        return false;
    }

private:
    XComponentClient() = default;
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
    static void JsOnAppear(const JSCallbackInfo& args);
    static void JsOnDisAppear(const JSCallbackInfo& args);
    static void JsOnAttach(const JSCallbackInfo& args);
    static void JsOnDetach(const JSCallbackInfo& args);

    static void JsOnTouch(const JSCallbackInfo& args);
    static void JsOnClick(const JSCallbackInfo& args);
    static void JsOnKeyEvent(const JSCallbackInfo& args);
    static void JsOnMouse(const JSCallbackInfo& args);
    static void JsOnHover(const JSCallbackInfo& args);
    static void JsOnFocus(const JSCallbackInfo& args);
    static void JsOnBlur(const JSCallbackInfo& args);

    static void JsBackgroundColor(const JSCallbackInfo& args);
    static void JsBackgroundImage(const JSCallbackInfo& args);
    static void JsBackgroundImageSize(const JSCallbackInfo& args);
    static void JsBackgroundImagePosition(const JSCallbackInfo& args);
    static void JsOpacity(const JSCallbackInfo& args);
    static void JsBlur(const JSCallbackInfo& args);
    static void JsBackdropBlur(const JSCallbackInfo& args);
    static void JsGrayscale(const JSCallbackInfo& args);
    static void JsBrightness(const JSCallbackInfo& args);
    static void JsSaturate(const JSCallbackInfo& args);
    static void JsContrast(const JSCallbackInfo& args);
    static void JsInvert(const JSCallbackInfo& args);
    static void JsSepia(const JSCallbackInfo& args);
    static void JsHueRotate(const JSCallbackInfo& args);
    static void JsColorBlend(const JSCallbackInfo& args);
    static void JsSphericalEffect(const JSCallbackInfo& args);
    static void JsLightUpEffect(const JSCallbackInfo& args);
    static void JsPixelStretchEffect(const JSCallbackInfo& args);
    static void JsLinearGradientBlur(const JSCallbackInfo& args);
    static void JsEnableAnalyzer(bool enable);
    static void JsRenderFit(const JSCallbackInfo& args);
    static void JsEnableSecure(const JSCallbackInfo& args);
    static void JsHdrBrightness(const JSCallbackInfo& args);
    static void JsBlendMode(const JSCallbackInfo& args);
    static void JsEnableTransparentLayer(const JSCallbackInfo& args);

    // For xcomponent node
    static void* Create(const XComponentParams& params);

    void RegisterOnCreate(const JsiExecutionContext& execCtx, const Local<JSValueRef>& func);
    void RegisterOnDestroy(const JsiExecutionContext& execCtx, const Local<JSValueRef>& func);
    void SetFrameNode(RefPtr<AceType> frameNode)
    {
        frameNode_ = frameNode;
    }
    RefPtr<AceType> GetFrameNode() const
    {
        return frameNode_;
    }
    bool ChangeRenderType(int32_t renderType);

private:
    static void ParseImageAIOptions(const JSRef<JSVal>& jsValue);
    static void ExtractInfoToXComponentOptions(
        XComponentOptions& options, JSRef<JSObject>& controllerObj,
        const JSRef<JSObject>& paramObject, const JSCallbackInfo& info);

    RefPtr<AceType> frameNode_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_XCOMPONENT_H
