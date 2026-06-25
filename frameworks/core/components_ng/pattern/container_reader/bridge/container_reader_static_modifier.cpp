/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_reader/container_reader_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/common/window_size_breakpoint.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "arkoala_api_generated.h"
#endif

namespace OHOS::Ace::NG::GeneratedModifier {

namespace ContainerReaderExtenderAccessor {

Ark_NativePointer ContainerReaderConstructorImpl(Ark_Int32 id)
{
    auto frameNode = ContainerReaderModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

void SetContainerReaderOptionsImpl(Ark_NativePointer node,
                                    const Ark_Size* size,
                                    const Callback_SizeInfo_Void* onChange,
                                    const Opt_Bindable_WidthBreakpoint* widthBreakpoint,
                                    const Opt_Bindable_HeightBreakpoint* heightBreakpoint)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (onChange && onChange->call) {
        auto callbackHelper = std::make_shared<CallbackHelper<Callback_SizeInfo_Void>>(*onChange);
        auto onSizeChange = [callbackHelper](const SizeF& sz) {
            Ark_Size arkSize;
            arkSize.width = static_cast<Ark_Float64>(sz.Width());
            arkSize.height = static_cast<Ark_Float64>(sz.Height());
            callbackHelper->Invoke(arkSize);
        };
        ContainerReaderModelStatic::SetOnSizeChange(frameNode, std::move(onSizeChange));
    }

    auto widthBpOpt = Converter::GetOptPtr(widthBreakpoint);
    if (widthBpOpt.has_value() && widthBpOpt->onChange.call != nullptr) {
        auto onWidthBpChange = [arkCallback = CallbackHelper(widthBpOpt->onChange)](WidthBreakpoint breakpoint) {
            arkCallback.Invoke(static_cast<Ark_WidthBreakpoint>(breakpoint));
        };
        ContainerReaderModelStatic::SetOnWidthBreakpointChange(frameNode, std::move(onWidthBpChange));
    }

    auto heightBpOpt = Converter::GetOptPtr(heightBreakpoint);
    if (heightBpOpt.has_value() && heightBpOpt->onChange.call != nullptr) {
        auto onHeightBpChange = [arkCallback = CallbackHelper(heightBpOpt->onChange)](HeightBreakpoint breakpoint) {
            arkCallback.Invoke(static_cast<Ark_HeightBreakpoint>(breakpoint));
        };
        ContainerReaderModelStatic::SetOnHeightBreakpointChange(frameNode, std::move(onHeightBpChange));
    }
}

void BreakpointConfigImpl(Ark_NativePointer node,
                          const Opt_Array_F64* width,
                          const Opt_Array_F64* height)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<double> widthBreakpoints;
    std::vector<double> heightBreakpoints;

    auto widthOpt = Converter::GetOptPtr(width);
    if (widthOpt.has_value()) {
        auto& arr = widthOpt.value();
        if (arr.array != nullptr && arr.length > 0) {
            widthBreakpoints.assign(arr.array, arr.array + arr.length);
        }
    }

    auto heightOpt = Converter::GetOptPtr(height);
    if (heightOpt.has_value()) {
        auto& arr = heightOpt.value();
        if (arr.array != nullptr && arr.length > 0) {
            heightBreakpoints.assign(arr.array, arr.array + arr.length);
        }
    }

    ContainerReaderModelStatic::SetBreakPointConfig(frameNode, widthBreakpoints, heightBreakpoints);
}

} // namespace ContainerReaderExtenderAccessor

#ifdef INCLUDE_GENERATED_SOURCES
const GENERATED_ArkUIContainerReaderExtenderAccessor* GetContainerReaderExtenderAccessor()
{
    static const GENERATED_ArkUIContainerReaderExtenderAccessor ContainerReaderExtenderAccessorImpl {
        ContainerReaderExtenderAccessor::ContainerReaderConstructorImpl,
        ContainerReaderExtenderAccessor::SetContainerReaderOptionsImpl,
        ContainerReaderExtenderAccessor::BreakpointConfigImpl,
    };
    return &ContainerReaderExtenderAccessorImpl;
}
#endif

} // namespace OHOS::Ace::NG::GeneratedModifier