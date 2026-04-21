#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (c) 2026 Huawei Device Co., Ltd.
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
import struct


def open_new_resource_index_v2(file_path):
    if not os.path.exists(file_path):
        raise Exception("not found:" + file_path)

    with open(file_path, "rb") as fp_resource_index:
        version = fp_resource_index.read(128)
        length = struct.unpack("I", fp_resource_index.read(4))[0]
        key_count = struct.unpack("I", fp_resource_index.read(4))[0]
        data_block_offset = struct.unpack("I", fp_resource_index.read(4))[0]

        key_configs = {}
        for i in range(key_count):
            key_tag = fp_resource_index.read(4)
            config_id = struct.unpack("I", fp_resource_index.read(4))[0]
            param_count = struct.unpack("I", fp_resource_index.read(4))[0]
            key_params = []
            for j in range(param_count):
                key_type = struct.unpack("I", fp_resource_index.read(4))[0]
                value = struct.unpack("I", fp_resource_index.read(4))[0]
                key_params.append((key_type, value))
            key_configs[config_id] = key_params

        id_set_tag = fp_resource_index.read(4)
        id_set_length = struct.unpack("I", fp_resource_index.read(4))[0]
        type_count = struct.unpack("I", fp_resource_index.read(4))[0]
        id_count = struct.unpack("I", fp_resource_index.read(4))[0]

        res_types = {}
        for i in range(type_count):
            res_type = struct.unpack("I", fp_resource_index.read(4))[0]
            res_type_length = struct.unpack("I", fp_resource_index.read(4))[0]
            res_id_count = struct.unpack("I", fp_resource_index.read(4))[0]
            res_indexs = {}
            for j in range(res_id_count):
                res_id = struct.unpack("I", fp_resource_index.read(4))[0]
                offset = struct.unpack("I", fp_resource_index.read(4))[0]
                name_length = struct.unpack("I", fp_resource_index.read(4))[0]
                name = fp_resource_index.read(name_length).decode('utf-8')
                res_indexs[res_id] = {'offset': offset, 'name': name}
            res_types[res_type] = res_indexs

        data_header_tag = fp_resource_index.read(4)
        data_header_length = struct.unpack("I", fp_resource_index.read(4))[0]
        data_id_count = struct.unpack("I", fp_resource_index.read(4))[0]

        res_infos = {}
        for i in range(data_id_count):
            res_id = struct.unpack("I", fp_resource_index.read(4))[0]
            res_info_length = struct.unpack("I", fp_resource_index.read(4))[0]
            value_count = struct.unpack("I", fp_resource_index.read(4))[0]
            data_offsets = {}
            for j in range(value_count):
                config_id = struct.unpack("I", fp_resource_index.read(4))[0]
                offset = struct.unpack("I", fp_resource_index.read(4))[0]
                data_offsets[config_id] = offset
            res_infos[res_id] = data_offsets

        data_pool_start = data_block_offset + data_header_length
        fp_resource_index.seek(data_pool_start)
        data_pool = fp_resource_index.read()

    third_data = {}
    for res_type, res_indexs in res_types.items():
        for res_id, res_info in res_indexs.items():
            if res_id not in res_infos:
                continue
            data_offsets = res_infos[res_id]
            for config_id, offset in data_offsets.items():
                key_params = key_configs.get(config_id, [])
                key_str = ""
                for idx, (key_type, value) in enumerate(key_params):
                    if idx == 0:
                        key_str = "{}:{}".format(key_type, value)
                    else:
                        key_str = "{}-{}:{}".format(key_str, key_type, value)
                real_offset = offset - data_pool_start
                if real_offset >= 0 and real_offset < len(data_pool):
                    data_len = struct.unpack("H", data_pool[real_offset:real_offset+2])[0]
                    data = data_pool[real_offset+2:real_offset+2+data_len]
                    
                    array_value = ""
                    if res_type == 10 or res_type == 11 or res_type == 16 or res_type == 17 or res_type == 22:
                        array_data = data
                        array_pos = 0
                        while array_pos < len(array_data) - 1:
                            value_len_l = struct.unpack("B", array_data[0 + array_pos:1 + array_pos])[0]
                            value_len_h = struct.unpack("B", array_data[1 + array_pos:2 + array_pos])[0]
                            value_len = value_len_l + value_len_h * 256
                            array_value = "{}<{}>".format(array_value, str(array_data[2 + array_pos:2 + value_len + array_pos]))
                            array_pos = array_pos + 2 + value_len + 1
                    else:
                        array_value = data.decode('utf-8', errors='ignore')
                    
                    if key_str not in third_data:
                        third_data[key_str] = {}
                    third_data[key_str][res_id] = [array_value, res_info['name']]

    def int_to_str(int_n):
        buf = ""
        i = 0
        while i < 4:
            a = ((int_n >> (3 - i) * 8) & 0xff)
            if a != 0:
                buf = buf + chr(a)
            i = i + 1
        return buf

    def key_to_dir_name(key_str):
        if key_str == "":
            return "base"
        
        resolution_map = {120: "sdpi", 160: "mdpi", 240: "ldpi", 320: "xldpi", 480: "xxldpi", 640: "xxxldpi"}
        orientation_map = {0: "vertical", 1: "horizontal"}
        device_map = {0: "phone", 1: "tablet", 2: "car", 3: "pc", 4: "tv", 5: "speaker",
                      6: "wearable", 7: "2in1", 8: "glasses", 9: "headset"}
        night_mode_map = {0: "dark", 1: "light"}
        input_device_map = {0: "pointingdevice"}
        
        dir_name = ""
        key_sets = key_str.split("-")
        for key_item in key_sets:
            key_s = key_item.split(":")
            key_type = int(key_s[0])
            value = int(key_s[1])
            
            if key_type == 0 or key_type == 1 or key_type == 5:
                dir_name = dir_name + int_to_str(value)
            elif key_type == 2:
                dir_name = dir_name + resolution_map.get(value, "")
            elif key_type == 3:
                dir_name = dir_name + orientation_map.get(value, "")
            elif key_type == 4:
                dir_name = dir_name + device_map.get(value, "")
            elif key_type == 6:
                dir_name = dir_name + night_mode_map.get(value, "")
            elif key_type == 7:
                dir_name = dir_name + "mcc" + str(value)
            elif key_type == 8:
                dir_name = dir_name + "mnc" + str(value)
            elif key_type == 10:
                dir_name = dir_name + input_device_map.get(value, "")
        
        return dir_name

    sorted_third_data = {}
    for key_str in sorted(third_data.keys(), key=lambda k: key_to_dir_name(k)):
        sorted_ids = sorted(third_data[key_str].keys())
        sorted_third_data[key_str] = {res_id: third_data[key_str][res_id] for res_id in sorted_ids}

    return sorted_third_data

