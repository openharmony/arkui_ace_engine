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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_LOADER_H

#include "compatible/components/component_loader.h"

namespace OHOS::Ace {
class SvgLoader : public ComponentLoader {
public:
    SvgLoader() = default;
    ~SvgLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
    const void* GetCustomModifier(const std::string& tag = "") override;
};

class SvgAnimateLoader : public ComponentLoader {
public:
    SvgAnimateLoader() = default;
    ~SvgAnimateLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgAnimateMotionLoader : public ComponentLoader {
public:
    SvgAnimateMotionLoader() = default;
    ~SvgAnimateMotionLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgAnimateTransformLoader : public ComponentLoader {
public:
    SvgAnimateTransformLoader() = default;
    ~SvgAnimateTransformLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgCircleLoader : public ComponentLoader {
public:
    SvgCircleLoader() = default;
    ~SvgCircleLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgDefsLoader : public ComponentLoader {
public:
    SvgDefsLoader() = default;
    ~SvgDefsLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgEllipseLoader : public ComponentLoader {
public:
    SvgEllipseLoader() = default;
    ~SvgEllipseLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgFeColorMatrixLoader : public ComponentLoader {
public:
    SvgFeColorMatrixLoader() = default;
    ~SvgFeColorMatrixLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgFeCompositeLoader : public ComponentLoader {
public:
    SvgFeCompositeLoader() = default;
    ~SvgFeCompositeLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgFeGaussianBlurLoader : public ComponentLoader {
public:
    SvgFeGaussianBlurLoader() = default;
    ~SvgFeGaussianBlurLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgFeOffsetLoader : public ComponentLoader {
public:
    SvgFeOffsetLoader() = default;
    ~SvgFeOffsetLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgFilterLoader : public ComponentLoader {
public:
    SvgFilterLoader() = default;
    ~SvgFilterLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgGLoader : public ComponentLoader {
public:
    SvgGLoader() = default;
    ~SvgGLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgLineLoader : public ComponentLoader {
public:
    SvgLineLoader() = default;
    ~SvgLineLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgMaskLoader : public ComponentLoader {
public:
    SvgMaskLoader() = default;
    ~SvgMaskLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgPathLoader : public ComponentLoader {
public:
    SvgPathLoader() = default;
    ~SvgPathLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgPolygonLoader : public ComponentLoader {
public:
    SvgPolygonLoader() = default;
    ~SvgPolygonLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgPolylineLoader : public ComponentLoader {
public:
    SvgPolylineLoader() = default;
    ~SvgPolylineLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgRectLoader : public ComponentLoader {
public:
    SvgRectLoader() = default;
    ~SvgRectLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgTextLoader : public ComponentLoader {
public:
    SvgTextLoader() = default;
    ~SvgTextLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgTextPathLoader : public ComponentLoader {
public:
    SvgTextPathLoader() = default;
    ~SvgTextPathLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgTspanLoader : public ComponentLoader {
public:
    SvgTspanLoader() = default;
    ~SvgTspanLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgUseLoader : public ComponentLoader {
public:
    SvgUseLoader() = default;
    ~SvgUseLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgGradientLoader : public ComponentLoader {
public:
    SvgGradientLoader() = default;
    ~SvgGradientLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};

class SvgStopLoader : public ComponentLoader {
public:
    SvgStopLoader() = default;
    ~SvgStopLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
    RefPtr<Declaration> CreateDeclaration() override;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SVG_LOADER_H