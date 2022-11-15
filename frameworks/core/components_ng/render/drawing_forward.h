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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_FORWARD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_FORWARD_H

#ifndef ACE_UNITTEST
namespace OHOS::Rosen {
class RSNode;
namespace Drawing {
class Canvas;
class RectF;
} // namespace Drawing
} // namespace OHOS::Rosen
namespace OHOS::Ace {
using RSCanvas = Rosen::Drawing::Canvas;
using RSRect = Rosen::Drawing::RectF;
using RSNode = Rosen::RSNode;
} // namespace OHOS::Ace
#else
#include "core/components_ng/render/drawing_mock.h"
#endif
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_FORWARD_H
