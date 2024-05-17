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

#include "frameworks/bridge/declarative_frontend/jsview/js_stepper_item.h"

#include <array>

#include "bridge/declarative_frontend/jsview/models/stepper_item_model_impl.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<StepperItemModel> StepperItemModel::instance_ = nullptr;
std::mutex StepperItemModel::mutex_;

StepperItemModel* StepperItemModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::StepperItemModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::StepperItemModelNG());
            } else {
                instance_.reset(new Framework::StepperItemModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {} // namespace

void JSStepperItem::Create(const JSCallbackInfo& info)
{
    StepperItemModel::GetInstance()->Create();
}

void JSStepperItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSStepperItem>::Declare("StepperItem");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSStepperItem>::StaticMethod("create", &JSStepperItem::Create, opt);

    JSClass<JSStepperItem>::StaticMethod("prevLabel", &JSStepperItem::SetPrevLabel);
    JSClass<JSStepperItem>::StaticMethod("nextLabel", &JSStepperItem::SetNextLabel);
    JSClass<JSStepperItem>::StaticMethod("status", &JSStepperItem::SetStatus);
    JSClass<JSStepperItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSStepperItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSStepperItem>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSStepperItem>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSStepperItem>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSStepperItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSStepperItem>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSStepperItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSStepperItem>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSStepperItem::SetPrevLabel(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        (info[0]->IsUndefined() || info[0]->IsNull())) {
        StepperItemModel::GetInstance()->ResetPrevLabel();
        return;
    }

    if (!info[0]->IsString()) {
        return;
    }

    StepperItemModel::GetInstance()->SetPrevLabel(info[0]->ToString());
}

void JSStepperItem::SetNextLabel(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) &&
        (info[0]->IsUndefined() || info[0]->IsNull())) {
        StepperItemModel::GetInstance()->ResetNextLabel();
        return;
    }

    if (!info[0]->IsString()) {
        return;
    }

    StepperItemModel::GetInstance()->SetNextLabel(info[0]->ToString());
}

void JSStepperItem::SetStatus(const JSCallbackInfo& info)
{
    const std::array<std::string, 4> statusArray = { "normal", "disabled", "waiting", "skip" };
    std::string status = statusArray[0];
    do {
        if (info.Length() < 1) {
            break;
        }
        if (!info[0]->IsNumber()) {
            break;
        }
        auto index = info[0]->ToNumber<uint32_t>();
        if (index < 0 || index >= statusArray.size()) {
            break;
        }
        status = statusArray.at(index);
    } while (false);
    StepperItemModel::GetInstance()->SetStatus(status);
}

} // namespace OHOS::Ace::Framework