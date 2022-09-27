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
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/pattern/list/list_view.h"
#include "core/components_v2/list/list_component.h"
#include "core/components_v2/list/list_position_controller.h"

namespace OHOS::Ace::Framework {
namespace {

using ThisComponent = V2::ListComponent;

constexpr DisplayMode DISPLAY_MODE_TABLE[] = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
constexpr EdgeEffect EDGE_EFFECT_TABLE[] = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
constexpr Axis DIRECTION_TABLE[] = { Axis::VERTICAL, Axis::HORIZONTAL };
constexpr V2::ListItemAlign LIST_ITEM_ALIGN_TABLE[] = { V2::ListItemAlign::START, V2::ListItemAlign::CENTER,
    V2::ListItemAlign::END };

} // namespace

void JSList::SetDirection(int32_t direction)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ListView::SetListDirection(static_cast<Axis>(direction));
        return;
    }
    JSViewSetProperty(&V2::ListComponent::SetDirection, direction, DIRECTION_TABLE, Axis::VERTICAL);
}

void JSList::SetScrollBar(int32_t scrollBar)
{
    if (Container::IsCurrentUseNewPipeline()) {
        LOGW("ScrollBar is not supported");
        return;
    }
    JSViewSetProperty(&V2::ListComponent::SetScrollBar, scrollBar, DISPLAY_MODE_TABLE, DisplayMode::OFF);
}

void JSList::SetEdgeEffect(int32_t edgeEffect)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ListView::SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
        return;
    }
    JSViewSetProperty(&V2::ListComponent::SetEdgeEffect, edgeEffect, EDGE_EFFECT_TABLE, EdgeEffect::SPRING);
}

void JSList::SetEditMode(bool editMode)
{
    JSViewSetProperty(&V2::ListComponent::SetEditMode, editMode);
}

void JSList::SetCachedCount(int32_t cachedCount)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ListView::SetCachedCount(cachedCount);
        return;
    }
    JSViewSetProperty(&V2::ListComponent::SetCachedCount, cachedCount);
}

void JSList::Create(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ListView::Create();
        if (args.Length() >= 1 && args[0]->IsObject()) {
            JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
            Dimension space;
            if (ConvertFromJSValue(obj->GetProperty("space"), space) && space.IsValid()) {
                NG::ListView::SetSpace(space);
            }
            int32_t initialIndex = 0;
            if (ConvertFromJSValue(obj->GetProperty("initialIndex"), initialIndex) && initialIndex >= 0) {
                NG::ListView::SetInitialIndex(initialIndex);
            }
        }
        return;
    }

    auto listComponent = AceType::MakeRefPtr<V2::ListComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(listComponent);

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

                // Init scroll bar proxy.
                auto proxy = scroller->GetScrollBarProxy();
                if (!proxy) {
                    proxy = AceType::MakeRefPtr<ScrollBarProxy>();
                    scroller->SetScrollBarProxy(proxy);
                }
                listComponent->SetScrollBarProxy(proxy);
            }
        }
    }

    ViewStackProcessor::GetInstance()->Push(listComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
    args.ReturnSelf();
}

void JSList::SetChainAnimation(bool enableChainAnimation)
{
    JSViewSetProperty(&V2::ListComponent::SetChainAnimation, enableChainAnimation);
}

void JSList::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    if (Container::IsCurrentUseNewPipeline()) {
        return;
    }
    JSViewSetProperty(&V2::ListComponent::SetHasWidth, true);
}

void JSList::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    if (Container::IsCurrentUseNewPipeline()) {
        return;
    }
    JSViewSetProperty(&V2::ListComponent::SetHasHeight, true);
}

void JSList::SetListItemAlign(int32_t itemAlignment)
{
    JSViewSetProperty(
        &V2::ListComponent::SetListItemAlign, itemAlignment, LIST_ITEM_ALIGN_TABLE, V2::ListItemAlign::START);
}

void JSList::SetLanes(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        int32_t laneNum = 1;
        if (ParseJsInteger<int32_t>(info[0], laneNum)) {
            // when [lanes] is set, [laneConstrain_] of list component will be reset to std::nullopt
            NG::ListView::SetLanes(laneNum);
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
        if (!ParseJsDimensionVp(minLengthParam, minLengthValue) ||
            !ParseJsDimensionVp(maxLengthParam, maxLengthValue)) {
            LOGW("minLength param or maxLength param is invalid");
            return;
        }
        NG::ListView::SetLaneMinLength(minLengthValue);
        NG::ListView::SetLaneMaxLength(maxLengthValue);
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto listComponent = AceType::DynamicCast<V2::ListComponent>(component);
    if (!listComponent) {
        LOGE("list component is null while trying set lanes");
        return;
    }
    int32_t laneNum = 1;
    if (ParseJsInteger<int32_t>(info[0], laneNum)) {
        // when [lanes] is set, [laneConstrain_] of list component will be reset to std::nullopt
        listComponent->SetLanes(laneNum);
        return;
    }
    LOGI("lanes is not number, parse lane length contraint.");
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
    listComponent->SetLaneConstrain(minLengthValue, maxLengthValue);
}

void JSList::SetSticky(int32_t sticky)
{
    JSViewSetProperty(&V2::ListComponent::SetSticky, static_cast<V2::StickyStyle>(sticky));
}

void JSList::SetDivider(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
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

            NG::ListView::SetDivider(divider);
        } while (0);
        return;
    }
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
    if (Container::IsCurrentUseNewPipeline()) {
        if (args[0]->IsFunction()) {
            auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                const Dimension& scrollOffset, const V2::ScrollState& scrollState) {
                auto params = ConvertToJSValues(scrollOffset, scrollState);
                func->Call(JSRef<JSObject>(), params.size(), params.data());
                return;
            };
            NG::ListView::SetOnScroll(onScroll);
        }
        return;
    }
    if (!JSViewBindEvent(&V2::ListComponent::SetOnScroll, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ReachStartCallback(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (args[0]->IsFunction()) {
            auto onReachStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
                func->Call(JSRef<JSObject>());
                return;
            };
            NG::ListView::SetOnReachStart(onReachStart);
        }
        return;
    }
    if (!JSViewBindEvent(&V2::ListComponent::SetOnReachStart, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ReachEndCallback(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (args[0]->IsFunction()) {
            auto onReachEnd = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
                func->Call(JSRef<JSObject>());
                return;
            };
            NG::ListView::SetOnReachEnd(onReachEnd);
        }
        return;
    }
    if (!JSViewBindEvent(&V2::ListComponent::SetOnReachEnd, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSList::ScrollStopCallback(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (args[0]->IsFunction()) {
            auto onScrollStop = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
                func->Call(JSRef<JSObject>());
                return;
            };
            NG::ListView::SetOnScrollStop(onScrollStop);
        }
        return;
    }
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
    if (Container::IsCurrentUseNewPipeline()) {
        if (args[0]->IsFunction()) {
            auto onScrollIndex = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                     const int32_t start, const int32_t end) {
                auto params = ConvertToJSValues(start, end);
                func->Call(JSRef<JSObject>(), params.size(), params.data());
                return;
            };
            NG::ListView::SetOnScrollIndex(onScrollIndex);
        }
        return;
    }
    if (!JSViewBindEvent(&V2::ListComponent::SetOnScrollIndex, args)) {
        LOGW("Failed to bind event");
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
    auto onItemDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragFunc)](
                                 const ItemDragInfo& dragInfo, int32_t itemIndex) -> RefPtr<Component> {
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
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            ACE_SCORING_EVENT("List.onItemDragStart.builder");
            builderFunc->Execute();
        }
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        if (!customComponent) {
            LOGE("Custom component is null.");
            return nullptr;
        }
        return customComponent;
    };
    auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListComponent>());
        return;
    }
    component->SetOnItemDragStartId(onItemDragStartId);
}

void JSList::ItemDragEnterCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragEnter event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                                 const ItemDragInfo& dragInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDragEnter");
        func->ItemDragEnterExecute(dragInfo);
    };
    auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListComponent>());
        return;
    }
    component->SetOnItemDragEnterId(onItemDragEnterId);
}

void JSList::ItemDragMoveCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragMove event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                                const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDragMove");
        func->ItemDragMoveExecute(dragInfo, itemIndex, insertIndex);
    };
    auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListComponent>());
        return;
    }
    component->SetOnItemDragMoveId(onItemDragMoveId);
}

void JSList::ItemDragLeaveCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragLeave event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                                 const ItemDragInfo& dragInfo, int32_t itemIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDragLeave");
        func->ItemDragLeaveExecute(dragInfo, itemIndex);
    };
    auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListComponent>());
        return;
    }
    component->SetOnItemDragLeaveId(onItemDragLeaveId);
}

void JSList::ItemDropCallback(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDrop event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                            const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("List.onItemDrop");
        func->ItemDropExecute(dragInfo, itemIndex, insertIndex, isSuccess);
    };
    auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListComponent>());
        return;
    }
    component->SetOnItemDropId(onItemDropId);
}

void JSList::SetMultiSelectable(bool multiSelectable)
{
    JSViewSetProperty(&V2::ListComponent::SetMultiSelectable, multiSelectable);
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
        if (Container::IsCurrentUseNewPipeline()) {
            NG::ListView::SetOnScrollBegin(onScrollBegin);
            return;
        }
        auto component = AceType::DynamicCast<V2::ListComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (!component) {
            LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListComponent>());
            return;
        }
        component->SetOnScrollBegin(onScrollBegin);
    }
}

} // namespace OHOS::Ace::Framework
