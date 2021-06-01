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

#include "core/components/tween/tween_element.h"

#include "core/animation/curve_animation.h"
#include "core/common/frontend.h"
#include "core/components/clip/render_clip.h"
#include "core/components/display/display_component.h"
#include "core/components/shared_transition/shared_transition_element.h"
#include "core/components/transform/transform_component.h"
#include "core/components/tween/tween_component.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace {
namespace {
RefPtr<PropertyAnimatable> GetAnimatable(const RefPtr<Element>& contentElement)
{
    if (!contentElement) {
        LOGE("Get Animatable failed. content element is null.");
        return nullptr;
    }
    return AceType::DynamicCast<PropertyAnimatable>(contentElement->GetRenderNode());
}

void SetTranslateProperties(const RefPtr<Animation<DimensionOffset>>& translateAnimation, TweenOption& option)
{
    if (option.GetCurve()) {
        translateAnimation->SetCurve(option.GetCurve());
    }
    if (!translateAnimation->HasInitValue()) {
        DimensionOffset beginPos = DimensionOffset(Dimension(), Dimension());
        translateAnimation->SetInitValue(beginPos);
    }
}

void SetScaleProperties(const RefPtr<Animation<float>>& scaleAnimation, TweenOption& option)
{
    if (option.GetCurve()) {
        scaleAnimation->SetCurve(option.GetCurve());
    }
    if (!scaleAnimation->HasInitValue()) {
        scaleAnimation->SetInitValue(1.0f);
    }
}

void SetRotateProperties(const RefPtr<Animation<float>>& rotateAnimation, TweenOption& option)
{
    if (option.GetCurve()) {
        rotateAnimation->SetCurve(option.GetCurve());
    }
    if (!rotateAnimation->HasInitValue()) {
        rotateAnimation->SetInitValue(0.0f);
    }
}

void ResetController(RefPtr<Animator>& controller)
{
    if (!controller) {
        LOGE("Reset Controller failed. controller is null.");
        return;
    }
    if (controller->GetStatus() != Animator::Status::IDLE && controller->GetStatus() != Animator::Status::STOPPED) {
        controller->Finish();
    }
    controller->ClearInterpolators();
}

} // namespace

const LinearEnumMapNode<AnimationType,
    void (*)(const RefPtr<Animation<float>>&, WeakPtr<RenderTransform>&, TweenOption&)>
    TweenElement::transformFloatAnimationAddMap_[] = {
        { AnimationType::SCALE,
            [](const RefPtr<Animation<float>>& scaleAnimation, WeakPtr<RenderTransform>& weakRender,
                TweenOption& option) {
                SetScaleProperties(scaleAnimation, option);
                scaleAnimation->AddListener([weakRender, scaleAnimation](float value) {
                    auto renderTransformNode = weakRender.Upgrade();
                    if (renderTransformNode) {
                        if (scaleAnimation->ShouldSkipAnimation()) {
                            renderTransformNode->Scale(scaleAnimation->GetEndValue());
                        } else {
                            renderTransformNode->Scale(value);
                        }
                    }
                });
            } },
        { AnimationType::SCALE_X,
            [](const RefPtr<Animation<float>>& scaleXAnimation, WeakPtr<RenderTransform>& weakRender,
                TweenOption& option) {
                SetScaleProperties(scaleXAnimation, option);
                double maxScaleXY = option.GetMaxScaleXY();
                auto renderTransformNode = weakRender.Upgrade();
                if (renderTransformNode) {
                    renderTransformNode->SetMaxScaleXY(maxScaleXY);
                }
                scaleXAnimation->AddListener([weakRender, scaleXAnimation](float value) {
                    auto renderTransformNode = weakRender.Upgrade();
                    if (renderTransformNode) {
                        if (scaleXAnimation->ShouldSkipAnimation()) {
                            renderTransformNode->Scale(scaleXAnimation->GetEndValue(), 1.0f);
                        } else {
                            renderTransformNode->Scale(value, 1.0f);
                        }
                    }
                });
            } },
        { AnimationType::SCALE_Y,
            [](const RefPtr<Animation<float>>& scaleYAnimation, WeakPtr<RenderTransform>& weakRender,
                TweenOption& option) {
                SetScaleProperties(scaleYAnimation, option);
                scaleYAnimation->AddListener([weakRender, scaleYAnimation](float value) {
                    auto renderTransformNode = weakRender.Upgrade();
                    if (renderTransformNode) {
                        if (scaleYAnimation->ShouldSkipAnimation()) {
                            renderTransformNode->Scale(1.0f, scaleYAnimation->GetEndValue());
                        } else {
                            renderTransformNode->Scale(1.0f, value);
                        }
                    }
                });
            } },
        { AnimationType::ROTATE_Z,
            [](const RefPtr<Animation<float>>& rotateZAnimation, WeakPtr<RenderTransform>& weakRender,
                TweenOption& option) {
                SetRotateProperties(rotateZAnimation, option);
                rotateZAnimation->AddListener([weakRender, rotateZAnimation](float value) {
                    auto renderTransformNode = weakRender.Upgrade();
                    if (renderTransformNode) {
                        if (rotateZAnimation->ShouldSkipAnimation()) {
                            renderTransformNode->RotateZ(rotateZAnimation->GetEndValue());
                        } else {
                            renderTransformNode->RotateZ(value);
                        }
                    }
                });
            } },
        { AnimationType::ROTATE_X,
            [](const RefPtr<Animation<float>>& rotateXAnimation, WeakPtr<RenderTransform>& weakRender,
                TweenOption& option) {
                SetRotateProperties(rotateXAnimation, option);
                rotateXAnimation->AddListener([weakRender, rotateXAnimation](float value) {
                    auto renderTransformNode = weakRender.Upgrade();
                    if (renderTransformNode) {
                        if (rotateXAnimation->ShouldSkipAnimation()) {
                            renderTransformNode->RotateX(rotateXAnimation->GetEndValue());
                        } else {
                            renderTransformNode->RotateX(value);
                        }
                    }
                });
            } },
        { AnimationType::ROTATE_Y,
            [](const RefPtr<Animation<float>>& rotateYAnimation, WeakPtr<RenderTransform>& weakRender,
                TweenOption& option) {
                SetRotateProperties(rotateYAnimation, option);
                rotateYAnimation->AddListener([weakRender, rotateYAnimation](float value) {
                    auto renderTransformNode = weakRender.Upgrade();
                    if (renderTransformNode) {
                        if (rotateYAnimation->ShouldSkipAnimation()) {
                            renderTransformNode->RotateY(rotateYAnimation->GetEndValue());
                        } else {
                            renderTransformNode->RotateY(value);
                        }
                    }
                });
            } }
    };

void TweenElement::Update()
{
    ComposedElement::Update();
    if (!component_) {
        return;
    }
    auto tweenComponent = AceType::DynamicCast<TweenComponent>(component_);
    if (!tweenComponent) {
        LOGE("Get TweenComponent failed.");
        return;
    }
    shadow_ = tweenComponent->GetShadow();
    positionParam_ = tweenComponent->GetPositionParam();
    if (tweenComponent->IsOptionCssChanged()) {
        needUpdateTweenOption_ = true;
        option_ = tweenComponent->GetTweenOption();
        tweenComponent->SetOptionCssChanged(false);
    }
    if (tweenComponent->IsOptionCustomChanged()) {
        needUpdateTweenOptionCustom_ = true;
        optionCustom_ = tweenComponent->GetCustomTweenOption();
        tweenComponent->SetOptionCustomChanged(false);
    }
    if (tweenComponent->IsOperationCssChanged()) {
        operation_ = tweenComponent->GetTweenOperation();
        tweenComponent->SetOperationCssChanged(false);
    }
    if (tweenComponent->IsOperationCustomChanged()) {
        operationCustom_ = tweenComponent->GetCustomTweenOperation();
        tweenComponent->SetOperationCustomChanged(false);
    }
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext) {
        RefPtr<Animator> controller = tweenComponent->GetAnimator();
        if (controller) {
            isComponentController_ = true;
            if (!controller->HasScheduler()) {
                controller->AttachScheduler(context_);
            }
            controllerCustom_ = controller;
        }
        if (!controller_) {
            isDelegatedController_ = false;
            controller_ = AceType::MakeRefPtr<Animator>(context_);
            LOGD("set animator to component when update.");

            if (pipelineContext->GetIsDeclarative()) {
                controller_->SetDeclarativeAnimator(true);
            }
        }

        LOGD("add request to pipeline context.");
        pipelineContext->AddPostFlushListener(AceType::Claim(this));
    }
}

void TweenElement::ApplyOperation(RefPtr<Animator>& controller, TweenOperation& operation)
{
    LOGD("apply operation: %{public}d", operation);
    switch (operation) {
        case TweenOperation::PLAY:
            controller->Play();
            break;
        case TweenOperation::PAUSE:
            controller->Pause();
            break;
        case TweenOperation::CANCEL:
            controller->Cancel();
            break;
        case TweenOperation::FINISH:
            controller->Finish();
            break;
        case TweenOperation::REVERSE:
            controller->Reverse();
            break;
        case TweenOperation::NONE:
        default:
            break;
    }
}

void TweenElement::OnPostFlush()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }
    pipelineContext->AddPreFlushListener(AceType::Claim(this));
}

void TweenElement::OnPreFlush()
{
    if (!controller_ && !controllerCustom_) {
        LOGD("empty controller, skip start tween.");
        return;
    }
    SetVisible(VisibleType::VISIBLE);
    if (isDelegatedController_ && !isComponentController_) {
        LOGD("controller is set from outside. skip prepare animation.");
        return;
    }

    if (needUpdateTweenOption_) {
        ResetController(controller_);
        ApplyKeyframes();
        ApplyOptions();
        needUpdateTweenOption_ = false;
    }
    if (needUpdateTweenOptionCustom_) {
        ResetController(controllerCustom_);
        ApplyKeyframes(controllerCustom_, optionCustom_, prepareIdCustom_);
        ApplyOptions(controllerCustom_, optionCustom_);
        needUpdateTweenOptionCustom_ = false;
    }
    if (operation_ != TweenOperation::NONE || operationCustom_ != TweenOperation::NONE) {
        auto pipelineContext = context_.Upgrade();
        if (!pipelineContext) {
            return;
        }
    }

    LOGD("Start tween animation with operation: %{public}d, operationCustom: %{public}d", operation_, operationCustom_);
    if (controller_) {
        ApplyOperation(controller_, operation_);
    }
    if (controllerCustom_) {
        ApplyOperation(controllerCustom_, operationCustom_);
    }

    // reset operation to none.
    operation_ = TweenOperation::NONE;
    operationCustom_ = TweenOperation::NONE;
}

bool TweenElement::IsNeedAnimation(RefPtr<Animator>& controller, TweenOption& option)
{
    if (!controller) {
        LOGE("add interpolator failed. controller is null.");
        return false;
    }
    bool needAnimation = false;
    auto& transformOffsetAnimations = option.GetTranslateAnimations();
    for (auto&& [translate, animation] : transformOffsetAnimations) {
        if (animation) {
            needAnimation = true;
            LOGD("add translate animation.");
            controller->AddInterpolator(animation);
        }
    }
    auto& transformFloatAnimations = option.GetTransformFloatAnimation();
    for (auto&& [transformFloat, animation] : transformFloatAnimations) {
        if (animation) {
            needAnimation = true;
            LOGD("add transform float animation.");
            controller->AddInterpolator(animation);
        }
    }
    auto& opacityAnimation = option.GetOpacityAnimation();
    if (opacityAnimation) {
        LOGD("add opacity animation.");
        controller->AddInterpolator(opacityAnimation);
        needAnimation = true;
    }
    auto& colorAnimation = option.GetColorAnimation();
    if (colorAnimation) {
        LOGD("add color animation.");
        controller->AddInterpolator(colorAnimation);
        needAnimation = true;
    }
    auto& backgroundPositionAnimation = option.GetBackgroundPositionAnimation();
    if (backgroundPositionAnimation) {
        LOGD("add background position animation.");
        controller->AddInterpolator(backgroundPositionAnimation);
        needAnimation = true;
    }

    if (AddToAnimator(option.GetFloatPropertyAnimation(), controller, option)) {
        needAnimation = true;
    }
    return needAnimation;
}

RefPtr<Component> TweenElement::BuildChild()
{
    RefPtr<TweenComponent> tween = AceType::DynamicCast<TweenComponent>(component_);
    if (tween) {
        if (tween->IsDeclarativeAnimation()) {
            return ComposedElement::BuildChild();
        }

        RefPtr<TransformComponent> transformComponent = AceType::MakeRefPtr<TransformComponent>();
        RefPtr<DisplayComponent> displayComponent = AceType::MakeRefPtr<DisplayComponent>(transformComponent);
        displayComponent->SetPositionType(positionParam_.type);
        displayComponent->SetHasLeft(positionParam_.left.second);
        displayComponent->SetHasRight(positionParam_.right.second);
        displayComponent->SetHasTop(positionParam_.top.second);
        displayComponent->SetHasBottom(positionParam_.bottom.second);
        displayComponent->SetLeft(positionParam_.left.first);
        displayComponent->SetRight(positionParam_.right.first);
        displayComponent->SetTop(positionParam_.top.first);
        displayComponent->SetBottom(positionParam_.bottom.first);
        displayComponent->DisableLayer(tween->IsLeafNode());
        transformComponent->SetChild(ComposedElement::BuildChild());
        if (!tween->GetIsFirstFrameShow()) {
            displayComponent->SetVisible(VisibleType::INVISIBLE);
        }
        return displayComponent;
    } else {
        LOGE("no tween component found. return empty child.");
        return nullptr;
    }
}

void TweenElement::PerformBuild()
{
    auto pipelineContext = context_.Upgrade();
    if (pipelineContext && !pipelineContext->GetIsDeclarative()) {
        // if tween Option or child changes, need to do PerformBuild. These changes conflict with tween operation, so if
        // there are any new operations, animate it first, just do not disturb child
        if (((operation_ != TweenOperation::NONE) || (operationCustom_ != TweenOperation::NONE)) &&
            !children_.empty()) {
            LOGI("Just update self, do not disturb children.");
            return;
        }
    }
    ComposedElement::PerformBuild();
}

void TweenElement::CreateTranslateAnimation(const RefPtr<RenderTransform>& renderTransformNode, TweenOption& option)
{
    if (!option.HasTransformOffsetChanged()) {
        LOGD("create translate animation with null. skip it.");
        return;
    }
    auto& transformOffsetAnimations = option.GetTranslateAnimations();
    WeakPtr<RenderTransform> weakRender = renderTransformNode;
    static const LinearEnumMapNode<AnimationType,
        void (*)(const RefPtr<Animation<DimensionOffset>>&, WeakPtr<RenderTransform>&, TweenOption&)>
        translateAnimationAddMap[] = {
            { AnimationType::TRANSLATE,
                [](const RefPtr<Animation<DimensionOffset>>& translateAnimation,
                    WeakPtr<RenderTransform>& weakRender, TweenOption& option) {
                    SetTranslateProperties(translateAnimation, option);
                    translateAnimation->AddListener([weakRender, translateAnimation](
                                                        const DimensionOffset& value) {
                        auto renderTransformNode = weakRender.Upgrade();
                        if (renderTransformNode) {
                            if (translateAnimation->ShouldSkipAnimation()) {
                                auto endValue = translateAnimation->GetEndValue();
                                renderTransformNode->Translate(
                                    endValue.GetX(), endValue.GetY());
                            } else {
                                renderTransformNode->Translate(value.GetX(), value.GetY());
                            }
                        }
                    });
                } },
            { AnimationType::TRANSLATE_X,
                [](const RefPtr<Animation<DimensionOffset>>& translateXAnimation, WeakPtr<RenderTransform>& weakRender,
                    TweenOption& option) {
                    SetTranslateProperties(translateXAnimation, option);
                    translateXAnimation->AddListener([weakRender, translateXAnimation](const DimensionOffset& value) {
                        auto renderTransformNode = weakRender.Upgrade();
                        if (renderTransformNode) {
                            if (translateXAnimation->ShouldSkipAnimation()) {
                                auto endValue = translateXAnimation->GetEndValue();
                                renderTransformNode->Translate(endValue.GetX(), 0.0_px);
                            } else {
                                renderTransformNode->Translate(value.GetX(), 0.0_px);
                            }
                        }
                    });
                } },
            { AnimationType::TRANSLATE_Y,
                [](const RefPtr<Animation<DimensionOffset>>& translateYAnimation, WeakPtr<RenderTransform>& weakRender,
                    TweenOption& option) {
                    SetTranslateProperties(translateYAnimation, option);
                    translateYAnimation->AddListener([weakRender, translateYAnimation](const DimensionOffset& value) {
                        auto renderTransformNode = weakRender.Upgrade();
                        if (renderTransformNode) {
                            if (translateYAnimation->ShouldSkipAnimation()) {
                                auto endValue = translateYAnimation->GetEndValue();
                                renderTransformNode->Translate(0.0_px, endValue.GetY());
                            } else {
                                renderTransformNode->Translate(0.0_px, value.GetY());
                            }
                        }
                    });
                } }
            };
    size_t mapSize = ArraySize(translateAnimationAddMap);
    auto iterTranslateAnimation = transformOffsetAnimations.find(AnimationType::TRANSLATE);
    if (iterTranslateAnimation != transformOffsetAnimations.end()) {
        auto translateAnimationIter =
            BinarySearchFindIndex(translateAnimationAddMap, mapSize, AnimationType::TRANSLATE);
        if (translateAnimationIter != -1) {
            auto& translateAnimation = iterTranslateAnimation->second;
            if (!translateAnimation->ShouldSkipAnimation()) {
                if (translateAnimation->IsDeclarativeAnimation()) {
                    translateAnimation->SetStart(
                        DimensionOffset(renderTransformNode->GetTranslateX(), renderTransformNode->GetTranslateY()));
                }
                translateAnimationAddMap[translateAnimationIter].value(translateAnimation, weakRender, option);
            } else {
                translateAnimation->SetStart(translateAnimation->GetEndValue());
                translateAnimationAddMap[translateAnimationIter].value(translateAnimation, weakRender, option);
                auto endValue = translateAnimation->GetEndValue();
                renderTransformNode->Translate(endValue.GetX(), endValue.GetY());
            }
        }
    }

    auto iterTranslateXAnimation = transformOffsetAnimations.find(AnimationType::TRANSLATE_X);
    if (iterTranslateXAnimation != transformOffsetAnimations.end()) {
        auto translateXAnimationIter =
            BinarySearchFindIndex(translateAnimationAddMap, mapSize, AnimationType::TRANSLATE_X);
        if (translateXAnimationIter != -1) {
            auto& translateXAnimation = iterTranslateXAnimation->second;
            if (!translateXAnimation->ShouldSkipAnimation()) {
                if (translateXAnimation->IsDeclarativeAnimation()) {
                    translateXAnimation->SetStart(DimensionOffset(renderTransformNode->GetTranslateX(), Dimension()));
                }
                translateAnimationAddMap[translateXAnimationIter].value(translateXAnimation, weakRender, option);
            } else {
                translateXAnimation->SetStart(translateXAnimation->GetEndValue());
                translateAnimationAddMap[translateXAnimationIter].value(translateXAnimation, weakRender, option);
                auto endValue = translateXAnimation->GetEndValue();
                renderTransformNode->Translate(endValue.GetX(), 0.0_px);
            }
        }
    }

    auto iterTranslateYAnimation = transformOffsetAnimations.find(AnimationType::TRANSLATE_Y);
    if (iterTranslateYAnimation != transformOffsetAnimations.end()) {
        auto translateYAnimationIter =
            BinarySearchFindIndex(translateAnimationAddMap, mapSize, AnimationType::TRANSLATE_Y);
        if (translateYAnimationIter != -1) {
            auto& translateYAnimation = iterTranslateYAnimation->second;
            if (!translateYAnimation->ShouldSkipAnimation()) {
                if (translateYAnimation->IsDeclarativeAnimation()) {
                    translateYAnimation->SetStart(DimensionOffset(Dimension(), renderTransformNode->GetTranslateY()));
                }
                translateAnimationAddMap[translateYAnimationIter].value(translateYAnimation, weakRender, option);
            } else {
                translateYAnimation->SetStart(translateYAnimation->GetEndValue());
                translateAnimationAddMap[translateYAnimationIter].value(translateYAnimation, weakRender, option);
                auto endValue = translateYAnimation->GetEndValue();
                renderTransformNode->Translate(0.0_px, endValue.GetY());
            }
        }
    }
}

void TweenElement::CreateScaleAnimation(const RefPtr<RenderTransform>& renderTransformNode, TweenOption& option)
{
    if (!option.HasTransformFloatChanged()) {
        LOGD("create scale animation with null. skip it.");
        return;
    }
    auto& transformFloatAnimations = option.GetTransformFloatAnimation();
    WeakPtr<RenderTransform> weakRender = renderTransformNode;
    auto iterScaleAnimation = transformFloatAnimations.find(AnimationType::SCALE);
    size_t mapSize = ArraySize(transformFloatAnimationAddMap_);
    if (iterScaleAnimation != transformFloatAnimations.end()) {
        auto scaleAnimationIter = BinarySearchFindIndex(transformFloatAnimationAddMap_, mapSize, AnimationType::SCALE);
        if (scaleAnimationIter != -1) {
            auto& scaleAnimation = iterScaleAnimation->second;
            if (!scaleAnimation->ShouldSkipAnimation()) {
                if (scaleAnimation->IsDeclarativeAnimation()) {
                    scaleAnimation->SetStart(renderTransformNode->GetScaleX());
                }
                transformFloatAnimationAddMap_[scaleAnimationIter].value(scaleAnimation, weakRender, option);
            } else {
                scaleAnimation->SetStart(scaleAnimation->GetEndValue());
                transformFloatAnimationAddMap_[scaleAnimationIter].value(scaleAnimation, weakRender, option);
                renderTransformNode->Scale(scaleAnimation->GetEndValue());
            }
        }
    }

    auto iterScaleXAnimation = transformFloatAnimations.find(AnimationType::SCALE_X);
    if (iterScaleXAnimation != transformFloatAnimations.end()) {
        auto scaleXAnimationIter =
            BinarySearchFindIndex(transformFloatAnimationAddMap_, mapSize, AnimationType::SCALE_X);
        if (scaleXAnimationIter != -1) {
            auto& scaleXAnimation = iterScaleXAnimation->second;
            if (!scaleXAnimation->ShouldSkipAnimation()) {
                if (scaleXAnimation->IsDeclarativeAnimation()) {
                    scaleXAnimation->SetStart(renderTransformNode->GetScaleX());
                }
                transformFloatAnimationAddMap_[scaleXAnimationIter].value(scaleXAnimation, weakRender, option);
            } else {
                scaleXAnimation->SetStart(scaleXAnimation->GetEndValue());
                transformFloatAnimationAddMap_[scaleXAnimationIter].value(scaleXAnimation, weakRender, option);
                renderTransformNode->Scale(scaleXAnimation->GetEndValue(), 1.0f);
            }
        }
    }

    auto iterScaleYAnimation = transformFloatAnimations.find(AnimationType::SCALE_Y);
    if (iterScaleYAnimation != transformFloatAnimations.end()) {
        auto scaleYAnimationIter =
            BinarySearchFindIndex(transformFloatAnimationAddMap_, mapSize, AnimationType::SCALE_Y);
        if (scaleYAnimationIter != -1) {
            auto& scaleYAnimation = iterScaleYAnimation->second;
            if (!scaleYAnimation->ShouldSkipAnimation()) {
                if (scaleYAnimation->IsDeclarativeAnimation()) {
                    scaleYAnimation->SetStart(renderTransformNode->GetScaleY());
                }
                transformFloatAnimationAddMap_[scaleYAnimationIter].value(scaleYAnimation, weakRender, option);
            } else {
                scaleYAnimation->SetStart(scaleYAnimation->GetEndValue());
                transformFloatAnimationAddMap_[scaleYAnimationIter].value(scaleYAnimation, weakRender, option);
                renderTransformNode->Scale(1.0f, scaleYAnimation->GetEndValue());
            }
        }
    }
}

void TweenElement::CreateTransformOriginAnimation(
    const RefPtr<RenderTransform>& renderTransformNode, TweenOption& option)
{
    if (option.HasTransformOriginChanged()) {
        renderTransformNode->SetTransformOrigin(option.GetTransformOriginX(), option.GetTransformOriginY());
        option.SetTransformOriginChanged(false);
    } else {
        renderTransformNode->SetTransformOrigin(HALF_PERCENT, HALF_PERCENT);
    }
    renderTransformNode->MarkNeedUpdateOrigin();
}

void TweenElement::CreateRotateAnimation(const RefPtr<RenderTransform>& renderTransformNode, TweenOption& option)
{
    if (!option.HasTransformFloatChanged()) {
        LOGD("create rotate animation with null. skip it.");
        return;
    }
    auto& transformFloatAnimations = option.GetTransformFloatAnimation();
    WeakPtr<RenderTransform> weakRender = renderTransformNode;
    auto iterRotateZAnimation = transformFloatAnimations.find(AnimationType::ROTATE_Z);
    size_t mapSize = ArraySize(transformFloatAnimationAddMap_);
    if (iterRotateZAnimation != transformFloatAnimations.end()) {
        auto rotateZAnimationIter =
            BinarySearchFindIndex(transformFloatAnimationAddMap_, mapSize, AnimationType::ROTATE_Z);
        if (rotateZAnimationIter != -1) {
            auto& rotateZAnimation = iterRotateZAnimation->second;
            transformFloatAnimationAddMap_[rotateZAnimationIter].value(rotateZAnimation, weakRender, option);
            if (!rotateZAnimation->ShouldSkipAnimation()) {
                if (rotateZAnimation->IsDeclarativeAnimation()) {
                    rotateZAnimation->SetStart(renderTransformNode->GetRotateZ());
                }
                transformFloatAnimationAddMap_[rotateZAnimationIter].value(rotateZAnimation, weakRender, option);
            } else {
                rotateZAnimation->SetStart(rotateZAnimation->GetEndValue());
                transformFloatAnimationAddMap_[rotateZAnimationIter].value(rotateZAnimation, weakRender, option);
                renderTransformNode->RotateZ(rotateZAnimation->GetEndValue());
            }
        }
    }

    auto iterRotateXAnimation = transformFloatAnimations.find(AnimationType::ROTATE_X);
    if (iterRotateXAnimation != transformFloatAnimations.end()) {
        auto rotateXAnimationIter =
            BinarySearchFindIndex(transformFloatAnimationAddMap_, mapSize, AnimationType::ROTATE_X);
        if (rotateXAnimationIter != -1) {
            auto& rotateXAnimation = iterRotateXAnimation->second;
            if (!rotateXAnimation->ShouldSkipAnimation()) {
                if (rotateXAnimation->IsDeclarativeAnimation()) {
                    rotateXAnimation->SetStart(renderTransformNode->GetRotateX());
                }
                transformFloatAnimationAddMap_[rotateXAnimationIter].value(rotateXAnimation, weakRender, option);
            } else {
                rotateXAnimation->SetStart(rotateXAnimation->GetEndValue());
                transformFloatAnimationAddMap_[rotateXAnimationIter].value(rotateXAnimation, weakRender, option);
                renderTransformNode->RotateX(rotateXAnimation->GetEndValue());
            }
        }
    }

    auto iterRotateYAnimation = transformFloatAnimations.find(AnimationType::ROTATE_Y);
    if (iterRotateYAnimation != transformFloatAnimations.end()) {
        auto rotateYAnimationIter =
            BinarySearchFindIndex(transformFloatAnimationAddMap_, mapSize, AnimationType::ROTATE_Y);
        if (rotateYAnimationIter != -1) {
            auto& rotateYAnimation = iterRotateYAnimation->second;
            if (!rotateYAnimation->ShouldSkipAnimation()) {
                if (rotateYAnimation->IsDeclarativeAnimation()) {
                    rotateYAnimation->SetStart(renderTransformNode->GetRotateY());
                }
                transformFloatAnimationAddMap_[rotateYAnimationIter].value(rotateYAnimation, weakRender, option);
            } else {
                rotateYAnimation->SetStart(rotateYAnimation->GetEndValue());
                transformFloatAnimationAddMap_[rotateYAnimationIter].value(rotateYAnimation, weakRender, option);
                renderTransformNode->RotateY(rotateYAnimation->GetEndValue());
            }
        }
    }
}

void TweenElement::CreateOpacityAnimation(const RefPtr<RenderDisplay>& renderDisplayNode, TweenOption& option)
{
    auto& opacityAnimation = option.GetOpacityAnimation();
    if (!opacityAnimation) {
        LOGD("create opacity animation with null. skip it.");
        return;
    }
    if (!opacityAnimation->HasInitValue()) {
        opacityAnimation->SetInitValue(UINT8_MAX);
    }

    if (!opacityAnimation->ShouldSkipAnimation()) {
        if (opacityAnimation->IsDeclarativeAnimation()) {
            opacityAnimation->SetStart(renderDisplayNode->GetOpacity() / (float)UINT8_MAX);
        }

        WeakPtr<RenderDisplay> weakRender = renderDisplayNode;
        opacityAnimation->AddListener([weakRender, opacityAnimation](float value) {
            auto opacity = static_cast<uint8_t>(std::round(value * UINT8_MAX));
            if (value < 0.0f || value > 1.0f) {
                opacity = UINT8_MAX;
            }
            auto renderDisplayNode = weakRender.Upgrade();
            if (renderDisplayNode) {
                renderDisplayNode->UpdateOpacity(opacity);
            }
        });

        if (option.GetCurve()) {
            opacityAnimation->SetCurve(option.GetCurve());
        }
    } else {
        auto endValue = opacityAnimation->GetEndValue();
        auto opacity = static_cast<uint8_t>(std::round(endValue * UINT8_MAX));
        if (endValue < 0.0f || endValue > 1.0f) {
            opacity = UINT8_MAX;
        }
        renderDisplayNode->UpdateOpacity(opacity);
    }
}

void TweenElement::CreateColorAnimation(const RefPtr<PropertyAnimatable>& animatable, TweenOption& option)
{
    if (!animatable) {
        LOGE("create color animation failed. not a animatable child.");
        return;
    }
    auto& colorAnimation = option.GetColorAnimation();
    if (!colorAnimation) {
        LOGD("create color animation with null. skip it.");
        return;
    }
    PropertyAnimatableType propertyType;
    if (option.GetIsBackground()) {
        propertyType = PropertyAnimatableType::PROPERTY_BACK_DECORATION_COLOR;
    } else {
        propertyType = PropertyAnimatableType::PROPERTY_FRONT_DECORATION_COLOR;
    }
    CreatePropertyAnimation<ColorPropertyAnimatable, Color>(animatable, propertyType, option, colorAnimation);
}

template<class U, class V>
bool TweenElement::CreatePropertyAnimation(const RefPtr<PropertyAnimatable>& propertyAnimatable,
    PropertyAnimatableType propertyType, const TweenOption& option, RefPtr<Animation<V>>& animation)
{
    if (animation && !animation->ShouldSkipAnimation()) {
        typename U::Type initValue;
        bool created =
            PropertyAnimatable::AddPropertyAnimation<U, V>(propertyAnimatable, propertyType, animation, initValue);
        if (!created) {
            LOGE("create property animation failed. property: %{public}d", propertyType);
            return false;
        }
        if (option.GetCurve()) {
            animation->SetCurve(option.GetCurve());
        }
        if (!animation->HasInitValue()) {
            animation->SetInitValue(initValue);
        }
    } else {
        bool propertySet = PropertyAnimatable::SetProperty<U, V>(propertyAnimatable, propertyType, animation);
        if (!propertySet) {
            LOGE("Cannot set property. property: %{public}d", propertyType);
            return false;
        }
    }
    return true;
}

template<class U>
bool TweenElement::AddToAnimator(
    const std::map<PropertyAnimatableType, U>& animations, RefPtr<Animator>& controller, TweenOption& option)
{
    bool needAnimation = false;
    for (auto&& [property, animation] : animations) {
        if (animation) {
            needAnimation = true;
            LOGD("add property animation. property: %{public}d", property);
            controller->AddInterpolator(animation);
        }
    }
    return needAnimation;
}

void TweenElement::CreateBackgroundPositionAnimation(const RefPtr<PropertyAnimatable>& animatable, TweenOption& option)
{
    if (!animatable) {
        LOGE("create background position animation failed. not a animatable child.");
        return;
    }
    auto& backgroundPositionAnimation = option.GetBackgroundPositionAnimation();
    if (!backgroundPositionAnimation) {
        LOGD("create background position animation with null. skip it.");
        return;
    }

    CreatePropertyAnimation<BackgroundPositionPropertyAnimatable, BackgroundImagePosition>(
        animatable, PropertyAnimatableType::PROPERTY_BACKGROUND_POSITION, option, backgroundPositionAnimation);
}

void TweenElement::SetController(const RefPtr<Animator>& controller)
{
    if (!controller) {
        LOGE("set controller failed. controller is empty.");
        return;
    }
    LOGD("set controller");
    if (!controller_->IsStopped()) {
        controller_->Stop();
    }
    isDelegatedController_ = true;
    controller_ = controller;
}

const TweenOption& TweenElement::GetOption() const
{
    return option_;
}

void TweenElement::SetOption(const TweenOption& option)
{
    LOGD("set tween option");
    option_ = option;
}

const RefPtr<Animator>& TweenElement::GetController() const
{
    return controller_;
}

void TweenElement::SetOpacity(uint8_t opacity)
{
    if (children_.empty()) {
        LOGE("no child when set Opacity");
        return;
    }
    const auto& child = children_.front();
    if (!child) {
        LOGE("child is null.");
        return;
    }
    auto childElement = AceType::DynamicCast<RenderElement>(child);
    if (!childElement) {
        LOGE("child element is null.");
        return;
    }
    const auto& displayRenderNode = AceType::DynamicCast<RenderDisplay>(childElement->GetRenderNode());
    if (!displayRenderNode) {
        LOGE("no display render node found.");
        return;
    }
    LOGD("set Opacity. Opacity: %{public}d", opacity);
    displayRenderNode->UpdateOpacity(opacity);
}

void TweenElement::SetVisible(VisibleType visible)
{
    if (children_.empty()) {
        LOGE("no child when set visible");
        return;
    }
    const auto& child = children_.front();
    if (!child) {
        LOGE("child is null.");
        return;
    }
    auto childElement = AceType::DynamicCast<RenderElement>(child);
    if (!childElement) {
        LOGE("child element is null.");
        return;
    }
    const auto& displayRenderNode = AceType::DynamicCast<RenderDisplay>(childElement->GetRenderNode());
    if (!displayRenderNode) {
        LOGE("no display render node found.");
        return;
    }
    LOGD("set visible. visible: %{public}d", visible);
    displayRenderNode->UpdateVisibleType(visible);
}

void TweenElement::SetTouchable(bool enable)
{
    LOGD("set tween touchable status: %{public}d", enable);

    if (children_.empty()) {
        LOGW("get content child failed. no child yet.");
        return;
    }
    const auto& child = children_.front();
    if (!child || child->GetType() != RENDER_ELEMENT) {
        LOGW("get content child failed. null child or not render child.");
        return;
    }
    const auto& transformElement = AceType::DynamicCast<RenderElement>(child)->GetFirstChild();
    if (!transformElement) {
        LOGE("Get RenderElement failed.");
        return;
    }
    const auto& transformRenderNode = AceType::DynamicCast<RenderTransform>(transformElement->GetRenderNode());
    if (transformRenderNode) {
        transformRenderNode->SetTouchable(enable);
    }
}

RefPtr<RenderNode> TweenElement::GetContentRender() const
{
    auto contentElement = GetContentElement();
    if (!contentElement) {
        return nullptr;
    }
    return contentElement->GetRenderNode();
}

bool TweenElement::ApplyKeyframes()
{
    return ApplyKeyframes(controller_, option_, prepareId_);
}

void TweenElement::AddPrepareListener(
    RefPtr<Animator>& controller, const WeakPtr<RenderTransform>& weakTransform, BaseId::IdType& prepareId)
{
    if (!controller) {
        LOGE("Add Prepare Listener failed. controller is null.");
        return;
    }
    controller->RemovePrepareListener(prepareId);
    prepareId =
        controller->AddPrepareListener([weakTransform, weakContext = context_,
                                           weakTween = AceType::WeakClaim(this)]() {
            // reset transform matrix at the start of every frame.
            auto context = weakContext.Upgrade();
            auto tween = weakTween.Upgrade();
            auto transform = weakTransform.Upgrade();
            if (context && tween && transform) {
                auto currentTimestamp = context->GetTimeFromExternalTimer();
                if (tween->currentTimestamp_ != currentTimestamp || tween->currentTimestamp_ == 0) {
                    if (!context->GetIsDeclarative() || tween->GetOption().IsValid()) {
                        transform->ResetTransform();
                    }
                    tween->currentTimestamp_ = currentTimestamp;
                }
            }
        });
}

bool TweenElement::ApplyKeyframes(RefPtr<Animator>& controller, TweenOption& option, BaseId::IdType& prepareId)
{
    if (!controller) {
        LOGW("controller is null.");
        return false;
    }
    if (children_.empty()) {
        LOGW("apply option failed. no child yet.");
        return false;
    }
    const auto& child = children_.front();
    if (!child || child->GetType() != RENDER_ELEMENT) {
        LOGW("apply option failed. null child or not render child.");
        return false;
    }
    LOGD("TweenElement: ApplyKeyframes.");

    auto pipelineContext = context_.Upgrade();
    if (pipelineContext && pipelineContext->GetIsDeclarative()) {
        if (shouldSkipAnimationOnCreation) {
            option.SkipAllPendingAnimation();
            shouldSkipAnimationOnCreation = false;
        }
    }

    const auto& displayRenderNode =
        AceType::DynamicCast<RenderDisplay>(AceType::DynamicCast<RenderElement>(child)->GetRenderNode());
    if (!displayRenderNode) {
        LOGE("display render node is null.");
        return false;
    }
    const auto& transformElement = AceType::DynamicCast<RenderElement>(child)->GetFirstChild();
    if (!transformElement) {
        LOGE("transform element node is null.");
        return false;
    }
    const auto& transformRenderNode = AceType::DynamicCast<RenderTransform>(transformElement->GetRenderNode());
    if (!transformRenderNode) {
        LOGE("transform render node is null.");
        return false;
    }
    if (shadow_.IsValid()) {
        displayRenderNode->SetShadow(shadow_);
        transformRenderNode->SetShadow(shadow_);
    }

    if (pipelineContext && pipelineContext->GetIsDeclarative()) {
        displayRenderNode->SetDeclarativeAnimationActive(true);
        transformRenderNode->SetDeclarativeAnimationActive(true);
    }

    const auto& contentElement = AceType::DynamicCast<RenderElement>(transformElement)->GetFirstChild();
    auto animatable = GetAnimatable(contentElement);
    if (animatable) {
        if (pipelineContext && pipelineContext->GetIsDeclarative()) {
            contentElement->GetRenderNode()->SetDeclarativeAnimationActive(true);
        }
        CreateColorAnimation(animatable, option);
        CreateBackgroundPositionAnimation(animatable, option);
        CreatePropertyAnimationFloat(animatable, option);
    }
    CreateTranslateAnimation(transformRenderNode, option);
    CreateScaleAnimation(transformRenderNode, option);
    CreateRotateAnimation(transformRenderNode, option);
    CreateTransformOriginAnimation(transformRenderNode, option);
    if (option.HasTransformOffsetChanged() || option.HasTransformFloatChanged()) {
        AddPrepareListener(controller, transformRenderNode, prepareId);
    }
    CreateOpacityAnimation(displayRenderNode, option);
    return IsNeedAnimation(controller, option);
}

void TweenElement::ApplyOptions(RefPtr<Animator>& controller, TweenOption& option)
{
    if (!controller) {
        LOGE("Apply Options failed. Controller is null.");
        return;
    }
    LOGD("apply options.");
    controller->SetDuration(option.GetDuration());
    controller->SetIteration(option.GetIteration());
    controller->SetStartDelay(option.GetDelay());
    controller->SetFillMode(option.GetFillMode());
    controller->SetAnimationDirection(option.GetAnimationDirection());
}

void TweenElement::ApplyOptions()
{
    ApplyOptions(controller_, option_);
}

RefPtr<Element> TweenElement::GetContentElement() const
{
    const auto& mountParent = GetContentParent();
    if (!mountParent) {
        LOGE("Get content element failed. content parent is null.");
        return nullptr;
    }
    return mountParent->GetFirstChild();
}

RefPtr<Element> TweenElement::GetContentParent() const
{
    const auto child = GetFirstChild();
    if (!child) {
        LOGW("Get transformElement failed. null child.");
        return nullptr;
    }
    const auto& displayRenderNode =
        AceType::DynamicCast<RenderDisplay>(AceType::DynamicCast<RenderElement>(child)->GetRenderNode());
    if (!displayRenderNode) {
        LOGE("display render node is null.");
        return nullptr;
    }
    const auto& transformElement = AceType::DynamicCast<RenderElement>(child)->GetFirstChild();
    if (!transformElement) {
        LOGE("Get transformElement failed. transform element is null");
        return nullptr;
    }
    const auto& transformRenderNode = AceType::DynamicCast<RenderTransform>(transformElement->GetRenderNode());
    if (!transformRenderNode) {
        LOGE("Get transformElement failed. transform render node is null.");
        return nullptr;
    }
    return transformElement;
}

void TweenElement::CreatePropertyAnimationFloat(const RefPtr<PropertyAnimatable>& animatable, TweenOption& option)
{
    if (!animatable) {
        LOGE("Create property animation for float failed. animatable is null.");
        return;
    }
    auto& propertyFloatMap = option.GetFloatPropertyAnimation();
    if (propertyFloatMap.empty()) {
        LOGD("No property animation float found. skip it.");
        return;
    }
    for (auto&& [property, animation] : propertyFloatMap) {
        LOGD("Create animation float for property: %{public}d", property);
        CreatePropertyAnimation<FloatPropertyAnimatable, float>(animatable, property, option, animation);
    }
}

} // namespace OHOS::Ace
