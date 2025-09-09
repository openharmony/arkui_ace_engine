/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <memory>

#include "core/components_ng/manager/drag_drop/drag_drop_related_configuration.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG {

RefPtr<DragSpringLoadingConfiguration> DragDropRelatedConfigurations::GetOrCreateDragSpringLoadingConfiguration()
{
    if (dragSpringLoadingConfiguration_) {
        return dragSpringLoadingConfiguration_;
    }
    dragSpringLoadingConfiguration_ = MakeRefPtr<DragSpringLoadingConfiguration>();
    return dragSpringLoadingConfiguration_;
}

void DragDropRelatedConfigurations::SetDragSpringLoadingConfiguration(
    const RefPtr<DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration)
{
    CHECK_NULL_VOID(dragSpringLoadingConfiguration);
    dragSpringLoadingConfiguration_ = std::move(dragSpringLoadingConfiguration);
}

DragPreviewOption DragDropRelatedConfigurations::GetOrCreateDragPreviewOption()
{
    if (previewOption_) {
        return *previewOption_;
    }
    previewOption_ = std::make_unique<DragPreviewOption>();
    CHECK_NULL_RETURN(previewOption_, DragPreviewOption());
    return *previewOption_;
}

void DragDropRelatedConfigurations::SetOptionsAfterApplied(const OptionsAfterApplied& optionsAfterApplied)
{
    if (!previewOption_) {
        previewOption_ = std::make_unique<DragPreviewOption>();
    }
    CHECK_NULL_VOID(previewOption_);
    previewOption_->options = optionsAfterApplied;
}

void DragDropRelatedConfigurations::SetDragPreviewOption(const DragPreviewOption& previewOption, bool isResetOptions)
{
    if (isResetOptions) {
        previewOption_ = std::make_unique<DragPreviewOption>(previewOption);
        CHECK_NULL_VOID(previewOption_);
        previewOption_->onApply = std::move(previewOption.onApply);
        return;
    }
    OptionsAfterApplied options = previewOption_ ? previewOption_->options : OptionsAfterApplied();
    previewOption_ = std::make_unique<DragPreviewOption>(previewOption);
    CHECK_NULL_VOID(previewOption_);
    previewOption_->options = options;
    previewOption_->onApply = std::move(previewOption.onApply);
}
} // namespace OHOS::Ace::NG