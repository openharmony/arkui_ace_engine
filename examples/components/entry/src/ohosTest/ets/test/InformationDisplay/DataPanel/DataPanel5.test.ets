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
  Slide,
  sliderDrag,
  ToggleClick,
  titleSearch,
  searchParentBlock,
  Search,
} from '../../../utils';
import { DataPanelStart } from './DataPanel';


const driver = Driver.create();

export default function DataPanel5() {
  describe('DataPanel5', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await DataPanelStart(done)


    })

    it('ArkUI_DataPanel_Comp_0332', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 4,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftTop'
      })

      done();

    })

    it('ArkUI_DataPanel_Comp_0333', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 5,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftBottom'
      })

      done();

    })

    it('ArkUI_DataPanel_Comp_0334', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 6,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightTop'
      })

      done();

    })

    it('ArkUI_DataPanel_Comp_0335', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 7,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightBottom'
      })

      done();

    })

    it('ArkUI_DataPanel_Comp_0336', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
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
    it('ArkUI_DataPanel_Comp_0337', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0338', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0339', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0340', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0341', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0342', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
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
    it('ArkUI_DataPanel_Comp_0343', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0344', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0345', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0346', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0347', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0348', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'DataPanel',
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

    it('ArkUI_DataPanel_Comp_0349', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
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
    it('ArkUI_DataPanel_Comp_0350', 0, async (done: Function) => {
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
    it('ArkUI_DataPanel_Comp_0351', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_DataPanel_Comp_0352', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })

    // BindPopup
    // show.button
    it('ArkUI_DataPanel_Comp_0353', 0, async (done: Function) => {

      await titleSearch('基础属性', 'show.button', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_DataPanel_Comp_0354', 0, async (done: Function) => {

      await titleSearch('基础属性', 'show.button', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // bindPopup.arrowOffset
    it('ArkUI_DataPanel_Comp_0355', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowOffset', '通用属性3')

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

      done();
    })

    // bindPopup.showInSubWindow
    it('ArkUI_DataPanel_Comp_0356', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.showInSubWindow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0357', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.showInSubWindow', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.maskType
    it('ArkUI_DataPanel_Comp_0358', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    // bindPopup.maskType
    it('ArkUI_DataPanel_Comp_0359', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.mask.color
    it('ArkUI_DataPanel_Comp_0360', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0361', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0362', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0363', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0364', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0365', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性3')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.mask.boolean
    it('ArkUI_DataPanel_Comp_0366', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.mask.boolean', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0367', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.mask.boolean', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.textColor
    it('ArkUI_DataPanel_Comp_0368', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0369', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0370', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0371', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0372', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0373', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.font.size
    it('ArkUI_DataPanel_Comp_0374', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.size', '通用属性3')

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

    // bindPopup.messageOptions.font.weight
    it('ArkUI_DataPanel_Comp_0375', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0376', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0377', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0378', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0379', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0380', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.messageOptions.font.style
    it('ArkUI_DataPanel_Comp_0381', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.style', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0382', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.style', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.targetSpace
    it('ArkUI_DataPanel_Comp_0383', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.targetSpace', '通用属性3')

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

    // bindPopup.placement
    it('ArkUI_DataPanel_Comp_0384', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0385', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0386', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0387', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0388', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0389', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0390', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0391', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0392', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0393', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0394', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0395', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0396', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0397', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0398', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0399', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0400', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0401', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0402', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0403', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0404', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0405', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0406', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0407', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0408', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_DataPanel_Comp_0409', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0410', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0411', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0412', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0413', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0414', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0415', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0416', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0417', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0418', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0419', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0420', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0421', 0, async (done: Function) => {
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
    it('ArkUI_DataPanel_Comp_0422', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0423', 0, async (done: Function) => {

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

    it('ArkUI_DataPanel_Comp_0424', 0, async (done: Function) => {

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
    it('ArkUI_DataPanel_Comp_0425', 0, async (done: Function) => {

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


  })
}




