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

#include <benchmark/benchmark.h>
#include <gmock/gmock.h>

#include "test/unittest/core/pattern/test_ng.h"

using Test = OHOS::Ace::NG::TestNG;

int main(int argc, char** argv)
{
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
        return 1;

    testing::FLAGS_gmock_verbose = "error";
    Test::SetUpTestSuite(); // to create mocked UI environment
    ::benchmark::RunSpecifiedBenchmarks();
    Test::TearDownTestSuite();

    ::benchmark::Shutdown();
}
