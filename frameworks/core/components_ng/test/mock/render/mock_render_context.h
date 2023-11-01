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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H

#include "gmock/gmock.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class MockRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(MockRenderContext, RenderContext)
public:
    ~MockRenderContext() override = default;

    MOCK_METHOD4(SetBounds, void(float, float, float, float));
    MOCK_METHOD1(GetPointWithTransform, void(PointF&));
    MOCK_METHOD2(AddChild, void(const RefPtr<RenderContext>& renderContext, int index));
    MOCK_METHOD1(AnimateHoverEffectScale, void(bool));
    MOCK_METHOD1(SetVisible, void(bool));

    void ResetBlendBgColor() override
    {
        blendColor_ = Color::TRANSPARENT;
    }

    void BlendBgColor(const Color& color) override
    {
        blendColor_ = color;
    }

    std::vector<double> GetTrans() override
    {
        return transInfo_;
    }

    RectF GetPaintRectWithTransform() override
    {
        return rect_;
    }

    RectF rect_;
    Color blendColor_ = Color::TRANSPARENT;
    std::vector<double> transInfo_ = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
