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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_LAYOUT_SAFE_AREA_TEST_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_LAYOUT_SAFE_AREA_TEST_NG_H

#include <cstdint>
#include <map>
#include <memory>

#include "gtest/gtest.h"

#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/offset.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
struct AvoidConfig {
    bool isAtomicService = false;
    bool isFullScreen = false;
    bool isNeedAvoidWindow = false;
    bool ignoreSafeArea = false;
    bool keyboardSafeAreaEnabled = false;
    std::string ToString()
    {
        std::string result;
        result.append("isAtomicService: ");
        result.append(isAtomicService ? "True" : "False");
        result.append(", isFullScreen: ");
        result.append(isFullScreen ? "True" : "False");
        result.append(", isNeedAvoidWindow: ");
        result.append(isNeedAvoidWindow ? "True" : "False");
        result.append(", ignoreSafeArea: ");
        result.append(ignoreSafeArea ? "True" : "False");
        result.append(", keyboardSafeAreaEnabled: ");
        result.append(keyboardSafeAreaEnabled ? "True" : "False");
        return result;
    }
};
class ExpandSafeAreaTestNg : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    virtual void GetInstance();

    void Create(const std::function<void()>& callback = nullptr, bool flushLayout = true);
    void CreateWithItem(const std::function<void()>& callback = nullptr);
    void AddItems(int32_t number);
    static void CreateItem(int32_t number = 10, bool defineSize = false);
    static void CreateItemWithHeight(float height);
    static void InitSafeArea(SafeAreaExpandOpts opts);
    static SafeAreaInsets GetSafeAreaInsets();
    static void InitSafeAreaManager(AvoidConfig config);

    // page
    RefPtr<FrameNode> frameNode_;
    RefPtr<Pattern> pagePattern_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_LAYOUT_SAFE_AREA_TEST_NG_H
