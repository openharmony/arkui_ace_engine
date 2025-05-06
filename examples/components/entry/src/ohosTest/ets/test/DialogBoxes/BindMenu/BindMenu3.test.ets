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
  radioClick,
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { BindMenuStart } from './BindMenu';


const driver = Driver.create();

export default function BindMenu3() {
  describe('BindMenu3', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await BindMenuStart(done)
    })
    /**
     * 测试组件clip
     */
    it('ArkUI_MenuItem_Comp_0222', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('clip', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0223', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('clip', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件clipShape
     */
    it('ArkUI_MenuItem_Comp_0224', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_MenuItem_Comp_0225', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      await searchParentBlock('clipShape.width', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0226', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      await searchParentBlock('clipShape.height', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0227', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件mask
     */
    it('ArkUI_MenuItem_Comp_0228', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_MenuItem_Comp_0229', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.value', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0230', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', false, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0231', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0232', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0233', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0234', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0235', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0236', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件maskShape
     */
    it('ArkUI_MenuItem_Comp_0237', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_MenuItem_Comp_0238', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      await searchParentBlock('maskShape.width', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0239', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      await searchParentBlock('maskShape.height', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0240', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件blur
     */
    it('ArkUI_MenuItem_Comp_0241', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('基础属性', 'blur.value', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0242', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('基础属性', 'blur.options.grayscale.number1', '通用属性2');
      // 读取不到
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0243', 0, async (done: Function) => {
      // 读取不到
      await Search('基础属性', 'blur.options.grayscale.number2', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();
    })
    /**
     * 测试组件shadow
     */
    it('ArkUI_MenuItem_Comp_0244', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.radius', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0245', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.type', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0246', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.type', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0247', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.color', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0248', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0249', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0250', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0251', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0252', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0253', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.offsetX', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0254', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.offsetY', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0255', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.fill', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })
      done();
    })
    it('ArkUI_MenuItem_Comp_0256', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('shadow.value.fill', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    /**
     * 测试组件grayscale
     */
    it('ArkUI_MenuItem_Comp_0257', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('grayscale', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件brightness
     */
    it('ArkUI_MenuItem_Comp_0258', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('brightness', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件saturate
     */
    it('ArkUI_MenuItem_Comp_0259', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('saturate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件contrast
     */
    it('ArkUI_MenuItem_Comp_0260', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('contrast', false, '基础属性', '通用属性2')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件invert
     */
    it('ArkUI_MenuItem_Comp_0261', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('invert', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件sepia
     */
    it('ArkUI_MenuItem_Comp_0262', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('sepia', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件hueRotate
     */
    it('ArkUI_MenuItem_Comp_0263', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('hueRotate', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件colorBlend
     */
    it('ArkUI_MenuItem_Comp_0264', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('colorBlend', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0265', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0266', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0267', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0268', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0269', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('colorBlend', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    /**
     * 测试组件linearGradientBlur
     */
    it('ArkUI_MenuItem_Comp_0270', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.value', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0271', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.fractionStops', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0272', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0273', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.fractionStops', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0274', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0275', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0276', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0277', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0278', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0279', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0280', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0281', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0282', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('linearGradientBlur.options.direction', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,

        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    // renderGroup
    it('ArkUI_MenuItem_Comp_0283', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('renderGroup', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0284', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('renderGroup', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();

    })
    // blendMode
    it('ArkUI_MenuItem_Comp_0285', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0286', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0287', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0288', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 3,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0289', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 4,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0290', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 5,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0291', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 6,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0292', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 7,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0293', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 8,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0294', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 9,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0295', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 10,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0296', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 11,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0297', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 12,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0298', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 13,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0299', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 14,
      })
      done();

    })
    it('ArkUI_MenuItem_Comp_0300', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 15,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0301', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 16,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0302', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 17,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0303', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 18,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0304', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 19,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0305', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 20,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0306', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 21,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0307', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 22,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0308', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 23,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0309', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 24,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0310', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 25,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0311', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 26,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0312', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 27,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0313', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 28,
      })

      done();

    })
    it('ArkUI_MenuItem_Comp_0314', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('blendMode.value', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 'LUMINOSITY',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      }, 'blendMode.value', '基础属性', '通用属性2')
      done();


    })

    it('ArkUI_MenuItem_Comp_0315', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'blendMode.type', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_MenuItem_Comp_0316', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('基础属性', 'blendMode.type', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_MenuItem_Comp_0317', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('useShadowBatching', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })
      done();

    })
    it('ArkUI_MenuItem_Comp_0318', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('useShadowBatching', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();

    })
    // sphericalEffect
    it('ArkUI_MenuItem_Comp_0319', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('sphericalEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    //   lightUpEffect
    it('ArkUI_MenuItem_Comp_0320', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('lightUpEffect', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    //   pixelStretchEffect
    it('ArkUI_MenuItem_Comp_0321', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('pixelStretchEffect.options.left', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0322', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('pixelStretchEffect.options.right', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0323', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('pixelStretchEffect.options.top', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    it('ArkUI_MenuItem_Comp_0324', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await searchParentBlock('pixelStretchEffect.options.bottom', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    //   freeze
    it('ArkUI_MenuItem_Comp_0325', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('freeze', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })

    it('ArkUI_MenuItem_Comp_0326', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('freeze', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })

    // linearGradient
    // linearGradient.angle
    it('ArkUI_MenuItem_Comp_0327', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.angle', '通用属性3')

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

    // linearGradient.direction
    it('ArkUI_MenuItem_Comp_0328', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 0,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0329', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 1,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0330', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 2,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0331', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 3,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0332', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 4,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0333', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 5,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0334', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 6,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0335', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 7,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0336', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.direction', '通用属性3')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    //linearGradient.color1
    it('ArkUI_MenuItem_Comp_0337', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0338', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0339', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0340', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0341', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0342', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color1', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // linearGradient.number1
    it('ArkUI_MenuItem_Comp_0343', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0344', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0345', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0346', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0347', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0348', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0349', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.color2', '通用属性3')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // linearGradient.number2
    it('ArkUI_MenuItem_Comp_0350', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0351', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_MenuItem_Comp_0352', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'linearGradient.repeating', '通用属性3')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    //focusable
    it('ArkUI_MenuItem_Comp_0353', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'focusable', '通用属性3')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_MenuItem_Comp_0354', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'focusable', '通用属性3')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done()
    })

    // defaultFocus
    it('ArkUI_MenuItem_Comp_0355', 0, async (done: Function) => {
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

    it('ArkUI_MenuItem_Comp_0356', 0, async (done: Function) => {
      // 无法取到属性值进行断言
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
    it('ArkUI_MenuItem_Comp_0357', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })

    it('ArkUI_MenuItem_Comp_0358', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'groupDefaultFocus', '通用属性3')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done()
    })
    // focusOnTouch
    it('ArkUI_MenuItem_Comp_0359', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done()
    })
    it('ArkUI_MenuItem_Comp_0360', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await titleSearch('基础属性', 'focusOnTouch', '通用属性3')

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