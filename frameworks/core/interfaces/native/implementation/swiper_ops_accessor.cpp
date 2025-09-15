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
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperOpsAccessor {
Ark_NativePointer RegisterIndexCallbackImpl(Ark_NativePointer node,
                                            const Ark_Number* value,
                                            const IndexCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto convValue = Converter::Convert<int32_t>(*value);
    SwiperModelStatic::SetIndex(frameNode, convValue < 0 ? OHOS::Ace::DEFAULT_SWIPER_CURRENT_INDEX : convValue);

    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        CHECK_NULL_VOID(swiperInfo);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(swiperInfo->GetIndex()));
    };
    SwiperModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // SwiperOpsAccessor
const GENERATED_ArkUISwiperOpsAccessor* GetSwiperOpsAccessor()
{
    static const GENERATED_ArkUISwiperOpsAccessor SwiperOpsAccessorImpl {
        SwiperOpsAccessor::RegisterIndexCallbackImpl,
    };
    return &SwiperOpsAccessorImpl;
}

}