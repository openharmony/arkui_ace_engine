/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
@Entry
@Component
struct CounterExample {
  @State value: number = 0;
  @State status: number = 0;

  build() {
    Scroll(){
      Column(){
        Image($r("app.media.success")).width(100).height(100).borderWidth(1).backgroundColor(Color.Red)
        Image($r("app.media.failure")).width(100).height(100).borderWidth(1).backgroundColor(Color.Red)
        Image($r("app.media.ls_bottom")).width(100).height(100).borderWidth(1).backgroundColor(Color.Red)
        Image($r("app.media.ls_middle")).width(100).height(100).borderWidth(1).backgroundColor(Color.Red)
        Image($r("app.media.ls_top")).width(100).height(100).borderWidth(1).backgroundColor(Color.Red)
        Image($r("app.media.foreground")).width(100).height(100).borderWidth(1).backgroundColor(Color.Red)
        Text('-----------------')
        Image($r("app.media.alert_circle_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.all_checked")).width(100).height(100).borderWidth(1)
        Image($r("app.media.all_select")).width(100).height(100).borderWidth(1)
        Image($r("app.media.all_selected")).width(100).height(100).borderWidth(1)
        Image($r("app.media.apps_big")).width(100).height(100).borderWidth(1)
        Image($r("app.media.arrow_back_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.arrow_redo_circle_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.back")).width(100).height(100).borderWidth(1)
        Image($r("app.media.background")).width(100).height(100).borderWidth(1)
        Image($r("app.media.bg")).width(100).height(100).borderWidth(1)
        Image($r("app.media.blackBg")).width(100).height(100).borderWidth(1)
        Image($r("app.media.camera_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.camera_tab")).width(100).height(100).borderWidth(1)
        Image($r("app.media.car_sport_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.check")).width(100).height(100).borderWidth(1)
        Image($r("app.media.checked")).width(100).height(100).borderWidth(1)
        Image($r("app.media.checkmark_circle_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.checkmark_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.chevron_forward")).width(100).height(100).borderWidth(1)
        Image($r("app.media.chevron_forward_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.close")).width(100).height(100).borderWidth(1)
        Image($r("app.media.copy_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.create_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.download")).width(100).height(100).borderWidth(1)
        Image($r("app.media.download_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.eyes_Visible")).width(100).height(100).borderWidth(1)
        Image($r("app.media.eye_off_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.eye_outline")).width(100).height(100).borderWidth(1)

        Image($r("app.media.film")).width(100).height(100).borderWidth(1)
        Image($r("app.media.film_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.film_tab")).width(100).height(100).borderWidth(1)
        Image($r("app.media.flash")).width(100).height(100).borderWidth(1)
        Image($r("app.media.flash_outline")).width(100).height(100).borderWidth(1).id('100')
        Image($r("app.media.full_screen")).width(100).height(100).borderWidth(1)
        Image($r("app.media.image")).width(100).height(100).borderWidth(1)
        Image($r("app.media.image_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.image_tab")).width(100).height(100).borderWidth(1)
        Image($r("app.media.journal_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.key_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.leaf_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.list_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.mic_off")).width(100).height(100).borderWidth(1)
        Image($r("app.media.mic_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.open_eyes_last")).width(100).height(100).borderWidth(1)
        Image($r("app.media.out_screen")).width(100).height(100).borderWidth(1)
        Image($r("app.media.pause")).width(100).height(100).borderWidth(1)
        Image($r("app.media.person_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.play")).width(100).height(100).borderWidth(1)
        Image($r("app.media.pulse_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.radio_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.refresh_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.reset")).width(100).height(100).borderWidth(1)
        Image($r("app.media.ribbon_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.Right")).width(100).height(100).borderWidth(1)
        Image($r("app.media.RightTwo")).width(100).height(100).borderWidth(1)
        Image($r("app.media.save_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.scan_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.settings")).width(100).height(100).borderWidth(1)
        Image($r("app.media.settings_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.settings_tab")).width(100).height(100).borderWidth(1)
        Image($r("app.media.startIcon")).width(100).height(100).borderWidth(1)
        Image($r("app.media.stopwatch_outline")).width(100).height(100).borderWidth(1)

        Image($r("app.media.time_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.trash_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.videocam")).width(100).height(100).borderWidth(1)
        Image($r("app.media.videocam_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.video_tab")).width(100).height(100).borderWidth(1)
        Image($r("app.media.volume_medium_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.warning_outline")).width(100).height(100).borderWidth(1)
        Image($r("app.media.wifi")).width(100).height(100).borderWidth(1)
      }
    }.width("100%").height("100%")
  }
}
