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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_OVERLAY_HOLDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_OVERLAY_HOLDER_H

#include <optional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/manager/select_content_overlay/select_overlay_callback.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SelectOverlayHolder : public virtual AceType {
    DECLARE_ACE_TYPE(SelectOverlayHolder, AceType);

public:
    SelectOverlayHolder() = default;
    ~SelectOverlayHolder() override = default;

    void OnBind(const WeakPtr<AceType>& manager)
    {
        bindManager_ = manager;
        if (manager.Invalid()) {
            auto callback = GetCallback();
            CHECK_NULL_VOID(callback);
            callback->OnUnbind();
        }
    }

    template<typename T>
    RefPtr<T> GetManager() const
    {
        return DynamicCast<T>(bindManager_.Upgrade());
    }

    virtual int32_t GetOwnerId()
    {
        auto owner = GetOwner();
        return owner ? owner->GetId() : -1;
    }

    virtual RefPtr<FrameNode> GetOwner()
    {
        return nullptr;
    }

    virtual std::optional<SelectHandleInfo> GetFirstHandleInfo()
    {
        return std::nullopt;
    }

    virtual std::optional<SelectHandleInfo> GetSecondHandleInfo()
    {
        return std::nullopt;
    }

    virtual void OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag) {}

    virtual void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode) {}

    virtual void OnHandleMarkInfoChange(std::shared_ptr<SelectOverlayInfo> info, SelectOverlayDirtyFlag flag) {}

    virtual void OnHandleExistOverlay(SelectOverlayInfo info, int32_t requestCode) {}

    virtual std::optional<RectF> GetAncestorNodeViewPort()
    {
        return std::nullopt;
    }

    virtual bool CheckRestartHiddenHandleTask(int32_t requestCode)
    {
        return true;
    }

    virtual RefPtr<SelectOverlayCallback> GetCallback()
    {
        return nullptr;
    }

    virtual RectF GetSelectArea()
    {
        return {};
    }

    virtual std::string GetSelectedText()
    {
        return "";
    }

    virtual bool IsEnableContainerModal()
    {
        return false;
    }

    virtual bool IsStopBackPress() const
    {
        return true;
    }
private:
    WeakPtr<AceType> bindManager_;
    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayHolder);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECT_OVERLAY_HOLDER_H
