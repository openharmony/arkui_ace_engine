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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { SwiperStart } from './Swiper'
import { Driver } from '@kit.TestKit';
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

const driver = Driver.create();

export default function Swiper1Test() {
  describe('Swiper1Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await SwiperStart(done)

    })
    /**
     * 测试组件DigitIndicator.digitFont.weight且获取属性正确
     */
    it('ArkUI_Swiper_0033', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.digitFont.weight')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Lighter","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0034', 0, async (done: Function) => {

      await Search('参数列表', 'DigitIndicator.digitFont.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0035', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.digitFont.weight')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Regular","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0036', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.digitFont.weight')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Medium","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0037', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.digitFont.weight')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Bold","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0038', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.digitFont.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.digitFont.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Bolder","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })
    /**
     * 测试组件DigitIndicator.selectedDigitFont.size且获取属性正确
     */
    it('ArkUI_Swiper_0039', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.size',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"30.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.size',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"10.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })
    /**
     * 测试组件DigitIndicator.selectedDigitFont.weight且获取属性正确
     */
    it('ArkUI_Swiper_0040', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.weight')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),

        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Lighter"}'
      })

      done();
    })

    it('ArkUI_Swiper_0041', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.weight')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Normal"}'
      })

      done();
    })

    it('ArkUI_Swiper_0042', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.weight')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Regular"}'
      })

      done();
    })

    it('ArkUI_Swiper_0043', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.weight')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Medium"}'
      })

      done();
    })

    it('ArkUI_Swiper_0044', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.weight')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.weight',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Bold"}'
      })

      done();
    })

    it('ArkUI_Swiper_0045', 0, async (done: Function) => {
      await Search('参数列表', 'DigitIndicator.selectedDigitFont.weight')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'DigitIndicator.selectedDigitFont.weight',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('indicator', JsonType.obj),
        ],
        assertEqual: '{"left":"0.00vp","top":"200.00vp","right":"0.00vp","bottom":"0.00vp","fontSize":"14.00fp","fontColor":"#FF182431","fontWeight":"FontWeight.Normal","selectedFontSize":"14.00fp","selectedFontColor":"#FF182431","selectedFontWeight":"FontWeight.Bolder"}'
      })

      done();
    })
    /**
     * 测试组件index且获取属性正确
     */
    it('ArkUI_Swiper_0046', 0, async (done: Function) => {

      await Search('参数列表', 'index')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'index',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('index', JsonType.value),
        ],
        assertEqual: '0'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'index',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('index', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();
    })
    /**
     * 测试组件autoPlay且获取属性正确
     */
    it('ArkUI_Swiper_0047', 0, async (done: Function) => {

      await Search('参数列表', 'autoPlay')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'autoPlay',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoPlay', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0048', 0, async (done: Function) => {

      await Search('参数列表', 'autoPlay')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'autoPlay',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoPlay', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件interval且获取属性正确
     */
    it('ArkUI_Swiper_0049', 0, async (done: Function) => {

      await Search('参数列表', 'interval')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'interval',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('interval', JsonType.value),
        ],
        assertEqual: '8000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'interval',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('interval', JsonType.value),
        ],
        assertEqual: '1000'
      })

      done();
    })
    /**
     * 测试组件loop且获取属性正确
     */
    it('ArkUI_Swiper_0050', 0, async (done: Function) => {

      await Search('参数列表', 'loop')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'loop',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('loop', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0051', 0, async (done: Function) => {

      await Search('参数列表', 'loop')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'loop',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('loop', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件duration且获取属性正确
     */
    it('ArkUI_Swiper_0052', 0, async (done: Function) => {

      await Search('参数列表', 'duration')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'duration',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('duration', JsonType.value),
        ],
        assertEqual: '2000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'duration',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('duration', JsonType.value),
        ],
        assertEqual: '100'
      })

      done();
    })
    /**
     * 测试组件vertical且获取属性正确
     */
    it('ArkUI_Swiper_0053', 0, async (done: Function) => {

      await Search('参数列表', 'vertical')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'vertical',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('vertical', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0054', 0, async (done: Function) => {

      await Search('参数列表', 'vertical')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'vertical',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('vertical', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件itemSpace且获取属性正确
     */
    it('ArkUI_Swiper_0055', 0, async (done: Function) => {

      await Search('参数列表', 'itemSpace')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'itemSpace',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemSpace', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'itemSpace',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemSpace', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件displayMode且获取属性正确
     */
    it('ArkUI_Swiper_0056', 0, async (done: Function) => {

      await Search('参数列表', 'displayMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('displayMode', JsonType.value),
        ],
        assertEqual: 'SwiperDisplayMode.Stretch'
      })

      done();
    })

    it('ArkUI_Swiper_0057', 0, async (done: Function) => {

      await Search('参数列表', 'displayMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayMode',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('displayMode', JsonType.value),
        ],
        assertEqual: 'SwiperDisplayMode.AutoLinear'
      })

      done();
    })
    /**
     * 测试组件cachedCount且获取属性正确
     */
    it('ArkUI_Swiper_0058', 0, async (done: Function) => {

      await Search('参数列表', 'cachedCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'cachedCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: 20
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'cachedCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件disableSwipe且获取属性正确
     */
    it('ArkUI_Swiper_0059', 0, async (done: Function) => {

      await Search('参数列表', 'disableSwipe')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'disableSwipe',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disableSwipe', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0060', 0, async (done: Function) => {

      await Search('参数列表', 'disableSwipe')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'disableSwipe',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('disableSwipe', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件curve且获取属性正确
     */
    it('ArkUI_Swiper_0061', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.Linear'
      })

      done();
    })

    it('ArkUI_Swiper_0062', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.Ease'
      })

      done();
    })

    it('ArkUI_Swiper_0063', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.EaseIn'
      })

      done();
    })

    it('ArkUI_Swiper_0064', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.EaseOut'
      })

      done();
    })

    it('ArkUI_Swiper_0065', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.EaseInOut'
      })

      done();
    })

    it('ArkUI_Swiper_0066', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.FastOutSlowIn'
      })

      done();
    })

    it('ArkUI_Swiper_0067', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.LinearOutSlowIn'
      })

      done();
    })

    it('ArkUI_Swiper_0068', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.FastOutLinearIn'
      })

      done();
    })

    it('ArkUI_Swiper_0069', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.ExtremeDeceleration'
      })

      done();
    })

    it('ArkUI_Swiper_0070', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.Sharp'
      })

      done();
    })

    it('ArkUI_Swiper_0071', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.Ease'
      })

      done();
    })

    it('ArkUI_Swiper_0072', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.Smooth'
      })

      done();
    })

    it('ArkUI_Swiper_0073', 0, async (done: Function) => {

      await Search('参数列表', 'curve')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickObj: 'curve',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('curve', JsonType.value),
        ],
        assertEqual: 'Curves.Friction'
      })

      done();
    })
    /**
     * 测试组件displayCount且获取属性正确
     */
    it('ArkUI_Swiper_0074', 0, async (done: Function) => {

      await Search('参数列表', 'displayCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'displayCount',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('displayCount', JsonType.value),
        ],
        assertEqual: 12
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'displayCount',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('displayCount', JsonType.value),
        ],
        assertEqual: 1
      })

      done();
    })
    /**
     * 测试组件displayCount.swipeByGroup且获取属性正确
     */
    it('ArkUI_Swiper_0075', 0, async (done: Function) => {

      await Search('参数列表', 'displayCount.swipeByGroup')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayCount.swipeByGroup',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('swipeByGroup', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0076', 0, async (done: Function) => {

      await Search('参数列表', 'displayCount.swipeByGroup')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayCount.swipeByGroup',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('swipeByGroup', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件effectMode且获取属性正确
     */
    it('ArkUI_Swiper_0077', 0, async (done: Function) => {

      await Search('参数列表', 'effectMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'effectMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectMode', JsonType.value),
        ],
        assertEqual: 'EdgeEffect.Spring'
      })

      done();
    })

    it('ArkUI_Swiper_0078', 0, async (done: Function) => {

      await Search('参数列表', 'effectMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'effectMode',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectMode', JsonType.value),
        ],
        assertEqual: 'EdgeEffect.Fade'
      })

      done();
    })

    it('ArkUI_Swiper_0079', 0, async (done: Function) => {

      await Search('参数列表', 'effectMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'effectMode',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('effectMode', JsonType.value),
        ],
        assertEqual: 'EdgeEffect.None'
      })

      done();
    })
    /**
     * 测试组件displayArrow.showBackground且获取属性正确
     */
    it('ArkUI_Swiper_0080', 0, async (done: Function) => {
      await Search('参数列表', 'displayArrow.showBackground')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayArrow.showBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showBackground', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0081', 0, async (done: Function) => {
      await Search('参数列表', 'displayArrow.showBackground')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayArrow.showBackground',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showBackground', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件displayArrow.isSidebarMiddle且获取属性正确
     */
    it('ArkUI_Swiper_0082', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.isSidebarMiddle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayArrow.isSidebarMiddle',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('isSidebarMiddle', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0083', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.isSidebarMiddle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayArrow.isSidebarMiddle',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('isSidebarMiddle', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件displayArrow.backgroundSize
     */
    it('ArkUI_Swiper_0084', 0, async (done: Function) => {
      //无法取到子组件状态

      await Search('参数列表', 'displayArrow.backgroundSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundSize',
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundSize',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件displayArrow.backgroundColor且获取属性正确
     */
    it('ArkUI_Swiper_0085', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.backgroundColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Swiper_0086', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Swiper_0087', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Swiper_0088', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Swiper_0089', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Swiper_0090', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'displayArrow.backgroundColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件displayArrow.arrowSize且获取属性正确
     */
    it('ArkUI_Swiper_0091', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowSize', JsonType.value),
        ],
        assertEqual: '60.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowSize', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })

      done();
    })
    /**
     * 测试组件displayArrow.arrowColor且获取属性正确
     */
    it('ArkUI_Swiper_0092', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Swiper_0093', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Swiper_0094', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_Swiper_0095', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Swiper_0096', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Swiper_0097', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.arrowColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'displayArrow.arrowColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('arrowColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    /**
     * 测试组件displayArrow.isHoverShow
     */
    it('ArkUI_Swiper_0098', 0, async (done: Function) => {
      //无法取到子组件状态

      await Search('参数列表', 'displayArrow.isHoverShow')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'displayArrow.isHoverShow',
          toggleClickType: ToggleClick.Open,
        },
        id: 'Swiper'
      })

      done();
    })

    it('ArkUI_Swiper_0099', 0, async (done: Function) => {

      await Search('参数列表', 'displayArrow.isHoverShow')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'displayArrow.isHoverShow',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件nextMargin且获取属性正确
     */
    it('ArkUI_Swiper_0100', 0, async (done: Function) => {

      await Search('参数列表', 'nextMargin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'nextMargin',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nextMargin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'nextMargin',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nextMargin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件nextMargin.ignoreBlank且获取属性正确
     */
    it('ArkUI_Swiper_0101', 0, async (done: Function) => {

      await Search('参数列表', 'nextMargin.ignoreBlank')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'nextMargin.ignoreBlank',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nextMarginIgnoreBlank', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0102', 0, async (done: Function) => {

      await Search('参数列表', 'nextMargin.ignoreBlank')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'nextMargin.ignoreBlank',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nextMarginIgnoreBlank', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件prevMargin且获取属性正确
     */
    it('ArkUI_Swiper_0103', 0, async (done: Function) => {
      await Search('参数列表', 'prevMargin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'prevMargin',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('prevMargin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'prevMargin',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('prevMargin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件prevMarginIgnoreBlank且获取属性正确
     */
    it('ArkUI_Swiper_0104', 0, async (done: Function) => {
      await Search('参数列表', 'prevMarginIgnoreBlank')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'prevMarginIgnoreBlank',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('prevMarginIgnoreBlank', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_Swiper_0105', 0, async (done: Function) => {
      await Search('参数列表', 'prevMarginIgnoreBlank')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'prevMarginIgnoreBlank',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('prevMarginIgnoreBlank', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件nestedScroll且获取属性正确
     */
    it('ArkUI_Swiper_0106', 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'nestedScroll',
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.value),
        ],
        assertEqual: 'SwiperNestedScrollMode.SELF_ONLY'
      })

      done();
    })

    it('ArkUI_Swiper_0107', 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'nestedScroll',
          toggleClickType: ToggleClick.Close
        },
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.value),
        ],
        assertEqual: 'SwiperNestedScrollMode.SELF_FIRST'
      })

      done();
    })
    /**
     * 测试组件indicatorInteractive
     */
    it('ArkUI_Swiper_0108', 0, async (done: Function) => {
      //无法获取子组件状态
      await Search('参数列表', 'indicatorInteractive')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'indicatorInteractive',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_Swiper_0109', 0, async (done: Function) => {
      await Search('参数列表', 'indicatorInteractive')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'indicatorInteractive',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Swiper_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Swiper',
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
        id: 'Swiper',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })

  })
}
