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

import { describe, it, expect, beforeAll } from '@ohos/hypium';
// 导入测试依赖kit
import { abilityDelegatorRegistry, Driver, ON, MouseButton, Component, MatchPattern } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

export default function IndexTest() {

  describe('IndexTest', () => {

    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      let driver = Driver.create();
      await driver.delayMs(1000);
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      console.info('get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    })

    /**
     * @tc.number UiTest_001
     * @tc.name testNestScroll
     * @tc.desc 测试嵌套滚动示例
     */
    it('testNestScroll', 0, async (done: Function) => {
      console.info('uitest: testNestScroll begin');
      let driver = Driver.create();
      let size = await driver.getDisplaySize()
      let startX = Math.floor(size.x * 0.5)
      let endX = Math.floor(size.x * 0.5)
      await driver.swipe(startX, 700, endX, 0, 1000);
      await driver.delayMs(1000);
      await driver.swipe(startX, 700, endX, 0, 1000);
      await driver.delayMs(1000);
      await driver.swipe(startX, 500, endX, 1000, 1000);
      await driver.delayMs(1000);
      await driver.swipe(startX, 500, endX, 1000, 1000);
      await driver.delayMs(1000);
      await driver.swipe(startX, 500, endX, 1000, 1000);
      await driver.delayMs(1000);
      await driver.pressBack();
      console.info('uitest: testNestScroll end');
      done();
    })
  })
}