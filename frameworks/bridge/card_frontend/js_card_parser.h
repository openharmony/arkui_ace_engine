/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_JS_CARD_PARSER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_JS_CARD_PARSER_H

#include <map>
#include <vector>

#include "base/memory/referenced.h"
#include "frameworks/bridge/card_frontend/media_queryer.h"
#include "frameworks/bridge/js_frontend/frontend_delegate_impl.h"
#include "frameworks/bridge/js_frontend/js_command.h"

namespace OHOS::Ace::Framework {

enum class ParsingStatus { CREATE, UPDATE };

class ACE_EXPORT JsCardParser : public Referenced {
public:
    JsCardParser(const WeakPtr<PipelineContext>& context, const WeakPtr<AssetManager>& assertManager,
        std::unique_ptr<JsonValue>&& rootBody)
        : Referenced(false), context_(context), assetManager_(assertManager), rootBody_(std::move(rootBody))
    {}
    ~JsCardParser() override = default;

    void ParseAttributes(const std::unique_ptr<JsonValue>& rootJson, int32_t nodeId,
        std::vector<std::pair<std::string, std::string>>& attrs, JsCommandDomElementOperator* command);
    bool GetShownValue(std::string& value);
    bool GetRepeatData(std::unique_ptr<JsonValue>& repeatValue, std::string& key);

    void ParseStyles(const std::unique_ptr<JsonValue>& rootJson, int32_t nodeId,
        std::vector<std::pair<std::string, std::string>>& styles);
    void ParseEvents(const std::unique_ptr<JsonValue>& rootJson, std::vector<std::string>& events,
        const RefPtr<JsAcePage>& page, int32_t nodeId);
    void UpdatePageData(const std::string& dataList, const RefPtr<JsAcePage>& page);
    void LoadImageInfo();
    void UpdateStyle(const RefPtr<JsAcePage>& page);
    void CreateDomNode(const RefPtr<Framework::JsAcePage>& page, const std::unique_ptr<JsonValue>& rootJson,
        int32_t parentId, bool isNewNode = false);
    void ParseVariable(std::string& value);
    void ParseMultiVariable(std::string& value);

    void ParseRepeatIndexItem(const std::unique_ptr<JsonValue>& repeatValue);
    void SetRepeatItemValue(uint32_t index, const std::unique_ptr<JsonValue>& repeatValue, bool hasKeyValue);
    bool Initialize();

    const WeakPtr<PipelineContext>& GetPipelineContext() const
    {
        return context_;
    }

    void SetColorMode(ColorMode colorMode)
    {
        colorMode_ = colorMode;
        mediaQueryer_.SetColorMode(colorMode);
    }

    void SetDensity(double density)
    {
        density_ = density;
    }

    void ResetNodeId()
    {
        maxNodeId_ = nodeId_;
        numberOfForNode_ = 0;
        nodeId_ = 0;
    }

    int32_t GetNumberOfNodes() const
    {
        return maxNodeId_;
    }

    // add for test case
    void SetIsRepeat(bool isRepeat)
    {
        isRepeat_ = isRepeat;
    }

    void OnSurfaceChanged(int32_t width, int32_t height);

private:
    void GetResImageUrl(std::string& value);
    bool GetI18nData(std::string& value);
    void GetPlurals(std::string& value);
    void ParseInlineStyles(
        const std::unique_ptr<JsonValue>& rootJson, std::vector<std::pair<std::string, std::string>>& styles);
    void SelectStyle(const std::string& className, const std::unique_ptr<JsonValue>& styleClass,
        std::vector<std::pair<std::string, std::string>>& styles);
    void SelectMediaQueryStyle(const std::string& styleClass, std::vector<std::pair<std::string, std::string>>& styles);
    void LoadMediaQueryStyle();
    void LoadResImageUrl(const std::string& jsonFile, const std::string& splitStr, std::string& value);
    void RegisterFont(const std::string& fontFamily);
    std::string GetEventAction(const std::string& action, const std::string& actionType, int32_t nodeId);
    bool ParseComplexExpression(std::string& value);
    bool ParseTernaryExpression(std::string& value);
    bool ParseLogicalExpression(std::string& value);
    bool ParseArrayExpression(const std::string& expression, std::stack<std::string>& keyStack);
    void UpdateDomNode(const RefPtr<Framework::JsAcePage>& page, const std::unique_ptr<JsonValue>& rootJson,
        int32_t parentId, const std::vector<int>& idArray = std::vector<int>());
    bool ParseSpecialVariable(std::string& value);
    bool GetVariable(std::string& value);
    template<typename T>
    void ParseSpecialAttr(const std::function<void(const std::unique_ptr<JsonValue>&, std::vector<T>&)>& function,
        std::string& value, std::vector<T>& vector);
    template<typename T>
    void ParseSpecialAttr(
        const std::function<void(const std::unique_ptr<JsonValue>&, T&)>& function, std::string& variable, T& value);
    bool ParsePointOperator(const std::string& tmpKey, std::stack<std::string>& keyStack, const std::string& dataJson);
    void ResetRepeatIndexItem();
    void CreateRepeatDomNode(
        const RefPtr<Framework::JsAcePage>& page, const std::unique_ptr<JsonValue>& rootJson, int32_t parentId);
    void GetResourceValue(const std::string& path);
    void GetClockConfig(const std::unique_ptr<JsonValue>& jsonDataSets, ClockConfig& clockConfig);
    void ProcessRepeatNode(const RefPtr<Framework::JsAcePage>& page,
        const std::unique_ptr<JsonValue>& rootJson, const std::string& key, int32_t parentId, bool hasKeyValue,
        std::unique_ptr<JsonValue>& repeatValue);
    void SetUpdateStatus(const RefPtr<Framework::JsAcePage>& page);
    void GetShownAttr(const std::unique_ptr<JsonValue>& rootJson, bool& shouldShow, bool& hasShownAttr);
    void CreateBlockNode(
        const RefPtr<Framework::JsAcePage>& page, const std::unique_ptr<JsonValue>& rootJson, int32_t parentId);
    void GetBoolValue(
        const std::unique_ptr<JsonValue>& rootJson, const std::string& key, bool& shouldShow, bool& hasShownAttr);

    double density_ = 1.0;
    int32_t nodeId_ = 0;
    int32_t maxNodeId_ = 0;
    int32_t numberOfForNode_ = 0;
    int32_t listNodeIndex_ = 0;
    ColorMode colorMode_ = ColorMode::LIGHT;
    ParsingStatus parsingStatus_ = ParsingStatus::CREATE;
    std::vector<int32_t> idArray_;
    WeakPtr<PipelineContext> context_;
    WeakPtr<AssetManager> assetManager_;
    std::unique_ptr<JsonValue> rootBody_;
    std::unique_ptr<JsonValue> styleJson_;
    std::unique_ptr<JsonValue> rootJson_;
    std::unique_ptr<JsonValue> eventJson_;
    std::unique_ptr<JsonValue> dataJson_;
    std::unique_ptr<JsonValue> repeatJson_;
    std::unique_ptr<JsonValue> resourceJson_;
    std::unordered_map<std::string, std::string> imageUrlMap_;
    std::unordered_map<int32_t, std::pair<std::vector<int32_t>, int32_t>> listIdMap_;
    std::unordered_map<std::string, int32_t> singleLoopMap_;
    std::unordered_map<std::string, std::unique_ptr<JsonValue>> mediaQueryStyles_;
    MediaQueryer mediaQueryer_;

    // for repeat attr
    bool isRepeat_ = false;
    std::string repeatIndex_;
    std::string repeatItem_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_JS_CARD_PARSER_H
