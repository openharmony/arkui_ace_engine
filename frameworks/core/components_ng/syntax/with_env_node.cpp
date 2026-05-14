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
#include "core/pipeline/base/element_register.h"

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

void WithEnvNode::SetEnvProperty(const std::string& key, const std::string& value)
{
    envPropertiesStringType_[key] = value;
}

void WithEnvNode::SetEnvProperty(const std::string& key, double value)
{
    envPropertiesDoubleType_[key] = value;
}

void WithEnvNode::SetEnvProperty(const std::string& key, bool value)
{
    envPropertiesBoolType_[key] = value;
}

void WithEnvNode::SetCustomEnvProperty(const std::string& key, std::any value)
{
    customEnvObjProperties_[key] = std::move(value);
}

bool WithEnvNode::GetEnvProperty(const std::string& key, std::string& value) const
{
    auto it = envPropertiesStringType_.find(key);
    if (it == envPropertiesStringType_.end()) {
        return false;
    }
    value = it->second;
    return true;
}

bool WithEnvNode::GetEnvProperty(const std::string& key, double& value) const
{
    auto it = envPropertiesDoubleType_.find(key);
    if (it == envPropertiesDoubleType_.end()) {
        return false;
    }
    value = it->second;
    return true;
}

bool WithEnvNode::GetEnvProperty(const std::string& key, bool& value) const
{
    auto it = envPropertiesBoolType_.find(key);
    if (it == envPropertiesBoolType_.end()) {
        return false;
    }
    value = it->second;
    return true;
}

const std::any* WithEnvNode::GetCustomEnvPropertyAny(const std::string& key) const
{
    auto it = customEnvObjProperties_.find(key);
    if (it != customEnvObjProperties_.end()) {
        return &(it->second);
    }
    return nullptr;
}

bool WithEnvNode::HasEnvProperty(const std::string& key) const
{
    return envPropertiesStringType_.count(key) > 0 || envPropertiesDoubleType_.count(key) > 0
        || envPropertiesBoolType_.count(key) > 0 || customEnvObjProperties_.count(key) > 0;
}

} // namespace OHOS::Ace::NG
