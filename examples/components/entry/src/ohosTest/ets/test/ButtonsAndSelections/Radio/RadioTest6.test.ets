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
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  Search,
  ToggleClick,
  titleSearch,
  searchParentBlock,
  searchToggle,
  getToggle
} from '../../../utils';
import { RadioTest } from './RadioTest.test'
const driver = Driver.create();
export default function RadioTest6() {
  describe('RadioTest6', () => {
    beforeAll(async (done: Function) => {
      await RadioTest(done)
    })
    // focusOnTouch
    it('ArkUI_Radio_Comp_0467', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Radio_Comp_0468', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_Radio_Comp_0469', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.margin', '通用属性3')

      //取不到focusBox值
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

      done()
    })

    // focusBox.strokeColor
    it('ArkUI_Radio_Comp_0470', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Radio_Comp_0471', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0472', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0473', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0474', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0475', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // focusBox.strokeWidth
    it('ArkUI_Radio_Comp_0476', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeWidth', '通用属性3')

      //取不到focusBox值
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

      done()
    })
    // hoverEffect
    it('ArkUI_Radio_Comp_0558', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Scale'
      })

      done()
    })

    it('ArkUI_Radio_Comp_0559', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 2,
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Highlight'
      })

      done()
    })

    it('ArkUI_Radio_Comp_0560', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')


      await radioClick({
        radioClickObj: 3,
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.None'
      })

      done()
    })

    it('ArkUI_Radio_Comp_0561', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Auto'
      })

      done()
    })

    // id
    it('ArkUI_Radio_Comp_0562', 0, async (done: Function) => {

      await titleSearch('基础属性', 'id', '通用属性4')

      // key优先级比id高会覆盖
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })

    it('ArkUI_Radio_Comp_0563', 0, async (done: Function) => {

      await titleSearch('基础属性', 'id', '通用属性4')

      // key优先级比id高会覆盖
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()

    })

    // key
    it('ArkUI_Radio_Comp_0564', 0, async (done: Function) => {

      await titleSearch('基础属性', 'key', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: '2',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('id', JsonType.value)
        ],
        assertEqual: '2'
      })

      done()

    })

    it('ArkUI_Radio_Comp_0565', 0, async (done: Function) => {

      await titleSearch('基础属性', 'key', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: '1',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('id', JsonType.value)
        ],
        assertEqual: '1'
      })

      done()
    })

    // reuseId
    it('ArkUI_Radio_Comp_0566', 0, async (done: Function) => {

      await titleSearch('基础属性', 'reuseId', '通用属性4')

      // 取不到reuseId属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Radio_Comp_0567', 0, async (done: Function) => {

      await titleSearch('基础属性', 'reuseId', '通用属性4')

      // 取不到reuseId属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // restoreId
    it('ArkUI_Radio_Comp_0568', 0, async (done: Function) => {

      await titleSearch('基础属性', 'restoreId', '通用属性4')

      // 取不到restoreId属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'restoreId'
        }
      })

      done()
    })

    it('ArkUI_Radio_Comp_0569', 0, async (done: Function) => {

      await titleSearch('基础属性', 'restoreId', '通用属性4')

      // 取不到restoreId属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'restoreId'
        }
      })

      done()
    })

    // foregroundEffect.radius
    it('ArkUI_Radio_Comp_0570', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundEffect.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('foregroundEffect', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Radio',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('foregroundEffect', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done()
    })

    // foregroundBlurStyle.value
    it('ArkUI_Radio_Comp_0571', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Radio_Comp_0572', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0573', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0574', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0575', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0576', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0577', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0578', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0579', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0580', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0581', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0582', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.colorMode
    it('ArkUI_Radio_Comp_0583', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Radio_Comp_0584', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Radio_Comp_0585', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.adaptiveColor
    it('ArkUI_Radio_Comp_0586', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.adaptiveColor', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Radio_Comp_0587', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.adaptiveColor', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // foregroundBlurStyle.options.blurOptions
    it('ArkUI_Radio_Comp_0588', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.blurOptions', '通用属性5')

      // 取不到foregroundBlurStyle值
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

      done()
    })

    // foregroundBlurStyle.options.scale
    it('ArkUI_Radio_Comp_0589', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.blurOptions', '通用属性5')

      // 取不到foregroundBlurStyle值
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

      done()
    })
  })
}