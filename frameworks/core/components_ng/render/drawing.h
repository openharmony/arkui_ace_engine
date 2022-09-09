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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_H

#include "draw/canvas.h"
#include "image/image.h"
#include "rosen_text/ui/font_collection.h"
#include "rosen_text/ui/typography.h"
#include "rosen_text/ui/typography_create.h"

namespace OHOS::Ace {

using RSCanvas = Rosen::Drawing::Canvas;
using RSImage = Rosen::Drawing::Image;
using RSBrush = Rosen::Drawing::Brush;
using RSFilter = Rosen::Drawing::Filter;
using RSColorFilter = Rosen::Drawing::ColorFilter;
using RSColorMatrix = Rosen::Drawing::ColorMatrix;
using RSPen = Rosen::Drawing::Pen;
using RSColor = Rosen::Drawing::Color;
using RSRect = Rosen::Drawing::RectF;
using RSPoint = Rosen::Drawing::PointF;
using RSBlendMode = Rosen::Drawing::BlendMode;
using RSSamplingOptions = Rosen::Drawing::SamplingOptions;
using RSRoundRect = Rosen::Drawing::RoundRect;
using RSPath = Rosen::Drawing::Path;

using RSParagraph = rosen::Typography;
using RSParagraphBuilder = rosen::TypographyCreate;
using RSFontCollection = rosen::FontCollection;
using RSParagraphStyle = rosen::TypographyStyle;
using RSTextStyle = rosen::TextStyle;

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_H
