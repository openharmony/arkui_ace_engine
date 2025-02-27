/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CONTAINER_MODAL_VIEW_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CONTAINER_MODAL_VIEW_H

#include <functional>
#include <optional>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"

namespace OHOS::Ace::Framework {

class JSContainerModal : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void CallNative(const JSCallbackInfo& info);

private:
    static RefPtr<NG::ContainerModalPatternEnhance> GetContainerModalPattern();

    static void OnMaxBtnClick(const JSCallbackInfo& info);
    static void OnMinBtnClick(const JSCallbackInfo& info);
    static void OnCloseBtnClick(const JSCallbackInfo& info);
    static void OnLeftSplitClick(const JSCallbackInfo& info);
    static void OnRightSplitClick(const JSCallbackInfo& info);
    static void AddButtonPointLightAnim(const JSCallbackInfo& info);
    static void CallButtonsRectChange(const JSCallbackInfo& info);
    static void CallMenuWidthChange(const JSCallbackInfo& info);
    static void CallWindowNative(const JSCallbackInfo& info);
    static void CallTitleRowUpdate(const JSCallbackInfo& info);
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CONTAINER_MODAL_VIEW_H
