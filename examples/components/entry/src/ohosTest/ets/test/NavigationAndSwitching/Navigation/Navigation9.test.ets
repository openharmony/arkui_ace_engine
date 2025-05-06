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
  ToggleClick,
  titleSearch,
  searchToggle,
  getToggle
} from '../../../utils';
import { NavigationStart } from './Navigation';
import { Driver } from '@kit.TestKit';

const driver = Driver.create();

export default function Navigation9() {
  describe('Navigation9', () => {
    beforeAll(async (done: Function) => {
      await NavigationStart(done)
    })

    //bindContentCover.options.transition.scale.centerX
    it('ArkUI_Navigation_Comp_0661', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerX', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerX', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.scale.centerY
    it('ArkUI_Navigation_Comp_0662', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.scale.centerY', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.scale.centerY', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.x
    it('ArkUI_Navigation_Comp_0663', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.x', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.x', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        id: 'Gauge_Comp',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.y
    it('ArkUI_Navigation_Comp_0664', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.y', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.y', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.z
    it('ArkUI_Navigation_Comp_0665', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.z', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.z', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.centerX
    it('ArkUI_Navigation_Comp_0666', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerX', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerX', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.centerY
    it('ArkUI_Navigation_Comp_0667', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerY', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerY', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.rotate.centerZ
    it('ArkUI_Navigation_Comp_0668', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.centerZ', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.centerZ', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    // bindContentCover.options.transition.rotate.perspective
    it('ArkUI_Navigation_Comp_0669', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.rotate.perspective',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.rotate.perspective', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.move
    /*
     * 测试组件bindContentCover.options.transition.move支持设置TOP且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0670', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置BOTTOM且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0671', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })
    /*
    * 测试组件bindContentCover.options.transition.move支持设置START且获取属性正确
    */
    it('ArkUI_Navigation_Comp_0672', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.move支持设置END且获取属性正确
     */
    it('ArkUI_Navigation_Comp_0673', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.move', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.move', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.duration
    it('ArkUI_Navigation_Comp_0674', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.duration',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.duration', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.tempo
    it('ArkUI_Navigation_Comp_0675', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.tempo', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.tempo', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.curve
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Linear且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0676', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Ease且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0677', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseIn且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0678', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseOut且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0679', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置EaseInOut且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0680', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutSlowIn且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0681', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置LinearOutSlowIn且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0682', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置FastOutLinearIn且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0683', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置ExtremeDeceleration且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0684', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Sharp且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0685', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Rhythm且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0686', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Smooth且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0687', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.curve支持设置Friction且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0688', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.curve', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.delay
    it('ArkUI_Navigation_Comp_0689', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.delay', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.delay', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.iterations
    it('ArkUI_Navigation_Comp_0690', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.iterations',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.iterations', '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.playMode
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Normal且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0691', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Reverse且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0692', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置Alternate且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0693', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件bindContentCover.options.transition.animation.playMode支持设置AlternateReverse且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0694', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow', 'bindContentCover.options.transition.animation.playMode',
        '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.playMode', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.max
    it('ArkUI_Navigation_Comp_0695', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.max', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.max',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.min
    it('ArkUI_Navigation_Comp_0696', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.min', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.min',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover.options.transition.animation.expectedFrameRateRange.expected
    it('ArkUI_Navigation_Comp_0697', 0, async (done: Function) => {
      //无法获取属性
      await searchToggle('bindContentCover.isShow',
        'bindContentCover.options.transition.animation.expectedFrameRateRange.expected', '通用属性7')
      await titleSearch('基础属性', 'bindContentCover.options.transition.animation.expectedFrameRateRange.expected',
        '通用属性7')
      await sliderDrag({
        slideStar: Slide.start,
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //bindContentCover相关属性测试完毕，关闭bindContentCover.isShow Toggle,无需断言
    it('ArkUI_Navigation_Comp_0698', 0, async (done: Function) => {
      await titleSearch('基础属性', 'bindContentCover.isShow', '通用属性7')
      await getToggle(ToggleClick.Close)
      done();
    })
    // obscured
    /*
     * 测试组件obscured支持设置null且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0761', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件obscured支持设置PLACEHOLDER且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0762', 0, async (done: Function) => {
      //获取不到属性值无法进行断言
      await titleSearch('基础属性', 'obscured', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //renderFit
    /*
     * 测试组件renderFit支持设置CENTER且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0763', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.CENTER'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0764', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.TOP'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0765', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.BOTTOM'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置LEFT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0766', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RIGHT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0767', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0768', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.TOP_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置TOP_RIGHT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0769', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.TOP_RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_LEFT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0770', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.BOTTOM_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0771', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.BOTTOM_RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_FILL且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0772', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_FILL'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0773', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0774', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 11,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN_TOP_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_CONTAIN_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0775', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN_BOTTOM_RIGHT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0776', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 13,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_COVER'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_TOP_LEFT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0777', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 14,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_COVER_TOP_LEFT'
      })
      done();
    })
    /*
     * 测试组件renderFit支持设置RESIZE_COVER_BOTTOM_RIGHT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0778', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 15,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_COVER_BOTTOM_RIGHT'
      })
      done();
    })
    // monopolizeEvents
    /*
     * 测试组件monopolizeEvents支持设置true且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0779', 0, async (done: Function) => {
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('monopolizeEvents', JsonType.value)
        ],
        assertEqual: true
      })
      done();
    })
    /*
     * 测试组件monopolizeEvents支持设置false且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0780', 0, async (done: Function) => {
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: "Navigation",
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('monopolizeEvents', JsonType.value)
        ],
        assertEqual: false
      })
      done();
    })
    //cursorControl
    /*
     * 测试组件cursorControl支持设置DEFAULT且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0781', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置EAST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0782', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0783', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 2
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0784', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 3
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0785', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 4
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置WEST_EAST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0786', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 5
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_SOUTH且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0787', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 6
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0788', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 7
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0789', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 8
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0790', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 9
      })
      done();
    })
    /*
    * 测试组件cursorControl支持设置SOUTH_WEST且获取属性正确
    * */
    it('ArkUI_Navigation_Comp_0791', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 10
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_EAST_SOUTH_WEST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0792', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 11
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置NORTH_WEST_SOUTH_EAST且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0793', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 12
      })
      done();
    })
    /*
     * 测试组件cursorControl支持设置CROSS且获取属性正确
     * */
    it('ArkUI_Navigation_Comp_0794', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'cursorControl', '通用属性7')
      await radioClick({
        radioClickObj: 13
      })
      done();
    })
  })
}