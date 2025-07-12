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
#include "core/components_ng/pattern/side_bar/side_bar_container_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SideBarContainerOpsAccessor {
constexpr int32_t DEFAULT_SIDE_BAR_WIDTH = 240;
Ark_NativePointer RegisterShowSideBarCallbackImpl(Ark_NativePointer node,
                                                  Ark_Boolean value,
                                                  const ShowSideBarCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    SideBarContainerModelStatic::SetShowSideBar(frameNode, Converter::Convert<bool>(value));
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto changeEvent = [arkCallback = CallbackHelper(*callback), weakNode](bool isShow) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isShow));
    };
    SideBarContainerModelStatic::SetOnChangeEvent(frameNode, std::move(changeEvent));
    return node;
}
Ark_NativePointer RegisterSideBarWidthCallbackImpl(Ark_NativePointer node,
                                                   const Ark_Number* value,
                                                   const SideBarWidthCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto width = Converter::Convert<Dimension>(*value);
    if (width.IsNegative()) {
        width.SetValue(DEFAULT_SIDE_BAR_WIDTH);
    }
    SideBarContainerModelStatic::SetSideBarWidth(frameNode, width);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto changeEvent = [arkCallback = CallbackHelper(*callback), weakNode](Dimension sideBarWidth) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(sideBarWidth));
    };
    SideBarContainerModelStatic::SetOnSideBarWidthChangeEvent(frameNode, std::move(changeEvent));
    return node;
}
} // SideBarContainerOpsAccessor
const GENERATED_ArkUISideBarContainerOpsAccessor* GetSideBarContainerOpsAccessor()
{
    static const GENERATED_ArkUISideBarContainerOpsAccessor SideBarContainerOpsAccessorImpl {
        SideBarContainerOpsAccessor::RegisterShowSideBarCallbackImpl,
        SideBarContainerOpsAccessor::RegisterSideBarWidthCallbackImpl,
    };
    return &SideBarContainerOpsAccessorImpl;
}

}
