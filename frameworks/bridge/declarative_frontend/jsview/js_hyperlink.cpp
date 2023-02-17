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

#include "frameworks/bridge/declarative_frontend/jsview/js_hyperlink.h"

#include "core/components/hyperlink/hyperlink_component.h"
#include "core/components/text/text_component.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

#include "bridge/declarative_frontend/jsview/models/hyperlink_model_impl.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<HyperlinkModel> HyperlinkModel::instance_ = nullptr;

HyperlinkModel* HyperlinkModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::HyperlinkModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::HyperlinkModelNG());
        } else {
            instance_.reset(new Framework::HyperlinkModelImpl());
        }
#endif
    }
    return instance_.get();
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
    JSClass<JSHyperlink>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSHyperlink>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSHyperlink>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSHyperlink>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSHyperlink>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSHyperlink>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSHyperlink>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSHyperlink>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSHyperlink>::Inherit<JSViewAbstract>();
    JSClass<JSHyperlink>::Bind(globalObj);
}

void JSHyperlink::Create(const JSCallbackInfo& args)
{
    LOGE("mxc, JSHyperlink::Create");
    std::string address;
    ParseJsString(args[0], address);
    LOGE("mxc, address is %{public}s", address.c_str());

    std::string summary;
    if (args.Length() == 2) {
        ParseJsString(args[1], summary);
    }
    LOGE("mxc, summary is %{public}s", summary.c_str());

    HyperlinkModel::GetInstance()->Create(address, summary);
}

void JSHyperlink::SetColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color color;
    if (!ParseJsColor(info[0], color)) {
        return;
    }
    HyperlinkModel::GetInstance()->SetColor(color);
}

void JSHyperlink::Pop()
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::Pop();
        return;
    }

    HyperlinkModel::GetInstance()->Pop();
}

} // namespace OHOS::Ace::Framework