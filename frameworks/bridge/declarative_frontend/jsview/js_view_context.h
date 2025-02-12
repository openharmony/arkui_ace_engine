/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_CONTEXT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_CONTEXT_H

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSViewContext {
public:
    static void JSBind(BindingTarget globalObj);
    static void JSAnimation(const JSCallbackInfo& info);
    static void JSAnimateTo(const JSCallbackInfo& info);
    static void JSAnimateToImmediately(const JSCallbackInfo& info);
    static void JSKeyframeAnimateTo(const JSCallbackInfo& info);
    static const AnimationOption CreateAnimation(const JSRef<JSObject>& animationArgs, bool isForm = false);
    static RefPtr<Curve> ParseCurve(const JSRef<JSVal>& curveArgs, bool exceptSpring = false);
    static void SetDynamicDimming(const JSCallbackInfo& info);
    static void JSOpenBindSheet(const JSCallbackInfo& info);
    static void JSUpdateBindSheet(const JSCallbackInfo& info);
    static void JSCloseBindSheet(const JSCallbackInfo& info);
    static void JSOpenPopup(const JSCallbackInfo& info);
    static void JSUpdatePopup(const JSCallbackInfo& info);
    static void JSClosePopup(const JSCallbackInfo& info);
    static void JSOpenMenu(const JSCallbackInfo& info);
    static void JSUpdateMenu(const JSCallbackInfo& info);
    static void JSCloseMenu(const JSCallbackInfo& info);
    static void IsFollowingSystemFontScale(const JSCallbackInfo& info);
    static void GetMaxFontScale(const JSCallbackInfo& info);
    static void SetEnableSwipeBack(const JSCallbackInfo& info);
private:
    static void AnimateToInner(const JSCallbackInfo& info, bool immediately);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_VIEW_CONTEXT_H