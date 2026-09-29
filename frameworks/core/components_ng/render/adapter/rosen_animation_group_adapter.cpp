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

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include "render_service_client/core/animation/rs_motion_path_option.h"
#include "render_service_client/core/ui/rs_node.h"
#include "ui/animation/curve.h"
#include "ui/animation/curves.h"

#include "core/common/container.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/animation/animation_group_adapter.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/interfaces/native/node/animation_group_util.h"

namespace OHOS::Ace::NG {

namespace {

constexpr int32_t BOUNDS_W_IDX = 2;
constexpr int32_t BOUNDS_H_IDX = 3;
constexpr int32_t ROTATE_Z_IDX = 2;
constexpr int32_t VEC2_CNT = 2;
constexpr int32_t ROTATE_CNT = 3;
constexpr int32_t BOUNDS_CNT = 4;

int32_t GetExpectedValueSize(OH_ArkUI_AnimationPropertyType propertyType)
{
    switch (propertyType) {
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION:
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE:
            return VEC2_CNT;
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION:
            return ROTATE_CNT;
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS:
            return BOUNDS_CNT;
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_X:
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Z:
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE_X:
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_X:
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Z:
        case OH_ARKUI_ANIMATION_PROPERTY_OPACITY:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_X:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_Y:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_WIDTH:
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_HEIGHT:
        case OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR:
            return 1;
        default:
            return 0;
    }
}

void SetPropertyValues(const std::shared_ptr<Rosen::RSNode>& rsNode, OH_ArkUI_AnimationPropertyType propertyType,
    const std::vector<ArkUI_NumberValue>& values, bool isFrom)
{
    if (static_cast<int32_t>(values.size()) < GetExpectedValueSize(propertyType)) {
        return;
    }
    switch (propertyType) {
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION:
            rsNode->SetTranslate(Rosen::Vector2f { values[0].f32, values[1].f32 });
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_X:
            rsNode->SetTranslateX(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Y:
            rsNode->SetTranslateY(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_TRANSLATION_Z:
            rsNode->SetTranslateZ(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE:
            rsNode->SetScale(values[0].f32, values[1].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE_X:
            rsNode->SetScaleX(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_SCALE_Y:
            rsNode->SetScaleY(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION:
            rsNode->SetRotation(values[0].f32, values[1].f32, values[ROTATE_Z_IDX].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_X:
            rsNode->SetRotationX(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Y:
            rsNode->SetRotationY(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_ROTATION_Z:
            rsNode->SetRotation(values[0].f32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_OPACITY:
            rsNode->SetAlpha(std::clamp(values[0].f32, 0.0f, 1.0f));
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS:
            rsNode->SetBounds(values[0].i32, values[1].i32, values[BOUNDS_W_IDX].i32, values[BOUNDS_H_IDX].i32);
            rsNode->SetFrame(values[0].i32, values[1].i32, values[BOUNDS_W_IDX].i32, values[BOUNDS_H_IDX].i32);
            break;
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_X: {
            auto bounds = rsNode->GetStagingProperties().GetBounds();
            rsNode->SetBounds(values[0].i32, bounds[1], bounds[BOUNDS_W_IDX], bounds[BOUNDS_H_IDX]);
            rsNode->SetFrame(values[0].i32, bounds[1], bounds[BOUNDS_W_IDX], bounds[BOUNDS_H_IDX]);
            break;
        }
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_Y: {
            auto bounds = rsNode->GetStagingProperties().GetBounds();
            rsNode->SetBounds(bounds[0], values[0].i32, bounds[BOUNDS_W_IDX], bounds[BOUNDS_H_IDX]);
            rsNode->SetFrame(bounds[0], values[0].i32, bounds[BOUNDS_W_IDX], bounds[BOUNDS_H_IDX]);
            break;
        }
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_WIDTH: {
            auto bounds = rsNode->GetStagingProperties().GetBounds();
            int32_t w = std::max(values[0].i32, 0);
            rsNode->SetBounds(bounds[0], bounds[1], w, bounds[BOUNDS_H_IDX]);
            rsNode->SetFrame(bounds[0], bounds[1], w, bounds[BOUNDS_H_IDX]);
            break;
        }
        case OH_ARKUI_ANIMATION_PROPERTY_BOUNDS_HEIGHT: {
            auto bounds = rsNode->GetStagingProperties().GetBounds();
            int32_t h = std::max(values[0].i32, 0);
            rsNode->SetBounds(bounds[0], bounds[1], bounds[BOUNDS_W_IDX], h);
            rsNode->SetFrame(bounds[0], bounds[1], bounds[BOUNDS_W_IDX], h);
            break;
        }
        case OH_ARKUI_ANIMATION_PROPERTY_BACKGROUND_COLOR:
            rsNode->SetBackgroundColor(values[0].u32);
            break;
        default:
            break;
    }
}

void HandlePropertyChild(const std::shared_ptr<Rosen::RSNode>& rsNode, const PropertyChildView& view,
    const RefPtr<Curve>& groupCurve)
{
    RefPtr<Curve> childCurve = view.curve;
    if (!childCurve) {
        childCurve = groupCurve;
    }
    if (!childCurve) {
        childCurve = Curves::LINEAR;
    }

    auto propertyType = view.propertyType;
    auto fromValue = view.fromValue;
    auto toValue = view.toValue;

    if (!fromValue.empty()) {
        AnimationUtils::ExecuteWithoutAnimation(
            [rsNode, propertyType, fromValue]() { SetPropertyValues(rsNode, propertyType, fromValue, true); });
    }

    std::function<void()> propCallback = [rsNode, propertyType, toValue]() {
        if (!toValue.empty()) {
            SetPropertyValues(rsNode, propertyType, toValue, false);
        }
    };

    auto option = view.option;
    option.SetCurve(childCurve);
    AnimationUtils::Animate(option, propCallback);
}

void HandleKeyframeChild(const std::shared_ptr<Rosen::RSNode>& rsNode, const KeyframeChildView& view,
    const RefPtr<Curve>& groupCurve)
{
    RefPtr<Curve> implicitCurve = view.implicitCurve;
    if (!implicitCurve) {
        implicitCurve = groupCurve;
    }
    if (!implicitCurve) {
        implicitCurve = Curves::LINEAR;
    }

    auto propertyType = view.propertyType;
    if (!view.keyframes.empty() && NearEqual<double>(view.keyframes.front().fraction, 0.0) &&
        !view.keyframes.front().values.empty()) {
        auto initValues = view.keyframes.front().values;
        AnimationUtils::ExecuteWithoutAnimation(
            [rsNode, propertyType, initValues]() { SetPropertyValues(rsNode, propertyType, initValues, false); });
    }

    AnimationUtils::OpenImplicitAnimation(view.option, implicitCurve, nullptr);

    for (const auto& keyframe : view.keyframes) {
        RefPtr<Curve> keyframeCurve = keyframe.curve;
        if (!keyframeCurve) {
            keyframeCurve = implicitCurve;
        }
        if (!keyframeCurve) {
            keyframeCurve = Curves::LINEAR;
        }
        auto values = keyframe.values;
        std::function<void()> keyframeCallback = [rsNode, propertyType, values]() {
            if (!values.empty()) {
                SetPropertyValues(rsNode, propertyType, values, false);
            }
        };
        AnimationUtils::AddDurationKeyFrame(keyframe.segmentDuration, keyframeCurve, keyframeCallback);
    }

    AnimationUtils::CloseImplicitAnimation();
}

void HandlePathChild(const std::shared_ptr<Rosen::RSNode>& rsNode, const PathChildView& view,
    const RefPtr<Curve>& groupCurve)
{
    RefPtr<Curve> childCurve = view.curve;
    if (!childCurve) {
        childCurve = groupCurve;
    }
    if (!childCurve) {
        childCurve = Curves::LINEAR;
    }

    auto previousMotionPathOption = rsNode->GetMotionPathOption();
    auto motionPathOption = std::make_shared<Rosen::RSMotionPathOption>(view.path);
    motionPathOption->SetBeginFraction(0.0f);
    motionPathOption->SetEndFraction(1.0f);
    motionPathOption->SetRotationMode(
        view.autoRotation ? Rosen::RotationMode::ROTATE_AUTO : Rosen::RotationMode::ROTATE_NONE);
    motionPathOption->SetPathNeedAddOrigin(false);
    rsNode->SetMotionPathOption(motionPathOption);

    auto translate = rsNode->GetStagingProperties().GetTranslate();
    float translateX = translate[0];
    float translateY = translate[1];
    AnimationUtils::ExecuteWithoutAnimation([rsNode, translateX, translateY]() {
        rsNode->SetTranslate(Rosen::Vector2f { translateX + 0.01f, translateY });
    });

    std::function<void()> pathCallback = [rsNode, translateX, translateY]() {
        rsNode->SetTranslate(Rosen::Vector2f { translateX, translateY });
    };
    auto option = view.option;
    option.SetCurve(childCurve);
    AnimationUtils::Animate(option, pathCallback);
    rsNode->SetMotionPathOption(previousMotionPathOption);
}

} // namespace

bool ValidateRSNodeInstance(
    const std::vector<Rosen::RSNode*>& rsNodes, int32_t instanceId)
{
    std::shared_ptr<Rosen::RSUIContext> contextRSUIContext;
    {
        ContainerScope scope(instanceId);
        contextRSUIContext = AnimationUtils::GetCurrentRSUIContext(nullptr);
    }
    for (auto* rsNode : rsNodes) {
        if (!rsNode) {
            continue;
        }
        auto nodeInstanceId = rsNode->GetInstanceId();
        if (nodeInstanceId != INSTANCE_ID_UNDEFINED) {
            if (nodeInstanceId != instanceId) {
                return false;
            }
        } else if (contextRSUIContext) {
            auto nodeRSUIContext = rsNode->GetRSUIContext();
            if (nodeRSUIContext && nodeRSUIContext != contextRSUIContext) {
                return false;
            }
        }
    }
    return true;
}

std::shared_ptr<AnimationUtils::InteractiveAnimation> CreateAndStartGroupAnimation(
    ArkUIAnimationGroupHandle group, const std::vector<Rosen::RSNode*>& childRawRSNodes,
    int32_t instanceId, const std::string& key, int64_t generation)
{
    CHECK_NULL_RETURN(group, nullptr);
    if (childRawRSNodes.empty()) {
        return nullptr;
    }

    std::vector<std::shared_ptr<Rosen::RSNode>> childRSNodes;
    childRSNodes.reserve(childRawRSNodes.size());
    for (auto* rawRSNode : childRawRSNodes) {
        if (!rawRSNode) {
            return nullptr;
        }
        childRSNodes.push_back(rawRSNode->shared_from_this());
    }

    AnimationGroupView view;
    auto result = BuildAnimationGroupView(group, view);
    if (result != ARKUI_ERROR_CODE_NO_ERROR) {
        return nullptr;
    }

    RefPtr<Curve> groupCurve = view.curve;
    AnimationOption groupOption = std::move(view.option);
    auto userOnFinish = std::move(view.onFinish);
    std::function<void()> onFinishWrapper = [userOnFinish = std::move(userOnFinish),
                                                instanceId, key, generation]() {
        if (userOnFinish) {
            userOnFinish();
        }
        AnimationGroupAdapter::GetInstance().RemoveIfMatched(instanceId, key, generation);
    };

    std::function<void()> addCallback = [childRSNodes = std::move(childRSNodes), view = std::move(view)]() {
        const RefPtr<Curve>& groupCurveRef = view.curve;
        size_t idx = 0;
        for (const auto& child : view.children) {
            auto rsNode = idx < childRSNodes.size() ? childRSNodes[idx] : nullptr;
            idx++;
            if (!rsNode) {
                continue;
            }
            if (const auto* propView = std::get_if<PropertyChildView>(&child)) {
                HandlePropertyChild(rsNode, *propView, groupCurveRef);
            } else if (const auto* kfView = std::get_if<KeyframeChildView>(&child)) {
                HandleKeyframeChild(rsNode, *kfView, groupCurveRef);
            } else if (const auto* pathView = std::get_if<PathChildView>(&child)) {
                HandlePathChild(rsNode, *pathView, groupCurveRef);
            }
        }
    };

    auto interactiveAnimation = AnimationUtils::CreateGroupInteractiveAnimation(
        addCallback, groupOption, groupCurve, onFinishWrapper);
    CHECK_NULL_RETURN(interactiveAnimation, nullptr);

    if (AnimationUtils::StartInteractiveAnimation(interactiveAnimation) != 0) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "StartInteractiveAnimation failed");
        return nullptr;
    }
    return interactiveAnimation;
}

} // namespace OHOS::Ace::NG
