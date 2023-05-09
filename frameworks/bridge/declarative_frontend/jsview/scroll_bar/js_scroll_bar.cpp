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

#include "frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"

#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "core/components/scroll_bar/scroll_bar_component.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_view.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {

const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::NONE };

void NGSetScrollControllerAndProxy(RefPtr<NG::ScrollBarPattern>& pattern, const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(pattern);
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        // Parse scroller.
        auto scrollerValue = obj->GetProperty("scroller");
        if (scrollerValue->IsObject() && JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>()) {
            auto jsScroller = JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>();
            auto proxy = AceType::DynamicCast<NG::ScrollBarProxy>(jsScroller->GetScrollBarProxy());
            if (!proxy) {
                proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
                jsScroller->SetScrollBarProxy(proxy);
            }
            proxy->RegisterScrollBar(pattern);
            pattern->SetScrollBarProxy(proxy);
        }
        // Parse direction.
        auto directionValue = obj->GetProperty("direction");
        if (directionValue->IsNumber()) {
            NG::ScrollBarView::SetAxis(AXIS[directionValue->ToNumber<int32_t>()]);
        }
        // Parse state.
        auto stateValue = obj->GetProperty("state");
        if (stateValue->IsNumber()) {
            NG::ScrollBarView::SetDisplayMode(stateValue->ToNumber<int32_t>());
        }
    }
}

} // namespace

void JSScrollBar::JSBind(BindingTarget globalObj)
{
    JSClass<JSScrollBar>::Declare("ScrollBar");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScrollBar>::StaticMethod("create", &JSScrollBar::Create, opt);

    JSClass<JSScrollBar>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSScrollBar>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSScrollBar>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSScrollBar>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSScrollBar>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSScrollBar>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSScrollBar>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSScrollBar>::Inherit<JSContainerBase>();
    JSClass<JSScrollBar>::Inherit<JSViewAbstract>();
    JSClass<JSScrollBar>::Bind<>(globalObj);
}

void JSScrollBar::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto frameNode = NG::ScrollBarView::Create();
        auto pattern = AceType::DynamicCast<NG::ScrollBarPattern>(frameNode->GetPattern());
        NGSetScrollControllerAndProxy(pattern, info);
        return;
    }

    RefPtr<Component> child;
    auto scrollBarComponent = AceType::MakeRefPtr<OHOS::Ace::ScrollBarComponent>(child);
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        // Parse scroller.
        auto scrollerValue = obj->GetProperty("scroller");
        if (scrollerValue->IsObject() && JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>()) {
            auto jsScroller = JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>();
            auto proxy = AceType::DynamicCast<ScrollBarProxy>(jsScroller->GetScrollBarProxy());
            if (!proxy) {
                proxy = AceType::MakeRefPtr<ScrollBarProxy>();
                jsScroller->SetScrollBarProxy(proxy);
            }
            scrollBarComponent->SetScrollBarProxy(proxy);
        }

        // Parse direction.
        auto directionValue = obj->GetProperty("direction");
        if (directionValue->IsNumber() && directionValue->ToNumber<uint32_t>() < AXIS.size()) {
            scrollBarComponent->SetAxis(AXIS[directionValue->ToNumber<int32_t>()]);
        }

        // Parse state.
        auto stateValue = obj->GetProperty("state");
        if (stateValue->IsNumber()) {
            scrollBarComponent->SetDisplayMode(DISPLAY_MODE[stateValue->ToNumber<int32_t>()]);
        }
    }
    ViewStackProcessor::GetInstance()->ClaimElementId(scrollBarComponent);
    ViewStackProcessor::GetInstance()->Push(scrollBarComponent);
    // Push DisplayComponent to enable opacity animation.
    ViewStackProcessor::GetInstance()->GetDisplayComponent();
}

} // namespace OHOS::Ace::Framework
