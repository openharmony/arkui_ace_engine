#!/usr/bin/env python3
"""
Fix static modifier missing issues in C API tests.
Adds ARKUI_CAPI_UNITTEST support to modifier files and updates build configuration.
"""

import os
import re
import sys
from pathlib import Path
from typing import Optional

class StaticModifierFixer:
    """Fix static modifier issues in C API tests."""

    def __init__(self, ace_engine_root: str):
        self.root = ace_engine_root
        self.modifier_template = """#ifdef ARKUI_CAPI_UNITTEST
const GENERATED_ArkUI{component}Modifier* Get{component}StaticModifier();
#endif

const GENERATED_ArkUI{component}Modifier* Get{component}Modifier()
{{
    static const GENERATED_ArkUI{component}Modifier* cachedModifier = nullptr;

    if (cachedModifier == nullptr) {{
#ifdef ARKUI_CAPI_UNITTEST
        cachedModifier = GeneratedModifier::Get{component}StaticModifier();
#else
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("{component}");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const GENERATED_ArkUI{component}Modifier*>(module->GetStaticModifier());
#endif
    }}

    return cachedModifier;
}}"""

    def find_modifier_file(self, component: str) -> Optional[str]:
        """Find modifier.cpp file for given component."""
        component_lower = component.lower()
        possible_paths = [
            f"frameworks/core/interfaces/native/implementation/{component_lower}_modifier.cpp",
            f"frameworks/core/interfaces/native/implementation/{component}Modifier.cpp",
        ]

        for rel_path in possible_paths:
            full_path = os.path.join(self.root, rel_path)
            if os.path.exists(full_path):
                return full_path

        # Try to search
        for dirpath, _, filenames in os.walk(os.path.join(self.root, "frameworks/core/interfaces/native")):
            for filename in filenames:
                if component_lower in filename.lower() and "modifier.cpp" in filename:
                    return os.path.join(dirpath, filename)

        return None

    def check_has_arkui_capi_unittest(self, file_path: str) -> bool:
        """Check if file already has ARKUI_CAPI_UNITTEST support."""
        if not os.path.exists(file_path):
            return False

        with open(file_path, 'r') as f:
            content = f.read()

        return "ARKUI_CAPI_UNITTEST" in content

    def add_arkui_capi_unittest_support(self, file_path: str, component: str) -> bool:
        """Add ARKUI_CAPI_UNITTEST support to modifier file."""
        if not os.path.exists(file_path):
            print(f"File not found: {file_path}")
            return False

        with open(file_path, 'r') as f:
            content = f.read()

        # Check if already has support
        if "ARKUI_CAPI_UNITTEST" in content:
            print(f"File already has ARKUI_CAPI_UNITTEST support: {file_path}")
            return True

        # Find Get{component}Modifier function
        pattern = rf"const GENERATED_ArkUI{component}Modifier\* Get{component}Modifier\(\)"
        match = re.search(pattern, content)

        if not match:
            print(f"Could not find Get{component}Modifier function in {file_path}")
            return False

        # Get the function
        func_start = match.start()
        # Find end of function (simple approach)
        brace_count = 0
        func_end = func_start
        for i in range(func_start, len(content)):
            if content[i] == '{':
                brace_count += 1
            elif content[i] == '}':
                brace_count -= 1
                if brace_count == 0:
                    func_end = i + 1
                    break

        old_function = content[func_start:func_end]

        # Generate new function
        new_function = self.modifier_template.format(component=component)

        # Replace function
        new_content = content[:func_start] + new_function + content[func_end:]

        # Backup original
        backup_path = file_path + ".bak"
        with open(backup_path, 'w') as f:
            f.write(content)

        # Write new content
        with open(file_path, 'w') as f:
            f.write(new_content)

        print(f"Added ARKUI_CAPI_UNITTEST support to {file_path}")
        print(f"Backup saved to {backup_path}")

        return True

    def add_to_build_config(self, component: str) -> bool:
        """Add static modifier file to test BUILD.gn."""
        build_gn_path = os.path.join(self.root, "test/unittest/capi/BUILD.gn")
        if not os.path.exists(build_gn_path):
            print(f"BUILD.gn not found: {build_gn_path}")
            return False

        component_lower = component.lower()
        static_modifier_file = f"\"$ace_root/frameworks/core/components_ng/pattern/{component_lower}/bridge/{component_lower}_static_modifier.cpp\","

        with open(build_gn_path, 'r') as f:
            content = f.read()

        # Check if already present
        if static_modifier_file in content:
            print(f"Static modifier file already in BUILD.gn: {static_modifier_file}")
            return True

        # Find where to insert (look for similar patterns)
        lines = content.split('\n')
        insertion_point = -1

        for i, line in enumerate(lines):
            if "static_modifier.cpp" in line and "bridge" in line:
                # Insert after this line
                insertion_point = i + 1
                break

        if insertion_point == -1:
            # Look for sources list
            for i, line in enumerate(lines):
                if "sources = [" in line:
                    insertion_point = i + 1
                    # Find the closing bracket
                    for j in range(i, len(lines)):
                        if "]" in lines[j]:
                            insertion_point = j
                            break
                    break

        if insertion_point == -1:
            print("Could not find insertion point in BUILD.gn")
            return False

        # Insert the line
        lines.insert(insertion_point, "    " + static_modifier_file)
        new_content = '\n'.join(lines)

        # Backup
        backup_path = build_gn_path + ".bak"
        with open(backup_path, 'w') as f:
            f.write(content)

        # Write new content
        with open(build_gn_path, 'w') as f:
            f.write(new_content)

        print(f"Added {static_modifier_file} to BUILD.gn")
        print(f"Backup saved to {backup_path}")

        return True

    def fix(self, component: str) -> bool:
        """Fix static modifier issue for given component."""
        print(f"Fixing static modifier issue for component: {component}")

        # 1. Find modifier file
        modifier_file = self.find_modifier_file(component)
        if not modifier_file:
            print(f"Could not find modifier file for component {component}")
            return False

        print(f"Found modifier file: {modifier_file}")

        # 2. Add ARKUI_CAPI_UNITTEST support
        if not self.check_has_arkui_capi_unittest(modifier_file):
            success = self.add_arkui_capi_unittest_support(modifier_file, component)
            if not success:
                print("Failed to add ARKUI_CAPI_UNITTEST support")
                return False
        else:
            print("Modifier file already has ARKUI_CAPI_UNITTEST support")

        # 3. Add to BUILD.gn
        success = self.add_to_build_config(component)
        if not success:
            print("Failed to update BUILD.gn")
            return False

        print(f"Successfully fixed static modifier issue for {component}")
        return True


def main():
    """Main entry point."""
    if len(sys.argv) < 2:
        print("Usage: python fix_static_modifier.py <component_name> [ace_engine_root]")
        print("Example: python fix_static_modifier.py SymbolGlyph")
        return 1

    component = sys.argv[1]
    root = sys.argv[2] if len(sys.argv) > 2 else os.getcwd()

    fixer = StaticModifierFixer(root)
    success = fixer.fix(component)

    return 0 if success else 1


if __name__ == "__main__":
    sys.exit(main())