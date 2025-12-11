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
#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
SliderPrefixOptions Convert(const Ark_SliderPrefixOptions& src)
{
    SliderPrefixOptions dst;
    dst.accessibilityText = Converter::OptConvert<std::string>(src.accessibilityText).value_or("");
    dst.accessibilityDescription = Converter::OptConvert<std::string>(src.accessibilityDescription).value_or("");
    dst.accessibilityLevel = Converter::OptConvert<std::string>(src.accessibilityLevel).value_or("auto");
    dst.accessibilityGroup = Converter::OptConvert<bool>(src.accessibilityGroup).value_or(false);
    return dst;
}

template<>
SliderSuffixOptions Convert(const Ark_SliderSuffixOptions& src)
{
    SliderSuffixOptions dst;
    dst.accessibilityText = Converter::OptConvert<std::string>(src.accessibilityText).value_or("");
    dst.accessibilityDescription = Converter::OptConvert<std::string>(src.accessibilityDescription).value_or("");
    dst.accessibilityLevel = Converter::OptConvert<std::string>(src.accessibilityLevel).value_or("auto");
    dst.accessibilityGroup = Converter::OptConvert<bool>(src.accessibilityGroup).value_or(false);
    return dst;
}
} // namespace OHOS::Ace::NG::Converter

using namespace OHOS::Ace::NG::Converter;
namespace OHOS::Ace::NG::GeneratedModifier {
namespace SliderExtenderAccessor {
void SetPrefixImpl(Ark_NativePointer node, Ark_NativePointer prefixNode, const Opt_SliderPrefixOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* prefixNodePeer = reinterpret_cast<FrameNodePeer*>(prefixNode);
    CHECK_NULL_VOID(prefixNodePeer);
    auto prefixNodeRef = FrameNodePeer::GetFrameNodeByPeer(prefixNodePeer);
    SliderPrefixOptions prefixOptions =
        options ? Converter::Convert<SliderPrefixOptions>(options->value) : SliderPrefixOptions();
    SliderModelNG::SetPrefix(frameNode, prefixNodeRef, prefixOptions);
}
void SetSuffixImpl(Ark_NativePointer node, Ark_NativePointer suffixNode, const Opt_SliderSuffixOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* suffixNodePeer = reinterpret_cast<FrameNodePeer*>(suffixNode);
    CHECK_NULL_VOID(suffixNodePeer);
    auto suffixNodeRef = FrameNodePeer::GetFrameNodeByPeer(suffixNodePeer);
    SliderSuffixOptions suffixOptions =
        options ? Converter::Convert<SliderSuffixOptions>(options->value) : SliderSuffixOptions();
    SliderModelNG::SetSuffix(frameNode, suffixNodeRef, suffixOptions);
}
} // namespace SliderExtenderAccessor
const GENERATED_ArkUISliderExtenderAccessor* GetSliderExtenderAccessor()
{
    static const GENERATED_ArkUISliderExtenderAccessor SliderExtenderAccessorImpl {
        SliderExtenderAccessor::SetPrefixImpl,
        SliderExtenderAccessor::SetSuffixImpl,
    };
    return &SliderExtenderAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier