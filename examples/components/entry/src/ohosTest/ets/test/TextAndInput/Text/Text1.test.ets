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

import { beforeAll, describe, it } from '@ohos/hypium';
import { Driver, ON } from '@kit.TestKit';
import { Component } from '@ohos.UiTest';
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
import { TextStart } from './Text.test';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function Text1Test() {
  describe('Text1Test', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await TextStart(done);
    })

    //textAlign
    /*
     * 测试组件textAlign支持设置Start且获取属性正确
     */
    it('ArkUI_Text_001', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Start'
      })
      done();
    })
    /** 测试组件textAlign支持设置Center且获取属性正确*/
    it('ArkUI_Text_002', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Center'
      })
      done();
    })
    /** 测试组件textAlign支持设置End且获取属性正确*/
    it('ArkUI_Text_003', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.End'
      })
      done();
    })
    /** 测试组件textAlign支持设置JUSTIFY且获取属性正确*/
    it('ArkUI_Text_004', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Justify'
      })
      done();
    })
    //textOverFlow
    /** 测试组件textOverFlow支持设置None且获取属性正确*/
    it('ArkUI_Text_005', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.None'
      })
      done();
    })
    /* * 测试组件textOverFlow支持设置Clip且获取属性正确*/
    it('ArkUI_Text_006', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Clip'
      })
      done();
    })
    /** 测试组件textOverFlow支持设置Ellipsis且获取属性正确*/
    it('ArkUI_Text_007', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Ellipsis'
      })
      done();
    })
    /** 测试组件textOverFlow支持设置MARQUEE且获取属性正确*/
    it('ArkUI_Text_008', 0, async (done: Function) => {
      await Search('参数列表', 'textOverFlow')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textOverflow', JsonType.value)
        ],
        assertEqual: 'TextOverflow.Marquee'
      })
      done();
    })
    //maxLines
    it('ArkUI_Text_009', 0, async (done: Function) => {
      await Search('参数列表', 'maxLines')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxLines', JsonType.value)
        ],
        assertEqual: '20'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxLines', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    //lineHeight
    it('ArkUI_Text_010', 0, async (done: Function) => {
      await Search('参数列表', 'lineHeight')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_011', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Underline且获取属性正确*/
    it('ArkUI_Text_012', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Underline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置Overline且获取属性正确*/
    it('ArkUI_Text_013', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.Overline","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.type支持设置LineThrough且获取属性正确*/
    it('ArkUI_Text_014', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.type')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
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
    it('ArkUI_Text_015', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Text',
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
    it('ArkUI_Text_016', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Text',
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
    it('ArkUI_Text_017', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Text',
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
    it('ArkUI_Text_018', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Text',
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
    it('ArkUI_Text_019', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Text',
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
    it('ArkUI_Text_020', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
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
    it('ArkUI_Text_021', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.SOLID"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置DOUBLE且获取属性正确*/
    it('ArkUI_Text_022', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOUBLE"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置DOTTED且获取属性正确*/
    it('ArkUI_Text_023', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DOTTED"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置DASHED且获取属性正确*/
    it('ArkUI_Text_024', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.DASHED"}'
      })
      done();
    })
    /** 测试组件decoration.style支持设置WAVY且获取属性正确*/
    it('ArkUI_Text_025', 0, async (done: Function) => {
      await Search('参数列表', 'decoration.style')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('decoration', JsonType.obj)
        ],
        assertEqual: '{"type":"TextDecorationType.None","color":"#FF000000","style":"TextDecorationStyle.WAVY"}'
      })
      done();
    })
    //baseLineOffSet
    it('ArkUI_Text_026', 0, async (done: Function) => {
      await Search('参数列表', 'baseLineOffSet')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('baselineOffset', JsonType.value)
        ],
        assertEqual: '20'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('baselineOffset', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    //letterSpacing
    it('ArkUI_Text_027', 0, async (done: Function) => {
      await Search('参数列表', 'letterSpacing')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
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
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('letterSpacing', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //minFontSize
    it('ArkUI_Text_028', 0, async (done: Function) => {
      await Search('参数列表', 'minFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '200.00fp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //maxFontSize
    it('ArkUI_Text_029', 0, async (done: Function) => {
      await Search('参数列表', 'maxFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
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
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontSize', JsonType.value)
        ],
        assertEqual: '0.00fp'
      })
      done()
    })
    //textCase
    /** 测试组件textCase支持设置Normal且获取属性正确*/
    it('ArkUI_Text_030', 0, async (done: Function) => {
      await Search('参数列表', 'textCase')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textCase', JsonType.value)
        ],
        assertEqual: 'TextCase.Normal'
      })
      done();
    })
    /** 测试组件textCase支持设置LowerCase且获取属性正确*/
    it('ArkUI_Text_031', 0, async (done: Function) => {
      await Search('参数列表', 'textCase')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textCase', JsonType.value)
        ],
        assertEqual: 'TextCase.LowerCase'
      })
      done();
    })
    /* * 测试组件textCase支持设置UpperCase且获取属性正确*/
    it('ArkUI_Text_032', 0, async (done: Function) => {
      await Search('参数列表', 'textCase')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textCase', JsonType.value)
        ],
        assertEqual: 'TextCase.UpperCase'
      })
      done();
    })
    //fontColor
    /**测试组件fontColor支持设置量规图的颜色为1号色显示且获取属性正确
     **/
    it('ArkUI_Text_033', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /*  *
       * 测试组件fontColor支持设置量规图的颜色为2号色显示且获取属性正确*/
    it('ArkUI_Text_034', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为3号色显示且获取属性正确*/
    it('ArkUI_Text_035', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /* *
      * 测试组件fontColor支持设置量规图的颜色为4号色显示且获取属性正确*/
    it('ArkUI_Text_036', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为5号色显示且获取属性正确*/
    it('ArkUI_Text_037', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件fontColor支持设置量规图的颜色为6号色显示且获取属性正确*/
    it('ArkUI_Text_038', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //fontSize
    it('ArkUI_Text_039', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
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
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done()
    })
    //fontStyle
    /** 测试组件fontStyle支持设置Normal且获取属性正确
     * */
    it('ArkUI_Text_040', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value)
        ],
        assertEqual: 'FontStyle.Normal'
      })
      done();
    })
    /* * 测试组件fontStyle支持设置Italic且获取属性正确
     * */
    it('ArkUI_Text_041', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value)
        ],
        assertEqual: 'FontStyle.Italic'
      })
      done();
    })
    //fontWeight
    /* * 测试组件fontWeight支持设置100且获取属性正确
     **/
    it('ArkUI_Text_042', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '100'
      })
      done();
    })
    /** 测试组件fontWeight支持设置200且获取属性正确
     * */
    it('ArkUI_Text_043', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '200'
      })
      done();
    })
    /* * 测试组件fontWeight支持设置300且获取属性正确
     * */
    it('ArkUI_Text_044', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 2,
        id: 'Text',
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
         * */
    it('ArkUI_Text_045', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '400'
      })
      done();
    })
    /* * 测试组件fontWeight支持设置500且获取属性正确
     * */
    it('ArkUI_Text_046', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 4,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '500'
      })
      done();
    })
    /** 测试组件fontWeight支持设置600且获取属性正确
     * */
    it('ArkUI_Text_047', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 5,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '600'
      })
      done();
    })
    /* * 测试组件fontWeight支持设置700且获取属性正确
     **/
    it('ArkUI_Text_048', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 6,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '700'
      })
      done();
    })
    /** 测试组件fontWeight支持设置800且获取属性正确
     **/
    it('ArkUI_Text_049', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 7,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '800'
      })
      done();
    })
    /** 测试组件fontWeight支持设置900且获取属性正确
     **/
    it('ArkUI_Text_050', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 8,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: '900'
      })
      done();
    })
    /** 测试组件fontWeight支持设置FontWeight.Lighter且获取属性正确
     * */
    it('ArkUI_Text_051', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 9,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Lighter'
      })
      done();
    })
    /** 测试组件fontWeight支持设置FontWeight.Normal且获取属性正确
     * */
    it('ArkUI_Text_052', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 10,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Normal'
      })
      done();
    })
    /** 测试组件fontWeight支持设置FontWeight.Regular且获取属性正确
     **/
    it('ArkUI_Text_053', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 11,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Regular'
      })
      done();
    })
    /** 测试组件fontWeight支持设置FontWeight.Medium且获取属性正确
     **/
    it('ArkUI_Text_054', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 12,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Medium'
      })
      done();
    })
    /** 测试组件fontWeight支持设置FontWeight.Bold且获取属性正确
     **/
    it('ArkUI_Text_055', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 13,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Bold'
      })
      done();
    })
    /** 测试组件fontWeight支持设置FontWeight.Bolder且获取属性正确
     * */
    it('ArkUI_Text_056', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value)
        ],
        assertEqual: 'FontWeight.Bolder'
      })
      done();
    })
    //copyOptions
    /** 测试组件copyOption支持设置None且获取属性正确*/
    it('ArkUI_Text_057', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.None'
      })
      done();
    })
    /** 测试组件copyOptions支持设置InApp且获取属性正确*/
    it('ArkUI_Text_058', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.InApp'
      })
      done();
    })
    /** 测试组件copyOptions支持设置LocalDevice且获取属性正确*/
    it('ArkUI_Text_059', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.Local'
      })
      done();
    })
    //draggable
    /* * 测试组件draggable支持设置true且获取属性正确*/
    it('ArkUI_Text_060', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'draggable')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /* * 测试组件draggable支持设置false且获取属性正确*/
    it('ArkUI_Text_061', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'draggable')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //textShadow.radius
    it('ArkUI_Text_062', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.radius')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '360.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done()
    })
    //textShadow.type
    /** 测试组件textShadow.type支持设置COLOR且获取属性正确
     **/
    it('ArkUI_Text_063', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.type')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    /** 测试组件textShadow.type支持设置BLUR且获取属性正确
     **/
    it('ArkUI_Text_064', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.type')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done()
    })
    //textShadow.color
    /*
     测试组件textShadow.color支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Text_065', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件textShadow.color支持设置量规图的颜色为2号色显示且获取属性正确*/
    it('ArkUI_Text_066', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /*
     * 测试组件textShadow.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Text_067', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件textShadow.color支持设置量规图的颜色为4号色显示且获取属性正确*/
    it('ArkUI_Text_068', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /* *
      * 测试组件textShadow.color支持设置量规图的颜色为5号色显示且获取属性正确*/
    it('ArkUI_Text_069', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'textShadow.color'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /* *
      * 测试组件textShadow.color支持设置量规图的颜色为6号色显示且获取属性正确*/
    it('ArkUI_Text_070', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'textShadow.color'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //textShadow.OffsetX
    it('ArkUI_Text_071', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.OffsetX')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '200.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done()
    })
    //textShadow.OffsetY
    it('ArkUI_Text_072', 0, async (done: Function) => {
      await Search('参数列表', 'textShadow.OffsetY')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '200.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done()
    })
    //textShadow.fill
    /* * 测试组件textShadow.fill支持设置true且获取属性正确
     **/
    it('ArkUI_Text_073', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textShadow.fill')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'textShadow.fill'
        }
      })
      done()
    })
    /* * 测试组件textShadow.fill支持设置false且获取属性正确
     **/
    it('ArkUI_Text_074', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textShadow.fill')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'textShadow.fill'
        }
      })
      done()
    })
    //heightAdaptivePolicy
    /* * 测试组件heightAdaptivePolicy支持设置MAX_LINES_FIRST且获取属性正确
       */
    it('ArkUI_Text_075', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.MAX_LINES_FIRST'
      })
      done();
    })
    /** 测试组件heightAdaptivePolicy支持设置MIN_FONT_SIZE_FIRST且获取属性正确*/
    it('ArkUI_Text_076', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST'
      })
      done();
    })
    /** 测试组件heightAdaptivePolicy支持设置LAYOUT_CONSTRAINT_FIRST且获取属性正确*/
    it('ArkUI_Text_077', 0, async (done: Function) => {
      await Search('参数列表', 'heightAdaptivePolicy')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('heightAdaptivePolicy', JsonType.value)
        ],
        assertEqual: 'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST'
      })
      done();
    })
    //textIndent
    it('ArkUI_Text_078', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textIndent')
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
    //wordBreak
    /* * 测试组件wordBreak支持设置NORMAL且获取属性正确*/
    it('ArkUI_Text_079', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'normal'
      })
      done();
    })
    /* * 测试组件wordBreak支持设置BREAK_ALL且获取属性正确*/
    it('ArkUI_Text_080', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'break-all'
      })
      done();
    })
    /* * 测试组件wordBreak支持设置BREAK_WORD且获取属性正确*/
    it('ArkUI_Text_081', 0, async (done: Function) => {
      await Search('参数列表', 'wordBreak')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('wordBreak', JsonType.value)
        ],
        assertEqual: 'break-word'
      })
      done();
    })
    //selection.start
    it('ArkUI_Text_082', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'selection.start')
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
    //selection.end
    it('ArkUI_Text_083', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'selection.end')
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
    //ellipsisMode
    /** 测试组件ellipsisMode支持设置START且获取属性正确*/
    it('ArkUI_Text_084', 0, async (done: Function) => {
      await Search('参数列表', 'ellipsisMode')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('ellipsisMode', JsonType.value)
        ],
        assertEqual: 'EllipsisMode.START'
      })
      done();
    })
    /** 测试组件ellipsisMode支持设置CENTER且获取属性正确*/
    it('ArkUI_Text_085', 0, async (done: Function) => {
      await Search('参数列表', 'ellipsisMode')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('ellipsisMode', JsonType.value)
        ],
        assertEqual: 'EllipsisMode.CENTER'
      })
      done();
    })
    /** 测试组件ellipsisMode支持设置END且获取属性正确*/
    it('ArkUI_Text_086', 0, async (done: Function) => {
      await Search('参数列表', 'ellipsisMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('ellipsisMode', JsonType.value)
        ],
        assertEqual: 'EllipsisMode.END'
      })
      done();
    })
    //enableDataDetector
    /** 测试组件enableDataDetector支持设置false且获取属性正确*/
    it('ArkUI_Text_087', 0, async (done: Function) => {
      await Search('参数列表', 'enableDataDetector')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableDataDetector', JsonType.value)
        ],
        assertEqual: 'false'
      })
      done();
    })
    /** 测试组件enableDataDetector支持设置true且获取属性正确*/
    it('ArkUI_Text_088', 0, async (done: Function) => {
      await Search('参数列表', 'enableDataDetector')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableDataDetector', JsonType.value)
        ],
        assertEqual: 'true'
      })
      done();
    })
    //textDataDetectorConfig.types
    /*
     * 测试组件textDataDetectorConfig.types支持设置NULL且获取属性正确
     */
    it('ArkUI_Text_089', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置PHONE_NUMBER且获取属性正确
     */
    it('ArkUI_Text_090', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置URL且获取属性正确
     */
    it('ArkUI_Text_091', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置EMAIL且获取属性正确
     */
    it('ArkUI_Text_092', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置ADDRESS且获取属性正确
     */
    it('ArkUI_Text_093', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置DATE_TIME且获取属性正确
     */
    it('ArkUI_Text_094', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSelectionMenu.spanType
    /*
     * 测试组件bindSelectionMenu.spanType支持设置TEXT且获取属性正确
     */
    it('ArkUI_Text_095', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.spanType')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":0,"responseType":1,"menuType":0}]'
      })
      done();
    })
    /*
     * 测试组件bindSelectionMenu.spanType支持设置IMAGE且获取属性正确
     */
    it('ArkUI_Text_096', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.spanType')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":1,"responseType":1,"menuType":0}]'
      })
      done();
    })
    /*
     * 测试组件bindSelectionMenu.spanType支持设置MIXED且获取属性正确
     */
    it('ArkUI_Text_097', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.spanType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":2,"responseType":1,"menuType":0}]'
      })
      done();
    })
    //bindSelectionMenu.responseType
    /*
     * 测试组件bindSelectionMenu.responseType支持设置RIGHT_CLICK且获取属性正确
     */
    it('ArkUI_Text_098', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.responseType')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":0,"responseType":0,"menuType":0}]'
      })
      done();
    })
    /*
     * 测试组件bindSelectionMenu.responseType支持设置LONG_PRESS且获取属性正确
     */
    it('ArkUI_Text_099', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.responseType')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":0,"responseType":1,"menuType":0}]'
      })
      done();
    })
    /*
     * 测试组件bindSelectionMenu.responseType支持设置SELECT且获取属性正确
     */
    it('ArkUI_Text_100', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.responseType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":0,"responseType":2,"menuType":0}]'
      })
      done();
    })
    //lineSpacing.value
    it('ArkUI_Text_101', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'lineSpacing.value')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done()
    })
    //lineSpacing.unit
    /*
     * 测试组件lineSpacing.unit支持设置PX且获取属性正确
     */
    it('ArkUI_Text_102', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置VP且获取属性正确
     */
    it('ArkUI_Text_103', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置FP且获取属性正确
     */
    it('ArkUI_Text_104', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置PERCENT且获取属性正确
     */
    it('ArkUI_Text_105', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件lineSpacing.unit支持设置LPX且获取属性正确
     */
    it('ArkUI_Text_106', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await Search('参数列表', 'lineSpacing.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //privacySensitive
    /*
     * 测试组件privacySensitive支持设置false且获取属性正确
     */
    it('ArkUI_Text_107', 0, async (done: Function) => {
      await Search('参数列表', 'privacySensitive')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('privacySensitive', JsonType.value)
        ],
        assertEqual: false
      })
      done();
    })
    /*
     * 测试组件privacySensitive支持设置true且获取属性正确
     */
    it('ArkUI_Text_108', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'privacySensitive')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('privacySensitive', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })
    //lineBreakStrategy
    /*
     * 测试组件lineBreakStrategy支持设置GREEDY且获取属性正确
     */
    it('ArkUI_Text_109', 0, async (done: Function) => {
      await Search('参数列表', 'lineBreakStrategy')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineBreakStrategy', JsonType.value)
        ],
        assertEqual: 'greedy'
      })
      done();
    })
  })
}