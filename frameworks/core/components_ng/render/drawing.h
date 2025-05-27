/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef ACE_UNITTEST
#include "draw/canvas.h"
#include "draw/shadow.h"
#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"
#include "drawing/engine_adapter/skia_adapter/skia_path.h"
#include "image/image.h"
#include "rosen_text/symbol_animation_config.h"
#include "render_service_client/core/animation/rs_symbol_animation.h"

// win API conflict handle
#ifdef DIFFERENCE
#undef DIFFERENCE
#endif
#ifdef DrawText
#undef DrawText
#endif
#ifdef GetMessage
#undef GetMessage
#endif
#ifdef LoadImage
#undef LoadImage
#endif
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif
#ifdef DOUBLE_CLICK
#undef DOUBLE_CLICK
#endif

#include "pipeline/rs_recording_canvas.h"
#include "rosen_text/font_collection.h"
#include "rosen_text/typography.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_types.h"
#include "rosen_text/text_style.h"
#include "utils/camera3d.h"
#include "utils/canvas_utils.h"
#include "utils/point3.h"
#include "utils/scalar.h"
#include "utils/picture_recorder.h"

namespace OHOS::Ace {
namespace RSDrawing = Rosen::Drawing;
using RSCanvas = Rosen::Drawing::Canvas;
using RSImage = Rosen::Drawing::Image;
using RSBrush = Rosen::Drawing::Brush;
using RSFilter = Rosen::Drawing::Filter;
using RSColorFilter = Rosen::Drawing::ColorFilter;
using RSColorMatrix = Rosen::Drawing::ColorMatrix;
using RSPen = Rosen::Drawing::Pen;
using RSColor = Rosen::Drawing::Color;
using RSRect = Rosen::Drawing::Rect;
using RSPoint = Rosen::Drawing::Point;
using RSPoint3 = Rosen::Drawing::Point3;
using RSShadowFlags = Rosen::Drawing::ShadowFlags;
using RSBlendMode = Rosen::Drawing::BlendMode;
using RSSamplingOptions = Rosen::Drawing::SamplingOptions;
using RSRoundRect = Rosen::Drawing::RoundRect;
using RSPath = Rosen::Drawing::Path;
using RSPathOp = Rosen::Drawing::PathOp;
using RSBitmap = Rosen::Drawing::Bitmap;
using RSBitmapFormat = Rosen::Drawing::BitmapFormat;
using RSColorType = Rosen::Drawing::ColorType;
using RSAlphaType = Rosen::Drawing::AlphaType;
using RSScalar = Rosen::Drawing::scalar;
using RSClipOp = Rosen::Drawing::ClipOp;
using RSSkCanvas = Rosen::Drawing::SkiaCanvas;
using RSCanvasUtils = Rosen::Drawing::CanvasUtils;
using RSMatrix = Rosen::Drawing::Matrix;
using RSCamera3D = Rosen::Drawing::Camera3D;
using RSMaskFilter = Rosen::Drawing::MaskFilter;
using RSBlurType = Rosen::Drawing::BlurType;
using RSPathFillType = Rosen::Drawing::PathFillType;
using RSSkPath = Rosen::Drawing::SkiaPath;
using RSColorQuad = Rosen::Drawing::ColorQuad;
using RSColor4f = Rosen::Drawing::Color4f;
using RSShaderEffect = Rosen::Drawing::ShaderEffect;
using RSTileMode = Rosen::Drawing::TileMode;
using RSFont = Rosen::Drawing::Font;
using RSXform = Rosen::Drawing::RSXform;
using RSTextBlob = Rosen::Drawing::TextBlob;
using RSTextEncoding = Rosen::Drawing::TextEncoding;
using RSTypeface = Rosen::Drawing::Typeface;
using RSEncodedImageFormat = Rosen::Drawing::EncodedImageFormat;
using RSAutoCanvasRestore = Rosen::Drawing::AutoCanvasRestore;
using RSCubicResampler = Rosen::Drawing::CubicResampler;
using RSColorSpace = Rosen::Drawing::ColorSpace;
using RSData = Rosen::Drawing::Data;
using RSDrawCmdList = Rosen::Drawing::DrawCmdList;
using RSHybridRenderType = Rosen::Drawing::DrawCmdList::HybridRenderType;
using RSFilterMode = Rosen::Drawing::FilterMode;
using RSImageFilter = Rosen::Drawing::ImageFilter;
using RSMipmapMode = Rosen::Drawing::MipmapMode;
using RSPathDashStyle = Rosen::Drawing::PathDashStyle;
using RSPathDirection = Rosen::Drawing::PathDirection;
using RSPathEffect = Rosen::Drawing::PathEffect;
using RSPicture = Rosen::Drawing::Picture;
using RSRecordingCanvas = Rosen::ExtendRecordingCanvas;
using RSRecordingColorFilter = Rosen::Drawing::ColorFilter;
using RSRecordingColorSpace = Rosen::Drawing::ColorSpace;
using RSRecordingImageFilter = Rosen::Drawing::ImageFilter;
using RSRecordingMaskFilter = Rosen::Drawing::MaskFilter;
using RSRecordingPath = Rosen::Drawing::Path;
using RSRecordingPathEffect = Rosen::Drawing::PathEffect;
using RSRecordingRegion = Rosen::Drawing::Region;
using RSRecordingShaderEffect = Rosen::Drawing::ShaderEffect;
using RSSaveLayerOps = Rosen::Drawing::SaveLayerOps;
using RSSize = Rosen::Drawing::Size;
using RSSrcRectConstraint = Rosen::Drawing::SrcRectConstraint;
using RSPixmap = Rosen::Drawing::Pixmap;
using RSImageInfo = Rosen::Drawing::ImageInfo;
using RSRectI = Rosen::Drawing::RectI;
using RSImageBlurType = Rosen::Drawing::ImageBlurType;
using RSColorQuad = Rosen::Drawing::ColorQuad;
using RSShaderEffect = Rosen::Drawing::ShaderEffect;
using RSTileMode = Rosen::Drawing::TileMode;
using RSTextDirection = Rosen::TextDirection;
using RSTextAlign = Rosen::TextAlign;
using RSWordBreakType = Rosen::WordBreakType;
using RSTextBaseline = Rosen::TextBaseline;
using RSTextStyle = Rosen::TextStyle;
using RSTextDecoration = Rosen::TextDecoration;
using RSTextDecorationStyle = Rosen::TextDecorationStyle;
using RSFontWeight = Rosen::FontWeight;
using RSFontStyle = Rosen::FontStyle;
using RSPathEffect = Rosen::Drawing::PathEffect;
using RSPathDirection = Rosen::Drawing::PathDirection;
using RSPathDashStyle = Rosen::Drawing::PathDashStyle;
using RSParagraph = Rosen::Typography;
using RSParagraphBuilder = Rosen::TypographyCreate;
using RSFontCollection = Rosen::FontCollection;
using RSParagraphStyle = Rosen::TypographyStyle;
using RSTextRectHeightStyle = Rosen::TextRectHeightStyle;
using RSTextRectWidthStyle = Rosen::TextRectWidthStyle;
using RSTextRect = Rosen::TextRect;
using RSEllipsisMode = Rosen::EllipsisModal;
using RSSymbolAnimation = Rosen::RSSymbolAnimation;
using RSSymbolAnimationConfig = Rosen::TextEngine::SymbolAnimationConfig;
using RSPictureRecorder = Rosen::Drawing::PictureRecorder;
struct RSDataWrapper {
    std::shared_ptr<RSData> data;
};

inline void RSDataWrapperReleaseProc(const void*, void* context)
{
    RSDataWrapper* wrapper = reinterpret_cast<RSDataWrapper*>(context);
    delete wrapper;
}
} // namespace OHOS::Ace
#else
#include "core/components_ng/render/drawing_mock.h"
#endif
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_H
