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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/refresh/refresh_model_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
namespace Converter {
void AssignArkValue(Ark_RefreshStatus& dst, const RefreshStatus& src)
{
    switch (src) {
        case RefreshStatus::INACTIVE:
            dst = ARK_REFRESH_STATUS_INACTIVE;
            break;
        case RefreshStatus::DRAG:
            dst = ARK_REFRESH_STATUS_DRAG;
            break;
        case RefreshStatus::OVER_DRAG:
            dst = ARK_REFRESH_STATUS_OVER_DRAG;
            break;
        case RefreshStatus::REFRESH:
            dst = ARK_REFRESH_STATUS_REFRESH;
            break;
        case RefreshStatus::DONE:
            dst = ARK_REFRESH_STATUS_DONE;
            break;
        default:
            dst = static_cast<Ark_RefreshStatus>(-1);
            LOGE("Unexpected enum value in RefreshStatus: %{public}d", src);
    }
}
} // namespace Converter
namespace {
std::optional<bool> ProcessBindableRefreshing(FrameNode* frameNode, const Ark_Union_Boolean_Bindable& value)
{
    std::optional<bool> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const std::string& param) {
                if (param != "true" && param != "false") {
                    return;
                }
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(Framework::StringToBool(param)));
            };
            RefreshModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RefreshModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = RefreshModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace RefreshModifier
namespace {
constexpr float PULLDOWNRATIO_MIN = 0.0f;
constexpr float PULLDOWNRATIO_MAX = 1.0f;
} // namespace
namespace RefreshInterfaceModifier {
void SetRefreshOptionsImpl(Ark_NativePointer node,
                           const Ark_RefreshOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto refreshing = ProcessBindableRefreshing(frameNode, value->refreshing);
    RefreshModelStatic::SetRefreshing(frameNode, refreshing);

    auto promptText = Converter::OptConvert<std::string>(value->promptText);
    RefreshModelStatic::SetLoadingText(frameNode, promptText);

    auto arkBuilder = Converter::OptConvert<CustomNodeBuilder>(value->builder);
    if (arkBuilder) {
        CallbackHelper(arkBuilder.value())
            .BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
                    RefreshModelStatic::SetCustomBuilder(frameNode, uiNode);
                    RefreshModelStatic::SetIsCustomBuilderExist(frameNode, true);
                },
                node);
    } else {
        RefreshModelStatic::SetCustomBuilder(frameNode, nullptr);
        RefreshModelStatic::SetIsCustomBuilderExist(frameNode, false);
    }
}
} // namespace RefreshInterfaceModifier
namespace RefreshAttributeModifier {
void SetOnStateChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_RefreshStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RefreshModelStatic::SetOnStateChange(frameNode, nullptr);
        return;
    }
    auto onStateChange = [arkCallback = CallbackHelper(*optValue)](const int32_t statusValue) {
        RefreshStatus status = static_cast<RefreshStatus>(statusValue);
        Ark_RefreshStatus arkStatus = Converter::ArkValue<Ark_RefreshStatus>(status);
        arkCallback.Invoke(arkStatus);
    };
    RefreshModelStatic::SetOnStateChange(frameNode, std::move(onStateChange));
}
void SetOnRefreshingImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RefreshModelStatic::SetOnRefreshing(frameNode, nullptr);
        return;
    }
    auto onRefreshing = [arkCallback = CallbackHelper(*optValue)]() { arkCallback.Invoke(); };
    RefreshModelStatic::SetOnRefreshing(frameNode, std::move(onRefreshing));
}
void SetRefreshOffsetImpl(Ark_NativePointer node,
                          const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    RefreshModelStatic::SetRefreshOffset(frameNode, convValue);
}
void SetPullToRefreshImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    RefreshModelStatic::SetPullToRefresh(frameNode, convValue);
}
void SetOnOffsetChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_F64_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RefreshModelStatic::ResetOnOffsetChange(frameNode);
        return;
    }
    auto onOffsetChange = [arkCallback = CallbackHelper(*optValue)](const float indexValue) {
        Ark_Float64 index = Converter::ArkValue<Ark_Float64>(indexValue);
        arkCallback.Invoke(index);
    };
    RefreshModelStatic::SetOnOffsetChange(frameNode, std::move(onOffsetChange));
}
void SetPullDownRatioImpl(Ark_NativePointer node,
                          const Opt_Float64* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ClampByRange(convValue, PULLDOWNRATIO_MIN, PULLDOWNRATIO_MAX);
    RefreshModelStatic::SetPullDownRatio(frameNode, convValue);
}
} // RefreshAttributeModifier
const GENERATED_ArkUIRefreshModifier* GetRefreshModifier()
{
    static const GENERATED_ArkUIRefreshModifier ArkUIRefreshModifierImpl {
        RefreshModifier::ConstructImpl,
        RefreshInterfaceModifier::SetRefreshOptionsImpl,
        RefreshAttributeModifier::SetOnStateChangeImpl,
        RefreshAttributeModifier::SetOnRefreshingImpl,
        RefreshAttributeModifier::SetRefreshOffsetImpl,
        RefreshAttributeModifier::SetPullToRefreshImpl,
        RefreshAttributeModifier::SetOnOffsetChangeImpl,
        RefreshAttributeModifier::SetPullDownRatioImpl,
    };
    return &ArkUIRefreshModifierImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
