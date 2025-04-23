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
  Search,
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { AlphabetIndexerStart } from './AlphabetIndexer';

const driver = Driver.create();

export default function AlphabetIndexer4Test() {
  describe('AlphabetIndexer4Test', () => {
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      await AlphabetIndexerStart(done)

    })
    /**
     * 测试开启borderImage.outset
     */
    it('ArkUI_AlphabetIndexer_Comp_0164', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.outset.top
     */
    it('ArkUI_AlphabetIndexer_Comp_0165', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0166', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0167', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0168', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0169', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.repeat
     */
    it('ArkUI_AlphabetIndexer_Comp_0170', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Repeat","fill":"false"}'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0171', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0172', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Round","fill":"false"}'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0173', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0174', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0175', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试关闭borderImage
     */
    it('ArkUI_AlphabetIndexer_Comp_0176', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件visibility
     */
    it('ArkUI_AlphabetIndexer_Comp_0177', 0, async (done: Function) => {
      await searchParentBlock('visibility', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Visible'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0178', 0, async (done: Function) => {
      await searchParentBlock('visibility', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Hidden'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0179', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0180', 0, async (done: Function) => {
      await searchParentBlock('enabled', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enabled', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0181', 0, async (done: Function) => {
      await searchParentBlock('enabled', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0182', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0183', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0184', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0185', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0186', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0187', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0188', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 4,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0189', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 5,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0190', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 6,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0191', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 7,
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0192', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0193', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0194', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0195', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', false, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0196', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件zIndex
     */
    it('ArkUI_AlphabetIndexer_Comp_0197', 0, async (done: Function) => {
      await searchParentBlock('zIndex', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
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
    it('ArkUI_AlphabetIndexer_Comp_0198', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0199', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0200', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0201', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0202', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.angle', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0203', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0204', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0205', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0206', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.perspective', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0207', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件translate
     */
    it('ArkUI_AlphabetIndexer_Comp_0208', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0209', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0210', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0211', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
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
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0212', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件scale
     */
    it('ArkUI_AlphabetIndexer_Comp_0213', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0214', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '300.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    it('ArkUI_AlphabetIndexer_Comp_0215', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '300.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })

    it('ArkUI_AlphabetIndexer_Comp_0216', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.z', false, '基础属性', '通用属性1')
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
    it('ArkUI_AlphabetIndexer_Comp_0217', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0218', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '300.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0219', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件transform
     */
    it('ArkUI_AlphabetIndexer_Comp_0220', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0221', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件clip
     */
    it('ArkUI_AlphabetIndexer_Comp_0222', 0, async (done: Function) => {
      await searchParentBlock('clip', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0223', 0, async (done: Function) => {
      await searchParentBlock('clip', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })
    /**
     * 测试组件clipShape
     */
    it('ArkUI_AlphabetIndexer_Comp_0224', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0225', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0226', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0227', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('clipShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件mask
     */
    it('ArkUI_AlphabetIndexer_Comp_0228', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0229', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0230', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0231', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0232', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0233', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0234', 0, async (done: Function) => {
      //读取不到
      await searchParentBlock('mask', true, '基础属性', '通用属性1')
      await searchParentBlock('mask.color', true, '基础属性', '通用属性1')
      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0235', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0236', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('mask', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件maskShape
     */
    it('ArkUI_AlphabetIndexer_Comp_0237', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0238', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0239', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0240', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('maskShape', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件blur
     */
    it('ArkUI_AlphabetIndexer_Comp_0241', 0, async (done: Function) => {
      await Search('基础属性', 'blur.value', '通用属性2');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('blur', JsonType.value),
        ],
        assertEqual: 0
      })

      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0242', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0243', 0, async (done: Function) => {
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
    it('ArkUI_AlphabetIndexer_Comp_0244', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.radius', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0245', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0246', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.type', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0247', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', false, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0248', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 1,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0249', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 2,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0250', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 3,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0251', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 4,
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0252', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.color', true, '基础属性', '通用属性2')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    it('ArkUI_AlphabetIndexer_Comp_0253', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetX', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0254', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.offsetY', false, '基础属性', '通用属性2')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0255', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', false, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '1'
      })
      done();
    })
    it('ArkUI_AlphabetIndexer_Comp_0256', 0, async (done: Function) => {
      await searchParentBlock('shadow.value.fill', true, '基础属性', '通用属性2')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'AlphabetIndexer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('fill', JsonType.value)
        ],
        assertEqual: '0'
      })
      done();
    })
  })
}