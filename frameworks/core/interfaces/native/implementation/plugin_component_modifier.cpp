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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/plugin/plugin_model_ng.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace {
    struct PluginComponentOptions {
        std::optional<RequestPluginInfo> requestPluginInfo;
        std::string data;
    };
} // namespace
namespace Converter {
    template<>
    PluginComponentOptions Convert(const Ark_PluginComponentOptions& options)
    {
        PluginComponentOptions opt;
        opt.requestPluginInfo = OptConvert<RequestPluginInfo>(options.template_);
        LOGE("PluginComponentModifier::Convert cannot convert data. data is Ark_CustomObject!");
        return opt;
    }
    template<>
    RequestPluginInfo Convert(const Ark_PluginComponentTemplate& temp)
    {
        RequestPluginInfo info;
        info.source = Convert<std::string>(temp.source);
        info.bundleName = Convert<std::string>(temp.bundleName);
        return info;
    }
} // Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PluginComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // PluginComponentModifier
namespace PluginComponentInterfaceModifier {
void SetPluginComponentOptionsImpl(Ark_NativePointer node,
                                   const Ark_PluginComponentOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);

    auto optInfoData = Converter::OptConvert<PluginComponentOptions>(*options);
    if (optInfoData) {
        PluginModelNG::SetRequestPluginInfo(frameNode, optInfoData->requestPluginInfo);
    } else {
        PluginModelNG::SetRequestPluginInfo(frameNode, std::nullopt);
    }
    LOGE("PluginComponentModifier::SetPluginComponentOptionsImpl setData into model isn't supported");
}
} // PluginComponentInterfaceModifier
namespace PluginComponentAttributeModifier {
void OnCompleteImpl(Ark_NativePointer node,
                    const VoidCallback* value)
{
#if defined(PLUGIN_COMPONENT_SUPPORTED)
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onComplete = [arkCallback = CallbackHelper(*value)](const std::string& param) -> void {
        arkCallback.Invoke();
    };
    PluginModelNG::SetOnComplete(frameNode, std::move(onComplete));
#endif
}
void OnErrorImpl(Ark_NativePointer node,
                 const PluginErrorCallback* value)
{
#ifdef PLUGIN_COMPONENT_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onError = [arkCallback = CallbackHelper(*value)](const std::string& param) -> void {
        auto json = JsonUtil::ParseJsonString(param);
        Ark_PluginErrorData errorData;
        errorData.errcode = Converter::ArkValue<Ark_Number>(StringUtils::StringToInt(json->GetString("errcode")));
        errorData.msg = Converter::ArkValue<Ark_String>(json->GetString("msg"));
        arkCallback.Invoke(errorData);
    };
    PluginModelNG::SetOnError(frameNode, std::move(onError));
#endif
}
} // PluginComponentAttributeModifier
const GENERATED_ArkUIPluginComponentModifier* GetPluginComponentModifier()
{
    static const GENERATED_ArkUIPluginComponentModifier ArkUIPluginComponentModifierImpl {
        PluginComponentModifier::ConstructImpl,
        PluginComponentInterfaceModifier::SetPluginComponentOptionsImpl,
        PluginComponentAttributeModifier::OnCompleteImpl,
        PluginComponentAttributeModifier::OnErrorImpl,
    };
    return &ArkUIPluginComponentModifierImpl;
}

}
