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
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect, TestType } from '@ohos/hypium';
import { abilityDelegatorRegistry, Driver, ON, MouseButton, Component } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

export default function InputEventTest() {
  describe('InputEventTest', () => {

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
    })

    afterEach(() => {
      hilog.info(0x0000, 'InputEventTest', 'InputEvent interface test case completed');
    })

    afterAll(() => {
      hilog.info(0x0000, 'InputEventTest', 'All inputEvent interface tests completed');
    })

    /**
     * @tc.number InputEventTest_001
     * @tc.name testTouchInput
     * @tc.desc 测试默认输入事件接口 - 监听触摸事件监听，及克隆事件接口
     */
    it('testTouchInput', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'InputEventTest', 'testTouchInput begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(1000);
        // 点击按钮1触发事件
        const button = await driver.findComponent(ON.id('bt'));
        await button.longClick();
        await driver.delayMs(1000);
      } catch (error) {
        hilog.error(0x0000, 'InputEventTest', 'testTouchInput failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'InputEventTest', 'testTouchInput end');
    })

    /**
     * @tc.number InputEventTest_002
     * @tc.name testMouseInput
     * @tc.desc 测试鼠标输入事件接口 - 测试鼠标悬停事件及点击事件监听
     */
    it('testMouseInput', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'InputEventTest', 'testMouseInput begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(1000);
        let button: Component = await driver.findComponent(ON.id('bt'));
        let point = await button.getBoundsCenter();
        // 移动鼠标，触发悬停事件
        await driver.mouseMoveWithTrack({ x: point.x, y: point.y + 200 }, { x: point.x, y: point.y });
        let btObj: ESObject = JSON.parse(getInspectorByKey('bt'));
        hilog.info(0x0000, 'InputEventTest', 'testMouseInput buttonColor: %{public}s',
          JSON.stringify(btObj.$attrs.backgroundColor));
        expect(btObj.$attrs.backgroundColor).assertEqual('#FF009F40');
        await driver.delayMs(1000);
        // 鼠标左键单击，触发鼠标按下/释放事件
        await driver.mouseLongClick({ x: point.x, y: point.y }, MouseButton.MOUSE_BUTTON_LEFT);
        await driver.delayMs(1000);
      } catch (error) {
        hilog.error(0x0000, 'InputEventTest', 'testMouseInput failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'InputEventTest', 'testMouseInput end');
    })

    /**
     * @tc.number InputEventTest_003
     * @tc.name testMouseScrollInput
     * @tc.desc 测试轴事件接口 - 测试鼠标滚轮触发轴事件信息
     */
    it('testMouseScrollInput', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'InputEventTest', 'testMouseScrollInput begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(1000);
        let button2: Component = await driver.findComponent(ON.id('bt'));
        let point2 = await button2.getBoundsCenter();
        // 鼠标滚轮滚动，触发轴事件
        await driver.mouseScroll({ x: point2.x, y: point2.y }, true, 30);
        await driver.delayMs(1000);
      } catch (error) {
        hilog.error(0x0000, 'InputEventTest', 'testMouseScrollInput failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'InputEventTest', 'testMouseScrollInput end');
    })

    /**
     * @tc.number InputEventTest_004
     * @tc.name testTouchProInput
     * @tc.desc 测试触摸事件冒泡接口 - 监听触摸事件，并阻止事件向上冒泡
     */
    it('testTouchProInput', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'InputEventTest', 'testTouchProInput begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(1000);
        // 点击按钮2触发事件，由于阻止事件冒泡，背景不会发生改变
        const button = await driver.findComponent(ON.id('bt2'));
        await button.longClick();
        await driver.delayMs(1000);
      } catch (error) {
        hilog.error(0x0000, 'InputEventTest', 'testTouchProInput failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'InputEventTest', 'testTouchProInput end');
    })

    /**
     * @tc.number InputEventTest_005
     * @tc.name testKeyInput
     * @tc.desc 测试按键输入事件接口 - 测试按键事件监听
     */
    it('testKeyInput', TestType.FUNCTION, async (done: Function) => {
      hilog.info(0x0000, 'InputEventTest', 'testKeyInput begin');
      try {
        let driver = Driver.create();
        await driver.delayMs(1000);
        // 按Tab键，验证按钮获焦
        await driver.triggerKey(2049);
        const button = await driver.findComponent(ON.id('bt'));
        const flag = await button.isFocused();
        await driver.delayMs(1000);
        expect(flag).assertTrue();
      } catch (error) {
        hilog.error(0x0000, 'InputEventTest', 'testKeyInput failed: %{public}s', error.message);
        expect().assertFail();
      }
      done();
      hilog.info(0x0000, 'InputEventTest', 'testKeyInput end');
    })

  })
}
