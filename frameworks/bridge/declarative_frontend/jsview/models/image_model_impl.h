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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H

#include "core/components_ng/pattern/image/image_model.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

class ImageModelImpl : public OHOS::Ace::ImageModel {
public:
    void SetAlt(const std::string& src) override;
    void SetBorder(const Border& border) override;
    void SetBackBorder() override;
    void SetBlur(double blur) override;
    void SetImageFit(ImageFit value) override;
    void SetMatchTextDirection(bool value) override;
    void SetFitOriginSize(bool value) override;
    void SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback) override;
    void SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback) override;
    void SetSvgAnimatorFinishEvent(std::function<void()>&& callback) override;
    void Create(const std::string& src, RefPtr<PixelMap>& pixMap, const std::string& bundleName,
        const std::string& moduleName) override;
    void SetImageSourceSize(const std::pair<Dimension, Dimension>& size) override;
    void SetImageFill(const Color& color) override;
    void SetImageInterpolation(ImageInterpolation iterpolation) override;
    void SetImageRepeat(ImageRepeat imageRepeat) override;
    void SetImageRenderMode(ImageRenderMode imageRenderMode) override;
    bool IsSrcSvgImage() override;
    void SetAutoResize(bool autoResize) override;
    void SetSyncMode(bool syncMode) override;
    void SetColorFilterMatrix(const std::vector<float>& matrix) override;
    void SetDraggable(bool draggable) override {}
    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override;
    void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) override;
    void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) override;
    void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) override;
    void SetOnDrop(NG::OnDragDropFunc&& onDrop) override;
    void SetCopyOption(const CopyOptions& copyOption) override;
    bool UpdateDragItemInfo(DragItemInfo& itemInfo) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_IMAGE_MODEL_IMPL_H
