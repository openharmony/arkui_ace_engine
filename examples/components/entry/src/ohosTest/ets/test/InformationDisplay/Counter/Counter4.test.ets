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
import { Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  searchParentBlock,
  titleSearch
} from '../../../utils';
import { CounterStart } from './Counter';


const driver = Driver.create();

export default function Counter4() {
  describe('Counter4', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await CounterStart(done)


    })

    it('ArkUI_Counter_Comp_0298', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 13,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 13
      })

      done();

    })
    it('ArkUI_Counter_Comp_0299', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 14,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 14
      })

      done();

    })
    it('ArkUI_Counter_Comp_0300', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 15,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 15
      })

      done();

    })
    it('ArkUI_Counter_Comp_0301', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 16,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 16
      })

      done();

    })
    it('ArkUI_Counter_Comp_0302', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 17,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 17
      })

      done();

    })
    it('ArkUI_Counter_Comp_0303', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 18,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 18
      })

      done();

    })
    it('ArkUI_Counter_Comp_0304', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 19,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 19
      })

      done();

    })
    it('ArkUI_Counter_Comp_0305', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 20,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 20
      })

      done();

    })
    it('ArkUI_Counter_Comp_0306', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 21,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 21
      })

      done();

    })
    it('ArkUI_Counter_Comp_0307', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 22,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 22
      })

      done();

    })
    it('ArkUI_Counter_Comp_0308', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 23,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 23
      })

      done();

    })
    it('ArkUI_Counter_Comp_0309', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 24,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 24
      })

      done();

    })
    it('ArkUI_Counter_Comp_0310', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 25,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 25
      })

      done();

    })
    it('ArkUI_Counter_Comp_0311', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 26,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 26
      })

      done();

    })
    it('ArkUI_Counter_Comp_0312', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 27,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 27
      })

      done();

    })
    it('ArkUI_Counter_Comp_0313', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 28,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 28
      })

      done();

    })
    it('ArkUI_Counter_Comp_0314', 0, async (done: Function) => {
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 'LUMINOSITY',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blendMode', JsonType.obj)
        ],
        assertEqual: 29
      }, 'blendMode.value', '基础属性', '通用属性2')
      done();


    })

    it('ArkUI_Counter_Comp_0315', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性','blendMode.type','通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_Counter_Comp_0316', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性','blendMode.type','通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Counter_Comp_0317', 0, async (done: Function) => {
      await searchParentBlock('useShadowBatching', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useShadowBatching', JsonType.obj)
        ],
        assertEqual: 'true'
      })
      done();

    })
    it('ArkUI_Counter_Comp_0318', 0, async (done: Function) => {
      await searchParentBlock('useShadowBatching', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('useShadowBatching', JsonType.obj)
        ],
        assertEqual: 'false'
      })
      done();

    })
    // sphericalEffect
    it('ArkUI_Counter_Comp_0319', 0, async (done: Function) => {
      await searchParentBlock('sphericalEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
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
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sphericalEffect', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    //   lightUpEffect
    it('ArkUI_Counter_Comp_0320', 0, async (done: Function) => {
      await searchParentBlock('lightUpEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
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
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lightUpEffect', JsonType.value)
        ],
        assertEqual: 0
      })

      done();
    })
    //   pixelStretchEffect
    it('ArkUI_Counter_Comp_0321', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.left', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
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
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('left', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_Counter_Comp_0322', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.right', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
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
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('right', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_Counter_Comp_0323', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.top', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
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
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelStretchEffect', JsonType.obj),
          new KeyStruct('top', JsonType.obj)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    it('ArkUI_Counter_Comp_0324', 0, async (done: Function) => {
      await searchParentBlock('pixelStretchEffect.options.bottom', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Counter',
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
        id: 'Counter',
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
    it('ArkUI_Counter_Comp_0325', 0, async (done: Function) => {
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

    it('ArkUI_Counter_Comp_0326', 0, async (done: Function) => {
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
    it('ArkUI_Counter_Comp_0327', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.angle', '通用属性3')

      await sliderDrag({
        slideStar: Slide.start,
        id: 'Counter',
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
        id: 'Counter',
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
    it('ArkUI_Counter_Comp_0328', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Left'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0329', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Top'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0330', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 2,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Right'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0331', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 3,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Bottom'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0332', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 4,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftTop'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0333', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 5,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftBottom'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0334', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 6,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightTop'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0335', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 7,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightBottom'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0336', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.None'
      })

      done();

    })

    //linearGradient.color1
    it('ArkUI_Counter_Comp_0337', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0338', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0339', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0340', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0341', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0342', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number1
    it('ArkUI_Counter_Comp_0343', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.number1', '通用属性3')

      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.color2
    it('ArkUI_Counter_Comp_0344', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0345', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0346', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0347', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0348', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0349', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('colors', JsonType.array),
          new KeyStruct('0', JsonType.array),
          new KeyStruct('0', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // linearGradient.number2
    it('ArkUI_Counter_Comp_0350', 0, async (done: Function) => {
      await titleSearch('基础属性', 'linearGradient.number2', '通用属性3')
      //取不到值需要，设置颜色获取
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();
    })

    // linearGradient.repeating
    it('ArkUI_Counter_Comp_0351', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_Counter_Comp_0352', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Counter',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })




  })
}




