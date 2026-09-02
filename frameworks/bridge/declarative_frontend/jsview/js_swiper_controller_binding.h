/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_CONTROLLER_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_CONTROLLER_BINDING_H

#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_swiper_controller.h"

namespace OHOS::Ace::Framework {

class JSSwiperControllerBinding final : public JSSwiperController {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSSwiperController* scroller);

    void SwipeTo(const JSCallbackInfo& args);
    void ShowNext(const JSCallbackInfo& args);
    void ShowPrevious(const JSCallbackInfo& args);
    void ChangeIndex(const JSCallbackInfo& args);
    void FinishAnimation(const JSCallbackInfo& args);
    void PreloadItems(const JSCallbackInfo& args);
    void OldPreloadItems(const JSCallbackInfo& args);
    void NewPreloadItems(const JSCallbackInfo& args);
    void StartFakeDrag(const JSCallbackInfo& args);
    void FakeDragBy(const JSCallbackInfo& args);
    void StopFakeDrag(const JSCallbackInfo& args);
    void IsFakeDragging(const JSCallbackInfo& args);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_SWIPER_CONTROLLER_BINDING_H
