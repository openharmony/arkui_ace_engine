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
#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_model_impl.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/list/list_model.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_position_controller.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

namespace OHOS::Ace {

std::unique_ptr<ListModel> ListModel::instance_ = nullptr;
std::mutex ListModel::mutex_;

ListModel* ListModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

const std::vector<V2::ScrollSnapAlign> SCROLL_SNAP_ALIGN = { V2::ScrollSnapAlign::NONE, V2::ScrollSnapAlign::START,
    V2::ScrollSnapAlign::CENTER, V2::ScrollSnapAlign::END };

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

void JSList::SetCachedCount(const JSCallbackInfo& info)
{
    int32_t cachedCount = 1;
    ParseJsInteger<int32_t>(info[0], cachedCount);
    cachedCount = cachedCount < 0 ? 1 : cachedCount;
    ListModel::GetInstance()->SetCachedCount(cachedCount);
}

void JSList::SetScroller(RefPtr<JSScroller> scroller)
{
    if (scroller) {
        RefPtr<ScrollControllerBase> listController = ListModel::GetInstance()->CreateScrollController();
        scroller->SetController(listController);

        // Init scroll bar proxy.
        auto proxy = scroller->GetScrollBarProxy();
        if (!proxy) {
            if (Container::IsCurrentUseNewPipeline()) {
                proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
            } else {
                proxy = AceType::MakeRefPtr<ScrollBarProxy>();
            }
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
        JSRef<JSVal> spaceValue = obj->GetProperty("space");
        if (!spaceValue->IsNull()) {
            CalcDimension space;
            ConvertFromJSValue(spaceValue, space);
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

void JSList::SetChainAnimationOptions(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (info[0]->IsObject()) {
        RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
        CHECK_NULL_VOID(listTheme);
        ChainAnimationOptions options = {
            .minSpace = listTheme->GetChainMinSpace(),
            .maxSpace = listTheme->GetChainMaxSpace(),
            .conductivity = listTheme->GetChainConductivity(),
            .intensity = listTheme->GetChainIntensity(),
            .edgeEffect = 0,
            .stiffness = listTheme->GetChainStiffness(),
            .damping = listTheme->GetChainDamping(),
        };
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        ParseJsDimensionVp(jsObj->GetProperty("minSpace"), options.minSpace);
        ParseJsDimensionVp(jsObj->GetProperty("maxSpace"), options.maxSpace);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("conductivity"), options.conductivity);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("intensity"), options.intensity);
        JSViewAbstract::ParseJsInt32(jsObj->GetProperty("edgeEffect"), options.edgeEffect);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("stiffness"), options.stiffness);
        JSViewAbstract::ParseJsDouble(jsObj->GetProperty("damping"), options.damping);
        ListModel::GetInstance()->SetChainAnimationOptions(options);
    }
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
        ListModel::GetInstance()->SetLaneConstrain(-1.0_vp, -1.0_vp);
        return;
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        auto minLengthParam = jsObj->GetProperty("minLength");
        auto maxLengthParam = jsObj->GetProperty("maxLength");
        if (minLengthParam->IsNull() || maxLengthParam->IsNull()) {
            LOGW("minLength and maxLength are not both set");
            return;
        }
        CalcDimension minLengthValue;
        CalcDimension maxLengthValue;
        if (!ParseJsDimensionVp(minLengthParam, minLengthValue)
            || !ParseJsDimensionVp(maxLengthParam, maxLengthValue)) {
            LOGW("minLength param or maxLength param is invalid");
            ListModel::GetInstance()->SetLanes(1);
            ListModel::GetInstance()->SetLaneConstrain(-1.0_vp, -1.0_vp);
            return;
        }
        ListModel::GetInstance()->SetLaneConstrain(minLengthValue, maxLengthValue);
        ListModel::GetInstance()->SetLanes(1);
    }
}

void JSList::SetSticky(int32_t sticky)
{
    ListModel::GetInstance()->SetSticky(static_cast<V2::StickyStyle>(sticky));
}

void JSList::SetScrollSnapAlign(int32_t scrollSnapAlign)
{
    V2::ScrollSnapAlign param;
    if (scrollSnapAlign < 0 || scrollSnapAlign >= static_cast<int32_t>(SCROLL_SNAP_ALIGN.size())) {
        param = V2::ScrollSnapAlign::NONE;
    } else {
        param = V2::ScrollSnapAlign(scrollSnapAlign);
    }
    ListModel::GetInstance()->SetScrollSnapAlign(param);
}

void JSList::SetDivider(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    V2::ItemDivider divider;
    if (!ConvertFromJSValue(obj->GetProperty("strokeWidth"), divider.strokeWidth)) {
        LOGW("Invalid strokeWidth of divider");
        divider.strokeWidth.Reset();
    }
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

void JSList::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        ListModel::GetInstance()->SetNestedScroll(nestedOpt);
        LOGW("Invalid params");
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        LOGW("ScrollFroward params invalid");
        froward = 0;
    }
    int32_t backward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        LOGW("ScrollFroward params invalid");
        backward = 0;
    }
    nestedOpt.forward = static_cast<NestedScrollMode>(froward);
    nestedOpt.backward = static_cast<NestedScrollMode>(backward);
    ListModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSList::ScrollCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
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

void JSList::ScrollStartCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        ListModel::GetInstance()->SetOnScrollStart(std::move(onScrollStart));
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
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (!result.IsEmpty() && result->IsBoolean()) {
                return result->ToBoolean();
            }
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
                                 const CalcDimension& dx, const CalcDimension& dy) -> ScrollInfo {
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
                scrollInfo.dx = CalcDimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            auto dyRemainValue = resObj->GetProperty("dyRemain");
            if (dyRemainValue->IsNumber()) {
                scrollInfo.dy = CalcDimension(dyRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollInfo;
        };
        ListModel::GetInstance()->SetOnScrollBegin(std::move(onScrollBegin));
    }
}

void JSList::ScrollFrameBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollBegin = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
            ScrollFrameResult scrollRes { .offset = offset };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollRes);
            auto params = ConvertToJSValues(offset, state);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                LOGE("Error calling onScrollFrameBegin, result is empty.");
                return scrollRes;
            }

            if (!result->IsObject()) {
                LOGE("Error calling onScrollFrameBegin, result is not object.");
                return scrollRes;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("offsetRemain");
            if (dxRemainValue->IsNumber()) {
                scrollRes.offset = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollRes;
        };
        ListModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollBegin));
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
    JSClass<JSList>::StaticMethod("chainAnimationOptions", &JSList::SetChainAnimationOptions);
    JSClass<JSList>::StaticMethod("multiSelectable", &JSList::SetMultiSelectable);
    JSClass<JSList>::StaticMethod("alignListItem", &JSList::SetListItemAlign);
    JSClass<JSList>::StaticMethod("lanes", &JSList::SetLanes);
    JSClass<JSList>::StaticMethod("sticky", &JSList::SetSticky);
    JSClass<JSList>::StaticMethod("nestedScroll", &JSList::SetNestedScroll);
    JSClass<JSList>::StaticMethod("scrollSnapAlign", &JSList::SetScrollSnapAlign);

    JSClass<JSList>::StaticMethod("onScroll", &JSList::ScrollCallback);
    JSClass<JSList>::StaticMethod("onReachStart", &JSList::ReachStartCallback);
    JSClass<JSList>::StaticMethod("onReachEnd", &JSList::ReachEndCallback);
    JSClass<JSList>::StaticMethod("onScrollStart", &JSList::ScrollStartCallback);
    JSClass<JSList>::StaticMethod("onScrollStop", &JSList::ScrollStopCallback);
    JSClass<JSList>::StaticMethod("onItemDelete", &JSList::ItemDeleteCallback);
    JSClass<JSList>::StaticMethod("onItemMove", &JSList::ItemMoveCallback);
    JSClass<JSList>::StaticMethod("onScrollIndex", &JSList::ScrollIndexCallback);
    JSClass<JSList>::StaticMethod("onScrollBegin", &JSList::ScrollBeginCallback);
    JSClass<JSList>::StaticMethod("onScrollFrameBegin", &JSList::ScrollFrameBeginCallback);

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

    JSClass<JSList>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
