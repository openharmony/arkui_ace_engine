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
  Search,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { searchBeforeAll } from './Search.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SearchBootcampTest2() {
  describe('SearchBootcampTest2', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      searchBeforeAll(done, delegator, driver);
    })
    /*
      *测试组件enterKeyType支持设置Send且获取属性正确
      * */
    it('ArkUI_Search_101', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置Next且获取属性正确
     * */
    it('ArkUI_Search_102', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置Done且获取属性正确
     * */
    it('ArkUI_Search_103', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置PREVIOUS且获取属性正确
     * */
    it('ArkUI_Search_104', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置NEW_LINE且获取属性正确
     * */
    it('ArkUI_Search_105', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    //lineHeight
    it('ArkUI_Search_106', 0, async (done: Function) => {
      await Search('参数列表', 'lineHeight')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineHeight', JsonType.value)
        ],
        assertEqual: '10.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineHeight', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //decoration.type
    /* * 测试组件decoration.type支持设置None且获取属性正确*/
    it('ArkUI_Search_107', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Underline且获取属性正确*/
    it('ArkUI_Search_108', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Underline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Overline且获取属性正确*/
    it('ArkUI_Search_109', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Overline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置LineThrough且获取属性正确*/
    it('ArkUI_Search_110', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.LineThrough","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    //decoration.color
    /* *测试组件decoration.color支持设置量规图的颜色为1号色显示且获取属性正确
     * */
    it('ArkUI_Search_111', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF0A59F7","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为2号色显示且获取属性正确*/
    it('ArkUI_Search_112', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF646AFD","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /* *
      * 测试组件decoration.color支持设置量规图的颜色为3号色显示且获取属性正确*/
    it('ArkUI_Search_113', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFFE7062","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /* *
      * 测试组件decoration.color支持设置量规图的颜色为4号色显示且获取属性正确*/
    it('ArkUI_Search_114', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFE9E8ED","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /**
     * 测试组件decoration.color支持设置量规图的颜色为5号色显示且获取属性正确*/
    it('ArkUI_Search_115', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF1C1C1C","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /* *
      * 测试组件decoration.color支持设置量规图的颜色为6号色显示且获取属性正确*/
    it('ArkUI_Search_116', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFFFFFFF","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    //decoration.style
    /* * 测试组件decoration.style支持设置SOLID且获取属性正确*/
    it('ArkUI_Search_117', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置DOUBLE且获取属性正确*/
    it('ArkUI_Search_118', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOUBLE"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置DOTTED且获取属性正确*/
    it('ArkUI_Search_119', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOTTED"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置DASHED且获取属性正确*/
    it('ArkUI_Search_120', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DASHED"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置WAVY且获取属性正确*/
    it('ArkUI_Search_121', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.WAVY"}'
      })
      done();
    })
    //letterSpacing
    it('ArkUI_Search_122', 0, async (done: Function) => {
      await Search('参数列表', 'letterSpacing')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '20.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //selectedBackgroundColor
    /*
    *测试组件selectedBackgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_123', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#330A59F7'
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Search_124', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33646AFD'
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Search_125', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33FE7062'
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Search_126', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33E9E8ED'
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Search_127', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#331C1C1C'
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Search_128', 0, async (done: Function) => {
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33FFFFFF'
      })
      done();
    })
    //textIndent
    it('ArkUI_Search_129', 0, async (done: Function) => {
      await Search('参数列表', 'textIndent')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'textIndent'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textIndent', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'textIndent'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textIndent', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    //minFontSize
    it('ArkUI_Search_130', 0, async (done: Function) => {
      await Search('参数列表', 'minFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'minFontSize'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '200.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'minFontSize'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //maxFontSize
    it('ArkUI_Search_131', 0, async (done: Function) => {
      await Search('参数列表', 'maxFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'maxFontSize'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontSize', JsonType.value)
        ],
        assertEqual: '200.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'maxFontSize'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //enablePreviewText
    /*
     * 测试组件enablePreviewText支持设置false且获取属性正确
     */
    it('ArkUI_Search_132', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'enablePreviewText'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enablePreviewText', JsonType.value)
        ],
        assertEqual: false
      })
      done();
    })
    /*
     * 测试组件enablePreviewText支持设置true且获取属性正确
     */
    it('ArkUI_Search_133', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'enablePreviewText'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enablePreviewText', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })
    //searchButton.value
    /*
     * 测试组件searchButton.value支持设置search且获取属性正确
     */
    it('ArkUI_Search_134', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.value')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'searchButton.value'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButton', JsonType.value)
        ],
        assertEqual: 'search'
      })
      done();
    })
    /*
     * 测试组件searchButton.value支持设置Search且获取属性正确
     */
    it('ArkUI_Search_135', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButton', JsonType.value)
        ],
        assertEqual: 'Search'
      })
      done();
    })
    //searchButton.option.fontSize
    it('ArkUI_Search_136', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'searchButton.option.fontSize'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '200.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'searchButton.option.fontSize'
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: '0.00fp'
      })
      done()
    })


    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Search_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0006', 0, async (done: Function) => {
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
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0007', 0, async (done: Function) => {
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
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0008', 0, async (done: Function) => {
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
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0009', 0, async (done: Function) => {
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
        id: 'Search',
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
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_Search_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0017', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0018', 0, async (done: Function) => {
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
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_Search_Comp_0019', 0, async (done: Function) => {
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
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_Search_Comp_0020', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0021', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0022', 0, async (done: Function) => {
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
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0023', 0, async (done: Function) => {
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
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0024', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_Search_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_Search_Comp_0027', 0, async (done: Function) => {
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Search_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Search_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_Search_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Search_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Search_Comp_0034', 0, async (done: Function) => {
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_Comp_0036', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0037', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0038', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0039', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0040', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0041', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0042', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0043', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0044', 0, async (done: Function) => {
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
    it('ArkUI_Search_Comp_0045', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Search_Comp_0046', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Search_Comp_0047', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Search_Comp_0048', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Search_Comp_0049', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Search_Comp_0050', 0, async (done: Function) => {
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
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

  })
}