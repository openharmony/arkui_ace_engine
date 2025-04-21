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

export default function Text8Test() {
  describe('Text8Test', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await TextStart(done);
    })
    // hoverEffect
    it('ArkUI_Text_Comp_0558', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Scale'
      })

      done()
    })

    it('ArkUI_Text_Comp_0559', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Highlight'
      })

      done()
    })

    it('ArkUI_Text_Comp_0560', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')


      await radioClick({
        radioClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.None'
      })

      done()
    })

    it('ArkUI_Text_Comp_0561', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Auto'
      })

      done()
    })

    // id
    it('ArkUI_Text_Comp_0562', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0563', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0564', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0565', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0566', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0567', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0568', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0569', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0570', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundEffect.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0571', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0572', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Text_Comp_0573', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Text_Comp_0574', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Text_Comp_0575', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Text_Comp_0576', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Text_Comp_0577', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Text_Comp_0578', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Text_Comp_0579', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Text_Comp_0580', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Text_Comp_0581', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Text_Comp_0582', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0583', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0584', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Text_Comp_0585', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0586', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0587', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0588', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0589', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0590', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.radius', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0591', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.anchorX', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0592', 0, async (done: Function) => {

      await titleSearch('基础属性', 'motionBlur.anchorY', '通用属性5')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0593', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Text_Comp_0594', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0595', 0, async (done: Function) => {

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
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '1'
      })

      done()
    })

    it('ArkUI_Text_Comp_0596', 0, async (done: Function) => {

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
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '2'
      })

      done()
    })

    it('ArkUI_Text_Comp_0597', 0, async (done: Function) => {

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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0598', 0, async (done: Function) => {

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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0599', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Text_Comp_0600', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: false
      })

      done()
    })

    //accessibilityText
    it('ArkUI_Text_Comp_0601', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '组件被选中时，仅播报无障碍文本内容'
      })

      done()
    })

    it('ArkUI_Text_Comp_0602', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '无障碍文本'
      })

      done()
    })

    // accessibilityDescription
    it('ArkUI_Text_Comp_0603', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '用于为用户进一步说明当前组件'
      })

      done()
    })

    it('ArkUI_Text_Comp_0604', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '无障碍说明'
      })

      done()
    })

    // accessibilityLevel
    it('ArkUI_Text_Comp_0605', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'yes'
      })

      done()
    })

    it('ArkUI_Text_Comp_0606', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no'
      })

      done()
    })

    it('ArkUI_Text_Comp_0607', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no-hide-descendants'
      })

      done()
    })

    it('ArkUI_Text_Comp_0608', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'auto'
      })

      done()
    })

    // attributeModifier
    it('ArkUI_Text_Comp_0609', 0, async (done: Function) => {

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

    it('ArkUI_Text_Comp_0610', 0, async (done: Function) => {

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
    it('ArkUI_Text_Comp_0611', 0, async (done: Function) => {
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
    it('ArkUI_Text_Comp_0612', 0, async (done: Function) => {
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
    it('ArkUI_Text_Comp_0613', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineWidth', JsonType.value)
        ],
        assertEqual: '32.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Text',
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
    it('ArkUI_Text_Comp_0614', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 0,
        id: 'Text',
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
    it('ArkUI_Text_Comp_0615', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 1,
        id: 'Text',
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
    it('ArkUI_Text_Comp_0616', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 2,
        id: 'Text',
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
    it('ArkUI_Text_Comp_0617', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 3,
        id: 'Text',
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
    it('ArkUI_Text_Comp_0618', 0, async (done: Function) => {
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 4,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('outlineColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
  })
}