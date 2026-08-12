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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_BRIDGE_RICH_EDITOR_CUSTOM_MODIFIER_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_BRIDGE_RICH_EDITOR_CUSTOM_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace {
struct ImageSpanOptions;
class JsonValue;
class ThemeConstants;
namespace NG {
struct DrawingContext;
class EventHub;
class FrameNode;
class GestureEventHub;
class ImageSpanNode;
struct KeyboardAppearanceConfig;
class OneStepDragController;
class PlaceholderSpanNode;
class PipelineContext;
template<typename T>
class RectT;
using RectF = RectT<float>;
class RichEditorTheme;
struct SelectMenuParam;
enum class TextSpanType : int32_t;
struct TextSelector;
class RichEditorController;
class RichEditorBaseController;
struct SelectOverlayInfo;
class TextPattern;
class ServiceCollaborationAceCallback;
class ServiceCollaborationMenuAceHelper;
} // namespace NG
class TokenThemeWrapper;

struct ArkUIRichEditorCustomModifier {
    RefPtr<NG::FrameNode> (*createRichEditorImpl)(int32_t nodeId);
    RefPtr<NG::FrameNode> (*createRichEditorStyledStringNode)(int32_t nodeId);
    bool (*addImageSpanFromCollaboration)(ImageSpanOptions& options,
        const RefPtr<NG::ServiceCollaborationAceCallback>& callback, uint32_t code,
        const RefPtr<NG::ServiceCollaborationMenuAceHelper>& helper);
    bool (*paintLeadingMarginSpan)(RefPtr<NG::TextPattern>& hostPattern, const void* paragraphInfo,
        const NG::OffsetT<float>& offset, NG::DrawingContext& drawingContext);
    RefPtr<NG::RichEditorTheme> (*getRichEditorTheme)(const RefPtr<NG::PipelineContext>& pipeline);
    RefPtr<NG::RichEditorTheme> (*getRichEditorThemeByScopeId)(
        const RefPtr<NG::PipelineContext>& pipeline, int32_t themeScopeId);
    bool (*getRichEditorDraggable)(const RefPtr<NG::PipelineContext>& pipeline);
    bool (*regisiterCaretChangeListener)(
        std::shared_ptr<NG::SelectOverlayInfo>& info, std::function<void(int32_t)>&& listener);
    NG::RectF (*getCaretRect)(std::shared_ptr<NG::SelectOverlayInfo>& info);
    void (*setKeyboardAppearanceConfig)(NG::FrameNode* frameNode, NG::KeyboardAppearanceConfig config);
    RefPtr<NG::FrameNode> (*getHost)(RefPtr<NG::RichEditorController> controller);
    bool (*getContentBySpans)(const RefPtr<NG::FrameNode>& frameNode, std::u16string& text);
    std::string (*extractRichEditorText)(const RefPtr<NG::FrameNode>& node);
    RefPtr<NG::RichEditorTheme> (*buildRichEditorTheme)(const RefPtr<ThemeConstants>& themeConstants);
    RefPtr<TokenThemeWrapper> (*buildRichEditorThemeWrapper)(const RefPtr<ThemeConstants>& themeConstants);
};
}

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_BRIDGE_RICH_EDITOR_CUSTOM_MODIFIER_H
