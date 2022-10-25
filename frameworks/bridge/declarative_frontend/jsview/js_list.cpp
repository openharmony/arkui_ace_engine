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

#include "bridge/declarative_frontend/jsview/js_list.h"

#include "base/geometry/axis.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_model_impl.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/list/list_model.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_position_controller.h"

namespace OHOS::Ace {

std::unique_ptr<ListModel> ListModel::instance_ = nullptr;

ListModel* ListModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ListModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ListModelNG());
        } else {
            instance_.reset(new Framework::ListModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSList::SetDirection(int32_t direction)
{
    ListModel::GetInstance()->SetListDirection(static_cast<Axis>(direction));
}

void JSList::SetScrollBar(int32_t scrollBar)
{
    ListModel::GetInstance()->SetScrollBar(static_cast<DisplayMode>(scrollBar));
}

void JSList::SetEdgeEffect(int32_t edgeEffect)
{
    ListModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
}

void JSList::SetEditMode(bool editMode)
{
    ListModel::GetInstance()->SetEditMode(editMode);
}

void JSList::SetCachedCount(int32_t cachedCount)
{
    ListModel::GetInstance()->SetCachedCount(cachedCount);
}

void JSList::SetScroller(RefPtr<JSScroller> scroller)
{
    if (scroller) {
        RefPtr<ScrollControllerBase> listController;
        if (Container::IsCurrentUseNewPipeline()) {
            listController.Swap(AceType::MakeRefPtr<NG::ListPositionController>());
        } else {
            listController.Swap(AceType::MakeRefPtr<V2::ListPositionController>());
        }
        scroller->SetController(listController);

        // Init scroll bar proxy.
        auto proxy = scroller->GetScrollBarProxy();
        if (!proxy) {
            proxy = AceType::MakeRefPtr<ScrollBarProxy>();
            scroller->SetScrollBarProxy(proxy);
        }
        ListModel::GetInstance()->SetScroller(listController, proxy);
    }
}

void JSList::Create(const JSCallbackInfo& args)
{
    ListModel::GetInstance()->Create();
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        Dimension space;
        if (ConvertFromJSValue(obj->GetProperty("space"), space) && space.IsValid()) {
            ListModel::GetInstance()->SetSpace(space);
        }
        int32_t initialIndex = 0;
        if (ConvertFromJSValue(obj->GetProperty("initialIndex"), initialIndex) && initialIndex >= 0) {
            ListModel::GetInstance()->SetInitialIndex(initialIndex);
        }
        JSRef<JSVal> scrollerValue = obj->GetProperty("scroller");
        if (scrollerValue->IsObject()) {
            void* scroller = JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>();
            RefPtr<JSScroller> jsScroller = Referenced::Claim(reinterpret_cast<JSScroller*>(scroller));
            SetScroller(jsScroller);
        }
    }

    args.ReturnSelf();
}

void JSList::SetChainAnimation(bool enableChainAnimation)
{
    ListModel::GetInstance()->SetChainAnimation(enableChainAnimation);
}

void JSList::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    ListModel::GetInstance()->SetHasWidth(true);
}

void JSList::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    ListModel::GetInstance()->SetHasHeight(true);
}

void JSList::SetListItemAlign(int32_t itemAlignment)
{
    ListModel::GetInstance()->SetListItemAlign(static_cast<V2::ListItemAlign>(itemAlignment));
}

void JSList::SetLanes(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    int32_t laneNum = 1;
    if (ParseJsInteger<int32_t>(info[0], laneNum)) {
        // when [lanes] is set, [laneConstrain_] of list component will be reset to std::nullopt
        ListModel::GetInstance()->SetLanes(laneNum);
        return;
    }
    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
    auto minLengthParam = jsObj->GetProperty("minLength");
    auto maxLengthParam = jsObj->GetProperty("maxLength");
    if (minLengthParam->IsNull() || maxLengthParam->IsNull()) {
        LOGW("minLength and maxLength are not both set");
        return;
    }
    Dimension minLengthValue;
    Dimension maxLengthValue;
    if (!ParseJsDimensionVp(minLengthParam, minLengthValue) || !ParseJsDimensionVp(maxLengthParam, maxLengthValue)) {
        LOGW("minLength param or maxLength param is invalid");
        return;
    }
    ListModel::GetInstance()->SetLaneConstrain(minLengthValue, maxLengthValue);
}

void JSList::SetSticky(int32_t sticky)
{
    ListModel::GetInstance()->SetSticky(static_cast<V2::StickyStyle>(sticky));
}

void JSList::SetDivider(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    Dimension strokeWidth;
    if (!ConvertFromJSValue(obj->GetProperty("strokeWidth"), strokeWidth) && strokeWidth.IsValid()) {
        LOGW("Invalid strokeWidth of divider");
        return;
    }

    V2::ItemDivider divider;
    divider.strokeWidth = strokeWidth;
    if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color)) {
        // Failed to get color from param, using default color defined in theme
        RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
        if (listTheme) {
            divider.color = listTheme->GetDividerColor();
        }
    }
    ConvertFromJSValue(obj->GetProperty("startMargin"), divider.startMargin);
    ConvertFromJSValue(obj->GetProperty("endMargin"), divider.endMargin);
    ListModel::GetInstance()->SetDivider(divider);

    args.ReturnSelf();
}

void JSList::ScrollCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const Dimension& scrollOffset, const V2::ScrollState& scrollState) {
            auto params = ConvertToJSValues(scrollOffset, scrollState);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
        ListModel::GetInstance()->SetOnScroll(std::move(onScroll));
    }
    args.ReturnSelf();
}

void JSList::ReachStartCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        ListModel::GetInstance()->SetOnReachStart(std::move(onReachStart));
    }
    args.ReturnSelf();
}

void JSList::ReachEndCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachEnd = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        ListModel::GetInstance()->SetOnReachEnd(std::move(onReachEnd));
    }
    args.ReturnSelf();
}

void JSList::ScrollStopCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStop = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        ListModel::GetInstance()->SetOnScrollStop(std::move(onScrollStop));
    }
    args.ReturnSelf();
}

void JSList::ItemDeleteCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onItemDelete = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                int32_t index) -> bool {
            auto params = ConvertToJSValues(index);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return true;
        };
        ListModel::GetInstance()->SetOnItemDelete(std::move(onItemDelete));
    }
    args.ReturnSelf();
}

void JSList::ItemMoveCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onItemMove = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                              int32_t start, int32_t end) -> bool {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
            auto params = ConvertToJSValues(start, end);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return true;
        };
        ListModel::GetInstance()->SetOnItemMove(std::move(onItemMove));
    }
    args.ReturnSelf();
}

void JSList::ScrollIndexCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollIndex = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const int32_t start, const int32_t end) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(start, end);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
        ListModel::GetInstance()->SetOnScrollIndex(std::move(onScrollIndex));
    }
    args.ReturnSelf();
}

void JSList::ItemDragStartCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragStart event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragFunc)](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) -> RefPtr<AceType> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        auto ret = func->ItemDragStartExecute(dragInfo, itemIndex);
        if (!ret->IsObject()) {
            LOGE("builder param is not an object.");
            return nullptr;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
        auto builder = builderObj->GetProperty("builder");
        if (!builder->IsFunction()) {
            LOGE("builder param is not a function.");
            return nullptr;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        if (!builderFunc) {
            LOGE("builder function is null.");
            return nullptr;
        }
        // use another VSP instance while executing the builder function
        ViewStackModel::GetInstance()->NewScope();
        {
            ACE_SCORING_EVENT("List.onItemDragStart.builder");
            builderFunc->Execute();
        }
        return ViewStackModel::GetInstance()->Finish();
    };
    ListModel::GetInstance()->SetOnItemDragStart(std::move(onItemDragStart));
}

void JSList::ItemDragEnterCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragEnter event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragEnter = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                               const ItemDragInfo& dragInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDragEnter");
        func->ItemDragEnterExecute(dragInfo);
    };
    ListModel::GetInstance()->SetOnItemDragEnter(std::move(onItemDragEnter));
}

void JSList::ItemDragMoveCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragMove event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragMove = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                              const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDragMove");
        func->ItemDragMoveExecute(dragInfo, itemIndex, insertIndex);
    };
    ListModel::GetInstance()->SetOnItemDragMove(std::move(onItemDragMove));
}

void JSList::ItemDragLeaveCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragLeave event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragLeave = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDragLeave");
        func->ItemDragLeaveExecute(dragInfo, itemIndex);
    };
    ListModel::GetInstance()->SetOnItemDragLeave(std::move(onItemDragLeave));
}

void JSList::ItemDropCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDrop event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDrop = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                          const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDrop");
        func->ItemDropExecute(dragInfo, itemIndex, insertIndex, isSuccess);
    };
    ListModel::GetInstance()->SetOnItemDrop(onItemDrop);
}

void JSList::SetMultiSelectable(bool multiSelectable)
{
    ListModel::GetInstance()->SetMultiSelectable(multiSelectable);
}

void JSList::ScrollBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollBegin = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const Dimension& dx, const Dimension& dy) -> ScrollInfo {
            ScrollInfo scrollInfo { .dx = dx, .dy = dy };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollInfo);
            auto params = ConvertToJSValues(dx, dy);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                LOGE("Error calling onScrollBegin, result is empty.");
                return scrollInfo;
            }

            if (!result->IsObject()) {
                LOGE("Error calling onScrollBegin, result is not object.");
                return scrollInfo;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("dxRemain");
            if (dxRemainValue->IsNumber()) {
                scrollInfo.dx = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            auto dyRemainValue = resObj->GetProperty("dyRemain");
            if (dyRemainValue->IsNumber()) {
                scrollInfo.dy = Dimension(dyRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollInfo;
        };
        ListModel::GetInstance()->SetOnScrollBegin(std::move(onScrollBegin));
    }
}

void JSList::JSBind(BindingTarget globalObj)
{
    JSClass<JSList>::Declare("List");
    JSClass<JSList>::StaticMethod("create", &JSList::Create);

    JSClass<JSList>::StaticMethod("width", &JSList::JsWidth);
    JSClass<JSList>::StaticMethod("height", &JSList::JsHeight);
    JSClass<JSList>::StaticMethod("listDirection", &JSList::SetDirection);
    JSClass<JSList>::StaticMethod("scrollBar", &JSList::SetScrollBar);
    JSClass<JSList>::StaticMethod("edgeEffect", &JSList::SetEdgeEffect);
    JSClass<JSList>::StaticMethod("divider", &JSList::SetDivider);
    JSClass<JSList>::StaticMethod("editMode", &JSList::SetEditMode);
    JSClass<JSList>::StaticMethod("cachedCount", &JSList::SetCachedCount);
    JSClass<JSList>::StaticMethod("chainAnimation", &JSList::SetChainAnimation);
    JSClass<JSList>::StaticMethod("multiSelectable", &JSList::SetMultiSelectable);
    JSClass<JSList>::StaticMethod("alignListItem", &JSList::SetListItemAlign);
    JSClass<JSList>::StaticMethod("lanes", &JSList::SetLanes);
    JSClass<JSList>::StaticMethod("sticky", &JSList::SetSticky);

    JSClass<JSList>::StaticMethod("onScroll", &JSList::ScrollCallback);
    JSClass<JSList>::StaticMethod("onReachStart", &JSList::ReachStartCallback);
    JSClass<JSList>::StaticMethod("onReachEnd", &JSList::ReachEndCallback);
    JSClass<JSList>::StaticMethod("onScrollStop", &JSList::ScrollStopCallback);
    JSClass<JSList>::StaticMethod("onItemDelete", &JSList::ItemDeleteCallback);
    JSClass<JSList>::StaticMethod("onItemMove", &JSList::ItemMoveCallback);
    JSClass<JSList>::StaticMethod("onScrollIndex", &JSList::ScrollIndexCallback);
    JSClass<JSList>::StaticMethod("onScrollBegin", &JSList::ScrollBeginCallback);

    JSClass<JSList>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSList>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSList>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSList>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSList>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSList>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSList>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSList>::StaticMethod("onItemDragStart", &JSList::ItemDragStartCallback);
    JSClass<JSList>::StaticMethod("onItemDragEnter", &JSList::ItemDragEnterCallback);
    JSClass<JSList>::StaticMethod("onItemDragMove", &JSList::ItemDragMoveCallback);
    JSClass<JSList>::StaticMethod("onItemDragLeave", &JSList::ItemDragLeaveCallback);
    JSClass<JSList>::StaticMethod("onItemDrop", &JSList::ItemDropCallback);
    JSClass<JSList>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSList>::Inherit<JSContainerBase>();
    JSClass<JSList>::Inherit<JSViewAbstract>();
    JSClass<JSList>::Bind(globalObj);
}

} // namespace OHOS::Ace::Framework
