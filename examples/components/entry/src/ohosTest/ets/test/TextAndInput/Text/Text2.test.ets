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

import { beforeAll, describe, it } from '@ohos/hypium';
import { Driver, ON } from '@kit.TestKit';
import { Component } from '@ohos.UiTest';
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
import { TextStart } from './Text.test';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function Text2Test() {
  describe('Text2Test', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await TextStart(done);
    })

    /*
        * 测试组件lineBreakStrategy支持设置HIGH_QUALITY且获取属性正确
        */
    it('ArkUI_Text_110', 0, async (done: Function) => {
      await Search('参数列表', 'lineBreakStrategy')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineBreakStrategy', JsonType.value)
        ],
        assertEqual: 'high-quality'
      })
      done();
    })
    /*
     * 测试组件lineBreakStrategy支持设置BALANCED且获取属性正确
     */
    it('ArkUI_Text_111', 0, async (done: Function) => {
      await Search('参数列表', 'lineBreakStrategy')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('lineBreakStrategy', JsonType.value)
        ],
        assertEqual: 'balanced'
      })
      done();
    })
    //textSelectable
    /*
     * 测试组件textSelectable支持设置SELECTABLE_UNFOCUSABLE且获取属性正确
     */
    it('ArkUI_Text_112', 0, async (done: Function) => {
      await Search('参数列表', 'textSelectable')
      await radioClick({
        radioClickObj: 0,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textSelectable', JsonType.value)
        ],
        assertEqual: 'selectable-unfocusable'
      })
      done();
    })
    /*
     * 测试组件textSelectable支持设置SELECTABLE_FOCUSABLE且获取属性正确
     */
    it('ArkUI_Text_113', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textSelectable')
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textSelectable', JsonType.value)
        ],
        assertEqual: 'selectable-focusable'
      })
      done();
    })
    /*
     * 测试组件textSelectable支持设置UNSELECTABLE且获取属性正确
     */
    it('ArkUI_Text_114', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'textSelectable')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('textSelectable', JsonType.value)
        ],
        assertEqual: 'unselectable'
      })
      done();
    })
    //minFontScale
    it('ArkUI_Text_115', 0, async (done: Function) => {
      await Search('参数列表', 'minFontScale')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontScale', JsonType.value)
        ],
        assertEqual: '1.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minFontScale', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done()
    })
    //maxFontScale
    it('ArkUI_Text_116', 0, async (done: Function) => {
      await Search('参数列表', 'maxFontScale')
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontScale', JsonType.value)
        ],
        assertEqual: '200.000000'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxFontScale', JsonType.value)
        ],
        assertEqual: '1.000000'
      })
      done()
    })
    //halfLeading
    /*
     * 测试组件halfLeading支持设置false且获取属性正确
     */
    it('ArkUI_Text_117', 0, async (done: Function) => {
      await Search('参数列表', 'halfLeading')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件halfLeading支持设置true且获取属性正确
     */
    it('ArkUI_Text_118', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'halfLeading')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //fontFeature
    /**
     * 测试组件fontFeature支持设置文字特性效果为normal
     */
    it('ArkUI_Text_119', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss01'on
     */
    it('ArkUI_Text_120', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss01"off
     */
    it('ArkUI_Text_121', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss02'on
     */
    it('ArkUI_Text_122', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss02"off
     */
    it('ArkUI_Text_123', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss03'on
     */
    it('ArkUI_Text_124', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss03"off
     */
    it('ArkUI_Text_125', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss04'on
     */
    it('ArkUI_Text_126', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss04"off
     */
    it('ArkUI_Text_127', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss05'on
     */
    it('ArkUI_Text_128', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss05"off
     */
    it('ArkUI_Text_129', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss08'on
     */
    it('ArkUI_Text_130', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss08"off
     */
    it('ArkUI_Text_131', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 12
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss09'on
     */
    it('ArkUI_Text_132', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 13
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss09"off
     */
    it('ArkUI_Text_133', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 14
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss10'on
     */
    it('ArkUI_Text_134', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 15
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss10"off
     */
    it('ArkUI_Text_135', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 16
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'frac'on
     */
    it('ArkUI_Text_136', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 17
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "frac"off
     */
    it('ArkUI_Text_137', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 18
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'sups'on
     */
    it('ArkUI_Text_138', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 19
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "sups"off
     */
    it('ArkUI_Text_139', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 20
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'subs'on
     */
    it('ArkUI_Text_140', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 21
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "subs"off
     */
    it('ArkUI_Text_141', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 22
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'numr'on
     */
    it('ArkUI_Text_142', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 23
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "numr"off
     */
    it('ArkUI_Text_143', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 24
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'dnom'on
     */
    it('ArkUI_Text_144', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 25
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "dnom"off
     */
    it('ArkUI_Text_145', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 26
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'case'on
     */
    it('ArkUI_Text_146', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: 27
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "case"off
     */
    it('ArkUI_Text_147', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"case" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'tnum'on
     */
    it('ArkUI_Text_148', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"tnum" on'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "tnum"off
     */
    it('ArkUI_Text_149', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"tnum" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'pnum'on
     */
    it('ArkUI_Text_150', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"pnum" on'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "pnum"off
     */
    it('ArkUI_Text_151', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"pnum" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'vert'on
     */
    it('ArkUI_Text_152', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"vert" on'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "vert"off
     */
    it('ArkUI_Text_153', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"vert" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'vrt2'on
     */
    it('ArkUI_Text_154', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"vrt2" on'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "vrt2"off
     */
    it('ArkUI_Text_155', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"vrt2" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'liga'on
     */
    it('ArkUI_Text_156', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"liga" on'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "liga"off
     */
    it('ArkUI_Text_157', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"liga" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ordn'on
     */
    it('ArkUI_Text_158', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"ordn" on'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ordn"off
     */
    it('ArkUI_Text_159', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"ordn" off'
      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'sinf'on
     */
    it('ArkUI_Text_160', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"sinf" on'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "sinf"off
     */
    it('ArkUI_Text_161', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'fontFeature')
      await radioClick({
        radioClickObj: '"sinf" off'
      })
      done();
    })

    //fontFeature的相关属性测试完毕，关闭fontFeature Toggle无需断言
    it('ArkUI_Text_162', 0, async (done: Function) => {
      await searchParentBlock('fontFeature', false, '参数列表')
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Text_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_Text_Comp_0006', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0007', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0008', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0009', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_Text_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_Text_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_Text_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_Text_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_Text_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_Text_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_Text_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_Text_Comp_0018', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0019', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_Text_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_Text_Comp_0022', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0023', 0, async (done: Function) => {
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
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试组件borderStyle
     */
    it('ArkUI_Text_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_Text_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_Text_Comp_0027', 0, async (done: Function) => {
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Text',
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Text_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Text_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_Text_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Text_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Text_Comp_0034', 0, async (done: Function) => {
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
        id: 'Text',
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
    it('ArkUI_Text_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Text',
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
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderWidth', JsonType.value),
        ],
        assertEqual: '0.00px'
      })

      done();

    })
    /**
     * 测试组件background.align
     */
    it('ArkUI_Text_Comp_0036', 0, async (done: Function) => {
      await titleSearch('基础属性', 'background.align');
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        }
      })
      done();
    })
    it('ArkUI_Text_Comp_0037', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    it('ArkUI_Text_Comp_0038', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })
    it('ArkUI_Text_Comp_0039', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })
    it('ArkUI_Text_Comp_0040', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })
    it('ArkUI_Text_Comp_0041', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })
    it('ArkUI_Text_Comp_0042', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 6,
      })
      done();
    })
    it('ArkUI_Text_Comp_0043', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 7,
      })
      done();
    })
    it('ArkUI_Text_Comp_0044', 0, async (done: Function) => {
      // 无法取到子组件状态
      await titleSearch('基础属性', 'background.align');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('background.align')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 8,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })
      done();
    })
    /**
     * 测试组件backgroundColor
     */
    it('ArkUI_Text_Comp_0045', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_Text_Comp_0046', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_Text_Comp_0047', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })
    it('ArkUI_Text_Comp_0048', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_Text_Comp_0049', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_Text_Comp_0050', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Text',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('backgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })
    /**
     * 测试组件backgroundImage.src
     */
    it('ArkUI_Text_Comp_0051', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
    it('ArkUI_Text_Comp_0052', 0, async (done: Function) => {
      await titleSearch('基础属性', 'backgroundImage.src');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('backgroundImage.src')))
      if (await toggle.isChecked() === true) {
        await toggle.click();
      }
      await driver.delayMs(1000)
      done();
    })
  })
}