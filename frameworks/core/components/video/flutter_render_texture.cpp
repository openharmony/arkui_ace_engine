/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/display/render_display.h"
#include "core/components/video/flutter_render_texture.h"

#include "flutter/fml/memory/ref_counted.h"
#include "flutter/lib/ui/painting/canvas.h"
#include "flutter/lib/ui/painting/picture_recorder.h"
#include "flutter/lib/ui/ui_dart_state.h"

#include "base/log/dump_log.h"

namespace OHOS::Ace {

using namespace Flutter;

RefPtr<RenderNode> RenderTexture::Create()
{
    return AceType::MakeRefPtr<FlutterRenderTexture>();
}

void FlutterRenderTexture::Paint(RenderContext& context, const Offset& offset)
{
    const Size& layout = GetLayoutSize();

    layer_->SetClip(0.0, layout.Width(), 0.0, layout.Height(), Flutter::Clip::NONE);
    AddBackgroundLayer();

    if (textureId_ != INVALID_TEXTURE) {
        AddTextureLayer();
    }

    RenderNode::Paint(context, offset);
}

RenderLayer FlutterRenderTexture::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<ClipLayer>(0.0, 0.0, 0.0, 0.0, Flutter::Clip::NONE);
    }

    return AceType::RawPtr(layer_);
}

void FlutterRenderTexture::AddTextureLayer()
{
    if (!textureLayer_) {
        textureLayer_ =
            AceType::MakeRefPtr<TextureLayer>(textureId_, false, drawSize_.Width(), drawSize_.Height(), opacity_);
    } else {
        textureLayer_->Update(textureId_, false, drawSize_.Width(), drawSize_.Height(), opacity_);
    }

    textureLayer_->SetOffset(alignmentX_, alignmentY_);

    layer_->AddChildren(textureLayer_);
}

void FlutterRenderTexture::AddBackgroundLayer()
{
    if (!backgroundLayer_) {
        backgroundLayer_ = AceType::MakeRefPtr<PictureLayer>();
    }

    if (needDrawBackground_) {
        DrawBackground();
    }

    if (imageFit_ != ImageFit::FILL) {
        layer_->AddChildren(backgroundLayer_);
    }
}

void FlutterRenderTexture::DrawBackground()
{
    const Size& layout = GetLayoutSize();
    fml::RefPtr<flutter::PictureRecorder> recorder;
    fml::RefPtr<flutter::Canvas> canvas;
    flutter::Paint paint;
    flutter::PaintData paintData;

    recorder = flutter::PictureRecorder::Create();
    canvas = flutter::Canvas::Create(recorder.get(), 0.0, 0.0, layout.Width(), layout.Height());
    paint.paint()->setColor(SK_ColorBLACK);
    paint.paint()->setAlpha(opacity_);
    canvas->drawRect(0.0, 0.0, layout.Width(), layout.Height(), paint, paintData);
    backgroundLayer_->SetPicture(recorder->endRecording());

    needDrawBackground_ = false;
}

void FlutterRenderTexture::PerformLayout()
{
    RenderTexture::PerformLayout();
    needDrawBackground_ = true;
}

void FlutterRenderTexture::UpdateOpacity(uint8_t opacity)
{
    if (!SupportOpacity()) {
        return;
    }
    if (opacity_ != opacity) {
        RenderNode::UpdateOpacity(opacity);
        needDrawBackground_ = true;
        auto displayChild = AceType::DynamicCast<RenderDisplay>(GetFirstChild());
        if (displayChild) {
            displayChild->UpdateOpacity(opacity);
        }
    }
}

void FlutterRenderTexture::DumpTree(int32_t depth)
{
    auto children = GetChildren();

    if (DumpLog::GetInstance().GetDumpFile() > 0) {
        DumpLog::GetInstance().AddDesc("textureId:", textureId_);
        DumpLog::GetInstance().AddDesc("drawSize:", "width = ", drawSize_.Width(), " height = ", drawSize_.Height());
        DumpLog::GetInstance().AddDesc("sourceSize:", "width = ", drawSize_.Width(), " height = ", drawSize_.Height());
        DumpLog::GetInstance().AddDesc("alignmentX:", alignmentX_);
        DumpLog::GetInstance().AddDesc("alignmentY:", alignmentY_);
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), children.size());
    }

    for (const auto& item : children) {
        item->DumpTree(depth + 1);
    }
}

} // namespace OHOS::Ace
