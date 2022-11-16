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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H

#include "utils/point.h"
#include "utils/rect.h"
#include "utils/scalar.h"

#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/rosen/mock_pen.h"
#include "core/components_ng/test/mock/rosen/testing_color.h"

namespace OHOS::Ace {
using RSCanvas = Testing::MockCanvas;
using RSPen = Testing::MockPen;
using RSColor = Testing::TestingColor;
using RSPoint = Rosen::Drawing::PointF;
using RSScalar = Rosen::Drawing::scalar;
using RSRect = Rosen::Drawing::RectF;
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H
