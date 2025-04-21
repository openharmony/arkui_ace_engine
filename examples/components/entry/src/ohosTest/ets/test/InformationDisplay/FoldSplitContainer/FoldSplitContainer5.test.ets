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
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search
} from '../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';
import { Driver, ON } from '@kit.TestKit';

const driver = Driver.create();

export default function FoldSplitContainer5() {
  describe('FoldSplitContainer5', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })

    //linearGradient.color1
    it('ArkUI_FoldSplitContainer_Comp_0134', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0135', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 1,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0136', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 2,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0137', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 3,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0138', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 4,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0139', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color1', '通用属性2')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0140', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.number1', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0141', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0142', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 1,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0143', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 2,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0144', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 3,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0145', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 4,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0146', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.color2', '通用属性2')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0147', 0, async (done: Function) => {
      await titleSearch('基础属性', 'linearGradient.number2', '通用属性2')
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
    it('ArkUI_FoldSplitContainer_Comp_0148', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('repeating', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0149', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0150', 0, async (done: Function) => {

      await titleSearch('基础属性', 'show.button', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0151', 0, async (done: Function) => {

      await titleSearch('基础属性', 'show.button', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0152', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowOffset', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0153', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.showInSubWindow', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0154', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.showInSubWindow', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0155', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0156', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0157', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0158', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0159', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0160', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0161', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0162', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.mask.color'))

      if (!title) {
        await Search('基础属性', 'bindPopup.maskType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.mask.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await titleSearch('基础属性', 'bindPopup.maskType', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindPopup.mask.boolean
    it('ArkUI_FoldSplitContainer_Comp_0163', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.mask.boolean', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0164', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.mask.boolean', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0165', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0166', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0167', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0168', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0169', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0170', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.textColor', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0171', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.size', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0172', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0173', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0174', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0175', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0176', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0177', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.weight', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0178', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.style', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0179', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.messageOptions.font.style', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0180', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.targetSpace', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0181', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0182', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0183', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0184', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0185', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0186', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0187', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0188', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0189', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0190', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.placement', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0191', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.offsetX', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0192', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.offsetY', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0193', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.enableArrow', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0194', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.enableArrow', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0195', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0196', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0197', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0198', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0199', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0200', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.popupColor', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0201', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.autoCancel', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0202', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.autoCancel', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0203', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.width', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0204', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0205', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0206', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.arrowPointPosition', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0207', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0208', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0209', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.radius'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }


      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.radius', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0209', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.type', '通用属性2')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0210', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.type', '通用属性2')
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
    it('ArkUI_FoldSplitContainer_Comp_0211', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性2')
      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0212', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0213', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性2')
      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0214', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0215', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性2')

      //取不到bindPopup属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0216', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.type'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.color', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0217', 0, async (done: Function) => {
      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.offsetX'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.offsetX', '通用属性2')
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
    it('ArkUI_FoldSplitContainer_Comp_0218', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.offsetY'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.offsetY', '通用属性2')
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
    it('ArkUI_FoldSplitContainer_Comp_0219', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.fill'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.fill', '通用属性2')
      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0220', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindPopup.shadowType.shadowOptions.fill'))

      if (!title) {
        await Search('基础属性', 'bindPopup.shadowType', '通用属性2')

        await radioClick({
          radioClickObj: 1,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowOptions.fill', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await titleSearch('基础属性', 'bindPopup.shadowType', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })


      done()
    })

    // bindPopup.shadowType.shadowStyle
    it('ArkUI_FoldSplitContainer_Comp_0221', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0222', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0223', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0224', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0225', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0226', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.shadowType.shadowStyle', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0227', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0228', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0229', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0230', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0231', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0232', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0233', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0234', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0235', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0236', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0237', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0238', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.BackgroundBlurStyle', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })
  })
}