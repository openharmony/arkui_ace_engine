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
  getToggle,
  searchToggle
} from '../../utils/index';
import { On, Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function FlexBootcampTest() {
  describe('FlexBootcampTest', () => {
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

        let scrollSearch: Component = await driver.findComponent(ON.text('弹性布局/Flex'))
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
    it('ArkUI_Flex_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'FlexDirection.Row'
      })
      done();
    })
    it('ArkUI_Flex_0002', 0, async (done: Function) => {
      await searchParentBlock('direction', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'FlexDirection.RowReverse'
      })
      done();
    })
    it('ArkUI_Flex_0003', 0, async (done: Function) => {
      await searchParentBlock('direction', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'FlexDirection.Column'
      })
      done();
    })
    it('ArkUI_Flex_0004', 0, async (done: Function) => {
      await searchParentBlock('direction', true, '参数列表');
      await radioClick({
        radioClickObj: 3,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'FlexDirection.ColumnReverse'
      })
      done();
    })
    it('ArkUI_Flex_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'wrap');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('wrap', JsonType.value)
        ],
        assertEqual: 'FlexWrap.Wrap'
      })
      done();
    })
    it('ArkUI_Flex_0006', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('wrap', JsonType.value)
        ],
        assertEqual: 'FlexWrap.NoWrap'
      })
      done();
    })
    it('ArkUI_Flex_0007', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('wrap', JsonType.value)
        ],
        assertEqual: 'FlexWrap.WrapReverse'
      })
      done();
    })
    it('ArkUI_Flex_0008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'justifyContent');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Start'
      })
      done();
    })
    it('ArkUI_Flex_0009', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Center'
      })
      done();
    })
    it('ArkUI_Flex_0010', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.End'
      })
      done();
    })
    it('ArkUI_Flex_0011', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 3,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceBetween'
      })
      done();
    })
    it('ArkUI_Flex_0012', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 4,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceAround'
      })
      done();
    })
    it('ArkUI_Flex_0013', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 5,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceEvenly'
      })
      done();
    })
    it('ArkUI_Flex_0014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'ItemAlign.Auto'
      })
      done();
    })
    it('ArkUI_Flex_0015', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'ItemAlign.Start'
      })
      done();
    })
    it('ArkUI_Flex_0016', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'ItemAlign.Center'
      })
      done();
    })
    it('ArkUI_Flex_0017', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 3,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'ItemAlign.End'
      })
      done();
    })
    it('ArkUI_Flex_0018', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 4,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'ItemAlign.Stretch'
      })
      done();
    })
    it('ArkUI_Flex_0019', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 5,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'ItemAlign.Baseline'
      })
      done();
    })
    it('ArkUI_Flex_0020', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
      })
      await titleSearch('参数列表', 'alignContent');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Start'
      })
      await searchParentBlock('wrap', false, '参数列表');
      done();
    })
    it('ArkUI_Flex_0021', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
      })
      await searchParentBlock('alignContent', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Center'
      })
      await searchParentBlock('wrap', false, '参数列表');
      done();
    })
    it('ArkUI_Flex_0022', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
      })
      await searchParentBlock('alignContent', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.End'
      })
      await searchParentBlock('wrap', false, '参数列表');
      done();
    })
    it('ArkUI_Flex_0023', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
      })
      await searchParentBlock('alignContent', true, '参数列表');
      await radioClick({
        radioClickObj: 3,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceBetween'
      })
      await searchParentBlock('wrap', false, '参数列表');
      done();
    })
    it('ArkUI_Flex_0024', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
      })
      await searchParentBlock('alignContent', true, '参数列表');
      await radioClick({
        radioClickObj: 4,
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceAround'
      })
      await searchParentBlock('wrap', false, '参数列表');
      done();
    })
    it('ArkUI_Flex_0025', 0, async (done: Function) => {
      await searchParentBlock('wrap', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
      })
      await searchParentBlock('alignContent', true, '参数列表');
      await radioClick({
        radioClickObj: 5,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constructor', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceEvenly'
      })
      await searchParentBlock('wrap', false, '参数列表');
      done();
    })
    it('ArkUI_Flex_0026', 0, async (done: Function) => {
      await searchParentBlock('space.main.LengthMetrics.px', false, '参数列表');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'space.main.LengthMetrics.px'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '100.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'space.main.LengthMetrics.px'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      await driver.delayMs(1000);
      done();

    })
    it('ArkUI_Flex_0027', 0, async (done: Function) => {
      await searchParentBlock('space.cross.LengthMetrics.px', false, '参数列表');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'space.cross.LengthMetrics.px'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '0.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Flex',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'space.cross.LengthMetrics.px'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      await driver.delayMs(1000);
      done();

    })

  })
}

