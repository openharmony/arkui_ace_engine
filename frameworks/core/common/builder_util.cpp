/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/common/builder_util.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::BuilderUtils {

    void GetBuilderNodes(const RefPtr<NG::UINode>& node, std::list<RefPtr<NG::UINode>>& nodes)
    {
        CHECK_NULL_VOID(node);
        if (node->GetIsRootBuilderNode()) {
            nodes.push_back(node);
        } else {
            GetFirstBuilderNode(node, nodes);
        }
    }

    bool IsBuilderContainer(const RefPtr<NG::UINode>& node)
    {
        CHECK_NULL_RETURN(node, false);
        return node->GetTag() == V2::NODE_CONTAINER_ETS_TAG ||
            node->GetTag() == V2::JS_NODE_SLOT_ETS_TAG;
    }

    bool HasParentView(const RefPtr<NG::UINode>& node)
    {
        CHECK_NULL_RETURN(node, false);
        auto context = node->GetContext();
        CHECK_NULL_RETURN(context, false);
        auto frontend = context->GetFrontend();
        CHECK_NULL_RETURN(frontend, false);
        std::vector<int32_t> argv = { node->GetId() };
        auto flag = frontend->BuilderNodeFunc("__hasParentView__", argv);
        return flag;
    }

    void AddBuilderToContainer(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes)
    {
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        auto frontend = context->GetFrontend();
        CHECK_NULL_VOID(frontend);
        std::vector<int32_t> argv = { node->GetId() };
        for (const auto& child : nodes) {
            argv.push_back(child->GetId());
        }
        frontend->BuilderNodeFunc("__addBuilderNode__", argv);
    }

    void AddBuilderToBuilder(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes)
    {
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        auto frontend = context->GetFrontend();
        CHECK_NULL_VOID(frontend);
        std::vector<int32_t> argv = { node->GetId() };
        for (const auto& child : nodes) {
            argv.push_back(child->GetId());
        }
        frontend->BuilderNodeFunc("__addBuilderNodeToBuilder__", argv);
    }

    void RemoveBuilderFromContainer(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes)
    {
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        auto frontend = context->GetFrontend();
        CHECK_NULL_VOID(frontend);
        std::vector<int32_t> argv = { node->GetId() };
        for (const auto& child : nodes) {
            argv.push_back(child->GetId());
        }
        frontend->BuilderNodeFunc("__deleteBuilderNode__", argv);
    }

    void RemoveBuilderFromBuilder(const RefPtr<NG::UINode>& node, const std::list<RefPtr<NG::UINode>>& nodes)
    {
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        auto frontend = context->GetFrontend();
        CHECK_NULL_VOID(frontend);
        std::vector<int32_t> argv = { node->GetId() };
        for (const auto& child : nodes) {
            argv.push_back(child->GetId());
        }
        frontend->BuilderNodeFunc("__deleteBuilderNodeFromBuilder__", argv);
    }

    void ClearBuilderFromContainer(const RefPtr<NG::UINode>& node)
    {
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        auto frontend = context->GetFrontend();
        CHECK_NULL_VOID(frontend);
        std::vector<int32_t> argv = { node->GetId() };
        frontend->BuilderNodeFunc("__clearBuilderNodes__", argv);
    }

    void ClearBuilderFromBuilder(const RefPtr<NG::UINode>& node)
    {
        CHECK_NULL_VOID(node);
        auto context = node->GetContext();
        CHECK_NULL_VOID(context);
        auto frontend = context->GetFrontend();
        CHECK_NULL_VOID(frontend);
        std::vector<int32_t> argv = { node->GetId() };
        frontend->BuilderNodeFunc("__clearFromBuilder__", argv);
    }

    void AddBuilderToParent(const RefPtr<NG::UINode>& node, std::list<RefPtr<NG::UINode>> nodes)
    {
        CHECK_NULL_VOID(node);
        if (nodes.empty()) {
            return;
        }
        auto parent = node->GetParent();
        while (parent) {
            if (IsBuilderContainer(parent) && HasParentView(parent)) {
                AddBuilderToContainer(parent, nodes);
                return;
            }
            if (parent->GetIsRootBuilderNode()) {
                AddBuilderToBuilder(parent, nodes);
                return;
            }
            parent = parent->GetParent();
        }
    }

    void RemoveBuilderFromParent(const RefPtr<NG::UINode>& node, std::list<RefPtr<NG::UINode>> nodes)
    {
        CHECK_NULL_VOID(node);
        if (nodes.empty()) {
            return;
        }
        auto parent = node->GetParent();
        CHECK_NULL_VOID(parent);
        while (parent) {
            if (IsBuilderContainer(parent) && HasParentView(parent)) {
                RemoveBuilderFromContainer(parent, nodes);
                return;
            }
            if (parent->GetIsRootBuilderNode()) {
                RemoveBuilderFromBuilder(parent, nodes);
                return;
            }
            parent = parent->GetParent();
        }
    }

    void ClearBuilder(const RefPtr<NG::UINode>& node)
    {
        CHECK_NULL_VOID(node);
        auto parent = node;
        while (parent) {
            if (IsBuilderContainer(parent) && HasParentView(parent)) {
                ClearBuilderFromContainer(parent);
                return;
            }
            if (parent->GetIsRootBuilderNode()) {
                ClearBuilderFromBuilder(parent);
                return;
            }
            parent = parent->GetParent();
        }
    }

    void GetFirstBuilderNode(const RefPtr<NG::UINode>& node, std::list<RefPtr<NG::UINode>>& nodes)
    {
        CHECK_NULL_VOID(node);
        std::stack<RefPtr<NG::UINode>> nodeStack;
        auto children = node->GetChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            nodeStack.push(*it);
        }
        while (!nodeStack.empty()) {
            auto currentNode = nodeStack.top();
            nodeStack.pop();
            if (currentNode->GetIsRootBuilderNode()) {
                nodes.push_back(currentNode);
                continue;
            }
            if (currentNode->GetTag() == V2::NODE_CONTAINER_ETS_TAG ||
                currentNode->GetTag() == V2::JS_NODE_SLOT_ETS_TAG) {
                continue;
            }
            auto currentChildren = currentNode->GetChildren();
            for (auto it = currentChildren.rbegin(); it != currentChildren.rend(); ++it) {
                nodeStack.push(*it);
            }
        }
    }

}