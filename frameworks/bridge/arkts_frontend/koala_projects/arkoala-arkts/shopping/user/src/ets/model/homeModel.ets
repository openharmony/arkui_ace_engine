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

export class TabTitleModel {
  public id: number
  public uri: string
  public selectedUri: string
  public title: string
  constructor(id: number, uri: string, selectedUri: string, title: string) {
    this.id = id;
    this.uri = uri;
    this.selectedUri = selectedUri;
    this.title = title;
  }
}

export class SearchTextModel {
  public searchText: string
  constructor(searchText: string) {
    this.searchText = searchText;
  }
}

export class NavDataModel {
  public navData: string
  constructor(navData: string) {
    this.navData = navData;
  }
}

export class SwiperModel {
  public img: string
  constructor(img: string) {
    this.img = img;
  }
}

export class TitleBarModel {
  public id: number
  public title: string
  constructor(id: number, title: string) {
    this.id = id;
    this.title = title;
  }
}

export class ProductDataModel {
  public uri: string
  public title: string
  public labels: string
  public price: string
  public index: number
  constructor(uri: string, title: string, labels: string, price: string, index: number) {
    this.uri = uri;
    this.title = title;
    this.labels = labels;
    this.price = price;
    this.index = index;
  }
}

export class CoreDataModel {
  public uri: string
  public title: string
  constructor(uri: string, title: string) {
    this.uri = uri;
    this.title = title;
  }
}

export class BoutiqueModel {
  public text1: string
  public text2: string
  public img1: string
  public img2: string
  constructor(text1: string, text2: string, img1: string, img2: string) {
    this.text1 = text1;
    this.text2 = text2;
    this.img1 = img1;
    this.img2 = img2;
  }
}

export class InformationModel {
  public uri: string
  public title: string
  public notice: string
  public time: string
  constructor(uri: string, title: string, notice: string, time: string) {
    this.uri = uri;
    this.title = title;
    this.notice = notice;
    this.time = time;
  }
}

export class ShopCartItemDataModel {
  public img: string
  public title: string
  constructor(img: string, title: string) {
    this.img = img;
    this.title = title;
  }
}

export class FindTitleTextModel {
  public titleText: string
  constructor(titleText: string) {
    this.titleText = titleText;
  }
}

export class FindImgSrcModel {
  public imgSrc: string
  constructor(imgSrc: string) {
    this.imgSrc = imgSrc;
  }
}

export class FindImgIntroModel {
  public imgIntro: string
  constructor(imgIntro: string) {
    this.imgIntro = imgIntro;
  }
}

export class FindImgNameModel {
  public imgName: string
  constructor(imgName: string) {
    this.imgName = imgName;
  }
}

export class FindIconSrcModel {
  public iconSrc: string
  constructor(iconSrc: string) {
    this.iconSrc = iconSrc;
  }
}

export class RecordModel {
  public img: string
  public title: string
  public uri: string
  constructor(img: string, title: string, uri: string) {
    this.img = img;
    this.title = title;
    this.uri = uri;
  }
}

export class OrderModel {
  public id: number
  public img: string
  public title: string
  public uri: string
  constructor(id: number, img: string, title: string, uri: string) {
    this.id = id;
    this.img = img;
    this.title = title;
    this.uri = uri;
  }
}

export class DiscountModel {
  public img: string
  public name: string
  public text: string
  constructor(img: string, name: string, text: string) {
    this.img = img;
    this.name = name;
    this.text = text;
  }
}

export class ServiceModel {
  public img: string
  public title: string
  public uri: string
  constructor(img: string, title: string, uri: string) {
    this.img = img;
    this.title = title;
    this.uri = uri;
  }
}