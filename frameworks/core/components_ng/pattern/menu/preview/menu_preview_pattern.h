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
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
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

    void SetHoverImageAfterScaleWidth(float width)
    {
        hoverImageAfterScaleWidth_ = width;
    }

    float GetHoverImageAfterScaleWidth() const
    {
        return hoverImageAfterScaleWidth_;
    }

    void SetHoverImageAfterScaleHeight(float height)
    {
        hoverImageAfterScaleHeight_ = height;
    }

    float GetHoverImageAfterScaleHeight() const
    {
        return hoverImageAfterScaleHeight_;
    }

    void SetClipStartWidth(float width)
    {
        clipStartWidth_ = width;
    }

    float GetClipStartWidth() const
    {
        return clipStartWidth_;
    }

    void SetClipStartHeight(float height)
    {
        clipStartHeight_ = height;
    }

    float GetClipStartHeight() const
    {
        return clipStartHeight_;
    }

    void SetClipStartValue(float value)
    {
        clipStartVal_ = value;
    }

    float GetClipStartValue() const
    {
        return clipStartVal_;
    }

    void SetClipEndValue(float value)
    {
        clipEndVal_ = value;
    }

    float GetClipEndValue() const
    {
        return clipEndVal_;
    }

    void SetHoverImageAfterScaleOffset(const OffsetF& offset)
    {
        hoverImageAfterScaleOffset_ = offset;
    }

    OffsetF GetHoverImageAfterScaleOffset() const
    {
        return hoverImageAfterScaleOffset_;
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

    void SetCustomPreviewAfterScaleWidth(float width)
    {
        customPreviewAfterScaleWidth_ = width;
    }

    float GetCustomPreviewAfterScaleWidth() const
    {
        return customPreviewAfterScaleWidth_;
    }

    void SetCustomPreviewAfterScaleHeight(float height)
    {
        customPreviewAfterScaleHeight_ = height;
    }

    float GetCustomPreviewAfterScaleHeight() const
    {
        return customPreviewAfterScaleHeight_;
    }

    void SetStackAfterScaleActualWidth(float width)
    {
        stackAfterScaleActualWidth_ = width;
    }

    float GetStackAfterScaleActualWidth() const
    {
        return stackAfterScaleActualWidth_;
    }

    void SetStackAfterScaleActualHeight(float height)
    {
        stackAfterScaleActualHeight_ = height;
    }

    float GetStackAfterScaleActualHeight() const
    {
        return stackAfterScaleActualHeight_;
    }

    void SetIsWidthDistLarger(bool widthDistLarger)
    {
        isWidthDistLarge_ = widthDistLarger;
    }

    bool GetIsWidthDistLarger() const
    {
        return isWidthDistLarge_;
    }

    void SetHoverImageScaleFrom(float scaleFrom)
    {
        hoverImageScaleFrom_ = scaleFrom;
    }

    float GetHoverImageScaleFrom() const
    {
        return hoverImageScaleFrom_;
    }

    void SetHoverImageScaleTo(float scaleTo)
    {
        hoverImageScaleTo_ = scaleTo;
    }

    float GetHoverImageScaleTo() const
    {
        return hoverImageScaleTo_;
    }

    void SetCustomPreviewScaleTo(float scaleTo)
    {
        customPreviewScaleTo_ = scaleTo;
    }

    float GetCustomPreviewScaleTo() const
    {
        return customPreviewScaleTo_;
    }

    void SetIsHoverImageScaleNearEqual(bool isEqual)
    {
        isHoverImageScaleNearEqual_ = isEqual;
    }

    bool IsHoverImageScaleNearEqual() const
    {
        return isHoverImageScaleNearEqual_;
    }

    void SetIsHoverImageAnimationPlaying(bool isPlay)
    {
        isHoverImageAnimationPlaying_ = isPlay;
    }

    bool IsHoverImageAnimationPlaying() const
    {
        return isHoverImageAnimationPlaying_;
    }

    RefPtr<FrameNode> GetMenuWrapper() const;

    void SetIsHoverImageScalePlaying(bool isPlay)
    {
        isHoverImageScalePlaying_ = isPlay;
    }

    bool IsHoverImageScalePlaying()
    {
        return isHoverImageScalePlaying_;
    }

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragEnd(float offsetX, float offsetY, float velocity);
    void UpdateShowScale(const RefPtr<RenderContext>& context, const RefPtr<MenuTheme>& menuTheme,
        const RefPtr<MenuPattern>& menuPattern);
    bool isFirstShow_ = false;
    bool hasPreviewTransitionEffect_ = false;

    bool isShowHoverImage_ = false;
    bool isHoverImageScaleNearEqual_ = false;
    bool isHoverImageAnimationPlaying_ = false;
    bool isWidthDistLarge_ = false;
    bool isHoverImageScalePlaying_ = false;
    OffsetF hoverImageAfterScaleOffset_;
    float hoverImageAfterScaleWidth_ = 0.0f;
    float hoverImageAfterScaleHeight_ = 0.0f;
    float clipStartWidth_ = 0.0f;
    float clipStartHeight_ = 0.0f;
    float clipStartVal_ = 0.0f;
    float clipEndVal_ = 0.0f;
    float customPreviewWidth_ = 0.0f;
    float customPreviewHeight_ = 0.0f;
    float customPreviewAfterScaleWidth_ = 0.0f;
    float customPreviewAfterScaleHeight_ = 0.0f;
    float stackAfterScaleActualWidth_ = 0.0f;
    float stackAfterScaleActualHeight_ = 0.0f;
    float hoverImageScaleFrom_ = 1.0f;
    float hoverImageScaleTo_ = 1.0f;
    float customPreviewScaleTo_ = 1.0f;
    ACE_DISALLOW_COPY_AND_MOVE(MenuPreviewPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PREVIEW_PATTERN_H
