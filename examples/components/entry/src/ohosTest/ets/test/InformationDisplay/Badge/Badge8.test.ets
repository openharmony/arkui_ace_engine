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
} from '../../../utils';
import { BadgeStart } from './Badge';


const driver = Driver.create();

export default function Badge8Test() {
  describe('Badge8Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await BadgeStart(done)

    })
    //outline.value.color
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Badge_Comp_0614', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Badge_Comp_0615', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为3号色显示且获取属性正确
     * */
    it('ArkUI_Badge_Comp_0616', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Badge_Comp_0617', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为5号色显示且获取属性正确
     * */
    it('ArkUI_Badge_Comp_0618', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Badge_Comp_0619', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    /*
     * outline.value.radius
    */
    it('ArkUI_Badge_Comp_0620', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.radius', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Badge',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //outline.value.style
    /*
     * 测试组件outline.value.style支持设置SOLID且获取属性正确
    */
    it('ArkUI_Badge_Comp_0621', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.SOLID'
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DASHED且获取属性正确
    */
    it('ArkUI_Badge_Comp_0622', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.DASHED'
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DOTTED且获取属性正确
    */
    it('ArkUI_Badge_Comp_0623', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.DOTTED'
      })
      done();
    })
    /*
     * outline.value.width展开属性测试完成，关闭outline.value.width，无需断言
     * */
    it('ArkUI_Badge_Comp_0624', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await getToggle(ToggleClick.Close)
      done();
    })
    // visualEffect
    /*
     *测试组件visualEffect支持设置true且获取属性正确
    */
    it('ArkUI_Badge_Comp_0625', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'visualEffect', '通用属性6')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
    *测试组件visualEffect支持设置false且获取属性正确
   */
    it('ArkUI_Badge_Comp_0626', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'visualEffect', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //backgroundFilter
    /*
    *测试组件backgroundFilter支持设置true且获取属性正确
    */
    it('ArkUI_Badge_Comp_0627', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件backgroundFilter支持设置false且获取属性正确
    */
    it('ArkUI_Badge_Comp_0628', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //foregroundFilter
    /*
    *测试组件foregroundFilter支持设置true且获取属性正确
    */
    it('ArkUI_Badge_Comp_0629', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件foregroundFilter支持设置false且获取属性正确
    */
    it('ArkUI_Badge_Comp_0630', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //compositingFilter
    /*
    *测试组件compositingFilter支持设置true且获取属性正确
    */
    it('ArkUI_Badge_Comp_0631', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'compositingFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件compositingFilter支持设置false且获取属性正确
    */
    it('ArkUI_Badge_Comp_0632', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'compositingFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.x
    it('ArkUI_Badge_Comp_0633', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.x', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.y
    it('ArkUI_Badge_Comp_0634', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.y', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.width
    /*
    * 测试组件responseRegion.value.width支持设置0%且获取属性正确
    */
    it('ArkUI_Badge_Comp_0635', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
    * 测试组件responseRegion.value.width支持设置30%且获取属性正确
    */
    it('ArkUI_Badge_Comp_0636', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置60%且获取属性正确
     */
    it('ArkUI_Badge_Comp_0637', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置90%且获取属性正确
     */
    it('ArkUI_Badge_Comp_0638', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置100%且获取属性正确
     */
    it('ArkUI_Badge_Comp_0639', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    //responseRegion.value.height
    /*
    * 测试组件responseRegion.value.height支持设置0%且获取属性正确
    */
    it('ArkUI_Badge_Comp_0640', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
    * 测试组件responseRegion.value.height支持设置30%且获取属性正确
    */
    it('ArkUI_Badge_Comp_0641', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置60%且获取属性正确
     */
    it('ArkUI_Badge_Comp_0642', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置90%且获取属性正确
     */
    it('ArkUI_Badge_Comp_0643', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置100%且获取属性正确
     */
    it('ArkUI_Badge_Comp_0644', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    //hitTestBehavior
    /*
     * 测试组件hitTestBehavior支持设置Default且获取属性正确
     * */
    it('ArkUI_Badge_Comp_0645', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Default'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Block且获取属性正确
     * */
    it('ArkUI_Badge_Comp_0646', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Block'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Transparent且获取属性正确
     * */
    it('ArkUI_Badge_Comp_0647', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Transparent'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置None且获取属性正确
     * */
    it('ArkUI_Badge_Comp_0648', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Badge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.None'
      })
      done();
    })

  })
}