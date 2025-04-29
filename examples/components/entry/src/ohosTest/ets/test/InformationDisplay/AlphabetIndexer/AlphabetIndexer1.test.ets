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
import {
  buttonClick,
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
import { AlphabetIndexerStart } from './AlphabetIndexer';

const driver = Driver.create();

export default function AlphabetIndexer1Test() {
  describe('AlphabetIndexer1Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await AlphabetIndexerStart(done)

    })
    /**
     * 测试组件popupFontSize且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0042', 0, async (done: Function) => {
      await Search('参数列表', 'popupFontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'popupFontSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: "32.00fp"
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'popupFontSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: "12.00fp"
      })


      done();
    })
    /**
     * 测试组件popupFontStyle且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0043', 0, async (done: Function) => {
      await Search('参数列表', 'popupFontStyle')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupFontStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: "FontStyle::NORMAL"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0044', 0, async (done: Function) => {
      await Search('参数列表', 'popupFontStyle')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupFontStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: "FontStyle::ITALIC"
      })

      done();
    })
    /**
     * 测试组件popupFontWeight且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0045', 0, async (done: Function) => {
      await Search('参数列表', 'popupFontWeight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Lighter"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0046', 0, async (done: Function) => {

      await Search('参数列表', 'popupFontWeight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupFontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Normal"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0047', 0, async (done: Function) => {
      await Search('参数列表', 'popupFontWeight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Regular"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0048', 0, async (done: Function) => {

      await Search('参数列表', 'popupFontWeight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupFontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Medium"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0049', 0, async (done: Function) => {
      await Search('参数列表', 'popupFontWeight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupFontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Bold"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0050', 0, async (done: Function) => {

      await Search('参数列表', 'popupFontWeight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupFontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupFont', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Bolder"
      })

      done();
    })
    /**
     * 测试组件fontSize且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0051', 0, async (done: Function) => {
      await Search('参数列表', 'fontSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: "16.00fp"
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'fontSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontSize', JsonType.value),
        ],
        assertEqual: "4.00fp"
      })


      done();
    })
    /**
     * 测试组件fontStyle且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0052', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: "FontStyle::NORMAL"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0053', 0, async (done: Function) => {
      await Search('参数列表', 'fontStyle')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontStyle', JsonType.value),
        ],
        assertEqual: "FontStyle::ITALIC"
      })

      done();
    })
    /**
     * 测试组件fontWeight且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0054', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Lighter"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0055', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Normal"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0056', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Regular"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0057', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Medium"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0058', 0, async (done: Function) => {
      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Bold"
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0059', 0, async (done: Function) => {

      await Search('参数列表', 'fontWeight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'fontWeight',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('font', JsonType.obj),
          new KeyStruct('fontWeight', JsonType.value),
        ],
        assertEqual: "FontWeight.Bolder"
      })

      done();
    })
    /**
     * 测试组件itemSize且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0060', 0, async (done: Function) => {
      await Search('参数列表', 'itemSize')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'itemSize',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemSize', JsonType.value),
        ],
        assertEqual: '32.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'itemSize',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemSize', JsonType.value),
        ],
        assertEqual: '12.00vp'
      })


      done();
    })
    /**
     * 测试组件alignStyle.value且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0061', 0, async (done: Function) => {
      await Search('参数列表', 'alignStyle.value')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'alignStyle.value',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignStyle', JsonType.value),
        ],
        assertEqual: 'IndexerAlign.Left'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0062', 0, async (done: Function) => {
      await Search('参数列表', 'alignStyle.value')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'alignStyle.value',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignStyle', JsonType.value),
        ],
        assertEqual: 'IndexerAlign.Right'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0063', 0, async (done: Function) => {
      await Search('参数列表', 'alignStyle.value')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'alignStyle.value',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignStyle', JsonType.value),
        ],
        assertEqual: 'IndexerAlign.Start'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0064', 0, async (done: Function) => {
      await Search('参数列表', 'alignStyle.value')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'alignStyle.value',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignStyle', JsonType.value),
        ],
        assertEqual: 'IndexerAlign.End'
      })

      done();
    })
    /**
     * 测试组件alignStyle.offset
     */
    it('ArkUI_AlphabetIndexer_0065', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'alignStyle.offset')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'alignStyle.offset',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'alignStyle.offset',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件selected且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0066', 0, async (done: Function) => {
      await Search('参数列表', 'selected')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'selected',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selected', JsonType.value),
        ],
        assertEqual: '27'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'selected',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('selected', JsonType.value),
        ],
        assertEqual: '0'
      })


      done();
    })
    /**
     * 测试组件popupPosition.value.y且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0067', 0, async (done: Function) => {
      await Search('参数列表', 'popupPosition.value.y')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'popupPosition.value.y',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupPosition', JsonType.obj),
          new KeyStruct('popupPositionY', JsonType.value),
        ],
        assertEqual: "72.00vp"
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'popupPosition.value.y',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupPosition', JsonType.obj),
          new KeyStruct('popupPositionY', JsonType.value),
        ],
        assertEqual: "24.00vp"
      })


      done();
    })
    /**
     * 测试组件popupSelectedColor且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0068', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0069', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0070', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0071', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0072', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0073', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件popupSelectedColor且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0074', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0075', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0076', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0077', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0078', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0079', 0, async (done: Function) => {
      await Search('参数列表', 'popupSelectedColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupSelectedColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupSelectedColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件popupItemFont.size且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0080', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.size')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'popupItemFont.size',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemFontSize', JsonType.value),
        ],
        assertEqual: '36.00fp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'popupItemFont.size',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemFontSize', JsonType.value),
        ],
        assertEqual: '12.00fp'
      })


      done();
    })
    /**
     * 测试组件popupItemFont.style
     */
    it('ArkUI_AlphabetIndexer_0081', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'popupItemFont.style')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupItemFont.style',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0082', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.style')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupItemFont.style',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件popupItemFont.weight
     */
    it('ArkUI_AlphabetIndexer_0083', 0, async (done: Function) => {
      //无法取到子组件状态
      await Search('参数列表', 'popupItemFont.weight')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupItemFont.weight',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0084', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.weight')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupItemFont.weight',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0085', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.weight')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupItemFont.weight',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0086', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.weight')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupItemFont.weight',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0087', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.weight')

      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupItemFont.weight',
          toggleClickType: ToggleClick.Open
        },
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0088', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemFont.weight')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupItemFont.weight',
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件popupItemBackgroundColor且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0089', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBackgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupItemBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBackground', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0090', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBackgroundColor')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupItemBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBackground', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0091', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBackgroundColor')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupItemBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBackground', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0092', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBackgroundColor')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupItemBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBackground', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0093', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBackgroundColor')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupItemBackgroundColor',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBackground', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0094', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBackgroundColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupItemBackgroundColor',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBackground', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件autoCollapse且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0095', 0, async (done: Function) => {
      await Search('参数列表', 'autoCollapse')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'autoCollapse',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoCollapse', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0096', 0, async (done: Function) => {
      await Search('参数列表', 'autoCollapse')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'autoCollapse',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoCollapse', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件popupItemBorderRadius且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0097', 0, async (done: Function) => {
      await Search('参数列表', 'popupItemBorderRadius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'popupItemBorderRadius',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBorderRadius', JsonType.value),
        ],
        assertEqual: '48.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'popupItemBorderRadius',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupItemBorderRadius', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })


      done();
    })
    /**
     * 测试组件itemBorderRadius且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0098', 0, async (done: Function) => {
      await Search('参数列表', 'itemBorderRadius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'itemBorderRadius',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemBorderRadius', JsonType.value),
        ],
        assertEqual: '16.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'itemBorderRadius',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemBorderRadius', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })


      done();
    })
    /**
     * 测试组件popupBackgroundBlurStyle且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0099', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.Thin'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0100', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.Regular'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0101', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.Thick'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0102', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_THIN'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0103', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_REGULAR'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0104', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_THICK'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0105', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.BACKGROUND_ULTRA_THICK'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0106', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.NONE'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0107', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_ULTRA_THIN'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0108', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_THIN'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0109', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_REGULAR'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0120', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_THICK'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0121', 0, async (done: Function) => {
      await Search('参数列表', 'popupBackgroundBlurStyle')

      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickObj: 'popupBackgroundBlurStyle',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupBackgroundBlurStyle', JsonType.value),
        ],
        assertEqual: 'BlurStyle.COMPONENT_ULTRA_THICK'
      })

      done();
    })
    /**
     * 测试组件popupTitleBackground且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0122', 0, async (done: Function) => {
      await Search('参数列表', 'popupTitleBackground')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickObj: 'popupTitleBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupTitleBackground', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0123', 0, async (done: Function) => {
      await Search('参数列表', 'popupTitleBackground')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'popupTitleBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupTitleBackground', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0124', 0, async (done: Function) => {
      await Search('参数列表', 'popupTitleBackground')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'popupTitleBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupTitleBackground', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0125', 0, async (done: Function) => {
      await Search('参数列表', 'popupTitleBackground')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'popupTitleBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupTitleBackground', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0126', 0, async (done: Function) => {
      await Search('参数列表', 'popupTitleBackground')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'popupTitleBackground',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupTitleBackground', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_0127', 0, async (done: Function) => {
      await Search('参数列表', 'popupTitleBackground')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj: 'popupTitleBackground',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('popupTitleBackground', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();


    })
    /**
     * 测试组件enableHapticFeedback且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_0128', 0, async (done: Function) => {
      await Search('参数列表', 'enableHapticFeedback')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'enableHapticFeedback',
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableHapticFeedback', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();
    })

    it('ArkUI_AlphabetIndexer_0129', 0, async (done: Function) => {
      await Search('参数列表', 'enableHapticFeedback')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'enableHapticFeedback',
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableHapticFeedback', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();
    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_AlphabetIndexer_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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