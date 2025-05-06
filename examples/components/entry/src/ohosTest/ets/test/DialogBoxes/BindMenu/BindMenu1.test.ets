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

import { describe, beforeAll, it } from '@ohos/hypium'
import { Driver, ON, Component } from '@kit.TestKit';
import {
  buttonClick,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { BindMenuStart } from './BindMenu';


const driver = Driver.create();

export default function BindMenu1() {
  describe('BindMenu1', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await BindMenuStart(done)
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0008', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0009', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_MenuItem_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0014', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0017', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0018', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0019', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试关闭markAnchor
     */
    it('ArkUI_MenuItem_Comp_0020', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0021', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0022', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_MenuItem_Comp_0023', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
     * 测试关闭offset
     */
    it('ArkUI_MenuItem_Comp_0024', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0025', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0026', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0027', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })
      done();
    })
    /**
     * 测试组件borderWidth
     */
    it('ArkUI_MenuItem_Comp_0028', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderWidth');
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
     * 测试组件borderColor
     */
    it('ArkUI_MenuItem_Comp_0029', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0030', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0031', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0032', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0033', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0034', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    /**
     * 测试组件borderRadius
     */
    it('ArkUI_MenuItem_Comp_0035', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderRadius');
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
     * 测试组件background.align
     */
    it('ArkUI_MenuItem_Comp_0036', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0037', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0038', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0039', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0040', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0041', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0042', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0043', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0044', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0045', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0046', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0047', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0048', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0049', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0050', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    /**
     * 测试组件backgroundImage.src
     */
    it('ArkUI_MenuItem_Comp_0051', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    it('ArkUI_MenuItem_Comp_0052', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0053', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundImage.repeat');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0054', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0055', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0056', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    /**
     * 测试组件backgroundImageSize
     */
    it('ArkUI_MenuItem_Comp_0057', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundImageSize');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0058', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0059', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundImageSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImageSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0060', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    /**
     * 测试组件backgroundImagePosition.x
     */
    it('ArkUI_MenuItem_Comp_0061', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0062', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0063', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0064', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0065', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0066', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0067', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0068', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0069', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0070', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0071', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0072', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0073', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0074', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0075', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0076', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0077', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0078', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0079', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0080', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0081', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0082', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0083', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0084', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0085', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0086', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backdropBlur');
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
    it('ArkUI_MenuItem_Comp_0087', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0088', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0089', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0090', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0091', 0, async (done: Function) => {
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
    it('ArkUI_MenuItem_Comp_0092', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0093', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0094', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();

    })
    it('ArkUI_MenuItem_Comp_0095', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0096', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0097', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0098', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0099', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0100', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0101', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.adaptiveColor');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0102', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.adaptiveColor');
      toggle = await driver.findComponent(ON.type('Toggle')
        .within(ON.type('Scroll'))
        .isAfter(ON.text('backgroundEffect.adaptiveColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0103', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundEffect');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle')
          .within(ON.type('Scroll'))
          .isAfter(ON.text('backgroundEffect')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'backgroundEffect.blurOptions.grayscale.left');
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
  })

}