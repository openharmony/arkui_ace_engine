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
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_list_item_theme.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_item_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
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

void JSListItem::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSListItem][pop]", &JSListItem::Pop);
    }
    JSContainerBase::Pop();
    ListItemModel::GetInstance()->OnDidPop();
}

void JSListItem::CreateForPartialUpdate(const JSCallbackInfo& args)
{
    const int32_t ARGS_LENGTH = 2;
    auto len = args.Length();
    if (len < ARGS_LENGTH) {
        ListItemModel::GetInstance()->Create();
        return;
    }
    JSRef<JSVal> arg0 = args[0];
    if (!arg0->IsFunction()) {
        ListItemModel::GetInstance()->Create();
        return;
    }

    JSRef<JSVal> arg1 = args[1];
    if (!arg1->IsBoolean()) {
        return;
    }
    const bool isLazy = arg1->ToBoolean();

    V2::ListItemStyle listItemStyle = V2::ListItemStyle::NONE;
    if (len > ARGS_LENGTH && args[ARGS_LENGTH]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[ARGS_LENGTH]);
        JSRef<JSVal> styleObj = obj->GetProperty("style");
        listItemStyle = styleObj->IsNumber() ? static_cast<V2::ListItemStyle>(styleObj->ToNumber<int32_t>())
                                             : V2::ListItemStyle::NONE;
    }

    if (!isLazy) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ListItemModel::GetInstance()->Create(nullptr, listItemStyle);
        } else {
            ListItemModel::GetInstance()->Create();
        }
    } else {
        auto deepRenderFunc = JSRef<JSFunc>::Cast(arg0);
        JSListItemTheme::ObtainDeepRenderFuncForThemeSupport(args.GetVm(), deepRenderFunc);
        RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), deepRenderFunc);
        auto listItemDeepRenderFunc = [execCtx = args.GetExecutionContext(),
                                          jsDeepRenderFunc = std::move(jsDeepRender)](int32_t nodeId) {
            ACE_SCOPED_TRACE("JSListItem::ExecuteDeepRender");
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            JSRef<JSVal> jsParams[2];
            jsParams[0] = JSRef<JSVal>::Make(ToJSValue(nodeId));
            jsParams[1] = JSRef<JSVal>::Make(ToJSValue(true));
            jsDeepRenderFunc->ExecuteJS(2, jsParams);
        }; // listItemDeepRenderFunc lambda
        ListItemModel::GetInstance()->Create(std::move(listItemDeepRenderFunc), listItemStyle);
        ListItemModel::GetInstance()->SetIsLazyCreating(isLazy);
    }
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

void JSListItem::SetSelectable(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool selectable = true;
    if (info[0]->IsBoolean()) {
        selectable = info[0]->ToBoolean();
    }
    ListItemModel::GetInstance()->SetSelectable(selectable);
}

void JSListItem::SetSelected(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool select = false;
    JSRef<JSVal> changeEventVal;
    auto selectedVal = info[0];
    if (selectedVal->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(selectedVal);
        selectedVal = obj->GetProperty("value");
        changeEventVal = obj->GetProperty("$value");
    } else if (info.Length() > 1) {
        changeEventVal = info[1];
    }
    if (selectedVal->IsBoolean()) {
        select = selectedVal->ToBoolean();
    }
    ListItemModel::GetInstance()->SetSelected(select);
    if (changeEventVal->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                               bool param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ListItem.ChangeEvent");
            auto newJSVal = JSRef<JSVal>::Make(ToJSValue(param));
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJS(1, &newJSVal);
        };
        ListItemModel::GetInstance()->SetSelectChangeEvent(std::move(changeEvent));
    }
}

void JSListItem::JsParseDeleteArea(const JsiExecutionContext& context, const JSRef<JSVal>& jsValue,
    bool isStartArea, NG::FrameNode* node)
{
    auto deleteAreaObj = JSRef<JSObject>::Cast(jsValue);

    auto onAction = deleteAreaObj->GetProperty("onAction");
    std::function<void()> onActionCallback;
    if (onAction->IsFunction()) {
        onActionCallback = [execCtx = context, func = JSRef<JSFunc>::Cast(onAction)]() {
            func->Call(JSRef<JSObject>());
            return;
        };
    }
    auto onEnterActionArea = deleteAreaObj->GetProperty("onEnterActionArea");
    std::function<void()> onEnterActionAreaCallback;
    if (onEnterActionArea->IsFunction()) {
        onEnterActionAreaCallback = [execCtx = context,
                                        func = JSRef<JSFunc>::Cast(onEnterActionArea)]() {
            func->Call(JSRef<JSObject>());
            return;
        };
    }
    auto onExitActionArea = deleteAreaObj->GetProperty("onExitActionArea");
    std::function<void()> onExitActionAreaCallback;
    if (onExitActionArea->IsFunction()) {
        onExitActionAreaCallback = [execCtx = context,
                                       func = JSRef<JSFunc>::Cast(onExitActionArea)]() {
            func->Call(JSRef<JSObject>());
            return;
        };
    }
    auto actionAreaDistance = deleteAreaObj->GetProperty("actionAreaDistance");
    CalcDimension length;
    if (!ParseJsDimensionVp(actionAreaDistance, length)) {
        auto listItemTheme = GetTheme<ListItemTheme>();
        length = listItemTheme->GetDeleteDistance();
    }
    auto onStateChange = deleteAreaObj->GetProperty("onStateChange");
    std::function<void(SwipeActionState state)> onStateChangeCallback;
    if (onStateChange->IsFunction()) {
        onStateChangeCallback = [execCtx = context,
                                    func = JSRef<JSFunc>::Cast(onStateChange)](SwipeActionState state) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(state);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
    }
    ParseBuilder(deleteAreaObj, std::move(onActionCallback), std::move(onEnterActionAreaCallback),
        std::move(onExitActionAreaCallback), std::move(onStateChangeCallback), length, isStartArea, node);
}

void JSListItem::SetSwiperAction(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        ListItemModel::GetInstance()->SetDeleteArea(
            nullptr, nullptr, nullptr, nullptr, nullptr, Dimension(0, DimensionUnit::VP), true);
        ListItemModel::GetInstance()->SetSwiperAction(nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::Spring);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    ParseSwiperAction(obj, args.GetExecutionContext());
}

void JSListItem::ParseSwiperAction(const JSRef<JSObject>& obj, const JsiExecutionContext& context, NG::FrameNode* node)
{
    std::function<void()> startAction;
    auto startObject = obj->GetProperty("start");
    if (startObject->IsObject()) {
        if (startObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(startObject));
            startAction = [builderFunc]() { builderFunc->Execute(); };
            ListItemModel::GetInstance()->SetDeleteArea(
                std::move(startAction), nullptr, nullptr, nullptr, nullptr,
                Dimension(0, DimensionUnit::VP), true, node);
        } else {
            JsParseDeleteArea(context, startObject, true, node);
        }
    } else {
        ListItemModel::GetInstance()->SetDeleteArea(
            nullptr, nullptr, nullptr, nullptr, nullptr, Dimension(0, DimensionUnit::VP), true, node);
    }

    std::function<void()> endAction;
    auto endObject = obj->GetProperty("end");
    if (endObject->IsObject()) {
        if (endObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(endObject));
            endAction = [builderFunc]() { builderFunc->Execute(); };
            ListItemModel::GetInstance()->SetDeleteArea(
                std::move(endAction), nullptr, nullptr, nullptr, nullptr,
                Dimension(0, DimensionUnit::VP), false, node);
        } else {
            JsParseDeleteArea(context, endObject, false, node);
        }
    } else {
        ListItemModel::GetInstance()->SetDeleteArea(
            nullptr, nullptr, nullptr, nullptr, nullptr, Dimension(0, DimensionUnit::VP), false, node);
    }

    auto edgeEffect = obj->GetProperty("edgeEffect");
    V2::SwipeEdgeEffect swipeEdgeEffect = V2::SwipeEdgeEffect::Spring;
    if (edgeEffect->IsNumber()) {
        swipeEdgeEffect = static_cast<V2::SwipeEdgeEffect>(edgeEffect->ToNumber<int32_t>());
    }

    auto onOffsetChangeFunc = obj->GetProperty("onOffsetChange");
    std::function<void(int32_t offset)> onOffsetChangeCallback;
    if (onOffsetChangeFunc->IsFunction()) {
        onOffsetChangeCallback = [execCtx = context,
                                     func = JSRef<JSFunc>::Cast(onOffsetChangeFunc)](int32_t offset) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(offset);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
    }

    // use SetDeleteArea to update builder function
    ListItemModel::GetInstance()->SetSwiperAction(
        nullptr, nullptr, std::move(onOffsetChangeCallback), swipeEdgeEffect, node);
}

void JSListItem::ParseBuilder(const JSRef<JSObject>& obj, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea, NG::FrameNode* node)
{
    if (obj->HasProperty("builderComponent")) {
        auto builderComponentObject = obj->GetProperty("builderComponent");
        RefPtr<NG::FrameNode> builderNode;
        ParseBuilderComponentContent(builderComponentObject, builderNode);
        ListItemModel::GetInstance()->SetDeleteAreaWithFrameNode(builderNode, std::move(onDelete),
            std::move(onEnterDeleteArea), std::move(onExitDeleteArea), std::move(onStateChange), length, isStartArea,
            node);
    } else {
        std::function<void()> builderAction;
        auto builderObject = obj->GetProperty("builder");
        if (builderObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builderObject));
            builderAction = [builderFunc]() { builderFunc->Execute(); };
        }
        ListItemModel::GetInstance()->SetDeleteArea(std::move(builderAction), std::move(onDelete),
            std::move(onEnterDeleteArea), std::move(onExitDeleteArea), std::move(onStateChange), length, isStartArea,
            node);
    }
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto node = frameNode.Upgrade();
    if (node && node->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FIFTEEN)) {
        JSViewAbstract::JsOnDragStart(info);
        return;
    }
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc),
                           targetNode = frameNode](
                           const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);
        PipelineContext::SetCallBackNode(targetNode);
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
void JSListItem::ParseBuilderComponentContent(const JSRef<JSVal>& contentParam, RefPtr<NG::FrameNode>& refPtrFrameNode)
{
    if (!contentParam->IsObject()) {
        return;
    }
    JSRef<JSObject> contentObject = JSRef<JSObject>::Cast(contentParam);
    JSRef<JSVal> builderNodeParam = contentObject->GetProperty("builderNode_");
    if (!builderNodeParam->IsObject()) {
        return ;
    }
    JSRef<JSObject> builderNodeObject = JSRef<JSObject>::Cast(builderNodeParam);
    JSRef<JSVal> nodeptr = builderNodeObject->GetProperty("nodePtr_");
    if (nodeptr.IsEmpty()) {
        return ;
    }
    const auto* vm = nodeptr->GetEcmaVM();
    auto* node = nodeptr->GetLocalHandle()->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    refPtrFrameNode = AceType::Claim(frameNode);
}

void JSListItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItem>::Declare("ListItem");
    JSClass<JSListItem>::StaticMethod("create", &JSListItem::Create);
    JSClass<JSListItem>::StaticMethod("pop", &JSListItem::Pop);

    JSClass<JSListItem>::StaticMethod("sticky", &JSListItem::SetSticky);
    JSClass<JSListItem>::StaticMethod("editable", &JSListItem::SetEditable);
    JSClass<JSListItem>::StaticMethod("selectable", &JSListItem::SetSelectable);
    JSClass<JSListItem>::StaticMethod("onSelect", &JSListItem::SelectCallback);
    JSClass<JSListItem>::StaticMethod("borderRadius", &JSListItem::JsBorderRadius);
    JSClass<JSListItem>::StaticMethod("swipeAction", &JSListItem::SetSwiperAction);
    JSClass<JSListItem>::StaticMethod("selected", &JSListItem::SetSelected);

    JSClass<JSListItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSListItem>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSListItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSListItem>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
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
