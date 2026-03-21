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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "adapter/ohos/capability/feature_config/extra_modules/extra_modules_manager_impl.h"
#undef private
#undef protected

#include <dlfcn.h>
#include <fstream>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
void* OpenTestDynamicHandle()
{
    return dlopen(nullptr, RTLD_LAZY);
}

std::string FindAvailableSymbol(void* handle)
{
    if (handle == nullptr) {
        return "";
    }
    std::vector<std::string> candidates = { "dlopen", "dlclose", "dlsym", "printf", "malloc", "free" };
    for (const auto& symbolName : candidates) {
        dlerror();
        auto* symbol = dlsym(handle, symbolName.c_str());
        if (symbol != nullptr) {
            return symbolName;
        }
    }
    return "";
}
} // namespace

class ExtraModulesManagerTest : public testing::Test {
public:
    void SetUp() override
    {
        auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
        manager.moduleCache_.clear();
        manager.initialized_ = false;
    }

    void TearDown() override
    {
        auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
        manager.moduleCache_.clear();
        manager.initialized_ = false;
    }
};

/**
 * @tc.name: ErrCodeToString001
 * @tc.desc: Verify the completeness of error code to string mapping.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, ErrCodeToString001, TestSize.Level1)
{
    EXPECT_STREQ(ErrCodeToString(ErrCode::SUCCESS), "Success");
    EXPECT_STREQ(ErrCodeToString(ErrCode::NOT_INITIALIZED), "Not initialized");
    EXPECT_STREQ(ErrCodeToString(ErrCode::CONFIG_FILE_NOT_FOUND), "Config file not found");
    EXPECT_STREQ(ErrCodeToString(ErrCode::CONFIG_PARSE_FAILED), "Config parse failed");
    EXPECT_STREQ(ErrCodeToString(ErrCode::FEATURE_NOT_FOUND), "Feature not found");
    EXPECT_STREQ(ErrCodeToString(ErrCode::CAPABILITY_NOT_FOUND), "Capability not found");
    EXPECT_STREQ(ErrCodeToString(ErrCode::MODULE_LOAD_FAILED), "Module load failed");
    EXPECT_STREQ(ErrCodeToString(ErrCode::SYMBOL_NOT_FOUND), "Symbol not found");
    EXPECT_STREQ(ErrCodeToString(ErrCode::MODULE_NOT_LOADED), "Module not loaded");
    EXPECT_STREQ(ErrCodeToString(ErrCode::INVALID_STATE), "Invalid state");
    EXPECT_STREQ(ErrCodeToString(ErrCode::ALREADY_INITIALIZED), "Already initialized");
    EXPECT_STREQ(ErrCodeToString(static_cast<ErrCode>(999)), "Unknown error");
}

/**
 * @tc.name: BuildLibraryPath001
 * @tc.desc: Verify SO path concatenation.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, BuildLibraryPath001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto result = manager.BuildLibraryPath("libexample.z.so");
#if defined(__aarch64__) || defined(__x86_64__)
    EXPECT_EQ(result, "/system/lib64/libexample.z.so");
#else
    EXPECT_EQ(result, "/system/lib/libexample.z.so");
#endif
}

/**
 * @tc.name: ParseConfigFile001
 * @tc.desc: Return CONFIG_FILE_NOT_FOUND when configuration file does not exist.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, ParseConfigFile001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto result = manager.ParseConfigFile("/tmp/extra_modules_manager_not_exist.json");
    EXPECT_EQ(result, ErrCode::CONFIG_FILE_NOT_FOUND);
}

/**
 * @tc.name: LoadModule001
 * @tc.desc: Module load failure branch.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, LoadModule001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    ModuleHolder holder;
    holder.moduleName = "lib_not_exist_for_extra_modules_manager_test.z.so";
    auto result = manager.LoadModule(holder);
    EXPECT_EQ(result, ErrCode::MODULE_LOAD_FAILED);
    EXPECT_EQ(holder.moduleHandle, nullptr);
}

/**
 * @tc.name: GetSymbol001
 * @tc.desc: GetSymbol parameter validation branch.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetSymbol001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    void* symbol = reinterpret_cast<void*>(0x1);

    auto result = manager.GetSymbol(nullptr, "printf", &symbol);
    EXPECT_EQ(result, ErrCode::INVALID_STATE);

    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);
    result = manager.GetSymbol(handle, "printf", nullptr);
    EXPECT_EQ(result, ErrCode::INVALID_STATE);
    dlclose(handle);
}

/**
 * @tc.name: GetSymbol002
 * @tc.desc: Return SYMBOL_NOT_FOUND when symbol does not exist.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetSymbol002, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    void* symbol = nullptr;
    auto result = manager.GetSymbol(handle, "__symbol_not_exist_for_extra_modules_test__", &symbol);
    EXPECT_EQ(result, ErrCode::SYMBOL_NOT_FOUND);
    EXPECT_EQ(symbol, nullptr);
    dlclose(handle);
}

/**
 * @tc.name: GetSymbol003
 * @tc.desc: Return SUCCESS when symbol exists.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetSymbol003, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    auto symbolName = FindAvailableSymbol(handle);
    if (symbolName.empty()) {
        dlclose(handle);
        GTEST_SKIP() << "No available symbol found in process handle.";
    }

    void* symbol = nullptr;
    auto result = manager.GetSymbol(handle, symbolName, &symbol);
    EXPECT_EQ(result, ErrCode::SUCCESS);
    EXPECT_NE(symbol, nullptr);
    dlclose(handle);
}

/**
 * @tc.name: GetCapability001
 * @tc.desc: GetCapability parameter and basic state branches.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetCapability001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    void* outFuncPtr = reinterpret_cast<void*>(0x1);
    auto result = manager.GetCapability("click_sound_effect", "InteractiveSoundEffects", nullptr);
    EXPECT_EQ(result, ErrCode::INVALID_STATE);

    result = manager.GetCapability("click_sound_effect", "InteractiveSoundEffects", &outFuncPtr);
    EXPECT_EQ(result, ErrCode::NOT_INITIALIZED);
    EXPECT_EQ(outFuncPtr, nullptr);

    manager.initialized_ = true;
    result = manager.GetCapability("click_sound_effect", "InteractiveSoundEffects", &outFuncPtr);
    EXPECT_EQ(result, ErrCode::FEATURE_NOT_FOUND);

    ModuleHolder holder;
    holder.moduleName = "libtest.z.so";
    holder.capabilities["AnotherCapability"] = nullptr;
    manager.moduleCache_["click_sound_effect"] = std::move(holder);
    result = manager.GetCapability("click_sound_effect", "InteractiveSoundEffects", &outFuncPtr);
    EXPECT_EQ(result, ErrCode::CAPABILITY_NOT_FOUND);
}

/**
 * @tc.name: GetCapability002
 * @tc.desc: Return success directly when capability is already cached.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetCapability002, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    manager.initialized_ = true;
    ModuleHolder holder;
    holder.moduleName = "libnotused.z.so";
    holder.moduleHandle = handle;
    auto* cached = reinterpret_cast<void*>(0x1234);
    holder.capabilities["CachedCapability"] = cached;
    manager.moduleCache_["feature"] = std::move(holder);

    void* outFuncPtr = nullptr;
    auto result = manager.GetCapability("feature", "CachedCapability", &outFuncPtr);
    EXPECT_EQ(result, ErrCode::SUCCESS);
    EXPECT_EQ(outFuncPtr, cached);
}

/**
 * @tc.name: GetCapability003
 * @tc.desc: Return MODULE_LOAD_FAILED when module is not loaded and loading fails.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetCapability003, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    manager.initialized_ = true;

    ModuleHolder holder;
    holder.moduleName = "lib_not_exist_for_extra_modules_capability_test.z.so";
    holder.capabilities["TargetCapability"] = nullptr;
    manager.moduleCache_["feature"] = std::move(holder);

    void* outFuncPtr = nullptr;
    auto result = manager.GetCapability("feature", "TargetCapability", &outFuncPtr);
    EXPECT_EQ(result, ErrCode::MODULE_LOAD_FAILED);
    EXPECT_EQ(outFuncPtr, nullptr);
}

/**
 * @tc.name: GetCapability004
 * @tc.desc: Return SYMBOL_NOT_FOUND when module is loaded but symbol is missing.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetCapability004, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    manager.initialized_ = true;
    ModuleHolder holder;
    holder.moduleName = "libnotused.z.so";
    holder.moduleHandle = handle;
    holder.capabilities["__cap_not_exist_for_test__"] = nullptr;
    manager.moduleCache_["feature"] = std::move(holder);

    void* outFuncPtr = nullptr;
    auto result = manager.GetCapability("feature", "__cap_not_exist_for_test__", &outFuncPtr);
    EXPECT_EQ(result, ErrCode::SYMBOL_NOT_FOUND);
    EXPECT_EQ(outFuncPtr, nullptr);
}

/**
 * @tc.name: GetCapability005
 * @tc.desc: Return SUCCESS and cache the symbol when module is loaded and symbol exists.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, GetCapability005, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    auto symbolName = FindAvailableSymbol(handle);
    if (symbolName.empty()) {
        dlclose(handle);
        GTEST_SKIP() << "No available symbol found in process handle.";
    }

    manager.initialized_ = true;
    ModuleHolder holder;
    holder.moduleName = "libnotused.z.so";
    holder.moduleHandle = handle;
    holder.capabilities[symbolName] = nullptr;
    manager.moduleCache_["feature"] = std::move(holder);

    void* outFuncPtr = nullptr;
    auto result = manager.GetCapability("feature", symbolName, &outFuncPtr);
    EXPECT_EQ(result, ErrCode::SUCCESS);
    EXPECT_NE(outFuncPtr, nullptr);
    EXPECT_EQ(manager.moduleCache_["feature"].capabilities[symbolName], outFuncPtr);
}

/**
 * @tc.name: UnloadModule001
 * @tc.desc: Feature not found and not loaded branches.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, UnloadModule001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto result = manager.UnloadModule("click_sound_effect");
    EXPECT_EQ(result, ErrCode::FEATURE_NOT_FOUND);

    ModuleHolder holder;
    holder.moduleName = "libtest.z.so";
    holder.capabilities["InteractiveSoundEffects"] = nullptr;
    manager.moduleCache_["click_sound_effect"] = std::move(holder);
    result = manager.UnloadModule("click_sound_effect");
    EXPECT_EQ(result, ErrCode::MODULE_NOT_LOADED);
}

/**
 * @tc.name: UnloadModule002
 * @tc.desc: Successfully unload loaded module and clear capability cache.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, UnloadModule002, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    ModuleHolder holder;
    holder.moduleName = "libtest.z.so";
    holder.moduleHandle = handle;
    holder.capabilities["InteractiveSoundEffects"] = reinterpret_cast<void*>(0x4321);
    manager.moduleCache_["click_sound_effect"] = std::move(holder);

    auto result = manager.UnloadModule("click_sound_effect");
    EXPECT_EQ(result, ErrCode::SUCCESS);
    EXPECT_EQ(manager.moduleCache_["click_sound_effect"].moduleHandle, nullptr);
    EXPECT_EQ(manager.moduleCache_["click_sound_effect"].capabilities["InteractiveSoundEffects"], nullptr);
}

/**
 * @tc.name: Destroy001
 * @tc.desc: Return NOT_INITIALIZED when Destroy is called without initialization.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, Destroy001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto result = manager.Destroy();
    EXPECT_EQ(result, ErrCode::NOT_INITIALIZED);
}

/**
 * @tc.name: Destroy002
 * @tc.desc: After initialization, Destroy clears cache and resets state.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, Destroy002, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto handle = OpenTestDynamicHandle();
    ASSERT_NE(handle, nullptr);

    manager.initialized_ = true;
    ModuleHolder loadedHolder;
    loadedHolder.moduleName = "libloaded.z.so";
    loadedHolder.moduleHandle = handle;
    loadedHolder.capabilities["LoadedCap"] = reinterpret_cast<void*>(0x1000);
    manager.moduleCache_["loaded"] = std::move(loadedHolder);

    ModuleHolder unloadedHolder;
    unloadedHolder.moduleName = "libunloaded.z.so";
    unloadedHolder.capabilities["UnloadedCap"] = nullptr;
    manager.moduleCache_["unloaded"] = std::move(unloadedHolder);

    auto result = manager.Destroy();
    EXPECT_EQ(result, ErrCode::SUCCESS);
    EXPECT_TRUE(manager.moduleCache_.empty());
    EXPECT_FALSE(manager.initialized_);
}

/**
 * @tc.name: Init001
 * @tc.desc: Return ALREADY_INITIALIZED when Init is called after initialization.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, Init001, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    manager.initialized_ = true;
    auto result = manager.Init();
    EXPECT_EQ(result, ErrCode::ALREADY_INITIALIZED);
}

/**
 * @tc.name: Init002
 * @tc.desc: Go through ParseConfigFile path when not initialized.
 * @tc.type: FUNC
 */
HWTEST_F(ExtraModulesManagerTest, Init002, TestSize.Level1)
{
    auto& manager = static_cast<ExtraModulesManagerImpl&>(ExtraModulesManager::GetInstance());
    auto result = manager.Init();
    EXPECT_NE(result, ErrCode::ALREADY_INITIALIZED);
    if (result == ErrCode::SUCCESS) {
        EXPECT_TRUE(manager.initialized_);
    } else {
        EXPECT_FALSE(manager.initialized_);
    }
}
} // namespace OHOS::Ace
