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

#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <unordered_map>

#define KOALA_INTEROP_MODULE ArkUINativeModule
#include "common-interop.h"
#include "interop-logging.h"

#include "arkoala_api_generated.h"
#include "Serializers.h"

const OH_AnyAPI* GetAnyImpl(int kind, int version, std::string* result = nullptr);

const GENERATED_ArkUIBasicNodeAPI* GetArkUIBasicNodeAPI() {
    return reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_BASIC),
        GENERATED_ARKUI_BASIC_NODE_API_VERSION, nullptr));
}

const GENERATED_ArkUIExtendedNodeAPI* GetArkUIExtendedNodeAPI() {
    return reinterpret_cast<const GENERATED_ArkUIExtendedNodeAPI*>(
        GetAnyImpl(static_cast<int>(GENERATED_Ark_APIVariantKind::GENERATED_EXTENDED),
        GENERATED_ARKUI_EXTENDED_NODE_API_VERSION, nullptr));
}

CustomDeserializer* DeserializerBase::customDeserializers = nullptr;

// TODO: Remove all this.
void disposeNode(KNativePointer* ptr) {
    GetArkUIBasicNodeAPI()->disposeNode((Ark_NodeHandle)ptr);
}
KNativePointer impl_GetNodeFinalizer() {
    return fnPtr<KNativePointer>(disposeNode);
}
KOALA_INTEROP_DIRECT_0(GetNodeFinalizer, KNativePointer)

// custom methods
void impl_ShowCrash(const KStringPtr& messagePtr) {
    GetArkUIExtendedNodeAPI()->showCrash(messagePtr.c_str());
}
KOALA_INTEROP_V1(ShowCrash, KStringPtr)

Ark_Int32 impl_LayoutNode(KVMContext vmContext, Ark_NativePointer nodePtr, KFloatArray data) {
    return GetArkUIExtendedNodeAPI()->layoutNode((Ark_VMContext)vmContext, (Ark_NodeHandle)nodePtr, (Ark_Float32(*)[2])data);
}
KOALA_INTEROP_CTX_2(LayoutNode, Ark_Int32, Ark_NativePointer, KFloatArray)

struct PerfInfo {
    int64_t start;
    int64_t end;
    int64_t cost;
    std::string perf_name;
    void Print(std::stringstream& result, float counterSelf = 0.0) {
        result << "Perf trace_name(" << perf_name <<  ") cost " << (cost / 1000.0 - counterSelf) << " us.";
    }
};

class Performance {
  public:
    void PrintAvgs(std::stringstream& result) {
        for (const auto& [name, perfs] : perfs_) {
            if (name == "perf_counter_self_cost") continue;
            float totalCost = 0;
            for (const auto& perf : perfs) {
                totalCost += perf.cost / 1000.0 - self_cost_;
            }
            auto avg = totalCost / perfs.size();
            result << "Perf trace_name(" << name << ") " << perfs.size() << " call avg cost " << avg << " us.";
        }
    }
    void PrintTotals(std::stringstream& result) {
        for (const auto& [name, perfs] : perfs_) {
            float totalCost = 0;
            for (const auto& perf : perfs) {
                totalCost += perf.cost / 1000.0 - self_cost_;
            }
            result << "Perf trace_name(" << name << ") " << perfs.size() << " call total cost " << totalCost << " us.";
        }
    }
    void PrintPeak(std::stringstream& result) {
        for(auto &kv : perfs_) {
            std::sort(kv.second.begin(), kv.second.end(), [](const PerfInfo &perf1, const PerfInfo &perf2) {
                return perf1.cost > perf2.cost;
            });
            auto maxCost = kv.second.front().cost / 1000.0 - self_cost_;
            auto minCost = kv.second.back().cost / 1000.0 - self_cost_;
            result << "Perf trace_name(" << kv.first << ") " << " maxCost = " << maxCost << " us, ";
            result << "minCost = " << minCost << " us.";
        }
    }
    void PrintDetails(std::stringstream& result) {
        for (const auto& [name, perfs] : perfs_) {
            for (auto perf : perfs) {
                perf.Print(result);
            }
        }
    }
    void FinishOne() {
        perfs_[current_.perf_name].emplace_back(current_);
    }
    void CalcSelfCost() {
        float totalCost = 0.0;
        auto it = perfs_.find("perf_counter_self_cost");
        if (it == perfs_.end()) {
            self_cost_ = totalCost;
            return;
        }
        for (const auto& perf : it->second) {
            totalCost += perf.cost / 1000.0;
        }
        self_cost_ = totalCost / it->second.size();
    }
    void Clean() {
        perfs_.clear();
    }
    PerfInfo* GetCurrent() { return &current_; }
    static Performance* GetInstance() {
        static Performance perf;
        return &perf;
    }
private:
    std::unordered_map<std::string, std::vector<PerfInfo>> perfs_;
    PerfInfo current_;
    float self_cost_;
};

void impl_StartPerf(const KStringPtr& traceName) {
    PerfInfo* perf = Performance::GetInstance()->GetCurrent();
    perf->perf_name = traceName.c_str();
    auto now = std::chrono::high_resolution_clock::now();
    perf->start = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
}
KOALA_INTEROP_V1(StartPerf, KStringPtr)

void impl_EndPerf(const KStringPtr& traceName) {
    auto now = std::chrono::high_resolution_clock::now();
    PerfInfo* perf = Performance::GetInstance()->GetCurrent();
    perf->end = std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count();
    perf->cost = perf->end - perf->start;
    Performance::GetInstance()->FinishOne();
}
KOALA_INTEROP_V1(EndPerf, KStringPtr)

enum DumpOptions {
    TOTAL = 0,
    AVERAGE = 1,
    PEAK = 2,
    DETAILS = 3,
    CLEAR = 4
};

KNativePointer impl_DumpPerf(KInt options) {
    std::stringstream result;
    result << std::fixed << std::setprecision(3);
    auto perf = Performance::GetInstance();
    perf->CalcSelfCost();
    switch (options) {
        case TOTAL:
            perf->PrintTotals(result);
            break;
        case AVERAGE:
            perf->PrintAvgs(result);
            break;
        case PEAK:
            perf->PrintPeak(result);
            break;
        case DETAILS:
            perf->PrintDetails(result);
            break;
        case CLEAR:
            perf->Clean();
            break;
        default:
            break;
    }
    return new std::string(result.str());
}
KOALA_INTEROP_1(DumpPerf, KNativePointer, KInt)
// custom API methods

Ark_NativePointer impl_CreateNode(Ark_Int32 type, Ark_Int32 id, Ark_Int32 flags)
{
    GENERATED_Ark_NodeType typeCast = GENERATED_Ark_NodeType(type);
    return GetArkUIBasicNodeAPI()->createNode(typeCast, id, flags);
}
KOALA_INTEROP_DIRECT_3(CreateNode, Ark_NativePointer, Ark_Int32, Ark_Int32, Ark_Int32)

Ark_NativePointer impl_GetNodeByViewStack()
{
    return GetArkUIBasicNodeAPI()->getNodeByViewStack();
}
KOALA_INTEROP_DIRECT_0(GetNodeByViewStack, Ark_NativePointer)

void impl_DisposeNode(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIBasicNodeAPI()->disposeNode(nodePtrCast);
}
KOALA_INTEROP_DIRECT_V1(DisposeNode, Ark_NativePointer)

void impl_DumpTreeNode(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIBasicNodeAPI()->dumpTreeNode(nodePtrCast);
}
KOALA_INTEROP_DIRECT_V1(DumpTreeNode, Ark_NativePointer)

void impl_RemoveChild(Ark_NativePointer parent, Ark_NativePointer child)
{
    Ark_NodeHandle parentCast = (Ark_NodeHandle) parent;
    Ark_NodeHandle childCast = (Ark_NodeHandle) child;
    GetArkUIBasicNodeAPI()->removeChild(parentCast, childCast);
    GetArkUIBasicNodeAPI()->markDirty(parentCast, GENERATED_ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
}
KOALA_INTEROP_DIRECT_V2(RemoveChild, Ark_NativePointer, Ark_NativePointer)

Ark_Int32 impl_InsertChildAfter(Ark_NativePointer parent, Ark_NativePointer child, Ark_NativePointer sibling)
{
    Ark_NodeHandle parentCast = (Ark_NodeHandle) parent;
    Ark_NodeHandle childCast = (Ark_NodeHandle) child;
    Ark_NodeHandle siblingCast = (Ark_NodeHandle) sibling;
    auto result = GetArkUIBasicNodeAPI()->insertChildAfter(parentCast, childCast, siblingCast);
    GetArkUIBasicNodeAPI()->markDirty(parentCast, GENERATED_ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return result;
}
KOALA_INTEROP_DIRECT_3(InsertChildAfter, Ark_Int32, Ark_NativePointer, Ark_NativePointer, Ark_NativePointer)

Ark_Int32 impl_AddChild(Ark_NativePointer parent, Ark_NativePointer child)
{
    Ark_NodeHandle parentCast = (Ark_NodeHandle) parent;
    Ark_NodeHandle childCast = (Ark_NodeHandle) child;
    auto result = GetArkUIBasicNodeAPI()->addChild(parentCast, childCast);
    GetArkUIBasicNodeAPI()->markDirty(parentCast, GENERATED_ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return result;
}
KOALA_INTEROP_DIRECT_2(AddChild, Ark_Int32, Ark_NativePointer, Ark_NativePointer)

Ark_Int32 impl_InsertChildBefore(Ark_NativePointer parent, Ark_NativePointer child, Ark_NativePointer sibling)
{
    Ark_NodeHandle parentCast = (Ark_NodeHandle) parent;
    Ark_NodeHandle childCast = (Ark_NodeHandle) child;
    Ark_NodeHandle siblingCast = (Ark_NodeHandle) sibling;
    auto result = GetArkUIBasicNodeAPI()->insertChildBefore(parentCast, childCast, siblingCast);
    GetArkUIBasicNodeAPI()->markDirty(parentCast, GENERATED_ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return result;
}
KOALA_INTEROP_DIRECT_3(InsertChildBefore, Ark_Int32, Ark_NativePointer, Ark_NativePointer, Ark_NativePointer)

Ark_Int32 impl_InsertChildAt(Ark_NativePointer parent, Ark_NativePointer child, Ark_Int32 position)
{
    Ark_NodeHandle parentCast = (Ark_NodeHandle) parent;
    Ark_NodeHandle childCast = (Ark_NodeHandle) child;
    auto result = GetArkUIBasicNodeAPI()->insertChildAt(parentCast, childCast, position);
    GetArkUIBasicNodeAPI()->markDirty(parentCast, GENERATED_ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST);
    return result;
}
KOALA_INTEROP_DIRECT_3(InsertChildAt, Ark_Int32, Ark_NativePointer, Ark_NativePointer, Ark_Int32)

void impl_ApplyModifierFinish(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIBasicNodeAPI()->applyModifierFinish(nodePtrCast);
}
KOALA_INTEROP_DIRECT_V1(ApplyModifierFinish, Ark_NativePointer)

void impl_MarkDirty(Ark_NativePointer nodePtr, KUInt dirtyFlag)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    Ark_UInt32 dirtyFlagCast = (Ark_UInt32) dirtyFlag;
    GetArkUIBasicNodeAPI()->markDirty(nodePtrCast, dirtyFlagCast);
}
KOALA_INTEROP_V2(MarkDirty, Ark_NativePointer, KUInt)

KBoolean impl_IsBuilderNode(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIBasicNodeAPI()->isBuilderNode(nodePtrCast);
}
KOALA_INTEROP_DIRECT_1(IsBuilderNode, KBoolean, Ark_NativePointer)

Ark_Float32 impl_ConvertLengthMetricsUnit(Ark_Float32 value, Ark_Int32 originUnit, Ark_Int32 targetUnit)
{
    return GetArkUIBasicNodeAPI()->convertLengthMetricsUnit(value, originUnit, targetUnit);
}
KOALA_INTEROP_DIRECT_3(ConvertLengthMetricsUnit, Ark_Float32, Ark_Float32, Ark_Int32, Ark_Int32)

void impl_MeasureLayoutAndDraw(KVMContext vmContext, Ark_NativePointer nodePtr)
{
    Ark_VMContext vmContextCast = (Ark_VMContext) vmContext;
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->measureLayoutAndDraw(vmContextCast, nodePtrCast);
}
KOALA_INTEROP_CTX_V1(MeasureLayoutAndDraw, Ark_NativePointer)

Ark_Int32 impl_MeasureNode(KVMContext vmContext, Ark_NativePointer nodePtr, KFloatArray data)
{
    Ark_VMContext vmContextCast = (Ark_VMContext) vmContext;
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    Ark_Float32* dataCast = (Ark_Float32*) data;
    return GetArkUIExtendedNodeAPI()->measureNode(vmContextCast, nodePtrCast, dataCast);
}
KOALA_INTEROP_CTX_2(MeasureNode, Ark_Int32, Ark_NativePointer, KFloatArray)

Ark_Int32 impl_DrawNode(KVMContext vmContext, Ark_NativePointer nodePtr, KFloatArray data)
{
    Ark_VMContext vmContextCast = (Ark_VMContext) vmContext;
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    Ark_Float32* dataCast = (Ark_Float32*) data;
    return GetArkUIExtendedNodeAPI()->drawNode(vmContextCast, nodePtrCast, dataCast);
}
KOALA_INTEROP_CTX_2(DrawNode, Ark_Int32, Ark_NativePointer, KFloatArray)

Ark_Int32 impl_IndexerChecker(KVMContext vmContext, Ark_NativePointer nodePtr)
{
    Ark_VMContext vmContextCast = (Ark_VMContext) vmContext;
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->indexerChecker(vmContextCast, nodePtrCast);
}
KOALA_INTEROP_CTX_1(IndexerChecker, Ark_Int32, Ark_NativePointer)

void impl_SetLazyItemIndexer(KVMContext vmContext, Ark_NativePointer nodePtr, Ark_Int32 indexerId)
{
    Ark_VMContext vmContextCast = (Ark_VMContext) vmContext;
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setLazyItemIndexer(vmContextCast, nodePtrCast, indexerId);
}
KOALA_INTEROP_CTX_V2(SetLazyItemIndexer, Ark_NativePointer, Ark_Int32)

void impl_SetCustomCallback(KVMContext vmContext, Ark_NativePointer nodePtr, Ark_Int32 updaterId)
{
    Ark_VMContext vmContextCast = (Ark_VMContext) vmContext;
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setCustomCallback(vmContextCast, nodePtrCast, updaterId);
}
KOALA_INTEROP_CTX_V2(SetCustomCallback, Ark_NativePointer, Ark_Int32)

void impl_SetMeasureWidth(Ark_NativePointer nodePtr, Ark_Int32 value)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setMeasureWidth(nodePtrCast, value);
}
KOALA_INTEROP_DIRECT_V2(SetMeasureWidth, Ark_NativePointer, Ark_Int32)

Ark_Int32 impl_GetMeasureWidth(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->getMeasureWidth(nodePtrCast);
}
KOALA_INTEROP_DIRECT_1(GetMeasureWidth, Ark_Int32, Ark_NativePointer)

void impl_SetMeasureHeight(Ark_NativePointer nodePtr, Ark_Int32 value)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setMeasureHeight(nodePtrCast, value);
}
KOALA_INTEROP_DIRECT_V2(SetMeasureHeight, Ark_NativePointer, Ark_Int32)

Ark_Int32 impl_GetMeasureHeight(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->getMeasureHeight(nodePtrCast);
}
KOALA_INTEROP_DIRECT_1(GetMeasureHeight, Ark_Int32, Ark_NativePointer)

void impl_SetX(Ark_NativePointer nodePtr, Ark_Int32 value)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setX(nodePtrCast, value);
}
KOALA_INTEROP_DIRECT_V2(SetX, Ark_NativePointer, Ark_Int32)

Ark_Int32 impl_GetX(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->getX(nodePtrCast);
}
KOALA_INTEROP_DIRECT_1(GetX, Ark_Int32, Ark_NativePointer)

void impl_SetY(Ark_NativePointer nodePtr, Ark_Int32 value)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setY(nodePtrCast, value);
}
KOALA_INTEROP_DIRECT_V2(SetY, Ark_NativePointer, Ark_Int32)

Ark_Int32 impl_GetY(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->getY(nodePtrCast);
}
KOALA_INTEROP_DIRECT_1(GetY, Ark_Int32, Ark_NativePointer)

void impl_SetAlignment(Ark_NativePointer nodePtr, Ark_Int32 value)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setAlignment(nodePtrCast, value);
}
KOALA_INTEROP_DIRECT_V2(SetAlignment, Ark_NativePointer, Ark_Int32)

Ark_Int32 impl_GetAlignment(Ark_NativePointer nodePtr)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    return GetArkUIExtendedNodeAPI()->getAlignment(nodePtrCast);
}
KOALA_INTEROP_DIRECT_1(GetAlignment, Ark_Int32, Ark_NativePointer)

void impl_SetRangeUpdater(Ark_NativePointer nodePtr, Ark_Int32 updaterId)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setRangeUpdater(nodePtrCast, updaterId);
}
KOALA_INTEROP_DIRECT_V2(SetRangeUpdater, Ark_NativePointer, Ark_Int32)

void impl_SetChildTotalCount(Ark_NativePointer nodePtr, Ark_Int32 totalCount)
{
    Ark_NodeHandle nodePtrCast = (Ark_NodeHandle) nodePtr;
    GetArkUIExtendedNodeAPI()->setChildTotalCount(nodePtrCast, totalCount);
}
KOALA_INTEROP_DIRECT_V2(SetChildTotalCount, Ark_NativePointer, Ark_Int32)

static const std::string PAGE_SUFFIX = "GeneratedEntry";
[[maybe_unused]] static bool isPageClass(const std::string& className)
{
    return (PAGE_SUFFIX.size() < className.size()) && std::equal(PAGE_SUFFIX.rbegin(), PAGE_SUFFIX.rend(), className.rbegin());
}

KVMObjectHandle impl_LoadUserView(KVMContext vm, const KStringPtr& viewClass, const KStringPtr& viewParams) {
#ifdef KOALA_USE_JAVA_VM
    JNIEnv* env = reinterpret_cast<JNIEnv*>(vm);
    std:: string className(viewClass.c_str());
    std::replace(className.begin(), className.end(), '.', '/');
    jclass viewClassClass = env->FindClass(className.c_str());
    if (!viewClassClass) {
        LOGE("Cannot find user class %" LOG_PUBLIC "s", viewClass.c_str());
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return nullptr;
    }
    jmethodID viewClassCtor = env->GetMethodID(viewClassClass, "<init>", "(Ljava/lang/String;)V");
    if (!viewClassCtor) {
        LOGE("Cannot find user class ctor");
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return nullptr;
    }
    jobject result = env->NewObject(viewClassClass, viewClassCtor, env->NewStringUTF(viewParams.c_str()));
    if (!result) {
        LOGE("Cannot instantiate user class");
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
        }
        return nullptr;
    }
    return (KVMObjectHandle)result;
#elif KOALA_ETS_NAPI
    EtsEnv* env = reinterpret_cast<EtsEnv*>(vm);
    std:: string className(viewClass.c_str());
    // TODO: hack, fix it!
    if (className == "ViewLoaderApp") {
        className = "Page.App";
    } else if (className == "EtsHarness") {
        className = "@koalaui.ets-harness.build.unmemoized.build.Page.EtsHarness";
    } else if (isPageClass(className)) {
        className = "@koalaui.user.build.unmemoized.build.generated." + className;
    } else {
        className = "@koalaui.user.build.unmemoized.src.Page." + className;
    }
    std::replace(className.begin(), className.end(), '.', '/');
    ets_class viewClassClass = env->FindClass(className.c_str());
    if (!viewClassClass) {
        fprintf(stderr, "Cannot find user class %s\n", viewClass.c_str());
        if (env->ErrorCheck()) {
            env->ErrorDescribe();
            env->ErrorClear();
        }
        return nullptr;
    }
    ets_method viewClassCtor = env->Getp_method(viewClassClass, "<ctor>", "Lstd/core/String;:V");
    if (!viewClassCtor) {
        fprintf(stderr, "Cannot find user class ctor\n");
        if (env->ErrorCheck()) {
            env->ErrorDescribe();
            env->ErrorClear();
        }
        return nullptr;
    }
    ets_object result = env->NewObject(viewClassClass, viewClassCtor, env->NewStringUTF(viewParams.c_str()));
    if (!result) {
        fprintf(stderr, "Cannot instantiate user class\n");
        if (env->ErrorCheck()) {
            env->ErrorDescribe();
            env->ErrorClear();
        }
        return nullptr;
    }
    return (KVMObjectHandle)result;
#elif KOALA_ANI
    ani_env* env = reinterpret_cast<ani_env*>(vm);
    std::string className(viewClass.c_str());
    // TODO: hack, fix it!
    if (className == "UserApp") {
        className = "L@koalaui.arkts-arkui.Application.UserView;";
    } if (className == "EtsHarness") {
        className = "L@koalaui.ets-harness.build.unmemoized.build.Page.EtsHarness";
    } else if (isPageClass(className)) {
        className = "L@koalaui.user.build.unmemoized.build.generated." + className + ";";
    } else {
        className = "L@koalaui.user.build.unmemoized.src.Page." + className + ";";
    }
    std::replace(className.begin(), className.end(), '.', '/');
    ani_class viewClassClass = nullptr;
    env->FindClass(className.c_str(), &viewClassClass);
    if (!viewClassClass) {
        LOGE("Cannot find user class %" LOG_PUBLIC "s\n", viewClass.c_str());
        ani_boolean hasError = false;
        env->ExistUnhandledError(&hasError);
        if (hasError) {
            env->DescribeError();
            env->ResetError();
        }
        return nullptr;
    }
    ani_method viewClassCtor = nullptr;
    env->Class_FindMethod(viewClassClass, "<ctor>", "Lstd/core/String;:V", &viewClassCtor);
    if (!viewClassCtor) {
        LOGE("Cannot find user class ctor");
        ani_boolean hasError = false;
        env->ExistUnhandledError(&hasError);
        if (hasError) {
            env->DescribeError();
            env->ResetError();
        }
        return nullptr;
    }
    ani_object result = nullptr;
    ani_string params = nullptr;
    env->String_NewUTF8(viewParams.c_str(), viewParams.length(), &params);
    env->Object_New(viewClassClass, viewClassCtor, &result, params);
    if (!result) {
        LOGE("Cannot instantiate user class");
        ani_boolean hasError = false;
        env->ExistUnhandledError(&hasError);
        if (hasError) {
            env->DescribeError();
            env->ResetError();
        }
        return nullptr;
    }
    return (KVMObjectHandle)result;
#else
    LOGE("LoadUserView() is not implemented yet");
    return nullptr;
#endif
}
KOALA_INTEROP_CTX_2(LoadUserView, KVMObjectHandle, KStringPtr, KStringPtr)
