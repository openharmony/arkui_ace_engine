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
  getToggle,
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { MenuStart } from './Menu';


const driver = Driver.create();

export default function Menu4() {
  describe('Menu4', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await MenuStart(done)
    })
    // key
    it('ArkUI_Menu_Comp_0375', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'key', '通用属性4')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()

    })

    it('ArkUI_Menu_Comp_0376', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'key', '通用属性4')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // reuseId
    it('ArkUI_Menu_Comp_0377', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

    it('ArkUI_Menu_Comp_0378', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0379', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

    it('ArkUI_Menu_Comp_0380', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0381', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundEffect.radius', '通用属性5')

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

    // foregroundBlurStyle.value
    it('ArkUI_Menu_Comp_0382', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

    it('ArkUI_Menu_Comp_0383', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 1,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0384', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0385', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 3,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0386', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 4,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0387', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 5,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0388', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 6,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0389', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 7,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0390', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 8,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0391', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 9,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0392', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.value', '通用属性5')


      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 10,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0393', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0394', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

    it('ArkUI_Menu_Comp_0395', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'foregroundBlurStyle.options.colorMode', '通用属性5')

      // 取不到foregroundBlurStyle值
      await radioClick({
        radioClickObj: 2,
      })

      done()
    })

    it('ArkUI_Menu_Comp_0396', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0397', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

    it('ArkUI_Menu_Comp_0398', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0399', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0400', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0401', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'motionBlur.radius', '通用属性5')

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

    // motionBlur.anchorX
    it('ArkUI_Menu_Comp_0402', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'motionBlur.anchorX', '通用属性5')

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

    // motionBlur.anchorY
    it('ArkUI_Menu_Comp_0403', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'motionBlur.anchorY', '通用属性5')

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

    // clickEffect
    it('ArkUI_Menu_Comp_0404', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'clickEffect', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done()
    })

    it('ArkUI_Menu_Comp_0405', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0406', 0, async (done: Function) => {

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
      })

      done()
    })

    it('ArkUI_Menu_Comp_0407', 0, async (done: Function) => {

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
      })

      done()
    })

    it('ArkUI_Menu_Comp_0408', 0, async (done: Function) => {

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
      })

      done()
    })

    // clickEffect.scale
    it('ArkUI_Menu_Comp_0409', 0, async (done: Function) => {

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
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
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
    it('ArkUI_Menu_Comp_0410', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Menu_Comp_0411', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityGroup', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    //accessibilityText
    it('ArkUI_Menu_Comp_0412', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Menu_Comp_0413', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityText', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // accessibilityDescription
    it('ArkUI_Menu_Comp_0414', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_Menu_Comp_0415', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityDescription', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // accessibilityLevel
    it('ArkUI_Menu_Comp_0416', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'accessibilityLevel'
        },
      })

      done()
    })

    it('ArkUI_Menu_Comp_0417', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
      })

      done()
    })

    it('ArkUI_Menu_Comp_0418', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickObj: 'accessibilityLevel'
        },
      })

      done()
    })

    it('ArkUI_Menu_Comp_0419', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'accessibilityLevel', '通用属性5')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'accessibilityLevel'
        },
      })

      done()
    })

    // attributeModifier
    it('ArkUI_Menu_Comp_0420', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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

    it('ArkUI_Menu_Comp_0421', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_Menu_Comp_0422', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0423', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0424', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })

      await sliderDrag({
        slideStar: Slide.end,
      })
      done();
    })
    //outline.value.color
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_Menu_Comp_0425', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为2号色显示且获取属性正确
    */
    it('ArkUI_Menu_Comp_0426', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为3号色显示且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0427', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    /*
     * 测试组件outline.value.color支持设置量规图的颜色为4号色显示且获取属性正确
    */
    it('ArkUI_Menu_Comp_0428', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为5号色显示且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0429', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })
    /**
     * 测试组件outline.value.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_Menu_Comp_0430', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.color', '通用属性6')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    /*
     * outline.value.radius
    */
    it('ArkUI_Menu_Comp_0431', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.radius', '通用属性6')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,

        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })
    //outline.value.style
    /*
     * 测试组件outline.value.style支持设置SOLID且获取属性正确
    */
    it('ArkUI_Menu_Comp_0432', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DASHED且获取属性正确
    */
    it('ArkUI_Menu_Comp_0433', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    *测试组件outline.value.style支持设置DOTTED且获取属性正确
    */
    it('ArkUI_Menu_Comp_0434', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.style', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })
    /*
     * outline.value.width展开属性测试完成，关闭outline.value.width，无需断言
     * */
    it('ArkUI_Menu_Comp_0435', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'outline.value.width', '通用属性6')
      await getToggle(ToggleClick.Close)
      done();
    })
    // visualEffect
    /*
     *测试组件visualEffect支持设置true且获取属性正确
    */
    it('ArkUI_Menu_Comp_0436', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0437', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0438', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0439', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0440', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0441', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0442', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0443', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0444', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0445', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0446', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0447', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0448', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0449', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0450', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0451', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0452', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0453', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0454', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0455', 0, async (done: Function) => {
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
    it('ArkUI_Menu_Comp_0456', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Block且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0457', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Transparent且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0458', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置None且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0459', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
      })
      done();
    })
    // obscured
    /*
     * 测试组件obscured支持设置null且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0460', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件obscured支持设置PLACEHOLDER且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0461', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //renderFit
    /*
     * 测试组件renderFit支持设置CENTER且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0462', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0463', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0464', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置LEFT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0465', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RIGHT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0466', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0467', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_RIGHT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0468', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_LEFT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0469', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0470', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_FILL且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0471', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0472', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0473', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 11,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0474', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 12,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0475', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 13,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0476', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 14,
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0477', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 15,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    // monopolizeEvents
    /*
     * 测试组件monopolizeEvents支持设置true且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0478', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 0,
      })
      done();
    })
    /*
     * 测试组件monopolizeEvents支持设置false且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0479', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    //cursorControl
    /*
     * 测试组件cursorControl支持设置DEFAULT且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0480', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置EAST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0481', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0482', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0483', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0484', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST_EAST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0485', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_SOUTH且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0486', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0487', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0488', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0489', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0490', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST_SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0491', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST_SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0492', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 12
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CROSS且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0493', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 13
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_COPY且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0494', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 14
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CURSOR_FORBID且获取属性正确
     * */
    it('ArkUI_Menu_Comp_0495', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 15
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置COLOR_SUCKER且获取属性正确
     * */

  })

}