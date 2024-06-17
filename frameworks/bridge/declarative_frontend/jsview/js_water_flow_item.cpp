/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow_item.h"

#include "frameworks/bridge/declarative_frontend/jsview/models/water_flow_item_model_impl.h"
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<WaterFlowItemModel> WaterFlowItemModel::instance_ = nullptr;
std::mutex WaterFlowItemModel::mutex_;

WaterFlowItemModel* WaterFlowItemModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::WaterFlowItemModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::WaterFlowItemModelNG());
            } else {
                instance_.reset(new Framework::WaterFlowItemModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSWaterFlowItem::Create()
{
    WaterFlowItemModel::GetInstance()->Create();
}

void JSWaterFlowItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSWaterFlowItem>::Declare("FlowItem");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSWaterFlowItem>::StaticMethod("create", &JSWaterFlowItem::Create, opt);
    JSClass<JSWaterFlowItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSWaterFlowItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSWaterFlowItem>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSWaterFlowItem>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSWaterFlowItem>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSWaterFlowItem>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSWaterFlowItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWaterFlowItem>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSWaterFlowItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSWaterFlowItem>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSWaterFlowItem>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
