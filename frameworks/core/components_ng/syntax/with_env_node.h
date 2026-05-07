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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_ENV_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_ENV_NODE_H

#include <any>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT WithEnvNode : public UINode {
    DECLARE_ACE_TYPE(WithEnvNode, UINode);

public:
    static RefPtr<WithEnvNode> GetWithEnvNode(int32_t nodeId);
    static RefPtr<WithEnvNode> CreateWithEnvNode(int32_t nodeId);
    static RefPtr<WithEnvNode> GetOrCreateWithEnvNode(int32_t nodeId);

    explicit WithEnvNode(int32_t nodeId) : UINode(V2::JS_WITH_ENV_ETS_TAG, nodeId) {}
    ~WithEnvNode() override;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsSyntaxNode() const override
    {
        return true;
    }

    void SetEnvProperty(const std::string& key, const std::string& value);
    void SetEnvProperty(const std::string& key, double value);
    void SetEnvProperty(const std::string& key, bool value);
    void SetCustomEnvProperty(const std::string& key, std::any value);

    bool GetEnvProperty(const std::string& key, std::string& value) const;
    bool GetEnvProperty(const std::string& key, double& value) const;
    bool GetEnvProperty(const std::string& key, bool& value) const;
    const std::any* GetCustomEnvPropertyAny(const std::string& key) const;
    bool HasEnvProperty(const std::string& key) const;


private:
    std::unordered_map<std::string, std::string> envPropertiesStringType_;
    std::unordered_map<std::string, double> envPropertiesDoubleType_;
    std::unordered_map<std::string, bool> envPropertiesBoolType_;
    std::unordered_map<std::string, std::any> customEnvObjProperties_;

    ACE_DISALLOW_COPY_AND_MOVE(WithEnvNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_WITH_ENV_NODE_H
