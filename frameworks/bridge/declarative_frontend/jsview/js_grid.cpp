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
std::mutex GridModel::mutex_;

GridModel* GridModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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
    RefPtr<ScrollControllerBase> positionController;
    RefPtr<ScrollProxy> scrollBarProxy;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSScroller* jsScroller = JSRef<JSObject>::Cast(info[0])->Unwrap<JSScroller>();
        if (jsScroller) {
            positionController = GridModel::GetInstance()->CreatePositionController();
            jsScroller->SetController(positionController);

            // Init scroll bar proxy.
            scrollBarProxy = jsScroller->GetScrollBarProxy();
            if (!scrollBarProxy) {
                scrollBarProxy = GridModel::GetInstance()->CreateScrollBarProxy();
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
#ifdef NG_BUILD
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
#else
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
#endif
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
    CalcDimension colGap;

    if (!ParseJsDimensionVp(info[0], colGap) || colGap.Value() < 0) {
        colGap.SetValue(0.0);
    }

    GridModel::GetInstance()->SetColumnsGap(colGap);
}

void JSGrid::SetRowsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension rowGap;

    if (!ParseJsDimensionVp(info[0], rowGap) || rowGap.Value() < 0) {
        rowGap.SetValue(0.0);
    }

    GridModel::GetInstance()->SetRowsGap(rowGap);
}

void JSGrid::JsGridHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        LOGE("parse height fail for grid, please check.");
        return;
    }
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    GridModel::GetInstance()->SetGridHeight(value);
}

void JSGrid::JsOnScrollBarUpdate(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto onScrollBarUpdate = [execCtx = info.GetExecutionContext(),
                                 func = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
                                     JSRef<JSFunc>::Cast(info[0]))](int32_t index, const Dimension& offset) {
        JSRef<JSVal> itemIndex = JSRef<JSVal>::Make(ToJSValue(index));
        JSRef<JSVal> itemOffset = ConvertToJSValue(offset);
        JSRef<JSVal> params[2] = { itemIndex, itemOffset };
        auto result = func->ExecuteJS(2, params);
        if (result->IsObject()) {
            JSRef<JSObject> obj = JSRef<JSObject>::Cast(result);

            Dimension totalOffset_;
            Dimension totalLength_;
            if (!ConvertFromJSValue(obj->GetProperty("totalOffset"), totalOffset_) ||
                !ConvertFromJSValue(obj->GetProperty("totalLength"), totalLength_)) {
                return std::pair<float, float>(0, 0);
            } else {
                return std::pair<float, float>(totalOffset_.ConvertToPx(), totalLength_.ConvertToPx());
            }
        }
        return std::pair<float, float>(0, 0);
    };
    GridModel::GetInstance()->SetOnScrollBarUpdate(std::move(onScrollBarUpdate));
}

void JSGrid::SetScrollEnabled(const JSCallbackInfo& args)
{
    GridModel::GetInstance()->SetScrollEnabled(args[0]->IsBoolean() ? args[0]->ToBoolean() : true);
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

    JSClass<JSGrid>::StaticMethod("onScrollBarUpdate", &JSGrid::JsOnScrollBarUpdate);
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
    JSClass<JSGrid>::StaticMethod("nestedScroll", &JSGrid::SetNestedScroll);
    JSClass<JSGrid>::StaticMethod("enableScrollInteraction", &JSGrid::SetScrollEnabled);
    JSClass<JSGrid>::StaticMethod("friction", &JSGrid::SetFriction);

    JSClass<JSGrid>::StaticMethod("onScroll", &JSGrid::JsOnScroll);
    JSClass<JSGrid>::StaticMethod("onReachStart", &JSGrid::JsOnReachStart);
    JSClass<JSGrid>::StaticMethod("onReachEnd", &JSGrid::JsOnReachEnd);
    JSClass<JSGrid>::StaticMethod("onScrollStart", &JSGrid::JsOnScrollStart);
    JSClass<JSGrid>::StaticMethod("onScrollStop", &JSGrid::JsOnScrollStop);
    JSClass<JSGrid>::StaticMethod("onScrollIndex", &JSGrid::JsOnScrollIndex);
    JSClass<JSGrid>::StaticMethod("onScrollFrameBegin", &JSGrid::JsOnScrollFrameBegin);

    JSClass<JSGrid>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSGrid::SetScrollBar(int32_t displayMode)
{
    if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        LOGE("Param is not valid");
        return;
    }
    GridModel::GetInstance()->SetScrollBarMode(displayMode);
}

void JSGrid::SetScrollBarColor(const std::string& color)
{
    if (!color.empty() && color != "undefined") {
        GridModel::GetInstance()->SetScrollBarColor(color);
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    Color defaultColor(theme->GetForegroundColor());
    GridModel::GetInstance()->SetScrollBarColor(defaultColor.ColorToString());
}

void JSGrid::SetScrollBarWidth(const JSCallbackInfo& scrollWidth)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    CalcDimension scrollBarWidth;
    if (scrollWidth.Length() < 1) {
        LOGE("scrollWidth is invalid");
        return;
    }
    if (!ParseJsDimensionVp(scrollWidth[0], scrollBarWidth) || scrollWidth[0]->IsNull() ||
        scrollWidth[0]->IsUndefined() || (scrollWidth[0]->IsString() && scrollWidth[0]->ToString().empty()) ||
        LessNotEqual(scrollBarWidth.Value(), 0.0)) {
        scrollBarWidth = theme->GetNormalWidth();
    }
    GridModel::GetInstance()->SetScrollBarWidth(scrollBarWidth.ToString());
}

void JSGrid::SetCachedCount(const JSCallbackInfo& info)
{
    int32_t cachedCount = 1;
    auto jsValue = info[0];

    if (!jsValue->IsUndefined() && jsValue->IsNumber()) {
        ParseJsInt32(jsValue, cachedCount);
        if (cachedCount < 0) {
            cachedCount = 1;
        }
    }

    GridModel::GetInstance()->SetCachedCount(cachedCount);
}

void JSGrid::SetEditMode(const JSCallbackInfo& info)
{
    // undefined means false to EditMode
    bool editMode = false;
    if (!info[0]->IsUndefined() && info[0]->IsBoolean()) {
        ParseJsBool(info[0], editMode);
    }
    GridModel::GetInstance()->SetEditable(editMode);
}

void JSGrid::SetMaxCount(const JSCallbackInfo& info)
{
    int32_t maxCount = Infinity<int32_t>();
    if (!info[0]->IsUndefined() && info[0]->IsNumber()) {
        ParseJsInt32(info[0], maxCount);
        if (maxCount < 1) {
            maxCount = Infinity<int32_t>();
        }
    }
    GridModel::GetInstance()->SetMaxCount(maxCount);
}

void JSGrid::SetMinCount(const JSCallbackInfo& info)
{
    int32_t minCount = 1;
    if (!info[0]->IsUndefined() && info[0]->IsNumber()) {
        ParseJsInt32(info[0], minCount);
        if (minCount < 1) {
            minCount = 1;
        }
    }
    GridModel::GetInstance()->SetMinCount(minCount);
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

void JSGrid::SetEdgeEffect(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("args is invalid");
        return;
    }
    int32_t edgeEffect;
    if (info[0]->IsNull() || info[0]->IsUndefined() || !ParseJsInt32(info[0], edgeEffect) ||
        edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(EdgeEffect::NONE);
    }
    GridModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
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

void JSGrid::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        GridModel::GetInstance()->SetNestedScroll(nestedOpt);
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
    GridModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSGrid::SetFriction(const JSCallbackInfo& info)
{
    double friction = -1.0;
    if (!JSViewAbstract::ParseJsDouble(info[0], friction)) {
        LOGW("Friction params invalid,can not convert to double");
        friction = -1.0;
    }
    GridModel::GetInstance()->SetFriction(friction);
}

void JSGrid::JsOnScroll(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const CalcDimension& scrollOffset, const ScrollState& scrollState) {
            auto params = ConvertToJSValues(scrollOffset, scrollState);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
        GridModel::GetInstance()->SetOnScroll(std::move(onScroll));
    }
    args.ReturnSelf();
}

void JSGrid::JsOnScrollStart(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        GridModel::GetInstance()->SetOnScrollStart(std::move(onScrollStart));
    }
    args.ReturnSelf();
}

void JSGrid::JsOnScrollStop(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStop = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        GridModel::GetInstance()->SetOnScrollStop(std::move(onScrollStop));
    }
    args.ReturnSelf();
}

void JSGrid::JsOnScrollIndex(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollIndex = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const int32_t first, const int32_t last) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(first, last);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
            return;
        };
        GridModel::GetInstance()->SetOnScrollIndex(std::move(onScrollIndex));
    }
    args.ReturnSelf();
}

void JSGrid::JsOnScrollFrameBegin(const JSCallbackInfo& args)
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
        GridModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollBegin));
    }
}

void JSGrid::JsOnReachStart(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        GridModel::GetInstance()->SetOnReachStart(std::move(onReachStart));
    }
    args.ReturnSelf();
}

void JSGrid::JsOnReachEnd(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachEnd = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        GridModel::GetInstance()->SetOnReachEnd(std::move(onReachEnd));
    }
    args.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
