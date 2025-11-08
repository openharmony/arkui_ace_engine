/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ani_profiler.h"

#include "ani_utils.h"
#include "load.h"

extern "C" int StartSamplingProfiler(const char* asptFileName, int interva);
extern "C" int StopSamplingProfiler();

namespace OHOS::Ace::Ani {

void AniProfiler::StartProfiler(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_string asptFileName, ani_int interva)
{
    auto fileName = AniUtils::ANIStringToStdString(env, asptFileName);
    StartSamplingProfiler(fileName.c_str(), static_cast<int>(interva));
}

void AniProfiler::StopProfiler(ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    StopSamplingProfiler();
}

} // namespace OHOS::Ace::Ani
