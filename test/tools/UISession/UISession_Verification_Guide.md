# UISession 验证部署指南

> 来源：`docs/kb/architecture/uisession-service.md` 附录验证步骤迁移
> 更新时间：2026-08-03

## 1. ui_session_sample 构建与部署

`ui_session_sample` 由 `interfaces/inner_api/ui_session:ui_session_example` group 拉起，实际构建 `ui_session_sample:ui_sa`。构建产物：`libui_sa.z.so`、`16666.json`、`ui_sa.cfg`。

```bash
./build.sh --product-name rk3568 --build-target //foundation/arkui/ace_engine/interfaces/inner_api/ui_session:ui_session_example
```

部署确认：

```bash
hdc shell hidumper -ls | grep 16666
hdc shell ps -ef | grep ui_sa
```

若是在已有开发板上临时验证，需要手动推送 `ui_sa` 库和配置。`ui_sa.cfg` 指定 `sa_main` 按 `/system/profile/16666.json` 拉起，profile 中 `libpath` 为 `libui_sa.z.so`，因此库需要放到 `sa_main` 可加载的平台库路径。推送前必须先确认设备已有库路径和本地产物架构，不要只按经验写死路径：32 位 `sa_main` 通常使用 `/system/lib/platformsdk/`，64 位 `sa_main` 通常使用 `/system/lib64/platformsdk/`。当前 32 位 RK3568 验证板实测 `libui_sa.z.so`、`libui_session.z.so`、`libace_compatible.z.so` 均在 `/system/lib/platformsdk/`。

```bash
# 1. 查找本地构建产物，并确认与设备位数一致
find out/rk3568 -name libui_sa.z.so -o -name libui_session.z.so -o -name libace_compatible.z.so -o -name 16666.json -o -name ui_sa.cfg
file <path-to-libui_sa.z.so> <path-to-libui_session.z.so> <path-to-libace_compatible.z.so>

# 2. 查询设备实际加载路径。必须以查询结果为准，不要盲目推送到 /system/lib64 或 /system/lib
hdc shell "file /system/bin/sa_main 2>/dev/null || true"
hdc shell "find /system -name libui_sa.z.so -o -name libui_session.z.so -o -name libace_compatible.z.so 2>/dev/null"
hdc shell "ls -l /system/lib/platformsdk/libui_sa.z.so /system/lib/platformsdk/libui_session.z.so /system/lib/platformsdk/libace_compatible.z.so 2>/dev/null"

# 3. 设备侧准备临时目录和可写系统分区
hdc shell mount -o rw,remount /
hdc shell mkdir -p /data/sofiles
hdc shell mkdir -p /data/local/tmp/pagescene_backup

# 4. 备份并推送库和配置文件（以当前 32 位 RK3568 实测路径为例）
hdc shell "cp -n /system/lib/platformsdk/libui_sa.z.so /data/local/tmp/pagescene_backup/libui_sa.z.so.bak 2>/dev/null || true"
hdc shell "cp -n /system/lib/platformsdk/libui_session.z.so /data/local/tmp/pagescene_backup/libui_session.z.so.bak 2>/dev/null || true"
hdc shell "cp -n /system/lib/platformsdk/libace_compatible.z.so /data/local/tmp/pagescene_backup/libace_compatible.z.so.bak 2>/dev/null || true"
hdc file send <path-to-libui_sa.z.so> /data/sofiles/libui_sa.z.so
hdc file send <path-to-libui_session.z.so> /data/sofiles/libui_session.z.so
hdc file send <path-to-libace_compatible.z.so> /data/sofiles/libace_compatible.z.so
hdc shell cp /data/sofiles/libui_sa.z.so /system/lib/platformsdk/libui_sa.z.so
hdc shell cp /data/sofiles/libui_session.z.so /system/lib/platformsdk/libui_session.z.so
hdc shell cp /data/sofiles/libace_compatible.z.so /system/lib/platformsdk/libace_compatible.z.so
hdc shell chmod 755 /system/lib/platformsdk/libui_sa.z.so /system/lib/platformsdk/libui_session.z.so /system/lib/platformsdk/libace_compatible.z.so
hdc file send interfaces/inner_api/ui_session/ui_session_sample/16666.json /system/profile/16666.json
hdc file send interfaces/inner_api/ui_session/ui_session_sample/ui_sa.cfg /system/etc/init/ui_sa.cfg

# 5. 补充 SA 账号和组。重复执行前先 grep，避免重复追加
hdc shell "grep -q '^ui_sa:' /system/etc/group || printf 'ui_sa:x:16666:\n' >> /system/etc/group"
hdc shell "grep -q '^ui_sa:' /system/etc/passwd || printf 'ui_sa:x:16666:16666:::/bin/false\n' >> /system/etc/passwd"

# 6. 开发板验证可临时放宽 SELinux，并创建 sample 输出目录
hdc shell "sed -i 's/^SELINUX=.*/SELINUX=permissive/g' /system/etc/selinux/config"
hdc shell "cat /system/etc/selinux/config | grep SELINUX="
hdc shell mkdir -p /data/service/el1/public/ui_sa
hdc shell chown ui_sa:ui_sa /data/service/el1/public/ui_sa
hdc shell chmod 770 /data/service/el1/public/ui_sa

# 7. 重启后确认 SA 已注册
hdc shell reboot
hdc shell power-shell wakeup
hdc shell "power-shell setmode 602"
hdc shell "power-shell timeout -o 18000000"
hdc shell "param set ohos.ctl.start ui_sa"
hdc shell hidumper -ls | grep 16666
hdc shell ps -ef | grep ui_sa
```

> **SA 注册权限问题**：若前台手动执行 `sa_main /system/profile/16666.json` 或 init 拉起日志出现 `AddSystemProcess PERMISSION DENIED` / `failed to add local abilitymanager`，需要在 `/system/etc/init/ui_sa.cfg` 的 `permission` 和 `permission_acls` 中补充 `ohos.permission.MANAGE_SYSTEM_ABILITY` 后重新推送并重启。手动拉起必须使用 init 识别的控制参数 `ohos.ctl.start`，例如 `hdc shell "param set ohos.ctl.start ui_sa"`；不要使用 `ctl.start`，该参数不会触发 OpenHarmony init 的服务控制 hook。最终以 `hdc shell "hidumper -ls | grep 16666"` 能看到 16666 为 SA 注册成功判据；若 `hidumper` 返回 `no such system ability 16666`，说明 sample SA 尚未被 init/samgr 纳入可调度上下文，不能继续判定 UISession 接口验证通过。

> 若需要保存树文件，必须先确保 sample 写入目录存在并归属 `ui_sa`：
> ```bash
> hdc shell mkdir -p /data/service/el1/public/ui_sa
> hdc shell chown ui_sa:ui_sa /data/service/el1/public/ui_sa
> ```

> 若 `hdc` 只能在 Windows 主机上执行，可先用 `scp -P 2222` 把本地构建产物复制到 Windows 主机，再在 Windows 侧执行同样的 `hdc file send` / `hdc shell` 命令。推荐把环境变量写在本地 shell 临时会话中，避免把个人信息写入仓内脚本。以下脚本只适用于已经确认三份库均位于 `/system/lib/platformsdk/` 的 32 位开发板；其他设备必须先执行前面的 `find /system` 查询并替换目标路径。
>
> ```bash
> WIN_USER=<windows_user>
> WIN_PORT=2222
> HDC='C:\path\to\hdc.exe'
> DEVICE=<device_id>
> WIN_SO='C:\Users\<windows_user>\Desktop\PageScene\so'
> WIN_LOG='C:\Users\<windows_user>\Desktop\PageScene\logs'
>
> scp -P ${WIN_PORT} out/rk3568/arkui/ace_engine/libui_sa.z.so ${WIN_USER}@127.0.0.1:${WIN_SO}/
> scp -P ${WIN_PORT} out/rk3568/arkui/ace_engine/libui_session.z.so ${WIN_USER}@127.0.0.1:${WIN_SO}/
> scp -P ${WIN_PORT} out/rk3568/arkui/ace_engine/libace_compatible.z.so ${WIN_USER}@127.0.0.1:${WIN_SO}/
>
> ssh -p ${WIN_PORT} ${WIN_USER}@127.0.0.1 \
>   "powershell -NoProfile -Command \"New-Item -ItemType Directory -Force '${WIN_SO}','${WIN_LOG}' | Out-Null; \
>   & '${HDC}' -t '${DEVICE}' shell 'find /system -name libui_sa.z.so -o -name libui_session.z.so -o -name libace_compatible.z.so 2>/dev/null'; \
>   & '${HDC}' -t '${DEVICE}' shell 'ls -l /system/lib/platformsdk/libui_sa.z.so /system/lib/platformsdk/libui_session.z.so /system/lib/platformsdk/libace_compatible.z.so 2>/dev/null'; \
>   & '${HDC}' -t '${DEVICE}' shell 'mount -o rw,remount /'; \
>   & '${HDC}' -t '${DEVICE}' shell 'mkdir -p /data/local/tmp/pagescene_backup'; \
>   & '${HDC}' -t '${DEVICE}' shell 'cp -n /system/lib/platformsdk/libui_sa.z.so /data/local/tmp/pagescene_backup/libui_sa.z.so.bak 2>/dev/null || true'; \
>   & '${HDC}' -t '${DEVICE}' shell 'cp -n /system/lib/platformsdk/libui_session.z.so /data/local/tmp/pagescene_backup/libui_session.z.so.bak 2>/dev/null || true'; \
>   & '${HDC}' -t '${DEVICE}' shell 'cp -n /system/lib/platformsdk/libace_compatible.z.so /data/local/tmp/pagescene_backup/libace_compatible.z.so.bak 2>/dev/null || true'; \
>   & '${HDC}' -t '${DEVICE}' file send '${WIN_SO}\libui_sa.z.so' '/system/lib/platformsdk/libui_sa.z.so'; \
>   & '${HDC}' -t '${DEVICE}' file send '${WIN_SO}\libui_session.z.so' '/system/lib/platformsdk/libui_session.z.so'; \
>   & '${HDC}' -t '${DEVICE}' file send '${WIN_SO}\libace_compatible.z.so' '/system/lib/platformsdk/libace_compatible.z.so'; \
>   & '${HDC}' -t '${DEVICE}' shell 'chmod 755 /system/lib/platformsdk/libui_sa.z.so /system/lib/platformsdk/libui_session.z.so /system/lib/platformsdk/libace_compatible.z.so'; \
>   & '${HDC}' -t '${DEVICE}' shell 'grep -q ^ui_sa: /system/etc/group || printf \"ui_sa:x:16666:\n\" >> /system/etc/group'; \
>   & '${HDC}' -t '${DEVICE}' shell 'grep -q ^ui_sa: /system/etc/passwd || printf \"ui_sa:x:16666:16666:::/bin/false\n\" >> /system/etc/passwd'; \
>   & '${HDC}' -t '${DEVICE}' shell 'sed -i s/enforcing/permissive/g /system/etc/selinux/config'; \
>   & '${HDC}' -t '${DEVICE}' shell 'mkdir -p /data/service/el1/public/ui_sa && chown ui_sa:ui_sa /data/service/el1/public/ui_sa && chmod 770 /data/service/el1/public/ui_sa'\""
> ```

## 2. WM 验证补丁构建与推送

WM 验证补丁用于打通 `ui_sa → WMS → app WindowAgent/WindowImpl → ArkUI UIContentImpl remote` 链路。验证性补丁建议放在 window_manager 仓的 `wm/src/window_session_impl.cpp`：当当前窗口 remote object 为空时，遍历同进程 `WindowSessionImpl::windowSessionMap_` 寻找非空 remote object fallback，并打印 `current uiContent remote is null`、`get fallback uiContent remote` 或 `uiContent remote is nullptr, no fallback found`。这是为了验证 `ui_sa` 到应用进程的 UISession IPC 链路；是否作为正式修复需要由 window_manager 评估焦点窗口、子窗口和安全边界后决定。

**补丁文件**：

```text
test/tools/UISession/window_manager_get_ui_content_remote_obj.patch
```

**补丁使用指南**：

```text
test/tools/UISession/WindowManager_UIContentRemoteObj_Verification_CN.md
```

该指南详细说明了补丁适用场景、补丁内容（separated WMS IPC 链路 + WMS 到应用进程窗口对象回调）、完整验证链路、应用步骤、编译产物确认、推送路径、验证步骤和关键日志模式。以下为精简步骤，完整说明请参考上述指南。

**应用补丁**：

```bash
cd <OH_ROOT>/foundation/window/window_manager
git apply --check <OH_ROOT>/foundation/arkui/ace_engine/test/tools/UISession/window_manager_get_ui_content_remote_obj.patch
git apply <OH_ROOT>/foundation/arkui/ace_engine/test/tools/UISession/window_manager_get_ui_content_remote_obj.patch
```

**编译并验证产物**：

```bash
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

**推送 WM 库**（推送前先确认设备路径）：

```bash
hdc shell "ls -l /system/lib/libwm.z.so /system/lib/libwms.z.so"
hdc shell "sha256sum /system/lib/libwm.z.so /system/lib/libwms.z.so"

hdc shell "mkdir -p /data/local/tmp/pagescene_backup /data/local/tmp/pagescene_push"
hdc shell "cp -n /system/lib/libwm.z.so /data/local/tmp/pagescene_backup/libwm.z.so.bak 2>/dev/null || true"
hdc shell "cp -n /system/lib/libwms.z.so /data/local/tmp/pagescene_backup/libwms.z.so.bak 2>/dev/null || true"
hdc shell mount -o rw,remount /
hdc file send out/rk3568/src/window/window_manager/libwm.z.so /data/local/tmp/pagescene_push/libwm.z.so
hdc file send out/rk3568/src/window/window_manager/libwms.z.so /data/local/tmp/pagescene_push/libwms.z.so
hdc shell "cp /data/local/tmp/pagescene_push/libwm.z.so /system/lib/libwm.z.so"
hdc shell "cp /data/local/tmp/pagescene_push/libwms.z.so /system/lib/libwms.z.so"
hdc shell "chmod 755 /system/lib/libwm.z.so /system/lib/libwms.z.so"
hdc shell "sha256sum /system/lib/libwm.z.so /system/lib/libwms.z.so"
hdc shell "sync; reboot"
```

> 32 位开发板实测应用进程和 `ui_sa` 加载的是 `/system/lib/libwm.z.so`，separated WMS 服务加载的是 `/system/lib/libwms.z.so`。推送前仍应先用 `find /system -name libwm.z.so -o -name libwms.z.so` 确认实际路径。

**WM 验证补丁关键点**：

- `hidumper -s 16666 -a "Connect"` 日志若出现 `tempRemoteObj is null`，说明 WindowManager IPC 返回成功但 `UIContent::GetRemoteObj()` 为空。
- unified/sceneboard 验证链路：`UiSaService::Dump` → `WindowManager::GetUIContentRemoteObj` → `WindowSessionImpl::GetUIContentRemoteObj` → `UIContentImpl::GetRemoteObj()`。
- 验证性补丁建议在 `wm/src/window_session_impl.cpp`：遍历同进程 `windowSessionMap_` 寻找非空 remote object fallback。
- separated WMS 架构需补充 WMS IPC 链路，缺口表现为 `IWindowManager::GetUIContentRemoteObj` 默认返回 `WS_OK` 但不写 remote object。

## 3. WM 验证重启后确认步骤

重启后按以下顺序确认验证路径：

```bash
hdc shell "param set ohos.ctl.start ui_sa"
hdc shell "hidumper -ls | grep 16666"
hdc shell "ps -ef | grep ui_sa"
hdc shell power-shell wakeup
hdc shell "power-shell setmode 602"
hdc shell "power-shell timeout -o 18000000"
hdc shell "aa start -b com.example.myapplication -a EntryAbility"
hdc shell "hidumper -s WindowManagerService -a \"-a\""
hdc shell "hilog -r"
hdc shell "hidumper -s 16666 -a Connect"
hdc shell "hidumper -s 16666 -a GetCurrentPageName"
hdc shell "hidumper -s 16666 -a GetVisibleInspectorTree"
hdc shell "hilog | grep -E 'GetUIContentRemoteObj from app|WindowAgent GetUIContentRemoteObj|get uiContent remote success|tempRemoteObj is null|connect success|GetVisibleInspectorTree'"
```

通过判据：`hidumper -ls` 能看到 `16666`，WMS dump 中目标应用窗口是焦点窗口，`Connect` 不再出现 `tempRemoteObj is null`；日志出现 `connect success, foucs window info = bundleName:...,moduleName:...,abilityName:...`。

关键日志模式：

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

## 4. hidumper 命令完整示例

sample 通过 `hidumper -s 16666 -a "<命令> [参数...]"` 驱动。`UiSaService::Dump` 会取当前焦点窗口，调用 `WindowManager::GetUIContentRemoteObj` 获取该窗口的 `IUiContentService`，因此验证前需要保证目标 ArkUI 应用窗口处于焦点。

验证前准备：

```bash
hdc shell power-shell wakeup
hdc shell "power-shell setmode 602"
hdc shell "power-shell timeout -o 18000000"
```

主线 sample 常用命令：

```bash
# 建立连接
hdc shell hidumper -s 16666 -a "Connect"

# InspectorTree；末尾 -tofile 时保存到 /data/service/el1/public/ui_sa/arkui_tree_*.json
hdc shell hidumper -s 16666 -a "GetVisibleInspectorTree"
hdc shell hidumper -s 16666 -a "GetVisibleInspectorTree true false true true false -tofile"

# 当前页面名
hdc shell hidumper -s 16666 -a "GetCurrentPageName"

# 组件变化事件；无参数=COMPONENT_EVENT_ALL，x=COMPONENT_EVENT_NONE，其余数字按 bit 位组合
hdc shell hidumper -s 16666 -a "RegisterComponentChangeEventCallback"
hdc shell hidumper -s 16666 -a "RegisterComponentChangeEventCallback 1 4 5"
hdc shell hidumper -s 16666 -a "UnregisterComponentChangeEventCallback"

# 内容变化检测；不带参数使用默认值，末尾 -tofile 保存 simpleTree
hdc shell hidumper -s 16666 -a "RegisterContentChangeCallback"
hdc shell hidumper -s 16666 -a "RegisterContentChangeCallback 100 0.15 x 100 100 600 -tofile"
hdc shell hidumper -s 16666 -a "UnregisterContentChangeCallback"

# 图片与 Web 信息
hdc shell hidumper -s 16666 -a "GetCurrentImagesShowing"
hdc shell hidumper -s 16666 -a "GetWebInfoByRequest <webId> RequestArkWebDomTree"

# 选中文本与内容偏移/高亮
hdc shell hidumper -s 16666 -a "RegisterSelectTextEventCallback"
hdc shell hidumper -s 16666 -a "GetSpecifiedContentOffsets <nodeId> hello\\wworld"
hdc shell hidumper -s 16666 -a "HighlightSpecifiedContent <nodeId> hello\\wworld"
```

翻译特性分支新增命令：

```bash
# 单次获取页面文本：2=ARKUI_ONLY，3=ARKUI_ARKWEB
hdc shell hidumper -s 16666 -a "GetPageTranslateText 2"
hdc shell hidumper -s 16666 -a "GetPageTranslateText 3"
hdc shell 'hidumper -s 16666 -a "GetPageTranslateText {\"scope\":3,\"extraData\":\"{}\"}"'

# 连续翻译：Start 后初始节点和后续变化通过 callback 打印摘要
hdc shell hidumper -s 16666 -a "StartPageTranslate 3"

# 批量回填译文。nodeId/version 必须来自 GetPageTranslateText 或 StartPageTranslate 日志
hdc shell 'hidumper -s 16666 -a "SendPageTranslateResult {\"results\":[{\"nodeId\":<nodeId1>,\"version\":<version1>,\"translatedText\":\"译文1\"},{\"nodeId\":<nodeId2>,\"version\":<version2>,\"translatedText\":\"译文2\"}]}"'

# 指定节点恢复；不带 nodeId 时全量恢复
hdc shell hidumper -s 16666 -a "ResetPageTranslate <nodeId>"
hdc shell hidumper -s 16666 -a "ResetPageTranslate"

# 结束连续翻译
hdc shell hidumper -s 16666 -a "EndPageTranslate"

# 同步查询当前 Ability 实例生效语言和地区
hdc shell hidumper -s 16666 -a "GetCurrentAbilityLanguageInfo"
```

## 5. 结果确认

**日志确认**：各 handler 使用 `LOGI` 输出带固定 tag 的结果，例如 `[GetVisibleInspectorTree]`、`[ContentChangeManager]`、`[ComponentChangeEvent]`、`[GetWebInfoByRequest]`。

**文件确认**：`GetVisibleInspectorTree -tofile` 保存 `arkui_tree_*.json`，`RegisterContentChangeCallback ... -tofile` 保存 `arkui_simpleTree_*.json`，`GetWebInfoByRequest <webId> RequestArkWebDomTree` 保存 `arkweb_tree_*.json`，目录均为 `/data/service/el1/public/ui_sa/`。

**页面翻译确认**：`GetPageTranslateText` 日志应出现 `[GetPageTranslateText] result=0` 和至少一条 `nodeId/textLen/version`；`StartPageTranslate` 后新增上树或内容变化节点应继续出现 `[StartPageTranslate] nodeId=...` 摘要；`SendPageTranslateResult` 应出现 `[SendPageTranslateResult] result=0`；`ResetPageTranslate` / `EndPageTranslate` 后可通过 `GetVisibleInspectorTree -tofile` 对比是否恢复原文。

## 6. 常见问题详细排查

1. **组件变化事件 SA 未收到**
   - 原因：需要同时满足远端 `ReportService` 存在、组件变化事件已注册、mask 命中当前 `eventType`。
   - 解决：检查 `RegisterComponentChangeEventCallback` 传入的 mask，以及 `GetComponentChangeEventRegistered()` 和 `NeedComponentChangeTypeReporting()`。

2. **InspectorTree 查询无结果**
   - 原因：`processMap_["getInspectorTree"]` 中没有请求进程、`inspectorFunction_` 未注册，或 Web 子树任务计数未归零。
   - 解决：检查 `ConnectInner`、`GetInspectorTreeInner`、`SaveInspectorTreeFunction`、`WebTaskNumsChange` 链路。

3. **页面翻译请求 PARAM_INVALID**
   - 原因：请求 JSON 中的 `scope` 不是数字，或 scope 未通过 `PageTranslateRequestUtil::IsTranslateScopeValid` 校验。
   - 解决：检查请求格式，非 JSON 请求会被当作 `extraData`，JSON 请求需保证 `scope` 合法。

4. **内容变化注册后没有 TEXT 上报**
   - 原因：文本变化采集会跳过滚动、过渡、空矩形、未与 root 相交、未达到文本面积比例阈值或最小上报间隔内的变化。
   - 解决：检查 `ContentChangeConfig.textContentRatio`、`minReportTime`、当前滚动/过渡状态和 `StopTextAABBCollecting` 条件。

## 7. 扩展指南

### 如何在 UISession 上新增能力

1. 在 `ui_content_service_interface.h` 增加 transaction code 和 `IUiContentService` 方法。
2. 在 `UiContentStub::OnRemoteRequest` 增加 code 分发，实现对应 `*Inner` 方法解析 `MessageParcel`。
3. 在 `UIContentServiceStubImpl` 中将服务方法转发到 `UiSessionManager`。
4. 在 `UiSessionManager` 增加虚接口与必要状态，在 `UiSessionManagerOhos` 中实现 OHOS 侧逻辑。
5. 如需访问 Pipeline 或节点树，在 `UIContentImpl::InitializeCallback` 或相关初始化路径注册回调，并通过 `TaskExecutor` 投递到 UI 线程。
6. 如需远端结果回调，更新 `ReportService` 相关 proxy/stub，并维护 `processMap_` 中对应能力 key 的请求进程集合。
7. 补充 `test/mock/interfaces/inner_api/ui_session/mock_ui_session_manager.*` 和相关单元测试。

### 如何新增本应用进程 dump 注入能力

当新能力只用于调试/验证时，优先复用应用进程已有 dump 链路：

- 链路：`UIContentImpl::DumpInfo` → `PostSyncTaskTimeout` → `AceContainer::Dump` → `AceView::Dump` / `PipelineContext::Dump`。
- 新增 dump 参数时 5 条边界规则：
  1. 在 `PipelineContext::OnDumpInfo` 或更靠近所属模块的 dump 分发点新增稳定参数，例如 `-contentChange` 这类以 `-` 开头的命令；调试专用能力应使用 `#ifndef IS_RELEASE_VERSION` 隔离。
  2. dump 处理必须在 UI 线程内快速完成。`UIContentImpl::DumpInfo` 当前超时为 1500ms，长耗时逻辑应拆为异步状态采集或仅触发动作。
  3. 参数需要显式防递归和防误触发。`UIContentImpl::DumpInfo` 已检查参数中是否包含当前 pid，避免跨进程 dump 回环。
  4. 输出应走 `DumpLog` 或 `info`，敏感内容只打印长度、id、version、错误码等摘要；涉及文本、图片或应用数据时不要默认打印正文。
  5. 动态组件或 UIExtension 需要透传到宿主 UIContent 时，复用 `NotifyUieDump → UIContentImpl::DumpInfo` 链路。

### 如何补充 ui_session_sample 验证手段

1. 在 `ui_sa_service.h` 声明 `HandleXxx`，在 `DUMP_MAP` 注册命令名到 handler。命令名应与 innerAPI 能力名一致。
2. handler 内只做参数解析、调用 `IUiContentService`、打印结构化结果。callback 类接口输出固定 tag、result、id、version、长度和结束标识，不打印正文；需要落盘时沿用 `-tofile` 模式写到 `/data/service/el1/public/ui_sa/`。
3. 需要依赖 callback timeout、watchdog 或死亡监听的能力，验证前必须先执行 `Connect`。`HandleConnect` 会把 sample 的 `eventHandler_` 传给 `IUiContentService::Connect`，后续 timeout 任务才能投递。
4. 验证脚本应覆盖正常请求、非法参数、批量输入、回调完成、超时清理、remote death 或 End/Reset 清理等分支；页面类能力还要在目标 ArkUI 应用处于前台焦点后执行。
5. 构建目标统一使用 `//foundation/arkui/ace_engine/interfaces/inner_api/ui_session:ui_session_example`。临时推送验证时同步推 `libui_sa.z.so`、`16666.json`、`ui_sa.cfg`，并确认 `hidumper -ls | grep 16666` 能看到 sample SA。

交付检查项：

1. 文档中列出 sample 命令、参数格式、预期日志 tag 和失败返回。
2. 真机验证至少包含一次 `Connect`、一次目标能力调用和一次恢复/取消路径。
3. 若命令会生成文件，验证 `/data/service/el1/public/ui_sa/` 的权限和文件名规则。
4. 若能力涉及翻译、文本或截图等敏感数据，sample 日志不得输出完整业务正文。
