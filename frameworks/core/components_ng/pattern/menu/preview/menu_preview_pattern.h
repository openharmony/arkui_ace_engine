/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PREVIEW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PREVIEW_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
class MenuPreviewPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(MenuPreviewPattern, Pattern);

public:
    MenuPreviewPattern() : LinearLayoutPattern(true) {}
    ~MenuPreviewPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MenuPreviewLayoutAlgorithm>();
    }

    void SetFirstShow()
    {
        isFirstShow_ = true;
    }

    void SetHasPreviewTransitionEffect(bool hasPreviewTransitionEffect)
    {
        hasPreviewTransitionEffect_ = hasPreviewTransitionEffect;
    }

    void SetIsShowHoverImage(bool isShow)
    {
        isShowHoverImage_ = isShow;
    }

    bool GetIsShowHoverImage() const
    {
        return isShowHoverImage_;
    }

    void SetCustomPreviewWidth(float width)
    {
        customPreviewWidth_ = width;
    }

    float GetCustomPreviewWidth() const
    {
        return customPreviewWidth_;
    }

    void SetCustomPreviewHeight(float height)
    {
        customPreviewHeight_ = height;
    }

    float GetCustomPreviewHeight() const
    {
        return customPreviewHeight_;
    }

    void SetCustomPreviewScaleFrom(float scaleFrom)
    {
        customPreviewScaleFrom_ = scaleFrom;
    }

    float GetCustomPreviewScaleFrom() const
    {
        return customPreviewScaleFrom_;
    }

    void SetCustomPreviewScaleTo(float scaleTo)
    {
        customPreviewScaleTo_ = scaleTo;
    }

    float GetCustomPreviewScaleTo() const
    {
        return customPreviewScaleTo_;
    }

    void SetHoverImageDisAppearScaleTo(float scaleTo)
    {
        hoverImageDisAppearScale_ = scaleTo;
    }

    float GetHoverImageDisAppearScaleTo() const
    {
        return hoverImageDisAppearScale_;
    }

    void SetCustomPreviewPositionXDist(float xDist)
    {
        previewPositionXDist_ = xDist;
    }

    float GetCustomPreviewPositionXDist()
    {
        return previewPositionXDist_;
    }

    void SetCustomPreviewPositionYDist(float yDist)
    {
        previewPositionYDist_ = yDist;
    }

    float GetCustomPreviewPositionYDist()
    {
        return previewPositionYDist_;
    }

    void ShowHoverImagePreviewDisAppearAnimation(const RefPtr<RenderContext>& context, float scaleFrom, float scaleTo,
        int32_t duration = 0);

    RefPtr<FrameNode> GetMenuWrapper() const;

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragEnd(float offsetX, float offsetY, float velocity);
    bool isFirstShow_ = false;
    bool hasPreviewTransitionEffect_ = false;

    bool isShowHoverImage_ = false;
    float customPreviewWidth_ = 0.0f;
    float customPreviewHeight_ = 0.0f;
    float customPreviewScaleFrom_ = 1.0f;
    float customPreviewScaleTo_ = 1.0f;
    float hoverImageDisAppearScale_ = 1.0f;
    float previewPositionXDist_ = 0.0f;
    float previewPositionYDist_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(MenuPreviewPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PREVIEW_PATTERN_H
