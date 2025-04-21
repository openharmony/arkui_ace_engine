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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON, Component } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  ToggleClick
} from '../../utils';


const TAG = 'AlertDialogBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function AlertDialogBootcampTest() {
  describe('AlertDialogBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(3500);
        console.info(TAG + 'AlertDialogBootcamp001' + ' begin');

        let ListItemGroup: Component[] = await driver.findComponents(ON.type('ListItemGroup'))
        let width: Point = await ListItemGroup[0].getBoundsCenter()
        let width2: Point = await ListItemGroup[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(2000);

        let atomDisplays: Component = await driver.findComponent(ON.text('弹窗'));
        await atomDisplays.click();
        await driver.delayMs(2000);
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)


        let scrollSearch: Component = await driver.findComponent(ON.text('警告弹窗/AlertDialog'))
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
    })


    /**
     * 测试组件autoCancel支持点击遮障层是否关闭弹窗为允许
     */
    it('ArkUI_AlertDialog_001', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'autoCancel')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件autoCancel支持点击遮障层是否关闭弹窗为禁止
     */
    it('ArkUI_AlertDialog_002', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'autoCancel')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为Default
     */
    it('ArkUI_AlertDialog_003', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为Top
     */
    it('ArkUI_AlertDialog_004', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为Center
     */
    it('ArkUI_AlertDialog_005', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为Bottom
     */
    it('ArkUI_AlertDialog_006', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为TopStart
     */
    it('ArkUI_AlertDialog_007', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为TopEnd
     */
    it('ArkUI_AlertDialog_008', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为CenterStart
     */
    it('ArkUI_AlertDialog_009', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为BottomStart
     */
    it('ArkUI_AlertDialog_010', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为BottomEnd
     */
    it('ArkUI_AlertDialog_011', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 8,
      })
      done();
    })

    /**
     * 测试组件alignment支持弹窗在竖直方向上的对齐方式为CenterEnd
     */
    it('ArkUI_AlertDialog_012', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'alignment')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件offset.dx支持弹窗相对alignment所在位置水平方向偏移量
     */
    it('ArkUI_AlertDialog_013', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'offset.dx')
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
      done();
    })

    /**
     * 测试组件offset.dy支持弹窗相对alignment所在位置竖直方向偏移量
     */
    it('ArkUI_AlertDialog_014', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'offset.dy')
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
      done();
    })

    /**
     * 测试组件gridCount支持弹窗容器宽度所占用栅格数
     */
    it('ArkUI_AlertDialog_015', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'gridCount')
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
      done();
    })

    /**
     * 测试组件isModal支持弹窗是否为模态窗口为允许
     */
    it('ArkUI_AlertDialog_016', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'isModal')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件isModal支持弹窗是否为模态窗口为禁止
     */
    it('ArkUI_AlertDialog_017', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'isModal')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件backgroundColor支持弹窗背板颜色为1号色
     */
    it('ArkUI_AlertDialog_018', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件backgroundColor支持弹窗背板颜色为2号色
     */
    it('ArkUI_AlertDialog_019', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件backgroundColor支持弹窗背板颜色为3号色
     */
    it('ArkUI_AlertDialog_020', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件backgroundColor支持弹窗背板颜色为4号色
     */
    it('ArkUI_AlertDialog_021', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件backgroundColor支持弹窗背板颜色为5号色
     */
    it('ArkUI_AlertDialog_022', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件backgroundColor支持弹窗背板颜色为6号色
     */
    it('ArkUI_AlertDialog_023', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为NONE
     */
    it('ArkUI_AlertDialog_024', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为Thin
     */
    it('ArkUI_AlertDialog_025', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为Thick
     */
    it('ArkUI_AlertDialog_026', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为Dark
     */
    it('ArkUI_AlertDialog_027', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为Light
     */
    it('ArkUI_AlertDialog_028', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraLight
     */
    it('ArkUI_AlertDialog_029', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraDark
     */
    it('ArkUI_AlertDialog_030', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraExtraLight
     */
    it('ArkUI_AlertDialog_031', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraExtraDark
     */
    it('ArkUI_AlertDialog_032', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraThick
     */
    it('ArkUI_AlertDialog_033', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraThin
     */
    it('ArkUI_AlertDialog_034', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraRegular
     */
    it('ArkUI_AlertDialog_035', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
      })
      done();
    })

    /**
     * 测试组件backgroundBlurStyle支持设置弹窗背板模糊材质为ExtraSemiThin
     */
    it('ArkUI_AlertDialog_036', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件cornerRadius.topLeft支持设置背板的左上角圆角半径
     */
    it('ArkUI_AlertDialog_037', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'cornerRadius.topLeft')
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
      done();
    })

    /**
     * 测试组件cornerRadius.topRight支持设置背板的右上角圆角半径
     */
    it('ArkUI_AlertDialog_038', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'cornerRadius.topRight')
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
      done();
    })

    /**
     * 测试组件cornerRadius.bottomLeft支持设置背板的左下角圆角半径
     */
    it('ArkUI_AlertDialog_039', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'cornerRadius.bottomLeft')
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
      done();
    })

    /**
     * 测试组件cornerRadius.bottomRight支持设置背板的右下角圆角半径
     */
    it('ArkUI_AlertDialog_040', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'cornerRadius.bottomRight')
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
      done();
    })

    /**
     * 测试组件textStyle.wordBreak支持设置弹窗message内容的文本截断方式为NORMAL
     */
    it('ArkUI_AlertDialog_041', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'textStyle.wordBreak')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件textStyle.wordBreak支持设置弹窗message内容的文本截断方式为BREAK_ALL
     */
    it('ArkUI_AlertDialog_042', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'textStyle.wordBreak')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件textStyle.wordBreak支持设置弹窗message内容的文本截断方式为BREAK_WORD
     */
    it('ArkUI_AlertDialog_043', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'textStyle.wordBreak')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件shadow支持设置弹窗背板的阴影为OUTER_FLOATING_MD
     */
    it('ArkUI_AlertDialog_044', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件shadow支持设置弹窗背板的阴影为OUTER_DEFAULT_XS
     */
    it('ArkUI_AlertDialog_045', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })


    /**
     * 测试组件shadow支持设置弹窗背板的阴影为OUTER_DEFAULT_SM
     */
    it('ArkUI_AlertDialog_046', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })


    /**
     * 测试组件shadow支持设置弹窗背板的阴影为OUTER_DEFAULT_MD
     */
    it('ArkUI_AlertDialog_047', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件shadow支持设置弹窗背板的阴影为OUTER_DEFAULT_LG
     */
    it('ArkUI_AlertDialog_048', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件shadow支持设置弹窗背板的阴影为OUTER_FLOATING_SM
     */
    it('ArkUI_AlertDialog_049', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'shadow')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件borderWidth支持设置4个边框宽度
     */
    it('ArkUI_AlertDialog_050', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderWidth')
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
      done();
    })

    /**
     * 测试组件borderColor支持设置弹窗背板的边框颜色为1号色
     */
    it('ArkUI_AlertDialog_051', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件borderColor支持设置弹窗背板的边框颜色为2号色
     */
    it('ArkUI_AlertDialog_052', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件borderColor支持设置弹窗背板的边框颜色为3号色
     */
    it('ArkUI_AlertDialog_053', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件borderColor支持设置弹窗背板的边框颜色为4号色
     */
    it('ArkUI_AlertDialog_054', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件borderColor支持设置弹窗背板的边框颜色为5号色
     */
    it('ArkUI_AlertDialog_055', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件borderColor支持设置弹窗背板的边框颜色为6号色
     */
    it('ArkUI_AlertDialog_056', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件borderStyle支持设置弹窗背板的边框样式为Dotted
     */
    it('ArkUI_AlertDialog_057', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件borderStyle支持设置弹窗背板的边框样式为Dashed
     */
    it('ArkUI_AlertDialog_058', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件borderStyle支持设置弹窗背板的边框样式为Solid
     */
    it('ArkUI_AlertDialog_059', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件width支持设置弹窗背板的宽度
     */
    it('ArkUI_AlertDialog_060', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'width')
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
      done();
    })

    /**
     * 测试组件height支持设置弹窗背板的高度
     */
    it('ArkUI_AlertDialog_061', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'height')
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
      done();
    })

    /**
     * 测试组件showInSubWindow支持显示在主窗口之外是否在子窗口显示此弹窗为允许
     */
    it('ArkUI_AlertDialog_062', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'showInSubWindow')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件showInSubWindow支持显示在主窗口之外是否在子窗口显示此弹窗为禁止
     */
    it('ArkUI_AlertDialog_063', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'showInSubWindow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件maskRect.x支持设置弹窗遮蔽层区域相对于窗口左上角的x轴坐标
     */
    it('ArkUI_AlertDialog_064', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.x')
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
      done();
    })

    /**
     * 测试组件maskRect.y支持设置弹窗遮蔽层区域相对于窗口左上角的y轴坐标
     */
    it('ArkUI_AlertDialog_065', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.y')
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
      done();
    })

    /**
     * 测试组件maskRect.width支持设置弹窗遮蔽层区域的宽度为50%
     */
    it('ArkUI_AlertDialog_066', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'maskRect.width'
        }
      })
      done();
    })

    /**
     * 测试组件maskRect.width支持设置弹窗遮蔽层区域的宽度为80%
     */
    it('ArkUI_AlertDialog_067', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'maskRect.width'
        }
      })
      done();
    })

    /**
     * 测试组件maskRect.width支持设置弹窗遮蔽层区域的宽度为100%
     */
    it('ArkUI_AlertDialog_068', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.width')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'maskRect.width',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件maskRect.height支持设置弹窗遮蔽层区域的高度为50%
     */
    it('ArkUI_AlertDialog_069', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'maskRect.height'
        }
      })
      done();
    })

    /**
     * 测试组件maskRect.height支持设置弹窗遮蔽层区域的高度为80%
     */
    it('ArkUI_AlertDialog_070', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'maskRect.height'
        }
      })
      done();
    })

    /**
     * 测试组件maskRect.height支持设置弹窗遮蔽层区域的高度为100%
     */
    it('ArkUI_AlertDialog_071', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'maskRect.height')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'maskRect.height',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })


    /**
     * 测试组件oneButton的confirm.enabled设置点击Button是否响应为可以响应
     */
    it('ArkUI_AlertDialog_072', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.enabled')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'confirm.enabled'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.enabled设置点击Button是否响应为可以不响应
     */
    it('ArkUI_AlertDialog_073', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.enabled')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'confirm.enabled',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.defaultFocus设置Button是否是默认焦点为是默认焦点
     */
    it('ArkUI_AlertDialog_074', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.defaultFocus')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'confirm.defaultFocus'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.defaultFocus设置Button是否是默认焦点为不是默认焦点
     */
    it('ArkUI_AlertDialog_075', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.defaultFocus')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'confirm.defaultFocus',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.style设置Button的风格样式为DEFAULT
     */
    it('ArkUI_AlertDialog_076', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.style')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'confirm.style'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.style设置Button的风格样式为HIGHLIGHT
     */
    it('ArkUI_AlertDialog_077', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'confirm.style',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.fontColor支持设置Button文本颜色为1号色
     */
    it('ArkUI_AlertDialog_078', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.fontColor支持设置Button文本颜色为2号色
     */
    it('ArkUI_AlertDialog_079', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.fontColor支持设置Button文本颜色为3号色
     */
    it('ArkUI_AlertDialog_080', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.fontColor支持设置Button文本颜色为4号色
     */
    it('ArkUI_AlertDialog_081', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.fontColor支持设置Button文本颜色为5号色
     */
    it('ArkUI_AlertDialog_082', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.fontColor支持设置Button文本颜色为6号色
     */
    it('ArkUI_AlertDialog_083', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'confirm.fontColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.backgroundColor支持设置Button背景颜色为1号色
     */
    it('ArkUI_AlertDialog_084', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'confirm.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.backgroundColor支持设置Button背景颜色为2号色
     */
    it('ArkUI_AlertDialog_085', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'confirm.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.backgroundColor支持设置Button背景颜色为3号色
     */
    it('ArkUI_AlertDialog_086', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'confirm.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.backgroundColor支持设置Button背景颜色为4号色
     */
    it('ArkUI_AlertDialog_087', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'confirm.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.backgroundColor支持设置Button背景颜色为5号色
     */
    it('ArkUI_AlertDialog_088', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'confirm.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件oneButton的confirm.backgroundColor支持设置Button背景颜色为6号色
     */
    it('ArkUI_AlertDialog_089', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'confirm.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'confirm.backgroundColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    //oneButton的相关属性测试完毕，关闭oneButton Toggle,无需断言
    it('ArkUI_AlertDialog_090', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('oneButton', false, '参数列表')
      done()
    })


    /**
     * 测试组件twoButton的primaryButton.enabled设置点击Button是否响应为可以响应
     */
    it('ArkUI_AlertDialog_091', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('twoButton', true, '参数列表')
      await Search('参数列表', 'primaryButton.enabled')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'primaryButton.enabled'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.enabled设置点击Button是否响应为可以不响应
     */
    it('ArkUI_AlertDialog_092', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.enabled')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'primaryButton.enabled',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.defaultFocus设置Button是否是默认焦点为是默认焦点
     */
    it('ArkUI_AlertDialog_093', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.defaultFocus')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'primaryButton.defaultFocus'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.defaultFocus设置Button是否是默认焦点为不是默认焦点
     */
    it('ArkUI_AlertDialog_094', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.defaultFocus')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'primaryButton.defaultFocus',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.style设置Button的风格样式为DEFAULT
     */
    it('ArkUI_AlertDialog_095', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.style')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'primaryButton.style'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.style设置Button的风格样式为HIGHLIGHT
     */
    it('ArkUI_AlertDialog_096', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'primaryButton.style',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.fontColor支持设置Button文本颜色为1号色
     */
    it('ArkUI_AlertDialog_097', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'primaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.fontColor支持设置Button文本颜色为2号色
     */
    it('ArkUI_AlertDialog_098', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'primaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.fontColor支持设置Button文本颜色为3号色
     */
    it('ArkUI_AlertDialog_099', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'primaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.fontColor支持设置Button文本颜色为4号色
     */
    it('ArkUI_AlertDialog_100', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'primaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.fontColor支持设置Button文本颜色为5号色
     */
    it('ArkUI_AlertDialog_101', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'primaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.fontColor支持设置Button文本颜色为6号色
     */
    it('ArkUI_AlertDialog_102', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'primaryButton.fontColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.backgroundColor支持设置Button背景颜色为1号色
     */
    it('ArkUI_AlertDialog_103', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'primaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.backgroundColor支持设置Button背景颜色为2号色
     */
    it('ArkUI_AlertDialog_104', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'primaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.backgroundColor支持设置Button背景颜色为3号色
     */
    it('ArkUI_AlertDialog_105', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'primaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.backgroundColor支持设置Button背景颜色为4号色
     */
    it('ArkUI_AlertDialog_106', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'primaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.backgroundColor支持设置Button背景颜色为5号色
     */
    it('ArkUI_AlertDialog_107', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'primaryButton.backgroundColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的primaryButton.backgroundColor支持设置Button背景颜色为6号色
     */
    it('ArkUI_AlertDialog_108', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'primaryButton.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'primaryButton.backgroundColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.enabled设置点击Button是否响应为可以响应
     */
    it('ArkUI_AlertDialog_109', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.enabled')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'secondaryButton.enabled'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.enabled设置点击Button是否响应为可以不响应
     */
    it('ArkUI_AlertDialog_110', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.enabled')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'secondaryButton.enabled',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.defaultFocus设置Button是否是默认焦点为是默认焦点
     */
    it('ArkUI_AlertDialog_111', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.defaultFocus')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'secondaryButton.defaultFocus'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.defaultFocus设置Button是否是默认焦点为不是默认焦点
     */
    it('ArkUI_AlertDialog_112', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.defaultFocus')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'secondaryButton.defaultFocus',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.style设置Button的风格样式为DEFAULT
     */
    it('ArkUI_AlertDialog_113', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.style')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'secondaryButton.style'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.style设置Button的风格样式为HIGHLIGHT
     */
    it('ArkUI_AlertDialog_114', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'secondaryButton.style',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.fontColor支持设置Button文本颜色为1号色
     */
    it('ArkUI_AlertDialog_115', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'secondaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.fontColor支持设置Button文本颜色为2号色
     */
    it('ArkUI_AlertDialog_116', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'secondaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.fontColor支持设置Button文本颜色为3号色
     */
    it('ArkUI_AlertDialog_117', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'secondaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.fontColor支持设置Button文本颜色为4号色
     */
    it('ArkUI_AlertDialog_118', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'secondaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.fontColor支持设置Button文本颜色为5号色
     */
    it('ArkUI_AlertDialog_119', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'secondaryButton.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件twoButton的secondaryButton.fontColor支持设置Button文本颜色为6号色
     */
    it('ArkUI_AlertDialog_120', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryButton.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'secondaryButton.fontColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })


  })
}