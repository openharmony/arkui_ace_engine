# ArkUI KB

> 更新时间：2026-07-13
> 组件数：10
> 适用范围：`OpenHarmony/foundation/arkui/ace_engine/docs/kb`

`docs/kb/` 是新版知识库专区。新版 KB 只作为 Agent 上下文导航页，行为事实以源码、SDK/API 声明、测试和 Spec 为准。

## 目录约束

```text
docs/kb/
├── components/      # 对外 UI 组件
├── capabilities/    # 通用能力
├── architecture/    # 引擎架构和框架机制
├── api/             # SDK、C API、NAPI、API 范式
├── syntax/          # ArkTS 声明式语法专题
└── _generated/      # 可再生成索引页
```

组件 KB 按 `docs/kb/components/<category>/<name>.md` 放置，例如 Text 试点页为 `docs/kb/components/basic/text.md`。

## 编写规则

- 新增 KB 必须同步 `docs/context_registry.json`。
- KB 迁移到新版路径后，同步删除对应旧 KB 文件，不再通过 `legacy_kb` 保留旧入口。
- KB 保留定位、源码/API/测试/Spec 路由、调试入口和常见问题定位。
- KB 不长期维护完整 API 行为矩阵、AC/BR/FR/ER/RC 或大段调用链复述。
- 代码级结论必须能从真实源码或 SDK 声明验证，未验证内容标注为“推测”。

## 当前试点

| ID | 主题 | 新版 KB | 状态 |
|----|------|---------|------|
| Text | 文本组件 | `docs/kb/components/basic/text.md` | 已迁移，旧 KB 已移除 |
| Image | 图片组件 | `docs/kb/components/media/image.md` | 已迁移，旧 KB 已移除 |
| ImageAnimator | 图片动画组件 | `docs/kb/components/media/image_animator.md` | 已迁移，旧 KB 已移除 |
| Video | 视频组件 | `docs/kb/components/media/video.md` | 新建（无旧 KB） |
| DrawableDescriptor | 图片资源描述能力 | `docs/kb/capabilities/drawable_descriptor.md` | 新增 |
| Toggle | 开关组件 | `docs/kb/components/selector/toggle.md` | 已迁移，旧 KB 已移除 |
| Navigation | 导航容器组件 | `docs/kb/components/container/navigation.md` | 新建 |
| Tabs | 标签页容器组件 | `docs/kb/components/container/tabs.md` | 新建 |
| Swiper | 轮播容器组件 | `docs/kb/components/container/swiper.md` | 新建 |
| SideBarContainer | 侧边栏容器组件 | `docs/kb/components/container/side_bar_container.md` | 新建 |
| NavDestination | 导航目标页组件 | `docs/kb/components/container/navdestination.md` | 新建 |
| Slider | 滑动选择器组件 | `docs/kb/components/input-form/slider.md` | 新建（无旧 KB） |
| TextPicker | 文本选择器组件 | `docs/kb/components/selector/text_picker.md` | 已迁移，旧 KB 已移除 |
| DatePicker | 日期选择器组件 | `docs/kb/components/selector/date_picker.md` | 已迁移，旧 KB 已移除 |
| TimePicker | 时间选择器组件 | `docs/kb/components/selector/time_picker.md` | 已迁移，旧 KB 已移除 |
| UIPickerComponent | UI选择器容器组件 | `docs/kb/components/selector/ui_picker_component.md` | 已迁移，旧 KB 已移除 |

## 检索

```bash
python3 docs/validate_context.py
python3 docs/kb_search.py Text
python3 docs/kb_search.py Text --field name
python3 -m json.tool docs/context_registry.json > /dev/null
```
