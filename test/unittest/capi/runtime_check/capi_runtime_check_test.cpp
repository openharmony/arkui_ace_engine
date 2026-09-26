#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <type_traits>

#include "gtest/gtest.h"
#include "base/log/log_wrapper.h"
#include "core/common/ace_application_info.h"

// Keep the singleton implementation private to production. Include it once here
// so each test can use a fresh local manager without a production reset API.
#include "interfaces/native/node/config_manager.cpp"

#include "interfaces/native/native_interface.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"
#include "test/mock/frameworks/base/log/mock_log_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NodeModel {

using ConfigManager::RuntimeCheckManager;

class RuntimeCheckApiTest : public Test {};

HWTEST_F(RuntimeCheckApiTest, RuntimeCheckEnumValues, TestSize.Level1)
{
    EXPECT_EQ(OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD, 0);
    EXPECT_EQ(OH_ARKUI_NATIVEMODULE_CHECK_TYPE_NODE_DISPOSED, 1);
    EXPECT_EQ(static_cast<uint32_t>(CheckType::UI_THREAD), OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD);
    EXPECT_EQ(static_cast<uint32_t>(CheckType::NODE_DISPOSED), OH_ARKUI_NATIVEMODULE_CHECK_TYPE_NODE_DISPOSED);
    EXPECT_EQ(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED, 0);
    EXPECT_EQ(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG, 1);
    EXPECT_EQ(OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH, 2);
}

HWTEST_F(RuntimeCheckApiTest, RuntimeCheckApiSignatureIsAvailable, TestSize.Level1)
{
    using SetMode = ArkUI_ErrorCode (*)(OH_ArkUI_NativeModule_RuntimeCheckType, OH_ArkUI_NativeModule_RuntimeCheckMode);
    static_assert(std::is_same_v<decltype(&OH_ArkUI_NativeModule_SetRuntimeCheckMode), SetMode>);
}

HWTEST_F(RuntimeCheckApiTest, BasicApiThreadPredicateFieldExists, TestSize.Level1)
{
    ArkUIBasicAPI api {};
    EXPECT_EQ(api.isCurrentThreadSafe, nullptr);
}

void SetMockBasicAPIProvider(const ArkUIBasicAPI* (*provider)());
void ResetMockBasicAPIProvider();

namespace {
constexpr auto BACKEND_WAIT_TIMEOUT = std::chrono::seconds(5);

struct RuntimeCheckBridge {
    ArkUIBasicAPI api {};
    std::atomic<bool> available { true };
    std::atomic<bool> threadSafe { true };
    std::atomic<bool> debugReady { true };
    std::atomic<int> backendQueries { 0 };
    std::atomic<int> threadQueries { 0 };
    std::atomic<int> readyQueries { 0 };
    std::atomic<int> debugQueries { 0 };
    std::atomic<bool> blockNextBackendQuery { false };
    std::atomic<bool> blockNextDebugQuery { false };
    std::mutex pauseMutex;
    std::condition_variable pauseCondition;
    bool queryBlocked = false;
    bool releaseQuery = false;
    bool waitTimedOut = false;
};

// Installed before worker threads start and cleared only after they have joined.
RuntimeCheckBridge* g_runtimeCheckBridge = nullptr;

void PauseQuery()
{
    auto& bridge = *g_runtimeCheckBridge;
    std::unique_lock<std::mutex> lock(bridge.pauseMutex);
    bridge.queryBlocked = true;
    bridge.pauseCondition.notify_all();
    if (!bridge.pauseCondition.wait_for(lock, BACKEND_WAIT_TIMEOUT, [&bridge]() {
        return bridge.releaseQuery;
    })) {
        bridge.waitTimedOut = true;
    }
}

ArkUI_Bool RuntimeThreadSafe()
{
    g_runtimeCheckBridge->threadQueries.fetch_add(1);
    return g_runtimeCheckBridge->threadSafe.load() ? 1 : 0;
}

ArkUI_Bool RuntimeDebugReady()
{
    g_runtimeCheckBridge->readyQueries.fetch_add(1);
    return g_runtimeCheckBridge->debugReady.load() ? 1 : 0;
}

ArkUI_Bool RuntimeDebugValue()
{
    auto& bridge = *g_runtimeCheckBridge;
    bridge.debugQueries.fetch_add(1);
    const auto value = AceApplicationInfo::GetInstance().IsDebugForParallel() ? 1 : 0;
    if (bridge.blockNextDebugQuery.exchange(false)) {
        PauseQuery();
    }
    return value;
}

ArkUI_Bool InitializeAfterDebugValueRead()
{
    const auto value = RuntimeDebugValue();
    // Model initialization completing after the value was read but before the getter returns.
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    g_runtimeCheckBridge->debugReady.store(true);
    return value;
}

const ArkUIBasicAPI* RuntimeBasicAPI()
{
    auto& bridge = *g_runtimeCheckBridge;
    bridge.backendQueries.fetch_add(1);
    if (bridge.blockNextBackendQuery.exchange(false)) {
        PauseQuery();
    }
    return bridge.available.load() ? &bridge.api : nullptr;
}
class RuntimeCheckBehaviorTest : public Test {
public:
    void SetUp() override
    {
        previousDebug_ = AceApplicationInfo::GetInstance().IsDebugForParallel();
        AceApplicationInfo::GetInstance().SetDebugForParallel(false);
        bridge_.api.isCurrentThreadSafe = RuntimeThreadSafe;
        bridge_.api.isDebugForParallel = RuntimeDebugValue;
        bridge_.api.isDebugForParallelSet = RuntimeDebugReady;
        g_runtimeCheckBridge = &bridge_;
        SetMockBasicAPIProvider(RuntimeBasicAPI);
        ResetPrintLogCount();
        ResetDiagnosticLog();
    }

    void TearDown() override
    {
        ResetMockBasicAPIProvider();
        g_runtimeCheckBridge = nullptr;
        AceApplicationInfo::GetInstance().SetDebugForParallel(previousDebug_);
    }

    void SetThreadSafe(bool isSafe)
    {
        bridge_.threadSafe.store(isSafe);
    }

    bool WaitForBlockedQuery()
    {
        std::unique_lock<std::mutex> lock(bridge_.pauseMutex);
        return bridge_.pauseCondition.wait_for(lock, BACKEND_WAIT_TIMEOUT, [this]() {
            return bridge_.queryBlocked;
        });
    }

    void ReleaseBlockedQuery()
    {
        std::lock_guard<std::mutex> lock(bridge_.pauseMutex);
        bridge_.releaseQuery = true;
        bridge_.pauseCondition.notify_all();
    }

    RuntimeCheckManager manager_;
    RuntimeCheckBridge bridge_;
    bool previousDebug_ = false;
};

HWTEST_F(RuntimeCheckBehaviorTest, ReleaseDefaultsToDisabled, TestSize.Level1)
{
    SetThreadSafe(false);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    manager_.CheckUIThread("ReleaseDefault");
}

HWTEST_F(RuntimeCheckBehaviorTest, DebugDefaultsToCrash, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
}

HWTEST_F(RuntimeCheckBehaviorTest, DebugSafeThreadDoesNotCrash, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    manager_.CheckUIThread("DebugSafe");
}

HWTEST_F(RuntimeCheckBehaviorTest, DebugIsQueriedUntilInitialization, TestSize.Level1)
{
    bridge_.debugReady.store(false);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    AceApplicationInfo::GetInstance().SetDebugForParallel(false);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(bridge_.backendQueries.load(), 3);
    EXPECT_EQ(bridge_.readyQueries.load(), 3);
    EXPECT_EQ(bridge_.debugQueries.load(), 3);

    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    bridge_.debugReady.store(true);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    EXPECT_EQ(bridge_.readyQueries.load(), 4);
    EXPECT_EQ(bridge_.debugQueries.load(), 4);
}

HWTEST_F(RuntimeCheckBehaviorTest, InitializedDefaultsSkipFurtherDebugQueries, TestSize.Level1)
{
    for (bool debug : { false, true }) {
        RuntimeCheckManager manager;
        bridge_.debugReady.store(true);
        AceApplicationInfo::GetInstance().SetDebugForParallel(debug);
        const auto expected = debug ? CheckMode::CRASH : CheckMode::DISABLED;
        const auto queriesBefore = bridge_.debugQueries.load();
        EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, expected);
        EXPECT_EQ(bridge_.debugQueries.load(), queriesBefore + 1);
        const auto backendQueries = bridge_.backendQueries.load();
        const auto readyQueries = bridge_.readyQueries.load();
        const auto debugQueries = bridge_.debugQueries.load();

        AceApplicationInfo::GetInstance().SetDebugForParallel(!debug);
        bridge_.debugReady.store(false);
        for (int i = 0; i < 3; ++i) {
            EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, expected);
        }
        EXPECT_EQ(bridge_.backendQueries.load(), backendQueries);
        EXPECT_EQ(bridge_.readyQueries.load(), readyQueries);
        EXPECT_EQ(bridge_.debugQueries.load(), debugQueries);
    }
}

HWTEST_F(RuntimeCheckBehaviorTest, InitializationDuringDebugReadDoesNotCacheEarlyValue, TestSize.Level1)
{
    bridge_.debugReady.store(false);
    bridge_.api.isDebugForParallel = InitializeAfterDebugValueRead;
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    EXPECT_EQ(bridge_.debugQueries.load(), 2);
}

HWTEST_F(RuntimeCheckBehaviorTest, ExplicitModesSkipBackendAndDebugQueries, TestSize.Level1)
{
    for (auto mode : { CheckMode::DISABLED, CheckMode::LOG, CheckMode::CRASH }) {
        RuntimeCheckManager manager;
        ASSERT_TRUE(manager.SetRuntimeCheckMode(0, static_cast<int32_t>(mode)));
        const auto backendQueries = bridge_.backendQueries.load();
        const auto readyQueries = bridge_.readyQueries.load();
        const auto debugQueries = bridge_.debugQueries.load();
        for (bool ready : { false, true }) {
            bridge_.debugReady.store(ready);
            for (bool debug : { false, true }) {
                AceApplicationInfo::GetInstance().SetDebugForParallel(debug);
                EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, mode);
            }
        }
        EXPECT_EQ(bridge_.backendQueries.load(), backendQueries);
        EXPECT_EQ(bridge_.readyQueries.load(), readyQueries);
        EXPECT_EQ(bridge_.debugQueries.load(), debugQueries);
    }
}

HWTEST_F(RuntimeCheckBehaviorTest, UnavailableBackendDoesNotFreezeDefault, TestSize.Level1)
{
    bridge_.available.store(false);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(bridge_.backendQueries.load(), 2);
    EXPECT_EQ(bridge_.readyQueries.load(), 0);
    EXPECT_EQ(bridge_.debugQueries.load(), 0);

    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    bridge_.available.store(true);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    EXPECT_EQ(bridge_.readyQueries.load(), 1);
    EXPECT_EQ(bridge_.debugQueries.load(), 1);
}

HWTEST_F(RuntimeCheckBehaviorTest, MissingDebugGetterDoesNotFreezeDefault, TestSize.Level1)
{
    bridge_.api.isDebugForParallel = nullptr;
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(bridge_.backendQueries.load(), 2);
    EXPECT_EQ(bridge_.readyQueries.load(), 0);
    EXPECT_EQ(bridge_.debugQueries.load(), 0);

    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    bridge_.api.isDebugForParallel = RuntimeDebugValue;
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    EXPECT_EQ(bridge_.debugQueries.load(), 1);
}

HWTEST_F(RuntimeCheckBehaviorTest, MissingReadyGetterKeepsDebugQueriesLive, TestSize.Level1)
{
    bridge_.api.isDebugForParallelSet = nullptr;
    for (bool debug : { false, true, false }) {
        AceApplicationInfo::GetInstance().SetDebugForParallel(debug);
        EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, debug ? CheckMode::CRASH : CheckMode::DISABLED);
    }
    EXPECT_EQ(bridge_.backendQueries.load(), 3);
    EXPECT_EQ(bridge_.readyQueries.load(), 0);
    EXPECT_EQ(bridge_.debugQueries.load(), 3);

    bridge_.api.isDebugForParallelSet = RuntimeDebugReady;
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    EXPECT_EQ(bridge_.readyQueries.load(), 1);
    EXPECT_EQ(bridge_.debugQueries.load(), 4);
}

HWTEST_F(RuntimeCheckBehaviorTest, MissingBackendOrThreadPredicateIsSafe, TestSize.Level1)
{
    bridge_.available.store(false);
    EXPECT_TRUE(manager_.IsCurrentThreadSafe());
    bridge_.available.store(true);
    bridge_.api.isCurrentThreadSafe = nullptr;
    EXPECT_TRUE(manager_.IsCurrentThreadSafe());
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::CRASH)));
    manager_.CheckUIThread("MissingThreadPredicate");
    EXPECT_EQ(bridge_.threadQueries.load(), 0);
    EXPECT_EQ(GetDiagnosticLogCount(), 0);
}

HWTEST_F(RuntimeCheckBehaviorTest, ThreadPredicateResultIsRespected, TestSize.Level1)
{
    SetThreadSafe(false);
    EXPECT_FALSE(manager_.IsCurrentThreadSafe());
    SetThreadSafe(true);
    EXPECT_TRUE(manager_.IsCurrentThreadSafe());
    EXPECT_EQ(bridge_.threadQueries.load(), 2);
}

HWTEST_F(RuntimeCheckBehaviorTest, ExplicitModesOverrideBothDefaults, TestSize.Level1)
{
    for (bool debug : { false, true }) {
        RuntimeCheckManager manager;
        AceApplicationInfo::GetInstance().SetDebugForParallel(debug);
        EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, debug ? CheckMode::CRASH : CheckMode::DISABLED);
        for (auto mode : { CheckMode::DISABLED, CheckMode::LOG, CheckMode::CRASH }) {
            ASSERT_TRUE(manager.SetRuntimeCheckMode(0, static_cast<int32_t>(mode)));
            EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, mode);
            EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, mode);
        }
    }
}

HWTEST_F(RuntimeCheckBehaviorTest, ExplicitDisabledSurvivesDebugInitialization, TestSize.Level1)
{
    bridge_.debugReady.store(false);
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::DISABLED)));
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    bridge_.debugReady.store(true);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::DISABLED);
    SetThreadSafe(false);
    manager_.CheckUIThread("ExplicitDisabled");
}

HWTEST_F(RuntimeCheckBehaviorTest, InvalidConfigurationPreservesDebugDefault, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(-1, 0));
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(2, 0));
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(0, -1));
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(0, 3));
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
}

HWTEST_F(RuntimeCheckBehaviorTest, InvalidConfigurationPreservesExplicitMode, TestSize.Level1)
{
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::LOG)));
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::LOG);
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(0, 3));
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(-1, 0));
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::LOG);
}

HWTEST_F(RuntimeCheckBehaviorTest, ExplicitLogOverridesDebugCrashAndEmitsLog, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::LOG)));
    SetThreadSafe(false);
    ResetDiagnosticLog();
    manager_.CheckUIThread("ExplicitLog");
    EXPECT_GT(GetDiagnosticLogCount(), 0);
    const auto* diag = GetLastDiagnosticLog();
    ASSERT_NE(diag, nullptr);
    EXPECT_TRUE(diag->checkName != nullptr && strstr(diag->checkName, "UI_THREAD") != nullptr);
    EXPECT_TRUE(diag->reason != nullptr && strstr(diag->reason, "C API must be called on the UI thread") != nullptr);
}

HWTEST_F(RuntimeCheckBehaviorTest, NullApiNameStillEmitsLog, TestSize.Level1)
{
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::LOG)));
    SetThreadSafe(false);
    ResetDiagnosticLog();
    manager_.CheckUIThread(nullptr);
    EXPECT_GT(GetDiagnosticLogCount(), 0);
}

HWTEST_F(RuntimeCheckBehaviorTest, DisabledAndSafeCallsDoNotLog, TestSize.Level1)
{
    for (bool debug : { false, true }) {
        AceApplicationInfo::GetInstance().SetDebugForParallel(debug);
        SetThreadSafe(true);
        ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::DISABLED)));
        SetThreadSafe(false);
        ResetDiagnosticLog();
        const auto threadQueries = bridge_.threadQueries.load();
        manager_.CheckUIThread("DisabledCall");
        EXPECT_EQ(bridge_.threadQueries.load(), threadQueries);
        EXPECT_EQ(GetDiagnosticLogCount(), 0);
        SetThreadSafe(true);
        for (auto mode : { CheckMode::LOG, CheckMode::CRASH }) {
            ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(mode)));
            ResetDiagnosticLog();
            manager_.CheckUIThread("SafeCall");
            EXPECT_EQ(GetDiagnosticLogCount(), 0);
        }
    }
}

HWTEST_F(RuntimeCheckBehaviorTest, ExplicitCrashOverridesReleaseDefault, TestSize.Level1)
{
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::CRASH)));
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
}

HWTEST_F(RuntimeCheckBehaviorTest, ExplicitConfigurationWinsBeforeDefaultPublication, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    bridge_.blockNextBackendQuery.store(true);
    auto observed = CheckMode::DISABLED;
    std::thread reader([this, &observed]() { observed = manager_.GetEffectiveMode(CheckType::UI_THREAD).mode; });
    const bool blocked = WaitForBlockedQuery();
    bool configured = false;
    if (blocked) {
        configured = manager_.SetRuntimeCheckMode(0, static_cast<int32_t>(CheckMode::LOG));
    }
    ReleaseBlockedQuery();
    reader.join();

    ASSERT_TRUE(blocked);
    ASSERT_FALSE(bridge_.waitTimedOut);
    ASSERT_TRUE(configured);
    EXPECT_EQ(observed, CheckMode::LOG);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::LOG);
}

HWTEST_F(RuntimeCheckBehaviorTest, PublishedDefaultSurvivesDelayedReader, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    bridge_.blockNextBackendQuery.store(true);
    auto observed = CheckMode::DISABLED;
    auto published = CheckMode::DISABLED;
    std::thread reader([this, &observed]() { observed = manager_.GetEffectiveMode(CheckType::UI_THREAD).mode; });
    const bool blocked = WaitForBlockedQuery();
    if (blocked) {
        published = manager_.GetEffectiveMode(CheckType::UI_THREAD).mode;
        AceApplicationInfo::GetInstance().SetDebugForParallel(false);
    }
    ReleaseBlockedQuery();
    reader.join();

    ASSERT_TRUE(blocked);
    ASSERT_FALSE(bridge_.waitTimedOut);
    EXPECT_EQ(published, CheckMode::CRASH);
    EXPECT_EQ(observed, CheckMode::CRASH);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
}

HWTEST_F(RuntimeCheckBehaviorTest, PublishedDefaultOverridesUnreadyReader, TestSize.Level1)
{
    for (bool debug : { false, true }) {
        RuntimeCheckManager manager;
        bridge_.debugReady.store(false);
        AceApplicationInfo::GetInstance().SetDebugForParallel(!debug);
        bridge_.queryBlocked = false;
        bridge_.releaseQuery = false;
        bridge_.blockNextDebugQuery.store(true);
        auto observed = CheckMode::LOG;
        auto published = CheckMode::LOG;
        // Pause after readiness was false and the old debug value was read.
        std::thread reader([&manager, &observed]() { observed = manager.GetEffectiveMode(CheckType::UI_THREAD).mode; });
        const bool blocked = WaitForBlockedQuery();
        if (blocked) {
            AceApplicationInfo::GetInstance().SetDebugForParallel(debug);
            bridge_.debugReady.store(true);
            published = manager.GetEffectiveMode(CheckType::UI_THREAD).mode;
        }
        ReleaseBlockedQuery();
        reader.join();

        ASSERT_TRUE(blocked);
        ASSERT_FALSE(bridge_.waitTimedOut);
        const auto expected = debug ? CheckMode::CRASH : CheckMode::DISABLED;
        EXPECT_EQ(published, expected);
        EXPECT_EQ(observed, expected);
        EXPECT_EQ(manager.GetEffectiveMode(CheckType::UI_THREAD).mode, expected);
    }
}

HWTEST_F(RuntimeCheckBehaviorTest, ConcurrentDefaultReadersShareStableMode, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    constexpr size_t readerCount = 8;
    std::array<CheckMode, readerCount> observed {};
    std::array<std::thread, readerCount> readers;
    std::atomic<bool> start { false };
    for (size_t i = 0; i < readerCount; ++i) {
        readers[i] = std::thread([this, &start, &observed, i]() {
            while (!start.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }
            observed[i] = manager_.GetEffectiveMode(CheckType::UI_THREAD).mode;
        });
    }
    start.store(true, std::memory_order_release);
    for (auto& reader : readers) {
        reader.join();
    }
    for (auto mode : observed) {
        EXPECT_EQ(mode, CheckMode::CRASH);
    }
    const auto debugQueries = bridge_.debugQueries.load();
    AceApplicationInfo::GetInstance().SetDebugForParallel(false);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    EXPECT_EQ(bridge_.debugQueries.load(), debugQueries);
}

HWTEST_F(RuntimeCheckBehaviorTest, ConfigurationPublishesToConcurrentReader, TestSize.Level1)
{
    // The handshake orders each new read after the successful configuration returns.
    // A second reader continuously reads the effective mode while the writer updates it.
    constexpr int iterations = 1000;
    std::atomic<int> published { 0 };
    std::atomic<int> consumed { 0 };
    std::atomic<bool> stop { false };
    std::atomic<int> mismatches { 0 };
    std::thread racingReader([this, &stop]() {
        while (!stop.load(std::memory_order_acquire)) {
            manager_.GetEffectiveMode(CheckType::UI_THREAD);
        }
    });
    std::thread orderedReader([this, &published, &mismatches, &consumed]() {
        for (int i = 1; i <= iterations; ++i) {
            while (published.load(std::memory_order_acquire) != i) {
                std::this_thread::yield();
            }
            if (manager_.GetEffectiveMode(CheckType::UI_THREAD).mode != static_cast<CheckMode>(i % 3)) {
                mismatches.fetch_add(1, std::memory_order_relaxed);
            }
            consumed.store(i, std::memory_order_release);
        }
    });
    for (int i = 1; i <= iterations; ++i) {
        EXPECT_TRUE(manager_.SetRuntimeCheckMode(0, i % 3));
        published.store(i, std::memory_order_release);
        while (consumed.load(std::memory_order_acquire) != i) {
            std::this_thread::yield();
        }
    }
    orderedReader.join();
    stop.store(true, std::memory_order_release);
    racingReader.join();
    EXPECT_EQ(mismatches.load(), 0);
}

HWTEST_F(RuntimeCheckBehaviorTest, CachedDefaultsRetainTheirOrigin, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    for (auto type : { CheckType::UI_THREAD, CheckType::NODE_DISPOSED }) {
        for (int i = 0; i < 3; ++i) {
            const auto effective = manager_.GetEffectiveMode(type);
            EXPECT_EQ(effective.mode, CheckMode::CRASH);
            EXPECT_TRUE(effective.isDefault);
        }
    }
    EXPECT_EQ(bridge_.debugQueries.load(), 1);
    EXPECT_EQ(bridge_.readyQueries.load(), 1);
}

HWTEST_F(RuntimeCheckBehaviorTest, UserConfigurationOverridesOnlyTheSelectedType, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    ASSERT_EQ(manager_.GetEffectiveMode(CheckType::UI_THREAD).mode, CheckMode::CRASH);
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::NODE_DISPOSED), static_cast<int32_t>(CheckMode::DISABLED)));
    const auto disposedMode = manager_.GetEffectiveMode(CheckType::NODE_DISPOSED);
    EXPECT_EQ(disposedMode.mode, CheckMode::DISABLED);
    EXPECT_FALSE(disposedMode.isDefault);
    const auto threadMode = manager_.GetEffectiveMode(CheckType::UI_THREAD);
    EXPECT_EQ(threadMode.mode, CheckMode::CRASH);
    EXPECT_TRUE(threadMode.isDefault);

    ASSERT_TRUE(manager_.SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::UI_THREAD), static_cast<int32_t>(CheckMode::CRASH)));
    EXPECT_FALSE(manager_.GetEffectiveMode(CheckType::UI_THREAD).isDefault);
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::NODE_DISPOSED).mode, CheckMode::DISABLED);
}

HWTEST_F(RuntimeCheckBehaviorTest, CountIsNotAConfigurableCheckType, TestSize.Level1)
{
    const auto count = static_cast<int32_t>(CheckType::COUNT);
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::NODE_DISPOSED), static_cast<int32_t>(CheckMode::LOG)));
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(count, static_cast<int32_t>(CheckMode::DISABLED)));
    EXPECT_FALSE(manager_.SetRuntimeCheckMode(count + 1, static_cast<int32_t>(CheckMode::DISABLED)));
    EXPECT_EQ(manager_.GetEffectiveMode(CheckType::NODE_DISPOSED).mode, CheckMode::LOG);
}

HWTEST_F(RuntimeCheckBehaviorTest, InvalidEffectiveTypeSkipsBackend, TestSize.Level1)
{
    for (auto type : { CheckType::COUNT, static_cast<CheckType>(-1) }) {
        const auto effective = manager_.GetEffectiveMode(type);
        EXPECT_EQ(effective.mode, CheckMode::DISABLED);
        EXPECT_FALSE(effective.isDefault);
    }
    EXPECT_EQ(bridge_.backendQueries.load(), 0);
}

HWTEST_F(RuntimeCheckBehaviorTest, DisabledDisposedNodeCheckDoesNotLog, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetDebugForParallel(true);
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::NODE_DISPOSED), static_cast<int32_t>(CheckMode::DISABLED)));
    ResetDiagnosticLog();
    ArkUI_Node node;
    node.magic = ARKUI_NODE_MAGIC_INVALID;
    manager_.CheckNodeDisposed(&node, "DisabledDisposedNode", nullptr);
    EXPECT_EQ(GetDiagnosticLogCount(), 0);
}

HWTEST_F(RuntimeCheckBehaviorTest, OnlyDisposedNodesEmitLogs, TestSize.Level1)
{
    ASSERT_TRUE(manager_.SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::NODE_DISPOSED), static_cast<int32_t>(CheckMode::LOG)));
    ResetDiagnosticLog();
    ArkUI_Node node;
    node.magic = ARKUI_NODE_MAGIC_VALID;
    manager_.CheckNodeDisposed(&node, "ValidNode", nullptr);
    manager_.CheckNodeDisposed(nullptr, "NullNode", nullptr);
    EXPECT_EQ(GetDiagnosticLogCount(), 0);

    node.magic = ARKUI_NODE_MAGIC_INVALID;
    manager_.CheckNodeDisposed(&node, "DisposedNode", nullptr);
    EXPECT_GT(GetDiagnosticLogCount(), 0);
    const auto* diag = GetLastDiagnosticLog();
    ASSERT_NE(diag, nullptr);
    EXPECT_TRUE(diag->checkName != nullptr && strstr(diag->checkName, "NODE_DISPOSED") != nullptr);
}

HWTEST_F(RuntimeCheckBehaviorTest, NamespaceFunctionsForwardToThePrivateManager, TestSize.Level1)
{
    EXPECT_TRUE(ConfigManager::SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::UI_THREAD), static_cast<int32_t>(CheckMode::LOG)));
    EXPECT_TRUE(ConfigManager::SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::NODE_DISPOSED), static_cast<int32_t>(CheckMode::LOG)));
    SetThreadSafe(false);
    ResetDiagnosticLog();
    ConfigManager::CheckUIThread("NamespaceThreadCheck");
    EXPECT_GT(GetDiagnosticLogCount(), 0);

    ArkUI_Node node;
    node.magic = ARKUI_NODE_MAGIC_INVALID;
    ConfigManager::CheckNodeDisposed(&node, "NamespaceDisposedCheck", "Disposed argument");
    EXPECT_GT(GetDiagnosticLogCount(), 1);
    const auto* diag = GetLastDiagnosticLog();
    ASSERT_NE(diag, nullptr);
    EXPECT_TRUE(diag->checkName != nullptr && strstr(diag->checkName, "NODE_DISPOSED") != nullptr);
    EXPECT_TRUE(diag->reason != nullptr && strstr(diag->reason, "Disposed argument") != nullptr);

    SetThreadSafe(true);
    EXPECT_TRUE(ConfigManager::SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::UI_THREAD), static_cast<int32_t>(CheckMode::DISABLED)));
    EXPECT_TRUE(ConfigManager::SetRuntimeCheckMode(
        static_cast<int32_t>(CheckType::NODE_DISPOSED), static_cast<int32_t>(CheckMode::DISABLED)));
}

} // namespace
} // namespace OHOS::Ace::NodeModel
