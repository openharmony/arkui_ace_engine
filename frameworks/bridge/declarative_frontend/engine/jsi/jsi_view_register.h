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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_VIEW_REGISTER_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_VIEW_REGISTER_H

#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"

namespace OHOS::Ace::Framework {

void JsBindViews(BindingTarget globalObj, void* nativeEngine);
void JsUINodeRegisterCleanUp(BindingTarget globalObj);
void JsBindFormViews(BindingTarget globalObj, const std::unordered_set<std::string>& formModuleList,
    void* nativeEngine, bool isReload = false);

void UpdateRootComponent(const EcmaVM* vm, const panda::Local<panda::ObjectRef>& obj);
void JsBindWorkerViews(BindingTarget globalObj, const shared_ptr<JsRuntime> runtime,
    void* nativeEngine, const shared_ptr<JsValue> globalPtr);
void CleanPageNode(const RefPtr<NG::FrameNode>& pageNode);

RefPtr<FrontendDelegate> JsGetFrontendDelegate();

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JSI_VIEW_REGISTER_H
