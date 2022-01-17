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

#include "bridge/declarative_frontend/jsview/js_list_item.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/list/list_item_component.h"

namespace OHOS::Ace::Framework {
namespace {

const V2::StickyMode STICKY_MODE_TABLE[] = { V2::StickyMode::NONE, V2::StickyMode::NORMAL, V2::StickyMode::OPACITY };

} // namespace

void JSListItem::Create(const JSCallbackInfo& args)
{
    auto listItemComponent = AceType::MakeRefPtr<V2::ListItemComponent>();
    if (args.Length() >= 1 && args[0]->IsString()) {
        listItemComponent->SetType(args[0]->ToString());
    }
    ViewStackProcessor::GetInstance()->Push(listItemComponent);
    JSInteractableView::SetFocusNode(true);
    args.ReturnSelf();
}

void JSListItem::SetSticky(int32_t sticky)
{
    JSViewSetProperty(&V2::ListItemComponent::SetSticky, sticky, STICKY_MODE_TABLE, V2::StickyMode::NONE);
}

void JSListItem::SetEditable(const JSCallbackInfo& args)
{
    do {
        if (args.Length() < 1) {
            LOGW("Not enough params");
            break;
        }

        if (args[0]->IsBoolean()) {
            uint32_t value =
                args[0]->ToBoolean() ? V2::EditMode::DELETABLE | V2::EditMode::MOVABLE : V2::EditMode::NONE;
            JSViewSetProperty(&V2::ListItemComponent::SetEditMode, value);
            break;
        }

        if (args[0]->IsNumber()) {
            uint32_t value = args[0]->ToNumber<uint32_t>();
            JSViewSetProperty(&V2::ListItemComponent::SetEditMode, value);
            break;
        }

        LOGW("Invalid params, unknown type");
    } while (0);

    args.ReturnSelf();
}

void JSListItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItem>::Declare("ListItem");
    JSClass<JSListItem>::StaticMethod("create", &JSListItem::Create);

    JSClass<JSListItem>::StaticMethod("sticky", &JSListItem::SetSticky);
    JSClass<JSListItem>::StaticMethod("editable", &JSListItem::SetEditable);

    JSClass<JSListItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSListItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSListItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSListItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSListItem>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSListItem>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSListItem>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSListItem>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSListItem>::Inherit<JSContainerBase>();
    JSClass<JSListItem>::Inherit<JSViewAbstract>();
    JSClass<JSListItem>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
