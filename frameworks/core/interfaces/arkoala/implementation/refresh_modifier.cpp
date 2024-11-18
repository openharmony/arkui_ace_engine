/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RefreshInterfaceModifier {
void SetRefreshOptionsImpl(Ark_NativePointer node,
                           const Ark_RefreshOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA RefreshInterfaceModifier::SetRefreshOptionsImpl is not implemented yet");
}
} // RefreshInterfaceModifier
namespace RefreshAttributeModifier {
void OnStateChangeImpl(Ark_NativePointer node,
                       const Callback_RefreshStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //RefreshModelNG::SetOnStateChange(frameNode, convValue);
    LOGE("ARKOALA RefreshInterfaceModifier::OnStateChangeImpl is not implemented yet");
}
void OnRefreshingImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //RefreshModelNG::SetOnRefreshing(frameNode, convValue);
    LOGE("ARKOALA RefreshInterfaceModifier::OnRefreshingImpl is not implemented yet");
}
void RefreshOffsetImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    RefreshModelNG::SetRefreshOffset(frameNode, convValue);
}
void PullToRefreshImpl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    RefreshModelNG::SetPullToRefresh(frameNode, convValue);
}
void OnOffsetChangeImpl(Ark_NativePointer node,
                        const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //RefreshModelNG::SetOnOffsetChange(frameNode, convValue);
    LOGE("ARKOALA RefreshInterfaceModifier::OnOffsetChangeImpl is not implemented yet");
}
void PullDownRatioImpl(Ark_NativePointer node,
                       const Ark_Union_Number_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    RefreshModelNG::SetPullDownRatio(frameNode, convValue);
}
} // RefreshAttributeModifier
const GENERATED_ArkUIRefreshModifier* GetRefreshModifier()
{
    static const GENERATED_ArkUIRefreshModifier ArkUIRefreshModifierImpl {
        RefreshInterfaceModifier::SetRefreshOptionsImpl,
        RefreshAttributeModifier::OnStateChangeImpl,
        RefreshAttributeModifier::OnRefreshingImpl,
        RefreshAttributeModifier::RefreshOffsetImpl,
        RefreshAttributeModifier::PullToRefreshImpl,
        RefreshAttributeModifier::OnOffsetChangeImpl,
        RefreshAttributeModifier::PullDownRatioImpl,
    };
    return &ArkUIRefreshModifierImpl;
}

}
