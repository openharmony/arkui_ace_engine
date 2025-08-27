/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <thread>
#define private public
#define protected public
#include "core/common/color_inverter.h"
#undef private
#undef protected
using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
constexpr char BUTTON_TAG[] = "Button";
} // namespace

class ColorInverterTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        ColorInverter::GetInstance().colorInvertFuncManagerMap_.clear();
    }
    static void TearDownTestCase()
    {
        ColorInverter::GetInstance().colorInvertFuncManagerMap_.clear();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: ColorInverterTest001
 * @tc.desc: ColorInvertFuncManager::Create
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ColorInvertFuncManager
     * @tc.expected: Create ColorInvertFuncManager Success
     */
    auto manager = ColorInvertFuncManager::Create();
    EXPECT_NE(manager, nullptr);
}

/**
 * @tc.name: ColorInverterTest002
 * @tc.desc: ColorInvertFuncManager::SetInvertFunc
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ColorInvertFuncManager
     * @tc.expected: Create ColorInvertFuncManager Success
     */
    auto manager = ColorInvertFuncManager::Create();
    EXPECT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. SetInvertFunc
     * @tc.expected: SetInvertFunc Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    manager->SetInvertFunc(BUTTON_TAG, std::move(func));
    auto funcMap = manager->colorInvertFuncMap_;
    EXPECT_NE(funcMap.size(), 0);
    auto iter = funcMap.find(BUTTON_TAG);
    EXPECT_NE(iter, funcMap.end());
    auto invertFunc = iter->second;
    EXPECT_EQ(invertFunc(0), 0);
}

/**
 * @tc.name: ColorInverterTest003
 * @tc.desc: ColorInvertFuncManager::DeleteInvertFunc
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ColorInvertFuncManager
     * @tc.expected: Create ColorInvertFuncManager Success
     */
    auto manager = ColorInvertFuncManager::Create();
    EXPECT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. SetInvertFunc
     * @tc.expected: SetInvertFunc Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    manager->SetInvertFunc(BUTTON_TAG, std::move(func));
    EXPECT_NE(manager->colorInvertFuncMap_.size(), 0);

    /**
     * @tc.steps: step2. DeleteInvertFunc
     * @tc.expected: DeleteInvertFunc Success
     */
    manager->DeleteInvertFunc(BUTTON_TAG);
    EXPECT_EQ(manager->colorInvertFuncMap_.size(), 0);
}

/**
 * @tc.name: ColorInverterTest004
 * @tc.desc: ColorInvertFuncManager::GetInvertFunc
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ColorInvertFuncManager
     * @tc.expected: Create ColorInvertFuncManager Success
     */
    auto manager = ColorInvertFuncManager::Create();
    EXPECT_NE(manager, nullptr);

    /**
     * @tc.steps: step2. SetInvertFunc
     * @tc.expected: SetInvertFunc Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    manager->SetInvertFunc(BUTTON_TAG, std::move(func));
    EXPECT_NE(manager->colorInvertFuncMap_.size(), 0);

    /**
     * @tc.steps: step3. GetInvertFunc
     * @tc.expected: GetInvertFunc Success
     */
    auto invertFunc = manager->GetInvertFunc(BUTTON_TAG);
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);
}

/**
 * @tc.name: ColorInverterTest005
 * @tc.desc: ColorInverter::DefaultInverter
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call DefaultInverter
     * @tc.expected: DefaultInverter Give Back Right Value
     */
    static const uint8_t fullColor = 255;
    Color full = Color::FromRGB(fullColor, fullColor, fullColor);
    Color invertColor = Color::FromRGB(0, 0, 0);
    EXPECT_EQ(ColorInverter::DefaultInverter(invertColor.GetValue()), full.GetValue());
}

/**
 * @tc.name: ColorInverterTest006
 * @tc.desc: ColorInverter::EnableColorInvert
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert
     * @tc.expected: EnableColorInvert Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    ColorInverter::GetInstance().EnableColorInvert(PROCESS_LEVEL_ID, "", std::move(func));
    auto managerMap = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_NE(managerMap.size(), 0);
    auto iter = managerMap.find(PROCESS_LEVEL_ID);
    EXPECT_NE(iter, managerMap.end());
    auto invertFunc = iter->second->GetInvertFunc("");
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);
}

/**
 * @tc.name: ColorInverterTest007
 * @tc.desc: ColorInverter::DisableColorInvert
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert
     * @tc.expected: EnableColorInvert Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    ColorInverter::GetInstance().EnableColorInvert(PROCESS_LEVEL_ID, "", std::move(func));
    auto managerMap = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_NE(managerMap.size(), 0);
    auto iter = managerMap.find(PROCESS_LEVEL_ID);
    EXPECT_NE(iter, managerMap.end());
    auto invertFunc = iter->second->GetInvertFunc("");
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);

    /**
     * @tc.steps: step2. Call DisableColorInvert
     * @tc.expected: DisableColorInvert Success
     */
    ColorInverter::GetInstance().DisableColorInvert(PROCESS_LEVEL_ID, "");
    auto managerMapNew = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_EQ(managerMapNew.size(), 0);
}

/**
 * @tc.name: ColorInverterTest008
 * @tc.desc: ColorInverter::GetInvertFunc
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert
     * @tc.expected: EnableColorInvert Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    ColorInverter::GetInstance().EnableColorInvert(PROCESS_LEVEL_ID, "", std::move(func));
    auto managerMap = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_NE(managerMap.size(), 0);
    auto iter = managerMap.find(PROCESS_LEVEL_ID);
    EXPECT_NE(iter, managerMap.end());
    auto invertFunc = iter->second->GetInvertFunc("");
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);

    /**
     * @tc.steps: step2. Call GetInvertFunc
     * @tc.expected: GetInvertFunc Success
     */
    auto invertFuncCopy = ColorInverter::GetInstance().GetInvertFunc(PROCESS_LEVEL_ID, "");
    EXPECT_NE(invertFuncCopy, nullptr);
    EXPECT_EQ(invertFuncCopy(0), 0);
}

/**
 * @tc.name: ColorInverterTest009
 * @tc.desc: ColorInverter::Invert
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert
     * @tc.expected: EnableColorInvert Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    ColorInverter::GetInstance().EnableColorInvert(PROCESS_LEVEL_ID, "", std::move(func));
    auto managerMap = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_NE(managerMap.size(), 0);
    auto iter = managerMap.find(PROCESS_LEVEL_ID);
    EXPECT_NE(iter, managerMap.end());
    auto invertFunc = iter->second->GetInvertFunc("");
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);

    /**
     * @tc.steps: step2. Call Invert
     * @tc.expected: Invert Success
     */
    Color rawColor = Color(1);
    Color invertColor = ColorInverter::Invert(rawColor, PROCESS_LEVEL_ID, "");
    EXPECT_EQ(rawColor.GetValue(), invertColor.GetValue());
}

/**
 * @tc.name: ColorInverterTest010
 * @tc.desc: ColorInverter::GetManager
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert
     * @tc.expected: EnableColorInvert Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    ColorInverter::GetInstance().EnableColorInvert(PROCESS_LEVEL_ID, "", std::move(func));
    auto managerMap = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_NE(managerMap.size(), 0);
    auto iter = managerMap.find(PROCESS_LEVEL_ID);
    EXPECT_NE(iter, managerMap.end());
    auto invertFunc = iter->second->GetInvertFunc("");
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);

    /**
     * @tc.steps: step2. Call GetManager
     * @tc.expected: GetManager Success
     */
    auto manager1 = ColorInverter::GetInstance().GetManager(PROCESS_LEVEL_ID);
    auto manager2 = ColorInverter::GetInstance().GetManager(1);
    EXPECT_NE(manager1, nullptr);
    EXPECT_EQ(manager2, nullptr);
}

/**
 * @tc.name: ColorInverterTest011
 * @tc.desc: ColorInverter::GetManager
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert
     * @tc.expected: EnableColorInvert Success
     */
    ColorInvertFunc func = [](uint32_t color) { return color; };
    ColorInverter::GetInstance().EnableColorInvert(PROCESS_LEVEL_ID, "", std::move(func));
    auto managerMap = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_NE(managerMap.size(), 0);
    auto iter = managerMap.find(PROCESS_LEVEL_ID);
    EXPECT_NE(iter, managerMap.end());
    auto invertFunc = iter->second->GetInvertFunc("");
    EXPECT_NE(invertFunc, nullptr);
    EXPECT_EQ(invertFunc(0), 0);

    /**
     * @tc.steps: step2. Call GetOrCreateManager
     * @tc.expected: GetOrCreateManager Success
     */
    auto manager1 = ColorInverter::GetInstance().GetOrCreateManager(PROCESS_LEVEL_ID);
    EXPECT_EQ(managerMap.size(), 1);
    EXPECT_NE(manager1, nullptr);
    auto manager2 = ColorInverter::GetInstance().GetOrCreateManager(1);
    EXPECT_NE(manager2, nullptr);
    auto managerMapNew = ColorInverter::GetInstance().colorInvertFuncManagerMap_;
    EXPECT_EQ(managerMapNew.size(), 1 + 1);
}

/**
 * @tc.name: ColorInverterTest0012
 * @tc.desc: ColorInverter::DefaultInverter
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call DefaultInverter With ARGB color
     * @tc.expected: DefaultInverter Give Back Right Value
     */
    static const uint8_t fullColor = 255;
    static const uint8_t halfAlpha = 128;
    Color full = Color::FromARGB(halfAlpha, fullColor, fullColor, fullColor);
    Color invertColor = Color::FromARGB(halfAlpha, 0, 0, 0);
    EXPECT_EQ(ColorInverter::DefaultInverter(full.GetValue()), invertColor.GetValue());
}

/**
 * @tc.name: ColorInverterTest0013
 * @tc.desc: test for mutiThread
 * @tc.type: FUNC
 */
HWTEST_F(ColorInverterTest, ColorInverterTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call EnableColorInvert and DisableColorInvert with mutithread
     * @tc.expected: no crash happend
     */
    ColorInverter::GetInstance().colorInvertFuncManagerMap_.clear();
    std::vector<std::thread> threads;
    auto enableTask = []() {
        ColorInvertFunc func = [](uint32_t color) { return ~color; };
        ColorInverter::GetInstance().EnableColorInvert(-1, "", std::move(func));
        auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(-1, "");
    };
    auto disableTask = []() {
        ColorInverter::GetInstance().DisableColorInvert(-1, "");
        auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(-1, "");
    };
    for (int i = 0; i < 20; ++i) {
        if (i % 2 == 0) {
            threads.emplace_back(std::thread(enableTask));
        } else {
            threads.emplace_back(std::thread(disableTask));
        }
    }
    for (auto&& thread : threads) {
        thread.join();
    }
    /**
     * @tc.steps: step2. Get invertFunc
     * @tc.expected: if invertFunc is null colorInvertFuncManagerMap_ is empty else give back right value
     */
    auto invertFunc = ColorInverter::GetInstance().GetInvertFunc(-1, "");
    if (invertFunc) {
        static const uint8_t fullColor = 255;
        Color full = Color::FromARGB(fullColor, fullColor, fullColor, fullColor);
        Color invertColor = Color::FromARGB(0, 0, 0, 0);
        EXPECT_EQ(Color(invertFunc(full.GetValue())), invertColor);
    } else {
        EXPECT_TRUE(ColorInverter::GetInstance().colorInvertFuncManagerMap_.empty());
    }
}
} // namespace OHOS::Ace
