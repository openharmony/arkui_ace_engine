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


export default function GridColBootcampTest() {
  describe('GridColBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);

        let atomDisplays: Component = await driver.findComponent(ON.text('栅格与分栏'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('栅格列/GridCol'))
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
    it('ArkUI_GridCol_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'span.xs');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.xs'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '8'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.xs',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'span.sm');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.sm'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '8'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.sm',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'span.md');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.md'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.md',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();

    })
    it('ArkUI_GridCol_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'span.lg');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.lg'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.lg',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();

    })
    it('ArkUI_GridCol_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'span.xl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.xl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.xl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();

    })
    it('ArkUI_GridCol_0006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'span.xxl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.xxl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'span.xxl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('span', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();

    })
    it('ArkUI_GridCol_0007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'offset.xs');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.xs'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.xs',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'offset.sm');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.sm'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.sm',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'offset.md');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.md'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.md',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'offset.lg');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.lg'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.lg',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'offset.xl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.xl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.xl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'offset.xxl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.xxl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'offset.xxl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'order.xs');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.xs'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '10'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.xs',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'order.sm');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.sm'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '10'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.sm',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'order.md');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.md'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.md',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'order.lg');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.lg'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.lg',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'order.xl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.xl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.xl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'order.xxl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.xxl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'order.xxl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('order', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gridColOffset');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'gridColOffset'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gridColOffset', JsonType.value)
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridCol',
        toggleClick: {
          toggleClickObj: 'gridColOffset',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gridColOffset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();

    })
    it('ArkUI_GridCol_0020', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'lineHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'lineHeight'
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'lineHeight',
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_GridCol_0021', 0, async (done: Function) => {
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
    it('ArkUI_GridCol_0022', 0, async (done: Function) => {
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
    it('ArkUI_GridCol_0023', 0, async (done: Function) => {
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
    it('ArkUI_GridCol_0024', 0, async (done: Function) => {
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
    it('ArkUI_GridCol_0025', 0, async (done: Function) => {
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