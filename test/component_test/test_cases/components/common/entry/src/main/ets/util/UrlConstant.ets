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

export class UrlClass {
  buttonName: string;
  buttonUrl: string;
  data: string;

  constructor(buttonName: string, buttonUrl: string, data: string) {
    this.buttonName = buttonName;
    this.buttonUrl = buttonUrl;
    this.data = data;
  }
}

export let ScrollUrlClass: UrlClass[] = [
  new UrlClass('ScrollCreate', 'pages/container/scroll/ScrollCreateSample', ''),
  new UrlClass('ScrollWidth', 'pages/container/scroll/ScrollWidthSample', ''),
  new UrlClass('ScrollHeight', 'pages/container/scroll/ScrollHeightSample', ''),
  new UrlClass('ScrollPadding', 'pages/container/scroll/ScrollPaddingSample', ''),
  new UrlClass('ScrollMargin', 'pages/container/scroll/ScrollMarginSample', ''),
  new UrlClass('ScrollEnableScrollInteraction', 'pages/container/scroll/ScrollEnableScrollInteractionSample', 'false'),
  new UrlClass('ScrollDrag', 'pages/container/scroll/ScrollDragSample', ''),
  new UrlClass('ScrollSlippage', 'pages/container/scroll/ScrollSlippageSample', ''),
  new UrlClass('ScrollScrollTo', 'pages/container/scroll/ScrollScrollToSample', ''),
  new UrlClass('ScrollScrollEdge', 'pages/container/scroll/ScrollScrollEdgeSample', ''),
  new UrlClass('ScrollEdgeEffect', 'pages/container/scroll/ScrollEdgeEffectSample', ''),
  new UrlClass('ScrollScrollBy', 'pages/container/scroll/ScrollScrollBySample', ''),
]