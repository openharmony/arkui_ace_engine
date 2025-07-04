/*
* Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ani_measure_layout.h"
namespace OHOS::Ace::Ani {

void Wrap(ani_env* env, ani_object object, OHOS::Ace::NG::MeasureLayoutChild* child)
{
    if (ANI_OK != env->Object_SetFieldByName_Long(object, "measureLayoutChild", reinterpret_cast<ani_long>(child))) {
        return;
    }
}

OHOS::Ace::NG::MeasureLayoutChild* Unwrap(ani_env* env, ani_object object)
{
    ani_long nativeAddr;
    if (ANI_OK != env->Object_GetFieldByName_Long(object, "measureLayoutChild", &nativeAddr)) {
        return nullptr;
    }
    return reinterpret_cast<OHOS::Ace::NG::MeasureLayoutChild*>(nativeAddr);
}

bool ParseAniDimension(ani_env* env, ani_object obj, CalcDimension& result, DimensionUnit defaultUnit)
{
    if (AniUtils::IsUndefined(env, obj)) {
        return false;
    }
    if (AniUtils::IsNumber(env, obj)) {
        ani_double param_value;
        env->Object_CallMethodByName_Double(obj, "unboxed", ":D", &param_value);

        result = CalcDimension(param_value, defaultUnit);
        return true;
    }
    if (AniUtils::IsString(env, obj)) {
        auto stringContent = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(obj));
        result = StringUtils::StringToCalcDimension(stringContent, false, defaultUnit);
        return true;
    }
    return false;
}

bool ParseAniDimensionVp(ani_env* env, ani_object obj, CalcDimension& result)
{
    // 'vp' -> the value varies with pixel density of device.
    return ParseAniDimension(env, obj, result, DimensionUnit::VP);
}

ani_object GenConstraintNG(ani_env* env, const NG::LayoutConstraintF& parentConstraint)
{
    auto minSize = parentConstraint.minSize;
    auto maxSize = parentConstraint.maxSize;
    ani_class cls;
    ani_object constraint_obj;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/ConstraintSizeOptionsInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    ani_object minWidth;
    ani_object minHeight;
    ani_object maxWidth;
    ani_object maxHeight;
    minWidth = AniUtils::CreateDouble(env, 0.0f);
    minHeight = AniUtils::CreateDouble(env, 0.0f);
    maxWidth = AniUtils::CreateDouble(env, 0.0f);
    maxHeight =AniUtils::CreateDouble(env, 0.0f);
    if (ANI_OK != env->Object_New(cls, ctor, &constraint_obj, minWidth, minHeight, maxWidth, maxHeight)) {
        return nullptr;
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    if (!pipeline) {
        return constraint_obj;
    }
    minWidth = AniUtils::CreateDouble(env, minSize.Width() / pipeline->GetDipScale());
    minHeight = AniUtils::CreateDouble(env, minSize.Height() / pipeline->GetDipScale());
    maxWidth = AniUtils::CreateDouble(env, maxSize.Width() / pipeline->GetDipScale());
    maxHeight = AniUtils::CreateDouble(env, maxSize.Height() / pipeline->GetDipScale());
    if (ANI_OK != env->Object_New(cls, ctor, &constraint_obj, minWidth, minHeight, maxWidth, maxHeight)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenConstraintNG failed.");
        return nullptr;
    }
    return constraint_obj;
}

ani_object GenPlaceChildrenConstraintNG(ani_env* env, const NG::SizeF& size, RefPtr<NG::LayoutProperty> layoutProperty)
{
    ani_object constraint_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/ConstraintSizeOptionsInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    ani_object minWidth;
    ani_object minHeight;
    ani_object maxWidth;
    ani_object maxHeight;
    auto pipeline = PipelineBase::GetCurrentContext();
    if (!layoutProperty || !pipeline) {
        minWidth = AniUtils::CreateDouble(env, 0.0f);
        minHeight = AniUtils::CreateDouble(env, 0.0f);
        maxWidth = AniUtils::CreateDouble(env, 0.0f);
        maxHeight =AniUtils::CreateDouble(env, 0.0f);
        if (ANI_OK != env->Object_New(cls, ctor, &constraint_obj, minWidth, minHeight, maxWidth, maxHeight)) {
            return nullptr;
        }

        return constraint_obj;
    }
    auto minSize = layoutProperty->GetLayoutConstraint().value().minSize;

    minWidth = AniUtils::CreateDouble(env, minSize.Width() / pipeline->GetDipScale());
    minHeight = AniUtils::CreateDouble(env, minSize.Height() / pipeline->GetDipScale());

    auto parentNode = AceType::DynamicCast<NG::FrameNode>(layoutProperty->GetHost()->GetParent());
    if (parentNode && parentNode->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
        layoutProperty = parentNode->GetLayoutProperty();
    }
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    const std::unique_ptr<NG::PaddingProperty>& padding =  layoutProperty->GetPaddingProperty();
    const std::unique_ptr<NG::BorderWidthProperty>& borderWidth =  layoutProperty->GetBorderWidthProperty();
    auto topPadding = padding ? padding->top->GetDimension().ConvertToVp() : 0.0f;
    auto bottomPadding = padding ? padding->bottom->GetDimension().ConvertToVp() : 0.0f;
    auto leftPadding = padding ? padding->left->GetDimension().ConvertToVp() : 0.0f;
    auto rightPadding = padding ? padding->right->GetDimension().ConvertToVp() : 0.0f;
    auto topBorder = borderWidth ? borderWidth->topDimen->ConvertToVp() : 0.0f;
    auto bottomBorder = borderWidth ? borderWidth->bottomDimen->ConvertToVp() : 0.0f;
    auto leftBorder = borderWidth ? borderWidth->leftDimen->ConvertToVp() : 0.0f;
    auto rightBorder = borderWidth ? borderWidth->rightDimen->ConvertToVp() : 0.0f;

    maxWidth = AniUtils::CreateDouble(env, size.Width() / pipeline->GetDipScale() - leftPadding - rightPadding -
        leftBorder - rightBorder);
    maxHeight =AniUtils::CreateDouble(env, size.Height() / pipeline->GetDipScale() - topPadding - bottomPadding -
        topBorder - bottomBorder);
    if (ANI_OK != env->Object_New(cls, ctor, &constraint_obj, minWidth, minHeight, maxWidth, maxHeight)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenPlaceChildrenConstraintNG failed.");
        return nullptr;
    }
    return constraint_obj;
}

ani_object GenPadding(ani_env* env,  const std::unique_ptr<NG::PaddingProperty>& paddingNative)
{
    ani_object padding_obj;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/PaddingInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    ani_object top;
    ani_object right;
    ani_object bottom;
    ani_object left;
    top = AniUtils::CreateDouble(env, paddingNative->top->GetDimension().ConvertToVp());
    right = AniUtils::CreateDouble(env, paddingNative->right->GetDimension().ConvertToVp());
    bottom = AniUtils::CreateDouble(env, paddingNative->bottom->GetDimension().ConvertToVp());
    left = AniUtils::CreateDouble(env, paddingNative->left->GetDimension().ConvertToVp());
    if (ANI_OK != env->Object_New(cls, ctor, &padding_obj, top, right, bottom, left)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenPadding failed.");
        return nullptr;
    }
    return padding_obj;
}

ani_object GenMargin(ani_env* env,  const std::unique_ptr<NG::MarginProperty>& marginNative)
{
    ani_object margin_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MarginInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    ani_object top;
    ani_object right;
    ani_object bottom;
    ani_object left;
    top = AniUtils::CreateDouble(env, marginNative->top->GetDimension().ConvertToVp());
    right = AniUtils::CreateDouble(env, marginNative->top->GetDimension().ConvertToVp());
    bottom = AniUtils::CreateDouble(env, marginNative->bottom->GetDimension().ConvertToVp());
    left = AniUtils::CreateDouble(env, marginNative->left->GetDimension().ConvertToVp());
    if (ANI_OK != env->Object_New(cls, ctor, &margin_obj, top, right, bottom, left)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenMargin failed.");
        return nullptr;
    }
    return margin_obj;
}

ani_object GenEdgeWidths(ani_env* env,  const std::unique_ptr<NG::BorderWidthProperty>& edgeWidthsNative)
{
    ani_object edgeWidths_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/EdgeWidthsInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    ani_object top;
    ani_object right;
    ani_object bottom;
    ani_object left;
    top = AniUtils::CreateDouble(env, edgeWidthsNative->topDimen->ConvertToVp());
    right = AniUtils::CreateDouble(env, edgeWidthsNative->rightDimen->ConvertToVp());
    bottom = AniUtils::CreateDouble(env, edgeWidthsNative->bottomDimen->ConvertToVp());
    left = AniUtils::CreateDouble(env, edgeWidthsNative->leftDimen->ConvertToVp());
    if (ANI_OK != env->Object_New(cls, ctor, &edgeWidths_obj, top, right, bottom, left)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenEdgeWidths failed.");
        return nullptr;
    }
    return edgeWidths_obj;
}

ani_object GenEdgesGlobalized(ani_env* env, const NG::PaddingPropertyT<float>& edgeNative, TextDirection direction)
{
    ani_object edges_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/DirectionalEdgesTInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    double px2vpScale = pipeline ? 1.0 / pipeline->GetDipScale() : 1.0;

    ani_double top;
    ani_double start;
    ani_double bottom;
    ani_double end;
    top = edgeNative.top.value_or(0) * px2vpScale;
    bottom = edgeNative.bottom.value_or(0) * px2vpScale;

    if (direction != TextDirection::RTL) {
        start = edgeNative.left.value_or(0) * px2vpScale;
        end = edgeNative.right.value_or(0) * px2vpScale;
    } else {
        start = edgeNative.right.value_or(0) * px2vpScale;
        end = edgeNative.left.value_or(0) * px2vpScale;
    }

    if (ANI_OK != env->Object_New(cls, ctor, &edges_obj, top, bottom, start, end)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenEdgesGlobalized failed.");
        return nullptr;
    }
    return edges_obj;
}

ani_object GenBorderWidthGlobalized(ani_env* env, const NG::BorderWidthPropertyT<float>& edgeNative,
    TextDirection direction)
{
    ani_object edges_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/DirectionalEdgesTInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    double px2vpScale = pipeline ? 1.0 / pipeline->GetDipScale() : 1.0;

    ani_double top;
    ani_double start;
    ani_double bottom;
    ani_double end;
    top = edgeNative.topDimen.value_or(0) * px2vpScale;
    bottom = edgeNative.bottomDimen.value_or(0) * px2vpScale;

    if (direction != TextDirection::RTL) {
        start = edgeNative.leftDimen.value_or(0) * px2vpScale;
        end = edgeNative.rightDimen.value_or(0) * px2vpScale;
    } else {
        start = edgeNative.rightDimen.value_or(0) * px2vpScale;
        end = edgeNative.leftDimen.value_or(0) * px2vpScale;
    }

    if (ANI_OK != env->Object_New(cls, ctor, &edges_obj, top, bottom, start, end)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenBorderWidthGlobalized failed.");
        return nullptr;
    }
    return edges_obj;
}
    
ani_object GenSelfLayoutInfo(ani_env* env, RefPtr<NG::LayoutProperty> layoutProperty)
{
    ani_object selfLayoutInfo_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/GeometryInfoInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    if (ANI_OK != env->Object_New(cls, ctor, &selfLayoutInfo_obj)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenSelfLayoutInfo failed.");
        return nullptr;
    }

    const std::unique_ptr<NG::PaddingProperty> defaultPadding = std::make_unique<NG::PaddingProperty>();
    const std::unique_ptr<NG::PaddingProperty> defaultMargin = std::make_unique<NG::MarginProperty>();
    const std::unique_ptr<NG::BorderWidthProperty>& defaultEdgeWidth = std::make_unique<NG::BorderWidthProperty>();
    auto pipeline = PipelineBase::GetCurrentContext();
    if (!layoutProperty || !pipeline) {
        env->Object_SetPropertyByName_Ref(selfLayoutInfo_obj, "borderWidth", GenEdgeWidths(env, defaultEdgeWidth));
        env->Object_SetPropertyByName_Ref(selfLayoutInfo_obj, "margin", GenMargin(env, defaultPadding));
        env->Object_SetPropertyByName_Ref(selfLayoutInfo_obj, "padding", GenPadding(env, defaultPadding));
        env->Object_SetPropertyByName_Double(selfLayoutInfo_obj, "width", (ani_double)0.0f);
        env->Object_SetPropertyByName_Double(selfLayoutInfo_obj, "height", (ani_double)0.0f);
        return selfLayoutInfo_obj;
    }
    CHECK_NULL_RETURN(layoutProperty->GetHost(), nullptr);
    auto parentNode = AceType::DynamicCast<NG::FrameNode>(layoutProperty->GetHost()->GetParent());
    if (parentNode && parentNode->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
        layoutProperty = parentNode->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProperty, nullptr);
    }
    auto host = layoutProperty->GetHost();
    NG::RectF originGeoRect;
    if (host) {
        originGeoRect = host->GetGeometryNode()->GetFrameRect();
    }
    auto width =
        GreatNotEqual(originGeoRect.Width(), 0.0f) ? originGeoRect.Width() / pipeline->GetDipScale()
        : layoutProperty->GetLayoutConstraint()
            ? layoutProperty->GetLayoutConstraint()->selfIdealSize.Width().value_or(0.0) / pipeline->GetDipScale()
            : 0.0f;
    auto height =
        GreatNotEqual(originGeoRect.Height(), 0.0f) ? originGeoRect.Height() / pipeline->GetDipScale()
        : layoutProperty->GetLayoutConstraint()
            ? layoutProperty->GetLayoutConstraint()->selfIdealSize.Height().value_or(0.0) / pipeline->GetDipScale()
            : 0.0f;

    env->Object_SetPropertyByName_Ref(selfLayoutInfo_obj, "borderWidth",
        GenEdgeWidths(env, layoutProperty->GetBorderWidthProperty() ?
            layoutProperty->GetBorderWidthProperty() : defaultEdgeWidth));
    env->Object_SetPropertyByName_Ref(selfLayoutInfo_obj, "margin",
        GenMargin(env, layoutProperty->GetMarginProperty() ? layoutProperty->GetMarginProperty() : defaultPadding));
    env->Object_SetPropertyByName_Ref(selfLayoutInfo_obj, "padding",
        GenPadding(env, layoutProperty->GetPaddingProperty() ? layoutProperty->GetPaddingProperty() : defaultPadding));
    env->Object_SetPropertyByName_Double(selfLayoutInfo_obj, "width",
        NearEqual(width, 0.0f)
            ? layoutProperty->GetLayoutConstraint()->percentReference.Width() / pipeline->GetDipScale()
            : width);
    env->Object_SetPropertyByName_Double(selfLayoutInfo_obj, "height",
        NearEqual(height, 0.0f)
            ? layoutProperty->GetLayoutConstraint()->percentReference.Height() / pipeline->GetDipScale()
            : height);
    return selfLayoutInfo_obj;
}

void FillPlaceSizeProperty(ani_env* env, ani_object info, const NG::SizeF& size)
{
    ani_object measureResult_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MeasureResultInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return;
    }

    Dimension measureWidth(size.Width(), DimensionUnit::PX);
    Dimension measureHeight(size.Height(), DimensionUnit::PX);
    ani_double width = measureWidth.ConvertToVp();
    ani_double height = measureHeight.ConvertToVp();
    if (ANI_OK != env->Object_New(cls, ctor, &measureResult_obj, width, height)) {
        return;
    }
    if (ANI_OK != env->Object_SetPropertyByName_Ref(info, "measureResult", measureResult_obj)) {
        return;
    }
}

ani_object GenMeasureResult(ani_env* env, const NG::SizeF& size)
{
    ani_object measureResult_obj;
    ani_class cls;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MeasureResultInner;";
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    Dimension measureWidth(size.Width(), DimensionUnit::PX);
    Dimension measureHeight(size.Height(), DimensionUnit::PX);
    ani_double width;
    ani_double height;
    width = measureWidth.ConvertToVp();
    height = measureHeight.ConvertToVp();
    if (ANI_OK != env->Object_New(cls, ctor, &measureResult_obj, width, height)) {
        TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenMeasureResult failed.");
        return nullptr;
    }

    return measureResult_obj;
}

JSMeasureLayoutParamNG::JSMeasureLayoutParamNG(NG::LayoutWrapper* layoutWrapper, ani_env* env)
    : MeasureLayoutParam(layoutWrapper)
{
    ani_vm* vm = nullptr;
    if (ANI_OK != env->GetVM(&vm)) {
        LOGE("GetVM failed");
    }
    deleter_ = [vm](ani_array_ref ref) {
            if (ref != nullptr) {
                ani_env* env = nullptr;
                vm->GetEnv(ANI_VERSION_1, &env);
                env->GlobalReference_Delete(static_cast<ani_ref>(ref));
            }
        };
    Init(env);
}

void JSMeasureLayoutParamNG::Init(ani_env* env)
{
    int32_t count = GetTotalChildCount();
    ani_class childCls = nullptr;
    static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MeasurableLayoutableInner;";
    if (ANI_OK != env->FindClass(className, &childCls)) {
        return;
    }

    ani_ref undefinedRef = nullptr;
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        return;
    }

    ani_array_ref array;
    if (ANI_OK != env->Array_New_Ref(childCls, count, undefinedRef, &array)) {
        return;
    }
    ani_ref temp;
    if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(array), &temp)) {
        return;
    }
    childArray_.reset(static_cast<ani_array_ref>(temp), deleter_);
    GenChildArray(env, 0, count);
}

ani_object GenMeasurable(ani_env* env,  NG::MeasureLayoutChild* child)
{
        ani_class cls ;
        static const char *className =
            "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MeasurableLayoutableInner;";
        if (ANI_OK != env->FindClass(className, &cls)) {
            return nullptr;
        }
        ani_method ctor;
        if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
            return nullptr;
        }

        ani_object measurable;
        if (ANI_OK != env->Object_New(cls, ctor, &measurable)) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT, "GenMeasurable failed.");
            return nullptr;
        }

        Wrap(env, measurable, child);
        return measurable;
}

void JSMeasureLayoutParamNG::GenChildArray(ani_env* env, int32_t start, int32_t end)
{
    for (int32_t index = start; index < end; index++) {
        auto child = GetChildByIndex(index);
        auto info = GenMeasurable(env, &Get(index));

        if (child && child->GetHostNode()) {
            auto uniqueId = child->GetHostNode()->GetId();
            ani_object uniqueId_obj = AniUtils::CreateDouble(env, uniqueId);
            if (ANI_OK != env->Object_SetPropertyByName_Ref(info, "uniqueId", uniqueId_obj)) {
                return;
            }
        }

        if (ANI_OK != env->Array_Set_Ref(childArray_.get(), index, info)) {
            return;
        }
    }
}

ani_object JSMeasureLayoutParamNG::GetConstraint(ani_env* env)
{
    auto layoutWrapper = GetLayoutWrapper();
    if (layoutWrapper && layoutWrapper->GetLayoutProperty() &&
        layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()) {
        auto layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint().value();
        return GenConstraintNG(env, layoutConstraint);
    }
    return GenConstraintNG(env, NG::LayoutConstraintF());
}

ani_object JSMeasureLayoutParamNG::GetPlaceChildrenConstraint(ani_env* env)
{
    auto layoutWrapper = GetLayoutWrapper();
    if (layoutWrapper && layoutWrapper->GetLayoutProperty() && layoutWrapper->GetGeometryNode()) {
        auto layoutFrameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        return GenPlaceChildrenConstraintNG(env, layoutFrameSize, layoutWrapper->GetLayoutProperty());
    }
    return GenPlaceChildrenConstraintNG(env, NG::SizeF(), MakeRefPtr<NG::LayoutProperty>());
}

ani_object JSMeasureLayoutParamNG::GetSelfLayoutInfo(ani_env* env)
{
    auto layoutWrapper = GetLayoutWrapper();
    return GenSelfLayoutInfo(env, layoutWrapper && layoutWrapper->GetLayoutProperty() ?
        layoutWrapper->GetLayoutProperty() : MakeRefPtr<NG::LayoutProperty>());
}

void JSMeasureLayoutParamNG::Update(ani_env* env,  NG::LayoutWrapper* layoutWrapper)
{
    NG::MeasureLayoutChild* addr = nullptr;
    int32_t count = GetTotalChildCount();
    if (count > 0) {
        addr = &Get(0);
    }
    MeasureLayoutParam::Update(layoutWrapper);
    int32_t newCount = GetTotalChildCount();
    if (count == newCount) {
        return;
    }
    if (count < newCount) {
        ani_class childCls = nullptr;
        static const char *className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MeasurableLayoutableInner;";
        if (ANI_OK != env->FindClass(className, &childCls)) {
            return;
        }

        ani_ref undefinedRef = nullptr;
        if (ANI_OK != env->GetUndefined(&undefinedRef)) {
            return;
        }
        
        ani_array_ref array;
        if (ANI_OK != env->Array_New_Ref(childCls, newCount, undefinedRef, &array)) {
            return;
        }
        
        for (int32_t index = 0; index < newCount; index++) {
            auto child = GetChildByIndex(index);
            auto info = GenMeasurable(env, &Get(index));

            if (child && child->GetHostNode()) {
                auto uniqueId = child->GetHostNode()->GetId();
                ani_object uniqueId_obj = AniUtils::CreateDouble(env, uniqueId);
                if (ANI_OK != env->Object_SetPropertyByName_Ref(info, "uniqueId", uniqueId_obj)) {
                    return;
                }
            }
            if (ANI_OK != env->Array_Set_Ref(array, index, info)) {
                return;
            }
        }
        ani_ref temp;
        if (ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(array), &temp)) {
            return;
        }
        childArray_.reset(static_cast<ani_array_ref>(temp), deleter_);
    }
}

ani_object ANIGetMargin(ani_env* env,  ani_object object)
{
    auto ptr = static_cast<NG::MeasureLayoutChild*>(Unwrap(env, object));

    auto child = ptr->GetOrCreateChild();
    if (!(child && child->GetLayoutProperty())) {
        return GenEdgesGlobalized(env, {}, TextDirection::LTR);
    }
    auto layoutProperty = child->GetLayoutProperty();
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    return GenEdgesGlobalized(env, layoutProperty->CreateMarginWithoutCache(), direction);
}
ani_object ANIGetPadding(ani_env* env, [[maybe_unused]] ani_object object)
{
    auto ptr = static_cast<NG::MeasureLayoutChild*>(Unwrap(env, object));
    auto child = ptr->GetOrCreateChild();
    if (!(child && child->GetLayoutProperty())) {
        return GenEdgesGlobalized(env, {}, TextDirection::LTR);
    }
    auto layoutProperty = child->GetLayoutProperty();
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    return GenEdgesGlobalized(env, layoutProperty->CreatePaddingWithoutBorder(false, false), direction);
}
ani_object ANIGetBorderWidth(ani_env* env, [[maybe_unused]] ani_object object)
{
    auto ptr = static_cast<NG::MeasureLayoutChild*>(Unwrap(env, object));
    auto child = ptr->GetOrCreateChild();
    if (!(child && child->GetLayoutProperty())) {
        return GenBorderWidthGlobalized(env, {}, TextDirection::LTR);
    }
    auto layoutProperty = child->GetLayoutProperty();
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    return GenBorderWidthGlobalized(env, layoutProperty->CreateBorder(), direction);
}

ani_object ANIMeasure(ani_env* env, ani_object aniClass, ani_object sizeObj)
{
    auto ptr = static_cast<NG::MeasureLayoutChild*>(Unwrap(env, aniClass));
    auto child = ptr->GetOrCreateChild();
    if (!child) {
        return AniUtils::GetUndefined(env);
    }
    auto childLayoutConstraint = ptr->CreateChildConstraint();
    auto layoutProperty = child->GetLayoutProperty();

    if (AniUtils::IsUndefined(env, sizeObj)) {
        return AniUtils::GetUndefined(env);
    }

    CalcDimension minWidth;
    
    ani_ref minWidth_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(sizeObj, "minWidth", &minWidth_ref)) {
        return nullptr;
    }
    ani_object minWidth_obj = static_cast<ani_object>(minWidth_ref);

    if (ParseAniDimensionVp(env, minWidth_obj, minWidth)) {
        if (layoutProperty) {
            layoutProperty->UpdateCalcMinSize(NG::CalcSize(NG::CalcLength(minWidth), std::nullopt));
        } else {
            auto length = ConvertToPx(NG::CalcLength(minWidth), childLayoutConstraint.scaleProperty,
                childLayoutConstraint.percentReference.Width());
            if (length) {
                childLayoutConstraint.minSize.SetWidth(length.value());
            }
        }
    }

    CalcDimension maxWidth;
    ani_ref maxWidth_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(sizeObj, "maxWidth", &maxWidth_ref)) {
        return nullptr;
    }
    ani_object maxWidth_obj = static_cast<ani_object>(maxWidth_ref);
    if (ParseAniDimensionVp(env, maxWidth_obj, maxWidth)) {
        if (layoutProperty) {
            layoutProperty->UpdateCalcMaxSize(NG::CalcSize(NG::CalcLength(maxWidth), std::nullopt));
        } else {
            auto length = ConvertToPx(NG::CalcLength(maxWidth), childLayoutConstraint.scaleProperty,
                childLayoutConstraint.percentReference.Width());
            if (length) {
                childLayoutConstraint.maxSize.SetWidth(length.value());
            }
        }
    }

    CalcDimension minHeight;
    ani_ref minHeight_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(sizeObj, "minHeight", &minHeight_ref)) {
        return nullptr;
    }
    ani_object minHeight_obj = static_cast<ani_object>(minHeight_ref);
    if (ParseAniDimensionVp(env, minHeight_obj, minHeight)) {
        if (layoutProperty) {
            layoutProperty->UpdateCalcMinSize(NG::CalcSize(std::nullopt, NG::CalcLength(minHeight)));
        } else {
            auto length = ConvertToPx(NG::CalcLength(minHeight), childLayoutConstraint.scaleProperty,
                childLayoutConstraint.percentReference.Height());
            if (length) {
                childLayoutConstraint.minSize.SetHeight(length.value());
            }
        }
    }

    CalcDimension maxHeight;
    ani_ref maxHeight_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(sizeObj, "maxHeight", &maxHeight_ref)) {
        return nullptr;
    }
    ani_object maxHeight_obj = static_cast<ani_object>(maxHeight_ref);
    if (ParseAniDimensionVp(env, maxHeight_obj, maxHeight)) {
        if (layoutProperty) {
            layoutProperty->UpdateCalcMaxSize(NG::CalcSize(std::nullopt, NG::CalcLength(maxHeight)));
        } else {
            auto length = ConvertToPx(NG::CalcLength(maxHeight), childLayoutConstraint.scaleProperty,
                childLayoutConstraint.percentReference.Height());
            if (length) {
                childLayoutConstraint.maxSize.SetHeight(length.value());
            }
        }
    }

    child->Measure(childLayoutConstraint);

    auto size = child->GetGeometryNode()->GetFrameSize();
    FillPlaceSizeProperty(env, aniClass, size);

    ani_object measureResultObject = GenMeasureResult(env, size);
    return measureResultObject;
}

ani_object ANIPlaceChildren(ani_env* env, ani_object aniClass, ani_object positionObj)
{
    auto ptr = static_cast<NG::MeasureLayoutChild*>(Unwrap(env, aniClass));
    auto child = ptr->GetChild();
    if (!child) {
        return AniUtils::GetUndefined(env);
    }

    if (AniUtils::IsUndefined(env, positionObj)) {
        child->Layout();
        return AniUtils::GetUndefined(env);
    }

    CalcDimension dimenX;
    ani_ref dimenX_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(positionObj, "x", &dimenX_ref)) {
        return nullptr;
    }
    ani_object dimenX_obj = static_cast<ani_object>(dimenX_ref);
    auto xResult = ParseAniDimensionVp(env, dimenX_obj, dimenX);

    CalcDimension dimenY;
    ani_ref dimenY_ref;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(positionObj, "y", &dimenY_ref)) {
        return nullptr;
    }
    ani_object dimenY_obj = static_cast<ani_object>(dimenY_ref);
    auto yResult = ParseAniDimensionVp(env, dimenY_obj, dimenY);
    if (!(xResult || yResult)) {
        LOGE("the position prop is illegal");
    } else {
        child->GetGeometryNode()->SetMarginFrameOffset({ dimenX.ConvertToPx(), dimenY.ConvertToPx() });
    }
    child->Layout();
    return AniUtils::GetUndefined(env);
}

ani_status BindMeasurable(ani_env* env)
{
    static const char* className = "Larkui/ani/arkts/ArkUIAniCustomNodeModule/MeasurableLayoutableInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "measureInner", nullptr, reinterpret_cast<void*>(ANIMeasure) },
        ani_native_function { "layoutInner", nullptr, reinterpret_cast<void*>(ANIPlaceChildren) },
        ani_native_function { "getMarginInner", nullptr, reinterpret_cast<void*>(ANIGetMargin) },
        ani_native_function { "getPaddingInner", nullptr, reinterpret_cast<void*>(ANIGetPadding) },
        ani_native_function { "getBorderWidthInner", nullptr, reinterpret_cast<void*>(ANIGetBorderWidth) },
    };
    ani_status tmp = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != tmp) {
        return ANI_ERROR;
    };
    return ANI_OK;
}

RefPtr<JSMeasureLayoutParamNG> JSMeasureLayoutParamNG::GetInstance(NG::LayoutWrapper* layoutWrapper, ani_env* env)
{
    auto host = AceType::DynamicCast<NG::CustomMeasureLayoutNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_RETURN(host, nullptr);
    BindMeasurable(env);
    auto jsParam = AceType::DynamicCast<JSMeasureLayoutParamNG>(host->GetMeasureLayoutParam());
    if (!jsParam) {
        jsParam = AceType::MakeRefPtr<JSMeasureLayoutParamNG>(layoutWrapper, env);
        host->SetMeasureLayoutParam(jsParam);
    } else {
        jsParam->Update(env, layoutWrapper);
    }
    return jsParam;
}

} // namespace OHOS::Ace::Ani