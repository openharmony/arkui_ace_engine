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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H

#include "test/mock/core/rosen/testing_image_blur_type.h"
#include "test/mock/core/rosen/testing_bitmap.h"
#include "test/mock/core/rosen/testing_brush.h"
#include "test/mock/core/rosen/testing_camera.h"
#include "test/mock/core/rosen/testing_canvas.h"
#include "test/mock/core/rosen/testing_color.h"
#include "test/mock/core/rosen/testing_color_filter.h"
#include "test/mock/core/rosen/testing_color_matrix.h"
#include "test/mock/core/rosen/testing_color_space.h"
#include "test/mock/core/rosen/testing_data.h"
#include "test/mock/core/rosen/testing_draw_cmd_list.h"
#include "test/mock/core/rosen/testing_filter.h"
#include "test/mock/core/rosen/testing_font.h"
#include "test/mock/core/rosen/testing_font_collection.h"
#include "test/mock/core/rosen/testing_image.h"
#include "test/mock/core/rosen/testing_image_filter.h"
#include "test/mock/core/rosen/testing_image_info.h"
#include "test/mock/core/rosen/testing_mask_filter.h"
#include "test/mock/core/rosen/testing_path.h"
#include "test/mock/core/rosen/testing_path_effect.h"
#include "test/mock/core/rosen/testing_pen.h"
#include "test/mock/core/rosen/testing_picture.h"
#include "test/mock/core/rosen/testing_point.h"
#include "test/mock/core/rosen/testing_point3.h"
#include "test/mock/core/rosen/testing_recording_canvas.h"
#include "test/mock/core/rosen/testing_recording_path_effect.h"
#include "test/mock/core/rosen/testing_sampling_options.h"
#include "test/mock/core/rosen/testing_save_layer_ops.h"
#include "test/mock/core/rosen/testing_scalar.h"
#include "test/mock/core/rosen/testing_shader_effect.h"
#include "test/mock/core/rosen/testing_shadowflags.h"
#include "test/mock/core/rosen/testing_surface.h"
#include "test/mock/core/rosen/testing_text_blob.h"
#include "test/mock/core/rosen/testing_text_style.h"
#include "test/mock/core/rosen/testing_typeface.h"
#include "test/mock/core/rosen/testing_typography.h"
#include "test/mock/core/rosen/testing_typography_create.h"
#include "test/mock/core/rosen/testing_typography_style.h"

namespace OHOS::Ace {
namespace RSDrawing = Testing;
using RSCanvas = Testing::TestingCanvas;
using RSPen = Testing::TestingPen;
using RSBrush = Testing::TestingBrush;
using RSPath = Testing::TestingPath;
using RSPathOp = Testing::TestingPathOp;
using RSImage = Testing::TestingImage;
using RSShaderEffect = Testing::TestingShaderEffect;
using RSPathDashStyle = Testing::TestingPathDashStyle;
using RSPathDirection = Testing::TestingPathDirection;
using RSPathEffect = Testing::TestingPathEffect;
using RSFilter = Testing::TestingFilter;
using RSColor = Testing::TestingColor;
using RSMaskFilter = Testing::TestingMaskFilter;
using RSImageFilter = Testing::TestingImageFilter;
using RSBlurType = Testing::BlurType;
using RSTileMode = Testing::TileMode;
using RSBitmap = Testing::TestingBitmap;
using RSBitmapFormat = Testing::BitmapFormat;
using RSColorType = Testing::ColorType;
using RSAlphaType = Testing::AlphaType;
using RSBlendMode = Testing::BlendMode;
using RSCamera3D = Testing::TestingCamera;
using RSMatrix = Testing::TestingMatrix;
using RSClipOp = Testing::ClipOp;
using RSPoint = Testing::TestingPoint;
using RSPoint3 = Testing::TestingPoint3;
using RSShadowFlags = Testing::TestingShadowFlags;
using RSRect = Testing::TestingRect;
using RSRoundRect = Testing::TestingRoundRect;
using RSTextDirection = Testing::TextDirection;
using RSTextAlign = Testing::TextAlign;
using RSWordBreakType = Testing::WordBreakType;
using RSEllipsisMode = Testing::EllipsisMode;
using RSTextStyle = Testing::TestingTextStyle;
using RSColorQuad = uint32_t;
using RSScalar = float;
using RSPathFillType = Testing::TestingPathFillType;
using RSParagraph = Testing::TestingTypography;
using RSTypographyProperties = Testing::TestingTypographyProperties;
using RSParagraphStyle = Testing::TestingTypographyStyle;
using RSParagraphBuilder = Testing::TestingTypographyCreate;
using RSFontCollection = Testing::TestingFontCollection;
using RSFontWeight = Testing::TestingFontWeight;
using RSTextDecoration = Testing::TestingTextDecoration;
using RSTextDecorationStyle = Testing::TestingTextDecorationStyle;
using RSSamplingOptions = Testing::TestingSamplingOptions;
using RSFontStyle = Testing::TestingFontStyle;
using RSTextBaseline = Testing::TestingTextBaseline;
using RSColorFilter = Testing::TestingColorFilter;
using RSColorMatrix = Testing::TestingColorMatrix;
using RSCubicResampler = Testing::TestingCubicResampler;
using RSColorSpace = Testing::TestingColorSpace;
using RSData = Testing::TestingData;
using RSRecordingCanvas = Testing::TestingRecordingCanvas;
using RSDrawCmdList = Testing::TestingDrawCmdList;
using RSFilterMode = Testing::FilterMode;
using RSMipmapMode = Testing::MipmapMode;
using RSRecordingPath = Testing::TestingPath;
using RSImageInfo = Testing::TestingImageInfo;
using RSRecordingPathEffect = Testing::TestingRecordingPathEffect;
using RSTypeface = Testing::TestingTypeface;
using RSTextBlob = Testing::TestingTextBlob;
using RSFont = Testing::TestingFont;
using RSTextEncoding = Testing::TestingTextEncoding;
using RSSaveLayerOps = Testing::TestingSaveLayerOps;
using RSSrcRectConstraint = Testing::SrcRectConstraint;
using RSImageBlurType = Testing::ImageBlurType;
using RSSurface = Testing::TestingSurface;
#ifdef USE_ROSEN_DRAWING
using RSRecordingColorFilter = Testing::TestingColorFilter;
using RSRecordingImageFilter = Testing::TestingImageFilter;
using RSRecordingShaderEffect = Testing::TestingShaderEffect;
using RSPicture = Testing::TestingPicture;
#endif
using RSTextRectHeightStyle = Testing::TestingTypographyProperties::TextRectHeightStyle;
using RSTextRectWidthStyle = Testing::TestingTypographyProperties::TextRectWidthStyle;
using RSTextRect = Testing::TestingTypographyProperties::TextRect;
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_DRAWING_MOCK_H
