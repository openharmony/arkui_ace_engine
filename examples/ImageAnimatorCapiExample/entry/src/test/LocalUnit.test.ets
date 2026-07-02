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

import { afterAll, afterEach, beforeAll, beforeEach, describe, expect, it } from '@ohos/hypium';

const SOURCE_TEXT = 'abc';
const TARGET_TEXT = 'b';
const DEFAULT_TEST_FILTER = 0;

export default function localUnitTest() {
  describe('localUnitTest', () => {
    beforeAll(() => {
    });
    beforeEach(() => {
    });
    afterEach(() => {
    });
    afterAll(() => {
    });
    it('assertContain', DEFAULT_TEST_FILTER, () => {
      expect(SOURCE_TEXT).assertContain(TARGET_TEXT);
      expect(SOURCE_TEXT).assertEqual(SOURCE_TEXT);
    });
  });
}
