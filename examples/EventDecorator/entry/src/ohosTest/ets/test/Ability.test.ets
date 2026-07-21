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
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import { abilityDelegatorRegistry, Driver, ON } from '@kit.TestKit';
import { Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
const TAG = '[Sample_EventDecorator]';
const DOMAIN = 0xF811;
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
export default function abilityTest() {
  describe('ActsAbilityTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'uitest: ActsAbilityTest begin');
      const want: Want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      const driver = Driver.create();
      await driver.delayMs(1000);
      hilog.info(DOMAIN, TAG, 'get top ability');
      await driver.delayMs(1000);

      done();
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(async (done: Function) => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
      const driver = Driver.create();
      await driver.pressBack();
      await driver.delayMs(3000);
      done();
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })
    /**
     * @tc.number UiTest_001
     * @tc.name processweb_EventDecoratorTest1_001
     * @tc.desc 测试更改父组件中变量场景示例
     * @tc.level: Level 1
     */
    it('processweb_EventDecoratorTest1_001', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'uitest: processweb_EventDecoratorTest1_001 begin');
      const driver = Driver.create();

      const button = await driver.findComponent(ON.text('EventDecoratorTest1Button'));
      await button.click();
      await driver.delayMs(3000);

      const button1 = await driver.findComponent(ON.text('change to Title Two'));
      await button1.click();
      await driver.delayMs(300);

      const text1 = await driver.findComponent(ON.type('Text'));
      const res1 = await text1.getText();
      expect(res1).assertEqual('Title Two');

      const button2 = await driver.findComponent(ON.text('change to Title One'));
      await button2.click();
      await driver.delayMs(300);

      const text2 = await driver.findComponent(ON.type('Text'));
      const res2 = await text2.getText();
      expect(res2).assertEqual('Title One');
      hilog.info(DOMAIN, TAG, 'uitest: processweb_EventDecoratorTest1_001 end');
      done();
    })

    /**
     * @tc.number UiTest_002
     * @tc.name processweb_EventDecoratorTest2_001
     * @tc.desc 测试从父组件将变化同步回子组件的过程是异步的场景示例
     * @tc.level: Level 1
     */
    it('processweb_EventDecoratorTest2_001', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'uitest: ActsAbilityTest begin');
      hilog.info(DOMAIN, TAG, 'uitest: processweb_EventDecoratorTest2_001 begin');
      const driver = Driver.create();
      await driver.delayMs(1000);
      const button = await driver.findComponent(ON.text('EventDecoratorTest2Button'));
      await button.click();
      await driver.delayMs(3000);

      const text = await driver.findComponent(ON.type('Text'));
      await text.click();
      await driver.delayMs(300)
      const res = await text.getText();
      expect(res).assertEqual('Child index: 20');
      hilog.info(DOMAIN, TAG, 'uitest: processweb_EventDecoratorTest2_001 end');

      done();
    })
  })
}