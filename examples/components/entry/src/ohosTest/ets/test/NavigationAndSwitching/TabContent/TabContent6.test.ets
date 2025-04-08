/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { describe, beforeAll, it } from '@ohos/hypium'
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  Search,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
} from '../../../utils';
import { TabContentStart } from './TabContent';
import { Driver, ON } from '@kit.TestKit';

const driver = Driver.create();

export default function TabContent6() {
  describe('TabContent6', () => {
    beforeAll(async (done: Function) => {
      await TabContentStart(done)
    })
    // hoverEffect
    it('ArkUI_Tabs_Comp_0558', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Scale'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0559', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 2,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Highlight'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0560', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')


      await radioClick({
        radioClickObj: 3,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.None'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0561', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Auto'
      })

      done()
    })

    // id
    it('ArkUI_Tabs_Comp_0562', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0563', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0564', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0565', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0566', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0567', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0568', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0569', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0570', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundEffect.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
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
        id: 'Tabs',
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
    it('ArkUI_Tabs_Comp_0571', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0572', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0573', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0574', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0575', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0576', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0577', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0578', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0579', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0580', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0581', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0582', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0583', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0584', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0585', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0586', 0, async (done: Function) => {

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

    it('ArkUI_Tabs_Comp_0587', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0588', 0, async (done: Function) => {

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
    it('ArkUI_Tabs_Comp_0589', 0, async (done: Function) => {

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

    // motionBlur.radius
    it('ArkUI_Tabs_Comp_0590', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: 100
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: 0
      })

      done()
    })

    // motionBlur.anchorX
    it('ArkUI_Tabs_Comp_0591', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.anchorX', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: 0
      })

      done()
    })

    // motionBlur.anchorY
    it('ArkUI_Tabs_Comp_0592', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.anchorY', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('motionBlur', JsonType.obj),
          new KeyStruct('anchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: 0
      })

      done()
    })

    // clickEffect
    it('ArkUI_Tabs_Comp_0593', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0594', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //clickEffect.level
    it('ArkUI_Tabs_Comp_0595', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性5')


      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '1'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0596', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性5')

      await radioClick({
        radioClickObj: 2,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '2'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0597', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '0'
      })

      done()
    })

    // clickEffect.scale
    it('ArkUI_Tabs_Comp_0598', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.scale'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性5')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.scale', '通用属性5')

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('scale', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('scale', JsonType.value),
        ],
        assertEqual: '1.000000'
      })

      await Search('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      done()
    })

    // accessibilityGroup
    it('ArkUI_Tabs_Comp_0599', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0600', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: false
      })

      done()
    })

    //accessibilityText
    it('ArkUI_Tabs_Comp_0601', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '组件被选中时，仅播报无障碍文本内容'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0602', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '无障碍文本'
      })

      done()
    })

    // accessibilityDescription
    it('ArkUI_Tabs_Comp_0603', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '用于为用户进一步说明当前组件'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0604', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '无障碍说明'
      })

      done()
    })

    // accessibilityLevel
    it('ArkUI_Tabs_Comp_0605', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'yes'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0606', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0607', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no-hide-descendants'
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0608', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'auto'
      })

      done()
    })

    // attributeModifier
    it('ArkUI_Tabs_Comp_0609', 0, async (done: Function) => {

      await titleSearch('基础属性', 'attributeModifier', '通用属性5')

      // 取不到attributeModifier属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'attributeModifier'
        }
      })

      done()
    })

    it('ArkUI_Tabs_Comp_0610', 0, async (done: Function) => {

      await titleSearch('基础属性', 'attributeModifier', '通用属性5')

      // 取不到attributeModifier属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'attributeModifier'
        }
      })

      done()
    })
    //gestureModifier
    /*
    * 测试组件gestureModifier支持设置为true且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0611', 0, async (done: Function) => {
      // 无法取到属性值
      await titleSearch('基础属性', 'gestureModifier', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件gestureModifier支持设置包含单个子组件为false且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0612', 0, async (done: Function) => {
      // 无法取到属性值
      await titleSearch('基础属性', 'gestureModifier', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //outline.value.width
    it('ArkUI_Tabs_Comp_0613', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    //outline.value.color
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0614', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0615', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为3号色显示且获取属性正确
     * */
    it('ArkUI_Tabs_Comp_0616', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0617', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为5号色显示且获取属性正确
     * */
    it('ArkUI_Tabs_Comp_0618', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0619', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    /*
     * outline.value.radius
    */
    it('ArkUI_Tabs_Comp_0620', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.radius', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Tabs',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineRadius', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    //outline.value.style
    /*
     * 测试组件outline.value.style支持设置SOLID且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0621', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.SOLID'
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DASHED且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0622', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.DASHED'
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DOTTED且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0623', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineStyle', JsonType.value)
        ],
        assertEqual: 'OutlineStyle.DOTTED'
      })
      done();
    })
    /*
     * outline.value.width展开属性测试完成，关闭outline.value.width，无需断言
     * */
    it('ArkUI_Tabs_Comp_0624', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await getToggle(ToggleClick.Close)
      done();
    })
    // visualEffect
    /*
     *测试组件visualEffect支持设置true且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0625', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'visualEffect', '通用属性6')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
    *测试组件visualEffect支持设置false且获取属性正确
   */
    it('ArkUI_Tabs_Comp_0626', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'visualEffect', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //backgroundFilter
    /*
    *测试组件backgroundFilter支持设置true且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0627', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件backgroundFilter支持设置false且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0628', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'backgroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //foregroundFilter
    /*
    *测试组件foregroundFilter支持设置true且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0629', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件foregroundFilter支持设置false且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0630', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //compositingFilter
    /*
    *测试组件compositingFilter支持设置true且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0631', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'compositingFilter', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    *测试组件compositingFilter支持设置false且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0632', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'compositingFilter', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.x
    it('ArkUI_Tabs_Comp_0633', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.x', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.y
    it('ArkUI_Tabs_Comp_0634', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.y', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //responseRegion.value.width
    /*
    * 测试组件responseRegion.value.width支持设置0%且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0635', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
    * 测试组件responseRegion.value.width支持设置30%且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0636', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置60%且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0637', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置90%且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0638', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.width支持设置100%且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0639', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性6')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'responseRegion.value.width'
        }
      })
      done();
    })
    //responseRegion.value.height
    /*
    * 测试组件responseRegion.value.height支持设置0%且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0640', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
    * 测试组件responseRegion.value.height支持设置30%且获取属性正确
    */
    it('ArkUI_Tabs_Comp_0641', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置60%且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0642', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置90%且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0643', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    /*
     * 测试组件responseRegion.value.height支持设置100%且获取属性正确
     */
    it('ArkUI_Tabs_Comp_0644', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性6')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'responseRegion.value.height'
        }
      })
      done();
    })
    //hitTestBehavior
    /*
     * 测试组件hitTestBehavior支持设置Default且获取属性正确
     * */
    it('ArkUI_Tabs_Comp_0645', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Default'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Block且获取属性正确
     * */
    it('ArkUI_Tabs_Comp_0646', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Block'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Transparent且获取属性正确
     * */
    it('ArkUI_Tabs_Comp_0647', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Transparent'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置None且获取属性正确
     * */
    it('ArkUI_Tabs_Comp_0648', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'Tabs',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.None'
      })
      done();
    })
  })
}