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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDERING_CONTEXT_2D_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RENDERING_CONTEXT_2D_CONTENT_MODIFIER_H

#include <optional>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Rosen {
class RSRecordingCanvas;
}

namespace OHOS::Ace::NG {
class Pattern;

class RenderingContext2DModifier : public ContentModifier {
    DECLARE_ACE_TYPE(RenderingContext2DModifier, ContentModifier)

public:
    RenderingContext2DModifier();
    ~RenderingContext2DModifier() override = default;
    void onDraw(DrawingContext& drawingContext) override;

    void MarkModifierDirty()
    {
        CHECK_NULL_VOID(needRender_);
        needRender_->Set(!needRender_->Get());
    }

    void UpdateCanvas(std::shared_ptr<OHOS::Rosen::RSRecordingCanvas> rsRecordingCanvas)
    {
        rsRecordingCanvas_ = rsRecordingCanvas;
    }

private:
    RefPtr<PropertyBool> needRender_;
    std::shared_ptr<OHOS::Rosen::RSRecordingCanvas> rsRecordingCanvas_;
    ACE_DISALLOW_COPY_AND_MOVE(RenderingContext2DModifier);
};
} // namespace OHOS::Ace::NG

#endif