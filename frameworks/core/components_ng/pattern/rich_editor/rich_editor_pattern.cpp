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

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/clipboard/paste_data.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/ime/text_input_client.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_input_ai_checker.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/element_register.h"

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "commonlibrary/c_utils/base/include/refbase.h"

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif

#include "core/common/ace_engine_ext.h"
#include "core/common/udmf/udmf_client.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif

namespace OHOS::Ace::NG {
namespace {
#if defined(ENABLE_STANDARD_INPUT)
// should be moved to theme
constexpr float CARET_WIDTH = 1.5f;
constexpr float DEFAULT_CARET_HEIGHT = 18.5f;
constexpr Dimension KEYBOARD_AVOID_OFFSET = 24.0_vp;
#endif
constexpr int32_t IMAGE_SPAN_LENGTH = 1;
constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
constexpr int32_t RICH_EDITOR_TWINKLING_INTERVAL_MS = 500;
constexpr float DEFAULT_TEXT_SIZE = 16.0f;
constexpr int32_t AUTO_SCROLL_INTERVAL = 15;
constexpr Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
constexpr Dimension AUTO_SCROLL_DRAG_EDGE_DISTANCE = 58.0_vp;
constexpr float MAX_DRAG_SCROLL_SPEED = 2400.0f;
constexpr float TIME_UNIT = 1000.0f;
constexpr float DOUBLE_CLICK_INTERVAL_MS = 300.0f;
constexpr float BOX_EPSILON = 0.5f;
constexpr uint32_t RECORD_MAX_LENGTH = 20;

const std::wstring lineSeparator = L"\n";
// hen do ai anaylsis, we should limit the left an right limit of the string
constexpr static int32_t AI_TEXT_RANGE_LEFT = 50;
constexpr static int32_t AI_TEXT_RANGE_RIGHT = 50;
} // namespace
RichEditorPattern::RichEditorPattern() {}

RichEditorPattern::~RichEditorPattern()
{
    if (isCustomKeyboardAttached_) {
        CloseCustomKeyboard();
    }
}

void RichEditorPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    copyOption_ = layoutProperty->GetCopyOption().value_or(CopyOptions::Distributed);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->AddOnAreaChangeNode(host->GetId());
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    instanceId_ = context->GetInstanceId();
    InitMouseEvent();
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    InitClickEvent(gestureEventHub);
    InitLongPressEvent(gestureEventHub);
    InitTouchEvent();
    HandleEnabled();
    ProcessInnerPadding();
    InitScrollablePattern();
    if (textDetectEnable_ && (aiDetectTypesChanged_ || !aiDetectInitialized_)) {
        TextPattern::StartAITask();
    }
    if (host->IsDraggable() && copyOption_ != CopyOptions::None) {
        InitDragDropEvent();
        AddDragFrameNodeToManager(host);
    } else {
        ClearDragDropEvent();
        RemoveDragFrameNodeFromManager(host);
    }
    Register2DragDropManager();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    bool enabledCache = eventHub->IsEnabled();
    if (textDetectEnable_ && enabledCache != enabled_) {
        enabled_ = enabledCache;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void RichEditorPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (IsDisabled()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
        CHECK_NULL_VOID(richEditorTheme);
        auto disabledAlpha = richEditorTheme->GetDisabledAlpha();
        renderContext->OnOpacityUpdate(disabledAlpha);
    } else {
        auto opacity = renderContext->GetOpacity().value_or(1.0);
        renderContext->OnOpacityUpdate(opacity);
    }
}

void RichEditorPattern::BeforeCreateLayoutWrapper()
{
    TextPattern::PreCreateLayoutWrapper();
}

bool RichEditorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    frameRect_ = dirty->GetGeometryNode()->GetFrameRect();
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto richEditorLayoutAlgorithm =
        DynamicCast<RichEditorLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(richEditorLayoutAlgorithm, false);
    parentGlobalOffset_ = richEditorLayoutAlgorithm->GetParentGlobalOffset();
    richTextRect_ = richEditorLayoutAlgorithm->GetTextRect();
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    auto restoreSelectOverlayProxy = selectOverlayProxy_;
    selectOverlayProxy_.Reset(); // skip show selectoverlay in the TextPattern.
    bool ret = TextPattern::OnDirtyLayoutWrapperSwap(dirty, config);
    selectOverlayProxy_ = restoreSelectOverlayProxy;
    UpdateScrollStateAfterLayout(config.frameSizeChange);
    if (!isRichEditorInit_) {
        auto eventHub = GetEventHub<RichEditorEventHub>();
        CHECK_NULL_RETURN(eventHub, ret);
        eventHub->FireOnReady();
        ClearOperationRecords();
        isFirstCallOnReady_ = true;
        isRichEditorInit_ = true;
    }
    MoveCaretAfterTextChange();
    MoveCaretToContentRect();
    if (textSelector_.baseOffset != -1 && textSelector_.destinationOffset != -1 && SelectOverlayIsOn()) {
        CalculateHandleOffsetAndShowOverlay();
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    }
    UpdateCaretInfoToController();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ret);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, ret);
    if (context->GetClipEdge().has_value()) {
        auto geometryNode = host->GetGeometryNode();
        auto frameOffset = geometryNode->GetFrameOffset();
        auto frameSize = geometryNode->GetFrameSize();
        auto height = static_cast<float>(paragraphs_.GetHeight() + std::fabs(baselineOffset_));
        if (!context->GetClipEdge().value() && LessNotEqual(frameSize.Height(), height)) {
            RectF boundsRect(frameOffset.GetX(), frameOffset.GetY(), frameSize.Width(), height);
            CHECK_NULL_RETURN(overlayMod_, ret);
            overlayMod_->SetBoundsRect(boundsRect);
        }
    }
    caretUpdateType_ = CaretUpdateType::NONE;
    return ret;
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
    auto createSourceInfoFunc = [src, noPixMap = !options.imagePixelMap.has_value(), pixMap, bundleName,
                                    moduleName]() -> ImageSourceInfo {
#if defined(PIXEL_MAP_SUPPORTED)
        if (noPixMap) {
            return { src, bundleName, moduleName };
        }
        return ImageSourceInfo(pixMap);
#else
        return { src, bundleName, moduleName };
#endif
    };
    return std::move(createSourceInfoFunc);
}

int32_t RichEditorPattern::GetTextContentLength()
{
    if (!spans_.empty()) {
        auto it = spans_.rbegin();
        return (*it)->position;
    }
    return 0;
}
int32_t RichEditorPattern::AddImageSpan(const ImageSpanOptions& options, bool isPaste, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();

    // Disable the image itself event
    imageNode->SetDraggable(false);
    auto gesture = imageNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gesture, -1);

    OperationRecord record;
    record.beforeCaretPosition = options.offset.value_or(static_cast<int32_t>(GetTextContentLength()));
    record.addText = " ";
    ClearRedoOperationRecords();
    record.afterCaretPosition = record.beforeCaretPosition + 1;
    AddOperationRecord(record);

    // Masked the default drag behavior of node image
    gesture->SetDragEvent(nullptr, { PanDirection::DOWN }, 0, Dimension(0));

    int32_t spanIndex = 0;
    int32_t offset = -1;
    if (options.offset.has_value()) {
        offset = TextSpanSplit(options.offset.value());
        if (offset == -1) {
            spanIndex = static_cast<int32_t>(host->GetChildren().size());
        } else {
            spanIndex = offset;
        }
        imageNode->MountToParent(host, offset);
    } else if (index != -1) {
        imageNode->MountToParent(host, index);
        spanIndex = index;
    } else {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
        imageNode->MountToParent(host);
    }
    std::function<ImageSourceInfo()> createSourceInfoFunc = CreateImageSourceInfo(options);
    imageLayoutProperty->UpdateImageSourceInfo(createSourceInfoFunc());
    if (options.imageAttribute.has_value()) {
        auto imgAttr = options.imageAttribute.value();
        if (imgAttr.size.has_value()) {
            imageLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(imgAttr.size.value().width), CalcLength(imgAttr.size.value().height)));
        }
        if (imgAttr.verticalAlign.has_value()) {
            imageLayoutProperty->UpdateVerticalAlign(imgAttr.verticalAlign.value());
        }
        if (imgAttr.objectFit.has_value()) {
            imageLayoutProperty->UpdateImageFit(imgAttr.objectFit.value());
        }
        if (imgAttr.marginProp.has_value()) {
            imageLayoutProperty->UpdateMargin(imgAttr.marginProp.value());
        }
        if (imgAttr.borderRadius.has_value()) {
            auto imageRenderCtx = imageNode->GetRenderContext();
            imageRenderCtx->UpdateBorderRadius(imgAttr.borderRadius.value());
            imageRenderCtx->SetClipToBounds(true);
        }
    }
    if (isPaste) {
        isTextChange_ = true;
        moveDirection_ = MoveDirection::FORWARD;
        moveLength_ += 1;
        MoveCaretAfterTextChange();
    }
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    auto spanItem = imageNode->GetSpanItem();
    // The length of the imageSpan defaults to the length of a character to calculate the position
    spanItem->content = " ";
    AddSpanItem(spanItem, offset);
    if (options.userGestureOption.onClick) {
        auto tmpClickFunc = options.userGestureOption.onClick;
        spanItem->SetOnClickEvent(std::move(tmpClickFunc));
    }
    if (options.userGestureOption.onLongPress) {
        auto tmpLongPressFunc = options.userGestureOption.onLongPress;
        spanItem->SetLongPressEvent(std::move(tmpLongPressFunc));
    }
    if (options.offset.has_value() && options.offset.value() <= GetCaretPosition()) {
        SetCaretPosition(options.offset.value() + 1 + moveLength_);
        moveLength_ = 0;
    } else {
        placeholderCount_++;
        SetCaretPosition(GetTextContentLength());
    }
    if (!isPaste && textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
    return spanIndex;
}

void RichEditorPattern::AddSpanItem(const RefPtr<SpanItem>& item, int32_t offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (offset == -1) {
        offset = host->GetChildren().size();
    }
    offset = std::clamp(offset, 0, static_cast<int32_t>(host->GetChildren().size()) - 1);
    auto it = spans_.begin();
    std::advance(it, offset);
    spans_.insert(it, item);
    UpdateSpanPosition();
}

int32_t RichEditorPattern::AddPlaceholderSpan(const RefPtr<UINode>& customNode, const SpanOptionBase& options)
{
    CHECK_NULL_RETURN(customNode, 0);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    CHECK_NULL_RETURN(placeholderSpanNode, 0);
    customNode->MountToParent(placeholderSpanNode);
    auto frameNode = DynamicCast<FrameNode>(customNode);
    if (frameNode) {
        frameNode->SetDraggable(false);
    }
    auto focusHub = placeholderSpanNode->GetOrCreateFocusHub();
    focusHub->SetFocusable(false);
    int32_t spanIndex = 0;
    int32_t offset = -1;
    auto optionalPosition = options.offset.value_or(-1);
    if (optionalPosition >= 0) {
        offset = TextSpanSplit(options.offset.value());
        if (offset == -1) {
            spanIndex = static_cast<int32_t>(host->GetChildren().size());
        } else {
            spanIndex = offset;
        }
        placeholderSpanNode->MountToParent(host, offset);
    } else {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
        placeholderSpanNode->MountToParent(host);
    }
    auto spanItem = placeholderSpanNode->GetSpanItem();
    spanItem->content = " ";
    AddSpanItem(spanItem, offset);
    if (options.offset.has_value() && options.offset.value() <= GetCaretPosition()) {
        SetCaretPosition(options.offset.value() + 1 + moveLength_);
        moveLength_ = 0;
    } else {
        placeholderCount_++;
        SetCaretPosition(GetTextContentLength());
    }
    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
    placeholderSpanNode->MarkModifyDone();
    placeholderSpanNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return spanIndex;
}

int32_t RichEditorPattern::AddTextSpan(const TextSpanOptions& options, bool isPaste, int32_t index)
{
    OperationRecord record;
    record.beforeCaretPosition = options.offset.value_or(static_cast<int32_t>(GetTextContentLength()));
    record.addText = options.value;
    ClearRedoOperationRecords();
    record.afterCaretPosition =
        record.beforeCaretPosition + static_cast<int32_t>(StringUtils::ToWstring(options.value).length());
    AddOperationRecord(record);
    return AddTextSpanOperation(options, isPaste, index, false, false);
}

int32_t RichEditorPattern::AddTextSpanOperation(
    const TextSpanOptions& options, bool isPaste, int32_t index, bool needLeadingMargin, bool updateCaretOPosition)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(nodeId);

    int32_t spanIndex = 0;
    int32_t offset = -1;
    if (options.offset.has_value()) {
        offset = TextSpanSplit(options.offset.value(), needLeadingMargin);
        if (offset == -1) {
            spanIndex = static_cast<int32_t>(host->GetChildren().size());
        } else {
            spanIndex = offset;
        }
        spanNode->MountToParent(host, offset);
    } else if (index != -1) {
        spanNode->MountToParent(host, index);
        spanIndex = index;
    } else {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
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
        spanNode->UpdateTextShadow(options.style.value().GetTextShadows());
        spanNode->AddPropertyInfo(PropertyInfo::TEXTSHADOW);
    }
    auto spanItem = spanNode->GetSpanItem();
    spanItem->content = options.value;
    spanItem->SetTextStyle(options.style);
    spanItem->hasResourceFontColor = options.hasResourceFontColor;
    spanItem->hasResourceDecorationColor = options.hasResourceDecorationColor;
    AddSpanItem(spanItem, offset);
    if (options.paraStyle) {
        int32_t start = 0;
        int32_t end = 0;
        spanItem->GetIndex(start, end);
        UpdateParagraphStyle(start, end, *options.paraStyle);
    }
    if (options.userGestureOption.onClick) {
        auto tmpClickFunc = options.userGestureOption.onClick;
        spanItem->SetOnClickEvent(std::move(tmpClickFunc));
    }
    if (options.userGestureOption.onLongPress) {
        auto tmpLongPressFunc = options.userGestureOption.onLongPress;
        spanItem->SetLongPressEvent(std::move(tmpLongPressFunc));
    }
    if (updateCaretOPosition) {
        if (options.offset.has_value() && options.offset.value() <= GetCaretPosition()) {
            SetCaretPosition(options.offset.value() + 1 + moveLength_);
            moveLength_ = 0;
        } else {
            SetCaretPosition(GetTextContentLength());
        }
    }
    if (!isPaste && textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
    SpanNodeFission(spanNode);
    return spanIndex;
}

int32_t RichEditorPattern::AddSymbolSpan(const SymbolSpanOptions& options, bool isPaste, int32_t index)
{
    OperationRecord record;
    record.beforeCaretPosition = options.offset.value_or(static_cast<int32_t>(GetTextContentLength()));
    record.addText = " ";
    ClearRedoOperationRecords();
    record.afterCaretPosition = record.beforeCaretPosition + 1;
    AddOperationRecord(record);
    return AddSymbolSpanOperation(options, isPaste, index);
}

int32_t RichEditorPattern::AddSymbolSpanOperation(const SymbolSpanOptions& options, bool isPaste, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, nodeId);

    int32_t spanIndex = 0;
    int32_t offset = -1;
    if (options.offset.has_value()) {
        offset = TextSpanSplit(options.offset.value());
        if (offset == -1) {
            spanIndex = static_cast<int32_t>(host->GetChildren().size());
        } else {
            spanIndex = offset;
        }
        spanNode->MountToParent(host, offset);
    } else if (index != -1) {
        spanNode->MountToParent(host, index);
        spanIndex = index;
    } else {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
        spanNode->MountToParent(host);
    }
    spanNode->UpdateContent(options.symbolId);
    spanNode->AddPropertyInfo(PropertyInfo::NONE);
    if (options.style.has_value()) {
        spanNode->UpdateFontSize(options.style.value().GetFontSize());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
        spanNode->UpdateFontWeight(options.style.value().GetFontWeight());
        spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
        spanNode->UpdateSymbolColorList(options.style.value().GetSymbolColorList());
        spanNode->AddPropertyInfo(PropertyInfo::SYMBOL_COLOR);
        spanNode->UpdateSymbolRenderingStrategy(options.style.value().GetRenderStrategy());
        spanNode->AddPropertyInfo(PropertyInfo::SYMBOL_RENDERING_STRATEGY);
        spanNode->UpdateSymbolEffectStrategy(options.style.value().GetEffectStrategy());
        spanNode->AddPropertyInfo(PropertyInfo::SYMBOL_EFFECT_STRATEGY);
    }
    auto spanItem = spanNode->GetSpanItem();
    spanItem->content = "  ";
    spanItem->SetTextStyle(options.style);
    AddSpanItem(spanItem, offset);
    if (options.offset.has_value() && options.offset.value() <= GetCaretPosition()) {
        SetCaretPosition(options.offset.value() + SYMBOL_SPAN_LENGTH + moveLength_);
        moveLength_ = 0;
    } else {
        SetCaretPosition(GetTextContentLength());
    }
    SpanNodeFission(spanNode);
    return spanIndex;
}

void RichEditorPattern::SpanNodeFission(RefPtr<SpanNode>& spanNode)
{
    auto spanItem = spanNode->GetSpanItem();
    auto content = StringUtils::ToWstring(spanItem->content);
    auto contentLen = content.length();
    auto spanStart = spanItem->position - contentLen;
    for (size_t i = 0; i < content.length(); i++) {
        auto character = content[i];
        if (character == '\n') {
            auto charPosition = spanStart + i;
            TextSpanSplit(static_cast<int32_t>(charPosition + 1));
        }
    }
}

void RichEditorPattern::DeleteSpans(const RangeOptions& options)
{
    int32_t start = 0;
    int32_t end = 0;
    auto length = GetTextContentLength();
    start = (!options.start.has_value()) ? 0 : options.start.value();
    end = (!options.end.has_value()) ? length : options.end.value();
    if (start > end) {
        auto value = start;
        start = end;
        end = value;
    }
    start = std::max(0, start);
    end = std::min(length, end);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "index range=[%{public}d, %{public}d]", start, end);
    if (start > length || end < 0 || start == end) {
        return;
    }

    OperationRecord record;
    record.beforeCaretPosition = start;
    std::wstringstream wss;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        wss << StringUtils::ToWstring((*iter)->content);
    }
    std::wstring deleteText = wss.str().substr(start, end - start);
    record.deleteText = StringUtils::ToString(deleteText);
    ClearRedoOperationRecords();
    record.afterCaretPosition = start;
    AddOperationRecord(record);

    auto startInfo = GetSpanPositionInfo(start);
    auto endInfo = GetSpanPositionInfo(end - 1);
    if (startInfo.spanIndex_ == endInfo.spanIndex_) {
        DeleteSpanByRange(start, end, startInfo);
    } else {
        DeleteSpansByRange(start, end, startInfo, endInfo);
    }
    if (textSelector_.IsValid()) {
        SetCaretPosition(textSelector_.GetTextStart());
        CloseSelectOverlay();
        ResetSelection();
    }
    SetCaretOffset(start);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrens = host->GetChildren();
    if (childrens.empty() || GetTextContentLength() == 0) {
        SetCaretPosition(0);
    }
    UpdateSpanPosition();
}

void RichEditorPattern::DeleteSpanByRange(int32_t start, int32_t end, SpanPositionInfo info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrens = host->GetChildren();
    auto it = childrens.begin();
    std::advance(it, info.spanIndex_);
    if (start == info.spanStart_ && end == info.spanEnd_) {
        ClearContent(*it);
        host->RemoveChild(*it);
    } else {
        auto spanNode = DynamicCast<SpanNode>(*it);
        CHECK_NULL_VOID(spanNode);
        auto spanItem = spanNode->GetSpanItem();
        auto beforStr = StringUtils::ToWstring(spanItem->content).substr(0, start - info.spanStart_);
        auto endStr = StringUtils::ToWstring(spanItem->content).substr(end - info.spanStart_);
        std::wstring result = beforStr + endStr;
        auto str = StringUtils::ToString(result);
        spanNode->UpdateContent(str);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::DeleteSpansByRange(
    int32_t start, int32_t end, SpanPositionInfo startInfo, SpanPositionInfo endInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrens = host->GetChildren();
    if (childrens.empty()) {
        return;
    }

    auto itStart = childrens.begin();
    if (startInfo.spanIndex_ >= static_cast<int32_t>(childrens.size())) {
        std::advance(itStart, childrens.size() - 1);
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "startInfo.spanIndex_ is larger than childrens size");
    } else {
        std::advance(itStart, startInfo.spanIndex_);
    }
    auto saveStartSpan = (start == startInfo.spanStart_) ? 0 : 1;
    if (saveStartSpan) {
        auto spanNodeStart = DynamicCast<SpanNode>(*itStart);
        CHECK_NULL_VOID(spanNodeStart);
        auto spanItemStart = spanNodeStart->GetSpanItem();
        auto beforStr = StringUtils::ToWstring(spanItemStart->content).substr(0, start - startInfo.spanStart_);
        auto strStart = StringUtils::ToString(beforStr);
        spanNodeStart->UpdateContent(strStart);
    }
    auto itEnd = childrens.begin();
    std::advance(itEnd, endInfo.spanIndex_);
    auto delEndSpan = (end == endInfo.spanEnd_) ? 1 : 0;
    if (!delEndSpan) {
        auto spanNodeEnd = DynamicCast<SpanNode>(*itEnd);
        CHECK_NULL_VOID(spanNodeEnd);
        auto spanItemEnd = spanNodeEnd->GetSpanItem();
        auto endStr =
            StringUtils::ToWstring(spanItemEnd->content).substr(end - endInfo.spanStart_, endInfo.spanEnd_ - end);
        auto strEnd = StringUtils::ToString(endStr);
        spanNodeEnd->UpdateContent(strEnd);
    }
    auto startIter = childrens.begin();
    std::advance(startIter, startInfo.spanIndex_ + saveStartSpan);
    auto endIter = childrens.begin();
    std::advance(endIter, endInfo.spanIndex_);
    for (auto iter = startIter; iter != endIter; ++iter) {
        ClearContent(*iter);
        host->RemoveChild(*iter);
    }
    if (endIter != childrens.end() && delEndSpan) {
        ClearContent(*endIter);
        host->RemoveChild(*endIter);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

std::u16string RichEditorPattern::GetLeftTextOfCursor(int32_t number)
{
    if (number > caretPosition_) {
        number = caretPosition_;
    }
    auto start = caretPosition_;
    if (IsSelected()) {
        start = std::min(textSelector_.GetStart(), textSelector_.GetEnd());
    }
    auto stringText = GetSelectedText(start - number, start);
    return StringUtils::Str8ToStr16(stringText);
}

std::u16string RichEditorPattern::GetRightTextOfCursor(int32_t number)
{
    auto end = caretPosition_;
    if (IsSelected()) {
        end = std::max(textSelector_.GetStart(), textSelector_.GetEnd());
    }
    auto stringText = GetSelectedText(end, end + number);
    return StringUtils::Str8ToStr16(stringText);
}

int32_t RichEditorPattern::GetTextIndexAtCursor()
{
    return caretPosition_;
}

void RichEditorPattern::ClearContent(const RefPtr<UINode>& child)
{
    CHECK_NULL_VOID(child);
    if (child->GetTag() == V2::SPAN_ETS_TAG) {
        auto spanNode = DynamicCast<SpanNode>(child);
        if (spanNode) {
            spanNode->UpdateContent("");
            spanNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

SpanPositionInfo RichEditorPattern::GetSpanPositionInfo(int32_t position)
{
    SpanPositionInfo spanPositionInfo(-1, -1, -1, -1);
    CHECK_NULL_RETURN(!spans_.empty(), spanPositionInfo);
    position = std::clamp(position, 0, GetTextContentLength());
    // find the spanItem where the position is
    auto it = std::find_if(spans_.begin(), spans_.end(), [position](const RefPtr<SpanItem>& spanItem) {
        return (spanItem->position - static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length()) <=
                   position) &&
               (position < spanItem->position);
    });
    if (it != spans_.end() && (*it)->unicode != 0 && (*it)->position - caretPosition_ + moveLength_ == 1) {
        it++;
        moveLength_++;
        position++;
    }

    // the position is at the end
    if (it == spans_.end()) {
        return spanPositionInfo;
    }

    spanPositionInfo.spanIndex_ = std::distance(spans_.begin(), it);
    auto contentLen = StringUtils::ToWstring((*it)->content).length();
    spanPositionInfo.spanStart_ = (*it)->position - contentLen;
    spanPositionInfo.spanEnd_ = (*it)->position;
    spanPositionInfo.spanOffset_ = position - spanPositionInfo.spanStart_;
    return spanPositionInfo;
}

void RichEditorPattern::CopyTextSpanStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target, bool needLeadingMargin)
{
    CHECK_NULL_VOID(source);
    CHECK_NULL_VOID(target);

    CopyTextSpanFontStyle(source, target);
    CopyTextSpanLineStyle(source, target, needLeadingMargin);
}

void RichEditorPattern::CopyTextSpanFontStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target)
{
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
}

void RichEditorPattern::CopyTextSpanLineStyle(
    RefPtr<SpanNode>& source, RefPtr<SpanNode>& target, bool needLeadingMargin)
{
    if (source->HasLineHeight()) {
        target->UpdateLineHeight(source->GetLineHeightValue(Dimension()));
        target->AddPropertyInfo(PropertyInfo::LINEHEIGHT);
    }

    if (source->HasTextShadow()) {
        target->UpdateTextShadow(source->GetTextShadowValue({Shadow()}));
        target->AddPropertyInfo(PropertyInfo::TEXTSHADOW);
    }

    if (needLeadingMargin && source->HasLeadingMargin()) {
        target->UpdateLeadingMargin(source->GetLeadingMarginValue({}));
        target->AddPropertyInfo(PropertyInfo::LEADING_MARGIN);
    }

    if (source->HasTextAlign()) {
        target->UpdateTextAlign(source->GetTextAlignValue(TextAlign::LEFT));
        target->AddPropertyInfo(PropertyInfo::TEXT_ALIGN);
    }
}

int32_t RichEditorPattern::TextSpanSplit(int32_t position, bool needLeadingMargin)
{
    if (spans_.empty()) {
        return -1;
    }

    auto positionInfo = GetSpanPositionInfo(position);
    int32_t spanIndex = positionInfo.spanIndex_;
    int32_t spanStart = positionInfo.spanStart_;
    int32_t offsetInSpan = positionInfo.spanOffset_;
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT,
        "position=%{public}d, spanIndex=%{public}d, spanStart=%{public}d, offsetInSpan=%{public}d",
        position, spanIndex, spanStart, offsetInSpan);

    if (offsetInSpan <= 0) {
        return spanIndex;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto it = host->GetChildren().begin();
    std::advance(it, spanIndex);

    auto spanNode = DynamicCast<SpanNode>(*it);
    CHECK_NULL_RETURN(spanNode, -1);
    auto spanItem = spanNode->GetSpanItem();
    auto spanItemContent = StringUtils::ToWstring(spanItem->content);
    if (offsetInSpan > static_cast<int32_t>(spanItemContent.length())) {
        offsetInSpan = static_cast<int32_t>(spanItemContent.length());
    }
    auto newContent = spanItemContent.substr(offsetInSpan);
    auto deleteContent = spanItemContent.substr(0, offsetInSpan);

    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, -1);
    auto nodeId = stack->ClaimNodeId();
    auto newSpanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    CHECK_NULL_RETURN(newSpanNode, -1);

    auto newSpanItem = newSpanNode->GetSpanItem();
    newSpanItem->position = spanStart + offsetInSpan;
    auto spanIter = spans_.begin();
    std::advance(spanIter, spanIndex);
    spans_.insert(spanIter, newSpanItem);

    spanNode->UpdateContent(StringUtils::ToString(newContent));
    newSpanNode->UpdateContent(StringUtils::ToString(deleteContent));

    CopyTextSpanStyle(spanNode, newSpanNode, needLeadingMargin);
    newSpanNode->MountToParent(host, spanIndex);

    return spanIndex + 1;
}

int32_t RichEditorPattern::GetCaretPosition()
{
    return caretPosition_;
}

bool RichEditorPattern::SetCaretOffset(int32_t caretPosition)
{
    bool success = false;
    success = SetCaretPosition(caretPosition);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (focusHub->IsCurrentFocus()) {
        StartTwinkling();
    }
    CloseSelectOverlay();
    ResetSelection();
    return success;
}

OffsetF RichEditorPattern::CalcCursorOffsetByPosition(
    int32_t position, float& selectLineHeight, bool downStreamFirst, bool needLineHighest)
{
    selectLineHeight = 0.0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0, 0));
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, OffsetF(0, 0));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    auto startOffset = paragraphs_.ComputeCursorOffset(position, selectLineHeight, downStreamFirst, needLineHighest);
    auto children = host->GetChildren();
    if (NearZero(selectLineHeight)) {
        if (children.empty() || GetTextContentLength() == 0) {
            CHECK_NULL_RETURN(overlayMod_, OffsetF(0, 0));
            float caretHeight = DynamicCast<RichEditorOverlayModifier>(overlayMod_)->GetCaretHeight();
            return textPaintOffset - rootOffset - OffsetF(0.0f, caretHeight / 2.0f);
        }
        if (std::all_of(children.begin(), children.end(), [](RefPtr<UINode>& node) {
                CHECK_NULL_RETURN(node, false);
                return (node->GetTag() == V2::IMAGE_ETS_TAG || node->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG);
            })) {
            bool isTail = false;
            auto it = children.begin();
            if (position >= static_cast<int32_t>(children.size())) {
                std::advance(it, (static_cast<int32_t>(children.size()) - 1));
                isTail = true;
            } else {
                std::advance(it, position);
            }
            if (it == children.end()) {
                return startOffset;
            }
            auto imageNode = DynamicCast<FrameNode>(*it);
            if (imageNode) {
                auto geometryNode = imageNode->GetGeometryNode();
                CHECK_NULL_RETURN(geometryNode, OffsetF(0.0f, 0.0f));
                startOffset = geometryNode->GetMarginFrameOffset();
                selectLineHeight = geometryNode->GetMarginFrameSize().Height();
                startOffset += isTail ? OffsetF(geometryNode->GetMarginFrameSize().Width(), 0.0f) : OffsetF(0.0f, 0.0f);
            }
            return startOffset;
        }
    }
    auto caretOffset = startOffset + textPaintOffset + rootOffset;
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, caretOffset);
    auto frameSize = geometryNode->GetFrameRect().GetSize();
    CHECK_NULL_RETURN(overlayMod_, caretOffset);
    float caretWidth = DynamicCast<RichEditorOverlayModifier>(overlayMod_)->GetCaretWidth();
    caretOffset.SetX(std::clamp(caretOffset.GetX(), 0.0f, static_cast<float>(frameSize.Width()) - caretWidth));
    return caretOffset;
}

bool RichEditorPattern::SetCaretPosition(int32_t pos)
{
    auto lastCaretPosition = caretPosition_;
    caretPosition_ = std::clamp(pos, 0, GetTextContentLength());
    ResetLastClickOffset();
    if (caretPosition_ == pos) {
        return true;
    }
    caretPosition_ = lastCaretPosition;
    return false;
}

bool RichEditorPattern::GetCaretVisible() const
{
    return caretVisible_;
}

void RichEditorPattern::SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle)
{
    updateSpanStyle_ = updateSpanStyle;
}

void RichEditorPattern::SetTypingStyle(struct UpdateSpanStyle typingStyle, TextStyle textStyle)
{
    typingStyle_ = typingStyle;
    typingTextStyle_ = textStyle;
}

void RichEditorPattern::UpdateTextStyle(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle)
{
    if (spanNode->GetTag() != V2::SPAN_ETS_TAG || updateSpanStyle_.isSymbolStyle) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (updateSpanStyle.updateTextColor.has_value()) {
        spanNode->UpdateTextColor(textStyle.GetTextColor());
        spanNode->AddPropertyInfo(PropertyInfo::FONTCOLOR);
    }
    if (updateSpanStyle.updateFontSize.has_value()) {
        spanNode->UpdateFontSize(textStyle.GetFontSize());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
    }
    if (updateSpanStyle.updateItalicFontStyle.has_value()) {
        spanNode->UpdateItalicFontStyle(textStyle.GetFontStyle());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSTYLE);
    }
    if (updateSpanStyle.updateFontWeight.has_value()) {
        spanNode->UpdateFontWeight(textStyle.GetFontWeight());
        spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
    }
    if (updateSpanStyle.updateFontFamily.has_value()) {
        spanNode->UpdateFontFamily(textStyle.GetFontFamilies());
        spanNode->AddPropertyInfo(PropertyInfo::FONTFAMILY);
    }
    if (updateSpanStyle.updateTextDecoration.has_value()) {
        spanNode->UpdateTextDecoration(textStyle.GetTextDecoration());
        spanNode->AddPropertyInfo(PropertyInfo::TEXTDECORATION);
    }
    if (updateSpanStyle.updateTextDecorationColor.has_value()) {
        spanNode->UpdateTextDecorationColor(textStyle.GetTextDecorationColor());
        spanNode->AddPropertyInfo(PropertyInfo::NONE);
    }
    if (updateSpanStyle.updateTextShadows.has_value()) {
        spanNode->UpdateTextShadow(textStyle.GetTextShadows());
        spanNode->AddPropertyInfo(PropertyInfo::TEXTSHADOW);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::UpdateSymbolStyle(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle)
{
    if (spanNode->GetTag() != V2::SYMBOL_SPAN_ETS_TAG || !updateSpanStyle_.isSymbolStyle) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (updateSpanStyle.updateFontSize.has_value()) {
        spanNode->UpdateFontSize(textStyle.GetFontSize());
        spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
    }
    if (updateSpanStyle.updateFontWeight.has_value()) {
        spanNode->UpdateFontWeight(textStyle.GetFontWeight());
        spanNode->AddPropertyInfo(PropertyInfo::FONTWEIGHT);
    }
    if (updateSpanStyle.updateSymbolColor.has_value()) {
        spanNode->UpdateSymbolColorList(textStyle.GetSymbolColorList());
        spanNode->AddPropertyInfo(PropertyInfo::SYMBOL_COLOR);
    }
    if (updateSpanStyle.updateSymbolRenderingStrategy.has_value()) {
        spanNode->UpdateSymbolRenderingStrategy(textStyle.GetRenderStrategy());
        spanNode->AddPropertyInfo(PropertyInfo::SYMBOL_RENDERING_STRATEGY);
    }
    if (updateSpanStyle.updateSymbolEffectStrategy.has_value()) {
        spanNode->UpdateSymbolEffectStrategy(textStyle.GetEffectStrategy());
        spanNode->AddPropertyInfo(PropertyInfo::SYMBOL_EFFECT_STRATEGY);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

bool RichEditorPattern::HasSameTypingStyle(const RefPtr<SpanNode>& spanNode)
{
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, false);
    auto spanTextStyle = spanItem->GetTextStyle();
    if (spanTextStyle.has_value() && typingTextStyle_.has_value()) {
        return spanTextStyle.value() == typingTextStyle_.value();
    } else {
        return !(spanTextStyle.has_value() || typingTextStyle_.has_value());
    }
}

void RichEditorPattern::UpdateImageStyle(RefPtr<FrameNode>& imageNode, const ImageSpanAttribute& imageStyle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    if (updateSpanStyle_.updateImageWidth.has_value() || updateSpanStyle_.updateImageHeight.has_value()) {
        imageLayoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(imageStyle.size.value().width), CalcLength(imageStyle.size.value().height)));
    }
    if (updateSpanStyle_.updateImageFit.has_value()) {
        imageLayoutProperty->UpdateImageFit(imageStyle.objectFit.value());
    }
    if (updateSpanStyle_.updateImageVerticalAlign.has_value()) {
        imageLayoutProperty->UpdateVerticalAlign(imageStyle.verticalAlign.value());
    }
    if (updateSpanStyle_.borderRadius.has_value()) {
        auto imageRenderCtx = imageNode->GetRenderContext();
        imageRenderCtx->UpdateBorderRadius(imageStyle.borderRadius.value());
        imageRenderCtx->SetClipToBounds(true);
    }
    if (updateSpanStyle_.marginProp.has_value()) {
        imageLayoutProperty->UpdateMargin(imageStyle.marginProp.value());
    }

    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::UpdateSpanStyle(
    int32_t start, int32_t end, const TextStyle& textStyle, const ImageSpanAttribute& imageStyle)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "range=[%{public}d, %{public}d]", start, end);
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
            spanNode->GetSpanItem()->GetIndex(spanStart, spanEnd);
        }
        if (spanEnd < start) {
            continue;
        }

        if (spanStart >= start && spanEnd <= end) {
            if (spanNode) {
                UpdateSymbolStyle(spanNode, updateSpanStyle_, textStyle);
                UpdateTextStyle(spanNode, updateSpanStyle_, textStyle);
            } else {
                UpdateImageStyle(imageNode, imageStyle);
            }
            if (spanEnd == end) {
                break;
            }
        } else if (spanStart < start && start < spanEnd) {
            TextSpanSplit(start, true);
            --it;
        } else if (spanStart < end && end < spanEnd) {
            TextSpanSplit(end, true);
            --(--it);
        } else if (spanStart >= end) {
            break;
        }
    }

    // Custom menus do not actively close.
    if (!SelectOverlayIsOn() || selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.menuBuilder == nullptr) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "CloseSelectOverlay");
        CloseSelectOverlay();
    }
}

std::vector<ParagraphInfo> RichEditorPattern::GetParagraphInfo(int32_t start, int32_t end)
{
    std::vector<ParagraphInfo> res;
    auto spanNodes = GetParagraphNodes(start, end);
    CHECK_NULL_RETURN(!spanNodes.empty(), {});

    auto&& firstSpan = spanNodes.front()->GetSpanItem();
    auto paraStart = firstSpan->position - StringUtils::ToWstring(firstSpan->content).length();

    for (auto it = spanNodes.begin(); it != spanNodes.end(); ++it) {
        if (it == std::prev(spanNodes.end()) || StringUtils::ToWstring((*it)->GetSpanItem()->content).back() == L'\n') {
            ParagraphInfo info;
            auto lm = (*it)->GetLeadingMarginValue({});

            res.emplace_back(ParagraphInfo {
                .leadingMarginPixmap = lm.pixmap,
                .leadingMarginSize = { Dimension(lm.size.Width()).ConvertToVp(),
                    Dimension(lm.size.Height()).ConvertToVp() },
                .textAlign = static_cast<int32_t>((*it)->GetTextAlignValue(TextAlign::START)),
                .range = { paraStart, (*it)->GetSpanItem()->position },
            });
            paraStart = (*it)->GetSpanItem()->position;
        }
    }

    return res;
}

int32_t RichEditorPattern::GetParagraphLength(const std::list<RefPtr<UINode>>& spans) const
{
    if (spans.empty()) {
        return 0;
    }
    int32_t imageSpanCnt = 0;
    for (auto it = spans.rbegin(); it != spans.rend(); ++it) {
        auto spanNode = DynamicCast<SpanNode>(*it);
        if (spanNode) {
            return spanNode->GetSpanItem()->position + imageSpanCnt;
        }
        ++imageSpanCnt;
    }
    return imageSpanCnt;
}

std::vector<RefPtr<SpanNode>> RichEditorPattern::GetParagraphNodes(int32_t start, int32_t end) const
{
    CHECK_NULL_RETURN(start != end, {});
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    CHECK_NULL_RETURN(!host->GetChildren().empty(), {});

    const auto& spans = host->GetChildren();
    int32_t length = GetParagraphLength(spans);
    std::vector<RefPtr<SpanNode>> res;

    if (start >= length) {
        return res;
    }

    auto headIt = spans.begin();
    auto flagNode = headIt;
    bool isEnd = false;
    int32_t spanEnd = -1;
    while (flagNode != spans.end()) {
        auto spanNode = DynamicCast<SpanNode>(*flagNode);
        if (spanNode) {
            auto&& info = spanNode->GetSpanItem();
            spanEnd = info->position;
            isEnd = StringUtils::ToWstring(info->content).back() == '\n';
        } else {
            ++spanEnd;
            isEnd = false;
        }
        flagNode++;
        if (spanEnd > start) {
            break;
        }
        if (isEnd) {
            headIt = flagNode;
        }
    }
    while (headIt != flagNode) {
        auto spanNode = DynamicCast<SpanNode>(*headIt);
        if (spanNode) {
            res.emplace_back(spanNode);
        }
        headIt++;
    }
    while (flagNode != spans.end() && (spanEnd < end || !isEnd)) {
        auto spanNode = DynamicCast<SpanNode>(*flagNode);
        if (spanNode) {
            res.emplace_back(spanNode);
            auto&& info = spanNode->GetSpanItem();
            spanEnd = info->position;
            isEnd = StringUtils::ToWstring(info->content).back() == '\n';
        } else {
            ++spanEnd;
            isEnd = false;
        }
        flagNode++;
    }

    return res;
}

void RichEditorPattern::UpdateParagraphStyle(int32_t start, int32_t end, const struct UpdateParagraphStyle& style)
{
    auto spanNodes = GetParagraphNodes(start, end);
    for (const auto& spanNode : spanNodes) {
        if (style.textAlign.has_value()) {
            spanNode->UpdateTextAlign(*style.textAlign);
        } else {
            spanNode->UpdateTextAlign(TextAlign::START);
        }
        if (style.leadingMargin.has_value()) {
            spanNode->GetSpanItem()->leadingMargin = *style.leadingMargin;
            spanNode->UpdateLeadingMargin(*style.leadingMargin);
        }
    }
}

void RichEditorPattern::ScheduleCaretTwinkling()
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        return;
    }

    if (isCursorAlwaysDisplayed_) {
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
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    if (hasClicked_) {
        hasClicked_ = false;
        TimeStamp clickTimeStamp = info.GetTimeStamp();
        std::chrono::duration<float, std::ratio<1, InputAIChecker::SECONDS_TO_MILLISECONDS>> timeout =
            clickTimeStamp - lastClickTimeStamp_;
        lastClickTimeStamp_ = info.GetTimeStamp();
        if (timeout.count() < DOUBLE_CLICK_INTERVAL_MS) {
            HandleDoubleClickEvent(info);
            return;
        }
    }
    HandleSingleClickEvent(info);
}

void RichEditorPattern::HandleSingleClickEvent(OHOS::Ace::GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "in handleSingleClickEvent");
    hasClicked_ = true;
    lastClickTimeStamp_ = info.GetTimeStamp();

    HandleClickAISpanEvent(info);
    if (isClickOnAISpan_ && selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->DisableMenu(true);
        return;
    }
    HandleUserClickEvent(info);
    if (textSelector_.IsValid() && !isMouseSelect_) {
        CloseSelectOverlay();
        ResetSelection();
    }

    caretUpdateType_ = CaretUpdateType::PRESSED;
    UseHostToUpdateTextFieldManager();

    auto textRect = GetTextRect();
    textRect.SetTop(textRect.GetY() - std::min(baselineOffset_, 0.0f));
    textRect.SetHeight(textRect.Height() - std::max(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textRect.GetX(),
        info.GetLocalLocation().GetY() - textRect.GetY() };

    auto position = paragraphs_.GetIndex(textOffset);
    AdjustCursorPosition(position);

    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (focusHub) {
        SetCaretPosition(position);
        if (!isClickOnAISpan_ && focusHub->RequestFocusImmediately()) {
            float caretHeight = 0.0f;
            OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight, false, false);
            CHECK_NULL_VOID(overlayMod_);
            DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(caretOffset, caretHeight);
            StartTwinkling();
            if (overlayMod_) {
                RequestKeyboard(false, true, true);
            }
        }
    }
    UseHostToUpdateTextFieldManager();
    CalcCaretInfoByClick(info);
}

void RichEditorPattern::HandleDoubleClickEvent(OHOS::Ace::GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "in double HandleDoubleClickEvent,use mouse:%{public}d", info.GetSourceDevice());
    caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    HandleDoubleClickOrLongPress(info);
}

bool RichEditorPattern::HandleUserGestureEvent(
    GestureEvent& info, std::function<bool(RefPtr<SpanItem> item, GestureEvent& info)>&& gestureFunc)
{
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    if (!textContentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY())) ||
        spans_.empty()) {
        return false;
    }
    PointF textOffset = { info.GetLocalLocation().GetX() - GetTextRect().GetX(),
        info.GetLocalLocation().GetY() - GetTextRect().GetY() };
    int32_t start = 0;
    bool isParagraphHead = true;
    Offset paragraphOffset(0, 0);
    for (const auto& item : spans_) {
        if (!item) {
            continue;
        }
        std::vector<RectF> selectedRects = paragraphs_.GetRects(start, item->position);
        start = item->position;
        if (isParagraphHead && !selectedRects.empty()) {
            if (item->leadingMargin.has_value()) {
                auto addWidth = item->leadingMargin.value().size.Width();
                selectedRects[0].SetLeft(selectedRects[0].GetX() - addWidth);
                selectedRects[0].SetWidth(selectedRects[0].GetSize().Width() + addWidth);
            }
            paragraphOffset.SetX(selectedRects[0].GetOffset().GetX());
            paragraphOffset.SetY(selectedRects[0].GetOffset().GetY());
            isParagraphHead = false;
        }
        if (!isParagraphHead && item->content.back() == '\n') {
            isParagraphHead = true;
        }
        for (auto&& rect : selectedRects) {
            if (!rect.IsInRegion(textOffset)) {
                continue;
            }
            info = info.SetScreenLocation(
                Offset(textOffset.GetX() - paragraphOffset.GetX(), textOffset.GetY() - paragraphOffset.GetY()));
            return gestureFunc(item, info);
        }
    }
    return false;
}

void RichEditorPattern::HandleClickAISpanEvent(GestureEvent& info)
{
    isClickOnAISpan_ = false;
    if (!NeedShowAIDetect()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    PointF textOffset = { info.GetLocalLocation().GetX() - GetTextRect().GetX(),
        info.GetLocalLocation().GetY() - GetTextRect().GetY() };
    for (const auto& kv : aiSpanMap_) {
        auto& aiSpan = kv.second;
        isClickOnAISpan_ = ClickAISpan(textOffset, aiSpan);
        if (isClickOnAISpan_) {
            return;
        }
    }
}

bool RichEditorPattern::ClickAISpan(const PointF& textOffset, const AISpan& aiSpan)
{
    auto calculateHandleFunc = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CalculateHandleOffsetAndShowOverlay();
    };
    auto showSelectOverlayFunc = [weak = WeakClaim(this)](const RectF& firstHandle, const RectF& secondHandle) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ShowSelectOverlay(firstHandle, secondHandle);
    };

    std::vector<RectF> aiRects = paragraphs_.GetRects(aiSpan.start, aiSpan.end);
    for (auto&& rect : aiRects) {
        if (rect.IsInRegion(textOffset)) {
            ShowUIExtensionMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
            return true;
        }
    }
    return false;
}

bool RichEditorPattern::HandleUserClickEvent(GestureEvent& info)
{
    auto clickFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool {
        if (item && item->onClick) {
            item->onClick(info);
            return true;
        }
        return false;
    };
    return HandleUserGestureEvent(info, std::move(clickFunc));
}

void RichEditorPattern::CalcCaretInfoByClick(GestureEvent& info)
{
    auto textRect = GetTextRect();
    auto touchOffset = info.GetLocalLocation();
    textRect.SetTop(textRect.GetY() - std::min(baselineOffset_, 0.0f));
    textRect.SetHeight(textRect.Height() - std::max(baselineOffset_, 0.0f));
    Offset textOffset = { touchOffset.GetX() - textRect.GetX(), touchOffset.GetY() - textRect.GetY() };
    // get the caret position
    auto position = paragraphs_.GetIndex(textOffset);
    // get the caret offset when click
    float selectLineHeight = 0.0f;
    auto lastClickOffset = paragraphs_.ComputeCursorInfoByClick(position, selectLineHeight,
        OffsetF(static_cast<float>(textOffset.GetX()), static_cast<float>(textOffset.GetY())));

    lastClickOffset.AddX(textRect.GetX());
    lastClickOffset.AddY(textRect.GetY());

    CHECK_NULL_VOID(overlayMod_);
    DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(lastClickOffset, selectLineHeight);
    SetLastClickOffset(lastClickOffset);

    MoveCaretToContentRect(lastClickOffset, selectLineHeight);
}

void RichEditorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEventInitialized_);
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
    CHECK_NULL_VOID(!focusEventInitialized_);
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
    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(std::move(keyTask));
}

bool RichEditorPattern::CheckBlurReason()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto curFocusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(curFocusHub, false);
    auto curBlurReason = curFocusHub->GetBlurReason();
    if (curBlurReason == BlurReason::FRAME_DESTROY) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TextFieldPattern CheckBlurReason, Close Keyboard.");
        return true;
    }
    return false;
}

void RichEditorPattern::HandleBlurEvent()
{
    if (textDetectEnable_) {
        isLongPress_ = false;
        StartAITask();
    }
    StopTwinkling();
    // The pattern handles blurevent, Need to close the softkeyboard first.
    if ((customKeyboardBuilder_ && isCustomKeyboardAttached_) || CheckBlurReason()) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "RichEditor Blur, Close Keyboard.");
        CloseKeyboard(true);
    }

    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
}

void RichEditorPattern::HandleFocusEvent()
{
    auto host = GetHost();
    if (host && textDetectEnable_ && !aiSpanMap_.empty()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    CancelAITask();
    UseHostToUpdateTextFieldManager();
    StartTwinkling();
    if (!usingMouseRightButton_ && !isLongPress_ && !isDragging_) {
        RequestKeyboard(false, true, true);
    }
}

void RichEditorPattern::UseHostToUpdateTextFieldManager()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto globalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
}

void RichEditorPattern::OnVisibleChange(bool isVisible)
{
    TextPattern::OnVisibleChange(isVisible);
    StopTwinkling();
    CloseKeyboard(true);
}

bool RichEditorPattern::CloseKeyboard(bool forceClose)
{
    CloseSelectOverlay();
    ResetSelection();
    if (forceClose) {
        if (customKeyboardBuilder_ && isCustomKeyboardAttached_) {
            return CloseCustomKeyboard();
        }
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Request close soft keyboard.");
#if defined(ENABLE_STANDARD_INPUT)
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        if (!imeAttached_) {
            return false;
        }
#endif
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        CHECK_NULL_RETURN(inputMethod, false);
        inputMethod->HideTextInput();
        inputMethod->Close();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeAttached_ = false;
#endif
#else
        if (HasConnection()) {
            connection_->Close(GetInstanceId());
            connection_ = nullptr;
        }
#endif
        return true;
    }
    return false;
}

bool RichEditorPattern::JudgeDraggable(GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    if (copyOption_ == CopyOptions::None) {
        return false;
    }
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, false);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    if (BetweenSelectedPosition(info.GetGlobalLocation())) {
        dragBoxes_ = GetTextBoxes();
        // prevent long press event from being triggered when dragging
        gestureHub->SetIsTextDraggable(true);
        return true;
    }
    gestureHub->SetIsTextDraggable(false);
    return false;
}

void RichEditorPattern::HandleLongPress(GestureEvent& info)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "handle long press!");
    caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    HandleDoubleClickOrLongPress(info);
}

void RichEditorPattern::HandleDoubleClickOrLongPress(GestureEvent& info)
{
    HandleUserLongPressEvent(info);
    if (JudgeDraggable(info) || isMousePressed_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    isLongPress_ = true;
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    InitSelection(textOffset);
    auto selectEnd = std::max(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto selectStart = std::min(textSelector_.baseOffset, textSelector_.destinationOffset);

    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    UpdateSelectionType(textSelectInfo);
    CalculateHandleOffsetAndShowOverlay();
    if (IsShowSelectMenuUsingMouse()) {
        CloseSelectOverlay();
    }
    selectionMenuOffset_ = info.GetGlobalLocation();
    if (info.GetSourceDevice() != SourceType::MOUSE || caretUpdateType_ != CaretUpdateType::DOUBLE_CLICK) {
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
        StopTwinkling();
    } else if (selectStart == selectEnd) {
        StartTwinkling();
    } else {
        StopTwinkling();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!textSelectInfo.GetSelection().resultObjects.empty()) {
        eventHub->FireOnSelect(&textSelectInfo);
    }
    SetCaretPosition(std::min(selectEnd, GetTextContentLength()));
    focusHub->RequestFocusImmediately();
    if (overlayMod_) {
        RequestKeyboard(false, true, true);
    }
}

bool RichEditorPattern::HandleUserLongPressEvent(GestureEvent& info)
{
    auto longPressFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool {
        if (item && item->onLongPress) {
            item->onLongPress(info);
            return true;
        }
        return false;
    };
    return HandleUserGestureEvent(info, std::move(longPressFunc));
}

void RichEditorPattern::HandleMenuCallbackOnSelectAll()
{
    auto textSize = static_cast<int32_t>(GetWideText().length()) + placeholderCount_;
    textSelector_.Update(0, textSize);
    CalculateHandleOffsetAndShowOverlay();
    if (IsShowSelectMenuUsingMouse()) {
        CloseSelectOverlay();
    }
    auto responseType = selectOverlayProxy_
                            ? static_cast<TextResponseType>(
                                  selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.responseType.value_or(0))
                            : TextResponseType::LONG_PRESS;
    selectMenuInfo_.showCopyAll = false;
    selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    selectOverlayProxy_.Reset();
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true, responseType);
    SetCaretPosition(textSize);
    MoveCaretToContentRect();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!longPressEvent_);
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureHub->SetLongPressEvent(longPressEvent_);

    auto onTextSelectorChange = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_SELECTION_UPDATE);
    };
    textSelector_.SetOnAccessibility(std::move(onTextSelectorChange));
}

void RichEditorPattern::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    gestureHub->SetThumbnailCallback(GetThumbnailCallback());
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart = [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                           const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo itemInfo;
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, itemInfo);
        pattern->timestamp_ = std::chrono::system_clock::now().time_since_epoch().count();
        auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
        eventHub->SetTimestamp(pattern->GetTimestamp());
        CHECK_NULL_RETURN(eventHub, itemInfo);
        pattern->showSelect_ = false;
        return pattern->OnDragStart(event, extraParams);
    };
    eventHub->SetOnDragStart(std::move(onDragStart));
    auto onDragMove = [weakPtr = WeakClaim(this)](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->showSelect_ = false;
        pattern->OnDragMove(event);
    };
    eventHub->SetOnDragMove(std::move(onDragMove));
    auto onDragEnd = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                         const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(scopeId);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->showSelect_ = true;
        pattern->StopAutoScroll();
        pattern->ClearRedoOperationRecords();
        pattern->OnDragEnd(event);
    };
    eventHub->SetOnDragEnd(std::move(onDragEnd));
    onDragDropAndLeave();
}

void RichEditorPattern::onDragDropAndLeave()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragDrop = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {};
    eventHub->SetOnDrop(std::move(onDragDrop));
    auto onDragDragLeave = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                               const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {
        ContainerScope scope(scopeId);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StopAutoScroll();
    };
    eventHub->SetOnDragLeave(onDragDragLeave);
}

void RichEditorPattern::ClearDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetIsTextDraggable(false);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(nullptr);
    eventHub->SetOnDragEnter(nullptr);
    eventHub->SetOnDragMove(nullptr);
    eventHub->SetOnDragLeave(nullptr);
    eventHub->SetOnDragEnd(nullptr);
    eventHub->SetOnDrop(nullptr);
}

void RichEditorPattern::OnDragMove(const RefPtr<OHOS::Ace::DragEvent>& event)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(theme);
    auto touchX = event->GetX();
    auto touchY = event->GetY();
    auto textRect = GetTextRect();
    textRect.SetTop(textRect.GetY() - std::min(baselineOffset_, 0.0f));
    Offset textOffset = { touchX - textRect.GetX() - GetParentGlobalOffset().GetX(),
        touchY - textRect.GetY() - GetParentGlobalOffset().GetY() - theme->GetInsertCursorOffset().ConvertToPx() };
    auto position = paragraphs_.GetIndex(textOffset);
    float caretHeight = 0.0f;
    SetCaretPosition(position);
    OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
    CHECK_NULL_VOID(overlayMod_);
    DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(caretOffset, caretHeight);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::DRAG, .showScrollbar = true };
    auto localOffset = OffsetF(touchX, touchY) - parentGlobalOffset_;
    AutoScrollByEdgeDetection(param, localOffset, EdgeDetectionStrategy::IN_BOUNDARY);
}

bool RichEditorPattern::SelectOverlayIsOn()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(selectOverlayProxy_, false);
    auto overlayId = selectOverlayProxy_->GetSelectOverlayId();
    return pipeline->GetSelectOverlayManager()->HasSelectOverlay(overlayId);
}

void RichEditorPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
    InsertValue(value->text);
}

void RichEditorPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    InsertValue("\n");
}

void RichEditorPattern::InitMouseEvent()
{
    CHECK_NULL_VOID(!mouseEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
    mouseEventInitialized_ = true;
}

void RichEditorPattern::OnHover(bool isHover)
{
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBar = GetScrollBar();
    if (isHover && !scrollBar->IsPressed()) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR);
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
}

bool RichEditorPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(needShowSoftKeyboard, false);
    if (needShowSoftKeyboard && customKeyboardBuilder_) {
        return RequestCustomKeyboard();
    }
#if defined(ENABLE_STANDARD_INPUT)
    if (!EnableStandardInput(needShowSoftKeyboard)) {
        return false;
    }
#else
    if (!UnableStandardInput(isFocusViewChanged)) {
        return false;
    }
#endif
    return true;
}

#if defined(ENABLE_STANDARD_INPUT)
#ifdef WINDOW_SCENE_SUPPORTED
uint32_t RichEditorPattern::GetSCBSystemWindowId()
{
    RefPtr<FrameNode> frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, {});
    auto focusSystemWindowId = WindowSceneHelper::GetFocusSystemWindowId(frameNode);
    return focusSystemWindowId;
}
#endif

bool RichEditorPattern::EnableStandardInput(bool needShowSoftKeyboard)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    MiscServices::Configuration configuration;
    configuration.SetEnterKeyType(static_cast<MiscServices::EnterKeyType>(static_cast<int32_t>(TextInputAction::DONE)));
    configuration.SetTextInputType(
        static_cast<MiscServices::TextInputType>(static_cast<int32_t>(TextInputType::UNSPECIFIED)));
    MiscServices::InputMethodController::GetInstance()->OnConfigurationChange(configuration);
    if (richEditTextChangeListener_ == nullptr) {
        richEditTextChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    CHECK_NULL_RETURN(inputMethod, false);
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_RETURN(miscTextConfig.has_value(), false);
    TAG_LOGI(
        AceLogTag::ACE_RICH_TEXT, "RequestKeyboard set calling window id is : %{public}u", miscTextConfig->windowId);
    MiscServices::TextConfig textconfig = miscTextConfig.value();
#ifdef WINDOW_SCENE_SUPPORTED
    auto systemWindowId = GetSCBSystemWindowId();
    if (systemWindowId) {
        miscTextConfig->windowId = systemWindowId;
    }
#endif
    inputMethod->Attach(richEditTextChangeListener_, needShowSoftKeyboard, textconfig);
    UpdateKeyboardOffset(textconfig.positionY, textconfig.height);
    if (context) {
        inputMethod->SetCallingWindow(context->GetWindowId());
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    imeAttached_ = true;
#endif
    return true;
}

std::optional<MiscServices::TextConfig> RichEditorPattern::GetMiscTextConfig()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, {});
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto windowRect = pipeline->GetCurrentWindowRect();
    double positionY = (tmpHost->GetPaintRectOffset() - pipeline->GetRootRect().GetOffset()).GetY() + windowRect.Top();
    double height = frameRect_.Height();

    float caretHeight = 0.0f;
    OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
    if (NearZero(caretHeight)) {
        auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
        caretHeight = overlayModifier ? overlayModifier->GetCaretHeight() : DEFAULT_CARET_HEIGHT;
    }
    auto offset = KEYBOARD_AVOID_OFFSET.ConvertToPx();
    auto caretTop = caretOffset.GetY() + windowRect.Top() + parentGlobalOffset_.GetY();
    height = caretTop + caretHeight + offset - positionY;

    MiscServices::CursorInfo cursorInfo { .left = caretOffset.GetX() + windowRect.Left() + parentGlobalOffset_.GetX(),
        .top = caretTop,
        .width = CARET_WIDTH,
        .height = caretHeight };
    MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)TextInputType::UNSPECIFIED,
        .enterKeyType = (int32_t)TextInputAction::DONE };
    MiscServices::TextConfig textConfig = { .inputAttribute = inputAttribute,
        .cursorInfo = cursorInfo,
        .range = { .start = textSelector_.GetStart(), .end = textSelector_.GetEnd() },
        .windowId = pipeline->GetFocusWindowId(),
        .positionY = positionY,
        .height = height };
    return textConfig;
}
#else
bool RichEditorPattern::UnableStandardInput(bool isFocusViewChanged)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    if (HasConnection()) {
        connection_->Show(isFocusViewChanged, GetInstanceId());
        return true;
    }
    TextInputConfiguration config;
    config.type = TextInputType::UNSPECIFIED;
    config.action = TextInputAction::DONE;
    config.obscureText = false;
    connection_ =
        TextInputProxy::GetInstance().Attach(WeakClaim(this), config, context->GetTaskExecutor(), GetInstanceId());
    if (!HasConnection()) {
        return false;
    }
    TextEditingValue value;
    if (spans_.empty()) {
        value.text = textForDisplay_;
    } else {
        for (auto it = spans_.begin(); it != spans_.end(); it++) {
            if ((*it)->placeholderIndex < 0) {
                value.text.append((*it)->content);
            } else {
                value.text.append(" ");
            }
        }
    }
    value.selection.Update(caretPosition_, caretPosition_);
    connection_->SetEditingState(value, GetInstanceId());
    connection_->Show(isFocusViewChanged, GetInstanceId());
    return true;
}
#endif

void RichEditorPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& spans = host->GetChildren();
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(theme->GetTextStyle().GetTextColor());
    textLayoutProperty->UpdateTextDecorationColor(theme->GetTextStyle().GetTextColor());
    for (auto span : spans) {
        auto spanNode = DynamicCast<SpanNode>(span);
        if (!spanNode) {
            continue;
        }
        auto spanItem = spanNode->GetSpanItem();
        if (!spanItem) {
            continue;
        }
        if (spanItem->hasResourceFontColor) {
            spanNode->UpdateTextColor(theme->GetTextStyle().GetTextColor());
        }
        if (spanItem->hasResourceDecorationColor) {
            spanNode->UpdateTextDecorationColor(theme->GetTextStyle().GetTextColor());
        }
    }
}

void RichEditorPattern::UpdateCaretInfoToController()
{
    CHECK_NULL_VOID(HasFocus());
    auto selectionResult = GetSpansInfo(0, GetTextContentLength(), GetSpansMethod::ONSELECT);
    auto resultObjects = selectionResult.GetSelection().resultObjects;
    std::string text = "";
    if (!resultObjects.empty()) {
        for (const auto& resultObj : resultObjects) {
            if (resultObj.type == SelectSpanType::TYPESPAN) {
                text += resultObj.valueString;
            }
        }
    }
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        StringUtils::Str8ToStr16(text), textSelector_.GetStart(), textSelector_.GetEnd());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "Caret position update, left %{public}f, top %{public}f, width %{public}f, height %{public}f; textSelector_ "
        "Start "
        "%{public}d, end %{public}d",
        cursorInfo.left, cursorInfo.top, cursorInfo.width, cursorInfo.height, textSelector_.GetStart(),
        textSelector_.GetEnd());
#else
    if (HasConnection()) {
        TextEditingValue editingValue;
        editingValue.text = text;
        editingValue.hint = "";
        editingValue.selection.Update(textSelector_.baseOffset, textSelector_.destinationOffset);
        connection_->SetEditingState(editingValue, GetInstanceId());
    }
#endif
}

bool RichEditorPattern::HasConnection() const
{
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    return imeAttached_;
#else
    return connection_ != nullptr;
#endif
}

bool RichEditorPattern::RequestCustomKeyboard()
{
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "RequestCKeyboard,close softkeyboard.");
        inputMethod->RequestHideInput();
        inputMethod->Close();
    }
#else
    if (HasConnection()) {
        connection_->Close(GetInstanceId());
        connection_ = nullptr;
    }
#endif

    if (isCustomKeyboardAttached_) {
        return true;
    }
    CHECK_NULL_RETURN(customKeyboardBuilder_, false);
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->BindKeyboard(customKeyboardBuilder_, frameNode->GetId());
    isCustomKeyboardAttached_ = true;
    keyboardOverlay_ = overlayManager;
    return true;
}

bool RichEditorPattern::CloseCustomKeyboard()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    CHECK_NULL_RETURN(keyboardOverlay_, false);
    keyboardOverlay_->CloseKeyboard(frameNode->GetId());
    isCustomKeyboardAttached_ = false;
    return true;
}

void RichEditorPattern::InsertValue(const std::string& insertValue)
{
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_ + moveLength_;
    if (textSelector_.IsValid()) {
        record.beforeCaretPosition = textSelector_.GetTextStart();
    }
    record.addText = insertValue;
    ClearRedoOperationRecords();
    InsertValueOperation(insertValue, &record);
    record.afterCaretPosition = caretPosition_ + moveLength_;
    AddOperationRecord(record);
}

void RichEditorPattern::InsertValueOperation(const std::string& insertValue, OperationRecord* const record)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Insert value '%{public}s'", insertValue.c_str());
    }
    bool isSelector = textSelector_.IsValid();
    if (isSelector) {
        SetCaretPosition(textSelector_.GetTextStart());
    }

    std::string insertValueTemp = insertValue;
    bool isLineSeparator = insertValueTemp == std::string("\n");

    auto isInsert = BeforeIMEInsertValue(insertValueTemp);
    CHECK_NULL_VOID(isInsert);
    TextInsertValueInfo info;
    CalcInsertValueObj(info);
    if (isSelector) {
        std::wstring deleteText = DeleteForwardOperation(textSelector_.GetTextEnd() - textSelector_.GetTextStart());
        if (record && deleteText.length() != 0) {
            record->deleteText = StringUtils::ToString(deleteText);
        }
        CloseSelectOverlay();
        ResetSelection();
    }
    if (!caretVisible_) {
        StartTwinkling();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<SpanNode> spanNode = DynamicCast<SpanNode>(host->GetChildAtIndex(info.GetSpanIndex()));
    if (spanNode == nullptr || spanNode->GetSpanItem()->unicode != 0) {
        InsertValueWithoutSpan(spanNode, info, insertValueTemp);
        return;
    }
    if (info.GetOffsetInSpan() == 0) {
        auto spanNodeBefore = DynamicCast<SpanNode>(host->GetChildAtIndex(info.GetSpanIndex() - 1));
        if (spanNodeBefore != nullptr && !IsLineSeparatorInLast(spanNodeBefore)) {
            InsertValueAfterBeforeSpan(spanNodeBefore, spanNode, info, insertValueTemp);
            return;
        }
    }
    if (typingStyle_.has_value() && !HasSameTypingStyle(spanNode)) {
        InsertDiffStyleValueInSpan(spanNode, info, insertValueTemp);
        return;
    }
    if (!isLineSeparator) {
        InsertValueToSpanNode(spanNode, insertValueTemp, info);
    } else {
        SpanNodeFission(spanNode, insertValueTemp, info);
    }
    AfterIMEInsertValue(spanNode, static_cast<int32_t>(StringUtils::ToWstring(insertValueTemp).length()), false);
}

void RichEditorPattern::InsertValueWithoutSpan(
    RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info, const std::string& insertValue)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (info.GetSpanIndex() == 0) {
        CreateTextSpanNode(spanNode, info, insertValue);
        return;
    }
    auto spanNodeBefore = DynamicCast<SpanNode>(host->GetChildAtIndex(info.GetSpanIndex() - 1));
    if (spanNodeBefore == nullptr || spanNodeBefore->GetSpanItem()->unicode != 0) {
        CreateTextSpanNode(spanNode, info, insertValue);
        return;
    }
    InsertValueAfterBeforeSpan(spanNodeBefore, spanNode, info, insertValue);
}

void RichEditorPattern::InsertValueAfterBeforeSpan(RefPtr<SpanNode>& spanNodeBefore, RefPtr<SpanNode>& spanNode,
    const TextInsertValueInfo& info, const std::string& insertValue)
{
    if (typingStyle_.has_value() && !HasSameTypingStyle(spanNodeBefore)) {
        CreateTextSpanNode(spanNode, info, insertValue);
        CopyTextSpanLineStyle(spanNodeBefore, spanNode, true);
        return;
    }
    auto spanNodeGet = InsertValueToBeforeSpan(spanNodeBefore, insertValue);
    bool isCreate = spanNodeBefore->GetId() != spanNodeGet->GetId();
    AfterIMEInsertValue(
        spanNodeGet, static_cast<int32_t>(StringUtils::ToWstring(insertValue).length()), isCreate);
}

void RichEditorPattern::InsertDiffStyleValueInSpan(
    RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info, const std::string& insertValue)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TextSpanOptions options;
    options.value = insertValue;
    options.offset = caretPosition_;
    options.style = typingTextStyle_;
    auto newSpanIndex = AddTextSpanOperation(options, false, -1,  true);
    auto newSpanNode = DynamicCast<SpanNode>(host->GetChildAtIndex(newSpanIndex));
    CopyTextSpanLineStyle(spanNode, newSpanNode, true);
    AfterIMEInsertValue(spanNode, static_cast<int32_t>(StringUtils::ToWstring(insertValue).length()), true);
}

bool RichEditorPattern::IsLineSeparatorInLast(RefPtr<SpanNode>& spanNode)
{
    auto spanItem = spanNode->GetSpanItem();
    auto text = spanItem->content;
    std::wstring textTemp = StringUtils::ToWstring(text);
    auto index = textTemp.find(lineSeparator);
    if (index != std::wstring::npos) {
        auto textBefore = textTemp.substr(0, index + 1);
        auto textAfter = textTemp.substr(index + 1);
        if (textAfter.empty()) {
            return true;
        }
    }
    return false;
}

void RichEditorPattern::InsertValueToSpanNode(
    RefPtr<SpanNode>& spanNode, const std::string& insertValue, const TextInsertValueInfo& info)
{
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    auto text = spanItem->content;
    std::wstring textTemp = StringUtils::ToWstring(text);
    std::wstring insertValueTemp = StringUtils::ToWstring(insertValue);
    textTemp.insert(info.GetOffsetInSpan(), insertValueTemp);
    text = StringUtils::ToString(textTemp);
    spanNode->UpdateContent(text);
    spanItem->position += static_cast<int32_t>(StringUtils::ToWstring(insertValue).length());
}

void RichEditorPattern::SpanNodeFission(
    RefPtr<SpanNode>& spanNode, const std::string& insertValue, const TextInsertValueInfo& info)
{
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    auto text = spanItem->content;
    std::wstring textTemp = StringUtils::ToWstring(text);
    std::wstring insertValueTemp = StringUtils::ToWstring(insertValue);
    textTemp.insert(info.GetOffsetInSpan(), insertValueTemp);

    auto index = textTemp.find(lineSeparator);
    if (index != std::wstring::npos) {
        auto textBefore = textTemp.substr(0, index + 1);
        auto textAfter = textTemp.substr(index + 1);
        text = StringUtils::ToString(textBefore);
        spanNode->UpdateContent(text);
        spanItem->position += 1 - static_cast<int32_t>(textAfter.length());
        if (!textAfter.empty()) {
            TextInsertValueInfo infoAfter;
            infoAfter.SetSpanIndex(info.GetSpanIndex() + 1);
            infoAfter.SetOffsetInSpan(0);
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
            RefPtr<SpanNode> spanNodeAfter = SpanNode::GetOrCreateSpanNode(nodeId);
            spanNodeAfter->MountToParent(host, infoAfter.GetSpanIndex());
            spanNodeAfter->UpdateContent(StringUtils::ToString(textAfter));
            CopyTextSpanStyle(spanNode, spanNodeAfter);
        }
    } else {
        text = StringUtils::ToString(textTemp);
        spanNode->UpdateContent(text);
        spanItem->position += static_cast<int32_t>(StringUtils::ToWstring(insertValue).length());
    }
}

RefPtr<SpanNode> RichEditorPattern::InsertValueToBeforeSpan(
    RefPtr<SpanNode>& spanNodeBefore, const std::string& insertValue)
{
    auto spanItem = spanNodeBefore->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, spanNodeBefore);
    auto text = spanItem->content;
    std::wstring textTemp = StringUtils::ToWstring(text);
    std::wstring insertValueTemp = StringUtils::ToWstring(insertValue);
    textTemp.append(insertValueTemp);

    auto index = textTemp.find(lineSeparator);
    if (index != std::wstring::npos) {
        auto textBefore = textTemp.substr(0, index + 1);
        auto textAfter = textTemp.substr(index + 1);
        text = StringUtils::ToString(textBefore);
        spanNodeBefore->UpdateContent(text);
        spanItem->position += static_cast<int32_t>(insertValueTemp.length()) - static_cast<int32_t>(textAfter.length());
        if (!textAfter.empty()) {
            auto host = GetHost();
            CHECK_NULL_RETURN(spanItem, spanNodeBefore);
            TextInsertValueInfo infoAfter;
            infoAfter.SetSpanIndex(host->GetChildIndex(spanNodeBefore) + 1);
            infoAfter.SetOffsetInSpan(0);
            auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
            RefPtr<SpanNode> spanNodeAfter = SpanNode::GetOrCreateSpanNode(nodeId);
            spanNodeAfter->MountToParent(host, infoAfter.GetSpanIndex());
            spanNodeAfter->UpdateContent(StringUtils::ToString(textAfter));
            CopyTextSpanStyle(spanNodeBefore, spanNodeAfter);
            auto spanItemAfter = spanNodeAfter->GetSpanItem();
            spanItemAfter->position = static_cast<int32_t>(textTemp.length());
            spanItemAfter->hasResourceFontColor = spanItem->hasResourceFontColor;
            spanItemAfter->hasResourceDecorationColor = spanItem->hasResourceDecorationColor;
            AddSpanItem(spanItemAfter, host->GetChildIndex(spanNodeBefore) + 1);
            SpanNodeFission(spanNodeAfter);
            return spanNodeAfter;
        }
    } else {
        text = StringUtils::ToString(textTemp);
        spanNodeBefore->UpdateContent(text);
        spanItem->position += static_cast<int32_t>(StringUtils::ToWstring(insertValue).length());
    }
    return spanNodeBefore;
}

void RichEditorPattern::CreateTextSpanNode(
    RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info, const std::string& insertValue, bool isIME)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    spanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    spanNode->MountToParent(host, info.GetSpanIndex());
    auto spanItem = spanNode->GetSpanItem();
    spanItem->hasResourceFontColor = true;
    spanItem->hasResourceDecorationColor = true;
    spanNode->UpdateContent(insertValue);
    AddSpanItem(spanItem, info.GetSpanIndex());
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        UpdateTextStyle(spanNode, typingStyle_.value(), typingTextStyle_.value());
        auto spanItem = spanNode->GetSpanItem();
        spanItem->SetTextStyle(typingTextStyle_);
    } else {
        spanNode->UpdateFontSize(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP));
        spanNode->AddPropertyInfo(PropertyInfo::FONTSIZE);
    }
    if (isIME) {
        AfterIMEInsertValue(spanNode, static_cast<int32_t>(StringUtils::ToWstring(insertValue).length()), true);
    }
}

bool RichEditorPattern::BeforeIMEInsertValue(const std::string& insertValue)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    RichEditorInsertValue insertValueInfo;
    insertValueInfo.SetInsertOffset(caretPosition_);
    insertValueInfo.SetInsertValue(insertValue);
    return eventHub->FireAboutToIMEInput(insertValueInfo);
}

void RichEditorPattern::AfterIMEInsertValue(const RefPtr<SpanNode>& spanNode, int32_t insertValueLength, bool isCreate)
{
    RichEditorAbstractSpanResult retInfo;
    isTextChange_ = true;
    moveDirection_ = MoveDirection::FORWARD;
    moveLength_ += insertValueLength;
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    retInfo.SetSpanIndex(host->GetChildIndex(spanNode));
    retInfo.SetEraseLength(insertValueLength);
    retInfo.SetValue(spanNode->GetSpanItem()->content);
    auto contentLength = StringUtils::ToWstring(spanNode->GetSpanItem()->content).length();
    if (isCreate) {
        auto spanStart = 0;
        auto spanEnd = static_cast<int32_t>(contentLength);
        retInfo.SetSpanRangeStart(spanStart);
        retInfo.SetSpanRangeEnd(spanEnd);
        retInfo.SetOffsetInSpan(0);
    } else {
        auto spanEnd = spanNode->GetSpanItem()->position;
        auto spanStart = spanEnd - static_cast<int32_t>(contentLength);
        retInfo.SetSpanRangeStart(spanStart);
        retInfo.SetSpanRangeEnd(spanEnd);
        retInfo.SetOffsetInSpan(GetCaretPosition() - retInfo.GetSpanRangeStart());
    }
    retInfo.SetFontColor(spanNode->GetTextColorValue(Color::BLACK).ColorToString());
    retInfo.SetFontSize(spanNode->GetFontSizeValue(Dimension(16.0f, DimensionUnit::VP)).ConvertToVp());
    retInfo.SetFontStyle(spanNode->GetItalicFontStyleValue(OHOS::Ace::FontStyle::NORMAL));
    retInfo.SetFontWeight(static_cast<int32_t>(spanNode->GetFontWeightValue(FontWeight::NORMAL)));
    std::string fontFamilyValue;
    auto fontFamily = spanNode->GetFontFamilyValue({ "HarmonyOS Sans" });
    for (const auto& str : fontFamily) {
        fontFamilyValue += str;
    }
    retInfo.SetFontFamily(fontFamilyValue);
    retInfo.SetTextDecoration(spanNode->GetTextDecorationValue(TextDecoration::NONE));
    retInfo.SetColor(spanNode->GetTextDecorationColorValue(Color::BLACK).ColorToString());
    UpdateSpanPosition();
    MoveCaretAfterTextChange();
    eventHub->FireOnIMEInputComplete(retInfo);
}

void RichEditorPattern::ResetFirstNodeStyle()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto spans = tmpHost->GetChildren();
    if (!spans.empty()) {
        auto&& firstNode = DynamicCast<SpanNode>(*(spans.begin()));
        if (firstNode) {
            firstNode->ResetTextAlign();
            firstNode->ResetLeadingMargin();
            tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void RichEditorPattern::FireOnDeleteComplete(const RichEditorDeleteValue& info)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto isDelete = eventHub->FireAboutToDelete(info);
    if (isDelete) {
        DeleteByDeleteValueInfo(info);
        eventHub->FireOnDeleteComplete();
    }
}

void RichEditorPattern::HandleOnDelete(bool backward)
{
    backward ? DeleteBackward(1) : DeleteForward(1);
}

void RichEditorPattern::DeleteBackward(int32_t length)
{
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_;
    std::wstring deleteText = DeleteBackwardOperation(length);
    if (deleteText.length() != 0) {
        ClearRedoOperationRecords();
        record.deleteText = StringUtils::ToString(deleteText);
        record.afterCaretPosition = caretPosition_;
        AddOperationRecord(record);
    }
}

std::wstring RichEditorPattern::DeleteBackwardOperation(int32_t length)
{
    if (textSelector_.IsValid()) {
        length = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
        SetCaretPosition(textSelector_.GetTextEnd());
        CloseSelectOverlay();
        ResetSelection();
    }
    std::wstringstream wss;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        wss << StringUtils::ToWstring((*iter)->content);
    }
    auto textContent = wss.str();
    if (static_cast<int32_t>(textContent.length()) != GetTextContentLength()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "textContent length mismatch, %{public}d vs. %{public}d",
            static_cast<int32_t>(textContent.length()), GetTextContentLength());
    }
    auto start = std::clamp(caretPosition_ - length, 0, static_cast<int32_t>(textContent.length()));
    std::wstring deleteText =
        textContent.substr(static_cast<uint32_t>(start), static_cast<uint32_t>(caretPosition_ - start));
    RichEditorDeleteValue info;
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::BACKWARD);
    if (caretPosition_ == 0) {
        info.SetLength(0);
        ResetFirstNodeStyle();
        FireOnDeleteComplete(info);
        return deleteText;
    }
    if (length == spans_.back()->position) {
        ResetFirstNodeStyle();
        textForDisplay_.clear();
    }
    info.SetOffset(caretPosition_ - 1);
    info.SetLength(length);
    int32_t currentPosition = std::clamp((caretPosition_ - length), 0, static_cast<int32_t>(GetTextContentLength()));
    if (!spans_.empty()) {
        CalcDeleteValueObj(currentPosition, length, info);
        FireOnDeleteComplete(info);
    }
    if (!caretVisible_) {
        StartTwinkling();
    }
    return deleteText;
}

void RichEditorPattern::DeleteForward(int32_t length)
{
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_;
    std::wstring deleteText = DeleteForwardOperation(length);
    if (deleteText.length() != 0) {
        ClearRedoOperationRecords();
        record.deleteText = StringUtils::ToString(deleteText);
        record.afterCaretPosition = caretPosition_;
        AddOperationRecord(record);
    }
}

std::wstring RichEditorPattern::DeleteForwardOperation(int32_t length)
{
    if (textSelector_.IsValid()) {
        length = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
        SetCaretPosition(textSelector_.GetTextStart());
        CloseSelectOverlay();
        ResetSelection();
    }
    std::wstringstream wss;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        wss << StringUtils::ToWstring((*iter)->content);
    }
    auto textContent = wss.str();
    if (static_cast<int32_t>(textContent.length()) != GetTextContentLength()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "textContent length mismatch, %{public}d vs. %{public}d",
            static_cast<int32_t>(textContent.length()), GetTextContentLength());
    }
    auto end = std::clamp(caretPosition_ + length, 0, static_cast<int32_t>(textContent.length()));
    std::wstring deleteText = textContent.substr(
        static_cast<uint32_t>(std::clamp(caretPosition_, 0, static_cast<int32_t>(textContent.length()))),
        static_cast<uint32_t>(end - caretPosition_));
    if (caretPosition_ == GetTextContentLength()) {
        return deleteText;
    }
    RichEditorDeleteValue info;
    info.SetOffset(caretPosition_);
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::FORWARD);
    info.SetLength(length);
    int32_t currentPosition = caretPosition_;
    if (!spans_.empty()) {
        CalcDeleteValueObj(currentPosition, length, info);
        auto eventHub = GetEventHub<RichEditorEventHub>();
        CHECK_NULL_RETURN(eventHub, deleteText);
        auto isDelete = eventHub->FireAboutToDelete(info);
        if (isDelete) {
            DeleteByDeleteValueInfo(info);
            eventHub->FireOnDeleteComplete();
        }
    }
    if (!caretVisible_) {
        StartTwinkling();
    }
    return deleteText;
}

bool RichEditorPattern::OnBackPressed()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "RichEditor %{public}d receives back press event", tmpHost->GetId());
    if (SelectOverlayIsOn()) {
        CloseSelectOverlay();
        textSelector_.Update(textSelector_.destinationOffset);
        StartTwinkling();
        return true;
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (!imeShown_ && !isCustomKeyboardAttached_) {
#else
    if (!isCustomKeyboardAttached_) {
#endif
        return false;
    }
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    CloseKeyboard(true);
    FocusHub::LostFocusToViewRoot();
#if defined(ANDROID_PLATFORM)
    return false;
#else
    return true;
#endif
}

void RichEditorPattern::SetInputMethodStatus(bool keyboardShown)
{
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    imeShown_ = keyboardShown;
#endif
}

bool RichEditorPattern::CursorMoveLeft()
{
    CloseSelectOverlay();
    ResetSelection();
    auto caretPosition = std::clamp((caretPosition_ - 1), 0, static_cast<int32_t>(GetTextContentLength()));
    if (caretPosition_ == caretPosition) {
        return false;
    }
    SetCaretPosition(caretPosition);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveRight()
{
    CloseSelectOverlay();
    ResetSelection();
    auto caretPosition = std::clamp((caretPosition_ + 1), 0, static_cast<int32_t>(GetTextContentLength()));
    if (caretPosition_ == caretPosition) {
        return false;
    }
    SetCaretPosition(caretPosition);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveUp()
{
    CloseSelectOverlay();
    ResetSelection();
    if (static_cast<int32_t>(GetTextContentLength()) > 1) {
        float caretHeight = 0.0f;
        OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
        auto minDet = paragraphs_.minParagraphFontSize.value_or(0.0f) / 2.0;
        int32_t caretPosition = paragraphs_.GetIndex(
            Offset(caretOffset.GetX() - GetTextRect().GetX(), caretOffset.GetY() - GetTextRect().GetY() - minDet));
        caretPosition = std::clamp(caretPosition, 0, static_cast<int32_t>(GetTextContentLength()));
        if (caretPosition_ == caretPosition) {
            return false;
        }
        SetCaretPosition(caretPosition);
        MoveCaretToContentRect();
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveDown()
{
    CloseSelectOverlay();
    ResetSelection();
    if (static_cast<int32_t>(GetTextContentLength()) > 1) {
        float caretHeight = 0.0f;
        OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
        auto minDet = paragraphs_.minParagraphFontSize.value() / 2.0;
        int32_t caretPosition = paragraphs_.GetIndex(Offset(caretOffset.GetX() - GetTextRect().GetX(),
            caretOffset.GetY() - GetTextRect().GetY() + caretHeight + minDet / 2.0));
        caretPosition = std::clamp(caretPosition, 0, static_cast<int32_t>(GetTextContentLength()));
        if (caretPosition_ == caretPosition) {
            return false;
        }
        SetCaretPosition(caretPosition);
        MoveCaretToContentRect();
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveLeftWord()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetLeftWordPosition(caretPosition_);
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveRightWord()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetRightWordPosition(caretPosition_);
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveToParagraphBegin()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetParagraphBeginPosition(caretPosition_);
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveToParagraphEnd()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetParagraphEndPosition(caretPosition_);
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveHome()
{
    CloseSelectOverlay();
    ResetSelection();
    if (0 == caretPosition_) {
        return false;
    }
    SetCaretPosition(0);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveEnd()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetTextContentLength();
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

int32_t RichEditorPattern::GetLeftWordPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    bool jumpSpace = true;
    for (auto iter = spans_.rbegin(); iter != spans_.rend(); iter++) {
        auto span = *iter;
        auto content = StringUtils::ToWstring(span->content);
        if (caretPosition <= span->position - static_cast<int32_t>(content.length())) {
            continue;
        }
        int32_t position = span->position;
        for (auto i = content.length() - 1; i >= 0; i--) {
            if (position-- > caretPosition) {
                continue;
            }
            if (content[i] != L' ' || span->placeholderIndex >= 0) {
                jumpSpace = false;
            }
            if (position + 1 == caretPosition) {
                if (!(StringUtils::IsLetterOrNumberForWchar(content[i]) ||
                        (content[i] == L' ' && span->placeholderIndex < 0))) {
                    return std::clamp(caretPosition - 1, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            if (!jumpSpace) {
                if (!StringUtils::IsLetterOrNumberForWchar(content[i])) {
                    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            } else {
                if (content[i] == L' ' && span->placeholderIndex >= 0) {
                    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            offset++;
        }
    }
    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

int32_t RichEditorPattern::GetRightWordPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    bool jumpSpace = false;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        auto span = *iter;
        auto content = StringUtils::ToWstring(span->content);
        if (caretPosition > span->position) {
            continue;
        }
        int32_t position = span->position - static_cast<int32_t>(content.length());
        for (size_t i = 0; i < content.length(); i++) {
            if (position++ < caretPosition) {
                continue;
            }
            if (content[i] == L' ' && span->placeholderIndex < 0) {
                jumpSpace = true;
                offset++;
                continue;
            }
            if (position - 1 == caretPosition) {
                if (!StringUtils::IsLetterOrNumberForWchar(content[i])) {
                    return std::clamp(caretPosition + 1, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            if (jumpSpace) {
                if (content[i] != L' ' || span->placeholderIndex >= 0) {
                    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            } else {
                if (!(StringUtils::IsLetterOrNumberForWchar(content[i]) ||
                        (content[i] == L' ' && span->placeholderIndex < 0))) {
                    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            offset++;
        }
    }
    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

int32_t RichEditorPattern::GetParagraphBeginPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    for (auto iter = spans_.rbegin(); iter != spans_.rend(); iter++) {
        auto span = *iter;
        auto content = StringUtils::ToWstring(span->content);
        if (caretPosition <= span->position - static_cast<int32_t>(content.length())) {
            continue;
        }
        int32_t position = span->position;
        for (auto i = content.length() - 1; i >= 0; i--) {
            if (position-- > caretPosition) {
                continue;
            }
            if (content[i] == L'\n') {
                return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
            }
            offset++;
        }
    }
    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

int32_t RichEditorPattern::GetParagraphEndPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        auto span = *iter;
        auto content = StringUtils::ToWstring(span->content);
        if (caretPosition > span->position) {
            continue;
        }
        int32_t position = span->position - static_cast<int32_t>(content.length());
        for (size_t i = 0; i < content.length(); i++) {
            if (position++ < caretPosition) {
                continue;
            }
            if (content[i] == L'\n') {
                return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
            }
            offset++;
        }
    }
    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

void RichEditorPattern::HandleOnSelectAll()
{
    CloseSelectOverlay();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t newPos = static_cast<int32_t>(GetTextContentLength());
    textSelector_.Update(0, newPos);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::HandleSelect(CaretMoveIntent direction)
{
    CloseSelectOverlay();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t newPos, fixedPos = caretPosition_;
    if (IsSelected()) {
        fixedPos = (caretPosition_ == textSelector_.GetTextStart() ? textSelector_.GetTextEnd()
                                                                   : textSelector_.GetTextStart());
    }
    switch (direction) {
        case CaretMoveIntent::Left:
            newPos = caretPosition_ - 1;
            break;
        case CaretMoveIntent::Right:
            newPos = caretPosition_ + 1;
            break;
        case CaretMoveIntent::Up: {
            float caretHeight = 0.0f;
            OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
            auto minDet = paragraphs_.minParagraphFontSize.value() / 2.0;
            newPos = paragraphs_.GetIndex(
                Offset(caretOffset.GetX() - GetTextRect().GetX(), caretOffset.GetY() - GetTextRect().GetY() - minDet));
            break;
        }
        case CaretMoveIntent::Down: {
            float caretHeight = 0.0f;
            OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
            auto minDet = paragraphs_.minParagraphFontSize.value() / 2.0;
            newPos = paragraphs_.GetIndex(Offset(caretOffset.GetX() - GetTextRect().GetX(),
                caretOffset.GetY() - GetTextRect().GetY() + caretHeight + minDet / 2.0));
            break;
        }
        default:
            LOGW("Unsupported select operation for rich editor");
            return;
    }
    newPos = std::clamp(newPos, 0, static_cast<int32_t>(GetTextContentLength()));
    if (newPos == caretPosition_) {
        return;
    }
    textSelector_.Update(newPos, fixedPos);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::ClearOperationRecords()
{
    ClearRedoOperationRecords();
    if (operationRecords_.empty()) {
        return;
    }
    operationRecords_.clear();
}

void RichEditorPattern::ClearRedoOperationRecords()
{
    if (redoOperationRecords_.empty()) {
        return;
    }
    redoOperationRecords_.clear();
}

void RichEditorPattern::AddOperationRecord(const OperationRecord& record)
{
    if (operationRecords_.size() >= RECORD_MAX_LENGTH) {
        // case of max length is 0
        if (operationRecords_.empty()) {
            return;
        }
        operationRecords_.erase(operationRecords_.begin());
    }
    operationRecords_.emplace_back(record);
}

bool RichEditorPattern::HandleOnEscape()
{
    CloseSelectOverlay();
    return false;
}

void RichEditorPattern::HandleOnUndoAction()
{
    if (operationRecords_.empty()) {
        return;
    }
    auto value = operationRecords_.back();
    operationRecords_.pop_back();
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH && !(redoOperationRecords_.empty())) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    redoOperationRecords_.push_back(value);
    CloseSelectOverlay();
    ResetSelection();
    if (value.addText.has_value() && value.deleteText.has_value()) {
        SetCaretPosition(value.afterCaretPosition);
        DeleteBackwardOperation(StringUtils::ToWstring(value.addText.value_or("")).length());
        InsertValueOperation(value.deleteText.value_or(""));
        return;
    }
    if (value.addText.has_value()) {
        SetCaretPosition(value.afterCaretPosition);
        DeleteBackwardOperation(StringUtils::ToWstring(value.addText.value_or("")).length());
    }
    if (value.deleteText.has_value()) {
        SetCaretPosition(value.afterCaretPosition);
        InsertValueOperation(value.deleteText.value_or(""));
    }
}

void RichEditorPattern::HandleOnRedoAction()
{
    if (redoOperationRecords_.empty()) {
        return;
    }
    auto value = redoOperationRecords_.back();
    redoOperationRecords_.pop_back();
    if (value.addText.has_value() && value.deleteText.has_value()) {
        SetCaretPosition(value.beforeCaretPosition);
        DeleteForwardOperation(StringUtils::ToWstring(value.deleteText.value_or("")).length());
        InsertValueOperation(value.addText.value_or(""));
        operationRecords_.push_back(value);
        return;
    }
    if (value.deleteText.has_value()) {
        SetCaretPosition(value.beforeCaretPosition);
        if (value.beforeCaretPosition != value.afterCaretPosition) {
            DeleteBackwardOperation(StringUtils::ToWstring(value.deleteText.value_or("")).length());
        } else {
            DeleteForwardOperation(StringUtils::ToWstring(value.deleteText.value_or("")).length());
        }
    }
    if (value.addText.has_value()) {
        SetCaretPosition(value.beforeCaretPosition);
        InsertValueOperation(value.addText.value_or(""));
    }
    operationRecords_.push_back(value);
}

void RichEditorPattern::CalcInsertValueObj(TextInsertValueInfo& info)
{
    if (spans_.empty()) {
        info.SetSpanIndex(0);
        info.SetOffsetInSpan(0);
        return;
    }
    auto it = std::find_if(
        spans_.begin(), spans_.end(), [caretPosition = caretPosition_ + moveLength_](const RefPtr<SpanItem>& spanItem) {
            return (spanItem->position - static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length()) <=
                       caretPosition) &&
                   (caretPosition < spanItem->position);
        });
    if (it != spans_.end() && (*it)->unicode != 0 && (*it)->position - caretPosition_ + moveLength_ == 1) {
        it++;
        moveLength_++;
    }
    info.SetSpanIndex(std::distance(spans_.begin(), it));
    if (it == spans_.end()) {
        info.SetOffsetInSpan(0);
        return;
    }
    info.SetOffsetInSpan(
        caretPosition_ + moveLength_ - ((*it)->position - StringUtils::ToWstring((*it)->content).length()));
}

void RichEditorPattern::CalcDeleteValueObj(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info)
{
    auto it =
        std::find_if(spans_.begin(), spans_.end(), [caretPosition = currentPosition](const RefPtr<SpanItem>& spanItem) {
            return (spanItem->position - static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length()) <=
                       caretPosition) &&
                   (caretPosition < spanItem->position);
        });
    while (it != spans_.end() && length > 0) {
        if ((*it)->placeholderIndex >= 0 || (*it)->unicode != 0) {
            RichEditorAbstractSpanResult spanResult;
            spanResult.SetSpanIndex(std::distance(spans_.begin(), it));
            int32_t eraseLength = 0;
            if ((*it)->unicode != 0) {
                eraseLength = DeleteValueSetSymbolSpan(*it, spanResult);
            } else if (AceType::InstanceOf<ImageSpanItem>(*it)) {
                eraseLength = DeleteValueSetImageSpan(*it, spanResult);
            } else {
                eraseLength = DeleteValueSetBuilderSpan(*it, spanResult);
            }
            currentPosition += eraseLength;
            length -= eraseLength;
            info.SetRichEditorDeleteSpans(spanResult);
        } else {
            RichEditorAbstractSpanResult spanResult;
            spanResult.SetSpanIndex(std::distance(spans_.begin(), it));
            auto eraseLength = DeleteValueSetTextSpan(*it, currentPosition, length, spanResult);
            length -= eraseLength;
            currentPosition += eraseLength;
            info.SetRichEditorDeleteSpans(spanResult);
        }
        std::advance(it, 1);
    }
}

int32_t RichEditorPattern::DeleteValueSetSymbolSpan(
    const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::SYMBOL);
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetSpanRangeStart(spanItem->position - SYMBOL_SPAN_LENGTH);
    if (GetCaretPosition() < spanItem->position) {
        spanResult.SetEraseLength(1);
    } else {
        spanResult.SetEraseLength(SYMBOL_SPAN_LENGTH);
    }
    return SYMBOL_SPAN_LENGTH;
}

int32_t RichEditorPattern::DeleteValueSetImageSpan(
    const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::IMAGE);
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetSpanRangeStart(spanItem->position - 1);
    spanResult.SetEraseLength(1);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, IMAGE_SPAN_LENGTH);
    auto uiNode = host->GetChildAtIndex(spanResult.GetSpanIndex());
    CHECK_NULL_RETURN(uiNode, IMAGE_SPAN_LENGTH);
    auto imageNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(imageNode, IMAGE_SPAN_LENGTH);
    auto geometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, IMAGE_SPAN_LENGTH);
    auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
    CHECK_NULL_RETURN(imageLayoutProperty, IMAGE_SPAN_LENGTH);
    spanResult.SetSizeWidth(geometryNode->GetMarginFrameSize().Width());
    spanResult.SetSizeHeight(geometryNode->GetMarginFrameSize().Height());
    if (!imageLayoutProperty->GetImageSourceInfo()->GetPixmap()) {
        spanResult.SetValueResourceStr(imageLayoutProperty->GetImageSourceInfo()->GetSrc());
    } else {
        spanResult.SetValuePixelMap(imageLayoutProperty->GetImageSourceInfo()->GetPixmap());
    }
    if (imageLayoutProperty->HasImageFit()) {
        spanResult.SetImageFit(imageLayoutProperty->GetImageFitValue());
    }
    if (imageLayoutProperty->HasVerticalAlign()) {
        spanResult.SetVerticalAlign(imageLayoutProperty->GetVerticalAlignValue());
    }
    return IMAGE_SPAN_LENGTH;
}

int32_t RichEditorPattern::DeleteValueSetBuilderSpan(
    const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::IMAGE);
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetSpanRangeStart(spanItem->position - 1);
    spanResult.SetEraseLength(1);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 1);
    auto uiNode = host->GetChildAtIndex(spanResult.GetSpanIndex());
    CHECK_NULL_RETURN(uiNode, 1);
    auto builderNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(builderNode, 1);
    auto geometryNode = builderNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 1);
    spanResult.SetSizeWidth(geometryNode->GetMarginFrameSize().Width());
    spanResult.SetSizeHeight(geometryNode->GetMarginFrameSize().Height());
    return 1;
}

int32_t RichEditorPattern::DeleteValueSetTextSpan(
    const RefPtr<SpanItem>& spanItem, int32_t currentPosition, int32_t length, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::TEXT);
    auto contentStartPosition = spanItem->position - StringUtils::ToWstring(spanItem->content).length();
    spanResult.SetSpanRangeStart(contentStartPosition);
    int32_t eraseLength = 0;
    if (spanItem->position - currentPosition >= length) {
        eraseLength = length;
    } else {
        eraseLength = spanItem->position - currentPosition;
    }
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetValue(spanItem->content);
    spanResult.SetOffsetInSpan(currentPosition - contentStartPosition);
    spanResult.SetEraseLength(eraseLength);
    spanResult.SetFontColor(spanItem->GetTextStyle()->GetTextColor().ColorToString());
    spanResult.SetFontSize(spanItem->GetTextStyle()->GetFontSize().Value());
    spanResult.SetFontStyle(spanItem->GetTextStyle()->GetFontStyle());
    spanResult.SetFontWeight((int32_t)(spanItem->GetTextStyle()->GetFontWeight()));
    if (!spanItem->GetTextStyle()->GetFontFamilies().empty()) {
        spanResult.SetFontFamily(spanItem->GetTextStyle()->GetFontFamilies().at(0));
    }
    spanResult.SetColor(spanItem->GetTextStyle()->GetTextDecorationColor().ColorToString());
    spanResult.SetTextDecoration(spanItem->GetTextStyle()->GetTextDecoration());
    return eraseLength;
}

void RichEditorPattern::DeleteByDeleteValueInfo(const RichEditorDeleteValue& info)
{
    auto deleteSpans = info.GetRichEditorDeleteSpans();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::list<RefPtr<UINode>> deleteNode;
    std::set<int32_t, std::greater<int32_t>> deleteNodes;
    auto caretMoveLength = 0;
    for (const auto& it : deleteSpans) {
        caretMoveLength += it.GetEraseLength();
        switch (it.GetType()) {
            case SpanResultType::TEXT: {
                auto ui_node = host->GetChildAtIndex(it.GetSpanIndex());
                CHECK_NULL_VOID(ui_node);
                auto spanNode = DynamicCast<SpanNode>(ui_node);
                CHECK_NULL_VOID(spanNode);
                auto spanItem = spanNode->GetSpanItem();
                CHECK_NULL_VOID(spanItem);
                auto text = spanItem->content;
                std::wstring textTemp = StringUtils::ToWstring(text);
                textTemp.erase(it.OffsetInSpan(), it.GetEraseLength());
                if (textTemp.size() == 0) {
                    deleteNodes.emplace(it.GetSpanIndex());
                }
                text = StringUtils::ToString(textTemp);
                spanNode->UpdateContent(text);
                spanItem->position -= it.GetEraseLength();
                break;
            }
            case SpanResultType::IMAGE:
                deleteNodes.emplace(it.GetSpanIndex());
                break;
            case SpanResultType::SYMBOL:
                deleteNodes.emplace(it.GetSpanIndex());
                break;
            default:
                break;
        }
    }
    for (auto index : deleteNodes) {
        host->RemoveChildAtIndex(index);
    }
    if (info.GetRichEditorDeleteDirection() == RichEditorDeleteDirection::BACKWARD) {
        SetCaretPosition(std::clamp(caretPosition_ - caretMoveLength, 0, static_cast<int32_t>(GetTextContentLength())));
    }
    UpdateSpanPosition();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    OnModifyDone();
}

bool RichEditorPattern::OnKeyEvent(const KeyEvent& keyEvent)
{
    return TextInputClient::HandleKeyEvent(keyEvent);
}

void RichEditorPattern::CursorMove(CaretMoveIntent direction)
{
    switch (direction) {
        case CaretMoveIntent::Left:
            CursorMoveLeft();
            break;
        case CaretMoveIntent::Right:
            CursorMoveRight();
            break;
        case CaretMoveIntent::Up:
            CursorMoveUp();
            break;
        case CaretMoveIntent::Down:
            CursorMoveDown();
            break;
        case CaretMoveIntent::LeftWord:
            CursorMoveLeftWord();
            break;
        case CaretMoveIntent::RightWord:
            CursorMoveRightWord();
            break;
        case CaretMoveIntent::ParagraghBegin:
            CursorMoveToParagraphBegin();
            break;
        case CaretMoveIntent::ParagraghEnd:
            CursorMoveToParagraphEnd();
            break;
        case CaretMoveIntent::Home:
            CursorMoveHome();
            break;
        case CaretMoveIntent::End:
            CursorMoveEnd();
            break;
        default:
            LOGW("Unsupported cursor move operation for rich editor");
    }
}

void RichEditorPattern::MoveCaretAfterTextChange()
{
    CHECK_NULL_VOID(isTextChange_);
    isTextChange_ = false;
    switch (moveDirection_) {
        case MoveDirection::BACKWARD:
            SetCaretPosition(
                std::clamp((caretPosition_ - moveLength_), 0, static_cast<int32_t>(GetTextContentLength())));
            break;
        case MoveDirection::FORWARD:
            SetCaretPosition(
                std::clamp((caretPosition_ + moveLength_), 0, static_cast<int32_t>(GetTextContentLength())));
            break;
        default:
            break;
    }
    moveLength_ = 0;
}

void RichEditorPattern::InitTouchEvent()
{
    CHECK_NULL_VOID(!touchListener_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchListener_);
}

void RichEditorPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    auto touchPoint = info.GetTouches().front();
    auto touchType = touchPoint.GetTouchType();
    if (touchType == TouchType::DOWN) {
        touchDownOffset_ = touchPoint.GetScreenLocation();
    }
    if (SelectOverlayIsOn()) {
        if (touchType == TouchType::MOVE) {
            auto touchOffset = touchPoint.GetScreenLocation();
            if (touchOffset == touchDownOffset_) {
                return;
            }
            selectMenuInfo_.menuIsShow = false;
            selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        } else if (touchType == TouchType::UP) {
            touchDownOffset_.Reset();
            selectMenuInfo_.menuIsShow = true;
            selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        }
        return;
    }
    if (touchType == TouchType::DOWN) {
    } else if (touchType == TouchType::UP) {
        touchDownOffset_.Reset();
        isMousePressed_ = false;
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        if (isLongPress_) {
            isLongPress_ = false;
        }
#endif
    }
}

bool RichEditorPattern::IsScrollBarPressed(const MouseInfo& info)
{
    auto scrollBar = GetScrollBar();
    Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
    return scrollBar->InBarTouchRegion(point);
}

void RichEditorPattern::HandleMouseLeftButtonMove(const MouseInfo& info)
{
    if (blockPress_ || !leftMousePress_) {
        return;
    }
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };

    mouseStatus_ = MouseStatus::MOVE;
    if (isFirstMouseSelect_) {
        int32_t extend = paragraphs_.GetIndex(textOffset);
        textSelector_.Update(textSelector_.baseOffset, extend);
        isFirstMouseSelect_ = false;
    } else {
        int32_t extend = paragraphs_.GetIndex(textOffset);
        textSelector_.Update(textSelector_.baseOffset, extend);
        auto position = paragraphs_.GetIndex(textOffset);
        AdjustCursorPosition(position);
        SetCaretPosition(position);
        AutoScrollParam param = {
            .autoScrollEvent = AutoScrollEvent::MOUSE, .showScrollbar = true, .eventOffset = info.GetLocalLocation()
        };
        AutoScrollByEdgeDetection(param, OffsetF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY()),
            EdgeDetectionStrategy::OUT_BOUNDARY);
    }

    isMouseSelect_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::HandleMouseLeftButtonPress(const MouseInfo& info)
{
    isMousePressed_ = true;
    if (IsScrollBarPressed(info) || BetweenSelectedPosition(info.GetGlobalLocation())) {
        blockPress_ = true;
        return;
    }
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    int32_t extend = paragraphs_.GetIndex(textOffset);
    textSelector_.Update(extend);
    leftMousePress_ = true;
    mouseStatus_ = MouseStatus::PRESSED;
    blockPress_ = false;
    caretUpdateType_ = CaretUpdateType::PRESSED;
    UseHostToUpdateTextFieldManager();

    auto position = paragraphs_.GetIndex(textOffset);
    AdjustCursorPosition(position);
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    if (focusHub && focusHub->RequestFocusImmediately()) {
        float caretHeight = 0.0f;
        SetCaretPosition(position);
        OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight, false, false);
        MoveCaretToContentRect();
        CHECK_NULL_VOID(overlayMod_);
        DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(caretOffset, caretHeight);
        StartTwinkling();
        if (overlayMod_) {
            RequestKeyboard(false, true, true);
        }
    }
    UseHostToUpdateTextFieldManager();
}

void RichEditorPattern::HandleMouseLeftButtonRelease(const MouseInfo& info)
{
    blockPress_ = false;
    leftMousePress_ = false;
    auto oldMouseStatus = mouseStatus_;
    mouseStatus_ = MouseStatus::RELEASED;
    isMouseSelect_ = false;
    isMousePressed_ = false;
    isFirstMouseSelect_ = true;
    auto selectStart = std::min(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto selectEnd = std::max(textSelector_.baseOffset, textSelector_.destinationOffset);
    FireOnSelect(selectStart, selectEnd);
    StopAutoScroll();
    if (textSelector_.IsValid() && !textSelector_.StartEqualToDest() && IsSelectedBindSelectionMenu() &&
        oldMouseStatus == MouseStatus::MOVE) {
        selectionMenuOffsetByMouse_ = OffsetF(static_cast<float>(info.GetGlobalLocation().GetX()),
            static_cast<float>(info.GetGlobalLocation().GetY()));
        ShowSelectOverlay(RectF(), RectF(), false, TextResponseType::SELECTED_BY_MOUSE);
    }
}

void RichEditorPattern::HandleMouseLeftButton(const MouseInfo& info)
{
    if (info.GetAction() == MouseAction::MOVE) {
        HandleMouseLeftButtonMove(info);
    } else if (info.GetAction() == MouseAction::PRESS) {
        HandleMouseLeftButtonPress(info);
    } else if (info.GetAction() == MouseAction::RELEASE) {
        HandleMouseLeftButtonRelease(info);
    }
}

void RichEditorPattern::HandleMouseRightButton(const MouseInfo& info)
{
    if (info.GetAction() == MouseAction::PRESS) {
        isMousePressed_ = true;
        usingMouseRightButton_ = true;
        CloseSelectionMenu();
    } else if (info.GetAction() == MouseAction::RELEASE) {
        selectionMenuOffsetByMouse_ = OffsetF(
            static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
        if (textSelector_.IsValid() && BetweenSelectedPosition(info.GetGlobalLocation())) {
            ShowSelectOverlay(RectF(), RectF(), IsSelectAll(), TextResponseType::RIGHT_CLICK);
            isMousePressed_ = false;
            usingMouseRightButton_ = false;
            return;
        }
        if (textSelector_.IsValid()) {
            CloseSelectOverlay();
            ResetSelection();
        }
        MouseRightFocus(info);
        ShowSelectOverlay(RectF(), RectF(), IsSelectAll(), TextResponseType::RIGHT_CLICK);
        isMousePressed_ = false;
        usingMouseRightButton_ = false;
    }
}

void RichEditorPattern::MouseRightFocus(const MouseInfo& info)
{
    auto textRect = GetTextRect();
    textRect.SetTop(textRect.GetY() - std::min(baselineOffset_, 0.0f));
    textRect.SetHeight(textRect.Height() - std::max(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textRect.GetX(),
        info.GetLocalLocation().GetY() - textRect.GetY() };
    InitSelection(textOffset);
    auto selectStart = std::min(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto selectEnd = std::max(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
    SetCaretPosition(selectEnd);

    TextInsertValueInfo spanInfo;
    CalcInsertValueObj(spanInfo);
    auto spanNode = DynamicCast<FrameNode>(GetChildByIndex(spanInfo.GetSpanIndex() - 1));
    if (spanNode && spanNode->GetTag() == V2::IMAGE_ETS_TAG && spanInfo.GetOffsetInSpan() == 0 &&
        selectEnd == selectStart + 1 && BetweenSelectedPosition(info.GetGlobalLocation())) {
        selectedType_ = TextSpanType::IMAGE;
        FireOnSelect(selectStart, selectEnd);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return;
    }
    if (textSelector_.IsValid()) {
        ResetSelection();
    }
    auto position = paragraphs_.GetIndex(textOffset);
    float caretHeight = 0.0f;
    OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
    SetCaretPosition(position);
    selectedType_ = TextSpanType::TEXT;
    CHECK_NULL_VOID(overlayMod_);
    DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(caretOffset, caretHeight);
    StartTwinkling();
}

void RichEditorPattern::FireOnSelect(int32_t selectStart, int32_t selectEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    if (!textSelectInfo.GetSelection().resultObjects.empty()) {
        eventHub->FireOnSelect(&textSelectInfo);
    }
    UpdateSelectionType(textSelectInfo);
}

void RichEditorPattern::HandleMouseEvent(const MouseInfo& info)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto frameId = tmpHost->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBar = GetScrollBar();
    if (scrollBar && (scrollBar->IsHover() || scrollBar->IsPressed())) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        return;
    }

    caretUpdateType_ = CaretUpdateType::NONE;
    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        HandleMouseLeftButton(info);
    } else if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        HandleMouseRightButton(info);
    }
}

void RichEditorPattern::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto selectStart = std::min(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto selectEnd = std::max(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    if (!textSelectInfo.GetSelection().resultObjects.empty()) {
        eventHub->FireOnSelect(&textSelectInfo);
    }
    UpdateSelectionType(textSelectInfo);
    SetCaretPosition(selectEnd);
    CalculateHandleOffsetAndShowOverlay();
    StopAutoScroll();
    if (selectOverlayProxy_) {
        SelectHandleInfo handleInfo;
        if (!selectOverlayProxy_->IsSingleHandle() && textSelector_.firstHandle == textSelector_.secondHandle) {
            CloseSelectOverlay();
            StartTwinkling();
            return;
        }
        if (isFirstHandle) {
            handleInfo.paintRect = textSelector_.firstHandle;
            selectOverlayProxy_->UpdateFirstSelectHandleInfo(handleInfo);
        } else {
            handleInfo.paintRect = textSelector_.secondHandle;
            selectOverlayProxy_->UpdateSecondSelectHandleInfo(handleInfo);
        }

        if (IsSelectAll() && selectMenuInfo_.showCopyAll == true) {
            selectMenuInfo_.showCopyAll = false;
            selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        } else if (!IsSelectAll() && selectMenuInfo_.showCopyAll == false) {
            selectMenuInfo_.showCopyAll = true;
            selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        }
        auto handleReverse = selectOverlayProxy_->IsHandleReverse();
        selectOverlayProxy_.Reset();
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, IsSelectAll(),
            TextResponseType::LONG_PRESS, handleReverse);
        return;
    }
    ShowSelectOverlay(
        textSelector_.firstHandle, textSelector_.secondHandle, IsSelectAll(), TextResponseType::LONG_PRESS);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType)
{
    auto selectType = selectedType_.value_or(TextSpanType::NONE);
    std::shared_ptr<SelectionMenuParams> menuParams = nullptr;
    menuParams = GetMenuParams(selectType, responseType);
    if (menuParams == nullptr) {
        return;
    }

    // long pressing on the image needs to set the position of the pop-up menu following the long pressing position
    if (selectType == TextSpanType::IMAGE && !selectInfo.isUsingMouse) {
        selectInfo.menuInfo.menuOffset = OffsetF(selectionMenuOffset_.GetX(), selectionMenuOffset_.GetY());
    }

    CopyBindSelectionMenuParams(selectInfo, menuParams);
}

void RichEditorPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle, bool isCopyAll,
    TextResponseType responseType, bool handleReverse)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto hasDataCallback = [weak = WeakClaim(this), handleReverse, pipeline, firstHandle, secondHandle, isCopyAll,
                               responseType](bool hasData) mutable {
        auto pattern = weak.Upgrade();
        SelectOverlayInfo selectInfo;
        selectInfo.handleReverse = handleReverse;
        bool usingMouse = pattern->IsUsingMouse();
        if (!pattern->IsUsingMouse() && responseType == TextResponseType::LONG_PRESS) {
            selectInfo.firstHandle.paintRect = firstHandle;
            selectInfo.secondHandle.paintRect = secondHandle;
        } else {
            if (responseType == TextResponseType::LONG_PRESS) {
                responseType = TextResponseType::RIGHT_CLICK;
            }
            selectInfo.isUsingMouse = true;
            selectInfo.rightClickOffset = pattern->GetSelectionMenuOffset();
            pattern->ResetIsMousePressed();
        }
        selectInfo.menuInfo.responseType = static_cast<int32_t>(responseType);
        selectInfo.menuInfo.editorType = static_cast<int32_t>(pattern->GetEditorType());
        selectInfo.onHandleMove = [weak](const RectF& handleRect, bool isFirst) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnHandleMove(handleRect, isFirst);
        };
        selectInfo.onHandleMoveDone = [weak](const RectF& handleRect, bool isFirst) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnHandleMoveDone(handleRect, isFirst);
        };

        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);

        selectInfo.menuCallback.onCopy = [weak, usingMouse]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnCopy();
            pattern->CloseSelectOverlay();
            if (!usingMouse) {
                pattern->ResetSelection();
            }
        };

        selectInfo.menuCallback.onCut = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnCut();
        };

        selectInfo.menuCallback.onPaste = [weak]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnPaste();
        };
        selectInfo.menuCallback.onSelectAll = [weak, usingMouse]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->isMousePressed_ = usingMouse;
            pattern->HandleMenuCallbackOnSelectAll();
        };

        selectInfo.menuCallback.onCameraInput = [weak, usingMouse]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnCameraInput();
        };

        if (pattern->GetTextDetectEnable()) {
            selectInfo.onClose = [weak](bool closedByGlobalEvent) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                if (closedByGlobalEvent) {
                    pattern->ResetSelection();
                }
            };
        }
        selectInfo.callerFrameNode = host;
        pattern->CopySelectionMenuParams(selectInfo, responseType);
        pattern->UpdateSelectMenuInfo(hasData, selectInfo, isCopyAll);
        pattern->CheckEditorTypeChange();
        pattern->UpdateSelectOverlayOrCreate(selectInfo);
    };
    CHECK_NULL_VOID(clipboard_);
    clipboard_->HasData(hasDataCallback);
}

void RichEditorPattern::CheckEditorTypeChange()
{
    CHECK_NULL_VOID(selectOverlayProxy_);
    CHECK_NULL_VOID(!selectOverlayProxy_->IsClosed());
    if (selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType.value_or(static_cast<int32_t>(
            TextSpanType::NONE)) != static_cast<int32_t>(selectedType_.value_or(TextSpanType::NONE))) {
        CloseSelectionMenu();
    }
}

void RichEditorPattern::HandleOnCopy()
{
    CHECK_NULL_VOID(clipboard_);
    if (copyOption_ == CopyOptions::None) {
        return;
    }
    auto selectStart = textSelector_.GetTextStart();
    auto selectEnd = textSelector_.GetTextEnd();
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    auto copyResultObjects = textSelectInfo.GetSelection().resultObjects;
    caretUpdateType_ = CaretUpdateType::NONE;
    if (copyResultObjects.empty()) {
        return;
    }
    RefPtr<PasteDataMix> pasteData = clipboard_->CreatePasteDataMix();
    auto resultProcessor = [weak = WeakClaim(this), pasteData, selectStart, selectEnd, clipboard = clipboard_](
                               const ResultObject& result) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (result.type == SelectSpanType::TYPESPAN) {
            auto data = pattern->GetSelectedSpanText(StringUtils::ToWstring(result.valueString),
                result.offsetInSpan[RichEditorSpanRange::RANGESTART],
                result.offsetInSpan[RichEditorSpanRange::RANGEEND]);
            clipboard->AddTextRecord(pasteData, data);
            return;
        }
        if (result.type == SelectSpanType::TYPEIMAGE) {
            if (result.valuePixelMap) {
                clipboard->AddPixelMapRecord(pasteData, result.valuePixelMap);
            } else {
                clipboard->AddImageRecord(pasteData, result.valueString);
            }
        }
    };
    for (auto resultObj = copyResultObjects.rbegin(); resultObj != copyResultObjects.rend(); ++resultObj) {
        resultProcessor(*resultObj);
    }
    clipboard_->SetData(pasteData, copyOption_);
    if (!textDetectEnable_) {
        StartTwinkling();
    }
}

void RichEditorPattern::ResetAfterPaste()
{
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_ + moveLength_;
    auto pasteStr = GetPasteStr();
    record.addText = pasteStr;
    SetCaretSpanIndex(-1);
    StartTwinkling();
    CloseSelectOverlay();
    if (textSelector_.IsValid()) {
        SetCaretPosition(textSelector_.GetTextStart());
        record.beforeCaretPosition = caretPosition_;
        auto length = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
        textSelector_.Update(-1, -1);
        record.deleteText = StringUtils::ToString(DeleteForwardOperation(length));
        ResetSelection();
    }
    InsertValueByPaste(pasteStr);
    ClearPasteStr();
    record.afterCaretPosition = caretPosition_ + moveLength_;
    ClearRedoOperationRecords();
    AddOperationRecord(record);
}

void RichEditorPattern::HandleOnPaste()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextCommonEvent event;
    eventHub->FireOnPaste(event);
    if (event.IsPreventDefault()) {
        CloseSelectOverlay();
        ResetSelection();
        StartTwinkling();
        return;
    }
    CHECK_NULL_VOID(clipboard_);
    auto pasteCallback = [weak = WeakClaim(this)](const std::string& data) {
        if (data.empty()) {
            return;
        }
        auto richEditor = weak.Upgrade();
        CHECK_NULL_VOID(richEditor);
        richEditor->AddPasteStr(data);
        richEditor->ResetAfterPaste();
    };
    clipboard_->GetData(pasteCallback);
}

void RichEditorPattern::InsertValueByPaste(const std::string& insertValue)
{
    RefPtr<UINode> child;
    TextInsertValueInfo info;
    CalcInsertValueObj(info);
    TextSpanOptions options;
    options.value = insertValue;
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        options.style = typingTextStyle_.value();
    }
    auto newSpanOffset = caretPosition_ + moveLength_;
    isTextChange_ = true;
    moveDirection_ = MoveDirection::FORWARD;
    moveLength_ += static_cast<int32_t>(StringUtils::ToWstring(insertValue).length());
    if (caretSpanIndex_ == -1) {
        child = GetChildByIndex(info.GetSpanIndex());
        if (child && child->GetTag() == V2::SPAN_ETS_TAG) {
            auto spanNode = DynamicCast<SpanNode>(child);
            CHECK_NULL_VOID(spanNode);
            if (typingStyle_.has_value() && !HasSameTypingStyle(spanNode)) {
                options.offset = newSpanOffset;
                caretSpanIndex_ = AddTextSpanOperation(options, true);
            } else {
                InsertValueToSpanNode(spanNode, insertValue, info);
            }
            return;
        } else if (!child) {
            auto spanNodeBefore = DynamicCast<SpanNode>(GetChildByIndex(info.GetSpanIndex() - 1));
            if (spanNodeBefore == nullptr) {
                caretSpanIndex_ = AddTextSpanOperation(options, true);
            } else if (typingStyle_.has_value() && !HasSameTypingStyle(spanNodeBefore)) {
                auto spanNode = DynamicCast<SpanNode>(child);
                CreateTextSpanNode(spanNode, info, insertValue, false);
                caretSpanIndex_ = info.GetSpanIndex();
            } else {
                InsertValueToBeforeSpan(spanNodeBefore, insertValue);
                caretSpanIndex_ = info.GetSpanIndex() - 1;
            }
            return;
        }
    } else {
        child = GetChildByIndex(caretSpanIndex_);
        if (child && child->GetTag() == V2::SPAN_ETS_TAG) {
            auto spanNode = DynamicCast<SpanNode>(child);
            CHECK_NULL_VOID(spanNode);
            if (typingStyle_.has_value() && !HasSameTypingStyle(spanNode)) {
                options.offset = newSpanOffset;
                caretSpanIndex_ = AddTextSpanOperation(options, true);
            } else {
                InsertValueToBeforeSpan(spanNode, insertValue);
            }
            return;
        }
    }
    if (child && child->GetTag() == V2::IMAGE_ETS_TAG) {
        auto spanNodeBefore = DynamicCast<SpanNode>(GetChildByIndex(info.GetSpanIndex() - 1));
        if (spanNodeBefore != nullptr && caretSpanIndex_ == -1) {
            if (typingStyle_.has_value() && !HasSameTypingStyle(spanNodeBefore)) {
                options.offset = newSpanOffset;
                caretSpanIndex_ = AddTextSpanOperation(options, true);
            } else {
                InsertValueToBeforeSpan(spanNodeBefore, insertValue);
                caretSpanIndex_ = info.GetSpanIndex() - 1;
            }
        } else {
            auto imageNode = DynamicCast<FrameNode>(child);
            if (imageNode && caretSpanIndex_ == -1) {
                caretSpanIndex_ = AddTextSpanOperation(options, true, info.GetSpanIndex());
            } else {
                caretSpanIndex_ = AddTextSpanOperation(options, true, caretSpanIndex_ + 1);
            }
        }
    } else {
        caretSpanIndex_ = AddTextSpanOperation(options, true);
    }
}

void RichEditorPattern::SetCaretSpanIndex(int32_t index)
{
    caretSpanIndex_ = index;
}

void RichEditorPattern::HandleOnCut()
{
    if (copyOption_ == CopyOptions::None) {
        return;
    }
    if (!textSelector_.IsValid()) {
        return;
    }
    caretUpdateType_ = CaretUpdateType::NONE;
    HandleOnCopy();
    DeleteBackward();
}

void RichEditorPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle)
{
    TextPattern::OnHandleMove(handleRect, isFirstHandle);
    if (!isFirstHandle) {
        SetCaretPosition(textSelector_.destinationOffset);
    }
    auto localOffset = handleRect.GetOffset() - parentGlobalOffset_;
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE,
        .handleRect = handleRect,
        .isFirstHandle = isFirstHandle,
        .showScrollbar = true };
    AutoScrollByEdgeDetection(param, localOffset, EdgeDetectionStrategy::OUT_BOUNDARY);
}

std::function<void(Offset)> RichEditorPattern::GetThumbnailCallback()
{
    return [wk = WeakClaim(this)](const Offset& point) {
        auto pattern = wk.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->BetweenSelectedPosition(point)) {
            auto host = pattern->GetHost();
            auto children = host->GetChildren();
            std::list<RefPtr<FrameNode>> imageChildren;
            for (const auto& child : children) {
                auto node = DynamicCast<FrameNode>(child);
                if (!node) {
                    continue;
                }
                auto image = node->GetPattern<ImagePattern>();
                if (image) {
                    imageChildren.emplace_back(node);
                }
            }
            pattern->dragNode_ = RichEditorDragPattern::CreateDragNode(host, imageChildren);
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
    };
}

void RichEditorPattern::CreateHandles()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    float startSelectHeight = 0.0f;
    float endSelectHeight = 0.0f;
    auto firstHandlePosition = CalcCursorOffsetByPosition(textSelector_.GetStart(), startSelectHeight, true);
    OffsetF firstHandleOffset(firstHandlePosition.GetX() + parentGlobalOffset_.GetX(),
        firstHandlePosition.GetY() + parentGlobalOffset_.GetY());
    textSelector_.firstHandleOffset_ = firstHandleOffset;
    auto secondHandlePosition = CalcCursorOffsetByPosition(textSelector_.GetEnd(), endSelectHeight);
    OffsetF secondHandleOffset(secondHandlePosition.GetX() + parentGlobalOffset_.GetX(),
        secondHandlePosition.GetY() + parentGlobalOffset_.GetY());
    textSelector_.secondHandleOffset_ = secondHandleOffset;
    SizeF firstHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), startSelectHeight };
    SizeF secondHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), endSelectHeight };
    RectF firstHandle = RectF(firstHandleOffset, firstHandlePaintSize);
    textSelector_.firstHandle = firstHandle;
    RectF secondHandle = RectF(secondHandleOffset, secondHandlePaintSize);
    textSelector_.secondHandle = secondHandle;
    ShowSelectOverlay(firstHandle, secondHandle, IsSelectAll(), TextResponseType::LONG_PRESS);
}

void RichEditorPattern::OnAreaChangedInner()
{
    float selectLineHeight = 0.0f;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto parentGlobalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    if (parentGlobalOffset != parentGlobalOffset_) {
        parentGlobalOffset_ = parentGlobalOffset;
        UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
        CHECK_NULL_VOID(SelectOverlayIsOn());
        textSelector_.selectionBaseOffset.SetX(
            CalcCursorOffsetByPosition(textSelector_.GetStart(), selectLineHeight).GetX());
        textSelector_.selectionDestinationOffset.SetX(
            CalcCursorOffsetByPosition(textSelector_.GetEnd(), selectLineHeight).GetX());
        CreateHandles();
    }
}

void RichEditorPattern::CloseSelectionMenu()
{
    CloseSelectOverlay();
}

void RichEditorPattern::CloseSelectOverlay()
{
    TextPattern::CloseSelectOverlay(true);
}

void RichEditorPattern::CalculateHandleOffsetAndShowOverlay(bool isUsingMouse)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto offset = host->GetPaintRectOffset();
    auto textPaintOffset = offset - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    float startSelectHeight = 0.0f;
    float endSelectHeight = 0.0f;
    int32_t destinationOffset = std::min(textSelector_.destinationOffset, GetTextContentLength());
    auto startOffset = CalcCursorOffsetByPosition(textSelector_.baseOffset, startSelectHeight, true, false);
    auto endOffset =
        CalcCursorOffsetByPosition(destinationOffset, endSelectHeight, false, false);
    SizeF firstHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), startSelectHeight };
    SizeF secondHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), endSelectHeight };
    OffsetF firstHandleOffset = startOffset + textPaintOffset - rootOffset;
    OffsetF secondHandleOffset = endOffset + textPaintOffset - rootOffset;
    if (GetTextContentLength() == 0) {
        float caretHeight = DynamicCast<RichEditorOverlayModifier>(overlayMod_)->GetCaretHeight();
        secondHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretHeight / 2 };
        secondHandleOffset = OffsetF(secondHandleOffset.GetX(), secondHandleOffset.GetY() + caretHeight / 2);
        // only show the second handle.
        firstHandlePaintSize = SizeF{};
        firstHandleOffset = OffsetF{};
    }
    textSelector_.selectionBaseOffset = firstHandleOffset;
    textSelector_.selectionDestinationOffset = secondHandleOffset;
    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize(firstHandlePaintSize);
    textSelector_.firstHandle = firstHandle;
    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize(secondHandlePaintSize);
    textSelector_.secondHandle = secondHandle;
}

void RichEditorPattern::ResetSelection()
{
    if (textSelector_.IsValid()) {
        textSelector_.Update(-1, -1);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<RichEditorEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto textSelectInfo = GetSpansInfo(-1, -1, GetSpansMethod::ONSELECT);
        eventHub->FireOnSelect(&textSelectInfo);
        UpdateSelectionType(textSelectInfo);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool RichEditorPattern::BetweenSelectedPosition(const Offset& globalOffset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto offset = host->GetPaintRectOffset();
    auto localOffset = globalOffset - Offset(offset.GetX(), offset.GetY());
    auto eventHub = host->GetEventHub<EventHub>();
    if (GreatNotEqual(textSelector_.GetTextEnd(), textSelector_.GetTextStart())) {
        // Determine if the pan location is in the selected area
        auto selectedRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
        auto panOffset = OffsetF(localOffset.GetX(), localOffset.GetY()) - GetTextRect().GetOffset() +
                         OffsetF(0.0, std::min(baselineOffset_, 0.0f));
        for (const auto& selectedRect : selectedRects) {
            if (selectedRect.IsInRegion(PointF(panOffset.GetX(), panOffset.GetY()))) {
                return true;
            }
        }
    }
    return false;
}

void RichEditorPattern::HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    if (newWidth != prevWidth || newHeight != prevHeight) {
        TextPattern::CloseSelectOverlay();
    }
    UpdateCaretInfoToController();
}

void RichEditorPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY)
{
    UpdateCaretInfoToController();
}

void RichEditorPattern::DumpInfo()
{
    if (customKeyboardBuilder_) {
        DumpLog::GetInstance().AddDesc(std::string("CustomKeyboard: true")
                                           .append(", Attached: ")
                                           .append(std::to_string(isCustomKeyboardAttached_)));
    }
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto richEditorTheme = context->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    DumpLog::GetInstance().AddDesc(std::string("caret offset: ").append(GetCaretRect().GetOffset().ToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("caret height: ")
            .append(std::to_string(NearZero(GetCaretRect().Height())
                                       ? richEditorTheme->GetDefaultCaretHeight().ConvertToPx()
                                       : GetCaretRect().Height())));
}

bool RichEditorPattern::HasFocus() const
{
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

void RichEditorPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    if (!HasFocus()) {
        return;
    }
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto richEditorTheme = context->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetClickPosition(
        { offset.GetX() + GetCaretRect().GetX(), offset.GetY() + GetCaretRect().GetY() });
    textFieldManager->SetHeight(NearZero(GetCaretRect().Height())
                                    ? richEditorTheme->GetDefaultCaretHeight().ConvertToPx()
                                    : GetCaretRect().Height());
    textFieldManager->SetOnFocusTextField(WeakClaim(this));

    if (!isTextChange_) {
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ScrollToSafeArea();
        },
        TaskExecutor::TaskType::UI);
}

bool RichEditorPattern::IsDisabled() const
{
    auto eventHub = GetHost()->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return !eventHub->IsEnabled();
}

void RichEditorPattern::InitSelection(const Offset& pos)
{
    int32_t currentPosition = paragraphs_.GetIndex(pos);
    currentPosition = std::min(currentPosition, GetTextContentLength());
    int32_t nextPosition = currentPosition + GetGraphemeClusterLength(GetWideText(), currentPosition);
    nextPosition = std::min(nextPosition, GetTextContentLength());
    adjusted_ = AdjustWordSelection(currentPosition, nextPosition);
    textSelector_.Update(currentPosition, nextPosition);
    auto selectedRects = paragraphs_.GetRects(currentPosition, nextPosition);
    if (selectedRects.empty() && !spans_.empty()) {
        auto it = std::find_if(
            spans_.begin(), spans_.end(), [caretPosition = currentPosition](const RefPtr<SpanItem>& spanItem) {
                return (spanItem->position - static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length()) <=
                           caretPosition) &&
                       (caretPosition < spanItem->position);
            });
        auto spanIndex = std::distance(spans_.begin(), it);
        auto spanNode = DynamicCast<FrameNode>(GetChildByIndex(spanIndex - 1));
        if (spanNode &&
            (spanNode->GetTag() == V2::IMAGE_ETS_TAG || spanNode->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG)) {
            textSelector_.Update(currentPosition - 1, currentPosition);
            return;
        }
    }

    if (adjusted_) {
        return;
    }

    bool selectedSingle =
        selectedRects.size() == 1 && (pos.GetX() < selectedRects[0].Left() || pos.GetY() < selectedRects[0].Top());
    bool selectedLast = selectedRects.empty() && currentPosition == GetTextContentLength();
    if (selectedSingle || selectedLast) {
        if (selectedLast) {
            nextPosition = currentPosition + 1;
        }
        auto selectedNextRects = paragraphs_.GetRects(currentPosition - 1, nextPosition - 1);
        if (selectedNextRects.size() == 1) {
            bool isInRange = pos.GetX() >= selectedNextRects[0].Left() && pos.GetX() <= selectedNextRects[0].Right() &&
                             pos.GetY() >= selectedNextRects[0].Top() && pos.GetY() <= selectedNextRects[0].Bottom();
            if (isInRange || (!selectedLast && selectedRects[0].Top() != selectedNextRects[0].Top())) {
                textSelector_.Update(currentPosition - 1, nextPosition - 1);
            }
        }
    }
}

void RichEditorPattern::SetSelection(int32_t start, int32_t end)
{
    CHECK_NULL_VOID(HasFocus());
    bool changeSelected = false;
    if (start > end) {
        changeSelected = textSelector_.IsValid();
        ResetSelection();
    } else {
        if (start == -1 && end == -1) {
            start = 0;
            end = GetTextContentLength();
        } else {
            start = std::min(std::max(0, start), GetTextContentLength());
            end = std::min(std::max(0, end), GetTextContentLength());
        }
        changeSelected = start != textSelector_.GetTextStart() || end != textSelector_.GetTextEnd();
        textSelector_.Update(start, end);
    }

    auto oldSelectedType = selectedType_;
    if (textSelector_.IsValid() && !textSelector_.StartEqualToDest()) {
        StopTwinkling();
        if (changeSelected) {
            FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
        }
    }
    if (SelectOverlayIsOn()) {
        isMousePressed_ = selectOverlayProxy_->GetSelectOverlayMangerInfo().isUsingMouse;
        auto selectedTypeChange = (oldSelectedType.has_value() && selectedType_.has_value() &&
                                      oldSelectedType.value() != selectedType_.value()) ||
                                  (!oldSelectedType.has_value() && selectedType_.has_value());
        if (!isMousePressed_ || selectedTypeChange) {
            CalculateHandleOffsetAndShowOverlay();
            CloseSelectOverlay();
            auto responseType = static_cast<TextResponseType>(
                selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.responseType.value_or(0));
            ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, IsSelectAll(), responseType);
        }
    }
    SetCaretPosition(textSelector_.GetTextEnd());
    MoveCaretToContentRect();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::BindSelectionMenu(TextResponseType type, TextSpanType richEditorType,
    std::function<void()>& menuBuilder, std::function<void(int32_t, int32_t)>& onAppear,
    std::function<void()>& onDisappear)
{
    TextPattern::BindSelectionMenu(richEditorType, type, menuBuilder, onAppear, onDisappear);
}

RefPtr<NodePaintMethod> RichEditorPattern::CreateNodePaintMethod()
{
    if (!contentMod_) {
        contentMod_ = MakeRefPtr<RichEditorContentModifier>(textStyle_, &paragraphs_, WeakClaim(this));
    }
    if (!overlayMod_) {
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
            scrollBarModifier->SetRect(scrollBar->GetActiveRect());
            scrollBarModifier->SetPositionMode(scrollBar->GetPositionMode());
            SetScrollBarOverlayModifier(scrollBarModifier);
        }
        SetEdgeEffect(EdgeEffect::FADE, GetAlwaysEnabled());
        SetEdgeEffect();
        overlayMod_ = AceType::MakeRefPtr<RichEditorOverlayModifier>(
            WeakClaim(this), GetScrollBarOverlayModifier(), GetScrollEdgeEffect());
    }

    if (GetIsCustomFont()) {
        contentMod_->SetIsCustomFont(true);
    }
    return MakeRefPtr<RichEditorPaintMethod>(WeakClaim(this), &paragraphs_, baselineOffset_, contentMod_, overlayMod_);
}

int32_t RichEditorPattern::GetHandleIndex(const Offset& offset) const
{
    return paragraphs_.GetIndex(Offset(offset.GetX() + contentRect_.GetX() - richTextRect_.GetX(),
        offset.GetY() + contentRect_.GetY() - richTextRect_.GetY()));
}

std::vector<RectF> RichEditorPattern::GetTextBoxes()
{
    auto selectedRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    std::vector<RectF> res;
    res.reserve(selectedRects.size());
    for (auto&& rect : selectedRects) {
        if (NearZero(rect.Width())) {
            continue;
        }
        res.emplace_back(rect);
    }
    if (!res.empty() && paragraphs_.IsSelectLineHeadAndUseLeadingMargin(textSelector_.GetTextStart())) {
        // To make drag screenshot include LeadingMarginPlaceholder.
        res.front().SetLeft(0.0f);
    }
    return res;
}

float RichEditorPattern::GetLineHeight() const
{
    auto selectedRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    CHECK_NULL_RETURN(selectedRects.size(), 0.0f);
    return selectedRects.front().Height();
}

void RichEditorPattern::UpdateSelectMenuInfo(bool hasData, SelectOverlayInfo& selectInfo, bool isCopyAll)
{
    auto hasValue = (static_cast<int32_t>(GetWideText().length()) + placeholderCount_) > 0;
    bool isShowItem = copyOption_ != CopyOptions::None;
    selectInfo.menuInfo.showCopy = isShowItem && hasValue && textSelector_.IsValid() &&
                                    !textSelector_.StartEqualToDest();
    selectInfo.menuInfo.showCut = isShowItem && hasValue && textSelector_.IsValid() &&
                                    !textSelector_.StartEqualToDest();
    selectInfo.menuInfo.showCopyAll = !isCopyAll && hasValue;
    selectInfo.menuInfo.showPaste = hasData;
    bool isSupportCameraInput = false;
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    isSupportCameraInput =
        inputMethod && inputMethod->IsInputTypeSupported(MiscServices::InputType::CAMERA_INPUT);
#endif
    selectInfo.menuInfo.showCameraInput = !IsSelected() && isSupportCameraInput && !customKeyboardBuilder_;
    selectInfo.menuInfo.menuIsShow = hasValue || hasData || selectInfo.menuInfo.showCameraInput;
    selectMenuInfo_ = selectInfo.menuInfo;
}

RectF RichEditorPattern::GetCaretRect() const
{
    RectF rect;
    CHECK_NULL_RETURN(overlayMod_, rect);
    auto richEditorOverlay = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_RETURN(richEditorOverlay, rect);
    rect.SetOffset(richEditorOverlay->GetCaretOffset());
    rect.SetHeight(richEditorOverlay->GetCaretHeight());
    return rect;
}

void RichEditorPattern::ScrollToSafeArea() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->ScrollTextFieldToSafeArea();
}

void RichEditorPattern::InitScrollablePattern()
{
    if (GetScrollableEvent()) {
        return;
    }
    SetAxis(Axis::VERTICAL);
    AddScrollEvent();
    SetScrollBar(DisplayMode::AUTO);
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
        CHECK_NULL_VOID(richEditorTheme);
        scrollBar->SetMinHeight(richEditorTheme->GetScrollbarMinHeight());
    }
    if (overlayMod_) {
        UpdateScrollBarOffset();
    }
    auto layoutProperty = GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto& paddingProperty = layoutProperty->GetPaddingProperty();
    if (paddingProperty) {
        auto offsetY = paddingProperty->top.has_value() ? paddingProperty->top->GetDimension().ConvertToPx() : 0.0f;
        auto offsetX = paddingProperty->left.has_value() ? paddingProperty->left->GetDimension().ConvertToPx() : 0.0f;
        richTextRect_.SetOffset(OffsetF(offsetX, offsetY));
    }
}

void RichEditorPattern::ProcessInnerPadding()
{
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto themePadding = theme->GetPadding();
    auto& paddingProp = layoutProperty->GetPaddingProperty();
    auto left = !paddingProp ? CalcLength(themePadding.Left()).GetDimension()
                             : paddingProp->left.value_or(CalcLength(themePadding.Left())).GetDimension();
    auto top = !paddingProp ? CalcLength(themePadding.Top()).GetDimension()
                            : paddingProp->top.value_or(CalcLength(themePadding.Top())).GetDimension();
    auto bottom = !paddingProp ? CalcLength(themePadding.Bottom()).GetDimension()
                               : paddingProp->bottom.value_or(CalcLength(themePadding.Bottom())).GetDimension();
    auto right = !paddingProp ? CalcLength(themePadding.Right()).GetDimension()
                              : paddingProp->right.value_or(CalcLength(themePadding.Right())).GetDimension();
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(top);
    paddings.bottom = NG::CalcLength(bottom);
    paddings.left = NG::CalcLength(left);
    paddings.right = NG::CalcLength(right);
    layoutProperty->UpdatePadding(paddings);
}

void RichEditorPattern::UpdateScrollStateAfterLayout(bool shouldDisappear)
{
    bool hasTextOffsetChanged = false;
    if (GreatNotEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        auto offset = richTextRect_.GetOffset();
        offset.AddY(contentRect_.GetY() - richTextRect_.GetY());
        richTextRect_.SetOffset(offset);
        hasTextOffsetChanged = true;
    }
    if (GreatNotEqual(richTextRect_.Height(), contentRect_.Height()) &&
        LessNotEqual(richTextRect_.Bottom(), contentRect_.Bottom())) {
        auto offset = richTextRect_.GetOffset();
        offset.AddY(contentRect_.Bottom() - richTextRect_.Bottom());
        richTextRect_.SetOffset(offset);
        hasTextOffsetChanged = true;
    }
    if (LessOrEqual(richTextRect_.Height(), contentRect_.Height()) &&
        LessNotEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        richTextRect_.SetOffset(contentRect_.GetOffset());
        hasTextOffsetChanged = true;
    }
    if (hasTextOffsetChanged) {
        UpdateChildrenOffset();
    }
    StopScrollable();
    CheckScrollable();
    if (overlayMod_) {
        UpdateScrollBarOffset();
    }
    if (!GetScrollBar()) {
        return;
    }
    if (isFirstCallOnReady_) {
        isFirstCallOnReady_ = false;
        GetScrollBar()->ScheduleDisappearDelayTask();
        return;
    }
    if (shouldDisappear) {
        GetScrollBar()->ScheduleDisappearDelayTask();
    }
}

bool RichEditorPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->PlayScrollBarAppearAnimation();
        }
        return true;
    }
    if (IsReachedBoundary(offset)) {
        return false;
    }
    auto newOffset = MoveTextRect(offset);
    MoveFirstHandle(newOffset);
    MoveSecondHandle(newOffset);
    return true;
}

float RichEditorPattern::MoveTextRect(float offset)
{
    if (GreatNotEqual(richTextRect_.Height(), contentRect_.Height())) {
        if (GreatNotEqual(richTextRect_.GetY() + offset, contentRect_.GetY())) {
            offset = contentRect_.GetY() - richTextRect_.GetY();
        } else if (LessNotEqual(richTextRect_.Bottom() + offset, contentRect_.Bottom())) {
            offset = contentRect_.Bottom() - richTextRect_.Bottom();
        }
    } else if (!NearEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        offset = contentRect_.GetY() - richTextRect_.GetY();
    } else {
        return 0.0f;
    }
    if (NearEqual(offset, 0.0f)) {
        return offset;
    }
    scrollOffset_ = richTextRect_.GetY() + offset;
    richTextRect_.SetOffset(OffsetF(richTextRect_.GetX(), scrollOffset_));
    UpdateScrollBarOffset();
    UpdateChildrenOffset();
    return offset;
}

void RichEditorPattern::MoveFirstHandle(float offset)
{
    if (SelectOverlayIsOn() && !NearEqual(offset, 0.0f)) {
        textSelector_.selectionBaseOffset.AddY(offset);
        auto firstHandleOffset = textSelector_.firstHandle.GetOffset();
        firstHandleOffset.AddY(offset);
        textSelector_.firstHandle.SetOffset(firstHandleOffset);
        SelectHandleInfo firstHandleInfo;
        firstHandleInfo.paintRect = textSelector_.firstHandle;
        firstHandleInfo.needLayout = true;
        CheckHandles(firstHandleInfo);
        selectOverlayProxy_->UpdateFirstSelectHandleInfo(firstHandleInfo);
    }
}

void RichEditorPattern::MoveSecondHandle(float offset)
{
    if (SelectOverlayIsOn() && !NearEqual(offset, 0.0f)) {
        textSelector_.selectionDestinationOffset.AddY(offset);
        auto secondHandleOffset = textSelector_.secondHandle.GetOffset();
        secondHandleOffset.AddY(offset);
        textSelector_.secondHandle.SetOffset(secondHandleOffset);
        SelectHandleInfo secondHandleInfo;
        secondHandleInfo.paintRect = textSelector_.secondHandle;
        secondHandleInfo.needLayout = true;
        CheckHandles(secondHandleInfo);
        selectOverlayProxy_->UpdateSecondSelectHandleInfo(secondHandleInfo);
    }
}

void RichEditorPattern::MoveCaretToContentRect()
{
    float caretHeight = 0.0f;
    auto caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight, true);
    MoveCaretToContentRect(caretOffset, caretHeight);
}

void RichEditorPattern::MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight)
{
    auto contentRect = GetTextContentRect();
    auto textRect = GetTextRect();
    if (LessOrEqual(textRect.Height(), contentRect.Height())) {
        return;
    }
    if (LessNotEqual(contentRect.GetSize().Height(), caretHeight) &&
        !NearEqual(caretOffset.GetY() + caretHeight, contentRect.Bottom())) {
        OnScrollCallback(contentRect.Bottom() - caretOffset.GetY() - caretHeight, SCROLL_FROM_NONE);
    }
    if (LessNotEqual(contentRect.GetSize().Height(), caretHeight)) {
        return;
    }
    if (LessNotEqual(caretOffset.GetY(), contentRect.GetY())) {
        if (LessOrEqual(caretOffset.GetX(), GetTextRect().GetX())) {
            OnScrollCallback(contentRect.GetY() - caretOffset.GetY() + caretHeight, SCROLL_FROM_NONE);
        } else {
            OnScrollCallback(contentRect.GetY() - caretOffset.GetY(), SCROLL_FROM_NONE);
        }
    } else if (GreatNotEqual(caretOffset.GetY() + caretHeight, contentRect.Bottom())) {
        OnScrollCallback(contentRect.Bottom() - caretOffset.GetY() - caretHeight, SCROLL_FROM_NONE);
    }
}

void RichEditorPattern::UpdateScrollBarOffset()
{
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    Size size(frameRect_.Width(), frameRect_.Height());
    auto verticalGap = frameRect_.Height() - contentRect_.Height();
    UpdateScrollBarRegion(
        contentRect_.GetY() - richTextRect_.GetY(), richTextRect_.Height() + verticalGap, size, Offset(0.0, 0.0));
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::OnScrollEndCallback()
{
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->ScheduleDisappearDelayTask();
    }
}

bool RichEditorPattern::IsReachedBoundary(float offset)
{
    return (NearEqual(richTextRect_.GetY(), contentRect_.GetY()) && GreatNotEqual(offset, 0.0f)) ||
           (NearEqual(richTextRect_.GetY() + richTextRect_.Height(), contentRect_.GetY() + contentRect_.Height()) &&
               LessNotEqual(offset, 0.0f));
}

void RichEditorPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    scrollable_ = GetTextContentLength() > 0 && GreatNotEqual(richTextRect_.Height(), contentRect_.Height());
    SetScrollEnable(scrollable_);
}

void RichEditorPattern::UpdateChildrenOffset()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<int32_t> placeholderIndex;
    for (const auto& child : spans_) {
        if (!child) {
            continue;
        }
        if (AceType::InstanceOf<ImageSpanItem>(child) || AceType::InstanceOf<PlaceholderSpanItem>(child)) {
            placeholderIndex.emplace_back(child->placeholderIndex);
        }
    }
    if (spans_.empty() || placeholderIndex.empty()) {
        return;
    }
    size_t index = 0;
    std::vector<RectF> rectsForPlaceholders = paragraphs_.GetPlaceholderRects();
    auto childrenNodes = host->GetChildren();
    auto textOffset = GetTextRect().GetOffset();
    for (const auto& child : childrenNodes) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (!childNode) {
            continue;
        }
        if (!(childNode->GetPattern<ImagePattern>() || childNode->GetPattern<PlaceholderSpanPattern>())) {
            continue;
        }
        if (index >= rectsForPlaceholders.size()) {
            break;
        }
        auto rect = rectsForPlaceholders.at(index);
        auto geometryNode = childNode->GetGeometryNode();
        if (geometryNode) {
            geometryNode->SetMarginFrameOffset(textOffset + OffsetF(rect.Left(), rect.Top()));
            childNode->ForceSyncGeometryNode();
            childNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        ++index;
    }
}

void RichEditorPattern::AutoScrollByEdgeDetection(AutoScrollParam param, OffsetF offset, EdgeDetectionStrategy strategy)
{
    if (NearEqual(prevAutoScrollOffset_.GetY(), offset.GetY())) {
        return;
    }
    prevAutoScrollOffset_ = offset;
    auto contentRect = GetTextContentRect();
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DISTANCE.ConvertToPx()
                                     : AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();
    auto maxHeight = isDragging ? frameRect_.Height() : contentRect.Height();
    if (GreatNotEqual(edgeThreshold * 2, maxHeight)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AutoScrollByEdgeDetection: hot area height is great than max height.");
        return;
    }
    float topEdgeThreshold = isDragging ? edgeThreshold : edgeThreshold + contentRect.GetY();
    float bottomThreshold = isDragging ? frameRect_.Height() - edgeThreshold : contentRect.Bottom() - edgeThreshold;
    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        auto handleTopOffset = offset;
        auto handleBottomOffset = OffsetF(offset.GetX(), offset.GetY() + param.handleRect.Height());
        if (GreatNotEqual(handleBottomOffset.GetY(), bottomThreshold)) {
            param.offset = bottomThreshold - handleBottomOffset.GetY();
            ScheduleAutoScroll(param);
        } else if (LessNotEqual(handleTopOffset.GetY(), topEdgeThreshold)) {
            param.offset = topEdgeThreshold - handleTopOffset.GetY();
            ScheduleAutoScroll(param);
        } else {
            StopAutoScroll();
        }
        return;
    }
    // drag and mouse
    if (GreatNotEqual(offset.GetY(), bottomThreshold)) {
        param.offset = isDragging ? -CalcDragSpeed(bottomThreshold, frameRect_.Height(), offset.GetY())
                                  : bottomThreshold - offset.GetY();
        ScheduleAutoScroll(param);
    } else if (LessNotEqual(offset.GetY(), topEdgeThreshold)) {
        param.offset = isDragging ? CalcDragSpeed(topEdgeThreshold, 0, offset.GetY())
                                  : topEdgeThreshold - offset.GetY();
        ScheduleAutoScroll(param);
    } else {
        StopAutoScroll();
    }
}

float RichEditorPattern::CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point)
{
    auto distanceRatio = (point - hotAreaStart) / (hotAreaEnd - hotAreaStart);
    auto speedFactor = Curves::SHARP->MoveInternal(distanceRatio);
    return ((MAX_DRAG_SCROLL_SPEED * speedFactor) / TIME_UNIT) * AUTO_SCROLL_INTERVAL;
}

void RichEditorPattern::ScheduleAutoScroll(AutoScrollParam param)
{
    if (GreatNotEqual(param.offset, 0.0f) && IsReachTop()) {
        return;
    }
    if (LessNotEqual(param.offset, 0.0f) && IsReachBottom()) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (param.isFirstRun_) {
        param.isFirstRun_ = false;
        currentScrollParam_ = param;
        if (isAutoScrollRunning_) {
            return;
        }
    }
    autoScrollTask_.Reset([weak = WeakClaim(this)]() {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnAutoScroll(client->currentScrollParam_);
        if (client->IsReachTop() || client->IsReachBottom()) {
            client->StopAutoScroll();
        }
    });
    isAutoScrollRunning_ = true;
    taskExecutor->PostDelayedTask(autoScrollTask_, TaskExecutor::TaskType::UI, AUTO_SCROLL_INTERVAL);
}

void RichEditorPattern::OnAutoScroll(AutoScrollParam param)
{
    if (param.showScrollbar) {
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->PlayScrollBarAppearAnimation();
        }
        param.showScrollbar = false;
    }

    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        auto newOffset = MoveTextRect(param.offset);
        if (param.isFirstHandle) {
            MoveSecondHandle(newOffset);
        } else {
            MoveFirstHandle(newOffset);
        }
        TextPattern::OnHandleMove(param.handleRect, param.isFirstHandle);
        if (NearEqual(newOffset, 0.0f)) {
            return;
        }
        ScheduleAutoScroll(param);
        return;
    }

    if (param.autoScrollEvent == AutoScrollEvent::DRAG) {
        auto newOffset = MoveTextRect(param.offset);
        if (NearEqual(newOffset, 0.0f)) {
            return;
        }
        ScheduleAutoScroll(param);
        return;
    }

    if (param.autoScrollEvent == AutoScrollEvent::MOUSE) {
        auto newOffset = MoveTextRect(param.offset);
        auto textOffset =
            Offset(param.eventOffset.GetX() - GetTextRect().GetX(), param.eventOffset.GetY() - GetTextRect().GetY());
        int32_t extend = paragraphs_.GetIndex(textOffset);
        textSelector_.Update(textSelector_.baseOffset, extend);
        SetCaretPosition(std::max(textSelector_.baseOffset, extend));
        if (NearEqual(newOffset, 0.0f)) {
            return;
        }
        ScheduleAutoScroll(param);
    }
}

void RichEditorPattern::StopAutoScroll()
{
    isAutoScrollRunning_ = false;
    autoScrollTask_.Cancel();
    prevAutoScrollOffset_ = OffsetF(0.0f, 0.0f);
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarDisappearAnimation();
    }
}

bool RichEditorPattern::NeedAiAnalysis(
    const CaretUpdateType targeType, const int32_t pos, const int32_t& spanStart, const std::string& content)
{
    if (spanStart < 0) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "NeedAiAnalysis -spanStart%{public}d,return!", spanStart);
        return false;
    }

    if (!InputAIChecker::NeedAIAnalysis(content, targeType, lastClickTimeStamp_ - lastAiPosTimeStamp_)) {
        return false;
    }

    if (IsClickBoundary(pos) && targeType == CaretUpdateType::PRESSED) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "NeedAiAnalysis IsClickBoundary,return!");
        return false;
    }
    return true;
}

void RichEditorPattern::AdjustCursorPosition(int32_t& pos)
{
    // the rich text has some spans, the pos is belong to the whole richtext content, should use (pos - spanStarint)
    int32_t spanStart = -1;
    // get the span text by the position, maybe text is empty
    std::string content = GetPositionSpansText(pos, spanStart);

    if (NeedAiAnalysis(CaretUpdateType::PRESSED, pos, spanStart, content)) {
        int32_t aiPos = pos - spanStart;
        DataDetectorMgr::GetInstance().AdjustCursorPosition(aiPos, content, lastAiPosTimeStamp_, lastClickTimeStamp_);
        if (aiPos < 0) {
            return;
        }
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get ai pos:%{public}d--spanStart%{public}d", aiPos, spanStart);
        pos = aiPos + spanStart;
    }
}

bool RichEditorPattern::AdjustWordSelection(int32_t& start, int32_t& end)
{
    // the rich text has some spans, the pos is belong to the whole richtext content, should use (pos - spanStarint)
    int32_t spanStart = -1;
    // get the span text by the position, maybe text is empty
    std::string content = GetPositionSpansText(start, spanStart);
    if (NeedAiAnalysis(CaretUpdateType::DOUBLE_CLICK, start, spanStart, content)) {
        int32_t aiPosStart = start - spanStart;
        int32_t aiPosEnd = end - spanStart;
        DataDetectorMgr::GetInstance().AdjustWordSelection(aiPosStart, content, aiPosStart, aiPosEnd);
        if (aiPosStart < 0 || aiPosEnd < 0) {
            return false;
        }

        start = std::min(aiPosStart + spanStart, GetTextContentLength());
        end = std::min(aiPosEnd + spanStart, GetTextContentLength());
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get ai selector [%{public}d--%{public}d", start, end);
        return true;
    }
    return false;
}

bool RichEditorPattern::IsClickBoundary(const int32_t position)
{
    if (InputAIChecker::IsSingleClickAtBoundary(position, GetTextContentLength())) {
        return true;
    }

    float height = 0;
    auto handleOffset = CalcCursorOffsetByPosition(position, height);
    if (InputAIChecker::IsMultiClickAtBoundary(handleOffset, TextPattern::GetTextRect())) {
        return true;
    }
    return false;
}

std::string RichEditorPattern::GetPositionSpansText(int32_t position, int32_t& startSpan)
{
    int32_t start = position - AI_TEXT_RANGE_LEFT;
    int32_t end = position + AI_TEXT_RANGE_RIGHT;

    start = std::clamp(start, 0, GetTextContentLength());
    end = std::clamp(end, 0, GetTextContentLength());

    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get span pos:%{public}d-start:%{public}d-end:%{public}d", position, start, end);

    // get all the spans between start and end, then filter the valid text
    auto infos = GetSpansInfo(start, end, GetSpansMethod::ONSELECT);
    if (infos.GetSelection().resultObjects.empty()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get spans text is null pos:%{public}d,return", position);
        return "";
    }
    auto list = infos.GetSelection().resultObjects;

    std::stringstream sstream;
    for (const auto& obj : list) {
        if (obj.type == SelectSpanType::TYPEIMAGE) {
            if (obj.spanPosition.spanRange[1] <= position) {
                sstream.str("");
                startSpan = -1;
            } else {
                break;
            }
        } else if (obj.type == SelectSpanType::TYPESPAN) {
            if (startSpan < 0) {
                startSpan = obj.spanPosition.spanRange[0] + obj.offsetInSpan[0];
            }
            // we should use the wide string deal to avoid crash
            auto wideText = StringUtils::ToWstring(obj.valueString);
            sstream << StringUtils::ToString(
                wideText.substr(obj.offsetInSpan[0], obj.offsetInSpan[1] - obj.offsetInSpan[0]));
        }
    }

    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get spans text ret spanStart:%{public}d", startSpan);
    return sstream.str();
}

void RichEditorPattern::CheckHandles(SelectHandleInfo& handleInfo)
{
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
}

bool RichEditorPattern::CheckHandleVisible(const RectF& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    // use global offset.
    RectF visibleContentRect(contentRect_.GetOffset() + parentGlobalOffset_, contentRect_.GetSize());
    auto parent = host->GetAncestorNodeOfFrame();
    visibleContentRect = GetVisibleContentRect(parent, visibleContentRect);
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintRect.Left(), paintRect.Top() + BOX_EPSILON };
    return visibleContentRect.IsInRegion(bottomPoint) && visibleContentRect.IsInRegion(topPoint);
}

bool RichEditorPattern::IsShowSelectMenuUsingMouse()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(selectOverlayManager, false);
    return selectOverlayManager->GetSelectOverlayInfo().isUsingMouse;
}

RefPtr<FocusHub> RichEditorPattern::GetFocusHub() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    return focusHub;
}

void RichEditorPattern::HandleCursorOnDragMoved(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isCursorAlwaysDisplayed_) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
                "In OnDragMoved, the cursor has always Displayed in the textField, id:%{public}d", host->GetId());
        }
        return;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "In OnDragMoved, the dragging node is moving in the richEditor, id:%{public}d", host->GetId());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
    isCursorAlwaysDisplayed_ = true;
    StartTwinkling();
};

void RichEditorPattern::HandleCursorOnDragLeaved(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "In OnDragLeaved, the dragging node has left from richEditor, id:%{public}d", host->GetId());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->LostFocus();
    isCursorAlwaysDisplayed_ = false;
    StopTwinkling();
};

void RichEditorPattern::HandleCursorOnDragEnded(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    StopAutoScroll();
    if (!isCursorAlwaysDisplayed_) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "In OnDragEnded,"
            " the released location is not in the current richEditor, id:%{public}d", host->GetId());
        focusHub->LostFocus();
        StopTwinkling();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "In OnDragEnded, the released location is in the current richEditor, id:%{public}d", host->GetId());
    if (HasFocus()) {
        RequestKeyboard(false, true, true);
    } else {
        focusHub->RequestFocusImmediately();
    }
    isCursorAlwaysDisplayed_ = false;
    StartTwinkling();
};

void RichEditorPattern::HandleOnDragStatusCallback(
    const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    ScrollablePattern::HandleOnDragStatusCallback(dragEventType, notifyDragEvent);
    switch (dragEventType) {
        case DragEventType::MOVE:
            isDragging_ = true;
            HandleCursorOnDragMoved(notifyDragEvent);
            break;
        case DragEventType::LEAVE:
            HandleCursorOnDragLeaved(notifyDragEvent);
            break;
        case DragEventType::DROP:
            isDragging_ = false;
            HandleCursorOnDragEnded(notifyDragEvent);
            break;
        default:
            break;
    }
}

void RichEditorPattern::HandleOnCameraInput()
{
#if defined(ENABLE_STANDARD_INPUT)
    if (richEditTextChangeListener_ == nullptr) {
        richEditTextChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (!inputMethod) {
        return;
    }
    StartTwinkling();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (imeShown_) {
        inputMethod->StartInputType(MiscServices::InputType::CAMERA_INPUT);
    } else {
        auto optionalTextConfig = GetMiscTextConfig();
        CHECK_NULL_VOID(optionalTextConfig.has_value());
        MiscServices::TextConfig textConfig = optionalTextConfig.value();
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnCameraInput set calling window id is : %{public}u",
            textConfig.windowId);
#ifdef WINDOW_SCENE_SUPPORTED
        auto systemWindowId = GetSCBSystemWindowId();
        if (systemWindowId) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "windowId From %{public}u to %{public}u.", textConfig.windowId,
                systemWindowId);
            textConfig.windowId = systemWindowId;
        }
#endif
        inputMethod->Attach(richEditTextChangeListener_, false, textConfig);
        inputMethod->StartInputType(MiscServices::InputType::CAMERA_INPUT);
        inputMethod->ShowTextInput();
    }
#endif
#endif
}

bool RichEditorPattern::CanStartAITask()
{
    return !HasFocus();
}

bool RichEditorPattern::NeedShowAIDetect()
{
    return textDetectEnable_ && !aiSpanMap_.empty() && enabled_ && copyOption_ != CopyOptions::None && !HasFocus();
}

void RichEditorPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("enableDataDetector", textDetectEnable_ ? "true" : "false");
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("types", "");
    json->Put("dataDetectorConfig", jsonValue->ToString().c_str());
}

void RichEditorPattern::GetCaretMetrics(CaretMetricsF& caretCaretMetric)
{
    float caretHeight = 0.0f;
    OffsetF caretOffset = CalcCursorOffsetByPosition(GetCaretPosition(), caretHeight);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto offset = host->GetPaintRectOffset();
    caretOffset += offset;
    caretCaretMetric.offset = caretOffset;
    caretCaretMetric.height = caretHeight;
}
} // namespace OHOS::Ace::NG
