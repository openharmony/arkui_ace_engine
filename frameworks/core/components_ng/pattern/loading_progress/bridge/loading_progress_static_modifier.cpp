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

#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/common_view/common_view_model_ng.h"
#include "core/components_ng/pattern/loading_progress/bridge/content_modifier_helper.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_static.h"
#include "core/interfaces/native/common/api_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/object_keeper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LoadingProgressModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = LoadingProgressModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // LoadingProgressModifier
namespace LoadingProgressInterfaceModifier {
void SetLoadingProgressOptionsImpl(Ark_NativePointer node)
{
    // Keep empty, since no options
}
} // LoadingProgressInterfaceModifier
namespace LoadingProgressAttributeModifier {
void SetColorImpl(Ark_NativePointer node,
                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<Color>(value);
    LoadingProgressModelStatic::SetColor(frameNode, color);
}
void SetEnableLoadingImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value).value_or(true);
    LoadingProgressModelNG::SetEnableLoading(frameNode, convValue);
}
} // LoadingProgressAttributeModifier

void ContentModifierLoadingProgressImpl(Ark_NativePointer node,
                                        const Ark_Object* contentModifier,
                                        const LoadingProgressModifierBuilder* builder)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(contentModifier);
    CHECK_NULL_VOID(builder);
    auto objectKeeper = std::make_shared<ObjectKeeper>(*contentModifier);
    auto builderFunc = [arkBuilder = CallbackHelper(*builder), node, frameNode, objectKeeper](
        LoadingProgressConfiguration config) -> RefPtr<FrameNode> {
        Ark_ContentModifier contentModifier = (*objectKeeper).get();
        Ark_LoadingProgressConfiguration arkConfig;
        arkConfig.contentModifier = contentModifier;
        arkConfig.enabled = Converter::ArkValue<Ark_Boolean>(config.enabled_);
        arkConfig.enableLoading = Converter::ArkValue<Ark_Boolean>(config.enableloading_);
        auto boxNode = GeneratedApiImpl::GetContentNode(node);
        if (boxNode == nullptr) {
            boxNode = CommonViewModelNG::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
            GeneratedApiImpl::SetContentNode(node, boxNode);
        }
        arkBuilder.BuildAsync([boxNode](const RefPtr<UINode>& uiNode) mutable {
            auto old = boxNode->GetChildAtIndex(0);
            if (old != nullptr) {
                boxNode->RemoveChildSilently(old);
            }
            boxNode->AddChild(uiNode);
            boxNode->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
            }, node, arkConfig);
        return boxNode;
    };
    LoadingProgressModelNG::SetBuilderFunc(frameNode, std::move(builderFunc));
}
void ResetContentModifierLoadingProgressImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetBuilderFunc(frameNode, nullptr);
}

const GENERATED_ArkUILoadingProgressModifier* GetLoadingProgressStaticModifier()
{
    static const GENERATED_ArkUILoadingProgressModifier ArkUILoadingProgressModifierImpl {
        LoadingProgressModifier::ConstructImpl,
        LoadingProgressInterfaceModifier::SetLoadingProgressOptionsImpl,
        LoadingProgressAttributeModifier::SetColorImpl,
        LoadingProgressAttributeModifier::SetEnableLoadingImpl,
    };
    return &ArkUILoadingProgressModifierImpl;
}

const ArkUILoadingProgressContentModifier* GetLoadingProgressStaticContentModifier()
{
    static const ArkUILoadingProgressContentModifier LoadingProgressContentModifierImpl {
        ContentModifierLoadingProgressImpl, ResetContentModifierLoadingProgressImpl
    };
    return &LoadingProgressContentModifierImpl;
}
}
