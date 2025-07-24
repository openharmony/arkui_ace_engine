/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_PAINT_METHOD_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_modifier.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/refresh/refresh_animation_state.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LoadingProgressPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(LoadingProgressPaintMethod, NodePaintMethod)
public:
    explicit LoadingProgressPaintMethod(const RefPtr<LoadingProgressModifier>& loadingProgressModifier)
        : loadingProgressModifier_(loadingProgressModifier)
    {}
    ~LoadingProgressPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(loadingProgressModifier_, nullptr);
        return loadingProgressModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(loadingProgressModifier_);
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto paintProperty = DynamicCast<LoadingProgressPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        auto host = paintProperty->GetHost();
        auto themeScopeId = host ? host->GetThemeScopeId() : 0;
        auto progressTheme = pipeline->GetTheme<ProgressTheme>(themeScopeId);
        CHECK_NULL_VOID(progressTheme);
        loadingProgressModifier_->SetEnableLoading(paintProperty->GetEnableLoadingValue(true));
        loadingProgressModifier_->SetContentOffset(paintWrapper->GetContentOffset());
        loadingProgressModifier_->SetContentSize(paintWrapper->GetContentSize());
        auto renderContext = paintWrapper->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (renderContext->HasForegroundColorStrategy()) {
            paintProperty->UpdateColor(Color::FOREGROUND);
        }
        if (!loadingProgressModifier_->GetForegroundColorParseFailed() || themeScopeId) {
            color_ = paintProperty->GetColor().value_or(progressTheme->GetLoadingColor());
            loadingProgressModifier_->SetColor(LinearColor(color_));
        }
        if (loadingProgressModifier_->GetOwner() == LoadingProgressOwner::SELF) {
            loadingProgressModifier_->ChangeSizeScaleData(1.0f);
            loadingProgressModifier_->StartRecycle();
            return;
        }
        auto loadingState = paintProperty->GetRefreshAnimationState().value_or(RefreshAnimationState::FOLLOW_HAND);
        switch (loadingState) {
            case RefreshAnimationState::FOLLOW_HAND:
                loadingProgressModifier_->ChangeRefreshFollowData(
                    paintProperty->GetRefreshSizeScaleRatio().value_or(1.0f));
                break;
            case RefreshAnimationState::FOLLOW_TO_RECYCLE:
                loadingProgressModifier_->StartTransToRecycleAnimation();
                break;
            case RefreshAnimationState::RECYCLE:
                loadingProgressModifier_->ChangeSizeScaleData(paintProperty->GetRefreshSizeScaleRatio().value_or(1.0f));
                loadingProgressModifier_->StartRecycle();
                break;
            default:
                break;
        }
    }

private:
    Color color_ = Color::BLUE;
    RefPtr<LoadingProgressModifier> loadingProgressModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_PAINT_METHOD_H
