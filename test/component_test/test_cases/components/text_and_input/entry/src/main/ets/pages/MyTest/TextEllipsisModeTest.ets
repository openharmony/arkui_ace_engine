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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textEllipsisModeTest() {
  /*
   * Text组件 EllipsisMode属性
   * 找到画面id为textEllipsisMode1,textEllipsisMode2的Text组件
   * 找到画面文本为TextEllipsisMode的Button组件
   * 获取text1的EllipsisMode属性与期待值'EllipsisMode.START'比对
   * 获取text2的EllipsisMode属性与期待值'EllipsisMode.CENTER'比对
   * 点击button，变更text2的EllipsisMode属性值为EllipsisMode.END
   * 获取text2的EllipsisMode属性与期待值'EllipsisMode.END'比对
   */
  defineTest('textEllipsisModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textEllipsisModeTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textEllipsisMode1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textEllipsisMode2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextEllipsisMode').enabled(true))

    let ellipsisMode1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(ellipsisMode1).$attrs.ellipsisMode, 'EllipsisMode.START')
    let ellipsisMode2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(ellipsisMode2).$attrs.ellipsisMode, 'EllipsisMode.CENTER')

    await button.tap()
    let ellipsisMode3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(ellipsisMode3).$attrs.ellipsisMode, 'EllipsisMode.END')
  }, 0)
}