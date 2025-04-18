/*
 * Copyright (c) 2025 Hunan OpenValley Digital Industry Development Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  Search,
  searchParentBlock,
  searchRadio,
  titleSearch,
  searchToggle,
  getToggle
} from '../../utils/index';
import { On, Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function ColumnBootcampTest() {
  describe('ColumnBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);

        let atomDisplays: Component = await driver.findComponent(ON.text('行列与堆叠'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('纵向布局/Column'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(() => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })
    it('ArkUI_Column_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'space');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '10.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done();

    })
    it('ArkUI_Column_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'HorizontalAlign.Start'
      })
      done();
    })
    it('ArkUI_Column_0003', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'HorizontalAlign.Center'
      })
      done();
    })
    it('ArkUI_Column_0004', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'HorizontalAlign.End'
      })
      await searchParentBlock('alignItems', false, '参数列表');
      done();
    })
    it('ArkUI_Column_0005', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Start'
      })
      done();
    })
    it('ArkUI_Column_0006', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Center'
      })
      done();
    })
    it('ArkUI_Column_0007', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.End'
      })
      done();
    })
    it('ArkUI_Column_0008', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 3,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceBetween'
      })
      done();
    })
    it('ArkUI_Column_0009', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 4,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceAround'
      })
      done();
    })
    it('ArkUI_Column_0010', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 5,
        id: 'Column',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceEvenly'
      })
      await searchParentBlock('justifyContent', false, '参数列表');
      done();
    })
    it('ArkUI_Column_0011', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('reverse', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'reverse'
        }
      })
      done();
    })
    it('ArkUI_Column_0012', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('reverse', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'reverse'
        }
      })
      done();
    })
  })
}