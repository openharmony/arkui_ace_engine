/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_model_ng.h"

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void TextModelNG::Create(const std::string& content)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TEXT_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, content);
    // set draggable for framenode
    if (frameNode->IsFirstBuilding()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto draggable = pipeline->GetDraggable<TextTheme>();
        frameNode->SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetTextDraggable(true);
    }

    auto textPattern = frameNode->GetPattern<TextPattern>();
    textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
    textPattern->GetTextController()->SetPattern(WeakPtr(textPattern));
    textPattern->ClearSelectionMenu();
}

RefPtr<FrameNode> TextModelNG::CreateFrameNode(int32_t nodeId, const std::string& content)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TextPattern>());

    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layout = frameNode->GetLayoutProperty<TextLayoutProperty>();
    if (layout) {
        layout->UpdateContent(content);
    }
    // set draggable for framenode
    if (frameNode->IsFirstBuilding()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto draggable = pipeline->GetDraggable<TextTheme>();
        frameNode->SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, nullptr);
        gestureHub->SetTextDraggable(true);
    }

    auto textPattern = frameNode->GetPattern<TextPattern>();
    textPattern->SetTextController(AceType::MakeRefPtr<TextController>());
    textPattern->GetTextController()->SetPattern(WeakPtr(textPattern));
    textPattern->ClearSelectionMenu();
    return frameNode;
}

void TextModelNG::SetFont(const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(value.fontSize.value());
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(value.fontFamilies);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(value.fontStyle.value());
    }
}

void TextModelNG::SetFontSize(const Dimension& value)
{
    if (!value.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, Dimension());
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value);
}

void TextModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    if (!value.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, Dimension(), frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontSize, value, frameNode);
}

void TextModelNG::SetTextColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextColor, value);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, ForegroundColor, value);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColor, value);
    ACE_RESET_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy);
    ACE_UPDATE_RENDER_CONTEXT(ForegroundColorFlag, true);
}

void TextModelNG::SetTextColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextColor, value, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, ForegroundColor, value, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColor, value, frameNode);
    ACE_RESET_NODE_RENDER_CONTEXT(RenderContext, ForegroundColorStrategy, frameNode);
    ACE_UPDATE_NODE_RENDER_CONTEXT(ForegroundColorFlag, true, frameNode);
}

void TextModelNG::SetTextShadow(const std::vector<Shadow>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextShadow, value);
}

void TextModelNG::SetItalicFontStyle(Ace::FontStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, ItalicFontStyle, value);
}

void TextModelNG::SetItalicFontStyle(FrameNode* frameNode, Ace::FontStyle value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, ItalicFontStyle, value, frameNode);
}

void TextModelNG::SetFontWeight(FrameNode* frameNode, Ace::FontWeight value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, value, frameNode);
}

void TextModelNG::SetFontWeight(Ace::FontWeight value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontWeight, value);
}

void TextModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, value);
}

void TextModelNG::SetWordBreak(Ace::WordBreak value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, WordBreak, value);
}

void TextModelNG::SetEllipsisMode(EllipsisMode value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, EllipsisMode, value);
}

void TextModelNG::SetTextAlign(Ace::TextAlign value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, value);
}

void TextModelNG::SetTextAlign(FrameNode* frameNode, Ace::TextAlign value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, value, frameNode);
}

void TextModelNG::SetTextOverflow(Ace::TextOverflow value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextOverflow, value);
}

void TextModelNG::SetTextOverflow(FrameNode* frameNode, Ace::TextOverflow value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextOverflow, value, frameNode);
}

void TextModelNG::SetMaxLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, MaxLines, value);
}

void TextModelNG::SetTextIndent(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextIndent, value);
}

void TextModelNG::SetLineHeight(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, LineHeight, value);
}

void TextModelNG::SetLineHeight(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LineHeight, value, frameNode);
}

void TextModelNG::SetTextDecoration(Ace::TextDecoration value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecoration, value);
}

void TextModelNG::SetTextDecoration(FrameNode* frameNode, TextDecoration value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecoration, value, frameNode);
}

void TextModelNG::SetTextDecorationColor(const Color& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationColor, value);
}

void TextModelNG::SetTextDecorationColor(FrameNode* frameNode, const Color& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationColor, value, frameNode);
}

void TextModelNG::SetTextDecorationStyle(Ace::TextDecorationStyle value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationStyle, value);
}

void TextModelNG::SetTextDecorationStyle(FrameNode* frameNode, TextDecorationStyle value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextDecorationStyle, value, frameNode);
}

void TextModelNG::SetBaselineOffset(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, BaselineOffset, value);
}

void TextModelNG::SetTextCase(Ace::TextCase value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextCase, value);
}

void TextModelNG::SetLetterSpacing(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, LetterSpacing, value);
}

void TextModelNG::SetAdaptMinFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMinFontSize, value);
}

void TextModelNG::SetAdaptMaxFontSize(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMaxFontSize, value);
}

void TextModelNG::SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, HeightAdaptivePolicy, value);
}

void TextModelNG::SetTextDetectEnable(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->SetTextDetectEnable(value);
}

void TextModelNG::SetTextDetectConfig(const std::string& value,
    std::function<void(const std::string&)>&& onResult)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->SetTextDetectTypes(value);
    textPattern->SetOnResult(std::move(onResult));
}

void TextModelNG::SetOnClick(std::function<void(const BaseEventInfo* info)>&& click)
{
    auto clickFunc = [func = std::move(click)](GestureEvent& info) { func(&info); };
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->SetOnClickEvent(std::move(clickFunc));
}

void TextModelNG::ClearOnClick()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->SetOnClickEvent(nullptr);
}

void TextModelNG::SetRemoteMessage(std::function<void()>&& event) {}

void TextModelNG::SetCopyOption(CopyOptions copyOption)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, CopyOption, copyOption);
}

void TextModelNG::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(draggable);
}

void TextModelNG::SetMenuOptionItems(std::vector<MenuOptionsParam>&& menuOptionsItems)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    textPattern->SetMenuOptionItems(std::move(menuOptionsItems));
}

void TextModelNG::SetOnCopy(std::function<void(const std::string&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void TextModelNG::SetTextSelection(int32_t startIndex, int32_t endIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->SetTextSelection(startIndex, endIndex);
}

void TextModelNG::SetOnDragStart(NG::OnDragStartFunc&& onDragStart)
{
    auto dragStart = [dragStartFunc = std::move(onDragStart)](
                         const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        auto dragInfo = dragStartFunc(event, extraParams);
        DragDropInfo info;
        info.extraInfo = dragInfo.extraInfo;
        info.pixelMap = dragInfo.pixelMap;
        info.customNode = AceType::DynamicCast<UINode>(dragInfo.node);
        return info;
    };
    ViewAbstract::SetOnDragStart(std::move(dragStart));
}

void TextModelNG::SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter)
{
    ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
}

void TextModelNG::SetOnDragMove(NG::OnDragDropFunc&& onDragMove)
{
    ViewAbstract::SetOnDragMove(std::move(onDragMove));
}

void TextModelNG::SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave)
{
    ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
}

void TextModelNG::SetOnDrop(NG::OnDragDropFunc&& onDrop)
{
    ViewAbstract::SetOnDrop(std::move(onDrop));
}

void TextModelNG::SetTextCase(FrameNode* frameNode, Ace::TextCase value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextCase, value, frameNode);
}

void TextModelNG::SetMaxLines(FrameNode* frameNode, uint32_t value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, MaxLines, value, frameNode);
}

void TextModelNG::SetAdaptMinFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMinFontSize, value, frameNode);
}

void TextModelNG::SetDraggable(FrameNode* frameNode, bool draggable)
{
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(draggable);
}

void TextModelNG::SetAdaptMaxFontSize(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, AdaptMaxFontSize, value, frameNode);
}

void TextModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, FontFamily, value, frameNode);
}

void TextModelNG::SetCopyOption(FrameNode* frameNode, CopyOptions copyOption)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, CopyOption, copyOption, frameNode);
}

void TextModelNG::SetTextShadow(FrameNode* frameNode, const std::vector<Shadow>& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextShadow, value, frameNode);
}

void TextModelNG::SetHeightAdaptivePolicy(FrameNode* frameNode, TextHeightAdaptivePolicy value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, HeightAdaptivePolicy, value, frameNode);
}

void TextModelNG::SetTextIndent(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, TextIndent, value, frameNode);
}

void TextModelNG::SetBaselineOffset(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, BaselineOffset, value, frameNode);
}

void TextModelNG::SetFont(FrameNode* frameNode, const Font& value)
{
    if (value.fontSize.has_value()) {
        SetFontSize(frameNode, value.fontSize.value());
    }
    if (value.fontWeight.has_value()) {
        SetFontWeight(frameNode, value.fontWeight.value());
    }
    if (!value.fontFamilies.empty()) {
        SetFontFamily(frameNode, value.fontFamilies);
    }
    if (value.fontStyle.has_value()) {
        SetItalicFontStyle(frameNode, value.fontStyle.value());
    }
}

void TextModelNG::SetLetterSpacing(FrameNode* frameNode, const Dimension& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, LetterSpacing, value, frameNode);
}

void TextModelNG::BindSelectionMenu(TextSpanType& spanType, TextResponseType& responseType,
    std::function<void()>& buildFunc, SelectMenuParam& menuParam)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextPattern>();
    if (pattern) {
        pattern->BindSelectionMenu(spanType, responseType, buildFunc, menuParam.onAppear, menuParam.onDisappear);
    }
}

void TextModelNG::SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(func));
}

RefPtr<TextControllerBase> TextModelNG::GetTextController()
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTextController();
}
} // namespace OHOS::Ace::NG
