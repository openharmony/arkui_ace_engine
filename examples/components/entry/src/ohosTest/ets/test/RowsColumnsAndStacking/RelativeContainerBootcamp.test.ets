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


export default function RelativeContainerBootcampTest() {
  describe('RelativeContainerBootcampTest', () => {
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

        let scrollSearch: Component = await driver.findComponent(ON.text('相对布局/RelativeContainer'))
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
    it('ArkUI_RelativeContainer_0001', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'guideLine.direction');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'guideLine.direction'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0002', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'guideLine.direction');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'guideLine.direction',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0003', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'guideLine.position.start');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'guideLine.position.start'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'guideLine.position.start'
        }
      })
      done();

    })
    it('ArkUI_RelativeContainer_0004', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'guideLine.position.end');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'guideLine.position.end'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'guideLine.position.end'
        }
      })
      done();

    })
    it('ArkUI_RelativeContainer_0005', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.direction');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barrier.direction'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0006', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.direction');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barrier.direction'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0007', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.direction');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barrier.direction'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0008', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.direction');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'barrier.direction'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0009', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.localizedDirection');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barrier.localizedDirection'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0010', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.localizedDirection');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barrier.localizedDirection'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0011', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.localizedDirection');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'barrier.localizedDirection'
        }
      })
      done();
    })
    it('ArkUI_RelativeContainer_0012', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'barrier.localizedDirection');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'barrier.localizedDirection'
        }
      })
      done();
    })
  })
}