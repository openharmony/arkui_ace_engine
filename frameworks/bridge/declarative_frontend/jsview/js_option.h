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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_OPTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_OPTION_H

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/memory/referenced.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/option/option_component.h"
#include "frameworks/core/components/text/text_component.h"

namespace OHOS::Ace::Framework {
class JSOption : public JSViewAbstract, public JSInteractableView {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    // Common text attribute
    static void SetFontColor(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(std::string value);
    static void SetFontFamily(std::string value);

    // On click event
    static void JSOnClick(const JSCallbackInfo& info);
private:
    static RefPtr<OptionComponent> GetOptionComponent();
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_OPTION_H