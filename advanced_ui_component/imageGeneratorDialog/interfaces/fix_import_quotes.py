#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright (c) 2025 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import re
import sys
from typing import List, Dict, Tuple, Optional
from dataclasses import dataclass
from enum import Enum

class ImportType(Enum):
    NAMED = 1
    DEFAULT = 2
    NAMESPACE = 3
    SIDE_EFFECT = 4

class QuoteStyle(Enum):
    SINGLE = "'"
    DOUBLE = '"'

@dataclass
class ImportStatement:
    raw_text: str
    import_type: ImportType
    module_path: str
    imported_names: List[str]
    quote_style: QuoteStyle
    line_number: int
    has_as_alias: bool = False

class ImportAnalyzer:
    def __init__(self):
        self.import_patterns = {
            'named': r'import\s*\{\s*([^}]+)\s*\}\s*from\s*([\'"])([^\'"]+)([\'"])',
            'default': r'import\s+([a-zA-Z_$][a-zA-Z0-9_$]*)\s*,?\s*\{\s*([^}]+)\s*\}\s*from\s*([\'"])([^\'"]+)([\'"])',
            'default_only': r'import\s+([a-zA-Z_$][a-zA-Z0-9_$]*)\s+from\s*([\'"])([^\'"]+)([\'"])',
            'namespace': r'import\s*\*\s+as\s+([a-zA-Z_$][a-zA-Z0-9_$]*)\s+from\s*([\'"])([^\'"]+)([\'"])',
            'side_effect': r'import\s*([\'"])([^\'"]+)([\'"])'
        }
        
        self.exclude_patterns = [
            r'^\.\/',
            r'^\.\.\/',
            r'^@ohos\/',
            r'^@kit\.'
        ]
        
        self.statistics = {
            'total_files': 0,
            'total_imports': 0,
            'converted_imports': 0,
            'skipped_imports': 0,
            'error_imports': 0,
            'by_type': {},
            'by_quote_style': {}
        }
    
    def should_process_file(self, filepath) -> bool:
        valid_extensions = ['.js', '.ets', '.ts', '.tsx', '.jsx']
        return any(filepath.endswith(ext) for ext in valid_extensions)
    
    def should_convert_import(self, import_stmt: ImportStatement) -> bool:
        for pattern in self.exclude_patterns:
            if re.match(pattern, import_stmt.module_path):
                return False
        return True
    
    def parse_import_line(self, line: str, line_number: int) -> Optional[ImportStatement]:
        line = line.strip()
        if not line.startswith('import'):
            return None
        
        for pattern_name, pattern in self.import_patterns.items():
            match = re.match(pattern, line)
            if match:
                return self._create_import_from_match(match, pattern_name, line, line_number)
        
        return None
    
    def _create_import_from_match(self, match, pattern_name: str, raw_text: str, line_number: int) -> ImportStatement:
        if pattern_name == 'named':
            imported_text = match.group(1).strip()
            names = [name.strip() for name in imported_text.split(',')]
            return ImportStatement(
                raw_text=raw_text,
                import_type=ImportType.NAMED,
                module_path=match.group(3),
                imported_names=names,
                quote_style=QuoteStyle(match.group(2)),
                line_number=line_number,
                has_as_alias=any('as' in name for name in names)
            )
        
        elif pattern_name == 'default_only':
            return ImportStatement(
                raw_text=raw_text,
                import_type=ImportType.DEFAULT,
                module_path=match.group(3),
                imported_names=[match.group(1)],
                quote_style=QuoteStyle(match.group(2)),
                line_number=line_number
            )
        
        elif pattern_name == 'namespace':
            return ImportStatement(
                raw_text=raw_text,
                import_type=ImportType.NAMESPACE,
                module_path=match.group(3),
                imported_names=[match.group(1)],
                quote_style=QuoteStyle(match.group(2)),
                line_number=line_number
            )
        
        elif pattern_name == 'side_effect':
            return ImportStatement(
                raw_text=raw_text,
                import_type=ImportType.SIDE_EFFECT,
                module_path=match.group(2),
                imported_names=[],
                quote_style=QuoteStyle(match.group(1)),
                line_number=line_number
            )
        
        return None
    
    def convert_import_quotes(self, import_stmt: ImportStatement) -> str:
        if import_stmt.quote_style == QuoteStyle.SINGLE:
            return import_stmt.raw_text
        
        raw_text = import_stmt.raw_text
        module_path = import_stmt.module_path
        
        for pattern_name, pattern in self.import_patterns.items():
            match = re.search(pattern, raw_text)
            if match:
                groups = match.groups()
                for i, group in enumerate(groups):
                    if group == module_path:
                        start_pos = match.start(i + 1)
                        end_pos = match.end(i + 1)
                        converted = raw_text[:start_pos] + "'" + module_path + "'" + raw_text[end_pos:]
                        return converted
        
        return raw_text
    
    def process_file(self, filepath: str) -> bool:
        try:
            with open(filepath, 'r', encoding='utf-8') as file:
                lines = file.readlines()
            
            imports_found = []
            for i, line in enumerate(lines, 1):
                import_stmt = self.parse_import_line(line, i)
                if import_stmt:
                    imports_found.append(import_stmt)
            
            if not imports_found:
                return False
            
            self.statistics['total_files'] += 1
            self.statistics['total_imports'] += len(imports_found)
            
            modified_lines = lines.copy()
            modified = False
            
            for import_stmt in imports_found:
                if import_stmt.quote_style == QuoteStyle.DOUBLE:
                    if self.should_convert_import(import_stmt):
                        converted_line = self.convert_import_quotes(import_stmt)
                        line_idx = import_stmt.line_number - 1
                        if modified_lines[line_idx].strip() != converted_line.strip():
                            modified_lines[line_idx] = converted_line + '\n'
                            modified = True
                            self.statistics['converted_imports'] += 1
                    else:
                        self.statistics['skipped_imports'] += 1
                else:
                    self.statistics['skipped_imports'] += 1
            
            if modified:
                temp_filepath = filepath + '.tmp'
                try:
                    with open(temp_filepath, 'w', encoding='utf-8') as file:
                        file.writelines(modified_lines)
                    os.replace(temp_filepath, filepath)
                except Exception as write_error:
                    if os.path.exists(temp_filepath):
                        os.remove(temp_filepath)
                    raise write_error
                return True
            
            return False
        
        except Exception as e:
            print(f'Error processing {filepath}: {str(e)}', file=sys.stderr)
            self.statistics['error_imports'] += 1
            return False
    
    def process_directory(self, root_dir: str) -> Dict[str, int]:
        for dirpath, _, filenames in os.walk(root_dir):
            for filename in filenames:
                filepath = os.path.join(dirpath, filename)
                if self.should_process_file(filepath):
                    self.process_file(filepath)
        
        return self.statistics
    
    def print_statistics(self):
        print('=== Import Quote Conversion Statistics ===')
        print(f'Total files processed: {self.statistics["total_files"]}')
        print(f'Total imports found: {self.statistics["total_imports"]}')
        print(f'Imports converted: {self.statistics["converted_imports"]}')
        print(f'Imports skipped: {self.statistics["skipped_imports"]}')
        print(f'Errors encountered: {self.statistics["error_imports"]}')
        
        if self.statistics['total_imports'] > 0:
            conversion_rate = (self.statistics['converted_imports'] / self.statistics['total_imports']) * 100
            print(f'Conversion rate: {conversion_rate:.2f}%')

def main():
    analyzer = ImportAnalyzer()
    current_dir = os.getcwd()
    
    print(f'Starting import quote conversion in: {current_dir}')
    print('Processing files...\n')
    
    stats = analyzer.process_directory(current_dir)
    
    print('\nConversion completed.')
    analyzer.print_statistics()

if __name__ == "__main__":
    main()
