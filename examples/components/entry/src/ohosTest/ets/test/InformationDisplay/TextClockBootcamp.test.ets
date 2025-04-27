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


const TAG = 'TextClockBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextClockBootcampTest() {
  describe('TextClockBootcampTest', () => {
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
        console.info(TAG + 'TextClockBootcamp001' + ' begin');

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


        let scrollSearch: Component = await driver.findComponent(ON.text('文本时钟/TextClock'))
        await scrollSearch.click()
        await driver.delayMs(2500);

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
     * 测试组件format支持设置显示时间格式为yyyy年M月d日 EEEE
     */
    it('ArkUI_TextClock_001', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 0,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy年M月d日 EEEE'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yyyy年M月d日
     */
    it('ArkUI_TextClock_002', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 1,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy年M月d日'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为M月d日 EEEE
     */
    it('ArkUI_TextClock_003', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 2,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'M月d日 EEEE'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为M月d日
     */
    it('ArkUI_TextClock_004', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 3,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'M月d日'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为MM/dd/yyyy
     */
    it('ArkUI_TextClock_005', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 4,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'MM/dd/yyyy'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为EEEE MM月dd日
     */
    it('ArkUI_TextClock_006', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 5,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'EEEE MM月dd日'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yyyy
     */
    it('ArkUI_TextClock_007', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 6,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yy
     */
    it('ArkUI_TextClock_008', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 7,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yy'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为MM
     */
    it('ArkUI_TextClock_009', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 8,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'MM'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为M
     */
    it('ArkUI_TextClock_010', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 9,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'M'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为dd
     */
    it('ArkUI_TextClock_011', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 10,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'dd'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为d
     */
    it('ArkUI_TextClock_012', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 11,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'd'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为EEEE
     */
    it('ArkUI_TextClock_013', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 12,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'EEEE'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为E
     */
    it('ArkUI_TextClock_014', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 13,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'E'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yyyy年M月d日
     */
    it('ArkUI_TextClock_015', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 14,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy年M月d日'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yyyy/M/d
     */
    it('ArkUI_TextClock_016', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 15,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy/M/d'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yyyy-M-d
     */
    it('ArkUI_TextClock_017', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 16,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy-M-d'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为yyyy.M.d
     */
    it('ArkUI_TextClock_018', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 17,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'yyyy.M.d'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为HH:mm:ss
     */
    it('ArkUI_TextClock_019', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 18,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'HH:mm:ss'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为aa hh:mm:ss
     */
    it('ArkUI_TextClock_020', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 19,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'aa hh:mm:ss'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为hh:mm:ss
     */
    it('ArkUI_TextClock_021', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 20,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'hh:mm:ss'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为HH:mm
     */
    it('ArkUI_TextClock_022', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 21,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'HH:mm'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为aa hh:mm
     */
    it('ArkUI_TextClock_023', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 22,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'aa hh:mm'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为hh:mm
     */
    it('ArkUI_TextClock_024', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 23,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'hh:mm'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为mm:ss
     */
    it('ArkUI_TextClock_025', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 24,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'mm:ss'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为mm:ss.SS
     */
    it('ArkUI_TextClock_026', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 25,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'mm:ss.SS'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为mm:ss.SSS
     */
    it('ArkUI_TextClock_027', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 26,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'mm:ss.SSS'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为hh:mm:ss aa
     */
    it('ArkUI_TextClock_028', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 27,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'hh:mm:ss aa'
      })
      done();
    })

    /**
     * 测试组件format支持设置显示时间格式为HH
     */
    it('ArkUI_TextClock_029', 0, async (done: Function) => {
      await Search('参数列表', 'format')
      await radioClick({
        radioClickObj: 28,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('format', JsonType.value),
        ],
        assertEqual: 'HH'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置字体颜色为1号色且获取属性正确
     */
    it('ArkUI_TextClock_030', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置字体颜色为2号色且获取属性正确
     */
    it('ArkUI_TextClock_031', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置字体颜色为3号色且获取属性正确
     */
    it('ArkUI_TextClock_032', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置字体颜色为4号色且获取属性正确
     */
    it('ArkUI_TextClock_033', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置字体颜色为5号色且获取属性正确
     */
    it('ArkUI_TextClock_034', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })

    /**
     * 测试组件fontColor支持设置字体颜色为6号色且获取属性正确
     */
    it('ArkUI_TextClock_035', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件fontSize支持设置字体大小
     */
    it('ArkUI_TextClock_036', 0, async (done: Function) => {

      await Search('参数列表', 'fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '24.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '12.00fp'
      })
      done();
    })

    /**
     * 测试组件fontStyle支持设置字体样式为Normal
     */
    it('ArkUI_TextClock_037', 0, async (done: Function) => {

      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 0,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle.Normal'
      })

      done();
    })

    /**
     * 测试组件fontStyle支持设置字体样式为Italic
     */
    it('ArkUI_TextClock_038', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle.Italic'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置文本的字体粗细为Normal
     */
    it('ArkUI_TextClock_039', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 0,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Normal'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置文本的字体粗细为Lighter
     */
    it('ArkUI_TextClock_040', 0, async (done: Function) => {

      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 1,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Lighter'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置文本的字体粗细为Regular
     */
    it('ArkUI_TextClock_041', 0, async (done: Function) => {

      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 2,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置文本的字体粗细为Medium
     */
    it('ArkUI_TextClock_042', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 3,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置文本的字体粗细为Bold
     */
    it('ArkUI_TextClock_043', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 4,
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bold'
      })
      done();
    })

    /**
     * 测试组件fontWeight支持设置文本的字体粗细为Bolder
     */
    it('ArkUI_TextClock_044', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bolder'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为normal
     */
    it('ArkUI_TextClock_045', 0, async (done: Function) => {
      // await searchParentBlock('fontFeature',true,'参数列表')
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontFeature',
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss01'on
     */
    it('ArkUI_TextClock_046', 0, async (done: Function) => {
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontFeature'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss01" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss01"off
     */
    it('ArkUI_TextClock_047', 0, async (done: Function) => {
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontFeature'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss01" 0'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss02'on
     */
    it('ArkUI_TextClock_048', 0, async (done: Function) => {
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontFeature'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss02" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss02"off
     */
    it('ArkUI_TextClock_049', 0, async (done: Function) => {
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontFeature'
        },
        id: 'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss02" 0'
      })
      done();
    })
  })
}