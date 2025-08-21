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

#include "bridge/declarative_frontend/jsview/js_menu_item_group.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"

namespace OHOS::Ace::Framework {
void JSMenuItemGroup::Create(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    NG::MenuItemGroupView::Create();
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto headerProp = obj->GetProperty("header");
    if (!headerProp.IsEmpty()) {
        if (headerProp->IsFunction()) {
            RefPtr<NG::UINode> header;
            {
                auto headerBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(headerProp));
                CHECK_NULL_VOID(headerBuilderFunc);
                NG::ScopedViewStackProcessor builderViewStackProcessor;
                headerBuilderFunc->Execute();
                header = NG::ViewStackProcessor::GetInstance()->Finish();
                CHECK_NULL_VOID(header);
            }
            NG::MenuItemGroupView::SetHeader(header);
        } else {
            if (!ParseJsHeaderString(headerProp)) {
                return;
            }
        }
    }
    auto footerProp = obj->GetProperty("footer");
    if (!footerProp.IsEmpty()) {
        if (footerProp->IsFunction()) {
            RefPtr<NG::UINode> footer;
            {
                auto footerBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(footerProp));
                CHECK_NULL_VOID(footerBuilderFunc);
                NG::ScopedViewStackProcessor builderViewStackProcessor;
                footerBuilderFunc->Execute();
                footer = NG::ViewStackProcessor::GetInstance()->Finish();
                CHECK_NULL_VOID(footer);
            }
            NG::MenuItemGroupView::SetFooter(footer);
        } else {
            if (!ParseJsFooterString(footerProp)) {
                return;
            }
        }
        return;
    }
}

bool JSMenuItemGroup::ParseJsHeaderString(const JSRef<JSVal>& headerProp)
{
    std::string headerStr;
    RefPtr<ResourceObject> resObj;
    if (!ParseJsString(headerProp, headerStr, resObj)) {
        return false;
    }
    NG::MenuItemGroupView::SetHeader(headerStr);
    if (SystemProperties::ConfigChangePerform()) {
        NG::MenuItemGroupView::CreateWithStringResourceObj(resObj, NG::MenuItemGroupStringType::HEADER);
    }
    return true;
}

bool JSMenuItemGroup::ParseJsFooterString(const JSRef<JSVal>& footerProp)
{
    std::string footerStr;
    RefPtr<ResourceObject> resObj;
    if (!ParseJsString(footerProp, footerStr, resObj)) {
        return false;
    }
    NG::MenuItemGroupView::SetFooter(footerStr);
    if (SystemProperties::ConfigChangePerform()) {
        NG::MenuItemGroupView::CreateWithStringResourceObj(resObj, NG::MenuItemGroupStringType::FOOTER);
    }
    return true;
}

void JSMenuItemGroup::JSBind(BindingTarget globalObj)
{
    JSClass<JSMenuItemGroup>::Declare("MenuItemGroup");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMenuItemGroup>::StaticMethod("create", &JSMenuItemGroup::Create, opt);
    JSClass<JSMenuItemGroup>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSMenuItemGroup>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMenuItemGroup>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSMenuItemGroup>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMenuItemGroup>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMenuItemGroup>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
