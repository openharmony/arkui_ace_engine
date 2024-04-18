/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_ITEM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_ITEM_H

#include <cstdint>
#include <string>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

// Syntax nodes are used for ForEach, LazyForEach, and IfElse nodes to wrap up the generated sub components and are
// uniquely identified by keys.
class ACE_EXPORT SyntaxItem : public UINode {
    DECLARE_ACE_TYPE(SyntaxItem, UINode);

public:
    explicit SyntaxItem(const std::string& key)
        : UINode(V2::JS_SYNTAX_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId()), key_(key)
    {}
    ~SyntaxItem() override
    {
        SetRemoveSilently(true);
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    const std::string& GetKey() const
    {
        return key_;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        UINode::ToJsonValue(json, filter);
        json->PutExtAttr("key", key_.c_str(), filter);
    }

    void FromJson(const std::unique_ptr<JsonValue>& json) override
    {
        UINode::FromJson(json);
    }

    static RefPtr<SyntaxItem> CreateSyntaxItemNode(const std::string& key)
    {
        auto node = AceType::MakeRefPtr<SyntaxItem>(key);
        ElementRegister::GetInstance()->AddUINode(node);
        return node;
    }

private:
    std::string key_;

    ACE_DISALLOW_COPY_AND_MOVE(SyntaxItem);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_ITEM_H
