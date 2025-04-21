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
import { buttonClick,
  getToggle,
  JsonType, KeyStruct, radioClick,
  searchToggle,
  Slide, sliderDrag,
  titleSearch,
  ToggleClick } from '../../../utils';
import { CalendarPickerStart } from './CalendarPicker';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function CalendarPicker8() {
  describe('CalendarPicker8', () => {

    beforeAll(async (done: Function) => {
      await CalendarPickerStart(done)
    })
    //hitTestBehavior
    /*
     * 测试组件hitTestBehavior支持设置Default且获取属性正确
     * */
    it('ArkUI_CalendarPicker_Comp_0645', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Default'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Block且获取属性正确
     * */
    it('ArkUI_CalendarPicker_Comp_0646', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Block'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置Transparent且获取属性正确
     * */
    it('ArkUI_CalendarPicker_Comp_0647', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.Transparent'
      })
      done();
    })
    /*
     * 测试组件hitTestBehavior支持设置None且获取属性正确
     * */
    it('ArkUI_CalendarPicker_Comp_0648', 0, async (done: Function) => {
      await titleSearch('基础属性', 'hitTestBehavior', '通用属性6')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'hitTestBehavior'
        },
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('hitTestBehavior', JsonType.value)
        ],
        assertEqual: 'HitTestMode.None'
      })
      done();
    })
    // obscured
    /*
     * 测试组件obscured支持设置null且获取属性正确
     * */
    it('ArkUI_CalendarPicker_Comp_0761', 0, async (done: Function) => {
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
    it('ArkUI_CalendarPicker_Comp_0762', 0, async (done: Function) => {
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
    it('ArkUI_CalendarPicker_Comp_0763', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0764', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0765', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0766', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0767', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0768', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0769', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0770', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0771', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0772', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,
        id: 'CalendarPicker',
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
    it('ArkUI_CalendarPicker_Comp_0773', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,
        id: 'CalendarPicker',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('renderFit', JsonType.value)
        ],
        assertEqual: 'RenderFit.RESIZE_CONTAIN'
      })
      done();
    })
  })
}