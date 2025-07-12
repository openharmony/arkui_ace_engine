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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace Converter {

void AssignArkValue(Ark_RefreshStatus& dst, const RefreshStatus& src)
{
    switch (src) {
        case RefreshStatus::INACTIVE: dst = ARK_REFRESH_STATUS_INACTIVE; break;
        case RefreshStatus::DRAG: dst = ARK_REFRESH_STATUS_DRAG; break;
        case RefreshStatus::OVER_DRAG: dst = ARK_REFRESH_STATUS_OVER_DRAG; break;
        case RefreshStatus::REFRESH: dst = ARK_REFRESH_STATUS_REFRESH; break;
        case RefreshStatus::DONE: dst = ARK_REFRESH_STATUS_DONE; break;
        default: dst = static_cast<Ark_RefreshStatus>(-1);
            LOGE("Unexpected enum value in RefreshStatus: %{public}d", src);
    }
}

} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RefreshModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = RefreshModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // RefreshModifier
namespace {
    constexpr float PULLDOWNRATIO_MIN = 0.0f;
    constexpr float PULLDOWNRATIO_MAX = 1.0f;
} // namespace
namespace RefreshInterfaceModifier {
void SetRefreshOptionsImpl(Ark_NativePointer node,
                           const Ark_RefreshOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA RefreshInterfaceModifier::SetRefreshOptionsImpl - refreshingContent is not supported yet");

    bool refreshing = Converter::Convert<bool>(value->refreshing);
    RefreshModelNG::SetRefreshing(frameNode, refreshing);

    auto promptText = Converter::OptConvert<std::string>(value->promptText);
    if (promptText) {
        // need check
    }

    RefPtr<UINode> customNode;
    auto arkBuilder = Converter::OptConvert<CustomNodeBuilder>(value->builder);
    if (arkBuilder) {
        customNode = CallbackHelper(arkBuilder.value()).BuildSync(node);
    }
    // need check
}
} // RefreshInterfaceModifier
namespace RefreshAttributeModifier {
void OnStateChangeImpl(Ark_NativePointer node,
                       const Callback_RefreshStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto onStateChange = [arkCallback = CallbackHelper(*value)](const int32_t statusValue) {
        RefreshStatus status = static_cast<RefreshStatus>(statusValue);
        Ark_RefreshStatus arkStatus = Converter::ArkValue<Ark_RefreshStatus>(status);
        arkCallback.Invoke(arkStatus);
    };
    RefreshModelNG::SetOnStateChange(frameNode, std::move(onStateChange));
}
void OnRefreshingImpl(Ark_NativePointer node,
                      const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto onRefreshing = [arkCallback = CallbackHelper(*value)]() {
        arkCallback.Invoke();
    };
    RefreshModelNG::SetOnRefreshing(frameNode, std::move(onRefreshing));
}
void RefreshOffsetImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    // need check
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

    auto onOffsetChange = [arkCallback = CallbackHelper(*value)](const float indexValue) {
        Ark_Number index = Converter::ArkValue<Ark_Number>(indexValue);
        arkCallback.Invoke(index);
    };
    RefreshModelNG::SetOnOffsetChange(frameNode, std::move(onOffsetChange));
}
void PullDownRatioImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<float>(*value) : std::nullopt;
    Validator::ClampByRange(convValue, PULLDOWNRATIO_MIN, PULLDOWNRATIO_MAX);
    RefreshModelNG::SetPullDownRatio(frameNode, convValue);
}
void _onChangeEvent_refreshingImpl(Ark_NativePointer node,
                                   const Callback_Boolean_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& param) {
        if (param != "true" && param != "false") {
            return;
        }
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(Framework::StringToBool(param)));
    };
    RefreshModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}
} // RefreshAttributeModifier
const GENERATED_ArkUIRefreshModifier* GetRefreshModifier()
{
    static const GENERATED_ArkUIRefreshModifier ArkUIRefreshModifierImpl {
        RefreshModifier::ConstructImpl,
        RefreshInterfaceModifier::SetRefreshOptionsImpl,
        RefreshAttributeModifier::OnStateChangeImpl,
        RefreshAttributeModifier::OnRefreshingImpl,
        RefreshAttributeModifier::RefreshOffsetImpl,
        RefreshAttributeModifier::PullToRefreshImpl,
        RefreshAttributeModifier::OnOffsetChangeImpl,
        RefreshAttributeModifier::PullDownRatioImpl,
        RefreshAttributeModifier::_onChangeEvent_refreshingImpl,
    };
    return &ArkUIRefreshModifierImpl;
}

}
