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
from typing import List, Dict, Tuple, Optional, Set
from dataclasses import dataclass
from datetime import datetime
from enum import Enum

class FileType(Enum):
    JAVASCRIPT = 1
    TYPESCRIPT = 2
    ARKTS = 3
    PYTHON = 4
    CPP = 5
    HEADER = 6
    UNKNOWN = 7

class CopyrightStyle(Enum):
    C_STYLE = 1
    CXX_STYLE = 2
    PYTHON_STYLE = 3
    BASH_STYLE = 4
    UNKNOWN = 5

@dataclass
class CopyrightInfo:
    raw_text: str
    style: CopyrightStyle
    start_year: Optional[int]
    end_year: Optional[int]
    company: Optional[str]
    line_numbers: Tuple[int, int]
    has_range: bool = False

class CopyrightAnalyzer:
    def __init__(self, target_year=None, target_end_year=None):
        self.copyright_patterns = {
            'c_style': r'/\*\s*\n\s*\*\s*Copyright\s*\(c\)\s*(\d{4})(?:-(\d{4}))?\s*([^*]+)\s*\*/',
            'cxx_style': r'//\s*Copyright\s*\(c\)\s*(\d{4})(?:-(\d{4}))?\s*([^\n]+)',
            'python_style': r'#\s*Copyright\s*\(c\)\s*(\d{4})(?:-(\d{4}))?\s*([^\n]+)',
            'bash_style': r'#\s*Copyright\s*\(c\)\s*(\d{4})(?:-(\d{4}))?\s*([^\n]+)'
        }
        
        current_year = datetime.now().year
        self.target_year = target_year if target_year is not None else current_year
        self.target_end_year = target_end_year if target_end_year is not None else current_year + 1
        
        self.file_type_mapping = {
            '.js': FileType.JAVASCRIPT,
            '.jsx': FileType.JAVASCRIPT,
            '.ts': FileType.TYPESCRIPT,
            '.tsx': FileType.TYPESCRIPT,
            '.ets': FileType.ARKTS,
            '.py': FileType.PYTHON,
            '.cpp': FileType.CPP,
            '.cc': FileType.CPP,
            '.cxx': FileType.CPP,
            '.c': FileType.CPP,
            '.h': FileType.HEADER,
            '.hpp': FileType.HEADER,
            '.hxx': FileType.HEADER
        }
        
        self.style_mapping = {
            FileType.JAVASCRIPT: CopyrightStyle.CXX_STYLE,
            FileType.TYPESCRIPT: CopyrightStyle.CXX_STYLE,
            FileType.ARKTS: CopyrightStyle.CXX_STYLE,
            FileType.PYTHON: CopyrightStyle.PYTHON_STYLE,
            FileType.CPP: CopyrightStyle.C_STYLE,
            FileType.HEADER: CopyrightStyle.C_STYLE
        }
        
        self.statistics = {
            'total_files': 0,
            'files_with_copyright': 0,
            'files_updated': 0,
            'files_skipped': 0,
            'files_with_errors': 0,
            'copyrights_found': 0,
            'copyrights_updated': 0,
            'by_file_type': {},
            'by_style': {}
        }
    
    def detect_file_type(self, filepath: str) -> FileType:
        for ext, file_type in self.file_type_mapping.items():
            if filepath.endswith(ext):
                return file_type
        return FileType.UNKNOWN
    
    def expected_style_for_file(self, file_type: FileType) -> CopyrightStyle:
        return self.style_mapping.get(file_type, CopyrightStyle.UNKNOWN)
    
    def find_copyright_in_content(self, content: str) -> List[CopyrightInfo]:
        copyrights = []
        lines = content.split('\n')
        
        for pattern_name, pattern in self.copyright_patterns.items():
            for match in re.finditer(pattern, content, re.MULTILINE):
                start_pos = match.start()
                end_pos = match.end()
                
                start_line = content[:start_pos].count('\n') + 1
                end_line = content[:end_pos].count('\n') + 1
                
                start_year = int(match.group(1)) if match.group(1) else None
                end_year = int(match.group(2)) if match.group(2) else None
                company = match.group(3).strip() if match.group(3) else None
                
                style = CopyrightStyle.UNKNOWN
                if pattern_name == 'c_style':
                    style = CopyrightStyle.C_STYLE
                elif pattern_name == 'cxx_style':
                    style = CopyrightStyle.CXX_STYLE
                elif pattern_name == 'python_style':
                    style = CopyrightStyle.PYTHON_STYLE
                elif pattern_name == 'bash_style':
                    style = CopyrightStyle.BASH_STYLE
                
                has_range = end_year is not None
                
                copyright_info = CopyrightInfo(
                    raw_text=match.group(0),
                    style=style,
                    start_year=start_year,
                    end_year=end_year,
                    company=company,
                    line_numbers=(start_line, end_line),
                    has_range=has_range
                )
                
                copyrights.append(copyright_info)
        
        return copyrights
    
    def should_update_copyright(self, copyright_info: CopyrightInfo) -> bool:
        if copyright_info.start_year != self.target_year:
            return False
        
        if copyright_info.end_year is None:
            return True
        
        if copyright_info.end_year < self.target_end_year:
            return True
        
        return False
    
    def update_copyright_text(self, copyright_info: CopyrightInfo) -> str:
        raw_text = copyright_info.raw_text
        style = copyright_info.style
        company = copyright_info.company if copyright_info.company else ''
        
        if style == CopyrightStyle.C_STYLE:
            lines = raw_text.split('\n')
            new_lines = []
            for line in lines:
                if 'Copyright' in line:
                    if self.target_end_year:
                        new_line = line.replace(f'Copyright (c) {copyright_info.start_year}', 
                                              f'Copyright (c) {self.target_year}-{self.target_end_year}')
                        if copyright_info.has_range:
                            new_line = new_line.replace(f'{copyright_info.start_year}-{copyright_info.end_year}', 
                                                       f'{self.target_year}-{self.target_end_year}')
                    else:
                        new_line = line.replace(f'Copyright (c) {copyright_info.start_year}', 
                                              f'Copyright (c) {self.target_year}')
                    new_lines.append(new_line)
                else:
                    new_lines.append(line)
            return '\n'.join(new_lines)
        
        elif style == CopyrightStyle.CXX_STYLE:
            new_text = raw_text.replace(f'Copyright (c) {copyright_info.start_year}', 
                                       f'Copyright (c) {self.target_year}-{self.target_end_year}')
            if copyright_info.has_range:
                new_text = new_text.replace(f'{copyright_info.start_year}-{copyright_info.end_year}', 
                                          f'{self.target_year}-{self.target_end_year}')
            return new_text
        
        elif style in [CopyrightStyle.PYTHON_STYLE, CopyrightStyle.BASH_STYLE]:
            new_text = raw_text.replace(f'Copyright (c) {copyright_info.start_year}', 
                                       f'Copyright (c) {self.target_year}-{self.target_end_year}')
            if copyright_info.has_range:
                new_text = new_text.replace(f'{copyright_info.start_year}-{copyright_info.end_year}', 
                                          f'{self.target_year}-{self.target_end_year}')
            return new_text
        
        return raw_text
    
    def process_file(self, filepath: str) -> bool:
        try:
            file_type = self.detect_file_type(filepath)
            if file_type == FileType.UNKNOWN:
                return False
            
            with open(filepath, 'r', encoding='utf-8') as file:
                content = file.read()
            
            copyrights = self.find_copyright_in_content(content)
            
            if not copyrights:
                return False
            
            self.statistics['files_with_copyright'] += 1
            self.statistics['copyrights_found'] += len(copyrights)
            
            updated_content = content
            file_modified = False
            
            for copyright_info in copyrights:
                if self.should_update_copyright(copyright_info):
                    updated_text = self.update_copyright_text(copyright_info)
                    updated_content = updated_content.replace(copyright_info.raw_text, updated_text, 1)
                    file_modified = True
                    self.statistics['copyrights_updated'] += 1
                else:
                    self.statistics['files_skipped'] += 1
            
            if file_modified:
                temp_filepath = filepath + '.tmp'
                try:
                    with open(temp_filepath, 'w', encoding='utf-8') as file:
                        file.write(updated_content)
                    os.replace(temp_filepath, filepath)
                    self.statistics['files_updated'] += 1
                except Exception as write_error:
                    if os.path.exists(temp_filepath):
                        os.remove(temp_filepath)
                    raise write_error
                return True
            
            return False
        
        except Exception as e:
            print(f'Error processing {filepath}: {str(e)}', file=sys.stderr)
            self.statistics['files_with_errors'] += 1
            return False
    
    def process_directory(self, root_dir: str) -> Dict[str, int]:
        for dirpath, _, filenames in os.walk(root_dir):
            for filename in filenames:
                filepath = os.path.join(dirpath, filename)
                self.process_file(filepath)
        
        return self.statistics
    
    def print_statistics(self):
        print('=== Copyright Year Update Statistics ===')
        print(f'Total files scanned: {self.statistics["total_files"]}')
        print(f'Files with copyright: {self.statistics["files_with_copyright"]}')
        print(f'Files updated: {self.statistics["files_updated"]}')
        print(f'Files skipped (no update needed): {self.statistics["files_skipped"]}')
        print(f'Files with errors: {self.statistics["files_with_errors"]}')
        print(f'Copyrights found: {self.statistics["copyrights_found"]}')
        print(f'Copyrights updated: {self.statistics["copyrights_updated"]}')
        
        if self.statistics['copyrights_found'] > 0:
            update_rate = (self.statistics['copyrights_updated'] / self.statistics['copyrights_found']) * 100
            print(f'Update rate: {update_rate:.2f}%')

def main():
    analyzer = CopyrightAnalyzer()
    current_dir = os.getcwd()
    
    print(f'Starting copyright year update in: {current_dir}')
    print(f'Target year range: {analyzer.target_year}-{analyzer.target_end_year}')
    print('Processing files...\n')
    
    stats = analyzer.process_directory(current_dir)
    
    print('\nUpdate completed.')
    analyzer.print_statistics()

if __name__ == "__main__":
    main()
