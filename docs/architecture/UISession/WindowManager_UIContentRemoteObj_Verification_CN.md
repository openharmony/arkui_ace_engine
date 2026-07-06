# WindowManager UIContent RemoteObj 验证补丁

## 概述

本文档固化 UISession 端到端验证中 window_manager 仓需要临时应用的验证补丁。补丁用于打通 separated WMS 架构下 `ui_sa -> WMS -> app WindowAgent/WindowImpl -> ArkUI UIContentImpl remote` 的链路，解决 `GetUIContentRemoteObj` 返回 `ret=0` 但 remote object 为空的问题。

补丁文件：

```text
foundation/arkui/ace_engine/docs/architecture/UISession/window_manager_get_ui_content_remote_obj.patch
```

## 适用场景

- `hidumper -s 16666 -a Connect` 日志出现 `through uiSa, get UIContentRemoteObj. ret=0`。
- 随后出现 `through uiSa, tempRemoteObj is null`。
- 当前设备走 separated WMS 路径，`IWindowManager::GetUIContentRemoteObj` 仅默认返回 `WS_OK`，未写入 remote object。

## 补丁内容

补丁包含两类验证能力：

1. separated WMS IPC 链路：
   - `WindowManagerService::GetUIContentRemoteObj`
   - `WindowManagerStub/Proxy::GetUIContentRemoteObj`
   - WMS reply 先写 `errCode`，成功时再写 remote object。

2. WMS 到应用进程窗口对象回调：
   - `IWindow::GetUIContentRemoteObj`
   - `WindowStub/Proxy::GetUIContentRemoteObj`
   - `WindowAgent::GetUIContentRemoteObj`
   - `WindowImpl::GetUIContentRemoteObj`
   - unified/sceneboard 路径的 `WindowSessionImpl` fallback 验证逻辑。

验证链路：

```text
ui_sa
  -> WindowManager::GetUIContentRemoteObj
  -> WindowManagerService::GetUIContentRemoteObj
  -> WindowRoot::GetWindowNode(persistentId)
  -> WindowNode::GetWindowToken()
  -> IWindow::GetUIContentRemoteObj
  -> WindowAgent::GetUIContentRemoteObj
  -> WindowImpl::GetUIContentRemoteObj
  -> UIContent::GetRemoteObj()
```

## 应用补丁

在 OpenHarmony 根目录或 window_manager 仓中执行：

```bash
cd /home/l00441630/OpenHarmony/foundation/window/window_manager
git apply --check /home/l00441630/OpenHarmony/foundation/arkui/ace_engine/docs/architecture/UISession/window_manager_get_ui_content_remote_obj.patch
git apply /home/l00441630/OpenHarmony/foundation/arkui/ace_engine/docs/architecture/UISession/window_manager_get_ui_content_remote_obj.patch
```

如 `git apply --check` 失败，先检查 window_manager 当前分支是否已包含同名接口或补丁是否已应用，不要直接回退用户本地改动。

## 编译产物

当前 32 位 RK3568 验证板需要编译并推送 32 位库：

```bash
cd /home/l00441630/OpenHarmony
./build.sh --product-name rk3568 \
  --build-target //foundation/window/window_manager/wm:libwm \
  --build-target //foundation/window/window_manager/wmserver:libwms \
  --ccache

file out/rk3568/src/window/window_manager/libwm.z.so \
  out/rk3568/src/window/window_manager/libwms.z.so

strings out/rk3568/src/window/window_manager/libwm.z.so | \
  grep -E "WindowAgent GetUIContentRemoteObj|get uiContent remote success"
strings out/rk3568/src/window/window_manager/libwms.z.so | \
  grep -E "GetUIContentRemoteObj from app"
```

通过判据：两个 so 均为 `ELF 32-bit LSB shared object, ARM`，且包含上述日志字符串。

## 推送路径

推送前必须先确认设备真实路径，不要盲目推送：

```bash
hdc shell "ls -l /system/lib/libwm.z.so /system/lib/libwms.z.so"
hdc shell "sha256sum /system/lib/libwm.z.so /system/lib/libwms.z.so"
```

当前验证板实测路径：

```text
/system/lib/libwm.z.so
/system/lib/libwms.z.so
```

推送流程：

```bash
hdc shell "mkdir -p /data/local/tmp/pagescene_backup /data/local/tmp/pagescene_push"
hdc shell "cp -n /system/lib/libwm.z.so /data/local/tmp/pagescene_backup/libwm.z.so.bak 2>/dev/null || true"
hdc shell "cp -n /system/lib/libwms.z.so /data/local/tmp/pagescene_backup/libwms.z.so.bak 2>/dev/null || true"
hdc shell "mount -o rw,remount /"

hdc file send out/rk3568/src/window/window_manager/libwm.z.so /data/local/tmp/pagescene_push/libwm.z.so
hdc file send out/rk3568/src/window/window_manager/libwms.z.so /data/local/tmp/pagescene_push/libwms.z.so

hdc shell "cp /data/local/tmp/pagescene_push/libwm.z.so /system/lib/libwm.z.so"
hdc shell "cp /data/local/tmp/pagescene_push/libwms.z.so /system/lib/libwms.z.so"
hdc shell "chmod 755 /system/lib/libwm.z.so /system/lib/libwms.z.so"
hdc shell "sha256sum /system/lib/libwm.z.so /system/lib/libwms.z.so"
hdc shell "sync; reboot"
```

## 验证步骤

重启后：

```bash
hdc shell "param set ohos.ctl.start ui_sa"
hdc shell "hidumper -ls | grep 16666"
hdc shell "power-shell wakeup"
hdc shell "power-shell setmode 602"
hdc shell "power-shell timeout -o 18000000"
hdc shell "aa start -b com.example.myapplication -a EntryAbility"
hdc shell "hidumper -s WindowManagerService -a \"-a\""
```

确认目标应用是焦点窗口后执行：

```bash
hdc shell "hilog -r"
hdc shell "hidumper -s 16666 -a Connect"
hdc shell "hidumper -s 16666 -a GetCurrentPageName"
hdc shell "hidumper -s 16666 -a GetVisibleInspectorTree"
hdc shell "hilog -x > /data/local/tmp/pagescene_uisa_retry.hilog"
```

关键日志：

```text
get uiContent remote success, winId:<targetWindowId>
WindowAgent GetUIContentRemoteObj, winId:<targetWindowId>, err:0, remote:1
GetUIContentRemoteObj from app, persistentId:<targetWindowId>, err:0, remote:1
through uiSa, connect success, foucs window info = bundleName:<targetBundle>
[GetVisibleInspectorTree] data = ... "BundleName":"<targetBundle>" ...
```

失败特征：

```text
through uiSa, tempRemoteObj is null
```

若命中系统窗口，例如 `ScreenLockWindow`，需要先解锁并确认 WMS dump 中目标应用窗口为 `Focus window`，再重试 `ui_sa` 命令。

## 实测记录

2026-06-30 RK3568 32 位开发板验证通过：

```text
WMS dump:
myapplication0 Pid 2188 WinId 12
Focus window: 12

hilog:
get uiContent remote success, winId:12
WindowAgent GetUIContentRemoteObj, winId:12, err:0, remote:1
GetUIContentRemoteObj from app, persistentId:12, err:0, remote:1
through uiSa, connect success, foucs window info = bundleName:com.example.myapplication,moduleName:entry,abilityName:EntryAbility
[GetVisibleInspectorTree] data = ... "BundleName":"com.example.myapplication","WindowID":12,"WindowName":"myapplication0" ...
```
