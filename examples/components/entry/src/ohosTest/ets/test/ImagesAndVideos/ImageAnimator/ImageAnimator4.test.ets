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
  JsonType, KeyStruct, radioClick, Search,
  searchParentBlock,
  Slide, sliderDrag, titleSearch, ToggleClick } from '../../../utils';
import { ImageAnimatorStart } from './ImageAnimator';


const driver = Driver.create();

export default function ImageAnimator4Test() {
  describe('ImageAnimator4Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await ImageAnimatorStart(done)

    })
    /**
     * 测试组件shadow
     */
    it('ArkUI_ImageAnimator_Comp_0244', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.radius', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0245', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    it('ArkUI_ImageAnimator_Comp_0246', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_ImageAnimator_Comp_0247', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0248', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0249', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0250', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0251', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0252', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0253', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetX', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0254', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetY', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0255', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_ImageAnimator_Comp_0256', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    /**
     * 测试组件grayscale
     */
    it('ArkUI_ImageAnimator_Comp_0257', 0, async (done: Function) => {
      await searchParentBlock('grayscale', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件brightness
     */
    it('ArkUI_ImageAnimator_Comp_0258', 0, async (done: Function) => {
      await searchParentBlock('brightness', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 2
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件saturate
     */
    it('ArkUI_ImageAnimator_Comp_0259', 0, async (done: Function) => {
      await searchParentBlock('saturate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value)
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件contrast
     */
    it('ArkUI_ImageAnimator_Comp_0260', 0, async (done: Function) => {
      await searchParentBlock('contrast', false, '基础属性', '通用属性2')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value)
        ],
        assertEqual: 10
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件invert
     */
    it('ArkUI_ImageAnimator_Comp_0261', 0, async (done: Function) => {
      await searchParentBlock('invert', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件sepia
     */
    it('ArkUI_ImageAnimator_Comp_0262', 0, async (done: Function) => {
      await searchParentBlock('sepia', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    /**
     * 测试组件hueRotate
     */
    it('ArkUI_ImageAnimator_Comp_0263', 0, async (done: Function) => {
      await searchParentBlock('hueRotate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value)
        ],
        assertEqual: 180
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value)
        ],
        assertEqual: 180
      })

      done();
    })
    /**
     * 测试组件colorBlend
     */
    it('ArkUI_ImageAnimator_Comp_0264', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0265', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0266', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0267', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0268', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0269', 0, async (done: Function) => {
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件linearGradientBlur
     */
    it('ArkUI_ImageAnimator_Comp_0270', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.value', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '60.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: '0.00px'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0271', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.100000,0.000000', '0.200000,1.000000']
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0272', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.100000,0.330000', '0.200000,0.660000', '0.300000,1.000000']
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0273', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('fractionStops', JsonType.obj),
        ],
        assertEqual: ['0.400000,0.250000', '0.300000,0.500000', '0.200000,0.750000', '0.100000,1.000000']
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0274', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0275', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0276', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0277', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'BOTTOM'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0278', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT_TOP'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0279', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT_BOTTOM'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0280', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT_TOP'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0281', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'RIGHT_BOTTOM'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0282', 0, async (done: Function) => {
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'ImageAnimator',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradientBlur', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('direction', JsonType.obj),
        ],
        assertEqual: 'LEFT'
      })

      done();

    })
    // renderGroup
    it('ArkUI_ImageAnimator_Comp_0283', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0284', 0, async (done: Function) => {
      await searchParentBlock('renderGroup', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderGroup', JsonType.obj)
        ],
        assertEqual: 'false'
      })

      done();

    })
    // blendMode
    it('ArkUI_ImageAnimator_Comp_0285', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0286', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 1
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0287', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 2
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0288', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 3
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0289', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 4
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0290', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 5
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0291', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 6
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0292', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 7
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0293', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 8,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 8
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0294', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 9,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 9
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0295', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 10,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 10
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0296', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 11,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 11
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0297', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 12,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 12
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0298', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 13,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 13
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0299', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 14,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 14
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0300', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 15,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 15
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0301', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 16,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 16
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0302', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 17,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 17
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0303', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 18,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 18
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0304', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 19,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 19
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0305', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 20,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 20
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0306', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 21,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 21
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0307', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 22,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 22
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0308', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 23,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 23
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0309', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 24,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 24
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0310', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 25,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 25
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0311', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 26,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 26
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0312', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 27,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 27
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0313', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 28,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 28
      })

      done();

    })
    it('ArkUI_ImageAnimator_Comp_0314', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 'LUMINOSITY',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 29
      }, 'blendMode.value', '基础属性', '通用属性2')
      done();


    })

    it('ArkUI_ImageAnimator_Comp_0315', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'blendMode.type', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_ImageAnimator_Comp_0316', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'blendMode.type', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_ImageAnimator_Comp_0317', 0, async (done: Function) => {
      await searchParentBlock('useShadowBatching', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useShadowBatching', JsonType.obj)
        ],
        assertEqual: 'true'
      })
      done();

    })
    it('ArkUI_ImageAnimator_Comp_0318', 0, async (done: Function) => {
      await searchParentBlock('useShadowBatching', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useShadowBatching', JsonType.obj)
        ],
        assertEqual: 'false'
      })
      done();

    })
    // sphericalEffect
    it('ArkUI_ImageAnimator_Comp_0319', 0, async (done: Function) => {
      await searchParentBlock('sphericalEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sphericalEffect', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sphericalEffect', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    //   lightUpEffect
    it('ArkUI_ImageAnimator_Comp_0320', 0, async (done: Function) => {
      await searchParentBlock('lightUpEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lightUpEffect', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lightUpEffect', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    //   pixelStretchEffect
    it('ArkUI_ImageAnimator_Comp_0321', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.left', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('left', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('left', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0322', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.right', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('right', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('right', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0323', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.top', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('top', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('top', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_ImageAnimator_Comp_0324', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.bottom', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('bottom', JsonType.obj)
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('bottom', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //   freeze
    it('ArkUI_ImageAnimator_Comp_0325', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('freeze', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })

    it('ArkUI_ImageAnimator_Comp_0326', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('freeze', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })

    // linearGradient
    // linearGradient.angle
    it('ArkUI_ImageAnimator_Comp_0327', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.angle', '通用属性3')

      await sliderDrag({
        slideStar: Slide.start,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '360.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();
    })

    // linearGradient.direction
    it('ArkUI_ImageAnimator_Comp_0328', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Left'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0329', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Top'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0330', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 2,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Right'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0331', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 3,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Bottom'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0332', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 4,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftTop'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0333', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 5,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftBottom'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0334', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 6,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightTop'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0335', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 7,
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightBottom'
      })

      done();

    })

    it('ArkUI_ImageAnimator_Comp_0336', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'ImageAnimator',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.None'
      })

      done();

    })

  })
}