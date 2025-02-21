/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/common/container.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_base.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_owner.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class LoadingProgressModifier : public ContentModifier {
    DECLARE_ACE_TYPE(LoadingProgressModifier, ContentModifier);

public:
    explicit LoadingProgressModifier(LoadingProgressOwner loadingProgressOwner = LoadingProgressOwner::SELF);
    ~LoadingProgressModifier() override = default;
    void onDraw(DrawingContext& context) override;
    void DrawOrbit(DrawingContext& canvas, const CometParam& cometParam, float orbitRadius, float date);
    void DrawRing(DrawingContext& canvas, const RingParam& ringParam);
    void DrawRingBackground(DrawingContext& canvas, const RingParam& ringParam, LinearColor& ringColor);
    void StartRecycle();
    void StartRecycleRingAnimation();
    void StartRecycleCometAnimation();
    void StartCometTailAnimation();
    void StartTransToRecycleAnimation();
    void SetColor(LinearColor color)
    {
        if (color_) {
            color_->Set(color);
        }
    }

    void DrawCustomStyle(DrawingContext& context);
    void RefreshRecycle(DrawingContext& context, Color& color, float scale);
    void ChangeRefreshFollowData(float refreshFollowRatio);
    void ChangeSizeScaleData(float fadeAwayRatio);
    float CorrectNormalize(float originData);

    LoadingProgressOwner GetOwner()
    {
        return loadingProgressOwner_;
    }

    void SetVisible(bool isVisible)
    {
        CHECK_NULL_VOID(isVisible_ != isVisible);
        isVisible_ = isVisible;
        isLoading_ = false;
    }

    bool GetVisible() const
    {
        return isVisible_;
    }

    void SetEnableLoading(bool enable)
    {
        CHECK_NULL_VOID(enableLoading_);
        enableLoading_->Set(enable);
    }

    void SetContentOffset(const OffsetF& offset)
    {
        CHECK_NULL_VOID(offset_);
        offset_->Set(offset);
    }

    void SetContentSize(const SizeF& contentSize)
    {
        CHECK_NULL_VOID(contentSize_);
        contentSize_->Set(contentSize);
    }
    void CloseAnimation(float date, float cometLen, float cometOpacity, float cometScale);

    void SetUseContentModifier(bool useContentModifier)
    {
        CHECK_NULL_VOID(useContentModifier_);
        useContentModifier_->Set(useContentModifier);
    }

private:
    void AdjustMatrix(RSCamera3D& camera, RSMatrix& matrix);
    float GetCurentCometOpacity(float baseOpacity, uint32_t index, uint32_t totalNumber);
    float GetCurentCometAngle(float baseAngle, uint32_t index, uint32_t totalNumber);
    uint32_t GetCometNumber();
    inline bool IsDynamicComponent()
    {
        auto container = Container::Current();
        return container && container->IsDynamicRender() &&
               container->GetUIContentType() == UIContentType::DYNAMIC_COMPONENT;
    }
    // no Animatable
    RefPtr<PropertyBool> enableLoading_;
    RefPtr<PropertyOffsetF> offset_;
    RefPtr<PropertySizeF> contentSize_;
    // Animatable
    RefPtr<AnimatablePropertyFloat> date_;
    RefPtr<AnimatablePropertyColor> color_;
    RefPtr<AnimatablePropertyFloat> centerDeviation_;
    RefPtr<AnimatablePropertyFloat> cometOpacity_;
    RefPtr<AnimatablePropertyFloat> cometSizeScale_;
    RefPtr<AnimatablePropertyFloat> cometTailLen_;
    RefPtr<AnimatablePropertyFloat> sizeScale_;
    RefPtr<PropertyBool> useContentModifier_;

    LoadingProgressOwner loadingProgressOwner_;
    bool isLoading_ = false;
    bool isVisible_ = false;
    float recycleSizeScale_ = 1.0f;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_MODIFIER_H

