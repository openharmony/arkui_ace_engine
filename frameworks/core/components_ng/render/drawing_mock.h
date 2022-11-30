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

#include "draw/clip.h"
#include "utils/point.h"
#include "utils/rect.h"
#include "utils/round_rect.h"
#include "utils/scalar.h"

#include "core/components_ng/test/mock/rosen/testing_bitmap.h"
#include "core/components_ng/test/mock/rosen/testing_brush.h"
#include "core/components_ng/test/mock/rosen/testing_canvas.h"
#include "core/components_ng/test/mock/rosen/testing_color.h"
#include "core/components_ng/test/mock/rosen/testing_filter.h"
#include "core/components_ng/test/mock/rosen/testing_mask_filter.h"
#include "core/components_ng/test/mock/rosen/testing_path.h"
#include "core/components_ng/test/mock/rosen/testing_pen.h"
#include "core/components_ng/test/mock/rosen/testing_shader_effect.h"
#include "core/components_ng/test/mock/rosen/testing_camera3d.h"

namespace OHOS::Ace {
using RSCanvas = Testing::TestingCanvas;
using RSPen = Testing::TestingPen;
using RSBrush = Testing::TestingBrush;
using RSPath = Testing::TestingPath;
using RSShaderEffect = Testing::TestingShaderEffect;
using RSFilter = Testing::TestingFilter;
using RSColor = Testing::TestingColor;
using RSMaskFilter = Testing::TestingMaskFilter;
using RSBlurType = Testing::BlurType;
using RSTileMode = Testing::TileMode;
using RSColorQuad = Testing::ColorQuad;
using RSBitmap = Testing::TestingBitmap;
using RSBitmapFormat = Testing::BitmapFormat;
using RSColorType = Testing::ColorType;
using RSAlphaType = Testing::AlphaType;
using RSPoint = Rosen::Drawing::PointF;
using RSScalar = Rosen::Drawing::scalar;
using RSRect = Rosen::Drawing::RectF;
using RSRoundRect = Rosen::Drawing::RoundRect;
using RSClipOp = Rosen::Drawing::ClipOp;
using RSCamera3D = Testing::TestingCamera3D;
using RSMatrix = Testing::TestingMatrix;
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H
