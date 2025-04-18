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
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search,
  searchToggle
} from '../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';
import { Driver, ON } from '@kit.TestKit';

const driver = Driver.create();

export default function FoldSplitContainer7() {
  describe('FoldSplitContainer7', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })

    // bindMenu.item中是否显示右侧图标
    it('ArkUI_FoldSplitContainer_Comp_0357', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.item中是否显示右侧图标', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0358', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.item中是否显示右侧图标', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    // bindMenu.Opacity
    it('ArkUI_FoldSplitContainer_Comp_0359', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Opacity', '通用属性3')

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
    // bindMenu.Visibility
    it('ArkUI_FoldSplitContainer_Comp_0360', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Visibility', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0361', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Visibility', '通用属性3')

      //取不到bindMenu属性值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()

    })

    // bindMenu.Padding
    it('ArkUI_FoldSplitContainer_Comp_0362', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Padding', '通用属性3')

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
    // bindMenu.Margin
    it('ArkUI_FoldSplitContainer_Comp_0363', 0, async (done: Function) => {

      await titleSearch('基础属性', 'bindMenu.Margin', '通用属性3')

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

    // hoverEffect
    it('ArkUI_FoldSplitContainer_Comp_0364', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Scale'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0365', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性3')

      await radioClick({
        radioClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Highlight'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0366', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性3')


      await radioClick({
        radioClickObj: 3,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.None'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0367', 0, async (done: Function) => {

      await titleSearch('基础属性', 'hoverEffect', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hoverEffect', JsonType.value)
        ],
        assertEqual: 'HoverEffect.Auto'
      })

      done()
    })

    // id
    it('ArkUI_FoldSplitContainer_Comp_0368', 0, async (done: Function) => {

      await titleSearch('基础属性', 'id', '通用属性3')

      // key优先级比id高会覆盖
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()

    })
    it('ArkUI_FoldSplitContainer_Comp_0369', 0, async (done: Function) => {

      await titleSearch('基础属性', 'id', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0370', 0, async (done: Function) => {

      await titleSearch('基础属性', 'key', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0371', 0, async (done: Function) => {

      await titleSearch('基础属性', 'key', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0372', 0, async (done: Function) => {

      await titleSearch('基础属性', 'reuseId', '通用属性3')

      // 取不到reuseId属性值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0373', 0, async (done: Function) => {

      await titleSearch('基础属性', 'reuseId', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0374', 0, async (done: Function) => {

      await titleSearch('基础属性', 'restoreId', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0375', 0, async (done: Function) => {

      await titleSearch('基础属性', 'restoreId', '通用属性3')

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
    it('ArkUI_FoldSplitContainer_Comp_0376', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundEffect.radius', '通用属性4')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0377', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0378', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0379', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0380', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0381', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0382', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0383', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0384', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0385', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0386', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0387', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0388', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性4')


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
    it('ArkUI_FoldSplitContainer_Comp_0389', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0390', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0391', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性4')

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
    it('ArkUI_FoldSplitContainer_Comp_0392', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.adaptiveColor', '通用属性4')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0393', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.adaptiveColor', '通用属性4')

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
    it('ArkUI_FoldSplitContainer_Comp_0394', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.blurOptions', '通用属性4')

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
    it('ArkUI_FoldSplitContainer_Comp_0395', 0, async (done: Function) => {

      await titleSearch('基础属性', 'foregroundBlurStyle.options.blurOptions', '通用属性4')

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

    // clickEffect
    it('ArkUI_FoldSplitContainer_Comp_0396', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0397', 0, async (done: Function) => {

      await titleSearch('基础属性', 'clickEffect', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done()
    })

    //clickEffect.level
    it('ArkUI_FoldSplitContainer_Comp_0398', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性4')


      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '1'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0399', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性4')

      await radioClick({
        radioClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('level', JsonType.value),
        ],
        assertEqual: '2'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0400', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.level'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.level', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0598', 0, async (done: Function) => {

      let title = await driver.findComponent(ON.text('clickEffect.scale'))

      if (!title) {

        await Search('基础属性', 'clickEffect', '通用属性4')

        await radioClick({
          radioClickObj: 0,
          toggleClick: {
            toggleClickType: ToggleClick.Open,
          }
        })

      }

      await titleSearch('基础属性', 'clickEffect.scale', '通用属性4')

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clickEffect', JsonType.obj),
          new KeyStruct('scale', JsonType.value),
        ],
        assertEqual: '1.000000'
      })

      await Search('基础属性', 'clickEffect', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })


      done()
    })

    // accessibilityGroup
    it('ArkUI_FoldSplitContainer_Comp_0599', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: true
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0600', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityGroup', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityGroup', JsonType.value),
        ],
        assertEqual: false
      })

      done()
    })

    //accessibilityText
    it('ArkUI_FoldSplitContainer_Comp_0601', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '组件被选中时，仅播报无障碍文本内容'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0602', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityText', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityText', JsonType.value),
        ],
        assertEqual: '无障碍文本'
      })

      done()
    })

    // accessibilityDescription
    it('ArkUI_FoldSplitContainer_Comp_0603', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '用于为用户进一步说明当前组件'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0604', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityDescription', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityDescription', JsonType.value),
        ],
        assertEqual: '无障碍说明'
      })

      done()
    })

    // accessibilityLevel
    it('ArkUI_FoldSplitContainer_Comp_0605', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'yes'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0606', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性4')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0607', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性4')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'no-hide-descendants'
      })

      done()
    })
    it('ArkUI_FoldSplitContainer_Comp_0608', 0, async (done: Function) => {

      await titleSearch('基础属性', 'accessibilityLevel', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'accessibilityLevel'
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('accessibilityLevel', JsonType.value),
        ],
        assertEqual: 'auto'
      })

      done()
    })

    //responseRegion.value.x
    it('ArkUI_FoldSplitContainer_Comp_0633', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.x', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0634', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.y', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0635', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0636', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0637', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0638', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0639', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.width', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0640', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0641', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0642', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0643', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0644', 0, async (done: Function) => {
      //需要前置条件responseRegion.value.x、responseRegion.value.y、responseRegion.value.width、responseRegion.value.height四个toggle打开，获取不到参数值
      await titleSearch('基础属性', 'responseRegion.value.height', '通用属性5')
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
    it('ArkUI_FoldSplitContainer_Comp_0645', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性5')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0646', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性5')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0647', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性5')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0648', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性5')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.None'
      })
      done();
    })

    //bindContentCover.isShow
    /*
     * 测试组件bindContentCover.isShow支持设置true且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0649', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性6')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
     * 测试组件bindContentCover.isShow支持设置false且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0650', 0, async (done: Function) => {
      //无法获取属性
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性6')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    // bindContentCover.options.modalTransition
    /*
     * 测试组件bindContentCover.options.modalTransition支持设置DEAULT且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0651', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.modalTransition支持设置NONE且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0652', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性6')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.modalTransition支持设置ALPHA且获取属性正确
    */
    it('ArkUI_FoldSplitContainer_Comp_0653', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.modalTransition', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.modalTransition', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    //bindContentCover.options.transition.opacity
    it('ArkUI_FoldSplitContainer_Comp_0654', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.opacity', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.opacity', '通用属性6')
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
    //bindContentCover.options.transition.translate.x
    it('ArkUI_FoldSplitContainer_Comp_0655', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.x', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.x', '通用属性6')
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
    //bindContentCover.options.transition.translate.y
    it('ArkUI_FoldSplitContainer_Comp_0656', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.y', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.y', '通用属性6')
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
    //bindContentCover.options.transition.translate.z
    it('ArkUI_FoldSplitContainer_Comp_0657', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.translate.z', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.translate.z', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge_Comp_',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.x
    it('ArkUI_FoldSplitContainer_Comp_0658', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.x', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.x', '通用属性6')
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
    //bindContentCover.options.transition.scale.y
    it('ArkUI_FoldSplitContainer_Comp_0659', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.y', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.y', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.z
    it('ArkUI_FoldSplitContainer_Comp_0660', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.z', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.z', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.centerX
    it('ArkUI_FoldSplitContainer_Comp_0661', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerX', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerX', '通用属性6')
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
    //bindContentCover.options.transition.scale.centerY
    it('ArkUI_FoldSplitContainer_Comp_0662', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerY', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerY', '通用属性6')
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
    //bindContentCover.options.transition.rotate.x
    it('ArkUI_FoldSplitContainer_Comp_0663', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.x', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.x', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge_Comp',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.y
    it('ArkUI_FoldSplitContainer_Comp_0664', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.y', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.y', '通用属性6')
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
    //bindContentCover.options.transition.rotate.z
    it('ArkUI_FoldSplitContainer_Comp_0665', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.z', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.z', '通用属性6')
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
    //bindContentCover.options.transition.rotate.centerX
    it('ArkUI_FoldSplitContainer_Comp_0666', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerX', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerX', '通用属性6')
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
    //bindContentCover.options.transition.rotate.centerY
    it('ArkUI_FoldSplitContainer_Comp_0667', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerY', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerY', '通用属性6')
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
    //bindContentCover.options.transition.rotate.centerZ
    it('ArkUI_FoldSplitContainer_Comp_0668', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerZ', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerZ', '通用属性6')
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
    // bindContentCover.options.transition.rotate.perspective
    it('ArkUI_FoldSplitContainer_Comp_0669', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.perspective',
        '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.perspective', '通用属性6')
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
    //bindContentCover.options.transition.move
    /*
     * 测试组件bindContentCover.options.transition.move支持设置TOP且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0670', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置BOTTOM且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0671', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性6')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.transition.move支持设置START且获取属性正确
    */
    it('ArkUI_FoldSplitContainer_Comp_0672', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性6')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置END且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0673', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.duration
    it('ArkUI_FoldSplitContainer_Comp_0674', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.duration',
        '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.duration', '通用属性6')
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
    //bindContentCover.options.transition.animation.tempo
    it('ArkUI_FoldSplitContainer_Comp_0675', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.tempo', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.tempo', '通用属性6')
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
    //bindContentCover.options.transition.animation.curve
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Linear且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0676', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Ease且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0677', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseIn且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0678', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseOut且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0679', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseInOut且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0680', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutSlowIn且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0681', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置LinearOutSlowIn且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0682', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutLinearIn且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0683', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置ExtremeDeceleration且获取属性正确
     * */
    it('ArkUI_FoldSplitContainer_Comp_0684', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性6')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
  })
}