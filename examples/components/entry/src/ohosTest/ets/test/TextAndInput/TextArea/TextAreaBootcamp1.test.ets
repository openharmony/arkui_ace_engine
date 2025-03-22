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
import {
    buttonClick, JsonType,
    KeyStruct,
    radioClick,
    Search, Slide,
    sliderDrag, ToggleClick
} from '../../../utils';
import { textAreaBeforeAll } from './TextArea.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function TextAreaBootcampTest() {
  describe('TextAreaBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      textAreaBeforeAll(done, delegator, driver);
    })
    //placeholderColor
    /*
    *测试组件placeholderColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_TextArea_001', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件placeholderColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_TextArea_002', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件placeholderColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_TextArea_003', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件placeholderColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_TextArea_004', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件placeholderColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_TextArea_005', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件placeholderColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_TextArea_006', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //placeholderFont.size
    it('ArkUI_TextArea_007', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"200.00fp","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"0.00fp","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done()
    })
    //placeholderFont.weight
    /*
     * 测试组件placeholderFont.weight支持设置100且获取属性正确
     */
    it('ArkUI_TextArea_008', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"100","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置200且获取属性正确
     */
    it('ArkUI_TextArea_009', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"200","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置300且获取属性正确

     */
    it('ArkUI_TextArea_010', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"300","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置400且获取属性正确

     */
    it('ArkUI_TextArea_011', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"400","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置500且获取属性正确

     */
    it('ArkUI_TextArea_012', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"500","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置600且获取属性正确

     */
    it('ArkUI_TextArea_013', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 5,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"600","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置700且获取属性正确
     */
    it('ArkUI_TextArea_014', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 6,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"700","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置800且获取属性正确
     */
    it('ArkUI_TextArea_015', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 7,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"800","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置900且获取属性正确
     */
    it('ArkUI_TextArea_016', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 8,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","weight":"900","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置placeholderFont.weight.Lighter且获取属性正确
     */
    it('ArkUI_TextArea_017', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 9,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Lighter","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置placeholderFont.weight.Normal且获取属性正确
     */
    it('ArkUI_TextArea_018', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 10,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_TextArea_019', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 11,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Regular","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_TextArea_020', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 12,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Medium","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_TextArea_021', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 13,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Bold","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_TextArea_022', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Bolder","fontFamily":"sans-serif"}'
      })
      done();
    })
    //placeholderFont.style
    /*
     * 测试组件placeholderFont.style支持设置Normal且获取属性正确
     */
    it('ArkUI_TextArea_023', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.style')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"-1.00px","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.style支持设置Italic且获取属性正确
     */
    it('ArkUI_TextArea_024', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Italic","size":"-1.00px","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done();
    })
    //textAlign
    /*
     * 测试组件textAlign支持设置Start且获取属性正确
     */
    it('ArkUI_TextArea_025', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Start'
      })
      done();
    })
    /** 测试组件textAlign支持设置Center且获取属性正确*/
    it('ArkUI_TextArea_026', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Center'
      })
      done();
    })
    /** 测试组件textAlign支持设置End且获取属性正确*/
    it('ArkUI_TextArea_027', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.End'
      })
      done();
    })
    /** 测试组件textAlign支持设置JUSTIFY且获取属性正确*/
    it('ArkUI_TextArea_028', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Justify'
      })
      done();
    })
    //caretColor
    /*
    *测试组件caretColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_TextArea_029', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextArea'
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_TextArea_030', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea'
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_TextArea_031', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextArea'
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_TextArea_032', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextArea'
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_TextArea_033', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextArea'
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_TextArea_034', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea'
      })
      done();
    })
    //fontColor
    /*
    *测试组件fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_TextArea_035', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_TextArea_036', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_TextArea_037', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_TextArea_038', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_TextArea_039', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_TextArea_040', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //fontSize
    it('ArkUI_TextArea_041', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value)
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
          new KeyStruct('fontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //fontStyle
    /*
     * 测试组件fontStyle支持设置Normal且获取属性正确
     */
    it('ArkUI_TextArea_042', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.obj)
        ],
        assertEqual: 'FontStyle.Normal'
      })
      done();
    })
    /*
     * 测试组件fontStyle支持设置Italic且获取属性正确
     */
    it('ArkUI_TextArea_043', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.obj)
        ],
        assertEqual: 'FontStyle.Italic'
      })
      done();
    })
    //fontWeight
    /*
     * 测试组件fontWeight支持设置100且获取属性正确
     *
     */
    it('ArkUI_TextArea_044', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '100'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置200且获取属性正确
     *
     */
    it('ArkUI_TextArea_045', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '200'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置300且获取属性正确
     *
     */
    it('ArkUI_TextArea_046', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '300'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置400且获取属性正确
     *
     */
    it('ArkUI_TextArea_047', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '400'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置500且获取属性正确
     *
     */
    it('ArkUI_TextArea_048', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '500'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置600且获取属性正确
     *
     */
    it('ArkUI_TextArea_049', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 5,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '600'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置700且获取属性正确
     *
     */
    it('ArkUI_TextArea_050', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 6,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '700'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置800且获取属性正确
     *
     */
    it('ArkUI_TextArea_051', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 7,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '800'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置900且获取属性正确
     *
     */
    it('ArkUI_TextArea_052', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 8,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '900'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Lighter且获取属性正确
     *
     */
    it('ArkUI_TextArea_053', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 9,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Lighter'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Normal且获取属性正确
     *
     */
    it('ArkUI_TextArea_054', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 10,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Normal'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Regular且获取属性正确
     *
     */
    it('ArkUI_TextArea_055', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 11,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Regular'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Medium且获取属性正确
     *
     */
    it('ArkUI_TextArea_056', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 12,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Medium'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Bold且获取属性正确
     *
     */
    it('ArkUI_TextArea_057', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 13,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Bold'
      })
      done();
    })
    /*
     * 测试组件fontWeight支持设置FontWeight.Bolder且获取属性正确
     *
     */
    it('ArkUI_TextArea_058', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Bolder'
      })
      done();
    })
    //copyOptions
    /*
     *测试组件copyOption支持设置None且获取属性正确
     * */
    it('ArkUI_TextArea_059', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.None'
      })
      done();
    })
    /*
     * 测试组件copyOptions支持设置InApp且获取属性正确
     * */
    it('ArkUI_TextArea_060', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.InApp'
      })
      done();
    })
    /*
     * 测试组件copyOptions支持设置LocalDevice且获取属性正确
     * */
    it('ArkUI_TextArea_061', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.Local'
      })
      done();
    })
    //maxLength
    it('ArkUI_TextArea_062', 0, async (done: Function) => {
      await Search('参数列表', 'maxLength')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxLength', JsonType.value)
        ],
        assertEqual: '200'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxLength', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    //showCounter.value
    /*
     * 测试组件showCounter.value支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_063', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.value')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
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
    it('ArkUI_TextArea_064', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
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
    it('ArkUI_TextArea_065', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.options.thresholdPercentage')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'TextArea',
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
        id: 'TextArea',
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
    it('ArkUI_TextArea_066', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.options.highlightBorder')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
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
    it('ArkUI_TextArea_067', 0, async (done: Function) => {
      await Search('参数列表', 'showCounter.options.highlightBorder')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
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
    //style
    /*
     *测试组件style支持设置DEFAULT且获取属性正确
     * */
    it('ArkUI_TextArea_068', 0, async (done: Function) => {
      await Search('参数列表', 'style')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'TextContentStyle.DEFAULT'
      })
      done();
    })
    /*
     * 测试组件style支持设置INLINE且获取属性正确
     * */
    it('ArkUI_TextArea_069', 0, async (done: Function) => {
      await Search('参数列表', 'style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'TextContentStyle.INLINE'
      })
      done();
    })
    //enableKeyboardOnFocus
    /*
     * 测试组件enableKeyboardOnFocus支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_070', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enableKeyboardOnFocus')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件enableKeyboardOnFocus支持设置true且获取属性正确
     */
    it('ArkUI_TextArea_071', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enableKeyboardOnFocus')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //selectionMenuHidden
    /*
     * 测试组件selectionMenuHidden支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_072', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectionMenuHidden')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件selectionMenuHidden支持设置true且获取属性正确
     */
    it('ArkUI_TextArea_073', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectionMenuHidden')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //barState
    /*
     *测试组件barState支持设置Off且获取属性正确
     * */
    it('ArkUI_TextArea_074', 0, async (done: Function) => {
      await Search('参数列表', 'barState')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barState', JsonType.value)
        ],
        assertEqual: 'BarState.OFF'
      })
      done();
    })
    /*
     * 测试组件barState支持设置Auto且获取属性正确
     * */
    it('ArkUI_TextArea_075', 0, async (done: Function) => {
      await Search('参数列表', 'barState')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barState', JsonType.value)
        ],
        assertEqual: 'BarState.AUTO'
      })
      done();
    })
    /*
     * 测试组件barState支持设置On且获取属性正确
     * */
    it('ArkUI_TextArea_076', 0, async (done: Function) => {
      await Search('参数列表', 'barState')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('barState', JsonType.value)
        ],
        assertEqual: 'BarState.ON'
      })
      done();
    })
    //maxLines
    it('ArkUI_TextArea_077', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'maxLines')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //customKeyboard.value
    /*
     * 测试组件customKeyboard.value支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_078', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.value')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件customKeyboard.value支持设置true且获取属性正确
     */
    it('ArkUI_TextArea_079', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.value')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //customKeyboard.options
    /*
     * 测试组件customKeyboard.options支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_080', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.options')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件customKeyboard.options支持设置true且获取属性正确
     */
    it('ArkUI_TextArea_081', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.options')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //type
    /*
     *测试组件type支持设置NORMAL且获取属性正确
     * */
    it('ArkUI_TextArea_082', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'TextAreaType.NORMAL'
      })
      done();
    })
    /*
     *测试组件type支持设置NUMBER且获取属性正确
     * */
    it('ArkUI_TextArea_083', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'TextAreaType.NUMBER'
      })
      done();
    })
    /*
     *测试组件type支持设置PHONE_NUMBER且获取属性正确
     * */
    it('ArkUI_TextArea_084', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'TextAreaType.PHONE_NUMBER'
      })
      done();
    })
    /*
     * 测试组件type支持设置EMAIL且获取属性正确
     * */
    it('ArkUI_TextArea_085', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'TextAreaType.EMAIL'
      })
      done();
    })
    /*
     * 测试组件type支持设置NUMBER_DECIMAL且获取属性正确
     * */
    it('ArkUI_TextArea_086', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'TextAreaType.NUMBER_DECIMAL'
      })
      done();
    })
    /*
     * 测试组件type支持设置URL且获取属性正确
     * */
    it('ArkUI_TextArea_087', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'TextAreaType.URL'
      })
      done();
    })
    //enterKeyType
    /*
     *测试组件enterKeyType支持设置Go且获取属性正确
     * */
    it('ArkUI_TextArea_089', 0, async (done: Function) => {
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enterKeyType', JsonType.value)
        ],
        assertEqual: 'EnterKeyType.Go'
      })
      done();
    })
    /*
     *测试组件enterKeyType支持设置Search且获取属性正确
     * */
    it('ArkUI_TextArea_090', 0, async (done: Function) => {
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enterKeyType', JsonType.value)
        ],
        assertEqual: 'EnterKeyType.Search'
      })
      done();
    })
    /*
     *测试组件enterKeyType支持设置Send且获取属性正确
     * */
    it('ArkUI_TextArea_091', 0, async (done: Function) => {
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enterKeyType', JsonType.value)
        ],
        assertEqual: 'EnterKeyType.Send'
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置Next且获取属性正确
     * */
    it('ArkUI_TextArea_092', 0, async (done: Function) => {
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 3,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enterKeyType', JsonType.value)
        ],
        assertEqual: 'EnterKeyType.Next'
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置Done且获取属性正确
     * */
    it('ArkUI_TextArea_093', 0, async (done: Function) => {
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 4,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enterKeyType', JsonType.value)
        ],
        assertEqual: 'EnterKeyType.Done'
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置PREVIOUS且获取属性正确
     * */
    it('ArkUI_TextArea_094', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件enterKeyType支持设置NEW_LINE且获取属性正确
     * */
    it('ArkUI_TextArea_095', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //enableAutoFill
    /*
     * 测试组件enableAutoFill支持设置false且获取属性正确
     */
    it('ArkUI_TextArea_096', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enableAutoFill')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件enableAutoFill支持设置true且获取属性正确
     */
    it('ArkUI_TextArea_097', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enableAutoFill')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // contentType
    /*
     *测试组件contentType支持设置USER_NAME且获取属性正确
     * */
    it('ArkUI_TextArea_098', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 0,
        id: 'TextArea',
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
    it('ArkUI_TextArea_099', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 1,
        id: 'TextArea',
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
    it('ArkUI_TextArea_100', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 2,
        id: 'TextArea',
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
    it('ArkUI_TextArea_101', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 3,
        id: 'TextArea',
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
    it('ArkUI_TextArea_102', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 4,
        id: 'TextArea',
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
    it('ArkUI_TextArea_103', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 5,
        id: 'TextArea',
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
    it('ArkUI_TextArea_104', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 6,
        id: 'TextArea',
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
    it('ArkUI_TextArea_105', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 7,
        id: 'TextArea',
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
    it('ArkUI_TextArea_106', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 8,
        id: 'TextArea',
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
    it('ArkUI_TextArea_107', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 9,
        id: 'TextArea',
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
    it('ArkUI_TextArea_108', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 10,
        id: 'TextArea',
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
    it('ArkUI_TextArea_109', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 11,
        id: 'TextArea',
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
    it('ArkUI_TextArea_110', 0, async (done: Function) => {
      await Search('参数列表', 'contentType')
      await radioClick({
        radioClickObj: 12,
        id: 'TextArea',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentType', JsonType.value)
        ],
        assertEqual: 'TextContentType.PHONE_NUMBER'
      })
      done();
    })
  })
}