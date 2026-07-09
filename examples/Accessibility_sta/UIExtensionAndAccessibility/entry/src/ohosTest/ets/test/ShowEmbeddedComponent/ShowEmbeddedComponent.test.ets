'use static';
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
import { describe, beforeAll, beforeEach, afterEach, afterAll, it } from '@ohos/hypium';
import Want from '@ohos.app.ability.Want';
import abilityDelegatorRegistry from '@ohos.app.ability.abilityDelegatorRegistry';
import { Driver, ON } from '@ohos.UiTest';

export default function ShowEmbeddedComponent() {
  describe('ShowEmbeddedComponent', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    let driver = Driver.create();
    const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
    beforeAll(async () => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      const want: Want = {
        bundleName: 'com.samples.uiextensionandaccessibility',
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(async (done: Function) => {
      const driver = Driver.create();
      await driver.pressBack();
      await driver.delayMs(2000);
      done()
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })

    /**
     * @tc.number ArkUI_Embedded_001
     * @tc.name EmbeddedTest_001
     * @tc.desc 通过EmbeddedComponent拉起EmbeddedUIExtensionAbility
     * @tc.level: Level 1
     */
    it('EmbeddedTest_001', 0, async (done: Function) => {
      const driver = Driver.create();
      const button = await driver.findComponent((ON.text('ShowPage')));
      await button.click();
      await driver.delayMs(1000);
      done();
    })
  })
}