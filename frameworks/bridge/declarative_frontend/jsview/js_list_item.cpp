/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/list/list_item_view.h"
#include "core/components_ng/syntax/shallow_builder.h"
#include "core/components_v2/common/element_proxy.h"
#include "core/components_v2/list/list_item_component.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {

const V2::StickyMode STICKY_MODE_TABLE[] = { V2::StickyMode::NONE, V2::StickyMode::NORMAL, V2::StickyMode::OPACITY };
const V2::SwipeEdgeEffect SWIPE_EDGE_EFFECT_TABLE[] = { V2::SwipeEdgeEffect::Spring, V2::SwipeEdgeEffect::None };

} // namespace

void JSListItem::Create(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUsePartialUpdate()) {
        if (Container::IsCurrentUseNewPipeline()) {
            CreateForNGPartialUpdate(args);
        } else {
            CreateForPartialUpdate(args);
        }
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ListItemView::Create();
        return;
    }

    auto listItemComponent = AceType::MakeRefPtr<V2::ListItemComponent>();
    if (args.Length() >= 1 && args[0]->IsString()) {
        listItemComponent->SetType(args[0]->ToString());
    }
    ViewStackProcessor::GetInstance()->Push(listItemComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
    args.ReturnSelf();
}

void JSListItem::CreateForPartialUpdate(const JSCallbackInfo& args)
{
    auto listItemComponent = AceType::MakeRefPtr<V2::ListItemComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(listItemComponent);

    if (args.Length() < 2 || !args[0]->IsFunction()) {
        LOGE("Expected deep render function parameter");
        return;
    }
    RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), JSRef<JSFunc>::Cast(args[0]));

    if (!args[1]->IsBoolean()) {
        LOGE("Expected isLazy parameter");
        return;
    }
    const bool isLazy = args[1]->ToBoolean();

    V2::DeepRenderFunc listItemDeepRenderFunc = [execCtx = args.GetExecutionContext(),
                                                    jsDeepRenderFunc = std::move(jsDeepRender),
                                                    elmtId = listItemComponent->GetElementId()]() -> RefPtr<Component> {
        ACE_SCOPED_TRACE("JSListItem::ExecuteDeepRender");

        LOGD("ListItem elmtId %{public}d DeepRender JS function execution start ....", elmtId);
        ACE_DCHECK(componentsStack_.empty());

        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        JSRef<JSVal> jsParams[2];
        jsParams[0] = JSRef<JSVal>::Make(ToJSValue(elmtId));
        jsParams[1] = JSRef<JSVal>::Make(ToJSValue(true));
        jsDeepRenderFunc->ExecuteJS(2, jsParams);
        RefPtr<Component> component = ViewStackProcessor::GetInstance()->Finish();
        ACE_DCHECK(AceType::DynamicCast<V2::ListItemComponent>(component) != nullptr);
        LOGD("ListItem elmtId %{public}d DeepRender JS function execution - done ", elmtId);
        return component;
    }; // listItemDeepRenderFunc lambda

    listItemComponent->SetDeepRenderFunc(listItemDeepRenderFunc);
    listItemComponent->SetIsLazyCreating(isLazy);
    ViewStackProcessor::GetInstance()->Push(listItemComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
    args.ReturnSelf();
}

void JSListItem::CreateForNGPartialUpdate(const JSCallbackInfo& args)
{
    if (args.Length() < 2 || !args[0]->IsFunction()) {
        LOGE("Expected deep render function parameter");
        return;
    }
    if (!args[1]->IsBoolean()) {
        LOGE("Expected isLazy parameter");
        return;
    }
    const bool isLazy = args[1]->ToBoolean();
    if (!isLazy) {
        NG::ListItemView::Create();
    } else {
        RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), JSRef<JSFunc>::Cast(args[0]));
        auto listItemDeepRenderFunc = [execCtx = args.GetExecutionContext(),
                                          jsDeepRenderFunc = std::move(jsDeepRender)](int32_t nodeId) {
            ACE_SCOPED_TRACE("JSListItem::ExecuteDeepRender");
            LOGD("ListItem elmtId %{public}d DeepRender JS function execution start ....", nodeId);
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            JSRef<JSVal> jsParams[2];
            jsParams[0] = JSRef<JSVal>::Make(ToJSValue(nodeId));
            jsParams[1] = JSRef<JSVal>::Make(ToJSValue(true));
            jsDeepRenderFunc->ExecuteJS(2, jsParams);
        }; // listItemDeepRenderFunc lambda
        NG::ListItemView::Create(std::move(listItemDeepRenderFunc));
    }
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
                args[0]->ToBoolean() ? V2::EditMode::DELETABLE | V2::EditMode::MOVABLE : V2::EditMode::SHAM;
            JSViewSetProperty(&V2::ListItemComponent::SetEditMode, value);
            break;
        }

        if (args[0]->IsNumber()) {
            auto value = args[0]->ToNumber<uint32_t>();
            JSViewSetProperty(&V2::ListItemComponent::SetEditMode, value);
            if (V2::EditMode::MOVABLE != value) {
                auto* stack = ViewStackProcessor::GetInstance();
                auto box = stack->GetBoxComponent();
                box->SetEnableDragStart(false);
            }
            break;
        }

        LOGW("Invalid params, unknown type");
    } while (false);

    args.ReturnSelf();
}

void JSListItem::SetSelectable(bool selectable)
{
    auto listItem = AceType::DynamicCast<V2::ListItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (listItem) {
        listItem->SetSelectable(selectable);
    }
}

void JSListItem::SetSwiperAction(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        LOGE("fail to bind SwiperAction event due to info is not object");
        return;
    }
    auto listItem = AceType::DynamicCast<V2::ListItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!listItem) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListItemComponent>());
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    auto startObject = obj->GetProperty("start");
    if (startObject->IsFunction()) {
        ScopedViewStackProcessor builderViewStackProcessor;
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(startObject));
        builderFunc->Execute();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        listItem->SetSwiperStartComponent(customComponent);
    }

    auto endObject = obj->GetProperty("end");
    if (endObject->IsFunction()) {
        ScopedViewStackProcessor builderViewStackProcessor;
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(endObject));
        builderFunc->Execute();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        listItem->SetSwiperEndComponent(customComponent);
    }

    auto edgeEffect = obj->GetProperty("edgeEffect");
    if (edgeEffect->IsNumber()) {
        JSViewSetProperty(&V2::ListItemComponent::SetEdgeEffect, edgeEffect->ToNumber<int32_t>(),
            SWIPE_EDGE_EFFECT_TABLE, V2::SwipeEdgeEffect::Spring);
    }
}

void JSListItem::SelectCallback(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        LOGE("fail to bind onSelect event due to info is not function");
        return;
    }

    RefPtr<JsMouseFunction> jsOnSelectFunc = AceType::MakeRefPtr<JsMouseFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onSelectId = [execCtx = args.GetExecutionContext(), func = std::move(jsOnSelectFunc)](bool isSelected) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->SelectExecute(isSelected);
    };
    auto listItem = AceType::DynamicCast<V2::ListItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!listItem) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListItemComponent>());
        return;
    }
    listItem->SetOnSelectId(onSelectId);
}

void JSListItem::JsBorderRadius(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderRadius(info);
    Dimension borderRadius;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], borderRadius)) {
        return;
    }
    JSViewSetProperty(&V2::ListItemComponent::SetBorderRadius, borderRadius);
}

void JSListItem::JsOnDragStart(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> DragItemInfo {
        DragItemInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);

        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            LOGE("builder param is not an object.");
            return itemInfo;
        }
        auto component = ParseDragItemComponent(ret);
        if (component) {
            LOGI("use custom builder param.");
            itemInfo.customComponent = component;
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if !defined(PREVIEW)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        component = ParseDragItemComponent(builderObj->GetProperty("builder"));
        itemInfo.customComponent = component;
        return itemInfo;
    };
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetOnDragStartId(onDragStartId);

    auto listItem = AceType::DynamicCast<V2::ListItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!listItem) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListItemComponent>());
        return;
    }
    listItem->MarkIsDragStart(true);
}

void JSListItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItem>::Declare("ListItem");
    JSClass<JSListItem>::StaticMethod("create", &JSListItem::Create);

    JSClass<JSListItem>::StaticMethod("sticky", &JSListItem::SetSticky);
    JSClass<JSListItem>::StaticMethod("editable", &JSListItem::SetEditable);
    JSClass<JSListItem>::StaticMethod("selectable", &JSListItem::SetSelectable);
    JSClass<JSListItem>::StaticMethod("onSelect", &JSListItem::SelectCallback);
    JSClass<JSListItem>::StaticMethod("borderRadius", &JSListItem::JsBorderRadius);
    JSClass<JSListItem>::StaticMethod("swipeAction", &JSListItem::SetSwiperAction);

    JSClass<JSListItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSListItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSListItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSListItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSListItem>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSListItem>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSListItem>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSListItem>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSListItem>::StaticMethod("onDragStart", &JSListItem::JsOnDragStart);

    JSClass<JSListItem>::Inherit<JSContainerBase>();
    JSClass<JSListItem>::Inherit<JSViewAbstract>();
    JSClass<JSListItem>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
