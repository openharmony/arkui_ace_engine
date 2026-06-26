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

#include "core/components_ng/syntax/with_env_node.h"

#include "core/components/common/layout/constants.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components_ng/animation/geometry_transition.h"

namespace OHOS::Ace::NG {

WithEnvNode::~WithEnvNode() = default;

RefPtr<WithEnvNode> WithEnvNode::GetWithEnvNode(int32_t nodeId)
{
    return ElementRegister::GetInstance()->GetSpecificItemById<WithEnvNode>(nodeId);
}

RefPtr<WithEnvNode> WithEnvNode::CreateWithEnvNode(int32_t nodeId)
{
    auto node = MakeRefPtr<WithEnvNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(node);
    return node;
}

RefPtr<WithEnvNode> WithEnvNode::GetOrCreateWithEnvNode(int32_t nodeId)
{
    auto node = WithEnvNode::GetWithEnvNode(nodeId);
    if (node) {
        return node;
    }
    return WithEnvNode::CreateWithEnvNode(nodeId);
}

void WithEnvNode::SetCustomEnvProperty(const std::string& key, std::any value)
{
    customEnvObjProperties_[key] = std::move(value);
}

void WithEnvNode::RemoveCustomEnvProperty(const std::string& key)
{
    customEnvObjProperties_.erase(key);
}

std::optional<std::any> WithEnvNode::GetCustomEnvPropertyAny(const std::string& key) const
{
    auto it = customEnvObjProperties_.find(key);
    if (it != customEnvObjProperties_.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool WithEnvNode::HasCustomEnvProperty(const std::string& key) const
{
    return customEnvObjProperties_.count(key) > 0;
}

void WithEnvNode::RemoveSystemEnvProperty(const std::string& key)
{
    systemEnvProperties_.erase(key);
}

bool WithEnvNode::SetSystemEnvProperty(const std::string& key, SystemEnvValue property)
{
    if (key == ENV_KEY_DIRECTION && property.GetDirection()) {
        systemEnvProperties_[key] = property;
        return true;
    }
    if (key == ENV_KEY_FONT_SCALE && property.GetDouble()) {
        systemEnvProperties_[key] = property;
        return true;
    }
    return false;
}

std::optional<SystemEnvValue> WithEnvNode::GetSystemEnvProperty(const std::string& key) const
{
    auto iter = systemEnvProperties_.find(key);
    if (iter == systemEnvProperties_.end()) {
        return std::nullopt;
    }
    return iter->second;
}

bool WithEnvNode::HasSystemEnvProperty(const std::string& key) const
{
    return systemEnvProperties_.count(key) > 0;
}

} // namespace OHOS::Ace::NG
