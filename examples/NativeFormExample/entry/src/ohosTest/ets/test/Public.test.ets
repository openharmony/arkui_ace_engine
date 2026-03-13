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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import { abilityDelegatorRegistry, BY, Driver, ON } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

export default function PublicTest() {
  describe('PublicTest', () => {

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

    beforeEach(async () => {
      let driver = Driver.create();
      await driver.delayMs(1000);
    })

    afterEach(() => {
      hilog.info(0x0000, 'PublicTest', 'Public event test case completed');
    })

    afterAll(() => {
      hilog.info(0x0000, 'PublicTest', 'All publicTest event tests completed');
    })

    /**
     * @tc.number PublicTest_001
     * @tc.name testPublicBackground
     * @tc.desc 测试背景色属性设置 - 打开Public界面，查看设置的Row组件背景色属性
     */
    it('testPublicBackground', 0, async (done: Function) => {
      hilog.info(0x0000, 'PublicTest', 'testPublicBackground begin');
      let driver = Driver.create();
      await driver.delayMs(1000);

      try {
        // 点击Public进入通用属性界面
        const button1 = await driver.findComponent(ON.id('Public'));
        await button1.click();
        await driver.delayMs(1000);

        // 验证backgroundColumn设置的背景色
        let strJson = getInspectorByKey('backgroundColumn');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'PublicTest', 'backgroundColumn backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FF009A61');
      } catch (error) {
        hilog.error(0x0000, 'PublicTest', 'testPublicBackground failed: %{public}s', error.message);
      }

      hilog.info(0x0000, 'PublicTest', 'testPublicBackground end');
      done();
    })

    /**
     * @tc.number PublicTest_002
     * @tc.name testPublicEnabled
     * @tc.desc 测试Enabled属性设置 - 打开Public界面，查看设置的Button组件Enabled属性
     */
    it('testPublicEnabled', 0, async (done: Function) => {
      hilog.info(0x0000, 'PublicTest', 'testPublicEnabled begin');
      let driver = Driver.create();
      await driver.delayMs(1000);

      try {
        // 点击Public进入通用属性界面
        const button1 = await driver.findComponent(ON.id('Public'));
        await button1.click();
        await driver.delayMs(1000);

        // 验证enabledButton设置的Enabled属性
        let strJson = getInspectorByKey('enabledButton');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'PublicTest', 'enabledButton enabled: %{public}s', obj.$attrs.enabled);
        expect(obj.$attrs.enabled).assertEqual(false);

        // 验证backgroundColumn设置的背景色
        let strJson1 = getInspectorByKey('notEnabledButton');
        let obj1: ESObject = JSON.parse(strJson1);
        hilog.info(0x0000, 'PublicTest', 'notEnabledButton enabled: %{public}s', obj1.$attrs.enabled);
        expect(obj1.$attrs.enabled).assertEqual(true);

      } catch (error) {
        hilog.error(0x0000, 'PublicTest', 'testPublicEnabled failed: %{public}s', error.message);
      }

      hilog.info(0x0000, 'PublicTest', 'testPublicEnabled end');
      done();
    })

    /**
     * @tc.number PublicTest_003
     * @tc.name testPublicZIndex
     * @tc.desc 测试zIndex属性设置 - 打开Public界面，查看设置的Button组件zIndex属性
     */
    it('testPublicZIndex', 0, async (done: Function) => {
      hilog.info(0x0000, 'PublicTest', 'testPublicZIndex begin');
      let driver = Driver.create();
      await driver.delayMs(1000);

      try {
        // 点击Public进入通用属性界面
        const button1 = await driver.findComponent(ON.id('Public'));
        await button1.click();
        await driver.delayMs(1000);

        // 滑动到测试区域
        const scroll = await driver.findComponent(ON.id('testScroll'));
        await scroll.scrollSearch(ON.id('zIndexText3'));
        await driver.delayMs(500);

        // 验证enabledButton获得设置的enabled的值
        let strJson = getInspectorByKey('zIndexText3');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'PublicTest', 'zIndexText3 zIndex: %{public}s', obj.$attrs.zIndex);
        expect(obj.$attrs.zIndex).assertEqual(0);

        let strJson1 = getInspectorByKey('zIndexText2');
        let obj1: ESObject = JSON.parse(strJson1);
        hilog.info(0x0000, 'PublicTest', 'zIndexText2 zIndex: %{public}s', obj1.$attrs.zIndex);
        expect(obj1.$attrs.zIndex).assertEqual(1);

        let strJson2 = getInspectorByKey('zIndexText1');
        let obj2: ESObject = JSON.parse(strJson2);
        hilog.info(0x0000, 'PublicTest', 'zIndexText1 zIndex: %{public}s', obj2.$attrs.zIndex);
        expect(obj2.$attrs.zIndex).assertEqual(2);

      } catch (error) {
        hilog.error(0x0000, 'PublicTest', 'testPublicZIndex failed: %{public}s', error.message);
      }

      hilog.info(0x0000, 'PublicTest', 'testPublicZIndex end');
      done();
    })

    /**
     * @tc.number PublicTest_004
     * @tc.name testPublicVisibility
     * @tc.desc 测试visibility属性设置 - 打开Public界面，查看设置的Row组件visibility属性
     */
    it('testPublicVisibility', 0, async (done: Function) => {
      hilog.info(0x0000, 'PublicTest', 'testPublicVisibility begin');
      let driver = Driver.create();
      await driver.delayMs(1000);

      try {
        // 点击Public进入通用属性界面
        const button1 = await driver.findComponent(ON.id('Public'));
        await button1.click();
        await driver.delayMs(1000);

        // 验证visibilityRow获得设置的visibility的值
        let strJson2 = getInspectorByKey('visibilityRow3');
        let obj2: ESObject = JSON.parse(strJson2);
        hilog.info(0x0000, 'PublicTest', ' visibilityRow3: %{public}s', obj2.$attrs.visibility);
        expect(obj2.$attrs.visibility).assertEqual('Visibility.Visible');

      } catch (error) {
        hilog.error(0x0000, 'PublicTest', 'testPublicVisibility failed: %{public}s', error.message);
      }
      hilog.info(0x0000, 'PublicTest', 'testPublicVisibility end');
      done();
    })
  })
}