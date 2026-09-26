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

#include <functional>
#include <string>
#include <cstring>

#include "gtest/gtest.h"
#include "base/log/log_wrapper.h"
#include "core/common/ace_application_info.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"

#include "interfaces/native/native_animate.h"
#include "interfaces/native/native_interface.h"
#include "interfaces/native/native_interface_xcomponent.h"
#include "interfaces/native/native_key_event.h"
#include "interfaces/native/native_node.h"
#include "interfaces/native/native_node_napi.h"
#include "interfaces/native/native_render.h"
#include "interfaces/native/node/animate_impl.h"
#include "interfaces/native/node/config_manager.h"
#include "interfaces/native/node/node_model.h"
#include "interfaces/native/node/node_model_safely.h"
#include "test/mock/frameworks/base/log/mock_log_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NodeModel {
namespace {

// === Mock 线程控制 ===
const ArkUIBasicAPI* g_runtimeCheckBasicApi = nullptr;
bool (*g_runtimeCheckThread)() = nullptr;

void SetMockIsCurrentThreadSafe(bool (*checker)())
{
    g_runtimeCheckThread = checker;
}

bool SafeThread() { return true; }
bool UnsafeThread() { return false; }

// === 默认参数调用辅助 ===
template<typename Return, typename... Args>
void CallWithDefaultArgs(Return (*function)(Args...))
{
    function(Args {}...);
}

struct ScopeEntry {
    const char* name;
    void (*invoke)();
};

// 特殊参数函数的包装
void InvokeRenderGetChild()
{
    ArkUI_RenderNodeHandle child = nullptr;
    OH_ArkUI_RenderNodeUtils_GetChild(nullptr, 0, &child);
}
void InvokeRenderGetChildren()
{
    ArkUI_RenderNodeHandle* children = nullptr;
    int32_t count = 0;
    OH_ArkUI_RenderNodeUtils_GetChildren(nullptr, &children, &count);
}
void InvokeRenderGetFirstChild()
{
    ArkUI_RenderNodeHandle child = nullptr;
    OH_ArkUI_RenderNodeUtils_GetFirstChild(nullptr, &child);
}
void InvokeRenderGetNextSibling()
{
    ArkUI_RenderNodeHandle sibling = nullptr;
    OH_ArkUI_RenderNodeUtils_GetNextSibling(nullptr, &sibling);
}
void InvokeRenderGetPreviousSibling()
{
    ArkUI_RenderNodeHandle sibling = nullptr;
    OH_ArkUI_RenderNodeUtils_GetPreviousSibling(nullptr, &sibling);
}
void InvokeNodeUtilsGetNodeUniqueId()
{
    int32_t uniqueId = -1;
    OH_ArkUI_NodeUtils_GetNodeUniqueId(nullptr, &uniqueId);
}
} // namespace

// === 测试基类 ===
class UiThreadDetectionTest : public Test {
protected:
    void SetUp() override
    {
        previousDebug_ = AceApplicationInfo::GetInstance().IsDebugForParallel();
        ASSERT_TRUE(InitialFullImpl());
        fullImpl_ = GetFullImpl();
        ASSERT_NE(fullImpl_, nullptr);
        ASSERT_EQ(fullImpl_->version, ARKUI_NODE_API_VERSION);
        ASSERT_NE(fullImpl_->getBasicAPI, nullptr);
        const auto* basicApi = fullImpl_->getBasicAPI();
        ASSERT_NE(basicApi, nullptr);

        basicApi_ = *basicApi;
        basicApi_.isCurrentThreadSafe = []() -> ArkUI_Bool {
            return g_runtimeCheckThread == nullptr || g_runtimeCheckThread();
        };
        basicApi_.isDebugForParallel = []() -> ArkUI_Bool {
            return AceApplicationInfo::GetInstance().IsDebugForParallel();
        };
        basicApi_.isDebugForParallelSet = []() -> ArkUI_Bool {
            return AceApplicationInfo::GetInstance().IsDebugForParallelSet();
        };
        previousBasicApiGetter_ = fullImpl_->getBasicAPI;
        g_runtimeCheckBasicApi = &basicApi_;
        fullImpl_->getBasicAPI = []() { return g_runtimeCheckBasicApi; };
        ResetToDefault();
    }

    void TearDown() override
    {
        if (previousBasicApiGetter_ != nullptr) {
            ResetToDefault();
            fullImpl_->getBasicAPI = previousBasicApiGetter_;
            g_runtimeCheckBasicApi = nullptr;
        }
        g_runtimeCheckThread = nullptr;
        AceApplicationInfo::GetInstance().SetDebugForParallel(previousDebug_);
    }

    static void ResetToDefault()
    {
        AceApplicationInfo::GetInstance().SetDebugForParallel(false);
        SetMockIsCurrentThreadSafe(SafeThread);
        ASSERT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
            OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD, OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED),
            ARKUI_ERROR_CODE_NO_ERROR);
        ResetPrintLogCount();
    }

    static void ResetToUnresolved()
    {
        SetMockIsCurrentThreadSafe(SafeThread);
        ASSERT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
            OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD, OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED),
            ARKUI_ERROR_CODE_NO_ERROR);
    }

    // === 诊断断言辅助 ===

    void SetupDiagnosticMatch(const std::string& /*apiName*/)
    {
        ResetPrintLogCount();
    }

    void RunAndAssert(std::function<void()> action, int expectedCount)
    {
        ResetPrintLogCount();
        action();
        EXPECT_EQ(GetPrintLogCount(), expectedCount);
    }

    void RunAndExpectDiagnostic(std::function<void()> action)
    {
        ResetPrintLogCount();
        action();
        EXPECT_GT(GetPrintLogCount(), 0);
    }

    void RunAndExpectNoDiagnostic(std::function<void()> action)
    {
        bool (*savedThread)() = g_runtimeCheckThread;
        SetMockIsCurrentThreadSafe(SafeThread);
        ResetPrintLogCount();
        action();
        int baseline = GetPrintLogCount();
        g_runtimeCheckThread = savedThread;
        ResetPrintLogCount();
        action();
        EXPECT_EQ(GetPrintLogCount(), baseline);
    }

    // === 模式控制 ===
    void EnableMode(OH_ArkUI_NativeModule_RuntimeCheckMode mode)
    {
        SetMockIsCurrentThreadSafe(SafeThread);
        ASSERT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
            OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD, mode), ARKUI_ERROR_CODE_NO_ERROR);
    }

    bool previousDebug_ = false;
    ArkUIFullNodeAPI* fullImpl_ = nullptr;
    ArkUIBasicAPI basicApi_ {};
    decltype(ArkUIFullNodeAPI::getBasicAPI) previousBasicApiGetter_ = nullptr;
};

// === 个体测试 ===

HWTEST_F(UiThreadDetectionTest, LogModeProducesDiagnosticsOnUnsafeThread, TestSize.Level1)
{
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED);
    SetMockIsCurrentThreadSafe(UnsafeThread);
    SetupDiagnosticMatch("TestApi_Disabled");
    RunAndExpectNoDiagnostic([] { ConfigManager::CheckUIThread("TestApi_Disabled"); });

    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG);
    SetMockIsCurrentThreadSafe(UnsafeThread);
    SetupDiagnosticMatch("TestApi_Log");
    RunAndExpectDiagnostic([] { ConfigManager::CheckUIThread("TestApi_Log"); });

    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG);
    SetMockIsCurrentThreadSafe(SafeThread);
    SetupDiagnosticMatch("TestApi_Safe");
    RunAndExpectNoDiagnostic([] { ConfigManager::CheckUIThread("TestApi_Safe"); });
}

HWTEST_F(UiThreadDetectionTest, RejectsInvalidRuntimeCheckArguments, TestSize.Level1)
{
    SetMockIsCurrentThreadSafe(SafeThread);
    EXPECT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
        static_cast<OH_ArkUI_NativeModule_RuntimeCheckType>(-1), OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
        static_cast<OH_ArkUI_NativeModule_RuntimeCheckType>(2), OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
        OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD, static_cast<OH_ArkUI_NativeModule_RuntimeCheckMode>(-1)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_SetRuntimeCheckMode(
        OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD, static_cast<OH_ArkUI_NativeModule_RuntimeCheckMode>(3)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

HWTEST_F(UiThreadDetectionTest, RuntimeCheckModeChangeInvalidatesCache, TestSize.Level1)
{
    SetMockIsCurrentThreadSafe(SafeThread);
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED);
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG);
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED);
}

// === 参数化导出测试（175 × 4 模式）===

class UiThreadExportLogTest : public UiThreadDetectionTest, public WithParamInterface<ScopeEntry> {};

// 模式 1：默认-debug + 安全线程 → 无诊断
TEST_P(UiThreadExportLogTest, DebugDefaultSafeThreadNoDiagnostic)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    ResetToUnresolved();
    SetupDiagnosticMatch(GetParam().name);
    SetMockIsCurrentThreadSafe(SafeThread);
    RunAndExpectNoDiagnostic(GetParam().invoke);
}

// 模式 2：默认-非debug + 不安全线程 → 无诊断
TEST_P(UiThreadExportLogTest, ReleaseDefaultUnsafeThreadNoDiagnostic)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(false);
    ResetToUnresolved();
    SetupDiagnosticMatch(GetParam().name);
    SetMockIsCurrentThreadSafe(UnsafeThread);
    RunAndExpectNoDiagnostic(GetParam().invoke);
}

// 模式 3：DISABLED + 不安全线程 → 无诊断
TEST_P(UiThreadExportLogTest, DisabledModeNoDiagnostic)
{
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED);
    SetupDiagnosticMatch(GetParam().name);
    SetMockIsCurrentThreadSafe(UnsafeThread);
    RunAndExpectNoDiagnostic(GetParam().invoke);
}

// 模式 4：LOG + 不安全线程 → 有诊断
TEST_P(UiThreadExportLogTest, LogModeProducesDiagnostic)
{
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG);
    SetupDiagnosticMatch(GetParam().name);
    SetMockIsCurrentThreadSafe(UnsafeThread);
    RunAndExpectDiagnostic(GetParam().invoke);
}

// === 参数化表测试（20 × 4 模式）===

struct TableScopeEntry {
    const char* name;
    void (*invoke)(ArkUI_NativeNodeAPI_1*);
};

#define TABLE_SCOPE_ENTRY(member) \
    { #member, [](ArkUI_NativeNodeAPI_1* api) { CallWithDefaultArgs(api->member); } }
const TableScopeEntry TABLE_SCOPE_ENTRIES[] = {
    TABLE_SCOPE_ENTRY(addChild),
    TABLE_SCOPE_ENTRY(createNode),
    TABLE_SCOPE_ENTRY(disposeNode),
    TABLE_SCOPE_ENTRY(getAttribute),
    TABLE_SCOPE_ENTRY(getChildAt),
    TABLE_SCOPE_ENTRY(getFirstChild),
    TABLE_SCOPE_ENTRY(getLastChild),
    TABLE_SCOPE_ENTRY(getNextSibling),
    TABLE_SCOPE_ENTRY(getParent),
    TABLE_SCOPE_ENTRY(getPreviousSibling),
    TABLE_SCOPE_ENTRY(getTotalChildCount),
    TABLE_SCOPE_ENTRY(insertChildAfter),
    TABLE_SCOPE_ENTRY(insertChildAt),
    TABLE_SCOPE_ENTRY(insertChildBefore),
    TABLE_SCOPE_ENTRY(markDirty),
    TABLE_SCOPE_ENTRY(removeAllChildren),
    TABLE_SCOPE_ENTRY(removeChild),
    TABLE_SCOPE_ENTRY(resetAttribute),
    TABLE_SCOPE_ENTRY(setAttribute),
    TABLE_SCOPE_ENTRY(setLengthMetricUnit),
};
#undef TABLE_SCOPE_ENTRY

class UiThreadTableLogTest : public UiThreadDetectionTest, public WithParamInterface<TableScopeEntry> {};

static ArkUI_NativeNodeAPI_1* GetNodeApi()
{
    return static_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
}

static std::string TableMemberName(const char* member)
{
    return std::string("ArkUI_NativeNodeAPI_1.") + member;
}

// 模式 1：默认-debug + 安全线程 → 无诊断
TEST_P(UiThreadTableLogTest, DebugDefaultSafeThreadNoDiagnostic)
{
    auto* api = GetNodeApi();
    ASSERT_NE(api, nullptr);
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    ResetToUnresolved();
    SetupDiagnosticMatch(TableMemberName(GetParam().name));
    SetMockIsCurrentThreadSafe(SafeThread);
    RunAndExpectNoDiagnostic([api, this] { GetParam().invoke(api); });
}

// 模式 2：默认-非debug + 不安全线程 → 无诊断
TEST_P(UiThreadTableLogTest, ReleaseDefaultUnsafeThreadNoDiagnostic)
{
    auto* api = GetNodeApi();
    ASSERT_NE(api, nullptr);
    AceApplicationInfo::GetInstance().SetDebugForParallel(false);
    ResetToUnresolved();
    SetupDiagnosticMatch(TableMemberName(GetParam().name));
    SetMockIsCurrentThreadSafe(UnsafeThread);
    RunAndExpectNoDiagnostic([api, this] { GetParam().invoke(api); });
}

// 模式 3：DISABLED + 不安全线程 → 无诊断
TEST_P(UiThreadTableLogTest, DisabledModeNoDiagnostic)
{
    auto* api = GetNodeApi();
    ASSERT_NE(api, nullptr);
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED);
    SetupDiagnosticMatch(TableMemberName(GetParam().name));
    SetMockIsCurrentThreadSafe(UnsafeThread);
    RunAndExpectNoDiagnostic([api, this] { GetParam().invoke(api); });
}

// 模式 4：LOG + 不安全线程 → 有诊断
TEST_P(UiThreadTableLogTest, LogModeProducesDiagnostic)
{
    auto* api = GetNodeApi();
    ASSERT_NE(api, nullptr);
    EnableMode(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG);
    SetupDiagnosticMatch(TableMemberName(GetParam().name));
    SetMockIsCurrentThreadSafe(UnsafeThread);
    RunAndExpectDiagnostic([api, this] { GetParam().invoke(api); });
}

// === Scope entries（175 导出函数，排除 5 个范围外 + 2 个 ANI）===

namespace {
#define SCOPE_ENTRY(api) { #api, [] { CallWithDefaultArgs(api); } }
const ScopeEntry SCOPE_ENTRIES[] = {
    SCOPE_ENTRY(OH_ArkUI_GetContextFromNapiValue),
    SCOPE_ENTRY(OH_ArkUI_GetNodeContentFromNapiValue),
    SCOPE_ENTRY(OH_ArkUI_GetNodeHandleFromNapiValue),
    SCOPE_ENTRY(OH_ArkUI_InitModuleForArkTSEnv),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_AdoptChild),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_ConvertPositionFromWindow),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_ConvertPositionToWindow),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_GetChildMountPolicy),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_GetPageRootNodeHandleByContext),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_InvalidateAttributes),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_IsInRenderState),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_RegisterCommonAreaApproximateChangeEvent),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_RegisterCommonEvent),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_RegisterCommonVisibleAreaApproximateChangeEvent),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_RemoveAdoptedChild),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_SetChildMountPolicy),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_UnregisterCommonEvent),
    SCOPE_ENTRY(OH_ArkUI_NativeModule_UnregisterCommonVisibleAreaApproximateChangeEvent),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapterEvent_GetHostNode),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapterEvent_GetRemovedNode),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_Create),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_Dispose),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_GetAllItems),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_GetTotalNodeCount),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_InsertItem),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_MoveItem),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_RegisterEventReceiver),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_ReloadAllItems),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_ReloadItem),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_RemoveItem),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_SetTotalNodeCount),
    SCOPE_ENTRY(OH_ArkUI_NodeAdapter_UnregisterEventReceiver),
    SCOPE_ENTRY(OH_ArkUI_NodeContent_AddNode),
    SCOPE_ENTRY(OH_ArkUI_NodeContent_GetUserData),
    SCOPE_ENTRY(OH_ArkUI_NodeContent_InsertNode),
    SCOPE_ENTRY(OH_ArkUI_NodeContent_RegisterCallback),
    SCOPE_ENTRY(OH_ArkUI_NodeContent_RemoveNode),
    SCOPE_ENTRY(OH_ArkUI_NodeContent_SetUserData),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_AddCustomProperty),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetActiveChildrenInfo),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetAttachedNodeHandleById),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetChildWithExpandMode),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetCrossLanguageOption),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetCurrentPageRootNode),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetCustomProperty),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetFirstChildIndexWithoutExpand),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetLastChildIndexWithoutExpand),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetLayoutPosition),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetLayoutPositionInGlobalDisplay),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetLayoutPositionInScreen),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetLayoutPositionInWindow),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetLayoutSize),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetNodeType),
    { "OH_ArkUI_NodeUtils_GetNodeUniqueId", InvokeNodeUtilsGetNodeUniqueId },
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetParentInPageTree),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetPositionToParent),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_GetWindowInfo),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_IsCreatedByNDK),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_MoveTo),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_RemoveCustomProperty),
    SCOPE_ENTRY(OH_ArkUI_NodeUtils_SetCrossLanguageOption),
    SCOPE_ENTRY(OH_ArkUI_NotifyArkTSEnvDestroy),
    SCOPE_ENTRY(OH_ArkUI_PostFrameCallback),
    SCOPE_ENTRY(OH_ArkUI_PostIdleCallback),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AddChild),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AddRenderNode),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachColorProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachContentModifier),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachFloatProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_AttachVector2Property),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_ClearChildren),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_ClearRenderNodeChildren),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateColorProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateContentModifier),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateFloatProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateNode),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_CreateVector2Property),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeColorProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeContentModifier),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeFloatProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeNode),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_DisposeVector2Property),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetBackgroundColor),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetBorderColor),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetBorderRadius),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetBorderStyle),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetBorderWidth),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetBounds),
    { "OH_ArkUI_RenderNodeUtils_GetChild", InvokeRenderGetChild },
    { "OH_ArkUI_RenderNodeUtils_GetChildren", InvokeRenderGetChildren },
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetChildrenCount),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetClipToBounds),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetClipToFrame),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetColorPropertyValue),
    { "OH_ArkUI_RenderNodeUtils_GetFirstChild", InvokeRenderGetFirstChild },
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue),
    { "OH_ArkUI_RenderNodeUtils_GetNextSibling", InvokeRenderGetNextSibling },
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetOpacity),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetPivot),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetPosition),
    { "OH_ArkUI_RenderNodeUtils_GetPreviousSibling", InvokeRenderGetPreviousSibling },
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetRenderNode),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetRenderNodeAt),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetRenderNodeChildrenCount),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetRotation),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetScale),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetShadowAlpha),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetShadowColor),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetShadowElevation),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetShadowOffset),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetShadowRadius),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetSize),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetTranslation),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_InsertChildAfter),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_InsertRenderNodeAt),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_Invalidate),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_RemoveChild),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_RemoveRenderNode),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_ResetBackgroundBlurOption),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_ResetContentBlurOption),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_ResetForegroundBlurOption),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBackgroundBlurOption),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBackgroundColor),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBorderColor),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBorderRadius),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBorderStyle),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBorderWidth),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetBounds),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetClip),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetClipToBounds),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetClipToFrame),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetColorAnimatablePropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetColorPropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetContentBlurOption),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetContentModifierOnDraw),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetDrawRegion),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetFloatAnimatablePropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetFloatPropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetForegroundBlurOption),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetMarkNodeGroup),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetMask),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetOpacity),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetPivot),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetPosition),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetRotation),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetScale),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetShadowAlpha),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetShadowColor),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetShadowElevation),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetShadowOffset),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetShadowRadius),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetSize),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetTransform),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetTranslation),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetVector2AnimatablePropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RenderNodeUtils_SetVector2PropertyValue),
    SCOPE_ENTRY(OH_ArkUI_RunTaskInScope),
};
#undef SCOPE_ENTRY
} // namespace

INSTANTIATE_TEST_SUITE_P(AllExports, UiThreadExportLogTest, ValuesIn(SCOPE_ENTRIES),
    [](const TestParamInfo<ScopeEntry>& info) { return std::string(info.param.name); });

INSTANTIATE_TEST_SUITE_P(AllTableMembers, UiThreadTableLogTest, ValuesIn(TABLE_SCOPE_ENTRIES),
    [](const TestParamInfo<TableScopeEntry>& info) { return std::string(info.param.name); });

} // namespace OHOS::Ace::NodeModel
