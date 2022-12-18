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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_COMPONENT_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/popup_param.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/composed_component.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

using PopupImpl = std::function<void()>;

class PopupController : public virtual AceType {
    DECLARE_ACE_TYPE(PopupController, AceType);

public:
    void ShowPopup()
    {
        if (showPopupImpl_) {
            showPopupImpl_();
        }
    }

    void SetShowPopupImpl(const PopupImpl& showPopupImpl)
    {
        showPopupImpl_ = showPopupImpl;
    }

    void CancelPopup()
    {
        if (cancelPopupImpl_) {
            cancelPopupImpl_();
        }
    }

    void SetCancelPopupImpl(const PopupImpl& cancelPopupImpl)
    {
        cancelPopupImpl_ = cancelPopupImpl;
    }

private:
    PopupImpl showPopupImpl_;
    PopupImpl cancelPopupImpl_;
};

class PopupComponent : public ComposedComponent {
    DECLARE_ACE_TYPE(PopupComponent, ComposedComponent);

public:
    PopupComponent(const ComposeId& id, const std::string& name, const RefPtr<Component>& child)
        : ComposedComponent(id, name, child)
    {
        popupParam_ = MakeRefPtr<PopupParam>();
        popupController_ = MakeRefPtr<PopupController>();
    };
    PopupComponent(const ComposeId& id, const std::string& name) : ComposedComponent(id, name)
    {
        popupParam_ = MakeRefPtr<PopupParam>();
        popupController_ = MakeRefPtr<PopupController>();
    };
    ~PopupComponent() override = default;

    RefPtr<Element> CreateElement() override;

    const RefPtr<PopupController>& GetPopupController() const
    {
        return popupController_;
    }

    void SetPopupParam(const RefPtr<PopupParam>& popupParam)
    {
        popupParam_ = popupParam;
    }

    const RefPtr<PopupParam>& GetPopupParam() const
    {
        return popupParam_;
    }

    bool IsShow() const
    {
        if (popupParam_) {
            return popupParam_->IsShow();
        }
        return true;
    }

private:
    RefPtr<PopupParam> popupParam_;
    RefPtr<PopupController> popupController_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_POPUP_POPUP_COMPONENT_H
