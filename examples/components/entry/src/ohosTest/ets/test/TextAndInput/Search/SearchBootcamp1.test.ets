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
import { searchBeforeAll } from './Search.test';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function SearchBootcampTest1() {
  describe('SearchBootcampTest1', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      searchBeforeAll(done, delegator, driver);
    })
    //searchButton.option.fontColor
    /*
    *测试组件searchButton.option.fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_001', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件searchButton.option.fontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Search_002', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件searchButton.option.fontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Search_003', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件searchButton.option.fontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Search_004', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件searchButton.option.fontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Search_005', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件searchButton.option.fontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Search_006', 0, async (done: Function) => {
      await Search('参数列表', 'searchButton.option.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchButtonOption', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //placeholderColor
    /*
    *测试组件placeholderColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_007', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
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
    it('ArkUI_Search_008', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
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
    it('ArkUI_Search_009', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
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
    it('ArkUI_Search_010', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
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
    it('ArkUI_Search_011', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
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
    it('ArkUI_Search_012', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //placeholderFont.size
    it('ArkUI_Search_013', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
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
        id: 'Search',
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
    it('ArkUI_Search_014', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"100","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置200且获取属性正确
     */
    it('ArkUI_Search_015', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"200","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置300且获取属性正确

     */
    it('ArkUI_Search_016', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"300","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置400且获取属性正确

     */
    it('ArkUI_Search_017', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"400","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置500且获取属性正确

     */
    it('ArkUI_Search_018', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"500","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置600且获取属性正确

     */
    it('ArkUI_Search_019', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 5,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"600","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置700且获取属性正确
     */
    it('ArkUI_Search_020', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 6,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"700","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置800且获取属性正确
     */
    it('ArkUI_Search_021', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 7,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"800","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置900且获取属性正确
     */
    it('ArkUI_Search_022', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 8,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","weight":"900","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Lighter且获取属性正确
     */
    it('ArkUI_Search_023', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 9,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Lighter","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Normal且获取属性正确
     */
    it('ArkUI_Search_024', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 10,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_Search_025', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 11,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Regular","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_Search_026', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 12,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Medium","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_Search_027', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 13,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Bold","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_Search_028', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.weight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Bolder","fontFamily":"sans-serif"}'
      })
      done();
    })
    //placeholderFont.style
    /*
     * 测试组件placeholderFont.style支持设置Normal且获取属性正确
     */
    it('ArkUI_Search_029', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Normal","size":"16.00fp","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.style支持设置Italic且获取属性正确
     */
    it('ArkUI_Search_030', 0, async (done: Function) => {
      await Search('参数列表', 'placeholderFont.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('placeholderFont', JsonType.obj)
        ],
        assertEqual: '{"style":"FontStyle.Italic","size":"16.00fp","fontWeight":"FontWeight.Normal","fontFamily":"sans-serif"}'
      })
      done();
    })
    //textFont.size
    it('ArkUI_Search_031', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"200.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Normal","fontFamily":"HarmonyOS Sans"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"0.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Normal","fontFamily":"HarmonyOS Sans"}'
      })
      done()
    })
    //textFont.weight
    /*
     * 测试组件placeholderFont.weight支持设置100且获取属性正确
     */
    it('ArkUI_Search_032', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"100","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置200且获取属性正确
     */
    it('ArkUI_Search_033', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"200","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置300且获取属性正确

     */
    it('ArkUI_Search_034', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"300","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置400且获取属性正确

     */
    it('ArkUI_Search_035', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"400","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置500且获取属性正确

     */
    it('ArkUI_Search_036', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"500","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置600且获取属性正确

     */
    it('ArkUI_Search_037', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 5,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"600","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置700且获取属性正确
     */
    it('ArkUI_Search_038', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 6,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"700","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置800且获取属性正确
     */
    it('ArkUI_Search_039', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 7,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"800","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置900且获取属性正确
     */
    it('ArkUI_Search_040', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 8,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"900","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Lighter且获取属性正确
     */
    it('ArkUI_Search_041', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 9,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Lighter","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Normal且获取属性正确
     */
    it('ArkUI_Search_042', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 10,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Normal","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_Search_043', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 11,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Regular","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_Search_044', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 12,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Medium","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_Search_045', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 13,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Bold","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_Search_046', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.weight')
      await radioClick({
        radioClickObj: 14,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Bolder","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    //textFont.style
    /*
     * 测试组件placeholderFont.style支持设置Normal且获取属性正确
     */
    it('ArkUI_Search_047', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Normal","fontWeight":"FontWeight.Normal","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    /*
     * 测试组件placeholderFont.style支持设置Italic且获取属性正确
     */
    it('ArkUI_Search_048', 0, async (done: Function) => {
      await Search('参数列表', 'textFont.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textFont', JsonType.obj)
        ],
        assertEqual: '{"fontSize":"16.00fp","fontStyle":"FontStyle.Italic","fontWeight":"FontWeight.Normal","fontFamily":"HarmonyOS Sans"}'
      })
      done();
    })
    //textAlign
    /*
     * 测试组件textAlign支持设置Start且获取属性正确
     */
    it('ArkUI_Search_049', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Start'
      })
      done();
    })
    /**
     * 测试组件textAlign支持设置Center且获取属性正确*/
    it('ArkUI_Search_050', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.Center'
      })
      done();
    })
    /**
     * 测试组件textAlign支持设置End且获取属性正确*/
    it('ArkUI_Search_051', 0, async (done: Function) => {
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textAlign', JsonType.value)
        ],
        assertEqual: 'TextAlign.End'
      })
      done();
    })
    /**
     * 测试组件textAlign支持设置JUSTIFY且获取属性正确*/
    it('ArkUI_Search_052', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textAlign')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //copyOptions
    /*
     *测试组件copyOption支持设置None且获取属性正确
     * */
    it('ArkUI_Search_053', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
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
    it('ArkUI_Search_054', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
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
    it('ArkUI_Search_055', 0, async (done: Function) => {
      await Search('参数列表', 'copyOptions')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('copyOption', JsonType.value)
        ],
        assertEqual: 'CopyOptions.Local'
      })
      done();
    })
    //searchIcon.size
    it('ArkUI_Search_056', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '48.00px'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done()
    })
    //searchIcon.color
    /*
    *测试组件searchIcon.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_057', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件searchIcon.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Search_058', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件searchIcon.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Search_059', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件searchIcon.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Search_060', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件searchIcon.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Search_061', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件searchIcon.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Search_062', 0, async (done: Function) => {
      await Search('参数列表', 'searchIcon.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('searchIcon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //cancelButton.style
    /*
     *测试组件cancelButton支持设置CONSTANT且获取属性正确
     * */
    it('ArkUI_Search_063', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'CancelButtonStyle.CONSTANT'
      })
      done();
    })
    /*
     * 测试组件cancelButton支持设置INVISIBLE且获取属性正确
     * */
    it('ArkUI_Search_064', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.style')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'CancelButtonStyle.INVISIBLE'
      })
      done();
    })
    /*
     * 测试组件cancelButton支持设置INPUT且获取属性正确
     * */
    it('ArkUI_Search_065', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.style')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('style', JsonType.value)
        ],
        assertEqual: 'CancelButtonStyle.INPUT'
      })
      done();
    })
    //cancelButton.icon.size
    it('ArkUI_Search_066', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '48.00px'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('size', JsonType.value)
        ],
        assertEqual: '0.00px'
      })
      done()
    })
    //cancelButton.icon.color
    /*
    *测试组件cancelButton.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_067', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件cancelButton.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Search_068', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件cancelButton.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Search_069', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件cancelButton.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Search_070', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件cancelButton.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Search_071', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件cancelButton.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Search_072', 0, async (done: Function) => {
      await Search('参数列表', 'cancelButton.icon.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cancelButton', JsonType.obj),
          new KeyStruct('icon', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //fontColor
    /*
    *测试组件fontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_073', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
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
    it('ArkUI_Search_074', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
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
    it('ArkUI_Search_075', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
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
    it('ArkUI_Search_076', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
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
    it('ArkUI_Search_077', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
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
    it('ArkUI_Search_078', 0, async (done: Function) => {
      await Search('参数列表', 'fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //caretStyle.width
    it('ArkUI_Search_079', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.width')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('width', JsonType.value)
        ],
        assertEqual: '200.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('width', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    //caretStyle.color
    /*
    *测试组件caretStyle.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Search_080', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Search_081', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Search_082', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Search_083', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Search_084', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件caretStyle.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Search_085', 0, async (done: Function) => {
      await Search('参数列表', 'caretStyle.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('caretStyle', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //enableKeyboardOnFocus
    /*
     * 测试组件enableKeyboardOnFocus支持设置false且获取属性正确
     */
    it('ArkUI_Search_086', 0, async (done: Function) => {
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
    it('ArkUI_Search_087', 0, async (done: Function) => {
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
    it('ArkUI_Search_088', 0, async (done: Function) => {
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
    it('ArkUI_Search_089', 0, async (done: Function) => {
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
    //customKeyboard.option
    /*
     * 测试组件customKeyboard.option支持设置false且获取属性正确
     */
    it('ArkUI_Search_090', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'customKeyboard.option')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件customKeyboard.options支持设置true且获取属性正确
     */
    it('ArkUI_Search_091', 0, async (done: Function) => {
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
    //type
    /*
     *测试组件type支持设置NORMAL且获取属性正确
     * */
    it('ArkUI_Search_092', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 0,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SearchType.NORMAL'
      })
      done();
    })
    /*
     *测试组件type支持设置NUMBER且获取属性正确
     * */
    it('ArkUI_Search_093', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 1,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SearchType.NUMBER'
      })
      done();
    })
    /*
     *测试组件type支持设置PHONE_NUMBER且获取属性正确
     * */
    it('ArkUI_Search_094', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 2,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SearchType.PHONE_NUMBER'
      })
      done();
    })
    /*
     * 测试组件type支持设置EMAIL且获取属性正确
     * */
    it('ArkUI_Search_095', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 3,
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SearchType.EMAIL'
      })
      done();
    })
    /*
     * 测试组件type支持设置NUMBER_DECIMAL且获取属性正确
     * */
    it('ArkUI_Search_096', 0, async (done: Function) => {
      //无法获取参数进行断言
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件type支持设置URL且获取属性正确
     * */
    it('ArkUI_Search_097', 0, async (done: Function) => {
      await Search('参数列表', 'type')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SearchType.URL'
      })
      done();
    })
    //maxLength
    it('ArkUI_Search_098', 0, async (done: Function) => {
      await Search('参数列表', 'maxLength')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Search',
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
        id: 'Search',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxLength', JsonType.value)
        ],
        assertEqual: '0'
      })
      done()
    })
    //enterKeyType
    /*
     *测试组件enterKeyType支持设置Go且获取属性正确
     * */
    it('ArkUI_Search_099', 0, async (done: Function) => {
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
    it('ArkUI_Search_100', 0, async (done: Function) => {
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

  })
}