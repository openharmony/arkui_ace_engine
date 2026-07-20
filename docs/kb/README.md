# ArkUI KB

> 更新时间：2026-07-18
> 主题数：34
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

## 当前主题

| ID | 主题 | 新版 KB | 状态 |
|----|------|---------|------|
| LayoutFramework | 布局框架 | `docs/kb/architecture/layout-framework.md` | 已重建，旧 KB 已移除 |
| LayoutAttributes | 基础布局属性 | `docs/kb/capabilities/layout-attributes.md` | 新建 |
| SafeArea | 安全区域机制 | `docs/kb/capabilities/safe-area.md` | 已合并重建，两份旧 KB 已移除 |
| Blank | 空白填充组件 | `docs/kb/components/basic/blank.md` | 新建 |
| Divider | 分隔线组件 | `docs/kb/components/basic/divider.md` | 新建 |
| Column | 纵向布局组件 | `docs/kb/components/container/column.md` | 新建 |
| Flex | 弹性布局组件（含 Wrap） | `docs/kb/components/container/flex.md` | 已重建，旧 KB 已移除 |
| GridCol | 响应式栅格列组件 | `docs/kb/components/container/grid_col.md` | 新建 |
| GridRow | 响应式栅格行组件 | `docs/kb/components/container/grid_row.md` | 新建 |
| Row | 横向布局组件 | `docs/kb/components/container/row.md` | 新建 |
| Stack | 层叠布局组件 | `docs/kb/components/container/stack.md` | 新建 |
| FolderStack | 折叠屏层叠布局组件 | `docs/kb/components/container/folder_stack.md` | 新建 |
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
| AlphabetIndexer | 字母索引组件 | `docs/kb/components/data_display/alphabet_indexer.md` | 新建 |
| Router | 路由管理 | `docs/kb/api/router.md` | 新建（不推荐，推荐 Navigation） |
| StateMgmtV1Core | V1 状态管理核心逻辑 | `docs/kb/architecture/state_management/v1_core.md` | 已注册 |
| StateMgmtV2Core | V2 状态管理核心逻辑 | `docs/kb/architecture/state_management/v2_core.md` | 已注册 |
| StateMgmtV1Decorators | V1 状态管理装饰器 | `docs/kb/architecture/state_management/v1_decorators.md` | 已注册 |
| StateMgmtV2Decorators | V2 状态管理装饰器 | `docs/kb/architecture/state_management/v2_decorators.md` | 已注册 |

## 检索

```bash
python3 docs/validate_context.py
python3 docs/kb_search.py Text
python3 docs/kb_search.py Text --field name
python3 -m json.tool docs/context_registry.json > /dev/null
```
