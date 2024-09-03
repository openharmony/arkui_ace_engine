/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/customdialog_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {

const std::unordered_map<std::string, std::function<std::string(const CustomDialogComposedElement &)>> CREATE_JSON_MAP {
    {"open", [](const CustomDialogComposedElement &inspector) { return inspector.Open(); }}
    };

void CustomDialogComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("open: ").append(Open()));
}

std::unique_ptr<JsonValue> CustomDialogComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto &value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

RefPtr<RenderDialog> CustomDialogComposedElement::GetRenderDialog() const
{
    auto node = GetInspectorNode(DialogElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderDialog>(node);
    }
    return nullptr;
}

std::string CustomDialogComposedElement::Open() const
{
    auto jsonArray = JsonUtil::CreateArray(true);
    auto item = JsonUtil::Create(true);
    item->Put("autoCancel", GetAutoCancel().c_str());
    item->Put("alignment", GetAlignment().c_str());
    item->Put("offset", GetDialogOffset());
    item->Put("customstyle", GetCustomStyle().c_str());
    jsonArray->Put(item);
    return jsonArray->ToString();
}

std::string CustomDialogComposedElement::GetAutoCancel() const
{
    auto renderDialog = GetRenderDialog();
    if (renderDialog) {
        return ConvertBoolToString(renderDialog->GetDialogProperties().autoCancel);
    }
    return "true";
}

std::string CustomDialogComposedElement::GetAlignment() const
{
    auto renderDialog = GetRenderDialog();
    auto Alignment = renderDialog ? renderDialog->GetDialogProperties().alignment : DialogAlignment::DEFAULT;
    return DialogAlignmentUtils::ConvertDialogAlignmentToString(Alignment);
}

std::unique_ptr<JsonValue> CustomDialogComposedElement::GetDialogOffset() const
{
    auto renderDialog = GetRenderDialog();
    auto dialogOffset = renderDialog->GetDialogProperties().offset;
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("dX", dialogOffset.GetX().Value());
    jsonValue->Put("dY", dialogOffset.GetY().Value());
    return jsonValue;
}

std::string CustomDialogComposedElement::GetCustomStyle() const
{
    auto renderDialog = GetRenderDialog();
    if (renderDialog) {
        return ConvertBoolToString(renderDialog->GetDialogProperties().customStyle);
    }
    return "false";
}

} // namespace OHOS::Ace::V2