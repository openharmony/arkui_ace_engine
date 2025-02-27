/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_2D_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_2D_ACCESSOR_PEER_IMPL_H

#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "canvas_path_peer_impl.h"
#include "canvas_renderer_peer_impl.h"
#include "matrix2d_peer_impl.h"

struct Path2DPeer : public OHOS::Ace::NG::GeneratedModifier::CanvasPathPeerImpl {
    Path2DPeer() = default;
    ~Path2DPeer() override = default;

    void SetOptions()
    {
        auto path2d = OHOS::Ace::NG::GeneratedModifier::CanvasRendererPeerImpl::MakePath2D();
        SetCanvasPath2d(path2d);
    }
    void Path2DAddPath(Path2DPeer* path2d, const std::optional<Matrix2DPeer*>& optMatrix)
    {
        // one parameter
        CHECK_NULL_VOID(path2d);
        auto canvasPath2D = path2d->GetCanvasPath2d();
        path2d_->AddPath(canvasPath2D);
        SetPathSize();
        // two parameters
        if (OHOS::Ace::Container::GreatOrEqualAPITargetVersion(OHOS::Ace::PlatformVersion::VERSION_TEN)) {
            auto matrix2d = optMatrix.value_or(nullptr);
            if (matrix2d) {
                path2d_->SetTransform(matrix2d->GetScaleX(), matrix2d->GetRotateX(), matrix2d->GetRotateY(),
                    matrix2d->GetScaleY(), matrix2d->GetTranslateX(), matrix2d->GetTranslateY());
                SetPathSize();
            }
        }
    }
};

namespace OHOS::Ace::NG::GeneratedModifier {
    using Path2DPeerImpl = ::Path2DPeer;
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_PATH_2D_ACCESSOR_PEER_IMPL_H