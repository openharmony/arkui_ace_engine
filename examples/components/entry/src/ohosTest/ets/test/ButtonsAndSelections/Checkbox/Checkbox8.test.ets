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
import { CheckboxStart } from './Checkbox';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function Checkbox8() {
  describe('Checkbox8', () => {

    beforeAll(async (done: Function) => {
      await CheckboxStart(done)
    })
    // obscured
    /*
     * 测试组件obscured支持设置null且获取属性正确
     * */
    it('ArkUI_Checkbox_Comp_0761', 0, async (done: Function) => {
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
    it('ArkUI_Checkbox_Comp_0762', 0, async (done: Function) => {
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
    it('ArkUI_Checkbox_Comp_0763', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0764', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0765', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 2,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0766', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 3,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0767', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 4,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0768', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 5,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0769', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 6,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0770', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 7,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0771', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 8,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0772', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 9,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0773', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 10,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0774', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 11,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0775', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 12,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0776', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 13,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0777', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 14,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0778', 0, async (done: Function) => {
      await titleSearch('基础属性', 'renderFit', '通用属性7')
      await radioClick({
        radioClickObj: 15,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0779', 0, async (done: Function) => {
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 0,
        id: 'Checkbox',
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
    it('ArkUI_Checkbox_Comp_0780', 0, async (done: Function) => {
      await titleSearch('基础属性', 'monopolizeEvents', '通用属性7')
      await radioClick({
        radioClickObj: 1,
        id: 'Checkbox',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('monopolizeEvents', JsonType.value)
        ],
        assertEqual: false
      })
      done();
    })
  })
}