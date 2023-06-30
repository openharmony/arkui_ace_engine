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

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

#include "core/components_ng/pattern/rich_editor/on_rich_editor_changed_listener_impl.h"
#endif
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t IMAGE_SPAN_LENGTH = 1;
constexpr int32_t RICH_EDITOR_TWINKLING_INTERVAL_MS = 500;
} // namespace
RichEditorPattern::RichEditorPattern() {}

RichEditorPattern::~RichEditorPattern() {}

void RichEditorPattern::OnModifyDone()
{
    TextPattern::OnModifyDone();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();
    InitMouseEvent();
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    InitClickEvent(gestureEventHub);
    InitLongPressEvent(gestureEventHub);
    InitTouchEvent();
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
    MoveCaretAfterTextChange();
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

int32_t RichEditorPattern::AddImageSpan(const ImageSpanOptions& options)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();

    int32_t spanIndex = 0;
    if (options.offset.has_value()) {
        int32_t offset = TextSpanSplit(options.offset.value());
        if (offset == -1) {
            spanIndex = host->GetChildren().size();
        } else {
            spanIndex = offset;
        }
        imageNode->MountToParent(host, offset);
    } else {
        spanIndex = host->GetChildren().size();
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

    return spanIndex;
}

int32_t RichEditorPattern::AddTextSpan(const TextSpanOptions& options)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);

    int32_t spanIndex = 0;
    if (options.offset.has_value()) {
        int32_t offset = TextSpanSplit(options.offset.value());
        if (offset == -1) {
            spanIndex = host->GetChildren().size();
        } else {
            spanIndex = offset;
        }
        spanNode->MountToParent(host, offset);
    } else {
        spanIndex = host->GetChildren().size();
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

    return spanIndex;
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
    auto lastCaretPosition = caretPosition_;
    caretPosition_ = std::clamp(pos, 0, GetTextContentLength());
    if (caretPosition_ == pos) {
        return true;
    } else {
        caretPosition_ = lastCaretPosition;
        return false;
    }
}

bool RichEditorPattern::GetCaretVisible() const
{
    return caretVisible_;
}

void RichEditorPattern::SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle)
{
    updateSpanStyle_ = updateSpanStyle;
}

void RichEditorPattern::UpdateTextStyle(RefPtr<SpanNode>& spanNode, TextStyle textStyle)
{
    if (updateSpanStyle_.updateTextColor.has_value()) {
        spanNode->UpdateTextColor(textStyle.GetTextColor());
    }
    if (updateSpanStyle_.updateFontSize.has_value()) {
        spanNode->UpdateFontSize(textStyle.GetFontSize());
    }
    if (updateSpanStyle_.updateItalicFontStyle.has_value()) {
        spanNode->UpdateItalicFontStyle(textStyle.GetFontStyle());
    }
    if (updateSpanStyle_.updateFontWeight.has_value()) {
        spanNode->UpdateFontWeight(textStyle.GetFontWeight());
    }
    if (updateSpanStyle_.updateFontFamily.has_value()) {
        spanNode->UpdateFontFamily(textStyle.GetFontFamilies());
    }
    if (updateSpanStyle_.updateTextDecoration.has_value()) {
        spanNode->UpdateTextDecoration(textStyle.GetTextDecoration());
    }
    if (updateSpanStyle_.updateTextDecorationColor.has_value()) {
        spanNode->UpdateTextDecorationColor(textStyle.GetTextDecorationColor());
    }
}

void RichEditorPattern::UpdateImageStyle(RefPtr<FrameNode>& imageNode, ImageSpanAttribute imageStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    if (updateSpanStyle_.updateImageWidth.has_value() || updateSpanStyle_.updateImageHeight.has_value()) {
        imageLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(
            CalcLength(imageStyle.size.value().width.Value()), CalcLength(imageStyle.size.value().height.Value())));
    }
    if (updateSpanStyle_.updateImageFit.has_value()) {
        imageLayoutProperty->UpdateVerticalAlign(imageStyle.verticalAlign.value());
    }
    if (updateSpanStyle_.updateImageVerticalAlign.has_value()) {
        imageLayoutProperty->UpdateImageFit(imageStyle.objectFit.value());
    }
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::UpdateSpanStyle(int32_t start, int32_t end, TextStyle textStyle, ImageSpanAttribute imageStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t spanStart = 0;
    int32_t spanEnd = 0;

    for (auto it = host->GetChildren().begin(); it != host->GetChildren().end(); ++it) {
        auto spanNode = DynamicCast<SpanNode>(*it);
        auto imageNode = DynamicCast<FrameNode>(*it);
        if (!spanNode) {
            if (spanEnd != 0) {
                spanStart = spanEnd;
            }
            spanEnd = spanStart + 1;
        } else {
            auto spanItem = spanNode->GetSpanItem();
            auto contentLen = StringUtils::ToWstring(spanItem->content).length();
            spanStart = spanItem->position - contentLen;
            spanEnd = spanItem->position;
        }
        if (spanEnd < start) {
            continue;
        }

        if (spanStart >= start && spanEnd <= end) {
            if (spanNode) {
                UpdateTextStyle(spanNode, textStyle);
            } else {
                UpdateImageStyle(imageNode, imageStyle);
            }
            if (spanEnd == end) {
                break;
            }
            continue;
        }
        if (spanStart < start && start < spanEnd) {
            TextSpanSplit(start);
            --it;
            continue;
        }
        if (spanStart < end && end < spanEnd) {
            TextSpanSplit(end);
            --(--it);
            continue;
        }
        if (spanStart >= end) {
            break;
        }
    }
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
    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
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

void RichEditorPattern::OnVisibleChange(bool isVisible)
{
    TextPattern::OnVisibleChange(isVisible);
}

bool RichEditorPattern::CloseKeyboard(bool forceClose)
{
    return false;
}

void RichEditorPattern::HandleLongPress(GestureEvent& info) {}

void RichEditorPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub) {}

bool RichEditorPattern::SelectOverlayIsOn()
{
    return true;
}

void RichEditorPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent) {}

void RichEditorPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard) {}

void RichEditorPattern::InitMouseEvent()
{
    TextPattern::InitMouseEvent();
}

void RichEditorPattern::OnHover(bool isHover) {}

bool RichEditorPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    return true;
}

#if defined(ENABLE_STANDARD_INPUT)
bool RichEditorPattern::EnableStandardInput(bool needShowSoftKeyboard)
{
    return true;
}
#else
bool RichEditorPattern::UnableStandardInput(bool isFocusViewChanged)
{
    return true;
}
#endif

bool RichEditorPattern::HasConnection() const
{
    return true;
}

void RichEditorPattern::InsertValue(const std::string& insertValue) {}

void RichEditorPattern::CreateTextSpanNode(RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info,
    const std::string& insertValue, RichEditorAbstractSpanResult& retInfo)
{}

bool RichEditorPattern::BeforeIMEInsertValue(const std::string& insertValue)
{
    return true;
}

void RichEditorPattern::AfterIMEInsertValue(
    const RefPtr<SpanNode>& spanNode, int32_t insertValueLength, RichEditorAbstractSpanResult& retInfo)
{}

void RichEditorPattern::DeleteBackward(int32_t length) {}

void RichEditorPattern::DeleteForward(int32_t length) {}

void RichEditorPattern::SetInputMethodStatus(bool keyboardShown) {}

bool RichEditorPattern::CursorMoveLeft()
{
    return true;
}

bool RichEditorPattern::CursorMoveRight()
{
    return true;
}

bool RichEditorPattern::CursorMoveUp()
{
    return true;
}

bool RichEditorPattern::CursorMoveDown()
{
    return true;
}

void RichEditorPattern::CalcInsertValueObj(TextInsertValueInfo& info) {}

void RichEditorPattern::CalcDeleteValueObj(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info) {}

int32_t RichEditorPattern::DeleteValueSetImageSpan(
    const RefPtr<SpanItem> spanItem, RichEditorAbstractSpanResult& spanResult)
{
    return IMAGE_SPAN_LENGTH;
}

int32_t RichEditorPattern::DeleteValueSetTextSpan(
    const RefPtr<SpanItem> spanItem, int32_t currentPosition, int32_t length, RichEditorAbstractSpanResult& spanResult)
{
    return 0;
}

void RichEditorPattern::DeleteByDeleteValueInfo(const RichEditorDeleteValue& info) {}

bool RichEditorPattern::OnKeyEvent(const KeyEvent& keyEvent)
{
    return true;
}

void RichEditorPattern::MoveCaretAfterTextChange() {}

void RichEditorPattern::InitTouchEvent() {}

void RichEditorPattern::HandleTouchEvent(const TouchEventInfo& info) {}

void RichEditorPattern::HandleMouseEvent(const MouseInfo& info) {}

void RichEditorPattern::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto selectStart = std::min(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto selectEnd = std::max(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd);
    if (textSelectInfo.GetSelection().resultObjects.size() > 0) {
        eventHub->FireOnSelect(&textSelectInfo);
    }
    TextPattern::OnHandleMoveDone(handleRect, isFirstHandle);
}

RefPtr<UINode> RichEditorPattern::GetChildByIndex(int32_t index) const
{
    auto host = GetHost();
    const auto& children = host->GetChildren();
    int32_t size = static_cast<int32_t>(children.size());
    if (index < 0 || index >= size) {
        return nullptr;
    }
    auto pos = children.begin();
    std::advance(pos, index);
    return *pos;
}

std::string RichEditorPattern::GetSelectedSpanText(std::wstring value, int32_t start, int32_t end) const
{
    if (start < 0 || end > static_cast<int32_t>(value.length()) || start >= end) {
        LOGI("Get selected boundary is invalid");
        return "";
    }
    auto min = std::min(start, end);
    auto max = std::max(start, end);

    return StringUtils::ToString(value.substr(min, max - min));
}

TextStyleResult RichEditorPattern::GetTextStyleObject(RefPtr<SpanNode> node)
{
    TextStyleResult textStyle;
    return textStyle;
}

ResultObject RichEditorPattern::GetTextResultObject(RefPtr<SpanItem> item, int32_t index, int32_t start, int32_t end)
{
    ResultObject resultObject;
    return resultObject;
}

ResultObject RichEditorPattern::GetImageResultObject(RefPtr<SpanItem> item, int32_t index, int32_t start, int32_t end)
{
    ResultObject resultObject;
    return resultObject;
}

RichEditorSelection RichEditorPattern::GetSpansInfo(int32_t start, int32_t end)
{
    RichEditorSelection selection;
    return selection;
}
} // namespace OHOS::Ace::NG
