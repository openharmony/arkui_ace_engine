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
#include "core/components_ng/pattern/search/bridge/search_custom_modifier.h"
#include "core/components_ng/pattern/search/search_model_static.h"
#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/common/dynamic_module_helper.h"
namespace OHOS::Ace::NG {
SearchModel* GetInstance()
{
#ifdef NG_BUILD
    static NG::SearchModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::SearchModelNG instance;
        return &instance;
    } else {
        static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("search");
        static SearchModel* instance = loader ? reinterpret_cast<SearchModel*>(loader->CreateModel()) : nullptr;
        return instance;
    }
#endif
}

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void SetKeyboardAppearanceConfig(FrameNode* frameNode, KeyboardAppearanceConfig config)
{
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetKeyboardAppearanceConfig(frameNode, config);
}

void SetTextValue(FrameNode* frameNode, const std::optional<std::string>& value)
{
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextValue(frameNode, value);
}

void SetOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetOnChangeEvent(frameNode, std::move(onChangeEvent));
}

void SetSearchSymbolIcon(ArkUINodeHandle node, std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchSymbolIcon(frameNode, iconSymbol);
}

void SetSearchCancelSymbolIcon(
    ArkUINodeHandle node, std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol, ArkUI_Int32 style)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCancelSymbolIcon(frameNode, iconSymbol);
}

void SetDragPreviewOptions(ArkUINodeHandle node, const NG::DragPreviewOption option)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetDragPreviewOptions(frameNode, option);
}

void CreateNormalSearch(std::optional<std::u16string>& stringValue, std::optional<std::u16string>& placeholder,
    std::optional<std::string>& iconSrc, const ArkUISearchCreateResourceParams* resParams)
{
    static SearchModelNG model;
    model.Create(stringValue, placeholder, iconSrc);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform()) {
        if (resParams && resParams->parseValueResult && resParams->stringValueRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resParams->stringValueRawPtr));
            pattern->RegisterResource<std::u16string>("text", resObj, stringValue.value());
        } else {
            pattern->UnRegisterResource("text");
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        if (resParams && resParams->parsePlaceholderResult && resParams->placeholderRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resParams->placeholderRawPtr));
            pattern->RegisterResource<std::u16string>("placeholder", resObj, placeholder.value());
        } else {
            pattern->UnRegisterResource("placeholder");
        }
    }
}
namespace NodeModifier {
const ArkUISearchCustomModifier* GetSearchCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISearchCustomModifier modifier = {
        .setKeyboardAppearanceConfig = SetKeyboardAppearanceConfig,
        .setTextValue = SetTextValue,
        .setOnChangeEvent = SetOnChangeEvent,
        .createNormalSearch = CreateNormalSearch,
        .setSearchSymbolIcon = SetSearchSymbolIcon,
        .setSearchCancelSymbolIcon = SetSearchCancelSymbolIcon,
        .setDragPreviewOptions = SetDragPreviewOptions,
        .getInstance = GetInstance,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG