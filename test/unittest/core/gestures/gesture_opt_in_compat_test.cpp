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

#include <unordered_set>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FINGER_A = 10;
constexpr int32_t FINGER_B = 11;
constexpr double PAN_DISTANCE = 10.0;
} // namespace

// Opt-in regression for the escape-to-EventManager channel (AC-Compat-1/2/3).
// Lock reuses the existing Pan-Pan escape mechanism (isLocked_/SetTriggeredIds),
// so only the escape channel (new) is covered here. EventManager-level
// escapeRecognizers_ empty-skip regression belongs to event_manager_test.
class GestureOptInCompatTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override
    {
        PanDirection direction;
        panRecognizer_ = AceType::MakeRefPtr<PanRecognizer>(1, direction, PAN_DISTANCE);
        ASSERT_NE(panRecognizer_, nullptr);
    }
    void TearDown() override {}
    RefPtr<PanRecognizer> panRecognizer_;
};

// Escape mode is off by default; no finger is escaped.
HWTEST_F(GestureOptInCompatTest, EscapeModeOffByDefault, TestSize.Level1)
{
    EXPECT_FALSE(panRecognizer_->IsFingerEscaped(FINGER_A));
    EXPECT_FALSE(panRecognizer_->IsFingerEscaped(FINGER_B));
}

// SetEscapeMode marks only the given fingers; ResetEscapeMode clears.
HWTEST_F(GestureOptInCompatTest, EscapeModeCycle, TestSize.Level1)
{
    panRecognizer_->SetEscapeMode({ FINGER_A });
    EXPECT_TRUE(panRecognizer_->IsFingerEscaped(FINGER_A));
    EXPECT_FALSE(panRecognizer_->IsFingerEscaped(FINGER_B));
    panRecognizer_->ResetEscapeMode();
    EXPECT_FALSE(panRecognizer_->IsFingerEscaped(FINGER_A));
}

// Escape-to-EventManager flag is off by default (opt-in, ADR-6).
HWTEST_F(GestureOptInCompatTest, EscapeToManagerDefaultFalse, TestSize.Level1)
{
    EXPECT_FALSE(panRecognizer_->IsEscapedToManager());
}

// SetEscapedToEventManager toggles the direct-success flag (AC-Escape-4).
HWTEST_F(GestureOptInCompatTest, EscapeToManagerToggle, TestSize.Level1)
{
    panRecognizer_->SetEscapedToEventManager(true);
    EXPECT_TRUE(panRecognizer_->IsEscapedToManager());
    panRecognizer_->SetEscapedToEventManager(false);
    EXPECT_FALSE(panRecognizer_->IsEscapedToManager());
}

// GetEscapedFingerIds reflects the set passed to SetEscapeMode.
HWTEST_F(GestureOptInCompatTest, GetEscapedFingerIdsReflectsSet, TestSize.Level1)
{
    std::unordered_set<int32_t> fingers = { FINGER_A, FINGER_B };
    panRecognizer_->SetEscapeMode(fingers);
    const auto& got = panRecognizer_->GetEscapedFingerIds();
    EXPECT_EQ(got.size(), 2U);
    EXPECT_EQ(got.count(FINGER_A), 1U);
    EXPECT_EQ(got.count(FINGER_B), 1U);
}

// Without opt-in, no finger is escaped -> ProcessTouchEvent filter never triggers.
HWTEST_F(GestureOptInCompatTest, NoOpWhenNotOptedIn, TestSize.Level1)
{
    EXPECT_FALSE(panRecognizer_->IsFingerEscaped(FINGER_A));
    EXPECT_FALSE(panRecognizer_->IsFingerEscaped(FINGER_B));
    EXPECT_FALSE(panRecognizer_->IsEscapedToManager());
}
} // namespace OHOS::Ace::NG
