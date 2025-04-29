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

import { describe, beforeAll, it } from '@ohos/hypium'
import { Component, Driver, ON } from '@kit.TestKit';
import { GridStart } from './Grid';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';

const driver = Driver.create();

export default function Grid1Test() {
  describe('Grid1Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await GridStart(done)

    })
    /**
     * 测试组件layoutDirection且获取属性正确
     */
    it('ArkUI_Grid_0028', 0, async (done: Function) => {

      await Search('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'layoutDirection',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'GridDirection.Column'
      })

      done();
    })

    it('ArkUI_Grid_0029', 0, async (done: Function) => {

      await Search('参数列表', 'layoutDirection')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'layoutDirection',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'GridDirection.ColumnReverse'
      })

      done();
    })

    it('ArkUI_Grid_0030', 0, async (done: Function) => {

      await Search('参数列表', 'layoutDirection')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'layoutDirection',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'GridDirection.Row'
      })

      done();
    })

    it('ArkUI_Grid_0031', 0, async (done: Function) => {

      await Search('参数列表', 'layoutDirection')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'layoutDirection',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'GridDirection.RowReverse'
      })

      done();
    })
    /**
     * 测试组件maxCount且获取属性正确
     */
    it('ArkUI_Grid_0032', 0, async (done: Function) => {
      await Search('参数列表', 'maxCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'maxCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxCount', JsonType.value),
        ],
        assertEqual: 10
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'maxCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxCount', JsonType.value),
        ],
        assertEqual: 1
      })

      done();
    })
    /**
     * 测试组件minCount且获取属性正确
     */
    it('ArkUI_Grid_0033', 0, async (done: Function) => {
      await Search('参数列表', 'minCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'minCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minCount', JsonType.value),
        ],
        assertEqual: 10
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'minCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minCount', JsonType.value),
        ],
        assertEqual: 1
      })

      done();
    })
    /**
     * 测试组件cellLength且获取属性正确
     */
    it('ArkUI_Grid_0034', 0, async (done: Function) => {
      await Search('参数列表', 'cellLength')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'cellLength',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cellLength', JsonType.value),
        ],
        assertEqual: 10
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'cellLength',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cellLength', JsonType.value),
        ],
        assertEqual: 1
      })

      done();
    })
    /**
     * 测试组件multiSelectable
     */
    it('ArkUI_Grid_0035', 0, async (done: Function) => {
      //获取不到子组件状态
      await Search('参数列表', 'multiSelectable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'multiSelectable',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Grid_0036', 0, async (done: Function) => {
      await Search('参数列表', 'multiSelectable')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'multiSelectable',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件supportAnimation
     */
    it('ArkUI_Grid_0037', 0, async (done: Function) => {
      //无法取到子组件状态
      await titleSearch('参数列表', 'supportAnimation')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'supportAnimation',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Grid_0038', 0, async (done: Function) => {

      await titleSearch('参数列表', 'supportAnimation')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'supportAnimation',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件edgeEffect.options.alwaysEnabled且获取属性正确
     */
    it('ArkUI_Grid_0039', 0, async (done: Function) => {

      await Search('参数列表', 'edgeEffect.options.alwaysEnabled')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'edgeEffect.options.alwaysEnabled',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffectOptions', JsonType.obj),
          new KeyStruct('alwaysEnabled', JsonType.value),
        ],
        assertEqual: true
      })

      done();
    })

    it('ArkUI_Grid_0040', 0, async (done: Function) => {

      await Search('参数列表', 'edgeEffect.options.alwaysEnabled')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'edgeEffect.options.alwaysEnabled',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffectOptions', JsonType.obj),
          new KeyStruct('alwaysEnabled', JsonType.value),
        ],
        assertEqual: false

      })

      done();
    })
    /**
     * 测试组件nestedScroll.scrollForward且获取属性正确
     */
    it('ArkUI_Grid_0041', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollForward')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollForward',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'

      })

      done();
    })

    it('ArkUI_Grid_0042', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollForward',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      })

      done();
    })

    it('ArkUI_Grid_0043', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollForward',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      })

      done();
    })

    it('ArkUI_Grid_0044', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollForward',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      })

      done();
    })
    /**
     * 测试组件nestedScroll.scrollBackward且获取属性正确
     */
    it('ArkUI_Grid_0045', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollBackward')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollBackward',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      })

      done();
    })

    it('ArkUI_Grid_0046', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollBackward',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: "NestedScrollMode.SELF_FIRST"
      })

      done();
    })

    it('ArkUI_Grid_0047', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollBackward',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: "NestedScrollMode.PARENT_FIRST"
      })

      done();
    })

    it('ArkUI_Grid_0048', 0, async (done: Function) => {

      await Search('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'nestedScroll.scrollBackward',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: "NestedScrollMode.PARALLEL"
      })

      done();
    })
    /**
     * 测试组件friction且获取属性正确
     */
    it('ArkUI_Grid_0049', 0, async (done: Function) => {

      await Search('参数列表', 'friction')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'friction',
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value),
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'friction',
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value),
        ],
        assertEqual: 0.75
      })

      done();
    })
    /**
     * 测试组件alignItems
     */
    it('ArkUI_Grid_0050', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'alignItems')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'alignItems',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Grid_0051', 0, async (done: Function) => {

      await Search('参数列表', 'alignItems')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'alignItems',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Grid_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_Grid_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_Grid_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_Grid_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_Grid_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Grid_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_Grid_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_Grid_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_Grid_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_Grid_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_Grid_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_Grid_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_Grid_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_Grid_Comp_0014', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_Grid_Comp_0015', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭position
     */
    it('ArkUI_Grid_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_Grid_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_Grid_Comp_0018', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_Grid_Comp_0019', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_Grid_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_Grid_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_Grid_Comp_0022', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_Grid_Comp_0023', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭offset
     */
    it('ArkUI_Grid_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试组件borderStyle
     */
    it('ArkUI_Grid_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_Grid_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_Grid_Comp_0027', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Solid'
      })
      done();
    })
    /**
     * 测试组件borderWidth
     */
    it('ArkUI_Grid_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    /**
     * 测试组件borderColor
     */
    it('ArkUI_Grid_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_Grid_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0034', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件borderRadius
     */
    it('ArkUI_Grid_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件background.align
     */
    it('ArkUI_Grid_Comp_0036', 0, async (done: Function) => {
      await titleSearch('基础属性', 'background.align');
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();
    })
    it('ArkUI_Grid_Comp_0037', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0038', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0039', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0040', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0041', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0042', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0043', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })
    it('ArkUI_Grid_Comp_0044', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    /**
     * 测试组件backgroundColor
     */
    it('ArkUI_Grid_Comp_0045', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0046', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0047', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0048', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0049', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Grid_Comp_0050', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Grid',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件backgroundImage.src
     */
    it('ArkUI_Grid_Comp_0051', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    it('ArkUI_Grid_Comp_0052', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
  })
}