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

#include "ani_trace.h"

#include "ani_utils.h"
#include "load.h"

namespace OHOS::Ace::Ani {

bool AniTrace::GetAttributeSetTraceEnabled(ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, false);
    auto* traceModifier = modifier->getTraceAniModifier();
    CHECK_NULL_RETURN(traceModifier, false);
    return traceModifier->getAttributeSetTraceEnabled();
}

void AniTrace::TraceBegin(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string aniTraceName)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* traceModifier = modifier->getTraceAniModifier();
    CHECK_NULL_VOID(traceModifier);
    auto traceName = AniUtils::ANIStringToStdString(env, aniTraceName);
    traceModifier->traceBegin(traceName);
}

void AniTrace::TraceEnd(ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* traceModifier = modifier->getTraceAniModifier();
    CHECK_NULL_VOID(traceModifier);
    traceModifier->traceEnd();
}

void AniTrace::AsyncTraceBegin(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_string aniTraceName, ani_int taskId)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* traceModifier = modifier->getTraceAniModifier();
    CHECK_NULL_VOID(traceModifier);
    auto traceName = AniUtils::ANIStringToStdString(env, aniTraceName);
    traceModifier->asyncTraceBegin(traceName, static_cast<int>(taskId));
}

void AniTrace::AsyncTraceEnd(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_string aniTraceName, ani_int taskId)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* traceModifier = modifier->getTraceAniModifier();
    CHECK_NULL_VOID(traceModifier);
    auto traceName = AniUtils::ANIStringToStdString(env, aniTraceName);
    traceModifier->asyncTraceEnd(traceName, static_cast<int>(taskId));
}

} // namespace OHOS::Ace::Ani
