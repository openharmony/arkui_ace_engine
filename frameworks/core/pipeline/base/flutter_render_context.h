/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_FLUTTER_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_FLUTTER_RENDER_CONTEXT_H

#include "flutter/lib/ui/compositing/scene.h"
#include "flutter/lib/ui/compositing/scene_builder.h"
#include "flutter/lib/ui/painting/canvas.h"
#include "flutter/lib/ui/painting/picture_recorder.h"

#include "base/geometry/rect.h"
#include "core/pipeline/base/render_context.h"
#include "core/pipeline/base/render_layer.h"
#include "core/pipeline/layers/container_layer.h"
#include "core/pipeline/layers/picture_layer.h"

namespace OHOS::Ace {

class FlutterRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(FlutterRenderContext, RenderContext)

public:
    FlutterRenderContext() = default;
    ~FlutterRenderContext() override;

    void Repaint(const RefPtr<RenderNode>& node) override;
    void PaintChild(const RefPtr<RenderNode>& child, const Offset& offset) override;

    void InitContext(RenderLayer layer, const Rect& rect);
    flutter::Canvas* GetCanvas();
    void StopRecordingIfNeeded();

    Flutter::ContainerLayer* GetContainerLayer() const
    {
        return containerLayer_;
    }

    bool IsRecording()
    {
        return !!canvas_;
    }

private:
    void StartRecording();

    fml::RefPtr<flutter::PictureRecorder> recorder_;
    fml::RefPtr<flutter::Canvas> canvas_;
    Flutter::ContainerLayer* containerLayer_ = nullptr;
    RefPtr<Flutter::PictureLayer> currentLayer_;
    Rect estimatedRect_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_FLUTTER_RENDER_CONTEXT_H
