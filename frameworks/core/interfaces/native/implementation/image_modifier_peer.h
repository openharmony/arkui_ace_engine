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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_MODIFIER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_MODIFIER_PEER_IMPL_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace {
class ImageModifierPeerImpl : public AceType {
    DECLARE_ACE_TYPE(ImageModifierPeerImpl, AceType);

public:
    ImageModifierPeerImpl() = default;
    ~ImageModifierPeerImpl() override = default;
};
} // namespace OHOS::Ace
struct ImageModifierPeer : OHOS::Ace::ImageModifierPeerImpl {
    std::function<void(OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>)> apply;
    void* imageModifierAni;
protected:
    ImageModifierPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_IMAGE_MODIFIER_PEER_IMPL_H