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

const DOMAIN = 0x0001;
const TAG = 'Sample_arktsfocus';

const delegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let driver: Driver;
let want: Want;

export default function FocusTest() {
  describe('ArkTSFocusTest', () => {
    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      driver = Driver.create();
      await driver.delayMs(2000);

      const ability: UIAbility = await delegator.getCurrentTopAbility();
      hilog.info(DOMAIN, TAG, 'get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    });

    /**
     * @tc.number ArkTSFocus_001
     * @tc.name testHomePageLoad
     * @tc.desc 测试首页加载是否成功
     */
    it('testHomePageLoad', 0, async (done: Function) => {
      hilog.info(DOMAIN, TAG, 'testHomePageLoad begin');

      const listItem = await driver.findComponent(ON.text('基础焦点能力'));
      hilog.info(DOMAIN, TAG, `list item found: ${listItem !== null}`);
      expect(listItem === null).assertFalse();

      const list = await driver.findComponent(ON.type('List'));
      expect(list === null).assertFalse();

      hilog.info(DOMAIN, TAG, 'testHomePageLoad end');
      done();
    });

    /**
     * @tc.number ArkTSFocus_002
     * @tc.name testBasicFocusPage
     * @tc.desc 测试基础焦点能力页面导航和默认焦点
     */
    it('testBasicFocusPage', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('基础焦点能力'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(2000);

          const titleText = await driver.findComponent(ON.text('基础焦点能力'));
          expect(titleText === null).assertFalse();

          const buttonA = await driver.findComponent(ON.text('Button A (defaultFocus)'));
          expect(buttonA === null).assertFalse();

          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG, 'error: %{public}s', JSON.stringify(error));
        done(error);
      }
    });

    /**
     * @tc.number ArkTSFocus_003
     * @tc.name testTabNavigationPage
     * @tc.desc 测试 Tab 键导航页面
     */
    it('testTabNavigationPage', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('Tab 键导航'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(2000);

          const btn2 = await driver.findComponent(ON.text('Button 2 (tabIndex: 1)'));
          expect(btn2 === null).assertFalse();

          const btn4 = await driver.findComponent(ON.text('Button 4 (tabStop: false)'));
          expect(btn4 === null).assertFalse();

          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG, 'error: %{public}s', JSON.stringify(error));
        done(error);
      }
    });

    /**
     * @tc.number ArkTSFocus_004
     * @tc.name testCustomNextFocusPage
     * @tc.desc 测试自定义焦点路径页面
     */
    it('testCustomNextFocusPage', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('自定义焦点路径'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(2000);

          const btnB3 = await driver.findComponent(ON.text('B3'));
          expect(btnB3 === null).assertFalse();

          const btnB5 = await driver.findComponent(ON.text('B5'));
          expect(btnB5 === null).assertFalse();

          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG, 'error: %{public}s', JSON.stringify(error));
        done(error);
      }
    });

    /**
     * @tc.number ArkTSFocus_005
     * @tc.name testFocusScopePage
     * @tc.desc 测试焦点域页面
     */
    it('testFocusScopePage', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('焦点域（分组与优先级）'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(2000);

          const scopeAText = await driver.findComponent(ON.text('Scope A'));
          expect(scopeAText === null).assertFalse();

          const scopeBText = await driver.findComponent(ON.text('Scope B (PRIOR)'));
          expect(scopeBText === null).assertFalse();

          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG, 'error: %{public}s', JSON.stringify(error));
        done(error);
      }
    });

    /**
     * @tc.number ArkTSFocus_006
     * @tc.name testFocusBoxStylePage
     * @tc.desc 测试自定义焦点框样式页面
     */
    it('testFocusBoxStylePage', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('自定义焦点框样式'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(2000);

          const defaultBox = await driver.findComponent(ON.text('Default Focus Box'));
          expect(defaultBox === null).assertFalse();

          const customBox = await driver.findComponent(ON.text('Custom Focus Box'));
          expect(customBox === null).assertFalse();

          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG, 'error: %{public}s', JSON.stringify(error));
        done(error);
      }
    });

    /**
     * @tc.number ArkTSFocus_007
     * @tc.name testFocusOnTouchPage
     * @tc.desc 测试触摸聚焦与命令式 API 页面
     */
    it('testFocusOnTouchPage', 0, async (done: Function) => {
      try {
        const targetItem = await driver.findComponent(ON.text('触摸聚焦与命令式 API'));
        if (targetItem !== null) {
          await targetItem.click();
          await driver.delayMs(2000);

          const touchArea = await driver.findComponent(ON.text('点击此区域聚焦 (focusOnTouch)'));
          expect(touchArea === null).assertFalse();

          if (touchArea !== null) {
            await touchArea.click();
            await driver.delayMs(500);
          }

          const requestBtn = await driver.findComponent(ON.text('请求聚焦 (UIContext)'));
          expect(requestBtn === null).assertFalse();

          await driver.pressBack();
          await driver.delayMs(1000);
        }
        done();
      } catch (error) {
        hilog.error(DOMAIN, TAG, 'error: %{public}s', JSON.stringify(error));
        done(error);
      }
    });
  });
}
