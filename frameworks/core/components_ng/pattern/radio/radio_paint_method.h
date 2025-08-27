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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/radio/radio_modifier.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class RadioPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RadioPaintMethod, NodePaintMethod);

public:
    explicit RadioPaintMethod(const RefPtr<RadioModifier>& radioModifier) : radioModifier_(radioModifier) {}

    ~RadioPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* /* paintWrapper */) override
    {
        CHECK_NULL_RETURN(radioModifier_, nullptr);
        return radioModifier_;
    }

    void UpdateUIStatus(bool checked, const RefPtr<FrameNode>& host);

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void SetHotZoneOffset(const OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(const SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

    void SetEnabled(const bool enabled)
    {
        enabled_ = enabled;
    }

    void SetIsOnAnimationFlag(const bool isOnAnimationFlag)
    {
        isOnAnimationFlag_ = isOnAnimationFlag;
    }

    void SetIsFirstCreated(const bool isFirstCreated)
    {
        isFirstCreated_ = isFirstCreated;
    }

    void SetTotalScale(const float totalScale)
    {
        totalScale_ = totalScale;
    }

    void SetPointScale(const float pointScale)
    {
        pointScale_ = pointScale;
    }

    void SetRingPointScale(const float ringPointScale)
    {
        ringPointScale_ = ringPointScale;
    }

    void SetUIStatus(const UIStatus uiStatus)
    {
        uiStatus_ = uiStatus;
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetShowHoverEffect(bool showHoverEffect)
    {
        showHoverEffect_ = showHoverEffect;
    }

    void SetIsUserSetUncheckBorderColor(const bool isUserSet)
    {
        isUserSetUncheckBorderColor_ = isUserSet;
    }

private:
    Color pointColor_;
    Color activeColor_;
    Color inactiveColor_;
    bool enabled_ = true;
    bool isOnAnimationFlag_ = false;
    bool isFirstCreated_ = true;
    bool showHoverEffect_ = true;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    float ringPointScale_ = 0.0f;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;

    RefPtr<RadioModifier> radioModifier_;
    bool isUserSetUncheckBorderColor_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RADIO_RADIO_PAINT_METHOD_H
