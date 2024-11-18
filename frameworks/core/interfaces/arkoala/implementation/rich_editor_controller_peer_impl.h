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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_CONTROLLER_PEER_IMPL_H

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"

#include "rich_editor_controller_structs.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_controller.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class RichEditorControllerPeerImpl : public Referenced {
public:
    RichEditorControllerPeerImpl() = default;

    void AddTargetController(const WeakPtr<RichEditorController> &handler)
    {
        handler_ = handler;
    }

    int32_t AddTextSpanImpl(const TextSpanOptions& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            result = controller->AddTextSpan(options);
        }
        return result;
    }

    int32_t AddImageSpanImpl(const ImageSpanOptions& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            result = controller->AddImageSpan(options);
        }
        return result;
    }

    int32_t AddBuilderSpanImpl(const SpanOptionBase& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId(); // May be incorrect way
            auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
            result = controller->AddPlaceholderSpan(spanNode, options);
        }
        return result;
    }

    int32_t AddSymbolSpanImpl(const SymbolSpanOptions& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            result = controller->AddSymbolSpan(options);
        }
        return result;
    }

    void UpdateSpanStyleImpl(const Converter::TextSpanOptionsForUpdate& options)
    {
        if (auto controller = handler_.Upgrade(); controller && options.textStyle) {
            controller->UpdateSpanStyle(
                options.start, options.end, options.textStyle.value(), options.imageSpanAttribute);
        }
    }

    void UpdateParagraphStyleImpl(const Converter::UpdateParagraphStyleForUpdate& options)
    {
        if (auto controller = handler_.Upgrade(); controller && options.style) {
            controller->UpdateParagraphStyle(options.start, options.end, options.style.value());
        }
    }

    void DeleteSpansImpl(const RangeOptions& options)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            controller->DeleteSpans(options);
        }
    }

    void GetSpansImpl(const RangeOptions& options)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto start = options.start.value_or(0);
            auto end = options.end.value_or(0);
            controller->GetSpansInfo(start, end);
        }
    }

    Ark_NativePointer GetSelectionImpl()
    {
        Ark_NativePointer ret = nullptr;
        if (auto controller = handler_.Upgrade(); controller) {
            selectionSpanInfo_ = controller->GetSelectionSpansInfo();
            ret = reinterpret_cast<Ark_NativePointer>(&selectionSpanInfo_);
        }
        return ret;
    }

    std::vector<ParagraphInfo> GetParagraphsImpl(const RangeOptions& options)
    {
        std::vector<ParagraphInfo> ret;
        if (auto controller = handler_.Upgrade(); controller) {
            auto start = options.start.value_or(0);
            auto end = options.end.value_or(0);
            ret = controller->GetParagraphsInfo(start, end);
        }
        return ret;
    }

    void FromStyledStringImpl(RefPtr<SpanStringBase> value)
    {
        if (auto controller = handler_.Upgrade(); controller && value) {
            controller->FromStyledString(value);
        }
    }

    RefPtr<SpanStringBase> ToStyledStringImpl(const RangeOptions& options)
    {
        RefPtr<SpanStringBase> ret;
        if (auto controller = handler_.Upgrade(); controller) {
            auto start = options.start.value_or(0);
            auto end = options.end.value_or(0);
            ret = controller->ToStyledString(start, end);
        }
        return ret;
    }

private:
    Ace::WeakPtr<RichEditorController> handler_;
    SelectionInfo selectionSpanInfo_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_CONTROLLER_PEER_IMPL_H