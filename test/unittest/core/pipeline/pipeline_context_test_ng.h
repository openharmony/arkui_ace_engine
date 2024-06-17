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

#ifndef TEST_UNITTEST_CORE_PIPELINE_PIPELINE_CONTEXT_TEST_NG_H
#define TEST_UNITTEST_CORE_PIPELINE_PIPELINE_CONTEXT_TEST_NG_H

#include "gtest/gtest.h"

#define private public
#define protected public
#include "common_constants.h"
#include "mock_schedule_task.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "test/mock/core/common/mock_frontend.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace NG {
namespace {
constexpr int32_t DEFAULT_INSTANCE_ID = 0;
constexpr int32_t DEFAULT_INT0 = 0;
constexpr int32_t DEFAULT_INT1 = 1;
constexpr int32_t DEFAULT_INT3 = 3;
constexpr int32_t DEFAULT_INT10 = 10;
constexpr int32_t DEFAULT_RESTORE_ID0 = 100;
constexpr int32_t DEFAULT_RESTORE_ID1 = 101;
constexpr int32_t DEFAULT_RESTORE_ID2 = 102;
constexpr int32_t NOT_REGISTER_ID = 307;
constexpr uint32_t DEFAULT_SIZE1 = 1;
constexpr uint32_t DEFAULT_SIZE2 = 2;
constexpr uint32_t DEFAULT_SIZE3 = 3;
constexpr uint32_t FRAME_COUNT = 10;
constexpr uint64_t NANO_TIME_STAMP = 10;
constexpr uint64_t DEFAULT_UINT64_1 = 39;
constexpr uint64_t DEFAULT_UINT64_2 = 41;
constexpr double DEFAULT_DOUBLE0 = 0.0;
constexpr double DEFAULT_DOUBLE1 = 1.0;
constexpr double DEFAULT_DOUBLE2 = 2.0;
constexpr double DEFAULT_DOUBLE4 = 4.0;
constexpr int32_t CLOSE_BUTTON_INDEX = 5;
const std::string TEST_TAG("test");
const std::string ACCESS_TAG("-accessibility");
const std::string TEST_FORM_INFO("test_info");
const int64_t RENDER_EVENT_ID = 10;
constexpr int32_t EXCEPTIONAL_CURSOR = 99;
constexpr int8_t RENDERINGMODE_FULL_COLOR = 0;
constexpr int8_t RENDERINGMODE_SINGLE_COLOR = 1;
} // namespace

class PipelineContextTestNg : public testing::Test {
public:
    static void ResetEventFlag(int32_t testFlag);

    static bool GetEventFlag(int32_t testFlag);

    static void SetUpTestSuite();

    static void TearDownTestSuite();

    static void CreateCycleDirtyNode(int cycle, bool& flagUpdate);

private:
    static ElementIdType frameNodeId_;
    static ElementIdType customNodeId_;
    static RefPtr<FrameNode> frameNode_;
    static RefPtr<CustomNode> customNode_;
    static RefPtr<PipelineContext> context_;
};
} // namespace NG
} // namespace OHOS::Ace
#endif // TEST_UNITTEST_CORE_PIPELINE_PIPELINE_CONTEXT_TEST_NG_H