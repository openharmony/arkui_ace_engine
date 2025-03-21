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
  Search,
  searchParentBlock
} from '../../utils';
import { FoldSplitContainerStart } from './FoldSplitContainer';
import { Driver, ON, Component } from '@kit.TestKit';

const driver = Driver.create();

export default function FoldSplitContainer3() {
  describe('FoldSplitContainer3', () => {
    beforeAll(async (done: Function) => {
      await FoldSplitContainerStart(done)
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

    /**
     * 测试组件'mask.color'支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_167', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.color')
      await buttonClick({
        buttonClickObj: 3,
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
     * 测试组件'mask.color'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_168', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.color')
      await buttonClick({
        buttonClickObj: 4,
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
     * 测试组件'mask.color'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_169', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
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
     * 测试组件'shadow.value.offsetX'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_170', 0, async (done: Function) => {
      await titleSearch('参数列表', 'shadow.value.offsetX')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
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
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();
    })

    /**
     * 测试组件'shadow.value.offsetY'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_171', 0, async (done: Function) => {
      await titleSearch('参数列表', 'shadow.value.offsetY')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('shadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
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
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '0.000000'
      })
      done();
    })

    /**
     * 测试组件'shadow.value.fill'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_172', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.fill')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'shadow.value.fill'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_173', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'shadow.value.fill')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'grayscale'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_174', 0, async (done: Function) => {
      await titleSearch('参数列表', 'grayscale')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value),
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('grayscale', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'brightness'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_175', 0, async (done: Function) => {
      await titleSearch('参数列表', 'brightness')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value),
        ],
        assertEqual: 2
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('brightness', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'saturate'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_176', 0, async (done: Function) => {
      await titleSearch('参数列表', 'saturate')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value),
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('saturate', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'contrast'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_177', 0, async (done: Function) => {
      await titleSearch('参数列表', 'contrast')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value),
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contrast', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'invert'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_178', 0, async (done: Function) => {
      await titleSearch('参数列表', 'invert')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value),
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('invert', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'sepia'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_179', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sepia')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value),
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sepia', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'hueRotate'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_180', 0, async (done: Function) => {
      await titleSearch('参数列表', 'hueRotate')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value),
        ],
        assertEqual: 50
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hueRotate', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'colorBlend'支持设置量规图的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_181', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colorBlend')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'colorBlend'支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_182', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colorBlend')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'colorBlend'支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_183', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'colorBlend')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'colorBlend支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_184', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'colorBlend')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'colorBlend'支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_185', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'colorBlend')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件'colorBlend'支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_186', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'colorBlend')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('colorBlend', JsonType.value),
        ],
        assertEqual: ''
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })

    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })

    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试开启constraintSize
     */
    it('ArkUI_FoldSplitContainer_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })
      done();
    })

    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })
      done();
    })

    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })
      done();
    })

    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })
      done();
    })

    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_FoldSplitContainer_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })

    /**
     * 测试开启position
     */
    it('ArkUI_FoldSplitContainer_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
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
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
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
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0014', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
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
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0015', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
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
     * 测试关闭position
     */
    it('ArkUI_FoldSplitContainer_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })

    /**
     * 测试开启markAnchor
     */
    it('ArkUI_FoldSplitContainer_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0018', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    /**
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0019', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    /**
     * 测试关闭markAnchor
     */
    it('ArkUI_FoldSplitContainer_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })

    /**
     * 测试开启offset
     */
    it('ArkUI_FoldSplitContainer_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })

    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0022', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    /**
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_FoldSplitContainer_Comp_0023', 0, async (done: Function) => {
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.y');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('offset', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

    /**
     * 测试关闭offset
     */
    it('ArkUI_FoldSplitContainer_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);

      done();
    })

    /**
     * 测试组件borderStyle
     */
    it('ArkUI_FoldSplitContainer_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0027', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Solid'
      })
      done();
    })

    /**
     * 测试组件borderWidth
     */
    it('ArkUI_FoldSplitContainer_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '20.00vp'
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
        assertEqual: '0.00vp'
      })

      done();

    })

    /**
     * 测试组件borderColor
     */
    it('ArkUI_FoldSplitContainer_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0034', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件borderRadius
     */
    it('ArkUI_FoldSplitContainer_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
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
     * 测试组件opacity
     */
    it('ArkUI_FoldSplitContainer_Comp_0036', 0, async (done: Function) => {
      await Search('基础属性', 'opacity');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0037', 0, async (done: Function) => {
      await Search('基础属性', 'aspectRatio', '通用属性1');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
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
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0038', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      done();
    })

    /**
     * 测试组件pixelRound.start
     */
    it('ArkUI_FoldSplitContainer_Comp_0039', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0040', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', true);
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.FORCE_CEIL","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0041', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.start', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0042', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0043', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', true);
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.FORCE_CEIL"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0044', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.bottom', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0045', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0046', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', true);
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_CEIL","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0047', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.top', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.FORCE_FLOOR","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件pixelRound.end
     */
    it('ArkUI_FoldSplitContainer_Comp_0048', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', false);
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.NO_FORCE_ROUND","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0049', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', true);
      await radioClick({
        radioClickObj: 1,
        id: 'FoldSplitContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('pixelRound', JsonType.value)
        ],
        assertEqual: '{"start":"PixelRoundCalcPolicy.NO_FORCE_ROUND","top":"PixelRoundCalcPolicy.NO_FORCE_ROUND","end":"PixelRoundCalcPolicy.FORCE_CEIL","bottom":"PixelRoundCalcPolicy.NO_FORCE_ROUND"}'
      })
      done();
    })
    it('ArkUI_FoldSplitContainer_Comp_0050', 0, async (done: Function) => {
      await searchParentBlock('pixelRound', true, '基础属性', '通用属性1')
      await searchParentBlock('pixelRound.end', true);
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'FoldSplitContainer',
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
    it('ArkUI_FoldSplitContainer_Comp_0051', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('pixelRound', false, '基础属性', '通用属性1')
      done();

      done();
    })

    /**
     * 测试开启borderImage
     */
    it('ArkUI_FoldSplitContainer_Comp_0052', 0, async (done: Function) => {
      // 无断言
      await searchParentBlock('borderImage', true, '基础属性', '通用属性1')
      done();
    })
  })
}