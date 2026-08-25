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

import AbilityDelegatorRegistry from '@ohos.app.ability.abilityDelegatorRegistry';
import { describe, it, expect } from '@ohos/hypium';
import { Driver, MatchPattern, ON, MouseButton } from '@ohos.UiTest';

const TAG = '[Sample_Native_XComponent]';

export default function abilityTest() {

  describe('ActsAbilityTest', () => {
    /**
     * 打开应用
     */
    it('StartAbility_001', 0, async (done: Function) => {
      console.info(TAG, 'StartAbility_001 begin');
      let driver = Driver.create();
      let abilityDelegator = AbilityDelegatorRegistry.getAbilityDelegator();
      try {
        await abilityDelegator.startAbility({
          bundleName: 'com.example.nativexcomponent',
          abilityName: 'EntryAbility'
        });
      } catch (exception) {
        console.info(TAG, `StartAbility_001 exception = ${JSON.stringify(exception)}`);
        expect().assertFail();
      }
      await driver.delayMs(1000);
      // 判断XComponent onLoad回调执行成功
      await driver.assertComponentExist(ON.text('期望帧率设置：'));
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.text('创建/销毁'));
      await driver.assertComponentExist(ON.text('needSoftKeyboard=',MatchPattern.STARTS_WITH));
      done();
      console.info(TAG, 'StartAbility_001 end');
    })

    /**
     * 点击按钮，按钮
     */
    it('DrawShape_001', 2, async (done: Function) => {
      console.info(TAG, 'CreateFiles_001 begin');
      let driver = Driver.create();
      // 判断XComponent onLoad回调执行成功
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.id('xcp',MatchPattern.STARTS_WITH));
      // 判断是否有按键
      await driver.assertComponentExist(ON.text('创建/销毁'));
      let drawStarBtn = await driver.findComponent(ON.text('创建/销毁'));
      // 点击'创建/销毁'按钮
      await drawStarBtn.click();
      await driver.delayMs(1000);

      // 判断xcomponent组件已经消失
      let xcomponent = await driver.findComponent(ON.id('xcp', MatchPattern.STARTS_WITH));
      expect(xcomponent === null).assertTrue();

      await drawStarBtn.click();
      await driver.delayMs(1000);
      // 判断xcomponent组件复现
      let xcomponent2 = await driver.findComponent(ON.id('xcp', MatchPattern.STARTS_WITH));
      expect(xcomponent2 === null).assertFalse();
      done();
      console.info(TAG, 'DrawShape_001 end');
    })

    it('DrawShape_002', 2, async (done: Function) => {
      console.info(TAG, 'DrawShape_002 begin');
      let driver = Driver.create();
      // 判断XComponent onLoad回调执行成功
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.id('xcp',MatchPattern.STARTS_WITH));
      // 判断是否有按键
      await driver.assertComponentExist(ON.text('创建/销毁'));

      // 点击XComponent组件
      let xcomponent = await driver.findComponent(ON.id('xcp', MatchPattern.STARTS_WITH));
      expect(xcomponent === null).assertFalse();
      await xcomponent.click();
      await driver.delayMs(1000);
      // 判断touch回调已执行
      await driver.assertComponentExist(ON.id('xcp',MatchPattern.STARTS_WITH));
      done();
      console.info(TAG, 'DrawShape_002 end');
    })

    it('SetExpectedFrameRate_001 ', 2, async (done: Function) => {
      console.info(TAG, 'SetExpectedFrameRate_001 start');
      let driver = await Driver.create();
      await driver.delayMs(1000);
      await driver.assertComponentExist(ON.text('期望帧率设置：'));
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.text('创建/销毁'));
      await driver.assertComponentExist(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH));

      let minBtn = await driver.findComponent(ON.text('min', MatchPattern.STARTS_WITH));
      expect(minBtn === null).assertFalse();

      let minSlider = await driver.findComponent(ON.id('minSlider'));
      expect(minSlider === null).assertFalse();
      let point = await minSlider.getBoundsCenter();
      await driver.mouseClick(point, MouseButton.MOUSE_BUTTON_LEFT);
      await driver.delayMs(1000);

      let text = await minBtn.getText();
      expect(text.toString() == 'min: 120').assertTrue();

      done();
      console.info(TAG, 'SetExpectedFrameRate_001 end');
    })

    it('SetExpectedFrameRate_002 ', 2, async (done: Function) => {
      console.info(TAG, 'SetExpectedFrameRate_002 start');
      let driver = await Driver.create();
      await driver.delayMs(1000);
      await driver.assertComponentExist(ON.text('期望帧率设置：'));
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.text('创建/销毁'));
      await driver.assertComponentExist(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH));

      let maxBtn = await driver.findComponent(ON.text('max', MatchPattern.STARTS_WITH));
      expect(maxBtn === null).assertFalse();

      let maxSlider = await driver.findComponent(ON.id('maxSlider'));
      expect(maxSlider === null).assertFalse();
      let rect = await maxSlider.getBounds();
      await driver.mouseClick({x:rect.right, y:(rect.top+rect.bottom)/2}, MouseButton.MOUSE_BUTTON_LEFT);
      await driver.delayMs(1000);

      let text = await maxBtn.getText();
      expect(text.toString() == 'max: 240').assertTrue();

      done();
      console.info(TAG, 'SetExpectedFrameRate_002 end');
    })

    it('SetExpectedFrameRate_003 ', 2, async (done: Function) => {
      console.info(TAG, 'SetExpectedFrameRate_003 start');
      let driver = await Driver.create();
      await driver.delayMs(1000);
      await driver.assertComponentExist(ON.text('期望帧率设置：'));
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.text('创建/销毁'));
      await driver.assertComponentExist(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH));

      let expectedBtn = await driver.findComponent(ON.text('expected', MatchPattern.STARTS_WITH));
      expect(expectedBtn === null).assertFalse();

      let expectedSlider = await driver.findComponent(ON.id('expectedSlider'));
      expect(expectedSlider === null).assertFalse();
      let point = await expectedSlider.getBoundsCenter();
      await driver.mouseClick(point, MouseButton.MOUSE_BUTTON_LEFT);
      await driver.delayMs(1000);

      let text = await expectedBtn.getText();
      expect(text.toString() == 'expected: 120').assertTrue();

      done();
      console.info(TAG, 'SetExpectedFrameRate_003 end');
    })

    it('SetSoftKeyboard_001', 2, async (done: Function) => {
      console.info(TAG, 'SetSoftKeyboard_001 start');
      let driver = Driver.create();
      await driver.delayMs(1000);
      await driver.assertComponentExist(ON.text('期望帧率设置：'));
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.text('创建/销毁'));
      await driver.assertComponentExist(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH));

      let text = await driver.findComponent(ON.id('textInput'));
      expect(text === null).assertFalse();
      await text.click();
      await driver.delayMs(1000);
      expect(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH) == null).assertFalse();

      // 点击XComponent组件
      let xcomponent = await driver.findComponent(ON.id('xcp', MatchPattern.STARTS_WITH));
      expect(xcomponent === null).assertFalse();
      await xcomponent.click();
      await driver.delayMs(1000);

      done();
      console.info(TAG, 'SetSoftKeyboard_001 end');
    })

    it('SetSoftKeyboard_002', 2, async (done: Function) => {
      console.info(TAG, 'SetSoftKeyboard_002 start');
      let driver = Driver.create();
      await driver.delayMs(1000);
      await driver.assertComponentExist(ON.text('期望帧率设置：'));
      await driver.assertComponentExist(ON.text('单指点击XComponent软键盘消失'));
      await driver.assertComponentExist(ON.text('创建/销毁'));
      await driver.assertComponentExist(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH));

      let button_softKeyboard = await driver.findComponent(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH));
      expect(button_softKeyboard === null).assertFalse();
      await button_softKeyboard.click();
      let text = await driver.findComponent(ON.id('textInput'));
      expect(text === null).assertFalse();
      await text.click();
      await driver.delayMs(1000);
      expect(ON.text('needSoftKeyboard', MatchPattern.STARTS_WITH) == null).assertFalse();

      // 点击XComponent组件
      let xcomponent = await driver.findComponent(ON.id('xcp', MatchPattern.STARTS_WITH));
      expect(xcomponent === null).assertFalse();
      await xcomponent.click();
      await driver.delayMs(1000);

      done();
      console.info(TAG, 'SetSoftKeyboard_002 end');
    })
  })
}