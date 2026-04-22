/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/depth_component/depth_component_paint_method.h"

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/depth_component/depth_component_pattern.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

class DepthComponentContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(DepthComponentContentModifier, ContentModifier);

public:
    explicit DepthComponentContentModifier(const WeakPtr<DepthComponentPaintMethod>& paintMethod)
        : paintMethod_(paintMethod)
    {}

    ~DepthComponentContentModifier() override = default;

    void onDraw(DrawingContext& /*context*/) override
    {
        auto paintMethod = paintMethod_.Upgrade();
        CHECK_NULL_VOID(paintMethod);
        paintMethod->PerformPaint(paintWrapper_);
    }

    void UpdatePaintWrapper(PaintWrapper* paintWrapper)
    {
        paintWrapper_ = paintWrapper;
        SetContentChange();
    }

private:
    WeakPtr<DepthComponentPaintMethod> paintMethod_;
    PaintWrapper* paintWrapper_ = nullptr;
};

DepthComponentPaintMethod::DepthComponentPaintMethod(const WeakPtr<DepthComponentPattern>& pattern) : pattern_(pattern)
{
    contentModifier_ = MakeRefPtr<DepthComponentContentModifier>(WeakClaim(this));

    canvasRenderContext_ = MakeRefPtr<RosenRenderContext>();
    CHECK_NULL_VOID(canvasRenderContext_);
    RenderContext::ContextParam param = { RenderContext::ContextType::CANVAS };
    canvasRenderContext_->InitContext(false, param);
}

RefPtr<Modifier> DepthComponentPaintMethod::GetContentModifier(PaintWrapper* paintWrapper)
{
    return contentModifier_;
}

void DepthComponentPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(contentModifier_);
    canvasRenderContext_->FlushContentModifier(contentModifier_);
}

void DepthComponentPaintMethod::PerformPaint(PaintWrapper* paintWrapper)
{
    ACE_FUNCTION_TRACE();
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->OnPaint3D();
}

} // namespace OHOS::Ace::NG
