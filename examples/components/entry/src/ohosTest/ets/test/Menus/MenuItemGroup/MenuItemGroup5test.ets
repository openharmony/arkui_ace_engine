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
import { Driver, ON,Component  } from '@kit.TestKit';
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
import { MenuItemGroupStart } from './MenuItemGroup';


const driver = Driver.create();

export default function MenuItemGroup5() {
  describe('MenuItemGroup5', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await MenuItemGroupStart(done)
    })
    //renderFit
    /*
     * 测试组件renderFit支持设置CENTER且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0462', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,



      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0463', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0464', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0465', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0466', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0467', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0468', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0469', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0470', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_FILL且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0471', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0472', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0473', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 11,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0474', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 12,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0475', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 13,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0476', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 14,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0477', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 15,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },

      })
      done();
    })
    // monopolizeEvents
    /*
     * 测试组件monopolizeEvents支持设置true且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0478', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })
    /*
     * 测试组件monopolizeEvents支持设置false且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0479', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })
    //cursorControl
    /*
     * 测试组件cursorControl支持设置DEFAULT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0480', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0481', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0482', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0483', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0484', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST_EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0485', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    //hitTestBehavior
    /*
     * 测试组件hitTestBehavior支持设置Default且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0456', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },


      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Block且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0457', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },


      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Transparent且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0458', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },


      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置None且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0459', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },


      })
      done();
    })
    // obscured
    /*
     * 测试组件obscured支持设置null且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0460', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件obscured支持设置PLACEHOLDER且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0461', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //renderFit
    /*
     * 测试组件renderFit支持设置CENTER且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0462', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,



      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0463', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0464', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0465', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0466', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0467', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0468', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0469', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0470', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_FILL且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0471', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0472', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0473', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 11,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0474', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 12,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0475', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 13,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0476', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 14,

      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0477', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 15,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },

      })
      done();
    })
    // monopolizeEvents
    /*
     * 测试组件monopolizeEvents支持设置true且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0478', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 0,

      })
      done();
    })
    /*
     * 测试组件monopolizeEvents支持设置false且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0479', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })
    //cursorControl
    /*
     * 测试组件cursorControl支持设置DEFAULT且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0480', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0481', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0482', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0483', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0484', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST_EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0485', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_SOUTH且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0486', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0487', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0488', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0489', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0490', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST_SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0491', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST_SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0492', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 12
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CROSS且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0493', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 13
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_COPY且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0494', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 14
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_FORBID且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0495', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 15
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置COLOR_SUCKER且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0496', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0497', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0498', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0499', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0500', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0501', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0502', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0503', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0504', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0505', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0506', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0507', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0508', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0509', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0510', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0511', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0512', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0513', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0514', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0515', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0516', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0517', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0518', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0519', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0520', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0521', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0522', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0523', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0524', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    //useEffect
    /*
     * 测试组件useEffect支持设置true且获取属性正确
     * */
    it('ArkUI_MenuItemGroup_Comp_0525', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0526', 0, async (done: Function) => {
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