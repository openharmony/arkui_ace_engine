/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/search_modifier.h"

#include "ui/base/utils/utils.h"

#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/search/bridge/search_custom_modifier.h"
#include "core/components_ng/pattern/search/search_model_ng.h"

namespace OHOS::Ace::NG {

namespace NodeModifier {
const ArkUISearchModifier* GetSearchModifier()
{
    static const ArkUISearchModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Search");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUISearchModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUISearchModifier* GetCJUISearchModifier()
{
    static const CJUISearchModifier* cachedCjModifier = nullptr;
    if (cachedCjModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Search");
        CHECK_NULL_RETURN(module, nullptr);
        cachedCjModifier = reinterpret_cast<const CJUISearchModifier*>(module->GetCjModifier());
    }
    return cachedCjModifier;
}

const ArkUISearchCustomModifier* GetSearchCustomModifier()
{
    static const ArkUISearchCustomModifier* cachedCustomModifier = nullptr;
    if (cachedCustomModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Search");
        CHECK_NULL_RETURN(module, nullptr);
        cachedCustomModifier = reinterpret_cast<const ArkUISearchCustomModifier*>(module->GetCustomModifier());
    }
    return cachedCustomModifier;
}

void SetOnSearchSubmit(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetSearchModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setOnSearchSubmitExtraParam(node, extraParam);
}

void SetOnSearchChange(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetSearchModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setOnSearchChangeExtraParam(node, extraParam);
}

void SetOnSearchCopy(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetSearchModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setOnSearchCopyExtraParam(node, extraParam);
}

void SetOnSearchCut(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetSearchModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setOnSearchCutExtraParam(node, extraParam);
}

void SetOnSearchPaste(ArkUINodeHandle node, void* extraParam)
{
    CHECK_NULL_VOID(node);
    auto modifier = GetSearchModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setOnSearchPasteExtraParam(node, extraParam);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
