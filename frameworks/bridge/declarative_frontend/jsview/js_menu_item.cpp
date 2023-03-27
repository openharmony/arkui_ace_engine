/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_menu_item.h"

#include "base/log/ace_scoring_log.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_view.h"

namespace OHOS::Ace::Framework {
void JSMenuItem::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || (!info[0]->IsObject() && !info[0]->IsFunction())) {
        LOGW("JSMenuItem The arg is wrong");
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        // custom menu item
        if (info[0]->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(info[0]));
            CHECK_NULL_VOID(builderFunc);

            NG::ScopedViewStackProcessor builderViewStackProcessor;
            builderFunc->Execute();
            auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
            CHECK_NULL_VOID(customNode);
        } else {
            auto menuItemObj = JSRef<JSObject>::Cast(info[0]);

            std::string startIconPath;
            std::string contentStr;
            std::string endIconPath;
            std::string labelStr;
            NG::MenuItemProperties menuItemProps;

            auto startIcon = menuItemObj->GetProperty("startIcon");
            auto content = menuItemObj->GetProperty("content");
            auto endIcon = menuItemObj->GetProperty("endIcon");
            auto label = menuItemObj->GetProperty("labelInfo");

            if (ParseJsMedia(startIcon, startIconPath)) {
                menuItemProps.startIcon = startIconPath;
            } else {
                LOGI("startIcon is null");
            }

            if (!ParseJsString(content, contentStr)) {
                LOGI("content is null");
            }
            menuItemProps.content = contentStr;

            if (ParseJsMedia(endIcon, endIconPath)) {
                menuItemProps.endIcon = endIconPath;
            } else {
                LOGI("endIcon is null");
            }

            if (ParseJsString(label, labelStr)) {
                menuItemProps.labelInfo = labelStr;
            } else {
                LOGI("labelInfo is null");
            }

            auto builder = menuItemObj->GetProperty("builder");
            if (!builder.IsEmpty() && builder->IsFunction()) {
                auto subBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
                CHECK_NULL_VOID(subBuilderFunc);
                auto subBuildFunc = [execCtx = info.GetExecutionContext(), func = std::move(subBuilderFunc)]() {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("MenuItem SubBuilder");
                    func->ExecuteJS();
                };
                menuItemProps.buildFunc = std::move(subBuildFunc);
            }
            NG::MenuItemView::Create(menuItemProps);
        }
        return;
    }
}

void JSMenuItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenuItem>::Declare("MenuItem");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenuItem>::StaticMethod("create", &JSMenuItem::Create, opt);

    JSClass<JSMenuItem>::StaticMethod("selected", &JSMenuItem::IsSelected, opt);
    JSClass<JSMenuItem>::StaticMethod("selectIcon", &JSMenuItem::SelectIcon, opt);
    JSClass<JSMenuItem>::StaticMethod("onChange", &JSMenuItem::OnChange, opt);
    JSClass<JSMenuItem>::Inherit<JSViewAbstract>();
    JSClass<JSMenuItem>::Bind(globalObj);
}

void JSMenuItem::IsSelected(bool isSelected)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::MenuItemView::SetSelected(isSelected);
    }
}

void JSMenuItem::SelectIcon(bool isShow)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::MenuItemView::SetSelectIcon(isShow);
    }
}

void JSMenuItem::OnChange(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](bool selected) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("MenuItem.onChange");
            JSRef<JSVal> params[1];
            params[0] = JSRef<JSVal>::Make(ToJSValue(selected));
            func->ExecuteJS(1, params);
        };
        NG::MenuItemView::SetOnChange(std::move(onChange));
    }
    info.ReturnSelf();
}
} // namespace OHOS::Ace::Framework
