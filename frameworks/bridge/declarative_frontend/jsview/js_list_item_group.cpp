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

#include "bridge/declarative_frontend/jsview/js_list_item_group.h"

#include "bridge/declarative_frontend/jsview/js_list_item.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_item_view.h"
#include "core/components_v2/list/list_item_group_component.h"

namespace OHOS::Ace::Framework {

void JSListItemGroup::Create(const JSCallbackInfo& args)
{
    auto listItemGroupComponent = AceType::MakeRefPtr<V2::ListItemGroupComponent>();
    if (!(args.Length() < 1) && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

        Dimension space;
        if (ConvertFromJSValue(obj->GetProperty("space"), space) && space.IsValid()) {
            listItemGroupComponent->SetSpace(space);
        }

        auto headerObject = obj->GetProperty("header");
        if (headerObject->IsFunction()) {
            ScopedViewStackProcessor builderViewStackProcessor;
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(headerObject));
            builderFunc->Execute();
            RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
            listItemGroupComponent->SetHeaderComponent(customComponent);
        }

        auto footerObject = obj->GetProperty("footer");
        if (footerObject->IsFunction()) {
            ScopedViewStackProcessor builderViewStackProcessor;
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(footerObject));
            builderFunc->Execute();
            RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
            listItemGroupComponent->SetFooterComponent(customComponent);
        }
    }
    ViewStackProcessor::GetInstance()->Push(listItemGroupComponent);
    args.ReturnSelf();
}

void JSListItemGroup::SetDivider(const JSCallbackInfo& args)
{
    do {
        if (args.Length() < 1 || !args[0]->IsObject()) {
            LOGW("Invalid params");
            break;
        }

        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        Dimension strokeWidth;
        if (!ConvertFromJSValue(obj->GetProperty("strokeWidth"), strokeWidth) && strokeWidth.IsValid()) {
            LOGW("Invalid strokeWidth of divider");
            break;
        }

        auto divider = std::make_unique<V2::ItemDivider>();
        divider->strokeWidth = strokeWidth;
        if (!ConvertFromJSValue(obj->GetProperty("color"), divider->color)) {
            // Failed to get color from param, using default color defined in theme
            RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
            if (listTheme) {
                divider->color = listTheme->GetDividerColor();
            }
        }
        ConvertFromJSValue(obj->GetProperty("startMargin"), divider->startMargin);
        ConvertFromJSValue(obj->GetProperty("endMargin"), divider->endMargin);

        JSViewSetProperty(&V2::ListItemGroupComponent::SetItemDivider, std::move(divider));
    } while (false);

    args.ReturnSelf();
}

void JSListItemGroup::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItemGroup>::Declare("ListItemGroup");
    JSClass<JSListItemGroup>::StaticMethod("create", &JSListItemGroup::Create);

    JSClass<JSListItemGroup>::StaticMethod("divider", &JSListItemGroup::SetDivider);

    JSClass<JSListItemGroup>::Inherit<JSInteractableView>();
    JSClass<JSListItemGroup>::Inherit<JSContainerBase>();
    JSClass<JSListItemGroup>::Inherit<JSViewAbstract>();
    JSClass<JSListItemGroup>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
