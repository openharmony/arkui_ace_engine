/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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

import { window } from '@kit.ArkUI';
import { AbilityConstant, UIAbility, Want, common } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { util } from '@kit.ArkTS';

const DOMAIN: number = 0x0000;
const TAG: string = 'WindowCtrlDemo';
const MAX_LOG_COUNT: number = 200;

interface LogEntry {
  time: string;
  level: string;
  msg: string;
}

interface WindowStateInfo {
  width: number;
  height: number;
  left: number;
  top: number;
  isFullScreen: boolean;
  isLayoutFullScreen: boolean;
  statusBarVisible: boolean;
  navBarVisible: boolean;
  density: number;
  focused: boolean;
}

interface SubWindowInfo {
  name: string;
  type: number;
  alive: boolean;
  visible: boolean;
  width: number;
  height: number;
}

interface SizeInput {
  width: number;
  height: number;
}

interface PosInput {
  x: number;
  y: number;
}

function formatTime(ts: number): string {
  let d = new Date(ts);
  let hh = d.getHours().toString().padStart(2, '0');
  let mm = d.getMinutes().toString().padStart(2, '0');
  let ss = d.getSeconds().toString().padStart(2, '0');
  let ms = d.getMilliseconds().toString().padStart(3, '0');
  return `${hh}:${mm}:${ss}.${ms}`;
}

function formatRect(w: number, h: number): string {
  return `${Math.round(w)} x ${Math.round(h)}`;
}

function boolText(v: boolean): string {
  return v ? 'true' : 'false';
}

@Entry
@Component
struct Index {
  @State logs: LogEntry[] = [];
  @State winState: WindowStateInfo = {
    width: 0, height: 0, left: 0, top: 0,
    isFullScreen: false, isLayoutFullScreen: false,
    statusBarVisible: true, navBarVisible: true,
    density: 1.0, focused: false
  };
  @State subWindows: SubWindowInfo[] = [];
  @State isMaximized: boolean = false;
  @State isMinimized: boolean = false;
  @State fullScreenOn: boolean = false;
  @State immersiveOn: boolean = false;
  @State listeningSize: boolean = false;
  @State listeningAvoid: boolean = false;
  @State listeningStatus: boolean = false;
  @State listeningKeyboard: boolean = false;
  @State sizeInput: SizeInput = { width: 1080, height: 2400 };
  @State posInput: PosInput = { x: 0, y: 0 };
  @State subWinNameInput: string = 'sub_1';
  @State subWinCount: number = 0;
  @State busy: boolean = false;
  @State lastOp: string = 'idle';
  @State keyboardHeight: number = 0;
  @State avoidTop: number = 0;
  @State avoidBottom: number = 0;
  @State winModeText: string = 'unknown';

  private mainWindow: window.Window | null = null;
  private ctx: common.UIAbilityContext | undefined = undefined;
  private sizeCallback: ((size: window.Size) => void) | null = null;
  private avoidCallback: ((data: window.AvoidAreaOptions) => void) | null = null;
  private statusCallback: ((status: window.WindowStatusType) => void) | null = null;
  private keyboardCallback: ((height: number) => void) | null = null;

  aboutToAppear(): void {
    this.ctx = getContext(this) as common.UIAbilityContext;
    this.log('info', 'demo aboutToAppear, ready to fetch main window');
    this.initMainWindow();
  }

  aboutToDisappear(): void {
    this.unregisterAllListeners();
    for (let s of this.subWindows) {
      this.destroySubWindowQuiet(s.name);
    }
  }

  private log(level: string, msg: string): void {
    let entry: LogEntry = { time: formatTime(Date.now()), level: level, msg: msg };
    let next = this.logs.concat([entry]);
    if (next.length > MAX_LOG_COUNT) {
      next = next.slice(next.length - MAX_LOG_COUNT);
    }
    this.logs = next;
    if (level === 'error') {
      hilog.error(DOMAIN, TAG, '%{public}s', msg);
    } else {
      hilog.info(DOMAIN, TAG, '%{public}s', msg);
    }
  }

  private clearLog(): void {
    this.logs = [];
    this.log('info', 'logs cleared');
  }

  private async initMainWindow(): Promise<void> {
    try {
      if (!this.ctx) {
        this.log('warn', 'ctx null, skip initMainWindow');
        return;
      }
      let win: window.Window = await window.getLastWindow(this.ctx);
      this.mainWindow = win;
      this.log('info', 'getLastWindow ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'getLastWindow failed: ' + JSON.stringify(e));
    }
  }

  private async refreshWindowState(): Promise<void> {
    if (!this.mainWindow) {
      return;
    }
    try {
      let prop = this.mainWindow.getWindowProperties();
      let sysBar = this.mainWindow.getWindowSystemBarProperties();
      let rect = prop.windowRect;
      this.winState = {
        width: rect.width,
        height: rect.height,
        left: rect.left,
        top: rect.top,
        isFullScreen: prop.isFullScreen,
        isLayoutFullScreen: prop.isLayoutFullScreen,
        statusBarVisible: sysBar?.statusBarContentColor !== undefined,
        navBarVisible: sysBar?.navigationBarContentColor !== undefined,
        density: prop.touchable ? 1 : 0,
        focused: prop.focusable
      };
      this.fullScreenOn = prop.isLayoutFullScreen;
    } catch (e) {
      this.log('error', 'refreshWindowState failed: ' + JSON.stringify(e));
    }
  }

  private setBusy(op: string): void {
    this.busy = true;
    this.lastOp = op;
  }

  private clearBusy(): void {
    this.busy = false;
  }

  private async maximizeWindow(): Promise<void> {
    this.setBusy('maximize');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip maximize');
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowLayoutFullScreen(true);
      this.isMaximized = true;
      this.isMinimized = false;
      this.log('info', 'maximize: setLayoutFullScreen(true) ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'maximize failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async minimizeWindow(): Promise<void> {
    this.setBusy('minimize');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip minimize');
        this.clearBusy();
        return;
      }
      try {
        await (this.mainWindow as window.Window).minimize();
        this.log('info', 'minimize() called');
      } catch (mErr) {
        this.log('warn', 'minimize() not supported on main window: ' + JSON.stringify(mErr));
      }
      await this.mainWindow.showWindow();
      this.log('info', 'showWindow() called after minimize attempt (restore foreground)');
      this.isMinimized = false;
      this.isMaximized = false;
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'minimize failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async restoreWindow(): Promise<void> {
    this.setBusy('restore');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip restore');
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowLayoutFullScreen(false);
      this.isMaximized = false;
      this.log('info', 'restore: setLayoutFullScreen(false) ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'restore failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async toggleFullScreen(): Promise<void> {
    this.setBusy('toggleFullScreen');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip toggleFullScreen');
        this.clearBusy();
        return;
      }
      let target = !this.fullScreenOn;
      await this.mainWindow.setWindowLayoutFullScreen(target);
      this.fullScreenOn = target;
      this.log('info', 'toggleFullScreen -> ' + boolText(target));
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'toggleFullScreen failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async enterImmersive(): Promise<void> {
    this.setBusy('enterImmersive');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip immersive');
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowLayoutFullScreen(true);
      await this.mainWindow.setWindowSystemBarEnable([]);
      this.immersiveOn = true;
      this.log('info', 'enterImmersive: fullScreen + hide sysbar ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'enterImmersive failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async exitImmersive(): Promise<void> {
    this.setBusy('exitImmersive');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip exitImmersive');
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowSystemBarEnable(['status', 'navigation']);
      await this.mainWindow.setWindowLayoutFullScreen(false);
      this.immersiveOn = false;
      this.log('info', 'exitImmersive: show sysbar + exit fullScreen ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'exitImmersive failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async showSystemBar(): Promise<void> {
    this.setBusy('showSystemBar');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowSystemBarEnable(['status', 'navigation']);
      this.log('info', 'showSystemBar ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'showSystemBar failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async hideSystemBar(): Promise<void> {
    this.setBusy('hideSystemBar');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowSystemBarEnable([]);
      this.log('info', 'hideSystemBar ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'hideSystemBar failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async hideStatusBarOnly(): Promise<void> {
    this.setBusy('hideStatusBar');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowSystemBarEnable(['navigation']);
      this.log('info', 'hideStatusBar only ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'hideStatusBarOnly failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async hideNavBarOnly(): Promise<void> {
    this.setBusy('hideNavBar');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowSystemBarEnable(['status']);
      this.log('info', 'hideNavBar only ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'hideNavBarOnly failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setWindowSizeBtn(): Promise<void> {
    this.setBusy('setWindowSize');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.resize(this.sizeInput.width, this.sizeInput.height);
      this.log('info', 'resize -> ' + formatRect(this.sizeInput.width, this.sizeInput.height));
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'setWindowSize failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async moveWindowBtn(): Promise<void> {
    this.setBusy('moveWindow');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.moveWindowTo(this.posInput.x, this.posInput.y);
      this.log('info', 'moveWindowTo -> (' + this.posInput.x + ',' + this.posInput.y + ')');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'moveWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setWindowFocusBtn(): Promise<void> {
    this.setBusy('setFocus');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowFocusable(true);
      this.log('info', 'setWindowFocusable ok');
    } catch (e) {
      this.log('error', 'setWindowFocus failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setBgRed(): Promise<void> {
    this.setBusy('setBgRed');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowBackgroundColor('#33FF0000');
      this.log('info', 'setWindowBackgroundColor red-ish ok');
    } catch (e) {
      this.log('error', 'setBgRed failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setBgBlue(): Promise<void> {
    this.setBusy('setBgBlue');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowBackgroundColor('#330000FF');
      this.log('info', 'setWindowBackgroundColor blue-ish ok');
    } catch (e) {
      this.log('error', 'setBgBlue failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setBgDefault(): Promise<void> {
    this.setBusy('setBgDefault');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowBackgroundColor('#00000000');
      this.log('info', 'setWindowBackgroundColor transparent ok');
    } catch (e) {
      this.log('error', 'setBgDefault failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async queryProperties(): Promise<void> {
    this.setBusy('queryProperties');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      let prop = this.mainWindow.getWindowProperties();
      this.log('info', 'getWindowProperties: rect=' + formatRect(prop.windowRect.width, prop.windowRect.height) +
        ' fullScreen=' + boolText(prop.isFullScreen) + ' layoutFull=' + boolText(prop.isLayoutFullScreen) +
        ' touchable=' + boolText(prop.touchable));
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'queryProperties failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async querySystemBar(): Promise<void> {
    this.setBusy('querySystemBar');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      let bar = this.mainWindow.getWindowSystemBarProperties();
      this.log('info', 'getWindowSystemBarProperties: statusColor=' + bar.statusBarContentColor +
        ' navColor=' + bar.navigationBarContentColor);
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'querySystemBar failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setSysBarContentDark(): Promise<void> {
    this.setBusy('sysBarDark');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      let prop: window.SystemBarProperties = {
        statusBarContentColor: '#000000',
        statusBarColor: '#FFFFFFFF',
        navigationBarContentColor: '#000000',
        navigationBarColor: '#FFFFFFFF'
      };
      await this.mainWindow.setWindowSystemBarProperties(prop);
      this.log('info', 'setSysBarContentDark ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'setSysBarContentDark failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setSysBarContentLight(): Promise<void> {
    this.setBusy('sysBarLight');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      let prop: window.SystemBarProperties = {
        statusBarContentColor: '#FFFFFF',
        statusBarColor: '#99000000',
        navigationBarContentColor: '#FFFFFF',
        navigationBarColor: '#99000000'
      };
      await this.mainWindow.setWindowSystemBarProperties(prop);
      this.log('info', 'setSysBarContentLight ok');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'setSysBarContentLight failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setStatusBarBgRed(): Promise<void> {
    this.setBusy('statusBgRed');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      let prop: window.SystemBarProperties = {
        statusBarContentColor: '#FFFFFF',
        statusBarColor: '#FFFF0000'
      };
      await this.mainWindow.setWindowSystemBarProperties(prop);
      this.log('info', 'setStatusBarBgRed ok');
    } catch (e) {
      this.log('error', 'setStatusBarBgRed failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setNavBarBgBlue(): Promise<void> {
    this.setBusy('navBgBlue');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      let prop: window.SystemBarProperties = {
        navigationBarContentColor: '#FFFFFF',
        navigationBarColor: '#FF0000FF'
      };
      await this.mainWindow.setWindowSystemBarProperties(prop);
      this.log('info', 'setNavBarBgBlue ok');
    } catch (e) {
      this.log('error', 'setNavBarBgBlue failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setPrivacyModeOn(): Promise<void> {
    this.setBusy('privacyOn');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowPrivacyMode(true);
      this.log('info', 'setWindowPrivacyMode(true) ok');
    } catch (e) {
      this.log('error', 'setPrivacyModeOn failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setPrivacyModeOff(): Promise<void> {
    this.setBusy('privacyOff');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowPrivacyMode(false);
      this.log('info', 'setWindowPrivacyMode(false) ok');
    } catch (e) {
      this.log('error', 'setPrivacyModeOff failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setSnapshotSkipOn(): Promise<void> {
    this.setBusy('snapshotSkipOn');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowPrivacyMode(true);
      this.log('info', 'setSnapshotSkip->privacyMode(true) ok');
    } catch (e) {
      this.log('error', 'setSnapshotSkipOn failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async setSnapshotSkipOff(): Promise<void> {
    this.setBusy('snapshotSkipOff');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      await this.mainWindow.setWindowPrivacyMode(false);
      this.log('info', 'setSnapshotSkip->privacyMode(false) ok');
    } catch (e) {
      this.log('error', 'setSnapshotSkipOff failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  @State uiVisibleToggle: boolean = true;
  private async toggleUIContentVisible(): Promise<void> {
    this.setBusy('toggleUIVisible');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      this.uiVisibleToggle = !this.uiVisibleToggle;
      await this.mainWindow.setWindowDecorVisible(this.uiVisibleToggle);
      this.log('info', 'setWindowDecorVisible -> ' + boolText(this.uiVisibleToggle));
    } catch (e) {
      this.log('error', 'toggleUIContentVisible failed: ' + JSON.stringify(e));
      this.uiVisibleToggle = !this.uiVisibleToggle;
    }
    this.clearBusy();
  }

  private async applyPresetPhone(): Promise<void> {
    this.sizeInput = { width: 1080, height: 2400 };
    await this.setWindowSizeBtn();
  }

  private async applyPresetTablet(): Promise<void> {
    this.sizeInput = { width: 1280, height: 800 };
    await this.setWindowSizeBtn();
  }

  private async applyPresetSmall(): Promise<void> {
    this.sizeInput = { width: 720, height: 1280 };
    await this.setWindowSizeBtn();
  }

  private async applyPresetSplit(): Promise<void> {
    this.sizeInput = { width: 540, height: 2400 };
    await this.setWindowSizeBtn();
  }

  private async movePresetTopLeft(): Promise<void> {
    this.posInput = { x: 0, y: 0 };
    await this.moveWindowBtn();
  }

  private async movePresetTopRight(): Promise<void> {
    this.posInput = { x: Math.max(0, this.winState.width - 540), y: 0 };
    await this.moveWindowBtn();
  }

  private async movePresetBottomLeft(): Promise<void> {
    this.posInput = { x: 0, y: Math.max(0, this.winState.height - 900) };
    await this.moveWindowBtn();
  }

  private async movePresetBottomRight(): Promise<void> {
    this.posInput = {
      x: Math.max(0, this.winState.width - 540),
      y: Math.max(0, this.winState.height - 900)
    };
    await this.moveWindowBtn();
  }

  private async movePresetCenter(): Promise<void> {
    this.posInput = {
      x: Math.max(0, Math.floor((this.winState.width - 540) / 2)),
      y: Math.max(0, Math.floor((this.winState.height - 900) / 2))
    };
    await this.moveWindowBtn();
  }

  private async runAllTests(): Promise<void> {
    this.setBusy('runAllTests');
    this.log('info', '==== runAllTests start ====');
    await this.queryProperties();
    await this.showSystemBar();
    await this.maximizeWindow();
    await this.queryProperties();
    await this.setSysBarContentDark();
    await this.setSysBarContentLight();
    await this.setPrivacyModeOn();
    await this.setPrivacyModeOff();
    await this.setSnapshotSkipOn();
    await this.setSnapshotSkipOff();
    await this.enterImmersive();
    await this.queryProperties();
    await this.exitImmersive();
    await this.applyPresetPhone();
    await this.applyPresetTablet();
    await this.applyPresetSmall();
    await this.movePresetTopLeft();
    await this.movePresetCenter();
    await this.restoreWindow();
    await this.refreshWindowState();
    this.log('info', '==== runAllTests done ====');
    this.clearBusy();
  }

  private async setAspect16x9(): Promise<void> {
    let h = this.winState.height > 0 ? this.winState.height : 2400;
    let w = Math.floor(h * 9 / 16);
    this.sizeInput = { width: w, height: h };
    await this.setWindowSizeBtn();
  }

  private async setAspect4x3(): Promise<void> {
    let h = this.winState.height > 0 ? this.winState.height : 2400;
    let w = Math.floor(h * 3 / 4);
    this.sizeInput = { width: w, height: h };
    await this.setWindowSizeBtn();
  }

  private async setAspect1x1(): Promise<void> {
    let h = this.winState.height > 0 ? this.winState.height : 2400;
    this.sizeInput = { width: h, height: h };
    await this.setWindowSizeBtn();
  }

  private async setAspectFull(): Promise<void> {
    this.sizeInput = { width: 1080, height: 2400 };
    await this.setWindowSizeBtn();
  }

  private async dumpAllInfo(): Promise<void> {
    this.setBusy('dumpAll');
    try {
      if (!this.mainWindow) {
        this.log('warn', 'mainWindow null, skip dump');
        this.clearBusy();
        return;
      }
      let prop = this.mainWindow.getWindowProperties();
      this.log('info', '--- dump start ---');
      this.log('info', 'windowRect: left=' + prop.windowRect.left + ' top=' + prop.windowRect.top +
        ' w=' + prop.windowRect.width + ' h=' + prop.windowRect.height);
      this.log('info', 'isFullScreen=' + boolText(prop.isFullScreen) +
        ' isLayoutFullScreen=' + boolText(prop.isLayoutFullScreen));
      this.log('info', 'touchable=' + boolText(prop.touchable) + ' focusable=' + boolText(prop.focusable));
      let bar = this.mainWindow.getWindowSystemBarProperties();
      this.log('info', 'statusBarContentColor=' + bar.statusBarContentColor);
      this.log('info', 'statusBarColor=' + bar.statusBarColor);
      this.log('info', 'navBarContentColor=' + bar.navigationBarContentColor);
      this.log('info', 'navBarColor=' + bar.navigationBarColor);
      this.log('info', 'listeners: size=' + boolText(this.listeningSize) +
        ' avoid=' + boolText(this.listeningAvoid) +
        ' status=' + boolText(this.listeningStatus) +
        ' kbd=' + boolText(this.listeningKeyboard));
      this.log('info', 'subWindows count=' + this.subWindows.length);
      this.log('info', '--- dump end ---');
      await this.refreshWindowState();
    } catch (e) {
      this.log('error', 'dumpAllInfo failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async minimizeToHome(): Promise<void> {
    this.setBusy('minToHome');
    try {
      if (!this.mainWindow) {
        this.clearBusy();
        return;
      }
      try {
        await (this.mainWindow as window.Window).minimize();
        this.log('info', 'minimizeToHome: minimize() called');
      } catch (mErr) {
        this.log('warn', 'minimizeToHome: minimize unsupported: ' + JSON.stringify(mErr));
      }
      this.isMinimized = true;
      this.isMaximized = false;
    } catch (e) {
      this.log('error', 'minimizeToHome failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async registerSizeListener(): Promise<void> {
    if (!this.mainWindow) {
      this.log('warn', 'mainWindow null, skip size listener');
      return;
    }
    if (this.listeningSize) {
      this.log('warn', 'size listener already on');
      return;
    }
    this.sizeCallback = (size: window.Size) => {
      this.log('info', 'windowSizeChange -> ' + formatRect(size.width, size.height));
      this.refreshWindowState();
    };
    try {
      this.mainWindow.on('windowSizeChange', this.sizeCallback);
      this.listeningSize = true;
      this.log('info', 'register windowSizeChange ok');
    } catch (e) {
      this.log('error', 'registerSizeListener failed: ' + JSON.stringify(e));
    }
  }

  private async unregisterSizeListener(): Promise<void> {
    if (!this.mainWindow) {
      return;
    }
    if (!this.listeningSize || !this.sizeCallback) {
      this.log('warn', 'size listener not on');
      return;
    }
    try {
      this.mainWindow.off('windowSizeChange', this.sizeCallback);
      this.listeningSize = false;
      this.sizeCallback = null;
      this.log('info', 'unregister windowSizeChange ok');
    } catch (e) {
      this.log('error', 'unregisterSizeListener failed: ' + JSON.stringify(e));
    }
  }

  private async registerAvoidListener(): Promise<void> {
    if (!this.mainWindow) {
      this.log('warn', 'mainWindow null, skip avoid listener');
      return;
    }
    if (this.listeningAvoid) {
      this.log('warn', 'avoid listener already on');
      return;
    }
    this.avoidCallback = (data: window.AvoidAreaOptions) => {
      let area = data.area;
      this.avoidTop = area.topRect.height;
      this.avoidBottom = area.bottomRect.height;
      this.log('info', 'avoidAreaChange type=' + data.type + ' top=' + area.topRect.height + ' bottom=' + area.bottomRect.height);
    };
    try {
      this.mainWindow.on('avoidAreaChange', this.avoidCallback);
      this.listeningAvoid = true;
      this.log('info', 'register avoidAreaChange ok');
    } catch (e) {
      this.log('error', 'registerAvoidListener failed: ' + JSON.stringify(e));
    }
  }

  private async unregisterAvoidListener(): Promise<void> {
    if (!this.mainWindow) {
      return;
    }
    if (!this.listeningAvoid || !this.avoidCallback) {
      this.log('warn', 'avoid listener not on');
      return;
    }
    try {
      this.mainWindow.off('avoidAreaChange', this.avoidCallback);
      this.listeningAvoid = false;
      this.avoidCallback = null;
      this.log('info', 'unregister avoidAreaChange ok');
    } catch (e) {
      this.log('error', 'unregisterAvoidListener failed: ' + JSON.stringify(e));
    }
  }

  private async registerStatusListener(): Promise<void> {
    if (!this.mainWindow) {
      this.log('warn', 'mainWindow null, skip status listener');
      return;
    }
    if (this.listeningStatus) {
      this.log('warn', 'status listener already on');
      return;
    }
    this.statusCallback = (status: window.WindowStatusType) => {
      this.log('info', 'windowStatusChange status=' + JSON.stringify(status));
    };
    try {
      this.mainWindow.on('windowStatusChange', this.statusCallback);
      this.listeningStatus = true;
      this.log('info', 'register windowStatusChange ok');
    } catch (e) {
      this.log('error', 'registerStatusListener failed: ' + JSON.stringify(e));
    }
  }

  private async unregisterStatusListener(): Promise<void> {
    if (!this.mainWindow) {
      return;
    }
    if (!this.listeningStatus || !this.statusCallback) {
      this.log('warn', 'status listener not on');
      return;
    }
    try {
      this.mainWindow.off('windowStatusChange', this.statusCallback);
      this.listeningStatus = false;
      this.statusCallback = null;
      this.log('info', 'unregister windowStatusChange ok');
    } catch (e) {
      this.log('error', 'unregisterStatusListener failed: ' + JSON.stringify(e));
    }
  }

  private async registerKeyboardListener(): Promise<void> {
    if (!this.mainWindow) {
      this.log('warn', 'mainWindow null, skip keyboard listener');
      return;
    }
    if (this.listeningKeyboard) {
      this.log('warn', 'keyboard listener already on');
      return;
    }
    this.keyboardCallback = (height: number) => {
      this.keyboardHeight = height;
      this.log('info', 'keyboardHeightChange -> ' + height);
    };
    try {
      this.mainWindow.on('keyboardHeightChange', this.keyboardCallback);
      this.listeningKeyboard = true;
      this.log('info', 'register keyboardHeightChange ok');
    } catch (e) {
      this.log('error', 'registerKeyboardListener failed: ' + JSON.stringify(e));
    }
  }

  private async unregisterKeyboardListener(): Promise<void> {
    if (!this.mainWindow) {
      return;
    }
    if (!this.listeningKeyboard || !this.keyboardCallback) {
      this.log('warn', 'keyboard listener not on');
      return;
    }
    try {
      this.mainWindow.off('keyboardHeightChange', this.keyboardCallback);
      this.listeningKeyboard = false;
      this.keyboardCallback = null;
      this.log('info', 'unregister keyboardHeightChange ok');
    } catch (e) {
      this.log('error', 'unregisterKeyboardListener failed: ' + JSON.stringify(e));
    }
  }

  private unregisterAllListeners(): void {
    if (this.listeningSize) {
      this.unregisterSizeListener();
    }
    if (this.listeningAvoid) {
      this.unregisterAvoidListener();
    }
    if (this.listeningStatus) {
      this.unregisterStatusListener();
    }
    if (this.listeningKeyboard) {
      this.unregisterKeyboardListener();
    }
  }

  private async createSubWindowBtn(): Promise<void> {
    this.setBusy('createSubWindow');
    try {
      if (!this.ctx) {
        this.log('warn', 'ctx null, skip createSubWindow');
        this.clearBusy();
        return;
      }
      let name = this.subWinNameInput || ('sub_' + (this.subWinCount + 1));
      this.subWinCount += 1;
      let cfg: window.Configuration = {
        name: name,
        windowType: window.WindowType.TYPE_DIALOG,
        ctx: this.ctx
      };
      let sub = await window.createWindow(cfg);
      await sub.resize(540, 900);
      await sub.moveWindowTo(120, 200);
      await sub.setUIContent('pages/Index');
      await sub.showWindow();
      this.log('info', 'createSubWindow ok: ' + name);
      this.subWindows = this.subWindows.concat([{
        name: name,
        type: window.WindowType.TYPE_DIALOG,
        alive: true,
        visible: true,
        width: 540,
        height: 900
      }]);
    } catch (e) {
      this.log('error', 'createSubWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async showSubWindow(name: string): Promise<void> {
    this.setBusy('showSub:' + name);
    try {
      let sub = await window.findWindow(name);
      await sub.showWindow();
      this.log('info', 'showSubWindow ok: ' + name);
      this.subWindows = this.subWindows.map(s => s.name === name ? {
        name: s.name, type: s.type, alive: s.alive, visible: true, width: s.width, height: s.height
      } : s);
    } catch (e) {
      this.log('error', 'showSubWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async hideSubWindow(name: string): Promise<void> {
    this.setBusy('hideSub:' + name);
    try {
      let sub = await window.findWindow(name);
      await sub.minimize();
      this.log('info', 'hideSubWindow (minimize) ok: ' + name);
      this.subWindows = this.subWindows.map(s => s.name === name ? {
        name: s.name, type: s.type, alive: s.alive, visible: false, width: s.width, height: s.height
      } : s);
    } catch (e) {
      this.log('error', 'hideSubWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async destroySubWindowQuiet(name: string): Promise<void> {
    try {
      let sub = await window.findWindow(name);
      await sub.destroyWindow();
    } catch (e) {
    }
  }

  private async destroySubWindow(name: string): Promise<void> {
    this.setBusy('destroySub:' + name);
    try {
      await this.destroySubWindowQuiet(name);
      this.log('info', 'destroySubWindow ok: ' + name);
      this.subWindows = this.subWindows.filter(s => s.name !== name);
    } catch (e) {
      this.log('error', 'destroySubWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async maximizeSubWindow(name: string): Promise<void> {
    this.setBusy('maxSub:' + name);
    try {
      let sub = await window.findWindow(name);
      try {
        await sub.maximize();
        this.log('info', 'maximize sub ok: ' + name);
      } catch (mErr) {
        await sub.resize(this.winState.width, this.winState.height);
        await sub.moveWindowTo(0, 0);
        this.log('info', 'maximize sub (resize fallback) ok: ' + name);
      }
      this.subWindows = this.subWindows.map(s => s.name === name ? {
        name: s.name, type: s.type, alive: s.alive, visible: true, width: this.winState.width, height: this.winState.height
      } : s);
    } catch (e) {
      this.log('error', 'maximizeSubWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async minimizeSubWindow(name: string): Promise<void> {
    this.setBusy('minSub:' + name);
    try {
      let sub = await window.findWindow(name);
      await sub.minimize();
      this.log('info', 'minimize sub (minimize) ok: ' + name);
      this.subWindows = this.subWindows.map(s => s.name === name ? {
        name: s.name, type: s.type, alive: s.alive, visible: false, width: s.width, height: s.height
      } : s);
    } catch (e) {
      this.log('error', 'minimizeSubWindow failed: ' + JSON.stringify(e));
    }
    this.clearBusy();
  }

  private async destroyAllSubWindows(): Promise<void> {
    this.setBusy('destroyAllSub');
    let names = this.subWindows.map(s => s.name);
    for (let n of names) {
      await this.destroySubWindowQuiet(n);
    }
    this.subWindows = [];
    this.log('info', 'destroyAllSubWindows ok, count=' + names.length);
    this.clearBusy();
  }

  private async setSubWinName(s: string): Promise<void> {
    this.subWinNameInput = s;
  }

  private onSizeWidthInput(val: string): void {
    let n = parseInt(val, 10);
    if (!isNaN(n) && n > 0) {
      this.sizeInput = { width: n, height: this.sizeInput.height };
    }
  }

  private onSizeHeightInput(val: string): void {
    let n = parseInt(val, 10);
    if (!isNaN(n) && n > 0) {
      this.sizeInput = { width: this.sizeInput.width, height: n };
    }
  }

  private onPosXInput(val: string): void {
    let n = parseInt(val, 10);
    if (!isNaN(n)) {
      this.posInput = { x: n, y: this.posInput.y };
    }
  }

  private onPosYInput(val: string): void {
    let n = parseInt(val, 10);
    if (!isNaN(n)) {
      this.posInput = { x: this.posInput.x, y: n };
    }
  }

  @Builder
  statusCell(label: string, value: string) {
    Column() {
      Text(label)
        .fontSize(11)
        .fontColor('#888888')
        .maxLines(1)
      Text(value)
        .fontSize(14)
        .fontColor('#222222')
        .fontWeight(FontWeight.Medium)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .alignItems(HorizontalAlign.Start)
    .layoutWeight(1)
    .padding(6)
  }

  @Builder
  ctrlBtn(label: string, color: string, enabled: boolean, action: () => void) {
    Button(label)
      .type(ButtonType.Capsule)
      .fontSize(13)
      .fontColor('#FFFFFF')
      .backgroundColor(enabled ? color : '#CCCCCC')
      .height(38)
      .layoutWeight(1)
      .enabled(enabled && !this.busy)
      .onClick(() => action())
  }

  @Builder
  sectionTitle(title: string) {
    Text(title)
      .fontSize(15)
      .fontWeight(FontWeight.Bold)
      .fontColor('#1F1F1F')
      .margin({ top: 10, bottom: 6 })
      .width('100%')
  }

  @Builder
  logItem(entry: LogEntry) {
    Row() {
      Text(entry.time)
        .fontSize(11)
        .fontColor('#999999')
        .width(110)
      Text(entry.level)
        .fontSize(11)
        .fontColor(entry.level === 'error' ? '#E53935' : (entry.level === 'warn' ? '#FB8C00' : '#43A047'))
        .width(46)
      Text(entry.msg)
        .fontSize(12)
        .fontColor('#333333')
        .layoutWeight(1)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .width('100%')
    .padding({ left: 8, right: 8, top: 3, bottom: 3 })
  }

  @Builder
  subWinItem(info: SubWindowInfo) {
    Row({ space: 6 }) {
      Column() {
        Text(info.name)
          .fontSize(13)
          .fontWeight(FontWeight.Medium)
          .fontColor('#222222')
        Text(formatRect(info.width, info.height) + (info.visible ? ' | visible' : ' | hidden'))
          .fontSize(11)
          .fontColor('#888888')
      }
      .alignItems(HorizontalAlign.Start)
      .layoutWeight(1)
      Button('show')
        .fontSize(11)
        .height(30)
        .enabled(info.alive && !info.visible && !this.busy)
        .onClick(() => this.showSubWindow(info.name))
      Button('hide')
        .fontSize(11)
        .height(30)
        .enabled(info.alive && info.visible && !this.busy)
        .onClick(() => this.hideSubWindow(info.name))
      Button('max')
        .fontSize(11)
        .height(30)
        .enabled(info.alive && !this.busy)
        .onClick(() => this.maximizeSubWindow(info.name))
      Button('min')
        .fontSize(11)
        .height(30)
        .enabled(info.alive && !this.busy)
        .onClick(() => this.minimizeSubWindow(info.name))
      Button('del')
        .fontSize(11)
        .height(30)
        .backgroundColor('#E53935')
        .enabled(info.alive && !this.busy)
        .onClick(() => this.destroySubWindow(info.name))
    }
    .width('100%')
    .padding({ top: 4, bottom: 4 })
  }

  build() {
    Scroll() {
      Column() {
        Text('Window Max/Min Control Demo')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .fontColor('#0B51C4')
          .margin({ top: 14, bottom: 4 })
          .width('100%')
          .textAlign(TextAlign.Center)
        Text('bundle: com.example.windowctrl')
          .fontSize(11)
          .fontColor('#999999')
          .margin({ bottom: 8 })
          .width('100%')
          .textAlign(TextAlign.Center)

        this.sectionTitle('Window State')
        Column() {
          Row() {
            this.statusCell('Width', this.winState.width.toFixed(0))
            this.statusCell('Height', this.winState.height.toFixed(0))
            this.statusCell('Left', this.winState.left.toFixed(0))
            this.statusCell('Top', this.winState.top.toFixed(0))
          }
          .width('100%')
          Row() {
            this.statusCell('FullScreen', boolText(this.winState.isFullScreen))
            this.statusCell('LayoutFull', boolText(this.winState.isLayoutFullScreen))
            this.statusCell('Density', this.winState.density.toFixed(2))
            this.statusCell('Status', this.winModeText)
          }
          .width('100%')
          Row() {
            this.statusCell('StatusBar', boolText(this.winState.statusBarVisible))
            this.statusCell('NavBar', boolText(this.winState.navBarVisible))
            this.statusCell('AvoidTop', this.avoidTop.toFixed(0))
            this.statusCell('AvoidBot', this.avoidBottom.toFixed(0))
          }
          .width('100%')
          Row() {
            this.statusCell('Maximized', boolText(this.isMaximized))
            this.statusCell('Minimized', boolText(this.isMinimized))
            this.statusCell('Immersive', boolText(this.immersiveOn))
            this.statusCell('Keyboard', this.keyboardHeight.toFixed(0))
          }
          .width('100%')
          Row() {
            this.statusCell('Busy', boolText(this.busy))
            this.statusCell('LastOp', this.lastOp)
          }
          .width('100%')
        }
        .width('94%')
        .padding(8)
        .backgroundColor('#F5F7FA')
        .borderRadius(10)
        .alignItems(HorizontalAlign.Center)

        this.sectionTitle('Maximize / Minimize / Restore')
        Row({ space: 8 }) {
          this.ctrlBtn('Maximize', '#0B51C4', true, () => { this.maximizeWindow() })
          this.ctrlBtn('Minimize', '#FB8C00', true, () => { this.minimizeWindow() })
          this.ctrlBtn('Restore', '#43A047', true, () => { this.restoreWindow() })
        }
        .width('94%')
        Row({ space: 8 }) {
          this.ctrlBtn('Toggle FullScreen', '#6755B3', true, () => { this.toggleFullScreen() })
          this.ctrlBtn('Enter Immersive', '#00897B', true, () => { this.enterImmersive() })
          this.ctrlBtn('Exit Immersive', '#8E6E53', true, () => { this.exitImmersive() })
        }
        .width('94%')
        .margin({ top: 8 })

        this.sectionTitle('System Bar Control')
        Row({ space: 8 }) {
          this.ctrlBtn('Show Bar', '#43A047', true, () => { this.showSystemBar() })
          this.ctrlBtn('Hide Bar', '#E53935', true, () => { this.hideSystemBar() })
          this.ctrlBtn('Hide Status', '#FB8C00', true, () => { this.hideStatusBarOnly() })
          this.ctrlBtn('Hide Nav', '#FB8C00', true, () => { this.hideNavBarOnly() })
        }
        .width('94%')

        this.sectionTitle('Window Size & Position')
        Row({ space: 8 }) {
          Text('W:').fontSize(12).width(28)
          TextInput({ text: this.sizeInput.width.toString() })
            .fontSize(12)
            .height(38)
            .layoutWeight(1)
            .type(InputType.Number)
            .onChange((v: string) => this.onSizeWidthInput(v))
          Text('H:').fontSize(12).width(28)
          TextInput({ text: this.sizeInput.height.toString() })
            .fontSize(12)
            .height(38)
            .layoutWeight(1)
            .type(InputType.Number)
            .onChange((v: string) => this.onSizeHeightInput(v))
          this.ctrlBtn('Resize', '#0B51C4', true, () => { this.setWindowSizeBtn() })
        }
        .width('94%')
        Row({ space: 8 }) {
          Text('X:').fontSize(12).width(28)
          TextInput({ text: this.posInput.x.toString() })
            .fontSize(12)
            .height(38)
            .layoutWeight(1)
            .type(InputType.Number)
            .onChange((v: string) => this.onPosXInput(v))
          Text('Y:').fontSize(12).width(28)
          TextInput({ text: this.posInput.y.toString() })
            .fontSize(12)
            .height(38)
            .layoutWeight(1)
            .type(InputType.Number)
            .onChange((v: string) => this.onPosYInput(v))
          this.ctrlBtn('Move', '#0B51C4', true, () => { this.moveWindowBtn() })
        }
        .width('94%')
        .margin({ top: 8 })
        Row({ space: 8 }) {
          this.ctrlBtn('Set Focus', '#6755B3', true, () => { this.setWindowFocusBtn() })
          this.ctrlBtn('Bg Red', '#E53935', true, () => { this.setBgRed() })
          this.ctrlBtn('Bg Blue', '#0B51C4', true, () => { this.setBgBlue() })
          this.ctrlBtn('Bg Clear', '#888888', true, () => { this.setBgDefault() })
        }
        .width('94%')
        .margin({ top: 8 })

        this.sectionTitle('Window Query')
        Row({ space: 8 }) {
          this.ctrlBtn('Properties', '#00897B', true, () => { this.queryProperties() })
          this.ctrlBtn('SystemBar', '#00897B', true, () => { this.querySystemBar() })
          this.ctrlBtn('Refresh', '#00897B', true, () => { this.refreshWindowState() })
        }
        .width('94%')

        this.sectionTitle('System Bar Color')
        Row({ space: 8 }) {
          this.ctrlBtn('Content Dark', '#222222', true, () => { this.setSysBarContentDark() })
          this.ctrlBtn('Content Light', '#888888', true, () => { this.setSysBarContentLight() })
          this.ctrlBtn('StatusBg Red', '#E53935', true, () => { this.setStatusBarBgRed() })
          this.ctrlBtn('NavBg Blue', '#0B51C4', true, () => { this.setNavBarBgBlue() })
        }
        .width('94%')

        this.sectionTitle('Privacy / Snapshot / UI Visible')
        Row({ space: 8 }) {
          this.ctrlBtn('Privacy On', '#FB8C00', true, () => { this.setPrivacyModeOn() })
          this.ctrlBtn('Privacy Off', '#43A047', true, () => { this.setPrivacyModeOff() })
          this.ctrlBtn('SkipSnap On', '#FB8C00', true, () => { this.setSnapshotSkipOn() })
          this.ctrlBtn('SkipSnap Off', '#43A047', true, () => { this.setSnapshotSkipOff() })
        }
        .width('94%')
        Row({ space: 8 }) {
          this.ctrlBtn('Toggle UIVisible', '#6755B3', true, () => { this.toggleUIContentVisible() })
        }
        .width('94%')
        .margin({ top: 8 })

        this.sectionTitle('Preset Window Size')
        Row({ space: 8 }) {
          this.ctrlBtn('Phone 1080x2400', '#0B51C4', true, () => { this.applyPresetPhone() })
          this.ctrlBtn('Tablet 1280x800', '#0B51C4', true, () => { this.applyPresetTablet() })
        }
        .width('94%')
        Row({ space: 8 }) {
          this.ctrlBtn('Small 720x1280', '#0B51C4', true, () => { this.applyPresetSmall() })
          this.ctrlBtn('Split 540x2400', '#0B51C4', true, () => { this.applyPresetSplit() })
        }
        .width('94%')
        .margin({ top: 8 })

        this.sectionTitle('Preset Window Position')
        Row({ space: 8 }) {
          this.ctrlBtn('TopLeft', '#00897B', true, () => { this.movePresetTopLeft() })
          this.ctrlBtn('TopRight', '#00897B', true, () => { this.movePresetTopRight() })
          this.ctrlBtn('BottomLeft', '#00897B', true, () => { this.movePresetBottomLeft() })
          this.ctrlBtn('BottomRight', '#00897B', true, () => { this.movePresetBottomRight() })
          this.ctrlBtn('Center', '#00897B', true, () => { this.movePresetCenter() })
        }
        .width('94%')

        this.sectionTitle('Aspect Ratio Preset')
        Row({ space: 8 }) {
          this.ctrlBtn('16:9', '#0B51C4', true, () => { this.setAspect16x9() })
          this.ctrlBtn('4:3', '#0B51C4', true, () => { this.setAspect4x3() })
          this.ctrlBtn('1:1', '#0B51C4', true, () => { this.setAspect1x1() })
          this.ctrlBtn('Full', '#0B51C4', true, () => { this.setAspectFull() })
        }
        .width('94%')

        this.sectionTitle('Info & Minimize')
        Row({ space: 8 }) {
          this.ctrlBtn('Dump All Info', '#00897B', true, () => { this.dumpAllInfo() })
          this.ctrlBtn('Min To Home', '#FB8C00', true, () => { this.minimizeToHome() })
        }
        .width('94%')

        this.sectionTitle('Batch Test')
        Row({ space: 8 }) {
          this.ctrlBtn('Run All Tests', '#E53935', true, () => { this.runAllTests() })
        }
        .width('94%')

        this.sectionTitle('Event Listeners')
        Row({ space: 8 }) {
          this.ctrlBtn(this.listeningSize ? 'Size ON' : 'Size OFF',
            this.listeningSize ? '#43A047' : '#888888', true,
            () => { this.listeningSize ? this.unregisterSizeListener() : this.registerSizeListener() })
          this.ctrlBtn(this.listeningAvoid ? 'Avoid ON' : 'Avoid OFF',
            this.listeningAvoid ? '#43A047' : '#888888', true,
            () => { this.listeningAvoid ? this.unregisterAvoidListener() : this.registerAvoidListener() })
          this.ctrlBtn(this.listeningStatus ? 'Status ON' : 'Status OFF',
            this.listeningStatus ? '#43A047' : '#888888', true,
            () => { this.listeningStatus ? this.unregisterStatusListener() : this.registerStatusListener() })
          this.ctrlBtn(this.listeningKeyboard ? 'Kbd ON' : 'Kbd OFF',
            this.listeningKeyboard ? '#43A047' : '#888888', true,
            () => { this.listeningKeyboard ? this.unregisterKeyboardListener() : this.registerKeyboardListener() })
        }
        .width('94%')
        Row({ space: 8 }) {
          this.ctrlBtn('Unregister All', '#E53935', true, () => { this.unregisterAllListeners() })
        }
        .width('94%')
        .margin({ top: 8 })

        this.sectionTitle('Sub Window Management')
        Row({ space: 8 }) {
          Text('Name:').fontSize(12).width(48)
          TextInput({ text: this.subWinNameInput })
            .fontSize(12)
            .height(38)
            .layoutWeight(1)
            .onChange((v: string) => this.subWinNameInput = v)
          this.ctrlBtn('Create', '#0B51C4', true, () => { this.createSubWindowBtn() })
        }
        .width('94%')
        ForEach(this.subWindows, (info: SubWindowInfo) => {
          this.subWinItem(info)
        }, (info: SubWindowInfo) => info.name)
        Row({ space: 8 }) {
          this.ctrlBtn('Destroy All Sub', '#E53935', this.subWindows.length > 0, () => { this.destroyAllSubWindows() })
        }
        .width('94%')
        .margin({ top: 6 })

        this.sectionTitle('Operation Log')
        Row({ space: 8 }) {
          this.ctrlBtn('Clear Log', '#888888', true, () => { this.clearLog() })
          Text('count: ' + this.logs.length.toString())
            .fontSize(11)
            .fontColor('#888888')
            .layoutWeight(1)
            .textAlign(TextAlign.End)
        }
        .width('94%')
        Column() {
          if (this.logs.length === 0) {
            Text('(no logs yet)')
              .fontSize(12)
              .fontColor('#AAAAAA')
              .padding(12)
          }
          ForEach(this.logs, (entry: LogEntry) => {
            this.logItem(entry)
          }, (entry: LogEntry) => entry.time + entry.msg)
        }
        .width('94%')
        .padding(4)
        .backgroundColor('#FFFFFF')
        .borderRadius(8)
        .border({ width: 1, color: '#EEEEEE' })
        .margin({ bottom: 20 })
      }
      .width('100%')
      .alignItems(HorizontalAlign.Center)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#EFEFF4')
  }
}
