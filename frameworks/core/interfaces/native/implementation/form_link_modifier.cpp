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

#include "base/json/json_util.h"
#include "core/components_ng/pattern/form_link/form_link_model_ng.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace {
std::unique_ptr<FormLinkModel> FormLinkModel::stsInstance_ = nullptr;
std::mutex FormLinkModel::stsMutex_;

FormLinkModel* FormLinkModel::GetStsInstance()
{
    if (!stsInstance_) {
        std::lock_guard<std::mutex> lock(stsMutex_);
        if (!stsInstance_) {
#ifdef NG_BUILD
            stsInstance_.reset(new NG::FormLinkModelNG());
#else
            stsInstance_.reset(Container::IsCurrentUseNewPipeline() ? new NG::FormLinkModelNG() : nullptr);
#endif
        }
    }
    return stsInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
struct FormLinkOptions {
    std::string action;
    std::optional<std::string> moduleName;
    std::optional<std::string> bundleName;
    std::optional<std::string> abilityName;
    std::optional<std::string> uri;
};
} // namespace

namespace Converter {
template<>
FormLinkOptions Convert(const Ark_FormLinkOptions& src)
{
    return { .action = Convert<std::string>(src.action),
        .moduleName = Converter::OptConvert<std::string>(src.moduleName),
        .bundleName = Converter::OptConvert<std::string>(src.bundleName),
        .abilityName = Converter::OptConvert<std::string>(src.abilityName),
        .uri = Converter::OptConvert<std::string>(src.uri) };
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FormLinkModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = FormLinkModel::GetStsInstance()->StsCreateFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace FormLinkModifier

namespace FormLinkInterfaceModifier {
std::string ToString(const FormLinkOptions& formLinkOptions)
{
    auto json = JsonUtil::Create(true);
    json->Put("action", formLinkOptions.action.c_str());
    json->Put("moduleName", formLinkOptions.moduleName ? formLinkOptions.moduleName.value().c_str() : "");
    json->Put("bundleName", formLinkOptions.bundleName ? formLinkOptions.bundleName.value().c_str() : "");
    json->Put("abilityName", formLinkOptions.abilityName ? formLinkOptions.abilityName.value().c_str() : "");
    json->Put("uri", formLinkOptions.uri ? formLinkOptions.uri.value().c_str() : "");

    return json->ToString();
}

void SetFormLinkOptionsImpl(Ark_NativePointer node, const Ark_FormLinkOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node); // RefPtr<OHOS::Ace::NG::FrameNode>

    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    FormLinkOptions formLinkOptions = Converter::Convert<FormLinkOptions>(*options);
    std::string opt = ToString(formLinkOptions);

    LOGI("End, StsSetAction: %{public}s", opt.c_str());
    FormLinkModel::GetStsInstance()->StsSetAction(frameNode, opt);
}
} // namespace FormLinkInterfaceModifier

const GENERATED_ArkUIFormLinkModifier* GetFormLinkModifier()
{
    static const GENERATED_ArkUIFormLinkModifier ArkUIFormLinkModifierImpl {
        FormLinkModifier::ConstructImpl,
        FormLinkInterfaceModifier::SetFormLinkOptionsImpl,
    };
    return &ArkUIFormLinkModifierImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
