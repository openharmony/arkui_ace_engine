/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/rating/rating_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
 
namespace OHOS::Ace::NG::GeneratedModifier {
namespace RatingOpsAccessor {
Ark_NativePointer RegisterRatingCallbackImpl(Ark_NativePointer node,
                                             const Ark_Number* rating,
                                             const RatingCallback* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::optional<double> ratingOpt = Converter::Convert<double>(*rating);
    std::optional<bool> indicator = false;
    RatingModelStatic::SetRatingOptions(frameNode, ratingOpt.value_or(0), indicator);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& value) {
        Ark_Number nValue = Converter::ArkValue<Ark_Number>(std::stof(value));
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(nValue);
    };
    RatingModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
    return node;
}
} // namespace RatingOpsAccessor
const GENERATED_ArkUIRatingOpsAccessor* GetRatingOpsAccessor()
{
    static const GENERATED_ArkUIRatingOpsAccessor RatingOpsAccessorImpl {
        RatingOpsAccessor::RegisterRatingCallbackImpl,
    };
    return &RatingOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
 