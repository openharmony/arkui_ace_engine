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
    buttonClick, JsonType,
    KeyStruct,
    radioClick,
    Search,
    searchParentBlock, Slide,
    sliderDrag,
    titleSearch,
    ToggleClick
} from '../../../utils';
import { textAreaBeforeAll } from './TextArea.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextAreaBootcampTest2() {
  describe('TextAreaBootcampTest2', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      textAreaBeforeAll(done, delegator, driver);
    })

    /*
    * 测试组件contentType支持设置PHONE_COUNTRY_CODE且获取属性正确
    * */
    it('ArkUI_TextArea_111', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 13,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PHONE_COUNTRY_CODE'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置FULL_PHONE_NUMBER且获取属性正确
     * */
    it('ArkUI_TextArea_112', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 14,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.FULL_PHONE_NUMBER'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置EMAIL_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextArea_113', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 15,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.EMAIL_ADDRESS'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置BANK_CARD_NUMBER且获取属性正确
     * */
    it('ArkUI_TextArea_114', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 16,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.BANK_CARD_NUMBER'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置ID_CARD_NUMBER且获取属性正确
     * */
    it('ArkUI_TextArea_115', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 17,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.ID_CARD_NUMBER'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置NICKNAME且获取属性正确
     * */
    it('ArkUI_TextArea_116', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 18,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.NICKNAME'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置DETAIL_INFO_WITHOUT_STREET且获取属性正确
     * */
    it('ArkUI_TextArea_117', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 'DETAIL_INFO_WITHOUT_STREET',
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.DETAIL_INFO_WITHOUT_STREET'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置FORMAT_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextArea_118', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 'FORMAT_ADDRESS',
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.FORMAT_ADDRESS'
      })
      done();
    })
    //contentType的相关属性测试完毕，关闭contentType Toggle无需断言
    it('ArkUI_TextArea_119', 0, async (done: Function) => {
      await searchParentBlock('contentType', false, '参数列表')
      done();
    })
    //lineHeight
    it('ArkUI_TextArea_120', 0, async (done: Function) => {
      await Search('参数列表', 'lineHeight')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_121', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Underline且获取属性正确*/
    it('ArkUI_TextArea_122', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Underline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Overline且获取属性正确*/
    it('ArkUI_TextArea_123', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Overline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置LineThrough且获取属性正确*/
    it('ArkUI_TextArea_124', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
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
    it('ArkUI_TextArea_125', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextArea',
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
    it('ArkUI_TextArea_126', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea',
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
    it('ArkUI_TextArea_127', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextArea',
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
    it('ArkUI_TextArea_128', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextArea',
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
    it('ArkUI_TextArea_129', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextArea',
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
    it('ArkUI_TextArea_130', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FFFFFFFF","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    //decoration.style
    /*
     * 测试组件decoration.style支持设置SOLID且获取属性正确
     */
    it('ArkUI_TextArea_131', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /*
     *  测试组件decoration.style支持设置DOUBLE且获取属性正确*/
    it('ArkUI_TextArea_132', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOUBLE"}'
      })
      done();
    })
    /*
    测试组件decoration.style支持设置DOTTED且获取属性正确*/
    it('ArkUI_TextArea_133', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOTTED"}'
      })
      done();
    })
    /*
     * 测试组件decoration.style支持设置DASHED且获取属性正确*/
    it('ArkUI_TextArea_134', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DASHED"}'
      })
      done();
    })
    //测试组件decoration.style支持设置WAVY且获取属性正确
    it('ArkUI_TextArea_135', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.WAVY"}'
      })
      done();
    })
    //letterSpacing
    it('ArkUI_TextArea_136', 0, async (done: Function) => {
      await Search('参数列表', 'letterSpacing')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
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
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //测试组件wordBreak支持设置NORMAL且获取属性正确
    it('ArkUI_TextArea_137', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'normal'
      })
      done();
    })
    /*
      测试组件wordBreak支持设置BREAK_ALL且获取属性正确*/
    it('ArkUI_TextArea_138', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'break-all'
      })
      done();
    })
    //测试组件wordBreak支持设置BREAK_WORD且获取属性正确
    it('ArkUI_TextArea_139', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'break-word'
      })
      done();
    })
    //测试组件selectedBackgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    it('ArkUI_TextArea_140', 0, async (done: Function) => {
      await Search('参数列表', 'SelectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#330A59F7'
      })
      done();
    })
    /**
     * 测试组件SelectedBackgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_TextArea_141', 0, async (done: Function) => {
      await Search('参数列表', 'SelectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33646AFD'
      })
      done();
    })
    /**
     * 测试组件SelectedBackgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_TextArea_142', 0, async (done: Function) => {
      await Search('参数列表', 'SelectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33FE7062'
      })
      done();
    })
    /**
     * 测试组件SelectedBackgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_TextArea_143', 0, async (done: Function) => {
      await Search('参数列表', 'SelectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33E9E8ED'
      })
      done();
    })
    /**
     * 测试组件SelectedBackgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_TextArea_144', 0, async (done: Function) => {
      await Search('参数列表', 'SelectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#331C1C1C'
      })
      done();
    })
    /**
     * 测试组件SelectedBackgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_TextArea_145', 0, async (done: Function) => {
      await Search('参数列表', 'SelectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectedBackgroundColor', JsonType.value)
        ],
        assertEqual: '#33FFFFFF'
      })
      done();
    })
    //caretStyle.width
    it('ArkUI_TextArea_146', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.width')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FF007DFF","width":"100.00vp"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FF007DFF","width":"0.00vp"}'
      })
      done()
    })
    //caretStyle.color
    /*
    *测试组件caretStyle.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_TextArea_147', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FF0A59F7","width":"2.00vp"}'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_TextArea_148', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FF646AFD","width":"2.00vp"}'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_TextArea_149', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FFFE7062","width":"2.00vp"}'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_TextArea_150', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FFE9E8ED","width":"2.00vp"}'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_TextArea_151', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FF1C1C1C","width":"2.00vp"}'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_TextArea_152', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj)
        ],
        assertEqual: '{"color":"#FFFFFFFF","width":"2.00vp"}'
      })
      done();
    })
    //textIndent
    it('ArkUI_TextArea_153', 0, async (done: Function) => {
      await Search('参数列表', 'textIndent')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textIndent', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textIndent', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    //textOverFlow
    /** 测试组件textOverFlow支持设置None且获取属性正确*/
    it('ArkUI_TextArea_154', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.None'
      })
      done();
    })
    /* * 测试组件textOverFlow支持设置Clip且获取属性正确*/
    it('ArkUI_TextArea_155', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Clip'
      })
      done();
    })
    /** 测试组件textOverFlow支持设置Ellipsis且获取属性正确*/
    it('ArkUI_TextArea_156', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Ellipsis'
      })
      done();
    })
    /** 测试组件textOverFlow支持设置MARQUEE且获取属性正确*/
    it('ArkUI_TextArea_157', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Marquee'
      })
      done();
    })
    //minFontSize
    it('ArkUI_TextArea_158', 0, async (done: Function) => {
      await Search('参数列表', 'minFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '1.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //maxFontSize
    it('ArkUI_TextArea_159', 0, async (done: Function) => {
      await Search('参数列表', 'maxFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontSize', JsonType.value)
        ],
        assertEqual: '200.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //heightAdaptivePolicy
    /* * 测试组件heightAdaptivePolicy支持设置MAX_LINES_FIRST且获取属性正确
     */
    it('ArkUI_TextArea_160', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.MAX_LINES_FIRST'
      })
      done();
    })
    /** 测试组件heightAdaptivePolicy支持设置MIN_FONT_SIZE_FIRST且获取属性正确*/
    it('ArkUI_TextArea_161', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST'
      })
      done();
    })
    /** 测试组件heightAdaptivePolicy支持设置LAYOUT_CONSTRAINT_FIRST且获取属性正确*/
    it('ArkUI_TextArea_162', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST'
      })
      done();
    })
    //lineSpacing.value
    it('ArkUI_TextArea_163', 0, async (done: Function) => {
      await Search('参数列表', 'lineSpacing.value')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'lineSpacing.value'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '20.00px'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'lineSpacing.value'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done()
    })
    //lineSpacing.unit
    /*
     * 测试组件lineSpacing.unit支持设置PX且获取属性正确
     */
    it('ArkUI_TextArea_164', 0, async (done: Function) => {
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'lineSpacing.unit'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置VP且获取属性正确
     */
    it('ArkUI_TextArea_165', 0, async (done: Function) => {
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'lineSpacing.unit'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置FP且获取属性正确
     */
    it('ArkUI_TextArea_166', 0, async (done: Function) => {
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'lineSpacing.unit'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置PERCENT且获取属性正确
     */
    it('ArkUI_TextArea_167', 0, async (done: Function) => {
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'lineSpacing.unit'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '0.00%'
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置LPX且获取属性正确
     */
    it('ArkUI_TextArea_168', 0, async (done: Function) => {
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'lineSpacing.unit'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineSpacing', JsonType.value)
        ],
        assertEqual: '0.00lpx'
      })
      done();
    })
    //lineBreakStrategy
    /*
     * 测试组件lineBreakStrategy支持设置GREEDY且获取属性正确
     */
    it('ArkUI_TextArea_169', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'lineBreakStrategy')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'lineBreakStrategy'
        }
      })
      done();
    })
    /*
     * 测试组件lineBreakStrategy支持设置HIGH_QUALITY且获取属性正确
     */
    it('ArkUI_TextArea_170', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'lineBreakStrategy')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'lineBreakStrategy'
        }
      })
      done();
    })
    /*
     * 测试组件lineBreakStrategy支持设置BALANCED且获取属性正确
     */
    it('ArkUI_TextArea_171', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'lineBreakStrategy')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'lineBreakStrategy'
        }
      })
      done();
    })
    //enablePreviewText
    /*
     * 测试组件enablePreviewText支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_172', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'enablePreviewText'
        },
        id: 'TextArea',
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
    it('ArkUI_TextArea_173', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'enablePreviewText'
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enablePreviewText', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_TextArea_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_TextArea_Comp_0006', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0007', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0008', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0009', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_TextArea_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_TextArea_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_TextArea_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_TextArea_Comp_0014', 0, async (done: Function) => {
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
    //测试组件position.right且获取属性正确
    it('ArkUI_TextArea_Comp_0015', 0, async (done: Function) => {
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
    //测试关闭position
    it('ArkUI_TextArea_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_TextArea_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    //测试组件markAnchor.x且获取属性正确
    it('ArkUI_TextArea_Comp_0018', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //测试组件markAnchor.y且获取属性正确
    it('ArkUI_TextArea_Comp_0019', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //测试关闭markAnchor
    it('ArkUI_TextArea_Comp_0020', 0, async (done: Function) => {
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
    //测试开启offset
    it('ArkUI_TextArea_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    //测试组件offset.x且获取属性正确
    it('ArkUI_TextArea_Comp_0022', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //测试组件offset.y且获取属性正确
    it('ArkUI_TextArea_Comp_0023', 0, async (done: Function) => {
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
        id: 'TextArea',
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
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //测试关闭offset
    it('ArkUI_TextArea_Comp_0024', 0, async (done: Function) => {
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
    //测试组件borderStyle
    it('ArkUI_TextArea_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_TextArea_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_TextArea_Comp_0027', 0, async (done: Function) => {
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextArea',
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
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    //测试组件borderColor
    it('ArkUI_TextArea_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    it('ArkUI_TextArea_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

  })
}