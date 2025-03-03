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

#include "bridge/cj_frontend/frontend/cj_frontend_ng.h"

#include "bridge/cj_frontend/frontend/container_modal_cj_utils.h"

namespace OHOS::Ace::Framework {
void CJFrontendNG::InternalInitialize()
{
    LOGD("CJFrontendNG InternalInitialize begin.");
    ngRouter_ = MakeRefPtr<CJPageRouterNG>(WeakClaim(this));
    pageRouterManager_ = ngRouter_;
    pageRouterManager_->SetManifestParser(manifestParser_);
    // Register the node construction function with the container view
    std::function<RefPtr<NG::FrameNode>()> title = []() -> RefPtr<NG::FrameNode> {
        return OHOS::Ace::NG::BuildTitleNodeForCj();
    };
    std::function<RefPtr<NG::FrameNode>(
        const WeakPtr<NG::ContainerModalPatternEnhance>& weakPattern, const RefPtr<NG::FrameNode>& containerTitleRow)>
        controlButton = [](const WeakPtr<NG::ContainerModalPatternEnhance>& weakPattern,
                            const RefPtr<NG::FrameNode>& containerTitleRow) -> RefPtr<NG::FrameNode> {
        return OHOS::Ace::NG::AddControlButtonsForCj(weakPattern, containerTitleRow);
    };
    NG::ContainerModalView::RegistCustomBuilder(title, controlButton);
}

} // namespace OHOS::Ace::Framework
