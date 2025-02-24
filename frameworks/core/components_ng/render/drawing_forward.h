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
enum class ClipOp;
class Pen;
class Brush;
class Path;
enum class PathOp;
class Bitmap;
class Pixmap;
class ImageInfo;
class DrawCmdList;
class RoundRect;
class Data;
class Image;
class ColorSpace;
class Picture;
struct BitmapFormat;
class ImageFilter;
class PointF;
class Surface;
} // namespace Drawing
} // namespace OHOS::Rosen
namespace OHOS::Ace {
using RSCanvas = Rosen::Drawing::Canvas;
using RSRect = Rosen::Drawing::RectF;
using RSNode = Rosen::RSNode;
using RSClipOp = Rosen::Drawing::ClipOp;
using RSPen = Rosen::Drawing::Pen;
using RSBrush = Rosen::Drawing::Brush;
using RSPath = Rosen::Drawing::Path;
using RSPathOp = Rosen::Drawing::PathOp;
using RSBitmap = Rosen::Drawing::Bitmap;
using RSPixmap = Rosen::Drawing::Pixmap;
using RSImageInfo = Rosen::Drawing::ImageInfo;
using RSDrawCmdList = Rosen::Drawing::DrawCmdList;
using RSRoundRect = Rosen::Drawing::RoundRect;
using RSPoint = Rosen::Drawing::PointF;
using RSData = Rosen::Drawing::Data;
using RSImage = Rosen::Drawing::Image;
using RSColorSpace = Rosen::Drawing::ColorSpace;
using RSPicture = Rosen::Drawing::Picture;
using RSBitmapFormat = Rosen::Drawing::BitmapFormat;
using RSImageFilter = Rosen::Drawing::ImageFilter;
using RSRecordingPath = Rosen::Drawing::Path;
using RSSurface = Rosen::Drawing::Surface;
} // namespace OHOS::Ace
#else
#include "core/components_ng/render/drawing_mock.h"
#endif
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_FORWARD_H
