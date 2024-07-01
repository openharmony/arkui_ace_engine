/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_TAB_CONTENT_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_TAB_CONTENT_H

#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/core/components/tab_bar/tab_content_component.h"
#include "frameworks/core/components_v2/tabs/tab_content_item_component.h"
#include "frameworks/core/components_v2/tabs/tabs_component.h"
#include "frameworks/core/components_ng/pattern/tabs/tab_content_model.h"
#include "frameworks/core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace::Framework {

class JSTabContent : public JSContainerBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void Pop();

    static void SetTabBar(const JSCallbackInfo& info);

protected:

    // The width and height of tabcontent depend on the size constraints of tabs and tabbar.
    static void SetTabContentWidth(const JSCallbackInfo& info)
    {
        LOGW("TabContent does not support width and height settings");
    }

    static void SetTabContentHeight(const JSCallbackInfo& info)
    {
        LOGW("TabContent does not support width and height settings");
    }

    static void SetTabContentSize(const JSCallbackInfo& info)
    {
        LOGW("TabContent does not support width and height settings");
    }

private:
    static void CreateForPartialUpdate(const JSCallbackInfo& info);
    static void CreateForNG(const JSCallbackInfo& info);
    static void SetTabBarForNG(const JSCallbackInfo& info);
    static void SetIndicator(const JSRef<JSVal>& info);
    static void SetBoard(const JSRef<JSVal>& info);
    static void SetSelectedMode(const JSRef<JSVal>& info);
    static void SetSubTabBarStyle(const JSRef<JSObject>& paramObject);
    static void SetLabelStyle(const JSRef<JSVal>& info, bool isSubTabStyle);
    static void SetIconStyle(const JSRef<JSVal>& info);
    static void SetPadding(const JSRef<JSVal>& info, bool isSubTabStyle);
    static void GetFontContent(JSRef<JSVal> font, LabelStyle& labelStyle, bool isSubTabStyle);
    static void GetLabelUnselectedContent(JSRef<JSVal> unselectedColorValue, LabelStyle& labelStyle);
    static void GetLabelSelectedContent(JSRef<JSVal> selectedColorValue, LabelStyle& labelStyle);
    static void CompleteParameters(LabelStyle& buttonParameters, bool isSubTabStyle);
    static void SetLayoutMode(const JSRef<JSVal>& info);
    static void SetVerticalAlign(const JSRef<JSVal>& info);
    static void SetSymmetricExtensible(const JSRef<JSVal>& info);
    static void SetId(const JSRef<JSVal>& info);
    static void SetBottomTabBarStyle(const JSCallbackInfo& info);
    static void SetOnWillShow(const JSCallbackInfo& info);
    static void SetOnWillHide(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_TAB_CONTENT_H
