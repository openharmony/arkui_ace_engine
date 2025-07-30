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
    auto pros = frameNode->GetPaintProperty<PatternLockPaintProperty>();
    if (pros) {
        pros->ResetPathColorSetByUser();
        pros->ResetRegularColorSetByUser();
        pros->ResetActiveColorSetByUser();
        pros->ResetSelectedColorSetByUser();
    }
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
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColorSetByUser, true);
}

void PatternLockModelNG::SetSelectedColorByUser(bool isByuserSet)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColorSetByUser, isByuserSet);
}

void PatternLockModelNG::SetAutoReset(bool isAutoReset)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset);
}

void PatternLockModelNG::SetPathColor(const Color& pathColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, pathColor);
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathColorSetByUser, true);
}

void PatternLockModelNG::SetPathColorByUser(bool isByuserSet)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, PathColorSetByUser, isByuserSet);
}

void PatternLockModelNG::SetActiveColor(const Color& activeColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColor, activeColor);
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColorSetByUser, true);
}

void PatternLockModelNG::SetActiveColorByUser(bool isByuserSet)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColorSetByUser, isByuserSet);
}

void PatternLockModelNG::SetRegularColor(const Color& regularColor)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, regularColor);
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColorSetByUser, true);
}

void PatternLockModelNG::SetRegularColorByUser(bool isByuserSet)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColorSetByUser, isByuserSet);
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
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColorSetByUser, true);
}

void PatternLockModelNG::SetActiveCircleColorByUser(bool isByuserSet)
{
    ACE_UPDATE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColorSetByUser, isByuserSet);
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
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColorSetByUser, true, frameNode);
}

void PatternLockModelNG::SetActiveColorByUser(FrameNode* frameNode, bool isByuserSet)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveColorSetByUser, isByuserSet, frameNode);
}

void PatternLockModelNG::SetPathColor(FrameNode* frameNode, const Color& pathColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColor, pathColor, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColorSetByUser, true, frameNode);
}

// const RefPtr<V2::PatternLockController> PatternLockModelNG::GetController(FrameNode* frameNode)
// {
//     CHECK_NULL_RETURN(frameNode, nullptr);
//     auto pattern = frameNode->GetPattern<PatternLockPattern>();
//     CHECK_NULL_RETURN(pattern, nullptr);
//     return pattern->GetPatternLockController();
// }

// void PatternLockModelNG::SetActiveColor(FrameNode* frameNode, const std::optional<Color>& activeColor)
// {
//     ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, selectedColor, frameNode);
//     ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColorSetByUser, true, frameNode);
// }

void PatternLockModelNG::SetSelectedColorByUser(FrameNode* frameNode, bool isByuserSet)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColorSetByUser, isByuserSet, frameNode);
}

void PatternLockModelNG::SetCircleRadius(FrameNode* frameNode, const Dimension& radius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, CircleRadius, radius, frameNode);
}

void PatternLockModelNG::SetSelectedColor(FrameNode* frameNode, const Color& selectedColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColor, selectedColor, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, SelectedColorSetByUser, true, frameNode);
}

void PatternLockModelNG::SetSideLength(FrameNode* frameNode, const Dimension& sideLength)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(PatternLockLayoutProperty, SideLength, sideLength, frameNode);
}

void PatternLockModelNG::SetAutoReset(FrameNode* frameNode, bool isAutoReset)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, AutoReset, isAutoReset, frameNode);
}

void PatternLockModelNG::SetRegularColorByUser(FrameNode* frameNode, bool isByuserSet)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColorSetByUser, isByuserSet, frameNode);
}

void PatternLockModelNG::SetStrokeWidth(FrameNode* frameNode, const Dimension& lineWidth)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathStrokeWidth, lineWidth, frameNode);
}

void PatternLockModelNG::SetPathColorByUser(FrameNode* frameNode, bool isByuserSet)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, PathColorSetByUser, isByuserSet, frameNode);
}

void PatternLockModelNG::SetRegularColor(FrameNode* frameNode, const Color& regularColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColor, regularColor, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, RegularColorSetByUser, true, frameNode);
}

void PatternLockModelNG::SetActiveCircleColorByUser(FrameNode* frameNode, bool isByuserSet)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColorSetByUser, isByuserSet, frameNode);
}


void PatternLockModelNG::SetActiveCircleRadius(FrameNode* frameNode, const Dimension& activeCircleRadius)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleRadius, activeCircleRadius, frameNode);
}

void PatternLockModelNG::SetActiveCircleColor(FrameNode* frameNode, const Color& activeCircleColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColor, activeCircleColor, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(PatternLockPaintProperty, ActiveCircleColorSetByUser, true, frameNode);
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

void PatternLockModelNG::CreateWithResourceObj(
    PatternLockResourceType PatternLockResourceType, const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, PatternLockResourceType, resObj);
}

void PatternLockModelNG::CreateWithResourceObj(
    FrameNode* frameNode, PatternLockResourceType PatternLockResourceType, const RefPtr<ResourceObject>& resObj)
{
    switch (PatternLockResourceType) {
        case PatternLockResourceType::SELECTEDCOLOR:
            HandleSelectedColorResource(frameNode, resObj);
            break;
        case PatternLockResourceType::PATHCOLOR:
            HandlePathColorResource(frameNode, resObj);
            break;
        case PatternLockResourceType::ACTIVECOLOR:
            HandleActiveColorResource(frameNode, resObj);
            break;
        case PatternLockResourceType::REGULARCOLOR:
            HandleRegularColorResource(frameNode, resObj);
            break;
        case PatternLockResourceType::CIRCLERADIUS:
            HandleCircleRadiusResource(frameNode, resObj);
            break;
        case PatternLockResourceType::SIDELENGTH:
            HandleSideLengthResource(frameNode, resObj);
            break;
        case PatternLockResourceType::ACTIVECIRCLECOLOR:
            HandleActiveCircleColorResource(frameNode, resObj);
            break;
        default:
            break;
    }
}

void PatternLockModelNG::HandleSelectedColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.selectedColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string color = pattern->GetResCacheMapByKey(key);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
            CHECK_NULL_VOID(theme);
            result = theme->GetSelectedColor();
        }
        pattern->UpdateSelectedColor(result, isFristLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void PatternLockModelNG::HandlePathColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.pathColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string color = pattern->GetResCacheMapByKey(key);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
            CHECK_NULL_VOID(theme);
            result = theme->GetPathColor();
        }
        pattern->UpdatePathColor(result, isFristLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void PatternLockModelNG::HandleActiveColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.activeColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string color = pattern->GetResCacheMapByKey(key);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
            CHECK_NULL_VOID(theme);
            result = theme->GetActiveColor();
        }
        pattern->UpdateActiveColor(result, isFristLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void PatternLockModelNG::HandleRegularColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.regularColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string color = pattern->GetResCacheMapByKey(key);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
            CHECK_NULL_VOID(theme);
            result = theme->GetRegularColor();
        }
        pattern->UpdateRegularColor(result, isFristLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void PatternLockModelNG::HandleCircleRadiusResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.circleRadius";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVp(resObj, result) || result.IsNonPositive()) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto theme = pipeline->GetTheme<V2::PatternLockTheme>();
            CHECK_NULL_VOID(theme);
            result = theme->GetCircleRadius();
        }
        pattern->UpdateCircleRadius(result, isFristLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void PatternLockModelNG::HandleSideLengthResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.sideLength";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
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
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void PatternLockModelNG::HandleActiveCircleColorResource(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    auto pattern = frameNode->GetPattern<PatternLockPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "patternLock.activeCircleColor";
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern)), key](
                            const RefPtr<ResourceObject>& resObj, bool isFristLoad = false) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        std::string color = pattern->GetResCacheMapByKey(key);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            result = Color::TRANSPARENT;
        }
        pattern->UpdateActiveCircleColor(result, isFristLoad);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}
} // namespace OHOS::Ace::NG
