/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_DRAWING_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_DRAWING_H

#include "draw/canvas.h"
#include "render_service_base/include/render/rs_image.h"
#include "utils/sampling_options.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
using RSCanvas = Rosen::Drawing::Canvas;
using RSAdaptiveImageInfo = Rosen::Drawing::AdaptiveImageInfo;
using RSSamplingOptions = Rosen::Drawing::SamplingOptions;
using RSPoint = Rosen::Drawing::Point;
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_DRAWING_H
