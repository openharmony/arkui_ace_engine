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

export default function FoldSplitContainer6() {
  describe('FoldSplitContainer6', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })

    // bindPopup.transition.opacity
    it('ArkUI_FoldSplitContainer_Comp_0239', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.opacity', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0240', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateX', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0241', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateY', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0242', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.translateZ', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0243', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleX', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0244', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleY', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0245', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scaleZ', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0246', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerX', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0247', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.scale.centerY', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0248', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateX', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0249', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateY', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0250', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.RotateZ', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0251', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.Rotate.CenterX', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0252', 0, async (done: Function) => {

      await titleSearch('基础属性', ' bindPopup.transition.Rotate.CenterY', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0253', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0254', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0255', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性2')

      //取不到bindPopup属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0256', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindPopup.transition.move', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0257', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0258', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusable', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusable', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // defaultFocus
    it('ArkUI_FoldSplitContainer_Comp_0259', 0, async (done: Function) => {
      //设置当前组件是否为当前页面上的默认焦点，仅在初次创建的页面第一次进入时生效。
      await titleSearch('基础属性', 'defaultFocus', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0260', 0, async (done: Function) => {

      await titleSearch('基础属性', 'defaultFocus', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // groupDefaultFocus
    it('ArkUI_FoldSplitContainer_Comp_0261', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0262', 0, async (done: Function) => {

      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('groupDefaultFocus', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusOnTouch
    it('ArkUI_FoldSplitContainer_Comp_0263', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: true
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0264', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusOnTouch', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('focusOnTouch', JsonType.value)
        ],
        assertEqual: false
      })

      done()
    })

    // focusBox.margin
    it('ArkUI_FoldSplitContainer_Comp_0265', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.margin', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0266', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性2')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0267', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性2')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0268', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性2')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0269', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性2')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0270', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性2')

      //取不到focusBox值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0271', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeColor', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0272', 0, async (done: Function) => {

      await titleSearch('基础属性', 'focusBox.strokeWidth', '通用属性2')

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
    it('ArkUI_FoldSplitContainer_Comp_0273', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.size', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0274', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0275', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0276', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0277', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0278', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0279', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.weight', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0280', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.style', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0281', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.font.style', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0282', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0283', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0284', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0285', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0286', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0287', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.fontColor', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0288', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.radius', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0298', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.width', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0290', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.height', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0291', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0292', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0293', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0294', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0295', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0296', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.color', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0297', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.strokeWidth', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0298', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.startMargin', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0299', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemDivider.endMargin', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0300', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.strokeWidth', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0301', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0302', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0303', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0304', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0305', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0306', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.color', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0307', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.startMargin', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0308', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.menuItemGroupDivider.endMargin', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0309', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0310', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0311', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.SubMenuExpandingMode', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0312', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0313', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0314', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.direction', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0315', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })
    it('ArkUI_FoldSplitContainer_Comp_0316', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0317', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0318', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0319', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0340', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0341', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0342', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      await Search('基础属性', 'bindMenu.菜单项1是否选中', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      done()
    })

    // bindMenu.菜单项2是否选中
    it('ArkUI_FoldSplitContainer_Comp_0343', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0344', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0345', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0346', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0347', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0348', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0349', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0350', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.是否显示选中图标
    it('ArkUI_FoldSplitContainer_Comp_0351', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0352', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0353', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')

      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0354', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0355', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0356', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('bindMenu.是否显示选中图标'))

      if (!title) {
        await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'bindMenu.是否显示选中图标', '通用属性3')
      //取不到bindMenu属性值
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      await Search('基础属性', 'bindMenu.菜单项2是否选中', '通用属性3')

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