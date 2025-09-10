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

import { describe, beforeAll, it} from '@ohos/hypium'
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
} from '../../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';

export default function FoldSplitContainer1() {
  describe('FoldSplitContainer1', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })
    /**
     * 测试组件'expandedLayoutOptions.isExtraRegionPerpendicular'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_001', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.isExtraRegionPerpendicular')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.isExtraRegionPerpendicular'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_002', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.isExtraRegionPerpendicular')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.verticalSplitRatio'支持设置包含单个子组件为'LAYOUT_1V1'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_003', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.verticalSplitRatio')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.verticalSplitRatio'支持设置包含单个子组件为'LAYOUT_2V3'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_004', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.verticalSplitRatio')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.verticalSplitRatio'支持设置包含单个子组件为'LAYOUT_3V2'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_005', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.verticalSplitRatio')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.horizontalSplitRatio'支持设置包含单个子组件为'LAYOUT_1V1'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_006', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.horizontalSplitRatio')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.horizontalSplitRatio'支持设置包含单个子组件为'LAYOUT_2V3'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_007', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.horizontalSplitRatio')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.horizontalSplitRatio'支持设置包含单个子组件为'LAYOUT_3V2'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_008', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.horizontalSplitRatio')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.extraRegionPosition'支持设置包含单个子组件为'TOP'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_009', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.extraRegionPosition')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'expandedLayoutOptions.extraRegionPosition'支持设置包含单个子组件为'BOTTOM'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_010', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'expandedLayoutOptions.extraRegionPosition')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.showExtraRegion'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_011', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.showExtraRegion')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.showExtraRegion'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_012', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.showExtraRegion')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.horizontalSplitRatio'支持设置包含单个子组件为'LAYOUT_1V1'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_013', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.horizontalSplitRatio')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.horizontalSplitRatio'支持设置包含单个子组件为'LAYOUT_2V3'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_014', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.horizontalSplitRatio')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.horizontalSplitRatio'支持设置包含单个子组件为'LAYOUT_3V2'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_015', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.horizontalSplitRatio')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.extraRegionPosition'支持设置包含单个子组件为'TOP'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_016', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.extraRegionPosition')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'hoverModeLayoutOptions.extraRegionPosition'支持设置包含单个子组件为'BOTTOM'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_017', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'hoverModeLayoutOptions.extraRegionPosition')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'foldedLayoutOptions.verticalSplitRatio'支持设置包含单个子组件为'LAYOUT_1V1'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_018', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'foldedLayoutOptions.verticalSplitRatio')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'foldedLayoutOptions.verticalSplitRatio'支持设置包含单个子组件为'LAYOUT_2V3'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_019', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'foldedLayoutOptions.verticalSplitRatio')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'foldedLayoutOptions.verticalSplitRatio'支持设置包含单个子组件为'LAYOUT_3V2'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_020', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'foldedLayoutOptions.verticalSplitRatio')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.duration'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_021', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.duration')
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
      done();
    })

    /**
     * 测试组件'animationOptions.tempo'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_022', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.tempo')
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
      done();
    })

    /**
     * 测试组件'animationOptions.curve'支持设置包含单个子组件为'Linear'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_023', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.curve'支持设置包含单个子组件为'Ease'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_024', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'Ease'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_025', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'EaseOut'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_026', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'EaseInOut'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_027', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'FastOutSlowIn'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_028', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'LinearOutSlowIn'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_029', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'FastOutLinearIn'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_030', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'ExtremeDeceleration'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_031', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'Sharp'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_032', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'Rhythm'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_033', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'Smooth'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_034', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.EaseIn'支持设置包含单个子组件为'Friction'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_035', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.curve')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.delay'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_036', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.delay')
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
      done();
    })

    /**
     * 测试组件'animationOptions.iterations'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_037', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.iterations')
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
      done();
    })

    /**
     * 测试组件'animationOptions.playMode'支持设置包含单个子组件为'Normal'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_038', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.playMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.playMode'支持设置包含单个子组件为'Reverse'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_039', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.playMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.playMode'支持设置包含单个子组件为'Alternate'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_040', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.playMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.playMode'支持设置包含单个子组件为'AlternateReverse'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_041', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.playMode')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.finishCallbackType'支持设置包含单个子组件为'REMOVED'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_042', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.finishCallbackType')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.finishCallbackType'支持设置包含单个子组件为'LOGICALLY'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_043', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.finishCallbackType')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'animationOptions.expectedFrameRateRange.min'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_044', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.expectedFrameRateRange.min')
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
      done();
    })

    /**
     * 测试组件'animationOptions.expectedFrameRateRange.max'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_045', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.expectedFrameRateRange.max')
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
      done();
    })

    /**
     * 测试组件'animationOptions.expectedFrameRateRange.expected'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_046', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'animationOptions.expectedFrameRateRange.expected')
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
      done();
    })

    /**
     * 测试组件'flexBasis'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_047', 0, async (done: Function) => {
      await titleSearch('参数列表', 'flexBasis')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value),
        ],
        assertEqual: '200.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Auto'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_048', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Auto'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Ltr'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_049', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Ltr'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Rtl'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_050', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Rtl'
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'TopStart'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_051', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'Top'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_052', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'TopEnd'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_053', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'Start'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_054', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'Center'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_055', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'End'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_056', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'BottomStart'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_057', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'Bottom'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_058', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'background.align'支持设置包含单个子组件为'BottomEnd'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_059', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'background.align')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundColor'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_060', 0, async (done: Function) => {

      await titleSearch('参数列表', 'backgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })

    /**
     * 测试组件'backgroundColor'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_061', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

    /**
     * 测试组件'backgroundColor'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_062', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })

    /**
     * 测试组件'backgroundColor'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_063', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })

    /**
     * 测试组件'backgroundColor'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_064', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })


    /**
     * 测试组件'backgroundColor'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_065', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件'backgroundImage.src'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_066', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImage.src')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImage.src'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_067', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImage.src')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImage.repeat'支持设置包含单个子组件为'TopStart'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_068', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImage.repeat')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImage.repeat'支持设置包含单个子组件为'TopStart'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_069', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImage.repeat')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImage.repeat'支持设置包含单个子组件为'TopStart'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_070', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImage.repeat')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImage.repeat'支持设置包含单个子组件为'TopStart'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_071', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImage.repeat')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageSize'支持设置包含单个子组件为'Auto'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_072', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundImageSize')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Auto'
      })
      done();
    })

    /**
     * 测试组件'backgroundImageSize'支持设置包含单个子组件为'Cover'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_073', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundImageSize')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Cover'
      })
      done();
    })

    /**
     * 测试组件'backgroundImageSize'支持设置包含单个子组件为'Contain'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_074', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundImageSize')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.Contain'
      })
      done();
    })

    /**
     * 测试组件'backgroundImageSize'支持设置包含单个子组件为'FILL'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_075', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backgroundImageSize')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundImageSize', JsonType.value),
        ],
        assertEqual: 'ImageSize.FILL'
      })
      done();
    })

    /**
     * 测试组件'backgroundImagePosition.x'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_076', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImagePosition.x')
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
      done();
    })

    /**
     * 测试组件'backgroundImagePosition.y'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_077', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImagePosition.y')
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
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'Thin'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_078', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'Regular'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_079', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'Thick'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_080', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THIN'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_081', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_REGULAR'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_082', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_THICK'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_083', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'BACKGROUND_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_084', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'NONE'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_085', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THIN'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_086', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 6,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THIN'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_087', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 7,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THIN'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_088', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_REGULAR'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_089', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 9,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_THICK'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_090', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 10,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyle'支持设置包含单个子组件为'COMPONENT_ULTRA_THICK'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_091', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyle')
      await radioClick({
        radioClickObj: 11,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_092', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_093', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.colorMode'支持设置包含单个子组件为'SYSTEM'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_094', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.colorMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.colorMode'支持设置包含单个子组件为'LIGHT'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_095', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.colorMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.colorMode'支持设置包含单个子组件为'DARK'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_096', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.colorMode')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.adaptiveColor'支持设置包含单个子组件为'DEFAULT'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_097', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.adaptiveColor')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.adaptiveColor'支持设置包含单个子组件为'AVERAGE'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_098', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.adaptiveColor')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.blurOptions.left'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_099', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.blurOptions.left')
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
      done();
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.blurOptions.right'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_100', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.blurOptions.right')
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
      done();
    })
  })
}