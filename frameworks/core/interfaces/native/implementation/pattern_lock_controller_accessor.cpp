/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/pattern_lock_controller_accessor_peer_impl.h"
#include "core/components_v2/pattern_lock/pattern_lock_controller.h"
namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<V2::PatternLockChallengeResult>& dst, const Ark_PatternLockChallengeResult& src)
{
    switch (src) {
        case ARK_PATTERN_LOCK_CHALLENGE_RESULT_CORRECT: dst = V2::PatternLockChallengeResult::CORRECT; break;
        case ARK_PATTERN_LOCK_CHALLENGE_RESULT_WRONG: dst = V2::PatternLockChallengeResult::WRONG; break;
        default: LOGE("PatternLockControllerAccessor::Unexpected enum value in "
            "Ark_PatternLockChallengeResult: %{public}d", src);
    }
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace PatternLockControllerAccessor {
void DestroyPeerImpl(Ark_PatternLockController peer)
{
    auto peerImpl = reinterpret_cast<PatternLockControllerPeerImpl *>(peer);
    if (peerImpl) {
        if (peerImpl->handler) {
            peerImpl->handler = nullptr;
        }
        delete peerImpl;
    }
}
Ark_PatternLockController CtorImpl()
{
    return reinterpret_cast<PatternLockControllerPeer *>(new PatternLockControllerPeerImpl());
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ResetImpl(Ark_PatternLockController peer)
{
    auto peerImpl = reinterpret_cast<PatternLockControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    peerImpl->handler->Reset();
}
void SetChallengeResultImpl(Ark_PatternLockController peer,
                            Ark_PatternLockChallengeResult result)
{
    auto peerImpl = reinterpret_cast<PatternLockControllerPeerImpl *>(peer);
    CHECK_NULL_VOID(peerImpl);
    auto optResult = Converter::OptConvert<V2::PatternLockChallengeResult>(result);
    if (optResult.has_value()) {
        peerImpl->handler->SetChallengeResult(optResult.value());
    }
}
} // PatternLockControllerAccessor
const GENERATED_ArkUIPatternLockControllerAccessor* GetPatternLockControllerAccessor()
{
    static const GENERATED_ArkUIPatternLockControllerAccessor PatternLockControllerAccessorImpl {
        PatternLockControllerAccessor::DestroyPeerImpl,
        PatternLockControllerAccessor::CtorImpl,
        PatternLockControllerAccessor::GetFinalizerImpl,
        PatternLockControllerAccessor::ResetImpl,
        PatternLockControllerAccessor::SetChallengeResultImpl,
    };
    return &PatternLockControllerAccessorImpl;
}

struct PatternLockControllerPeer {
    virtual ~PatternLockControllerPeer() = default;
};
}
