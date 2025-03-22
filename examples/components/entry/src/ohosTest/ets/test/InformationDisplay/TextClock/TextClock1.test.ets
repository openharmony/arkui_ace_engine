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
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search,
  searchParentBlock
} from '../../../utils';
import { TextClockStart } from './TextClock';

const driver = Driver.create();

export default function TextClock1() {
  describe('TextClock1', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await TextClockStart(done)
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss03'on
     */
    it('ArkUI_TextClock_050', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:5,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss03" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss03"off
     */
    it('ArkUI_TextClock_051', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:6,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss03" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss04'on
     */
    it('ArkUI_TextClock_052', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:7,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss04" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss04"off
     */
    it('ArkUI_TextClock_053', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:8,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss04" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss05'on
     */
    it('ArkUI_TextClock_054', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:9,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss05" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss05"off
     */
    it('ArkUI_TextClock_055', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:10,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss05" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss08'on
     */
    it('ArkUI_TextClock_056', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:11,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss08" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss08"off
     */
    it('ArkUI_TextClock_057', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:12,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss08" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss09'on
     */
    it('ArkUI_TextClock_058', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:13,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss09" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss09"off
     */
    it('ArkUI_TextClock_059', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:14,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss09" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ss10'on
     */
    it('ArkUI_TextClock_060', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:15,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss10" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ss10"off
     */
    it('ArkUI_TextClock_061', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:16,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ss10" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'frac'on
     */
    it('ArkUI_TextClock_062', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:17,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"frac" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "frac"off
     */
    it('ArkUI_TextClock_063', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:18,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"frac" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'sups'on
     */
    it('ArkUI_TextClock_064', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:19,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"sups" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "sups"off
     */
    it('ArkUI_TextClock_065', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:20,
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"sups" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'subs'on
     */
    it('ArkUI_TextClock_066', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:21,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"subs" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "subs"off
     */
    it('ArkUI_TextClock_067', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:22,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"subs" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'numr'on
     */
    it('ArkUI_TextClock_068', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:23,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"numr" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "numr"off
     */
    it('ArkUI_TextClock_069', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:24,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"numr" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'dnom'on
     */
    it('ArkUI_TextClock_070', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:25,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"dnom" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "dnom"off
     */
    it('ArkUI_TextClock_071', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:26,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"dnom" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'case'on
     */
    it('ArkUI_TextClock_072', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:27,
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"case" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "case"off
     */
    it('ArkUI_TextClock_073', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"case" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"case" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'tnum'on
     */
    it('ArkUI_TextClock_074', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"tnum" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"tnum" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "tnum"off
     */
    it('ArkUI_TextClock_075', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"tnum" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"tnum" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'pnum'on
     */
    it('ArkUI_TextClock_076', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"pnum" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"pnum" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "pnum"off
     */
    it('ArkUI_TextClock_077', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"pnum" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"pnum" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'vert'on
     */
    it('ArkUI_TextClock_078', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"vert" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"vert" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "vert"off
     */
    it('ArkUI_TextClock_079', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"vert" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"vert" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'vrt2'on
     */
    it('ArkUI_TextClock_080', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"vrt2" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"vrt2" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "vrt2"off
     */
    it('ArkUI_TextClock_081', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"vrt2" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"vrt2" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'liga'on
     */
    it('ArkUI_TextClock_082', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"liga" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"liga" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "liga"off
     */
    it('ArkUI_TextClock_083', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"liga" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"liga" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'ordn'on
     */
    it('ArkUI_TextClock_084', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"ordn" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ordn" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "ordn"off
     */
    it('ArkUI_TextClock_085', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"ordn" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"ordn" 0'

      })
      done();
    })
    /**
     * 测试组件fontFeature支持设置文字特性效果为 'sinf'on
     */
    it('ArkUI_TextClock_086', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"sinf" on',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"sinf" 1'
      })
      done();
    })

    /**
     * 测试组件fontFeature支持设置文字特性效果为 "sinf"off
     */
    it('ArkUI_TextClock_087', 0, async (done: Function) => {
      await Search('参数列表','fontFeature')
      await radioClick({
        radioClickObj:'"sinf" off',
        toggleClick:{
          toggleClickObj:'fontFeature'
        },
        id:'TextClock',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fontFeature', JsonType.value),
        ],
        assertEqual: '"sinf" 0'

      })
      done();
    })

    //fontFeature的相关属性测试完毕，关闭fontFeature Toggle
    it('ArkUI_TextClock_88', 0, async (done: Function) => {
      await searchParentBlock('fontFeature',false,'参数列表')
      done();
    })

    /**
     * 测试组件contentModifier支持定制TextClock内容区的方法为允许
     */
    it('ArkUI_TextClock_089', 0, async (done: Function) => {
      await Search('参数列表','contentModifier')
      await radioClick({
        radioClickObj:1,
        toggleClick:{
          toggleClickObj:'contentModifier'
        },
      })
      done();
    })

    /**
     * 测试组件contentModifier支持定制TextClock内容区的方法禁止
     */
    it('ArkUI_TextClock_090', 0, async (done: Function) => {
      await Search('参数列表','contentModifier')
      await radioClick({
        radioClickObj:1,
        toggleClick:{
          toggleClickObj:'contentModifier'
        }

      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_TextClock_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0006', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0007', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0008', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0009', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0017', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0018', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0019', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0020', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0021', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0022', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0023', 0, async (done: Function) => {
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
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0024', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0025', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dotted'
      })
      done();
    })
    it('ArkUI_TextClock_Comp_0026', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderStyle', JsonType.value)
        ],
        assertEqual: 'BorderStyle.Dashed'
      })
      done();
    })
    it('ArkUI_TextClock_Comp_0027', 0, async (done: Function) => {
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0028', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0029', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })
    it('ArkUI_TextClock_Comp_0030', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })
    it('ArkUI_TextClock_Comp_0031', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();
    })
    it('ArkUI_TextClock_Comp_0032', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })
    it('ArkUI_TextClock_Comp_0033', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'Gauge',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })
    it('ArkUI_TextClock_Comp_0034', 0, async (done: Function) => {
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
        id: 'Gauge',
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
    it('ArkUI_TextClock_Comp_0035', 0, async (done: Function) => {
      await titleSearch('基础属性', 'borderRadius');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Gauge',
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
     * 测试组件background.align
     */
    it('ArkUI_TextClock_Comp_0036', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0037', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0038', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0039', 0, async (done: Function) => {
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
    it('ArkUI_TextClock_Comp_0040', 0, async (done: Function) => {
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

    })

}