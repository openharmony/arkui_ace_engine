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
  searchParentBlock,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
} from '../../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';

export default function FoldSplitContainer4() {
  describe('FoldSplitContainer4', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })

    /**
     * 测试开启关闭borderImage.source
     */
    it('ArkUI_FoldSplitContainer_Comp_0053', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.source', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0054', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.source', false, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试开启borderImage.slice
     */
    it('ArkUI_FoldSplitContainer_Comp_0055', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件borderImage.slice.top
     */
    it('ArkUI_FoldSplitContainer_Comp_0056', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0057', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0058', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0059', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0060', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.slice', false, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试开启borderImage.width
     */
    it('ArkUI_FoldSplitContainer_Comp_0061', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件borderImage.width.top
     */
    it('ArkUI_FoldSplitContainer_Comp_0062', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0063', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0064', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0065', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0066', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.width', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试开启borderImage.outset
     */
    it('ArkUI_FoldSplitContainer_Comp_0067', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件borderImage.outset.top
     */
    it('ArkUI_FoldSplitContainer_Comp_0068', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.top', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0069', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.bottom', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0070', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.left', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0071', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset.right', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0072', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.outset', false, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件borderImage.repeat
     */
    it('ArkUI_FoldSplitContainer_Comp_0073', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Repeat","fill":"false"}'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0074', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Stretch","fill":"false"}'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0075', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderImage', JsonType.value),
        ],
        assertEqual: '{"source":"","slice":"0.00vp","width":"0.00vp","outset":"0.00vp","repeat":"RepeatMode.Round","fill":"false"}'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0076', 0, async (done: Function) => {
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.repeat', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0077', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0078', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      await searchParentBlock('borderImage.fill', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试关闭borderImage
     */
    it('ArkUI_FoldSplitContainer_Comp_0079', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件visibility
     */
    it('ArkUI_FoldSplitContainer_Comp_0080', 0, async (done: Function) => {
      await searchParentBlock('visibility', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Visible'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0081', 0, async (done: Function) => {
      await searchParentBlock('visibility', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Hidden'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0082', 0, async (done: Function) => {
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
    it('ArkUI_FoldSplitContainer_Comp_0083', 0, async (done: Function) => {
      await searchParentBlock('enabled', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enabled', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0181', 0, async (done: Function) => {
      await searchParentBlock('enabled', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0084', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0085', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0086', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', false, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0087', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0088', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 2,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0089', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 3,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0090', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 4,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0091', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 5,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0092', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 6,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0093', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 7,
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0094', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.align', true, '基础属性', '通用属性1')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0095', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0096', 0, async (done: Function) => {
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options.offset.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0097', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', true, '基础属性', '通用属性1')
      await searchParentBlock('overlay.options', false, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0098', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('overlay', false, '基础属性', '通用属性1')
      done();
    })
    /**
     * 测试组件zIndex
     */
    it('ArkUI_FoldSplitContainer_Comp_0099', 0, async (done: Function) => {
      await searchParentBlock('zIndex', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0100', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0101', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0102', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0103', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0104', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.angle', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0105', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0106', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '50.00%'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0107', 0, async (done: Function) => {
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
    it('ArkUI_FoldSplitContainer_Comp_0108', 0, async (done: Function) => {
      await searchParentBlock('rotate', true, '基础属性', '通用属性1')
      await searchParentBlock('rotate.perspective', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('rotate', JsonType.obj),
          new KeyStruct('perspective', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0109', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('rotate', false, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件translate
     */
    it('ArkUI_FoldSplitContainer_Comp_0110', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0111', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0112', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0113', 0, async (done: Function) => {
      await searchParentBlock('translate', true, '基础属性', '通用属性1')
      await searchParentBlock('translate.z', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('translate', JsonType.obj),
          new KeyStruct('z', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0114', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('translate', false, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件scale
     */
    it('ArkUI_FoldSplitContainer_Comp_0115', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0116', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.x', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('x', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0117', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.y', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('y', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0118', 0, async (done: Function) => {
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
    it('ArkUI_FoldSplitContainer_Comp_0119', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerX', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerX', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0120', 0, async (done: Function) => {
      await searchParentBlock('scale', true, '基础属性', '通用属性1')
      await searchParentBlock('scale.centerY', false, '基础属性', '通用属性1')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scale', JsonType.obj),
          new KeyStruct('centerY', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0121', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('scale', false, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件transform
     */
    it('ArkUI_FoldSplitContainer_Comp_0122', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', true, '基础属性', '通用属性1')
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0123', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('transform', false, '基础属性', '通用属性1')
      done();
    })
    // linearGradient
    // linearGradient.angle
    it('ArkUI_FoldSplitContainer_Comp_0124', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.angle', '通用属性2')

      await sliderDrag({
        slideStar: Slide.start,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '360.00px'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('angle', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();
    })

    // linearGradient.direction
    it('ArkUI_FoldSplitContainer_Comp_0125', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 0,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Left'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0126', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Top'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0127', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Right'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0128', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 3,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.Bottom'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0129', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 4,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftTop'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0130', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 5,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.LeftBottom'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0131', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 6,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightTop'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0132', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 7,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.RightBottom'
      })

      done();

    })
    it('ArkUI_FoldSplitContainer_Comp_0133', 0, async (done: Function) => {

      await titleSearch('基础属性', 'linearGradient.direction', '通用属性2')

      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('linearGradient', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'GradientDirection.None'
      })

      done();

    })
  })
}