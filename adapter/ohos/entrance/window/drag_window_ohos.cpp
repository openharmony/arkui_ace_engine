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

#include "drag_window_ohos.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph_txt.h"
#else
#include "rosen_text/typography.h"
#endif

#include "include/core/SkCanvas.h"
#include "include/core/SkSamplingOptions.h"

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/image/pixel_map.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/components/text/render_text.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Rosen;

namespace OHOS::Ace {
#ifdef ENABLE_ROSEN_BACKEND
namespace {
// Adapt text dragging background shadows to expand the width of dargwindow
const Dimension Window_EXTERN = 10.0_vp;

RSAlphaType AlphaTypeToAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return RSAlphaType::ALPHATYPE_OPAQUE;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return RSAlphaType::ALPHATYPE_PREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return RSAlphaType::ALPHATYPE_UNPREMUL;
        default:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
    }
}

RSColorType PixelFormatToColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return RSColorType::COLORTYPE_RGB_565;
        case PixelFormat::RGBA_8888:
            return RSColorType::COLORTYPE_RGBA_8888;
        case PixelFormat::BGRA_8888:
            return RSColorType::COLORTYPE_BGRA_8888;
        case PixelFormat::ALPHA_8:
            return RSColorType::COLORTYPE_ALPHA_8;
        case PixelFormat::RGBA_F16:
            return RSColorType::COLORTYPE_RGBA_F16;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return RSColorType::COLORTYPE_UNKNOWN;
    }
}

RSBitmapFormat MakeBitmapFormatFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    RSBitmapFormat format;
    format.colorType = PixelFormatToColorType(pixmap);
    format.alphaType = AlphaTypeToAlphaType(pixmap);
    return format;
}

void DrawDrawingImage(RSCanvas* canvas, const std::shared_ptr<RSImage>& drawingImage, int32_t width, int32_t height)
{
    CHECK_NULL_VOID(drawingImage);
    RSBrush brush;
    auto colorSpace = RSRecordingColorSpace::CreateRefImage(*drawingImage);
    brush.SetColor(brush.GetColor4f(), colorSpace);
    auto srcRect = RSRect(0, 0, drawingImage->GetWidth(), drawingImage->GetHeight());
    auto dstRect = RSRect(0, 0, width, height);
    RSSamplingOptions sampling;
    canvas->AttachBrush(brush);
    canvas->DrawImageRect(
        *drawingImage, srcRect, dstRect, sampling, Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    canvas->DetachBrush();
}

void DrawPixelMapInner(RSCanvas* canvas, const RefPtr<PixelMap>& pixmap, int32_t width, int32_t height)
{
    // Step1: Create Bitmap
    auto bitmapFormat = MakeBitmapFormatFromPixelMap(pixmap);
    auto bitmap = std::make_shared<RSBitmap>();
    bitmap->Build(pixmap->GetWidth(), pixmap->GetHeight(), bitmapFormat);
    bitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixmap->GetPixels())));

    // Step2: Create Image and draw it
    auto image = std::make_shared<RSImage>();
    image->BuildFromBitmap(*bitmap);
    DrawDrawingImage(canvas, image, width, height);
}
} // namespace
#endif

RefPtr<DragWindow> DragWindow::CreateDragWindow(
    const std::string& windowName, int32_t x, int32_t y, uint32_t width, uint32_t height)
{
    return CreateDragWindow({ windowName, x, y, width, height });
}

RefPtr<DragWindow> DragWindow::CreateDragWindow(const DragWindowParams& params)
{
    int32_t halfWidth = static_cast<int32_t>(params.width) / 2;
    int32_t halfHeight = static_cast<int32_t>(params.height) / 2;

    OHOS::sptr<OHOS::Rosen::WindowOption> option = new OHOS::Rosen::WindowOption();
    option->SetWindowRect({ params.x - halfWidth, params.y - halfHeight, params.width, params.height });
    option->SetHitOffset(halfWidth, halfHeight);
    if (params.parentWindowId == -1) {
        option->SetWindowType(OHOS::Rosen::WindowType::WINDOW_TYPE_DRAGGING_EFFECT);
    } else {
        option->SetParentId(params.parentWindowId);
        option->SetWindowType(OHOS::Rosen::WindowType::WINDOW_TYPE_APP_SUB_WINDOW);
    }
    option->SetWindowMode(OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING);
    option->SetFocusable(false);
    OHOS::sptr<OHOS::Rosen::Window> dragWindow = OHOS::Rosen::Window::Create(params.windowName, option);
    CHECK_NULL_RETURN(dragWindow, nullptr);

    OHOS::Rosen::WMError ret = dragWindow->MoveTo(params.x - halfWidth, params.y - halfHeight, true);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow MoveTo, drag window move failed, ret: %d", ret);
        return nullptr;
    }

    ret = dragWindow->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow CreateDragWindow, drag window Show() failed, ret: %d", ret);
        return nullptr;
    }

    auto window = AceType::MakeRefPtr<DragWindowOhos>(dragWindow);
    window->SetSize(params.width, params.height);
    return window;
}

RefPtr<DragWindow> DragWindow::CreateTextDragWindow(
    const std::string& windowName, int32_t x, int32_t y, uint32_t width, uint32_t height)
{
    int32_t halfWidth = static_cast<int32_t>(width + Window_EXTERN.ConvertToPx() * 2) / 2;
    int32_t halfHeight = static_cast<int32_t>(height + Window_EXTERN.ConvertToPx() * 2) / 2;

    OHOS::sptr<OHOS::Rosen::WindowOption> option = new OHOS::Rosen::WindowOption();
    option->SetWindowRect({ x - Window_EXTERN.ConvertToPx(), y - Window_EXTERN.ConvertToPx(),
        width + Window_EXTERN.ConvertToPx() * 2, height + Window_EXTERN.ConvertToPx() * 2 });
    option->SetHitOffset(halfWidth, halfHeight);
    option->SetWindowType(OHOS::Rosen::WindowType::WINDOW_TYPE_DRAGGING_EFFECT);
    option->SetWindowMode(OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING);
    option->SetFocusable(false);
    OHOS::sptr<OHOS::Rosen::Window> dragWindow = OHOS::Rosen::Window::Create(windowName, option);
    CHECK_NULL_RETURN(dragWindow, nullptr);

    OHOS::Rosen::WMError ret = dragWindow->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow CreateTextDragWindow, drag window Show() failed, ret: %d", ret);
    }

    auto window = AceType::MakeRefPtr<DragWindowOhos>(dragWindow);
    window->SetSize(width + Window_EXTERN.ConvertToPx() * 2, height + Window_EXTERN.ConvertToPx() * 2);
    return window;
}

void DragWindowOhos::MoveTo(int32_t x, int32_t y) const
{
    CHECK_NULL_VOID(dragWindow_);

    OHOS::Rosen::WMError ret = dragWindow_->MoveTo(x + offsetX_ - width_ / 2, y + offsetY_ - height_ / 2, true);
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow MoveTo, drag window move failed, ret: %d", ret);
        return;
    }

    ret = dragWindow_->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow CreateDragWindow, drag window Show() failed, ret: %d", ret);
    }
}

void DragWindowOhos::TextDragWindowMove(double x, double y) const
{
    CHECK_NULL_VOID(dragWindow_);
    OHOS::Rosen::WMError ret =
        dragWindow_->MoveTo(x - Window_EXTERN.ConvertToPx() + offsetX_, y + offsetY_ - Window_EXTERN.ConvertToPx());
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow TextDragWindowMove, drag window move failed, ret: %d", ret);
        return;
    }

    ret = dragWindow_->Show();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow TextDragWindowMove, drag window Show() failed, ret: %d", ret);
    }
}

void DragWindowOhos::Destroy() const
{
    CHECK_NULL_VOID(dragWindow_);

    OHOS::Rosen::WMError ret = dragWindow_->Destroy();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DRAG, "DragWindow Destroy, drag window destroy failed, ret: %d", ret);
    }
}

void DragWindowOhos::DrawFrameNode(const RefPtr<NG::FrameNode>& rootNode)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(rootNode);

    auto surfaceNode = dragWindow_->GetSurfaceNode();
    rsUiDirector_ = Rosen::RSUIDirector::Create();
    rsUiDirector_->Init();
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
    rsUiDirector_->SetRSSurfaceNode(surfaceNode);

    auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(rootNode->GetRenderContext());
    CHECK_NULL_VOID(renderContext);
    auto rsNode = renderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);

    rsUiDirector_->SetRoot(rsNode->GetId());
    rsUiDirector_->SendMessages();
#endif
}

void DragWindowOhos::DrawPixelMap(const RefPtr<PixelMap>& pixelmap)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(pixelmap);
    auto surfaceNode = dragWindow_->GetSurfaceNode();
    rsUiDirector_ = Rosen::RSUIDirector::Create();
    rsUiDirector_->Init();
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
    rsUiDirector_->SetRSSurfaceNode(surfaceNode);
    rootNode_ = Rosen::RSRootNode::Create();
    rootNode_->SetBounds(0, 0, static_cast<float>(width_), static_cast<float>(height_));
    rootNode_->SetFrame(0, 0, static_cast<float>(width_), static_cast<float>(height_));
    rsUiDirector_->SetRoot(rootNode_->GetId());
    auto canvasNode = std::static_pointer_cast<Rosen::RSCanvasNode>(rootNode_);
    auto drawing = canvasNode->BeginRecording(width_, height_);
    DrawPixelMapInner(drawing, pixelmap, width_, height_);
    canvasNode->FinishRecording();
    rsUiDirector_->SendMessages();
#endif
}

void DragWindowOhos::DrawImage(void* drawingImage)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(drawingImage);
    auto* canvasImagePtr = reinterpret_cast<RefPtr<NG::CanvasImage>*>(drawingImage);
    CHECK_NULL_VOID(canvasImagePtr);
    RefPtr<NG::DrawingImage> canvasImage = AceType::DynamicCast<NG::DrawingImage>(*canvasImagePtr);
    CHECK_NULL_VOID(canvasImage);
    auto surfaceNode = dragWindow_->GetSurfaceNode();
    rsUiDirector_ = Rosen::RSUIDirector::Create();
    rsUiDirector_->Init();
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
    rsUiDirector_->SetRSSurfaceNode(surfaceNode);
    rootNode_ = Rosen::RSRootNode::Create();
    rootNode_->SetBounds(0, 0, static_cast<float>(width_), static_cast<float>(height_));
    rootNode_->SetFrame(0, 0, static_cast<float>(width_), static_cast<float>(height_));
    rsUiDirector_->SetRoot(rootNode_->GetId());
    auto canvasNode = std::static_pointer_cast<Rosen::RSCanvasNode>(rootNode_);
    auto drawing = canvasNode->BeginRecording(width_, height_);
    auto rsImage = canvasImage->GetImage();
    DrawDrawingImage(drawing, rsImage, width_, height_);
    canvasNode->FinishRecording();
    rsUiDirector_->SendMessages();
#endif
}

#ifndef USE_GRAPHIC_TEXT_GINE
void DragWindowOhos::DrawText(
    std::shared_ptr<txt::Paragraph> paragraph, const Offset& offset, const RefPtr<RenderText>& renderText)
#else
void DragWindowOhos::DrawText(
    std::shared_ptr<Rosen::Typography> paragraph, const Offset& offset, const RefPtr<RenderText>& renderText)
#endif
{
#ifndef NG_BUILD
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(paragraph);
    auto surfaceNode = dragWindow_->GetSurfaceNode();
    rsUiDirector_ = Rosen::RSUIDirector::Create();
    rsUiDirector_->Init();
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
    rsUiDirector_->SetRSSurfaceNode(surfaceNode);
    rootNode_ = Rosen::RSRootNode::Create();
    rootNode_->SetBounds(0, 0, static_cast<float>(width_), static_cast<float>(height_));
    rootNode_->SetFrame(0, 0, static_cast<float>(width_), static_cast<float>(height_));
    rsUiDirector_->SetRoot(rootNode_->GetId());
    auto canvasNode = std::static_pointer_cast<Rosen::RSCanvasNode>(rootNode_);
    RSRecordingPath path;
    if (renderText->GetStartOffset().GetY() == renderText->GetEndOffset().GetY()) {
        path.MoveTo(renderText->GetStartOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetEndOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetEndOffset().GetY() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetEndOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetEndOffset().GetY() - renderText->GetSelectHeight() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetStartOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetSelectHeight() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetStartOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetGlobalOffset().GetY());
    } else {
        path.MoveTo(renderText->GetStartOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetStartOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetSelectHeight() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetPaintRect().Right() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetSelectHeight() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetPaintRect().Right() - renderText->GetGlobalOffset().GetX(),
            renderText->GetEndOffset().GetY() - renderText->GetSelectHeight() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetEndOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetEndOffset().GetY() - renderText->GetSelectHeight() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetEndOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetEndOffset().GetY() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetPaintRect().Left() - renderText->GetGlobalOffset().GetX(),
            renderText->GetEndOffset().GetY() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetPaintRect().Left() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetGlobalOffset().GetY());
        path.LineTo(renderText->GetStartOffset().GetX() - renderText->GetGlobalOffset().GetX(),
            renderText->GetStartOffset().GetY() - renderText->GetGlobalOffset().GetY());
    }
    rootNode_->SetClipToBounds(true);
    rootNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(path));
    auto recordingCanvas = canvasNode->BeginRecording(width_, height_);
    paragraph->Paint(recordingCanvas, 0, 0);
    canvasNode->FinishRecording();
    rsUiDirector_->SendMessages();
#endif
#endif
}

void DragWindowOhos::DrawTextNG(const RefPtr<NG::Paragraph>& paragraph, const RefPtr<NG::TextPattern>& textPattern)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_VOID(paragraph);
    auto surfaceNode = dragWindow_->GetSurfaceNode();
    rsUiDirector_ = Rosen::RSUIDirector::Create();
    CHECK_NULL_VOID(rsUiDirector_);
    rsUiDirector_->Init();
    auto transactionProxy = Rosen::RSTransactionProxy::GetInstance();
    if (transactionProxy != nullptr) {
        transactionProxy->FlushImplicitTransaction();
    }
    rsUiDirector_->SetRSSurfaceNode(surfaceNode);

    rootNode_ = Rosen::RSRootNode::Create();
    CHECK_NULL_VOID(rootNode_);
    rootNode_->SetBounds(Window_EXTERN.ConvertToPx(), Window_EXTERN.ConvertToPx(), static_cast<float>(width_),
        static_cast<float>(height_));
    rootNode_->SetFrame(Window_EXTERN.ConvertToPx(), Window_EXTERN.ConvertToPx(), static_cast<float>(width_),
        static_cast<float>(height_));
    rsUiDirector_->SetRoot(rootNode_->GetId());
    auto canvasNode = std::static_pointer_cast<Rosen::RSCanvasNode>(rootNode_);
    CHECK_NULL_VOID(canvasNode);
    Offset globalOffset;
    textPattern->GetGlobalOffset(globalOffset);
    RSRecordingPath path;
    if (textPattern->GetStartOffset().GetY() == textPattern->GetEndOffset().GetY()) {
        path.MoveTo(textPattern->GetStartOffset().GetX() - globalOffset.GetX(),
            textPattern->GetStartOffset().GetY() - globalOffset.GetY());
        path.LineTo(textPattern->GetEndOffset().GetX() - globalOffset.GetX(),
            textPattern->GetEndOffset().GetY() - globalOffset.GetY());
        path.LineTo(textPattern->GetEndOffset().GetX() - globalOffset.GetX(),
            textPattern->GetEndOffset().GetY() + textPattern->GetSelectHeight() - globalOffset.GetY());
        path.LineTo(textPattern->GetStartOffset().GetX() - globalOffset.GetX(),
            textPattern->GetStartOffset().GetY() + textPattern->GetSelectHeight() - globalOffset.GetY());
        path.LineTo(textPattern->GetStartOffset().GetX() - globalOffset.GetX(),
            textPattern->GetStartOffset().GetY() - globalOffset.GetY());
    } else {
        path.MoveTo(textPattern->GetStartOffset().GetX() - globalOffset.GetX(),
            textPattern->GetStartOffset().GetY() - globalOffset.GetY());
        path.LineTo(
            textPattern->GetTextContentRect().Width(), textPattern->GetStartOffset().GetY() - globalOffset.GetY());
        path.LineTo(
            textPattern->GetTextContentRect().Width(), textPattern->GetEndOffset().GetY() - globalOffset.GetY());
        path.LineTo(textPattern->GetEndOffset().GetX() - globalOffset.GetX(),
            textPattern->GetEndOffset().GetY() - globalOffset.GetY());
        path.LineTo(textPattern->GetEndOffset().GetX() - globalOffset.GetX(),
            textPattern->GetEndOffset().GetY() + textPattern->GetSelectHeight() - globalOffset.GetY());
        path.LineTo(textPattern->GetTextContentRect().GetX(),
            textPattern->GetEndOffset().GetY() + textPattern->GetSelectHeight() - globalOffset.GetY());
        path.LineTo(textPattern->GetTextContentRect().GetX(),
            textPattern->GetStartOffset().GetY() + textPattern->GetSelectHeight() - globalOffset.GetY());
        path.LineTo(textPattern->GetStartOffset().GetX() - globalOffset.GetX(),
            textPattern->GetStartOffset().GetY() + textPattern->GetSelectHeight() - globalOffset.GetY());
        path.LineTo(textPattern->GetStartOffset().GetX() - globalOffset.GetX(),
            textPattern->GetStartOffset().GetY() - globalOffset.GetY());
    }
    rootNode_->SetClipToBounds(true);
    rootNode_->SetClipBounds(Rosen::RSPath::CreateRSPath(path));
    auto recordingCanvas = canvasNode->BeginRecording(width_, height_);
    paragraph->Paint(*recordingCanvas, textPattern->GetTextContentRect().GetX(),
        textPattern->GetTextContentRect().GetY() - std::min(textPattern->GetBaselineOffset(), 0.0f));
    canvasNode->FinishRecording();
    rsUiDirector_->SendMessages();

    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
#endif
}
} // namespace OHOS::Ace
