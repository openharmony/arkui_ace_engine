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
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/progress_mask_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
inline std::optional<float> ConvertProgressMaskValue(const Ark_Number* value)
{
    CHECK_NULL_RETURN(value, std::nullopt);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(convValue);
    return convValue;
}

void SetProgressMaskValue(const RefPtr<ProgressMaskProperty>& property, const Ark_Number* value)
{
    auto convValue = ConvertProgressMaskValue(value);
    CHECK_NULL_VOID(convValue);
    property->SetValue(*convValue);
}

void SetProgressMaskMaxValue(const RefPtr<ProgressMaskProperty>& property, const Ark_Number* value)
{
    auto convValue = ConvertProgressMaskValue(value);
    CHECK_NULL_VOID(convValue);
    property->SetMaxValue(*convValue);
}

void SetProgressMaskColor(const RefPtr<ProgressMaskProperty>& property, const Ark_ResourceColor* value)
{
    CHECK_NULL_VOID(value);
    const auto convColor = Converter::OptConvert<Color>(*value);
    CHECK_NULL_VOID(convColor);
    property->SetColor(convColor.value());
}
} // namespace
namespace ProgressMaskAccessor {
void DestroyPeerImpl(Ark_ProgressMask peer)
{
    delete peer;
}
Ark_ProgressMask CtorImpl(const Ark_Number* value,
                          const Ark_Number* total,
                          const Ark_ResourceColor* color)
{
    auto peer = new ProgressMaskPeer();
    const auto& property = peer->GetProperty();
    SetProgressMaskValue(property, value);
    SetProgressMaskMaxValue(property, total);
    SetProgressMaskColor(property, color);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void UpdateProgressImpl(Ark_ProgressMask peer,
                        const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    SetProgressMaskValue(peer->GetProperty(), value);
}
void UpdateColorImpl(Ark_ProgressMask peer,
                     const Ark_ResourceColor* value)
{
    CHECK_NULL_VOID(peer);
    SetProgressMaskColor(peer->GetProperty(), value);
}
void EnableBreathingAnimationImpl(Ark_ProgressMask peer,
                                  Ark_Boolean value)
{
    CHECK_NULL_VOID(peer);
    peer->GetProperty()->SetEnableBreathe(Converter::Convert<bool>(value));
}
} // ProgressMaskAccessor
const GENERATED_ArkUIProgressMaskAccessor* GetProgressMaskAccessor()
{
    static const GENERATED_ArkUIProgressMaskAccessor ProgressMaskAccessorImpl {
        ProgressMaskAccessor::DestroyPeerImpl,
        ProgressMaskAccessor::CtorImpl,
        ProgressMaskAccessor::GetFinalizerImpl,
        ProgressMaskAccessor::UpdateProgressImpl,
        ProgressMaskAccessor::UpdateColorImpl,
        ProgressMaskAccessor::EnableBreathingAnimationImpl,
    };
    return &ProgressMaskAccessorImpl;
}

struct ProgressMaskPeer {
    virtual ~ProgressMaskPeer() = default;
};
}
