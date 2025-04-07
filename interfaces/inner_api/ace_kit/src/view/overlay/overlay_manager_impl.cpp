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

#include "interfaces/inner_api/ace_kit/src/view/overlay/overlay_manager_impl.h"

#include "ui/base/utils/utils.h"
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Kit {

OverlayManagerImpl::OverlayManagerImpl(NG::PipelineContext* context)
{
    if (context) {
        overlayManager_ = AceType::RawPtr(context->GetOverlayManager());
    }
}

OverlayManagerImpl::~OverlayManagerImpl()
{
    Reset();
}

void OverlayManagerImpl::Reset()
{
    overlayManager_ = nullptr;
}

void OverlayManagerImpl::CloseDialog(RefPtr<FrameNode>& dialogNode)
{
    CHECK_NULL_VOID(overlayManager_);
    CHECK_NULL_VOID(dialogNode);
    auto frameNode = AceType::DynamicCast<FrameNodeImpl>(dialogNode);
    CHECK_NULL_VOID(frameNode);
    auto aceNode = frameNode->GetAceNode();
    CHECK_NULL_VOID(aceNode);
    overlayManager_->CloseDialog(aceNode);
}

void OverlayManagerImpl::ShowMenu(const int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode>& menu)
{
    CHECK_NULL_VOID(overlayManager_);
    CHECK_NULL_VOID(menu);
    auto menuNodeImpl = AceType::DynamicCast<FrameNodeImpl>(menu);
    CHECK_NULL_VOID(menuNodeImpl);
    auto aceMenuNode = menuNodeImpl->MoveOwnershipAndGetAceNode();
    CHECK_NULL_VOID(aceMenuNode);
    overlayManager_->ShowMenu(targetId, offset, aceMenuNode);
}

NG::SafeAreaInsets OverlayManagerImpl::GetSafeAreaInsets(const RefPtr<FrameNode>& frameNode, bool useCurrentWindow)
{
    CHECK_NULL_RETURN(overlayManager_, {});
    CHECK_NULL_RETURN(frameNode, {});
    auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(frameNode);
    CHECK_NULL_RETURN(frameNodeImpl, {});
    auto aceFrameNode = frameNodeImpl->GetAceNode();
    CHECK_NULL_RETURN(aceFrameNode, {});
    return overlayManager_->GetSafeAreaInsets(aceFrameNode, useCurrentWindow);
}

} // OHOS::Ace::Kit
