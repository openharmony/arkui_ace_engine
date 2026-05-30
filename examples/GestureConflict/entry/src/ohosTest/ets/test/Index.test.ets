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
import hilog from '@ohos.hilog';

// HiLog通常需要domain, tag等参数
const DOMAIN = 0x0001;
const TAG = 'Sample_gestureconflict';

const delegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let driver: Driver;
let want: Want;

export default function GestureConflict() {
  describe('GestureConflict', () => {
    beforeAll(async () => {
      // 启动应用
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      driver = Driver.create();
      await driver.delayMs(2000); // 增加初始等待时间

      // 验证当前页面是否正确
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      hilog.info(DOMAIN, TAG,'get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    });

    /**
     * @tc.number GestureConflict_001
     * @tc.name testHomePageLoad
     * @tc.desc 测试首页加载是否成功
     */
    it('testHomePageLoad', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG,'GestureConflict: testHomePageLoad begin');

      // 验证列表项存在 - 使用首页中实际存在的文本
      const listItem = await driver.findComponent(ON.text('Custom gesture recognition'));
      hilog.info(DOMAIN, TAG,`GestureConflict: list item found: ${listItem !== null}`);
      expect(listItem === null).assertFalse();

      // 验证列表存在
      const list = await driver.findComponent(ON.type('List'));
      hilog.info(DOMAIN, TAG,`GestureConflict: list found: ${list !== null}`);
      expect(list === null).assertFalse();

      hilog.info(DOMAIN, TAG,'GestureConflict: testHomePageLoad end');
      done();
    });

    /**
     * @tc.number GestureConflict_002
     * @tc.name testNavigationToDetailPage
     * @tc.desc 测试页面 长按拖动
     */
    it('testNavigationToDetailPage', 0, async (done: Function) => {
      // 查找并点击第一个列表项
      const targetItem = await driver.findComponent(ON.text('Custom gesture recognition'));
      if (targetItem !== null) {
        await targetItem.click();
        // 等待目标页面加载
        await driver.delayMs(2000);
        // 返回首页
        await driver.pressBack();
        await driver.delayMs(1000);
      }
      done();
    });

    /**
     * @tc.number GestureConflict_003
     * @tc.name GestureAndMotionControl
     * @tc.desc 滑动页面.
     */
    it('GestureAndMotionControl', 0, async (done: Function) => {
      // 查找并点击第一个列表项
      const targetItem = await driver.findComponent(ON.text('Gesture and motion control'));
      if (targetItem !== null) {
        await targetItem.click();
        // 等待目标页面加载
        await driver.delayMs(10000);

        // 使用 swipe 方法向下滑动
        await driver.swipe(500, 1000, 500, 200, 100);

        // 返回首页
        await driver.pressBack();
        await driver.delayMs(1000);
      }
      done();
    });

    /**
     * @tc.number GestureConflict_004
     * @tc.name PreventGestureRecognition
     * @tc.desc 长按页面,加速进度.
     */
    it('PreventGestureRecognition', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('Preventing gesture participation in recognition'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(3000);
          const centerX = 500;
          const centerY = 800;
          await driver.swipe(centerX, centerY, centerX + 10, centerY + 10, 3000);
          await driver.delayMs(3000);
          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG,'error:', error);
        done(error);
      }
    });
  });
}