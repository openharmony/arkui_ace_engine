/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "canvas_renderer_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {

void CanvasRendererPeerImpl::TriggerBeginPathImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerBeginPathImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->BeginPath();
}
void CanvasRendererPeerImpl::TriggerStroke0Impl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerStroke0Impl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Stroke();
}
void CanvasRendererPeerImpl::TriggerRestoreImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerRestoreImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Restore();
}
void CanvasRendererPeerImpl::TriggerSaveImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSaveImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Save();
}
void CanvasRendererPeerImpl::TriggerResetTransformImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerResetTransformImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->ResetTransform();
}
void CanvasRendererPeerImpl::TriggerSaveLayerImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerSaveLayerImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->SaveLayer();
}
void CanvasRendererPeerImpl::TriggerRestoreLayerImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerRestoreLayerImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->RestoreLayer();
}
void CanvasRendererPeerImpl::TriggerResetImpl()
{
    if (!pattern_) {
        LOGE("ARKOALA CanvasRendererPeerImpl::TriggerResetImpl pattern "
             "not bound to component.");
        return;
    }
    pattern_->Reset();
}

} // namespace OHOS::Ace::NG::GeneratedModifier
