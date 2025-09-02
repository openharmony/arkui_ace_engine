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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_static.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonMethodOpsAccessor {
void VisualEffectHandWrittenImpl(Ark_NativePointer node, Ark_Int64 value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto addr = Converter::Convert<int64_t>(value);
    auto convValue = reinterpret_cast<OHOS::Rosen::VisualEffect* >(addr);
    if (!convValue) {
        return;
    }
    ViewAbstractModelStatic::SetVisualEffect(frameNode, convValue);
}

void BackgroundFilterHandWrittenImpl(Ark_NativePointer node, Ark_Int64 value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto addr = Converter::Convert<int64_t>(value);
    auto convValue = reinterpret_cast<OHOS::Rosen::Filter* >(addr);
    if (!convValue) {
        return;
    }
    ViewAbstractModelStatic::SetBackgroundFilter(frameNode, convValue);
}
void ForegroundFilterHandWrittenImpl(Ark_NativePointer node, Ark_Int64 value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto addr = Converter::Convert<int64_t>(value);
    auto convValue = reinterpret_cast<OHOS::Rosen::Filter* >(addr);
    if (!convValue) {
        return;
    }
    ViewAbstractModelStatic::SetForegroundFilter(frameNode, convValue);
}
void CompositingFilterHandWrittenImpl(Ark_NativePointer node, Ark_Int64 value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto addr = Converter::Convert<int64_t>(value);
    auto convValue = reinterpret_cast<OHOS::Rosen::Filter* >(addr);
    if (!convValue) {
        return;
    }
    ViewAbstractModelStatic::SetCompositingFilter(frameNode, convValue);
}
void AdvancedBlendModeObjectImpl(Ark_NativePointer node,
    Ark_Int64 effect, const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto addr = Converter::Convert<int64_t>(effect);
    auto convValue = reinterpret_cast<OHOS::Rosen::BrightnessBlender* >(addr);
    if (!convValue) {
        return;
    }
    ViewAbstractModelStatic::SetBrightnessBlender(frameNode, convValue);
    BlendApplyType blendApplyType = BlendApplyType::FAST;
    std::optional<BlendApplyType> blendApplyTypeOpt = Converter::OptConvertPtr<BlendApplyType>(type);
    blendApplyType = blendApplyTypeOpt.value_or(blendApplyType);
    ViewAbstractModelStatic::SetBlendApplyType(frameNode, blendApplyTypeOpt);
}
void AdvancedBlendModeEnumImpl(Ark_NativePointer node,
    const Opt_BlendMode* effect, const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto blendMode = Converter::OptConvertPtr<BlendMode>(effect);
    auto blendApplyType = Converter::OptConvertPtr<BlendApplyType>(type);
    ViewAbstractModelStatic::SetBlendMode(frameNode, blendMode);
    ViewAbstractModelStatic::SetBlendApplyType(frameNode, blendApplyType);
}
} // CommonMethodOpsAccessor
const GENERATED_ArkUICommonMethodOpsAccessor* GetCommonMethodOpsAccessor()
{
    static const GENERATED_ArkUICommonMethodOpsAccessor CommonMethodOpsAccessorImpl {
        CommonMethodOpsAccessor::VisualEffectHandWrittenImpl,
        CommonMethodOpsAccessor::BackgroundFilterHandWrittenImpl,
        CommonMethodOpsAccessor::ForegroundFilterHandWrittenImpl,
        CommonMethodOpsAccessor::CompositingFilterHandWrittenImpl,
        CommonMethodOpsAccessor::AdvancedBlendModeObjectImpl,
        CommonMethodOpsAccessor::AdvancedBlendModeEnumImpl,
    };
    return &CommonMethodOpsAccessorImpl;
}
}
