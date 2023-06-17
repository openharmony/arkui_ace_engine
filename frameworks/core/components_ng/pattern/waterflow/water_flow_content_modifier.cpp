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

#include "core/components_ng/pattern/waterflow/water_flow_content_modifier.h"

namespace OHOS::Ace::NG {
WaterFlowContentModifier::WaterFlowContentModifier()
{
    clipOffset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    clipSize_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(SizeF());
    clip_ = AceType::MakeRefPtr<PropertyBool>(true);

    AttachProperty(clipOffset_);
    AttachProperty(clipSize_);
    AttachProperty(clip_);
}

void WaterFlowContentModifier::onDraw(DrawingContext& context)
{
    if (clip_->Get()) {
        auto offset = clipOffset_->Get();
        auto size = clipSize_->Get();
        auto clipRect =
            RSRect(offset.GetX(), offset.GetY(), offset.GetX() + size.Width(), offset.GetY() + size.Height());
        context.canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }
}
} // namespace OHOS::Ace::NG
