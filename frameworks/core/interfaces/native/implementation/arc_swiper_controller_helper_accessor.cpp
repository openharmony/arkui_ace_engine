/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ArcSwiperControllerHelperAccessor {
void DestroyPeerImpl(Ark_ArcSwiperControllerHelper peer)
{
}
Ark_ArcSwiperControllerHelper ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ShowNextImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::ShowNext(frameNode, convValue);
}
void ShowPreviousImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::ShowPrevious(frameNode, convValue);
}
void FinishAnimationImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* callback_)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(node);
    //auto convValue = Converter::OptConvert<type>(node); // for enums
    //undefinedModelNG::FinishAnimation(frameNode, convValue);
}
} // ArcSwiperControllerHelperAccessor
const GENERATED_ArkUIArcSwiperControllerHelperAccessor* GetArcSwiperControllerHelperAccessor()
{
    static const GENERATED_ArkUIArcSwiperControllerHelperAccessor ArcSwiperControllerHelperAccessorImpl {
        ArcSwiperControllerHelperAccessor::DestroyPeerImpl,
        ArcSwiperControllerHelperAccessor::ConstructImpl,
        ArcSwiperControllerHelperAccessor::GetFinalizerImpl,
        ArcSwiperControllerHelperAccessor::ShowNextImpl,
        ArcSwiperControllerHelperAccessor::ShowPreviousImpl,
        ArcSwiperControllerHelperAccessor::FinishAnimationImpl,
    };
    return &ArcSwiperControllerHelperAccessorImpl;
}

}
