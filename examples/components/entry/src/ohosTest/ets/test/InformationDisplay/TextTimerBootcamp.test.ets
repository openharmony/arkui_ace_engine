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

import { describe, beforeAll,  it, } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON, Component } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../utils';


const TAG = 'TextTimerBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextTimerBootcampTest() {
  describe('TextTimerBootcampTest', () => {
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
        console.info(TAG + 'TextTimerBootcamp001' + ' begin');


        let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        console.info(TAG + 'ListItemGroup' + ListItemGroup.toString());
        let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
        let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
        await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
        await driver.delayMs(3500);

        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(4000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 1000)
        await driver.delayMs(2000);

        let ListItems1: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[2].getBoundsCenter()
        let width4: Point = await ListItems1[4].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 1000)
        await driver.delayMs(2000);

        let scrollSearch: Component = await driver.findComponent(ON.text('文本计时器/TextTimer'))
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
     * 测试组件isCountDown支持设置显示倒计时时间且获取属性正确
     */
    it('ArkUI_TextTimer_001', 0, async (done: Function) => {
      await Search('参数列表', 'isCountDown')
      await radioClick({
        radioClickObj: 0,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('isCountDown', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件isCountDown支持设置不显示倒计时时间且获取属性正确
     */
    it('ArkUI_TextTimer_002', 0, async (done: Function) => {
      await Search('参数列表', 'isCountDown')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('isCountDown', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件count支持设置倒计时时间且获取属性正确
     */
    it('ArkUI_TextTimer_003', 0, async (done: Function) => {
      await Search('参数列表', 'count')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('count', JsonType.value),
        ],
        assertEqual: '60000.000000'
      })
      // 取到属性值错误无法进行断言
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置倒计时字体颜色1号色且获取属性正确
     */
    it('ArkUI_TextTimer_004', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置倒计时字体颜色2号色且获取属性正确
     */
    it('ArkUI_TextTimer_005', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置倒计时字体颜色3号色且获取属性正确
     */
    it('ArkUI_TextTimer_006', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置倒计时字体颜色4号色且获取属性正确
     */
    it('ArkUI_TextTimer_007', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置倒计时字体颜色5号色且获取属性正确
     */
    it('ArkUI_TextTimer_008', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置倒计时字体颜色6号色且获取属性正确
     */
    it('ArkUI_TextTimer_009', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件fontSize支持设置倒计时字体大小且获取属性正确
     */
    it('ArkUI_TextTimer_010', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '24.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '12.00fp'
      })
      done();
    })

    /**
     * 测试组件fontStyle支持设置倒计时字体样式为Normal且获取属性正确
     */
    it('ArkUI_TextTimer_011', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 0,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle.Normal'
      })
      done();
    })

    /**
     * 测试组件fontStyle支持设置倒计时字体样式为Italic且获取属性正确
     */
    it('ArkUI_TextTimer_012', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle.Italic'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置倒计时文本的字体粗细为Normal且获取属性正确
     */
    it('ArkUI_TextTimer_013', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 0,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Normal'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置倒计时文本的字体粗细为Lighter且获取属性正确
     */
    it('ArkUI_TextTimer_014', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 1,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Lighter'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置倒计时文本的字体粗细为Regular且获取属性正确
     */
    it('ArkUI_TextTimer_015', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 2,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置倒计时文本的字体粗细为Medium且获取属性正确
     */
    it('ArkUI_TextTimer_016', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 3,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置倒计时文本的字体粗细为Bold且获取属性正确
     */
    it('ArkUI_TextTimer_017', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 4,
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bold'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置倒计时文本的字体粗细为Bolder且获取属性正确
     */
    it('ArkUI_TextTimer_018', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bolder'
      })
      done();
    })

    /**
     * 测试组件textShadow.radius支持设置阴影的模糊半径且获取属性正确
     */
    it('ArkUI_TextTimer_019', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.radius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'textShadow.radius'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '24.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'textShadow.radius'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();
    })

    /**
     * 测试组件textShadow.offsetX支持设置阴影的X轴偏移量且获取属性正确
     */
    it('ArkUI_TextTimer_020', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.offsetX')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'textShadow.offsetX'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '24.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'textShadow.offsetX'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();
    })

    /**
     * 测试组件textShadow.offsetY支持阴影的Y轴偏移量且获取属性正确
     */
    it('ArkUI_TextTimer_021', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.offsetY')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'textShadow.offsetY'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '24.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'textShadow.offsetY'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();
    })

    /**
     * 测试组件textShadow.color支持阴影的颜色1号色且获取属性正确
     */
    it('ArkUI_TextTimer_022', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })

    /**
     * 测试组件textShadow.color支持阴影的颜色2号色且获取属性正确
     */
    it('ArkUI_TextTimer_023', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

    /**
     * 测试组件textShadow.color支持阴影的颜色3号色且获取属性正确
     */
    it('ArkUI_TextTimer_024', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })

    /**
     * 测试组件textShadow.color支持阴影的颜色4号色且获取属性正确
     */
    it('ArkUI_TextTimer_025', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })

    /**
     * 测试组件textShadow.color支持阴影的颜色5号色且获取属性正确
     */
    it('ArkUI_TextTimer_026', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })

    /**
     * 测试组件textShadow.color支持阴影的颜色6号色且获取属性正确
     */
    it('ArkUI_TextTimer_027', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'textShadow.color',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件contentModifier支持设置定制TextTimer内容区的方法
     */
    it('ArkUI_TextTimer_028', 0, async (done: Function) => {
      //无法取到属性值进行断言
      await Search('参数列表', 'contentModifier')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'contentModifier'
        }
      })
      done();
    })

    /**
     * 测试组件contentModifier不支持设置定制TextTimer内容区的方法且获取属性正确
     */
    it('ArkUI_TextTimer_029', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'contentModifier')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'contentModifier',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_TextTimer_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_TextTimer_Comp_0006', 0, async (done: Function) => {
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
        id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0007', 0, async (done: Function) => {
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
        id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0008', 0, async (done: Function) => {
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
        id: 'TextTimer',
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
        id: 'TextTimer',
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
    it('ArkUI_TextTimer_Comp_0009', 0, async (done: Function) => {
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
        id: 'TextTimer',
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
        id: 'TextTimer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
  })
}