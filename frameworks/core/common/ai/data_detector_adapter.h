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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AI_PROPERTIES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AI_PROPERTIES_H

#include <set>

#include "interfaces/inner_api/ace/ai/data_detector_interface.h"
#include "interfaces/inner_api/ace/ai/data_url_analyzer.h"

#include "base/memory/ace_type.h"
#include "base/thread/cancelable_callback.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::AAFwk {
class Want;
class WantParams;
} // namespace OHOS::AAFwk

namespace OHOS::Ace {

namespace NG {
class TextPattern;
class RichEditorPattern;
}

struct AISpan {
    int32_t start = 0;
    int32_t end = 0;
    std::string content = "";
    TextDataDetectType type = TextDataDetectType::PHONE_NUMBER;
    bool operator==(const AISpan& span) const
    {
        return start == span.start && end == span.end && content == span.content && type == span.type;
    }
};
class DataDetectorAdapter : public AceType {
    DECLARE_ACE_TYPE(DataDetectorAdapter, AceType);

public:
    DataDetectorAdapter() = default;
    ~DataDetectorAdapter() override = default;

    RefPtr<NG::FrameNode> GetHost() const
    {
        return frameNode_.Upgrade();
    }
    void SetTextDetectResult(const TextDataDetectResult result)
    {
        textDetectResult_ = result;
    }
    void FireFinalResult();
    void FireOnResult(const std::string& result)
    {
        if (onResult_) {
            onResult_(result);
        }
    }
    bool ParseOriText(const std::unique_ptr<JsonValue>& entityJson, std::u16string& text);
    void PreprocessTextDetect();
    void InitTextDetect(int32_t startPos, std::string detectText);
    void HandleTextUrlDetect();
    void HandleUrlResult(std::vector<UrlEntity> urlEntities);
    void SetTextDetectTypes(const std::string& types);
    void ParseAIResult(const TextDataDetectResult& result, int32_t startPos);
    void ParseAIJson(const std::unique_ptr<JsonValue>& jsonValue, TextDataDetectType type, int32_t startPos);
    void StartAITask();
    void CancelAITask()
    {
        if (aiDetectDelayTask_) {
            aiDetectDelayTask_.Cancel();
        }
        aiDetectInitialized_ = false;
    }
    bool ShowAIEntityMenu(const AISpan& aiSpan, const NG::RectF& aiRect, const RefPtr<NG::FrameNode>& targetNode,
        bool isShowCopy = true, bool isShowSelectText = true);
    void ResponseBestMatchItem(const AISpan& aiSpan);
    void GetAIEntityMenu();
    void MarkDirtyNode() const;

private:
    friend class NG::TextPattern;
    friend class NG::RichEditorPattern;

    std::function<void()> GetDetectDelayTask(const std::map<int32_t, AISpan>& aiSpanMap);
    void OnClickAIMenuOption(const AISpan& aiSpan, const std::pair<std::string, FuncVariant>& menuOption,
        const RefPtr<NG::FrameNode>& targetNode = nullptr);

    WeakPtr<NG::FrameNode> frameNode_;
    bool aiDetectInitialized_ = false;
    bool hasClickedAISpan_ = false;
    bool pressedByLeftMouse_ = false;
    bool typeChanged_ = false;
    bool hasClickedMenuOption_ = false;
    bool hasUrlType_ = false;
    uint8_t aiDetectFlag_ = 0;
    std::vector<NG::RectF> aiSpanRects_;
    AISpan clickedAISpan_;
    std::string textDetectTypes_;
    std::u16string textForAI_;
    std::u16string lastTextForAI_;
    std::set<std::string> textDetectTypesSet_;
    TextDataDetectResult textDetectResult_;
    std::function<void(const std::string&)> onResult_;
    std::function<void(const std::string&)> onClickMenu_;
    std::map<int32_t, AISpan> aiSpanMap_;
    CancelableCallback<void()> aiDetectDelayTask_;
    std::unordered_map<int32_t, std::string> entityJson_;
    TimeStamp startDetectorTimeStamp_;
    std::vector<std::string> detectTexts_;
    int32_t mainContainerId_ = -1;
    std::optional<Color> entityColor_;
    std::optional<TextDecoration> entityDecorationType_;
    std::optional<Color> entityDecorationColor_;
    std::optional<TextDecorationStyle> entityDecorationStyle_;
    std::string textDetectConfigStr_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_AI_PROPERTIES_H
