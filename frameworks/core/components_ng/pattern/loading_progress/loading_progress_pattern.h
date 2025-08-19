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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_PATTERN_H

#include "core/components_ng/pattern/loading_progress/loading_progress_layout_algorithm.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_layout_property.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
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

    bool OnThemeScopeUpdate(int32_t themeScopeId) override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!loadingProgressModifier_) {
            auto host = GetHost();
            CHECK_NULL_RETURN(host, nullptr);
            auto paintProperty = GetPaintProperty<LoadingProgressPaintProperty>();
            CHECK_NULL_RETURN(paintProperty, nullptr);
            auto loadingOwner =
                paintProperty->GetLoadingProgressOwner().value_or(LoadingProgressOwner::SELF);
            loadingProgressModifier_ = AceType::MakeRefPtr<LoadingProgressModifier>(loadingOwner, WeakClaim(this));
            loadingProgressModifier_->SetUseContentModifier(UseContentModifier());
            InitThemeValues();
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

    void SetBuilderFunc(LoadingProgressMakeCallback&& makeFunc)
    {
        if (makeFunc == nullptr) {
            makeFunc_ = std::nullopt;
            contentModifierNode_ = nullptr;
            OnModifyDone();
            return;
        }
        makeFunc_ = std::move(makeFunc);
    }

    const RefPtr<FrameNode>& GetContentModifierNode() const
    {
        return contentModifierNode_;
    }

    bool UseContentModifier() const
    {
        return contentModifierNode_ != nullptr;
    }
    void UpdateColor(const Color& color, bool isFristLoad = false);

    void SetForegroundColorParseFailed(bool isParseFailed)
    {
        CHECK_NULL_VOID(loadingProgressModifier_);
        loadingProgressModifier_->SetForegroundColorParseFailed(isParseFailed);
    }

    void SetColorLock(bool colorLock)
    {
        colorLock_ = colorLock;
    }

    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

private:
    void RegisterVisibleAreaChange();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnAttachToMainTree() override;
    void OnDetachFromMainTree() override;

    void OnAttachToFrameNodeMultiThread() {}
    void OnDetachFromFrameNodeMultiThread(FrameNode* frameNode) {}
    void OnAttachToMainTreeMultiThread();
    void OnDetachFromMainTreeMultiThread();
    void OnModifyDone() override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override {}
    void StartAnimation();
    void StopAnimation();
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    void InitThemeValues();
    void InitFocusEvent();
    void HandleFocusEvent();
    void HandleBlurEvent();
    void SetFocusStyle();
    void ClearFocusStyle();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void OnColorConfigurationUpdate() override;

    Color defaultColor_;
    Color focusedColor_;
    bool isFocusColorSet_ = false;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    std::optional<LoadingProgressMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;

    bool hasVisibleChangeRegistered_ = false;
    bool enableLoading_ = true;
    bool isVisibleArea_ = false;
    bool isVisible_ = true;
    bool isShow_ = true;
    bool colorLock_ = false;
    RefPtr<LoadingProgressModifier> loadingProgressModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_PATTERN_H
