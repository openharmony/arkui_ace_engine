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

#include "core/components_ng/image_provider/image_object.h"

namespace OHOS::Ace::NG {
int32_t ImageObject::GetFrameCount() const
{
    return 1;
}

const SizeF& ImageObject::GetImageSize() const
{
    return {};
}

ImageRotateOrientation ImageObject::GetOrientation() const
{
    return static_cast<ImageRotateOrientation>(0);
}

void ImageObject::SetOrientation(ImageRotateOrientation) {}

void ImageObject::SetUserOrientation(ImageRotateOrientation) {}
} // namespace OHOS::Ace::NG
