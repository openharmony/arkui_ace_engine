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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_v2/grid/render_grid_scroll.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroller.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };

} // namespace

void JSGrid::Create(const JSCallbackInfo& info)
{
    LOGD("Create component: Grid");
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    RefPtr<OHOS::Ace::GridLayoutComponent> gridComponent = AceType::MakeRefPtr<GridLayoutComponent>(componentChildren);
    gridComponent->SetDeclarative();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSScroller* jsScroller = JSRef<JSObject>::Cast(info[0])->Unwrap<JSScroller>();
        if (jsScroller) {
            auto positionController = AceType::MakeRefPtr<V2::GridPositionController>();
            jsScroller->SetController(positionController);
            gridComponent->SetController(positionController);
        }
    }
    ViewStackProcessor::GetInstance()->Push(gridComponent);
}

void JSGrid::SetColumnsTemplate(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetColumnsArgs(value);
    }
}

void JSGrid::SetRowsTemplate(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetRowsArgs(value);
    }
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
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetColumnGap(colGap);
    }
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
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetRowGap(rowGap);
    }
}

void JSGrid::JsOnScrollIndex(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto onScrolled = EventMarker(
            [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(info[0])](const BaseEventInfo* event) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                auto eventInfo = TypeInfoHelper::DynamicCast<V2::GridEventInfo>(event);
                if (!eventInfo) {
                    return;
                }
                auto params = ConvertToJSValues(eventInfo->GetScrollIndex());
                func->Call(JSRef<JSObject>(), params.size(), params.data());
            });

        auto grid = AceType::DynamicCast<GridLayoutComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (grid) {
            grid->SetScrolledEvent(onScrolled);
        }
    }
}

void JSGrid::JSBind(BindingTarget globalObj)
{
    LOGD("JSGrid:V8Bind");
    JSClass<JSGrid>::Declare("Grid");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSGrid>::StaticMethod("create", &JSGrid::Create, opt);
    JSClass<JSGrid>::StaticMethod("columnsTemplate", &JSGrid::SetColumnsTemplate, opt);
    JSClass<JSGrid>::StaticMethod("rowsTemplate", &JSGrid::SetRowsTemplate, opt);
    JSClass<JSGrid>::StaticMethod("columnsGap", &JSGrid::SetColumnsGap, opt);
    JSClass<JSGrid>::StaticMethod("rowsGap", &JSGrid::SetRowsGap, opt);
    JSClass<JSGrid>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSGrid>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSGrid>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSGrid>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGrid>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSGrid>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSGrid>::StaticMethod("scrollBar", &JSGrid::SetScrollBar, opt);
    JSClass<JSGrid>::StaticMethod("scrollBarWidth", &JSGrid::SetScrollBarWidth, opt);
    JSClass<JSGrid>::StaticMethod("scrollBarColor", &JSGrid::SetScrollBarColor, opt);
    JSClass<JSGrid>::StaticMethod("onScrollIndex", &JSGrid::JsOnScrollIndex);
    JSClass<JSGrid>::Inherit<JSContainerBase>();
    JSClass<JSGrid>::Inherit<JSViewAbstract>();
    JSClass<JSGrid>::Bind<>(globalObj);
}

void JSGrid::SetScrollBar(int32_t displayMode)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (!grid) {
        return;
    }
    if (displayMode >= 0 && displayMode < static_cast<int32_t>(DISPLAY_MODE.size())) {
        grid->SetScrollBar(DISPLAY_MODE[displayMode]);
    }
}

void JSGrid::SetScrollBarColor(const std::string& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetScrollBarColor(color);
    }
}

void JSGrid::SetScrollBarWidth(const std::string& width)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto grid = AceType::DynamicCast<GridLayoutComponent>(component);
    if (grid) {
        grid->SetScrollBarWidth(width);
    }
}

} // namespace OHOS::Ace::Framework
