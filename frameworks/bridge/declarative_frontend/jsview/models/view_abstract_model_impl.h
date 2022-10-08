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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H

#include "base/utils/macros.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {

class ViewAbstractModelImpl : public ViewAbstractModel {
public:
    ~ViewAbstractModelImpl() override = default;

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override;
    void SetOnTouch(TouchEventFunc&& touchEventFunc) override;
    void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) override;
    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override;
    void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) override;
    void SetOnDelete(std::function<void()>&& onDeleteCallback) override;
    void SetOnAppear(std::function<void()>&& onAppearCallback) override;
    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override;
    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override;
    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override;
    void SetTouchable(bool touchable) override;
    void SetFocusable(bool focusable) override;
    void SetFocusNode(bool focus) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H
