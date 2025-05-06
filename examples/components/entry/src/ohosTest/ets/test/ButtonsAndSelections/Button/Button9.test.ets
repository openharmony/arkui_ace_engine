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
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { ButtonStart } from './Button';

export default function Button9() {
  describe('Button9', () => {

    beforeAll(async (done: Function) => {
      await ButtonStart(done)
    })

    /*
 * 测试组件cursorControl支持设置SCREENSHOT_CURSOR且获取属性正确
 * */
    it('ArkUI_Button_Comp_0806', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'SCREENSHOT_CURSOR'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置TEXT_CURSOR且获取属性正确
     * */
    it('ArkUI_Button_Comp_0807', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'TEXT_CURSOR'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置ZOOM_IN且获取属性正确
     * */
    it('ArkUI_Button_Comp_0808', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'ZOOM_IN'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置ZOOM_OUT且获取属性正确
     * */
    it('ArkUI_Button_Comp_0809', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'ZOOM_OUT'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_EAST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0810', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_WEST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0811', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_WEST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_SOUTH且获取属性正确
     * */
    it('ArkUI_Button_Comp_0812', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_SOUTH'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH且获取属性正确
     * */
    it('ArkUI_Button_Comp_0813', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_SOUTH且获取属性正确
     * */
    it('ArkUI_Button_Comp_0814', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_SOUTH'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_EAST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0815', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_WEST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0816', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_WEST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0817', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_SOUTH_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0818', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_SOUTH_WEST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MIDDLE_BTN_NORTH_SOUTH_WEST_EAST且获取属性正确
     * */
    it('ArkUI_Button_Comp_0819', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'MIDDLE_BTN_NORTH_SOUTH_WEST_EAST'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HORIZONTAL_TEXT_CURSOR获取属性正确
     * */
    it('ArkUI_Button_Comp_0820', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'HORIZONTAL_TEXT_CURSOR'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_CROSS且获取属性正确
     * */
    it('ArkUI_Button_Comp_0821', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'CURSOR_CROSS'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_CIRCLE且获取属性正确
     * */
    it('ArkUI_Button_Comp_0822', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'CURSOR_CIRCLE'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置LOADING且获取属性正确
     * */
    it('ArkUI_Button_Comp_0823', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'LOADING'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置RUNNING且获取属性正确
     * */
    it('ArkUI_Button_Comp_0824', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'RUNNING'
      })
      done();
    })
    /*
     * 滑到cursorControl位置，关闭按钮，无需断言
     * */
    it('ArkUI_Button_Comp_0825', 0, async (done: Function) => {
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    //useEffect
    /*
     * 测试组件useEffect支持设置true且获取属性正确
     * */
    it('ArkUI_Button_Comp_0826', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'useEffect', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'useEffect'
        }
      })
      done();
    })
    /*
     * 测试组件useEffect支持设置true且获取属性正确
     * */
    it('ArkUI_Button_Comp_0827', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'useEffect', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'useEffect'
        }
      })
      done();
    })

    // fontColor
    it('ArkUI_Button_Comp_0828', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontColor', '通用属性7')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();
    })

    it('ArkUI_Button_Comp_0829', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontColor', '通用属性7')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();
    })

    it('ArkUI_Button_Comp_0830', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontColor', '通用属性7')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Button_Comp_0831', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontColor', '通用属性7')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();
    })

    it('ArkUI_Button_Comp_0832', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontColor', '通用属性7')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontColor'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();
    })

    it('ArkUI_Button_Comp_0833', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontColor', '通用属性7')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();
    })

    // fontSize
    it('ArkUI_Button_Comp_0834', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontSize', '通用属性7')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'fontSize'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '32.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Close,
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '0.00fp'
      })

      done();
    })

    // fontStyle
    it('ArkUI_Button_Comp_0835', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontStyle', '通用属性7')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontStyle'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle.Italic'
      })

      done();
    })

    it('ArkUI_Button_Comp_0836', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontStyle', '通用属性7')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: 'FontStyle.Normal'
      })

      done();
    })

    // fontWeight
    it('ArkUI_Button_Comp_0837', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontWeight', '通用属性7')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontWeight'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Regular'
      })

      done();
    })

    it('ArkUI_Button_Comp_0838', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontWeight', '通用属性7')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontWeight'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Medium'
      })

      done();
    })

    it('ArkUI_Button_Comp_0839', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontWeight', '通用属性7')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontWeight'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bold'
      })

      done();
    })

    it('ArkUI_Button_Comp_0840', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontWeight', '通用属性7')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontWeight'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Bolder'
      })

      done();
    })

    it('ArkUI_Button_Comp_0841', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontWeight', '通用属性7')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontWeight'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Lighter'
      })

      done();
    })

    it('ArkUI_Button_Comp_0842', 0, async (done: Function) => {

      await titleSearch('基础属性', 'fontWeight', '通用属性7')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: 'FontWeight.Normal'
      })

      done();
    })

  })
}