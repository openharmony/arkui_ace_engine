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
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick
} from '../../../utils';
import { ListItemGroupStart } from './ListItemGroup.test';

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function ListItemGroup1Test() {
  describe('ListItemGroup1Test', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      await ListItemGroupStart(done);
    })

    //scrollBar
    /*
     * 测试组件scrollBar支持设置Auto且获取属性正确
     */
    it('ArkUI_ListItemGroup_001', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'scrollBar')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    * 测试组件scrollBar支持设置Off且获取属性正确
    */
    it('ArkUI_ListItemGroup_002', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'scrollBar')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
    * 测试组件scrollBar支持设置On且获取属性正确
    */
    it('ArkUI_ListItemGroup_003', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'scrollBar')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //edgeEffect
    /*
     * 测试组件scrollBar支持设置Spring且获取属性正确
     */
    it('ArkUI_ListItemGroup_004', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'edgeEffect')
      await radioClick({
        radioClickObj: 0
      })
      done();
    })
    /*
    * 测试组件edgeEffect支持设置Fade且获取属性正确
    */
    it('ArkUI_ListItemGroup_005', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'edgeEffect')
      await radioClick({
        radioClickObj: 1
      })
      done();
    })
    /*
    * 测试组件edgeEffect支持设置None且获取属性正确
    */
    it('ArkUI_ListItemGroup_006', 0, async (done: Function) => {
      //无法获取属性值进行断言
      await Search('参数列表', 'edgeEffect')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })
    //divider.color
    /*
    *测试组件divider.color支持设置量规图的颜色为1号色显示且获取属性正确
    * */
    it('ArkUI_ListItemGroup_007', 0, async (done: Function) => {
      await Search('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 0,
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })
    /**
     * 测试组件divider.color支持设置量规图的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_ListItemGroup_008', 0, async (done: Function) => {
      await Search('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 1,
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })
    /**
     * 测试组件divider.color支持设置量规图的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_ListItemGroup_009', 0, async (done: Function) => {
      await Search('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 2,
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })
    /**
     * 测试组件divider.color支持设置量规图的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_ListItemGroup_010', 0, async (done: Function) => {
      await Search('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 3,
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })
    /**
     * 测试组件divider.color支持设置量规图的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_ListItemGroup_011', 0, async (done: Function) => {
      await Search('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 4,
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })
    /**
     * 测试组件divider.color支持设置量规图的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_ListItemGroup_012', 0, async (done: Function) => {
      await Search('参数列表', 'divider.color')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('color', JsonType.value)
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })
    //divider.strokeWidth
    it('ArkUI_ListItemGroup_013', 0, async (done: Function) => {
      await Search('参数列表', 'divider.strokeWidth')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.strokeWidth'
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value)
        ],
        assertEqual: '30.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'divider.strokeWidth'
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    //divider.startMargin
    it('ArkUI_ListItemGroup_014', 0, async (done: Function) => {
      await Search('参数列表', 'divider.startMargin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.startMargin'
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('startMargin', JsonType.value)
        ],
        assertEqual: '30.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'divider.startMargin'
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('startMargin', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    //divider.endMargin
    it('ArkUI_ListItemGroup_015', 0, async (done: Function) => {
      await Search('参数列表', 'divider.endMargin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.endMargin'
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('endMargin', JsonType.value)
        ],
        assertEqual: '30.00vp'
      })
      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'divider.endMargin'
        },
        id: 'ListItemGroup',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
          new KeyStruct('endMargin', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done()
    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_ListItemGroup_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_ListItemGroup_Comp_0006', 0, async (done: Function) => {
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
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0007', 0, async (done: Function) => {
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
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0008', 0, async (done: Function) => {
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
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0009', 0, async (done: Function) => {
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
        id: 'ListItemGroup',
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
        id: 'ListItemGroup',
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
    it('ArkUI_ListItemGroup_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_ListItemGroup_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_ListItemGroup_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_ListItemGroup_Comp_0013', 0, async (done: Function) => {
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
  })
}