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
import { AlphabetIndexerStart } from './AlphabetIndexer';

const driver = Driver.create();

export default function AlphabetIndexer7Test() {
  describe('AlphabetIndexer7Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await AlphabetIndexerStart(done)

    })
    // bindPopup.transition.scale.centerX
    it('ArkUI_Column_Comp_0450', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0451', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0452', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0453', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0454', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0455', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0456', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0457', 0, async (done: Function) => {

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

    it('ArkUI_Column_Comp_0458', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0459', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性3')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0460', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0461', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Column_Comp_0462', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_Column_Comp_0463', 0, async (done: Function) => {
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

    it('ArkUI_Column_Comp_0464', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0465', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Column_Comp_0466', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusOnTouch
    it('ArkUI_Column_Comp_0467', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })

    it('ArkUI_Column_Comp_0468', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Column',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_Column_Comp_0469', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0470', 0, async (done: Function) => {

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

    it('ArkUI_Column_Comp_0471', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0472', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0473', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0474', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性3')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0475', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0476', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0477', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0478', 0, async (done: Function) => {

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

    it('ArkUI_Column_Comp_0479', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0480', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0481', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0482', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0483', 0, async (done: Function) => {

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
    it('ArkUI_Column_Comp_0484', 0, async (done: Function) => {

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

    it('ArkUI_Column_Comp_0485', 0, async (done: Function) => {

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

    // bindMenu.fontColor
    it('ArkUI_Column_Comp_0486', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0487', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0488', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0489', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0490', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0491', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // bindMenu.radius
    it('ArkUI_Column_Comp_0492', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.radius', '通用属性4')

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

    // bindMenu.width
    it('ArkUI_Column_Comp_0493', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.width', '通用属性4')

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

    // bindMenu.height
    it('ArkUI_Column_Comp_0494', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.height', '通用属性4')

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

    // bindMenu.menuItemDivider.color
    it('ArkUI_Column_Comp_0495', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0496', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0497', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0498', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0499', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0500', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemDivider.strokeWidth
    it('ArkUI_Column_Comp_0501', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.strokeWidth', '通用属性4')

      //取不到bindMenu属性值
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

    // bindMenu.menuItemDivider.startMargin
    it('ArkUI_Column_Comp_0502', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.startMargin', '通用属性4')

      //取不到bindMenu属性值
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

    // bindMenu.menuItemDivider.endMargin
    it('ArkUI_Column_Comp_0503', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.endMargin', '通用属性4')

      //取不到bindMenu属性值
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

    // bindMenu.menuItemGroupDivider.strokeWidth
    it('ArkUI_Column_Comp_0504', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.strokeWidth', '通用属性4')

      //取不到bindMenu属性值
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

    // bindMenu.menuItemGroupDivider.color
    it('ArkUI_Column_Comp_0505', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0506', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0507', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0508', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0509', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0510', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.menuItemGroupDivider.startMargin
    it('ArkUI_Column_Comp_0511', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.startMargin', '通用属性4')

      //取不到bindMenu属性值
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

    // bindMenu.menuItemGroupDivider.endMargin
    it('ArkUI_Column_Comp_0512', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.endMargin', '通用属性4')

      //取不到bindMenu属性值
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

    // bindMenu.SubMenuExpandingMode
    it('ArkUI_Column_Comp_0513', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0514', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0515', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.direction
    it('ArkUI_Column_Comp_0516', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0517', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0518', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.菜单项1是否选中
    it('ArkUI_Column_Comp_0519', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })

    it('ArkUI_Column_Comp_0520', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Column_Comp_0521', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0522', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0523', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0524', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0525', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0526', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      done()
    })

    // bindMenu.菜单项2是否选中
    it('ArkUI_Column_Comp_0527', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0528', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Column_Comp_0529', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0530', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0531', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0532', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0533', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0534', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.菜单项3是否选中
    it('ArkUI_Column_Comp_0535', 0, async (done: Function) => {


      await titleSearch('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })

    it('ArkUI_Column_Comp_0536', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_Column_Comp_0537', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0538', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })

    it('ArkUI_Column_Comp_0539', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })

    it('ArkUI_Column_Comp_0540', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })

    it('ArkUI_Column_Comp_0541', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })

    it('ArkUI_Column_Comp_0542', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性4')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await Search('基础属性', 'bindMenu.菜单项3是否选中', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.菜单项4是否选中
    it('ArkUI_Column_Comp_0543', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Column_Comp_0544', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项4是否选中', '通用属性4')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

  })
}