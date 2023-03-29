/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/web/flutter_render_web.h"
namespace OHOS::Ace {

using namespace Flutter;

void FlutterRenderWeb::PerformLayout()
{
    RenderWeb::PerformLayout();
}

void FlutterRenderWeb::DumpTree(int32_t depth) {}

#if !defined(PREVIEW) and defined(OHOS_STANDARD_SYSTEM)
void FlutterRenderWeb::OnPaintFinish()
{
    if (!delegate_) {
        return;
    }

    position_ = GetGlobalOffset();
    if (!isCreateWebView_) {
        isCreateWebView_ = true;
        prePosition_ = position_;
        preDrawSize_ = drawSize_;
        return;
    }

    if (NearEqual(prePosition_.GetX(), position_.GetX()) &&
        NearEqual(prePosition_.GetY(), position_.GetY()) &&
        NearEqual(preDrawSize_.Width(), drawSize_.Width()) &&
        NearEqual(preDrawSize_.Height(), drawSize_.Height())) {
    } else {
        delegate_->SetBoundsOrResize(drawSize_, position_);
    }
    LOGI("FlutterRenderWeb::OnPaintFinish");
}

RenderLayer FlutterRenderWeb::GetRenderLayer()
{
    if (!isEnhanceSurface_) {
        return nullptr;
    }
    if (!holeLayer_) {
        holeLayer_ = AceType::MakeRefPtr<HoleLayer>(drawSize_.Width(), drawSize_.Height());
    } else {
        holeLayer_->SetSize(drawSize_.Width(), drawSize_.Height());
    }
    holeLayer_->SetOffset(GetCoordinatePoint().GetX(), GetCoordinatePoint().GetY());

    return AceType::RawPtr(holeLayer_);
}

void FlutterRenderWeb::Paint(RenderContext& context, const Offset& offset)
{
    if (!isEnhanceSurface_) {
        return;
    }
    LOGI("FlutterRenderWeb::Paint");
    if (drawSize_.Width() == Size::INFINITE_SIZE || drawSize_.Height() == Size::INFINITE_SIZE ||
        drawSize_.Width() == 0 || drawSize_.Height() == 0) {
        LOGE("Web drawSize height or width is invalid");
        return;
    }
    if (delegate_) {
        delegate_->SetBoundsOrResize(drawSize_, GetGlobalOffset());
    }
    RenderNode::Paint(context, offset);
}

#endif

} // namespace OHOS::Ace
