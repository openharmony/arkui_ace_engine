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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_PAINT_METHOD_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_modifer.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LoadingProgressPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(LoadingProgressPaintMethod, NodePaintMethod)
public:
    explicit LoadingProgressPaintMethod(const RefPtr<LoadingProgressModifier>& loadingProgressModifier)
        : loadingProgressModifier_(loadingProgressModifier)
    {}
    ~LoadingProgressPaintMethod() override = default;

    RefPtr<Modifier> GetModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(loadingProgressModifier_, nullptr);
        return loadingProgressModifier_;
    }

    void UpdateModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(loadingProgressModifier_);
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto progressTheme = pipeline->GetTheme<ProgressTheme>();
        CHECK_NULL_VOID(progressTheme);

        auto paintProperty = DynamicCast<LoadingProgressPaintProperty>(paintWrapper->GetPaintProperty());
        if (paintProperty) {
            color_ = paintProperty->GetColor().value_or(progressTheme->GetLoadingColor());
        }
        loadingProgressModifier_->SetDate(FULL_COUNT);
        loadingProgressModifier_->SetColor(LinearColor(color_));
    }

private:
    Color color_ = Color::BLUE;
    RefPtr<LoadingProgressModifier> loadingProgressModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(LoadingProgressPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PROGRESS_LOADING_PROGRESS_PAINT_METHOD_H
