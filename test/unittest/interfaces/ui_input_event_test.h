/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef TEST_UNITTEST_INTERFACES_UI_INPUT_EVENT_TEST_H
#define TEST_UNITTEST_INTERFACES_UI_INPUT_EVENT_TEST_H
#include "event/ui_input_event_impl.h"
#include "gtest/gtest.h"
#include "interfaces/native/node/event_converter.h"
#include "native_node.h"
#include "ui_input_event.h"
#include "base/error/error_code.h"

#include "frameworks/core/event/ace_events.h"
#include "frameworks/core/event/axis_event.h"
#include "frameworks/core/event/touch_event.h"

namespace OHOS::Ace {
class UIInputEventTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};
} // namespace OHOS::Ace

#endif // TEST_UNITTEST_INTERFACES_UI_INPUT_EVENT_TEST_H