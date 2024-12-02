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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_PROXY_H

#include <cstdint>
#include <optional>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::NG {

// SelectOverlayProxy is the class to control select handle and select menu.
class ACE_EXPORT SelectOverlayProxy : public virtual AceType {
    DECLARE_ACE_TYPE(SelectOverlayProxy, AceType);

public:
    explicit SelectOverlayProxy(int32_t selectOverlayId) : selectOverlayId_(selectOverlayId) {}
    ~SelectOverlayProxy() override = default;

    void UpdateFirstSelectHandleInfo(const SelectHandleInfo& info) const;

    void UpdateSecondSelectHandleInfo(const SelectHandleInfo& info) const;

    void UpdateFirstAndSecondHandleInfo(const SelectHandleInfo& firstInfo, const SelectHandleInfo& secondInfo) const;

    void UpdateSelectMenuInfo(const SelectMenuInfo& info) const;

    void UpdateSelectMenuInfo(std::function<void(SelectMenuInfo& menuInfo)> updateAction) const;

    void UpdateAncestorViewPort(const std::optional<RectF>& ancestorViewPort) const;

    void UpdateShowArea(const RectF& area) const;

    void SetSelectRegionVisible(bool isSelectRegionVisible);

    void SetHandleReverse(bool reverse);

    bool IsClosed() const;

    void Close(bool animation = false) const;

    void UpdateSelectArea(const RectF& selectArea);

    void SetIsNewAvoid(bool isNewAvoid);

    int32_t GetSelectOverlayId() const
    {
        return selectOverlayId_;
    }

    void SetSelectInfo(const std::string& selectInfo) const;
    void ShowOrHiddenMenu(bool isHidden, bool noAnimation = false);
    void DisableMenu(bool isDisabled);
    bool IsMenuShow();
    bool IsSingleHandleMenuShow();
    bool IsHandleShow();
    bool IsSingleHandle();
    bool IsHandleReverse();
    SelectOverlayInfo GetSelectOverlayMangerInfo();

private:
    int32_t selectOverlayId_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayProxy);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_PROXY_H
