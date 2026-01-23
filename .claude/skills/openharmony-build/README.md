# OpenHarmony Build Skill

用于编译和分析 OpenHarmony 代码的 Claude Code Skill。

## 功能特性

- ✅ 自动导航到 OpenHarmony 根目录
- ✅ 执行完整的系统编译
- ✅ 编译特定组件（如 ace_engine）
- ✅ 快速编译（跳过 GN 生成）
- ✅ 验证编译成功状态
- ✅ 分析编译失败日志
- ✅ 提供错误诊断和解决建议

## 新增功能 (v0.1.1)

- ✨ **快速编译支持**：通过 `--fast-rebuild` 选项跳过 GN 生成
- ✨ **智能判断**：使用 `check_fast_rebuild.sh` 脚本检查是否可用快速编译
- ✨ **速度提升**：代码修改场景下编译速度提升 30-50%

## 目录结构

```
openharmony-build/
├── SKILL.md                              # Skill 主文件
├── README.md                             # 本文件
├── examples/
│   └── example-workflow.md               # 使用示例
├── references/
│   ├── build-commands.md                 # 编译命令参考
│   ├── common-errors.md                  # 常见错误及解决方案
│   └── log-locations.md                  # 日志文件位置指南
└── scripts/
    ├── analyze_build_error.sh            # 编译错误分析脚本
    └── find_recent_errors.sh             # 快速错误检查脚本
```

## 使用方法

### 与 Claude 对话

直接向 Claude 提出请求：

```
"请帮我编译 OpenHarmony 代码"
"编译 ace_engine 组件"
"编译失败了，帮我分析错误"
"查看 rk3568 的编译日志"
"执行完整编译"
```

### 手动使用脚本

**分析编译错误**：
```bash
/home/sunfei/workspace/openHarmony/foundation/arkui/ace_engine/.claude/skills/openharmony-build/scripts/analyze_build_error.sh rk3568
```

**快速查看最近错误**：
```bash
/home/sunfei/workspace/openHarmony/foundation/arkui/ace_engine/.claude/skills/openharmony-build/scripts/find_recent_errors.sh rk3568
```

## 编译命令

### 标准编译

```bash
# 动态查找 OpenHarmony 根目录
find_root() {
    local dir="$(pwd)"
    while [[ ! -f "$dir/.gn" ]]; do
        dir="$(dirname "$dir)"
        [[ "$dir" == "/" ]] && { echo "Error: .gn not found" >&2; return 1; }
    done
    echo "$dir"
}

cd "$(find_root)"
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache
```

### 快速编译（跳过 GN 生成）

```bash
# 适用于仅修改代码，未修改 BUILD.gn 文件
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --ccache --fast-rebuild

# 快速编译特定组件
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine --ccache --fast-rebuild
```

**快速编译优势**：
- ⚡ 速度提升 30-50%
- 跳过 GN 解析和 ninja 文件生成
- 适合迭代开发

### 组件编译

```bash
# 编译 ace_engine
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine --ccache
```

### 测试编译

**推荐：编译 ACE Engine 测试用例**（快速，适合 ACE Engine 开发）：
```bash
# 编译 ace_engine 测试用例（推荐）
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine_test --ccache

# 快速编译测试用例（跳过 GN 生成）
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target ace_engine_test --ccache --fast-rebuild
```

**备选：编译全量单元测试**（较慢，完整测试套件）：
```bash
# 编译全量单元测试（完整测试套件）
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target unittest --ccache

# 快速编译全量测试
./build.sh --export-para PYCACHE_ENABLE:true --product-name rk3568 --build-target unittest --ccache --fast-rebuild
```

**测试编译目标选择建议**：
- ⭐ **ACE Engine 开发**：优先使用 `ace_engine_test`（更快）
- **跨模块测试**：使用 `unittest`（完整但较慢）
- **性能测试**：使用 `benchmark_linux`

### 常用产品名

- `rk3568` - RK3568 开发板
- `ohos-sdk` - OpenHarmony SDK
- `rk3588` - RK3588 开发板（高性能）

## 日志位置

编译日志位于 `out/` 目录：

```bash
# 动态获取 OpenHarmony 根目录
OH_ROOT=$(find_root)
```

```
$OH_ROOT/out/
├── <product-name>/
│   ├── build.log          # 主编译日志
│   ├── packages/          # 编译输出包
│   └── logs/              # 组件日志
```

示例：
- `$OH_ROOT/out/rk3568/build.log` - RK3568 编译日志
- `$OH_ROOT/out/rk3568/logs/arkui/ace_engine/` - ACE Engine 组件日志

## 错误分析流程

1. **编译失败** - 退出码非零
2. **⭐ 优先检查主构建日志** - `out/<product>/build.log`（包含所有编译信息）
3. **分析错误** - 使用 `analyze_build_error.sh` 脚本
4. **查找原因** - 根据错误类型定位问题
5. **提供方案** - 基于错误上下文给出建议

**重要提示**：主构建日志 `out/<product>/build.log` 包含完整的编译信息（GN 生成、Ninja 编译、链接、打包），应该始终优先检查此文件，而不是组件特定的日志文件。

## 常见错误类型

### 编译错误
- 头文件未找到
- 语法错误
- 类型不匹配

### 链接错误
- 未定义的引用
- 库文件缺失
- 循环依赖

### 环境错误
- Python 版本不匹配
- Node.js 版本错误
- 依赖缺失

## 参考文档

- **编译命令参考** - `references/build-commands.md` (包含快速编译说明)
- **常见错误** - `references/common-errors.md`
- **日志位置** - `references/log-locations.md`
- **使用示例** - `examples/example-workflow.md` (包含快速编译示例)

## Skill 特性

### 渐进式加载

1. **Metadata** - 始终加载（名称和描述）
2. **SKILL.md** - 触发时加载（核心流程）
3. **References** - 按需加载（详细文档）

### 触发条件

当用户提出以下请求时触发此 Skill：
- "编译 OpenHarmony"
- "build OpenHarmony"
- "编译完整代码"
- "执行编译"
- "编译 OpenHarmony 代码"
- "快速编译"
- "跳过gn编译"
- "fast-build"
- "编译测试" (新增)
- "编译测试用例" (新增)
- "build ace_engine_test" (新增)

## 开发者信息

- **位置**: `ace_engine/.claude/skills/openharmony-build/`
- **版本**: 0.1.0
- **依赖**: OpenHarmony 编译环境（build.sh, hb）
- **路径查找**: 动态查找 `.gn` 文件定位 OpenHarmony 根目录

## 更新日志

### v0.2.0 (2025-01-23)
- ✨ 新增 `ace_engine_test` 编译目标支持
- 📝 明确测试编译优先级：`ace_engine_test` > `unittest`
- ⭐ 推荐使用 `ace_engine_test` 进行 ACE Engine 测试编译（更快）
- 📚 更新所有文档和示例，添加测试编译说明
- 🔧 优化测试编译工作流，支持快速编译测试用例
- 🎯 新增触发关键词："编译测试"、"编译测试用例"、"build ace_engine_test"

### v0.1.3 (2025-01-23)
- ✨ 明确错误解析优先级：强调优先查看 `out/{product}/build.log`
- 📝 更新所有文档，明确主构建日志的重要性和优先性
- 🔧 优化错误分析流程，确保首先检查主构建日志
- 📚 更新示例代码，展示正确的日志检查顺序

### v0.1.2 (2025-01-23)
- ✨ 新增快速编译功能 (`--fast-rebuild` 选项)
- ✨ 新增 `check_fast_rebuild.sh` 辅助脚本
- ✨ 支持通过"快速编译"、"跳过gn编译"、"fast-build"关键词触发
- ✨ 更新所有文档和示例，添加快速编译说明

### v0.1.1 (2025-01-23)
- ✅ 路径查找改为动态（通过 `.gn` 文件标识）
- ✅ 默认编译命令添加缓存选项（`--export-para PYCACHE_ENABLE:true --ccache`）
- ✅ 更新所有文档和示例使用动态路径

### v0.1.0 (2025-01-23)
- ✅ 初始版本
- ✅ 编译执行功能
- ✅ 错误分析脚本
- ✅ 完整参考文档
- ✅ 使用示例

## 待办事项

您需要稍后提供的具体日志路径。当前脚本默认查找：
- 主编译日志: `out/<product>/build.log`
- 组件日志: `out/<product>/logs/<component>/`

如需自定义日志路径，请更新 `references/log-locations.md` 文件。

## 测试

测试脚本是否正常工作：

```bash
# 测试路径是否正确
pwd  # 应该在: /home/sunfei/workspace/openHarmony/foundation/arkui/ace_engine

# 测试错误检查脚本
.claude/skills/openharmony-build/scripts/find_recent_errors.sh rk3568

# 测试完整错误分析
.claude/skills/openharmony-build/scripts/analyze_build_error.sh rk3568
```

## 支持

如遇问题，请检查：
1. 脚本会自动从当前位置向上查找 `.gn` 文件来定位 OpenHarmony 根目录
2. 编译日志文件是否存在
3. 脚本是否有执行权限
