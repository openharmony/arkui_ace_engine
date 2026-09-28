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

#include "core/common/container.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/one_step_drag_controller.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/select_overlay/service_collaboration_menu_ace_helper.h"
#include "core/interfaces/native/node/rich_editor_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_static.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme_wrapper.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/common/resource/resource_object.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {

RefPtr<NG::FrameNode> CreateRichEditorStyledStringNode(int32_t nodeId)
{
    return RichEditorModelNG::CreateRichEditorStyledStringNode(nodeId);
}

void ServiceCollaborationAceCallback::RemovePopupNode() {}

bool AddImageSpanFromCollaboration(
    ImageSpanOptions& options, const RefPtr<ServiceCollaborationAceCallback>& callback,
    uint32_t code, const RefPtr<ServiceCollaborationMenuAceHelper>& helper)
{
    CHECK_NULL_RETURN(callback && callback->info_ && helper, false);
    auto richEditorPattern = AceType::DynamicCast<RichEditorPattern>(callback->info_->pattern.Upgrade());
    CHECK_NULL_RETURN(richEditorPattern, false);
    if (!richEditorPattern->GetTextSelector().SelectNothing()) {
            richEditorPattern->DeleteBackward(1);
    }
    options.offset = richEditorPattern->GetCaretPosition() + helper->photoCount_;
    richEditorPattern->AddImageSpanFromCollaboration(options, false);
    helper->photoCount_++;
    if (code == SEND_PHOTO_SUCCESS) {
        richEditorPattern->SetCaretPosition(richEditorPattern->GetCaretPosition() + helper->photoCount_);
        callback->RemovePopupNode();
        callback->isTransmit_ = false;
        callback->info_ = nullptr;
        callback->isMultiImage_ = false;
    }
    return true;
}

bool PaintLeadingMarginSpan(RefPtr<NG::TextPattern>& hostPattern, const void* paragraphInfo,
    const OffsetT<float>& offset, NG::DrawingContext& drawingContext)
{
    CHECK_NULL_RETURN(hostPattern, false);
    auto pattern = AceType::DynamicCast<RichEditorPattern>(hostPattern);
    CHECK_NULL_RETURN(pattern, false);
    CHECK_NULL_RETURN(paragraphInfo, false);
    pattern->GetRichEditorParagraphManager().PaintLeadingMarginSpan(
        *static_cast<const NG::ParagraphManager::ParagraphInfo*>(paragraphInfo), offset, drawingContext);
    return true;
}

RefPtr<NG::RichEditorTheme> GetRichEditorTheme(const RefPtr<NG::PipelineContext>& pipeline)
{
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<RichEditorTheme>();
}

RefPtr<NG::RichEditorTheme> GetRichEditorThemeByScopeId(
    const RefPtr<NG::PipelineContext>& pipeline, int32_t themeScopeId)
{
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<RichEditorTheme>(themeScopeId);
}

RefPtr<NG::RichEditorTheme> BuildRichEditorTheme(const RefPtr<ThemeConstants>& themeConstants)
{
    CHECK_NULL_RETURN(themeConstants, nullptr);
    return RichEditorTheme::Builder().Build(themeConstants);
}

RefPtr<TokenThemeWrapper> BuildRichEditorThemeWrapper(const RefPtr<ThemeConstants>& themeConstants)
{
    CHECK_NULL_RETURN(themeConstants, nullptr);
    return RichEditorThemeWrapper::WrapperBuilder().BuildWrapper(themeConstants);
}

bool GetRichEditorDraggable(const RefPtr<NG::PipelineContext>& pipeline)
{
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->GetDraggable<RichEditorTheme>();
}

bool RegisiterCaretChangeListener(std::shared_ptr<NG::SelectOverlayInfo>& info, std::function<void(int32_t)>&& listener)
{
    CHECK_NULL_RETURN(info, false);
    auto pattern = AceType::DynamicCast<RichEditorPattern>(info->pattern.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    pattern->RegisiterCaretChangeListener(std::move(listener));
    return true;
}

NG::RectF GetCaretRect(std::shared_ptr<NG::SelectOverlayInfo>& info)
{
    CHECK_NULL_RETURN(info, {});
    auto pattern = AceType::DynamicCast<RichEditorPattern>(info->pattern.Upgrade());
    CHECK_NULL_RETURN(pattern, {});
    return pattern->GetCaretRect();
}

void SetRichEditorKeyboardAppearanceConfig(FrameNode* frameNode, KeyboardAppearanceConfig config)
{
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetKeyboardAppearanceConfig(frameNode, config);
}

RefPtr<NG::FrameNode> CreateRichEditorImpl(int32_t nodeId)
{
    return RichEditorModelStatic::CreateFrameNode(nodeId);
}

RefPtr<NG::FrameNode> GetHost(RefPtr<NG::RichEditorController> controller)
{
    CHECK_NULL_RETURN(controller, nullptr);
    return controller->GetHost();
}

bool GetContentBySpans(const RefPtr<NG::FrameNode>& frameNode, std::u16string& text)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = AceType::DynamicCast<RichEditorPattern>(frameNode->GetPattern());
    CHECK_NULL_RETURN(pattern, false);
    pattern->GetContentBySpans(text);
    return true;
}

 std::string ExtractRichEditorText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, "");
    auto richEditorPattern = node->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, "");
    std::u16string text;
    richEditorPattern->GetContentBySpans(text);
    if (text.empty()) {
        return richEditorPattern->GetPlaceHolder();
    }
    return UtfUtils::Str16DebugToStr8(text);
}

std::optional<float> GetEnvFontScale(RefPtr<NG::RichEditorBaseController> controller)
{
    CHECK_NULL_RETURN(controller, std::nullopt);
    return controller->GetEnvFontScale();
}

void RequestRichEditorKeyboardForStylus(const RefPtr<NG::FrameNode>& frameNode, int32_t& resultCode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<NG::RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RequestKeyboardForStylus();
    resultCode = 0;
}

namespace NodeModifier {
void SetRichEditorShowCounter(ArkUINodeHandle node, ArkUIShowCountOptions* showCountOptions,
    void* counterTextColorRawPtr, void* counterTextOverflowColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(showCountOptions);
    RichEditorModelNG::SetShowCounter(frameNode, static_cast<bool>(showCountOptions->open));
    RichEditorModelNG::SetCounter(frameNode, showCountOptions->thresholdPercentage);
    RichEditorModelNG::SetShowHighlightBorder(frameNode, static_cast<bool>(showCountOptions->highlightBorder));
    if (showCountOptions->counterTextColorIsSet) {
        RichEditorModelNG::SetCounterTextColor(frameNode, Color(showCountOptions->counterTextColor));
    } else {
        RichEditorModelNG::ResetCounterTextColor(frameNode);
    }
    if (showCountOptions->counterTextOverflowColorIsSet) {
        RichEditorModelNG::SetCounterTextOverflowColor(frameNode, Color(showCountOptions->counterTextOverflowColor));
    } else {
        RichEditorModelNG::ResetCounterTextOverflowColor(frameNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        if (counterTextColorRawPtr) {
            auto resObjTextColor = AceType::Claim(reinterpret_cast<ResourceObject*>(counterTextColorRawPtr));
            pattern->RegisterResource<Color>(
                "counterTextColor", resObjTextColor, Color(showCountOptions->counterTextColor));
        } else {
            pattern->UnRegisterResource("counterTextColor");
        }
        if (counterTextOverflowColorRawPtr) {
            auto resObjTextOverflowColor =
                AceType::Claim(reinterpret_cast<ResourceObject*>(counterTextOverflowColorRawPtr));
            pattern->RegisterResource<Color>(
                "counterTextOverflowColor", resObjTextOverflowColor,
                Color(showCountOptions->counterTextOverflowColor));
        } else {
            pattern->UnRegisterResource("counterTextOverflowColor");
        }
    }
}

void ResetRichEditorShowCounter(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetShowCounter(frameNode, false);
    RichEditorModelNG::SetCounter(frameNode, -1);
    RichEditorModelNG::SetShowHighlightBorder(frameNode, true);
    RichEditorModelNG::ResetCounterTextColor(frameNode);
    RichEditorModelNG::ResetCounterTextOverflowColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("counterTextColor");
        pattern->UnRegisterResource("counterTextOverflowColor");
    }
}

void GetRichEditorShowCounterOptions(ArkUINodeHandle node, ArkUIShowCountOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    options->open = RichEditorModelNG::GetShowCounter(frameNode);
    options->thresholdPercentage = RichEditorModelNG::GetCounterType(frameNode);
    options->highlightBorder = RichEditorModelNG::GetShowCounterBorder(frameNode);
    options->counterTextColor = RichEditorModelNG::GetCounterTextColor(frameNode).GetValue();
    options->counterTextOverflowColor = RichEditorModelNG::GetCounterTextOverflowColor(frameNode).GetValue();
}

const ArkUIRichEditorCustomModifier* GetRichEditorCustomModifier()
{
    static const ArkUIRichEditorCustomModifier modifier = {
        .createRichEditorImpl = CreateRichEditorImpl,
        .createRichEditorStyledStringNode = CreateRichEditorStyledStringNode,
        .addImageSpanFromCollaboration = AddImageSpanFromCollaboration,
        .paintLeadingMarginSpan = PaintLeadingMarginSpan,
        .getRichEditorTheme = GetRichEditorTheme,
        .getRichEditorThemeByScopeId = GetRichEditorThemeByScopeId,
        .getRichEditorDraggable = GetRichEditorDraggable,
        .regisiterCaretChangeListener = RegisiterCaretChangeListener,
        .getCaretRect = GetCaretRect,
        .setKeyboardAppearanceConfig = SetRichEditorKeyboardAppearanceConfig,
        .getHost = GetHost,
        .getContentBySpans = GetContentBySpans,
        .extractRichEditorText = ExtractRichEditorText,
        .getEnvFontScale = GetEnvFontScale,
        .buildRichEditorTheme = BuildRichEditorTheme,
        .buildRichEditorThemeWrapper = BuildRichEditorThemeWrapper,
        .requestRichEditorKeyboardForStylus = RequestRichEditorKeyboardForStylus,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
