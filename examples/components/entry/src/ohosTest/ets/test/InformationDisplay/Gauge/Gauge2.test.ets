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
import { Driver } from '@kit.TestKit';
import {
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  searchParentBlock
} from '../../../utils';

import { GaugeStart } from './Gauge';

const driver = Driver.create();

export default function Gauge2() {
  describe('Gauge2', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await GaugeStart(done)

    })

    it('ArkUI_Gauge_Comp_0124', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds.bottom', false)
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
    it('ArkUI_Gauge_Comp_0125', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fBounds', false)
      done();

    })
    it('ArkUI_Gauge_Comp_0126', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fColors', false)
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0127', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fColors', true)
      await radioClick({
        radioClickObj: 1
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0128', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', true)
      await searchParentBlock('backgroundImageResizable.lattice.fColors', true)
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0129', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('backgroundImageResizable', true)
      await searchParentBlock('backgroundImageResizable.lattice', false)
      done();

    })
    it('ArkUI_Gauge_Comp_0130', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('backgroundImageResizable', false)
      done();

    })
    /**
     * 测试组件backgroundBrightness
     */
    it('ArkUI_Gauge_Comp_0131', 0, async (done: Function) => {
      await Search('基础属性', 'backgroundBrightness.rate');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpRate', JsonType.value)
        ],
        assertEqual: 5
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpRate', JsonType.value)
        ],
        assertEqual: 0
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0132', 0, async (done: Function) => {
      await Search('基础属性', 'backgroundBrightness.lightUpDegree');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpDegree', JsonType.value)
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('BackgroundBrightness', JsonType.obj),
          new KeyStruct('dynamicLightUpDegree', JsonType.value)
        ],
        assertEqual: -1
      })

      done();

    })
    /**
     * 测试组件opacity
     */
    it('ArkUI_Gauge_Comp_0133', 0, async (done: Function) => {
      await Search('基础属性', 'opacity');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('opacity', JsonType.value),
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('opacity', JsonType.value),
        ],
        assertEqual: 0
      })

      done();

    })
    /**
     * 测试组件aspectRatio且获取属性正确
     */
    it('ArkUI_Gauge_Comp_0134', 0, async (done: Function) => {
      await Search('基础属性', 'aspectRatio', '通用属性1');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('aspectRatio', JsonType.value)
        ],
        assertEqual: 5
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('aspectRatio', JsonType.value)
        ],
        assertEqual: ''
      })
      done();
    })
    /**
     * 测试开启pixelRound
     */
    it('ArkUI_Gauge_Comp_0135', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件pixelRound.start
     */
    it('ArkUI_Gauge_Comp_0136', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0137', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_CEIL","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0138', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_FLOOR","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    /**
     * 测试组件pixelRound.bottom
     */
    it('ArkUI_Gauge_Comp_0139', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0140', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_CEIL"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0141', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_FLOOR"}'
      })
      done();
    })

    /**
     * 测试组件pixelRound.top
     */
    it('ArkUI_Gauge_Comp_0142', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0143', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_CEIL","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0144', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_FLOOR","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件pixelRound.end
     */
    it('ArkUI_Gauge_Comp_0145', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0146', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', true);
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_CEIL","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_Gauge_Comp_0147', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_FLOOR","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    /**
     * 测试关闭pixelRound
     */
    it('ArkUI_Gauge_Comp_0148', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('pixelRound', false, '基础属性', '通用属性1')
      done();

      done();
    })
    /**
     * 测试开启borderImage
     */
    it('ArkUI_Gauge_Comp_0149', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启关闭borderImage.source
     */
    it('ArkUI_Gauge_Comp_0150', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.source', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0151', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.source', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.slice
     */
    it('ArkUI_Gauge_Comp_0152', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.slice.top
     */
    it('ArkUI_Gauge_Comp_0153', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [0.00px] right: [0.00px] top: [300.00vp] bottom: [0.00px]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.slice.bottom
     */
    it('ArkUI_Gauge_Comp_0154', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [0.00px] right: [0.00px] top: [0.00px] bottom: [300.00vp]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.slice.left
     */
    it('ArkUI_Gauge_Comp_0155', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [300.00vp] right: [0.00px] top: [0.00px] bottom: [0.00px]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.slice.right
     */
    it('ArkUI_Gauge_Comp_0156', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"left: [0.00px] right: [300.00vp] top: [0.00px] bottom: [0.00px]","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试关闭borderImage.slice
     */
    it('ArkUI_Gauge_Comp_0157', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.width
     */
    it('ArkUI_Gauge_Comp_0158', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.width.top
     */
    it('ArkUI_Gauge_Comp_0159', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [0.00px] right: [0.00px] top: [300.00vp] bottom: [0.00px]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.width.bottom
     */
    it('ArkUI_Gauge_Comp_0160', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [0.00px] right: [0.00px] top: [0.00px] bottom: [300.00vp]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.width.left
     */
    it('ArkUI_Gauge_Comp_0161', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [300.00vp] right: [0.00px] top: [0.00px] bottom: [0.00px]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.width.right
     */
    it('ArkUI_Gauge_Comp_0162', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"left: [0.00px] right: [300.00vp] top: [0.00px] bottom: [0.00px]","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试关闭borderImage.width
     */
    it('ArkUI_Gauge_Comp_0163', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.outset
     */
    it('ArkUI_Gauge_Comp_0164', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.outset.top
     */
    it('ArkUI_Gauge_Comp_0165', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [0.00px] right: [0.00px] top: [300.00vp] bottom: [0.00px]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.outset.bottom
     */
    it('ArkUI_Gauge_Comp_0166', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [0.00px] right: [0.00px] top: [0.00px] bottom: [300.00vp]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.outset.left
     */
    it('ArkUI_Gauge_Comp_0167', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [300.00vp] right: [0.00px] top: [0.00px] bottom: [0.00px]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件borderImage.outset.right
     */
    it('ArkUI_Gauge_Comp_0168', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"left: [0.00px] right: [300.00vp] top: [0.00px] bottom: [0.00px]","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试关闭borderImage.outset
     */
    it('ArkUI_Gauge_Comp_0169', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.repeat
     */
    it('ArkUI_Gauge_Comp_0170', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Repeat","fill":"false"}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0171', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0172', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Round","fill":"false"}'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0173', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Space","fill":"false"}'
      })

      done();

    })
    /**
     * 测试组件borderImage.fill
     */
    it('ArkUI_Gauge_Comp_0174', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0175', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试关闭borderImage
     */
    it('ArkUI_Gauge_Comp_0176', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件visibility
     */
    it('ArkUI_Gauge_Comp_0177', 0, async (done: Function) => {
      await searchParentBlock('visibility', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Visible'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0178', 0, async (done: Function) => {
      await searchParentBlock('visibility', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Hidden'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0179', 0, async (done: Function) => {
      await searchParentBlock('visibility', true, '基础属性', '通用属性1')
      // 组件没了，没有状态
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })
    /**
     * 测试组件enable
     */
    it('ArkUI_Gauge_Comp_0180', 0, async (done: Function) => {
      await searchParentBlock('enabled', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enabled', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0181', 0, async (done: Function) => {
      await searchParentBlock('enabled', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enabled', JsonType.value),
        ],
        assertEqual: false
      })

      done();
    })
    /**
     * 测试组件overlay
     */
    it('ArkUI_Gauge_Comp_0182', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0183', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0184', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.TopStart'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0185', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Top'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0186', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.TopEnd'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0187', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Start'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0188', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Center'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0189', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 5,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.End'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0190', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 6,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.BottomStart'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0191', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 7,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.Bottom'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0192', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('align', JsonType.value)
        ],
        assertEqual: 'Alignment.BottomEnd'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0193', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0194', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('overlay', JsonType.obj),
          new KeyStruct('options', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0195', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', false, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0196', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件zIndex
     */
    it('ArkUI_Gauge_Comp_0197', 0, async (done: Function) => {
      await searchParentBlock('zIndex', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('zIndex', JsonType.value),
        ],
        assertEqual: 100
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('zIndex', JsonType.value),
        ],
        assertEqual: -100
      })

      done();

    })
    /**
     * 测试组件rotate
     */
    it('ArkUI_Gauge_Comp_0198', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0199', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0200', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0201', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0202', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.angle', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '360.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_Gauge_Comp_0203', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0204', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0205', 0, async (done: Function) => {
      // 读取不到属性值
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerZ', false, '基础属性', '通用属性1')
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
    it('ArkUI_Gauge_Comp_0206', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.perspective', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0207', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件translate
     */
    it('ArkUI_Gauge_Comp_0208', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_Gauge_Comp_0209', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0210', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_Gauge_Comp_0211', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })


  })
}




