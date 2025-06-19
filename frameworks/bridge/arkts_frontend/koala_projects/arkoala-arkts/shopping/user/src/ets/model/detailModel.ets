/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

export class SwiperModel {
  public src: string
  constructor(src: string) {
    this.src = src;
  }
}

export class PhoneTypeModel {
  public uri: string
  public color: string
  constructor(uri: string, color: string) {
    this.uri = uri;
    this.color = color;
  }
}

export class RecommendDataModel {
  public img: string
  public title: string
  public price: string
  constructor(img: string, title: string, price: string) {
    this.img = img;
    this.title = title;
    this.price = price;
  }
}

export class ShowImgModel {
  public uri: string
  constructor(uri: string) {
    this.uri = uri;
  }
}

export class GoodsInfoModel {
  public img: string
  constructor(img: string) {
    this.img = img;
  }
}

export class ListDataModel {
  public img: string
  public title: string
  public price: string
  constructor(img: string, title: string, price: string) {
    this.img = img;
    this.title = title;
    this.price = price;
  }
}