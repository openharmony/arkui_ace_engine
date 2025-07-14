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

project(
    'es2panda_interop',
    'cpp',
    version: '1.0',
    default_options: [
        'cpp_std=c++17',
        'buildtype=release',
    ],
)

sources = [
    './src/common.cc',
    './src/bridges.cc',
    './src/generated/bridges.cc',
    get_option('interop_src_dir') / 'common-interop.cc',
    get_option('interop_src_dir') / 'callback-resource.cc',
    get_option('interop_src_dir') / 'interop-logging.cc',
    get_option('interop_src_dir') / 'napi/convertors-napi.cc',
]

cflags = [
    '-DKOALA_INTEROP_MODULE=NativeModule',
    '-DINTEROP_LIBRARY_NAME=' + get_option('lib_name'),
    '-DKOALA_USE_NODE_VM',
    '-DKOALA_NAPI',
]

if (target_machine.system() == 'windows')
    cflags += ['-DKOALA_WINDOWS']
    if (meson.get_compiler('cpp').get_id() == 'msvc')
        # apply node.exe symbol loading hook
        sources += [
            get_option('interop_src_dir') / 'napi/win-dynamic-node.cc'
        ]
    endif
else
    cflags += ['-DKOALA_LINUX']
endif

arch = target_machine.cpu()

oses = { 'darwin': 'macos' }  # rename meson default names to convenient ones
archs = { 'x86_64': 'x64', 'aarch64': 'arm64', 'armv7-a': 'arm32', 'wasm32': 'wasm' }

os = target_machine.system()
os = oses.get(os, os)
arch = target_machine.cpu()
arch = archs.get(arch, arch)

cflags_cross = []
cflags_host = []
suffix_host = '_' + arch
suffix_cross = ''

if get_option('cross_compile')
if arch == 'arm64'
cflags_cross = ['--target=x86_64-linux-gnu']
suffix_cross = '_x64'
endif
if arch == 'x64'
cflags_cross = ['--target=aarch64-linux-gnu']
suffix_cross = '_arm64'
endif
endif

shared_library(
    get_option('lib_name') + suffix_host,
    sources,
    override_options: [
        'b_lundef=false',
    ],
    install: true,
    name_prefix: '',
    name_suffix: 'node',
    include_directories: [
        './src/',
        get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda/public',
        get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda',
        get_option('interop_src_dir'),
        get_option('interop_src_dir') / 'types',
        get_option('interop_src_dir') / 'napi',
        get_option('node_modules_dir') / 'node-api-headers/include',
        get_option('node_modules_dir') / 'node-addon-api',
    ],
    cpp_args: cflags + cflags_host,
    link_args: [cflags_host],
    dependencies: []
)

if get_option('cross_compile')
    # sudo apt install g++-aarch64-linux-gnu binutils-aarch64-linux-gnu
    shared_library(
        get_option('lib_name') + suffix_cross,
        sources,
        override_options: [
            'b_lundef=false',
        ],
        install: true,
        name_prefix: '',
        name_suffix: 'node',
        include_directories: [
            './src/',
            get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda/public',
            get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda',
            get_option('interop_src_dir'),
            get_option('interop_src_dir') / 'types',
            get_option('interop_src_dir') / 'napi',
            get_option('node_modules_dir') / 'node-api-headers/include',
            get_option('node_modules_dir') / 'node-addon-api',
        ],
        cpp_args: cflags  + cflags_cross,
        link_args: [cflags_cross],
        dependencies: []
    )
endif