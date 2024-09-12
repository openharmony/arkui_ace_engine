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
import { assertEqual } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function grayScaleTest() {
  /*
  * image组件 grayscale属性
  * 找到画面id为 imageGrayscale1 的image组件
  * 找到画面文本为ButtonGrayScale1、ButtonGrayScale2的Button组件
  * 获取 imageGrayscale1 的grayscale属性与期待值1比对
  * 点击button1，变更 imageGrayscale1 的grayscale属性值为-1
  * 获取imageGrayscale1的grayscale属性与期待值0比对
  * 点击button2，变更imageGrayscale1的grayscale属性值为2
  * 获取imageGrayscale1的grayscale属性与期待值1比对
  */
  defineTest('grayScaleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("grayScaleTestDemo running")
    let driver: Tester = Tester.create()
    let imageGrayscale1: Component = await driver.findComponent(Matcher.create().id('imageGrayscale1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonGrayScale1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonGrayScale2').enabled(true))
    let grayscale1: string = await imageGrayscale1.getInspectorInfo()
    assertEqual(JSON.parse(grayscale1).$attrs.grayscale, 1)
    await button1.tap()
    let grayscale2: string = await imageGrayscale1.getInspectorInfo()
    assertEqual(JSON.parse(grayscale2).$attrs.grayscale, 0)
    await button2.tap()
    let grayscale3: string = await imageGrayscale1.getInspectorInfo()
    assertEqual(JSON.parse(grayscale3).$attrs.grayscale, 1)
  }, 0)
}