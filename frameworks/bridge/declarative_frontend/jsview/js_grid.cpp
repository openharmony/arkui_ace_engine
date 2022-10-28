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

#include "bridge/declarative_frontend/jsview/js_grid.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/grid_model_impl.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"
#include "core/components_v2/grid/grid_event.h"

namespace OHOS::Ace {

std::unique_ptr<GridModel> GridModel::instance_ = nullptr;

GridModel* GridModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::GridModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::GridModelNG());
        } else {
            instance_.reset(new Framework::GridModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };

} // namespace

void JSGrid::Create(const JSCallbackInfo& info)
{
    RefPtr<V2::GridPositionController> positionController;
    RefPtr<ScrollBarProxy> scrollBarProxy;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSScroller* jsScroller = JSRef<JSObject>::Cast(info[0])->Unwrap<JSScroller>();
        if (jsScroller) {
            positionController = AceType::MakeRefPtr<V2::GridPositionController>();
            jsScroller->SetController(positionController);

            // Init scroll bar proxy.
            scrollBarProxy = jsScroller->GetScrollBarProxy();
            if (!scrollBarProxy) {
                scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
                jsScroller->SetScrollBarProxy(scrollBarProxy);
            }
        }
    }
    GridModel::GetInstance()->Create(positionController, scrollBarProxy);
}

void JSGrid::PopGrid(const JSCallbackInfo& /*info*/)
{
    GridModel::GetInstance()->Pop();
}

void JSGrid::UseProxy(const JSCallbackInfo& args)
{
    auto parentGrid = ViewStackProcessor::GetInstance()->GetTopGrid();
    if (parentGrid == nullptr) {
        LOGE("no parent Grid");
    }

    // return true if code path for GridElement and its children will rely on
    // ElementProxy. Only in this case shallow render functionality can be used
    // see also GridLayoutComponent::CreateElement() and GridItemElementProxy class
    LOGD("parent Grid uses proxied code path %{public}s.",
        (parentGrid ? !parentGrid->UseNonProxiedCodePath() ? "yes" : "false" : "no parent grid (error)"));
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(parentGrid ? !parentGrid->UseNonProxiedCodePath() : false)));
}

void JSGrid::SetColumnsTemplate(const std::string& value)
{
    GridModel::GetInstance()->SetColumnsTemplate(value);
}

void JSGrid::SetRowsTemplate(const std::string& value)
{
    GridModel::GetInstance()->SetRowsTemplate(value);
}

void JSGrid::SetColumnsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension colGap;
    if (!ParseJsDimensionVp(info[0], colGap)) {
        return;
    }

    GridModel::GetInstance()->SetColumnsGap(colGap);
}

void JSGrid::SetRowsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension rowGap;
    if (!ParseJsDimensionVp(info[0], rowGap)) {
        return;
    }

    GridModel::GetInstance()->SetRowsGap(rowGap);
}

void JSGrid::JsGridHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGE("parse height fail for grid, please check.");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    GridModel::GetInstance()->SetGridHeight(value);
}

void JSGrid::JsOnScrollIndex(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        LOGE("param not valid, need function");
        return;
    }

    auto onScrollIndex = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(info[0])](
                             const BaseEventInfo* event) {
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::GridEventInfo>(event);
        if (!eventInfo) {
            return;
        }
        auto params = ConvertToJSValues(eventInfo->GetScrollIndex());
        func->Call(JSRef<JSObject>(), static_cast<int>(params.size()), params.data());
    };
    GridModel::GetInstance()->SetOnScrollToIndex(std::move(onScrollIndex));
}

void JSGrid::JSBind(BindingTarget globalObj)
{
    LOGD("JSGrid:Bind");
    JSClass<JSGrid>::Declare("Grid");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSGrid>::StaticMethod("create", &JSGrid::Create, opt);
    JSClass<JSGrid>::StaticMethod("pop", &JSGrid::PopGrid, opt);
    JSClass<JSGrid>::StaticMethod("willUseProxy", &JSGrid::UseProxy, opt);
    JSClass<JSGrid>::StaticMethod("columnsTemplate", &JSGrid::SetColumnsTemplate, opt);
    JSClass<JSGrid>::StaticMethod("rowsTemplate", &JSGrid::SetRowsTemplate, opt);
    JSClass<JSGrid>::StaticMethod("columnsGap", &JSGrid::SetColumnsGap, opt);
    JSClass<JSGrid>::StaticMethod("rowsGap", &JSGrid::SetRowsGap, opt);
    JSClass<JSGrid>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSGrid>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSGrid>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSGrid>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGrid>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSGrid>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSGrid>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSGrid>::StaticMethod("scrollBar", &JSGrid::SetScrollBar, opt);
    JSClass<JSGrid>::StaticMethod("scrollBarWidth", &JSGrid::SetScrollBarWidth, opt);
    JSClass<JSGrid>::StaticMethod("scrollBarColor", &JSGrid::SetScrollBarColor, opt);
    JSClass<JSGrid>::StaticMethod("onScrollIndex", &JSGrid::JsOnScrollIndex);
    JSClass<JSGrid>::StaticMethod("cachedCount", &JSGrid::SetCachedCount);
    JSClass<JSGrid>::StaticMethod("editMode", &JSGrid::SetEditMode, opt);
    JSClass<JSGrid>::StaticMethod("multiSelectable", &JSGrid::SetMultiSelectable, opt);
    JSClass<JSGrid>::StaticMethod("maxCount", &JSGrid::SetMaxCount, opt);
    JSClass<JSGrid>::StaticMethod("minCount", &JSGrid::SetMinCount, opt);
    JSClass<JSGrid>::StaticMethod("cellLength", &JSGrid::CellLength, opt);
    JSClass<JSGrid>::StaticMethod("layoutDirection", &JSGrid::SetLayoutDirection, opt);
    JSClass<JSGrid>::StaticMethod("dragAnimation", &JSGrid::SetDragAnimation, opt);
    JSClass<JSGrid>::StaticMethod("edgeEffect", &JSGrid::SetEdgeEffect, opt);
    JSClass<JSGrid>::StaticMethod("direction", &JSGrid::SetDirection, opt);
    JSClass<JSGrid>::StaticMethod("supportAnimation", &JSGrid::SetSupportAnimation, opt);
    JSClass<JSGrid>::StaticMethod("onItemDragEnter", &JSGrid::JsOnGridDragEnter);
    JSClass<JSGrid>::StaticMethod("onItemDragMove", &JSGrid::JsOnGridDragMove);
    JSClass<JSGrid>::StaticMethod("onItemDragLeave", &JSGrid::JsOnGridDragLeave);
    JSClass<JSGrid>::StaticMethod("onItemDragStart", &JSGrid::JsOnGridDragStart);
    JSClass<JSGrid>::StaticMethod("height", &JSGrid::JsGridHeight);
    JSClass<JSGrid>::StaticMethod("onItemDrop", &JSGrid::JsOnGridDrop);
    JSClass<JSGrid>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSGrid>::Inherit<JSContainerBase>();
    JSClass<JSGrid>::Inherit<JSViewAbstract>();
    JSClass<JSGrid>::Bind<>(globalObj);
}

void JSGrid::SetScrollBar(int32_t displayMode)
{
    if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        LOGE("Param is not valid");
        return;
    }
    GridModel::GetInstance()->SetScrollBarMode(DISPLAY_MODE[displayMode]);
}

void JSGrid::SetScrollBarColor(const std::string& color)
{
    GridModel::GetInstance()->SetScrollBarColor(color);
}

void JSGrid::SetScrollBarWidth(const std::string& width)
{
    GridModel::GetInstance()->SetScrollBarWidth(width);
}

void JSGrid::SetCachedCount(int32_t cachedCount)
{
    GridModel::GetInstance()->SetCachedCount(cachedCount);
}

void JSGrid::SetEditMode(bool editMode)
{
    GridModel::GetInstance()->SetEditable(editMode);
}

void JSGrid::SetMaxCount(double maxCount)
{
    GridModel::GetInstance()->SetMaxCount(static_cast<int32_t>(maxCount));
}

void JSGrid::SetMinCount(double minCount)
{
    GridModel::GetInstance()->SetMinCount(static_cast<int32_t>(minCount));
}

void JSGrid::CellLength(int32_t cellLength)
{
    GridModel::GetInstance()->SetCellLength(cellLength);
}

void JSGrid::SetSupportAnimation(bool supportAnimation)
{
    GridModel::GetInstance()->SetSupportAnimation(supportAnimation);
}

void JSGrid::SetDragAnimation(bool value)
{
    GridModel::GetInstance()->SetSupportDragAnimation(value);
}

void JSGrid::SetEdgeEffect(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        return;
    }
    GridModel::GetInstance()->SetEdgeEffect(EDGE_EFFECT[value]);
}

void JSGrid::SetLayoutDirection(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        LOGE("Param is not valid");
        return;
    }
    GridModel::GetInstance()->SetLayoutDirection(LAYOUT_DIRECTION[value]);
}

void JSGrid::SetDirection(const std::string& dir)
{
    bool rightToLeft = false;
    if (dir == "Ltr") {
        rightToLeft = false;
    } else if (dir == "Rtl") {
        rightToLeft = true;
    } else {
        rightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    }
    GridModel::GetInstance()->SetIsRTL(rightToLeft);
}

void JSGrid::JsOnGridDragEnter(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragEnter event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragEnter = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                               const ItemDragInfo& dragInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Grid.onItemDragEnter");
        func->ItemDragEnterExecute(dragInfo);
    };
    GridModel::GetInstance()->SetOnItemDragEnter(std::move(onItemDragEnter));
}

void JSGrid::JsOnGridDragMove(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragMove event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragMove = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                              const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Grid.onItemDragMove");
        func->ItemDragMoveExecute(dragInfo, itemIndex, insertIndex);
    };
    GridModel::GetInstance()->SetOnItemDragMove(std::move(onItemDragMove));
}

void JSGrid::JsOnGridDragLeave(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragLeave event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragLeave = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Grid.onItemDragLeave");
        func->ItemDragLeaveExecute(dragInfo, itemIndex);
    };
    GridModel::GetInstance()->SetOnItemDragLeave(std::move(onItemDragLeave));
}

void JSGrid::JsOnGridDragStart(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDragStart event due to info is not function");
        return;
    }

    auto jsOnDragFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragFunc)](
                               const ItemDragInfo& dragInfo, int32_t itemIndex) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Grid.onItemDragStart");
        auto ret = func->ItemDragStartExecute(dragInfo, itemIndex);
        if (!ret->IsObject()) {
            LOGE("builder param is not an object.");
            return;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
        auto builder = builderObj->GetProperty("builder");
        if (!builder->IsFunction()) {
            LOGE("builder param is not a function.");
            return;
        }
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        CHECK_NULL_VOID(builderFunc);
        builderFunc->Execute();
    };
    GridModel::GetInstance()->SetOnItemDragStart(std::move(onItemDragStart));
}

void JSGrid::JsOnGridDrop(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("fail to bind onItemDrop event due to info is not function");
        return;
    }

    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onItemDrop = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                          const ItemDragInfo& dragInfo, int32_t itemIndex, int32_t insertIndex, bool isSuccess) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Grid.onItemDrop");
        func->ItemDropExecute(dragInfo, itemIndex, insertIndex, isSuccess);
    };
    GridModel::GetInstance()->SetOnItemDrop(std::move(onItemDrop));
}

void JSGrid::SetMultiSelectable(bool multiSelectable)
{
    GridModel::GetInstance()->SetMultiSelectable(multiSelectable);
}

} // namespace OHOS::Ace::Framework
