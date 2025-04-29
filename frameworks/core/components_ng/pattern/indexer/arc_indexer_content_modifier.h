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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_INDEXER_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_INDEXER_CONTENT_MODIFIER_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class PipelineContext;

class ArcIndexerContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(ArcIndexerContentModifier, ContentModifier);

public:
    explicit ArcIndexerContentModifier();
    ~ArcIndexerContentModifier() override = default;

    void onDraw(DrawingContext& context) override;
    void DrawArcShadow(DrawingContext& context);
    void DrawArc(DrawingContext& context);

    void SetStrokeWidth(float strokeWidth)
    {
        strokeWidth_->Set(strokeWidth);
    }

    void SetArcCenter(OffsetF arcCenter)
    {
        arcCenter_->Set(arcCenter);
    }

    void SetStartAngle(float startAngle)
    {
        startAngle_->Set(startAngle);
    }

    void SetSweepAngle(float sweepAngle)
    {
        sweepAngle_->Set(sweepAngle);
    }

    void SetArcRadius(float arcRadius)
    {
        arcRadius_->Set(arcRadius);
    }

    void SetStepAngle(float stepAngle)
    {
        stepAngle_->Set(stepAngle);
    }

private:
    RefPtr<AnimatablePropertyFloat> strokeWidth_;
    RefPtr<PropertyOffsetF> arcCenter_;
    RefPtr<PropertyFloat> startAngle_;
    RefPtr<AnimatablePropertyFloat> sweepAngle_;
    RefPtr<PropertyFloat> arcRadius_;
    RefPtr<PropertyFloat> stepAngle_;
    ACE_DISALLOW_COPY_AND_MOVE(ArcIndexerContentModifier);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_INDEXER_CONTENT_MODIFIER_H
