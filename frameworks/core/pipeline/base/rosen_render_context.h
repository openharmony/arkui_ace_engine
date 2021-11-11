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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ROSEN_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ROSEN_RENDER_CONTEXT_H

#include "render_service_client/core/ui/rs_node.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkPictureRecorder.h"

#include "base/geometry/rect.h"
#include "core/pipeline/base/render_context.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RosenRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(RosenRenderContext, RenderContext)

public:
    RosenRenderContext() = default;
    ~RosenRenderContext() override;

    void Repaint(const RefPtr<RenderNode>& node) override;
    void PaintChild(const RefPtr<RenderNode>& child, const Offset& offset) override;
    bool IsIntersectWith(const RefPtr<RenderNode>& child, Offset& offset) override;
    void ClipHoleBegin(const Rect& holeRect) override;
    void ClipHoleEnd() override;

    void InitContext(const RSNode::SharedPtr& rsNode, const Rect& rect, const Offset& initialOffset = Offset::Zero());
    SkCanvas* GetCanvas();
    const RSNode::SharedPtr& GetRSNode();

    void StartRecording();
    void StopRecordingIfNeeded();

    bool IsRecording()
    {
        return !!recordingCanvas_;
    }

    sk_sp<SkPicture> FinishRecordingAsPicture()
    {
        if (recorder_) {
            auto picture = recorder_->finishRecordingAsPicture();
            if (picture) {
                return picture;
            }
        }
        return nullptr;
    }

    sk_sp<SkImage> FinishRecordingAsImage()
    {
        if (recorder_) {
            auto picture = recorder_->finishRecordingAsPicture();
            if (picture) {
                auto image = SkImage::MakeFromPicture(picture, { estimatedRect_.Width(), estimatedRect_.Height() },
                    nullptr, nullptr, SkImage::BitDepth::kU8, nullptr);
                if (image) {
                    return image;
                }
            }
        }
        return nullptr;
    }

private:
    RSNode::SharedPtr rsNode_ = nullptr;
    SkPictureRecorder* recorder_ = nullptr;
    SkCanvas* recordingCanvas_ = nullptr;
    SkCanvas* rosenCanvas_ = nullptr;
    Rect estimatedRect_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_ROSEN_RENDER_CONTEXT_H
