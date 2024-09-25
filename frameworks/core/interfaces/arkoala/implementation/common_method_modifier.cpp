/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <variant>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG {
using ColorOrStrategy = std::variant<std::monostate, std::optional<Color>, std::optional<ForegroundColorStrategy>>;

namespace Converter {
template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Color& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Resource& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_String& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Number& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_ColoringStrategy& src)
{
    dst = OptConvert<ForegroundColorStrategy>(src);
}
}
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr int32_t CASE_0 = 0;
constexpr int32_t CASE_1 = 1;
constexpr int32_t CASE_2 = 2;

namespace CommonMethodModifier {
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::ConvertOrDefault(*value, CalcLength());
    ViewAbstract::SetWidth(frameNode, result);
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::ConvertOrDefault(*value, CalcLength());
    ViewAbstract::SetHeight(frameNode, result);
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Type_CommonMethod_drawModifier_Arg0* modifier)
{
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Ark_String* name,
                        const Opt_Object* value)
{
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Type_CommonMethod_responseRegion_Arg0* value)
{
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Type_CommonMethod_mouseResponseRegion_Arg0* value)
{
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<CalcLength>(value->width);
    if (width) {
        ViewAbstract::SetWidth(frameNode, width.value());
    }
    auto height = Converter::OptConvert<CalcLength>(value->height);
    if (height) {
        ViewAbstract::SetHeight(frameNode, height.value());
    }
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto minWidth = Converter::OptConvert<CalcLength>(value->minWidth);
    if (minWidth) {
        ViewAbstract::SetMinWidth(frameNode, minWidth.value());
    }
    auto minHeight = Converter::OptConvert<CalcLength>(value->minHeight);
    if (minHeight) {
        ViewAbstract::SetMinHeight(frameNode, minHeight.value());
    }
    auto maxWidth = Converter::OptConvert<CalcLength>(value->maxWidth);
    if (maxWidth) {
        ViewAbstract::SetMaxWidth(frameNode, maxWidth.value());
    }
    auto maxHeight = Converter::OptConvert<CalcLength>(value->maxHeight);
    if (maxHeight) {
        ViewAbstract::SetMaxHeight(frameNode, maxHeight.value());
    }
}
void TouchableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTouchable(frameNode, static_cast<bool>(value));
}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         enum Ark_HitTestMode value)
{
}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          Ark_Function event)
{
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Type_CommonMethod_layoutWeight_Arg0* value)
{
}
void PaddingImpl(Ark_NativePointer node,
                 const Type_CommonMethod_padding_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PaddingProperty indents;
    switch (value->selector) {
        case CASE_0:
            indents.left = Converter::OptConvert<CalcLength>(value->value0.left);
            indents.top = Converter::OptConvert<CalcLength>(value->value0.top);
            indents.right = Converter::OptConvert<CalcLength>(value->value0.right);
            indents.bottom = Converter::OptConvert<CalcLength>(value->value0.bottom);
            break;
        case CASE_1:
            indents = Converter::OptConvert<PaddingProperty>(value->value1).value();
            break;
        case CASE_2:
            indents = Converter::Convert<PaddingProperty>(value->value2);
            break;
        default:
            LOGE("ARKOALA: CommonMethod::PaddingImpl: Unexpected selector: %{public}d\n", value->selector);
            return;
    }
    ViewAbstract::SetPadding(frameNode, indents);
}
void MarginImpl(Ark_NativePointer node,
                const Type_CommonMethod_margin_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PaddingProperty indents;
    switch (value->selector) {
        case CASE_0:
            indents.left = Converter::OptConvert<CalcLength>(value->value0.left);
            indents.top = Converter::OptConvert<CalcLength>(value->value0.top);
            indents.right = Converter::OptConvert<CalcLength>(value->value0.right);
            indents.bottom = Converter::OptConvert<CalcLength>(value->value0.bottom);
            break;
        case CASE_1:
            indents = Converter::OptConvert<PaddingProperty>(value->value1).value();
            break;
        case CASE_2:
            indents = Converter::OptConvert<PaddingProperty>(value->value2).value();
            break;
        default:
            LOGE("ARKOALA: CommonMethod::MarginImpl: Unexpected selector: %{public}d\n", value->selector);
            return;
    }
    ViewAbstract::SetMargin(frameNode, indents);
}
void BackgroundImpl(Ark_NativePointer node,
                    const CustomBuilder* builder,
                    const Opt_Type_CommonMethod_background_Arg1* options)
{
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        ViewAbstract::SetBackgroundColor(frameNode, color.value());
    } else {
        LOGI("#### CommonMethod::BackgroundColorImpl: color is empty");
    }
}
void PixelRoundImpl(Ark_NativePointer node,
                    const Ark_PixelRoundPolicy* value)
{
}
void BackgroundImageImpl(Ark_NativePointer node,
                         const Type_CommonMethod_backgroundImage_Arg0* src,
                         const Opt_ImageRepeat* repeat)
{
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Type_CommonMethod_backgroundImageSize_Arg0* value)
{
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Type_CommonMethod_backgroundImagePosition_Arg0* value)
{
}
void BackgroundBlurStyleImpl(Ark_NativePointer node,
                             enum Ark_BlurStyle value,
                             const Opt_BackgroundBlurStyleOptions* options)
{
}
void BackgroundEffectImpl(Ark_NativePointer node,
                          const Ark_BackgroundEffectOptions* options)
{
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Ark_ResizableOptions* value)
{
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Ark_ForegroundEffectOptions* options)
{
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Ark_CustomObject* effect)
{
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* filter)
{
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* filter)
{
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Ark_CustomObject* filter)
{
}
void ForegroundBlurStyleImpl(Ark_NativePointer node,
                             enum Ark_BlurStyle value,
                             const Opt_ForegroundBlurStyleOptions* options)
{
}
void OpacityImpl(Ark_NativePointer node,
                 const Type_CommonMethod_opacity_Arg0* value)
{
}
void BorderImpl(Ark_NativePointer node,
                const Ark_BorderOptions* value)
{
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Type_CommonMethod_borderStyle_Arg0* value)
{
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Type_CommonMethod_borderWidth_Arg0* value)
{
}
void BorderColorImpl(Ark_NativePointer node,
                     const Type_CommonMethod_borderColor_Arg0* value)
{
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Type_CommonMethod_borderRadius_Arg0* value)
{
}
void BorderImageImpl(Ark_NativePointer node,
                     const Ark_BorderImageOption* value)
{
}
void OutlineImpl(Ark_NativePointer node,
                 const Ark_OutlineOptions* value)
{
}
void OutlineStyleImpl(Ark_NativePointer node,
                      const Type_CommonMethod_outlineStyle_Arg0* value)
{
}
void OutlineWidthImpl(Ark_NativePointer node,
                      const Type_CommonMethod_outlineWidth_Arg0* value)
{
}
void OutlineColorImpl(Ark_NativePointer node,
                      const Type_CommonMethod_outlineColor_Arg0* value)
{
}
void OutlineRadiusImpl(Ark_NativePointer node,
                       const Type_CommonMethod_outlineRadius_Arg0* value)
{
}

void ForegroundColorImpl(Ark_NativePointer node,
                         const Type_CommonMethod_foregroundColor_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    auto var = Converter::OptConvert<ColorOrStrategy>(*value);
    if (var && var->index() == 1) {
        const auto& color = std::get<1>(*var);
        if (color) {
            ViewAbstract::SetForegroundColor(frameNode, color.value());
        } else {
            LOGI("#### CommonMethod::ForegroundColorImpl: color is empty");
        }
    } else {
        LOGE("#### CommonMethod::ForegroundColorImpl: strategy handling is not implemented!");
    }
}

void OnClick0Impl(Ark_NativePointer node,
                  Ark_Function event)
{
}
void OnClick1Impl(Ark_NativePointer node,
                  Ark_Function event,
                  const Ark_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](GestureEvent& info) {
        Ark_ClickEvent onClick;

        Offset globalOffset = info.GetGlobalLocation();
        Offset localOffset = info.GetLocalLocation();
        Offset screenOffset = info.GetScreenLocation();

        onClick.axisHorizontal.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onClick.axisVertical.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onClick.displayX = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));
        onClick.displayY = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

        onClick.pressure = Converter::ArkValue<Ark_Number>(0.0f);
        onClick.preventDefault.id = 0;

        onClick.screenX = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
        onClick.screenY = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

        onClick.source = static_cast<Ark_SourceType>(info.GetSourceDevice());

        onClick.sourceTool = static_cast<Ark_SourceTool>(0);
        onClick.deviceId = Converter::ArkValue<Opt_Number>();
        onClick.target.area.globalPosition.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onClick.target.area.globalPosition.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onClick.target.area.height.type = 0;
        onClick.target.area.height.unit = 1;
        onClick.target.area.height.value = 0;
        onClick.target.area.width.type = 0;
        onClick.target.area.width.unit = 1;
        onClick.target.area.width.value = 0;
        onClick.target.area.position.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onClick.target.area.position.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;

        onClick.tiltX = Converter::ArkValue<Ark_Number>(0);
        onClick.tiltY = Converter::ArkValue<Ark_Number>(0);

        onClick.timestamp = Converter::ArkValue<Ark_Number>(
            static_cast<float>(info.GetTimeStamp().time_since_epoch().count()));

        onClick.windowX = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));
        onClick.windowY = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

        onClick.x = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));
        onClick.y = Converter::ArkValue<Ark_Number>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));

        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onClick1(frameNode->GetId(), onClick);
    };

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              Ark_Function callback)
{
}
void HoverEffectImpl(Ark_NativePointer node,
                     enum Ark_HoverEffect value)
{
}
void OnMouseImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnTouchImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](TouchEventInfo& eventInfo) {
        Ark_TouchEvent onTouch;
        onTouch.axisHorizontal.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.axisVertical.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.changedTouches.array = nullptr;
        onTouch.changedTouches.length = 0;
        auto changedTouches = eventInfo.GetChangedTouches();
        if (!changedTouches.empty()) {
            std::vector<Ark_TouchObject> array;
            for (auto& info : changedTouches) {
                array.push_back(Converter::ConvertTouchInfo(info));
            }
            onTouch.changedTouches.array = &array[0];
            onTouch.changedTouches.length = changedTouches.size();
        }
        onTouch.pressure.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.pressure.f32 = 0.0f;
        onTouch.preventDefault.id = 0;
        onTouch.source = static_cast<Ark_SourceType>(eventInfo.GetSourceDevice());
        onTouch.sourceTool = static_cast<Ark_SourceTool>(0);
        onTouch.stopPropagation.id = 0;
        onTouch.target.area.globalPosition.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.globalPosition.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.height.type = 0;
        onTouch.target.area.height.unit = 1;
        onTouch.target.area.height.value = 0;
        onTouch.target.area.width.type = 0;
        onTouch.target.area.width.unit = 1;
        onTouch.target.area.width.value = 0;
        onTouch.target.area.position.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.position.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.tiltX.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.tiltX.f32 = 0;
        onTouch.tiltY.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.tiltY.f32 = 0;
        onTouch.timestamp.tag = Ark_Tag::ARK_TAG_INT32;
        onTouch.timestamp.i32 = eventInfo.GetTimeStamp().time_since_epoch().count();
        onTouch.type = static_cast<Ark_TouchType>(0);
        onTouch.touches.array = nullptr;
        onTouch.touches.length = 0;
        auto touches = eventInfo.GetTouches();
        if (!touches.empty()) {
            std::vector<Ark_TouchObject> array;
            for (auto& info : touches) {
                array.push_back(Converter::ConvertTouchInfo(info));
            }
            onTouch.touches.array = &array[0];
            onTouch.touches.length = touches.size();
        }

        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onTouch(frameNode->GetId(), onTouch);
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void OnKeyEventImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, static_cast<bool>(value));
}
void OnFocusImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onFocus(frameNode->GetId());
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void OnBlurImpl(Ark_NativePointer node,
                Ark_Function event)
{
}
void TabIndexImpl(Ark_NativePointer node,
                  const Ark_Number* index)
{
}
void DefaultFocusImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Ark_FocusBoxStyle* style)
{
}
void FocusScopeIdImpl(Ark_NativePointer node,
                      const Ark_String* id,
                      const Opt_Boolean* isGroup)
{
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Ark_String* scopeId,
                            const Opt_FocusPriority* priority)
{
}
void AnimationImpl(Ark_NativePointer node,
                   const Ark_AnimateParam* value)
{
}
void Transition0Impl(Ark_NativePointer node,
                     const Type_CommonMethod_transition_Arg0* value)
{
}
void Transition1Impl(Ark_NativePointer node,
                     const Ark_TransitionEffect* effect,
                     const Opt_Function* onFinish)
{
}
void GestureImpl(Ark_NativePointer node,
                 const Ark_GestureType* gesture,
                 const Opt_GestureMask* mask)
{
}
void PriorityGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
}
void ParallelGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
}
void BlurImpl(Ark_NativePointer node,
              const Ark_Number* value,
              const Opt_BlurOptions* options)
{
}
void LinearGradientBlurImpl(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Ark_LinearGradientBlurOptions* options)
{
}
void MotionBlurImpl(Ark_NativePointer node,
                    const Ark_MotionBlurOptions* value)
{
}
void BrightnessImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void ContrastImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void GrayscaleImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void ColorBlendImpl(Ark_NativePointer node,
                    const Type_CommonMethod_colorBlend_Arg0* value)
{
}
void SaturateImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void SepiaImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
}
void InvertImpl(Ark_NativePointer node,
                const Type_CommonMethod_invert_Arg0* value)
{
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
}
void HueRotateImpl(Ark_NativePointer node,
                   const Type_CommonMethod_hueRotate_Arg0* value)
{
}
void UseShadowBatchingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
}
void UseEffectImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void BackdropBlurImpl(Ark_NativePointer node,
                      const Ark_Number* value,
                      const Opt_BlurOptions* options)
{
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{
}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{
}
void GridSpanImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void RotateImpl(Ark_NativePointer node,
                const Ark_RotateOptions* value)
{
}
void TransformImpl(Ark_NativePointer node,
                   const Ark_CustomObject* value)
{
}
void OnAppearImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
                     Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onDisAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnDetachImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void VisibilityImpl(Ark_NativePointer node,
                    enum Ark_Visibility value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(value));
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Type_CommonMethod_flexBasis_Arg0* value)
{
}
void AlignSelfImpl(Ark_NativePointer node,
                   enum Ark_ItemAlign value)
{
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
}
void ZIndexImpl(Ark_NativePointer node,
                const Ark_Number* value)
{
}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Ark_String* id,
                          const Opt_sharedTransitionOptions* options)
{
}
void DirectionImpl(Ark_NativePointer node,
                   enum Ark_Direction value)
{
}
void AlignImpl(Ark_NativePointer node,
               enum Ark_Alignment value)
{
}
void PositionImpl(Ark_NativePointer node,
                  const Type_CommonMethod_position_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    switch (value->selector) {
        case CASE_0: {
            auto x = Converter::ConvertOrDefault(value->value0.x, Dimension());
            auto y = Converter::ConvertOrDefault(value->value0.y, Dimension());
            ViewAbstract::SetPosition(frameNode, { x, y });
            break;
        }
        case CASE_1: {
            auto result = Converter::ConvertOrDefault(value->value1, EdgesParam());
            ViewAbstract::SetPositionEdges(frameNode, result);
            break;
        }
        case CASE_2:
            LOGE("ARKOALA: LocalizedEdges is not fully support.");
            ViewAbstract::SetPositionLocalizedEdges(frameNode, true);
            break;

        default:
            LOGE("ARKOALA:PositionImpl: Unexpected value->selector: %{public}d\n", value->selector);
            return;
    }
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Type_CommonMethod_markAnchor_Arg0* value)
{
}
void OffsetImpl(Ark_NativePointer node,
                const Type_CommonMethod_offset_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    switch (value->selector) {
        case CASE_0: {
            auto x = Converter::ConvertOrDefault(value->value0.x, Dimension());
            auto y = Converter::ConvertOrDefault(value->value0.y, Dimension());
            ViewAbstract::SetOffset(frameNode, { x, y });
            break;
        }
        case CASE_1: {
            auto result = Converter::ConvertOrDefault(value->value1, EdgesParam());
            ViewAbstract::SetOffsetEdges(frameNode, result);
            break;
        }
        case CASE_2:
            LOGE("ARKOALA: LocalizedEdges is not fully support.");
            ViewAbstract::SetOffsetLocalizedEdges(frameNode, true);
            break;
        default:
            LOGE("ARKOALA:OffsetImpl: Unexpected value->selector: %{public}d\n", value->selector);
            return;
    }
}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, static_cast<bool>(value));
}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Type_CommonMethod_useSizeType_Arg0* value)
{
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* alignRule)
{
}
void ChainModeImpl(Ark_NativePointer node,
                   enum Ark_Axis direction,
                   enum Ark_ChainStyle style)
{
}
void AspectRatioImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void ClickEffectImpl(Ark_NativePointer node,
                     const Type_CommonMethod_clickEffect_Arg0* value)
{
}
void OnDragStartImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnDragEnterImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnDragMoveImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnDropImpl(Ark_NativePointer node,
                Ark_Function event)
{
}
void OnDragEndImpl(Ark_NativePointer node,
                   Ark_Function event)
{
}
void AllowDropImpl(Ark_NativePointer node,
                   const Type_CommonMethod_allowDrop_Arg0* value)
{
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void DragPreviewImpl(Ark_NativePointer node,
                     const Type_CommonMethod_dragPreview_Arg0* value)
{
}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Ark_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{
}
void OnPreDragImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
}
void OverlayImpl(Ark_NativePointer node,
                 const Type_CommonMethod_overlay_Arg0* value,
                 const Opt_OverlayOptions* options)
{
}
void LinearGradientImpl(Ark_NativePointer node,
                        const Type_CommonMethod_linearGradient_Arg0* value)
{
}
void SweepGradientImpl(Ark_NativePointer node,
                       const Type_CommonMethod_sweepGradient_Arg0* value)
{
}
void RadialGradientImpl(Ark_NativePointer node,
                        const Type_CommonMethod_radialGradient_Arg0* value)
{
}
void MotionPathImpl(Ark_NativePointer node,
                    const Ark_MotionPathOptions* value)
{
}
void ShadowImpl(Ark_NativePointer node,
                const Type_CommonMethod_shadow_Arg0* value)
{
}
void BlendModeImpl(Ark_NativePointer node,
                   enum Ark_BlendMode value,
                   const Opt_BlendApplyType* type)
{
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Type_CommonMethod_advancedBlendMode_Arg0* effect,
                           const Opt_BlendApplyType* type)
{
}
void Clip0Impl(Ark_NativePointer node,
               Ark_Boolean value)
{
}
void Clip1Impl(Ark_NativePointer node,
               const Type_CommonMethod_clip1_Arg0* value)
{
}
void ClipShapeImpl(Ark_NativePointer node,
                   const Type_CommonMethod_clipShape_Arg0* value)
{
}
void Mask0Impl(Ark_NativePointer node,
               const Ark_Materialized* value)
{
}
void Mask1Impl(Ark_NativePointer node,
               const Type_CommonMethod_mask1_Arg0* value)
{
}
void MaskShapeImpl(Ark_NativePointer node,
                   const Type_CommonMethod_maskShape_Arg0* value)
{
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* id)
{
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Ark_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
}
void BindPopupImpl(Ark_NativePointer node,
                   Ark_Boolean show,
                   const Type_CommonMethod_bindPopup_Arg1* popup)
{
}
void BindMenu0Impl(Ark_NativePointer node,
                   const Type_CommonMethod_bindMenu_Arg0* content,
                   const Opt_MenuOptions* options)
{
}
void BindMenu1Impl(Ark_NativePointer node,
                   Ark_Boolean isShow,
                   const Type_CommonMethod_bindMenu1_Arg1* content,
                   const Opt_MenuOptions* options)
{
}
void BindContextMenu0Impl(Ark_NativePointer node,
                          const CustomBuilder* content,
                          enum Ark_ResponseType responseType,
                          const Opt_ContextMenuOptions* options)
{
}
void BindContextMenu1Impl(Ark_NativePointer node,
                          Ark_Boolean isShown,
                          const CustomBuilder* content,
                          const Opt_ContextMenuOptions* options)
{
}
void BindContentCover0Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomBuilder* builder,
                           const Opt_ModalTransition* type)
{
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{
}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const CustomBuilder* builder,
                   const Opt_SheetOptions* options)
{
}
void StateStylesImpl(Ark_NativePointer node,
                     const Ark_StateStyles* value)
{
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Array_Number* ratios,
                             Ark_Function event)
{
}
void SphericalEffectImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
}
void LightUpEffectImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
}
void PixelStretchEffectImpl(Ark_NativePointer node,
                            const Ark_PixelStretchEffectOptions* options)
{
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Type_CommonMethod_keyboardShortcut_Arg0* value,
                          const Array_ModifierKey* keys,
                          const Opt_Function* action)
{
}
void AccessibilityGroupImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Ark_String* value)
{
}
void AccessibilityText1Impl(Ark_NativePointer node,
                            const Ark_Resource* text)
{
}
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Ark_String* value)
{
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Ark_String* value)
{
}
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Ark_Resource* description)
{
}
void AccessibilityLevelImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const CustomBuilder* builder)
{
}
void ObscuredImpl(Ark_NativePointer node,
                  const Array_ObscuredReasons* reasons)
{
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Ark_String* id)
{
}
void RenderFitImpl(Ark_NativePointer node,
                   enum Ark_RenderFit fitMode)
{
}
void GestureModifierImpl(Ark_NativePointer node,
                         const Ark_Materialized* modifier)
{
}
void BackgroundBrightnessImpl(Ark_NativePointer node,
                              const Ark_BackgroundBrightnessOptions* params)
{
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
}
void OnGestureRecognizerJudgeBeginImpl(Ark_NativePointer node,
                                       Ark_Function callback)
{
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             Ark_Function callback)
{
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean monopolize)
{
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          Ark_Function callback)
{
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::WidthImpl,
        CommonMethodModifier::HeightImpl,
        CommonMethodModifier::DrawModifierImpl,
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::ResponseRegionImpl,
        CommonMethodModifier::MouseResponseRegionImpl,
        CommonMethodModifier::SizeImpl,
        CommonMethodModifier::ConstraintSizeImpl,
        CommonMethodModifier::TouchableImpl,
        CommonMethodModifier::HitTestBehaviorImpl,
        CommonMethodModifier::OnChildTouchTestImpl,
        CommonMethodModifier::LayoutWeightImpl,
        CommonMethodModifier::PaddingImpl,
        CommonMethodModifier::MarginImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundColorImpl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundBlurStyleImpl,
        CommonMethodModifier::BackgroundEffectImpl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
        CommonMethodModifier::ForegroundBlurStyleImpl,
        CommonMethodModifier::OpacityImpl,
        CommonMethodModifier::BorderImpl,
        CommonMethodModifier::BorderStyleImpl,
        CommonMethodModifier::BorderWidthImpl,
        CommonMethodModifier::BorderColorImpl,
        CommonMethodModifier::BorderRadiusImpl,
        CommonMethodModifier::BorderImageImpl,
        CommonMethodModifier::OutlineImpl,
        CommonMethodModifier::OutlineStyleImpl,
        CommonMethodModifier::OutlineWidthImpl,
        CommonMethodModifier::OutlineColorImpl,
        CommonMethodModifier::OutlineRadiusImpl,
        CommonMethodModifier::ForegroundColorImpl,
        CommonMethodModifier::OnClick0Impl,
        CommonMethodModifier::OnClick1Impl,
        CommonMethodModifier::OnHoverImpl,
        CommonMethodModifier::OnAccessibilityHoverImpl,
        CommonMethodModifier::HoverEffectImpl,
        CommonMethodModifier::OnMouseImpl,
        CommonMethodModifier::OnTouchImpl,
        CommonMethodModifier::OnKeyEventImpl,
        CommonMethodModifier::OnKeyPreImeImpl,
        CommonMethodModifier::FocusableImpl,
        CommonMethodModifier::OnFocusImpl,
        CommonMethodModifier::OnBlurImpl,
        CommonMethodModifier::TabIndexImpl,
        CommonMethodModifier::DefaultFocusImpl,
        CommonMethodModifier::GroupDefaultFocusImpl,
        CommonMethodModifier::FocusOnTouchImpl,
        CommonMethodModifier::FocusBoxImpl,
        CommonMethodModifier::FocusScopeIdImpl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::AnimationImpl,
        CommonMethodModifier::Transition0Impl,
        CommonMethodModifier::Transition1Impl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::BlurImpl,
        CommonMethodModifier::LinearGradientBlurImpl,
        CommonMethodModifier::MotionBlurImpl,
        CommonMethodModifier::BrightnessImpl,
        CommonMethodModifier::ContrastImpl,
        CommonMethodModifier::GrayscaleImpl,
        CommonMethodModifier::ColorBlendImpl,
        CommonMethodModifier::SaturateImpl,
        CommonMethodModifier::SepiaImpl,
        CommonMethodModifier::InvertImpl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::HueRotateImpl,
        CommonMethodModifier::UseShadowBatchingImpl,
        CommonMethodModifier::UseEffectImpl,
        CommonMethodModifier::BackdropBlurImpl,
        CommonMethodModifier::RenderGroupImpl,
        CommonMethodModifier::FreezeImpl,
        CommonMethodModifier::TranslateImpl,
        CommonMethodModifier::ScaleImpl,
        CommonMethodModifier::GridSpanImpl,
        CommonMethodModifier::GridOffsetImpl,
        CommonMethodModifier::RotateImpl,
        CommonMethodModifier::TransformImpl,
        CommonMethodModifier::OnAppearImpl,
        CommonMethodModifier::OnDisAppearImpl,
        CommonMethodModifier::OnAttachImpl,
        CommonMethodModifier::OnDetachImpl,
        CommonMethodModifier::OnAreaChangeImpl,
        CommonMethodModifier::VisibilityImpl,
        CommonMethodModifier::FlexGrowImpl,
        CommonMethodModifier::FlexShrinkImpl,
        CommonMethodModifier::FlexBasisImpl,
        CommonMethodModifier::AlignSelfImpl,
        CommonMethodModifier::DisplayPriorityImpl,
        CommonMethodModifier::ZIndexImpl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::DirectionImpl,
        CommonMethodModifier::AlignImpl,
        CommonMethodModifier::PositionImpl,
        CommonMethodModifier::MarkAnchorImpl,
        CommonMethodModifier::OffsetImpl,
        CommonMethodModifier::EnabledImpl,
        CommonMethodModifier::UseSizeTypeImpl,
        CommonMethodModifier::AlignRules0Impl,
        CommonMethodModifier::AlignRules1Impl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::AspectRatioImpl,
        CommonMethodModifier::ClickEffectImpl,
        CommonMethodModifier::OnDragStartImpl,
        CommonMethodModifier::OnDragEnterImpl,
        CommonMethodModifier::OnDragMoveImpl,
        CommonMethodModifier::OnDragLeaveImpl,
        CommonMethodModifier::OnDropImpl,
        CommonMethodModifier::OnDragEndImpl,
        CommonMethodModifier::AllowDropImpl,
        CommonMethodModifier::DraggableImpl,
        CommonMethodModifier::DragPreviewImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::LinearGradientImpl,
        CommonMethodModifier::SweepGradientImpl,
        CommonMethodModifier::RadialGradientImpl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::ShadowImpl,
        CommonMethodModifier::BlendModeImpl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::Clip0Impl,
        CommonMethodModifier::Clip1Impl,
        CommonMethodModifier::ClipShapeImpl,
        CommonMethodModifier::Mask0Impl,
        CommonMethodModifier::Mask1Impl,
        CommonMethodModifier::MaskShapeImpl,
        CommonMethodModifier::KeyImpl,
        CommonMethodModifier::IdImpl,
        CommonMethodModifier::GeometryTransition0Impl,
        CommonMethodModifier::GeometryTransition1Impl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::SphericalEffectImpl,
        CommonMethodModifier::LightUpEffectImpl,
        CommonMethodModifier::PixelStretchEffectImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
        CommonMethodModifier::AccessibilityGroupImpl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::RenderFitImpl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightnessImpl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBeginImpl,
        CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::MonopolizeEventsImpl,
        CommonMethodModifier::OnTouchInterceptImpl,
        CommonMethodModifier::OnSizeChangeImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
