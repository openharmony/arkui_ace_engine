/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/animated_image.h"

namespace OHOS::Ace::NG {
RefPtr<CanvasImage> AnimatedImage::Create(
    const RefPtr<DrawingImageData>& data, const ResizeParam& size, const std::string& url)
{
    return nullptr;
}

bool AnimatedImage::GetIsAnimating() const
{
    return false;
}
} // namespace OHOS::Ace::NG