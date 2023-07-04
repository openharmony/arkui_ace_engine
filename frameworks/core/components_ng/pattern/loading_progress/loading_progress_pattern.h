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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_PATTERN_H

#include "base/log/log_wrapper.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_method.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
// ProgressPattern is the base class for text render node to perform paint progress.
class LoadingProgressPattern : public Pattern {
    DECLARE_ACE_TYPE(LoadingProgressPattern, Pattern);

public:
    LoadingProgressPattern() = default;
    ~LoadingProgressPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!loadingProgressModifier_) {
            auto host = GetHost();
            CHECK_NULL_RETURN(host, nullptr);
            auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
            CHECK_NULL_RETURN(paintProperty, nullptr);
            auto loadingOwner =
                paintProperty->GetLoadingProgressOwner().value_or(LoadingProgressOwner::SELF);
            loadingProgressModifier_ = AceType::MakeRefPtr<LoadingProgressModifier>(loadingOwner);
        }
        return MakeRefPtr<LoadingProgressPaintMethod>(loadingProgressModifier_);
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LoadingProgressLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LoadingProgressLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<LoadingProgressPaintProperty>();
    }

    void OnVisibleChange(bool isVisible) override;

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }
private:
    void RegisterVisibleAreaChange();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void StartAnimation();
    void StopAnimation();

    bool hasVisibleChangeRegistered_ = false;
    bool enableLoading_ = true;
    bool isVisibleArea_ = true;
    bool isVisible_ = true;
    bool isShow_ = true;
    RefPtr<LoadingProgressModifier> loadingProgressModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_PATTERN_H
