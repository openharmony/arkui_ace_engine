/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//import web_webview from '@ohos.web.webview'

@Entry
@Component
struct WebTest {
  //controller: web_webview.WebviewController = new web_webview.WebviewController()
  controller: WebController = new WebController()
  testObj = {
    testMethod: (data: number) => {
      return "testObj.test data = " + data
    },
    toStringMethod: () => {
      return ('testObj.toString')
    }
  }

  build() {
      Web(
        { src: 'www.example.com', controller: this.controller }
        )
        .javaScriptAccess(true)
        .fileAccess(false)
        .onlineImageAccess(true)
        .domStorageAccess(false)
        .imageAccess(true)
        .mixedMode(MixedMode.None)
        .zoomAccess(false)
        .geolocationAccess(true)
        .javaScriptProxy({ object: this.testObj, name: "objName", methodList: ["testMethod", "toStringMethod"], controller: this.controller })
        .password(false)
        .cacheMode(CacheMode.Only)
        .darkMode(WebDarkMode.Auto)
        .forceDarkAccess(true)
        .mediaOptions({resumeInterval: 10, audioExclusive: true})
        .tableData(false)
        .wideViewModeAccess(true)
        .overviewModeAccess(false)
        .textZoomRatio(55)
        .databaseAccess(true)
        .initialScale(77)
        .userAgent("User Agent")
        .mediaPlayGestureAccess(false)
        .multiWindowAccess(true)
        .webStandardFont("arial")
        .webSerifFont("serif")
        .webSansSerifFont("sans-serif")
        .webFixedFont("monospace")
        .webFantasyFont("fantasy")
        .webCursiveFont("cursive")
        .defaultFixedFontSize(12)
        .defaultFontSize(14)
        .minFontSize(10)
        .minLogicalFontSize(8)
        .blockNetwork(false)
        .horizontalScrollBarAccess(true)
        .pinchSmooth(false)
        .allowWindowOpenMethod(true)
        .layoutMode(WebLayoutMode.FIT_CONTENT)
        .nestedScroll({scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARENT_FIRST })
        .enableNativeEmbedMode(false)
        .copyOptions(CopyOptions.CROSS_DEVICE)
        .overScrollMode(OverScrollMode.ALWAYS)
        .javaScriptOnDocumentStart([{script: "script_1", scriptRules: ["rule_11"]}, {script: "script_2", scriptRules: ["rule_21", "rule_22"]}])
        .javaScriptOnDocumentEnd([{script: "script_1", scriptRules: ["rule_11", "rule_12"]}, {script: "script_2", scriptRules: ["rule_21"]}])
  }
}
