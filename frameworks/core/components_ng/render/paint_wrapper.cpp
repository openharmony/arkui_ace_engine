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

#include "core/components_ng/render/paint_wrapper.h"

#include "ui/base/utils/utils.h"
#include "ui/view/draw/node_paint_method.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

PaintWrapper::PaintWrapper(WeakPtr<RenderContext> renderContext, RefPtr<GeometryNode> geometryNode,
    RefPtr<PaintProperty> paintProperty, RefPtr<ExtensionHandler> handler)
    : renderContext_(std::move(renderContext)), geometryNode_(std::move(geometryNode)),
      paintProperty_(std::move(paintProperty)), extensionHandler_(std::move(handler))
{}

PaintWrapper::~PaintWrapper() = default;

void PaintWrapper::SetNodePaintMethod(const RefPtr<NodePaintMethod>& nodePaintImpl)
{
    nodePaintImpl_ = nodePaintImpl;
    CHECK_NULL_VOID(nodePaintImpl_);
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    auto contentModifier = AceType::DynamicCast<ContentModifier>(nodePaintImpl_->GetContentModifier(this));
    if (contentModifier) {
        if (extensionHandler_) {
            contentModifier->SetExtensionHandler(extensionHandler_);
        }
        renderContext->FlushContentModifier(contentModifier);
    }
    auto overlayModifier = AceType::DynamicCast<OverlayModifier>(nodePaintImpl_->GetOverlayModifier(this));
    if (overlayModifier) {
        if (extensionHandler_) {
            overlayModifier->SetExtensionHandler(extensionHandler_);
        }
        renderContext->FlushOverlayModifier(overlayModifier);
    }
    auto foregroundModifier = AceType::DynamicCast<ForegroundModifier>(nodePaintImpl_->GetForegroundModifier(this));
    if (foregroundModifier) {
        if (extensionHandler_) {
            foregroundModifier->SetExtensionHandler(extensionHandler_);
        }
        renderContext->FlushForegroundModifier(foregroundModifier);
    }
}

void PaintWrapper::SetKitNodePaintMethod(const RefPtr<Kit::NodePaintMethod>& nodePaintMethod)
{
    nodePaintMethod_ = nodePaintMethod;
    auto modifier = nodePaintMethod_->GetContentModifier();
    CHECK_NULL_VOID(modifier);
    modifier->InitAdapter();
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    renderContext->FlushKitContentModifier(modifier);
}

void PaintWrapper::FlushOverlayModifier()
{
    CHECK_NULL_VOID(nodePaintImpl_);
    auto overlayModifier = nodePaintImpl_->GetOverlayModifier(this);
    CHECK_NULL_VOID(overlayModifier);
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    renderContext->FlushOverlayModifier(overlayModifier);
}

void PaintWrapper::FlushContentModifier()
{
    CHECK_NULL_VOID(nodePaintImpl_);
    auto contentModifier = nodePaintImpl_->GetContentModifier(this);
    CHECK_NULL_VOID(contentModifier);
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    renderContext->FlushContentModifier(contentModifier);
}

void PaintWrapper::FlushRender()
{
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);

    auto contentModifier =
        DynamicCast<ContentModifier>(nodePaintImpl_ ? nodePaintImpl_->GetContentModifier(this) : nullptr);
    if (contentModifier) {
        nodePaintImpl_->UpdateContentModifier(this);
        if (extensionHandler_) {
            extensionHandler_->InvalidateRender();
        }
    }

    auto overlayModifier = nodePaintImpl_ ? nodePaintImpl_->GetOverlayModifier(this) : nullptr;
    if (overlayModifier) {
        nodePaintImpl_->UpdateOverlayModifier(this);
        if (extensionHandler_) {
            extensionHandler_->OverlayRender();
        }
    }

    auto foregroundModifier = nodePaintImpl_ ? nodePaintImpl_->GetForegroundModifier(this) : nullptr;
    if (foregroundModifier) {
        nodePaintImpl_->UpdateForegroundModifier(this);
        if (extensionHandler_) {
            extensionHandler_->ForegroundRender();
        }
    }

    renderContext->StartRecording();

    auto contentDraw = nodePaintImpl_ ? nodePaintImpl_->GetContentDrawFunction(this) : nullptr;
    auto foregroundDraw = nodePaintImpl_ ? nodePaintImpl_->GetForegroundDrawFunction(this) : nullptr;
    auto overlayDraw = nodePaintImpl_ ? nodePaintImpl_->GetOverlayDrawFunction(this) : nullptr;

    if (extensionHandler_) {
        auto layoutSize = GetGeometryNode()->GetFrameSize();
        auto width = layoutSize.Width();
        auto height = layoutSize.Height();
        if (!contentModifier) {
            if (contentDraw) {
                extensionHandler_->SetInnerDrawImpl([contentDraw = std::move(contentDraw)](
                                                        DrawingContext& context) { contentDraw(context.canvas); });
            }
            renderContext->FlushContentDrawFunction(
                [extensionHandler = RawPtr(extensionHandler_), width, height](RSCanvas& canvas) {
                    DrawingContext context = { canvas, width, height };
                    extensionHandler->Draw(context);
                });
        }
        if (!foregroundModifier) {
            if (foregroundDraw) {
                extensionHandler_->SetInnerForegroundDrawImpl(
                    [foregroundDraw = std::move(foregroundDraw)](
                        DrawingContext& context) { foregroundDraw(context.canvas); });
            }
            renderContext->FlushForegroundDrawFunction(
                [extensionHandler = RawPtr(extensionHandler_), width, height](RSCanvas& canvas) {
                    DrawingContext context = { canvas, width, height };
                    extensionHandler->ForegroundDraw(context);
                });
        }
        if (!overlayModifier) {
            if (overlayDraw) {
                extensionHandler_->SetInnerOverlayDrawImpl(
                    [overlayDraw = std::move(overlayDraw)](
                        DrawingContext& context) { overlayDraw(context.canvas); });
            }
            renderContext->FlushOverlayDrawFunction(
                [extensionHandler = RawPtr(extensionHandler_), width, height](RSCanvas& canvas) {
                    DrawingContext context = { canvas, width, height };
                    extensionHandler->OverlayDraw(context);
                });
        }
    } else {
        if (contentDraw && !contentModifier) {
            renderContext->FlushContentDrawFunction(std::move(contentDraw));
        }
        if (foregroundDraw && !foregroundModifier) {
            renderContext->FlushForegroundDrawFunction(std::move(foregroundDraw));
        }
        if (overlayDraw && !overlayModifier) {
            renderContext->FlushOverlayDrawFunction(std::move(overlayDraw));
        }
    }

    if (renderContext->GetAccessibilityFocus().value_or(false)) {
        renderContext->PaintAccessibilityFocus();
    }

    renderContext->StopRecordingIfNeeded();
}
} // namespace OHOS::Ace::NG
