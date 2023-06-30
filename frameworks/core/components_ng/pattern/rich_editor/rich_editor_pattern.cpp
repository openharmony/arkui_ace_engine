/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t RICH_EDITOR_TWINKLING_INTERVAL_MS = 500;
}

void RichEditorPattern::OnModifyDone()
{
    TextPattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();

    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    InitClickEvent(gestureEventHub);

    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
}

void RichEditorPattern::BeforeCreateLayoutWrapper()
{
    TextPattern::BeforeCreateLayoutWrapper();
}

bool RichEditorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    bool ret = TextPattern::OnDirtyLayoutWrapperSwap(dirty, config);
    if (!isRichEditorInit_) {
        auto eventHub = GetEventHub<RichEditorEventHub>();
        CHECK_NULL_RETURN(eventHub, ret);
        eventHub->FireOnReady();
        isRichEditorInit_ = true;
    }
    return ret;
}
int32_t RichEditorPattern::GetInstanceId() const
{
    return instanceId_;
}

std::function<ImageSourceInfo()> RichEditorPattern::CreateImageSourceInfo(const ImageSpanOptions& options)
{
    std::string src;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string bundleName;
    std::string moduleName;
    if (options.image.has_value()) {
        src = options.image.value();
    }
    if (options.imagePixelMap.has_value()) {
        pixMap = options.imagePixelMap.value();
    }
    if (options.bundleName.has_value()) {
        bundleName = options.bundleName.value();
    }
    if (options.moduleName.has_value()) {
        moduleName = options.moduleName.value();
    }
    auto createSourceInfoFunc = [&src, noPixMap = !options.imagePixelMap.has_value(), &pixMap, &bundleName,
                                    &moduleName]() -> ImageSourceInfo {
#if defined(PIXEL_MAP_SUPPORTED)
        if (noPixMap) {
            return ImageSourceInfo(src, bundleName, moduleName);
        }
        return ImageSourceInfo(pixMap);
#else
        return ImageSourceInfo(src, bundleName, moduleName);
#endif
    };
    return std::move(createSourceInfoFunc);
}

void RichEditorPattern::AddImageSpan(const ImageSpanOptions& options)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    if (options.offset.has_value()) {
        imageNode->MountToParent(host, TextSpanSplit(options.offset.value()));
    } else {
        spanIndex_ = host->GetChildren().size();
        imageNode->MountToParent(host);
    }
    std::function<ImageSourceInfo()> createSourceInfoFunc = CreateImageSourceInfo(options);
    imageLayoutProperty->UpdateImageSourceInfo(createSourceInfoFunc());
    if (options.imageAttribute.has_value()) {
        if (options.imageAttribute.value().size.has_value()) {
            imageLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(options.imageAttribute.value().size.value().width.Value()),
                    CalcLength(options.imageAttribute.value().size.value().height.Value())));
        }
        if (options.imageAttribute.value().verticalAlign.has_value()) {
            imageLayoutProperty->UpdateVerticalAlign(options.imageAttribute.value().verticalAlign.value());
        }
        if (options.imageAttribute.value().objectFit.has_value()) {
            imageLayoutProperty->UpdateImageFit(options.imageAttribute.value().objectFit.value());
        }
    }
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::AddTextSpan(const TextSpanOptions& options)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    if (options.offset.has_value()) {
        spanNode->MountToParent(host, TextSpanSplit(options.offset.value()));
    } else {
        spanIndex_ = host->GetChildren().size();
        spanNode->MountToParent(host);
    }
    spanNode->UpdateContent(options.value);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
    if (options.style.has_value()) {
        spanNode->UpdateTextColor(options.style.value().GetTextColor());
        spanNode->AddPropertyInfo(PropertyInfo::FONTCOLOR);
        spanNode->UpdateFontSize(options.style.value().GetFontSize());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
        spanNode->UpdateItalicFontStyle(options.style.value().GetFontStyle());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSTYLE);
        spanNode->UpdateFontWeight(options.style.value().GetFontWeight());
        spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
        spanNode->UpdateFontFamily(options.style.value().GetFontFamilies());
        spanNode->AddPropertyInfo(PropertyInfo::FONTFAMILY);
        spanNode->UpdateTextDecoration(options.style.value().GetTextDecoration());
        spanNode->AddPropertyInfo(PropertyInfo::TEXTDECORATION);
        spanNode->UpdateTextDecorationColor(options.style.value().GetTextDecorationColor());
        spanNode->AddPropertyInfo(PropertyInfo::NONE);
    }
}

SpanPositionInfo RichEditorPattern::GetSpanPositionInfo(int32_t position)
{
    SpanPositionInfo spanPositionInfo(-1, -1, -1, -1);
    if (!spanItemChildren_.empty()) {
        position = std::clamp(position, 0, GetTextContentLength());
        // find the spanItem where the position is
        auto it = std::find_if(
            spanItemChildren_.begin(), spanItemChildren_.end(), [position](const RefPtr<SpanItem>& spanItem) {
                return (spanItem->position - static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length()) <=
                           position) &&
                       (position < spanItem->position);
            });
        // the position is at the end
        if (it == spanItemChildren_.end()) {
            return spanPositionInfo;
        }

        spanPositionInfo.spanIndex_ = std::distance(spanItemChildren_.begin(), it);
        auto contentLen = StringUtils::ToWstring((*it)->content).length();
        spanPositionInfo.spanStart_ = (*it)->position - contentLen;
        spanPositionInfo.spanEnd_ = (*it)->position;
        spanPositionInfo.spanOffset_ = position - spanPositionInfo.spanStart_;
    }
    return spanPositionInfo;
}

void RichEditorPattern::CopyTextSpanStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target)
{
    CHECK_NULL_VOID(source);
    CHECK_NULL_VOID(target);

    if (source->HasFontSize()) {
        target->UpdateFontSize(source->GetFontSizeValue(Dimension()));
        target->AddPropertyInfo(PropertyInfo::FONTSIZE);
    }

    if (source->HasTextColor()) {
        target->UpdateTextColor(source->GetTextColorValue(Color::BLACK));
        target->AddPropertyInfo(PropertyInfo::FONTCOLOR);
    }

    if (source->HasItalicFontStyle()) {
        target->UpdateItalicFontStyle(source->GetItalicFontStyleValue(OHOS::Ace::FontStyle::NORMAL));
        target->AddPropertyInfo(PropertyInfo::FONTSTYLE);
    }

    if (source->HasFontWeight()) {
        target->UpdateFontWeight(source->GetFontWeightValue(FontWeight::NORMAL));
        target->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
    }

    if (source->HasFontFamily()) {
        target->UpdateFontFamily(source->GetFontFamilyValue({ "HarmonyOS Sans" }));
        target->AddPropertyInfo(PropertyInfo::FONTFAMILY);
    }

    if (source->HasTextDecoration()) {
        target->UpdateTextDecoration(source->GetTextDecorationValue(TextDecoration::NONE));
        target->AddPropertyInfo(PropertyInfo::TEXTDECORATION);
    }

    if (source->HasTextDecorationColor()) {
        target->UpdateTextDecorationColor(source->GetTextDecorationColorValue(Color::BLACK));
        target->AddPropertyInfo(PropertyInfo::NONE);
    }

    if (source->HasTextCase()) {
        target->UpdateTextCase(source->GetTextCaseValue(TextCase::NORMAL));
        target->AddPropertyInfo(PropertyInfo::TEXTCASE);
    }

    if (source->HasLetterSpacing()) {
        target->UpdateLetterSpacing(source->GetLetterSpacingValue(Dimension()));
        target->AddPropertyInfo(PropertyInfo::LETTERSPACE);
    }

    if (source->HasLineHeight()) {
        target->UpdateLineHeight(source->GetLineHeightValue(Dimension()));
        target->AddPropertyInfo(PropertyInfo::LINEHEIGHT);
    }
}

int32_t RichEditorPattern::TextSpanSplit(int32_t position)
{
    int32_t spanIndex = 0;
    int32_t spanStart = 0;
    int32_t spanOffset = 0;

    if (spanItemChildren_.empty()) {
        return -1;
    }

    auto positionInfo = GetSpanPositionInfo(position);
    spanIndex = positionInfo.spanIndex_;
    spanStart = positionInfo.spanStart_;
    spanOffset = positionInfo.spanOffset_;

    if (spanOffset == 0 || spanOffset == -1) {
        spanIndex_ = spanIndex;
        return spanIndex;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto it = host->GetChildren().begin();
    std::advance(it, spanIndex);

    auto spanNode = DynamicCast<SpanNode>(*it);
    CHECK_NULL_RETURN(spanNode, -1);
    auto spanItem = spanNode->GetSpanItem();
    auto newContent = StringUtils::ToWstring(spanItem->content).substr(spanOffset);
    auto deleteContent = StringUtils::ToWstring(spanItem->content).substr(0, spanOffset);

    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, -1);
    auto nodeId = stack->ClaimNodeId();
    auto newSpanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    CHECK_NULL_RETURN(newSpanNode, -1);

    auto newSpanItem = newSpanNode->GetSpanItem();
    newSpanItem->position = spanStart + spanOffset;
    auto spanIter = spanItemChildren_.begin();
    std::advance(spanIter, spanIndex);
    spanItemChildren_.insert(spanIter, newSpanItem);

    spanNode->UpdateContent(StringUtils::ToString(newContent));
    newSpanNode->UpdateContent(StringUtils::ToString(deleteContent));

    CopyTextSpanStyle(spanNode, newSpanNode);
    newSpanNode->MountToParent(host, spanIndex);

    spanIndex_ = spanIndex + 1;

    return spanIndex + 1;
}

int32_t RichEditorPattern::GetTextContentLength()
{
    if (!spanItemChildren_.empty()) {
        auto it = spanItemChildren_.rbegin();
        return (*it)->position;
    }
    return 0;
}

int32_t RichEditorPattern::GetSpanIndex()
{
    return spanIndex_;
}

int32_t RichEditorPattern::GetCaretPosition()
{
    return caretPosition_;
}

bool RichEditorPattern::SetCaretOffset(int32_t caretPosition)
{
    bool success = false;
    success = SetCaretPosition(caretPosition);
    StartTwinkling();
    return success;
}

OffsetF RichEditorPattern::CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0, 0));
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, OffsetF(0, 0));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    auto startOffset = TextPattern::CalcCursorOffsetByPosition(position, selectLineHeight);
    return startOffset + textPaintOffset - rootOffset;
}

bool RichEditorPattern::SetCaretPosition(int32_t pos)
{
    caretPosition_ = std::clamp(pos, 0, GetTextContentLength());
    return caretPosition_ == pos;
}

bool RichEditorPattern::GetCaretVisible() const
{
    return caretVisible_;
}

void RichEditorPattern::ScheduleCaretTwinkling()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        LOGW("context has no task executor.");
        return;
    }

    auto weak = WeakClaim(this);
    caretTwinklingTask_.Reset([weak] {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnCaretTwinkling();
    });
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(caretTwinklingTask_, TaskExecutor::TaskType::UI, RICH_EDITOR_TWINKLING_INTERVAL_MS);
}

void RichEditorPattern::StartTwinkling()
{
    caretTwinklingTask_.Cancel();
    caretVisible_ = true;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretTwinkling();
}

void RichEditorPattern::OnCaretTwinkling()
{
    caretTwinklingTask_.Cancel();
    caretVisible_ = !caretVisible_;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretTwinkling();
}

void RichEditorPattern::StopTwinkling()
{
    caretTwinklingTask_.Cancel();
    if (caretVisible_) {
        caretVisible_ = false;
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void RichEditorPattern::HandleClickEvent(GestureEvent& info)
{
    auto contentRect = GetTextRect();
    contentRect.SetTop(contentRect.GetY() - std::min(baselineOffset_, 0.0f));
    contentRect.SetHeight(contentRect.Height() - std::max(baselineOffset_, 0.0f));
    if (contentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY()))) {
        CHECK_NULL_VOID_NOLOG(!spanItemChildren_.empty());
        Offset textOffset = { info.GetLocalLocation().GetX() - contentRect.GetX(),
            info.GetLocalLocation().GetY() - contentRect.GetY() };
        CHECK_NULL_VOID(paragraph_);
        auto position = paragraph_->GetHandlePositionForClick(textOffset);
        auto focusHub = GetHost()->GetOrCreateFocusHub();
        if (focusHub) {
            if (focusHub->RequestFocusImmediately()) {
                float caretHeight = 0.0f;
                SetCaretPosition(position);
                OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
                CHECK_NULL_VOID(richEditorOverlayModifier_);
                richEditorOverlayModifier_->SetCaretOffsetAndHeight(caretOffset, caretHeight);
                StartTwinkling();
            } else {
                LOGE("request focus fail");
            }
        } else {
            LOGE("focusHub is NULL");
        }
    }
}

void RichEditorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!clickEventInitialized_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickListener);
    clickEventInitialized_ = true;
}

void RichEditorPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID_NOLOG(!focusEventInitialized_);
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    focusEventInitialized_ = true;
}

void RichEditorPattern::HandleBlurEvent()
{
    StopTwinkling();
}

void RichEditorPattern::HandleFocusEvent() {}
} // namespace OHOS::Ace::NG
