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
  getToggle,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { MenuStart } from './Menu';


const driver = Driver.create();

export default function Menu5() {
  describe('Menu5', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await MenuStart(done)
    })
    /*
    * 测试组件cursorControl支持设置COLOR_SUCKER且获取属性正确
    * */
    it('ArkUI_Menu_Comp_0496', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 16
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HAND_GRABBING且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0497', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 17
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HAND_OPEN且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0498', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 18
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HAND_POINTING且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0499', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 19
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置HELP且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0500', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 20
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置MOVE且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0501', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 21
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置RESIZE_LEFT_RIGHT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0502', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 22
      })
      done();
    })
    /*
    * 测试组件cursorControl支持设置RESIZE_UP_DOWN且获取属性正确
    * */
    it('ArkUI_Menu_Comp_0503', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'RESIZE_UP_DOWN'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SCREENSHOT_CHOOSE且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0504', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 'SCREENSHOT_CHOOSE'
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SCREENSHOT_CURSOR且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0505', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0506', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0507', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0508', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0509', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0510', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0511', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0512', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0513', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0514', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0515', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0516', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0517', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0518', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0519', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0520', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0521', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0522', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0523', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0524', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    //useEffect
    /*
     * 测试组件useEffect支持设置true且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0525', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0526', 0, async (done: Function) => {
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

  })

}