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

#include "dynamiclayout/dynamiclayout_module.h"

#include <memory>

#include "base/utils/utils.h"
#include "load.h"
#include "base/log/log.h"
#include "utils/ani_utils.h"
#include "common/common_module.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::Ani {
ani_object CreateLayoutConstraintF(ani_env* env, const NG::LayoutConstraintF& constraintF);
ani_object CreateLayoutOffset(ani_env* env, const NG::OffsetF& offset);

ani_long DynamicLayoutConstruct(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id, ani_int flags)
{
    ani_long nativeObj {};
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nativeObj);
    const auto* dynamicLayoutModifier = modifier->getArkUIAniDynamicLayoutModifier();
    CHECK_NULL_RETURN(dynamicLayoutModifier, nativeObj);
    if (dynamicLayoutModifier->construct) {
        auto* node = dynamicLayoutModifier->construct(id, flags);
        nativeObj = reinterpret_cast<ani_long>(node);
    }
    return nativeObj;
}

void SetStackLayoutAlgorithmParam(
    ani_env* env, const ani_object& obj, ArkUINodeHandle node, const ArkUIAniDynamicLayoutModifier* modifier)
{
    ArkUIStackLayoutAlgorithm algorithm;
    ani_ref alignContentRef;
    env->Object_GetPropertyByName_Ref(obj, "alignContent", &alignContentRef);
    ani_boolean isUndefined = ANI_FALSE;
    env->Reference_IsUndefined(alignContentRef, &isUndefined);
    if (!isUndefined) {
        ani_int ordinal = 0;
        ani_object alignObj = static_cast<ani_object>(alignContentRef);
        if (env->Object_CallMethodByName_Int(alignObj, "getOrdinal", nullptr, &ordinal) == ANI_OK) {
            algorithm.alignContent = static_cast<ArkUI_Int32>(ordinal);
        }
    }
    if (modifier->setDynamicLayoutStackOptions) {
        modifier->setDynamicLayoutStackOptions(node, algorithm);
    }
}

ArkUILayoutAlgorithmLengthMetrics ParseLengthMetrics(ani_env* env, ani_ref lengthMetricsRef)
{
    ArkUILayoutAlgorithmLengthMetrics result;
    if (AniUtils::IsUndefined(env, lengthMetricsRef)) {
        return result;
    }
    ani_object propObj = static_cast<ani_object>(lengthMetricsRef);
    ani_double value = 0.0;
    if (env->Object_GetPropertyByName_Double(propObj, "value", &value) == ANI_OK) {
        result.value = value;
    }
    ani_ref unitRef;
    env->Object_GetPropertyByName_Ref(propObj, "unit", &unitRef);
    if (!AniUtils::IsUndefined(env, unitRef)) {
        ani_int ordinal = 0;
        ani_object unitObj = static_cast<ani_object>(unitRef);
        if (env->Object_CallMethodByName_Int(unitObj, "getOrdinal", nullptr, &ordinal) == ANI_OK) {
            result.unit = static_cast<ArkUI_Int32>(ordinal);
        }
    }
    ani_ref resourceRef;
    if (env->Object_GetPropertyByName_Ref(propObj, "resource", &resourceRef) != ANI_OK) {
        return result;
    }
    if (AniUtils::IsUndefined(env, resourceRef)) {
        return result;
    }
    ani_object resObj = static_cast<ani_object>(resourceRef);
    if (!AniUtils::IsClassObject(env, resObj, "global.resource.Resource")) {
        return result;
    }
    result.isResource = true;
    ani_long aniId = 0;
    if (env->Object_GetPropertyByName_Long(resObj, "id", &aniId) == ANI_OK) {
        result.resource.resId = static_cast<int32_t>(aniId);
    }
    ani_ref typeRef;
    if (env->Object_GetPropertyByName_Ref(resObj, "type", &typeRef) == ANI_OK) {
        AniUtils::GetOptionalInt(env, typeRef, result.resource.resType);
    }
    std::string bundleName;
    std::string moduleName;
    AniUtils::GetStringByName(env, resObj, "bundleName", bundleName);
    AniUtils::GetStringByName(env, resObj, "moduleName", moduleName);
    result.resource.bundleName = bundleName.empty() ? "" : bundleName;
    result.resource.moduleName = moduleName.empty() ? "" : moduleName;
    return result;
}

void ReadLengthMetricsProperty(
    ani_env* env, const ani_object& obj, const char* propName, ArkUILayoutAlgorithmLengthMetrics& outMetrics)
{
    ani_ref propRef;
    if (env->Object_GetPropertyByName_Ref(obj, propName, &propRef) == ANI_OK) {
        outMetrics = ParseLengthMetrics(env, propRef);
    }
}

void ReadEnumPropertyAsInt(
    ani_env* env, const ani_object& obj, const char* propName, ArkUI_Int32& outValue)
{
    ani_ref propRef;
    if (env->Object_GetPropertyByName_Ref(obj, propName, &propRef) != ANI_OK) {
        return;
    }
    if (AniUtils::IsUndefined(env, propRef)) {
        return;
    }
    ani_int ordinal = 0;
    ani_object propObj = static_cast<ani_object>(propRef);
    if (env->Object_CallMethodByName_Int(propObj, "getOrdinal", nullptr, &ordinal) == ANI_OK) {
        outValue = static_cast<ArkUI_Int32>(ordinal);
    }
}

void ReadBooleanProperty(
    ani_env* env, const ani_object& obj, const char* propName, ani_boolean& outValue)
{
    ani_ref propRef;
    if (env->Object_GetPropertyByName_Ref(obj, propName, &propRef) != ANI_OK) {
        return;
    }
    if (AniUtils::IsUndefined(env, propRef)) {
        return;
    }
    bool result = false;
    if (AniUtils::GetBoolParam(env, propRef, result)) {
        outValue = static_cast<ani_boolean>(result);
    }
}

void SetRowLayoutAlgorithmParam(
    ani_env* env, const ani_object& obj, ArkUINodeHandle node, const ArkUIAniDynamicLayoutModifier* modifier)
{
    ArkUIRowLayoutAlgorithm algorithm;
    ReadLengthMetricsProperty(env, obj, "space", algorithm.space);
    ReadEnumPropertyAsInt(env, obj, "alignItems", algorithm.alignItems);
    ReadEnumPropertyAsInt(env, obj, "justifyContent", algorithm.justifyContent);
    ReadBooleanProperty(env, obj, "isReverse", algorithm.isReverse);
    if (modifier->setDynamicLayoutRowOptions) {
        modifier->setDynamicLayoutRowOptions(node, algorithm);
    }
}

void SetColumnLayoutAlgorithmParam(
    ani_env* env, const ani_object& obj, ArkUINodeHandle node, const ArkUIAniDynamicLayoutModifier* modifier)
{
    ArkUIColumnLayoutAlgorithm algorithm;
    ReadLengthMetricsProperty(env, obj, "space", algorithm.space);
    ReadEnumPropertyAsInt(env, obj, "alignItems", algorithm.alignItems);
    ReadEnumPropertyAsInt(env, obj, "justifyContent", algorithm.justifyContent);
    ReadBooleanProperty(env, obj, "isReverse", algorithm.isReverse);
    if (modifier->setDynamicLayoutColumnOptions) {
        modifier->setDynamicLayoutColumnOptions(node, algorithm);
    }
}

void SetDynamicLayoutStackLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object stackLayoutAlgorithm)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    const auto* dynamicLayoutModifier = modifier->getArkUIAniDynamicLayoutModifier();
    if (!dynamicLayoutModifier) {
        return;
    }
    if (AniUtils::IsUndefined(env, stackLayoutAlgorithm)) {
        return;
    }

    ani_class dynamicLayoutStackLayoutAlgorithm;
    if (env->FindClass("arkui.LayoutAlgorithm.StackLayoutAlgorithm", &dynamicLayoutStackLayoutAlgorithm) != ANI_OK) {
        return;
    }
    ani_boolean isExpectedType = ANI_FALSE;
    env->Object_InstanceOf(stackLayoutAlgorithm, dynamicLayoutStackLayoutAlgorithm, &isExpectedType);
    if (isExpectedType) {
        SetStackLayoutAlgorithmParam(env, stackLayoutAlgorithm, arkNode, dynamicLayoutModifier);
    }
}

void SetDynamicLayoutRowLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object rowLayoutAlgorithm)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    const auto* dynamicLayoutModifier = modifier->getArkUIAniDynamicLayoutModifier();
    if (!dynamicLayoutModifier) {
        return;
    }
    if (AniUtils::IsUndefined(env, rowLayoutAlgorithm)) {
        return;
    }

    ani_class dynamicLayoutRowLayoutAlgorithm;
    if (env->FindClass("arkui.LayoutAlgorithm.RowLayoutAlgorithm", &dynamicLayoutRowLayoutAlgorithm) != ANI_OK) {
        return;
    }
    ani_boolean isExpectedType = ANI_FALSE;
    env->Object_InstanceOf(rowLayoutAlgorithm, dynamicLayoutRowLayoutAlgorithm, &isExpectedType);
    if (isExpectedType) {
        SetRowLayoutAlgorithmParam(env, rowLayoutAlgorithm, arkNode, dynamicLayoutModifier);
    }
}

void SetDynamicLayoutColumnLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object columnLayoutAlgorithm)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode) {
        return;
    }
    const auto* dynamicLayoutModifier = modifier->getArkUIAniDynamicLayoutModifier();
    if (!dynamicLayoutModifier) {
        return;
    }
    if (AniUtils::IsUndefined(env, columnLayoutAlgorithm)) {
        return;
    }

    ani_class dynamicLayoutColumnLayoutAlgorithm;
    if (env->FindClass("arkui.LayoutAlgorithm.ColumnLayoutAlgorithm", &dynamicLayoutColumnLayoutAlgorithm) != ANI_OK) {
        return;
    }
    ani_boolean isExpectedType = ANI_FALSE;
    env->Object_InstanceOf(columnLayoutAlgorithm, dynamicLayoutColumnLayoutAlgorithm, &isExpectedType);
    if (isExpectedType) {
        SetColumnLayoutAlgorithmParam(env, columnLayoutAlgorithm, arkNode, dynamicLayoutModifier);
    }
}

std::function<void(const NG::LayoutConstraintF&)> CreateOnMeasureFunc(ani_vm* vm,
    std::shared_ptr<ani_wref> algoWeakRef, std::shared_ptr<ani_wref> frameNodeWeakRef)
{
    return [vm, algoWeakRef, frameNodeWeakRef](const NG::LayoutConstraintF& layoutConstraint) -> void {
        CHECK_NULL_VOID(vm);
        ani_env* refEnv = nullptr;
        GetAniEnv(vm, &refEnv);
        CHECK_NULL_VOID(refEnv);
        ani_boolean algoReleased = ANI_FALSE;
        ani_ref algoRef;
        if (refEnv->WeakReference_GetReference(*algoWeakRef, &algoReleased, &algoRef) != ANI_OK || algoReleased) {
            return;
        }
        ani_boolean frameNodeReleased = ANI_FALSE;
        ani_ref frameNodeRef;
        if (refEnv->WeakReference_GetReference(
            *frameNodeWeakRef, &frameNodeReleased, &frameNodeRef) != ANI_OK || frameNodeReleased) {
            return;
        }
        auto algoObj = reinterpret_cast<ani_object>(algoRef);
        auto fnObj = reinterpret_cast<ani_object>(frameNodeRef);
        auto constraintObj = CreateLayoutConstraintF(refEnv, layoutConstraint);
        if (!constraintObj) {
            return;
        }
        auto status = refEnv->Object_CallMethodByName_Void(algoObj, "onMeasure",
            "C{arkui.FrameNode.FrameNode}C{arkui.FrameNode.LayoutConstraint}:", fnObj, constraintObj);
        if (status != ANI_OK) {
            HILOGE("SetDynamicLayoutCustomLayoutAlgorithm invoke onMeasure fail, status: %{public}d", status);
        }
    };
}

std::function<void(const OHOS::Ace::NG::OffsetF&)> CreateOnLayoutFunc(ani_vm* vm,
    std::shared_ptr<ani_wref> algoWeakRef, std::shared_ptr<ani_wref> frameNodeWeakRef)
{
    return [vm, algoWeakRef, frameNodeWeakRef](const OHOS::Ace::NG::OffsetF& offset) -> void {
        CHECK_NULL_VOID(vm);
        ani_env* refEnv = nullptr;
        GetAniEnv(vm, &refEnv);
        CHECK_NULL_VOID(refEnv);

        ani_boolean algoReleased = ANI_FALSE;
        ani_ref algoRef;
        if (refEnv->WeakReference_GetReference(*algoWeakRef, &algoReleased, &algoRef) != ANI_OK || algoReleased) {
            return;
        }
        ani_boolean frameNodeReleased = ANI_FALSE;
        ani_ref frameNodeRef;
        if (refEnv->WeakReference_GetReference(
            *frameNodeWeakRef, &frameNodeReleased, &frameNodeRef) != ANI_OK || frameNodeReleased) {
            return;
        }
        auto algoObj = reinterpret_cast<ani_object>(algoRef);
        auto fnObj = reinterpret_cast<ani_object>(frameNodeRef);

        auto positionObj = CreateLayoutOffset(refEnv, offset);
        if (!positionObj) {
            return;
        }
        auto status = refEnv->Object_CallMethodByName_Void(algoObj, "onLayout",
            "C{arkui.FrameNode.FrameNode}C{arkui.Graphics.Vector2}:", fnObj, positionObj);
        if (status != ANI_OK) {
            HILOGE("SetDynamicLayoutCustomLayoutAlgorithm invoke onLayout fail, status: %{public}d", status);
        }
    };
}

bool hasOnMeasureFunc(ani_env* env, const ani_object& customLayoutAlgorithm)
{
    ani_type objType = nullptr;
    if ((env->Object_GetType(customLayoutAlgorithm, &objType)) != ANI_OK) {
        HILOGI("CustomLayoutAlgorithm Object_GetType fail");
        return false;
    }
    ani_method onMeasureMethod = nullptr;
    auto status = env->Class_FindMethod(static_cast<ani_class>(objType), "onMeasure",
        "C{arkui.FrameNode.FrameNode}C{arkui.FrameNode.LayoutConstraint}:", &onMeasureMethod);
    return (status == ANI_OK) && onMeasureMethod;
}

bool hasOnLayoutFunc(ani_env* env, const ani_object& customLayoutAlgorithm)
{
    ani_type objType = nullptr;
    if ((env->Object_GetType(customLayoutAlgorithm, &objType)) != ANI_OK) {
        HILOGI("CustomLayoutAlgorithm Object_GetType fail");
        return false;
    }
    ani_method onLayoutMethod = nullptr;
    auto status = env->Class_FindMethod(static_cast<ani_class>(objType), "onLayout",
        "C{arkui.FrameNode.FrameNode}C{arkui.Graphics.Vector2}:", &onLayoutMethod);
    return (status == ANI_OK) && onLayoutMethod;
}

void SetDynamicLayoutCustomLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object customLayoutAlgorithm,
    ani_object frameNode)
{
    const auto* modifier = GetNodeAniModifier();
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(ptr);
    if (!modifier || !arkNode || !env) {
        return;
    }
    const auto* dynamicLayoutModifier = modifier->getArkUIAniDynamicLayoutModifier();
    if (!dynamicLayoutModifier || !dynamicLayoutModifier->setDynamicLayoutCustomOptions) {
        return;
    }
    if (AniUtils::IsUndefined(env, customLayoutAlgorithm) || AniUtils::IsUndefined(env, frameNode)) {
        return;
    }
    ani_class customLayoutAlgorithmClass;
    if (env->FindClass("arkui.LayoutAlgorithm.CustomLayoutAlgorithm", &customLayoutAlgorithmClass) != ANI_OK) {
        return;
    }
    ani_boolean isExpectedType = ANI_FALSE;
    env->Object_InstanceOf(customLayoutAlgorithm, customLayoutAlgorithmClass, &isExpectedType);
    if (!isExpectedType) {
        return;
    }
    ani_vm* vm = nullptr;
    if (env->GetVM(&vm) != ANI_OK || !vm) {
        return;
    }
    std::shared_ptr<ani_wref> algoWeakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* refEnv = nullptr;
        vm->GetEnv(ANI_VERSION_1, &refEnv);
        if (refEnv) {
            refEnv->WeakReference_Delete(*wref);
        }
    });
    env->WeakReference_Create(customLayoutAlgorithm, algoWeakRef.get());
    std::shared_ptr<ani_wref> frameNodeWeakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* refEnv = nullptr;
        vm->GetEnv(ANI_VERSION_1, &refEnv);
        if (refEnv) {
            refEnv->WeakReference_Delete(*wref);
        }
    });
    env->WeakReference_Create(frameNode, frameNodeWeakRef.get());
    ArkUICustomLayoutAlgorithm algorithm;
    if (hasOnMeasureFunc(env, customLayoutAlgorithm)) {
        algorithm.onMeasureFunc = CreateOnMeasureFunc(vm, algoWeakRef, frameNodeWeakRef);
    }
    if (hasOnLayoutFunc(env, customLayoutAlgorithm)) {
        algorithm.onPlaceChildrenFunc = CreateOnLayoutFunc(vm, algoWeakRef, frameNodeWeakRef);
    }
    dynamicLayoutModifier->setDynamicLayoutCustomOptions(arkNode, algorithm);
}
} // namespace OHOS::Ace::Ani
