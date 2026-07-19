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

const DEFAULT_FRAME_COUNT = 0;
const DEFAULT_CASE_COUNT = 0;

const NativeMock: Record<string, Object> = {
  'getCoverageReport': () => {
    return {
      nodeApiAvailable: false,
      items: [],
      note: 'Native ImageAnimator C API is unavailable in mock mode.',
    };
  },
  'getFrameInfoCaseReport': () => {
    return {
      nodeApiAvailable: false,
      totalCases: DEFAULT_CASE_COUNT,
      passedCases: DEFAULT_CASE_COUNT,
      failedCases: DEFAULT_CASE_COUNT,
      totalChecks: DEFAULT_CASE_COUNT,
      passedChecks: DEFAULT_CASE_COUNT,
      failedChecks: DEFAULT_CASE_COUNT,
      cases: [],
    };
  },
  'attachImageAnimator': () => {
    return {
      attached: false,
      frameCount: DEFAULT_FRAME_COUNT,
    };
  },
  'setAnimatorState': () => false,
  'setAnimatorOptions': () => false,
  'getAnimatorSnapshot': () => {
    return { attached: false };
  },
  'detachImageAnimator': () => true,
};

export default NativeMock;
