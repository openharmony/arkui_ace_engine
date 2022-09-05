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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Rosen::Drawing {
class Canvas;
}
namespace OHOS::Ace::NG {
class GeometryNode;
class RenderPropertyNode;
class FrameNode;

using RSCanvas = Rosen::Drawing::Canvas;
using CanvasDrawFunction = std::function<void(RSCanvas& canvas)>;

// RenderContext is used for render node to paint.
class RenderContext : public virtual AceType {
    DECLARE_ACE_TYPE(NG::RenderContext, AceType)

public:
    ~RenderContext() override = default;

    static RefPtr<RenderContext> Create();

    void SetRequestFrame(const std::function<void()>& requestFrame)
    {
        requestFrame_ = requestFrame;
    }

    virtual void FlushContentDrawFunction(CanvasDrawFunction&& contentDraw) {}

    virtual void FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw) {}

    virtual void FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw) {}

    virtual void RebuildFrame(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void SyncGeometryProperties(GeometryNode* geometryNode) {}

    virtual void InitContext(bool isRoot, const std::optional<std::string>& surfaceName) {}

    virtual void StartRecording() {}
    virtual void StopRecordingIfNeeded() {}

    virtual void SetDrawContentAtLast(bool useDrawContentLastOrder) {}

    virtual void ResetBlendBgColor() {}

    virtual void BlendBgColor(const Color& color) {}

    virtual void SetClipToFrame(bool useClip) {}

    virtual RefPtr<Canvas> GetCanvas() = 0;

    virtual void Restore() = 0;

    void RequestNextFrame() const
    {
        if (requestFrame_) {
            requestFrame_();
        }
    }

    ACE_DEFINE_PROPERTY_GROUP(Background, BackgroundProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundColor, Color);
    // TODO Add BorderRadius in group.
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BorderRadius, BorderRadiusProperty);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BorderColor, BorderColorProperty);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BorderWidth, BorderWidthProperty);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BorderStyle, BorderStyleProperty);

protected:
    RenderContext() = default;

    virtual void OnBackgroundColorUpdate(const Color& value) {}
    virtual void OnBorderRadiusUpdate(const BorderRadiusProperty& value) {}
    virtual void OnBorderColorUpdate(const BorderColorProperty& value) {}
    virtual void OnBorderWidthUpdate(const BorderWidthProperty& value) {}
    virtual void OnBorderStyleUpdate(const BorderStyleProperty& value) {}

private:
    std::function<void()> requestFrame_;
    BorderRadiusProperty borderRadius_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
