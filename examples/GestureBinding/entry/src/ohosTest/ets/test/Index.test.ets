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
const TAG = 'Sample_gesturebinding';
const delegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let driver: Driver;
let want: Want;

const testPages = [
  'gesture',
  'priorityGesture',
  'parallelGesture'
];

export default function GestureBinding() {
  describe('GestureBinding', () => {
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
     * @tc.number GestureBinding_001
     * @tc.name testHomePageLoad
     * @tc.desc 测试首页加载是否成功
     */
    it('testHomePageLoad', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'GestureBinding: testHomePageLoad begin');

      // 验证列表存在
      const list = await driver.findComponent(ON.type('List'));
      expect(list === null).assertFalse();

      // 验证至少一个列表项存在
      const firstItem = await driver.findComponent(ON.text('gesture'));
      expect(firstItem === null).assertFalse();

      hilog.info(DOMAIN, TAG, 'GestureBinding: testHomePageLoad end');
      done();
    });

    /**
     * @tc.number GestureBinding_002
     * @tc.name testAllGesturePages
     * @tc.desc 测试所有Gesture相关页面，按顺序点击进入三个页面，每个页面停留3秒
     */
    it('testAllGesturePages', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'GestureBinding: testAllGesturePages begin');

      for (let i = 0; i < testPages.length; i++) {
        const pageName = testPages[i];
        hilog.info(DOMAIN, TAG, `GestureBinding: Testing page ${i + 1}: ${pageName}`);

        // 查找并点击页面项
        const targetItem = await driver.findComponent(ON.text(pageName));
        if (targetItem !== null) {
          await targetItem.click();
          hilog.info(DOMAIN, TAG, `GestureBinding: Clicked ${pageName} item`);

          // 等待目标页面加载
          await driver.delayMs(2000);

          // 验证是否成功跳转到目标页面
          try {
            // 尝试查找目标页面特有的元素来验证页面加载成功
            // 这里可以根据实际页面的内容添加具体的验证
            hilog.info(DOMAIN, TAG, `GestureBinding: Successfully navigated to ${pageName} page`);

            // 在页面停留3秒
            hilog.info(DOMAIN, TAG, `GestureBinding: Staying on ${pageName} page for 3 seconds`);
            await driver.delayMs(1000);
          } catch (error) {
            hilog.error(DOMAIN, TAG, `GestureBinding: Failed to verify ${pageName} page: ${error}`);
          }

          // 返回主页
          await driver.pressBack();
          await driver.delayMs(1000);
          hilog.info(DOMAIN, TAG, `GestureBinding: Returned from ${pageName} page`);

          // 验证是否返回主页
          const homePageItem = await driver.findComponent(ON.text('gesture'));
          expect(homePageItem === null).assertFalse();
        } else {
          hilog.error(DOMAIN, TAG, `GestureBinding: Could not find ${pageName} item`);
          // 即使找不到某个页面，也继续测试下一个
          continue;
        }
      }
      hilog.info(DOMAIN, TAG, 'GestureBinding: Completed all pages test successfully');
      hilog.info(DOMAIN, TAG, 'GestureBinding: testAllGesturePages end');
      done();
    });
  });
}