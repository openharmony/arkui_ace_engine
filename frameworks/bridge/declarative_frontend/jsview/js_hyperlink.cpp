/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_hyperlink.h"

#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/base/view_stack_model.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/hyperlink_model_impl.h"
#include "frameworks/core/components_ng/pattern/hyperlink/hyperlink_model.h"
#include "frameworks/core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<HyperlinkModel> HyperlinkModel::instance_ = nullptr;
std::mutex HyperlinkModel::mutex_;

HyperlinkModel* HyperlinkModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::HyperlinkModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::HyperlinkModelNG instance;
        return &instance;
    } else {
        static Framework::HyperlinkModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSHyperlink::JSBind(BindingTarget globalObj)
{
    JSClass<JSHyperlink>::Declare("Hyperlink");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSHyperlink>::StaticMethod("create", &JSHyperlink::Create, opt);
    JSClass<JSHyperlink>::StaticMethod("color", &JSHyperlink::SetColor, opt);
    JSClass<JSHyperlink>::StaticMethod("pop", &JSHyperlink::Pop);
    JSClass<JSHyperlink>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSHyperlink>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSHyperlink>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSHyperlink>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSHyperlink>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSHyperlink>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSHyperlink>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSHyperlink>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);

    JSClass<JSHyperlink>::StaticMethod("draggable", &JSHyperlink::JsSetDraggable);
    JSClass<JSHyperlink>::StaticMethod("responseRegion", &JSHyperlink::JsResponseRegion);
    JSClass<JSHyperlink>::Inherit<JSInteractableView>();

    JSClass<JSHyperlink>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSHyperlink::Create(const JSCallbackInfo& args)
{
    std::string address;
    ParseJsString(args[0], address);

    std::string summary;
    if (args.Length() == 2) {
        ParseJsString(args[1], summary);
    }

    HyperlinkModel::GetInstance()->Create(address, summary);
}

void JSHyperlink::SetColor(const JSCallbackInfo& info)
{
    Color color;
    if (!ParseJsColor(info[0], color)) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<HyperlinkTheme>();
        CHECK_NULL_VOID(theme);
        color = theme->GetTextColor();
    }
    HyperlinkModel::GetInstance()->SetColor(color);
}

void JSHyperlink::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSHyperlink][pop]", &JSHyperlink::Pop);
    }
    if (Container::IsCurrentUseNewPipeline()) {
        ViewStackModel::GetInstance()->PopContainer();
        return;
    }

    HyperlinkModel::GetInstance()->Pop();
}

void JSHyperlink::JsSetDraggable(bool draggable)
{
    HyperlinkModel::GetInstance()->SetDraggable(draggable);
}

void JSHyperlink::JsResponseRegion(const JSCallbackInfo& info)
{
    JSViewAbstract::JsResponseRegion(info);
    HyperlinkModel::GetInstance()->SetResponseRegion(true);
}

} // namespace OHOS::Ace::Framework