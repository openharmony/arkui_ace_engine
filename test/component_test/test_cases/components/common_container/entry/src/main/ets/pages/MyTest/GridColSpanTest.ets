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

export default async function GridColSpanTest() {
  /*
   * GridCol组件 Span属性
   * 找到画面id为gridColSpan的Span组件
   * 找到画面文本为GridColSpan的Button组件
   * 获取gridCol的Span属性与期待值3比对
   * 点击button，变更gridCol的Span属性值为{ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 }
   * 获取gridCol的Span属性与期待值{ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 }比对
   */
  defineTest('GridColSpanTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridColSpanTestDemo running')
    let driver: Tester = Tester.create()
    let gridCol: Component = await driver.findComponent(Matcher.create().id('gridColSpan').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridColSpan').enabled(true))

    let span1: string = await gridCol.getInspectorInfo()
    assertEqual(JSON.parse(span1).$attrs.span, '3')

    await button.tap()
    let span2: string = await gridCol.getInspectorInfo()
    assertEqual(JSON.parse(span2).$attrs.span.xs, 1)
    assertEqual(JSON.parse(span2).$attrs.span.sm, 2)
    assertEqual(JSON.parse(span2).$attrs.span.md, 3)
    assertEqual(JSON.parse(span2).$attrs.span.lg, 4)
    assertEqual(JSON.parse(span2).$attrs.span.xl, 5)
    assertEqual(JSON.parse(span2).$attrs.span.xxl, 6)
  })
}