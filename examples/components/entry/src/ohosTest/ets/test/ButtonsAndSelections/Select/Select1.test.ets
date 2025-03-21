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

import { beforeAll, describe, it, } from '@ohos/hypium';
import { Driver, ON } from '@kit.TestKit';
import { Component } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { SelectStart } from './Select.test';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function Select1Test() {
  describe('Select1Test', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await SelectStart(done);
    })
    // optionBgColor
    /*
    *测试组件optionBgColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_051', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionBgColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionBgColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件optionBgColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_052', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionBgColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionBgColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件optionBgColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_053', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionBgColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionBgColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件optionBgColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_054', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionBgColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionBgColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件optionBgColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_055', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionBgColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionBgColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件optionBgColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_056', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionBgColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionBgColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //optionFont.Font.size
    it('ArkUI_Select_057', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.size')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"100.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"0.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done()
    })
    //optionFont.Font.weight
    /*
     * 测试组件optionFont.Font.weight支持设置Lighter且获取属性正确
     */
    it('ArkUI_Select_058', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.weight')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Lighter","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件optionFont.Font.weight支持设置Normal且获取属性正确
     */
    it('ArkUI_Select_059', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.weight')
      await radioClick({
        radioClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Normal","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件optionFont.Font.weight支持设置Regular且获取属性正确
     */
    it('ArkUI_Select_060', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.weight')
      await radioClick({
        radioClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件optionFont.Font.weight支持设置Medium且获取属性正确
     */
    it('ArkUI_Select_061', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.weight')
      await radioClick({
        radioClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Medium","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件optionFont.Font.weight支持设置Bold且获取属性正确
     */
    it('ArkUI_Select_062', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.weight')
      await radioClick({
        radioClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Bold","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件optionFont.Font.weight支持设置Bolder且获取属性正确
     */
    it('ArkUI_Select_063', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Bolder","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    //optionFont.Font.family  没有属性值，无法断言
    it('ArkUI_Select_064', 0, async (done: Function) => {
      await Search('参数列表', 'optionFont.Font.weight')
      await getToggle(ToggleClick.Close)
      done();
    })
    //optionFont.Font.style
    /*
     * 测试组件optionFont.Font.style支持设置Normal且获取属性正确
     */
    it('ArkUI_Select_065', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.style')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Normal"}'
      })
      done();
    })
    /*
     * 测试组件optionFont.Font.style支持设置Italic且获取属性正确
     */
    it('ArkUI_Select_066', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFont.Font.style')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFont', JsonType.obj)
        ],
        assertEqual: '{"size":"16.00fp","weight":"FontWeight.Regular","family":"","style":"FontStyle.Italic"}'
      })
      done();
    })
    //optionFontColor
    /*
    *测试组件optionFontColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_067', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFontColor')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFontColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件optionFontColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_068', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFontColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFontColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件optionFontColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_069', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFontColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFontColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件optionFontColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_070', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFontColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFontColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件optionFontColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_071', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFontColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFontColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件optionFontColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_072', 0, async (done: Function) => {
      await searchParentBlock('selected', true, '参数列表')
      await Search('参数列表', 'optionFontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionFontColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      await searchParentBlock('selected', false, '参数列表')
      done();
    })
    //space
    it('ArkUI_Select_073', 0, async (done: Function) => {
      await Search('参数列表', 'space')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '8.00vp'
      })
      done()
    })
    //arrowPosition
    /*
     * 测试组件arrowPosition支持设置END且获取属性正确
     */
    it('ArkUI_Select_074', 0, async (done: Function) => {
      await Search('参数列表', 'arrowPosition')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowPosition', JsonType.value)
        ],
        assertEqual: 'ArrowPosition.END'
      })
      done();
    })
    /*
     * 测试组件arrowPosition支持设置START且获取属性正确
     */
    it('ArkUI_Select_075', 0, async (done: Function) => {
      await Search('参数列表', 'arrowPosition')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowPosition', JsonType.value)
        ],
        assertEqual: 'ArrowPosition.START'
      })
      done();
    })
    //menuAlign.MenuAlignType
    /*
     * 测试组件menuAlign.MenuAlignType支持设置START且获取属性正确
     */
    it('ArkUI_Select_076', 0, async (done: Function) => {
      await Search('参数列表', 'menuAlign.MenuAlignType')
      await radioClick({
        radioClickObj: 0,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('alignType', JsonType.value)
        ],
        assertEqual: 'MenuAlignType.Start'
      })
      done();
    })
    /*
     * 测试组件menuAlign.MenuAlignType支持设置CENTER且获取属性正确
     */
    it('ArkUI_Select_077', 0, async (done: Function) => {
      await Search('参数列表', 'menuAlign.MenuAlignType')
      await radioClick({
        radioClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('alignType', JsonType.value)
        ],
        assertEqual: 'MenuAlignType.Center'
      })
      done();
    })
    /*
     * 测试组件menuAlign.MenuAlignType支持设置END且获取属性正确
     */
    it('ArkUI_Select_078', 0, async (done: Function) => {
      await Search('参数列表', 'menuAlign.MenuAlignType')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('alignType', JsonType.value)
        ],
        assertEqual: 'MenuAlignType.End'
      })
      done();
    })
    //menuAlign.offset.dx
    it('ArkUI_Select_079', 0, async (done: Function) => {
      await searchParentBlock('menuAlign.MenuAlignType', true, '参数列表')
      await Search('参数列表', 'menuAlign.offset.dx')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dX', JsonType.value),
        ],
        assertEqual: 100
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dX', JsonType.value),
        ],
        assertEqual: 0
      })
      done()
    })
    //menuAlign.offset.dy
    it('ArkUI_Select_080', 0, async (done: Function) => {
      await searchParentBlock('menuAlign.MenuAlignType', true, '参数列表')
      await Search('参数列表', 'menuAlign.offset.dy')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dY', JsonType.value),
        ],
        assertEqual: 100
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuAlign', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('dY', JsonType.value),
        ],
        assertEqual: 0
      })
      await searchParentBlock('menuAlign.MenuAlignType', false, '参数列表')
      done()
    })
    // optionWidth
    /*
     * 测试组件optionWidth支持设置FIT_CONTENT且获取属性正确
     */
    it('ArkUI_Select_081', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'optionWidth')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件optionWidth支持设置FIT_TRIGGER且获取属性正确
     */
    it('ArkUI_Select_082', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'optionWidth')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //optionHeight  Slider滑到100时，取到的值为150，最小值取到1.5
    it('ArkUI_Select_083', 0, async (done: Function) => {
      await Search('参数列表', 'optionHeight')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionHeight', JsonType.value),
        ],
        assertEqual: '150.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('optionHeight', JsonType.value)
        ],
        assertEqual: '1.500000'
      })
      done()
    })
    //menuBackgroundColor
    /*
    *测试组件menuBackgroundColor支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_Select_084', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'menuBackgroundColor'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundColor', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件menuBackgroundColor支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_Select_085', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'menuBackgroundColor'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件menuBackgroundColor支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_Select_086', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'menuBackgroundColor'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件menuBackgroundColor支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_Select_087', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'menuBackgroundColor'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件menuBackgroundColor支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_Select_088', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'menuBackgroundColor'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件menuBackgroundColor支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Select_089', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'menuBackgroundColor'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //menuBackgroundBlurStyle
    /*
     * 测试组件menuBackgroundBlurStyle支持设置Thin且获取属性正确
     */
    it('ArkUI_Select_090', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.Thin'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置Regular且获取属性正确
     */
    it('ArkUI_Select_091', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.Regular'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置Thick且获取属性正确
     */
    it('ArkUI_Select_092', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.Thick'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置BACKGROUND_THIN且获取属性正确
     */
    it('ArkUI_Select_093', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.BACKGROUND_THIN'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置BACKGROUND_REGULAR且获取属性正确
     */
    it('ArkUI_Select_094', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.BACKGROUND_REGULAR'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置BACKGROUND_THICK且获取属性正确
     */
    it('ArkUI_Select_095', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.BACKGROUND_THICK'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置BACKGROUND_ULTRA_THICK且获取属性正确
     */
    it('ArkUI_Select_096', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.BACKGROUND_ULTRA_THICK'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置COMPONENT_ULTRA_THIN且获取属性正确
     */
    it('ArkUI_Select_097', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.COMPONENT_ULTRA_THIN'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置COMPONENT_THICK且获取属性正确
     */
    it('ArkUI_Select_098', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.COMPONENT_THIN'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置COMPONENT_REGULAR且获取属性正确
     */
    it('ArkUI_Select_099', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.COMPONENT_REGULAR'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置COMPONENT_THICK且获取属性正确
     */
    it('ArkUI_Select_100', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.COMPONENT_THICK'
      })
      done();
    })
    /*
     * 测试组件menuBackgroundBlurStyle支持设置COMPONENT_ULTRA_THICK且获取属性正确
     */
    it('ArkUI_Select_101', 0, async (done: Function) => {
      await Search('参数列表', 'menuBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'menuBackgroundBlurStyle'
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('menuBackgroundBlurStyle', JsonType.obj)
        ],
        assertEqual: 'BlurStyle.COMPONENT_ULTRA_THICK'
      })
      done();
    })


    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Select_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0006', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0007', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0008', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0009', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0017', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0018', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0019', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0020', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0021', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0022', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0023', 0, async (done: Function) => {
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
        id: 'Select',
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0024', 0, async (done: Function) => {
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
    it('ArkUI_Select_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_Select_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_Select_Comp_0027', 0, async (done: Function) => {
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
        id: 'Select',
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
    it('ArkUI_Select_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Select',
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
        id: 'Select',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
  })
}