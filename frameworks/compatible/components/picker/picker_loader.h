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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PICKER_PICKER_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PICKER_PICKER_LOADER_H

#include "compatible/components/component_loader.h"

namespace OHOS::Ace {
class PickerLoader : public ComponentLoader {
public:
    PickerLoader() = default;
    ~PickerLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};

class DatePickerLoader : public ComponentLoader {
public:
    DatePickerLoader() = default;
    ~DatePickerLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};

class DatePickerDialogLoader : public ComponentLoader {
public:
    DatePickerDialogLoader() = default;
    ~DatePickerDialogLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};

class TimePickerLoader : public ComponentLoader {
public:
    TimePickerLoader() = default;
    ~TimePickerLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};

class TimePickerDialogLoader : public ComponentLoader {
public:
    TimePickerDialogLoader() = default;
    ~TimePickerDialogLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};

class TextPickerLoader : public ComponentLoader {
public:
    TextPickerLoader() = default;
    ~TextPickerLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};

class TextPickerDialogLoader : public ComponentLoader {
public:
    TextPickerDialogLoader() = default;
    ~TextPickerDialogLoader() = default;

    RefPtr<Framework::DOMNode> CreateDomNode(int32_t nodeId, const std::string& nodeName) override;
    void* CreateModel() override;
    RefPtr<V2::InspectorComposedElement> CreateInspectorElement(const std::string& id) override;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_PICKER_PICKER_LOADER_H