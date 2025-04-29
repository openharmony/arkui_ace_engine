/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/cppview/interactable_view.h"

#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {

void InteractableView::SetFocusable(bool focusable)
{
    ViewAbstractModel::GetInstance()->SetFocusable(focusable);
}

void InteractableView::SetFocusNode(bool isFocusNode)
{
    ViewAbstractModel::GetInstance()->SetFocusNode(isFocusNode);
}

static GestureEventFunc GestureEventWrapper(std::function<void(const ClickInfo& clickInfo)> callback)
{
    return [callback](GestureEvent& info) {
        LOGI("About to call InteractableView::GetTapGesture callback method on cj");
        // js frontend has no fingerid either
        ClickInfo ffiClickInfo(-1);
        ffiClickInfo.SetGlobalLocation(info.GetGlobalLocation());
        ffiClickInfo.SetLocalLocation(info.GetLocalLocation());
        callback(ffiClickInfo);
    };
}

void InteractableView::OnClick(std::function<void(const ClickInfo& clickInfo)> callback)
{
    ViewAbstractModel::GetInstance()->SetOnClick(
        GestureEventWrapper(callback), [callback](const ClickInfo* info)->void {
        callback(*info);
    });
}

void InteractableView::OnTouch(std::function<void(TouchEventInfo& touchInfo)> callback)
{
    LOGI("InteractableView::OnTouch start!");
    ViewAbstractModel::GetInstance()->SetOnTouch(std::move(callback));
}

void InteractableView::OnAppear(std::function<void()> callback)
{
    ViewAbstractModel::GetInstance()->SetOnAppear(std::move(callback));
}

void InteractableView::OnDisAppear(std::function<void()> callback)
{
    ViewAbstractModel::GetInstance()->SetOnDisAppear(std::move(callback));
}

void InteractableView::OnHover(std::function<void(bool)> callback)
{
    ViewAbstractModel::GetInstance()->SetOnHover([callback](bool v, HoverInfo& info) {
        callback(v);
    });
}

void InteractableView::OnHoverMove(std::function<void()> callback)
{
    ViewAbstractModel::GetInstance()->SetOnHoverMove([callback](HoverInfo& info) {
        callback();
    });
}

void InteractableView::OnKey(std::function<bool(KeyEventInfo& keyInfo)> callback)
{
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(std::move(callback));
}

void InteractableView::OnDelete(std::function<void()> callback)
{
    ViewAbstractModel::GetInstance()->SetOnDelete(std::move(callback));
}

} // namespace OHOS::Ace::Framework
