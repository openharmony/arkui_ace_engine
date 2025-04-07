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
import { richEditorBeforeAll } from './RichEditor.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function RichEditorBootcampTest1() {
  describe('RichEditorBootcampTest1', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      richEditorBeforeAll(done, delegator, driver);
    })
    //Direction
    /*
     *测试组件Direction支持设置Auto且获取属性正确
     * */
    it('ArkUI_RichEditor_001', 0, async (done: Function) => {
      await Search('参数列表', 'Direction')
      await radioClick({
        radioClickObj: 0,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'Direction.Auto'
      })
      done();
    })
    /*
     *测试组件Direction支持设置Rtl且获取属性正确
     * */
    it('ArkUI_RichEditor_002', 0, async (done: Function) => {
      await Search('参数列表', 'Direction')
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'Direction.Rtl'
      })
      done();
    })
    /*
     *测试组件Direction支持设置Ltr且获取属性正确
     * */
    it('ArkUI_RichEditor_003', 0, async (done: Function) => {
      await Search('参数列表', 'Direction')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'Direction.Ltr'
      })
      done();
    })
    //customSelectionMenu
    /*
     * 测试组件customSelectionMenu支持设置true且获取属性正确
     */
    it('ArkUI_RichEditor_004', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customSelectionMenu')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件customSelectionMenu支持设置false且获取属性正确
     */
    it('ArkUI_RichEditor_005', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customSelectionMenu')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //textSelectionMenu
    /*
     * 测试组件textSelectionMenu支持设置true且获取属性正确
     */
    it('ArkUI_RichEditor_006', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await searchParentBlock('customSelectionMenu', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'textSelectionMenu')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件textSelectionMenu支持设置false且获取属性正确
     */
    it('ArkUI_RichEditor_007', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await searchParentBlock('customSelectionMenu', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'textSelectionMenu')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //systemSelectionMenu
    /*
     * 测试组件systemSelectionMenu支持设置true且获取属性正确
     */
    it('ArkUI_RichEditor_008', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await searchParentBlock('customSelectionMenu', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'systemSelectionMenu')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件systemSelectionMenu支持设置false且获取属性正确
     */
    it('ArkUI_RichEditor_009', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await searchParentBlock('customSelectionMenu', true, '参数列表')
      await radioClick({
        radioClickObj: 0
      })
      await Search('参数列表', 'systemSelectionMenu')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //customSelectionMenu相关属性测试完成，关闭Toggle，无需断言
    it('ArkUI_RichEditor_010', 0, async (done: Function) => {
      await Search('参数列表', 'customSelectionMenu')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //selectedBackgroundColor
    /*
    *测试组件selectedBackgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_RichEditor_011', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 0
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_012', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 1
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_013', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 2
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_014', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 3
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_015', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 4
      })
      done();
    })
    /**
     * 测试组件selectedBackgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_016', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'selectedBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //BackgroundColor
    /*
    *测试组件BackgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_RichEditor_017', 0, async (done: Function) => {
      await Search('参数列表', 'BackgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件BackgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_018', 0, async (done: Function) => {
      await Search('参数列表', 'BackgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件BackgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_019', 0, async (done: Function) => {
      await Search('参数列表', 'BackgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件BackgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_020', 0, async (done: Function) => {
      await Search('参数列表', 'BackgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件BackgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_021', 0, async (done: Function) => {
      await Search('参数列表', 'BackgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件BackgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_022', 0, async (done: Function) => {
      await Search('参数列表', 'BackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //customKeyboard.option
    /*
     * 测试组件customKeyboard.option支持设置false且获取属性正确
     */
    it('ArkUI_RichEditor_023', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.option')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件customKeyboard.option支持设置true且获取属性正确
     */
    it('ArkUI_RichEditor_024', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.option')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindSelectionMenu.spanType
    /*
     * 测试组件bindSelectionMenu.spanType支持设置RichEditor且获取属性正确
     */
    it('ArkUI_RichEditor_025', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.spanType')
      await radioClick({
        radioClickObj: 0,
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_026', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.spanType')
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_027', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.spanType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_028', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.responseType')
      await radioClick({
        radioClickObj: 0,
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_029', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.responseType')
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_030', 0, async (done: Function) => {
      await Search('参数列表', 'bindSelectionMenu.responseType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('bindSelectionMenu', JsonType.value)
        ],
        assertEqual: '[{"spanType":0,"responseType":2,"menuType":0}]'
      })
      done();
    })
    //copyOptions
    /**
     * 测试组件copyOption支持设置None且获取属性正确*/
    it('ArkUI_RichEditor_031', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 0,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.None'
      })
      done();
    })
    /**
     * 测试组件copyOptions支持设置InApp且获取属性正确*/
    it('ArkUI_RichEditor_032', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.InApp'
      })
      done();
    })
    /**
     * 测试组件copyOptions支持设置LocalDevice且获取属性正确*/
    it('ArkUI_RichEditor_033', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.Local'
      })
      done();
    })
    //enableDataDetector
    /**
     * 测试组件enableDataDetector支持设置false且获取属性正确*/
    it('ArkUI_RichEditor_034', 0, async (done: Function) => {
      await Search('参数列表', 'enableDataDetector')
      await radioClick({
        radioClickObj: 0,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableDataDetector', JsonType.value)
        ],
        assertEqual: 'false'
      })
      done();
    })
    /**
     * 测试组件enableDataDetector支持设置true且获取属性正确*/
    it('ArkUI_RichEditor_035', 0, async (done: Function) => {
      await Search('参数列表', 'enableDataDetector')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_036', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_037', 0, async (done: Function) => {
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dataDetectorConfig', JsonType.obj)
        ],
        assertEqual: '{"types":"phoneNum","color":"#FF007DFF","decoration":{"type":1,"color":"#FF007DFF","style":0}}'
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置URL且获取属性正确
     */
    it('ArkUI_RichEditor_038', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dataDetectorConfig', JsonType.obj)
        ],
        assertEqual: '{"types":"url","color":"#FF007DFF","decoration":{"type":1,"color":"#FF007DFF","style":0}}'
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置EMAIL且获取属性正确
     */
    it('ArkUI_RichEditor_039', 0, async (done: Function) => {
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 3,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dataDetectorConfig', JsonType.obj)
        ],
        assertEqual: '{"types":"email","color":"#FF007DFF","decoration":{"type":1,"color":"#FF007DFF","style":0}}'
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置ADDRESS且获取属性正确
     */
    it('ArkUI_RichEditor_040', 0, async (done: Function) => {
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 4,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dataDetectorConfig', JsonType.obj)
        ],
        assertEqual: '{"types":"location","color":"#FF007DFF","decoration":{"type":1,"color":"#FF007DFF","style":0}}'
      })
      done();
    })
    /*
     * 测试组件textDataDetectorConfig.types支持设置DATE_TIME且获取属性正确
     */
    it('ArkUI_RichEditor_041', 0, async (done: Function) => {
      await Search('参数列表', 'textDataDetectorConfig.types')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('dataDetectorConfig', JsonType.obj)
        ],
        assertEqual: '{"types":"datetime","color":"#FF007DFF","decoration":{"type":1,"color":"#FF007DFF","style":0}}'
      })
      done();
    })
    //enablePreviewText
    /*
     * 测试组件enablePreviewText支持设置false且获取属性正确
     */
    it('ArkUI_RichEditor_042', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件enablePreviewText支持设置true且获取属性正确
     */
    it('ArkUI_RichEditor_043', 0, async (done: Function) => {
      await Search('参数列表', 'enablePreviewText')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //placeholderStyle.font.size
    it('ArkUI_RichEditor_044', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"200.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"1.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done()
    })
    //placeholderStyle.font.weight
    /*
     * 测试组件placeholderStyle.font.weight支持设置100且获取属性正确
     */
    it('ArkUI_RichEditor_045', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"100","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置200且获取属性正确
     */
    it('ArkUI_RichEditor_046', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"200","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置300且获取属性正确

     */
    it('ArkUI_RichEditor_047', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"300","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置400且获取属性正确

     */
    it('ArkUI_RichEditor_048', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"400","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置500且获取属性正确
     */
    it('ArkUI_RichEditor_049', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"500","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置600且获取属性正确
     */
    it('ArkUI_RichEditor_050', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 5,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"600","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置700且获取属性正确
     */
    it('ArkUI_RichEditor_051', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 6,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"700","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置800且获取属性正确
     */
    it('ArkUI_RichEditor_052', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 7,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"800","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置900且获取属性正确
     */
    it('ArkUI_RichEditor_053', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 8,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"900","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置placeholderStyle.font.weight.Lighter且获取属性正确
     */
    it('ArkUI_RichEditor_054', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 9,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Lighter","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置placeholderStyle.font.weight.Normal且获取属性正确
     */
    it('ArkUI_RichEditor_055', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 10,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_RichEditor_056', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 11,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Regular","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_RichEditor_057', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 12,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Medium","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_RichEditor_058', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 13,
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Bold","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_RichEditor_059', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.weight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Bolder","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    //placeholderStyle.font.style
    /*
     * 测试组件placeholderStyle.font.style支持设置Normal且获取属性正确
     */
    it('ArkUI_RichEditor_060', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.style')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'placeholderStyle.font.style'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    /*
     * 测试组件placeholderStyle.font.style支持设置Italic且获取属性正确
     */
    it('ArkUI_RichEditor_061', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.font.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'placeholderStyle.font.style'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Italic"}","fontColor":"#99182431"}"}'
      })
      done();
    })
    //placeholderStyle.fontColor
    /*
    *测试组件placeholderStyle.fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_RichEditor_062', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'placeholderStyle.fontColor'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#FF0A59F7"}"}'
      })
      done();
    })
    /**
     * 测试组件placeholderStyle.fontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_063', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'placeholderStyle.fontColor'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#FF646AFD"}"}'
      })
      done();
    })
    /**
     * 测试组件placeholderStyle.fontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_064', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'placeholderStyle.fontColor'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#FFFE7062"}"}'
      })
      done();
    })
    /**
     * 测试组件placeholderStyle.fontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_065', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'placeholderStyle.fontColor'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#FFE9E8ED"}"}'
      })
      done();
    })
    /**
     * 测试组件placeholderStyle.fontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_066', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'placeholderStyle.fontColor'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#FF1C1C1C"}"}'
      })
      done();
    })
    /**
     * 测试组件placeholderStyle.fontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_067', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderStyle.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'placeholderStyle.fontColor'
        },
        id: 'RichEditor',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholder', JsonType.obj)
        ],
        assertEqual: '{"value":"请输入","style":"{"font":"{"size":"16.00fp","weight":"FontWeight.Normal","family":"HarmonyOS Sans","style":"FontStyle.Normal"}","fontColor":"#FFFFFFFF"}"}'
      })
      done();
    })
    //caretColor
    /*
    *测试组件caretColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_RichEditor_068', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'caretColor'
        }
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_069', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'caretColor'
        }
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_070', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'caretColor'
        }
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_071', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'caretColor'
        }
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_072', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'caretColor'
        }
      })
      done();
    })
    /**
     * 测试组件caretColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_RichEditor_073', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'caretColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'caretColor'
        },
        id: 'RichEditor'
      })
      done();
    })
    //enterKeyType
    /*
     *测试组件enterKeyType支持设置Go且获取属性正确
     * */
    it('ArkUI_RichEditor_074', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    /*
     *测试组件enterKeyType支持设置Search且获取属性正确
     * */
    it('ArkUI_RichEditor_075', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'enterKeyType')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'enterKeyType'
        }
      })
      done();
    })
    /*
     *测试组件enterKeyType支持设置Send且获取属性正确
     * */
    it('ArkUI_RichEditor_076', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_077', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_078', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_079', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_080', 0, async (done: Function) => {
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


    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_RichEditor_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0006', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0007', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0008', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0009', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0017', 0, async (done: Function) => {
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
    it('ArkUI_RichEditor_Comp_0018', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0019', 0, async (done: Function) => {
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
        id: 'RichEditor',
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
        id: 'RichEditor',
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
    it('ArkUI_RichEditor_Comp_0020', 0, async (done: Function) => {
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

  })
}