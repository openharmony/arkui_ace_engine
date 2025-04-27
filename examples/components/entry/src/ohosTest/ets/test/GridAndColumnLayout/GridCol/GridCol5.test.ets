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
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  Search,
  titleSearch,
} from '../../../utils/index';
import { On, Point } from '@ohos.UiTest';
import { GridColStart } from './GridCol';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function GridCol5Test() {
  describe('GridCol5Test', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
      await GridColStart(done)
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(() => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })
    it('ArkUI_GridCol_Comp_0348', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
        id: 'GridCol',
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

    it('ArkUI_GridCol_Comp_0349', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'GridCol',
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
    it('ArkUI_GridCol_Comp_0350', 0, async (done: Function) => {
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
    it('ArkUI_GridCol_Comp_0351', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'GridCol',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_GridCol_Comp_0352', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'GridCol',
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
    it('ArkUI_GridCol_Comp_0353', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0354', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0355', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0356', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0357', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0358', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0359', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0360', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0361', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0362', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0363', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0364', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0365', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0366', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0367', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0368', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0369', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0370', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0371', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0372', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0373', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0374', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0375', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0376', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0377', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0378', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0379', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0380', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0381', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0382', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0383', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0384', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0385', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0386', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0387', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0388', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0389', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0390', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0391', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0392', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0393', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0394', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0395', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0396', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0397', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0398', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0399', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0400', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0401', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0402', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性3')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0403', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0404', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0405', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0406', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0407', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0408', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0409', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0410', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0411', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0412', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0413', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0414', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0415', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0416', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0417', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0418', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0419', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0420', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0421', 0, async (done: Function) => {
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
    it('ArkUI_GridCol_Comp_0422', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0423', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0424', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0425', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0426', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0427', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0428', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0429', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0430', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0431', 0, async (done: Function) => {

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

    it('ArkUI_GridCol_Comp_0432', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0433', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0434', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0435', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0436', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0437', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0438', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0439', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0440', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0441', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_GridCol_Comp_0442', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0443', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0444', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0445', 0, async (done: Function) => {

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
    it('ArkUI_GridCol_Comp_0446', 0, async (done: Function) => {

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
  })
}