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

#include "core/components_ng/pattern/text/text_pattern.h"

#include <cstdint>
#include <iterator>
#include <stack>
#include <string>

#include "adapter/ohos/capability/clipboard/clipboard_impl.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "base/window/drag_window.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/common/udmf/udmf_client.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/text/text_emoji_processor.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t API_PROTEXTION_GREATER_NINE = 9;
}; // namespace

void TextPattern::OnAttachToFrameNodeMultiThread()
{
    // nothing, thread unsafe
}

void TextPattern::OnDetachFromFrameNodeMultiThread(FrameNode* node)
{
    // nothing, thread unsafe
}

void TextPattern::OnAttachToMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline_ = pipeline;
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->AddFontNodeNG(host);
    }
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        if (pipeline->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE) {
            host->GetRenderContext()->UpdateClipEdge(true);
            host->GetRenderContext()->SetClipToFrame(true);
        }
    }
    InitSurfaceChangedCallback();
    InitSurfacePositionChangedCallback();
    pipeline->AddWindowStateChangedCallback(host->GetId());
    pipeline->AddWindowSizeChangeCallback(host->GetId());
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    textLayoutProperty->UpdateTextAlign(theme->GetTextStyle().GetTextAlign());
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
    isDetachFromMainTree_ = false;
}

void TextPattern::OnDetachFromMainTreeMultiThread()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FrameNode* node = RawPtr(host);
    dataDetectorAdapter_->aiDetectDelayTask_.Cancel();
    CloseSelectOverlay();
    auto pipeline = pipeline_.Upgrade();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    if (HasSurfacePositionChangedCallback()) {
        pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionChangedCallbackId_.value_or(-1));
    }
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->UnRegisterCallbackNG(frameNode);
        fontManager->RemoveVariationNodeNG(frameNode);
    }
    pipeline->RemoveOnAreaChangeNode(node->GetId());
    pipeline->RemoveWindowStateChangedCallback(node->GetId());
    pipeline->RemoveVisibleAreaChangeNode(node->GetId());
    pipeline->RemoveWindowSizeChangeCallback(node->GetId());
    isDetachFromMainTree_ = true;
}

void TextPattern::OnModifyDoneMultiThread()
{
    Pattern::OnModifyDone();
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto nowTime = static_cast<unsigned long long>(GetSystemTimestamp());
    ACE_TEXT_SCOPED_TRACE("OnModifyDone[Text][id:%d][time:%llu]", host->GetId(), nowTime);
    auto logTag = "OnModifyDone:" + std::to_string(nowTime);
    DumpRecord(logTag, true);
    LogForFormRender(logTag);
    auto pipeline = host->GetContext();
    if (!(pipeline && pipeline->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE)) {
        bool shouldClipToContent =
            textLayoutProperty->GetTextOverflow().value_or(TextOverflow::CLIP) == TextOverflow::CLIP;
        host->GetRenderContext()->SetClipToFrame(shouldClipToContent);
    }
    if (textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE) {
        if (!renderContext->GetClipEdge().has_value()) {
            renderContext->UpdateClipEdge(true);
            renderContext->SetClipToFrame(true);
        }
        UpdateMarqueeStartPolicy();
    }
    const auto& children = host->GetChildren();
    if (children.empty()) {
        std::u16string textCache = textForDisplay_;
        if (!isSpanStringMode_) {
            textForDisplay_ = textLayoutProperty->GetContent().value_or(u"");
        }
        if (textCache != textForDisplay_) {
            host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, UtfUtils::Str16DebugToStr8(textCache),
                UtfUtils::Str16DebugToStr8(textForDisplay_));
            dataDetectorAdapter_->aiDetectInitialized_ = false;
            CloseSelectOverlay();
            ResetSelection();
        }

        if (CanStartAITask() && !dataDetectorAdapter_->aiDetectInitialized_) {
            ParseOriText(textForDisplay_);
        }
    }
    RecoverCopyOption();

    // Multi Thread
    OnModifyDoneMultiThreadAddition();
}

void TextPattern::OnModifyDoneMultiThreadAddition()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (setTextDetectEnableMultiThread_) {
        setTextDetectEnableMultiThread_ = false;
        if (textDetectEnable_) {
            auto callback = [weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->dataDetectorAdapter_->GetAIEntityMenu();
            };
            pipeline->SetConfigChangedCallback(host->GetId(), callback);
        } else {
            dataDetectorAdapter_->CancelAITask();
        }
        host->MarkDirtyWithOnProChange(PROPERTY_UPDATE_MEASURE);
    }
    if (setExternalSpanItemMultiThread_) {
        setExternalSpanItemMultiThread_ = false;
        ProcessSpanString();
        auto layoutProperty = GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateContent(textForDisplay_);
    }
}

void TextPattern::SetTextDetectEnableMultiThread(bool enable)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    dataDetectorAdapter_->frameNode_ = host;
    if (enable == textDetectEnable_) {
        return;
    }
    textDetectEnable_ = enable;
    setTextDetectEnableMultiThread_ = true;
}

void TextPattern::SetStyledStringMultiThread(const RefPtr<SpanString>& value, bool closeSelectOverlay)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AllocStyledString();
    isSpanStringMode_ = true;
    host->PostAfterAttachMainTreeTask([
        spanString = WeakClaim(RawPtr(value)), closeSelectOverlay, weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto value = spanString.Upgrade();
        CHECK_NULL_VOID(value);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        if (closeSelectOverlay) {
            pattern->CloseSelectOverlay();
        }
        auto length = pattern->styledString_->GetLength();
        pattern->styledString_->RemoveCustomSpan();
        pattern->styledString_->ReplaceSpanString(0, length, value);
        pattern->spans_ = pattern->styledString_->GetSpanItems();
        pattern->ProcessSpanString();
        pattern->styledString_->AddCustomSpan();
        pattern->styledString_->SetFramNode(WeakClaim(Referenced::RawPtr(host)));
        host->MarkDirtyWithOnProChange(PROPERTY_UPDATE_MEASURE);
    });
}

void TextPattern::SetExternalSpanItemMultiThread(const std::list<RefPtr<SpanItem>>& spans)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    isSpanStringMode_ = !spans.empty();
    if (isSpanStringMode_) {
        AllocStyledString();
    }
    spans_ = spans;
    setExternalSpanItemMultiThread_ = true;
}
} // namespace OHOS::Ace::NG
