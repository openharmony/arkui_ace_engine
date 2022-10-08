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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H

#include <utility>

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ViewAbstractModelNG : public ViewAbstractModel {
public:
    ~ViewAbstractModelNG() override = default;

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override
    {
        ViewAbstract::SetOnClick(std::move(tapEventFunc));
    }

    void SetOnTouch(TouchEventFunc&& touchEventFunc) override
    {
        ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    }

    void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) override
    {
        ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));
    }

    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override
    {
        ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    }

    void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) override
    {
        ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    }

    void SetOnDelete(std::function<void()>&& onDeleteCallback) override {}

    void SetOnAppear(std::function<void()>&& onAppearCallback) override
    {
        ViewAbstract::SetOnAppear(std::move(onAppearCallback));
    }

    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override
    {
        ViewAbstract::SetOnDisappear(std::move(onDisAppearCallback));
    }

    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override {}

    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override {}

    void SetTouchable(bool touchable) override
    {
        ViewAbstract::SetTouchable(touchable);
    }

    void SetFocusable(bool focusable) override
    {
        ViewAbstract::SetFocusable(focusable);
    }

    void SetFocusNode(bool focus) override {}
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
