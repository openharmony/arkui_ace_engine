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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_HIVIEWDFX_HISTOGRAM_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_HIVIEWDFX_HISTOGRAM_WRAPPER_H

#ifdef ACE_ENGINE_API_METRICS_EXT_ENABLE
#include "histogram_plugin_macros.h"

/**
 * @brief Record a boolean histogram sample.
 *
 * Automatically prefixed with "ArkUI." at the wrapper level.
 * Callers should NOT include the "ArkUI." prefix in the name parameter.
 *
 * Valid sample values:
 *   0 = false / failure / disabled / no
 *   1 = true  / success / enabled  / yes
 *
 * Typical use cases:
 *   - API call frequency (sample = 1)
 *   - API success rate
 *   - Feature switch enabled ratio
 *
 * @param name   Metric name without "ArkUI." prefix.
 * @param sample Must be 0 or 1.
 */
#define ACE_ENGINE_HISTOGRAM_BOOLEAN(name, sample) \
    HISTOGRAM_BOOLEAN("ArkUI." name, (sample))

/**
 * @brief Record an enumeration histogram sample.
 *
 * Automatically prefixed with "ArkUI." at the wrapper level.
 * Callers should NOT include the "ArkUI." prefix in the name parameter.
 *
 * Valid input range:
 *   sample   ∈ [0, boundary]
 *   boundary > 0
 *
 * Typical use cases:
 *   - Error codes mapped to small enums
 *   - API success/failure (boundary = 1, sample = 0 or 1)
 *   - State machine final state
 *
 * @param name      Metric name without "ArkUI." prefix.
 * @param sample    Enum value to record.
 * @param boundary  Maximum enum value (inclusive).
 */
#define ACE_ENGINE_HISTOGRAM_ENUMERATION(name, sample, boundary) \
    HISTOGRAM_ENUMERATION("ArkUI." name, (sample), (boundary))

/**
 * @brief Record a custom count histogram sample.
 *
 * Automatically prefixed with "ArkUI." at the wrapper level.
 * Callers should NOT include the "ArkUI." prefix in the name parameter.
 *
 * Valid input rules:
 *   sample       ∈ [0, INT32_MAX)
 *   min          >= 0
 *   max          < INT32_MAX
 *   min          < max
 *   bucket_count >= 2
 *   bucket_count < 100
 *
 * Typical use cases:
 *   - Retry count
 *   - Object count
 *   - Queue depth
 *
 * @param name         Metric name without "ArkUI." prefix.
 * @param sample       Sample value to record.
 * @param min          Lower bound of histogram domain.
 * @param max          Upper bound of histogram domain.
 * @param bucket_count Bucket count, must be < 100.
 */
#define ACE_ENGINE_HISTOGRAM_CUSTOM_COUNTS(name, sample, min, max, bucket_count) \
    HISTOGRAM_CUSTOM_COUNTS("ArkUI." name, (sample), (min), (max), (bucket_count))

/**
 * @brief Record a time histogram sample.
 *
 * Automatically prefixed with "ArkUI." at the wrapper level.
 * Callers should NOT include the "ArkUI." prefix in the name parameter.
 *
 * Valid sample range:
 *   sample ∈ [0, INT32_MAX)
 *
 * Unit recommendation:
 *   milliseconds (ms)
 *
 * Typical use cases:
 *   - API latency
 *   - Page render time
 *   - Startup duration
 *
 * @param name   Metric name without "ArkUI." prefix.
 * @param sample Time cost value, normally milliseconds.
 */
#define ACE_ENGINE_HISTOGRAM_TIMES(name, sample) \
    HISTOGRAM_TIMES("ArkUI." name, (sample))

/**
 * @brief Record a percentage histogram sample.
 *
 * Automatically prefixed with "ArkUI." at the wrapper level.
 * Callers should NOT include the "ArkUI." prefix in the name parameter.
 *
 * Valid sample range:
 *   sample ∈ [0, 100]
 *
 * Typical use cases:
 *   - CPU utilization
 *   - Success percentage
 *   - Cache hit ratio
 *
 * @param name   Metric name without "ArkUI." prefix.
 * @param sample Percentage value from 0 to 100 inclusive.
 */
#define ACE_ENGINE_HISTOGRAM_PERCENTAGE(name, sample) \
    HISTOGRAM_PERCENTAGE("ArkUI." name, (sample))

#else

#define ACE_ENGINE_HISTOGRAM_BOOLEAN(name, sample) ((void)0)

#define ACE_ENGINE_HISTOGRAM_ENUMERATION(name, sample, boundary) ((void)0)

#define ACE_ENGINE_HISTOGRAM_CUSTOM_COUNTS(name, sample, min, max, bucket_count) ((void)0)

#define ACE_ENGINE_HISTOGRAM_TIMES(name, sample) ((void)0)

#define ACE_ENGINE_HISTOGRAM_PERCENTAGE(name, sample) ((void)0)

#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_HIVIEWDFX_HISTOGRAM_WRAPPER_H
