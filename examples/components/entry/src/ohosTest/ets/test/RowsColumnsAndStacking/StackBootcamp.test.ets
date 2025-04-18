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


export default function StackBootcampTest() {
  describe('StackBootcampTest', () => {
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

        let scrollSearch: Component = await driver.findComponent(ON.text('层叠布局/Stack'))
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
    it('ArkUI_Stack_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignContent');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'alignContent'
        },
        id: 'Stack',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'Alignment.Start'
      })
      done();
    })
    it('ArkUI_Stack_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignContent');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'alignContent'
        },
        id: 'Stack',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'Alignment.Center'
      })
      done();
    })
    it('ArkUI_Stack_0003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignContent');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'alignContent'
        },
        id: 'Stack',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'Alignment.End'
      })
      done();
    })
    it('ArkUI_Stack_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignContent');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'alignContent'
        },
        id: 'Stack',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'Alignment.Top'
      })
      done();
    })
    it('ArkUI_Stack_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignContent');
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'alignContent'
        },
        id: 'Stack',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignContent', JsonType.value)
        ],
        assertEqual: 'Alignment.Bottom'
      })
      done();
    })
    it('ArkUI_Stack_0006', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.type');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'decoration.value.type'
        }
      })
      done();
    })
    it('ArkUI_Stack_0007', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.type');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'decoration.value.type'
        }
      })
      done();
    })
    it('ArkUI_Stack_0008', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.type');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'decoration.value.type'
        }
      })
      done();
    })
    it('ArkUI_Stack_0009', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.type');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'decoration.value.type',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    it('ArkUI_Stack_0010', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.color');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'decoration.value.color'
        }
      })

      done();

    })
    it('ArkUI_Stack_0011', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.color');
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'decoration.value.color'
        }
      })

      done();

    })
    it('ArkUI_Stack_0012', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.color');
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'decoration.value.color'
        }
      })

      done();

    })
    it('ArkUI_Stack_0013', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.color');
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'decoration.value.color'
        }
      })

      done();

    })
    it('ArkUI_Stack_0014', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.color');
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'decoration.value.color'
        }
      })

      done();

    })
    it('ArkUI_Stack_0015', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.color');
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'decoration.value.color'
        }
      })

      done();

    })
    it('ArkUI_Stack_0016', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.style');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'decoration.value.style'
        }
      })
      done();
    })
    it('ArkUI_Stack_0017', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.style');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'decoration.value.style'
        }
      })
      done();
    })
    it('ArkUI_Stack_0018', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.style');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'decoration.value.style'
        }
      })
      done();
    })
    it('ArkUI_Stack_0019', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.style');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'decoration.value.style'
        }
      })
      done();
    })
    it('ArkUI_Stack_0020', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'decoration.value.style');
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'decoration.value.style',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
  })
}