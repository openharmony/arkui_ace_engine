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
import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  Search,
  ToggleClick,
  titleSearch,
  searchParentBlock,
  searchToggle,
  getToggle
} from '../../../utils';
import { ScrollTest } from './ScrollTest';

export default function ScrollTest1() {
  describe('ScrollTest1', () => {
      beforeAll(async (done: Function) => {
        await ScrollTest(done);
      })
    it('ArkUI_scroll_001', 0, async (done: Function) => {
      await Search('参数列表', 'scrollable');
      await radioClick({
        radioClickObj:0,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs',JsonType.obj),
          new KeyStruct('scrollable',JsonType.value)
        ],
        assertEqual:'ScrollDirection.Vertical'
      });

      done();
    })

    it('ArkUI_scroll_002', 0, async (done: Function) => {
      await Search('参数列表', 'scrollable');
      await radioClick({
        radioClickObj:1,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs',JsonType.obj),
          new KeyStruct('scrollable',JsonType.value)
        ],
        assertEqual:'ScrollDirection.Horizontal'

      });

      done();
    })

    it('ArkUI_scroll_003', 0, async (done: Function) => {
      await Search('参数列表', 'scrollable');
      await radioClick({
        radioClickObj:2,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
        },
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs',JsonType.obj),
          new KeyStruct('scrollable',JsonType.value)
        ],
        assertEqual:'ScrollDirection.None'

      });

      done();
    })

    it("ArkUI_scroll_004", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBar');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBar', JsonType.value)
        ],
        assertEqual: 'BarState.Off'

      });
      done();
    })

    it("ArkUI_scroll_005", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBar');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBar', JsonType.value)
        ],
        assertEqual: 'BarState.On'

      });
      done();
    })

    it("ArkUI_scroll_006", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBar');
      await radioClick({
        radioClickObj: 2,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
        },
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBar', JsonType.value)
        ],
        assertEqual: 'BarState.Auto'

      });
      done();
    })

    it("ArkUI_scroll_007", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor');
      await buttonClick({
        buttonClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor',JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      });
      done();
    })

    it("ArkUI_scroll_008", 0, async (done: Function) => {
      await Search('参数列表','scrollBarColor');
      await buttonClick({
        buttonClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      });
      done();
    })

    it("ArkUI_scroll_009", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor');
      await buttonClick({
        buttonClickObj: 2,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      });
      done();
    })

    it("ArkUI_scroll_010", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor');
      await buttonClick({
        buttonClickObj: 3,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      });
      done();
    })

    it("ArkUI_scroll_011", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor');
      await buttonClick({
        buttonClickObj: 4,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      });
      done();
    })

    it("ArkUI_scroll_012", 0, async (done: Function) => {
      await Search('参数列表', 'scrollBarColor');
      await buttonClick({
        buttonClickObj: 5,
        id: 'Scroll',
        toggleClick:{
          toggleClickType:ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarColor', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      });
      done();
    })

    it("ArkUI_scroll_013", 0, async (done: Function) => {
      await Search('参数列表','scrollBarWidth');
      await sliderDrag({
        slideStar:Slide.start,
        id:'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarWidth', JsonType.value)
        ],
        assertEqual: '8.00vp'
      });
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        },
        id:'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollBarWidth', JsonType.value)
        ],
        assertEqual: '1.00vp'
      });
      done();
    })

    it("ArkUI_scroll_014", 0, async (done: Function) => {
      await Search('参数列表', 'scrollSnap.snapAlign');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value)
        ],
        assertEqual: 'ScrollSnapAlign.NONE'
      });
      done();
    })

    it("ArkUI_scroll_015", 0, async (done: Function) => {
      await Search('参数列表', 'scrollSnap.snapAlign');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value)
        ],
        assertEqual: 'ScrollSnapAlign.START'
      });
      done();
    })

    it("ArkUI_scroll_016", 0, async (done: Function) => {
      await Search('参数列表', 'scrollSnap.snapAlign');
      await radioClick({
        radioClickObj: 2,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value)
        ],
        assertEqual: 'ScrollSnapAlign::CENTER'
      });
      done();
    })

    it("ArkUI_scroll_017", 0, async (done: Function) => {
      await Search('参数列表', 'scrollSnap.snapAlign');
      await radioClick({
        radioClickObj: 3,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value)
        ],
        assertEqual: 'ScrollSnapAlign::END'
      });
      done();
    })

    it("ArkUI_scroll_018", 0, async (done: Function) => {
      await Search('参数列表', 'scrollSnap.snapPagination');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnap', JsonType.obj),
          new KeyStruct('snapPagination', JsonType.value),
        ],
        assertEqual: '1000.00vp'
      });

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnap', JsonType.obj),
          new KeyStruct('snapPagination', JsonType.value),
        ],
        assertEqual: '100.00vp'
      });
      done();
    })

    it("ArkUI_scroll_019", 0, async (done:Function) => {
      await Search('参数列表', 'scrollSnap.enableSnapToStart');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnap', JsonType.obj),
          new KeyStruct('enableSnapToStart', JsonType.value)
        ],
        assertEqual: true
      });
      done();
    })

    it("ArkUI_scroll_020", 0, async (done:Function) => {
      await Search('参数列表', 'scrollSnap.enableSnapToStart');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnap', JsonType.obj),
          new KeyStruct('enableSnapToStart', JsonType.value)
        ],
        assertEqual: false
      });
      done();
    })

    it("ArkUI_scroll_021", 0, async (done:Function) => {
      await Search('参数列表', 'scrollSnap.enableSnapToEnd');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnap', JsonType.obj),
          new KeyStruct('enableSnapToEnd', JsonType.value)
        ],
        assertEqual: true
      });
      done();
    })

    it("ArkUI_scroll_022", 0, async (done:Function) => {
      await Search('参数列表', 'scrollSnap.enableSnapToEnd');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnap', JsonType.obj),
          new KeyStruct('enableSnapToEnd', JsonType.value)
        ],
        assertEqual: false
      });
      done();
    })

    it("ArkUI_scroll_023", 0, async (done: Function) => {
      await Search('参数列表', 'edgeEffect');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffect', JsonType.value)
        ],
        assertEqual: 'EdgeEffect.Spring'
      });
      done();
    })

    it("ArkUI_scroll_024", 0, async (done: Function) => {
      await Search('参数列表', 'edgeEffect');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffect', JsonType.value)
        ],
        assertEqual: 'EdgeEffect.Fade'
      });
      done();
    })

    it("ArkUI_scroll_025", 0, async (done: Function) => {
      await Search('参数列表', 'edgeEffect');
      await radioClick({
        radioClickObj: 2,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffect', JsonType.value)
        ],
        assertEqual: 'EdgeEffect.None'
      });
      done();
    })

    it("ArkUI_scroll_026", 0, async (done: Function) => {
      await Search('参数列表','edgeEffect.options.alwaysEnabled');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs',JsonType.obj),
          new KeyStruct('edgeEffectOptions', JsonType.obj),
          new KeyStruct('alwaysEnabled', JsonType.value)
        ],
        assertEqual: true
      });
      done();
    })

    it("ArkUI_scroll_027", 0, async (done: Function) => {
      await Search('参数列表','edgeEffect.options.alwaysEnabled');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs',JsonType.obj),
          new KeyStruct('edgeEffectOptions', JsonType.obj),
          new KeyStruct('alwaysEnabled', JsonType.value)
        ],
        assertEqual: false
      });
      done();
    })

    it("ArkUI_scroll_028", 0, async (done: Function) => {
      await Search('参数列表', 'enableScrollInteraction');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableScrollInteraction', JsonType.value)
        ],
        assertEqual: true
      });
      done();
    })

    it("ArkUI_scroll_029", 0, async (done: Function) => {
      await Search('参数列表', 'enableScrollInteraction');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableScrollInteraction', JsonType.value)
        ],
        assertEqual: false
      });
      done();
    })

    it("ArkUI_scroll_030", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollForward');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      });
      done();
    })

    it("ArkUI_scroll_031", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollForward');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      });
      done();
    })

    it("ArkUI_scroll_032", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollForward');
      await radioClick({
        radioClickObj: 2,
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      });
      done();
    })

    it("ArkUI_scroll_033", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollForward');
      await radioClick({
        radioClickObj: 3,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      });
      done();
    })

    it("ArkUI_scroll_034", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollBackward');
      await radioClick({
        radioClickObj: 0,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      });
      done();
    })

    it("ArkUI_scroll_035", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollBackward');
      await radioClick({
        radioClickObj: 1,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      });
      done();
    })

    it("ArkUI_scroll_036", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollBackward');
      await radioClick({
        radioClickObj: 2,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      });
      done();
    })

    it("ArkUI_scroll_037", 0, async (done: Function) => {
      await Search('参数列表', 'nestedScroll.scrollBackward');
      await radioClick({
        radioClickObj: 3,
        toggleClick:{
          toggleClickType:ToggleClick.Close
        },
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value)
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      });
      done();
    })

    it("ArkUI_scroll_038", 0, async (done: Function) => {
      await Search('参数列表', 'friction');
      await sliderDrag({
        slideStar:Slide.start,
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value)
        ],
        assertEqual: 1
      });

      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType: ToggleClick.Close
        },
        id: 'Scroll',
        arr:[
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value)
        ],
        assertEqual: 0.75
      });
      done();
    })

    it("ArkUI_scroll_039", 0, async (done: Function) => {
      //如果同时设置了划动翻页enablePaging和限位滚动scrollSnap，则scrollSnap优先生效，enablePaging不生效
      //无法断言
      await Search('参数列表', 'enablePaging');
      await radioClick({
        radioClickObj: 0,
        toggleClick:{
          toggleClickObj:'enablePaging'

        }
      });
      done();
    })

    it("ArkUI_scroll_040", 0, async (done: Function) => {
      //如果同时设置了划动翻页enablePaging和限位滚动scrollSnap，则scrollSnap优先生效，enablePaging不生效
      //无法断言
      await Search('参数列表', 'enablePaging');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj:'enablePaging'
        }
      });
      done();
    })

    it("ArkUI_scroll_041", 0, async (done: Function) => {
      await Search('参数列表', 'initialOffset.xOffset');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick:{
          toggleClickObj:'initialOffset.xOffset'
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('initialOffset', JsonType.obj),
          new KeyStruct('xOffset', JsonType.value)
        ],
        assertEqual: '100.00vp'
      });

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick:{
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'initialOffset.xOffset',
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('initialOffset', JsonType.obj),
          new KeyStruct('xOffset', JsonType.value)
        ],
        assertEqual: '0.00vp'
      });
      done();
    })

    it("ArkUI_scroll_042", 0, async (done: Function) => {
      await Search('参数列表', 'initialOffset.yOffset');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick:{
          toggleClickObj: 'initialOffset.yOffset'
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('initialOffset', JsonType.obj),
          new KeyStruct('yOffset', JsonType.value)
        ],
        assertEqual: '100.00vp'
      });

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'initialOffset.yOffset',
        },
        id: 'Scroll',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('initialOffset', JsonType.obj),
          new KeyStruct('yOffset', JsonType.value)
        ],
        assertEqual: '0.00vp'
      });
      done();
    })

  })
}