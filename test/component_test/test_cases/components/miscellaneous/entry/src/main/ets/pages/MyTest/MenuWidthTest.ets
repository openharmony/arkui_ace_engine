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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function menuWidthTest() {
  /*
* Menu组件 Width属性
* 找到画面id为menuWidth1、 menuWidth2的Menu组件
* 找到画面文本为MenuWidth的Button组件
* 获取menu1的Width属性值与期待值'220.00vp'比对
* 点击button1，变更menu1的Width属性值为'200px'
* 获取menu1的Width属性值与期待值'200.00px'比对
* 获取menu2的Width属性值与期待值$r('app.string.menu_width')比对
*/
  defineTest('menuWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuWidthTestDemo running')
    let driver: Tester = Tester.create()
    let menu1: Component = await driver.findComponent(Matcher.create().id('menuWidth1').enabled(true))
    let menu2: Component = await driver.findComponent(Matcher.create().id('menuWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('MenuWidth').enabled(true))

    let width1: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(width1).$attrs.width, '220.00vp')
    await button.tap()
    let width2: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(width2).$attrs.width, '200.00px')
    let width3: string = await menu2.getInspectorInfo()
    assertEqual(JSON.parse(width3).$attrs.width, $r('app.string.menu_width'))
  }, 0)
}