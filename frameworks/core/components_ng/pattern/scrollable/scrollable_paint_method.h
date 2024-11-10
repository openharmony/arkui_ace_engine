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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_PAINT_METHOD_H

#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScrollablePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ScrollablePaintMethod, NodePaintMethod)
public:
    ScrollablePaintMethod() = default;
    ScrollablePaintMethod(bool vertical, bool isReverse, bool isVerticalReverse = false)
        : vertical_(vertical), isReverse_(isReverse), isVerticalReverse_(isVerticalReverse)
    {}
    ~ScrollablePaintMethod() override = default;

    void SetOverlayRenderContext(const RefPtr<RenderContext>& overlayRenderContext)
    {
        overlayRenderContext_ = overlayRenderContext;
    }

    void SetFadingInfo(bool isFadingTop, bool isFadingBottom, bool hasFadingEdge, float percentFading = 0.0f,
        float startPercent = 0.0f, float endPercent = 1.0f)
    {
        isFadingTop_ = isFadingTop;
        isFadingBottom_ = isFadingBottom;
        hasFadingEdge_ = hasFadingEdge;
        percentFading_ = percentFading;
        startPercent_ = startPercent;
        endPercent_ = endPercent;
    }

protected:
    void UpdateFadingGradient(const RefPtr<RenderContext>& renderContext);

    /**
     * @brief Try to set content clip to render context.
     *
     * @return true if content clip is set up
     */
    bool TryContentClip(PaintWrapper* wrapper);

    bool vertical_ = false;
    bool isReverse_ = false;
    bool isVerticalReverse_ = false;

private:
    /**
     * @brief Return the default content clip mode.
     */
    virtual ContentClipMode GetDefaultContentClip() const = 0;

    RefPtr<RenderContext> overlayRenderContext_;
    bool isFadingTop_ = false;
    bool isFadingBottom_ = false;
    bool hasFadingEdge_ = false;
    float percentFading_ = 0.0f;
    float startPercent_ = 0.0f;
    float endPercent_ = 1.0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_PAINT_METHOD_H
