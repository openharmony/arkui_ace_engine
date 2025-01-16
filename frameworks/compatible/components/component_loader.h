/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_COMPONENT_LOADER
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_COMPONENT_LOADER

#include <cstdint>
#include "base/memory/referenced.h"

namespace OHOS::Ace {

class Declaration;
class PipelineBase;

namespace Framework {
class DOMNode;
class JsCommand;
}

namespace V2 {
class InspectorComposedElement;
}

struct CanvasBridgeParams {
    RefPtr<PipelineBase> pipeline;
    int32_t width;
    int32_t height;
    bool isOffscreen;
};

class ComponentLoader {
public:
    ComponentLoader() = default;
    virtual ~ComponentLoader() = default;

    virtual RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) = 0;
    virtual void* CreateModel() = 0;
    virtual RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) = 0;
    virtual RefPtr<Declaration> CreateDeclaration()
    {
        return nullptr;
    }
    virtual void UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config) {}

    static ComponentLoader* GetLoaderByName(const char* name);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_COMPONENT_LOADER
