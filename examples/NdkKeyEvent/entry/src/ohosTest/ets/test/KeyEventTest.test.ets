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

export default function KeyEventTest() {
  describe('KeyEventTest', () => {

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
      hilog.info(0x0000, 'KeyEventTest', 'Key event test case completed');
    })

    afterAll(() => {
      hilog.info(0x0000, 'KeyEventTest', 'All key event tests completed');
    })

    /**
     * @tc.number KeyEvent_001  
     * @tc.name testButton1KeyEvent
     * @tc.desc 测试Button1按键事件 - 滑动到Button1，点击获焦，按键A，验证颜色变化
     */
    it('testButton1KeyEvent', 0, async (done: Function) => {
      hilog.info(0x0000, 'KeyEventTest', 'testButton1KeyEvent begin');
      let driver = Driver.create();
      await driver.delayMs(1000);
      
      try {
        // 滑动到Button1的位置
        const scroll = await driver.findComponent(ON.id('testScroll'));
        await scroll.scrollSearch(ON.id('testKeyEvent'));
        await driver.delayMs(500);
        
        // 点击Button1获取焦点
        const button1 = await driver.findComponent(ON.id('Button1'));
        await button1.click();
        await driver.delayMs(1000);
        
        // 验证Button1获得焦点后的颜色变化（焦点状态下的颜色）
        let strJson = getInspectorByKey('Button1');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button1 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        // 焦点状态下应该是更亮的蓝色 0xFF2E86DE
        expect(obj.$attrs.backgroundColor).assertEqual('#FF2E86DE');
        
        // 按键A，验证按键事件处理
        await driver.triggerKey(2017); // KEY_A
        await driver.delayMs(1000);
        
        // 验证按键事件处理后Button1变浅红色
        strJson = getInspectorByKey('Button1');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button1 after key A backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFFEBEE');
        
      } catch (error) {
        hilog.error(0x0000, 'KeyEventTest', 'testButton1KeyEvent failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'KeyEventTest', 'testButton1KeyEvent end');
      done();
    })

    /**
     * @tc.number KeyEvent_002
     * @tc.name testButton2PreIME
     * @tc.desc 测试Button2预输入法按键事件 - Button2获焦，测试PreIme事件类型
     */
    it('testButton2PreIME', 0, async (done: Function) => {
      hilog.info(0x0000, 'KeyEventTest', 'testButton2PreIME begin');
      let driver = Driver.create();
      await driver.delayMs(1000);
      
      try {
        // 滑动到测试区域
        const scroll = await driver.findComponent(ON.id('testScroll'));
        await scroll.scrollSearch(ON.id('testKeyEvent'));
        await driver.delayMs(1500);
        
        // 点击Button2获取焦点
        const button2 = await driver.findComponent(ON.id('Button2'));
        await button2.click();
        await driver.delayMs(1000);
        
        // 验证Button2获得焦点后的颜色变化
        let strJson = getInspectorByKey('Button2');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button2 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FF2E86DE');
        
        // 按键B测试PreIME事件
        await driver.triggerKey(2018); // KEY_B
        await driver.delayMs(1000);
        
        // 验证PreIME事件处理后Button2变浅红色
        strJson = getInspectorByKey('Button2');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button2 after key B backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFFEBEE');
        
      } catch (error) {
        hilog.error(0x0000, 'KeyEventTest', 'testButton2PreIME failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'KeyEventTest', 'testButton2PreIME end');
      done();
    })

    /**
     * @tc.number KeyEvent_003
     * @tc.name testButton3Dispatch  
     * @tc.desc 测试Button3分发按键事件 - Button3获焦，测试Dispatch事件类型
     */
    it('testButton3Dispatch', 0, async (done: Function) => {
      hilog.info(0x0000, 'KeyEventTest', 'testButton3Dispatch begin');
      let driver = Driver.create();
      await driver.delayMs(1000);
      
      try {
        // 滑动到测试区域
        const scroll = await driver.findComponent(ON.id('testScroll'));
        await scroll.scrollSearch(ON.id('testKeyEvent'));
        await driver.delayMs(500);
        
        // 点击Button3获取焦点
        const button3 = await driver.findComponent(ON.id('Button3'));
        await button3.click();
        await driver.delayMs(1000);
        
        // 验证Button3获得焦点后的颜色变化
        let strJson = getInspectorByKey('Button3');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button3 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FF2E86DE');
        
        // 按键C测试Dispatch事件
        await driver.triggerKey(2019); // KEY_C
        await driver.delayMs(1000);
        
        // 验证Dispatch事件处理后Button3变浅红色
        strJson = getInspectorByKey('Button3');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button3 after key C backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFFEBEE');
        
      } catch (error) {
        hilog.error(0x0000, 'KeyEventTest', 'testButton3Dispatch failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'KeyEventTest', 'testButton3Dispatch end');
      done();
    })

    /**
     * @tc.number KeyEvent_004
     * @tc.name testButton4EventControl
     * @tc.desc 测试Button4事件控制 - Button4获焦，测试ESC、F1和A键，验证父组件颜色变化
     */
    it('testButton4EventControl', 0, async (done: Function) => {
      hilog.info(0x0000, 'KeyEventTest', 'testButton4EventControl begin');
      let driver = Driver.create();
      await driver.delayMs(1000);
      
      try {
        // 滑动到测试区域
        const scroll = await driver.findComponent(ON.id('testScroll'));
        await scroll.scrollSearch(ON.id('testKeyEvent'));
        await driver.delayMs(500);
        
        // 点击Button4获取焦点
        const button4 = await driver.findComponent(ON.id('Button4'));
        await button4.click();
        await driver.delayMs(1000);
        
        // 验证Button4获得焦点后的颜色变化
        let strJson = getInspectorByKey('Button4');
        let obj: ESObject = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button4 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FF2E86DE');
        
        // 测试ESC键 - 应该被消费，父组件不变色
        await driver.triggerKey(2070); // ESC键
        await driver.delayMs(1000);

        // 父组件背景色应该保持正常状态 0xFFE8F5E8
        strJson = getInspectorByKey('parentColumn');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button4 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FF2E86DE');
        hilog.info(0x0000, 'KeyEventTest', 'After ESC key - parent should not change color');
        
        // 测试F1键 - 应该阻止传播，父组件不变色  
        await driver.triggerKey(2090); // F1键
        await driver.delayMs(1000);
        // 父组件背景色应该保持正常状态 0xFFE8F5E8
        strJson = getInspectorByKey('parentColumn');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button4 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FF2E86DE');
        
        hilog.info(0x0000, 'KeyEventTest', 'After F1 key - parent should not change color');
        
        // 测试A键 - 应该正常传播，父组件变色
        await driver.triggerKey(2017); // KEY_A
        await driver.delayMs(1000);

        strJson = getInspectorByKey('parentColumn');
        obj = JSON.parse(strJson);
        hilog.info(0x0000, 'KeyEventTest', 'Button4 focus backgroundColor: %{public}s', obj.$attrs.backgroundColor);
        expect(obj.$attrs.backgroundColor).assertEqual('#FFFFEBEE');
        
        hilog.info(0x0000, 'KeyEventTest', 'After A key - parent should change color');
      } catch (error) {
        hilog.error(0x0000, 'KeyEventTest', 'testButton4EventControl failed: %{public}s', error.message);
        expect().assertFail();
      }

      hilog.info(0x0000, 'KeyEventTest', 'testButton4EventControl end');
      done();
    })

  })
}
