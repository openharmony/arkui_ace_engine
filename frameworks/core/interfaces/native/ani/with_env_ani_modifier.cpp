/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "with_env_ani_modifier.h"

#include <any>
#include <optional>
#include <utility>

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/syntax/with_env_node.h"
#include "core/pipeline_ng/environment_manager.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr ArkUI_Int32 FRONTEND_DIRECTION_LTR = 0;
constexpr ArkUI_Int32 FRONTEND_DIRECTION_RTL = 1;
constexpr ArkUI_Int32 FRONTEND_DIRECTION_AUTO = 2;

RefPtr<UINode> GetUINode(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    return AceType::Claim(reinterpret_cast<UINode*>(node));
}

RefPtr<WithEnvNode> GetWithEnvNode(ArkUINodeHandle node)
{
    return AceType::DynamicCast<WithEnvNode>(GetUINode(node));
}

PipelineContext* GetPipelineContext(const RefPtr<UINode>& node)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    if (pipeline) {
        return pipeline.GetRawPtr();
    }
    CHECK_NULL_RETURN(node, nullptr);
    return node->GetContext();
}

RefPtr<EnvironmentManager> GetEnvironmentManager(const RefPtr<UINode>& node)
{
    auto* pipeline = GetPipelineContext(node);
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetEnvironmentManager();
}

std::optional<TextDirection> ConvertDirection(ArkUI_Int32 value)
{
    switch (value) {
        case FRONTEND_DIRECTION_LTR:
            return TextDirection::LTR;
        case FRONTEND_DIRECTION_RTL:
            return TextDirection::RTL;
        case FRONTEND_DIRECTION_AUTO:
            return TextDirection::AUTO;
        default:
            return std::nullopt;
    }
}

std::optional<double> ConvertDirectionToFrontendValue(TextDirection value)
{
    switch (value) {
        case TextDirection::LTR:
            return FRONTEND_DIRECTION_LTR;
        case TextDirection::RTL:
            return FRONTEND_DIRECTION_RTL;
        case TextDirection::AUTO:
            return FRONTEND_DIRECTION_AUTO;
        default:
            return std::nullopt;
    }
}

void FillCustomQueryResult(const std::any* value, ArkUIAniEnvironmentQueryResult& outResult)
{
    outResult = {};
    CHECK_NULL_VOID(value);
    outResult.type = ARKUI_ANI_ENV_VALUE_TYPE_CUSTOM;
    outResult.customValue = *value;
}

bool FillSystemQueryResult(const SystemEnvValue* value, ArkUIAniEnvironmentQueryResult& outResult)
{
    outResult = {};
    CHECK_NULL_RETURN(value, false);
    if (auto direction = value->GetDirection()) {
        auto frontendValue = ConvertDirectionToFrontendValue(*direction);
        CHECK_NULL_RETURN(frontendValue, false);
        outResult.type = ARKUI_ANI_ENV_VALUE_TYPE_NUMBER;
        outResult.numberValue = *frontendValue;
        return true;
    }
    if (auto fontScale = value->GetDouble()) {
        outResult.type = ARKUI_ANI_ENV_VALUE_TYPE_NUMBER;
        outResult.numberValue = *fontScale;
        return true;
    }
    return false;
}
} // namespace

ArkUINodeHandle ConstructWithEnv(ArkUI_Int32 id)
{
    auto withEnvNode = WithEnvNode::GetOrCreateWithEnvNode(id);
    CHECK_NULL_RETURN(withEnvNode, nullptr);
    withEnvNode->IncRefCount();
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    if (pipeline) {
        pipeline->SetUseEnvManager(true);
    }
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(withEnvNode));
}

void RemoveSystemEnvProperty(ArkUINodeHandle node, const std::string& key)
{
    auto withEnvNode = GetWithEnvNode(node);
    CHECK_NULL_VOID(withEnvNode);
    auto envManager = GetEnvironmentManager(withEnvNode);
    if (envManager && envManager->RemoveSystemEnvValue(withEnvNode, key)) {
        return;
    }
    withEnvNode->RemoveSystemEnvProperty(key);
}

void SetSystemEnvProperty(ArkUINodeHandle node, const std::string& key, double value)
{
    auto withEnvNode = GetWithEnvNode(node);
    CHECK_NULL_VOID(withEnvNode);
    SystemEnvValue envValue;
    if (key == ENV_KEY_DIRECTION) {
        auto directionValue = static_cast<ArkUI_Int32>(value);
        if (static_cast<double>(directionValue) != value) {
            return;
        }
        auto direction = ConvertDirection(directionValue);
        CHECK_NULL_VOID(direction);
        envValue = SystemEnvValue::FromDirection(*direction);
    } else if (key == ENV_KEY_FONT_SCALE) {
        envValue = SystemEnvValue::FromDouble(value);
    } else {
        return;
    }
    auto envManager = GetEnvironmentManager(withEnvNode);
    if (envManager && envManager->SetSystemEnvValue(withEnvNode, key, envValue)) {
        return;
    }
    withEnvNode->SetSystemEnvProperty(key, envValue);
}

void RemoveCustomEnvProperty(ArkUINodeHandle node, const std::string& key)
{
    auto withEnvNode = GetWithEnvNode(node);
    CHECK_NULL_VOID(withEnvNode);
    auto envManager = GetEnvironmentManager(withEnvNode);
    if (envManager && envManager->RemoveCustomEnvValue(withEnvNode, key)) {
        return;
    }
    withEnvNode->RemoveCustomEnvProperty(key);
}

void SetCustomEnvProperty(ArkUINodeHandle node, const std::string& key, std::any value)
{
    auto withEnvNode = GetWithEnvNode(node);
    CHECK_NULL_VOID(withEnvNode);
    auto envManager = GetEnvironmentManager(withEnvNode);
    if (envManager && envManager->SetCustomEnvValue(withEnvNode, key, value)) {
        return;
    }
    withEnvNode->SetCustomEnvProperty(key, std::move(value));
}

bool FindCustomEnvValueByKey(ArkUINodeHandle node, const std::string& key, ArkUIAniEnvironmentQueryResult& outResult)
{
    auto uiNode = GetUINode(node);
    CHECK_NULL_RETURN(uiNode, false);
    auto envManager = GetEnvironmentManager(uiNode);
    CHECK_NULL_RETURN(envManager, false);
    std::any value;
    if (!envManager->FindCustomEnvValueByKey(uiNode, key, value)) {
        return false;
    }
    FillCustomQueryResult(&value, outResult);
    return true;
}

bool FindSystemEnvValueByKey(ArkUINodeHandle node, const std::string& key, ArkUIAniEnvironmentQueryResult& outResult)
{
    auto uiNode = GetUINode(node);
    CHECK_NULL_RETURN(uiNode, false);
    auto envManager = GetEnvironmentManager(uiNode);
    CHECK_NULL_RETURN(envManager, false);
    SystemEnvValue value;
    if (!envManager->FindSystemEnvValueByKey(uiNode, key, value)) {
        return false;
    }
    return FillSystemQueryResult(&value, outResult);
}

void SetOnCustomEnvUpdate(ArkUINodeHandle node, ArkUIAniEnvironmentUpdateCallback&& callback)
{
    auto customNode = AceType::DynamicCast<CustomNode>(GetUINode(node));
    CHECK_NULL_VOID(customNode);
    customNode->SetOnCustomEnvUpdateFunc(
        [callback = std::move(callback)](const std::string& key, const std::optional<std::any>& value) {
            if (!callback) {
                return;
            }
            std::optional<ArkUIAniEnvironmentQueryResult> result;
            if (value) {
                ArkUIAniEnvironmentQueryResult converted;
                FillCustomQueryResult(&(*value), converted);
                result.emplace(std::move(converted));
            }
            callback(key, result);
        });
}

void SetOnSystemEnvUpdate(ArkUINodeHandle node, ArkUIAniEnvironmentUpdateCallback&& callback)
{
    auto customNode = AceType::DynamicCast<CustomNode>(GetUINode(node));
    CHECK_NULL_VOID(customNode);
    customNode->SetOnSystemEnvUpdateFunc(
        [callback = std::move(callback)](const std::string& key, const std::optional<SystemEnvValue>& value) {
            if (!callback) {
                return;
            }
            std::optional<ArkUIAniEnvironmentQueryResult> result;
            if (value) {
                ArkUIAniEnvironmentQueryResult converted;
                if (FillSystemQueryResult(&(*value), converted)) {
                    result.emplace(std::move(converted));
                }
            }
            callback(key, result);
        });
}

const ArkUIAniWithEnvModifier* GetArkUIAniWithEnvModifier()
{
    static const ArkUIAniWithEnvModifier impl = {
        .construct = ConstructWithEnv,
        .removeSystemEnvProperty = RemoveSystemEnvProperty,
        .setSystemEnvProperty = SetSystemEnvProperty,
        .removeCustomEnvProperty = RemoveCustomEnvProperty,
        .setCustomEnvProperty = SetCustomEnvProperty,
        .findCustomEnvValueByKey = FindCustomEnvValueByKey,
        .findSystemEnvValueByKey = FindSystemEnvValueByKey,
        .setOnCustomEnvUpdate = SetOnCustomEnvUpdate,
        .setOnSystemEnvUpdate = SetOnSystemEnvUpdate,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
