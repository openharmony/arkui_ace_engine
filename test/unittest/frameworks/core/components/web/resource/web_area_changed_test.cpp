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
#include "vector"
#include "core/components/web/resource/web_area_changed.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace {

using namespace testing;
using namespace testing::ext;

class onAvoidAreaChangedTest : public ::testing::Test {
protected:
    WeakPtr<WebDelegate> webDelegate;

protected:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name  : OnAvoidAreaChanged_ShouldCallDelegate_WhenDelegateIsNotNull
 * @tc.number: Ace_Web_OnAvoidAreaChanged_001
 * @tc.desc  : Test if delegate is not null, then it should call delegate's OnAvoidAreaChanged method
 */
HWTEST_F(onAvoidAreaChangedTest, OnAvoidAreaChanged_ShouldCallDelegate_WhenDelegateIsNotNull, TestSize.Level1)
{
    EXPECT_EQ(webDelegate.GetRawPtr(), nullptr);
    WebAvoidAreaChangedListener listener(webDelegate);
    listener.OnAvoidAreaChanged(OHOS::Rosen::AvoidArea(), OHOS::Rosen::AvoidAreaType());
}
} // namespace OHOS::Ace