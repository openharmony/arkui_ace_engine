'use static'

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
  LengthMetrics,
  ComponentContent,
  Column,
  ColumnOptions,
  Row,
  RowOptions,
  NavDestination,
  Entry,
  Component,
  Builder,
  Text,
  Image,
  List,
  ListOptions,
  ListItem,
  $r,
  Color,
  ResourceStr,
  Resource,
  Alignment,
  UIContext,
  wrapBuilder
} from '@kit.ArkUI';
import { ArcList, ArcListItem, ArkListOptions } from '@ohos.arkui.ArcList';
import { SubHeaderV2 } from '@ohos.arkui.advanced.SubHeaderV2';
import { ComponentCard } from '../../common/Card';

@Builder
function customHeader(): void {
  Column() {
    Text($r('app.string.ArcListCrown_set'))
      .fontColor('#FFFFFFFF')
      .fontSize('19fp')
  }
}

@Entry
@Component
export struct ArcListStyles {
  context: UIContext = this.getUIContext();
  arcListHeader: ComponentContent<Object> = new ComponentContent<Object>(this.context, wrapBuilder(customHeader));

  @Builder
  TitleBuilderDisplay(): void {
    Text($r('app.string.ArcListStyles_Display'))
      .fontSize('35px')
      .fontColor('#FFFFFFFF')
  }

  @Builder
  TitleBuilderInternet(): void {
    Text($r('app.string.internet'))
      .fontSize('35px')
      .fontColor('#FFFFFFFF')
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        List({ space: 12 } as ListOptions) {
          ListItem() {
            ComponentCard({ title: $r('app.string.ArcListStyles_head') }) {
              ArcList({ header: this.arcListHeader }) {
                ArcListItem() {
                  Row() {
                    Image($r('app.media.wlan')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_wlan')).fontSize('38px').fontColor('#FFFFFFFF')
                      Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.blueTooth')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_blue')).fontSize('38px').fontColor('#FFFFFFFF')
                      Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.mobileData')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_net')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.ic_settings_more_connections')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_connect')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.displayAndBrightness')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_light')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')
              }
              .width('466px')
              .height('466px')
              .space(LengthMetrics.px(10))
              .borderRadius('233px')
              .backgroundColor(Color.Black)
            }
          }

          ListItem() {
            ComponentCard({ title: $r('app.string.ArcListStyles_titleSpacing') }) {
              ArcList({ initialIndex: 2 }) {
                ArcListItem() {
                  Row() {
                    Image($r('app.media.wlan')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_wlan')).fontSize('38px').fontColor('#FFFFFFFF')
                      Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.blueTooth')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_blue')).fontSize('38px').fontColor('#FFFFFFFF')
                      Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.mobileData')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_net')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.ic_settings_more_connections')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_connect')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.displayAndBrightness')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_light')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('129px')
                .backgroundColor('#26FFFFFF')
              }
              .space(LengthMetrics.px(30))
              .width('466px')
              .height('466px')
              .borderRadius('233px')
              .backgroundColor(Color.Black)
            }
          }

          ListItem() {
            ComponentCard({ title: $r('app.string.ArcListStyles_titleScale') }) {
              ArcList({ initialIndex: 2 }) {
                ArcListItem() {
                  Row() {
                    Column() {
                      SubHeaderV2({
                        titleBuilder: (): void => {
                          this.TitleBuilderInternet();
                        },
                      })
                    }
                  }
                  .padding({ left: '125px', right: '120px' })
                }
                .autoScale(false)
                .width('414px')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.wlan')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_wlan')).fontSize('38px').fontColor('#FFFFFFFF')
                      Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('100px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.mobileData')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_net')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .autoScale(false)
                .borderRadius('65px')
                .width('414px')
                .height('100px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                    Column() {
                      SubHeaderV2({
                        titleBuilder: (): void => {
                          this.TitleBuilderDisplay();
                        }
                      })
                    }
                  .padding({ left: '125px', right: '120px' })
                }
                .autoScale(false)
                .width('414px')
                .height('40px')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.displayAndBrightness')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_light')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('100px')
                .backgroundColor('#26FFFFFF')
                // .autoScale(false)

                ArcListItem() {
                  Row() {
                    Image($r('app.media.ic_settings_more_connections')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_connect')).fontSize('38px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('100px')
                .backgroundColor('#26FFFFFF')

                ArcListItem() {
                  Row() {
                    Image($r('app.media.blueTooth')).width('99px').height('99px')
                      .borderRadius('50px').margin({ left: 7 })
                    Column() {
                      Text($r('app.string.ArcListStyles_blue')).fontSize('38px').fontColor('#FFFFFFFF')
                      Text($r('app.string.ArcListStyles_open')).fontSize('20px').fontColor('#FFFFFFFF')
                    }.width('190px')

                    Image($r('app.media.ic_settings_arrow')).width('92px').height('92px')
                      .borderRadius('50px')
                  }
                }
                .borderRadius('65px')
                .width('414px')
                .height('100px')
                .backgroundColor('#26FFFFFF')
              }
              .width('466px')
              .height('466px')
              .space(LengthMetrics.px(16))
              .borderRadius('233px')
              .backgroundColor(Color.Black)
            }
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Replace $r('app.string.ArcListStyles_title') with actual resource file.
    // In this example, the resource file's value is "Customize arc list styles"
    .title($r('app.string.ArcListStyles_title'))
  }
}
