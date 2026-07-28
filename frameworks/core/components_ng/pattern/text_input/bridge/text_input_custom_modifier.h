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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_BRIDGE_TEXT_INPUT_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_BRIDGE_TEXT_INPUT_CUSTOM_MODIFIER_H

#include <chrono>

#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/interfaces/native/node/node_api.h"

namespace panda {
template<typename T>
class Local;
class JSValueRef;
namespace ecmascript {
class EcmaVM;
} // namespace ecmascript
using EcmaVM = ecmascript::EcmaVM;
} // namespace panda
namespace OHOS::Ace {
class Color;
class Dimension;
class TextInputClient;
class IAceStylusCallback;
struct IMEClient;
struct ResultData;
enum class CommandType;
using IMEAttachCallback = std::function<void(IMEClient&)>;
namespace NG {
class Pattern;
class CalcLength;
class FrameNode;
class FocusHub;
struct KeyboardAppearanceConfig;
template<typename T>
class OffsetT;
using OffsetF = OffsetT<float>;
template<typename T>
struct BorderRadiusPropertyT;
using BorderRadiusProperty = BorderRadiusPropertyT<Dimension>;
template<typename T>
struct PaddingPropertyT;
using PaddingProperty = PaddingPropertyT<CalcLength>;
constexpr static uint32_t SECONDS_TO_MILLISECONDS = 1000;
} // namespace NG

struct ArkUITextInputCustomModifier {
    ArkUINodeHandle (*createTextInputNode)(int32_t nodeId);
    void (*setTextFieldWidthAuto)(NG::FrameNode* frameNode, bool value);
    void (*setTextFieldPadding)(NG::FrameNode* frameNode, const NG::PaddingProperty& newPadding, bool tmp);
    void (*setTextFieldMargin)(NG::FrameNode* frameNode);
    void (*setTextFieldBackBorder)(NG::FrameNode* frameNode);
    void (*setTextFieldBackgroundColor)(NG::FrameNode* frameNode, const std::optional<Color>& color);
    void (*setTextFieldTextColor)(NG::FrameNode* frameNode, const std::optional<Color>& color);
    void (*updateTextFieldTextColor)(NG::FrameNode* frameNode, const Color& color);
    std::optional<NG::BorderRadiusProperty> (*getTextFieldThemeBorderRadius)(NG::FrameNode* frameNode);
    void (*updateTextFieldValueAtCreation)(
        NG::FrameNode* frameNode, const std::optional<std::u16string>& value);
    void (*setTextFieldOnChangeEvent)(NG::FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    RefPtr<NG::FocusHub> (*getSearchTextFieldFocusHub)(const RefPtr<NG::FrameNode>& frameNode);
    void (*requestTextFieldKeyboardForStylus)(const RefPtr<NG::FrameNode>& frameNode, int32_t& resultCode);
    void (*setTextFieldTextForStylus)(const RefPtr<NG::FrameNode>& frameNode, const std::string& text,
        const std::shared_ptr<IAceStylusCallback>& callback, const ResultData& res);
    void (*getText)(
        const RefPtr<NG::FrameNode>& frameNode, const std::shared_ptr<IAceStylusCallback>& callback, ResultData& res);
    void (*redoTextField)(const RefPtr<NG::FrameNode>& frameNode);
    void (*undoTextField)(const RefPtr<NG::FrameNode>& frameNode);
    void (*onDetectorSync)(const RefPtr<NG::FrameNode>& frameNode, bool& result, const CommandType& command);
    void (*setKeyboardAppearanceConfig)(NG::FrameNode* frameNode, NG::KeyboardAppearanceConfig config);
    IMEAttachCallback (*parseAndCreateIMEAttachCallback)(
        panda::EcmaVM* vm, panda::Local<panda::JSValueRef> callbackArg, NG::FrameNode* frameNode, bool isJsView);
    std::string (*extractTextFieldText)(const RefPtr<NG::FrameNode>& frameNode);
    bool (*needAIAnalysis)(bool isEmpty, NG::CaretUpdateType targetType,
        std::chrono::duration<float, std::ratio<1, NG::SECONDS_TO_MILLISECONDS>> timeout);
    bool (*isSingleClickAtBoundary)(int32_t position, int32_t textLength);
    bool (*isMultiClickAtBoundary)(const NG::OffsetF& handleOffset, const NG::RectF& textRect);
    RefPtr<NG::Pattern> (*createTextFieldPattern)();
    void (*updateCaretInfoToController)(const RefPtr<NG::Pattern>& pattern, bool forceUpdate);
    int32_t (*getSessionId)(const RefPtr<NG::FrameNode>& host);
    void (*triggerCustomKeyboardAvoid)(const RefPtr<NG::Pattern>& pattern);
    bool (*getTextByPattern)(const RefPtr<NG::FrameNode>& frameNode, std::string& text);
    void* (*createTextChangedListenerImpl)(const WeakPtr<TextInputClient>& pattern);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_INPUT_BRIDGE_TEXT_INPUT_CUSTOM_MODIFIER_H
