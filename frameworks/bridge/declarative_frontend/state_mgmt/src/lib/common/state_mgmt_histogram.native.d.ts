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

/**
 * StateMgmtHistogram implemented on C++ side.
 *
 * Framework internal bridge to the ArkUI histogram backend. The metric name is
 * supplied by the caller; the C++ side prepends the "ArkUI." prefix, so callers
 * must NOT include it. `sample` is clamped to 0/1.
 *
 * non-public API
 */

declare class StateMgmtHistogram {
    /**
     * Record a boolean histogram sample.
     * @param name Metric name WITHOUT the "ArkUI." prefix.
     * @param sample 0 or 1 (clamped).
     */
    static recordBoolean(name: string, sample: number): void;
}
