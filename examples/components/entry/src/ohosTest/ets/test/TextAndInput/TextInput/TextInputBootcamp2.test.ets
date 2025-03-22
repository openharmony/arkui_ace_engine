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
import { textInputBeforeAll } from './TextInput.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextInputBootcampTest2() {
  describe('TextInputBootcampTest2', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      textInputBeforeAll(done, delegator, driver);
    })
    //cancelButton
    /*
     *测试组件cancelButton支持设置CONSTANT且获取属性正确
     * */
    it('ArkUI_TextInput_111', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj)
        ],
        assertEqual: '{"style":0,"icon":"{\\"size\\":\\"24.00vp\\",\\"src\\":\\"\\",\\"color\\":\\"#FF000000\\"}"}'
      })
      done();
    })
    /*
     * 测试组件cancelButton支持设置INVNISIBLE且获取属性正确
     * */
    it('ArkUI_TextInput_112', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj)
        ],
        assertEqual: '{"style":1,"icon":"{\\"size\\":\\"24.00vp\\",\\"src\\":\\"\\",\\"color\\":\\"#FF000000\\"}"}'
      })
      done();
    })
    /*
     * 测试组件cancelButton支持设置INPUT且获取属性正确
     * */
    it('ArkUI_TextInput_113', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj)
        ],
        assertEqual: '{"style":2,"icon":"{\\"size\\":\\"24.00vp\\",\\"src\\":\\"\\",\\"color\\":\\"#FF000000\\"}"}'
      })
      done();
    })
    //selectAll
    /*
     * 测试组件selectAll支持设置false且获取属性正确
     */
    it('ArkUI_TextInput_114', 0, async (done: Function) => {
      await Search('参数列表', 'selectAll')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectAll', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })
    /*
     * 测试组件selectAll支持设置true且获取属性正确
     */
    it('ArkUI_TextInput_115', 0, async (done: Function) => {
      await Search('参数列表', 'selectAll')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selectAll', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })
    //showCounter.value
    /*
     * 测试组件showCounter.value支持设置false且获取属性正确
     */
    it('ArkUI_TextInput_116', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.value')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showCounter', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })
    /*
     * 测试组件showCounter.value支持设置true且获取属性正确
     */
    it('ArkUI_TextInput_117', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showCounter', JsonType.obj),
          new KeyStruct('value', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })
    //showCounter.options.thresholdPercentage
    it('ArkUI_TextInput_118', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.options.thresholdPercentage')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showCounter', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('thresholdPercentage', JsonType.value)
        ],
        assertEqual: 100
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showCounter', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('thresholdPercentage', JsonType.value)
        ],
        assertEqual: 0
      })
      done()
    })
    //showCounter.options.highlightBorder
    /*
     * 测试组件showCounter.options.highlightBorder支持设置false且获取属性正确
     */
    it('ArkUI_TextInput_119', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.options.highlightBorder')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showCounter', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('highlightBorder', JsonType.value)
        ],
        assertEqual: false
      })
      done();
    })
    /*
     * 测试组件showCounter.options.highlightBorder支持设置true且获取属性正确
     */
    it('ArkUI_TextInput_120', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.options.highlightBorder')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showCounter', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('highlightBorder', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })
    // contentType
    /*
     *测试组件contentType支持设置USER_NAME且获取属性正确
     * */
    it('ArkUI_TextInput_121', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.USER_NAME'
      })
      done();
    })
    /*
     *测试组件contentType支持设置PASSWORD且获取属性正确
     * */
    it('ArkUI_TextInput_122', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.VISIBLE_PASSWORD'
      })
      done();
    })
    /*
     *测试组件contentType支持设置NEW_PASSWORD且获取属性正确
     * */
    it('ArkUI_TextInput_123', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 2,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.NEW_PASSWORD'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置FULL_STREET_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextInput_124', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 3,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.FULL_STREET_ADDRESS'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置HOUSE_NUMBER且获取属性正确
     * */
    it('ArkUI_TextInput_125', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 4,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.HOUSE_NUMBER'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置DISTRICT_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextInput_126', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 5,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.DISTRICT_ADDRESS'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置CITY_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextInput_127', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 6,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.CITY_ADDRESS'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置PROVINCE_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextInput_128', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 7,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PROVINCE_ADDRESS'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置COUNTRY_ADDRESS且获取属性正确
     * */
    it('ArkUI_TextInput_129', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 8,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.COUNTRY_ADDRESS'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置PERSON_FULL_NAME且获取属性正确
     * */
    it('ArkUI_TextInput_130', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 9,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PERSON_FULL_NAME'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置PERSON_LAST_NAME且获取属性正确
     * */
    it('ArkUI_TextInput_131', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 10,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PERSON_LAST_NAME'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置PERSON_FIRST_NAME且获取属性正确
     * */
    it('ArkUI_TextInput_132', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 11,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PERSON_FIRST_NAME'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置PHONE_NUMBER且获取属性正确
     * */
    it('ArkUI_TextInput_133', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 12,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PHONE_NUMBER'
      })
      done();
    })
    /*
     * 测试组件contentType支持设置PHONE_COUNTRY_CODE且获取属性正确
     * */
    it('ArkUI_TextInput_134', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 13,
        id: 'TextInput',
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
    it('ArkUI_TextInput_135', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 14,
        id: 'TextInput',
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
    it('ArkUI_TextInput_136', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 15,
        id: 'TextInput',
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
    it('ArkUI_TextInput_137', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 16,
        id: 'TextInput',
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
    it('ArkUI_TextInput_138', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 17,
        id: 'TextInput',
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
    it('ArkUI_TextInput_139', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 18,
        id: 'TextInput',
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
    it('ArkUI_TextInput_140', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 'DETAIL_INFO_WITHOUT_STREET',
        id: 'TextInput',
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
    it('ArkUI_TextInput_141', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 'FORMAT_ADDRESS',
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.FORMAT_ADDRESS'
      })
      done();
    })
    //contentType的相关属性测试完毕，关闭contentType Toggle无需断言
    it('ArkUI_TextInput_142', 0, async (done: Function) => {
      await searchParentBlock('contentType', false, '参数列表')
      done();
    })
    //underlineColor
    /*
    *测试组件underlineColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_TextInput_143', 0, async (done: Function) => {
      await Search('参数列表', 'underlineColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('underlineColor', JsonType.obj)
        ],
        assertEqual: '{"normal":"#FF0A59F7","typing":"#99182431","error":"#FFFA2A2D","disable":"#14182431"}'
      })
      done();
    })
    /**
     * 测试组件underlineColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_TextInput_144', 0, async (done: Function) => {
      await Search('参数列表', 'underlineColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('underlineColor', JsonType.obj)
        ],
        assertEqual: '{"normal":"#FF646AFD","typing":"#99182431","error":"#FFFA2A2D","disable":"#14182431"}'
      })
      done();
    })
    /**
     * 测试组件underlineColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_TextInput_145', 0, async (done: Function) => {
      await Search('参数列表', 'underlineColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('underlineColor', JsonType.obj)
        ],
        assertEqual: '{"normal":"#FFFE7062","typing":"#99182431","error":"#FFFA2A2D","disable":"#14182431"}'
      })
      done();
    })
    /**
     * 测试组件underlineColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_TextInput_146', 0, async (done: Function) => {
      await Search('参数列表', 'underlineColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('underlineColor', JsonType.obj)
        ],
        assertEqual: '{"normal":"#FFE9E8ED","typing":"#99182431","error":"#FFFA2A2D","disable":"#14182431"}'
      })
      done();
    })
    /**
     * 测试组件underlineColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_TextInput_147', 0, async (done: Function) => {
      await Search('参数列表', 'underlineColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('underlineColor', JsonType.obj)
        ],
        assertEqual: '{"normal":"#FF1C1C1C","typing":"#99182431","error":"#FFFA2A2D","disable":"#14182431"}'
      })
      done();
    })
    /**
     * 测试组件underlineColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_TextInput_148', 0, async (done: Function) => {
      await Search('参数列表', 'underlineColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('underlineColor', JsonType.obj)
        ],
        assertEqual: '{"normal":"#FFFFFFFF","typing":"#99182431","error":"#FFFA2A2D","disable":"#14182431"}'
      })
      done();
    })
    //lineHeight
    it('ArkUI_TextInput_149', 0, async (done: Function) => {
      await Search('参数列表', 'lineHeight')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_150', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Underline且获取属性正确*/
    it('ArkUI_TextInput_151', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Underline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Overline且获取属性正确*/
    it('ArkUI_TextInput_152', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 2,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Overline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置LineThrough且获取属性正确*/
    it('ArkUI_TextInput_153', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
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
    it('ArkUI_TextInput_154', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextInput',
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
    it('ArkUI_TextInput_155', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextInput',
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
    it('ArkUI_TextInput_156', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextInput',
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
    it('ArkUI_TextInput_157', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextInput',
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
    it('ArkUI_TextInput_158', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextInput',
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
    it('ArkUI_TextInput_159', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
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
    it('ArkUI_TextInput_160', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
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
    it('ArkUI_TextInput_161', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
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
    it('ArkUI_TextInput_162', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 2,
        id: 'TextInput',
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
    it('ArkUI_TextInput_163', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 3,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DASHED"}'
      })
      done();
    })
    /*
     * 测试组件decoration.style支持设置WAVY且获取属性正确*/
    it('ArkUI_TextInput_164', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.WAVY"}'
      })
      done();
    })
    //letterSpacing
    it('ArkUI_TextInput_165', 0, async (done: Function) => {
      await Search('参数列表', 'letterSpacing')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextInput',
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
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //wordBreak
    /*
      测试组件wordBreak支持设置NORMAL且获取属性正确*/
    it('ArkUI_TextInput_166', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
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
    it('ArkUI_TextInput_167', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'break-all'
      })
      done();
    })
    /*
      测试组件wordBreak支持设置BREAK_WORD且获取属性正确*/
    it('ArkUI_TextInput_168', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'break-word'
      })
      done();
    })

    //textOverFlow
    /** 测试组件textOverFlow支持设置None且获取属性正确*/
    it('ArkUI_TextInput_169', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.None'
      })
      done();
    })
    /* * 测试组件textOverFlow支持设置Clip且获取属性正确*/
    it('ArkUI_TextInput_170', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Clip'
      })
      done();
    })
    /** 测试组件textOverFlow支持设置Ellipsis且获取属性正确*/
    it('ArkUI_TextInput_171', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 2,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Ellipsis'
      })
      done();
    })
    /** 测试组件textOverFlow支持设置MARQUEE且获取属性正确*/
    it('ArkUI_TextInput_172', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Marquee'
      })
      done();
    })
    //textIndent
    it('ArkUI_TextInput_173', 0, async (done: Function) => {
      await Search('参数列表', 'textIndent')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextInput',
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
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textIndent', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    //minFontSize
    it('ArkUI_TextInput_174', 0, async (done: Function) => {
      await Search('参数列表', 'minFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '100.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //maxFontSize
    it('ArkUI_TextInput_175', 0, async (done: Function) => {
      await Search('参数列表', 'maxFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontSize', JsonType.value)
        ],
        assertEqual: '100.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
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
    it('ArkUI_TextInput_176', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 0,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.MAX_LINES_FIRST'
      })
      done();
    })
    /** 测试组件heightAdaptivePolicy支持设置MIN_FONT_SIZE_FIRST且获取属性正确*/
    it('ArkUI_TextInput_177', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 1,
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST'
      })
      done();
    })
    /** 测试组件heightAdaptivePolicy支持设置LAYOUT_CONSTRAINT_FIRST且获取属性正确*/
    it('ArkUI_TextInput_178', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST'
      })
      done();
    })
    //showPassword
    /*
     * 测试组件showPassword支持设置false且获取属性正确
     */
    it('ArkUI_TextInput_179', 0, async (done: Function) => {
      await Search('参数列表', 'showPassword')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'showPassword'
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showPassword', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })
    /*
     * 测试组件showPassword支持设置true且获取属性正确
     */
    it('ArkUI_TextInput_180', 0, async (done: Function) => {
      await Search('参数列表', 'showPassword')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'showPassword'
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showPassword', JsonType.value),
        ],
        assertEqual: true
      })
      done();
    })

    //lineBreakStrategy
    /*
     * 测试组件lineBreakStrategy支持设置GREEDY且获取属性正确
     */
    it('ArkUI_TextInput_181', 0, async (done: Function) => {
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
    it('ArkUI_TextInput_182', 0, async (done: Function) => {
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
    it('ArkUI_TextInput_183', 0, async (done: Function) => {
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
    it('ArkUI_TextInput_184', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'enablePreviewText'
        },
        id: 'TextInput',
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
    it('ArkUI_TextInput_185', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'enablePreviewText'
        },
        id: 'TextInput',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enablePreviewText', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })
    //hapticFeedback
    /*
     * 测试组件hapticFeedback支持设置false且获取属性正确
     */
    it('ArkUI_TextInput_186', 0, async (done: Function) => {
      //无法获取参数进行断言
      await Search('参数列表', 'hapticFeedback')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hapticFeedback'
        }
      })
      done();
    })
    /*
     * 测试组件hapticFeedback支持设置true且获取属性正确
     */
    it('ArkUI_TextInput_187', 0, async (done: Function) => {
      //无法获取参数进行断言
      await Search('参数列表', 'hapticFeedback')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hapticFeedback'
        }
      })
      done();
    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_TextInput_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_TextInput_Comp_0006', 0, async (done: Function) => {
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
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0007', 0, async (done: Function) => {
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
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0008', 0, async (done: Function) => {
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
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0009', 0, async (done: Function) => {
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
        id: 'TextInput',
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
        id: 'TextInput',
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
    it('ArkUI_TextInput_Comp_0010', 0, async (done: Function) => {
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
  })
}