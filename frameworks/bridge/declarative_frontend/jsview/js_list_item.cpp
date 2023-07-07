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

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_item_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ListItemModel> ListItemModel::instance_ = nullptr;
std::mutex ListItemModel::mutex_;

ListItemModel* ListItemModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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

    V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE;
    if (args[2]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[2]);
        JSRef<JSVal> styleObj = obj->GetProperty("style");
        listItemStyle = styleObj->IsNumber() ? static_cast<V2::ListItemStyle>(styleObj->ToNumber<int32_t>())
                                             : V2::ListItemStyle::NONE;
    }

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
        ListItemModel::GetInstance()->Create(std::move(listItemDeepRenderFunc), listItemStyle);
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
}

void JSListItem::SetSelectable(bool selectable)
{
    ListItemModel::GetInstance()->SetSelectable(selectable);
}

void JSListItem::SetSelected(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have 1 or 2 arguments");
        return;
    }
    bool select = false;
    if (info[0]->IsBoolean()) {
        select = info[0]->ToBoolean();
    }
    ListItemModel::GetInstance()->SetSelected(select);

    if (info.Length() > 1 && info[1]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
        auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](bool param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ListItem.ChangeEvent");
            auto newJSVal = JSRef<JSVal>::Make(ToJSValue(param));
            func->ExecuteJS(1, &newJSVal);
        };
        ListItemModel::GetInstance()->SetSelectChangeEvent(std::move(changeEvent));
    }
}

void JSListItem::JsParseDeleteArea(const JSCallbackInfo& args, const JSRef<JSVal>& jsValue, bool isStartArea)
{
    auto deleteAreaObj = JSRef<JSObject>::Cast(jsValue);
    auto listItemTheme = GetTheme<ListItemTheme>();

    std::function<void()> builderAction;
    auto builderObject = deleteAreaObj->GetProperty("builder");
    if (builderObject->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builderObject));
        builderAction = [builderFunc]() { builderFunc->Execute(); };
    }
    auto defaultDeleteAnimation = deleteAreaObj->GetProperty("useDefaultDeleteAnimation");
    bool useDefaultDeleteAnimation = true;
    if (defaultDeleteAnimation->IsBoolean()) {
        useDefaultDeleteAnimation = defaultDeleteAnimation->ToBoolean();
    }
    auto onDelete = deleteAreaObj->GetProperty("onDelete");
    std::function<void()> onDeleteCallback;
    if (onDelete->IsFunction()) {
        onDeleteCallback = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onDelete)]() {
            func->Call(JSRef<JSObject>());
            return;
        };
    }
    auto onEnterDeleteArea = deleteAreaObj->GetProperty("onEnterDeleteArea");
    std::function<void()> onEnterDeleteAreaCallback;
    if (onEnterDeleteArea->IsFunction()) {
        onEnterDeleteAreaCallback = [execCtx = args.GetExecutionContext(),
                                        func = JSRef<JSFunc>::Cast(onEnterDeleteArea)]() {
            func->Call(JSRef<JSObject>());
            return;
        };
    }
    auto onExitDeleteArea = deleteAreaObj->GetProperty("onExitDeleteArea");
    std::function<void()> onExitDeleteAreaCallback;
    if (onExitDeleteArea->IsFunction()) {
        onExitDeleteAreaCallback = [execCtx = args.GetExecutionContext(),
                                       func = JSRef<JSFunc>::Cast(onExitDeleteArea)]() {
            func->Call(JSRef<JSObject>());
            return;
        };
    }
    auto deleteAreaDistance = deleteAreaObj->GetProperty("deleteAreaDistance");
    CalcDimension length;
    if (!ParseJsDimensionVp(deleteAreaDistance, length)) {
        length = listItemTheme->GetDeleteDistance();
    }

    ListItemModel::GetInstance()->SetDeleteArea(std::move(builderAction), useDefaultDeleteAnimation,
        std::move(onDeleteCallback), std::move(onEnterDeleteAreaCallback), std::move(onExitDeleteAreaCallback), length,
        isStartArea);
}

void JSListItem::SetSwiperAction(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    std::function<void()> startAction;
    auto startObject = obj->GetProperty("start");
    if (startObject->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(startObject));
        startAction = [builderFunc]() { builderFunc->Execute(); };
    } else if (startObject->IsObject()) {
        JsParseDeleteArea(args, startObject, true);
    }

    std::function<void()> endAction;
    auto endObject = obj->GetProperty("end");
    if (endObject->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(endObject));
        endAction = [builderFunc]() { builderFunc->Execute(); };
    } else if (endObject->IsObject()) {
        JsParseDeleteArea(args, endObject, false);
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
    CalcDimension borderRadius;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], borderRadius)) {
        return;
    }
    ListItemModel::GetInstance()->SetBorderRadius(borderRadius);
}

void JSListItem::JsOnDragStart(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
                           const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);

        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            return itemInfo;
        }
        auto node = ParseDragNode(ret);
        if (node) {
            itemInfo.node = node;
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        node = ParseDragNode(builderObj->GetProperty("builder"));
        itemInfo.node = node;
        return itemInfo;
    };
#ifdef NG_BUILD
    ViewAbstractModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
#else
    if (Container::IsCurrentUseNewPipeline()) {
        ViewAbstractModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
    } else {
        ListItemModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
    }
#endif
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
    JSClass<JSListItem>::StaticMethod("selected", &JSListItem::SetSelected);

    JSClass<JSListItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSListItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSListItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSListItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSListItem>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSListItem>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSListItem>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSListItem>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSListItem>::StaticMethod("onDragStart", &JSListItem::JsOnDragStart);

    JSClass<JSListItem>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
