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

#include "bridge/declarative_frontend/jsview/js_list.h"

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/list/list_component.h"
#include "core/components_v2/list/list_position_controller.h"

namespace OHOS::Ace::Framework {
namespace {

using ThisComponent = V2::ListComponent;

constexpr DisplayMode DISPLAY_MODE_TABLE[] = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
constexpr EdgeEffect EDGE_EFFECT_TABLE[] = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
constexpr Axis DIRECTION_TABLE[] = { Axis::VERTICAL, Axis::HORIZONTAL };

} // namespace

void JSList::SetDirection(int32_t direction)
{
    JSViewSetProperty(&V2::ListComponent::SetDirection, direction, DIRECTION_TABLE, Axis::VERTICAL);
}

void JSList::SetScrollBar(int32_t scrollBar)
{
    JSViewSetProperty(&V2::ListComponent::SetScrollBar, scrollBar, DISPLAY_MODE_TABLE, DisplayMode::OFF);
}

void JSList::SetEdgeEffect(int32_t edgeEffect)
{
    JSViewSetProperty(&V2::ListComponent::SetEdgeEffect, edgeEffect, EDGE_EFFECT_TABLE, EdgeEffect::SPRING);
}

void JSList::SetEditMode(bool editMode)
{
    JSViewSetProperty(&V2::ListComponent::SetEditMode, editMode);
}

void JSList::SetCachedCount(int32_t cachedCount)
{
    JSViewSetProperty(&V2::ListComponent::SetCachedCount, cachedCount);
}

void JSList::Create(const JSCallbackInfo& args)
{
    auto listComponent = AceType::MakeRefPtr<V2::ListComponent>();
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

        Dimension space;
        if (ConvertFromJSValue(obj->GetProperty("space"), space) && space.IsValid()) {
            listComponent->SetSpace(space);
        }

        int32_t initialIndex = 0;
        if (ConvertFromJSValue(obj->GetProperty("initialIndex"), initialIndex) && initialIndex >= 0) {
            listComponent->SetInitialIndex(initialIndex);
        }

        JSRef<JSVal> scrollerValue = obj->GetProperty("scroller");
        if (scrollerValue->IsObject()) {
            auto scroller = Referenced::Claim(JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>());
            if (scroller) {
                auto listController = AceType::MakeRefPtr<V2::ListPositionController>();
                scroller->SetController(listController);
                listComponent->SetScrollController(listController);
            }
        }
    }

    ViewStackProcessor::GetInstance()->Push(listComponent);
    JSInteractableView::SetFocusNode(true);
    args.ReturnSelf();
}

void JSList::SetChainAnimation(bool enableChainAnimation)
{
    JSViewSetProperty(&V2::ListComponent::SetChainAnimation, enableChainAnimation);
}

void JSList::JSBind(BindingTarget globalObj)
{
    JSClass<JSList>::Declare("List");
    JSClass<JSList>::StaticMethod("create", &JSList::Create);

    JSClass<JSList>::StaticMethod("listDirection", &JSList::SetDirection);
    JSClass<JSList>::StaticMethod("scrollBar", &JSList::SetScrollBar);
    JSClass<JSList>::StaticMethod("edgeEffect", &JSList::SetEdgeEffect);
    JSClass<JSList>::StaticMethod("divider", &JSList::SetDivider);
    JSClass<JSList>::StaticMethod("editMode", &JSList::SetEditMode);
    JSClass<JSList>::StaticMethod("cachedCount", &JSList::SetCachedCount);
    JSClass<JSList>::StaticMethod("chainAnimation", &JSList::SetChainAnimation);

    JSClass<JSList>::StaticMethod("onScroll", &JSList::ScrollCallback);
    JSClass<JSList>::StaticMethod("onReachStart", &JSList::ReachStartCallback);
    JSClass<JSList>::StaticMethod("onReachEnd", &JSList::ReachEndCallback);
    JSClass<JSList>::StaticMethod("onScrollStop", &JSList::ScrollStopCallback);
    JSClass<JSList>::StaticMethod("onItemDelete", &JSList::ItemDeleteCallback);
    JSClass<JSList>::StaticMethod("onItemMove", &JSList::ItemMoveCallback);
    JSClass<JSList>::StaticMethod("onScrollIndex", &JSList::ScrollIndexCallback);

    JSClass<JSList>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSList>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSList>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSList>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSList>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSList>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSList>::Inherit<JSContainerBase>();
    JSClass<JSList>::Inherit<JSViewAbstract>();
    JSClass<JSList>::Bind(globalObj);
}

void JSList::SetDivider(const JSCallbackInfo& args)
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

        JSViewSetProperty(&V2::ListComponent::SetItemDivider, std::move(divider));
    } while (0);

    args.ReturnSelf();
}

void JSList::ScrollCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnScroll, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ReachStartCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnReachStart, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ReachEndCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnReachEnd, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ScrollStopCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnScrollStop, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ItemDeleteCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnItemDelete, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ItemMoveCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnItemMove, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ScrollIndexCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::ListComponent::SetOnScrollIndex, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
