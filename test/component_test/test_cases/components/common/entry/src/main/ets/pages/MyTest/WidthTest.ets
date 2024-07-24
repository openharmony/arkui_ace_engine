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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function widthTest() {
  /*
  * 使用Column，Rect组件 Width属性
  * 找到画面id为columnWidth，rectWidth的Column，Rect组件
  * 找到画面文本为ButtonWidth的Button组件
  * 获取columnWidth1的Width属性与期待值20.00vp比对
  * 获取columnWidth2的Width属性与期待值'100.00px'比对
  * 点击button，变更columnWidth2的Width属性值为$r('app.string.common_width')
  * 获取columnWidth2的Width属性与期待值$r('app.string.common_width')比对
  */
  defineTest('widthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('widthTestDemo running')
    let driver: Tester = Tester.create()
    let columnWidth: Component = await driver.findComponent(Matcher.create().id('columnWidth').enabled(true))
    let rectWidth: Component = await driver.findComponent(Matcher.create().id('rectWidth').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonWidth').enabled(true))
    let width1: string = await columnWidth.getInspectorInfo()
    assertEqual(JSON.parse(width1).$attrs.width, '20.00vp')
    let width2: string = await rectWidth.getInspectorInfo()
    assertEqual(JSON.parse(width2).$attrs.width, '100.00px')
    await button.tap()
    let width3: string = await rectWidth.getInspectorInfo()
    assertEqual(JSON.parse(width3).$attrs.width, $r('app.string.common_width'))
  }, 0)
}