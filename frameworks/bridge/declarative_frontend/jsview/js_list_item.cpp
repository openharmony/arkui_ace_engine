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
#include <functional>

#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_item_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ListItemModel> ListItemModel::instance_ = nullptr;

ListItemModel* ListItemModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ListItemModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ListItemModelNG());
        } else {
            instance_.reset(new Framework::ListItemModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSListItem::Create(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUsePartialUpdate()) {
        CreateForPartialUpdate(args);
        return;
    }
    std::string type;
    if (args.Length() >= 1 && args[0]->IsString()) {
        type = args[0]->ToString();
    }

    ListItemModel::GetInstance()->Create();
    if (!type.empty()) {
        ListItemModel::GetInstance()->SetType(type);
    }
    args.ReturnSelf();
}

void JSListItem::CreateForPartialUpdate(const JSCallbackInfo& args)
{
    if (args.Length() < 2 || !args[0]->IsFunction()) {
        LOGE("Expected deep render function parameter");
        ListItemModel::GetInstance()->Create();
        return;
    }
    RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), JSRef<JSFunc>::Cast(args[0]));

    if (!args[1]->IsBoolean()) {
        LOGE("Expected isLazy parameter");
        return;
    }
    const bool isLazy = args[1]->ToBoolean();
    if (!isLazy) {
        ListItemModel::GetInstance()->Create();
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
        ListItemModel::GetInstance()->Create(std::move(listItemDeepRenderFunc));
        ListItemModel::GetInstance()->SetIsLazyCreating(isLazy);
    }
    args.ReturnSelf();
}

void JSListItem::SetSticky(int32_t sticky)
{
    ListItemModel::GetInstance()->SetSticky(static_cast<V2::StickyMode>(sticky));
}

void JSListItem::SetEditable(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        LOGW("Not enough params");
        return;
    }

    if (args[0]->IsBoolean()) {
        uint32_t value = args[0]->ToBoolean() ? V2::EditMode::DELETABLE | V2::EditMode::MOVABLE : V2::EditMode::SHAM;
        ListItemModel::GetInstance()->SetEditMode(value);
        return;
    }

    if (args[0]->IsNumber()) {
        auto value = args[0]->ToNumber<uint32_t>();
        ListItemModel::GetInstance()->SetEditMode(value);
        return;
    }
    LOGW("Invalid params, unknown type");
}

void JSListItem::SetSelectable(bool selectable)
{
    ListItemModel::GetInstance()->SetSelectable(selectable);
}

void JSListItem::SetSwiperAction(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        LOGE("fail to bind SwiperAction event due to info is not object");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    std::function<void()> startAction;
    auto startObject = obj->GetProperty("start");
    if (startObject->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(startObject));
        startAction = [builderFunc]() { builderFunc->Execute(); };
    }

    std::function<void()> endAction;
    auto endObject = obj->GetProperty("end");
    if (endObject->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(endObject));
        endAction = [builderFunc]() { builderFunc->Execute(); };
    }

    auto edgeEffect = obj->GetProperty("edgeEffect");
    V2::SwipeEdgeEffect swipeEdgeEffect = V2::SwipeEdgeEffect::Spring;
    if (edgeEffect->IsNumber()) {
        swipeEdgeEffect = static_cast<V2::SwipeEdgeEffect>(edgeEffect->ToNumber<int32_t>());
    }
    ListItemModel::GetInstance()->SetSwiperAction(std::move(startAction), std::move(endAction), swipeEdgeEffect);
}

void JSListItem::SelectCallback(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        LOGE("fail to bind onSelect event due to info is not function");
        return;
    }

    RefPtr<JsMouseFunction> jsOnSelectFunc = AceType::MakeRefPtr<JsMouseFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onSelect = [execCtx = args.GetExecutionContext(), func = std::move(jsOnSelectFunc)](bool isSelected) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->SelectExecute(isSelected);
    };
    ListItemModel::GetInstance()->SetSelectCallback(std::move(onSelect));
}

void JSListItem::JsBorderRadius(const JSCallbackInfo& info)
{
    JSViewAbstract::JsBorderRadius(info);
    Dimension borderRadius;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], borderRadius)) {
        return;
    }
    ListItemModel::GetInstance()->SetBorderRadius(borderRadius);
}

void JSListItem::JsOnDragStart(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
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
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        component = ParseDragItemComponent(builderObj->GetProperty("builder"));
        itemInfo.customComponent = component;
        return itemInfo;
    };
    ListItemModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
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
