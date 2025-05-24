/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/patternlock/patternlock_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<V2::PatternLockController> PatternLockModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PATTERN_LOCK_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::PATTERN_LOCK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<PatternLockPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    pattern->SetPatternLockController(AceType::MakeRefPtr<V2::PatternLockController>());
    return pattern->GetPatternLockController();
}

void PatternLockModelNG::SetPatternComplete(NG::PatternLockCompleteEvent&& onComplete)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(onComplete));
}

void PatternLockModelNG::SetDotConnect(std::function<void(int32_t)>&& onDotConnect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDotConnect(std::move(onDotConnect));
}

void PatternLockModelNG::SetSelectedColor(const Color& selectedColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, selectedColor);
}

void PatternLockModelNG::SetAutoReset(bool isAutoReset)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset);
}

void PatternLockModelNG::SetPathColor(const Color& pathColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, pathColor);
}

void PatternLockModelNG::SetActiveColor(const Color& activeColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, activeColor);
}

void PatternLockModelNG::SetRegularColor(const Color& regularColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, regularColor);
}

void PatternLockModelNG::SetCircleRadius(const Dimension& radius)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, radius);
}

void PatternLockModelNG::SetSideLength(const Dimension& sideLength)
{
    ACE_UPDATE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, sideLength);
}

void PatternLockModelNG::SetStrokeWidth(const Dimension& lineWidth)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, lineWidth);
}

void PatternLockModelNG::SetActiveCircleColor(const Color& activeCircleColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor, activeCircleColor);
}

void PatternLockModelNG::SetActiveCircleRadius(const Dimension& activeCircleRadius)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius, activeCircleRadius);
}

void PatternLockModelNG::SetEnableWaveEffect(bool enableWaveEffect)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect, enableWaveEffect);
}

void PatternLockModelNG::SetEnableForeground(bool enableForeground)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, EnableForeground, enableForeground);
}

void PatternLockModelNG::SetSkipUnselectedPoint(bool isSkipUnselectedPoint)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, SkipUnselectedPoint, isSkipUnselectedPoint);
}

void PatternLockModelNG::SetActiveColor(FrameNode* frameNode, const Color& activeColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, activeColor, frameNode);
}

void PatternLockModelNG::SetCircleRadius(FrameNode* frameNode, const Dimension& radius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, radius, frameNode);
}

void PatternLockModelNG::SetSelectedColor(FrameNode* frameNode, const Color& selectedColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, selectedColor, frameNode);
}

void PatternLockModelNG::SetSideLength(FrameNode* frameNode, const Dimension& sideLength)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, sideLength, frameNode);
}

void PatternLockModelNG::SetAutoReset(FrameNode* frameNode, bool isAutoReset)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset, frameNode);
}

void PatternLockModelNG::SetStrokeWidth(FrameNode* frameNode, const Dimension& lineWidth)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, lineWidth, frameNode);
}

void PatternLockModelNG::SetRegularColor(FrameNode* frameNode, const Color& regularColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, regularColor, frameNode);
}

void PatternLockModelNG::SetPathColor(FrameNode* frameNode, const Color& pathColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, pathColor, frameNode);
}

void PatternLockModelNG::SetActiveCircleColor(FrameNode* frameNode, const Color& activeCircleColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor, activeCircleColor, frameNode);
}

void PatternLockModelNG::SetActiveCircleRadius(FrameNode* frameNode, const Dimension& activeCircleRadius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius, activeCircleRadius, frameNode);
}

void PatternLockModelNG::SetEnableWaveEffect(FrameNode* frameNode, bool enableWaveEffect)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, EnableWaveEffect, enableWaveEffect, frameNode);
}

void PatternLockModelNG::SetEnableForeground(FrameNode* frameNode, bool enableForeground)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, EnableForeground, enableForeground, frameNode);
}

void PatternLockModelNG::SetSkipUnselectedPoint(FrameNode* frameNode, bool isSkipUnselectedPoint)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SkipUnselectedPoint, isSkipUnselectedPoint, frameNode);
}

void PatternLockModelNG::SetPatternComplete(FrameNode* frameNode, NG::PatternLockCompleteEvent&& onComplete)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(onComplete));
}
void PatternLockModelNG::SetDotConnect(FrameNode* frameNode, std::function<void(int32_t)>&& onDotConnect)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<PatternLockEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDotConnect(std::move(onDotConnect));
}

void PatternLockModelNG::CreateWithResourceObj(JsResourceType jsResourceType, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    if (resObj) {
        switch (jsResourceType) {
            case JsResourceType::SELECTEDCOLOR: {
                std::string key = "patternLock.selectedColor";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    std::string color = pattern->GetResCacheMapByKey(key);
                    Color result;
                    if (color.empty()) {
                        if (ResourceParseUtils::ParseResColor(resObj, result)) {
                            pattern->AddResCache(key, result.ColorToString());
                        } else {
                            auto pipeline = PipelineBase::GetCurrentContext();
                            CHECK_NULL_VOID(pipeline);
                            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
                            CHECK_NULL_VOID(theme);
                            result = theme->GetSelectedColor();
                        }
                    } else {
                        result = Color::ColorFromString(color);
                    }
                    pattern->UpdateSelectedColor(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));

                break;
            }
            case JsResourceType::PATHCOLOR: {
                std::string key = "patternLock.pathColor";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    std::string color = pattern->GetResCacheMapByKey(key);
                    Color result;
                    if (color.empty()) {
                        if (ResourceParseUtils::ParseResColor(resObj, result)) {
                            pattern->AddResCache(key, result.ColorToString());
                        } else {
                            auto pipeline = PipelineBase::GetCurrentContext();
                            CHECK_NULL_VOID(pipeline);
                            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
                            CHECK_NULL_VOID(theme);
                            result = theme->GetPathColor();
                        }
                    } else {
                        result = Color::ColorFromString(color);
                    }
                    pattern->UpdatePathColor(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));
                break;
            }
            case JsResourceType::ACTIVECOLOR: {
                std::string key = "patternLock.activeColor";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    std::string color = pattern->GetResCacheMapByKey(key);
                    Color result;
                    if (color.empty()) {
                        if (ResourceParseUtils::ParseResColor(resObj, result)) {
                            pattern->AddResCache(key, result.ColorToString());
                        } else {
                            auto pipeline = PipelineBase::GetCurrentContext();
                            CHECK_NULL_VOID(pipeline);
                            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
                            CHECK_NULL_VOID(theme);
                            result = theme->GetActiveColor();
                        }
                    } else {
                        result = Color::ColorFromString(color);
                    }
                    pattern->UpdateActiveColor(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));
                break;
            }
            case JsResourceType::REGULARCOLOR: {
                std::string key = "patternLock.regularColor";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    std::string color = pattern->GetResCacheMapByKey(key);
                    Color result;
                    if (color.empty()) {
                        if (ResourceParseUtils::ParseResColor(resObj, result)) {
                            pattern->AddResCache(key, result.ColorToString());
                        } else {
                            auto pipeline = PipelineBase::GetCurrentContext();
                            CHECK_NULL_VOID(pipeline);
                            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
                            CHECK_NULL_VOID(theme);
                            result = theme->GetRegularColor();
                        }
                    } else {
                        result = Color::ColorFromString(color);
                    }
                    pattern->UpdateRegularColor(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));
                break;
            }
            case JsResourceType::CIRCLERADIUS: {
                std::string key = "patternLock.circleRadius";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    CalcDimension result;
                    if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                        auto pipeline = PipelineBase::GetCurrentContext();
                        CHECK_NULL_VOID(pipeline);
                        auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
                        CHECK_NULL_VOID(theme);
                        result = theme->GetCircleRadius();
                    }
                    pattern->UpdateCircleRadius(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));
                break;
            }
            case JsResourceType::SIDELENGTH: {
                std::string key = "patternLock.sideLength";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    CalcDimension result;
                    if (!ResourceParseUtils::ParseResDimensionVp(resObj, result)) {
                        auto pipeline = PipelineBase::GetCurrentContext();
                        CHECK_NULL_VOID(pipeline);
                        auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
                        CHECK_NULL_VOID(theme);
                        result = theme->GetSideLength();
                    }
                    pattern->UpdateSideLength(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));
                break;
            }
            case JsResourceType::ACTIVECIRCLECOLOR: {
                std::string key = "patternLock.activeCircleColor";
                auto&& updateFunc = [pattern, key](const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
                    std::string color = pattern->GetResCacheMapByKey(key);
                    Color result;
                    if (color.empty()) {
                        if (ResourceParseUtils::ParseResColor(resObj, result)) {
                            pattern->AddResCache(key, result.ColorToString());
                        } else {
                            result = Color::TRANSPARENT;
                        }
                    } else {
                        result = Color::ColorFromString(color);
                    }
                    pattern->UpdateActiveCircleColor(result, isFristLoad);
                };
                updateFunc(resObj, true);
                pattern->AddResObj(key, resObj, std::move(updateFunc));
                break;
            }
            default:
                break;
        }
    }
}
} // namespace OHOS::Ace::NG
