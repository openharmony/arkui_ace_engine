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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PREVIEWER_MOCK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PREVIEWER_MOCK_H

#include "core/components/text/text_component_v2.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSForm : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
};

class JSRichText : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
};

class JSXComponent : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
};

class JSXComponentController : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
    static void Mock(const JSCallbackInfo& args);
};

class JSWeb : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
};

class JSWebController : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
};

class JSVideo : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
};

class JSVideoController : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
    static void Mock(const JSCallbackInfo& info);
};

class JSPlugin : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
};

class JSUIExtension : public JSViewAbstract, public JSInteractableView {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void onRemoteReady(const JSCallbackInfo& info);
    static void onReceive(const JSCallbackInfo& info);
    static void onResult(const JSCallbackInfo& info);
    static void onRelease(const JSCallbackInfo& info);
    static void onError(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
};

class JSSecurityUIExtension : public JSViewAbstract, public JSInteractableView {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
};

class JSAbilityComponent : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void Mock(const JSCallbackInfo& info);
};

class JSSceneView : public JSViewAbstract {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void Mock(const JSCallbackInfo& info);
};

class JSEmbeddedComponent : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void Mock(const JSCallbackInfo& info);
};

class JSIsolatedComponent : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);
    static void Mock(const JSCallbackInfo& info);
};

class JSRemoteWindow : public JSViewAbstract, public JSInteractableView {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void Mock(const JSCallbackInfo& info);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PREVIEWER_MOCK_H
