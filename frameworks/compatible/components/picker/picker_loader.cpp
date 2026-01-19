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

#include "compatible/components/picker/picker_loader.h"

#include "compatible/components/picker/date_picker_composed_element.h"
#include "compatible/components/picker/date_picker_dialog_composed_element.h"
#include "compatible/components/picker/dom_picker_base.h"
#include "compatible/components/picker/dom_picker_dialog.h"
#include "compatible/components/picker/picker_model_impl.h"
#include "compatible/components/picker/picker_text_dialog_composed_element.h"
#include "compatible/components/picker/text_picker_composed_element.h"
#include "compatible/components/picker/textpicker_model_impl.h"
#include "compatible/components/picker/time_picker_composed_element.h"
#include "compatible/components/picker/time_picker_dialog_composed_element.h"
#include "compatible/components/picker/timepicker_model_impl.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"

namespace OHOS::Ace {
RefPtr<Framework::DOMNode> PickerLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
#ifndef WEARABLE_PRODUCT
    return AceType::MakeRefPtr<Framework::DOMPickerDialog>(nodeId, nodeName);
#else
    return nullptr;
#endif
}

void* PickerLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> PickerLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Framework::DOMNode> DatePickerLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPickerBase>(nodeId, nodeName, true);
}

void* DatePickerLoader::CreateModel()
{
    return new Framework::DatePickerModelImpl();
}

RefPtr<V2::InspectorComposedElement> DatePickerLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::DatePickerComposedElement>(id);
}

RefPtr<Framework::DOMNode> DatePickerDialogLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPickerBase>(nodeId, nodeName, true);
}

void* DatePickerDialogLoader::CreateModel()
{
    return new Framework::DatePickerDialogModelImpl();
}

RefPtr<V2::InspectorComposedElement> DatePickerDialogLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::DatePickerDialogComposedElement>(id);
}

RefPtr<Framework::DOMNode> TimePickerLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPickerBase>(nodeId, nodeName, true);
}

void* TimePickerLoader::CreateModel()
{
    return new Framework::TimePickerModelImpl();
}

RefPtr<V2::InspectorComposedElement> TimePickerLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TimePickerComposedElement>(id);
}

RefPtr<Framework::DOMNode> TimePickerDialogLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPickerBase>(nodeId, nodeName, true);
}

void* TimePickerDialogLoader::CreateModel()
{
    return new Framework::TimePickerDialogModelImpl();
}

RefPtr<V2::InspectorComposedElement> TimePickerDialogLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TimePickerDialogComposedElement>(id);
}

RefPtr<Framework::DOMNode> TextPickerLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPickerBase>(nodeId, nodeName, true);
}

void* TextPickerLoader::CreateModel()
{
    return new Framework::TextPickerModelImpl();
}

RefPtr<V2::InspectorComposedElement> TextPickerLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TextPickerComposedElement>(id);
}

RefPtr<Framework::DOMNode> TextPickerDialogLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMPickerBase>(nodeId, nodeName, true);
}

void* TextPickerDialogLoader::CreateModel()
{
    return new Framework::TextPickerDialogModelImpl();
}

RefPtr<V2::InspectorComposedElement> TextPickerDialogLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::PickerTextDialogComposedElement>(id);
}
} // namespace OHOS::Ace