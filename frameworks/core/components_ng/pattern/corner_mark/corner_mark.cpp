/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/corner_mark/corner_mark.h"

#include "core/components/theme/corner_mark_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace {
constexpr int32_t INDEX_MIN = 0;
constexpr int32_t INDEX_MAX = 99;
} // namespace

namespace OHOS::Ace::NG {

int32_t CornerMark::ResponseShowCornerMarkEvent(const RefPtr<NG::FrameNode>& node, const std::string& command)
{
    int32_t result = RET_FAILED;
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || json->IsNull()) {
        TAG_LOGE(AceLogTag::ACE_TEXT, "Parse command json failed, command: %{public}s", command.c_str());
        return result;
    }
    auto params = json->GetValue("params");
    CHECK_NULL_RETURN(params, result);
    auto indexptr = params->GetValue("CornerMarkIndex");
    if (indexptr->IsNull()) {
        TAG_LOGE(AceLogTag::ACE_TEXT, "CornerMarkIndex is null in command: %{public}s", command.c_str());
        return result;
    }
    std::string string = "";
    if (indexptr->IsNumber()) {
        auto index = indexptr->GetInt();
        string = std::to_string(index);
        if (index < INDEX_MIN || index > INDEX_MAX) {
            TAG_LOGW(AceLogTag::ACE_TEXT, "The index of corner mark is %{public}d", index);
        }
    } else if (indexptr->IsString()) {
        string = indexptr->GetString();
    } else {
        TAG_LOGE(
            AceLogTag::ACE_TEXT, "CornerMarkIndex is neither number nor string, command: %{public}s", command.c_str());
        return result;
    }

    auto isShowptr = params->GetValue("showCornerMarkNode");
    if (isShowptr->IsNull() || !isShowptr->IsBool()) {
        return result;
    }
    auto isShow = isShowptr->GetBool();
    if (isShow) {
        if (node->GetCornerMarkNode()) {
            result = UpdateCornerMarkNode(node, string);
        } else {
            result = AddCornerMarkNode(node, string);
        }
    } else {
        result = RemoveCornerMarkNode(node);
    }
    return result;
}

int32_t CornerMark::AddCornerMarkNode(const RefPtr<NG::FrameNode>& node, const std::string& index)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(frameNode, RET_FAILED);
    auto textRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(textRenderContext, RET_FAILED);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, RET_FAILED);
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, RET_FAILED);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, RET_FAILED);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(context, RET_FAILED);
    auto cornerMarkTheme = pipelineContext->GetTheme<CornerMarkTheme>();
    CHECK_NULL_RETURN(cornerMarkTheme, RET_FAILED);
    RectF rect(0.0f, 0.0f, cornerMarkTheme->GetWidth().ConvertToPx(), cornerMarkTheme->GetHeight().ConvertToPx());
    auto geometryNode = node->GetGeometryNode();
    if (AceApplicationInfo::GetInstance().IsRightToLeft() && geometryNode) {
        rect.SetLeft(geometryNode->GetFrameRect().Width() - cornerMarkTheme->GetWidth().ConvertToPx());
    }
    textLayoutProperty->SetLayoutRect(rect);
    textLayoutProperty->UpdateContent(index);
    textLayoutProperty->UpdateTextColor(Color(cornerMarkTheme->GetFontColor()));
    textLayoutProperty->UpdateFontSize(cornerMarkTheme->GetFontSize());
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateMaxLines(1);
    BorderRadiusProperty borderRadius(cornerMarkTheme->GetCornerRadius());
    textRenderContext->UpdateBorderRadius(borderRadius);
    if (context->GetColorMode() == ColorMode::DARK) {
        textRenderContext->UpdateBackgroundColor(cornerMarkTheme->GetDarkThemeBackgroundColor());
    } else {
        textRenderContext->UpdateBackgroundColor(cornerMarkTheme->GetWhiteThemeBackgroundColor());
    }
    node->SetCornerMarkNode(frameNode);
    frameNode->SetParent(AceType::WeakClaim(AceType::RawPtr(node)));
    frameNode->SetActive(true);
    textRenderContext->UpdateZIndex(INT32_MAX);
    context->FlushUITaskWithSingleDirtyNode(frameNode);
    context->FlushSyncGeometryNodeTasks();
    return RET_SUCCESS;
}

int32_t CornerMark::UpdateCornerMarkNode(const RefPtr<NG::FrameNode>& node, const std::string& index)
{
    auto frameNode = node->GetCornerMarkNode();
    CHECK_NULL_RETURN(frameNode, RET_FAILED);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, RET_FAILED);
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, RET_FAILED);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, RET_FAILED);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_RETURN(context, RET_FAILED);
    textLayoutProperty->UpdateContent(index);
    context->FlushUITaskWithSingleDirtyNode(frameNode);
    context->FlushSyncGeometryNodeTasks();
    return RET_SUCCESS;
}

int32_t CornerMark::RemoveCornerMarkNode(const RefPtr<NG::FrameNode>& node)
{
    auto frameNode = node->GetCornerMarkNode();
    CHECK_NULL_RETURN(frameNode, RET_FAILED);
    frameNode->SetParent(nullptr);
    node->SetCornerMarkNode(nullptr);
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    return RET_SUCCESS;
}

void CornerMark::UpdateCornerMarkNodeLanguage(const RefPtr<NG::FrameNode>& node)
{
    auto frameNode = node->GetCornerMarkNode();
    CHECK_NULL_VOID(frameNode);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto cornerMarkTheme = pipelineContext->GetTheme<CornerMarkTheme>();
    CHECK_NULL_VOID(cornerMarkTheme);
    RectF rect(0.0f, 0.0f, cornerMarkTheme->GetWidth().ConvertToPx(), cornerMarkTheme->GetHeight().ConvertToPx());
    auto geometryNode = node->GetGeometryNode();
    if (AceApplicationInfo::GetInstance().IsRightToLeft() && geometryNode) {
        rect.SetLeft(geometryNode->GetFrameRect().Width() - cornerMarkTheme->GetWidth().ConvertToPx());
    }
    textLayoutProperty->SetLayoutRect(rect);
    context->FlushUITaskWithSingleDirtyNode(frameNode);
    context->FlushSyncGeometryNodeTasks();
}

void CornerMark::UpdateCornerMarkNodeColorMode(const RefPtr<NG::FrameNode>& node)
{
    auto frameNode = node->GetCornerMarkNode();
    CHECK_NULL_VOID(frameNode);
    auto textRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    auto cornerMarkTheme = pipelineContext->GetTheme<CornerMarkTheme>();
    CHECK_NULL_VOID(cornerMarkTheme);
    if (context->GetColorMode() == ColorMode::DARK) {
        textRenderContext->UpdateBackgroundColor(cornerMarkTheme->GetDarkThemeBackgroundColor());
    } else {
        textRenderContext->UpdateBackgroundColor(cornerMarkTheme->GetWhiteThemeBackgroundColor());
    }
    context->FlushUITaskWithSingleDirtyNode(frameNode);
    context->FlushSyncGeometryNodeTasks();
}

void CornerMark::UpdateCornerMarkNodePosition(const RefPtr<NG::FrameNode>& node)
{
    if (!AceApplicationInfo::GetInstance().IsRightToLeft()) {
        return;
    }
    auto frameNode = node->GetCornerMarkNode();
    CHECK_NULL_VOID(frameNode);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto cornerMarkTheme = pipelineContext->GetTheme<CornerMarkTheme>();
    CHECK_NULL_VOID(cornerMarkTheme);
    auto geometryNode = node->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto markWidth = cornerMarkTheme->GetWidth().ConvertToPx();
    auto markHeight = cornerMarkTheme->GetHeight().ConvertToPx();
    auto newLeft = geometryNode->GetFrameRect().Width() - markWidth;
    RectF rect(newLeft, 0.0f, markWidth, markHeight);
    textLayoutProperty->SetLayoutRect(rect);

    // Called during SyncGeometryNode (layout in progress), so FlushUITaskWithSingleDirtyNode
    // would be deferred and cause a one-frame visual jump. Sync geometry directly instead.
    auto markGeometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(markGeometryNode);
    markGeometryNode->SetFrameOffset(OffsetF(newLeft, 0.0f));
    markGeometryNode->SetFrameSize(SizeF(markWidth, markHeight));
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SavePaintRect();
    renderContext->SyncGeometryProperties(RawPtr(markGeometryNode));
}
} // namespace OHOS::Ace::NG