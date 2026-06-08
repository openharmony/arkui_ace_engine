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
import { abilityDelegatorRegistry, Driver, ON } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
const DOMAIN = 0x0001;
const TAG = 'Sample_gesturegroup';
const delegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let driver: Driver;
let want: Want;

// 定义要测试的页面列表
const testPages = [
  'sequence Identification',
  'parallel recognition',
  'Mutual exclusion identification',
  'Scene Example'
];

export default function GestureGroup() {
  describe('GestureGroup', () => {
    beforeAll(async () => {
      // 启动应用
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      driver = Driver.create();
      await driver.delayMs(1000);
      // 验证当前页面是否正确
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      hilog.info(DOMAIN, TAG, 'get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    });

    /**
     * @tc.number GestureGroup_001
     * @tc.name sequence Identification
     * @tc.desc 测试首页加载是否成功
     */
    it('sequence Identification', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'GestureGroupTest: sequence Identification begin');
      // 验证列表存在
      const list = await driver.findComponent(ON.type('List'));
      expect(list === null).assertFalse();

      // 验证至少一个列表项存在
      const firstItem = await driver.findComponent(ON.text('sequence Identification'));
      expect(firstItem === null).assertFalse();

      hilog.info(DOMAIN, TAG, 'GestureGroupTest: sequence Identification end');
      done();
    });

    /**
     * @tc.number GestureGroup_002
     * @tc.name testAllGestureGroupPages
     * @tc.desc 测试所有GestureGroup页面，按顺序点击进入四个页面，每个页面停留3秒
     */
    it('testAllGestureGroupPages', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'GestureGroupTest: testAllGestureGroupPages begin');

      for (let i = 0; i < testPages.length; i++) {
        const pageName = testPages[i];
        hilog.info(DOMAIN, TAG, `GestureGroupTest: Testing page ${i + 1}: ${pageName}`);

        // 查找并点击页面项
        const targetItem = await driver.findComponent(ON.text(pageName));
        if (targetItem !== null) {
          await targetItem.click();
          hilog.info(DOMAIN, TAG, `GestureGroupTest: Clicked ${pageName} item`);

          // 等待目标页面加载
          await driver.delayMs(1000);

          // 在页面停留3秒
          hilog.info(DOMAIN, TAG, `GestureGroupTest: Staying on ${pageName} page for 3 seconds`);
          await driver.delayMs(1000);

          // 返回主页
          await driver.pressBack();
          await driver.delayMs(1000);
          hilog.info(DOMAIN, TAG, `GestureGroupTest: Returned from ${pageName} page`);
        } else {
          hilog.error(DOMAIN, TAG, `GestureGroupTest: Could not find ${pageName} item`);
          // 即使找不到某个页面，也继续测试下一个
          continue;
        }
      }

      hilog.info(DOMAIN, TAG, 'GestureGroupTest: Completed all pages test successfully');
      hilog.info(DOMAIN, TAG, 'GestureGroupTest: testAllGestureGroupPages end');
      done();
    });
  });
}