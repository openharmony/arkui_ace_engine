/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_H

#include "base/geometry/dimension.h"
#include "base/image/pixel_map.h"
#include "base/memory/referenced.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/image/image_event.h"

namespace OHOS::Ace {

// ImageModel is essentially the same class as ImageView
// there should be only one left in the final implementation
class ImageModel {
public:
    static ImageModel* GetInstance();
    virtual ~ImageModel() = default;

    virtual void SetAlt(const std::string& src) = 0;
    virtual void SetBlur(double blur) = 0;
    virtual void SetBorder(const Border& border) = 0;
    virtual void SetImageFit(int32_t value) = 0;
    virtual void SetMatchTextDirection(bool value) = 0;
    virtual void SetFitMaxSize(bool value) = 0;
    virtual void SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback) = 0;
    virtual void SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback) = 0;
    virtual void SetSvgAnimatorFinishEvent(std::function<void()>&& callback) = 0;
    virtual void Create(const std::string& src, bool noPixMap, RefPtr<PixelMap>& pixMap) = 0;
    virtual void SetImageSourceSize(const std::pair<Dimension, Dimension>& size) = 0;
    virtual void SetImageFill(const Color& color) = 0;
    virtual void SetImageInterpolation(ImageInterpolation interpolation) = 0;
    virtual void SetImageRepeat(ImageRepeat imageRepeat) = 0;
    virtual void SetImageRenderMode(ImageRenderMode imageRenderMode) = 0;
    virtual bool IsSrcSvgImage() = 0;
    virtual void SetAutoResize(bool autoResize) = 0;
    virtual void SetSyncMode(bool syncMode) = 0;
    virtual void SetColorFilterMatrix(const std::vector<float>& matrix) = 0;
    virtual void SetOnDragStartId(const OnDragFunc& onDragStartId) = 0;
    virtual void SetOnDragEnterId(const OnDropFunc& onDragStartId) = 0;
    virtual void SetOnDragLeaveId(const OnDropFunc& onDragStartId) = 0;
    virtual void SetOnDragMoveId(const OnDropFunc& onDragMoveId) = 0;
    virtual void SetOnDropId(const OnDropFunc& onDropId) = 0;
    virtual void SetCopyOption(const CopyOptions& copyOption) = 0;
    virtual bool UpdateDragItemInfo(DragItemInfo& itemInfo) = 0;

private:
    static std::unique_ptr<ImageModel> instance_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_H
