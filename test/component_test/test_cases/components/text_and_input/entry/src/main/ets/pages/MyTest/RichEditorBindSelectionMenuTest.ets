/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function richEditorBindSelectionMenuTest() {
  /*
* RichEditor组件 BindSelectionMenu属性
* 找到画面id为richEditorBindSelectionMenu1,richEditorBindSelectionMenu2，richEditorBindSelectionMenu3的RichEditor组件
* 找到画面文本为RichEditorBindSelectionMenu1,RichEditorBindSelectionMenu2的Button组件
* 获取richEditor1的BindSelectionMenu属性与期待值{RichEditorSpanType.TEXT,'菜单模式',ResponseType.LongPress,onDisappear: () => {}}比对
* 点击button1，变更richEditor1的BindSelectionMenu属性值为{RichEditorSpanType.IMAGE,ResponseType.RightClick,onAppear: () => {}}
* 获取richEditor1的BindSelectionMenu属性与期待值{RichEditorSpanType.IMAGE,ResponseType.RightClick,onAppear: () => {}}比对
* 获取richEditor2的BindSelectionMenu.spantype属性与期待值RichEditorSpanType.IMAGE比对
* 获取richEditor2的BindSelectionMenu.responseType属性与期待值RichEditorResponseType.RIGHT_CLICK比对
* 获取richEditor2的BindSelectionMenu.options属性与期待值onAppear: () => {}比对
* 点击button2，变更richEditor2的BindSelectionMenu属性BindSelectionMenu.spantype值为RichEditorResponseType.SELECT
* 获取richEditor2的BindSelectionMenu.spantype属性与期待值RichEditorResponseType.SELECT比对
* 获取richEditor3的BindSelectionMenu.spantype属性与期待值RichEditorSpanType.MIXED比对
* 获取richEditor3的BindSelectionMenu.responseType属性与期待值RichEditorResponseType.LONG_PRESS比对
* 获取richEditor3的BindSelectionMenu.options属性与期待值onDisappear: () => {}比对
*/
  defineTest('richEditorBindSelectionMenuTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("richEditorBindSelectionMenuTestDemo running")
    let driver: Tester = Tester.create()
    let richEditor1: Component =
      await driver.findComponent(Matcher.create().id('richEditorBindSelectionMenu1').enabled(true))
    let richEditor2: Component =
      await driver.findComponent(Matcher.create().id('richEditorBindSelectionMenu2').enabled(true))
    let richEditor3: Component =
      await driver.findComponent(Matcher.create().id('richEditorBindSelectionMenu3').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('RichEditorBindSelectionMenu1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('RichEditorBindSelectionMenu2').enabled(true))


    let bindSelectionMenu1: string = await richEditor1.getInspectorInfo()
    assertFalse(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu == undefined)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.spantype, RichEditorSpanType.TEXT)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.responseType, ResponseType.LongPress)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.content, '菜单模式')
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.options, {
      onDisappear: () => {
      }
    })
    let bindSelectionMenu2: string = await richEditor2.getInspectorInfo()
    assertEqual(JSON.parse(bindSelectionMenu2).$attrs.bindSelectionMenu.spantype, RichEditorSpanType.IMAGE)
    assertEqual(JSON.parse(bindSelectionMenu2).$attrs.bindSelectionMenu.responseType,
      RichEditorResponseType.RIGHT_CLICK)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.options, {
      onAppear: () => {
      }
    })
    let bindSelectionMenu3: string = await richEditor3.getInspectorInfo()
    assertEqual(JSON.parse(bindSelectionMenu3).$attrs.bindSelectionMenu.spantype, RichEditorSpanType.MIXED)
    assertEqual(JSON.parse(bindSelectionMenu3).$attrs.bindSelectionMenu.responseType, RichEditorResponseType.LONG_PRESS)
    assertEqual(JSON.parse(bindSelectionMenu3).$attrs.bindSelectionMenu.options, {
      onDisappear: () => {
      }
    })

    await button1.tap()
    let bindSelectionMenu4: string = await richEditor1.getInspectorInfo()
    assertEqual(JSON.parse(bindSelectionMenu4).$attrs.bindSelectionMenu.spantype, RichEditorSpanType.IMAGE)
    assertEqual(JSON.parse(bindSelectionMenu4).$attrs.bindSelectionMenu.responseType, ResponseType.RightClick)
    assertEqual(JSON.parse(bindSelectionMenu4).$attrs.bindSelectionMenu.options, {
      onAppear: () => {
      }
    })
    await button2.tap()
    let bindSelectionMenu5: string = await richEditor2.getInspectorInfo()
    assertEqual(JSON.parse(bindSelectionMenu5).$attrs.bindSelectionMenu.responseType, RichEditorResponseType.SELECT)
  }, 0)
}