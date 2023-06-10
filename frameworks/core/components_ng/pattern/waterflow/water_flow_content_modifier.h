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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_CONTENT_MODIFIER_H

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class WaterFlowContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(WaterFlowContentModifier, ContentModifier);

public:
    WaterFlowContentModifier();
    ~WaterFlowContentModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetClipOffset(OffsetF offset)
    {
        clipOffset_->Set(offset);
    }

    void SetClipSize(SizeF size)
    {
        clipSize_->Set(size);
    }

    void SetClip(bool clip)
    {
        clip_->Set(clip);
    }

private:
    RefPtr<AnimatablePropertyOffsetF> clipOffset_;
    RefPtr<AnimatablePropertySizeF> clipSize_;
    RefPtr<PropertyBool> clip_;

    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowContentModifier);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_CONTENT_MODIFIER_H
