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
} from '../../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';

export default function FoldSplitContainer2() {
  describe('FoldSplitContainer2', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
    })

    /**
     * 测试组件'backgroundBlurStyleParams.options.params.scale'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_101', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundBlurStyleParams.options.params.scale')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
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
     * 测试组件'backdropBlur'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_102', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backdropBlur')
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
     * 测试组件'backdropBlur.options.grayscale'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_103', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backdropBlur.options.grayscale')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backdropBlur.options.grayscale'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_104', 0, async (done: Function) => {
      await titleSearch('参数列表', 'backdropBlur.options.grayscale')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backdropBlur.options.grayscale.left'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_105', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backdropBlur.options.grayscale')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backdropBlur.options.grayscale.left')
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
     * 测试组件'backdropBlur.options.grayscale.right'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_106', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backdropBlur.options.grayscale')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backdropBlur.options.grayscale.right')
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
     * 测试组件'backgroundEffect'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_107', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_108', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.radius'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_109', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.radius')
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
     * 测试组件'backgroundEffect.saturation'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_110', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.saturation')
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
     * 测试组件'backgroundEffect.brightness'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_111', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.brightness')
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
     * 测试组件'backgroundEffect.color'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_112', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.color')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.color'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_113', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.color'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_114', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.color'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_115', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.color'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_116', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.color'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_117', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.adaptiveColor'支持设置包含单个子组件为'DEFAULT'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_118', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.adaptiveColor')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.adaptiveColor'支持设置包含单个子组件为'DEFAULT'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_119', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.adaptiveColor')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundEffect.blurOptions.grayscale.left'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_120', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.blurOptions.grayscale.left')
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
     * 测试组件'backgroundEffect.blurOptions.grayscale.right'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_121', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundEffect')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundEffect.blurOptions.grayscale.right')
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
     * 测试组件'backgroundImageResizable'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_122', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageResizable'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_123', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageResizable.slice.top'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_124', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.slice.top')
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
     * 测试组件'backgroundImageResizable.slice.bottom'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_125', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.slice.bottom')
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
     * 测试组件'backgroundImageResizable.slice.left'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_126', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.slice.left')
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
     * 测试组件'backgroundImageResizable.slice.right'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_127', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.slice.right')
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
     * 测试组件'backgroundImageResizable.lattice'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_128', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_129', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.xDivs'支持设置包含单个子组件为'[1, 2, 3]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_130', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.xDivs')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.xDivs'支持设置包含单个子组件为'[3, 4, 5]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_131', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.xDivs')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.xDivs'支持设置包含单个子组件为'[5, 6, 3]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_132', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.xDivs')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.yDivs'支持设置包含单个子组件为'[1, 2, 3]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_133', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.yDivs')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.yDivs'支持设置包含单个子组件为'[3, 4, 5]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_134', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.yDivs')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.yDivs'支持设置包含单个子组件为'[5, 6, 3]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_135', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.yDivs')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.fXCount'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_136', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fXCount')
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
     * 测试组件'backgroundImageResizable.lattice.fYCount'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_137', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fYCount')
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
     * 测试组件'backgroundImageResizable.lattice.fBounds'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_138', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fBounds')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.fBounds'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_139', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fBounds')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.fYCount.left'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_140', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fBounds')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fYCount.left')
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
     * 测试组件'backgroundImageResizable.lattice.fYCount.top'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_141', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fBounds')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fYCount.top')
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
     * 测试组件'backgroundImageResizable.lattice.fYCount.right'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_142', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fBounds')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fYCount.right')
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
     * 测试组件'backgroundImageResizable.lattice.fYCount.bottom'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_143', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fBounds')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fYCount.bottom')
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
     * 测试组件'backgroundImageResizable.lattice.fColors'支持设置包含单个子组件为'[{alpha:0,red:0,green:0,blue:0}]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_144', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fColors')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.fColors'支持设置包含单个子组件为'[{alpha:100,red:100,green:100,blue:100}]'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_145', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fColors')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'backgroundImageResizable.lattice.fColors'支持设置包含单个子组件为'[{alpha:255,red:255,green:255,blue:255}]''且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_146', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'backgroundImageResizable')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await titleSearch('参数列表', 'backgroundImageResizable.lattice.fColors')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'clip'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_147', 0, async (done: Function) => {
      await titleSearch('参数列表', 'clip')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件'clip'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_148', 0, async (done: Function) => {
      await titleSearch('参数列表', 'clip')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件'mask'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_149', 0, async (done: Function) => {
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件'mask'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_150', 0, async (done: Function) => {
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件'mask.value'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_151', 0, async (done: Function) => {
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.value')
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
     * 测试组件'mask.color'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_152', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_153', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_154', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_155', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.color')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_156', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.color')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_157', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'mask')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('mask', JsonType.value),
        ],
        assertEqual: 'true'
      })

      await titleSearch('参数列表', 'mask.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'blur.value'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_158', 0, async (done: Function) => {
      await titleSearch('参数列表', 'blur.value')
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
     * 测试组件'blur.options.grayscale.number1'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_159', 0, async (done: Function) => {
      await titleSearch('参数列表', 'blur.options.grayscale.number1')
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
     * 测试组件'blur.options.grayscale.number2'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_160', 0, async (done: Function) => {
      await titleSearch('参数列表', 'blur.options.grayscale.number2')
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
     * 测试组件'shadow.value.radius'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_161', 0, async (done: Function) => {
      await titleSearch('参数列表', 'shadow.value.radius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
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
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();
    })

    /**
     * 测试组件'shadow.value.type'支持设置包含单个子组件为'COLOR'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_162', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.type')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'shadow.value.type'支持设置包含单个子组件为'BLUR'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_163', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.type')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'shadow.value.color'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_164', 0, async (done: Function) => {
      await titleSearch('参数列表', 'shadow.value.color')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'shadow.value.color'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_165', 0, async (done: Function) => {
      await titleSearch('参数列表', 'shadow.value.color')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_166', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.color')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('color', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })
  })
}