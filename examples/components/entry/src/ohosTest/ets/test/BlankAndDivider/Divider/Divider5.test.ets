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
import { Driver, ON, Component } from '@kit.TestKit';
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
import { DividerStart } from './Divider';

const driver = Driver.create();

export default function Divider5() {
  describe('Divider5', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await DividerStart(done)
    })
    // bindPopup.placement
    it('ArkUI_Divider_Comp_0384', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0385', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0386', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0387', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0388', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0389', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0390', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })
      done()
    })

    it('ArkUI_Divider_Comp_0391', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0392', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0393', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.offsetX
    it('ArkUI_Divider_Comp_0394', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.offsetX', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.offsetY
    it('ArkUI_Divider_Comp_0395', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.offsetY', '通用属性3')

      //取不到bindPopup属性值
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

    //bindPopup.enableArrow
    it('ArkUI_Divider_Comp_0396', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.enableArrow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0397', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.enableArrow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //bindPopup.popupColor
    it('ArkUI_Divider_Comp_0398', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0399', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0400', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0401', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0402', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0403', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.autoCancel
    it('ArkUI_Divider_Comp_0404', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.autoCancel', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0405', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.autoCancel', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()

    })

    // bindPopup.width
    it('ArkUI_Divider_Comp_0406', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.width', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.arrowPointPosition
    it('ArkUI_Divider_Comp_0407', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0408', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0409', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType
    it('ArkUI_Divider_Comp_0410', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    // bindPopup.shadowType
    it('ArkUI_Divider_Comp_0411', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.radius
    it('ArkUI_Divider_Comp_0412', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.radius'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }


      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.radius', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.shadowType.shadowOptions.type
    it('ArkUI_Divider_Comp_0413', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.type', '通用属性3')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0414', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.type', '通用属性3')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.color
    it('ArkUI_Divider_Comp_0415', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')
      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0416', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0417', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')
      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0418', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0419', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0420', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.shadowType.shadowOptions.offsetX
    it('ArkUI_Divider_Comp_0421', 0, async (done: Function) => {
      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.offsetX'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.offsetX', '通用属性3')
      //取不到bindPopup属性值
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

    // bindPopup.shadowType.shadowOptions.offsetY
    it('ArkUI_Divider_Comp_0422', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.offsetY'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.offsetY', '通用属性3')
      //取不到bindPopup属性值
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

    // bindPopup.shadowType.shadowOptions.fill
    it('ArkUI_Divider_Comp_0423', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.fill'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.fill', '通用属性3')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0424', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.fill'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.fill', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })


      done()
    })

    // bindPopup.shadowType.shadowStyle
    it('ArkUI_Divider_Comp_0425', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0426', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0427', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0428', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0429', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0430', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.BackgroundBlurStyle
    it('ArkUI_Divider_Comp_0431', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0432', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0433', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0434', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0435', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0436', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0437', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0438', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0439', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0440', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0441', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0442', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.transition.opacity
    it('ArkUI_Divider_Comp_0443', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.opacity', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.translateX
    it('ArkUI_Divider_Comp_0444', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateX', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.translateY
    it('ArkUI_Divider_Comp_0445', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateY', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.translateZ
    it('ArkUI_Divider_Comp_0446', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateZ', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.scaleX
    it('ArkUI_Divider_Comp_0447', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleX', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.scaleY
    it('ArkUI_Divider_Comp_0448', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleY', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.scaleZ
    it('ArkUI_Divider_Comp_0449', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleZ', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.scale.centerX
    it('ArkUI_Divider_Comp_0450', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerX', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.scale.centerY
    it('ArkUI_Divider_Comp_0451', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerY', '通用属性3')

      //取不到bindPopup属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
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

    // bindPopup.transition.RotateX
    it('ArkUI_Divider_Comp_0452', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateX', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.RotateY
    it('ArkUI_Divider_Comp_0453', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateY', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.RotateZ
    it('ArkUI_Divider_Comp_0454', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateZ', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.Rotate.CenterX
    it('ArkUI_Divider_Comp_0455', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.Rotate.CenterX', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.Rotate.CenterY
    it('ArkUI_Divider_Comp_0456', 0, async (done: Function) => {

      await titleSearch('基础属性', ' bindPopup.transition.Rotate.CenterY', '通用属性3')

      //取不到bindPopup属性值
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

    // bindPopup.transition.move
    it('ArkUI_Divider_Comp_0457', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0458', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0459', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0460', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //focusable
    it('ArkUI_Divider_Comp_0461', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Divider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Divider_Comp_0462', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Divider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_Divider_Comp_0463', 0, async (done: Function) => {
      //设置当前组件是否为当前页面上的默认焦点，仅在初次创建的页面第一次进入时生效。
      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Divider_Comp_0464', 0, async (done: Function) => {

      await titleSearch('基础属性', 'defaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // groupDefaultFocus
    it('ArkUI_Divider_Comp_0465', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Divider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Divider_Comp_0466', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Divider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusOnTouch
    it('ArkUI_Divider_Comp_0467', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Divider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Divider_Comp_0468', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Divider',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_Divider_Comp_0469', 0, async (done: Function) => {

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
    it('ArkUI_Divider_Comp_0470', 0, async (done: Function) => {

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

    it('ArkUI_Divider_Comp_0471', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0472', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0473', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0474', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0475', 0, async (done: Function) => {

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
    it('ArkUI_Divider_Comp_0476', 0, async (done: Function) => {

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

    // bindMenu.font.size
    it('ArkUI_Divider_Comp_0477', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.size', '通用属性4')

      //取不到bindMenu属性值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.font.weight
    it('ArkUI_Divider_Comp_0478', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Divider_Comp_0479', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0480', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0481', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0482', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Divider_Comp_0483', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.font.style
    it('ArkUI_Divider_Comp_0484', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.style', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Divider_Comp_0485', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.style', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })


  })

}