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

#ifndef IMAGE_ANIMATOR_CAPI_EXAMPLE_IMAGE_ANIMATOR_CASE_RUNNER_H
#define IMAGE_ANIMATOR_CAPI_EXAMPLE_IMAGE_ANIMATOR_CASE_RUNNER_H

#include <cstdint>
#include <string>
#include <vector>

namespace ImageAnimatorCaseRunner {
struct MetricCheck {
    std::string name;
    int32_t expected = 0;
    int32_t actual = 0;
    bool passed = false;
};

struct CaseResult {
    std::string group;
    std::string name;
    std::string api;
    std::string note;
    bool passed = false;
    std::vector<MetricCheck> checks;
};

struct CaseReport {
    bool nodeApiAvailable = false;
    int32_t totalCases = 0;
    int32_t passedCases = 0;
    int32_t failedCases = 0;
    int32_t totalChecks = 0;
    int32_t passedChecks = 0;
    int32_t failedChecks = 0;
    std::vector<CaseResult> cases;
};

CaseReport RunImageAnimatorFrameInfoCases();
} // namespace ImageAnimatorCaseRunner

#endif // IMAGE_ANIMATOR_CAPI_EXAMPLE_IMAGE_ANIMATOR_CASE_RUNNER_H
