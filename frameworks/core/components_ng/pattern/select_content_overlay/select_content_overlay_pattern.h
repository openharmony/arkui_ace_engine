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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_CONTENT_OVERLAY_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_CONTENT_OVERLAY_PATTERN_H

#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectContentOverlayPattern : public SelectOverlayPattern {
    DECLARE_ACE_TYPE(SelectContentOverlayPattern, SelectOverlayPattern);

public:
    explicit SelectContentOverlayPattern(std::shared_ptr<SelectOverlayInfo> info, SelectOverlayMode mode)
        : SelectOverlayPattern(info, mode)
    {}
    ~SelectContentOverlayPattern() override = default;

    void UpdateMenuIsShow(bool menuIsShow, bool noAnimation = false);
    void UpdateMenuInfo(const SelectMenuInfo& info);
    void UpdateIsShowHandleLine(bool isShowHandleLine);
    void UpdateIsSingleHandle(bool isSingleHandle);
    void RestartHiddenHandleTask(bool isDelay);
    void CancelHiddenHandleTask();
    SelectMenuInfo GetSelectMenuInfo();
    void UpdateViewPort(const std::optional<RectF>& viewPort);
    void UpdateSelectArea(const RectF& selectArea) override;
    void SetHandleCircleIsShow(bool isFirst, bool isShow);
    void SetIsHandleLineShow(bool isShow);
    void UpdateMenuAccessibility(bool menuIsShow);

protected:
    void CheckHandleReverse() override;
    void UpdateHandleHotZone() override;
    void UpdateMouseHotZone();

private:
    bool UpdateHandleHotZoneWithPoint();
    void UpdateHandleHotRegion(RectF& hotRegion, const OffsetF& offset);
    DimensionRect ConvertToHotRect(const RectF& rect);
    bool IsHandleInSameLine(const RectF& first, const RectF& second);
    OffsetF GetHandleHotZoneOffset(bool isFirst, float raidus, bool handleOnTop);
    bool IsDraggingSingleHandle();

private:
    ACE_DISALLOW_COPY_AND_MOVE(SelectContentOverlayPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_CONTENT_OVERLAY_PATTERN_H
