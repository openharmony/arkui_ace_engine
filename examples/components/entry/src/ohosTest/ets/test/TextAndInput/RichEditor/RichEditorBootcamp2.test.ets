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

import { describe, beforeAll, it } from '@ohos/hypium';
import { abilityDelegatorRegistry, Driver } from '@kit.TestKit';
import { Component, ON } from '@ohos.UiTest';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { richEditorBeforeAll } from './RichEditor.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function RichEditorBootcampTest2() {
  describe('RichEditorBootcampTest2', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      richEditorBeforeAll(done, delegator, driver);
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_RichEditor_Comp_0021', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0022', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0023', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0024', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0027', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_RichEditor_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0034', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0036', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0037', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0038', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0039', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0040', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0041', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0042', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0043', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0044', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0045', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0046', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0047', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0048', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0049', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0050', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0051', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    it('ArkUI_RichEditor_Comp_0052', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    /**
     * 测试组件backgroundImage.repeat
     */
    it('ArkUI_RichEditor_Comp_0053', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.NoRepeat'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0054', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.X'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0055', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.Y'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0056', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.repeat');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundImage.repeat')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImage', JsonType.value),
        ],
        assertEqual: ', ImageRepeat.XY'
      })

      done();

    })
    /**
     * 测试组件backgroundImageSize
     */
    it('ArkUI_RichEditor_Comp_0057', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Auto'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0058', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Cover'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0059', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Contain'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0060', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.FILL'
      })

      done();

    })
    /**
     * 测试组件backgroundImagePosition.x
     */
    it('ArkUI_RichEditor_Comp_0061', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundImagePosition.x');
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
     * 测试组件backgroundImagePosition.y
     */
    it('ArkUI_RichEditor_Comp_0062', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundImagePosition.y');
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
     * 测试组件backgroundBlurStyle
     */
    it('ArkUI_RichEditor_Comp_0063', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0064', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0065', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0066', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0067', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 4,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0068', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 5,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0069', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 6,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0070', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 7,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0071', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 8,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0072', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 9,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0073', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 10,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0074', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 11,
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0075', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundBlurStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件backgroundBlurStyle.options
     */
    it('ArkUI_RichEditor_Comp_0076', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_RichEditor_Comp_0077', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.colorMode');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('colorMode', JsonType.value)
        ],
        assertEqual: 'ThemeColorMode.System'
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0078', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.colorMode');
      // 获取不到新值
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0079', 0, async (done: Function) => {
      // 获取不到新值
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.colorMode');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0080', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.adaptiveColor');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('adaptiveColor', JsonType.value)
        ],
        assertEqual: 'AdaptiveColor.Default'
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0081', 0, async (done: Function) => {
      // 获取不到新值
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.adaptiveColor');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    it('ArkUI_RichEditor_Comp_0082', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.blurOptions.left');
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
    it('ArkUI_RichEditor_Comp_0083', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.blurOptions.right');
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
    it('ArkUI_RichEditor_Comp_0084', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params.scale');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('scale', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundBlurStyle', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('scale', JsonType.value)
        ],
        assertEqual: 1
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0085', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundBlurStyleParams.options.params');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundBlurStyleParams.options.params')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      done();

    })
    /**
     * 测试组件backdropBlur
     */
    it('ArkUI_RichEditor_Comp_0086', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backdropBlur');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backdropBlur', JsonType.value),
        ],
        assertEqual: 0
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backdropBlur', JsonType.value),
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0087', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_RichEditor_Comp_0088', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backdropBlur.options.grayscale.left');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0089', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backdropBlur.options.grayscale.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0090', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backdropBlur.options.grayscale');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backdropBlur.options.grayscale')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      done();

    })
    /**
     * 测试组件backgroundEffect
     */
    it('ArkUI_RichEditor_Comp_0091', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      done();

    })
    it('ArkUI_RichEditor_Comp_0092', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.radius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: 100
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0093', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.saturation');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('saturation', JsonType.value)
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('saturation', JsonType.value)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0094', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.brightness');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 2
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 0
      })
      done();

    })
    it('ArkUI_RichEditor_Comp_0095', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0096', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0097', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0098', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0099', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_RichEditor_Comp_0100', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.color');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        id: 'RichEditor',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundEffect', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
  })
}