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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H

#include "core/components/image/image_event.h"
#include "core/components_ng/pattern/image/image_model.h"

namespace OHOS::Ace::NG {

// ImageModel is essentially the same class as ImageView
// there should be only one left in the final implementation

class  ACE_EXPORT ImageModelNG : public OHOS::Ace::Framework::ImageModel {
public:
    virtual void SetAlt(std::string src);
    virtual void SetImageFit(int32_t value);
    virtual void SetMatchTextDirection(bool value);
    virtual void SetFitMaxSize(bool value);
    virtual void SetOnComplete(std::function<void(const LoadImageSuccessEvent& info)>&& callback);
    virtual void SetOnError(std::function<void(const LoadImageFailEvent& info)>&& callback);
    virtual void SetSvgAnimatorFinishEvent(std::function<void()>&& callback);
    virtual void Create(std::string src, bool noPixMap, RefPtr<PixelMap>& pixMap);
    virtual void SetImageSourceSize(std::pair<Dimension, Dimension> size);
    virtual void SetImageFill(Color color);
    virtual void SetImageInterpolation(ImageInterpolation iterpolation);
    virtual void SetImageRepeat(ImageRepeat imageRepeat);
    virtual void SetImageRenderMode(ImageRenderMode imageRenderMode);
    virtual bool IsSrcSvgImage();
    virtual void SetAutoResize(bool autoResize);
    virtual void SetSyncMode(bool syncMode);
    virtual void SetColorFilterMatrix(const std::vector<float>& matrix);
    virtual void SetOnDragStartId(const OnDragFunc& onDragStartId);
    virtual void SetOnDragEnterId(const OnDropFunc&  onDragStartId);
    virtual void SetOnDragLeaveId(const OnDropFunc& onDragStartId);
    virtual void SetOnDragMoveId(const OnDropFunc& onDragMoveId);
    virtual void SetOnDropId(const OnDropFunc& onDropId);
    virtual void SetCopyOption(const CopyOptions& copyOption);
    virtual bool UpdateDragItemInfo(DragItemInfo& itemInfo);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_IMAGE_IMAGE_MODEL_NG_H
