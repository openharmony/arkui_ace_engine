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

export default async function textBindSelectionMenuTest() {
  /*
   * Text组件 BindSelectionMenu属性
   * 找到画面id为textBindSelectionMenu1,textBindSelectionMenu2，textBindSelectionMenu3的Text组件
   * 找到画面文本为TextBindSelectionMenu的Button组件
   * 获取text1的BindSelectionMenu.spantype属性与期待值TextSpanType.IMAGE比对
   * 获取text1的BindSelectionMenu.content属性与期待值"Menu1"比对
   * 获取text1的BindSelectionMenu.content属性与期待值"Menu2"比对
   * 获取text1的BindSelectionMenu.responseType属性与期待值TextResponseType.RIGHT_CLICK比对
   * 获取text1的BindSelectionMenu.options属性与期待值{onDisappear: () => {console.info('自定义选择菜单关闭时回调');},onAppear: () => {console.info('自定义选择菜单弹出时回调');}}比对
   * 点击button1，变更text1的BindSelectionMenu属性BindSelectionMenu.spantype值为TextSpanType.MIXED
   * 变更text1的BindSelectionMenu属性BindSelectionMenu.responseType值为TextResponseType.LONG_PRESS
   * 获取text1的BindSelectionMenu属性BindSelectionMenu.spantype与期待值TextSpanType.MIXED比对
   * 获取text1的BindSelectionMenu属性BindSelectionMenu.responseType与期待值TextResponseType.LONG_PRESS比对
   * 获取text2的BindSelectionMenu.spantype属性与期待值textSpanType.IMAGE比对
   * 获取text2的BindSelectionMenu.responseType属性与期待值textResponseType.RIGHT_CLICK比对
   * 获取text2的BindSelectionMenu.options属性与期待值onAppear: () => {}比对
   * 点击button2，变更text2的BindSelectionMenu属性BindSelectionMenu.spantype值为textResponseType.SELECT
   * 获取text2的BindSelectionMenu.spantype属性与期待值TextSpanType.TEXT比对
   * 获取text2的BindSelectionMenu.content属性与期待值"Menu1"比对
   * 获取text2的BindSelectionMenu.content属性与期待值"Menu2"比对
   * 获取text2的BindSelectionMenu.responseType属性与期待值TextResponseType.LONG_PRESS比对
   */
  defineTest('textBindSelectionMenuTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textBindSelectionMenuTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textBindSelectionMenu1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textBindSelectionMenu2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextBindSelectionMenu').enabled(true))

    let bindSelectionMenu1: string = await text1.getInspectorInfo()
    assertFalse(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu == undefined)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.spantype, TextSpanType.IMAGE)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.content, "Menu1")
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.content, "Menu2")
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.responseType, TextResponseType.RIGHT_CLICK)
    assertEqual(JSON.parse(bindSelectionMenu1).$attrs.bindSelectionMenu.options, {
      onDisappear: () => {
        console.log('自定义选择菜单关闭时回调');

      },
      onAppear: () => {
        console.log('自定义选择菜单弹出时回调');
      }
    })
    let bindSelectionMenu2: string = await text2.getInspectorInfo()
    await text2.press()
    let menu2: Component = await driver.findComponent(Matcher.create().text('Menu1').enabled())
    let type2: string = await menu2.getType()
    assertEqual(type2, 'MenuItem')
    assertEqual(JSON.parse(bindSelectionMenu2).$attrs.bindSelectionMenu.spantype, TextSpanType.TEXT)
    assertEqual(JSON.parse(bindSelectionMenu2).$attrs.bindSelectionMenu.content, "Menu1")
    assertEqual(JSON.parse(bindSelectionMenu2).$attrs.bindSelectionMenu.content, "Menu2")
    assertEqual(JSON.parse(bindSelectionMenu2).$attrs.bindSelectionMenu.responseType, TextResponseType.LONG_PRESS)

    await button.tap()
    let bindSelectionMenu3: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(bindSelectionMenu3).$attrs.bindSelectionMenu.spantype, TextSpanType.MIXED)
    assertEqual(JSON.parse(bindSelectionMenu3).$attrs.bindSelectionMenu.responseType, TextResponseType.LONG_PRESS)
  }, 0)
}