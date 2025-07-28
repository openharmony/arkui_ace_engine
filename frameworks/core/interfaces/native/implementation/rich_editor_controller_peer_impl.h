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
#include "core/interfaces/native/implementation/rich_editor_base_controller_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class RichEditorControllerPeerImpl : public RichEditorBaseControllerPeer {
public:
    RichEditorControllerPeerImpl() = default;

    int32_t AddTextSpanImpl(const TextSpanOptions& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, result);
            result = richEditorController->AddTextSpan(options);
        }
        return result;
    }

    int32_t AddImageSpanImpl(const ImageSpanOptions& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, result);
            result = richEditorController->AddImageSpan(options);
        }
        return result;
    }

    int32_t AddBuilderSpanImpl(const SpanOptionBase& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId(); // May be incorrect way
            auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, result);
            result = richEditorController->AddPlaceholderSpan(spanNode, options);
        }
        return result;
    }

    int32_t AddBuilderSpanImpl(RefPtr<UINode> spanNode, const SpanOptionBase& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, result);
            result = richEditorController->AddPlaceholderSpan(spanNode, options);
        }
        return result;
    }

    int32_t AddSymbolSpanImpl(const SymbolSpanOptions& options)
    {
        int32_t result = 0;
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, result);
            result = richEditorController->AddSymbolSpan(options);
        }
        return result;
    }

    void UpdateSpanStyleImpl(const Converter::TextSpanOptionsForUpdate& options)
    {
        if (auto controller = handler_.Upgrade(); controller && options.textStyle) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_VOID(richEditorController);
            richEditorController->UpdateSpanStyle(
                options.start, options.end, options.textStyle.value(), options.imageSpanAttribute);
        }
    }

    void UpdateParagraphStyleImpl(const Converter::UpdateParagraphStyleForUpdate& options)
    {
        if (auto controller = handler_.Upgrade(); controller && options.style) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_VOID(richEditorController);
            richEditorController->UpdateParagraphStyle(options.start, options.end, options.style.value());
        }
    }

    void DeleteSpansImpl(const RangeOptions& options)
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_VOID(richEditorController);
            richEditorController->DeleteSpans(options);
        }
    }

    SelectionInfo GetSpansImpl(const RangeOptions& options)
    {
        SelectionInfo result;
        if (auto controller = handler_.Upgrade(); controller) {
            auto start = options.start.value_or(0);
            auto end = options.end.value_or(0);
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, result);
            result = richEditorController->GetSpansInfo(start, end);
        }
        return result;
    }

    SelectionInfo GetSelectionImpl()
    {
        if (auto controller = handler_.Upgrade(); controller) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, {});
            return richEditorController->GetSelectionSpansInfo();
        }
        return {};
    }

    std::vector<ParagraphInfo> GetParagraphsImpl(const RangeOptions& options)
    {
        std::vector<ParagraphInfo> ret;
        if (auto controller = handler_.Upgrade(); controller) {
            auto start = options.start.value_or(0);
            auto end = options.end.value_or(0);
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, ret);
            ret = richEditorController->GetParagraphsInfo(start, end);
        }
        return ret;
    }

    SelectionInfo FromStyledStringImpl(RefPtr<SpanStringBase> value)
    {
        if (auto controller = handler_.Upgrade(); controller && value) {
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, {});
            return richEditorController->FromStyledString(value);
        }
        return {};
    }

    RefPtr<SpanStringBase> ToStyledStringImpl(const RangeOptions& options)
    {
        RefPtr<SpanStringBase> ret;
        if (auto controller = handler_.Upgrade(); controller) {
            auto start = options.start.value_or(0);
            auto end = options.end.value_or(0);
            auto richEditorController = AceType::DynamicCast<RichEditorControllerBase>(controller);
            CHECK_NULL_RETURN(richEditorController, ret);
            ret = richEditorController->ToStyledString(start, end);
        }
        return ret;
    }
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct RichEditorControllerPeer : public OHOS::Ace::NG::GeneratedModifier::RichEditorControllerPeerImpl {};
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_RICHEDITOR_CONTROLLER_PEER_IMPL_H
