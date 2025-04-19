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

const driver = Driver.create();

export default function Grid8Test() {
  describe('Grid8Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await GridStart(done)
    })
    // attributeModifier
    it('ArkUI_Column_Comp_0609', 0, async (done: Function) => {

      await titleSearch('基础属性', 'attributeModifier', '通用属性5')

      // 取不到attributeModifier属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'attributeModifier'
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0610', 0, async (done: Function) => {

      await titleSearch('基础属性', 'attributeModifier', '通用属性5')

      // 取不到attributeModifier属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'attributeModifier'
        }
      })

      done()
    })

    //gestureModifier
    /*
    * 测试组件gestureModifier支持设置为true且获取属性正确
    */
    it('ArkUI_Column_Comp_0611', 0, async (done: Function) => {
      // 无法取到属性值
      await titleSearch('基础属性', 'gestureModifier', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件gestureModifier支持设置包含单个子组件为false且获取属性正确
    */
    it('ArkUI_Column_Comp_0612', 0, async (done: Function) => {
      // 无法取到属性值
      await titleSearch('基础属性', 'gestureModifier', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //outline.value.width
    it('ArkUI_Column_Comp_0613', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    //outline.value.color
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Column_Comp_0614', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0615', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0616', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0617', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0618', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0619', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Column',
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
    it('ArkUI_Column_Comp_0620', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.radius', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0621', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0622', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        id: 'Column',
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
    it('ArkUI_Column_Comp_0623', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Column',
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
    it('ArkUI_Column_Comp_0624', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await getToggle(ToggleClick.Close)
      done();
    })
    // visualEffect
    /*
     *测试组件visualEffect支持设置true且获取属性正确
    */
    it('ArkUI_Column_Comp_0625', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0626', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0627', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0628', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0629', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0630', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0631', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0632', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0633', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0634', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0635', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0636', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0637', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0638', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0639', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0640', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0641', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0642', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0643', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0644', 0, async (done: Function) => {
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
    it('ArkUI_Column_Comp_0645', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Column',
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
    it('ArkUI_Column_Comp_0646', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Column',
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
    it('ArkUI_Column_Comp_0647', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Column',
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
    it('ArkUI_Column_Comp_0648', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.None'
      })
      done();
    })
    //bindContentCover.isShow
    /*
     * 测试组件bindContentCover.isShow支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0649', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
     * 测试组件bindContentCover.isShow支持设置false且获取属性正确
     * */
    it('ArkUI_Column_Comp_0650', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    // bindContentCover.options.modalTransition
    /*
     * 测试组件bindContentCover.options.modalTransition支持设置DEAULT且获取属性正确
     * */
    it('ArkUI_Column_Comp_0651', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.modalTransition支持设置NONE且获取属性正确
     */
    it('ArkUI_Column_Comp_0652', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.modalTransition支持设置ALPHA且获取属性正确
    */
    it('ArkUI_Column_Comp_0653', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.opacity
    it('ArkUI_Column_Comp_0654', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.opacity', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.opacity', '通用属性7')
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
    //bindContentCover.options.transition.translate.x
    it('ArkUI_Column_Comp_0655', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.x', '通用属性7')
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
    //bindContentCover.options.transition.translate.y
    it('ArkUI_Column_Comp_0656', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.y', '通用属性7')
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
    //bindContentCover.options.transition.translate.z
    it('ArkUI_Column_Comp_0657', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.z', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Column_Comp_',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.x
    it('ArkUI_Column_Comp_0658', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.x', '通用属性7')
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
    //bindContentCover.options.transition.scale.y
    it('ArkUI_Column_Comp_0659', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.y', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.z
    it('ArkUI_Column_Comp_0660', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.z', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.centerX
    it('ArkUI_Column_Comp_0661', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerX', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerX', '通用属性7')
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
    //bindContentCover.options.transition.scale.centerY
    it('ArkUI_Column_Comp_0662', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerY', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerY', '通用属性7')
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
    //bindContentCover.options.transition.rotate.x
    it('ArkUI_Column_Comp_0663', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.x', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Column_Comp',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.y
    it('ArkUI_Column_Comp_0664', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.y', '通用属性7')
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
    //bindContentCover.options.transition.rotate.z
    it('ArkUI_Column_Comp_0665', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.z', '通用属性7')
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
    //bindContentCover.options.transition.rotate.centerX
    it('ArkUI_Column_Comp_0666', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerX', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerX', '通用属性7')
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
    //bindContentCover.options.transition.rotate.centerY
    it('ArkUI_Column_Comp_0667', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerY', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerY', '通用属性7')
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
    //bindContentCover.options.transition.rotate.centerZ
    it('ArkUI_Column_Comp_0668', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerZ', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerZ', '通用属性7')
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
    // bindContentCover.options.transition.rotate.perspective
    it('ArkUI_Column_Comp_0669', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.perspective',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.perspective', '通用属性7')
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
    //bindContentCover.options.transition.move
    /*
     * 测试组件bindContentCover.options.transition.move支持设置TOP且获取属性正确
     * */
    it('ArkUI_Column_Comp_0670', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置BOTTOM且获取属性正确
     */
    it('ArkUI_Column_Comp_0671', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.transition.move支持设置START且获取属性正确
    */
    it('ArkUI_Column_Comp_0672', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置END且获取属性正确
     */
    it('ArkUI_Column_Comp_0673', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.duration
    it('ArkUI_Column_Comp_0674', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.duration',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.duration', '通用属性7')
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
    //bindContentCover.options.transition.animation.tempo
    it('ArkUI_Column_Comp_0675', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.tempo', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.tempo', '通用属性7')
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
    //bindContentCover.options.transition.animation.curve
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Linear且获取属性正确
     * */
    it('ArkUI_Column_Comp_0676', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Ease且获取属性正确
     * */
    it('ArkUI_Column_Comp_0677', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseIn且获取属性正确
     * */
    it('ArkUI_Column_Comp_0678', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseOut且获取属性正确
     * */
    it('ArkUI_Column_Comp_0679', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseInOut且获取属性正确
     * */
    it('ArkUI_Column_Comp_0680', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutSlowIn且获取属性正确
     * */
    it('ArkUI_Column_Comp_0681', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置LinearOutSlowIn且获取属性正确
     * */
    it('ArkUI_Column_Comp_0682', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutLinearIn且获取属性正确
     * */
    it('ArkUI_Column_Comp_0683', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置ExtremeDeceleration且获取属性正确
     * */
    it('ArkUI_Column_Comp_0684', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Sharp且获取属性正确
     * */
    it('ArkUI_Column_Comp_0685', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Rhythm且获取属性正确
     * */
    it('ArkUI_Column_Comp_0686', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Smooth且获取属性正确
     * */
    it('ArkUI_Column_Comp_0687', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Friction且获取属性正确
     * */
    it('ArkUI_Column_Comp_0688', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.delay
    it('ArkUI_Column_Comp_0689', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.delay', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.delay', '通用属性7')
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
    //bindContentCover.options.transition.animation.iterations
    it('ArkUI_Column_Comp_0690', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.iterations',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.iterations', '通用属性7')
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
    //bindContentCover.options.transition.animation.playMode
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Normal且获取属性正确
     * */
    it('ArkUI_Column_Comp_0691', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Reverse且获取属性正确
     * */
    it('ArkUI_Column_Comp_0692', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Alternate且获取属性正确
     * */
    it('ArkUI_Column_Comp_0693', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置AlternateReverse且获取属性正确
     * */
    it('ArkUI_Column_Comp_0694', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.max
    it('ArkUI_Column_Comp_0695', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.max', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.max',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.min
    it('ArkUI_Column_Comp_0696', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.min', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.min',
        '通用属性7')
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
    //bindContentCover.options.transition.animation.expectedFrameRateRange.expected
    it('ArkUI_Column_Comp_0697', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.expected', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected',
        '通用属性7')
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
    //bindContentCover相关属性测试完毕，关闭bindContentCover.isShow Toggle,无需断言
    it('ArkUI_Column_Comp_0698', 0, async (done: Function) => {
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    //bindSheet.isShow
    /*
     * 测试组件bindSheet.isShow支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0699', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindSheet.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      await driver.delayMs(1000);
      await driver.click(645, 115)
      done();
    })
    /*
     * 测试组件bindSheet.isShow支持设置false且获取属性正确
     * */
    it('ArkUI_Column_Comp_0700', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindSheet.isShow', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    //bindSheet.options.height
    /*
     * 测试组件bindSheet.options.height支持设置MEDIUM且获取属性正确
     * */
    it('ArkUI_Column_Comp_0701', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.height', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.height', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.height支持设置LARGE且获取属性正确
     * */
    it('ArkUI_Column_Comp_0702', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.height', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.height', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.height支持设置FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Column_Comp_0703', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.height', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.height', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.detents
    /*
     * 测试组件bindSheet.options.detents支持设置MEDIUM,LARGE,FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Column_Comp_0704', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.detents', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.detents', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.detents支持设置LARGE,FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Column_Comp_0705', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.detents', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.detents', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.detents支持设置FIT_CONTENT且获取属性正确
     * */
    it('ArkUI_Column_Comp_0706', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.detents', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.detents', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.preferType
    /*
     * 测试组件bindSheet.options.preferType支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_Column_Comp_0707', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.preferType', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.preferType', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.preferType支持设置CENTER且获取属性正确
     * */
    it('ArkUI_Column_Comp_0708', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.preferType', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.preferType', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.preferType支持设置POPUP且获取属性正确
     * */
    it('ArkUI_Column_Comp_0709', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.preferType', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.preferType', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.showClose
    /*
     * 测试组件bindSheet.options.showClose支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0710', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.showClose', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.showClose', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.showClose支持设置false且获取属性正确
     * */
    it('ArkUI_Column_Comp_0711', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.showClose', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.showClose', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.dragBar
    /*
     * 测试组件bindSheet.options.dragBar支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0712', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.dragBar', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.dragBar', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.dragBar支持设置false且获取属性正确
     * */
    it('ArkUI_Column_Comp_0713', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.dragBar', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.dragBar', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.blurStyle
    /*
     * 测试组件bindSheet.options.blurStyle支持设置Thin且获取属性正确
     * */
    it('ArkUI_Column_Comp_0714', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置Regular且获取属性正确
     * */
    it('ArkUI_Column_Comp_0715', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置Thick且获取属性正确
     * */
    it('ArkUI_Column_Comp_0716', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_THIN且获取属性正确
     * */
    it('ArkUI_Column_Comp_0717', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_REGULAR且获取属性正确
     * */
    it('ArkUI_Column_Comp_0718', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_THICK且获取属性正确
     * */
    it('ArkUI_Column_Comp_0719', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置BACKGROUND_ULTRA_THICK且获取属性正确
     * */
    it('ArkUI_Column_Comp_0720', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置NONE且获取属性正确
     * */
    it('ArkUI_Column_Comp_0721', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_ULTRA_THIN且获取属性正确
     * */
    it('ArkUI_Column_Comp_0722', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_THIN且获取属性正确
     * */
    it('ArkUI_Column_Comp_0723', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_REGULAR且获取属性正确
     * */
    it('ArkUI_Column_Comp_0724', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_THICK且获取属性正确
     * */
    it('ArkUI_Column_Comp_0725', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.blurStyle支持设置COMPONENT_ULTRA_THICK且获取属性正确
     * */
    it('ArkUI_Column_Comp_0726', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.blurStyle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.blurStyle', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.maskColor
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Column_Comp_0727', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Column_Comp_0728', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为3号色显示且获取属性正确*/
    it('ArkUI_Column_Comp_0729', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Column_Comp_0730', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为5号色显示且获取属性正确*/
    it('ArkUI_Column_Comp_0731', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件bindSheet.options.maskColor支持设置量规图的颜色为6号色显示且获取属性正确*/
    it('ArkUI_Column_Comp_0732', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.maskColor', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.maskColor', '通用属性7')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // bindSheet.options.title.title
    /*
     * 测试组件bindSheet.options.title.title支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0733', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.title', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.title', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.title.title支持设置false且获取属性正确
     * */
    it('ArkUI_Column_Comp_0734', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.title', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.title', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.title.subtitle
    /*
     * 测试组件bindSheet.options.title.subtitle支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0735', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.subtitle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.subtitle', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindSheet.options.title.subtitle支持设置false且获取属性正确
     * */
    it('ArkUI_Column_Comp_0736', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.title.subtitle', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.title.subtitle', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSheet.options.enableOutsideInteractive
    /*
     * 测试组件bindSheet.options.enableOutsideInteractive支持设置true且获取属性正确
     * */
    it('ArkUI_Column_Comp_0737', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindSheet.isShow', 'bindSheet.options.enableOutsideInteractive', '通用属性7')
      await titleSearch('基础属性', 'bindSheet.options.enableOutsideInteractive', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
  })
}