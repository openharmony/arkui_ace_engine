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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_VIEW_H

#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/image/image_event_hub.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ImageView {
public:
    static void Create(const std::string& src);
    static void SetObjectFit(ImageFit imageFit);
    static void SetAutoResize(bool autoResize);
    static void SetImageRenderMode(ImageRenderMode imageRenderMode);
    static void SetImageInterpolation(ImageInterpolation imageInterpolation);
    static void SetImageRepeat(ImageRepeat imageRepeat);
    static void SetImageSourceSize(const std::pair<Dimension, Dimension>& sourceSize);
    static void SetFitOriginalSize(bool fitOriginalSize);
    static void SetAlt(const std::string& altSrc);
    static void SetOnError(ErrorEvent&& onError);
    static void SetOnComplete(CompleteEvent&& onComplete);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_IMAGE_VIEW_H
