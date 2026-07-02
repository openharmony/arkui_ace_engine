/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cmath>
#include "lazy_dynamic_layout/lazy_dynamic_layout_module.h"

#include <memory>

#include "load.h"
#include "log/log.h"
#include "utils/ani_utils.h"
#include "common/common_module.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/interfaces/ani/ani_api.h"
#include "ani.h"

namespace OHOS::Ace::Ani {
ani_object CreateLayoutConstraintF(ani_env* env, const NG::LayoutConstraintF& constraintF);
ani_object CreateLayoutOffset(ani_env* env, const NG::OffsetF& offset);
ani_object CreateLazyLayoutInfo(ani_env* env, const NG::ViewPosReference& viewPosRef, float mainSize);
std::function<void(const NG::LayoutConstraintF&)> CreateOnMeasureFunc(ani_vm* vm,
    std::shared_ptr<ani_wref> algoWeakRef, std::shared_ptr<ani_wref> frameNodeWeakRef);
std::function<void(const NG::LayoutConstraintF&, float)> CreateLazyOnMeasureFunc(ani_vm* vm,
    std::shared_ptr<ani_wref> algoWeakRef, std::shared_ptr<ani_wref> frameNodeWeakRef, ArkUINodeHandle arkNode);
std::function<void(const NG::OffsetF&)> CreateOnLayoutFunc(ani_vm* vm,
    std::shared_ptr<ani_wref> algoWeakRef, std::shared_ptr<ani_wref> frameNodeWeakRef);
bool hasOnMeasureFunc(ani_env* env, const ani_object& customLayoutAlgorithm);
bool hasOnLayoutFunc(ani_env* env, const ani_object& customLayoutAlgorithm);
ani_method GetLazyOnMeasureMethod(ani_env* env, const ani_object& customLayoutAlgorithm);

void HandleAdjustedOffset(ani_env* env, ArkUINodeHandle arkNode, ani_object resultObj,
    const ArkUIAniLazyDynamicLayoutModifier* modifier)
{
    ani_int adjustedOffsetValue = 0;
    ANI_CALL(env, Object_GetPropertyByName_Int(resultObj, "adjustedOffset", &adjustedOffsetValue), return);
    int32_t adjustedOffset = static_cast<int32_t>(adjustedOffsetValue);
    if (modifier->setAdjustedOffset) {
        modifier->setAdjustedOffset(arkNode, static_cast<float>(adjustedOffset));
    }
}

void HandleInActiveChildren(ani_env* env, ArkUINodeHandle arkNode, ani_object resultObj,
    const ArkUIAniLazyDynamicLayoutModifier* modifier)
{
    std::vector<int32_t> inActiveChildren;
    if (!AniUtils::GetArrayIntParam(env, resultObj, "inActiveChildren", inActiveChildren)) {
        return;
    }
    
    if (modifier->setInActiveChildren) {
        modifier->setInActiveChildren(arkNode, inActiveChildren);
    }
}

void HandleLazyMeasureResult(ani_env* env, ArkUINodeHandle arkNode, ani_object resultObj)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    const auto* lazyDynamicLayoutModifier = modifier->getArkUIAniLazyDynamicLayoutModifier();
    CHECK_NULL_VOID(lazyDynamicLayoutModifier);
    
    HandleAdjustedOffset(env, arkNode, resultObj, lazyDynamicLayoutModifier);
    HandleInActiveChildren(env, arkNode, resultObj, lazyDynamicLayoutModifier);
}

ani_object CreateLazyLayoutInfo(ani_env* env, const NG::ViewPosReference& viewPosRef, float mainSize)
{
    ani_object result = nullptr;
    ani_class lazyLayoutInfoClass;
    ANI_CALL(env, FindClass("arkui.LazyLayoutAlgorithm.LazyLayoutInfo", &lazyLayoutInfoClass), return nullptr);
    
    ani_method lazyLayoutInfoCtor;
    ANI_CALL(env, Class_FindMethod(lazyLayoutInfoClass, "<ctor>",
        "iiC{arkui.LazyLayoutAlgorithm.LazyLayoutDirection}:", &lazyLayoutInfoCtor), return nullptr);
    
    float viewStart = viewPosRef.viewPosStart - viewPosRef.viewExtStart;
    float viewEnd = viewPosRef.viewPosEnd + viewPosRef.viewExtEnd;
    
    if (viewPosRef.referenceEdge == NG::ReferenceEdge::START) {
        viewStart -= viewPosRef.referencePos;
        viewEnd -= viewPosRef.referencePos;
    } else {
        viewStart -= (viewPosRef.referencePos - mainSize);
        viewEnd -= (viewPosRef.referencePos - mainSize);
    }

    // Clamp values to valid int32 range to prevent RangeError
    float clampedViewStart = std::clamp(viewStart, static_cast<float>(INT32_MIN), static_cast<float>(INT32_MAX));
    float clampedViewEnd = std::clamp(viewEnd, static_cast<float>(INT32_MIN), static_cast<float>(INT32_MAX));
    
    // Handle NaN/Infinity by defaulting to 0
    if (!std::isfinite(clampedViewStart)) {
        clampedViewStart = 0.0f;
    }
    if (!std::isfinite(clampedViewEnd)) {
        clampedViewEnd = 0.0f;
    }
    
    ani_int viewStartInt = static_cast<ani_int>(std::floor(clampedViewStart));
    ani_int viewEndInt = static_cast<ani_int>(std::floor(clampedViewEnd));
    ani_size directionIndex = static_cast<ani_size>(viewPosRef.referenceEdge);

    ani_enum_item lazyLayoutDirectionItem = nullptr;
    if (!AniUtils::GetEnumItem(env, directionIndex,
        "arkui.LazyLayoutAlgorithm.LazyLayoutDirection", lazyLayoutDirectionItem)) {
        HILOGE("Get LazyLayoutDirection enum item failed");
        return nullptr;
    }
    
    ANI_CALL(env, Object_New(lazyLayoutInfoClass, lazyLayoutInfoCtor, &result,
        viewStartInt, viewEndInt, lazyLayoutDirectionItem), return nullptr);
    
    return result;
}

ani_method GetLazyOnMeasureMethod(ani_env* env, const ani_object& customLayoutAlgorithm)
{
    ani_type objType = nullptr;
    ANI_CALL(env, Object_GetType(customLayoutAlgorithm, &objType), return nullptr);
    ani_method lazyOnMeasureMethod = nullptr;
    ANI_CALL(env, Class_FindMethod(static_cast<ani_class>(objType), "__onMeasure__",
        nullptr, &lazyOnMeasureMethod), return nullptr);
    return lazyOnMeasureMethod;
}

std::function<void(const NG::LayoutConstraintF&, float)> CreateLazyOnMeasureFunc(ani_vm* vm,
    std::shared_ptr<ani_wref> algoWeakRef, std::shared_ptr<ani_wref> frameNodeWeakRef, ArkUINodeHandle arkNode)
{
    return [vm, algoWeakRef, frameNodeWeakRef, arkNode](
        const NG::LayoutConstraintF& layoutConstraint, float mainSize) -> void {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(arkNode);
        ani_env* refEnv = nullptr;
        GetAniEnv(vm, &refEnv);
        CHECK_NULL_VOID(refEnv);
        
        ani_boolean algoReleased = ANI_FALSE;
        ani_ref algoRefRaw;
        ANI_CALL(refEnv, WeakReference_GetReference(*algoWeakRef, &algoReleased, &algoRefRaw), return);
        if (algoReleased) {
            return;
        }
        AniLocalRefGuard algoGuard(refEnv, algoRefRaw);
        
        ani_boolean frameNodeReleased = ANI_FALSE;
        ani_ref frameNodeRefRaw;
        ANI_CALL(refEnv, WeakReference_GetReference(
            *frameNodeWeakRef, &frameNodeReleased, &frameNodeRefRaw), return);
        if (frameNodeReleased) {
            return;
        }
        AniLocalRefGuard frameNodeGuard(refEnv, frameNodeRefRaw);
        
        auto algoObj = static_cast<ani_object>(algoGuard);
        auto fnObj = static_cast<ani_object>(frameNodeGuard);
        
        auto constraintObj = CreateLayoutConstraintF(refEnv, layoutConstraint);
        CHECK_NULL_VOID(constraintObj);
        
        ani_ref resultRef;
        ani_method onMeasureMethod = GetLazyOnMeasureMethod(refEnv, algoObj);
        
        if (onMeasureMethod && layoutConstraint.viewPosRef.has_value()) {
            auto lazyLayoutInfoObj = CreateLazyLayoutInfo(refEnv, layoutConstraint.viewPosRef.value(), mainSize);
            CHECK_NULL_VOID(lazyLayoutInfoObj);
            
            ANI_CALL(refEnv, Object_CallMethod_Ref(algoObj, onMeasureMethod,
                &resultRef, fnObj, constraintObj, lazyLayoutInfoObj), return);
            
            ani_boolean resultUndefined = ANI_FALSE;
            ANI_CALL(refEnv, Reference_IsUndefined(resultRef, &resultUndefined), return);
            if (resultUndefined) {
                return;
            }
            
            auto resultObj = reinterpret_cast<ani_object>(resultRef);
            
            HandleLazyMeasureResult(refEnv, arkNode, resultObj);
        } else {
            ani_ref undefinedRef;
            ANI_CALL(refEnv, GetUndefined(&undefinedRef), return);
            ANI_CALL(refEnv, Object_CallMethodByName_Void(algoObj, "onMeasure",
                nullptr, fnObj, constraintObj, undefinedRef), return);
        }
    };
}

ani_long LazyDynamicLayoutConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id, ani_int flags)
{
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nativeObj);
    const auto* lazyDynamicLayoutModifier = modifier->getArkUIAniLazyDynamicLayoutModifier();
    CHECK_NULL_RETURN(lazyDynamicLayoutModifier, nativeObj);
    if (lazyDynamicLayoutModifier->construct) {
        auto* node = lazyDynamicLayoutModifier->construct(id, flags);
        nativeObj = reinterpret_cast<ani_long>(node);
    }
    return nativeObj;
}

void SetLazyDynamicLayoutCustomLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object customLayoutAlgorithm,
    ani_object frameNode)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode || !env) {
        return;
    }
    const auto* lazyDynamicLayoutModifier = modifier->getArkUIAniLazyDynamicLayoutModifier();
    if (!lazyDynamicLayoutModifier || !lazyDynamicLayoutModifier->setLazyDynamicLayoutOptions) {
        return;
    }
    if (AniUtils::IsUndefined(env, customLayoutAlgorithm) || AniUtils::IsUndefined(env, frameNode)) {
        return;
    }
    ani_class lazyCustomLayoutAlgorithmClass;
    ANI_CALL(env, FindClass("arkui.LazyLayoutAlgorithm.LazyCustomLayoutAlgorithm",
        &lazyCustomLayoutAlgorithmClass), return);
    ani_boolean isExpectedType = ANI_FALSE;
    ANI_CALL(env, Object_InstanceOf(customLayoutAlgorithm, lazyCustomLayoutAlgorithmClass, &isExpectedType), return);
    if (!isExpectedType) {
        return;
    }
    ani_ref axisRef = nullptr;
    ANI_CALL(env, Object_GetPropertyByName_Ref(customLayoutAlgorithm, "axis", &axisRef), return);
    ani_int axisValue = 0;
    ani_enum_item axisItem = static_cast<ani_enum_item>(static_cast<ani_object>(axisRef));
    ANI_CALL(env, EnumItem_GetValue_Int(axisItem, &axisValue), return);
    ani_vm* vm = nullptr;
    ANI_CALL(env, GetVM(&vm), return);
    CHECK_NULL_VOID(vm);
    std::shared_ptr<ani_wref> algoWeakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* refEnv = nullptr;
        vm->GetEnv(ANI_VERSION_1, &refEnv);
        if (refEnv) {
            refEnv->WeakReference_Delete(*wref);
        }
    });
    ANI_CALL(env, WeakReference_Create(customLayoutAlgorithm, algoWeakRef.get()), return);
    std::shared_ptr<ani_wref> frameNodeWeakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* refEnv = nullptr;
        vm->GetEnv(ANI_VERSION_1, &refEnv);
        if (refEnv) {
            refEnv->WeakReference_Delete(*wref);
        }
    });
    ANI_CALL(env, WeakReference_Create(frameNode, frameNodeWeakRef.get()), return);
    ArkUILazyCustomLayoutAlgorithm algorithm;
    algorithm.axis = axisValue;
    if (GetLazyOnMeasureMethod(env, customLayoutAlgorithm)) {
        algorithm.onMeasureFunc = CreateLazyOnMeasureFunc(vm, algoWeakRef, frameNodeWeakRef, arkNode);
    }
    if (hasOnLayoutFunc(env, customLayoutAlgorithm)) {
        algorithm.onPlaceChildrenFunc = CreateOnLayoutFunc(vm, algoWeakRef, frameNodeWeakRef);
    }
    lazyDynamicLayoutModifier->setLazyDynamicLayoutOptions(arkNode, algorithm);
}

void SetLazyDynamicLayoutOnVisibleIndexesChange(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object callback)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    CHECK_NULL_VOID(modifier);
    CHECK_NULL_VOID(arkNode);
    const auto* lazyDynamicLayoutModifier = modifier->getArkUIAniLazyDynamicLayoutModifier();
    CHECK_NULL_VOID(lazyDynamicLayoutModifier);
    if (!lazyDynamicLayoutModifier->setOnVisibleIndexesChange) {
        return;
    }
    if (AniUtils::IsUndefined(env, callback)) {
        lazyDynamicLayoutModifier->setOnVisibleIndexesChange(arkNode, nullptr);
        return;
    }
    ani_vm* vm = nullptr;
    ANI_CALL(env, GetVM(&vm), return);
    CHECK_NULL_VOID(vm);
    std::shared_ptr<ani_wref> callbackWeakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* refEnv = nullptr;
        vm->GetEnv(ANI_VERSION_1, &refEnv);
        if (refEnv) {
            refEnv->WeakReference_Delete(*wref);
        }
    });
    ANI_CALL(env, WeakReference_Create(callback, callbackWeakRef.get()), return);
    auto onVisibleIndexesChange = [vm, callbackWeakRef](const std::vector<int32_t>& indexes) {
        CHECK_NULL_VOID(vm);
        ani_env* refEnv = nullptr;
        vm->GetEnv(ANI_VERSION_1, &refEnv);
        CHECK_NULL_VOID(refEnv);
        ani_boolean released = ANI_FALSE;
        ani_ref callbackRefRaw;
        ANI_CALL(refEnv, WeakReference_GetReference(*callbackWeakRef, &released, &callbackRefRaw), return);
        if (released) {
            return;
        }
        AniLocalRefGuard callbackGuard(refEnv, callbackRefRaw);
        auto callbackFn = static_cast<ani_fn_object>(callbackGuard);
        ani_ref undefined;
        ANI_CALL(refEnv, GetUndefined(&undefined), return);
        ani_array indexesArray;
        ani_size arraySize = static_cast<ani_size>(indexes.size());
        ANI_CALL(refEnv, Array_New(arraySize, undefined, &indexesArray), return);
        ani_class intCls;
        ANI_CALL(refEnv, FindClass("std.core.Int", &intCls), return);
        ani_method intCtor;
        ANI_CALL(refEnv, Class_FindMethod(intCls, "<ctor>", "i:", &intCtor), return);
        for (ani_size i = 0; i < arraySize; ++i) {
            ani_object intObj;
            ANI_CALL(refEnv, Object_New(intCls, intCtor, &intObj, static_cast<ani_int>(indexes[i])), continue);
            ANI_CALL(refEnv, Array_Set(indexesArray, i, intObj), continue);
        }
        ani_ref result;
        ani_ref args[] = { static_cast<ani_ref>(indexesArray) };
        ANI_CALL(refEnv, FunctionalObject_Call(callbackFn, 1, args, &result), return);
    };
    lazyDynamicLayoutModifier->setOnVisibleIndexesChange(arkNode, std::move(onVisibleIndexesChange));
}

} // namespace OHOS::Ace::Ani