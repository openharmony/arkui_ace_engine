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
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  Search,
  titleSearch,
} from '../../../utils/index';
import { On, Point } from '@ohos.UiTest';
import { FlexStart } from '../../../utils/RowsColumnsAndStacking/Flex';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function Flex6Test() {
  describe('Flex6Test', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
      await FlexStart(done)
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
    // focusable
    it('ArkUI_Flex_Comp_0461', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Flex_Comp_0462', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_Flex_Comp_0463', 0, async (done: Function) => {
      //设置当前组件是否为当前页面上的默认焦点，仅在初次创建的页面第一次进入时生效。
      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Flex_Comp_0464', 0, async (done: Function) => {

      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // groupDefaultFocus
    it('ArkUI_Flex_Comp_0465', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Flex_Comp_0466', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusOnTouch
    it('ArkUI_Flex_Comp_0467', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Flex_Comp_0468', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Flex',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_Flex_Comp_0469', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.margin', '通用属性3')

      // 取不到focusBox值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // focusBox.strokeColor
    it('ArkUI_Flex_Comp_0470', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      // 取不到focusBox值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Flex_Comp_0471', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      // 取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Flex_Comp_0472', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      // 取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Flex_Comp_0473', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      // 取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Flex_Comp_0474', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      // 取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Flex_Comp_0475', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      // 取不到focusBox值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // focusBox.strokeWidth
    it('ArkUI_Flex_Comp_0476', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeWidth', '通用属性3')

      // 取不到focusBox值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })
  })
}