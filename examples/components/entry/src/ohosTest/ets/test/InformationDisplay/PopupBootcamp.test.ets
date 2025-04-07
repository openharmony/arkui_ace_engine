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

import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON,Component, } from '@kit.TestKit'
import { Point } from '@ohos.UiTest';
import { buttonClick, JsonType, KeyStruct,
  radioClick,
  Search, Slide, sliderDrag,  ToggleClick } from '../../utils';

const TAG = 'PopupBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function PopupBootcampTest() {
  describe('PopupBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(3500);
        console.info(TAG + 'PopupBootcamp001' + ' begin');


        let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
        console.info(TAG + 'ListItemGroup' + ListItemGroup.toString());
        let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
        let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
        await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
        await driver.delayMs(3500);

        let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
        await atomDisplays.click();
        await driver.delayMs(4000);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[2].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 1000)
        await driver.delayMs(2000);

        let ListItems1: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width3: Point = await ListItems1[2].getBoundsCenter()
        let width4: Point = await ListItems1[4].getBoundsCenter()
        await driver.swipe(width3.x, width4.y, width3.x, width3.y, 1000)
        await driver.delayMs(2000);


        let scrollSearch: Component = await driver.findComponent(ON.text('气泡/Popup'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })


    /**
     * 测试组件icon.image支持设置图标内容为1号图标
     */
    it('ArkUI_Popup_001', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.image")
      await buttonClick({
        buttonClickObj:0,
      })
      done();
    })

    /**
     * 测试组件icon.image支持设置图标内容为2号图标
     */
    it('ArkUI_Popup_002', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.image")
      await buttonClick({
        buttonClickObj:1,
      })
      done();
    })

    /**
     * 测试组件icon.image支持设置图标内容为3号图标
     */
    it('ArkUI_Popup_003', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.image")
      await buttonClick({
        buttonClickObj:2,
      })
      done();
    })

    /**
     * 测试组件icon.image支持设置图标内容为4号图标
     */
    it('ArkUI_Popup_004', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.image")
      await buttonClick({
        buttonClickObj:3,
      })
      done();
    })

    /**
     * 测试组件icon.image支持设置图标内容为5号图标
     */
    it('ArkUI_Popup_005', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.image")
      await buttonClick({
        buttonClickObj:4,
      })
      done();
    })

    /**
     * 测试组件icon.image支持设置图标内容为6号图标
     */
    it('ArkUI_Popup_006', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.image")
      await buttonClick({
        buttonClickObj:5,
        toggleClick:{
          toggleClickType:ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件icon.width支持设置图标宽度
     */
    it('ArkUI_Popup_007', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.width")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'icon.width'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'icon.width'
        }
      })
      done();
    })

    /**
     * 测试组件icon.height支持设置图标高度
     */
    it('ArkUI_Popup_008', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.height")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'icon.height'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'icon.height'
        }
      })
      done();
    })

    /**
     * 测试组件icon.fillColor支持设置图标填充颜色为1号色
     */
    it('ArkUI_Popup_009', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'icon.fillColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件icon.fillColor支持设置图标填充颜色为2号色
     */
    it('ArkUI_Popup_010', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'icon.fillColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件icon.fillColor支持设置图标填充颜色为3号色
     */
    it('ArkUI_Popup_011', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'icon.fillColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件icon.fillColor支持设置图标填充颜色为4号色
     */
    it('ArkUI_Popup_012', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'icon.fillColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件icon.fillColor支持设置图标填充颜色为5号色
     */
    it('ArkUI_Popup_013', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'icon.fillColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件icon.fillColor支持设置图标填充颜色为6号色
     */
    it('ArkUI_Popup_014', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'icon.fillColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件icon.borderRadius支持设置图标圆角
     */
    it('ArkUI_Popup_015', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","icon.borderRadius")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'icon.borderRadius'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'icon.borderRadius'
        }
      })
      done();
    })

    /**
     * 测试组件title.fontColor支持设置文本字体颜色为1号色
     */
    it('ArkUI_Popup_016', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'title.fontColor')
      await buttonClick({
        buttonClickObj: 0,
      })
      done();
    })

    /**
     * 测试组件title.fontColor支持设置文本字体颜色为2号色
     */
    it('ArkUI_Popup_017', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'title.fontColor')
      await buttonClick({
        buttonClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件title.fontColor支持设置文本字体颜色为3号色
     */
    it('ArkUI_Popup_018', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'title.fontColor')
      await buttonClick({
        buttonClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件title.fontColor支持设置文本字体颜色为4号色
     */
    it('ArkUI_Popup_019', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'title.fontColor')
      await buttonClick({
        buttonClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件title.fontColor支持设置文本字体颜色为5号色
     */
    it('ArkUI_Popup_020', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'title.fontColor')
      await buttonClick({
        buttonClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件title.fontColor支持设置文本字体颜色为6号色
     */
    it('ArkUI_Popup_021', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'title.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件title.fontSize支持设置文本字体大小
     */
    it('ArkUI_Popup_022', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","title.fontSize")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'title.fontSize'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'title.fontSize'
        }
      })
      done();
    })

    /**
     * 测试组件title.fontWeight支持设置文本字体粗细为Lighter
     */
    it('ArkUI_Popup_023', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','title.fontWeight')
      await radioClick({
        radioClickObj:0,
      })
      done();
    })

    /**
     * 测试组件title.fontWeight支持设置文本字体粗细为Normal
     */
    it('ArkUI_Popup_024', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','title.fontWeight')
      await radioClick({
        radioClickObj:1,
      })
      done();
    })

    /**
     * 测试组件title.fontWeight支持设置文本字体粗细为Regular
     */
    it('ArkUI_Popup_025', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','title.fontWeight')
      await radioClick({
        radioClickObj:2,
      })
      done();
    })

    /**
     * 测试组件title.fontWeight支持设置文本字体粗细为Medium
     */
    it('ArkUI_Popup_026', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','title.fontWeight')
      await radioClick({
        radioClickObj:3,
      })
      done();
    })

    /**
     * 测试组件title.fontWeight支持设置文本字体粗细为Bold
     */
    it('ArkUI_Popup_027', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','title.fontWeight')
      await radioClick({
        radioClickObj:4,
      })
      done();
    })

    /**
     * 测试组件title.fontWeight支持设置文本字体粗细为Bolder
     */
    it('ArkUI_Popup_028', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','title.fontWeight')
      await radioClick({
        radioClickObj:5,
        toggleClick:{
          toggleClickType:ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件message.fontColor支持设置文本字体颜色为1号色
     */
    it('ArkUI_Popup_029', 0, async (done: Function)  =>{
      // 无法取到属性值进行断言
      await Search('参数列表','message.fontColor')
      await buttonClick({
        buttonClickObj:0,
      })
      done();
    })

    /**
     * 测试组件message.fontColor支持设置文本字体颜色为2号色
     */
    it('ArkUI_Popup_030', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','message.fontColor')
      await buttonClick({
        buttonClickObj:1,
      })
      done();
    })

    /**
     * 测试组件message.fontColor支持设置文本字体颜色为3号色
     */
    it('ArkUI_Popup_031', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','message.fontColor')
      await buttonClick({
        buttonClickObj:2,
      })
      done();
    })

    /**
     * 测试组件message.fontColor支持设置文本字体颜色为4号色
     */
    it('ArkUI_Popup_032', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','message.fontColor')
      await buttonClick({
        buttonClickObj:3,
      })
      done();
    })

    /**
     * 测试组件message.fontColor支持设置文本字体颜色为5号色
     */
    it('ArkUI_Popup_033', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','message.fontColor')
      await buttonClick({
        buttonClickObj:4,
      })
      done();
    })

    /**
     * 测试组件message.fontColor支持设置文本字体颜色为6号色
     */
    it('ArkUI_Popup_034', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表','message.fontColor')
      await buttonClick({
        buttonClickObj:5,
        toggleClick:{
          toggleClickType:ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件message.fontSize支持设置文本字体大小
     */
    it('ArkUI_Popup_035', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","message.fontSize")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'message.fontSize'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'message.fontSize'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.confirm.fontColor支持设置confirm按钮文本字体颜色为1号色
     */
    it('ArkUI_Popup_036', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.confirm.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick:{
          toggleClickObj:'buttons.confirm.fontColor'
        }
      })
      done();
    })

    /**
     *测试组件buttons.confirm.fontColor支持设置confirm按钮文本字体颜色为2号色
     */
    it('ArkUI_Popup_037', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.confirm.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick:{
          toggleClickObj:'buttons.confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.confirm.fontColor支持设置confirm按钮文本字体颜色为3号色
     */
    it('ArkUI_Popup_038', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.confirm.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick:{
          toggleClickObj:'buttons.confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.confirm.fontColor支持设置confirm按钮文本字体颜色为4号色
     */
    it('ArkUI_Popup_039', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.confirm.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick:{
          toggleClickObj:'buttons.confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.confirm.fontColor支持设置confirm按钮文本字体颜色为5号色
     */
    it('ArkUI_Popup_040', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.confirm.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick:{
          toggleClickObj:'buttons.confirm.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.confirm.fontColor支持设置confirm按钮文本字体颜色为6号色
     */
    it('ArkUI_Popup_041', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.confirm.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj:'buttons.confirm.fontColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件buttons.confirm.fontSize支持设置confirm按钮文本字体大小
     */
    it('ArkUI_Popup_042', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","buttons.confirm.fontSize")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'buttons.confirm.fontSize'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'buttons.confirm.fontSize'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.cancel.fontColor支持设置cancel按钮文本字体颜色为1号色
     */
    it('ArkUI_Popup_043', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.cancel.fontColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick:{
          toggleClickObj:'buttons.cancel.fontColor'
        }
      })
      done();
    })

    /**
     *测试组件buttons.cancel.fontColor支持设置cancel按钮文本字体颜色为2号色
     */
    it('ArkUI_Popup_044', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.cancel.fontColor')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick:{
          toggleClickObj:'buttons.cancel.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.cancel.fontColor支持设置cancel按钮文本字体颜色为3号色
     */
    it('ArkUI_Popup_045', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.cancel.fontColor')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick:{
          toggleClickObj:'buttons.cancel.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.cancel.fontColor支持设置cancel按钮文本字体颜色为4号色
     */
    it('ArkUI_Popup_046', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.cancel.fontColor')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick:{
          toggleClickObj:'buttons.cancel.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.cancel.fontColor支持设置cancel按钮文本字体颜色为5号色
     */
    it('ArkUI_Popup_047', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.cancel.fontColor')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick:{
          toggleClickObj:'buttons.cancel.fontColor'
        }
      })
      done();
    })

    /**
     * 测试组件buttons.cancel.fontColor支持设置cancel按钮文本字体颜色为6号色
     */
    it('ArkUI_Popup_048', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'buttons.cancel.fontColor')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj:'buttons.cancel.fontColor',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件buttons.cancel.fontSize支持设置cancel.按钮文本字体大小
     */
    it('ArkUI_Popup_049', 0, async (done: Function)  => {
      // 无法取到属性值进行断言
      await Search("参数列表","buttons.cancel.fontSize")
      await sliderDrag({
        slideStar:Slide.start,
        toggleClick:{
          toggleClickType:ToggleClick.Open,
          toggleClickObj:'buttons.cancel.fontSize'
        }
      })
      await sliderDrag({
        slideStar:Slide.end,
        toggleClick:{
          toggleClickType:ToggleClick.Close,
          toggleClickObj:'buttons.cancel.fontSize'
        }
      })
      done();
    })


  })
}